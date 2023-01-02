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

  case 106: // ChooseRule: "choose" VariableSelections "do" Rule
#line 1107 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseRule::Ptr > () = CST::make< ChooseRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < VariableSelections::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3901 "GrammarParser.cpp"
    break;

  case 107: // IterateRule: "iterate" Rule
#line 1115 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = CST::make< IterateRule >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3909 "GrammarParser.cpp"
    break;

  case 108: // BlockRule: "{" Rules "}"
#line 1123 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = CST::make< BlockRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3917 "GrammarParser.cpp"
    break;

  case 109: // BlockRule: "par" Rules "endpar"
#line 1127 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = CST::make< BlockRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3925 "GrammarParser.cpp"
    break;

  case 110: // BlockRule: "{" error "}"
#line 1131 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3934 "GrammarParser.cpp"
    break;

  case 111: // BlockRule: "par" error "endpar"
#line 1136 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3943 "GrammarParser.cpp"
    break;

  case 112: // SequenceRule: "{|" Rules "|}"
#line 1145 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = CST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3951 "GrammarParser.cpp"
    break;

  case 113: // SequenceRule: "seq" Rules "endseq"
#line 1149 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = CST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 3959 "GrammarParser.cpp"
    break;

  case 114: // SequenceRule: "{|" error "|}"
#line 1153 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3968 "GrammarParser.cpp"
    break;

  case 115: // SequenceRule: "seq" error "endseq"
#line 1158 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3977 "GrammarParser.cpp"
    break;

  case 116: // UpdateRule: DirectCallExpression ":=" Term
#line 1167 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = CST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3985 "GrammarParser.cpp"
    break;

  case 117: // UpdateRule: MethodCallExpression ":=" Term
#line 1171 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = CST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < MethodCallExpression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3993 "GrammarParser.cpp"
    break;

  case 118: // CallRule: CallExpression
#line 1179 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallRule::Ptr > () = CST::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 4001 "GrammarParser.cpp"
    break;

  case 119: // WhileRule: "while" Term "do" Rule
#line 1187 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < WhileRule::Ptr > () = CST::make< WhileRule >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 4009 "GrammarParser.cpp"
    break;

  case 120: // Terms: Terms "," Term
#line 1199 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 4020 "GrammarParser.cpp"
    break;

  case 121: // Terms: Term
#line 1206 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = CST::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 4030 "GrammarParser.cpp"
    break;

  case 122: // Term: Expression
#line 1216 "../../obj/src/GrammarParser.y"
  {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 4038 "GrammarParser.cpp"
    break;

  case 123: // Term: TypeCastingExpression
#line 1220 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 4046 "GrammarParser.cpp"
    break;

  case 124: // Term: OperatorExpression
#line 1224 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 4054 "GrammarParser.cpp"
    break;

  case 125: // Term: LetExpression
#line 1228 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 4062 "GrammarParser.cpp"
    break;

  case 126: // Term: ConditionalExpression
#line 1232 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 4070 "GrammarParser.cpp"
    break;

  case 127: // Term: ChooseExpression
#line 1236 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 4078 "GrammarParser.cpp"
    break;

  case 128: // Term: UniversalQuantifierExpression
#line 1240 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 4086 "GrammarParser.cpp"
    break;

  case 129: // Term: ExistentialQuantifierExpression
#line 1244 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 4094 "GrammarParser.cpp"
    break;

  case 130: // Term: CardinalityExpression
#line 1248 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 4102 "GrammarParser.cpp"
    break;

  case 131: // Term: MatchExpression
#line 1252 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < MatchExpression::Ptr > ();
  }
#line 4110 "GrammarParser.cpp"
    break;

  case 132: // Expression: "(" Term ")"
#line 1260 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< CST::EmbracedExpression >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4118 "GrammarParser.cpp"
    break;

  case 133: // Expression: "(" error ")"
#line 1264 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 4126 "GrammarParser.cpp"
    break;

  case 134: // Expression: CallExpression
#line 1268 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 4134 "GrammarParser.cpp"
    break;

  case 135: // Expression: LiteralCallExpression
#line 1272 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 4142 "GrammarParser.cpp"
    break;

  case 136: // Expression: Literal
#line 1276 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 4150 "GrammarParser.cpp"
    break;

  case 137: // Expression: "+" Expression
#line 1280 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4158 "GrammarParser.cpp"
    break;

  case 138: // Expression: "-" Expression
#line 1284 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4166 "GrammarParser.cpp"
    break;

  case 139: // OperatorExpression: Term "+" Term
#line 1296 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4174 "GrammarParser.cpp"
    break;

  case 140: // OperatorExpression: Term "-" Term
#line 1300 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4182 "GrammarParser.cpp"
    break;

  case 141: // OperatorExpression: Term "*" Term
#line 1304 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4190 "GrammarParser.cpp"
    break;

  case 142: // OperatorExpression: Term "/" Term
#line 1308 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4198 "GrammarParser.cpp"
    break;

  case 143: // OperatorExpression: Term "%" Term
#line 1312 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4206 "GrammarParser.cpp"
    break;

  case 144: // OperatorExpression: Term "^" Term
#line 1316 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4214 "GrammarParser.cpp"
    break;

  case 145: // OperatorExpression: Term "!=" Term
#line 1320 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4222 "GrammarParser.cpp"
    break;

  case 146: // OperatorExpression: Term "=" Term
#line 1324 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4230 "GrammarParser.cpp"
    break;

  case 147: // OperatorExpression: Term "<" Term
#line 1328 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4238 "GrammarParser.cpp"
    break;

  case 148: // OperatorExpression: Term ">" Term
#line 1332 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4246 "GrammarParser.cpp"
    break;

  case 149: // OperatorExpression: Term "<=" Term
#line 1336 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4254 "GrammarParser.cpp"
    break;

  case 150: // OperatorExpression: Term ">=" Term
#line 1340 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4262 "GrammarParser.cpp"
    break;

  case 151: // OperatorExpression: Term "or" Term
#line 1344 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4270 "GrammarParser.cpp"
    break;

  case 152: // OperatorExpression: Term "xor" Term
#line 1348 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4278 "GrammarParser.cpp"
    break;

  case 153: // OperatorExpression: Term "and" Term
#line 1352 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4286 "GrammarParser.cpp"
    break;

  case 154: // OperatorExpression: Term "=>" Term
#line 1356 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4294 "GrammarParser.cpp"
    break;

  case 155: // OperatorExpression: Term "implies" Term
#line 1360 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4302 "GrammarParser.cpp"
    break;

  case 156: // OperatorExpression: "not" Term
#line 1364 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = CST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4310 "GrammarParser.cpp"
    break;

  case 157: // CallExpression: DirectCallExpression
#line 1372 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 4318 "GrammarParser.cpp"
    break;

  case 158: // CallExpression: MethodCallExpression
#line 1376 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 4326 "GrammarParser.cpp"
    break;

  case 159: // CallExpression: IndirectCallExpression
#line 1380 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 4334 "GrammarParser.cpp"
    break;

  case 160: // DirectCallExpression: "this"
#line 1388 "../../obj/src/GrammarParser.y"
  {
      const auto identifier = CST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      identifier->setSpans( m_lexer.fetchSpansAndReset() );
      const auto identifierPath = IdentifierPath::fromIdentifier( identifier );
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, identifierPath );
  }
#line 4345 "GrammarParser.cpp"
    break;

  case 161: // DirectCallExpression: IdentifierPath
#line 1395 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4353 "GrammarParser.cpp"
    break;

  case 162: // DirectCallExpression: IdentifierPath "(" ")"
#line 1399 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), arguments, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4362 "GrammarParser.cpp"
    break;

  case 163: // DirectCallExpression: IdentifierPath "(" Terms ")"
#line 1404 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = CST::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expressions::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4370 "GrammarParser.cpp"
    break;

  case 164: // DirectCallExpression: IdentifierPath "(" error ")"
#line 1408 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 4378 "GrammarParser.cpp"
    break;

  case 165: // MethodCallExpression: Expression "." Identifier
#line 1416 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 4387 "GrammarParser.cpp"
    break;

  case 166: // MethodCallExpression: Expression "." Identifier "(" ")"
#line 1421 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4398 "GrammarParser.cpp"
    break;

  case 167: // MethodCallExpression: Expression "." Identifier "(" Terms ")"
#line 1428 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = CST::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4408 "GrammarParser.cpp"
    break;

  case 168: // MethodCallExpression: Expression "." Identifier "(" error ")"
#line 1434 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 4416 "GrammarParser.cpp"
    break;

  case 169: // LiteralCallExpression: Expression "." IntegerLiteral
#line 1442 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = CST::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 4424 "GrammarParser.cpp"
    break;

  case 170: // IndirectCallExpression: CallExpression "(" ")"
#line 1450 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = CST::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4435 "GrammarParser.cpp"
    break;

  case 171: // IndirectCallExpression: CallExpression "(" Terms ")"
#line 1457 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = CST::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4445 "GrammarParser.cpp"
    break;

  case 172: // IndirectCallExpression: CallExpression "(" error ")"
#line 1463 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 4453 "GrammarParser.cpp"
    break;

  case 173: // TypeCastingExpression: Expression "as" Type
#line 1471 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = CST::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
  }
#line 4461 "GrammarParser.cpp"
    break;

  case 174: // LetExpression: "let" VariableBindings "in" Term
#line 1479 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = CST::make< LetExpression >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4469 "GrammarParser.cpp"
    break;

  case 175: // ConditionalExpression: "if" Term "then" Term "else" Term
#line 1487 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = CST::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4477 "GrammarParser.cpp"
    break;

  case 176: // ChooseExpression: "choose" VariableSelections "do" Term
#line 1495 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = CST::make< ChooseExpression >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < VariableSelections::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4485 "GrammarParser.cpp"
    break;

  case 177: // UniversalQuantifierExpression: "forall" AttributedVariables "in" Term "holds" Term
#line 1503 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = CST::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4493 "GrammarParser.cpp"
    break;

  case 178: // ExistentialQuantifierExpression: "exists" AttributedVariables "in" Term "with" Term
#line 1511 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = CST::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4501 "GrammarParser.cpp"
    break;

  case 179: // CardinalityExpression: "|" Expression "|"
