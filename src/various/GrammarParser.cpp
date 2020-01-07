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
#line 93 "../../obj/src/GrammarParser.y"

    #include "../../src/Lexer.h"

    #include <libstdhl/Type>

    #undef yylex
    #define yylex m_lexer.nextToken

    static BasicType::Ptr createVoidType( libstdhl::SourceLocation& sourceLocation )
    {
        const auto name = AST::make< Identifier >( sourceLocation, TypeInfo::TYPE_NAME_VOID );
        const auto path = AST::make< IdentifierPath >( sourceLocation, name );
        const auto node = AST::make< BasicType >( sourceLocation, path );
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
      case symbol_kind::S_TEMPLATE: // "template"
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

      case symbol_kind::S_Template: // Template
      case symbol_kind::S_MaybeTemplate: // MaybeTemplate
        value.YY_MOVE_OR_COPY< Template::Ptr > (YY_MOVE (that.value));
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
        value.YY_MOVE_OR_COPY< libcasm_fe::AST::Type::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_TEMPLATE: // "template"
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

      case symbol_kind::S_Template: // Template
      case symbol_kind::S_MaybeTemplate: // MaybeTemplate
        value.move< Template::Ptr > (YY_MOVE (that.value));
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
        value.move< libcasm_fe::AST::Type::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_TEMPLATE: // "template"
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

      case symbol_kind::S_Template: // Template
      case symbol_kind::S_MaybeTemplate: // MaybeTemplate
        value.copy< Template::Ptr > (that.value);
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
        value.copy< libcasm_fe::AST::Type::Ptr > (that.value);
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
      case symbol_kind::S_TEMPLATE: // "template"
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

      case symbol_kind::S_Template: // Template
      case symbol_kind::S_MaybeTemplate: // MaybeTemplate
        value.move< Template::Ptr > (that.value);
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
        value.move< libcasm_fe::AST::Type::Ptr > (that.value);
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
      case symbol_kind::S_TEMPLATE: // "template"
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

      case symbol_kind::S_Template: // Template
      case symbol_kind::S_MaybeTemplate: // MaybeTemplate
        yylhs.value.emplace< Template::Ptr > ();
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
        yylhs.value.emplace< libcasm_fe::AST::Type::Ptr > ();
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
      m_specification.setHeader( yystack_[1].value.as < HeaderDefinition::Ptr > () );
      m_specification.setDefinitions( yystack_[0].value.as < Definitions::Ptr > () );
      m_specification.setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 2876 "GrammarParser.cpp"
    break;

  case 3: // Header: Attributes "CASM"
#line 455 "../../obj/src/GrammarParser.y"
  {
      auto definition = AST::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2886 "GrammarParser.cpp"
    break;

  case 4: // Header: "CASM"
#line 461 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < HeaderDefinition::Ptr > () = AST::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 2894 "GrammarParser.cpp"
    break;

  case 5: // Definitions: Definitions AttributedDefinition
#line 469 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2904 "GrammarParser.cpp"
    break;

  case 6: // Definitions: AttributedDefinition
#line 475 "../../obj/src/GrammarParser.y"
  {
      auto definitions = AST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2914 "GrammarParser.cpp"
    break;

  case 7: // AttributedDefinition: Attributes Definition
#line 485 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2924 "GrammarParser.cpp"
    break;

  case 8: // AttributedDefinition: Definition
#line 491 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2932 "GrammarParser.cpp"
    break;

  case 9: // AttributedDefinition: error
#line 495 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2940 "GrammarParser.cpp"
    break;

  case 10: // Definition: InitDefinition
#line 503 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2948 "GrammarParser.cpp"
    break;

  case 11: // Definition: EnumerationDefinition
#line 507 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2956 "GrammarParser.cpp"
    break;

  case 12: // Definition: DerivedDefinition
#line 511 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2964 "GrammarParser.cpp"
    break;

  case 13: // Definition: RuleDefinition
#line 515 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2972 "GrammarParser.cpp"
    break;

  case 14: // Definition: FunctionDefinition
#line 519 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 2980 "GrammarParser.cpp"
    break;

  case 15: // Definition: UsingDefinition
#line 523 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 2988 "GrammarParser.cpp"
    break;

  case 16: // Definition: UsingPathDefinition
#line 527 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingPathDefinition::Ptr > ();
  }
#line 2996 "GrammarParser.cpp"
    break;

  case 17: // Definition: InvariantDefinition
#line 531 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 3004 "GrammarParser.cpp"
    break;

  case 18: // Definition: ImportDefinition
#line 535 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 3012 "GrammarParser.cpp"
    break;

  case 19: // Definition: StructureDefinition
#line 539 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < StructureDefinition::Ptr > ();
  }
#line 3020 "GrammarParser.cpp"
    break;

  case 20: // Definition: BehaviorDefinition
#line 543 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < BehaviorDefinition::Ptr > ();
  }
#line 3028 "GrammarParser.cpp"
    break;

  case 21: // Definition: ImplementDefinition
#line 547 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImplementDefinition::Ptr > ();
  }
#line 3036 "GrammarParser.cpp"
    break;

  case 22: // Definition: DomainDefinition
#line 551 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DomainDefinition::Ptr > ();
  }
#line 3044 "GrammarParser.cpp"
    break;

  case 23: // Definition: BuiltinDefinition
#line 555 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < BuiltinDefinition::Ptr > ();
  }
#line 3052 "GrammarParser.cpp"
    break;

  case 24: // InitDefinition: "init" IdentifierPath
#line 563 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = AST::make< InitDefinition >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3060 "GrammarParser.cpp"
    break;

  case 25: // InitDefinition: "init" "{" Initializers "}"
#line 567 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = AST::make< InitDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3068 "GrammarParser.cpp"
    break;

  case 26: // EnumerationDefinition: "enumeration" Identifier "=" "{" Enumerators "}"
#line 575 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumerationDefinition::Ptr > () = AST::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3076 "GrammarParser.cpp"
    break;

  case 27: // DerivedDefinition: "derived" Identifier "->" Type "=" Term
#line 583 "../../obj/src/GrammarParser.y"
  {
      const auto params = AST::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = AST::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3085 "GrammarParser.cpp"
    break;

  case 28: // DerivedDefinition: "derived" Identifier "(" Parameters ")" "->" Type "=" Term
#line 588 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = AST::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < AST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < AST::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
  }
#line 3095 "GrammarParser.cpp"
    break;

  case 29: // DerivedDefinition: "derived" Identifier "(" MethodParameters ")" "->" Type "=" Term
#line 594 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = AST::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < AST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < AST::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
  }
#line 3105 "GrammarParser.cpp"
    break;

  case 30: // DerivedDefinition: "derived" Identifier "(" error ")" "->" Type "=" Term
#line 600 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 3113 "GrammarParser.cpp"
    break;

  case 31: // RuleDefinition: "rule" Identifier "=" Rule
#line 608 "../../obj/src/GrammarParser.y"
  {
      const auto params = AST::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = AST::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3123 "GrammarParser.cpp"
    break;

  case 32: // RuleDefinition: "rule" Identifier "->" Type "=" Rule
#line 614 "../../obj/src/GrammarParser.y"
  {
      const auto params = AST::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = AST::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3132 "GrammarParser.cpp"
    break;

  case 33: // RuleDefinition: "rule" Identifier "(" Parameters ")" "=" Rule
#line 619 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = AST::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < AST::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < AST::Token::Ptr > () );
  }
#line 3143 "GrammarParser.cpp"
    break;

  case 34: // RuleDefinition: "rule" Identifier "(" Parameters ")" "->" Type "=" Rule
#line 626 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = AST::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < AST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
  }
#line 3153 "GrammarParser.cpp"
    break;

  case 35: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "=" Rule
#line 632 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = AST::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < AST::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < AST::Token::Ptr > () );
  }
#line 3164 "GrammarParser.cpp"
    break;

  case 36: // RuleDefinition: "rule" Identifier "(" MethodParameters ")" "->" Type "=" Rule
#line 639 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = AST::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < AST::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < AST::Token::Ptr > () );
  }
#line 3174 "GrammarParser.cpp"
    break;

  case 37: // RuleDefinition: "rule" Identifier "(" error ")" "=" Rule
#line 645 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3182 "GrammarParser.cpp"
    break;

  case 38: // RuleDefinition: "rule" Identifier "(" error ")" "->" Type "=" Rule
#line 649 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3190 "GrammarParser.cpp"
    break;

  case 39: // FunctionDefinition: "function" Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 657 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = AST::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < AST::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
  }
#line 3198 "GrammarParser.cpp"
    break;

  case 40: // EnumeratorDefinition: Identifier
#line 665 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = AST::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3206 "GrammarParser.cpp"
    break;

  case 41: // EnumeratorDefinition: Attributes Identifier
#line 669 "../../obj/src/GrammarParser.y"
  {
      auto enumerator = AST::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 3216 "GrammarParser.cpp"
    break;

  case 42: // EnumeratorDefinition: error
#line 675 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 3224 "GrammarParser.cpp"
    break;

  case 43: // Enumerators: Enumerators "," EnumeratorDefinition
#line 683 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3235 "GrammarParser.cpp"
    break;

  case 44: // Enumerators: EnumeratorDefinition
#line 690 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = AST::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3245 "GrammarParser.cpp"
    break;

  case 45: // UsingDefinition: "using" Identifier "=" Type
#line 700 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingDefinition::Ptr > () = AST::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > () );
  }
#line 3253 "GrammarParser.cpp"
    break;

  case 46: // UsingPathDefinition: "using" IdentifierPath
#line 708 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = AST::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3261 "GrammarParser.cpp"
    break;

  case 47: // UsingPathDefinition: "using" IdentifierPath "::" "*"
#line 712 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = AST::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3269 "GrammarParser.cpp"
    break;

  case 48: // InvariantDefinition: "invariant" Identifier "=" Term
#line 720 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InvariantDefinition::Ptr > () = AST::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3277 "GrammarParser.cpp"
    break;

  case 49: // ImportDefinition: "import" IdentifierPath
#line 728 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = AST::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3285 "GrammarParser.cpp"
    break;

  case 50: // ImportDefinition: "import" IdentifierPath "as" Identifier
#line 732 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = AST::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3293 "GrammarParser.cpp"
    break;

  case 51: // StructureDefinition: MaybeTemplate "structure" Identifier "=" "{" StructureDefinitionList "}"
#line 744 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < StructureDefinition::Ptr > () = AST::make< StructureDefinition >( yylhs.location, yystack_[6].value.as < Template::Ptr > (), yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < FunctionDefinitions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3301 "GrammarParser.cpp"
    break;

  case 52: // StructureDefinitionList: StructureDefinitionList StructureDefinitionElement
