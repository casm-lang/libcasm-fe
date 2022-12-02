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

      case symbol_kind::S_VariableSelection: // VariableSelection
        value.YY_MOVE_OR_COPY< VariableSelection::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VariableSelections: // VariableSelections
        value.YY_MOVE_OR_COPY< VariableSelections::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_VariableSelection: // VariableSelection
        value.move< VariableSelection::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VariableSelections: // VariableSelections
        value.move< VariableSelections::Ptr > (YY_MOVE (that.value));
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

      case symbol_kind::S_VariableSelection: // VariableSelection
        value.copy< VariableSelection::Ptr > (that.value);
        break;

      case symbol_kind::S_VariableSelections: // VariableSelections
        value.copy< VariableSelections::Ptr > (that.value);
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

      case symbol_kind::S_VariableSelection: // VariableSelection
        value.move< VariableSelection::Ptr > (that.value);
        break;

      case symbol_kind::S_VariableSelections: // VariableSelections
        value.move< VariableSelections::Ptr > (that.value);
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

      case symbol_kind::S_VariableSelection: // VariableSelection
        yylhs.value.emplace< VariableSelection::Ptr > ();
        break;

      case symbol_kind::S_VariableSelections: // VariableSelections
        yylhs.value.emplace< VariableSelections::Ptr > ();
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
#line 448 "../../obj/src/GrammarParser.y"
  {
      const auto& cst = CST::make< CST::Root >(
          yylhs.location, yystack_[1].value.as < HeaderDefinition::Ptr > (), yystack_[0].value.as < Definitions::Ptr > (), m_lexer.fetchSpansAndReset() );
      m_specification.setCst( cst );
  }
#line 3006 "GrammarParser.cpp"
    break;

  case 3: // Header: Attributes "CASM"
#line 458 "../../obj/src/GrammarParser.y"
  {
      auto definition = CST::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 3016 "GrammarParser.cpp"
    break;

  case 4: // Header: "CASM"
#line 464 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < HeaderDefinition::Ptr > () = CST::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3024 "GrammarParser.cpp"
    break;

  case 5: // Definitions: Definitions AttributedDefinition
#line 472 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3034 "GrammarParser.cpp"
    break;

  case 6: // Definitions: AttributedDefinition
#line 478 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3044 "GrammarParser.cpp"
    break;

  case 7: // AttributedDefinition: Attributes Definition
#line 488 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3054 "GrammarParser.cpp"
    break;

  case 8: // AttributedDefinition: Definition
#line 494 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 3062 "GrammarParser.cpp"
    break;

  case 9: // AttributedDefinition: error
#line 498 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 3070 "GrammarParser.cpp"
    break;

  case 10: // Definition: InitDefinition
#line 506 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 3078 "GrammarParser.cpp"
    break;

  case 11: // Definition: EnumerationDefinition
#line 510 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 3086 "GrammarParser.cpp"
    break;

  case 12: // Definition: DerivedDefinition
#line 514 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3094 "GrammarParser.cpp"
    break;

  case 13: // Definition: RuleDefinition
#line 518 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3102 "GrammarParser.cpp"
    break;

  case 14: // Definition: FunctionDefinition
#line 522 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 3110 "GrammarParser.cpp"
    break;

  case 15: // Definition: UsingDefinition
#line 526 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 3118 "GrammarParser.cpp"
    break;

  case 16: // Definition: UsingPathDefinition
#line 530 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingPathDefinition::Ptr > ();
  }
#line 3126 "GrammarParser.cpp"
    break;

  case 17: // Definition: InvariantDefinition
#line 534 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 3134 "GrammarParser.cpp"
    break;

  case 18: // Definition: ImportDefinition
#line 538 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 3142 "GrammarParser.cpp"
    break;

  case 19: // Definition: StructureDefinition
#line 542 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < StructureDefinition::Ptr > ();
  }
#line 3150 "GrammarParser.cpp"
    break;

  case 20: // Definition: BehaviorDefinition
#line 546 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < BehaviorDefinition::Ptr > ();
  }
#line 3158 "GrammarParser.cpp"
    break;

  case 21: // Definition: ImplementDefinition
#line 550 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImplementDefinition::Ptr > ();
  }
#line 3166 "GrammarParser.cpp"
    break;

  case 22: // Definition: DomainDefinition
#line 554 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DomainDefinition::Ptr > ();
  }
#line 3174 "GrammarParser.cpp"
    break;

  case 23: // Definition: BuiltinDefinition
#line 558 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < BuiltinDefinition::Ptr > ();
  }
#line 3182 "GrammarParser.cpp"
    break;

  case 24: // InitDefinition: "init" IdentifierPath
#line 566 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = CST::make< InitDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3190 "GrammarParser.cpp"
    break;

  case 25: // InitDefinition: "init" "{" MappedExpressions "}"
#line 570 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = CST::make< InitDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < MappedExpressions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3198 "GrammarParser.cpp"
    break;

  case 26: // EnumerationDefinition: "enumeration" Identifier "=" "{" Enumerators "}"
#line 578 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumerationDefinition::Ptr > () = CST::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3206 "GrammarParser.cpp"
    break;

  case 27: // DerivedDefinition: "derived" Identifier "->" Type "=" Term
#line 586 "../../obj/src/GrammarParser.y"
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3215 "GrammarParser.cpp"
    break;

  case 28: // DerivedDefinition: "derived" Identifier "(" Parameters ")" "->" Type "=" Term
#line 591 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3225 "GrammarParser.cpp"
    break;

  case 29: // DerivedDefinition: "derived" Identifier "(" MethodParameters ")" "->" Type "=" Term
#line 597 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = CST::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3235 "GrammarParser.cpp"
    break;

  case 30: // DerivedDefinition: "derived" Identifier "(" error ")" "->" Type "=" Term
#line 603 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 3243 "GrammarParser.cpp"
    break;

  case 31: // RuleDefinition: "rule" Identifier "=" Rule
#line 611 "../../obj/src/GrammarParser.y"
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3253 "GrammarParser.cpp"
    break;

  case 32: // RuleDefinition: "rule" Identifier "->" Type "=" Rule
#line 617 "../../obj/src/GrammarParser.y"
  {
      const auto params = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3262 "GrammarParser.cpp"
    break;

  case 33: // RuleDefinition: "rule" Identifier "(" Parameters ")" "=" Rule
#line 622 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < CST::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
  }
#line 3273 "GrammarParser.cpp"
    break;

  case 34: // RuleDefinition: "rule" Identifier "(" Parameters ")" "->" Type "=" Rule
#line 629 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3283 "GrammarParser.cpp"
    break;

  case 35: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "=" Rule
#line 635 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < CST::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
  }
#line 3294 "GrammarParser.cpp"
    break;

  case 36: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "->" Type "=" Rule
#line 642 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = CST::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < CST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < CST::Token::Ptr > () );
  }
#line 3304 "GrammarParser.cpp"
    break;

  case 37: // RuleDefinition: "rule" Identifier "(" error ")" "=" Rule
#line 648 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3312 "GrammarParser.cpp"
    break;

  case 38: // RuleDefinition: "rule" Identifier "(" error ")" "->" Type "=" Rule
#line 652 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3320 "GrammarParser.cpp"
    break;

  case 39: // FunctionDefinition: "function" Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 660 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = CST::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < CST::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
  }
#line 3328 "GrammarParser.cpp"
    break;

  case 40: // EnumeratorDefinition: Identifier
#line 668 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = CST::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3336 "GrammarParser.cpp"
    break;

  case 41: // EnumeratorDefinition: Attributes Identifier