#line 1519 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = CST::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4509 "GrammarParser.cpp"
    break;

  case 180: // MatchExpression: "match" Term "with" "{" MatchArms "}"
#line 1526 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MatchExpression::Ptr > () = CST::make< MatchExpression >( yylhs.location, yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < MatchArms::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4517 "GrammarParser.cpp"
    break;

  case 181: // MatchArms: MatchArms "," MatchArm
#line 1533 "../../obj/src/GrammarParser.y"
  {
      auto arms = yystack_[2].value.as < MatchArms::Ptr > ();
      yystack_[0].value.as < MatchArm::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      arms->add( yystack_[0].value.as < MatchArm::Ptr > () );
      yylhs.value.as < MatchArms::Ptr > () = arms;
  }
#line 4528 "GrammarParser.cpp"
    break;

  case 182: // MatchArms: MatchArm
#line 1540 "../../obj/src/GrammarParser.y"
  {
      auto arms = CST::make< MatchArms >( yylhs.location );
      arms->add( yystack_[0].value.as < MatchArm::Ptr > () );
      yylhs.value.as < MatchArms::Ptr > () = arms;
  }
#line 4538 "GrammarParser.cpp"
    break;

  case 183: // MatchArm: Term "=>" Term
#line 1549 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MatchArm::Ptr > () = CST::make< MatchArm >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4546 "GrammarParser.cpp"
    break;

  case 184: // Literal: UndefinedLiteral
#line 1562 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 4554 "GrammarParser.cpp"
    break;

  case 185: // Literal: BooleanLiteral
#line 1566 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4562 "GrammarParser.cpp"
    break;

  case 186: // Literal: IntegerLiteral
#line 1570 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4570 "GrammarParser.cpp"
    break;

  case 187: // Literal: RationalLiteral
#line 1574 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4578 "GrammarParser.cpp"
    break;

  case 188: // Literal: DecimalLiteral
#line 1578 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4586 "GrammarParser.cpp"
    break;

  case 189: // Literal: BinaryLiteral
#line 1582 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4594 "GrammarParser.cpp"
    break;

  case 190: // Literal: StringLiteral
#line 1586 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4602 "GrammarParser.cpp"
    break;

  case 191: // Literal: ReferenceLiteral
#line 1590 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 4610 "GrammarParser.cpp"
    break;

  case 192: // Literal: ListLiteral
#line 1598 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 4618 "GrammarParser.cpp"
    break;

  case 193: // Literal: RangeLiteral
#line 1602 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 4626 "GrammarParser.cpp"
    break;

  case 194: // Literal: TupleLiteral
#line 1606 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 4634 "GrammarParser.cpp"
    break;

  case 195: // Literal: RecordLiteral
#line 1610 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 4642 "GrammarParser.cpp"
    break;

  case 196: // UndefinedLiteral: "undef"
#line 1618 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = CST::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4651 "GrammarParser.cpp"
    break;

  case 197: // BooleanLiteral: "true"
#line 1627 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = CST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4661 "GrammarParser.cpp"
    break;

  case 198: // BooleanLiteral: "false"
#line 1633 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = CST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < CST::Token::Ptr > ()->spans() );
  }
#line 4671 "GrammarParser.cpp"
    break;

  case 199: // IntegerLiteral: "integer"
#line 1643 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4679 "GrammarParser.cpp"
    break;

  case 200: // RationalLiteral: "rational"
#line 1651 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4687 "GrammarParser.cpp"
    break;

  case 201: // DecimalLiteral: "decimal"
#line 1659 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4695 "GrammarParser.cpp"
    break;

  case 202: // BinaryLiteral: "binary"
#line 1667 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4703 "GrammarParser.cpp"
    break;

  case 203: // BinaryLiteral: "hexadecimal"
#line 1671 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4711 "GrammarParser.cpp"
    break;

  case 204: // StringLiteral: "string"
#line 1679 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4719 "GrammarParser.cpp"
    break;

  case 205: // ReferenceLiteral: "@" IdentifierPath
#line 1687 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = CST::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4727 "GrammarParser.cpp"
    break;

  case 206: // ListLiteral: "[" "]"