#line 751 "../../obj/src/GrammarParser.y"
  {
      auto functions = yystack_[1].value.as < FunctionDefinitions::Ptr > ();
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3311 "GrammarParser.cpp"
    break;

  case 53: // StructureDefinitionList: StructureDefinitionElement
#line 757 "../../obj/src/GrammarParser.y"
  {
      auto functions = AST::make< FunctionDefinitions >( yylhs.location );
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3321 "GrammarParser.cpp"
    break;

  case 54: // StructureDefinitionElement: Attributes FunctionDefinition
#line 766 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 3331 "GrammarParser.cpp"
    break;

  case 55: // StructureDefinitionElement: FunctionDefinition
#line 772 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 3339 "GrammarParser.cpp"
    break;

  case 56: // BehaviorDefinition: MaybeTemplate "behavior" Type "=" "{" BehaviorDefinitionList "}"
#line 784 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BehaviorDefinition::Ptr > () = AST::make< BehaviorDefinition >( yylhs.location, yystack_[6].value.as < Template::Ptr > (), yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3347 "GrammarParser.cpp"
    break;

  case 57: // BehaviorDefinitionElement: Attributes Declaration
#line 792 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Declaration::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3357 "GrammarParser.cpp"
    break;

  case 58: // BehaviorDefinitionElement: Declaration
#line 798 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Declaration::Ptr > ();
  }
#line 3365 "GrammarParser.cpp"
    break;

  case 59: // BehaviorDefinitionElement: Attributes DerivedDefinition
#line 802 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < DerivedDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3375 "GrammarParser.cpp"
    break;

  case 60: // BehaviorDefinitionElement: DerivedDefinition
#line 808 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3383 "GrammarParser.cpp"
    break;

  case 61: // BehaviorDefinitionElement: Attributes RuleDefinition
#line 812 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < RuleDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3393 "GrammarParser.cpp"
    break;

  case 62: // BehaviorDefinitionElement: RuleDefinition
#line 818 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3401 "GrammarParser.cpp"
    break;

  case 63: // BehaviorDefinitionList: BehaviorDefinitionList BehaviorDefinitionElement
#line 826 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3411 "GrammarParser.cpp"
    break;

  case 64: // BehaviorDefinitionList: BehaviorDefinitionElement
#line 832 "../../obj/src/GrammarParser.y"
  {
      auto definitions = AST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3421 "GrammarParser.cpp"
    break;

  case 65: // Template: "template" "<" TemplateVariables ">"
#line 841 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Template::Ptr > () = AST::make< Template >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < VariableDefinitions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3429 "GrammarParser.cpp"
    break;

  case 66: // MaybeTemplate: Template
#line 848 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Template::Ptr > () = yystack_[0].value.as < Template::Ptr > ();
  }
#line 3437 "GrammarParser.cpp"
    break;

  case 67: // MaybeTemplate: %empty
#line 852 "../../obj/src/GrammarParser.y"
  {
      const auto& templateSymbols = AST::make< VariableDefinitions >( yylhs.location );
      yylhs.value.as < Template::Ptr > () = AST::make< Template >( yylhs.location, Token::unresolved(), Token::unresolved(), templateSymbols, Token::unresolved() );
  }
#line 3446 "GrammarParser.cpp"
    break;

  case 68: // ImplementDefinition: MaybeTemplate "implement" Type "=" "{" ImplementDefinitionList "}"
#line 866 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementDefinition::Ptr > () = AST::make< ImplementDefinition >( yylhs.location, yystack_[6].value.as < Template::Ptr > (), yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3454 "GrammarParser.cpp"
    break;

  case 69: // ImplementDefinition: MaybeTemplate "implement" Type "for" Type "=" "{" ImplementDefinitionList "}"
#line 870 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementDefinition::Ptr > () = AST::make< ImplementDefinition >( yylhs.location, yystack_[8].value.as < Template::Ptr > (), yystack_[7].value.as < AST::Token::Ptr > (), yystack_[6].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Definitions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3462 "GrammarParser.cpp"
    break;

  case 70: // ImplementDefinitionList: ImplementDefinitionList ImplementDefinitionElement
#line 877 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3472 "GrammarParser.cpp"
    break;

  case 71: // ImplementDefinitionList: ImplementDefinitionElement
#line 883 "../../obj/src/GrammarParser.y"
  {
      auto definitions = AST::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3482 "GrammarParser.cpp"
    break;

  case 72: // ImplementDefinitionElement: Attributes ImplementDefinitionAttributedElement
#line 892 "../../obj/src/GrammarParser.y"
  {
      const auto& definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3492 "GrammarParser.cpp"
    break;

  case 73: // ImplementDefinitionElement: ImplementDefinitionAttributedElement
#line 898 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 3500 "GrammarParser.cpp"
    break;

  case 74: // ImplementDefinitionAttributedElement: DerivedDefinition
#line 905 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3508 "GrammarParser.cpp"
    break;

  case 75: // ImplementDefinitionAttributedElement: RuleDefinition
#line 909 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3516 "GrammarParser.cpp"
    break;

  case 76: // DomainDefinition: MaybeTemplate "domain" Type
#line 921 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DomainDefinition::Ptr > () = AST::make< DomainDefinition >( yylhs.location, yystack_[2].value.as < Template::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > () );
  }
#line 3524 "GrammarParser.cpp"
    break;

  case 77: // BuiltinDefinition: MaybeTemplate "builtin" RelationType
#line 933 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BuiltinDefinition::Ptr > () = AST::make< BuiltinDefinition >( yylhs.location, yystack_[2].value.as < Template::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < RelationType::Ptr > () );
  }
#line 3532 "GrammarParser.cpp"
    break;

  case 78: // Declaration: "derived" Identifier ":" MaybeFunctionParameters "->" Type
#line 945 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = AST::make< Declaration >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > () );
  }
#line 3540 "GrammarParser.cpp"
    break;

  case 79: // Declaration: "rule" Identifier ":" MaybeFunctionParameters "->" Type
#line 949 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Declaration::Ptr > () = AST::make< Declaration >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > () );
  }
#line 3548 "GrammarParser.cpp"
    break;

  case 80: // Rules: Rules Rule
#line 961 "../../obj/src/GrammarParser.y"
  {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3558 "GrammarParser.cpp"
    break;

  case 81: // Rules: Rule
#line 967 "../../obj/src/GrammarParser.y"
  {
      auto rules = AST::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3568 "GrammarParser.cpp"
    break;

  case 82: // Rule: SkipRule
#line 977 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 3576 "GrammarParser.cpp"
    break;

  case 83: // Rule: ConditionalRule
#line 981 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 3584 "GrammarParser.cpp"
    break;

  case 84: // Rule: CaseRule
#line 985 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 3592 "GrammarParser.cpp"
    break;

  case 85: // Rule: LetRule
#line 989 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 3600 "GrammarParser.cpp"
    break;

  case 86: // Rule: LocalRule
#line 993 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LocalRule::Ptr > ();
  }
#line 3608 "GrammarParser.cpp"
    break;

  case 87: // Rule: ForallRule
#line 997 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 3616 "GrammarParser.cpp"
    break;

  case 88: // Rule: ChooseRule
#line 1001 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 3624 "GrammarParser.cpp"
    break;

  case 89: // Rule: IterateRule
#line 1005 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 3632 "GrammarParser.cpp"
    break;

  case 90: // Rule: BlockRule
#line 1009 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 3640 "GrammarParser.cpp"
    break;

  case 91: // Rule: SequenceRule
#line 1013 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 3648 "GrammarParser.cpp"
    break;

  case 92: // Rule: UpdateRule
#line 1017 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 3656 "GrammarParser.cpp"
    break;

  case 93: // Rule: CallRule
#line 1021 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 3664 "GrammarParser.cpp"
    break;

  case 94: // Rule: WhileRule
#line 1025 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 3672 "GrammarParser.cpp"
    break;

  case 95: // SkipRule: "skip"
#line 1033 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SkipRule::Ptr > () = AST::make< SkipRule >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3680 "GrammarParser.cpp"
    break;

  case 96: // ConditionalRule: "if" Term "then" Rule
#line 1041 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = AST::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3688 "GrammarParser.cpp"
    break;

  case 97: // ConditionalRule: "if" Term "then" Rule "else" Rule
#line 1045 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = AST::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3696 "GrammarParser.cpp"
    break;

  case 98: // CaseRule: "case" Term "of" "{" CaseLabels "}"
#line 1053 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = AST::make< CaseRule >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3704 "GrammarParser.cpp"
    break;

  case 99: // CaseRule: "case" Term "of" "{" error "}"
#line 1057 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 3712 "GrammarParser.cpp"
    break;

  case 100: // CaseLabels: CaseLabels CaseLabel
#line 1065 "../../obj/src/GrammarParser.y"
  {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3722 "GrammarParser.cpp"
    break;

  case 101: // CaseLabels: CaseLabel
#line 1071 "../../obj/src/GrammarParser.y"
  {
      auto cases = AST::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3732 "GrammarParser.cpp"
    break;

  case 102: // CaseLabel: "default" ":" Rule
#line 1081 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = AST::make< DefaultCase >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3740 "GrammarParser.cpp"
    break;

  case 103: // CaseLabel: "_" ":" Rule
#line 1085 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = AST::make< DefaultCase >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3748 "GrammarParser.cpp"
    break;

  case 104: // CaseLabel: Term ":" Rule
#line 1089 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = AST::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3756 "GrammarParser.cpp"
    break;

  case 105: // LetRule: "let" VariableBindings "in" Rule
#line 1097 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetRule::Ptr > () = AST::make< LetRule >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3764 "GrammarParser.cpp"
    break;

  case 106: // LocalRule: "local" LocalFunctionDefinitions "in" Rule
#line 1105 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LocalRule::Ptr > () = AST::make< LocalRule >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < FunctionDefinitions::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3772 "GrammarParser.cpp"
    break;

  case 107: // ForallRule: "forall" AttributedVariables "in" Term "do" Rule
#line 1113 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = AST::make< ForallRule >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3780 "GrammarParser.cpp"
    break;

  case 108: // ForallRule: "forall" AttributedVariables "in" Term "with" Term "do" Rule
#line 1117 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = AST::make< ForallRule >( yylhs.location, yystack_[7].value.as < AST::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3788 "GrammarParser.cpp"
    break;

  case 109: // ChooseRule: "choose" AttributedVariables "in" Term "do" Rule
#line 1125 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseRule::Ptr > () = AST::make< ChooseRule >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3796 "GrammarParser.cpp"
    break;

  case 110: // IterateRule: "iterate" Rule
#line 1133 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = AST::make< IterateRule >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3804 "GrammarParser.cpp"
    break;

  case 111: // BlockRule: "{" Rules "}"
#line 1141 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = AST::make< BlockRule >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3812 "GrammarParser.cpp"
    break;

  case 112: // BlockRule: "par" Rules "endpar"
#line 1145 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = AST::make< BlockRule >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3820 "GrammarParser.cpp"
    break;

  case 113: // BlockRule: "{" error "}"
#line 1149 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3829 "GrammarParser.cpp"
    break;

  case 114: // BlockRule: "par" error "endpar"
#line 1154 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3838 "GrammarParser.cpp"
    break;

  case 115: // SequenceRule: "{|" Rules "|}"
#line 1163 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = AST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3846 "GrammarParser.cpp"
    break;

  case 116: // SequenceRule: "seq" Rules "endseq"
#line 1167 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = AST::make< SequenceRule >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 3854 "GrammarParser.cpp"
    break;

  case 117: // SequenceRule: "{|" error "|}"
#line 1171 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3863 "GrammarParser.cpp"
    break;

  case 118: // SequenceRule: "seq" error "endseq"
#line 1176 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3872 "GrammarParser.cpp"
    break;

  case 119: // UpdateRule: DirectCallExpression ":=" Term
#line 1185 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = AST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3880 "GrammarParser.cpp"
    break;

  case 120: // UpdateRule: MethodCallExpression ":=" Term
#line 1189 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = AST::make< UpdateRule >( yylhs.location, yystack_[2].value.as < MethodCallExpression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3888 "GrammarParser.cpp"
    break;

  case 121: // CallRule: CallExpression
#line 1197 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallRule::Ptr > () = AST::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 3896 "GrammarParser.cpp"
    break;

  case 122: // WhileRule: "while" Term "do" Rule
#line 1205 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < WhileRule::Ptr > () = AST::make< WhileRule >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3904 "GrammarParser.cpp"
    break;

  case 123: // Terms: Terms "," Term
#line 1217 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3915 "GrammarParser.cpp"
    break;

  case 124: // Terms: Term
#line 1224 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = AST::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3925 "GrammarParser.cpp"
    break;

  case 125: // Term: SimpleOrClaspedTerm
#line 1234 "../../obj/src/GrammarParser.y"
  {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3933 "GrammarParser.cpp"
    break;

  case 126: // Term: TypeCastingExpression
#line 1238 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 3941 "GrammarParser.cpp"
    break;

  case 127: // Term: OperatorExpression
#line 1242 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3949 "GrammarParser.cpp"
    break;

  case 128: // Term: LetExpression
#line 1246 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 3957 "GrammarParser.cpp"
    break;

  case 129: // Term: ConditionalExpression
#line 1250 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 3965 "GrammarParser.cpp"
    break;

  case 130: // Term: ChooseExpression
#line 1254 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 3973 "GrammarParser.cpp"
    break;

  case 131: // Term: UniversalQuantifierExpression
#line 1258 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 3981 "GrammarParser.cpp"
    break;

  case 132: // Term: ExistentialQuantifierExpression
#line 1262 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 3989 "GrammarParser.cpp"
    break;

  case 133: // Term: CardinalityExpression
#line 1266 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 3997 "GrammarParser.cpp"
    break;

  case 134: // SimpleOrClaspedTerm: "(" Term ")"
#line 1274 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< AST::EmbracedExpression >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4005 "GrammarParser.cpp"
    break;

  case 135: // SimpleOrClaspedTerm: "(" error ")"
#line 1278 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 4013 "GrammarParser.cpp"
    break;

  case 136: // SimpleOrClaspedTerm: CallExpression
#line 1282 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 4021 "GrammarParser.cpp"
    break;

  case 137: // SimpleOrClaspedTerm: LiteralCallExpression
#line 1286 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 4029 "GrammarParser.cpp"
    break;

  case 138: // SimpleOrClaspedTerm: Literal
#line 1290 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 4037 "GrammarParser.cpp"
    break;

  case 139: // SimpleOrClaspedTerm: "+" SimpleOrClaspedTerm
#line 1294 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4045 "GrammarParser.cpp"
    break;

  case 140: // SimpleOrClaspedTerm: "-" SimpleOrClaspedTerm
#line 1298 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4053 "GrammarParser.cpp"
    break;

  case 141: // OperatorExpression: Term "+" Term
#line 1310 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4061 "GrammarParser.cpp"
    break;

  case 142: // OperatorExpression: Term "-" Term
#line 1314 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4069 "GrammarParser.cpp"
    break;

  case 143: // OperatorExpression: Term "*" Term
#line 1318 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4077 "GrammarParser.cpp"
    break;

  case 144: // OperatorExpression: Term "/" Term
#line 1322 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4085 "GrammarParser.cpp"
    break;

  case 145: // OperatorExpression: Term "%" Term
#line 1326 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4093 "GrammarParser.cpp"
    break;

  case 146: // OperatorExpression: Term "^" Term
#line 1330 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4101 "GrammarParser.cpp"
    break;

  case 147: // OperatorExpression: Term "!=" Term
#line 1334 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4109 "GrammarParser.cpp"
    break;

  case 148: // OperatorExpression: Term "=" Term
#line 1338 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4117 "GrammarParser.cpp"
    break;

  case 149: // OperatorExpression: Term "<" Term
#line 1342 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4125 "GrammarParser.cpp"
    break;

  case 150: // OperatorExpression: Term ">" Term
#line 1346 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4133 "GrammarParser.cpp"
    break;

  case 151: // OperatorExpression: Term "<=" Term
#line 1350 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4141 "GrammarParser.cpp"
    break;

  case 152: // OperatorExpression: Term ">=" Term
#line 1354 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4149 "GrammarParser.cpp"
    break;

  case 153: // OperatorExpression: Term "or" Term
#line 1358 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4157 "GrammarParser.cpp"
    break;

  case 154: // OperatorExpression: Term "xor" Term
#line 1362 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4165 "GrammarParser.cpp"
    break;

  case 155: // OperatorExpression: Term "and" Term
#line 1366 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4173 "GrammarParser.cpp"
    break;

  case 156: // OperatorExpression: Term "=>" Term
#line 1370 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4181 "GrammarParser.cpp"
    break;

  case 157: // OperatorExpression: Term "implies" Term
#line 1374 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4189 "GrammarParser.cpp"
    break;

  case 158: // OperatorExpression: "not" Term
#line 1378 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = AST::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4197 "GrammarParser.cpp"
    break;

  case 159: // CallExpression: DirectCallExpression
#line 1386 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 4205 "GrammarParser.cpp"
    break;

  case 160: // CallExpression: MethodCallExpression
#line 1390 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 4213 "GrammarParser.cpp"
    break;

  case 161: // CallExpression: IndirectCallExpression
#line 1394 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 4221 "GrammarParser.cpp"
    break;

  case 162: // DirectCallExpression: "this"
#line 1402 "../../obj/src/GrammarParser.y"
  {
      const auto identifier = AST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      const auto identifierPath = IdentifierPath::fromIdentifier( identifier );
      yylhs.value.as < DirectCallExpression::Ptr > () = AST::make< DirectCallExpression >( yylhs.location, identifierPath );
  }
#line 4231 "GrammarParser.cpp"
    break;

  case 163: // DirectCallExpression: IdentifierPath
#line 1408 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = AST::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4239 "GrammarParser.cpp"
    break;

  case 164: // DirectCallExpression: IdentifierPath "(" ")"
#line 1412 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = AST::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = AST::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), arguments, yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4248 "GrammarParser.cpp"
    break;

  case 165: // DirectCallExpression: IdentifierPath "(" Terms ")"
#line 1417 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = AST::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expressions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4256 "GrammarParser.cpp"
    break;

  case 166: // DirectCallExpression: Template IdentifierPath "(" Terms ")"
#line 1421 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = AST::make< DirectCallExpression >( yylhs.location, yystack_[4].value.as < Template::Ptr > (), yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expressions::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4264 "GrammarParser.cpp"
    break;

  case 167: // DirectCallExpression: IdentifierPath "(" error ")"
#line 1425 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 4272 "GrammarParser.cpp"
    break;

  case 168: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier
#line 1433 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = AST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = AST::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 4281 "GrammarParser.cpp"
    break;

  case 169: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" ")"
#line 1438 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = AST::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = AST::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < AST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4292 "GrammarParser.cpp"
    break;

  case 170: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" Terms ")"
#line 1445 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = AST::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < AST::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < AST::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4302 "GrammarParser.cpp"
    break;

  case 171: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" error ")"
#line 1451 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 4310 "GrammarParser.cpp"
    break;

  case 172: // LiteralCallExpression: SimpleOrClaspedTerm "." IntegerLiteral
#line 1459 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = AST::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 4318 "GrammarParser.cpp"
    break;

  case 173: // IndirectCallExpression: CallExpression "(" ")"
#line 1467 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = AST::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = AST::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < AST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4329 "GrammarParser.cpp"
    break;

  case 174: // IndirectCallExpression: CallExpression "(" Terms ")"
#line 1474 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = AST::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < AST::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4339 "GrammarParser.cpp"
    break;

  case 175: // IndirectCallExpression: CallExpression "(" error ")"
#line 1480 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 4347 "GrammarParser.cpp"
    break;

  case 176: // TypeCastingExpression: SimpleOrClaspedTerm "as" Type
#line 1488 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = AST::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > () );
  }