#line 672 "../../obj/src/GrammarParser.y"
  {
      auto enumerator = CST::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 3346 "GrammarParser.cpp"
    break;

  case 42: // EnumeratorDefinition: error
#line 678 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 3354 "GrammarParser.cpp"
    break;

  case 43: // Enumerators: Enumerators "," EnumeratorDefinition
#line 686 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3365 "GrammarParser.cpp"
    break;

  case 44: // Enumerators: EnumeratorDefinition
#line 693 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = CST::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3375 "GrammarParser.cpp"
    break;

  case 45: // UsingDefinition: "using" Identifier "=" Type
#line 703 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingDefinition::Ptr > () = CST::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3383 "GrammarParser.cpp"
    break;

  case 46: // UsingPathDefinition: "using" IdentifierPath
#line 711 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = CST::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3391 "GrammarParser.cpp"
    break;

  case 47: // UsingPathDefinition: "using" IdentifierPath "::" "*"
#line 715 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = CST::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3399 "GrammarParser.cpp"
    break;

  case 48: // InvariantDefinition: "invariant" Identifier "=" Term
#line 723 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InvariantDefinition::Ptr > () = CST::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3407 "GrammarParser.cpp"
    break;

  case 49: // ImportDefinition: "import" IdentifierPath
#line 731 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = CST::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3415 "GrammarParser.cpp"
    break;

  case 50: // ImportDefinition: "import" IdentifierPath "as" Identifier
#line 735 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = CST::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3423 "GrammarParser.cpp"
    break;

  case 51: // StructureDefinition: "structure" Identifier "=" "{" StructureDefinitionList "}"
#line 747 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < StructureDefinition::Ptr > () = CST::make< StructureDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < FunctionDefinitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3431 "GrammarParser.cpp"
    break;

  case 52: // StructureDefinitionList: StructureDefinitionList StructureDefinitionElement
#line 754 "../../obj/src/GrammarParser.y"
  {
      auto functions = yystack_[1].value.as < FunctionDefinitions::Ptr > ();
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3441 "GrammarParser.cpp"
    break;

  case 53: // StructureDefinitionList: StructureDefinitionElement
#line 760 "../../obj/src/GrammarParser.y"
  {
      auto functions = CST::make< FunctionDefinitions >( yylhs.location );
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3451 "GrammarParser.cpp"
    break;

  case 54: // StructureDefinitionElement: Attributes FunctionDefinition
#line 769 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 3461 "GrammarParser.cpp"
    break;

  case 55: // StructureDefinitionElement: FunctionDefinition
#line 775 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 3469 "GrammarParser.cpp"
    break;

  case 56: // BehaviorDefinition: "behavior" Type "=" "{" BehaviorDefinitionList "}"
#line 787 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BehaviorDefinition::Ptr > () = CST::make< BehaviorDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3477 "GrammarParser.cpp"
    break;

  case 57: // BehaviorDefinitionElement: Attributes Declaration
#line 795 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Declaration::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3487 "GrammarParser.cpp"
    break;

  case 58: // BehaviorDefinitionElement: Declaration
#line 801 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Declaration::Ptr > ();
  }
#line 3495 "GrammarParser.cpp"
    break;

  case 59: // BehaviorDefinitionElement: Attributes DerivedDefinition
#line 805 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < DerivedDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3505 "GrammarParser.cpp"
    break;

  case 60: // BehaviorDefinitionElement: DerivedDefinition
#line 811 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3513 "GrammarParser.cpp"
    break;

  case 61: // BehaviorDefinitionElement: Attributes RuleDefinition
#line 815 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < RuleDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3523 "GrammarParser.cpp"
    break;

  case 62: // BehaviorDefinitionElement: RuleDefinition
#line 821 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3531 "GrammarParser.cpp"
    break;

  case 63: // BehaviorDefinitionList: BehaviorDefinitionList BehaviorDefinitionElement
#line 828 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3541 "GrammarParser.cpp"
    break;

  case 64: // BehaviorDefinitionList: BehaviorDefinitionElement
#line 834 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3551 "GrammarParser.cpp"
    break;

  case 65: // ImplementDefinition: "implement" Type "=" "{" ImplementDefinitionList "}"
#line 848 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementDefinition::Ptr > () = CST::make< ImplementDefinition >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3559 "GrammarParser.cpp"
    break;

  case 66: // ImplementDefinition: "implement" Type "for" Type "=" "{" ImplementDefinitionList "}"
#line 852 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementDefinition::Ptr > () = CST::make< ImplementDefinition >( yylhs.location, yystack_[7].value.as < CST::Token::Ptr > (), yystack_[6].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3567 "GrammarParser.cpp"
    break;

  case 67: // ImplementDefinitionList: ImplementDefinitionList ImplementDefinitionElement
#line 859 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3577 "GrammarParser.cpp"
    break;

  case 68: // ImplementDefinitionList: ImplementDefinitionElement
#line 865 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3587 "GrammarParser.cpp"
    break;

  case 69: // ImplementDefinitionElement: Attributes ImplementDefinitionAttributedElement
#line 874 "../../obj/src/GrammarParser.y"
  {
      const auto& definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3597 "GrammarParser.cpp"
    break;

  case 70: // ImplementDefinitionElement: ImplementDefinitionAttributedElement
#line 880 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 3605 "GrammarParser.cpp"
    break;

  case 71: // ImplementDefinitionAttributedElement: DerivedDefinition
#line 887 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3613 "GrammarParser.cpp"
    break;

  case 72: // ImplementDefinitionAttributedElement: RuleDefinition
#line 891 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3621 "GrammarParser.cpp"
    break;

  case 73: // DomainDefinition: "domain" Type
#line 903 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DomainDefinition::Ptr > () = CST::make< DomainDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3629 "GrammarParser.cpp"
    break;

  case 74: // BuiltinDefinition: "builtin" RelationType
#line 915 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BuiltinDefinition::Ptr > () = CST::make< BuiltinDefinition >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < RelationType::Ptr > () );
  }
#line 3637 "GrammarParser.cpp"
    break;

  case 75: // Declaration: "derived" Identifier ":" MaybeFunctionParameters "->" Type
#line 927 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = CST::make< Declaration >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3645 "GrammarParser.cpp"
    break;

  case 76: // Declaration: "rule" Identifier ":" MaybeFunctionParameters "->" Type
#line 931 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = CST::make< Declaration >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 3653 "GrammarParser.cpp"
    break;

  case 77: // Rules: Rules Rule
#line 943 "../../obj/src/GrammarParser.y"
  {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3663 "GrammarParser.cpp"
    break;

  case 78: // Rules: Rule
#line 949 "../../obj/src/GrammarParser.y"
  {
      auto rules = CST::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3673 "GrammarParser.cpp"
    break;

  case 79: // Rule: SkipRule
#line 959 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 3681 "GrammarParser.cpp"
    break;

  case 80: // Rule: ConditionalRule
#line 963 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 3689 "GrammarParser.cpp"
    break;

  case 81: // Rule: CaseRule
#line 967 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 3697 "GrammarParser.cpp"
    break;

  case 82: // Rule: LetRule
#line 971 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 3705 "GrammarParser.cpp"
    break;

  case 83: // Rule: LocalRule
#line 975 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LocalRule::Ptr > ();
  }
#line 3713 "GrammarParser.cpp"
    break;

  case 84: // Rule: ForallRule
#line 979 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 3721 "GrammarParser.cpp"
    break;

  case 85: // Rule: ChooseRule
#line 983 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 3729 "GrammarParser.cpp"
    break;

  case 86: // Rule: IterateRule
#line 987 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 3737 "GrammarParser.cpp"
    break;

  case 87: // Rule: BlockRule
#line 991 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 3745 "GrammarParser.cpp"
    break;

  case 88: // Rule: SequenceRule
#line 995 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 3753 "GrammarParser.cpp"
    break;

  case 89: // Rule: UpdateRule
#line 999 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 3761 "GrammarParser.cpp"
    break;

  case 90: // Rule: CallRule
#line 1003 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 3769 "GrammarParser.cpp"
    break;

  case 91: // Rule: WhileRule
#line 1007 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 3777 "GrammarParser.cpp"
    break;

  case 92: // SkipRule: "skip"
#line 1015 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SkipRule::Ptr > () = CST::make< SkipRule >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3785 "GrammarParser.cpp"
    break;

  case 93: // ConditionalRule: "if" Term "then" Rule
#line 1023 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = CST::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3793 "GrammarParser.cpp"
    break;

  case 94: // ConditionalRule: "if" Term "then" Rule "else" Rule
#line 1027 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = CST::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3801 "GrammarParser.cpp"
    break;

  case 95: // CaseRule: "case" Term "of" "{" CaseLabels "}"
#line 1035 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = CST::make< CaseRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3809 "GrammarParser.cpp"
    break;

  case 96: // CaseRule: "case" Term "of" "{" error "}"
#line 1039 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 3817 "GrammarParser.cpp"
    break;

  case 97: // CaseLabels: CaseLabels CaseLabel
#line 1047 "../../obj/src/GrammarParser.y"
  {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3827 "GrammarParser.cpp"
    break;

  case 98: // CaseLabels: CaseLabel
#line 1053 "../../obj/src/GrammarParser.y"
  {
      auto cases = CST::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3837 "GrammarParser.cpp"
    break;

  case 99: // CaseLabel: "default" ":" Rule
#line 1063 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = CST::make< DefaultCase >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3845 "GrammarParser.cpp"
    break;

  case 100: // CaseLabel: "_" ":" Rule
#line 1067 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = CST::make< DefaultCase >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3853 "GrammarParser.cpp"
    break;

  case 101: // CaseLabel: Term ":" Rule
#line 1071 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = CST::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3861 "GrammarParser.cpp"
    break;

  case 102: // LetRule: "let" VariableBindings "in" Rule
#line 1079 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetRule::Ptr > () = CST::make< LetRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3869 "GrammarParser.cpp"
    break;

  case 103: // LocalRule: "local" LocalFunctionDefinitions "in" Rule
#line 1087 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LocalRule::Ptr > () = CST::make< LocalRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < FunctionDefinitions::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3877 "GrammarParser.cpp"
    break;

  case 104: // ForallRule: "forall" AttributedVariables "in" Term "do" Rule
#line 1095 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = CST::make< ForallRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3885 "GrammarParser.cpp"
    break;

  case 105: // ForallRule: "forall" AttributedVariables "in" Term "with" Term "do" Rule
#line 1099 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = CST::make< ForallRule >( yylhs.location, yystack_[7].value.as < CST::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3893 "GrammarParser.cpp"
    break;

  case 106: // ChooseRule: "choose" AttributedVariables "in" Term "do" Rule
#line 1107 "../../obj/src/GrammarParser.y"
  {
      const auto withToken = Token::unresolved();
      const auto alwaysTrue = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      const auto condition = CST::make< ValueLiteral >( yylhs.location, alwaysTrue );
      yylhs.value.as < ChooseRule::Ptr > () = CST::make< ChooseRule >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), withToken, condition, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3904 "GrammarParser.cpp"
    break;

  case 107: // IterateRule: "iterate" Rule
#line 1122 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = CST::make< IterateRule >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3912 "GrammarParser.cpp"
    break;

  case 108: // BlockRule: "{" Rules "}"
#line 1130 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = CST::make< BlockRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3920 "GrammarParser.cpp"
    break;

  case 109: // BlockRule: "par" Rules "endpar"
#line 1134 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = CST::make< BlockRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3928 "GrammarParser.cpp"
    break;

  case 110: // BlockRule: "{" error "}"
#line 1138 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3937 "GrammarParser.cpp"
    break;

  case 111: // BlockRule: "par" error "endpar"
#line 1143 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3946 "GrammarParser.cpp"
    break;

  case 112: // SequenceRule: "{|" Rules "|}"
#line 1152 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = CST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3954 "GrammarParser.cpp"
    break;

  case 113: // SequenceRule: "seq" Rules "endseq"
#line 1156 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = CST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3962 "GrammarParser.cpp"
    break;

  case 114: // SequenceRule: "{|" error "|}"
#line 1160 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3971 "GrammarParser.cpp"
    break;

  case 115: // SequenceRule: "seq" error "endseq"
#line 1165 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3980 "GrammarParser.cpp"
    break;

  case 116: // UpdateRule: DirectCallExpression ":=" Term
#line 1174 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = CST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3988 "GrammarParser.cpp"
    break;

  case 117: // UpdateRule: MethodCallExpression ":=" Term
#line 1178 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = CST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < MethodCallExpression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3996 "GrammarParser.cpp"
    break;

  case 118: // CallRule: CallExpression
#line 1186 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallRule::Ptr > () = CST::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 4004 "GrammarParser.cpp"
    break;

  case 119: // WhileRule: "while" Term "do" Rule
#line 1194 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < WhileRule::Ptr > () = CST::make< WhileRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 4012 "GrammarParser.cpp"
    break;

  case 120: // Terms: Terms "," Term
#line 1206 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 4023 "GrammarParser.cpp"
    break;

  case 121: // Terms: Term
#line 1213 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = CST::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 4033 "GrammarParser.cpp"
    break;

  case 122: // Term: Expression
#line 1223 "../../obj/src/GrammarParser.y"
  {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 4041 "GrammarParser.cpp"
    break;

  case 123: // Term: TypeCastingExpression
#line 1227 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 4049 "GrammarParser.cpp"
    break;

  case 124: // Term: OperatorExpression
#line 1231 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 4057 "GrammarParser.cpp"
    break;

  case 125: // Term: LetExpression
#line 1235 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 4065 "GrammarParser.cpp"
    break;

  case 126: // Term: ConditionalExpression
#line 1239 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 4073 "GrammarParser.cpp"
    break;

  case 127: // Term: ChooseExpression
#line 1243 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 4081 "GrammarParser.cpp"
    break;

  case 128: // Term: UniversalQuantifierExpression
#line 1247 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 4089 "GrammarParser.cpp"
    break;

  case 129: // Term: ExistentialQuantifierExpression
#line 1251 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 4097 "GrammarParser.cpp"
    break;

  case 130: // Term: CardinalityExpression
#line 1255 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 4105 "GrammarParser.cpp"
    break;

  case 131: // Term: MatchExpression
#line 1259 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < MatchExpression::Ptr > ();
  }
#line 4113 "GrammarParser.cpp"
    break;

  case 132: // Expression: "(" Term ")"
#line 1267 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< CST::EmbracedExpression >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4121 "GrammarParser.cpp"
    break;

  case 133: // Expression: "(" error ")"
#line 1271 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 4129 "GrammarParser.cpp"
    break;

  case 134: // Expression: CallExpression
#line 1275 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 4137 "GrammarParser.cpp"
    break;

  case 135: // Expression: LiteralCallExpression
#line 1279 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 4145 "GrammarParser.cpp"
    break;

  case 136: // Expression: Literal
#line 1283 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 4153 "GrammarParser.cpp"
    break;

  case 137: // Expression: "+" Expression
#line 1287 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4161 "GrammarParser.cpp"
    break;

  case 138: // Expression: "-" Expression
#line 1291 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4169 "GrammarParser.cpp"
    break;

  case 139: // OperatorExpression: Term "+" Term
#line 1303 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4177 "GrammarParser.cpp"
    break;

  case 140: // OperatorExpression: Term "-" Term
#line 1307 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4185 "GrammarParser.cpp"
    break;

  case 141: // OperatorExpression: Term "*" Term
#line 1311 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4193 "GrammarParser.cpp"
    break;

  case 142: // OperatorExpression: Term "/" Term
#line 1315 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4201 "GrammarParser.cpp"
    break;

  case 143: // OperatorExpression: Term "%" Term
#line 1319 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4209 "GrammarParser.cpp"
    break;

  case 144: // OperatorExpression: Term "^" Term
#line 1323 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4217 "GrammarParser.cpp"
    break;

  case 145: // OperatorExpression: Term "!=" Term
#line 1327 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4225 "GrammarParser.cpp"
    break;

  case 146: // OperatorExpression: Term "=" Term
#line 1331 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4233 "GrammarParser.cpp"
    break;

  case 147: // OperatorExpression: Term "<" Term
#line 1335 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4241 "GrammarParser.cpp"
    break;

  case 148: // OperatorExpression: Term ">" Term
#line 1339 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4249 "GrammarParser.cpp"
    break;

  case 149: // OperatorExpression: Term "<=" Term
#line 1343 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4257 "GrammarParser.cpp"
    break;

  case 150: // OperatorExpression: Term ">=" Term
#line 1347 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4265 "GrammarParser.cpp"
    break;

  case 151: // OperatorExpression: Term "or" Term
#line 1351 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4273 "GrammarParser.cpp"
    break;

  case 152: // OperatorExpression: Term "xor" Term
#line 1355 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4281 "GrammarParser.cpp"
    break;

  case 153: // OperatorExpression: Term "and" Term
#line 1359 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4289 "GrammarParser.cpp"
    break;

  case 154: // OperatorExpression: Term "=>" Term
#line 1363 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4297 "GrammarParser.cpp"
    break;

  case 155: // OperatorExpression: Term "implies" Term
#line 1367 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4305 "GrammarParser.cpp"
    break;

  case 156: // OperatorExpression: "not" Term
#line 1371 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4313 "GrammarParser.cpp"
    break;

  case 157: // CallExpression: DirectCallExpression
#line 1379 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 4321 "GrammarParser.cpp"
    break;

  case 158: // CallExpression: MethodCallExpression
#line 1383 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 4329 "GrammarParser.cpp"
    break;

  case 159: // CallExpression: IndirectCallExpression
#line 1387 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 4337 "GrammarParser.cpp"
    break;

  case 160: // DirectCallExpression: "this"
#line 1395 "../../obj/src/GrammarParser.y"
  {
      const auto identifier = CST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      identifier->setSpans( m_lexer.fetchSpansAndReset() );
      const auto identifierPath = IdentifierPath::fromIdentifier( identifier );
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, identifierPath );
  }
#line 4348 "GrammarParser.cpp"
    break;

  case 161: // DirectCallExpression: IdentifierPath
#line 1402 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4356 "GrammarParser.cpp"
    break;

  case 162: // DirectCallExpression: IdentifierPath "(" ")"
#line 1406 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), arguments, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4365 "GrammarParser.cpp"
    break;

  case 163: // DirectCallExpression: IdentifierPath "(" Terms ")"
#line 1411 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expressions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4373 "GrammarParser.cpp"
    break;

  case 164: // DirectCallExpression: IdentifierPath "(" error ")"
#line 1415 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 4381 "GrammarParser.cpp"
    break;

  case 165: // MethodCallExpression: Expression "." Identifier
#line 1423 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 4390 "GrammarParser.cpp"
    break;

  case 166: // MethodCallExpression: Expression "." Identifier "(" ")"
#line 1428 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4401 "GrammarParser.cpp"
    break;

  case 167: // MethodCallExpression: Expression "." Identifier "(" Terms ")"
#line 1435 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4411 "GrammarParser.cpp"
    break;

  case 168: // MethodCallExpression: Expression "." Identifier "(" error ")"
#line 1441 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 4419 "GrammarParser.cpp"
    break;

  case 169: // LiteralCallExpression: Expression "." IntegerLiteral
#line 1449 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = CST::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 4427 "GrammarParser.cpp"
    break;

  case 170: // IndirectCallExpression: CallExpression "(" ")"
#line 1457 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = CST::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4438 "GrammarParser.cpp"
    break;

  case 171: // IndirectCallExpression: CallExpression "(" Terms ")"
#line 1464 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = CST::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4448 "GrammarParser.cpp"
    break;

  case 172: // IndirectCallExpression: CallExpression "(" error ")"
#line 1470 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 4456 "GrammarParser.cpp"
    break;

  case 173: // TypeCastingExpression: Expression "as" Type
#line 1478 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = CST::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 4464 "GrammarParser.cpp"
    break;

  case 174: // LetExpression: "let" VariableBindings "in" Term
#line 1486 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = CST::make< LetExpression >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4472 "GrammarParser.cpp"
    break;

  case 175: // ConditionalExpression: "if" Term "then" Term "else" Term
#line 1494 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = CST::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4480 "GrammarParser.cpp"
    break;

  case 176: // ChooseExpression: "choose" VariableSelections "do" Term
#line 1502 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = CST::make< ChooseExpression >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < VariableSelections::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4488 "GrammarParser.cpp"
    break;

  case 177: // UniversalQuantifierExpression: "forall" AttributedVariables "in" Term "holds" Term
#line 1510 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = CST::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4496 "GrammarParser.cpp"
    break;

  case 178: // ExistentialQuantifierExpression: "exists" AttributedVariables "in" Term "with" Term
#line 1518 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = CST::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4504 "GrammarParser.cpp"
    break;

  case 179: // CardinalityExpression: "|" Expression "|"
#line 1526 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = CST::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4512 "GrammarParser.cpp"
    break;

  case 180: // MatchExpression: "match" Term "with" "{" MatchArms "}"
#line 1533 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MatchExpression::Ptr > () = CST::make< MatchExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < MatchArms::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4520 "GrammarParser.cpp"
    break;

  case 181: // MatchArms: MatchArms "," MatchArm
#line 1540 "../../obj/src/GrammarParser.y"
  {
      auto arms = yystack_[2].value.as < MatchArms::Ptr > ();
      yystack_[0].value.as < MatchArm::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      arms->add( yystack_[0].value.as < MatchArm::Ptr > () );
      yylhs.value.as < MatchArms::Ptr > () = arms;
  }
#line 4531 "GrammarParser.cpp"
    break;

  case 182: // MatchArms: MatchArm
#line 1547 "../../obj/src/GrammarParser.y"
  {
      auto arms = CST::make< MatchArms >( yylhs.location );
      arms->add( yystack_[0].value.as < MatchArm::Ptr > () );
      yylhs.value.as < MatchArms::Ptr > () = arms;
  }
#line 4541 "GrammarParser.cpp"
    break;

  case 183: // MatchArm: Term "=>" Term
#line 1556 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MatchArm::Ptr > () = CST::make< MatchArm >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4549 "GrammarParser.cpp"
    break;

  case 184: // Literal: UndefinedLiteral
#line 1569 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 4557 "GrammarParser.cpp"
    break;

  case 185: // Literal: BooleanLiteral
#line 1573 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4565 "GrammarParser.cpp"
    break;

  case 186: // Literal: IntegerLiteral
#line 1577 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4573 "GrammarParser.cpp"
    break;

  case 187: // Literal: RationalLiteral
#line 1581 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4581 "GrammarParser.cpp"
    break;

  case 188: // Literal: DecimalLiteral
#line 1585 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4589 "GrammarParser.cpp"
    break;

  case 189: // Literal: BinaryLiteral
#line 1589 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4597 "GrammarParser.cpp"
    break;

  case 190: // Literal: StringLiteral
#line 1593 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4605 "GrammarParser.cpp"
    break;

  case 191: // Literal: ReferenceLiteral
#line 1597 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 4613 "GrammarParser.cpp"
    break;

  case 192: // Literal: ListLiteral
#line 1605 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 4621 "GrammarParser.cpp"
    break;

  case 193: // Literal: RangeLiteral
#line 1609 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 4629 "GrammarParser.cpp"
    break;

  case 194: // Literal: TupleLiteral
#line 1613 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 4637 "GrammarParser.cpp"
    break;

  case 195: // Literal: RecordLiteral
#line 1617 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 4645 "GrammarParser.cpp"
    break;

  case 196: // UndefinedLiteral: "undef"
#line 1625 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = CST::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4654 "GrammarParser.cpp"
    break;

  case 197: // BooleanLiteral: "true"
#line 1634 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = CST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4664 "GrammarParser.cpp"
    break;

  case 198: // BooleanLiteral: "false"
#line 1640 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = CST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4674 "GrammarParser.cpp"
    break;

  case 199: // IntegerLiteral: "integer"
#line 1650 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4682 "GrammarParser.cpp"
    break;

  case 200: // RationalLiteral: "rational"
#line 1658 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4690 "GrammarParser.cpp"
    break;

  case 201: // DecimalLiteral: "decimal"
#line 1666 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4698 "GrammarParser.cpp"
    break;

  case 202: // BinaryLiteral: "binary"
#line 1674 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4706 "GrammarParser.cpp"
    break;

  case 203: // BinaryLiteral: "hexadecimal"
#line 1678 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4714 "GrammarParser.cpp"
    break;

  case 204: // StringLiteral: "string"
#line 1686 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4722 "GrammarParser.cpp"
    break;

  case 205: // ReferenceLiteral: "@" IdentifierPath
#line 1694 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = CST::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4730 "GrammarParser.cpp"
    break;

  case 206: // ListLiteral: "[" "]"
#line 1723 "../../obj/src/GrammarParser.y"
  {
      const auto& expressions = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = CST::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4741 "GrammarParser.cpp"
    break;

  case 207: // ListLiteral: "[" Terms "]"
#line 1730 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = CST::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4751 "GrammarParser.cpp"
    break;

  case 208: // ListLiteral: "[" error "]"
#line 1736 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 4759 "GrammarParser.cpp"
    break;

  case 209: // RangeLiteral: "[" Term ".." Term "]"
#line 1744 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = CST::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4769 "GrammarParser.cpp"
    break;

  case 210: // TupleLiteral: "(" Terms "," Term ")"
#line 1754 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = CST::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4782 "GrammarParser.cpp"
    break;

  case 211: // RecordLiteral: "{" Assignments "}"
#line 1767 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = CST::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4792 "GrammarParser.cpp"
    break;

  case 212: // Assignments: Assignments "," Assignment
#line 1781 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4803 "GrammarParser.cpp"
    break;

  case 213: // Assignments: Assignment
#line 1788 "../../obj/src/GrammarParser.y"
  {
      auto assignments = CST::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4813 "GrammarParser.cpp"
    break;

  case 214: // Assignment: Identifier ":" Term
#line 1797 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = CST::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4821 "GrammarParser.cpp"
    break;

  case 215: // MappedExpressions: MappedExpressions "," MappedExpression
#line 1804 "../../obj/src/GrammarParser.y"
  {
      const auto& mappedExpressions = yystack_[2].value.as < MappedExpressions::Ptr > ();
      yystack_[0].value.as < MappedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      mappedExpressions->add( yystack_[0].value.as < MappedExpression::Ptr > () );
      yylhs.value.as < MappedExpressions::Ptr > () = mappedExpressions;
  }
#line 4832 "GrammarParser.cpp"
    break;

  case 216: // MappedExpressions: MappedExpression
#line 1811 "../../obj/src/GrammarParser.y"
  {
      auto mappedExpressions = CST::make< MappedExpressions >( yylhs.location );
      mappedExpressions->add( yystack_[0].value.as < MappedExpression::Ptr > () );
      yylhs.value.as < MappedExpressions::Ptr > () = mappedExpressions;
  }
#line 4842 "GrammarParser.cpp"
    break;

  case 217: // MappedExpression: "->" Term
#line 1820 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4851 "GrammarParser.cpp"
    break;

  case 218: // MappedExpression: "(" Term ")" "->" Term
#line 1825 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = CST::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), arguments, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4861 "GrammarParser.cpp"
    break;

  case 219: // MappedExpression: TupleLiteral "->" Term
#line 1831 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto& leftBracket = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto& rightBracket = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4872 "GrammarParser.cpp"
    break;

  case 220: // Types: Types "," Type
#line 1847 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4883 "GrammarParser.cpp"
    break;

  case 221: // Types: Type
#line 1854 "../../obj/src/GrammarParser.y"
  {
      auto types = CST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4893 "GrammarParser.cpp"
    break;

  case 222: // Type: BasicType
#line 1863 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4901 "GrammarParser.cpp"
    break;

  case 223: // Type: TupleType
#line 1867 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4909 "GrammarParser.cpp"
    break;

  case 224: // Type: RecordType
#line 1871 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4917 "GrammarParser.cpp"
    break;

  case 225: // Type: TemplateType
#line 1875 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4925 "GrammarParser.cpp"
    break;

  case 226: // Type: RelationType
#line 1879 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4933 "GrammarParser.cpp"
    break;

  case 227: // Type: FixedSizedType
#line 1883 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4941 "GrammarParser.cpp"
    break;

  case 228: // Type: MappingType
#line 1887 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < MappingType::Ptr > ();
  }
#line 4949 "GrammarParser.cpp"
    break;

  case 229: // Type: VaradicType
#line 1891 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < VaradicType::Ptr > ();
  }
#line 4957 "GrammarParser.cpp"
    break;

  case 230: // BasicType: IdentifierPath
#line 1899 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = CST::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4965 "GrammarParser.cpp"
    break;

  case 231: // TupleType: "(" Types "," Type ")"
#line 1907 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = CST::make< TupleType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), subTypes, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4976 "GrammarParser.cpp"
    break;

  case 232: // RecordType: "{" TypedVariables "," TypedVariable "}"
#line 1918 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = CST::make< RecordType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4987 "GrammarParser.cpp"
    break;

  case 233: // TemplateType: IdentifierPath "<" Types ">"
#line 1929 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = CST::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4995 "GrammarParser.cpp"
    break;

  case 234: // RelationType: IdentifierPath "<" MaybeFunctionParameters "->" Type ">"
#line 1937 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = CST::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 5003 "GrammarParser.cpp"
    break;

  case 235: // FixedSizedType: IdentifierPath "'" Term
#line 1945 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = CST::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5011 "GrammarParser.cpp"
    break;

  case 236: // MappingType: "<" FunctionParameters "->" Type ">"
#line 1953 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MappingType::Ptr > () = CST::make< MappingType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );      
  }
#line 5019 "GrammarParser.cpp"
    break;

  case 237: // VaradicType: Identifier "..."
#line 1961 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VaradicType::Ptr > () = CST::make< VaradicType >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 5027 "GrammarParser.cpp"
    break;

  case 238: // FunctionParameters: FunctionParameters "*" Type
#line 1973 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 5038 "GrammarParser.cpp"
    break;

  case 239: // FunctionParameters: Type
#line 1980 "../../obj/src/GrammarParser.y"
  {
      auto types = CST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 5048 "GrammarParser.cpp"
    break;

  case 240: // MaybeFunctionParameters: FunctionParameters
#line 1990 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 5056 "GrammarParser.cpp"
    break;

  case 241: // MaybeFunctionParameters: %empty
#line 1994 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = CST::make< Types >( yylhs.location );
  }
#line 5064 "GrammarParser.cpp"
    break;

  case 242: // MethodParameters: MethodParameters "," TypedAttributedVariable
#line 2002 "../../obj/src/GrammarParser.y"
  {
      const auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5075 "GrammarParser.cpp"
    break;

  case 243: // MethodParameters: "this"
#line 2009 "../../obj/src/GrammarParser.y"
  {
      const auto parameters = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto identifier = CST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      identifier->setSpans( m_lexer.fetchSpansAndReset() );
      const auto unresolvedType = CST::make< UnresolvedType >( yylhs.location );
      const auto variable = CST::make< VariableDefinition >( yylhs.location, identifier, Token::unresolved(), unresolvedType );
      parameters->add( variable );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5089 "GrammarParser.cpp"
    break;

  case 244: // Parameters: Parameters "," TypedAttributedVariable
#line 2023 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5100 "GrammarParser.cpp"
    break;

  case 245: // Parameters: TypedAttributedVariable
#line 2030 "../../obj/src/GrammarParser.y"
  {
      auto parameters = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5110 "GrammarParser.cpp"
    break;

  case 246: // MaybeDefined: "defined" "{" Term "}"
#line 2044 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = CST::make< Defined >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 5118 "GrammarParser.cpp"
    break;

  case 247: // MaybeDefined: %empty
#line 2048 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = CST::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), CST::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 5126 "GrammarParser.cpp"
    break;

  case 248: // MaybeInitially: "=" "{" Expression "}"
#line 2056 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: drop braces and replace this rule with ::= Expression
      const auto& embracedExpression = CST::make< EmbracedExpression >( yystack_[1].location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), embracedExpression );
  }
#line 5136 "GrammarParser.cpp"
    break;

  case 249: // MaybeInitially: "=" "{" MappedExpressions "}"
#line 2062 "../../obj/src/GrammarParser.y"
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
#line 5153 "GrammarParser.cpp"
    break;

  case 250: // MaybeInitially: %empty
#line 2075 "../../obj/src/GrammarParser.y"
  {
      const auto& expression = CST::make< CST::AbstractExpression >( yylhs.location, Token::unresolved() );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, Token::unresolved(), expression );
  }
#line 5162 "GrammarParser.cpp"
    break;

  case 251: // Identifier: "identifier"
#line 2088 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 5170 "GrammarParser.cpp"
    break;

  case 252: // Identifier: "in"
#line 2092 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5179 "GrammarParser.cpp"
    break;

  case 253: // Identifier: "CASM"
#line 2097 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5188 "GrammarParser.cpp"
    break;

  case 254: // Identifier: "self"
#line 2102 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5197 "GrammarParser.cpp"
    break;

  case 255: // Identifier: "enumeration"
#line 2107 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5206 "GrammarParser.cpp"
    break;

  case 256: // Identifier: "structure"
#line 2112 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5215 "GrammarParser.cpp"
    break;

  case 257: // IdentifierPath: IdentifierPath "::" Identifier
#line 2121 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < CST::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 5226 "GrammarParser.cpp"
    break;

  case 258: // IdentifierPath: Identifier
#line 2128 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = CST::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5234 "GrammarParser.cpp"
    break;

  case 259: // Variable: TypedVariable
#line 2140 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5242 "GrammarParser.cpp"
    break;

  case 260: // Variable: Identifier
#line 2144 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = CST::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = CST::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 5251 "GrammarParser.cpp"
    break;

  case 261: // AttributedVariables: AttributedVariables "," AttributedVariable
#line 2153 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5262 "GrammarParser.cpp"
    break;

  case 262: // AttributedVariables: AttributedVariable
#line 2160 "../../obj/src/GrammarParser.y"
  {
      auto variables = CST::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5272 "GrammarParser.cpp"
    break;

  case 263: // TypedVariables: TypedVariables "," TypedVariable
#line 2170 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5283 "GrammarParser.cpp"
    break;

  case 264: // TypedVariables: TypedVariable
#line 2177 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = CST::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5293 "GrammarParser.cpp"
    break;

  case 265: // TypedVariable: Identifier ":" Type
#line 2187 "../../obj/src/GrammarParser.y"
  {
      auto variable = CST::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5302 "GrammarParser.cpp"
    break;

  case 266: // AttributedVariable: Attributes Variable
#line 2196 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5312 "GrammarParser.cpp"
    break;

  case 267: // AttributedVariable: Variable
#line 2202 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5320 "GrammarParser.cpp"
    break;

  case 268: // TypedAttributedVariable: Attributes TypedVariable
#line 2210 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5330 "GrammarParser.cpp"
    break;

  case 269: // TypedAttributedVariable: TypedVariable
#line 2216 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5338 "GrammarParser.cpp"
    break;

  case 270: // VariableBindings: VariableBindings "," VariableBinding
#line 2228 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5349 "GrammarParser.cpp"
    break;

  case 271: // VariableBindings: VariableBinding
#line 2235 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = CST::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5359 "GrammarParser.cpp"
    break;

  case 272: // VariableBinding: AttributedVariable "=" Term
#line 2244 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = CST::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5367 "GrammarParser.cpp"
    break;

  case 273: // VariableSelections: VariableSelections "," VariableSelection
#line 2256 "../../obj/src/GrammarParser.y"
  {
      auto variableSelections = yystack_[2].value.as < VariableSelections::Ptr > ();
      yystack_[0].value.as < VariableSelection::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      variableSelections->add( yystack_[0].value.as < VariableSelection::Ptr > () );
      yylhs.value.as < VariableSelections::Ptr > () = variableSelections;
  }
#line 5378 "GrammarParser.cpp"
    break;

  case 274: // VariableSelections: VariableSelection
#line 2263 "../../obj/src/GrammarParser.y"
  {
      auto variableSelections = CST::make< VariableSelections >( yylhs.location );
      variableSelections->add( yystack_[0].value.as < VariableSelection::Ptr > () );
      yylhs.value.as < VariableSelections::Ptr > () = variableSelections;
  }
#line 5388 "GrammarParser.cpp"
    break;

  case 275: // VariableSelection: AttributedVariable "in" Term "with" Term
#line 2272 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableSelection::Ptr > () = CST::make< VariableSelection >( yylhs.location, yystack_[4].value.as < VariableDefinition::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5396 "GrammarParser.cpp"
    break;

  case 276: // VariableSelection: AttributedVariable "in" Term
#line 2276 "../../obj/src/GrammarParser.y"
  {
      const auto withToken = Token::unresolved();
      const auto alwaysTrue = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      const auto condition = CST::make< ValueLiteral >( yylhs.location, alwaysTrue );

      yylhs.value.as < VariableSelection::Ptr > () = CST::make< VariableSelection >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), withToken, condition );
  }
#line 5408 "GrammarParser.cpp"
    break;

  case 277: // LocalFunctionDefinitions: LocalFunctionDefinitions "," AttributedLocalFunctionDefinition
#line 2292 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[2].value.as < FunctionDefinitions::Ptr > ();
      yystack_[0].value.as < FunctionDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5419 "GrammarParser.cpp"
    break;

  case 278: // LocalFunctionDefinitions: AttributedLocalFunctionDefinition
#line 2299 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< FunctionDefinitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5429 "GrammarParser.cpp"
    break;

  case 279: // AttributedLocalFunctionDefinition: Attributes LocalFunctionDefinition
#line 2308 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 5439 "GrammarParser.cpp"
    break;

  case 280: // AttributedLocalFunctionDefinition: LocalFunctionDefinition
#line 2314 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 5447 "GrammarParser.cpp"
    break;

  case 281: // AttributedLocalFunctionDefinition: error
#line 2318 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = nullptr;
  }
#line 5455 "GrammarParser.cpp"
    break;

  case 282: // LocalFunctionDefinition: Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 2325 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = CST::make< FunctionDefinition >( yylhs.location, Token::unresolved(), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > ()->setClassification( FunctionDefinition::Classification::LOCAL );
  }
#line 5464 "GrammarParser.cpp"
    break;

  case 283: // Attributes: Attributes Attribute
#line 2338 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5474 "GrammarParser.cpp"
    break;

  case 284: // Attributes: Attribute
#line 2344 "../../obj/src/GrammarParser.y"
  {
      auto attributes = CST::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5484 "GrammarParser.cpp"
    break;

  case 285: // Attribute: "[" BasicAttribute "]"
#line 2353 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5495 "GrammarParser.cpp"
    break;

  case 286: // Attribute: "[" SymbolAttribute "]"
#line 2360 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < SymbolAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5506 "GrammarParser.cpp"
    break;

  case 287: // Attribute: "[" ExpressionAttribute "]"
#line 2367 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5517 "GrammarParser.cpp"
    break;

  case 288: // Attribute: "[" error "]"
#line 2374 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 5525 "GrammarParser.cpp"
    break;

  case 289: // BasicAttribute: Identifier
#line 2381 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = CST::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5533 "GrammarParser.cpp"
    break;

  case 290: // SymbolAttribute: Identifier TypedVariable
#line 2388 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SymbolAttribute::Ptr > () = CST::make< SymbolAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < VariableDefinition::Ptr > () );
  }
#line 5541 "GrammarParser.cpp"
    break;

  case 291: // ExpressionAttribute: Identifier Term
#line 2395 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = CST::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5549 "GrammarParser.cpp"
    break;


#line 5553 "GrammarParser.cpp"

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


  const short Parser::yypact_ninf_ = -427;

  const short Parser::yytable_ninf_ = -240;

  const short
  Parser::yypact_[] =
  {
      13,  -427,   261,    29,   741,    14,  -427,    24,  -427,  -427,
    -427,  -427,  -427,  -427,  2584,    49,   135,   157,  -427,  -427,
     341,   544,   544,   544,   544,   544,   544,   544,   315,   315,
     315,   544,   544,  1170,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    1297,  -427,  -427,  -427,  -427,    53,    53,    53,  2584,    53,
    2584,  -427,  -427,  -427,  2584,   825,   825,  2000,  1732,   544,
     825,   544,  -427,  -427,  -427,  -427,  -427,  -427,  3261,   -25,
    -427,   172,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,   150,   212,  -427,
    -427,  -427,  -427,    96,  -427,   176,   162,   227,   113,   228,
     188,   248,    83,   252,   315,   544,   315,   254,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,   232,   156,    -4,  -427,
    -427,   203,   249,  -427,  -427,   150,  -427,  -427,   260,    89,
    -427,    53,   111,  -427,   291,   -21,  -427,  2717,   120,  2894,
    -427,  -427,  -427,   263,   256,  3030,   265,  -427,   196,  2993,
     -29,  -427,   266,   121,   176,  2584,  2584,  2584,  2584,  2584,
    2584,  2584,  2584,  2584,  2584,  2584,  2584,  2584,  2584,  2584,
    2584,  2584,   315,    59,  1799,   315,  1866,   544,  2584,  2584,
     257,   218,  -427,    33,   315,   267,  2450,   169,   315,   315,
     459,  2584,   544,   271,   270,  -427,   150,   273,  -427,  -427,
     216,   278,  -427,   315,  2584,   315,   281,   315,   315,  2584,
    2584,    53,  -427,  2584,    53,  2584,  2584,    53,  2584,  2584,
     286,  -427,  2584,  -427,  -427,  -427,  2584,  2584,  -427,   544,
    2584,  -427,  1200,  1269,  1137,   574,   339,   339,   922,   351,
     351,   277,   277,   277,  -427,   574,   922,   351,   351,  -427,
    -427,   295,   297,  -427,   -26,  3261,  -427,   298,  -427,    87,
    -427,  3063,  3261,  2584,  -427,    96,   301,  -427,   110,   177,
    -427,  -427,    53,   304,   230,    74,  1414,  -427,    53,   237,
      53,    53,  2450,  2584,  2584,  2584,  1506,  1598,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,   283,    23,   287,   290,   303,   202,   213,   313,
    -427,  -427,  3261,  -427,     5,   315,   544,   315,   315,    40,
      25,   235,   300,   302,  -427,   318,    71,   305,  3261,  3261,
    -427,  2861,  -427,  2927,  3261,  -427,  2789,  2960,  2584,  3096,
    3261,  3129,  -427,  3261,  1933,  -427,  -427,  -427,  -427,   307,
    3261,  -427,   309,   312,    53,   314,    53,  -427,  2584,  -427,
    -427,   226,  -427,    53,   357,  2090,  -427,   366,  2180,   122,
    -427,   329,   131,  -427,  -427,    53,   146,   148,  -427,  2750,
    2826,  2609,   333,  2270,   266,   316,  2360,  2584,  2584,    82,
     124,   145,  2450,  -427,    54,  -427,     5,   342,   345,  -427,
     331,   544,   544,  -427,  -427,  -427,     8,  -427,    40,   315,
    -427,   315,   353,  -427,  -427,    35,  -427,  -427,    71,   315,
    2584,  2584,  2584,  2584,  3294,   239,  -427,  -427,  -427,   358,
    -427,   217,  2584,   315,   315,  -427,   315,  -427,  3261,  -427,
     230,  -427,  -427,  -427,  -427,  -427,  -427,  2450,   315,  2450,
     237,  -427,  2584,  2584,  2450,   354,  2450,  -427,  -427,  -427,
    -427,  3261,  3261,  2450,   315,  2450,   315,  2450,   315,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,   147,   198,  -427,  -427,
    -427,  -427,  -427,  -427,   347,    71,  -427,  -427,  -427,   382,
    3261,  3261,  3261,  3261,  2584,  -427,  2584,  -427,  -427,  3261,
     362,   370,   376,  -427,  -427,   359,  -427,  -427,  1011,  2651,
     397,  1665,  -427,  -427,   380,  -427,   384,  -427,   386,   315,
     315,  -427,    77,   385,   387,  3327,  -427,  2584,  2584,  2584,
     315,  2450,  2584,  2450,  2450,   383,   388,   391,  2517,  -427,
    3162,  2450,  2450,  2450,   371,   372,  -427,  2584,   389,  -427,
    3261,  3261,  3261,   382,  -427,  2684,  -427,  -427,  -427,  2450,
    2450,  -427,  -427,  2450,  -427,  -427,  -427,   315,   315,  3195,
     728,   387,  2450,  -427,  -427,  -427,  -427,  -427,  -427,  2000,
      75,   257,   241,  -427,  -427,  3228,  -427,  -427,   307
  };

  const short
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   284,     0,   253,   255,
     256,   254,   252,   251,   289,     0,     0,     0,     1,     9,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     8,    10,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
       0,     3,   283,   288,   160,     0,     0,     0,     0,     0,
       0,   196,   198,   197,     0,     0,     0,     0,     0,     0,
       0,     0,   202,   203,   199,   200,   201,   204,   291,   122,
     124,   134,   157,   158,   135,   159,   123,   125,   126,   127,
     128,   129,   130,   131,   136,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   258,   161,   290,
     285,   286,   287,     0,   258,    24,     0,     0,     0,   258,
      46,     0,    49,     0,     0,     0,     0,     0,   222,   223,
     224,   225,   226,   227,   228,   229,   258,   230,     0,    73,
      74,     0,     0,     5,     7,   260,   267,   259,     0,     0,
     271,     0,     0,   262,     0,     0,   274,     0,     0,     0,
     156,   137,   138,     0,     0,   121,     0,   206,     0,   121,
       0,   213,     0,     0,   205,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   216,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   221,     0,     0,   264,   239,
       0,     0,   237,   241,     0,     0,     0,   241,   241,     0,
       0,     0,   266,     0,     0,     0,     0,     0,     0,     0,
       0,   133,     0,   132,   208,   207,     0,     0,   211,     0,
       0,   179,   153,   151,   152,   155,   139,   140,   146,   147,
     148,   141,   142,   143,   144,   154,   145,   149,   150,   173,
     169,   165,     0,   170,     0,   121,   265,     0,   162,     0,
     257,   121,   217,     0,    25,     0,     0,   243,     0,     0,
     269,   245,     0,     0,     0,     0,     0,    92,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,     0,   118,   157,   158,     0,     0,     0,     0,
      45,    47,    48,    50,     0,     0,     0,     0,     0,     0,
       0,   221,   240,     0,   235,     0,     0,     0,   272,   174,
     270,     0,   261,   276,   176,   273,     0,     0,     0,   120,
     120,     0,   212,   214,     0,   172,   171,   164,   163,     0,
     219,   215,     0,     0,     0,     0,     0,   268,     0,    42,
      44,     0,    40,     0,     0,     0,    78,     0,     0,     0,
     281,     0,     0,   278,   280,     0,     0,     0,   107,     0,
       0,     0,     0,     0,   258,     0,     0,     0,     0,     0,
       0,     0,     0,    55,     0,    53,     0,   220,   263,   238,
       0,     0,     0,    60,    62,    64,     0,    58,     0,     0,
     233,     0,     0,    71,    72,     0,    68,    70,     0,     0,
       0,     0,     0,     0,     0,     0,   182,   210,   209,     0,
     166,     0,     0,     0,     0,   242,     0,   244,    27,    26,
       0,    41,   115,   113,    77,   111,   109,     0,   241,     0,
       0,   279,     0,     0,     0,     0,     0,   110,   108,   114,
     112,   116,   117,     0,     0,     0,     0,     0,     0,    32,
      51,    52,    54,   231,   232,   236,     0,     0,    56,    63,
      59,    61,    57,   220,     0,     0,    65,    67,    69,   247,
     177,   275,   175,   178,     0,   180,     0,   168,   167,   218,
       0,     0,     0,    43,   102,     0,   103,   277,     0,     0,
      93,     0,   119,    37,     0,    35,     0,    33,     0,   241,
     241,   234,     0,     0,   250,   154,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    98,
       0,     0,     0,     0,     0,     0,    66,     0,     0,    39,
      30,    29,    28,   247,   104,     0,   106,    94,    96,     0,
       0,    95,    97,     0,    38,    36,    34,     0,     0,     0,
       0,   250,     0,    99,   100,   101,    75,    76,   246,     0,
       0,   194,     0,   282,   105,   121,   248,   249,   132
  };

  const short
  Parser::yypgoto_[] =
  {
    -427,  -427,  -427,  -427,   423,   407,  -427,  -427,     0,    10,
    -328,    -1,  -427,  -427,  -427,  -427,  -427,  -427,  -427,    46,
    -427,    37,  -427,  -427,   -44,  -426,    26,  -427,  -427,    39,
     -50,   844,  -427,  -427,  -427,  -427,   -89,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,   -63,   328,   555,
    -427,   420,   682,   808,  -427,  -427,  -427,  -427,  -427,  -427,
    -427,  -427,  -427,  -427,  -427,   -45,  -427,  -427,  -427,   279,
    -427,  -427,  -427,  -427,  -427,  -427,  -427,  -112,  -427,  -427,
     224,  -115,   191,   258,   153,  -427,  -427,  -427,  -427,   446,
    -427,  -427,  -427,   368,  -226,   272,   285,   -93,   -95,    -2,
     469,   350,   -51,  -427,   -11,   -20,  -233,   204,   289,  -427,
     284,  -427,    52,   129,   109,     2,  -427,  -427,  -427
  };

  const short
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    33,    34,    35,    36,    37,   433,   434,
      40,   380,   381,    41,    42,    43,    44,    45,   414,   415,
      46,   425,   426,    47,   435,   436,   437,    48,    49,   427,
     385,   386,   309,   310,   311,   558,   559,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   164,   275,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,   445,   446,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   170,
     171,   201,   202,   214,   219,   128,   129,   130,   131,   132,
     133,   134,   135,   342,   343,   288,   289,   544,   569,   114,
     108,   146,   152,   217,   147,   153,   291,   149,   150,   155,
     156,   392,   393,   394,   151,     6,    15,    16,    17
  };

  const short
  Parser::yytable_[] =
  {
      14,   200,   347,   109,    38,   168,   413,    52,   158,   507,
     225,   236,   107,   421,    39,   422,     1,    51,   192,   116,
     117,   118,   119,   121,    32,   123,   136,   136,   136,    18,
     142,   366,   248,    38,   286,   148,     8,   154,   249,     9,
      21,   246,    23,    39,    10,   421,   237,   422,    11,   287,
      38,   226,    52,   145,   145,   145,     8,   145,   193,     9,
      39,    12,     8,     2,    10,     9,     2,   172,    11,   498,
      10,     2,     2,    32,    11,   384,    21,     8,    23,   194,
       9,    12,    21,    53,    23,    10,   413,    12,   492,    11,
      54,     2,   429,     2,   430,   295,   506,   296,     2,   297,
     298,   299,    12,   300,   301,   302,  -134,   303,   110,     5,
     304,     2,     2,    50,   218,   490,   507,   230,   305,    61,
      62,    63,   136,   216,   136,    13,   212,    65,    66,     2,
      67,   274,    68,   279,   306,     2,   606,   483,   566,   233,
      71,   455,    50,   457,   368,    13,   197,    74,   239,   145,
     467,    13,   198,    52,   246,   307,   231,   484,   193,   469,
      72,    73,    74,    75,    76,    77,    13,   373,   206,   207,
     326,   199,     8,   200,   472,     9,   473,   374,   234,   485,
      10,   127,   138,   139,    11,   287,   251,   234,   208,   231,
     136,   271,   290,   136,   111,   280,   290,    12,   470,   486,
     487,   216,   136,   203,   193,   216,   136,   136,   280,   539,
     333,   148,   195,   234,   352,   234,   112,   154,   203,   197,
     488,   136,   204,   136,   223,   136,   136,     2,   194,   145,
     224,   379,   145,     8,   375,   145,     9,   204,   390,   197,
       8,    10,   525,     9,   376,    11,   388,   172,    10,   396,
     397,   210,    11,   206,   207,   245,   403,   406,    12,   410,
     540,    13,     7,   246,     8,    12,   197,     9,   196,   374,
     411,   227,    10,   208,   518,   197,    11,   215,   148,   284,
     376,   377,   205,   209,   246,   285,   337,   459,     2,    12,
     216,   338,   382,   460,    52,     2,   145,   391,   145,   145,
     515,   451,   607,   211,   404,  -239,   516,   213,   285,   221,
    -239,   228,   292,   564,   565,   229,   292,   222,     8,   235,
     241,     9,    13,   242,   244,   418,    10,   294,   250,    13,
      11,   334,   283,   136,   216,   136,   136,   335,   339,   423,
     336,   346,    78,    12,     8,   269,   358,     9,   276,   424,
     187,   364,    10,    13,   365,   367,    11,   293,   372,   378,
     409,   329,   330,   290,   407,   290,   193,   408,   412,    12,
     337,   124,   216,   432,   216,   125,   341,   431,   345,   462,
     439,   461,   452,   126,   453,    52,   157,   454,   159,   456,
     465,   468,   160,   391,   477,   165,   169,    52,   479,   493,
     495,   113,   543,   383,   179,   180,   494,    13,   395,   184,
     185,   186,   187,   505,   531,   517,   541,   547,    52,   496,
     497,   184,   185,   186,   187,   548,   423,   136,   500,   136,
      52,   549,   554,    13,   550,   561,   424,   136,   501,   562,
      52,   563,   568,   416,   578,   567,   587,   588,   428,   590,
     579,   136,   136,   580,   136,   438,   143,   144,   382,   523,
     491,   542,     8,   499,   508,     9,   136,   502,   391,   582,
      10,   546,   270,   362,    11,   602,   371,   140,   601,   327,
     591,   340,   136,   292,   136,   292,   136,    12,   417,   115,
     419,   420,   328,   120,   220,   122,   603,   137,   137,   137,
     141,   232,   389,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     350,   355,   527,   416,   471,     0,   281,   282,     0,   331,
       0,     0,     0,     0,     0,   428,     0,   136,   136,   332,
     174,     0,     0,     0,   438,     0,     0,     8,   136,     0,
       9,    13,   344,     0,     0,    10,     0,   348,   349,    11,
       0,   351,     0,   353,   354,     0,   356,   357,     0,   383,
     359,     0,    12,     0,   360,   361,     0,     0,   363,   395,
       0,     0,   503,     0,   504,   136,   136,     0,     0,     0,
       0,     0,   509,   137,     0,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   520,   521,     0,   522,
       0,   370,     0,     0,   438,     0,     0,     0,     0,     0,
     161,   162,   175,   176,   177,   173,   323,   179,   180,   181,
       0,   399,   400,   401,     0,     0,    13,   534,     0,   536,
       0,   538,   182,   183,   184,   185,   186,   187,     0,     0,
       0,   438,   189,   190,   191,     0,     0,     0,     0,     0,
       0,   137,     0,     0,   137,     0,     0,     0,     0,     0,
       0,     0,     0,   137,     0,     0,     0,   137,   137,     0,
       0,     0,     0,     0,     0,     0,   444,     0,     0,     0,
       0,     0,   137,     0,   137,     0,   137,   137,     0,     0,
       0,     0,     0,   573,     0,     0,   458,     0,     0,     0,
       0,     0,     0,     0,     0,   323,   323,     0,     0,     0,
       0,     0,   323,     0,     0,     0,   323,   323,     0,     0,
       0,     8,     0,     0,     9,   481,   482,     0,     0,    10,
     596,   597,    19,    11,    54,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,     0,    12,     0,    30,    31,
      32,   322,     0,     0,     0,     0,     0,     0,   510,   511,
     512,   513,     0,    61,    62,    63,     0,     0,     0,     0,
     519,    65,    66,     0,   599,     0,    68,     0,    69,     0,
       0,     0,     0,     0,    71,     0,     0,     0,     0,     2,
     528,   529,     0,   199,   137,   323,   137,   137,   323,     0,
       0,     0,     0,     0,    72,    73,    74,    75,    76,    77,
      13,     0,     0,   323,     0,     0,   323,     0,     8,     0,
       0,     9,   323,     0,     0,     0,    10,     0,     0,     0,
      11,    54,   545,     0,   444,     0,     0,     0,     0,     0,
     322,   322,     0,    12,     0,     0,     0,   322,     0,   560,
       0,   322,   322,     0,     0,     0,     0,     0,     0,     0,
      61,    62,    63,     0,     0,   570,   571,   572,    65,    66,
     575,    67,     0,    68,     0,    69,   560,   323,   324,   323,
       0,    71,     0,     0,   323,   589,   323,     0,   137,     0,
     137,     0,     0,   323,     0,   323,     0,   323,   137,     0,
       0,    72,    73,    74,    75,    76,    77,    13,     0,     0,
       0,     0,   137,   137,     0,   137,     0,   605,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   137,     0,     0,
     322,     0,     0,   322,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   137,     0,   137,     0,   137,   322,     0,
       0,   322,     0,     0,     0,     0,     0,   322,     0,     0,
       0,   323,     0,   323,   323,   179,   180,   324,   324,     0,
       0,   323,   323,   323,   324,     0,     0,     0,   324,   324,
     182,   183,   184,   185,   186,   187,     0,     0,     0,   323,
     323,   190,   191,   323,     0,     0,     0,     0,   137,   137,
       0,     0,   323,     0,   325,     0,     0,     0,     0,   137,
       0,     0,   322,     0,   322,     0,     0,     0,     0,   322,
       0,   322,     0,     0,     0,     0,     0,     0,   322,     0,
     322,     0,   322,   551,     0,     0,     0,     0,     0,     0,
     308,     0,     0,   552,     0,     0,   137,   137,     0,   175,
     176,   177,   178,     0,   179,   180,   181,   324,     0,     0,
     324,     0,     0,     0,     0,     0,     0,     0,     0,   182,
     183,   184,   185,   186,   187,   324,     0,   188,   324,   189,
     190,   191,     0,     0,   324,     0,     0,     0,     0,     0,
       0,     0,     0,   325,   325,     0,   322,     0,   322,   322,
     325,     0,     0,     0,   325,   325,   322,   322,   322,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   322,   322,     0,     0,   322,     0,
       0,     0,     0,     0,     0,   600,   398,   322,     0,   324,
       0,   324,     0,     0,     0,     0,   324,     0,   324,     0,
       0,     0,     0,     0,     0,   324,     0,   324,     0,   324,
      -2,    19,     0,     0,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     0,   175,     0,    30,    31,    32,
     179,   180,   181,   325,     0,     0,   325,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,   184,   185,   186,
     187,   325,     0,     0,   325,   189,   190,   191,     0,     0,
     325,     0,     0,     0,     0,     0,     0,     0,     2,   464,
       0,     0,   464,   324,     0,   324,   324,     0,     0,     0,
       0,     0,     0,   324,   324,   324,     0,   464,     0,     0,
     464,     0,     0,   179,   180,   181,   489,     0,     0,     0,
       0,   324,   324,     0,     0,   324,     0,     0,   182,   183,
     184,   185,   186,   187,   324,   325,     0,   325,   189,   190,
     191,     0,   325,     0,   325,     0,     0,     0,     0,     0,
       0,   325,     0,   325,     0,   325,     0,     0,     0,     0,
       0,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,   524,     0,   526,    30,    31,    32,   175,   530,   177,
     532,     0,   179,   180,   181,     0,     0,   533,     0,   535,
       0,   537,     0,     0,     0,     0,     0,   182,   183,   184,
     185,   186,   187,     0,     0,     0,     0,   189,   190,   191,
       0,     0,     0,     0,     0,     2,     0,     0,     0,   325,
       0,   325,   325,     0,     0,     0,     0,     0,     0,   325,
     325,   325,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   325,   325,     0,
       0,   325,     0,     0,     0,   574,     0,   576,   577,     0,
     325,     0,     0,     0,     0,   584,   585,   586,     0,     0,
       0,     0,     0,     0,     0,   387,     0,     8,     0,     0,
       9,     0,     0,   593,   594,    10,     0,   595,     0,    11,
      54,     0,     0,     0,     0,   295,   604,   296,     0,   297,
     298,   299,    12,   300,   301,   302,     0,   303,     0,     0,
     304,     0,     0,     0,     0,     0,     0,     0,   305,    61,
      62,    63,     0,     0,     0,     0,     0,    65,    66,     0,
      67,     0,    68,     0,   306,     0,     0,     0,     0,     0,
      71,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   307,     0,     0,     0,     0,
      72,    73,    74,    75,    76,    77,    13,   402,     0,     8,
       0,     0,     9,     0,     0,     0,     0,    10,     0,     0,
       0,    11,    54,     0,     0,     0,     0,   295,     0,   296,
       0,   297,   298,   299,    12,   300,   301,   302,     0,   303,
       0,     0,   304,     0,     0,     0,     0,     0,     0,     0,
     305,    61,    62,    63,     0,     0,     0,     0,     0,    65,
      66,     0,    67,     0,    68,     0,   306,     0,     0,     0,
       0,     0,    71,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   307,     0,     0,
       0,     0,    72,    73,    74,    75,    76,    77,    13,   405,
       0,     8,     0,     0,     9,     0,     0,     0,     0,    10,
       0,     0,     0,    11,    54,     0,     0,     0,     0,   295,
       0,   296,     0,   297,   298,   299,    12,   300,   301,   302,
       0,   303,     0,     0,   304,     0,     0,     0,     0,     0,
       0,     0,   305,    61,    62,    63,     0,     0,     0,     0,
       0,    65,    66,     0,    67,     0,    68,     0,   306,     0,
       0,     0,     0,     0,    71,     0,   555,     0,     8,     0,
       0,     9,     0,     0,     0,     0,    10,     0,     0,   307,
      11,    54,     0,     0,    72,    73,    74,    75,    76,    77,
      13,    55,     0,    12,    56,    57,     0,     0,    58,     0,
       0,     0,     0,   556,     0,    59,    60,     0,     0,     0,
      61,    62,    63,     0,     0,     0,     0,    64,    65,    66,
       0,    67,     0,    68,     0,    69,     0,     0,     0,   557,
      70,    71,     0,   166,     0,     8,     0,     0,     9,     0,
       0,     0,     0,    10,     0,     0,     0,    11,    54,     0,
       0,    72,    73,    74,    75,    76,    77,    13,    55,     0,
      12,    56,    57,     0,     0,    58,     0,     0,     0,     0,
       0,     0,    59,    60,     0,     0,     0,    61,    62,    63,
       0,     0,     0,     0,    64,    65,    66,     0,    67,     0,
      68,   167,    69,     0,     0,     0,     0,    70,    71,     0,
     272,     0,     8,     0,     0,     9,     0,     0,     0,     0,
      10,     0,     0,     0,    11,    54,     0,     0,    72,    73,
      74,    75,    76,    77,    13,    55,     0,    12,    56,    57,
       0,     0,    58,     0,     0,     0,     0,     0,     0,    59,
      60,     0,     0,     0,    61,    62,    63,     0,     0,     0,
       0,    64,    65,    66,     0,    67,   273,    68,     0,    69,
       0,     0,     0,     0,    70,    71,     0,   277,     0,     8,
       0,     0,     9,     0,     0,     0,     0,    10,     0,     0,
       0,    11,    54,     0,     0,    72,    73,    74,    75,    76,
      77,    13,    55,     0,    12,    56,    57,     0,     0,    58,
       0,     0,     0,     0,     0,     0,    59,    60,     0,     0,
       0,    61,    62,    63,     0,     0,     0,     0,    64,    65,
      66,     0,    67,   278,    68,     0,    69,     0,     0,     0,
       0,    70,    71,     0,   449,     0,     8,     0,     0,     9,
       0,     0,     0,     0,    10,     0,     0,     0,    11,    54,
       0,     0,    72,    73,    74,    75,    76,    77,    13,    55,
       0,    12,    56,    57,     0,     0,    58,     0,     0,     0,
       0,     0,     0,    59,    60,     0,     0,     0,    61,    62,
      63,     0,     0,     0,     0,    64,    65,    66,     0,    67,
     450,    68,     0,    69,     0,     0,     0,     0,    70,    71,
       0,   163,     0,     8,     0,     0,     9,     0,     0,     0,
       0,    10,     0,     0,     0,    11,    54,     0,     0,    72,
      73,    74,    75,    76,    77,    13,    55,     0,    12,    56,
      57,     0,     0,    58,     0,     0,     0,     0,     0,     0,
      59,    60,     0,     0,     0,    61,    62,    63,     0,     0,
       0,     0,    64,    65,    66,     0,    67,     0,    68,     0,
      69,     0,     0,     0,     0,    70,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    72,    73,    74,    75,
      76,    77,    13,     8,     0,     0,     9,     0,     0,     0,
       0,    10,     0,     0,     0,    11,    54,     0,     0,     0,
       0,   295,   463,   296,     0,   297,   298,   299,    12,   300,
     301,   302,     0,   303,     0,     0,   304,     0,     0,     0,
       0,     0,     0,     0,   305,    61,    62,    63,     0,     0,
       0,     0,     0,    65,    66,     0,    67,     0,    68,     0,
     306,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   307,     0,     0,     0,     0,    72,    73,    74,    75,
      76,    77,    13,     8,     0,     0,     9,     0,     0,     0,
       0,    10,     0,     0,     0,    11,    54,     0,     0,     0,
       0,   295,     0,   296,   466,   297,   298,   299,    12,   300,
     301,   302,     0,   303,     0,     0,   304,     0,     0,     0,
       0,     0,     0,     0,   305,    61,    62,    63,     0,     0,
       0,     0,     0,    65,    66,     0,    67,     0,    68,     0,
     306,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   307,     0,     0,     0,     0,    72,    73,    74,    75,
      76,    77,    13,     8,     0,     0,     9,     0,     0,     0,
       0,    10,     0,     0,     0,    11,    54,     0,     0,     0,
       0,   295,     0,   296,     0,   297,   298,   299,    12,   300,
     301,   302,     0,   303,     0,     0,   304,     0,     0,     0,
       0,     0,     0,     0,   305,    61,    62,    63,     0,     0,
       0,     0,     0,    65,    66,     0,    67,     0,    68,     0,
     306,   478,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   307,     0,     0,     0,     0,    72,    73,    74,    75,
      76,    77,    13,     8,     0,     0,     9,     0,     0,     0,
       0,    10,     0,     0,     0,    11,    54,     0,     0,     0,
       0,   295,     0,   296,     0,   297,   298,   299,    12,   300,
     301,   302,     0,   303,     0,     0,   304,     0,     0,     0,
       0,     0,     0,     0,   305,    61,    62,    63,     0,     0,
       0,     0,     0,    65,    66,     0,    67,     0,    68,     0,
     306,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   307,   480,     0,     0,     0,    72,    73,    74,    75,
      76,    77,    13,     8,     0,     0,     9,     0,     0,     0,
       0,    10,     0,     0,     0,    11,    54,     0,     0,     0,
       0,   295,     0,   296,     0,   297,   298,   299,    12,   300,
     301,   302,     0,   303,     0,     0,   304,     0,     0,     0,
       0,     0,     0,     0,   305,    61,    62,    63,     0,     0,
       0,     0,     0,    65,    66,     0,    67,     0,    68,     0,
     306,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       8,     0,     0,     9,     0,     0,     0,     0,    10,     0,
       0,   307,    11,    54,     0,     0,    72,    73,    74,    75,
      76,    77,    13,    55,     0,    12,    56,    57,     0,     0,
      58,     0,     0,     0,     0,   556,     0,    59,    60,     0,
       0,     0,    61,    62,    63,     0,     0,     0,     0,    64,
      65,    66,     0,    67,     0,    68,     0,    69,   581,     0,
       0,   557,    70,    71,     0,     0,     0,     8,     0,     0,
       9,     0,     0,     0,     0,    10,     0,     0,     0,    11,
      54,     0,     0,    72,    73,    74,    75,    76,    77,    13,
      55,     0,    12,    56,    57,     0,     0,    58,     0,     0,
       0,     0,     0,     0,    59,    60,     0,     0,     0,    61,
      62,    63,     0,     0,     0,     0,    64,    65,    66,     0,
      67,   476,    68,     0,    69,     0,     0,     0,     0,    70,
      71,     0,     0,     0,     0,     0,     0,   175,   176,   177,
     178,     0,   179,   180,   181,     0,     0,     0,     0,     0,
      72,    73,    74,    75,    76,    77,    13,   182,   183,   184,
     185,   186,   187,   553,     0,   188,     0,   189,   190,   191,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   175,
     176,   177,   178,     0,   179,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   592,     0,     0,   182,
     183,   184,   185,   186,   187,     0,     0,   188,     0,   189,
     190,   191,   175,   176,   177,   178,     0,   179,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   238,   182,   183,   184,   185,   186,   187,     0,     0,
     188,     0,   189,   190,   191,   175,   176,   177,   178,     0,
     179,   180,   181,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   474,   182,   183,   184,   185,   186,
     187,     0,     0,   188,     0,   189,   190,   191,   175,   176,
     177,   178,     0,   179,   180,   181,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   182,   183,
     184,   185,   186,   187,   442,     0,   188,     0,   189,   190,
     191,     0,     0,     0,     0,     0,     0,   175,   176,   177,
     178,     0,   179,   180,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   182,   183,   184,
     185,   186,   187,   475,     0,   188,     0,   189,   190,   191,
       0,     0,     0,     0,   175,   176,   177,   178,     0,   179,
     180,   181,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   182,   183,   184,   185,   186,   187,
     440,     0,   188,     0,   189,   190,   191,     0,     0,   175,
     176,   177,   178,     0,   179,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   182,
     183,   184,   185,   186,   187,     0,   240,   188,     0,   189,
     190,   191,   175,   176,   177,   178,     0,   179,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   182,   183,   184,   185,   186,   187,     0,   441,
     188,     0,   189,   190,   191,   175,   176,   177,   178,     0,
     179,   180,   181,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,   184,   185,   186,
     187,     0,   443,   188,     0,   189,   190,   191,   175,   176,
     177,   178,     0,   179,   180,   181,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   182,   183,
     184,   185,   186,   187,     0,     0,   188,     0,   189,   190,
     191,   175,   176,   177,   178,     0,   179,   180,   181,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   183,   184,   185,   186,   187,     0,     0,   188,
       0,   189,   190,   191,     0,     0,     0,   247,   175,   176,
     177,   178,     0,   179,   180,   181,     0,   243,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   182,   183,
     184,   185,   186,   187,     0,     0,   188,     0,   189,   190,
     191,   175,   176,   177,   178,     0,   179,   180,   181,     0,
     369,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   183,   184,   185,   186,   187,     0,     0,   188,
       0,   189,   190,   191,   175,   176,   177,   178,     0,   179,
     180,   181,     0,   447,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   182,   183,   184,   185,   186,   187,
       0,     0,   188,     0,   189,   190,   191,   175,   176,   177,
     178,     0,   179,   180,   181,     0,     0,     0,   448,     0,
       0,     0,     0,     0,     0,     0,     0,   182,   183,   184,
     185,   186,   187,     0,     0,   188,     0,   189,   190,   191,
     175,   176,   177,   178,     0,   179,   180,   181,     0,     0,
       0,     0,     0,     0,   583,     0,     0,     0,     0,     0,
     182,   183,   184,   185,   186,   187,     0,     0,   188,     0,
     189,   190,   191,   175,   176,   177,   178,     0,   179,   180,
     181,     0,     0,     0,     0,     0,   598,     0,     0,     0,
       0,     0,     0,   182,   183,   184,   185,   186,   187,     0,
       0,   188,     0,   189,   190,   191,   175,   176,   177,   178,
       0,   179,   180,   181,     0,   608,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   182,   183,   184,   185,
     186,   187,     0,     0,   188,     0,   189,   190,   191,   175,
     176,   177,   178,     0,   179,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   182,
     183,   184,   185,   186,   187,     0,     0,   188,     0,   189,
     190,   191,   175,   176,   177,   178,     0,   179,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   182,   183,   184,   185,   186,   187,     0,     0,
     514,     0,   189,   190,   191,   175,   176,   177,     0,     0,
     179,   180,   181,     0,     0,     0,     0,     0,  -183,     0,
       0,     0,     0,     0,  -183,   182,   183,   184,   185,   186,
     187,     0,     0,     0,     0,   189,   190,   191
  };

  const short
  Parser::yycheck_[] =
  {
       2,   113,   228,    14,     4,    68,   334,     5,    59,   435,
      14,    32,    14,     5,     4,     7,     3,     3,    43,    21,
      22,    23,    24,    25,    19,    27,    28,    29,    30,     0,
      32,    57,    61,    33,     1,    55,     3,    57,    67,     6,
       5,    67,     7,    33,    11,     5,    67,     7,    15,    16,
      50,    55,    50,    55,    56,    57,     3,    59,    83,     6,
      50,    28,     3,    58,    11,     6,    58,    69,    15,    61,
      11,    58,    58,    19,    15,     1,     5,     3,     7,    56,
       6,    28,     5,    59,     7,    11,   414,    28,   416,    15,
      16,    58,    67,    58,    69,    21,    61,    23,    58,    25,
      26,    27,    28,    29,    30,    31,    83,    33,    59,     0,
      36,    58,    58,     4,   125,    61,   542,    28,    44,    45,
      46,    47,   124,   125,   126,    92,    43,    53,    54,    58,
      56,   194,    58,   196,    60,    58,    61,    55,    61,    28,
      66,   374,    33,   376,    57,    92,    63,    88,    28,   151,
      28,    92,    56,   151,    67,    81,    67,    75,    83,    28,
      86,    87,    88,    89,    90,    91,    92,    57,    55,    56,
       1,    75,     3,   285,    28,     6,    28,    67,    67,    55,
      11,    28,    29,    30,    15,    16,    65,    67,    75,    67,
     192,   193,   203,   195,    59,   197,   207,    28,    67,    75,
      55,   203,   204,    56,    83,   207,   208,   209,   210,    62,
     212,   231,    62,    67,   234,    67,    59,   237,    56,    63,
      75,   223,    75,   225,    68,   227,   228,    58,    56,   231,
      74,     1,   234,     3,    57,   237,     6,    75,     1,    63,
       3,    11,   468,     6,    67,    15,   296,   249,    11,   300,
     301,    63,    15,    55,    56,    59,   306,   307,    28,    57,
      62,    92,     1,    67,     3,    28,    63,     6,    56,    67,
      57,    68,    11,    75,    57,    63,    15,   124,   298,    61,
      67,   292,    55,    55,    67,    67,    70,    61,    58,    28,
     292,    75,   294,    67,   292,    58,   298,   299,   300,   301,
      61,   364,    61,    55,   306,    70,    67,    55,    67,    55,
      75,    62,   203,   539,   540,    55,   207,    85,     3,    28,
      57,     6,    92,    67,    59,   336,    11,    60,    62,    92,
      15,    60,    75,   335,   336,   337,   338,    67,    60,   339,
      67,    60,    14,    28,     3,   192,    60,     6,   195,   339,
      73,    56,    11,    92,    57,    57,    15,   204,    57,    55,
      57,   208,   209,   374,    77,   376,    83,    77,    55,    28,
      70,    56,   374,    55,   376,    60,   223,    75,   225,    22,
      75,   383,    75,    68,    75,   383,    58,    75,    60,    75,
      24,    62,    64,   395,    61,    67,    68,   395,    82,    57,
      69,    60,    20,   294,    53,    54,    61,    92,   299,    70,
      71,    72,    73,    60,    60,    57,    69,    55,   416,   421,
     422,    70,    71,    72,    73,    55,   426,   429,   428,   431,
     428,    55,    35,    92,    75,    55,   426,   439,   428,    55,
     438,    55,    55,   334,    61,    60,    75,    75,   339,    60,
      62,   453,   454,    62,   456,   346,    33,    50,   460,   460,
     414,   505,     3,   426,   438,     6,   468,   428,   470,   558,
      11,   516,   193,   249,    15,   590,   285,    31,   590,   207,
     573,   223,   484,   374,   486,   376,   488,    28,   335,    20,
     337,   338,   207,    24,   126,    26,   591,    28,    29,    30,
      31,   151,   298,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     231,   237,   470,   414,   395,    -1,   198,   199,    -1,    70,
      -1,    -1,    -1,    -1,    -1,   426,    -1,   539,   540,   211,
      71,    -1,    -1,    -1,   435,    -1,    -1,     3,   550,    -1,
       6,    92,   224,    -1,    -1,    11,    -1,   229,   230,    15,
      -1,   233,    -1,   235,   236,    -1,   238,   239,    -1,   460,
     242,    -1,    28,    -1,   246,   247,    -1,    -1,   250,   470,
      -1,    -1,   429,    -1,   431,   587,   588,    -1,    -1,    -1,
      -1,    -1,   439,   124,    -1,   126,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   453,   454,    -1,   456,
      -1,   283,    -1,    -1,   505,    -1,    -1,    -1,    -1,    -1,
      65,    66,    48,    49,    50,    70,   206,    53,    54,    55,
      -1,   303,   304,   305,    -1,    -1,    92,   484,    -1,   486,
      -1,   488,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,   542,    78,    79,    80,    -1,    -1,    -1,    -1,    -1,
      -1,   192,    -1,    -1,   195,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   204,    -1,    -1,    -1,   208,   209,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   358,    -1,    -1,    -1,
      -1,    -1,   223,    -1,   225,    -1,   227,   228,    -1,    -1,
      -1,    -1,    -1,   550,    -1,    -1,   378,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   295,   296,    -1,    -1,    -1,
      -1,    -1,   302,    -1,    -1,    -1,   306,   307,    -1,    -1,
      -1,     3,    -1,    -1,     6,   407,   408,    -1,    -1,    11,
     587,   588,     1,    15,    16,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    -1,    28,    -1,    17,    18,
      19,   206,    -1,    -1,    -1,    -1,    -1,    -1,   440,   441,
     442,   443,    -1,    45,    46,    47,    -1,    -1,    -1,    -1,
     452,    53,    54,    -1,    56,    -1,    58,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    58,
     472,   473,    -1,    75,   335,   385,   337,   338,   388,    -1,
      -1,    -1,    -1,    -1,    86,    87,    88,    89,    90,    91,
      92,    -1,    -1,   403,    -1,    -1,   406,    -1,     3,    -1,
      -1,     6,   412,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      15,    16,   514,    -1,   516,    -1,    -1,    -1,    -1,    -1,
     295,   296,    -1,    28,    -1,    -1,    -1,   302,    -1,   531,
      -1,   306,   307,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      45,    46,    47,    -1,    -1,   547,   548,   549,    53,    54,
     552,    56,    -1,    58,    -1,    60,   558,   467,   206,   469,
      -1,    66,    -1,    -1,   474,   567,   476,    -1,   429,    -1,
     431,    -1,    -1,   483,    -1,   485,    -1,   487,   439,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,    -1,    -1,
      -1,    -1,   453,   454,    -1,   456,    -1,   599,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   468,    -1,    -1,
     385,    -1,    -1,   388,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   484,    -1,   486,    -1,   488,   403,    -1,
      -1,   406,    -1,    -1,    -1,    -1,    -1,   412,    -1,    -1,
      -1,   551,    -1,   553,   554,    53,    54,   295,   296,    -1,
      -1,   561,   562,   563,   302,    -1,    -1,    -1,   306,   307,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,   579,
     580,    79,    80,   583,    -1,    -1,    -1,    -1,   539,   540,
      -1,    -1,   592,    -1,   206,    -1,    -1,    -1,    -1,   550,
      -1,    -1,   467,    -1,   469,    -1,    -1,    -1,    -1,   474,
      -1,   476,    -1,    -1,    -1,    -1,    -1,    -1,   483,    -1,
     485,    -1,   487,    32,    -1,    -1,    -1,    -1,    -1,    -1,
     206,    -1,    -1,    42,    -1,    -1,   587,   588,    -1,    48,
      49,    50,    51,    -1,    53,    54,    55,   385,    -1,    -1,
     388,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,   403,    -1,    76,   406,    78,
      79,    80,    -1,    -1,   412,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   295,   296,    -1,   551,    -1,   553,   554,
     302,    -1,    -1,    -1,   306,   307,   561,   562,   563,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   579,   580,    -1,    -1,   583,    -1,
      -1,    -1,    -1,    -1,    -1,   590,   302,   592,    -1,   467,
      -1,   469,    -1,    -1,    -1,    -1,   474,    -1,   476,    -1,
      -1,    -1,    -1,    -1,    -1,   483,    -1,   485,    -1,   487,
       0,     1,    -1,    -1,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    48,    -1,    17,    18,    19,
      53,    54,    55,   385,    -1,    -1,   388,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,   403,    -1,    -1,   406,    78,    79,    80,    -1,    -1,
     412,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,   385,
      -1,    -1,   388,   551,    -1,   553,   554,    -1,    -1,    -1,
      -1,    -1,    -1,   561,   562,   563,    -1,   403,    -1,    -1,
     406,    -1,    -1,    53,    54,    55,   412,    -1,    -1,    -1,
      -1,   579,   580,    -1,    -1,   583,    -1,    -1,    68,    69,
      70,    71,    72,    73,   592,   467,    -1,   469,    78,    79,
      80,    -1,   474,    -1,   476,    -1,    -1,    -1,    -1,    -1,
      -1,   483,    -1,   485,    -1,   487,    -1,    -1,    -1,    -1,
      -1,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   467,    -1,   469,    17,    18,    19,    48,   474,    50,
     476,    -1,    53,    54,    55,    -1,    -1,   483,    -1,   485,
      -1,   487,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,   551,
      -1,   553,   554,    -1,    -1,    -1,    -1,    -1,    -1,   561,
     562,   563,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   579,   580,    -1,
      -1,   583,    -1,    -1,    -1,   551,    -1,   553,   554,    -1,
     592,    -1,    -1,    -1,    -1,   561,   562,   563,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,     3,    -1,    -1,
       6,    -1,    -1,   579,   580,    11,    -1,   583,    -1,    15,
      16,    -1,    -1,    -1,    -1,    21,   592,    23,    -1,    25,
      26,    27,    28,    29,    30,    31,    -1,    33,    -1,    -1,
      36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      46,    47,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,
      56,    -1,    58,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,    92,     1,    -1,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    15,    16,    -1,    -1,    -1,    -1,    21,    -1,    23,
      -1,    25,    26,    27,    28,    29,    30,    31,    -1,    33,
      -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,
      54,    -1,    56,    -1,    58,    -1,    60,    -1,    -1,    -1,
      -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,
      -1,    -1,    86,    87,    88,    89,    90,    91,    92,     1,
      -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,
      -1,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    21,
      -1,    23,    -1,    25,    26,    27,    28,    29,    30,    31,
      -1,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    45,    46,    47,    -1,    -1,    -1,    -1,
      -1,    53,    54,    -1,    56,    -1,    58,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    66,    -1,     1,    -1,     3,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    81,
      15,    16,    -1,    -1,    86,    87,    88,    89,    90,    91,
      92,    26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,
      -1,    -1,    -1,    38,    -1,    40,    41,    -1,    -1,    -1,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    56,    -1,    58,    -1,    60,    -1,    -1,    -1,    64,
      65,    66,    -1,     1,    -1,     3,    -1,    -1,     6,    -1,
      -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,    26,    -1,
      28,    29,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    -1,    -1,    -1,    45,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    54,    -1,    56,    -1,
      58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,
       1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    15,    16,    -1,    -1,    86,    87,
      88,    89,    90,    91,    92,    26,    -1,    28,    29,    30,
      -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    -1,    -1,    -1,    45,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    -1,    56,    57,    58,    -1,    60,
      -1,    -1,    -1,    -1,    65,    66,    -1,     1,    -1,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,
      -1,    15,    16,    -1,    -1,    86,    87,    88,    89,    90,
      91,    92,    26,    -1,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    -1,
      -1,    45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      54,    -1,    56,    57,    58,    -1,    60,    -1,    -1,    -1,
      -1,    65,    66,    -1,     1,    -1,     3,    -1,    -1,     6,
      -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,
      -1,    -1,    86,    87,    88,    89,    90,    91,    92,    26,
      -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    56,
      57,    58,    -1,    60,    -1,    -1,    -1,    -1,    65,    66,
      -1,     1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,    86,
      87,    88,    89,    90,    91,    92,    26,    -1,    28,    29,
      30,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    41,    -1,    -1,    -1,    45,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    54,    -1,    56,    -1,    58,    -1,
      60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,    92,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    21,    22,    23,    -1,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,    92,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    21,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,    92,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    21,    -1,    23,    -1,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,
      60,    61,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    -1,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,    92,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    21,    -1,    23,    -1,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    81,    82,    -1,    -1,    -1,    86,    87,    88,    89,
      90,    91,    92,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,
      -1,    21,    -1,    23,    -1,    25,    26,    27,    28,    29,
      30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,
       3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,
      -1,    81,    15,    16,    -1,    -1,    86,    87,    88,    89,
      90,    91,    92,    26,    -1,    28,    29,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    38,    -1,    40,    41,    -1,
      -1,    -1,    45,    46,    47,    -1,    -1,    -1,    -1,    52,
      53,    54,    -1,    56,    -1,    58,    -1,    60,    61,    -1,
      -1,    64,    65,    66,    -1,    -1,    -1,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    15,
      16,    -1,    -1,    86,    87,    88,    89,    90,    91,    92,
      26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,
      56,    32,    58,    -1,    60,    -1,    -1,    -1,    -1,    65,
      66,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      86,    87,    88,    89,    90,    91,    92,    68,    69,    70,
      71,    72,    73,    32,    -1,    76,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,
      49,    50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    -1,    76,    -1,    78,
      79,    80,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    68,    69,    70,    71,    72,    73,    -1,    -1,
      76,    -1,    78,    79,    80,    48,    49,    50,    51,    -1,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    68,    69,    70,    71,    72,
      73,    -1,    -1,    76,    -1,    78,    79,    80,    48,    49,
      50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    35,    -1,    76,    -1,    78,    79,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    37,    -1,    76,    -1,    78,    79,    80,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    -1,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      39,    -1,    76,    -1,    78,    79,    80,    -1,    -1,    48,
      49,    50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    42,    76,    -1,    78,
      79,    80,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    42,
      76,    -1,    78,    79,    80,    48,    49,    50,    51,    -1,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    -1,    42,    76,    -1,    78,    79,    80,    48,    49,
      50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    -1,    -1,    76,    -1,    78,    79,
      80,    48,    49,    50,    51,    -1,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    -1,    -1,    76,
      -1,    78,    79,    80,    -1,    -1,    -1,    84,    48,    49,
      50,    51,    -1,    53,    54,    55,    -1,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    -1,    -1,    76,    -1,    78,    79,
      80,    48,    49,    50,    51,    -1,    53,    54,    55,    -1,
      57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    -1,    -1,    76,
      -1,    78,    79,    80,    48,    49,    50,    51,    -1,    53,
      54,    55,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      -1,    -1,    76,    -1,    78,    79,    80,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    59,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    -1,    76,    -1,    78,    79,    80,
      48,    49,    50,    51,    -1,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    -1,    -1,    76,    -1,
      78,    79,    80,    48,    49,    50,    51,    -1,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    -1,
      -1,    76,    -1,    78,    79,    80,    48,    49,    50,    51,
      -1,    53,    54,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    -1,    -1,    76,    -1,    78,    79,    80,    48,
      49,    50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    -1,    76,    -1,    78,
      79,    80,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    -1,
      76,    -1,    78,    79,    80,    48,    49,    50,    -1,    -1,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    -1,    -1,    -1,    -1,    78,    79,    80
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    58,    99,   100,   212,   213,     1,     3,     6,
      11,    15,    28,    92,   197,   214,   215,   216,     0,     1,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      17,    18,    19,   101,   102,   103,   104,   105,   106,   107,
     108,   111,   112,   113,   114,   115,   118,   121,   125,   126,
     212,     3,   213,    59,    16,    26,    29,    30,    33,    40,
      41,    45,    46,    47,    52,    53,    54,    56,    58,    60,
      65,    66,    86,    87,    88,    89,    90,    91,   146,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   197,   198,   202,
      59,    59,    59,    60,   197,   198,   197,   197,   197,   197,
     198,   197,   198,   197,    56,    60,    68,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   197,   198,   182,   182,
     187,   198,   197,   102,   103,   197,   199,   202,   203,   205,
     206,   212,   200,   203,   203,   207,   208,   146,   200,   146,
     146,   147,   147,     1,   145,   146,     1,    59,   145,   146,
     177,   178,   197,   147,   198,    48,    49,    50,    51,    53,
      54,    55,    68,    69,    70,    71,    72,    73,    76,    78,
      79,    80,    43,    83,    56,    62,    56,    63,    56,    75,
     175,   179,   180,    56,    75,    55,    55,    56,    75,    55,
      63,    55,    43,    55,   181,   182,   197,   201,   202,   182,
     191,    55,    85,    68,    74,    14,    55,    68,    62,    55,
      28,    67,   199,    28,    67,    28,    32,    67,    34,    28,
      42,    57,    67,    57,    59,    59,    67,    84,    61,    67,
      62,    65,   146,   146,   146,   146,   146,   146,   146,   146,
     146,   146,   146,   146,   146,   146,   146,   146,   146,   182,
     167,   197,     1,    57,   145,   146,   182,     1,    57,   145,
     197,   146,   146,    75,    61,    67,     1,    16,   193,   194,
     202,   204,   212,   182,    60,    21,    23,    25,    26,    27,
      29,    30,    31,    33,    36,    44,    60,    81,   129,   130,
     131,   132,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   147,   149,   150,   151,     1,   193,   194,   182,
     182,    70,   146,   197,    60,    67,    67,    70,    75,    60,
     181,   182,   191,   192,   146,   182,    60,   192,   146,   146,
     206,   146,   203,   146,   146,   208,   146,   146,    60,   146,
     146,   146,   178,   146,    56,    57,    57,    57,    57,    57,
     146,   180,    57,    57,    67,    57,    67,   202,    55,     1,
     109,   110,   197,   212,     1,   128,   129,     1,   128,   205,
       1,   197,   209,   210,   211,   212,   200,   200,   129,   146,
     146,   146,     1,   128,   197,     1,   128,    77,    77,    57,
      57,    57,    55,   108,   116,   117,   212,   182,   202,   182,
     182,     5,     7,   106,   107,   119,   120,   127,   212,    67,
      69,    75,    55,   106,   107,   122,   123,   124,   212,    75,
      39,    42,    35,    42,   146,   162,   163,    57,    59,     1,
      57,   145,    75,    75,    75,   204,    75,   204,   146,    61,
      67,   197,    22,    22,   129,    24,    24,    28,    62,    28,
      67,   211,    28,    28,    34,    37,    32,    61,    61,    82,
      82,   146,   146,    55,    75,    55,    75,    55,    75,   129,
      61,   117,   108,    57,    61,    69,   197,   197,    61,   119,
     106,   107,   127,   182,   182,    60,    61,   123,   124,   182,
     146,   146,   146,   146,    76,    61,    67,    57,    57,   146,
     182,   182,   182,   109,   129,   192,   129,   210,   146,   146,
     129,    60,   129,   129,   182,   129,   182,   129,   182,    62,
      62,    69,   122,    20,   195,   146,   163,    55,    55,    55,
      75,    32,    42,    32,    35,     1,    38,    64,   133,   134,
     146,    55,    55,    55,   192,   192,    61,    60,    55,   196,
     146,   146,   146,   182,   129,   146,   129,   129,    61,    62,
      62,    61,   134,    62,   129,   129,   129,    75,    75,   146,
      60,   195,    32,   129,   129,   129,   182,   182,    61,    56,
     147,   175,   179,   196,   129,   146,    61,    61,    57
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
     205,   205,   206,   207,   207,   208,   208,   209,   209,   210,
     210,   210,   211,   212,   212,   213,   213,   213,   213,   214,
     215,   216
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
       3,     4,     4,     3,     4,     6,     4,     6,     6,     3,
       6,     3,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     2,     3,     3,     5,
       5,     3,     3,     1,     3,     3,     1,     2,     5,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     4,     6,     3,     5,     2,     3,     1,
       1,     0,     3,     1,     3,     1,     4,     0,     4,     4,
       0,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     3,     1,     3,     2,     1,     2,     1,
       3,     1,     3,     3,     1,     5,     3,     3,     1,     2,
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
  "VariableBinding", "VariableSelections", "VariableSelection",
  "LocalFunctionDefinitions", "AttributedLocalFunctionDefinition",
  "LocalFunctionDefinition", "Attributes", "Attribute", "BasicAttribute",
  "SymbolAttribute", "ExpressionAttribute", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   447,   447,   457,   463,   471,   477,   487,   493,   497,
     505,   509,   513,   517,   521,   525,   529,   533,   537,   541,
     545,   549,   553,   557,   565,   569,   577,   585,   590,   596,
     602,   610,   616,   621,   628,   634,   641,   647,   651,   659,
     667,   671,   677,   685,   692,   702,   710,   714,   722,   730,
     734,   746,   753,   759,   768,   774,   786,   794,   800,   804,
     810,   814,   820,   827,   833,   847,   851,   858,   864,   873,
     879,   886,   890,   902,   914,   926,   930,   942,   948,   958,
     962,   966,   970,   974,   978,   982,   986,   990,   994,   998,
    1002,  1006,  1014,  1022,  1026,  1034,  1038,  1046,  1052,  1062,
    1066,  1070,  1078,  1086,  1094,  1098,  1106,  1121,  1129,  1133,
    1137,  1142,  1151,  1155,  1159,  1164,  1173,  1177,  1185,  1193,
    1205,  1212,  1222,  1226,  1230,  1234,  1238,  1242,  1246,  1250,
    1254,  1258,  1266,  1270,  1274,  1278,  1282,  1286,  1290,  1302,
    1306,  1310,  1314,  1318,  1322,  1326,  1330,  1334,  1338,  1342,
    1346,  1350,  1354,  1358,  1362,  1366,  1370,  1378,  1382,  1386,
    1394,  1401,  1405,  1410,  1414,  1422,  1427,  1434,  1440,  1448,
    1456,  1463,  1469,  1477,  1485,  1493,  1501,  1509,  1517,  1525,
    1532,  1539,  1546,  1555,  1568,  1572,  1576,  1580,  1584,  1588,
    1592,  1596,  1604,  1608,  1612,  1616,  1624,  1633,  1639,  1649,
    1657,  1665,  1673,  1677,  1685,  1693,  1722,  1729,  1735,  1743,
    1753,  1766,  1780,  1787,  1796,  1803,  1810,  1819,  1824,  1830,
    1846,  1853,  1862,  1866,  1870,  1874,  1878,  1882,  1886,  1890,
    1898,  1906,  1917,  1928,  1936,  1944,  1952,  1960,  1972,  1979,
    1989,  1993,  2001,  2008,  2022,  2029,  2043,  2047,  2055,  2061,
    2074,  2087,  2091,  2096,  2101,  2106,  2111,  2120,  2127,  2139,
    2143,  2152,  2159,  2169,  2176,  2186,  2195,  2201,  2209,  2215,
    2227,  2234,  2243,  2255,  2262,  2271,  2275,  2291,  2298,  2307,
    2313,  2317,  2324,  2337,  2343,  2352,  2359,  2366,  2373,  2380,
    2387,  2394
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
#line 7032 "GrammarParser.cpp"

#line 2400 "../../obj/src/GrammarParser.y"


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