#line 1716 "../../obj/src/GrammarParser.y"
  {
      const auto& expressions = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = CST::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < CST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4738 "GrammarParser.cpp"
    break;

  case 207: // ListLiteral: "[" Terms "]"
#line 1723 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = CST::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4748 "GrammarParser.cpp"
    break;

  case 208: // ListLiteral: "[" error "]"
#line 1729 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 4756 "GrammarParser.cpp"
    break;

  case 209: // RangeLiteral: "[" Term ".." Term "]"
#line 1737 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = CST::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4766 "GrammarParser.cpp"
    break;

  case 210: // TupleLiteral: "(" Terms "," Term ")"
#line 1747 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = CST::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < CST::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4779 "GrammarParser.cpp"
    break;

  case 211: // RecordLiteral: "{" Assignments "}"
#line 1760 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = CST::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < CST::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4789 "GrammarParser.cpp"
    break;

  case 212: // Assignments: Assignments "," Assignment
#line 1774 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4800 "GrammarParser.cpp"
    break;

  case 213: // Assignments: Assignment
#line 1781 "../../obj/src/GrammarParser.y"
  {
      auto assignments = CST::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4810 "GrammarParser.cpp"
    break;

  case 214: // Assignment: Identifier ":" Term
#line 1790 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = CST::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4818 "GrammarParser.cpp"
    break;

  case 215: // MappedExpressions: MappedExpressions "," MappedExpression
#line 1797 "../../obj/src/GrammarParser.y"
  {
      const auto& mappedExpressions = yystack_[2].value.as < MappedExpressions::Ptr > ();
      yystack_[0].value.as < MappedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      mappedExpressions->add( yystack_[0].value.as < MappedExpression::Ptr > () );
      yylhs.value.as < MappedExpressions::Ptr > () = mappedExpressions;
  }
#line 4829 "GrammarParser.cpp"
    break;

  case 216: // MappedExpressions: MappedExpression
#line 1804 "../../obj/src/GrammarParser.y"
  {
      auto mappedExpressions = CST::make< MappedExpressions >( yylhs.location );
      mappedExpressions->add( yystack_[0].value.as < MappedExpression::Ptr > () );
      yylhs.value.as < MappedExpressions::Ptr > () = mappedExpressions;
  }
#line 4839 "GrammarParser.cpp"
    break;

  case 217: // MappedExpression: "->" Term
#line 1813 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = CST::make< Expressions >( yylhs.location );
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4848 "GrammarParser.cpp"
    break;

  case 218: // MappedExpression: "(" Term ")" "->" Term
#line 1818 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = CST::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), arguments, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4858 "GrammarParser.cpp"
    break;

  case 219: // MappedExpression: TupleLiteral "->" Term
#line 1824 "../../obj/src/GrammarParser.y"
  {
      const auto& arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto& leftBracket = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto& rightBracket = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < MappedExpression::Ptr > () = CST::make< MappedExpression >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4869 "GrammarParser.cpp"
    break;

  case 220: // Types: Types "," Type
#line 1840 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4880 "GrammarParser.cpp"
    break;

  case 221: // Types: Type
#line 1847 "../../obj/src/GrammarParser.y"
  {
      auto types = CST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4890 "GrammarParser.cpp"
    break;

  case 222: // Type: BasicType
#line 1856 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4898 "GrammarParser.cpp"
    break;

  case 223: // Type: TupleType
#line 1860 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4906 "GrammarParser.cpp"
    break;

  case 224: // Type: RecordType
#line 1864 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4914 "GrammarParser.cpp"
    break;

  case 225: // Type: TemplateType
#line 1868 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4922 "GrammarParser.cpp"
    break;

  case 226: // Type: RelationType
#line 1872 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4930 "GrammarParser.cpp"
    break;

  case 227: // Type: FixedSizedType
#line 1876 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4938 "GrammarParser.cpp"
    break;

  case 228: // Type: MappingType
#line 1880 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < MappingType::Ptr > ();
  }
#line 4946 "GrammarParser.cpp"
    break;

  case 229: // Type: VaradicType
#line 1884 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::CST::Type::Ptr > () = yystack_[0].value.as < VaradicType::Ptr > ();
  }
#line 4954 "GrammarParser.cpp"
    break;

  case 230: // BasicType: IdentifierPath
#line 1892 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = CST::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4962 "GrammarParser.cpp"
    break;

  case 231: // TupleType: "(" Types "," Type ")"
#line 1900 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = CST::make< TupleType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), subTypes, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4973 "GrammarParser.cpp"
    break;

  case 232: // RecordType: "{" TypedVariables "," TypedVariable "}"
#line 1911 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < CST::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = CST::make< RecordType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4984 "GrammarParser.cpp"
    break;

  case 233: // TemplateType: IdentifierPath "<" Types ">"
#line 1922 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = CST::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 4992 "GrammarParser.cpp"
    break;

  case 234: // RelationType: IdentifierPath "<" MaybeFunctionParameters "->" Type ">"
#line 1930 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = CST::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 5000 "GrammarParser.cpp"
    break;

  case 235: // FixedSizedType: IdentifierPath "'" Term
#line 1938 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = CST::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5008 "GrammarParser.cpp"
    break;

  case 236: // MappingType: "<" FunctionParameters "->" Type ">"
#line 1946 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MappingType::Ptr > () = CST::make< MappingType >( yylhs.location, yystack_[4].value.as < CST::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );      
  }
#line 5016 "GrammarParser.cpp"
    break;

  case 237: // VaradicType: Identifier "..."
#line 1954 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VaradicType::Ptr > () = CST::make< VaradicType >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 5024 "GrammarParser.cpp"
    break;

  case 238: // FunctionParameters: FunctionParameters "*" Type
#line 1966 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 5035 "GrammarParser.cpp"
    break;

  case 239: // FunctionParameters: Type
#line 1973 "../../obj/src/GrammarParser.y"
  {
      auto types = CST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 5045 "GrammarParser.cpp"
    break;

  case 240: // MaybeFunctionParameters: FunctionParameters
#line 1983 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 5053 "GrammarParser.cpp"
    break;

  case 241: // MaybeFunctionParameters: %empty
#line 1987 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = CST::make< Types >( yylhs.location );
  }
#line 5061 "GrammarParser.cpp"
    break;

  case 242: // MethodParameters: MethodParameters "," TypedAttributedVariable
#line 1995 "../../obj/src/GrammarParser.y"
  {
      const auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5072 "GrammarParser.cpp"
    break;

  case 243: // MethodParameters: "this"
#line 2002 "../../obj/src/GrammarParser.y"
  {
      const auto parameters = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto identifier = CST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      identifier->setSpans( m_lexer.fetchSpansAndReset() );
      const auto unresolvedType = CST::make< UnresolvedType >( yylhs.location );
      const auto variable = CST::make< VariableDefinition >( yylhs.location, identifier, Token::unresolved(), unresolvedType );
      parameters->add( variable );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5086 "GrammarParser.cpp"
    break;

  case 244: // Parameters: Parameters "," TypedAttributedVariable
#line 2016 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5097 "GrammarParser.cpp"
    break;

  case 245: // Parameters: TypedAttributedVariable
#line 2023 "../../obj/src/GrammarParser.y"
  {
      auto parameters = CST::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 5107 "GrammarParser.cpp"
    break;

  case 246: // MaybeDefined: "defined" "{" Term "}"
#line 2037 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = CST::make< Defined >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
  }
#line 5115 "GrammarParser.cpp"
    break;

  case 247: // MaybeDefined: %empty
#line 2041 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = CST::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), CST::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 5123 "GrammarParser.cpp"
    break;

  case 248: // MaybeInitially: "=" "{" Expression "}"
#line 2049 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: drop braces and replace this rule with ::= Expression
      const auto& embracedExpression = CST::make< EmbracedExpression >( yystack_[1].location, yystack_[2].value.as < CST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, yystack_[3].value.as < CST::Token::Ptr > (), embracedExpression );
  }
#line 5133 "GrammarParser.cpp"
    break;

  case 249: // MaybeInitially: "=" "{" MappedExpressions "}"
#line 2055 "../../obj/src/GrammarParser.y"
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
#line 5150 "GrammarParser.cpp"
    break;

  case 250: // MaybeInitially: %empty
#line 2068 "../../obj/src/GrammarParser.y"
  {
      const auto& expression = CST::make< CST::AbstractExpression >( yylhs.location, Token::unresolved() );
      yylhs.value.as < Initially::Ptr > () = CST::make< Initially >( yylhs.location, Token::unresolved(), expression );
  }
#line 5159 "GrammarParser.cpp"
    break;

  case 251: // Identifier: "identifier"
#line 2081 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 5167 "GrammarParser.cpp"
    break;

  case 252: // Identifier: "in"
#line 2085 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5176 "GrammarParser.cpp"
    break;

  case 253: // Identifier: "CASM"
#line 2090 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5185 "GrammarParser.cpp"
    break;

  case 254: // Identifier: "self"
#line 2095 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5194 "GrammarParser.cpp"
    break;

  case 255: // Identifier: "enumeration"
#line 2100 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5203 "GrammarParser.cpp"
    break;

  case 256: // Identifier: "structure"
#line 2105 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = CST::make< Identifier >( yylhs.location, yystack_[0].value.as < CST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5212 "GrammarParser.cpp"
    break;

  case 257: // IdentifierPath: IdentifierPath "::" Identifier
#line 2114 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < CST::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 5223 "GrammarParser.cpp"
    break;

  case 258: // IdentifierPath: Identifier
#line 2121 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = CST::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5231 "GrammarParser.cpp"
    break;

  case 259: // Variable: TypedVariable
#line 2133 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5239 "GrammarParser.cpp"
    break;

  case 260: // Variable: Identifier
#line 2137 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = CST::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = CST::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 5248 "GrammarParser.cpp"
    break;

  case 261: // AttributedVariables: AttributedVariables "," AttributedVariable
#line 2146 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5259 "GrammarParser.cpp"
    break;

  case 262: // AttributedVariables: AttributedVariable
#line 2153 "../../obj/src/GrammarParser.y"
  {
      auto variables = CST::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5269 "GrammarParser.cpp"
    break;

  case 263: // TypedVariables: TypedVariables "," TypedVariable
#line 2163 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5280 "GrammarParser.cpp"
    break;

  case 264: // TypedVariables: TypedVariable
#line 2170 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = CST::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5290 "GrammarParser.cpp"
    break;

  case 265: // TypedVariable: Identifier ":" Type
#line 2180 "../../obj/src/GrammarParser.y"
  {
      auto variable = CST::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::CST::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5299 "GrammarParser.cpp"
    break;

  case 266: // AttributedVariable: Attributes Variable
#line 2189 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5309 "GrammarParser.cpp"
    break;

  case 267: // AttributedVariable: Variable
#line 2195 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5317 "GrammarParser.cpp"
    break;

  case 268: // TypedAttributedVariable: Attributes TypedVariable
#line 2203 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5327 "GrammarParser.cpp"
    break;

  case 269: // TypedAttributedVariable: TypedVariable
#line 2209 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5335 "GrammarParser.cpp"
    break;

  case 270: // VariableBindings: VariableBindings "," VariableBinding
#line 2221 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5346 "GrammarParser.cpp"
    break;

  case 271: // VariableBindings: VariableBinding
#line 2228 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = CST::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5356 "GrammarParser.cpp"
    break;

  case 272: // VariableBinding: AttributedVariable "=" Term
#line 2237 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = CST::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5364 "GrammarParser.cpp"
    break;

  case 273: // VariableSelections: VariableSelections "," VariableSelection
#line 2249 "../../obj/src/GrammarParser.y"
  {
      auto variableSelections = yystack_[2].value.as < VariableSelections::Ptr > ();
      yystack_[0].value.as < VariableSelection::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      variableSelections->add( yystack_[0].value.as < VariableSelection::Ptr > () );
      yylhs.value.as < VariableSelections::Ptr > () = variableSelections;
  }
#line 5375 "GrammarParser.cpp"
    break;

  case 274: // VariableSelections: VariableSelection
#line 2256 "../../obj/src/GrammarParser.y"
  {
      auto variableSelections = CST::make< VariableSelections >( yylhs.location );
      variableSelections->add( yystack_[0].value.as < VariableSelection::Ptr > () );
      yylhs.value.as < VariableSelections::Ptr > () = variableSelections;
  }
#line 5385 "GrammarParser.cpp"
    break;

  case 275: // VariableSelection: AttributedVariable "in" Term "with" Term
#line 2265 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableSelection::Ptr > () = CST::make< VariableSelection >( yylhs.location, yystack_[4].value.as < VariableDefinition::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5393 "GrammarParser.cpp"
    break;

  case 276: // VariableSelection: AttributedVariable "in" Term
#line 2269 "../../obj/src/GrammarParser.y"
  {
      const auto withToken = Token::unresolved();
      const auto alwaysTrue = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      const auto condition = CST::make< ValueLiteral >( yylhs.location, alwaysTrue );

      yylhs.value.as < VariableSelection::Ptr > () = CST::make< VariableSelection >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < CST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), withToken, condition );
  }
#line 5405 "GrammarParser.cpp"
    break;

  case 277: // LocalFunctionDefinitions: LocalFunctionDefinitions "," AttributedLocalFunctionDefinition
#line 2285 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[2].value.as < FunctionDefinitions::Ptr > ();
      yystack_[0].value.as < FunctionDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < CST::Token::Ptr > () );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5416 "GrammarParser.cpp"
    break;

  case 278: // LocalFunctionDefinitions: AttributedLocalFunctionDefinition
#line 2292 "../../obj/src/GrammarParser.y"
  {
      auto definitions = CST::make< FunctionDefinitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5426 "GrammarParser.cpp"
    break;

  case 279: // AttributedLocalFunctionDefinition: Attributes LocalFunctionDefinition
#line 2301 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 5436 "GrammarParser.cpp"
    break;

  case 280: // AttributedLocalFunctionDefinition: LocalFunctionDefinition
#line 2307 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 5444 "GrammarParser.cpp"
    break;

  case 281: // AttributedLocalFunctionDefinition: error
#line 2311 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = nullptr;
  }
#line 5452 "GrammarParser.cpp"
    break;

  case 282: // LocalFunctionDefinition: Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 2318 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = CST::make< FunctionDefinition >( yylhs.location, Token::unresolved(), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < CST::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < CST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::CST::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > ()->setClassification( FunctionDefinition::Classification::LOCAL );
  }
#line 5461 "GrammarParser.cpp"
    break;

  case 283: // Attributes: Attributes Attribute
#line 2331 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5471 "GrammarParser.cpp"
    break;

  case 284: // Attributes: Attribute