#line 4355 "GrammarParser.cpp"
    break;

  case 177: // LetExpression: "let" VariableBindings "in" Term
#line 1496 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = AST::make< LetExpression >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4363 "GrammarParser.cpp"
    break;

  case 178: // ConditionalExpression: "if" Term "then" Term "else" Term
#line 1504 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = AST::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4371 "GrammarParser.cpp"
    break;

  case 179: // ChooseExpression: "choose" AttributedVariables "in" Term "do" Term
#line 1512 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = AST::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4379 "GrammarParser.cpp"
    break;

  case 180: // UniversalQuantifierExpression: "forall" AttributedVariables "in" Term "holds" Term
#line 1520 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = AST::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4387 "GrammarParser.cpp"
    break;

  case 181: // ExistentialQuantifierExpression: "exists" AttributedVariables "in" Term "with" Term
#line 1528 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = AST::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4395 "GrammarParser.cpp"
    break;

  case 182: // CardinalityExpression: "|" SimpleOrClaspedTerm "|"
#line 1536 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = AST::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4403 "GrammarParser.cpp"
    break;

  case 183: // Literal: UndefinedLiteral
#line 1548 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 4411 "GrammarParser.cpp"
    break;

  case 184: // Literal: BooleanLiteral
#line 1552 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4419 "GrammarParser.cpp"
    break;

  case 185: // Literal: IntegerLiteral
#line 1556 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4427 "GrammarParser.cpp"
    break;

  case 186: // Literal: RationalLiteral
#line 1560 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4435 "GrammarParser.cpp"
    break;

  case 187: // Literal: DecimalLiteral
#line 1564 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4443 "GrammarParser.cpp"
    break;

  case 188: // Literal: BinaryLiteral
#line 1568 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4451 "GrammarParser.cpp"
    break;

  case 189: // Literal: StringLiteral
#line 1572 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4459 "GrammarParser.cpp"
    break;

  case 190: // Literal: ReferenceLiteral
#line 1576 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 4467 "GrammarParser.cpp"
    break;

  case 191: // Literal: ListLiteral
#line 1580 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 4475 "GrammarParser.cpp"
    break;

  case 192: // Literal: RangeLiteral
#line 1584 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 4483 "GrammarParser.cpp"
    break;

  case 193: // Literal: TupleLiteral
#line 1588 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 4491 "GrammarParser.cpp"
    break;

  case 194: // Literal: RecordLiteral
#line 1592 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 4499 "GrammarParser.cpp"
    break;

  case 195: // UndefinedLiteral: "undef"
#line 1600 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = AST::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < AST::Token::Ptr > ()->spans() );
  }
#line 4508 "GrammarParser.cpp"
    break;

  case 196: // BooleanLiteral: "true"
#line 1609 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = AST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < AST::Token::Ptr > ()->spans() );
  }
#line 4518 "GrammarParser.cpp"
    break;

  case 197: // BooleanLiteral: "false"
#line 1615 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = AST::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < AST::Token::Ptr > ()->spans() );
  }
#line 4528 "GrammarParser.cpp"
    break;

  case 198: // IntegerLiteral: "integer"
#line 1625 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4536 "GrammarParser.cpp"
    break;

  case 199: // RationalLiteral: "rational"
#line 1633 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4544 "GrammarParser.cpp"
    break;

  case 200: // DecimalLiteral: "decimal"
#line 1641 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4552 "GrammarParser.cpp"
    break;

  case 201: // BinaryLiteral: "binary"
#line 1649 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4560 "GrammarParser.cpp"
    break;

  case 202: // BinaryLiteral: "hexadecimal"
#line 1653 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4568 "GrammarParser.cpp"
    break;

  case 203: // StringLiteral: "string"
#line 1661 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4576 "GrammarParser.cpp"
    break;

  case 204: // ReferenceLiteral: "@" IdentifierPath
#line 1669 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = AST::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4584 "GrammarParser.cpp"
    break;

  case 205: // ListLiteral: "[" "]"
#line 1677 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = AST::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = AST::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < AST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4595 "GrammarParser.cpp"
    break;

  case 206: // ListLiteral: "[" Terms "]"
#line 1684 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = AST::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < AST::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4605 "GrammarParser.cpp"
    break;

  case 207: // ListLiteral: "[" error "]"
#line 1690 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 4613 "GrammarParser.cpp"
    break;

  case 208: // RangeLiteral: "[" Term ".." Term "]"
#line 1698 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = AST::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4623 "GrammarParser.cpp"
    break;

  case 209: // TupleLiteral: "(" Terms "," Term ")"
#line 1708 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < AST::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = AST::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < AST::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4636 "GrammarParser.cpp"
    break;

  case 210: // RecordLiteral: "{" Assignments "}"
#line 1721 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = AST::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < AST::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4646 "GrammarParser.cpp"
    break;

  case 211: // Assignments: Assignments "," Assignment
#line 1735 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4657 "GrammarParser.cpp"
    break;

  case 212: // Assignments: Assignment
#line 1742 "../../obj/src/GrammarParser.y"
  {
      auto assignments = AST::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4667 "GrammarParser.cpp"
    break;

  case 213: // Assignment: Identifier ":" Term
#line 1751 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = AST::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4675 "GrammarParser.cpp"
    break;

  case 214: // Types: Types "," Type
#line 1763 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4686 "GrammarParser.cpp"
    break;

  case 215: // Types: Type
#line 1770 "../../obj/src/GrammarParser.y"
  {
      auto types = AST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4696 "GrammarParser.cpp"
    break;

  case 216: // Type: BasicType
#line 1779 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::AST::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4704 "GrammarParser.cpp"
    break;

  case 217: // Type: TupleType
#line 1783 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::AST::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4712 "GrammarParser.cpp"
    break;

  case 218: // Type: RecordType
#line 1787 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::AST::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4720 "GrammarParser.cpp"
    break;

  case 219: // Type: TemplateType
#line 1791 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::AST::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4728 "GrammarParser.cpp"
    break;

  case 220: // Type: RelationType
#line 1795 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::AST::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4736 "GrammarParser.cpp"
    break;

  case 221: // Type: FixedSizedType
#line 1799 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::AST::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4744 "GrammarParser.cpp"
    break;

  case 222: // BasicType: IdentifierPath
#line 1807 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = AST::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4752 "GrammarParser.cpp"
    break;

  case 223: // TupleType: "(" Types "," Type ")"
#line 1815 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::AST::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < AST::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::AST::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = AST::make< TupleType >( yylhs.location, yystack_[4].value.as < AST::Token::Ptr > (), subTypes, yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4763 "GrammarParser.cpp"
    break;

  case 224: // RecordType: "{" TypedVariables "," TypedVariable "}"
#line 1826 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < AST::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = AST::make< RecordType >( yylhs.location, yystack_[4].value.as < AST::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4774 "GrammarParser.cpp"
    break;

  case 225: // TemplateType: IdentifierPath "<" Types ">"
#line 1837 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = AST::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4782 "GrammarParser.cpp"
    break;

  case 226: // RelationType: IdentifierPath "<" MaybeFunctionParameters "->" Type ">"
#line 1845 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = AST::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < AST::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4790 "GrammarParser.cpp"
    break;

  case 227: // FixedSizedType: IdentifierPath "'" Term
#line 1853 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = AST::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4798 "GrammarParser.cpp"
    break;

  case 228: // FunctionParameters: FunctionParameters "*" Type
#line 1865 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4809 "GrammarParser.cpp"
    break;

  case 229: // FunctionParameters: Type
#line 1872 "../../obj/src/GrammarParser.y"
  {
      auto types = AST::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4819 "GrammarParser.cpp"
    break;

  case 230: // MaybeFunctionParameters: FunctionParameters
#line 1882 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 4827 "GrammarParser.cpp"
    break;

  case 231: // MaybeFunctionParameters: %empty
#line 1886 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = AST::make< Types >( yylhs.location );
  }
#line 4835 "GrammarParser.cpp"
    break;

  case 232: // MethodParameters: MethodParameters "," TypedAttributedVariable
#line 1894 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4846 "GrammarParser.cpp"
    break;

  case 233: // MethodParameters: "this"
#line 1901 "../../obj/src/GrammarParser.y"
  {
      auto parameters = AST::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto identifier = AST::make< Identifier >( yystack_[0].location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      const auto unresolvedType = AST::make< UnresolvedType >( yylhs.location );
      auto variable = AST::make< VariableDefinition >( yylhs.location, identifier, Token::unresolved(), unresolvedType );
      parameters->add( variable );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4859 "GrammarParser.cpp"
    break;

  case 234: // Parameters: Parameters "," TypedAttributedVariable
#line 1914 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4870 "GrammarParser.cpp"
    break;

  case 235: // Parameters: TypedAttributedVariable
#line 1921 "../../obj/src/GrammarParser.y"
  {
      auto parameters = AST::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4880 "GrammarParser.cpp"
    break;

  case 236: // MaybeDefined: "defined" "{" Term "}"
#line 1935 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = AST::make< Defined >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4888 "GrammarParser.cpp"
    break;

  case 237: // MaybeDefined: %empty
#line 1939 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = AST::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), AST::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 4896 "GrammarParser.cpp"
    break;

  case 238: // MaybeInitially: "=" "{" Initializers "}"
#line 1947 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Initially::Ptr > () = AST::make< Initially >( yylhs.location, yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < AST::Token::Ptr > () );
  }
#line 4904 "GrammarParser.cpp"
    break;

  case 239: // MaybeInitially: %empty
#line 1951 "../../obj/src/GrammarParser.y"
  {
      const auto initializers = AST::make< Initializers >( yylhs.location );
      yylhs.value.as < Initially::Ptr > () = AST::make< Initially >( yylhs.location, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
#line 4913 "GrammarParser.cpp"
    break;

  case 240: // Initializers: Initializers "," Initializer
#line 1960 "../../obj/src/GrammarParser.y"
  {
      auto initializers = yystack_[2].value.as < Initializers::Ptr > ();
      yystack_[0].value.as < Initializer::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4924 "GrammarParser.cpp"
    break;

  case 241: // Initializers: Initializer
#line 1967 "../../obj/src/GrammarParser.y"
  {
      auto initializers = AST::make< Initializers >( yylhs.location );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4934 "GrammarParser.cpp"
    break;

  case 242: // Initializer: Term
#line 1977 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = AST::make< Expressions >( yylhs.location );
      yylhs.value.as < Initializer::Ptr > () = AST::make< Initializer >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 4945 "GrammarParser.cpp"
    break;

  case 243: // Initializer: "(" Term ")" "->" Term
#line 1984 "../../obj/src/GrammarParser.y"
  {
      auto arguments = AST::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > () = AST::make< Initializer >( yylhs.location, yystack_[4].value.as < AST::Token::Ptr > (), arguments, yystack_[2].value.as < AST::Token::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 4957 "GrammarParser.cpp"
    break;

  case 244: // Initializer: TupleLiteral "->" Term
#line 1992 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto lbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto rbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < Initializer::Ptr > () = AST::make< Initializer >( yylhs.location, lbToken, arguments, rbToken, yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 4970 "GrammarParser.cpp"
    break;

  case 245: // Identifier: "identifier"
#line 2009 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 4978 "GrammarParser.cpp"
    break;

  case 246: // Identifier: "in"
#line 2013 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = AST::make< Identifier >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 4987 "GrammarParser.cpp"
    break;

  case 247: // Identifier: "CASM"
#line 2018 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = AST::make< Identifier >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 4996 "GrammarParser.cpp"
    break;

  case 248: // Identifier: "self"
#line 2023 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = AST::make< Identifier >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5005 "GrammarParser.cpp"
    break;

  case 249: // Identifier: "enumeration"
#line 2028 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = AST::make< Identifier >( yylhs.location, yystack_[0].value.as < AST::Token::Ptr > ()->tokenString() );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 5014 "GrammarParser.cpp"
    break;

  case 250: // IdentifierPath: IdentifierPath "::" Identifier
#line 2037 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < AST::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 5025 "GrammarParser.cpp"
    break;

  case 251: // IdentifierPath: Identifier
#line 2044 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = AST::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5033 "GrammarParser.cpp"
    break;

  case 252: // Variable: TypedVariable
#line 2056 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5041 "GrammarParser.cpp"
    break;

  case 253: // Variable: Identifier
#line 2060 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = AST::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = AST::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 5050 "GrammarParser.cpp"
    break;

  case 254: // AttributedVariables: AttributedVariables "," AttributedVariable
#line 2069 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5061 "GrammarParser.cpp"
    break;

  case 255: // AttributedVariables: AttributedVariable
#line 2076 "../../obj/src/GrammarParser.y"
  {
      auto variables = AST::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 5071 "GrammarParser.cpp"
    break;

  case 256: // TypedVariables: TypedVariables "," TypedVariable
#line 2086 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5082 "GrammarParser.cpp"
    break;

  case 257: // TypedVariables: TypedVariable
#line 2093 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = AST::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 5092 "GrammarParser.cpp"
    break;

  case 258: // TypedVariable: Identifier ":" Type
#line 2103 "../../obj/src/GrammarParser.y"
  {
      auto variable = AST::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::AST::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5101 "GrammarParser.cpp"
    break;

  case 259: // AttributedVariable: Attributes Variable
#line 2112 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5111 "GrammarParser.cpp"
    break;

  case 260: // AttributedVariable: Variable
#line 2118 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5119 "GrammarParser.cpp"
    break;

  case 261: // TypedAttributedVariable: Attributes TypedVariable
#line 2126 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 5129 "GrammarParser.cpp"
    break;

  case 262: // TypedAttributedVariable: TypedVariable
#line 2132 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5137 "GrammarParser.cpp"
    break;

  case 263: // TemplateVariables: TemplateVariables "," TemplateVariable
#line 2140 "../../obj/src/GrammarParser.y"
  {
      auto templateVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      templateVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = templateVariables;
  }
#line 5148 "GrammarParser.cpp"
    break;

  case 264: // TemplateVariables: TemplateVariable
#line 2147 "../../obj/src/GrammarParser.y"
  {
      auto templateVariables = AST::make< VariableDefinitions >( yylhs.location );
      templateVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = templateVariables;
  }
#line 5158 "GrammarParser.cpp"
    break;

  case 265: // TemplateVariable: Variable
#line 2157 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 5166 "GrammarParser.cpp"
    break;

  case 266: // VariableBindings: VariableBindings "," VariableBinding
#line 2170 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5177 "GrammarParser.cpp"
    break;

  case 267: // VariableBindings: VariableBinding
#line 2177 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = AST::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5187 "GrammarParser.cpp"
    break;

  case 268: // VariableBinding: AttributedVariable "=" Term
#line 2186 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = AST::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < AST::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5195 "GrammarParser.cpp"
    break;

  case 269: // LocalFunctionDefinitions: LocalFunctionDefinitions "," AttributedLocalFunctionDefinition
#line 2198 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[2].value.as < FunctionDefinitions::Ptr > ();
      yystack_[0].value.as < FunctionDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < AST::Token::Ptr > () );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5206 "GrammarParser.cpp"
    break;

  case 270: // LocalFunctionDefinitions: AttributedLocalFunctionDefinition
#line 2205 "../../obj/src/GrammarParser.y"
  {
      auto definitions = AST::make< FunctionDefinitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5216 "GrammarParser.cpp"
    break;

  case 271: // AttributedLocalFunctionDefinition: Attributes LocalFunctionDefinition
#line 2214 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 5226 "GrammarParser.cpp"
    break;

  case 272: // AttributedLocalFunctionDefinition: LocalFunctionDefinition
#line 2220 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 5234 "GrammarParser.cpp"
    break;

  case 273: // AttributedLocalFunctionDefinition: error
#line 2224 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = nullptr;
  }
#line 5242 "GrammarParser.cpp"
    break;

  case 274: // LocalFunctionDefinition: Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 2231 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = AST::make< FunctionDefinition >( yylhs.location, Token::unresolved(), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < AST::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < AST::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::AST::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > ()->setClassification( FunctionDefinition::Classification::LOCAL );
  }
#line 5251 "GrammarParser.cpp"
    break;

  case 275: // Attributes: Attributes Attribute
#line 2244 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5261 "GrammarParser.cpp"
    break;

  case 276: // Attributes: Attribute
#line 2250 "../../obj/src/GrammarParser.y"
  {
      auto attributes = AST::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5271 "GrammarParser.cpp"
    break;

  case 277: // Attribute: "[" BasicAttribute "]"
#line 2259 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < AST::Token::Ptr > () );
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < AST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5282 "GrammarParser.cpp"
    break;

  case 278: // Attribute: "[" ExpressionAttribute "]"
#line 2266 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < AST::Token::Ptr > () );
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < AST::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5293 "GrammarParser.cpp"
    break;

  case 279: // Attribute: "[" error "]"
#line 2273 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 5301 "GrammarParser.cpp"
    break;

  case 280: // BasicAttribute: Identifier
#line 2280 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = AST::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5309 "GrammarParser.cpp"
    break;

  case 281: // ExpressionAttribute: Identifier Term
#line 2287 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = AST::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5317 "GrammarParser.cpp"
    break;


#line 5321 "GrammarParser.cpp"

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


  const short Parser::yypact_ninf_ = -464;

  const short Parser::yytable_ninf_ = -230;

  const short
  Parser::yypact_[] =
  {
      14,  -464,    48,    68,  2490,    33,  -464,    -7,  -464,  -464,
    -464,  -464,  -464,  2270,    38,    41,  -464,  -464,   132,   232,
     232,   232,   232,   232,   232,   160,   232,  2462,  -464,  -464,
    -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,
    -464,  -464,   337,  -464,  -464,  -464,   312,  -464,  -464,  -464,
    -464,   139,   139,   139,  2270,   139,  -464,  -464,  -464,  2270,
    2399,  2399,  1740,  1432,   232,  2399,   232,  -464,  -464,  -464,
    -464,  -464,  -464,   232,  3139,    43,  -464,    71,  -464,  -464,
    -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,
    -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,
    -464,  -464,  -464,   131,  -464,  -464,  2335,    83,   -24,   134,
     122,   145,   192,   202,    78,   232,   217,  -464,   232,    64,
      64,    64,   232,  -464,   220,  -464,  -464,   226,    -9,  -464,
     139,    42,  -464,   119,  2676,   129,  -464,  -464,  -464,   245,
     236,  2894,   256,  -464,   121,  2929,   246,  -464,   265,    60,
      83,   195,  2270,  2270,  2270,  2270,  2270,  2270,  2270,  2270,
    2270,  2270,  2270,  2270,  2270,  2270,  2270,  2270,  2270,    64,
     150,  1509,  1586,   232,  1740,  3139,   259,   295,  -464,    15,
      64,   277,  2140,    59,    64,    64,   219,  2270,   232,  -464,
      63,  -464,    64,   283,    64,   232,   290,  -464,  -464,  -464,
    -464,  -464,  -464,   -34,    50,  -464,  -464,   237,    64,  2270,
    2270,   139,  -464,  2270,   139,  2270,  2270,  2270,  -464,  2270,
    -464,  -464,  -464,  2270,  2270,  -464,   232,  2270,  -464,  2270,
     271,  3174,  3204,   448,   313,   313,   482,   221,   221,   273,
     273,   273,  -464,   448,   482,   221,   221,  -464,  -464,   291,
     306,  -464,   186,  3139,   308,  -464,   187,  -464,  2964,  2270,
    -464,  2335,   309,  -464,   216,   229,   220,  -464,  -464,   139,
     317,    32,   997,  1121,  -464,   139,    79,   139,   139,  2140,
    2270,  2270,  2270,  1199,  1277,  -464,  -464,  -464,  -464,  -464,
    -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,   292,
      88,   301,   303,   322,   230,   231,   332,  -464,  -464,  3139,
    -464,   232,  -464,  -464,   318,   314,   335,   323,  -464,   325,
    -464,   339,    64,  2270,    64,   341,    64,  -464,  3139,  3139,
    -464,  2824,  -464,  2514,  2753,  2859,  2999,  3139,  3034,  -464,
    3139,   242,  1663,  -464,  -464,  -464,  -464,   327,  3139,  -464,
     328,   329,   139,   331,   139,  -464,  2270,  -464,  -464,   297,
    -464,   139,   379,  1817,  -464,   385,  1895,   162,  -464,   349,
     164,  -464,  -464,   139,   172,   175,  -464,  2715,  2789,  2555,
     353,  1973,   265,   334,  2051,  2270,  2270,    56,   118,   126,
    2140,  -464,    64,    64,   111,    64,   232,    52,   116,   208,
     338,  -464,   364,    76,  2270,  2270,  2270,  2270,  -464,  -464,
    -464,   363,  -464,   244,  2270,    64,    64,  -464,    64,  -464,
    3139,  -464,    32,  -464,  -464,  -464,  -464,  -464,  -464,  2140,
      64,  2140,    79,  -464,  2270,  2270,  2140,   361,  2140,  -464,
    -464,  -464,  -464,  3139,  3139,  2140,    64,  2140,    64,  2140,
      64,  -464,  -464,   402,  -464,   102,  -464,   111,   367,   365,
     232,   232,  -464,  -464,  -464,    34,  -464,    52,    64,  -464,
      64,   369,  -464,  -464,    82,  -464,  -464,    76,  3139,  3139,
    3139,  3139,  -464,  -464,  3139,   370,   372,   376,  -464,  -464,
     356,  -464,  -464,  2473,  2596,   398,  1355,  -464,  -464,   380,
    -464,   381,  -464,   382,   383,   387,  -464,  -464,  -464,  -464,
    -464,   190,   194,  -464,  -464,  -464,  -464,  -464,  -464,   371,
      76,  -464,  -464,  -464,  2270,  2270,  2270,    64,  2140,  2270,
    2140,  2140,   384,   386,   392,  2205,  -464,  3069,  2140,  2140,
    2140,  2270,   389,  -464,    64,    64,  -464,    91,  3139,  3139,
    3139,   402,  -464,  2637,  -464,  -464,  -464,  2140,  2140,  -464,
    -464,  2140,  -464,  -464,  -464,  3104,  2335,   378,   391,  -464,
     387,  2140,  -464,  -464,  -464,  -464,   300,    64,    64,  -464,
    -464,  -464,  -464,  -464
  };

  const short
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   276,     0,   247,   249,
     248,   246,   245,   280,     0,     0,     1,     9,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     6,     8,
      10,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    66,     0,    21,    22,    23,    67,     3,   275,   279,
     162,     0,     0,     0,     0,     0,   195,   197,   196,     0,
       0,     0,     0,     0,     0,     0,     0,   201,   202,   198,
     199,   200,   203,     0,   281,   125,   127,   136,   159,   160,
     137,   161,   126,   128,   129,   130,   131,   132,   133,   138,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,   194,   251,   163,   277,   278,     0,    24,     0,     0,
       0,   251,    46,     0,    49,     0,     0,     5,     0,     0,
       0,     0,     0,     7,   253,   260,   252,     0,     0,   267,
       0,     0,   255,     0,     0,     0,   158,   139,   140,     0,
       0,   124,     0,   205,     0,   124,     0,   212,     0,     0,
     204,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   242,   193,     0,   241,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   265,
       0,   264,   231,     0,     0,     0,     0,   216,   217,   218,
     219,   220,   221,   222,     0,    76,    77,     0,     0,     0,
       0,     0,   259,     0,     0,     0,     0,     0,   135,     0,
     134,   207,   206,     0,     0,   210,     0,     0,   182,     0,
     155,   153,   154,   157,   141,   142,   148,   149,   150,   143,
     144,   145,   146,   156,   147,   151,   152,   176,   172,   168,
       0,   173,     0,   124,     0,   164,     0,   250,   124,     0,
      25,     0,     0,   233,     0,     0,     0,   262,   235,     0,
       0,     0,     0,     0,    95,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    31,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
     121,   159,   160,     0,     0,     0,     0,    45,    47,    48,
      50,     0,    65,   229,   230,     0,     0,     0,   215,     0,
     257,     0,   231,     0,     0,     0,   231,   258,   268,   177,
     266,     0,   254,     0,     0,     0,   123,   123,     0,   211,
     213,     0,     0,   175,   174,   167,   165,   134,   244,   240,
       0,     0,     0,     0,     0,   261,     0,    42,    44,     0,
      40,     0,     0,     0,    81,     0,     0,     0,   273,     0,
       0,   270,   272,     0,     0,     0,   110,     0,     0,     0,
       0,     0,   251,     0,     0,     0,     0,     0,     0,     0,
       0,   263,     0,     0,     0,     0,     0,     0,     0,   215,
       0,   227,     0,     0,     0,     0,     0,     0,   209,   208,
     166,     0,   169,     0,     0,     0,     0,   232,     0,   234,
      27,    26,     0,    41,   118,   116,    80,   114,   112,     0,
     231,     0,     0,   271,     0,     0,     0,     0,     0,   113,
     111,   117,   115,   119,   120,     0,     0,     0,     0,     0,
       0,    32,   228,   237,    55,     0,    53,     0,   214,   256,
       0,     0,    60,    62,    64,     0,    58,     0,     0,   225,
       0,     0,    74,    75,     0,    71,    73,     0,   180,   179,
     178,   181,   171,   170,   243,     0,     0,     0,    43,   105,
       0,   106,   269,     0,     0,    96,     0,   122,    37,     0,
      35,     0,    33,     0,     0,   239,    51,    52,    54,   223,
     224,     0,     0,    56,    63,    59,    61,    57,   214,     0,
       0,    68,    70,    72,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,     0,     0,     0,
       0,     0,     0,    39,   231,   231,   226,     0,    30,    29,
      28,   237,   107,     0,   109,    97,    99,     0,     0,    98,
     100,     0,    38,    36,    34,     0,     0,     0,     0,    69,
     239,     0,   102,   103,   104,   236,     0,     0,     0,   274,
     108,   238,    78,    79
  };

  const short
  Parser::yypgoto_[] =
  {
    -464,  -464,  -464,  -464,   417,   400,  -464,  -464,    -1,    10,
    -379,    25,  -464,  -464,  -464,  -464,  -464,  -464,  -464,     1,
    -464,     0,  -464,    23,  -464,  -464,   -59,  -463,    -8,  -464,
    -464,     3,  -155,   330,  -464,  -464,  -464,  -464,   -56,  -464,
    -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,   -58,
      53,   199,  -464,   388,   539,   573,  -464,  -464,  -464,  -464,
    -464,  -464,  -464,  -464,  -464,  -464,  -464,  -464,   310,  -464,
    -464,  -464,  -464,  -464,  -464,  -464,  -104,  -464,  -464,   250,
     159,   209,  -464,  -464,  -464,  -464,   368,  -464,  -464,  -185,
     302,   311,   -65,   -81,   -75,   234,   521,   -18,   -87,   -45,
    -464,  -170,   -39,  -330,  -464,   181,   224,   289,  -464,    72,
     133,    19,    -4,  -464,  -464
  };

  const short
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    27,    28,    29,    30,    31,   472,   473,
      34,   358,   359,    35,    36,    37,    38,    39,   455,   456,
      40,   464,   465,    73,    42,    43,   474,   475,   476,    44,
      45,   466,   363,   364,   286,   287,   288,   535,   536,   289,
     290,   291,   292,   293,   294,   295,   296,   297,   298,   140,
     253,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   146,   147,
     317,   313,   197,   198,   199,   200,   201,   202,   314,   400,
     264,   265,   505,   543,   177,   178,   102,   103,   125,   131,
     319,   126,   132,   268,   190,   191,   128,   129,   370,   371,
     372,   130,     6,    14,    15
  };

  const short
  Parser::yytable_[] =
  {
     107,    48,   176,    32,   112,   144,   114,   315,   133,   267,
     135,   522,   127,   267,    33,   454,   262,     1,     8,     5,
     210,     9,   417,    46,   419,   320,    32,    41,   189,   173,
      10,   263,   179,   357,   322,     8,    47,    33,     9,   460,
     323,   461,    48,   212,    11,    32,    46,    10,   150,     7,
      41,     8,    49,   180,     9,   151,    33,   460,   211,   461,
     303,    11,     8,    10,   324,     9,    74,     8,    16,    41,
       9,   213,     2,     2,    10,   263,   454,    11,   508,    10,
     368,    19,     8,    21,   522,     9,   169,    19,    11,    21,
       2,     2,     2,    11,    10,   513,    19,   104,    21,   355,
     105,   203,   203,   203,   207,   325,    12,   134,    11,   214,
       2,   445,   136,   252,   256,   141,   145,     2,   366,   170,
     194,   188,    26,    12,   195,   228,    48,   171,   381,   384,
     311,    26,   312,   446,     2,     8,   170,     2,     9,    12,
       2,   173,     8,   521,   171,     9,   173,    10,   215,     2,
      12,   203,   569,     8,    10,    12,     9,   176,   217,   175,
       2,    11,   203,   506,  -136,    10,   203,   203,    11,     2,
      12,   341,   127,   447,   203,   332,   203,   182,   183,    11,
     222,   449,   267,   468,   267,   469,   214,   172,   223,   181,
     203,   429,   106,   431,   173,   448,   214,     2,   269,   184,
     185,   434,   269,   450,   435,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,     8,    12,   189,     9,   459,   258,   115,   211,
      12,   432,   374,   375,    10,     8,   127,    69,     9,   214,
     309,    12,   214,   344,   346,   490,   179,    10,    11,   182,
     183,   229,   544,   223,   223,   186,   545,   187,   173,   137,
     138,    11,   328,   329,   149,    48,   331,   180,   333,   334,
     335,   184,   336,   351,   156,   157,   337,   338,  -229,   192,
     340,   209,   208,   352,   413,  -229,   353,   388,   389,   308,
     361,   161,   162,   163,   164,   373,   354,   352,   354,   410,
     173,   483,   218,   219,   203,   326,   203,   225,   203,   223,
      12,   223,   348,   226,   175,   221,    18,    19,    20,    21,
      22,    23,    24,    12,   156,   157,   158,   227,   196,   204,
     205,    25,    26,   377,   378,   379,   259,   271,   316,   159,
     160,   161,   162,   163,   164,   321,   164,   342,   118,   119,
     120,   166,   167,   168,   121,   122,   260,    48,   421,   567,
     568,   581,   261,   343,   422,   345,   350,   261,   170,    48,
       2,   269,   356,   269,   203,   203,   401,   203,   247,   387,
     385,   299,   386,   161,   162,   163,   164,   390,   392,   270,
     395,   393,   396,   306,   307,   394,   462,   203,   203,   397,
     203,   403,   424,   318,   414,   415,   416,   463,   418,   420,
     427,   430,   203,   457,   439,   470,   467,   327,   441,   471,
     482,   496,   477,   504,   509,   524,   510,   525,   203,   520,
     203,   526,   203,   527,   531,   538,   539,   540,   443,   444,
     546,   361,   542,   541,   117,   556,   123,   488,   557,   566,
     203,   373,   203,    48,   558,   577,   507,   478,   479,   480,
     481,   547,   176,    48,   462,   514,   515,   484,   578,   523,
     517,   299,   299,    48,   457,   463,   339,   516,   299,   560,
     248,   398,   299,   299,   467,   304,   570,   493,   494,   579,
     206,   576,   391,   477,   305,   349,   152,   153,   154,   367,
     330,   156,   157,   158,   492,     0,   433,     0,     0,   203,
       0,     0,   285,     0,     0,     0,   159,   160,   161,   162,
     163,   164,     0,    13,     0,     0,   203,   203,   166,   167,
     168,   399,     0,   402,     0,   156,   157,     0,     0,   477,
     108,   109,   110,   111,   113,     0,     0,   116,     0,   537,
     159,   160,   161,   162,   163,   164,     0,     0,     0,   203,
     203,     0,   299,   167,   168,   299,   477,     0,     0,     0,
     300,     0,   124,   124,   124,     0,   124,   548,   549,   550,
     299,     0,   553,   299,     0,   148,     0,     0,   537,   299,
       0,     0,     0,     0,   565,     0,     0,     0,     0,     0,
       0,   452,   453,     0,   458,     0,     0,     0,     0,   376,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   175,
       0,     0,     0,     0,   485,   486,     0,   487,   299,     0,
     299,     0,     0,     0,     0,   299,   124,   299,     0,   193,
       0,     0,     0,     0,   299,     0,   299,     0,   299,     0,
       0,   124,     0,     0,     0,   499,     0,   501,     0,   503,
     300,   300,     0,     0,     0,     0,     0,   300,     0,     0,
       0,   300,   300,     0,     0,     0,     0,   518,     0,   519,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   249,     0,   426,   257,     0,   426,     0,     0,     0,
     266,     0,     0,     0,   266,     0,     0,   257,     0,   310,
       0,   426,     0,     0,   426,     0,   266,     0,     0,     0,
     451,   301,     0,     0,     0,     0,     0,   299,     0,   299,
     299,     0,   124,     0,     0,   124,   551,   299,   299,   299,
       0,     0,     0,     0,     0,     0,     0,   148,     0,     0,
       0,   300,     0,     0,   300,   302,   299,   299,     0,   489,
     299,   491,     0,     0,     0,     0,   495,     0,   497,   300,
     299,     0,   300,     0,     0,   498,     0,   500,   300,   502,
       0,     0,     0,     0,     0,     0,   582,   583,     0,     0,
     266,     0,   360,     0,     0,     0,   124,   369,   124,   124,
       0,     0,     0,     0,   382,     0,     0,     0,     0,     0,
       0,   301,   301,     0,     0,     0,     0,   300,   301,   300,
       0,     0,   301,   301,   300,     0,   300,     0,     0,     0,
       0,     0,   124,   300,     0,   300,     0,   300,     0,     0,
       0,     0,     0,     0,     0,   302,   302,     0,     0,     0,
       0,     0,   302,     0,     0,     0,   302,   302,   552,     0,
     554,   555,     0,     0,     0,     0,     0,     0,   562,   563,
     564,     0,     0,   266,     0,   266,     0,     0,     0,     0,
       0,     0,   423,     0,     0,     0,     0,   572,   573,     0,
       0,   574,     0,     0,   369,     0,     0,     0,     0,     0,
       0,   580,   301,     0,     0,   301,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   300,   266,   300,   300,
     301,     0,     0,   301,     0,     0,   300,   300,   300,   301,
       0,     0,     0,     0,     0,     0,   302,     0,     0,   302,
       0,     0,     0,   360,     0,   300,   300,     0,     0,   300,
       0,     0,     0,   369,   302,     0,     0,   302,     0,   300,
       0,     0,     0,   302,     0,     0,     0,     0,   301,     0,
     301,     0,     0,     0,     0,   301,     0,   301,     0,     0,
       0,   511,   512,     0,   301,     0,   301,     0,   301,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   362,     0,
       8,     0,   302,     9,   302,     0,     0,     0,     0,   302,
       0,   302,    10,    50,     0,     0,    25,     0,   302,   272,
     302,   273,   302,   274,   275,   276,    11,   277,   278,   279,
       0,   280,     0,     0,   281,     0,     0,     0,     0,     0,
       0,   282,    56,    57,    58,     0,     0,     0,     0,     0,
      60,    61,     0,    62,     0,    63,     0,   283,     0,     0,
       0,     0,     0,    66,     0,     0,     0,   301,     0,   301,
     301,     0,     0,     0,     0,     0,     0,   301,   301,   301,
     284,     0,    67,    68,    69,    70,    71,    72,    12,     0,
       0,     0,     0,     0,     0,     0,   301,   301,     0,     0,
     301,   302,     0,   302,   302,     0,     0,     0,     0,     0,
     301,   302,   302,   302,     0,     0,     0,     0,     0,     0,
       0,     0,   365,     0,     8,     0,     0,     9,     0,     0,
     302,   302,     0,     0,   302,     0,    10,    50,     0,     0,
      25,     0,     0,   272,   302,   273,     0,   274,   275,   276,
      11,   277,   278,   279,     0,   280,     0,     0,   281,     0,
       0,     0,     0,     0,     0,   282,    56,    57,    58,     0,
       0,     0,     0,     0,    60,    61,     0,    62,     0,    63,
       0,   283,     0,     0,     0,     0,     0,    66,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     380,     0,     8,     0,   284,     9,    67,    68,    69,    70,
      71,    72,    12,     0,    10,    50,     0,     0,    25,     0,
       0,   272,     0,   273,     0,   274,   275,   276,    11,   277,
     278,   279,     0,   280,     0,     0,   281,     0,     0,     0,
       0,     0,     0,   282,    56,    57,    58,     0,     0,     0,
       0,     0,    60,    61,     0,    62,     0,    63,     0,   283,
       0,     0,     0,     0,     0,    66,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   383,     0,
       8,     0,   284,     9,    67,    68,    69,    70,    71,    72,
      12,     0,    10,    50,     0,     0,    25,     0,     0,   272,
       0,   273,     0,   274,   275,   276,    11,   277,   278,   279,
       0,   280,     0,     0,   281,     0,     0,     0,     0,     0,
       0,   282,    56,    57,    58,     0,     0,     0,     0,     0,
      60,    61,     0,    62,     0,    63,     0,   283,     0,     0,
       0,     0,     0,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   532,     0,     8,     0,
     284,     9,    67,    68,    69,    70,    71,    72,    12,     0,
      10,    50,     0,     0,    25,     0,     0,     0,     0,     0,
       0,     0,    51,     0,    11,    52,    53,     0,     0,    54,
       0,     0,     0,     0,   533,     0,    55,     0,     0,     0,
      56,    57,    58,     0,     0,     0,     0,    59,    60,    61,
       0,    62,     0,    63,     0,    64,     0,     0,     0,   534,
      65,    66,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   142,     0,     8,     0,     0,     9,     0,
      67,    68,    69,    70,    71,    72,    12,    10,    50,     0,
       0,    25,     0,     0,     0,     0,     0,     0,     0,    51,
       0,    11,    52,    53,     0,     0,    54,     0,     0,     0,
       0,     0,     0,    55,     0,     0,     0,    56,    57,    58,
       0,     0,     0,     0,    59,    60,    61,     0,    62,     0,
      63,   143,    64,     0,     0,     0,     0,    65,    66,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     250,     0,     8,     0,     0,     9,     0,    67,    68,    69,
      70,    71,    72,    12,    10,    50,     0,     0,    25,     0,
       0,     0,     0,     0,     0,     0,    51,     0,    11,    52,
      53,     0,     0,    54,     0,     0,     0,     0,     0,     0,
      55,     0,     0,     0,    56,    57,    58,     0,     0,     0,
       0,    59,    60,    61,     0,    62,   251,    63,     0,    64,
       0,     0,     0,     0,    65,    66,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   254,     0,     8,
       0,     0,     9,     0,    67,    68,    69,    70,    71,    72,
      12,    10,    50,     0,     0,    25,     0,     0,     0,     0,
       0,     0,     0,    51,     0,    11,    52,    53,     0,     0,
      54,     0,     0,     0,     0,     0,     0,    55,     0,     0,
       0,    56,    57,    58,     0,     0,     0,     0,    59,    60,
      61,     0,    62,   255,    63,     0,    64,     0,     0,     0,
       0,    65,    66,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   411,     0,     8,     0,     0,     9,
       0,    67,    68,    69,    70,    71,    72,    12,    10,    50,
       0,     0,    25,     0,     0,     0,     0,     0,     0,     0,
      51,     0,    11,    52,    53,     0,     0,    54,     0,     0,
       0,     0,     0,     0,    55,     0,     0,     0,    56,    57,
      58,     0,     0,     0,     0,    59,    60,    61,     0,    62,
     412,    63,     0,    64,     0,     0,     0,     0,    65,    66,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   139,     0,     8,     0,     0,     9,     0,    67,    68,
      69,    70,    71,    72,    12,    10,    50,     0,     0,    25,
       0,     0,     0,     0,     0,     0,     0,    51,     0,    11,
      52,    53,     0,     0,    54,     0,     0,     0,     0,     0,
       0,    55,     0,     0,     0,    56,    57,    58,     0,     0,
       0,     0,    59,    60,    61,     0,    62,     0,    63,     0,
      64,     0,     0,     0,     0,    65,    66,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       8,     0,     0,     9,     0,    67,    68,    69,    70,    71,
      72,    12,    10,    50,     0,     0,    25,     0,     0,   272,
     425,   273,     0,   274,   275,   276,    11,   277,   278,   279,
       0,   280,     0,     0,   281,     0,     0,     0,     0,     0,
       0,   282,    56,    57,    58,     0,     0,     0,     0,     0,
      60,    61,     0,    62,     0,    63,     0,   283,     0,     0,
       0,     0,     0,    66,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     8,     0,
     284,     9,    67,    68,    69,    70,    71,    72,    12,     0,
      10,    50,     0,     0,    25,     0,     0,   272,     0,   273,
     428,   274,   275,   276,    11,   277,   278,   279,     0,   280,
       0,     0,   281,     0,     0,     0,     0,     0,     0,   282,
      56,    57,    58,     0,     0,     0,     0,     0,    60,    61,
       0,    62,     0,    63,     0,   283,     0,     0,     0,     0,
       0,    66,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     8,     0,   284,     9,
      67,    68,    69,    70,    71,    72,    12,     0,    10,    50,
       0,     0,    25,     0,     0,   272,     0,   273,     0,   274,
     275,   276,    11,   277,   278,   279,     0,   280,     0,     0,
     281,     0,     0,     0,     0,     0,     0,   282,    56,    57,
      58,     0,     0,     0,     0,     0,    60,    61,     0,    62,
       0,    63,     0,   283,   440,     0,     0,     0,     0,    66,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     0,   284,     9,    67,    68,
      69,    70,    71,    72,    12,     0,    10,    50,     0,     0,
      25,     0,     0,   272,     0,   273,     0,   274,   275,   276,
      11,   277,   278,   279,     0,   280,     0,     0,   281,     0,
       0,     0,     0,     0,     0,   282,    56,    57,    58,     0,
       0,     0,     0,     0,    60,    61,     0,    62,     0,    63,
       0,   283,     0,     0,     0,     0,     0,    66,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   284,   442,    67,    68,    69,    70,
      71,    72,    12,     8,     0,     0,     9,     0,     0,     0,
       0,     0,     0,     0,     0,    10,    50,     0,     0,    25,
       0,     0,   272,     0,   273,     0,   274,   275,   276,    11,
     277,   278,   279,     0,   280,     0,     0,   281,     0,     0,
       0,     0,     0,     0,   282,    56,    57,    58,     0,     0,
       0,     0,     0,    60,    61,     0,    62,     0,    63,     0,
     283,     0,     0,     0,     0,     0,    66,     0,     8,     0,
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
      10,    50,     0,   284,    25,    67,    68,    69,    70,    71,
      72,    12,    51,     0,    11,    52,    53,     0,     0,    54,
       0,     0,     0,     0,   533,     0,    55,     0,     0,     0,
      56,    57,    58,     0,     0,     0,     0,    59,    60,    61,
       0,    62,     0,    63,     0,    64,   559,     0,     0,   534,
      65,    66,     0,     8,     0,     0,     9,     0,     0,     0,
       0,     0,     0,     0,     0,    10,    50,     0,     0,    25,
      67,    68,    69,    70,    71,    72,    12,    51,     0,    11,
      52,    53,     0,     0,    54,     0,     0,     0,     0,     0,
       0,    55,     0,     0,     0,    56,    57,    58,     0,     0,
       0,     0,    59,    60,    61,     0,    62,     0,    63,     0,
      64,     0,     0,     0,     0,    65,    66,     0,     8,     0,
       0,     9,     0,     0,     0,     0,     0,     0,     0,     0,
      10,    50,     0,     0,    25,    67,    68,    69,    70,    71,
      72,    12,    51,     0,    11,    52,    53,     0,     0,    54,
       0,     0,     0,     0,     0,     0,    55,     0,     0,     0,
      56,    57,    58,     0,     0,     0,     0,    59,    60,    61,
       0,   174,     0,    63,     0,    64,     0,     0,     0,     0,
      65,    66,     8,     0,     0,     9,     0,     0,     0,     0,
       0,     0,     0,     0,    10,    50,     0,     0,    25,     0,
      67,    68,    69,    70,    71,    72,    12,     0,    11,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    56,    57,    58,     0,     0,     0,
       0,     0,    60,    61,     0,    62,     0,    63,     0,    64,
       0,     0,    -2,    17,     0,    66,    18,    19,    20,    21,
      22,    23,    24,   -67,   -67,   -67,     0,     0,     0,   -67,
     -67,    25,    26,     0,    67,    68,    69,    70,    71,    72,
      12,    17,     0,     0,    18,    19,    20,    21,    22,    23,
      24,   -67,   -67,   -67,     0,     0,   528,   -67,   -67,    25,
      26,     0,     0,     0,     0,   529,     0,     0,     0,     0,
       2,   152,   153,   154,   155,     0,   156,   157,   158,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,   160,   161,   162,   163,   164,   405,     2,     0,
       0,   165,     0,   166,   167,   168,     0,     0,     0,     0,
       0,     0,   152,   153,   154,   155,     0,   156,   157,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,   160,   161,   162,   163,   164,   438,     0,
       0,     0,   165,     0,   166,   167,   168,     0,     0,     0,
       0,     0,     0,   152,   153,   154,   155,     0,   156,   157,
     158,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159,   160,   161,   162,   163,   164,   530,
       0,     0,     0,   165,     0,   166,   167,   168,     0,     0,
       0,     0,     0,     0,   152,   153,   154,   155,     0,   156,
     157,   158,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159,   160,   161,   162,   163,   164,
     571,     0,     0,     0,   165,     0,   166,   167,   168,     0,
       0,     0,     0,     0,     0,   152,   153,   154,   155,     0,
     156,   157,   158,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   159,   160,   161,   162,   163,
     164,   216,     0,     0,     0,   165,     0,   166,   167,   168,
       0,     0,     0,     0,   152,   153,   154,   155,     0,   156,
     157,   158,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   159,   160,   161,   162,   163,   164,
     436,     0,     0,     0,   165,     0,   166,   167,   168,     0,
       0,     0,     0,   152,   153,   154,   155,     0,   156,   157,
     158,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   159,   160,   161,   162,   163,   164,   406,
       0,     0,     0,   165,     0,   166,   167,   168,     0,     0,
       0,   152,   153,   154,   155,     0,   156,   157,   158,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   159,   160,   161,   162,   163,   164,   437,     0,     0,
       0,   165,     0,   166,   167,   168,     0,   152,   153,   154,
     155,     0,   156,   157,   158,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   159,   160,   161,
     162,   163,   164,     0,   404,     0,     0,   165,     0,   166,
     167,   168,   152,   153,   154,   155,     0,   156,   157,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,   160,   161,   162,   163,   164,     0,     0,
       0,   407,   165,     0,   166,   167,   168,   152,   153,   154,
     155,     0,   156,   157,   158,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   159,   160,   161,
     162,   163,   164,     0,     0,     0,     0,   165,     0,   166,
     167,   168,   152,   153,   154,   155,     0,   156,   157,   158,
       0,   220,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,   160,   161,   162,   163,   164,     0,     0,
       0,     0,   165,     0,   166,   167,   168,   152,   153,   154,
     155,     0,   156,   157,   158,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   159,   160,   161,
     162,   163,   164,     0,   224,     0,     0,   165,     0,   166,
     167,   168,   152,   153,   154,   155,     0,   156,   157,   158,
       0,   347,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,   160,   161,   162,   163,   164,     0,     0,
       0,     0,   165,     0,   166,   167,   168,   152,   153,   154,
     155,     0,   156,   157,   158,     0,   408,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   159,   160,   161,
     162,   163,   164,     0,     0,     0,     0,   165,     0,   166,
     167,   168,   152,   153,   154,   155,     0,   156,   157,   158,
       0,     0,     0,   409,     0,     0,     0,     0,     0,     0,
       0,     0,   159,   160,   161,   162,   163,   164,     0,     0,
       0,     0,   165,     0,   166,   167,   168,   152,   153,   154,
     155,     0,   156,   157,   158,     0,     0,     0,     0,     0,
       0,   561,     0,     0,     0,     0,     0,   159,   160,   161,
     162,   163,   164,     0,     0,     0,     0,   165,     0,   166,
     167,   168,   152,   153,   154,   155,     0,   156,   157,   158,
       0,     0,     0,     0,     0,   575,     0,     0,     0,     0,
       0,     0,   159,   160,   161,   162,   163,   164,     0,     0,
       0,     0,   165,     0,   166,   167,   168,   152,   153,   154,
     155,     0,   156,   157,   158,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   159,   160,   161,
     162,   163,   164,     0,     0,     0,     0,   165,     0,   166,
     167,   168,   152,     0,   154,     0,     0,   156,   157,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,   160,   161,   162,   163,   164,     0,     0,
       0,     0,   152,     0,   166,   167,   168,   156,   157,   158,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   159,   160,   161,   162,   163,   164,     0,     0,
       0,     0,     0,     0,   166,   167,   168
  };

  const short
  Parser::yycheck_[] =
  {
      18,     5,   106,     4,    22,    63,    24,   192,    53,   179,
      55,   474,    51,   183,     4,   394,     1,     3,     3,     0,
      29,     6,   352,     4,   354,   195,    27,     4,   115,    63,
      15,    16,    56,     1,    68,     3,     3,    27,     6,     5,
      74,     7,    46,   130,    29,    46,    27,    15,    66,     1,
      27,     3,    59,    77,     6,    73,    46,     5,    67,     7,
       1,    29,     3,    15,    14,     6,    13,     3,     0,    46,
       6,    29,    58,    58,    15,    16,   455,    29,   457,    15,
       1,     5,     3,     7,   547,     6,    43,     5,    29,     7,
      58,    58,    58,    29,    15,    61,     5,    59,     7,   269,
      59,   119,   120,   121,   122,    55,    91,    54,    29,    67,
      58,    55,    59,   171,   172,    62,    63,    58,   273,    76,
      56,    43,    20,    91,    60,    65,   130,    56,   283,   284,
      67,    20,    69,    77,    58,     3,    76,    58,     6,    91,
      58,    63,     3,    61,    56,     6,    63,    15,    29,    58,
      91,   169,    61,     3,    15,    91,     6,   261,    29,   106,
      58,    29,   180,    61,    76,    15,   184,   185,    29,    58,
      91,   229,   211,    55,   192,   214,   194,    55,    56,    29,
      59,    55,   352,    67,   354,    69,    67,    56,    67,    55,
     208,    29,    60,    29,    63,    77,    67,    58,   179,    77,
      55,    29,   183,    77,    29,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
     167,   168,     3,    91,   311,     6,   396,   174,    68,    67,
      91,    67,   277,   278,    15,     3,   275,    87,     6,    67,
     187,    91,    67,    57,    57,   430,    56,    15,    29,    55,
      56,    56,    62,    67,    67,    63,    62,    55,    63,    60,
      61,    29,   209,   210,    65,   269,   213,    77,   215,   216,
     217,    77,   219,    57,    53,    54,   223,   224,    70,    62,
     227,    55,    62,    67,   342,    77,    57,    57,    57,    70,
     271,    70,    71,    72,    73,   276,    67,    67,    67,    57,
      63,    57,    57,    67,   322,    68,   324,    61,   326,    67,
      91,    67,   259,    67,   261,    59,     4,     5,     6,     7,
       8,     9,    10,    91,    53,    54,    55,    62,   119,   120,
     121,    19,    20,   280,   281,   282,    77,    60,    55,    68,
      69,    70,    71,    72,    73,    55,    73,    56,    11,    12,
      13,    80,    81,    82,    17,    18,    61,   361,    61,   544,
     545,    61,    67,    57,    67,    57,    57,    67,    76,   373,
      58,   352,    55,   354,   392,   393,   323,   395,   169,    57,
      79,   182,    79,    70,    71,    72,    73,    55,    70,   180,
      67,    77,    67,   184,   185,    60,   397,   415,   416,    60,
     418,    60,    23,   194,    77,    77,    77,   397,    77,   356,
      25,    62,   430,   394,    61,    77,   397,   208,    84,    55,
      57,    60,   403,    21,    57,    55,    61,    55,   446,    60,
     448,    55,   450,    77,    36,    55,    55,    55,   385,   386,
      69,   422,    55,    60,    27,    61,    46,   422,    62,    60,
     468,   432,   470,   457,    62,    77,   455,   404,   405,   406,
     407,   520,   566,   467,   465,   465,   467,   414,    77,   477,
     467,   272,   273,   477,   455,   465,   226,   467,   279,   535,
     170,   322,   283,   284,   465,   183,   551,   434,   435,   570,
     122,   566,   311,   474,   183,   261,    48,    49,    50,   275,
     211,    53,    54,    55,   432,    -1,   373,    -1,    -1,   527,
      -1,    -1,   182,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    -1,     2,    -1,    -1,   544,   545,    80,    81,
      82,   322,    -1,   324,    -1,    53,    54,    -1,    -1,   520,
      19,    20,    21,    22,    23,    -1,    -1,    26,    -1,   496,
      68,    69,    70,    71,    72,    73,    -1,    -1,    -1,   577,
     578,    -1,   363,    81,    82,   366,   547,    -1,    -1,    -1,
     182,    -1,    51,    52,    53,    -1,    55,   524,   525,   526,
     381,    -1,   529,   384,    -1,    64,    -1,    -1,   535,   390,
      -1,    -1,    -1,    -1,   541,    -1,    -1,    -1,    -1,    -1,
      -1,   392,   393,    -1,   395,    -1,    -1,    -1,    -1,   279,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   566,
      -1,    -1,    -1,    -1,   415,   416,    -1,   418,   429,    -1,
     431,    -1,    -1,    -1,    -1,   436,   115,   438,    -1,   118,
      -1,    -1,    -1,    -1,   445,    -1,   447,    -1,   449,    -1,
      -1,   130,    -1,    -1,    -1,   446,    -1,   448,    -1,   450,
     272,   273,    -1,    -1,    -1,    -1,    -1,   279,    -1,    -1,
      -1,   283,   284,    -1,    -1,    -1,    -1,   468,    -1,   470,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   170,    -1,   363,   173,    -1,   366,    -1,    -1,    -1,
     179,    -1,    -1,    -1,   183,    -1,    -1,   186,    -1,   188,
      -1,   381,    -1,    -1,   384,    -1,   195,    -1,    -1,    -1,
     390,   182,    -1,    -1,    -1,    -1,    -1,   528,    -1,   530,
     531,    -1,   211,    -1,    -1,   214,   527,   538,   539,   540,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   226,    -1,    -1,
      -1,   363,    -1,    -1,   366,   182,   557,   558,    -1,   429,
     561,   431,    -1,    -1,    -1,    -1,   436,    -1,   438,   381,
     571,    -1,   384,    -1,    -1,   445,    -1,   447,   390,   449,
      -1,    -1,    -1,    -1,    -1,    -1,   577,   578,    -1,    -1,
     269,    -1,   271,    -1,    -1,    -1,   275,   276,   277,   278,
      -1,    -1,    -1,    -1,   283,    -1,    -1,    -1,    -1,    -1,
      -1,   272,   273,    -1,    -1,    -1,    -1,   429,   279,   431,
      -1,    -1,   283,   284,   436,    -1,   438,    -1,    -1,    -1,
      -1,    -1,   311,   445,    -1,   447,    -1,   449,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   272,   273,    -1,    -1,    -1,
      -1,    -1,   279,    -1,    -1,    -1,   283,   284,   528,    -1,
     530,   531,    -1,    -1,    -1,    -1,    -1,    -1,   538,   539,
     540,    -1,    -1,   352,    -1,   354,    -1,    -1,    -1,    -1,
      -1,    -1,   361,    -1,    -1,    -1,    -1,   557,   558,    -1,
      -1,   561,    -1,    -1,   373,    -1,    -1,    -1,    -1,    -1,
      -1,   571,   363,    -1,    -1,   366,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   528,   396,   530,   531,
     381,    -1,    -1,   384,    -1,    -1,   538,   539,   540,   390,
      -1,    -1,    -1,    -1,    -1,    -1,   363,    -1,    -1,   366,
      -1,    -1,    -1,   422,    -1,   557,   558,    -1,    -1,   561,
      -1,    -1,    -1,   432,   381,    -1,    -1,   384,    -1,   571,
      -1,    -1,    -1,   390,    -1,    -1,    -1,    -1,   429,    -1,
     431,    -1,    -1,    -1,    -1,   436,    -1,   438,    -1,    -1,
      -1,   460,   461,    -1,   445,    -1,   447,    -1,   449,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       3,    -1,   429,     6,   431,    -1,    -1,    -1,    -1,   436,
      -1,   438,    15,    16,    -1,    -1,    19,    -1,   445,    22,
     447,    24,   449,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,
      53,    54,    -1,    56,    -1,    58,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,   528,    -1,   530,
     531,    -1,    -1,    -1,    -1,    -1,    -1,   538,   539,   540,
      83,    -1,    85,    86,    87,    88,    89,    90,    91,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   557,   558,    -1,    -1,
     561,   528,    -1,   530,   531,    -1,    -1,    -1,    -1,    -1,
     571,   538,   539,   540,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,     3,    -1,    -1,     6,    -1,    -1,
     557,   558,    -1,    -1,   561,    -1,    15,    16,    -1,    -1,
      19,    -1,    -1,    22,   571,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,     3,    -1,    83,     6,    85,    86,    87,    88,
      89,    90,    91,    -1,    15,    16,    -1,    -1,    19,    -1,
      -1,    22,    -1,    24,    -1,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    -1,    -1,    37,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,    60,
      -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
       3,    -1,    83,     6,    85,    86,    87,    88,    89,    90,
      91,    -1,    15,    16,    -1,    -1,    19,    -1,    -1,    22,
      -1,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,
      53,    54,    -1,    56,    -1,    58,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,    -1,
      83,     6,    85,    86,    87,    88,    89,    90,    91,    -1,
      15,    16,    -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    27,    -1,    29,    30,    31,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    39,    -1,    41,    -1,    -1,    -1,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    56,    -1,    58,    -1,    60,    -1,    -1,    -1,    64,
      65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,     3,    -1,    -1,     6,    -1,
      85,    86,    87,    88,    89,    90,    91,    15,    16,    -1,
      -1,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    29,    30,    31,    -1,    -1,    34,    -1,    -1,    -1,
      -1,    -1,    -1,    41,    -1,    -1,    -1,    45,    46,    47,
      -1,    -1,    -1,    -1,    52,    53,    54,    -1,    56,    -1,
      58,    59,    60,    -1,    -1,    -1,    -1,    65,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,     3,    -1,    -1,     6,    -1,    85,    86,    87,
      88,    89,    90,    91,    15,    16,    -1,    -1,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    29,    30,
      31,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    -1,    -1,    -1,    45,    46,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    -1,    56,    57,    58,    -1,    60,
      -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,     3,
      -1,    -1,     6,    -1,    85,    86,    87,    88,    89,    90,
      91,    15,    16,    -1,    -1,    19,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    27,    -1,    29,    30,    31,    -1,    -1,
      34,    -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,
      -1,    45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,
      54,    -1,    56,    57,    58,    -1,    60,    -1,    -1,    -1,
      -1,    65,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,     3,    -1,    -1,     6,
      -1,    85,    86,    87,    88,    89,    90,    91,    15,    16,
      -1,    -1,    19,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      27,    -1,    29,    30,    31,    -1,    -1,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,    45,    46,
      47,    -1,    -1,    -1,    -1,    52,    53,    54,    -1,    56,
      57,    58,    -1,    60,    -1,    -1,    -1,    -1,    65,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,     3,    -1,    -1,     6,    -1,    85,    86,
      87,    88,    89,    90,    91,    15,    16,    -1,    -1,    19,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    27,    -1,    29,
      30,    31,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    45,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    54,    -1,    56,    -1,    58,    -1,
      60,    -1,    -1,    -1,    -1,    65,    66,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       3,    -1,    -1,     6,    -1,    85,    86,    87,    88,    89,
      90,    91,    15,    16,    -1,    -1,    19,    -1,    -1,    22,
      23,    24,    -1,    26,    27,    28,    29,    30,    31,    32,
      -1,    34,    -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    -1,    -1,    -1,    -1,    -1,
      53,    54,    -1,    56,    -1,    58,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,
      83,     6,    85,    86,    87,    88,    89,    90,    91,    -1,
      15,    16,    -1,    -1,    19,    -1,    -1,    22,    -1,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    -1,    34,
      -1,    -1,    37,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,    46,    47,    -1,    -1,    -1,    -1,    -1,    53,    54,
      -1,    56,    -1,    58,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     3,    -1,    83,     6,
      85,    86,    87,    88,    89,    90,    91,    -1,    15,    16,
      -1,    -1,    19,    -1,    -1,    22,    -1,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    -1,    34,    -1,    -1,
      37,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,
      47,    -1,    -1,    -1,    -1,    -1,    53,    54,    -1,    56,
      -1,    58,    -1,    60,    61,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     3,    -1,    83,     6,    85,    86,
      87,    88,    89,    90,    91,    -1,    15,    16,    -1,    -1,
      19,    -1,    -1,    22,    -1,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    -1,    -1,    37,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,
      -1,    -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    83,    84,    85,    86,    87,    88,
      89,    90,    91,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    19,
      -1,    -1,    22,    -1,    24,    -1,    26,    27,    28,    29,
      30,    31,    32,    -1,    34,    -1,    -1,    37,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    47,    -1,    -1,
      -1,    -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    66,    -1,     3,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    16,    -1,    83,    19,    85,    86,    87,    88,    89,
      90,    91,    27,    -1,    29,    30,    31,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    39,    -1,    41,    -1,    -1,    -1,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    56,    -1,    58,    -1,    60,    61,    -1,    -1,    64,
      65,    66,    -1,     3,    -1,    -1,     6,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    19,
      85,    86,    87,    88,    89,    90,    91,    27,    -1,    29,
      30,    31,    -1,    -1,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    41,    -1,    -1,    -1,    45,    46,    47,    -1,    -1,
      -1,    -1,    52,    53,    54,    -1,    56,    -1,    58,    -1,
      60,    -1,    -1,    -1,    -1,    65,    66,    -1,     3,    -1,
      -1,     6,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      15,    16,    -1,    -1,    19,    85,    86,    87,    88,    89,
      90,    91,    27,    -1,    29,    30,    31,    -1,    -1,    34,
      -1,    -1,    -1,    -1,    -1,    -1,    41,    -1,    -1,    -1,
      45,    46,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      -1,    56,    -1,    58,    -1,    60,    -1,    -1,    -1,    -1,
      65,    66,     3,    -1,    -1,     6,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    15,    16,    -1,    -1,    19,    -1,
      85,    86,    87,    88,    89,    90,    91,    -1,    29,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    45,    46,    47,    -1,    -1,    -1,
      -1,    -1,    53,    54,    -1,    56,    -1,    58,    -1,    60,
      -1,    -1,     0,     1,    -1,    66,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    -1,    -1,    -1,    17,
      18,    19,    20,    -1,    85,    86,    87,    88,    89,    90,
      91,     1,    -1,    -1,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    -1,    -1,    33,    17,    18,    19,
      20,    -1,    -1,    -1,    -1,    42,    -1,    -1,    -1,    -1,
      58,    48,    49,    50,    51,    -1,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    33,    58,    -1,
      -1,    78,    -1,    80,    81,    82,    -1,    -1,    -1,    -1,
      -1,    -1,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    33,    -1,
      -1,    -1,    78,    -1,    80,    81,    82,    -1,    -1,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    -1,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    33,
      -1,    -1,    -1,    78,    -1,    80,    81,    82,    -1,    -1,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    -1,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      33,    -1,    -1,    -1,    78,    -1,    80,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    51,    -1,
      53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    35,    -1,    -1,    -1,    78,    -1,    80,    81,    82,
      -1,    -1,    -1,    -1,    48,    49,    50,    51,    -1,    53,
      54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,    73,
      35,    -1,    -1,    -1,    78,    -1,    80,    81,    82,    -1,
      -1,    -1,    -1,    48,    49,    50,    51,    -1,    53,    54,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    36,
      -1,    -1,    -1,    78,    -1,    80,    81,    82,    -1,    -1,
      -1,    48,    49,    50,    51,    -1,    53,    54,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    38,    -1,    -1,
      -1,    78,    -1,    80,    81,    82,    -1,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    40,    -1,    -1,    78,    -1,    80,
      81,    82,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    42,    78,    -1,    80,    81,    82,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    78,    -1,    80,
      81,    82,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    78,    -1,    80,    81,    82,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    75,    -1,    -1,    78,    -1,    80,
      81,    82,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    78,    -1,    80,    81,    82,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    78,    -1,    80,
      81,    82,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    78,    -1,    80,    81,    82,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    78,    -1,    80,
      81,    82,    48,    49,    50,    51,    -1,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    78,    -1,    80,    81,    82,    48,    49,    50,
      51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,
      71,    72,    73,    -1,    -1,    -1,    -1,    78,    -1,    80,
      81,    82,    48,    -1,    50,    -1,    -1,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    48,    -1,    80,    81,    82,    53,    54,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    80,    81,    82
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    58,    98,    99,   208,   209,     1,     3,     6,
      15,    29,    91,   193,   210,   211,     0,     1,     4,     5,
       6,     7,     8,     9,    10,    19,    20,   100,   101,   102,
     103,   104,   105,   106,   107,   110,   111,   112,   113,   114,
     117,   120,   121,   122,   126,   127,   208,     3,   209,    59,
      16,    27,    30,    31,    34,    41,    45,    46,    47,    52,
      53,    54,    56,    58,    60,    65,    66,    85,    86,    87,
      88,    89,    90,   120,   147,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   193,   194,    59,    59,    60,   194,   193,   193,
     193,   193,   194,   193,   194,    68,   193,   101,    11,    12,
      13,    17,    18,   102,   193,   195,   198,   199,   203,   204,
     208,   196,   199,   196,   147,   196,   147,   148,   148,     1,
     146,   147,     1,    59,   146,   147,   175,   176,   193,   148,
     194,   194,    48,    49,    50,    51,    53,    54,    55,    68,
      69,    70,    71,    72,    73,    78,    80,    81,    82,    43,
      76,    56,    56,    63,    56,   147,   173,   191,   192,    56,
      77,    55,    55,    56,    77,    55,    63,    55,    43,   195,
     201,   202,    62,   193,    56,    60,   178,   179,   180,   181,
     182,   183,   184,   194,   178,   178,   183,   194,    62,    55,
      29,    67,   195,    29,    67,    29,    35,    29,    57,    67,
      57,    59,    59,    67,    75,    61,    67,    62,    65,    56,
     147,   147,   147,   147,   147,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   147,   147,   147,   178,   165,   193,
       1,    57,   146,   147,     1,    57,   146,   193,   147,    77,
      61,    67,     1,    16,   187,   188,   193,   198,   200,   208,
     178,    60,    22,    24,    26,    27,    28,    30,    31,    32,
      34,    37,    44,    60,    83,   130,   131,   132,   133,   136,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   148,
     150,   151,   152,     1,   187,   188,   178,   178,    70,   147,
     193,    67,    69,   178,   185,   186,    55,   177,   178,   197,
     198,    55,    68,    74,    14,    55,    68,   178,   147,   147,
     204,   147,   199,   147,   147,   147,   147,   147,   147,   176,
     147,   146,    56,    57,    57,    57,    57,    57,   147,   192,
      57,    57,    67,    57,    67,   198,    55,     1,   108,   109,
     193,   208,     1,   129,   130,     1,   129,   203,     1,   193,
     205,   206,   207,   208,   196,   196,   130,   147,   147,   147,
       1,   129,   193,     1,   129,    79,    79,    57,    57,    57,
      55,   202,    70,    77,    60,    67,    67,    60,   177,   178,
     186,   147,   178,    60,    40,    33,    36,    42,    57,    59,
      57,     1,    57,   146,    77,    77,    77,   200,    77,   200,
     147,    61,    67,   193,    23,    23,   130,    25,    25,    29,
      62,    29,    67,   207,    29,    29,    35,    38,    33,    61,
      61,    84,    84,   147,   147,    55,    77,    55,    77,    55,
      77,   130,   178,   178,   107,   115,   116,   208,   178,   198,
       5,     7,   105,   106,   118,   119,   128,   208,    67,    69,
      77,    55,   105,   106,   123,   124,   125,   208,   147,   147,
     147,   147,    57,    57,   147,   178,   178,   178,   108,   130,
     186,   130,   206,   147,   147,   130,    60,   130,   130,   178,
     130,   178,   130,   178,    21,   189,    61,   116,   107,    57,
      61,   193,   193,    61,   118,   105,   106,   128,   178,   178,
      60,    61,   124,   125,    55,    55,    55,    77,    33,    42,
      33,    36,     1,    39,    64,   134,   135,   147,    55,    55,
      55,    60,    55,   190,    62,    62,    69,   123,   147,   147,
     147,   178,   130,   147,   130,   130,    61,    62,    62,    61,
     135,    62,   130,   130,   130,   147,    60,   186,   186,    61,
     189,    33,   130,   130,   130,    61,   191,    77,    77,   190,
     130,    61,   178,   178
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
     118,   118,   118,   119,   119,   120,   121,   121,   122,   122,
     123,   123,   124,   124,   125,   125,   126,   127,   128,   128,
     129,   129,   130,   130,   130,   130,   130,   130,   130,   130,
     130,   130,   130,   130,   130,   131,   132,   132,   133,   133,
     134,   134,   135,   135,   135,   136,   137,   138,   138,   139,
     140,   141,   141,   141,   141,   142,   142,   142,   142,   143,
     143,   144,   145,   146,   146,   147,   147,   147,   147,   147,
     147,   147,   147,   147,   148,   148,   148,   148,   148,   148,
     148,   149,   149,   149,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   150,
     150,   150,   151,   151,   151,   151,   151,   151,   152,   152,
     152,   152,   153,   154,   154,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   162,   162,   162,   162,   162,   162,
     162,   162,   162,   162,   162,   163,   164,   164,   165,   166,
     167,   168,   168,   169,   170,   171,   171,   171,   172,   173,
     174,   175,   175,   176,   177,   177,   178,   178,   178,   178,
     178,   178,   179,   180,   181,   182,   183,   184,   185,   185,
     186,   186,   187,   187,   188,   188,   189,   189,   190,   190,
     191,   191,   192,   192,   192,   193,   193,   193,   193,   193,
     194,   194,   195,   195,   196,   196,   197,   197,   198,   199,
     199,   200,   200,   201,   201,   202,   203,   203,   204,   205,
     205,   206,   206,   206,   207,   208,   208,   209,   209,   209,
     210,   211
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     4,     6,     6,     9,     9,
       9,     4,     6,     7,     9,     7,     9,     7,     9,     8,
       1,     2,     1,     3,     1,     4,     2,     4,     4,     2,
       4,     7,     2,     1,     2,     1,     7,     2,     1,     2,
       1,     2,     1,     2,     1,     4,     1,     0,     7,     9,
       2,     1,     2,     1,     1,     1,     3,     3,     6,     6,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     6,     6,     6,
       2,     1,     3,     3,     3,     4,     4,     6,     8,     6,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     1,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     1,     1,     3,     4,     5,     4,     3,     5,
       6,     6,     3,     3,     4,     4,     3,     4,     6,     6,
       6,     6,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     3,     3,     5,     5,
       3,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     5,     4,     6,     3,     3,     1,
       1,     0,     3,     1,     3,     1,     4,     0,     4,     0,
       3,     1,     1,     5,     3,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     3,     1,     3,     1,     3,     2,
       1,     2,     1,     3,     1,     1,     3,     1,     3,     3,
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
  "\"invariant\"", "\"import\"", "\"structure\"", "\"behavior\"",
  "\"implement\"", "\"for\"", "\"self\"", "\"this\"", "\"domain\"",
  "\"builtin\"", "\"template\"", "\"function\"", "\"defined\"", "\"seq\"",
  "\"endseq\"", "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"",
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
  "ImportDefinition", "StructureDefinition", "StructureDefinitionList",
  "StructureDefinitionElement", "BehaviorDefinition",
  "BehaviorDefinitionElement", "BehaviorDefinitionList", "Template",
  "MaybeTemplate", "ImplementDefinition", "ImplementDefinitionList",
  "ImplementDefinitionElement", "ImplementDefinitionAttributedElement",
  "DomainDefinition", "BuiltinDefinition", "Declaration", "Rules", "Rule",
  "SkipRule", "ConditionalRule", "CaseRule", "CaseLabels", "CaseLabel",
  "LetRule", "LocalRule", "ForallRule", "ChooseRule", "IterateRule",
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
  "BasicType", "TupleType", "RecordType", "TemplateType", "RelationType",
  "FixedSizedType", "FunctionParameters", "MaybeFunctionParameters",
  "MethodParameters", "Parameters", "MaybeDefined", "MaybeInitially",
  "Initializers", "Initializer", "Identifier", "IdentifierPath",
  "Variable", "AttributedVariables", "TypedVariables", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "TemplateVariables",
  "TemplateVariable", "VariableBindings", "VariableBinding",
  "LocalFunctionDefinitions", "AttributedLocalFunctionDefinition",
  "LocalFunctionDefinition", "Attributes", "Attribute", "BasicAttribute",
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
     807,   811,   817,   825,   831,   840,   847,   851,   865,   869,
     876,   882,   891,   897,   904,   908,   920,   932,   944,   948,
     960,   966,   976,   980,   984,   988,   992,   996,  1000,  1004,
    1008,  1012,  1016,  1020,  1024,  1032,  1040,  1044,  1052,  1056,
    1064,  1070,  1080,  1084,  1088,  1096,  1104,  1112,  1116,  1124,
    1132,  1140,  1144,  1148,  1153,  1162,  1166,  1170,  1175,  1184,
    1188,  1196,  1204,  1216,  1223,  1233,  1237,  1241,  1245,  1249,
    1253,  1257,  1261,  1265,  1273,  1277,  1281,  1285,  1289,  1293,
    1297,  1309,  1313,  1317,  1321,  1325,  1329,  1333,  1337,  1341,
    1345,  1349,  1353,  1357,  1361,  1365,  1369,  1373,  1377,  1385,
    1389,  1393,  1401,  1407,  1411,  1416,  1420,  1424,  1432,  1437,
    1444,  1450,  1458,  1466,  1473,  1479,  1487,  1495,  1503,  1511,
    1519,  1527,  1535,  1547,  1551,  1555,  1559,  1563,  1567,  1571,
    1575,  1579,  1583,  1587,  1591,  1599,  1608,  1614,  1624,  1632,
    1640,  1648,  1652,  1660,  1668,  1676,  1683,  1689,  1697,  1707,
    1720,  1734,  1741,  1750,  1762,  1769,  1778,  1782,  1786,  1790,
    1794,  1798,  1806,  1814,  1825,  1836,  1844,  1852,  1864,  1871,
    1881,  1885,  1893,  1900,  1913,  1920,  1934,  1938,  1946,  1950,
    1959,  1966,  1976,  1983,  1991,  2008,  2012,  2017,  2022,  2027,
    2036,  2043,  2055,  2059,  2068,  2075,  2085,  2092,  2102,  2111,
    2117,  2125,  2131,  2139,  2146,  2156,  2169,  2176,  2185,  2197,
    2204,  2213,  2219,  2223,  2230,  2243,  2249,  2258,  2265,  2272,
    2279,  2286
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
#line 6763 "GrammarParser.cpp"

#line 2292 "../../obj/src/GrammarParser.y"


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