#line 2337 "../../obj/src/GrammarParser.y"
  {
      auto attributes = CST::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5481 "GrammarParser.cpp"
    break;

  case 285: // Attribute: "[" BasicAttribute "]"
#line 2346 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5492 "GrammarParser.cpp"
    break;

  case 286: // Attribute: "[" SymbolAttribute "]"
#line 2353 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < SymbolAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5503 "GrammarParser.cpp"
    break;

  case 287: // Attribute: "[" ExpressionAttribute "]"
#line 2360 "../../obj/src/GrammarParser.y"
  {
      const auto& attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      attribute->setLeftBrace( yystack_[2].value.as < CST::Token::Ptr > () );
      attribute->setRightBrace( yystack_[0].value.as < CST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5514 "GrammarParser.cpp"
    break;

  case 288: // Attribute: "[" error "]"
#line 2367 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 5522 "GrammarParser.cpp"
    break;

  case 289: // BasicAttribute: Identifier
#line 2374 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = CST::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5530 "GrammarParser.cpp"
    break;

  case 290: // SymbolAttribute: Identifier TypedVariable
#line 2381 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SymbolAttribute::Ptr > () = CST::make< SymbolAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < VariableDefinition::Ptr > () );
  }
#line 5538 "GrammarParser.cpp"
    break;

  case 291: // ExpressionAttribute: Identifier Term
#line 2388 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = CST::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5546 "GrammarParser.cpp"
    break;


#line 5550 "GrammarParser.cpp"

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
      21,  -425,    88,    37,   778,    26,  -425,     5,  -425,  -425,
    -425,  -425,  -425,  -425,  2635,    79,   113,   145,  -425,  -425,
     149,   252,   252,   252,   252,   252,   252,   252,   126,   126,
     126,   252,   252,   590,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,
     798,  -425,  -425,  -425,  -425,   216,   216,   216,  2635,   216,
    2635,  -425,  -425,  -425,  2635,  1255,  1255,  2051,  1783,   252,
    1255,   252,  -425,  -425,  -425,  -425,  -425,  -425,  3279,    -1,
    -425,    53,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,    51,   111,  -425,
    -425,  -425,  -425,    -9,  -425,   122,    50,   148,    55,   156,
     157,   173,   -12,   198,   126,   252,   126,   201,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,   127,   242,    35,  -425,
    -425,   -28,   202,  -425,  -425,    51,  -425,  -425,   205,    73,
    -425,   216,    80,  -425,   247,    72,  -425,  2735,    92,  2912,
    -425,  -425,  -425,   219,   235,  3048,   244,  -425,   109,  3011,
     239,  -425,   260,   -31,   122,  2635,  2635,  2635,  2635,  2635,
    2635,  2635,  2635,  2635,  2635,  2635,  2635,  2635,  2635,  2635,
    2635,  2635,   126,   160,  1850,   126,  1917,   252,  2635,  2635,
     245,   248,  -425,    59,   126,   263,  2501,    70,   126,   126,
     251,  2635,   252,   295,   292,  -425,    51,   293,  -425,  -425,
     203,   301,  -425,   126,  2635,   126,   302,   126,   126,  2635,
    2635,   216,  -425,  2635,   216,  2635,  2635,   216,  2635,  2635,
     304,  -425,  2635,  -425,  -425,  -425,  2635,  2635,  -425,   252,
    2635,  -425,   215,  3345,   844,  1009,   296,   296,   258,   144,
     144,   297,   297,   297,  -425,  1009,   258,   144,   144,  -425,
    -425,   315,   316,  -425,   -19,  3279,  -425,   318,  -425,   132,
    -425,  3081,  3279,  2635,  -425,    -9,   319,  -425,   250,   283,
    -425,  -425,   216,   322,    77,  1373,  1465,  -425,   216,   142,
     216,   216,  2501,  2635,  2635,  2635,  1557,  1649,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,   299,   -42,   303,   306,   321,   284,   289,   324,
    -425,  -425,  3279,  -425,    44,   126,   252,   126,   126,    10,
      67,   207,   314,   310,  -425,   332,    38,   323,  3279,  3279,
    -425,  2879,  -425,  2945,  3279,  -425,  2807,  2978,  2635,  3114,
    3279,  3147,  -425,  3279,  1984,  -425,  -425,  -425,  -425,   326,
    3279,  -425,   327,   329,   216,   330,   216,  -425,  2635,  -425,
    -425,   257,  -425,   216,   367,  2141,  -425,   366,  2231,    98,
    -425,   335,   114,  -425,  -425,   216,   116,    89,  -425,  2768,
    2844,  2660,   333,  2321,   260,   309,  2411,  2635,  2635,    52,
     158,   190,  2501,  -425,   100,  -425,    44,   342,   345,  -425,
     338,   252,   252,  -425,  -425,  -425,    11,  -425,    10,   126,
    -425,   126,   348,  -425,  -425,    39,  -425,  -425,    38,   126,
    2635,  2635,  2635,  2635,  3312,   287,  -425,  -425,  -425,   352,
    -425,   290,  2635,   126,   126,  -425,   126,  -425,  3279,  -425,
      77,  -425,  -425,  -425,  -425,  -425,  -425,  2501,   126,  2501,
     142,  -425,  2635,  2501,  2501,   351,  2501,  -425,  -425,  -425,
    -425,  3279,  3279,  2501,   126,  2501,   126,  2501,   126,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,   168,   184,  -425,  -425,
    -425,  -425,  -425,  -425,   344,    38,  -425,  -425,  -425,   394,
    3279,  3279,  3279,  3279,  2635,  -425,  2635,  -425,  -425,  3279,
     360,   363,   368,  -425,  -425,   346,  -425,  -425,  1127,  -425,
     389,  1716,  -425,  -425,   370,  -425,   375,  -425,   380,   126,
     126,  -425,    54,   376,   384,   906,  -425,  2635,  2635,  2635,
     126,  2501,  2635,  2501,   392,   379,   388,  2568,  -425,  3180,
    2501,  2501,  2501,   381,   382,  -425,  2635,   399,  -425,  3279,
    3279,  3279,   394,  -425,  2702,  -425,  -425,  2501,  2501,  -425,
    -425,  2501,  -425,  -425,  -425,   126,   126,  3213,   657,   384,
    2501,  -425,  -425,  -425,  -425,  -425,  -425,  2051,   -25,   245,
     291,  -425,  -425,  3246,  -425,  -425,   326
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
       0,     0,     0,    43,   102,     0,   103,   277,     0,   106,
      93,     0,   119,    37,     0,    35,     0,    33,     0,   241,
     241,   234,     0,     0,   250,   154,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    98,     0,
       0,     0,     0,     0,     0,    66,     0,     0,    39,    30,
      29,    28,   247,   104,     0,    94,    96,     0,     0,    95,
      97,     0,    38,    36,    34,     0,     0,     0,     0,   250,
       0,    99,   100,   101,    75,    76,   246,     0,     0,   194,
       0,   282,   105,   121,   248,   249,   132
  };

  const short
  Parser::yypgoto_[] =
  {
    -425,  -425,  -425,  -425,   427,   411,  -425,  -425,     0,     6,
    -321,     2,  -425,  -425,  -425,  -425,  -425,  -425,  -425,    49,
    -425,    41,  -425,  -425,   -41,  -424,    31,  -425,  -425,    42,
     -35,   805,  -425,  -425,  -425,  -425,   -86,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,   -63,   328,   523,
    -425,   559,   687,   745,  -425,  -425,  -425,  -425,  -425,  -425,
    -425,  -425,  -425,  -425,  -425,   -44,  -425,  -425,  -425,   280,
    -425,  -425,  -425,  -425,  -425,  -425,  -425,  -112,  -425,  -425,
     225,  -113,   192,   255,   208,  -425,  -425,  -425,  -425,   448,
    -425,  -425,  -425,   355,  -226,   276,   281,   -82,  -102,    -2,
     418,   340,   -51,  -425,   -11,   -50,   -85,   195,   264,   193,
     259,  -425,    28,   102,   146,    27,  -425,  -425,  -425
  };

  const short
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    33,    34,    35,    36,    37,   433,   434,
      40,   380,   381,    41,    42,    43,    44,    45,   414,   415,
      46,   425,   426,    47,   435,   436,   437,    48,    49,   427,
     385,   386,   309,   310,   311,   557,   558,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   164,   275,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,   445,   446,    94,    95,    96,    97,
      98,    99,   100,   101,   102,   103,   104,   105,   106,   170,
     171,   201,   202,   214,   219,   128,   129,   130,   131,   132,
     133,   134,   135,   342,   343,   288,   289,   544,   568,   114,
     108,   146,   152,   217,   147,   148,   291,   149,   150,   155,
     156,   392,   393,   394,   151,     6,    15,    16,    17
  };

  const short
  Parser::yytable_[] =
  {
      14,   200,   347,   109,    38,   168,   153,   154,   158,   153,
      39,   507,   107,   413,   194,   421,   421,   422,   422,   116,
     117,   118,   119,   121,     1,   123,   136,   136,   136,    51,
     142,   212,    52,    38,   251,   197,   604,    18,   366,    39,
     227,  -134,   192,    21,    21,    23,    23,   198,   246,   225,
      38,   197,   193,   145,   145,   145,    39,   145,   193,    21,
     286,    23,     8,    32,    53,     9,   199,   172,     2,     2,
      10,   326,   498,     8,    11,   287,     9,    52,   379,     2,
       8,    10,   193,     9,     2,    11,   287,    12,    10,     7,
     226,     8,    11,   413,     9,   492,     2,     2,    12,    10,
     506,   230,     2,    11,   236,    12,   203,   483,   233,   194,
     206,   207,     2,   195,   218,   565,    12,     2,   507,    32,
     239,   473,   136,   216,   136,   204,   467,   484,     2,     8,
     208,   274,     9,   279,   429,     2,   430,    10,   110,   237,
     231,    11,   469,   390,   472,     8,     5,   234,     9,   145,
      50,    13,     8,    10,    12,     9,   237,    11,     2,   234,
      10,   490,    13,     8,    11,   231,     9,   196,   245,    13,
      12,    10,   111,   200,   197,    11,   246,    12,    52,    50,
      13,   470,   124,   234,   352,   197,   125,   154,    12,   368,
     136,   271,   290,   136,   126,   280,   290,   179,   180,   246,
       2,   216,   136,   205,   112,   216,   136,   136,   280,   113,
     333,   209,   222,   485,   184,   185,   186,   187,    13,     8,
     210,   136,     9,   136,   203,   136,   136,    10,   211,   145,
     539,    11,   145,   486,    13,   145,   127,   138,   139,   206,
     207,    13,   525,   204,    12,   487,   540,   172,    74,   396,
     153,   154,    13,   213,     8,     8,   221,     9,     9,   208,
     229,   388,    10,    10,   228,   488,    11,    11,   179,   180,
     181,   403,   406,   337,     2,   235,   241,  -239,   338,    12,
      12,   377,  -239,   182,   183,   184,   185,   186,   187,   455,
     216,   457,   382,   189,   190,   191,   145,   391,   145,   145,
     248,   451,   242,   244,   404,   197,   249,   373,    13,   284,
     223,   179,   180,   563,   564,   285,   224,   374,   459,    52,
     283,   331,   250,   294,   460,   418,   182,   183,   184,   185,
     186,   187,   215,   136,   216,   136,   136,   190,   191,   423,
     375,   410,    78,    13,    13,   424,   411,   518,   515,   292,
     376,   374,   605,   292,   516,   334,   376,   246,   285,   335,
     336,   339,   346,   290,   358,   290,   184,   185,   186,   187,
     187,   364,   216,   365,   216,   367,   372,   378,   409,   412,
     407,   461,   193,   408,   337,   431,   157,   432,   159,   462,
     465,   479,   160,   391,   477,   165,   169,   468,   439,   493,
     269,   452,   453,   276,   454,   456,   494,   495,   505,   517,
      52,   531,   293,   541,   543,   547,   329,   330,   548,   496,
     497,   550,    52,   549,   553,   560,   423,   136,   500,   136,
     561,   341,   424,   345,   501,   562,   566,   136,   115,   567,
     383,   577,   120,    52,   122,   395,   137,   137,   137,   141,
     578,   136,   136,   576,   136,    52,   585,   586,   382,   588,
     143,   144,   523,   491,   542,    52,   136,   499,   391,   508,
     502,   580,   546,   270,   362,   600,   599,   371,   340,   140,
     416,   220,   136,   327,   136,   428,   136,   601,   328,   174,
     589,   232,   438,   389,   397,   350,   355,   471,   527,     0,
       0,     0,     0,   252,   253,   254,   255,   256,   257,   258,
     259,   260,   261,   262,   263,   264,   265,   266,   267,   268,
     292,     0,   292,     0,     0,     0,   281,   282,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   136,   136,   332,
       0,     0,   137,   417,   137,   419,   420,     0,   136,     0,
       0,     0,   344,     0,     0,     0,     0,   348,   349,     0,
     416,   351,     0,   353,   354,     0,   356,   357,     0,     0,
     359,     0,   428,     0,   360,   361,     0,     0,   363,     0,
       0,   438,     0,   136,   136,     0,     0,     0,   161,   162,
      -2,    19,     0,   173,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,     0,     0,   383,    30,    31,    32,
     137,   370,     0,   137,     0,     0,   395,     0,     0,     0,
       0,     0,   137,     0,     0,     0,   137,   137,     0,     0,
       0,   399,   400,   401,     0,     0,     0,   503,     0,   504,
       0,   137,     0,   137,     0,   137,   137,   509,     2,     0,
       0,   438,     0,     0,     0,     0,     0,     0,     0,     0,
       8,   520,   521,     9,   522,     0,     0,     0,    10,     0,
       0,     0,    11,    54,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    12,   444,     0,   438,     0,
       0,     0,   534,     0,   536,     0,   538,     0,     0,     0,
       0,     0,    61,    62,    63,     0,   458,     0,     0,     0,
      65,    66,     0,   597,     0,    68,     0,    69,     0,     0,
       0,     0,     0,    71,     0,     0,     0,     0,     0,   322,
       0,     0,   199,     0,     0,   481,   482,     0,     0,     0,
       0,     0,     0,    72,    73,    74,    75,    76,    77,    13,
       0,     0,     0,   137,     0,   137,   137,     0,   572,     0,
       0,     0,     0,     0,     0,   323,     0,     0,   510,   511,
     512,   513,     0,     0,     0,     0,     0,     0,     0,    19,
     519,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,     0,   594,   595,    30,    31,    32,     0,     0,
     528,     0,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,     0,     0,     0,    30,    31,    32,   322,   322,
       0,     0,     0,     0,     0,   322,     0,     0,     0,   322,
     322,     0,     0,     0,     0,     0,     2,     0,     0,     0,
       0,     0,   545,     0,   444,     0,     0,   137,     0,   137,
       0,     0,     0,     0,   323,   323,     2,   137,     0,   559,
       0,   323,     0,     0,     0,   323,   323,     0,     0,     0,
       0,   137,   137,     0,   137,   569,   570,   571,     0,     0,
     574,     0,     0,     0,     0,   559,   137,     0,     0,     0,
       0,     0,   175,   324,   587,     0,     0,   179,   180,   181,
       0,     0,   137,     0,   137,     0,   137,     0,   322,     0,
       0,   322,   182,   183,   184,   185,   186,   187,     0,     0,
       0,     0,   189,   190,   191,   603,   322,     0,     0,   322,
       0,     0,     0,     0,     0,   322,     0,     0,     0,     0,
       0,     0,     0,     0,   323,     0,     0,   323,     0,     0,
       0,   325,     0,     0,   175,   176,   177,   137,   137,   179,
     180,   181,   323,     0,     0,   323,     0,  -183,   137,     0,
       0,   323,     0,  -183,   182,   183,   184,   185,   186,   187,
       0,     0,   324,   324,   189,   190,   191,     0,     0,   324,
     322,     0,   322,   324,   324,     0,   322,   322,     0,   322,
       0,     0,     0,   137,   137,     0,   322,     0,   322,     0,
     322,   308,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   323,     0,   323,     0,
       0,     0,   323,   323,     0,   323,     0,     0,     0,     0,
     325,   325,   323,     0,   323,     0,   323,   325,     0,     0,
       0,   325,   325,     0,     0,     0,     0,   175,   176,   177,
       0,     0,   179,   180,   181,     0,     0,     0,     0,     0,
       0,     0,   324,     0,   322,   324,   322,   182,   183,   184,
     185,   186,   187,   322,   322,   322,     0,   189,   190,   191,
     324,     0,     0,   324,     0,     0,     0,     0,     0,   324,
     322,   322,     0,     0,   322,     0,     0,   398,     0,     0,
     323,   598,   323,   322,     0,     0,     0,     0,     0,   323,
     323,   323,     0,     0,     0,     0,     0,     0,     0,     0,
     325,     0,     0,   325,     0,     0,   323,   323,     0,     0,
     323,     0,     0,     0,     0,     0,     0,     0,   325,   323,
       0,   325,     0,     0,   324,     0,   324,   325,     0,   551,
     324,   324,     0,   324,     0,     0,     0,     0,     0,   552,
     324,     0,   324,     0,   324,   175,   176,   177,   178,     0,
     179,   180,   181,     0,     0,     0,     0,     0,     0,     0,
     464,     0,     0,   464,     0,   182,   183,   184,   185,   186,
     187,     0,     0,   188,     0,   189,   190,   191,   464,     0,
       0,   464,   325,     0,   325,     0,     0,   489,   325,   325,
       0,   325,     0,     0,     0,     0,     0,     0,   325,     0,
     325,     0,   325,     0,     0,     0,     0,     0,   324,     0,
     324,     0,     0,     0,     0,     0,     0,   324,   324,   324,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
       0,     9,     0,     0,   324,   324,    10,     0,   324,     0,
      11,    54,   524,     0,   526,     0,     0,   324,   529,   530,
       0,   532,     0,    12,     0,     0,     0,     0,   533,     0,
     535,     0,   537,     0,     0,     0,   325,     0,   325,     0,
      61,    62,    63,     0,     0,   325,   325,   325,    65,    66,
       0,    67,     0,    68,     0,    69,     0,     0,     0,     0,
       0,    71,   325,   325,     0,     0,   325,     0,     0,     0,
       0,     0,     0,     0,     0,   325,     0,     0,     0,     0,
       0,    72,    73,    74,    75,    76,    77,    13,     0,     0,
       0,     0,     0,     0,     0,     0,   573,     0,   575,     0,
       0,     0,     0,     0,     0,   582,   583,   584,     0,     0,
       0,     0,     0,     0,   384,     0,     8,     0,     0,     9,
       0,     0,   591,   592,    10,     0,   593,     0,    11,    54,
       0,     0,     0,     0,   295,   602,   296,     0,   297,   298,
     299,    12,   300,   301,   302,     0,   303,     0,     0,   304,
       0,     0,     0,     0,     0,     0,     0,   305,    61,    62,
      63,     0,     0,     0,     0,     0,    65,    66,     0,    67,
       0,    68,     0,   306,     0,     0,     0,     0,     0,    71,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   307,     0,     0,     0,     0,    72,
      73,    74,    75,    76,    77,    13,   387,     0,     8,     0,
       0,     9,     0,     0,     0,     0,    10,     0,     0,     0,
      11,    54,     0,     0,     0,     0,   295,     0,   296,     0,
     297,   298,   299,    12,   300,   301,   302,     0,   303,     0,
       0,   304,     0,     0,     0,     0,     0,     0,     0,   305,
      61,    62,    63,     0,     0,     0,     0,     0,    65,    66,
       0,    67,     0,    68,     0,   306,     0,     0,     0,     0,
       0,    71,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   307,     0,     0,     0,
       0,    72,    73,    74,    75,    76,    77,    13,   402,     0,
       8,     0,     0,     9,     0,     0,     0,     0,    10,     0,
       0,     0,    11,    54,     0,     0,     0,     0,   295,     0,
     296,     0,   297,   298,   299,    12,   300,   301,   302,     0,
     303,     0,     0,   304,     0,     0,     0,     0,     0,     0,
       0,   305,    61,    62,    63,     0,     0,     0,     0,     0,
      65,    66,     0,    67,     0,    68,     0,   306,     0,     0,
       0,     0,     0,    71,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   307,     0,
       0,     0,     0,    72,    73,    74,    75,    76,    77,    13,
     405,     0,     8,     0,     0,     9,     0,     0,     0,     0,
      10,     0,     0,     0,    11,    54,     0,     0,     0,     0,
     295,     0,   296,     0,   297,   298,   299,    12,   300,   301,
     302,     0,   303,     0,     0,   304,     0,     0,     0,     0,
       0,     0,     0,   305,    61,    62,    63,     0,     0,     0,
       0,     0,    65,    66,     0,    67,     0,    68,     0,   306,
       0,     0,     0,     0,     0,    71,     0,   554,     0,     8,
       0,     0,     9,     0,     0,     0,     0,    10,     0,     0,
     307,    11,    54,     0,     0,    72,    73,    74,    75,    76,
      77,    13,    55,     0,    12,    56,    57,     0,     0,    58,
       0,     0,     0,     0,   555,     0,    59,    60,     0,     0,
       0,    61,    62,    63,     0,     0,     0,     0,    64,    65,
      66,     0,    67,     0,    68,     0,    69,     0,     0,     0,
     556,    70,    71,     0,   166,     0,     8,     0,     0,     9,
       0,     0,     0,     0,    10,     0,     0,     0,    11,    54,
       0,     0,    72,    73,    74,    75,    76,    77,    13,    55,
       0,    12,    56,    57,     0,     0,    58,     0,     0,     0,
       0,     0,     0,    59,    60,     0,     0,     0,    61,    62,
      63,     0,     0,     0,     0,    64,    65,    66,     0,    67,
       0,    68,   167,    69,     0,     0,     0,     0,    70,    71,
       0,   272,     0,     8,     0,     0,     9,     0,     0,     0,
       0,    10,     0,     0,     0,    11,    54,     0,     0,    72,
      73,    74,    75,    76,    77,    13,    55,     0,    12,    56,
      57,     0,     0,    58,     0,     0,     0,     0,     0,     0,
      59,    60,     0,     0,     0,    61,    62,    63,     0,     0,
       0,     0,    64,    65,    66,     0,    67,   273,    68,     0,
      69,     0,     0,     0,     0,    70,    71,     0,   277,     0,
       8,     0,     0,     9,     0,     0,     0,     0,    10,     0,
       0,     0,    11,    54,     0,     0,    72,    73,    74,    75,
      76,    77,    13,    55,     0,    12,    56,    57,     0,     0,
      58,     0,     0,     0,     0,     0,     0,    59,    60,     0,
       0,     0,    61,    62,    63,     0,     0,     0,     0,    64,
      65,    66,     0,    67,   278,    68,     0,    69,     0,     0,
       0,     0,    70,    71,     0,   449,     0,     8,     0,     0,
       9,     0,     0,     0,     0,    10,     0,     0,     0,    11,
      54,     0,     0,    72,    73,    74,    75,    76,    77,    13,
      55,     0,    12,    56,    57,     0,     0,    58,     0,     0,
       0,     0,     0,     0,    59,    60,     0,     0,     0,    61,
      62,    63,     0,     0,     0,     0,    64,    65,    66,     0,
      67,   450,    68,     0,    69,     0,     0,     0,     0,    70,
      71,     0,   163,     0,     8,     0,     0,     9,     0,     0,
       0,     0,    10,     0,     0,     0,    11,    54,     0,     0,
      72,    73,    74,    75,    76,    77,    13,    55,     0,    12,
      56,    57,     0,     0,    58,     0,     0,     0,     0,     0,
       0,    59,    60,     0,     0,     0,    61,    62,    63,     0,
       0,     0,     0,    64,    65,    66,     0,    67,     0,    68,
       0,    69,     0,     0,     0,     0,    70,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    72,    73,    74,
      75,    76,    77,    13,     8,     0,     0,     9,     0,     0,
       0,     0,    10,     0,     0,     0,    11,    54,     0,     0,
       0,     0,   295,   463,   296,     0,   297,   298,   299,    12,
     300,   301,   302,     0,   303,     0,     0,   304,     0,     0,
       0,     0,     0,     0,     0,   305,    61,    62,    63,     0,
       0,     0,     0,     0,    65,    66,     0,    67,     0,    68,
       0,   306,     0,     0,     0,     0,     0,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   307,     0,     0,     0,     0,    72,    73,    74,
      75,    76,    77,    13,     8,     0,     0,     9,     0,     0,
       0,     0,    10,     0,     0,     0,    11,    54,     0,     0,
       0,     0,   295,     0,   296,   466,   297,   298,   299,    12,
     300,   301,   302,     0,   303,     0,     0,   304,     0,     0,
       0,     0,     0,     0,     0,   305,    61,    62,    63,     0,
       0,     0,     0,     0,    65,    66,     0,    67,     0,    68,
       0,   306,     0,     0,     0,     0,     0,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   307,     0,     0,     0,     0,    72,    73,    74,
      75,    76,    77,    13,     8,     0,     0,     9,     0,     0,
       0,     0,    10,     0,     0,     0,    11,    54,     0,     0,
       0,     0,   295,     0,   296,     0,   297,   298,   299,    12,
     300,   301,   302,     0,   303,     0,     0,   304,     0,     0,
       0,     0,     0,     0,     0,   305,    61,    62,    63,     0,
       0,     0,     0,     0,    65,    66,     0,    67,     0,    68,
       0,   306,   478,     0,     0,     0,     0,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   307,     0,     0,     0,     0,    72,    73,    74,
      75,    76,    77,    13,     8,     0,     0,     9,     0,     0,
       0,     0,    10,     0,     0,     0,    11,    54,     0,     0,
       0,     0,   295,     0,   296,     0,   297,   298,   299,    12,
     300,   301,   302,     0,   303,     0,     0,   304,     0,     0,
       0,     0,     0,     0,     0,   305,    61,    62,    63,     0,
       0,     0,     0,     0,    65,    66,     0,    67,     0,    68,
       0,   306,     0,     0,     0,     0,     0,    71,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   307,   480,     0,     0,     0,    72,    73,    74,
      75,    76,    77,    13,     8,     0,     0,     9,     0,     0,
       0,     0,    10,     0,     0,     0,    11,    54,     0,     0,
       0,     0,   295,     0,   296,     0,   297,   298,   299,    12,
     300,   301,   302,     0,   303,     0,     0,   304,     0,     0,
       0,     0,     0,     0,     0,   305,    61,    62,    63,     0,
       0,     0,     0,     0,    65,    66,     0,    67,     0,    68,
       0,   306,     0,     0,     0,     0,     0,    71,     0,     0,
       0,     8,     0,     0,     9,     0,     0,     0,     0,    10,
       0,     0,   307,    11,    54,     0,     0,    72,    73,    74,
      75,    76,    77,    13,    55,     0,    12,    56,    57,     0,
       0,    58,     0,     0,     0,     0,   555,     0,    59,    60,
       0,     0,     0,    61,    62,    63,     0,     0,     0,     0,
      64,    65,    66,     0,    67,     0,    68,     0,    69,   579,
       0,     0,   556,    70,    71,     0,     0,     0,     8,     0,
       0,     9,     0,     0,     0,     0,    10,     0,     0,     0,
      11,    54,     0,     0,    72,    73,    74,    75,    76,    77,
      13,    55,     0,    12,    56,    57,     0,     0,    58,     0,
       0,     0,     0,     0,     0,    59,    60,     0,     0,     0,
      61,    62,    63,     0,     0,     0,     0,    64,    65,    66,
       0,    67,   476,    68,     0,    69,     0,     0,     0,     0,
      70,    71,     0,     0,     0,     0,     0,     0,   175,   176,
     177,   178,     0,   179,   180,   181,     0,     0,     0,     0,
       0,    72,    73,    74,    75,    76,    77,    13,   182,   183,
     184,   185,   186,   187,   590,     0,   188,     0,   189,   190,
     191,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     175,   176,   177,   178,     0,   179,   180,   181,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   238,
     182,   183,   184,   185,   186,   187,     0,     0,   188,     0,
     189,   190,   191,   175,   176,   177,   178,     0,   179,   180,
     181,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   474,   182,   183,   184,   185,   186,   187,     0,
       0,   188,     0,   189,   190,   191,   175,   176,   177,   178,
       0,   179,   180,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   182,   183,   184,   185,
     186,   187,   442,     0,   188,     0,   189,   190,   191,     0,
       0,     0,     0,     0,     0,   175,   176,   177,   178,     0,
     179,   180,   181,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,   184,   185,   186,
     187,   475,     0,   188,     0,   189,   190,   191,     0,     0,
       0,     0,   175,   176,   177,   178,     0,   179,   180,   181,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   182,   183,   184,   185,   186,   187,   440,     0,
     188,     0,   189,   190,   191,     0,     0,   175,   176,   177,
     178,     0,   179,   180,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   182,   183,   184,
     185,   186,   187,     0,   240,   188,     0,   189,   190,   191,
     175,   176,   177,   178,     0,   179,   180,   181,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     182,   183,   184,   185,   186,   187,     0,   441,   188,     0,
     189,   190,   191,   175,   176,   177,   178,     0,   179,   180,
     181,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   182,   183,   184,   185,   186,   187,     0,
     443,   188,     0,   189,   190,   191,   175,   176,   177,   178,
       0,   179,   180,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   182,   183,   184,   185,
     186,   187,     0,     0,   188,     0,   189,   190,   191,   175,
     176,   177,   178,     0,   179,   180,   181,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   182,
     183,   184,   185,   186,   187,     0,     0,   188,     0,   189,
     190,   191,     0,     0,     0,   247,   175,   176,   177,   178,
       0,   179,   180,   181,     0,   243,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   182,   183,   184,   185,
     186,   187,     0,     0,   188,     0,   189,   190,   191,   175,
     176,   177,   178,     0,   179,   180,   181,     0,   369,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   182,
     183,   184,   185,   186,   187,     0,     0,   188,     0,   189,
     190,   191,   175,   176,   177,   178,     0,   179,   180,   181,
       0,   447,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   182,   183,   184,   185,   186,   187,     0,     0,
     188,     0,   189,   190,   191,   175,   176,   177,   178,     0,
     179,   180,   181,     0,     0,     0,   448,     0,     0,     0,
       0,     0,     0,     0,     0,   182,   183,   184,   185,   186,
     187,     0,     0,   188,     0,   189,   190,   191,   175,   176,
     177,   178,     0,   179,   180,   181,     0,     0,     0,     0,
       0,     0,   581,     0,     0,     0,     0,     0,   182,   183,
     184,   185,   186,   187,     0,     0,   188,     0,   189,   190,
     191,   175,   176,   177,   178,     0,   179,   180,   181,     0,
       0,     0,     0,     0,   596,     0,     0,     0,     0,     0,
       0,   182,   183,   184,   185,   186,   187,     0,     0,   188,
       0,   189,   190,   191,   175,   176,   177,   178,     0,   179,
     180,   181,     0,   606,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   182,   183,   184,   185,   186,   187,
       0,     0,   188,     0,   189,   190,   191,   175,   176,   177,
     178,     0,   179,   180,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   182,   183,   184,
     185,   186,   187,     0,     0,   188,     0,   189,   190,   191,
     175,   176,   177,   178,     0,   179,   180,   181,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     182,   183,   184,   185,   186,   187,     0,     0,   514,     0,
     189,   190,   191,   175,     0,   177,     0,     0,   179,   180,
     181,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   182,   183,   184,   185,   186,   187,     0,
       0,     0,     0,   189,   190,   191
  };

  const short
  Parser::yycheck_[] =
  {
       2,   113,   228,    14,     4,    68,    56,    57,    59,    59,
       4,   435,    14,   334,    56,     5,     5,     7,     7,    21,
      22,    23,    24,    25,     3,    27,    28,    29,    30,     3,
      32,    43,     5,    33,    65,    63,    61,     0,    57,    33,
      68,    83,    43,     5,     5,     7,     7,    56,    67,    14,
      50,    63,    83,    55,    56,    57,    50,    59,    83,     5,
       1,     7,     3,    19,    59,     6,    75,    69,    58,    58,
      11,     1,    61,     3,    15,    16,     6,    50,     1,    58,
       3,    11,    83,     6,    58,    15,    16,    28,    11,     1,
      55,     3,    15,   414,     6,   416,    58,    58,    28,    11,
      61,    28,    58,    15,    32,    28,    56,    55,    28,    56,
      55,    56,    58,    62,   125,    61,    28,    58,   542,    19,
      28,    32,   124,   125,   126,    75,    28,    75,    58,     3,
      75,   194,     6,   196,    67,    58,    69,    11,    59,    67,
      67,    15,    28,     1,    28,     3,     0,    67,     6,   151,
       4,    92,     3,    11,    28,     6,    67,    15,    58,    67,
      11,    61,    92,     3,    15,    67,     6,    56,    59,    92,
      28,    11,    59,   285,    63,    15,    67,    28,   151,    33,
      92,    67,    56,    67,   234,    63,    60,   237,    28,    57,
     192,   193,   203,   195,    68,   197,   207,    53,    54,    67,
      58,   203,   204,    55,    59,   207,   208,   209,   210,    60,
     212,    55,    85,    55,    70,    71,    72,    73,    92,     3,
      63,   223,     6,   225,    56,   227,   228,    11,    55,   231,
      62,    15,   234,    75,    92,   237,    28,    29,    30,    55,
      56,    92,   468,    75,    28,    55,    62,   249,    88,   300,
     300,   301,    92,    55,     3,     3,    55,     6,     6,    75,
      55,   296,    11,    11,    62,    75,    15,    15,    53,    54,
      55,   306,   307,    70,    58,    28,    57,    70,    75,    28,
      28,   292,    75,    68,    69,    70,    71,    72,    73,   374,
     292,   376,   294,    78,    79,    80,   298,   299,   300,   301,
      61,   364,    67,    59,   306,    63,    67,    57,    92,    61,
      68,    53,    54,   539,   540,    67,    74,    67,    61,   292,
      75,    70,    62,    60,    67,   336,    68,    69,    70,    71,
      72,    73,   124,   335,   336,   337,   338,    79,    80,   339,
      57,    57,    14,    92,    92,   339,    57,    57,    61,   203,
      67,    67,    61,   207,    67,    60,    67,    67,    67,    67,
      67,    60,    60,   374,    60,   376,    70,    71,    72,    73,
      73,    56,   374,    57,   376,    57,    57,    55,    57,    55,
      77,   383,    83,    77,    70,    75,    58,    55,    60,    22,
      24,    82,    64,   395,    61,    67,    68,    62,    75,    57,
     192,    75,    75,   195,    75,    75,    61,    69,    60,    57,
     383,    60,   204,    69,    20,    55,   208,   209,    55,   421,
     422,    75,   395,    55,    35,    55,   426,   429,   428,   431,
      55,   223,   426,   225,   428,    55,    60,   439,    20,    55,
     294,    62,    24,   416,    26,   299,    28,    29,    30,    31,
      62,   453,   454,    61,   456,   428,    75,    75,   460,    60,
      33,    50,   460,   414,   505,   438,   468,   426,   470,   438,
     428,   557,   516,   193,   249,   588,   588,   285,   223,    31,
     334,   126,   484,   207,   486,   339,   488,   589,   207,    71,
     572,   151,   346,   298,   301,   231,   237,   395,   470,    -1,
      -1,    -1,    -1,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   187,   188,   189,   190,   191,
     374,    -1,   376,    -1,    -1,    -1,   198,   199,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   539,   540,   211,
      -1,    -1,   124,   335,   126,   337,   338,    -1,   550,    -1,
      -1,    -1,   224,    -1,    -1,    -1,    -1,   229,   230,    -1,
     414,   233,    -1,   235,   236,    -1,   238,   239,    -1,    -1,
     242,    -1,   426,    -1,   246,   247,    -1,    -1,   250,    -1,
      -1,   435,    -1,   585,   586,    -1,    -1,    -1,    65,    66,
       0,     1,    -1,    70,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,   460,    17,    18,    19,
     192,   283,    -1,   195,    -1,    -1,   470,    -1,    -1,    -1,
      -1,    -1,   204,    -1,    -1,    -1,   208,   209,    -1,    -1,
      -1,   303,   304,   305,    -1,    -1,    -1,   429,    -1,   431,
      -1,   223,    -1,   225,    -1,   227,   228,   439,    58,    -1,
      -1,   505,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,   453,   454,     6,   456,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,   358,    -1,   542,    -1,
      -1,    -1,   484,    -1,   486,    -1,   488,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    -1,   378,    -1,    -1,    -1,
      53,    54,    -1,    56,    -1,    58,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,   206,
      -1,    -1,    75,    -1,    -1,   407,   408,    -1,    -1,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,    92,
      -1,    -1,    -1,   335,    -1,   337,   338,    -1,   550,    -1,
      -1,    -1,    -1,    -1,    -1,   206,    -1,    -1,   440,   441,
     442,   443,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
     452,    -1,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,   585,   586,    17,    18,    19,    -1,    -1,
     472,    -1,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    -1,    -1,    -1,    17,    18,    19,   295,   296,
      -1,    -1,    -1,    -1,    -1,   302,    -1,    -1,    -1,   306,
     307,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,    -1,
      -1,    -1,   514,    -1,   516,    -1,    -1,   429,    -1,   431,
      -1,    -1,    -1,    -1,   295,   296,    58,   439,    -1,   531,
      -1,   302,    -1,    -1,    -1,   306,   307,    -1,    -1,    -1,
      -1,   453,   454,    -1,   456,   547,   548,   549,    -1,    -1,
     552,    -1,    -1,    -1,    -1,   557,   468,    -1,    -1,    -1,
      -1,    -1,    48,   206,   566,    -1,    -1,    53,    54,    55,
      -1,    -1,   484,    -1,   486,    -1,   488,    -1,   385,    -1,
      -1,   388,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    78,    79,    80,   597,   403,    -1,    -1,   406,
      -1,    -1,    -1,    -1,    -1,   412,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   385,    -1,    -1,   388,    -1,    -1,
      -1,   206,    -1,    -1,    48,    49,    50,   539,   540,    53,
      54,    55,   403,    -1,    -1,   406,    -1,    61,   550,    -1,
      -1,   412,    -1,    67,    68,    69,    70,    71,    72,    73,
      -1,    -1,   295,   296,    78,    79,    80,    -1,    -1,   302,
     467,    -1,   469,   306,   307,    -1,   473,   474,    -1,   476,
      -1,    -1,    -1,   585,   586,    -1,   483,    -1,   485,    -1,
     487,   206,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   467,    -1,   469,    -1,
      -1,    -1,   473,   474,    -1,   476,    -1,    -1,    -1,    -1,
     295,   296,   483,    -1,   485,    -1,   487,   302,    -1,    -1,
      -1,   306,   307,    -1,    -1,    -1,    -1,    48,    49,    50,
      -1,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   385,    -1,   551,   388,   553,    68,    69,    70,
      71,    72,    73,   560,   561,   562,    -1,    78,    79,    80,
     403,    -1,    -1,   406,    -1,    -1,    -1,    -1,    -1,   412,
     577,   578,    -1,    -1,   581,    -1,    -1,   302,    -1,    -1,
     551,   588,   553,   590,    -1,    -1,    -1,    -1,    -1,   560,
     561,   562,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     385,    -1,    -1,   388,    -1,    -1,   577,   578,    -1,    -1,
     581,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   403,   590,
      -1,   406,    -1,    -1,   467,    -1,   469,   412,    -1,    32,
     473,   474,    -1,   476,    -1,    -1,    -1,    -1,    -1,    42,
     483,    -1,   485,    -1,   487,    48,    49,    50,    51,    -1,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     385,    -1,    -1,   388,    -1,    68,    69,    70,    71,    72,
      73,    -1,    -1,    76,    -1,    78,    79,    80,   403,    -1,
      -1,   406,   467,    -1,   469,    -1,    -1,   412,   473,   474,
      -1,   476,    -1,    -1,    -1,    -1,    -1,    -1,   483,    -1,
     485,    -1,   487,    -1,    -1,    -1,    -1,    -1,   551,    -1,
     553,    -1,    -1,    -1,    -1,    -1,    -1,   560,   561,   562,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      -1,     6,    -1,    -1,   577,   578,    11,    -1,   581,    -1,
      15,    16,   467,    -1,   469,    -1,    -1,   590,   473,   474,
      -1,   476,    -1,    28,    -1,    -1,    -1,    -1,   483,    -1,
     485,    -1,   487,    -1,    -1,    -1,   551,    -1,   553,    -1,
      45,    46,    47,    -1,    -1,   560,   561,   562,    53,    54,
      -1,    56,    -1,    58,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    66,   577,   578,    -1,    -1,   581,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   590,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   551,    -1,   553,    -1,
      -1,    -1,    -1,    -1,    -1,   560,   561,   562,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,     3,    -1,    -1,     6,
      -1,    -1,   577,   578,    11,    -1,   581,    -1,    15,    16,
      -1,    -1,    -1,    -1,    21,   590,    23,    -1,    25,    26,
      27,    28,    29,    30,    31,    -1,    33,    -1,    -1,    36,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,
      47,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    56,
      -1,    58,    -1,    60,    -1,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,    -1,    86,
      87,    88,    89,    90,    91,    92,     1,    -1,     3,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      15,    16,    -1,    -1,    -1,    -1,    21,    -1,    23,    -1,
      25,    26,    27,    28,    29,    30,    31,    -1,    33,    -1,
      -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,    54,
      -1,    56,    -1,    58,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,     1,    -1,
       3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    15,    16,    -1,    -1,    -1,    -1,    21,    -1,
      23,    -1,    25,    26,    27,    28,    29,    30,    31,    -1,
      33,    -1,    -1,    36,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,
      53,    54,    -1,    56,    -1,    58,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    -1,
      -1,    -1,    -1,    86,    87,    88,    89,    90,    91,    92,
       1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      11,    -1,    -1,    -1,    15,    16,    -1,    -1,    -1,    -1,
      21,    -1,    23,    -1,    25,    26,    27,    28,    29,    30,
      31,    -1,    33,    -1,    -1,    36,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,    60,
      -1,    -1,    -1,    -1,    -1,    66,    -1,     1,    -1,     3,
      -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,
      81,    15,    16,    -1,    -1,    86,    87,    88,    89,    90,
      91,    92,    26,    -1,    28,    29,    30,    -1,    -1,    33,
      -1,    -1,    -1,    -1,    38,    -1,    40,    41,    -1,    -1,
      -1,    45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      54,    -1,    56,    -1,    58,    -1,    60,    -1,    -1,    -1,
      64,    65,    66,    -1,     1,    -1,     3,    -1,    -1,     6,
      -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    15,    16,
      -1,    -1,    86,    87,    88,    89,    90,    91,    92,    26,
      -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    56,
      -1,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,
      -1,     1,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,    86,
      87,    88,    89,    90,    91,    92,    26,    -1,    28,    29,
      30,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    41,    -1,    -1,    -1,    45,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    54,    -1,    56,    57,    58,    -1,
      60,    -1,    -1,    -1,    -1,    65,    66,    -1,     1,    -1,
       3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,    -1,
      -1,    -1,    15,    16,    -1,    -1,    86,    87,    88,    89,
      90,    91,    92,    26,    -1,    28,    29,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    -1,
      -1,    -1,    45,    46,    47,    -1,    -1,    -1,    -1,    52,
      53,    54,    -1,    56,    57,    58,    -1,    60,    -1,    -1,
      -1,    -1,    65,    66,    -1,     1,    -1,     3,    -1,    -1,
       6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,    15,
      16,    -1,    -1,    86,    87,    88,    89,    90,    91,    92,
      26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    -1,    40,    41,    -1,    -1,    -1,    45,
      46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,
      56,    57,    58,    -1,    60,    -1,    -1,    -1,    -1,    65,
      66,    -1,     1,    -1,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,
      86,    87,    88,    89,    90,    91,    92,    26,    -1,    28,
      29,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    -1,    -1,    -1,    45,    46,    47,    -1,
      -1,    -1,    -1,    52,    53,    54,    -1,    56,    -1,    58,
      -1,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,    92,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,
      -1,    -1,    21,    22,    23,    -1,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,    92,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,
      -1,    -1,    21,    -1,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,    92,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,
      -1,    -1,    21,    -1,    23,    -1,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,
      -1,    60,    61,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    -1,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,    92,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,
      -1,    -1,    21,    -1,    23,    -1,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    81,    82,    -1,    -1,    -1,    86,    87,    88,
      89,    90,    91,    92,     3,    -1,    -1,     6,    -1,    -1,
      -1,    -1,    11,    -1,    -1,    -1,    15,    16,    -1,    -1,
      -1,    -1,    21,    -1,    23,    -1,    25,    26,    27,    28,
      29,    30,    31,    -1,    33,    -1,    -1,    36,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,    11,
      -1,    -1,    81,    15,    16,    -1,    -1,    86,    87,    88,
      89,    90,    91,    92,    26,    -1,    28,    29,    30,    -1,
      -1,    33,    -1,    -1,    -1,    -1,    38,    -1,    40,    41,
      -1,    -1,    -1,    45,    46,    47,    -1,    -1,    -1,    -1,
      52,    53,    54,    -1,    56,    -1,    58,    -1,    60,    61,
      -1,    -1,    64,    65,    66,    -1,    -1,    -1,     3,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    11,    -1,    -1,    -1,
      15,    16,    -1,    -1,    86,    87,    88,    89,    90,    91,
      92,    26,    -1,    28,    29,    30,    -1,    -1,    33,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    -1,    -1,    -1,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    56,    32,    58,    -1,    60,    -1,    -1,    -1,    -1,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,
      50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    86,    87,    88,    89,    90,    91,    92,    68,    69,
      70,    71,    72,    73,    32,    -1,    76,    -1,    78,    79,
      80,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      48,    49,    50,    51,    -1,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      68,    69,    70,    71,    72,    73,    -1,    -1,    76,    -1,
      78,    79,    80,    48,    49,    50,    51,    -1,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    68,    69,    70,    71,    72,    73,    -1,
      -1,    76,    -1,    78,    79,    80,    48,    49,    50,    51,
      -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    35,    -1,    76,    -1,    78,    79,    80,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    -1,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    37,    -1,    76,    -1,    78,    79,    80,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    39,    -1,
      76,    -1,    78,    79,    80,    -1,    -1,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    42,    76,    -1,    78,    79,    80,
      48,    49,    50,    51,    -1,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    -1,    42,    76,    -1,
      78,    79,    80,    48,    49,    50,    51,    -1,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    -1,
      42,    76,    -1,    78,    79,    80,    48,    49,    50,    51,
      -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    -1,    -1,    76,    -1,    78,    79,    80,    48,
      49,    50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    -1,    76,    -1,    78,
      79,    80,    -1,    -1,    -1,    84,    48,    49,    50,    51,
      -1,    53,    54,    55,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    -1,    -1,    76,    -1,    78,    79,    80,    48,
      49,    50,    51,    -1,    53,    54,    55,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    -1,    -1,    76,    -1,    78,
      79,    80,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    -1,
      76,    -1,    78,    79,    80,    48,    49,    50,    51,    -1,
      53,    54,    55,    -1,    -1,    -1,    59,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    -1,    -1,    76,    -1,    78,    79,    80,    48,    49,
      50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    -1,    -1,    76,    -1,    78,    79,
      80,    48,    49,    50,    51,    -1,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    -1,    -1,    76,
      -1,    78,    79,    80,    48,    49,    50,    51,    -1,    53,
      54,    55,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      -1,    -1,    76,    -1,    78,    79,    80,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    -1,    76,    -1,    78,    79,    80,
      48,    49,    50,    51,    -1,    53,    54,    55,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    -1,    -1,    76,    -1,
      78,    79,    80,    48,    -1,    50,    -1,    -1,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    -1,
      -1,    -1,    -1,    78,    79,    80
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
       1,   197,   209,   210,   211,   212,   200,   207,   129,   146,
     146,   146,     1,   128,   197,     1,   128,    77,    77,    57,
      57,    57,    55,   108,   116,   117,   212,   182,   202,   182,
     182,     5,     7,   106,   107,   119,   120,   127,   212,    67,
      69,    75,    55,   106,   107,   122,   123,   124,   212,    75,
      39,    42,    35,    42,   146,   162,   163,    57,    59,     1,
      57,   145,    75,    75,    75,   204,    75,   204,   146,    61,
      67,   197,    22,    22,   129,    24,    24,    28,    62,    28,
      67,   211,    28,    32,    34,    37,    32,    61,    61,    82,
      82,   146,   146,    55,    75,    55,    75,    55,    75,   129,
      61,   117,   108,    57,    61,    69,   197,   197,    61,   119,
     106,   107,   127,   182,   182,    60,    61,   123,   124,   182,
     146,   146,   146,   146,    76,    61,    67,    57,    57,   146,
     182,   182,   182,   109,   129,   192,   129,   210,   146,   129,
     129,    60,   129,   129,   182,   129,   182,   129,   182,    62,
      62,    69,   122,    20,   195,   146,   163,    55,    55,    55,
      75,    32,    42,    35,     1,    38,    64,   133,   134,   146,
      55,    55,    55,   192,   192,    61,    60,    55,   196,   146,
     146,   146,   182,   129,   146,   129,    61,    62,    62,    61,
     134,    62,   129,   129,   129,    75,    75,   146,    60,   195,
      32,   129,   129,   129,   182,   182,    61,    56,   147,   175,
     179,   196,   129,   146,    61,    61,    57
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
       3,     3,     4,     4,     6,     8,     4,     2,     3,     3,
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
    1066,  1070,  1078,  1086,  1094,  1098,  1106,  1114,  1122,  1126,
    1130,  1135,  1144,  1148,  1152,  1157,  1166,  1170,  1178,  1186,
    1198,  1205,  1215,  1219,  1223,  1227,  1231,  1235,  1239,  1243,
    1247,  1251,  1259,  1263,  1267,  1271,  1275,  1279,  1283,  1295,
    1299,  1303,  1307,  1311,  1315,  1319,  1323,  1327,  1331,  1335,
    1339,  1343,  1347,  1351,  1355,  1359,  1363,  1371,  1375,  1379,
    1387,  1394,  1398,  1403,  1407,  1415,  1420,  1427,  1433,  1441,
    1449,  1456,  1462,  1470,  1478,  1486,  1494,  1502,  1510,  1518,
    1525,  1532,  1539,  1548,  1561,  1565,  1569,  1573,  1577,  1581,
    1585,  1589,  1597,  1601,  1605,  1609,  1617,  1626,  1632,  1642,
    1650,  1658,  1666,  1670,  1678,  1686,  1715,  1722,  1728,  1736,
    1746,  1759,  1773,  1780,  1789,  1796,  1803,  1812,  1817,  1823,
    1839,  1846,  1855,  1859,  1863,  1867,  1871,  1875,  1879,  1883,
    1891,  1899,  1910,  1921,  1929,  1937,  1945,  1953,  1965,  1972,
    1982,  1986,  1994,  2001,  2015,  2022,  2036,  2040,  2048,  2054,
    2067,  2080,  2084,  2089,  2094,  2099,  2104,  2113,  2120,  2132,
    2136,  2145,  2152,  2162,  2169,  2179,  2188,  2194,  2202,  2208,
    2220,  2227,  2236,  2248,  2255,  2264,  2268,  2284,  2291,  2300,
    2306,  2310,  2317,  2330,  2336,  2345,  2352,  2359,  2366,  2373,
    2380,  2387
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
#line 7033 "GrammarParser.cpp"

#line 2393 "../../obj/src/GrammarParser.y"


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
