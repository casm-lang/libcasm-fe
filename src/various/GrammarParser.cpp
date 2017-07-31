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

      case symbol_kind::S_Declaration: // Declaration
        value.YY_MOVE_OR_COPY< DeclarationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.YY_MOVE_OR_COPY< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDefinitionElement: // FeatureDefinitionElement
      case symbol_kind::S_ImplementationDefinitionDefinition: // ImplementationDefinitionDefinition
        value.YY_MOVE_OR_COPY< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
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

      case symbol_kind::S_Declaration: // Declaration
        value.move< DeclarationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.move< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDefinitionElement: // FeatureDefinitionElement
      case symbol_kind::S_ImplementationDefinitionDefinition: // ImplementationDefinitionDefinition
        value.move< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
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

      case symbol_kind::S_Declaration: // Declaration
        value.copy< DeclarationDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.copy< Defined::Ptr > (that.value);
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDefinitionElement: // FeatureDefinitionElement
      case symbol_kind::S_ImplementationDefinitionDefinition: // ImplementationDefinitionDefinition
        value.copy< Definition::Ptr > (that.value);
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
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

      case symbol_kind::S_Declaration: // Declaration
        value.move< DeclarationDefinition::Ptr > (that.value);
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.move< Defined::Ptr > (that.value);
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDefinitionElement: // FeatureDefinitionElement
      case symbol_kind::S_ImplementationDefinitionDefinition: // ImplementationDefinitionDefinition
        value.move< Definition::Ptr > (that.value);
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
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

      case symbol_kind::S_Declaration: // Declaration
        yylhs.value.emplace< DeclarationDefinition::Ptr > ();
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        yylhs.value.emplace< Defined::Ptr > ();
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_FeatureDefinitionElement: // FeatureDefinitionElement
      case symbol_kind::S_ImplementationDefinitionDefinition: // ImplementationDefinitionDefinition
        yylhs.value.emplace< Definition::Ptr > ();
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
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
#line 435 "../../obj/src/GrammarParser.y"
  {
      m_specification.setHeader( yystack_[1].value.as < HeaderDefinition::Ptr > () );
      m_specification.setDefinitions( yystack_[0].value.as < Definitions::Ptr > () );
      m_specification.setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 2773 "GrammarParser.cpp"
    break;

  case 3: // Header: Attributes "CASM"
#line 445 "../../obj/src/GrammarParser.y"
  {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2783 "GrammarParser.cpp"
    break;

  case 4: // Header: "CASM"
#line 451 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2791 "GrammarParser.cpp"
    break;

  case 5: // Definitions: Definitions AttributedDefinition
#line 459 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2801 "GrammarParser.cpp"
    break;

  case 6: // Definitions: AttributedDefinition
#line 465 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2811 "GrammarParser.cpp"
    break;

  case 7: // AttributedDefinition: Attributes Definition
#line 475 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2821 "GrammarParser.cpp"
    break;

  case 8: // AttributedDefinition: Definition
#line 481 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2829 "GrammarParser.cpp"
    break;

  case 9: // AttributedDefinition: error
#line 485 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2837 "GrammarParser.cpp"
    break;

  case 10: // Definition: InitDefinition
#line 493 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2845 "GrammarParser.cpp"
    break;

  case 11: // Definition: EnumerationDefinition
#line 497 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2853 "GrammarParser.cpp"
    break;

  case 12: // Definition: DerivedDefinition
#line 501 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2861 "GrammarParser.cpp"
    break;

  case 13: // Definition: RuleDefinition
#line 505 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2869 "GrammarParser.cpp"
    break;

  case 14: // Definition: FunctionDefinition
#line 509 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 2877 "GrammarParser.cpp"
    break;

  case 15: // Definition: UsingDefinition
#line 513 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 2885 "GrammarParser.cpp"
    break;

  case 16: // Definition: UsingPathDefinition
#line 517 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingPathDefinition::Ptr > ();
  }
#line 2893 "GrammarParser.cpp"
    break;

  case 17: // Definition: InvariantDefinition
#line 521 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 2901 "GrammarParser.cpp"
    break;

  case 18: // Definition: ImportDefinition
#line 525 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 2909 "GrammarParser.cpp"
    break;

  case 19: // Definition: StructureDefinition
#line 529 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < StructureDefinition::Ptr > ();
  }
#line 2917 "GrammarParser.cpp"
    break;

  case 20: // Definition: FeatureDefinition
#line 533 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FeatureDefinition::Ptr > ();
  }
#line 2925 "GrammarParser.cpp"
    break;

  case 21: // Definition: ImplementationDefinition
#line 537 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImplementationDefinition::Ptr > ();
  }
#line 2933 "GrammarParser.cpp"
    break;

  case 22: // InitDefinition: "init" IdentifierPath
#line 545 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2941 "GrammarParser.cpp"
    break;

  case 23: // InitDefinition: "init" "{" Initializers "}"
#line 549 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2949 "GrammarParser.cpp"
    break;

  case 24: // EnumerationDefinition: "enumeration" Identifier "=" "{" Enumerators "}"
#line 557 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2957 "GrammarParser.cpp"
    break;

  case 25: // DerivedDefinition: "derived" Identifier "->" Type "=" Term
#line 565 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2966 "GrammarParser.cpp"
    break;

  case 26: // DerivedDefinition: "derived" Identifier "(" Parameters ")" "->" Type "=" Term
#line 570 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2976 "GrammarParser.cpp"
    break;

  case 27: // DerivedDefinition: "derived" Identifier "(" error ")" "->" Type "=" Term
#line 576 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 2984 "GrammarParser.cpp"
    break;

  case 28: // RuleDefinition: "rule" Identifier "=" Rule
#line 584 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2994 "GrammarParser.cpp"
    break;

  case 29: // RuleDefinition: "rule" Identifier "->" Type "=" Rule
#line 590 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3003 "GrammarParser.cpp"
    break;

  case 30: // RuleDefinition: "rule" Identifier "(" Parameters ")" "=" Rule
#line 595 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
  }
#line 3014 "GrammarParser.cpp"
    break;

  case 31: // RuleDefinition: "rule" Identifier "(" Parameters ")" "->" Type "=" Rule
#line 602 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 3024 "GrammarParser.cpp"
    break;

  case 32: // RuleDefinition: "rule" Identifier "(" error ")" "=" Rule
#line 608 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3032 "GrammarParser.cpp"
    break;

  case 33: // RuleDefinition: "rule" Identifier "(" error ")" "->" Type "=" Rule
#line 612 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3040 "GrammarParser.cpp"
    break;

  case 34: // FunctionDefinition: "function" Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 636 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = Ast::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      const auto initially = yylhs.value.as < FunctionDefinition::Ptr > ()->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->setFunction( yylhs.value.as < FunctionDefinition::Ptr > () );
      }
  }
#line 3055 "GrammarParser.cpp"
    break;

  case 35: // EnumeratorDefinition: Identifier
#line 651 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3063 "GrammarParser.cpp"
    break;

  case 36: // EnumeratorDefinition: Attributes Identifier
#line 655 "../../obj/src/GrammarParser.y"
  {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 3073 "GrammarParser.cpp"
    break;

  case 37: // EnumeratorDefinition: error
#line 661 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 3081 "GrammarParser.cpp"
    break;

  case 38: // Enumerators: Enumerators "," EnumeratorDefinition
#line 669 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3092 "GrammarParser.cpp"
    break;

  case 39: // Enumerators: EnumeratorDefinition
#line 676 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3102 "GrammarParser.cpp"
    break;

  case 40: // UsingDefinition: "using" Identifier "=" Type
#line 686 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3110 "GrammarParser.cpp"
    break;

  case 41: // UsingPathDefinition: "using" IdentifierPath
#line 694 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3118 "GrammarParser.cpp"
    break;

  case 42: // UsingPathDefinition: "using" IdentifierPath "::" "*"
#line 698 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3126 "GrammarParser.cpp"
    break;

  case 43: // InvariantDefinition: "invariant" Identifier "=" Term
#line 706 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InvariantDefinition::Ptr > () = Ast::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3134 "GrammarParser.cpp"
    break;

  case 44: // ImportDefinition: "import" IdentifierPath
#line 718 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3142 "GrammarParser.cpp"
    break;

  case 45: // ImportDefinition: "import" IdentifierPath "as" Identifier
#line 722 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3150 "GrammarParser.cpp"
    break;

  case 46: // StructureDefinition: "structure" Identifier "=" "{" StructureDefinitionList "}"
#line 730 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, $4, and $6
      // $$ = Ast::make< StructureDefinition >( @$, $2, $5 );
  }
#line 3159 "GrammarParser.cpp"
    break;

  case 47: // StructureDefinitionElement: "[" Attributes "]" FunctionDefinition
#line 739 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 3169 "GrammarParser.cpp"
    break;

  case 48: // StructureDefinitionElement: FunctionDefinition
#line 745 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 3177 "GrammarParser.cpp"
    break;

  case 49: // StructureDefinitionList: StructureDefinitionList StructureDefinitionElement
#line 753 "../../obj/src/GrammarParser.y"
  {
      auto functions = yystack_[1].value.as < FunctionDefinitions::Ptr > ();
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3187 "GrammarParser.cpp"
    break;

  case 50: // StructureDefinitionList: StructureDefinitionElement
#line 759 "../../obj/src/GrammarParser.y"
  {
      auto functions = Ast::make< FunctionDefinitions >( yylhs.location );
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3197 "GrammarParser.cpp"
    break;

  case 51: // FeatureDefinition: "feature" Identifier "=" "{" FeatureDefinitionList "}"
#line 773 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, $4, and $6
      yylhs.value.as < FeatureDefinition::Ptr > () = Ast::make< FeatureDefinition >( yylhs.location, yystack_[4].value.as < Identifier::Ptr > (), yystack_[1].value.as < Definitions::Ptr > () );
  }
#line 3206 "GrammarParser.cpp"
    break;

  case 52: // FeatureDefinitionElement: "[" Attributes "]" Declaration
#line 782 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < DeclarationDefinition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3216 "GrammarParser.cpp"
    break;

  case 53: // FeatureDefinitionElement: Declaration
#line 788 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DeclarationDefinition::Ptr > ();
  }
#line 3224 "GrammarParser.cpp"
    break;

  case 54: // FeatureDefinitionElement: "[" Attributes "]" DerivedDefinition
#line 792 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < DerivedDefinition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3234 "GrammarParser.cpp"
    break;

  case 55: // FeatureDefinitionElement: DerivedDefinition
#line 798 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3242 "GrammarParser.cpp"
    break;

  case 56: // FeatureDefinitionElement: "[" Attributes "]" RuleDefinition
#line 802 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < RuleDefinition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3252 "GrammarParser.cpp"
    break;

  case 57: // FeatureDefinitionElement: RuleDefinition
#line 808 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3260 "GrammarParser.cpp"
    break;

  case 58: // FeatureDefinitionList: FeatureDefinitionList FeatureDefinitionElement
#line 816 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3270 "GrammarParser.cpp"
    break;

  case 59: // FeatureDefinitionList: FeatureDefinitionElement
#line 822 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3280 "GrammarParser.cpp"
    break;

  case 60: // ImplementationDefinition: "implements" IdentifierPath "for" Type "=" "{" ImplementationDefinitionDefinitions "}"
#line 836 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementationDefinition::Ptr > () = Ast::make< ImplementationDefinition >( yylhs.location, yystack_[6].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Definitions::Ptr > () );
  }
#line 3288 "GrammarParser.cpp"
    break;

  case 61: // ImplementationDefinition: "implements" Type "=" "{" ImplementationDefinitionDefinitions "}"
#line 840 "../../obj/src/GrammarParser.y"
  {
      const auto name = Ast::make< Identifier >( yylhs.location, "" );
      const auto path = asIdentifierPath( name );
      yylhs.value.as < ImplementationDefinition::Ptr > () = Ast::make< ImplementationDefinition >( yylhs.location, path, yystack_[4].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Definitions::Ptr > () );
  }
#line 3298 "GrammarParser.cpp"
    break;

  case 62: // ImplementationDefinitionDefinition: DerivedDefinition
#line 850 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3306 "GrammarParser.cpp"
    break;

  case 63: // ImplementationDefinitionDefinition: RuleDefinition
#line 854 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3314 "GrammarParser.cpp"
    break;

  case 64: // ImplementationDefinitionDefinitions: ImplementationDefinitionDefinition ImplementationDefinitionDefinitions
#line 862 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[0].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[1].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3324 "GrammarParser.cpp"
    break;

  case 65: // ImplementationDefinitionDefinitions: ImplementationDefinitionDefinition
#line 868 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3334 "GrammarParser.cpp"
    break;

  case 66: // Declaration: "derived" Identifier ":" MaybeFunctionParameters "->" Type
#line 882 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, and $5
      yylhs.value.as < DeclarationDefinition::Ptr > () = Ast::make< DeclarationDefinition >
          ( yylhs.location, yystack_[4].value.as < Identifier::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > (), DeclarationDefinition::Kind::DERIVED );
  }
#line 3344 "GrammarParser.cpp"
    break;

  case 67: // Declaration: "rule" Identifier ":" MaybeFunctionParameters "->" Type
#line 888 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, and $5
      yylhs.value.as < DeclarationDefinition::Ptr > () = Ast::make< DeclarationDefinition >
          ( yylhs.location, yystack_[4].value.as < Identifier::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > (), DeclarationDefinition::Kind::RULE );
  }
#line 3354 "GrammarParser.cpp"
    break;

  case 68: // Rules: Rules Rule
#line 902 "../../obj/src/GrammarParser.y"
  {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3364 "GrammarParser.cpp"
    break;

  case 69: // Rules: Rule
#line 908 "../../obj/src/GrammarParser.y"
  {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3374 "GrammarParser.cpp"
    break;

  case 70: // Rule: SkipRule
#line 918 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 3382 "GrammarParser.cpp"
    break;

  case 71: // Rule: ConditionalRule
#line 922 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 3390 "GrammarParser.cpp"
    break;

  case 72: // Rule: CaseRule
#line 926 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 3398 "GrammarParser.cpp"
    break;

  case 73: // Rule: LetRule
#line 930 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 3406 "GrammarParser.cpp"
    break;

  case 74: // Rule: LocalRule
#line 934 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LocalRule::Ptr > ();
  }
#line 3414 "GrammarParser.cpp"
    break;

  case 75: // Rule: ForallRule
#line 938 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 3422 "GrammarParser.cpp"
    break;

  case 76: // Rule: ChooseRule
#line 942 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 3430 "GrammarParser.cpp"
    break;

  case 77: // Rule: IterateRule
#line 946 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 3438 "GrammarParser.cpp"
    break;

  case 78: // Rule: BlockRule
#line 950 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 3446 "GrammarParser.cpp"
    break;

  case 79: // Rule: SequenceRule
#line 954 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 3454 "GrammarParser.cpp"
    break;

  case 80: // Rule: UpdateRule
#line 958 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 3462 "GrammarParser.cpp"
    break;

  case 81: // Rule: CallRule
#line 962 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 3470 "GrammarParser.cpp"
    break;

  case 82: // Rule: WhileRule
#line 966 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 3478 "GrammarParser.cpp"
    break;

  case 83: // SkipRule: "skip"
#line 974 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3486 "GrammarParser.cpp"
    break;

  case 84: // ConditionalRule: "if" Term "then" Rule
#line 982 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3494 "GrammarParser.cpp"
    break;

  case 85: // ConditionalRule: "if" Term "then" Rule "else" Rule
#line 986 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3502 "GrammarParser.cpp"
    break;

  case 86: // CaseRule: "case" Term "of" "{" CaseLabels "}"
#line 994 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3510 "GrammarParser.cpp"
    break;

  case 87: // CaseRule: "case" Term "of" "{" error "}"
#line 998 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 3518 "GrammarParser.cpp"
    break;

  case 88: // CaseLabels: CaseLabels CaseLabel
#line 1006 "../../obj/src/GrammarParser.y"
  {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3528 "GrammarParser.cpp"
    break;

  case 89: // CaseLabels: CaseLabel
#line 1012 "../../obj/src/GrammarParser.y"
  {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3538 "GrammarParser.cpp"
    break;

  case 90: // CaseLabel: "default" ":" Rule
#line 1022 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3546 "GrammarParser.cpp"
    break;

  case 91: // CaseLabel: "_" ":" Rule
#line 1026 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3554 "GrammarParser.cpp"
    break;

  case 92: // CaseLabel: Term ":" Rule
#line 1030 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3562 "GrammarParser.cpp"
    break;

  case 93: // LetRule: "let" VariableBindings "in" Rule
#line 1038 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3570 "GrammarParser.cpp"
    break;

  case 94: // LocalRule: "local" LocalFunctionDefinitions "in" Rule
#line 1046 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LocalRule::Ptr > () = Ast::make< LocalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < FunctionDefinitions::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3578 "GrammarParser.cpp"
    break;

  case 95: // ForallRule: "forall" AttributedVariables "in" Term "do" Rule
#line 1054 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3586 "GrammarParser.cpp"
    break;

  case 96: // ForallRule: "forall" AttributedVariables "in" Term "with" Term "do" Rule
#line 1058 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3594 "GrammarParser.cpp"
    break;

  case 97: // ChooseRule: "choose" AttributedVariables "in" Term "do" Rule
#line 1066 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3602 "GrammarParser.cpp"
    break;

  case 98: // IterateRule: "iterate" Rule
#line 1074 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3610 "GrammarParser.cpp"
    break;

  case 99: // BlockRule: "{" Rules "}"
#line 1082 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3618 "GrammarParser.cpp"
    break;

  case 100: // BlockRule: "par" Rules "endpar"
#line 1086 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3626 "GrammarParser.cpp"
    break;

  case 101: // BlockRule: "{" error "}"
#line 1090 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3635 "GrammarParser.cpp"
    break;

  case 102: // BlockRule: "par" error "endpar"
#line 1095 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3644 "GrammarParser.cpp"
    break;

  case 103: // SequenceRule: "{|" Rules "|}"
#line 1104 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3652 "GrammarParser.cpp"
    break;

  case 104: // SequenceRule: "seq" Rules "endseq"
#line 1108 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3660 "GrammarParser.cpp"
    break;

  case 105: // SequenceRule: "{|" error "|}"
#line 1112 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3669 "GrammarParser.cpp"
    break;

  case 106: // SequenceRule: "seq" error "endseq"
#line 1117 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3678 "GrammarParser.cpp"
    break;

  case 107: // UpdateRule: DirectCallExpression ":=" Term
#line 1126 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3686 "GrammarParser.cpp"
    break;

  case 108: // CallRule: CallExpression
#line 1134 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 3694 "GrammarParser.cpp"
    break;

  case 109: // WhileRule: "while" Term "do" Rule
#line 1142 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3702 "GrammarParser.cpp"
    break;

  case 110: // Terms: Terms "," Term
#line 1154 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3713 "GrammarParser.cpp"
    break;

  case 111: // Terms: Term
#line 1161 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3723 "GrammarParser.cpp"
    break;

  case 112: // Term: SimpleOrClaspedTerm
#line 1171 "../../obj/src/GrammarParser.y"
  {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3731 "GrammarParser.cpp"
    break;

  case 113: // Term: TypeCastingExpression
#line 1175 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 3739 "GrammarParser.cpp"
    break;

  case 114: // Term: OperatorExpression
#line 1179 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3747 "GrammarParser.cpp"
    break;

  case 115: // Term: LetExpression
#line 1183 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 3755 "GrammarParser.cpp"
    break;

  case 116: // Term: ConditionalExpression
#line 1187 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 3763 "GrammarParser.cpp"
    break;

  case 117: // Term: ChooseExpression
#line 1191 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 3771 "GrammarParser.cpp"
    break;

  case 118: // Term: UniversalQuantifierExpression
#line 1195 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 3779 "GrammarParser.cpp"
    break;

  case 119: // Term: ExistentialQuantifierExpression
#line 1199 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 3787 "GrammarParser.cpp"
    break;

  case 120: // Term: CardinalityExpression
#line 1203 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 3795 "GrammarParser.cpp"
    break;

  case 121: // SimpleOrClaspedTerm: "(" Term ")"
#line 1211 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< Ast::EmbracedExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3803 "GrammarParser.cpp"
    break;

  case 122: // SimpleOrClaspedTerm: "(" error ")"
#line 1215 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 3811 "GrammarParser.cpp"
    break;

  case 123: // SimpleOrClaspedTerm: CallExpression
#line 1219 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 3819 "GrammarParser.cpp"
    break;

  case 124: // SimpleOrClaspedTerm: LiteralCallExpression
#line 1223 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 3827 "GrammarParser.cpp"
    break;

  case 125: // SimpleOrClaspedTerm: Literal
#line 1227 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 3835 "GrammarParser.cpp"
    break;

  case 126: // SimpleOrClaspedTerm: "+" SimpleOrClaspedTerm
#line 1231 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3843 "GrammarParser.cpp"
    break;

  case 127: // SimpleOrClaspedTerm: "-" SimpleOrClaspedTerm
#line 1235 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 3851 "GrammarParser.cpp"
    break;

  case 128: // OperatorExpression: Term "+" Term
#line 1247 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3859 "GrammarParser.cpp"
    break;

  case 129: // OperatorExpression: Term "-" Term
#line 1251 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 3867 "GrammarParser.cpp"
    break;

  case 130: // OperatorExpression: Term "*" Term
#line 1255 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 3875 "GrammarParser.cpp"
    break;

  case 131: // OperatorExpression: Term "/" Term
#line 1259 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 3883 "GrammarParser.cpp"
    break;

  case 132: // OperatorExpression: Term "%" Term
#line 1263 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 3891 "GrammarParser.cpp"
    break;

  case 133: // OperatorExpression: Term "^" Term
#line 1267 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 3899 "GrammarParser.cpp"
    break;

  case 134: // OperatorExpression: Term "!=" Term
#line 1271 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 3907 "GrammarParser.cpp"
    break;

  case 135: // OperatorExpression: Term "=" Term
#line 1275 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 3915 "GrammarParser.cpp"
    break;

  case 136: // OperatorExpression: Term "<" Term
#line 1279 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 3923 "GrammarParser.cpp"
    break;

  case 137: // OperatorExpression: Term ">" Term
#line 1283 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 3931 "GrammarParser.cpp"
    break;

  case 138: // OperatorExpression: Term "<=" Term
#line 1287 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 3939 "GrammarParser.cpp"
    break;

  case 139: // OperatorExpression: Term ">=" Term
#line 1291 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 3947 "GrammarParser.cpp"
    break;

  case 140: // OperatorExpression: Term "or" Term
#line 1295 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 3955 "GrammarParser.cpp"
    break;

  case 141: // OperatorExpression: Term "xor" Term
#line 1299 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 3963 "GrammarParser.cpp"
    break;

  case 142: // OperatorExpression: Term "and" Term
#line 1303 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 3971 "GrammarParser.cpp"
    break;

  case 143: // OperatorExpression: Term "=>" Term
#line 1307 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3979 "GrammarParser.cpp"
    break;

  case 144: // OperatorExpression: Term "implies" Term
#line 1311 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3987 "GrammarParser.cpp"
    break;

  case 145: // OperatorExpression: "not" Term
#line 1315 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 3995 "GrammarParser.cpp"
    break;

  case 146: // CallExpression: DirectCallExpression
#line 1323 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 4003 "GrammarParser.cpp"
    break;

  case 147: // CallExpression: MethodCallExpression
#line 1327 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 4011 "GrammarParser.cpp"
    break;

  case 148: // CallExpression: IndirectCallExpression
#line 1331 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 4019 "GrammarParser.cpp"
    break;

  case 149: // DirectCallExpression: IdentifierPath
#line 1339 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > (), arguments );
  }
#line 4028 "GrammarParser.cpp"
    break;

  case 150: // DirectCallExpression: IdentifierPath "(" ")"
#line 1344 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), arguments );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4039 "GrammarParser.cpp"
    break;

  case 151: // DirectCallExpression: IdentifierPath "(" Terms ")"
#line 1351 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4049 "GrammarParser.cpp"
    break;

  case 152: // DirectCallExpression: IdentifierPath "(" error ")"
#line 1357 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 4057 "GrammarParser.cpp"
    break;

  case 153: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier
#line 1365 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 4066 "GrammarParser.cpp"
    break;

  case 154: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" ")"
#line 1370 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4077 "GrammarParser.cpp"
    break;

  case 155: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" Terms ")"
#line 1377 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4087 "GrammarParser.cpp"
    break;

  case 156: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" error ")"
#line 1383 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 4095 "GrammarParser.cpp"
    break;

  case 157: // LiteralCallExpression: SimpleOrClaspedTerm "." IntegerLiteral
#line 1391 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 4103 "GrammarParser.cpp"
    break;

  case 158: // IndirectCallExpression: CallExpression "(" ")"
#line 1399 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4114 "GrammarParser.cpp"
    break;

  case 159: // IndirectCallExpression: CallExpression "(" Terms ")"
#line 1406 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4124 "GrammarParser.cpp"
    break;

  case 160: // IndirectCallExpression: CallExpression "(" error ")"
#line 1412 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 4132 "GrammarParser.cpp"
    break;

  case 161: // TypeCastingExpression: SimpleOrClaspedTerm "as" Type
#line 1420 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 4140 "GrammarParser.cpp"
    break;

  case 162: // LetExpression: "let" VariableBindings "in" Term
#line 1428 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4148 "GrammarParser.cpp"
    break;

  case 163: // ConditionalExpression: "if" Term "then" Term "else" Term
#line 1436 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4156 "GrammarParser.cpp"
    break;

  case 164: // ChooseExpression: "choose" AttributedVariables "in" Term "do" Term
#line 1444 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4164 "GrammarParser.cpp"
    break;

  case 165: // UniversalQuantifierExpression: "forall" AttributedVariables "in" Term "holds" Term
#line 1452 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4172 "GrammarParser.cpp"
    break;

  case 166: // ExistentialQuantifierExpression: "exists" AttributedVariables "in" Term "with" Term
#line 1460 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4180 "GrammarParser.cpp"
    break;

  case 167: // CardinalityExpression: "|" SimpleOrClaspedTerm "|"
#line 1468 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4188 "GrammarParser.cpp"
    break;

  case 168: // Literal: UndefinedLiteral
#line 1481 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 4196 "GrammarParser.cpp"
    break;

  case 169: // Literal: BooleanLiteral
#line 1485 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4204 "GrammarParser.cpp"
    break;

  case 170: // Literal: IntegerLiteral
#line 1489 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4212 "GrammarParser.cpp"
    break;

  case 171: // Literal: RationalLiteral
#line 1493 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4220 "GrammarParser.cpp"
    break;

  case 172: // Literal: DecimalLiteral
#line 1497 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4228 "GrammarParser.cpp"
    break;

  case 173: // Literal: BinaryLiteral
#line 1501 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4236 "GrammarParser.cpp"
    break;

  case 174: // Literal: StringLiteral
#line 1505 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4244 "GrammarParser.cpp"
    break;

  case 175: // Literal: ReferenceLiteral
#line 1509 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 4252 "GrammarParser.cpp"
    break;

  case 176: // Literal: ListLiteral
#line 1513 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 4260 "GrammarParser.cpp"
    break;

  case 177: // Literal: RangeLiteral
#line 1517 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 4268 "GrammarParser.cpp"
    break;

  case 178: // Literal: TupleLiteral
#line 1521 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 4276 "GrammarParser.cpp"
    break;

  case 179: // Literal: RecordLiteral
#line 1525 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 4284 "GrammarParser.cpp"
    break;

  case 180: // UndefinedLiteral: "undef"
#line 1533 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4293 "GrammarParser.cpp"
    break;

  case 181: // BooleanLiteral: "true"
#line 1542 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4303 "GrammarParser.cpp"
    break;

  case 182: // BooleanLiteral: "false"
#line 1548 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4313 "GrammarParser.cpp"
    break;

  case 183: // IntegerLiteral: "integer"
#line 1558 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4321 "GrammarParser.cpp"
    break;

  case 184: // RationalLiteral: "rational"
#line 1566 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4329 "GrammarParser.cpp"
    break;

  case 185: // DecimalLiteral: "decimal"
#line 1574 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4337 "GrammarParser.cpp"
    break;

  case 186: // BinaryLiteral: "binary"
#line 1582 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4345 "GrammarParser.cpp"
    break;

  case 187: // BinaryLiteral: "hexadecimal"
#line 1586 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4353 "GrammarParser.cpp"
    break;

  case 188: // StringLiteral: "string"
#line 1594 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4361 "GrammarParser.cpp"
    break;

  case 189: // ReferenceLiteral: "@" IdentifierPath
#line 1602 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4369 "GrammarParser.cpp"
    break;

  case 190: // ListLiteral: "[" "]"
#line 1610 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4380 "GrammarParser.cpp"
    break;

  case 191: // ListLiteral: "[" Terms "]"
#line 1617 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4390 "GrammarParser.cpp"
    break;

  case 192: // ListLiteral: "[" error "]"
#line 1623 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 4398 "GrammarParser.cpp"
    break;

  case 193: // RangeLiteral: "[" Term ".." Term "]"
#line 1631 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4408 "GrammarParser.cpp"
    break;

  case 194: // TupleLiteral: "(" Terms "," Term ")"
#line 1640 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4421 "GrammarParser.cpp"
    break;

  case 195: // RecordLiteral: "(" Assignments ")"
#line 1651 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4431 "GrammarParser.cpp"
    break;

  case 196: // Assignments: Assignments "," Assignment
#line 1660 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4442 "GrammarParser.cpp"
    break;

  case 197: // Assignments: Assignment
#line 1667 "../../obj/src/GrammarParser.y"
  {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4452 "GrammarParser.cpp"
    break;

  case 198: // Assignment: Identifier ":" Term
#line 1676 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4460 "GrammarParser.cpp"
    break;

  case 199: // Types: Types "," Type
#line 1688 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4471 "GrammarParser.cpp"
    break;

  case 200: // Types: Type
#line 1695 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4481 "GrammarParser.cpp"
    break;

  case 201: // Type: BasicType
#line 1704 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4489 "GrammarParser.cpp"
    break;

  case 202: // Type: TupleType
#line 1708 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4497 "GrammarParser.cpp"
    break;

  case 203: // Type: RecordType
#line 1712 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4505 "GrammarParser.cpp"
    break;

  case 204: // Type: TemplateType
#line 1716 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4513 "GrammarParser.cpp"
    break;

  case 205: // Type: RelationType
#line 1720 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4521 "GrammarParser.cpp"
    break;

  case 206: // Type: FixedSizedType
#line 1724 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4529 "GrammarParser.cpp"
    break;

  case 207: // BasicType: IdentifierPath
#line 1732 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4537 "GrammarParser.cpp"
    break;

  case 208: // TupleType: "(" Types "," Type ")"
#line 1740 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = Ast::make< TupleType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), subTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4548 "GrammarParser.cpp"
    break;

  case 209: // RecordType: "(" TypedVariables "," TypedVariable ")"
#line 1751 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = Ast::make< RecordType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4559 "GrammarParser.cpp"
    break;

  case 210: // TemplateType: IdentifierPath "<" Types ">"
#line 1762 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4567 "GrammarParser.cpp"
    break;

  case 211: // RelationType: IdentifierPath "<" MaybeFunctionParameters "->" Type ">"
#line 1770 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4575 "GrammarParser.cpp"
    break;

  case 212: // FixedSizedType: IdentifierPath "'" Term
#line 1778 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4583 "GrammarParser.cpp"
    break;

  case 213: // FunctionParameters: FunctionParameters "*" Type
#line 1790 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4594 "GrammarParser.cpp"
    break;

  case 214: // FunctionParameters: Type
#line 1797 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4604 "GrammarParser.cpp"
    break;

  case 215: // MaybeFunctionParameters: FunctionParameters
#line 1807 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 4612 "GrammarParser.cpp"
    break;

  case 216: // MaybeFunctionParameters: %empty
#line 1811 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 4620 "GrammarParser.cpp"
    break;

  case 217: // Parameters: Parameters "," TypedAttributedVariable
#line 1819 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4631 "GrammarParser.cpp"
    break;

  case 218: // Parameters: TypedAttributedVariable
#line 1826 "../../obj/src/GrammarParser.y"
  {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4641 "GrammarParser.cpp"
    break;

  case 219: // MaybeDefined: "defined" "{" Term "}"
#line 1840 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4649 "GrammarParser.cpp"
    break;

  case 220: // MaybeDefined: %empty
#line 1844 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 4657 "GrammarParser.cpp"
    break;

  case 221: // MaybeInitially: "=" "{" Initializers "}"
#line 1852 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4665 "GrammarParser.cpp"
    break;

  case 222: // MaybeInitially: %empty
#line 1856 "../../obj/src/GrammarParser.y"
  {
      const auto initializers = Ast::make< Initializers >( yylhs.location );
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
#line 4674 "GrammarParser.cpp"
    break;

  case 223: // Initializers: Initializers "," Initializer
#line 1865 "../../obj/src/GrammarParser.y"
  {
      auto initializers = yystack_[2].value.as < Initializers::Ptr > ();
      yystack_[0].value.as < Initializer::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4685 "GrammarParser.cpp"
    break;

  case 224: // Initializers: Initializer
#line 1872 "../../obj/src/GrammarParser.y"
  {
      auto initializers = Ast::make< Initializers >( yylhs.location );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4695 "GrammarParser.cpp"
    break;

  case 225: // Initializer: Term
#line 1882 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4704 "GrammarParser.cpp"
    break;

  case 226: // Initializer: "(" Term ")" "->" Term
#line 1887 "../../obj/src/GrammarParser.y"
  {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), arguments, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4714 "GrammarParser.cpp"
    break;

  case 227: // Initializer: TupleLiteral "->" Term
#line 1893 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto lbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto rbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, lbToken, arguments, rbToken, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4725 "GrammarParser.cpp"
    break;

  case 228: // Identifier: "identifier"
#line 1908 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 4733 "GrammarParser.cpp"
    break;

  case 229: // Identifier: "in"
#line 1912 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 4742 "GrammarParser.cpp"
    break;

  case 230: // IdentifierPath: IdentifierPath "::" Identifier
#line 1921 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < Ast::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 4753 "GrammarParser.cpp"
    break;

  case 231: // IdentifierPath: Identifier
#line 1928 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4761 "GrammarParser.cpp"
    break;

  case 232: // Variable: TypedVariable
#line 1940 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4769 "GrammarParser.cpp"
    break;

  case 233: // Variable: Identifier
#line 1944 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 4778 "GrammarParser.cpp"
    break;

  case 234: // AttributedVariables: AttributedVariables "," AttributedVariable
#line 1953 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 4789 "GrammarParser.cpp"
    break;

  case 235: // AttributedVariables: AttributedVariable
#line 1960 "../../obj/src/GrammarParser.y"
  {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 4799 "GrammarParser.cpp"
    break;

  case 236: // TypedVariables: TypedVariables "," TypedVariable
#line 1970 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4810 "GrammarParser.cpp"
    break;

  case 237: // TypedVariables: TypedVariable
#line 1977 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4820 "GrammarParser.cpp"
    break;

  case 238: // TypedVariable: Identifier ":" Type
#line 1987 "../../obj/src/GrammarParser.y"
  {
      auto variable = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4829 "GrammarParser.cpp"
    break;

  case 239: // AttributedVariable: Attributes Variable
#line 1996 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4839 "GrammarParser.cpp"
    break;

  case 240: // AttributedVariable: Variable
#line 2002 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4847 "GrammarParser.cpp"
    break;

  case 241: // TypedAttributedVariable: Attributes TypedVariable
#line 2010 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4857 "GrammarParser.cpp"
    break;

  case 242: // TypedAttributedVariable: TypedVariable
#line 2016 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4865 "GrammarParser.cpp"
    break;

  case 243: // VariableBindings: VariableBindings "," VariableBinding
#line 2028 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4876 "GrammarParser.cpp"
    break;

  case 244: // VariableBindings: VariableBinding
#line 2035 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4886 "GrammarParser.cpp"
    break;

  case 245: // VariableBinding: AttributedVariable "=" Term
#line 2044 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4894 "GrammarParser.cpp"
    break;

  case 246: // LocalFunctionDefinitions: LocalFunctionDefinitions "," AttributedLocalFunctionDefinition
#line 2056 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[2].value.as < FunctionDefinitions::Ptr > ();
      yystack_[0].value.as < FunctionDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 4905 "GrammarParser.cpp"
    break;

  case 247: // LocalFunctionDefinitions: AttributedLocalFunctionDefinition
#line 2063 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< FunctionDefinitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 4915 "GrammarParser.cpp"
    break;

  case 248: // AttributedLocalFunctionDefinition: Attributes LocalFunctionDefinition
#line 2072 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 4925 "GrammarParser.cpp"
    break;

  case 249: // AttributedLocalFunctionDefinition: LocalFunctionDefinition
#line 2078 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 4933 "GrammarParser.cpp"
    break;

  case 250: // AttributedLocalFunctionDefinition: error
#line 2082 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = nullptr;
  }
#line 4941 "GrammarParser.cpp"
    break;

  case 251: // LocalFunctionDefinition: Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 2089 "../../obj/src/GrammarParser.y"
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
#line 4957 "GrammarParser.cpp"
    break;

  case 252: // Attributes: Attributes Attribute
#line 2109 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4967 "GrammarParser.cpp"
    break;

  case 253: // Attributes: Attribute
#line 2115 "../../obj/src/GrammarParser.y"
  {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4977 "GrammarParser.cpp"
    break;

  case 254: // Attribute: "[" BasicAttribute "]"
#line 2124 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4988 "GrammarParser.cpp"
    break;

  case 255: // Attribute: "[" ExpressionAttribute "]"
#line 2131 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4999 "GrammarParser.cpp"
    break;

  case 256: // Attribute: "[" error "]"
#line 2138 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 5007 "GrammarParser.cpp"
    break;

  case 257: // BasicAttribute: Identifier
#line 2145 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5015 "GrammarParser.cpp"
    break;

  case 258: // ExpressionAttribute: Identifier Term
#line 2152 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5023 "GrammarParser.cpp"
    break;


#line 5027 "GrammarParser.cpp"

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


  const short Parser::yypact_ninf_ = -357;

  const short Parser::yytable_ninf_ = -215;

  const short
  Parser::yypact_[] =
  {
      52,  -357,    20,    42,   337,    56,  -357,    60,  -357,  -357,
    1952,   100,   119,  -357,  -357,   -20,     1,     1,     1,     1,
       1,     1,     1,     1,    -5,     1,   123,  -357,  -357,  -357,
    -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,
    -357,   589,  -357,  -357,  -357,    -1,    -1,    -1,  1952,    -1,
    -357,  -357,  -357,  1952,   250,   250,  1472,  1212,   250,     1,
    -357,  -357,  -357,  -357,  -357,  -357,  2709,   -10,  -357,    45,
    -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,
    -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,
    -357,  -357,  -357,  -357,  -357,   129,  -357,  -357,  2017,   133,
     -12,   161,   168,   180,   199,   189,    -9,   204,   239,    -5,
     243,  -357,  -357,  -357,  -357,  -357,  -357,    50,   247,  -357,
    -357,   249,  -357,  -357,   257,     6,  -357,    -1,     8,  -357,
      14,  2246,    38,  -357,  -357,  -357,   209,   246,  2464,     7,
    -357,   252,   258,  -357,   202,  2499,    90,   133,  1952,  1952,
    1952,  1952,  1952,  1952,  1952,  1952,  1952,  1952,  1952,  1952,
    1952,  1952,  1952,  1952,  1952,    -5,    -7,  1277,  1342,     1,
    1472,  2709,   248,    39,  -357,    12,    -5,   263,  1822,    18,
      -5,    -5,    -8,  1952,     1,   264,   266,   260,  -357,   249,
     169,   262,  -357,   270,    -5,    -5,  1952,    -5,    -5,  1952,
    1952,    -1,  -357,  1952,    -1,  1952,  1952,  1952,  -357,  1952,
    -357,  -357,     1,  1952,  -357,  -357,  1952,  1952,  -357,   220,
     731,  2774,  2744,   211,   211,   328,   290,   290,   261,   261,
     261,  -357,  2744,   328,   290,   290,  -357,  -357,   275,   299,
    -357,   171,  2709,   301,  -357,   179,  -357,  2534,  1952,  -357,
    2017,   302,   182,   249,  -357,  -357,    -1,   309,    21,   872,
     942,  -357,    -1,    24,    -1,    -1,  1822,  1952,  1952,  1952,
    1012,  1082,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,
    -357,  -357,  -357,  -357,  -357,  -357,   289,    69,   287,   311,
     196,   315,  -357,  -357,  2709,  -357,    19,   135,    -5,     1,
      49,   319,   238,   120,   307,   306,  -357,  -357,   312,  -357,
    2709,  2709,  -357,  2394,  -357,  2084,  2323,  2429,  2569,  -357,
     252,  2709,  2709,  2604,  1407,  -357,  -357,  -357,  -357,   313,
    2709,  -357,   317,   325,    -1,  -357,  1952,  -357,  -357,   112,
    -357,    -1,   365,  1542,  -357,   368,  1612,   101,  -357,   341,
     121,  -357,  -357,    -1,   122,   127,  -357,  2285,  2359,  2125,
     345,  1682,   327,  1752,  1952,    71,    94,  1822,   355,  -357,
    -357,    11,     1,     1,   355,  -357,  -357,  -357,    27,  -357,
     359,   360,  -357,  -357,    49,   357,   364,    -5,  -357,    -5,
      -5,    -5,  1952,  1952,  1952,  1952,  -357,  -357,   370,  -357,
     198,  1952,    -5,    -5,  -357,  2709,  -357,    21,  -357,  -357,
    -357,  -357,  -357,  -357,  1822,    -5,  1822,    24,  -357,  1952,
    1952,  1822,   371,  1822,  -357,  -357,  -357,  -357,  2709,  1822,
      -5,  1822,    -5,  -357,   213,  -357,  -357,   164,   105,   218,
    -357,  -357,  -357,  -357,  -357,  -357,    49,  -357,  -357,   353,
     407,  2709,  2709,  2709,  2709,  -357,  -357,  2709,   375,   378,
    -357,  -357,   358,  -357,  -357,  2043,  2166,   398,  1147,  -357,
    -357,   381,  -357,   382,   418,    -5,    -5,    78,   379,  -357,
     387,   384,  1952,  1952,    -5,  1822,  1952,  1822,  1822,   380,
     388,   389,  1887,  -357,  2639,  1822,  1822,  -357,   372,   377,
    -357,  -357,  -357,  -357,  1952,   395,  -357,  2709,  2709,   407,
    -357,  2207,  -357,  -357,  -357,  1822,  1822,  -357,  -357,  1822,
    -357,  -357,    -5,    -5,  2674,  2017,   384,  1822,  -357,  -357,
    -357,  -357,  -357,  -357,   181,  -357,  -357,  -357
  };

  const short
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   253,     0,   229,   228,
     257,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,     8,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     0,     3,   252,   256,     0,     0,     0,     0,     0,
     180,   182,   181,     0,     0,     0,     0,     0,     0,     0,
     186,   187,   183,   184,   185,   188,   258,   112,   114,   123,
     146,   147,   124,   148,   113,   115,   116,   117,   118,   119,
     120,   125,   168,   169,   170,   171,   172,   173,   174,   175,
     176,   177,   178,   179,   231,   149,   254,   255,     0,    22,
       0,     0,     0,   231,    41,     0,    44,     0,     0,     0,
       0,   201,   202,   203,   204,   205,   206,   207,     0,     5,
       7,   233,   240,   232,     0,     0,   244,     0,     0,   235,
       0,     0,     0,   145,   126,   127,     0,     0,   111,     0,
     197,   231,     0,   190,     0,   111,     0,   189,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   225,   178,     0,   224,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   200,   231,
     207,     0,   237,     0,     0,   216,     0,   216,     0,     0,
       0,     0,   239,     0,     0,     0,     0,     0,   122,     0,
     121,   195,     0,     0,   192,   191,     0,     0,   167,   142,
     140,   141,   144,   128,   129,   135,   136,   137,   130,   131,
     132,   133,   143,   134,   138,   139,   161,   157,   153,     0,
     158,     0,   111,     0,   150,     0,   230,   111,     0,    23,
       0,     0,     0,     0,   242,   218,     0,     0,     0,     0,
       0,    83,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    28,    70,    71,    72,    73,    74,    75,    76,
      77,    78,    79,    80,    81,    82,     0,   108,   146,     0,
       0,     0,    40,    42,    43,    45,     0,     0,     0,     0,
       0,     0,     0,   200,   215,     0,   212,   214,     0,   238,
     245,   162,   243,     0,   234,     0,     0,     0,   110,   196,
       0,   198,   110,     0,     0,   160,   159,   152,   151,   121,
     227,   223,     0,     0,     0,   241,     0,    37,    39,     0,
      35,     0,     0,     0,    69,     0,     0,     0,   250,     0,
       0,   247,   249,     0,     0,     0,    98,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
      50,     0,     0,     0,     0,    55,    57,    59,     0,    53,
     199,   236,    62,    63,    65,     0,     0,     0,   210,     0,
       0,     0,     0,     0,     0,     0,   194,   193,     0,   154,
       0,     0,     0,     0,   217,    25,    24,     0,    36,   106,
     104,    68,   102,   100,     0,   216,     0,     0,   248,     0,
       0,     0,     0,     0,   101,    99,   105,   103,   107,     0,
       0,     0,     0,    29,     0,    46,    49,     0,     0,     0,
      51,    58,   208,   209,    64,    61,     0,   199,   213,     0,
     220,   165,   164,   163,   166,   156,   155,   226,     0,     0,
      38,    93,     0,    94,   246,     0,     0,    84,     0,   109,
      32,     0,    30,     0,     0,   216,   216,     0,     0,   211,
       0,   222,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    89,     0,     0,     0,    47,     0,     0,
      54,    56,    52,    60,     0,     0,    34,    27,    26,   220,
      95,     0,    97,    85,    87,     0,     0,    86,    88,     0,
      33,    31,     0,     0,     0,     0,   222,     0,    90,    91,
      92,    66,    67,   219,     0,   251,    96,   221
  };

  const short
  Parser::yypgoto_[] =
  {
    -357,  -357,  -357,  -357,   412,   411,  -357,  -357,  -286,  -259,
    -280,    46,  -357,  -357,  -357,  -357,  -357,  -357,    83,  -357,
    -357,    79,  -357,  -357,  -357,  -356,   -21,  -122,   316,  -357,
    -357,  -357,  -357,   -34,  -357,  -357,  -357,  -357,  -357,  -357,
    -357,  -357,  -357,  -357,   -50,    47,    58,  -357,   225,   362,
    -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,  -357,
    -357,  -357,  -357,   293,  -357,  -357,  -357,  -357,  -357,  -357,
    -357,   -97,  -357,  -357,   251,   269,   -22,  -357,  -357,  -357,
    -357,  -357,  -357,  -357,  -194,   291,   -41,   -55,   -52,   226,
     503,   -15,   348,   -39,  -357,   -86,   -33,   143,   216,   279,
    -357,    65,   130,    48,    10,  -357,  -357
  };

  const short
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    26,    27,    28,    29,    30,    31,    32,
      33,   338,   339,    34,    35,    36,    37,    38,   370,   371,
      39,   377,   378,    40,   384,   385,   379,   343,   344,   273,
     274,   275,   492,   493,   276,   277,   278,   279,   280,   281,
     282,   283,   284,   285,   137,   171,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,   139,   140,   187,   307,   111,   112,   113,
     114,   115,   116,   304,   305,   252,   481,   506,   173,   174,
      94,    95,   122,   128,   191,   123,   129,   255,   125,   126,
     350,   351,   352,   127,     6,    11,    12
  };

  const short
  Parser::yytable_[] =
  {
      99,   172,   110,   308,   104,     8,   106,   144,   130,   117,
     132,   375,   124,   251,   382,    43,   369,     8,     8,   289,
       8,     7,   337,   192,     8,   348,     8,    25,   444,   165,
     184,   200,   372,   203,   373,    25,    98,     8,   376,   205,
     175,   383,    13,     8,   147,     8,     8,   109,     5,     8,
     169,    43,    41,     2,    16,     1,    18,    66,   293,    42,
     211,   176,   166,   207,   194,   368,     2,     9,   435,   201,
     212,   204,     2,   368,    41,     2,    62,   204,     2,     9,
       9,   374,     9,   372,   440,   373,     9,   188,     9,   254,
     478,   369,   375,   254,   190,   131,   249,   167,   382,     9,
     133,   204,   250,   138,   145,     9,     2,     9,     9,   169,
       2,     9,   134,   135,   195,    44,   146,   241,   245,   376,
     196,   167,   429,    -2,    14,   383,   414,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    43,   346,    25,
     372,  -123,   373,   236,   430,   431,   416,   419,   361,   363,
     190,   218,   420,   172,   257,    96,   178,   179,   291,   292,
     382,   190,   166,   476,   201,   190,   190,   432,   124,   406,
     335,   314,   301,   303,    97,   407,   309,     2,   180,   190,
     190,   168,   190,   190,   417,   204,  -214,   383,   169,   374,
     204,   500,   169,  -214,   497,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     234,   235,   177,   381,   242,   242,   175,   247,   501,   178,
     179,   462,   475,   256,   326,   354,   355,   256,   169,   124,
     294,   181,   328,   195,   216,   333,   286,   176,   537,   196,
     183,   180,   216,   306,   250,   334,   310,   311,   254,   366,
     313,   456,   315,   316,   317,   185,   318,   215,   182,   334,
     321,   216,   208,   322,   323,   216,    43,     2,   474,   152,
     153,   154,     2,   477,   400,     8,   380,   157,   158,   159,
     160,   498,   499,   190,   155,   156,   157,   158,   159,   160,
     186,    50,    51,    52,   193,   330,   162,   163,   164,    54,
      55,   387,    56,   388,    57,   197,   341,   198,   199,   209,
     213,   353,    59,   214,   357,   358,   359,   286,   286,   258,
     296,   248,   297,   298,   286,   299,   300,   324,   286,   286,
     160,    60,    61,    62,    63,    64,    65,     9,    14,   152,
     153,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    43,   325,    25,   327,   332,   157,   158,   159,   160,
     336,   166,   364,    43,   365,   447,   367,   448,   449,   450,
     386,   242,   190,   389,   190,   190,   190,   152,   153,   390,
     458,   459,   256,   405,   409,   391,   401,   190,   190,   412,
     402,     2,   155,   156,   157,   158,   159,   160,   403,   415,
     190,   286,   424,   287,   286,   163,   164,   426,   471,     2,
     473,   428,   442,   443,   445,   190,   434,   190,   479,   286,
     446,   286,   439,   455,   480,   286,   482,   468,   172,   483,
     488,   484,   495,   496,    25,   505,   503,   514,   119,   451,
     452,   453,   454,   504,    43,   522,   515,   516,   457,    43,
     523,   525,   120,   460,   436,   341,   502,   441,   518,   237,
     190,   190,   509,   319,   302,   353,   465,   466,   526,   190,
     290,   535,   286,   534,   286,   202,   331,   404,   347,   286,
     312,   286,   464,   418,   287,   287,     0,   286,     0,   286,
       0,   287,     0,     0,   272,   287,   287,     0,     0,     0,
     531,   532,     0,     0,     0,    10,     0,   190,   190,     0,
       0,     0,     0,     0,     0,   494,     0,     0,     0,   100,
     101,   102,   103,   105,     0,   107,   108,     0,   118,   507,
     508,     0,     0,   511,     0,     0,     0,     0,     0,   494,
     288,     0,     0,   286,     0,   286,   286,     0,   121,   121,
     121,   524,   121,   286,   286,     0,     0,     0,     0,   141,
       0,     0,     0,     0,     0,     0,     0,     0,   287,     0,
       0,   287,     0,   286,   286,     0,     0,   286,     0,     0,
       0,     0,   356,     0,     0,   286,   287,     0,   287,     0,
       0,     0,   287,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     0,     0,    25,     0,     0,     0,     0,
       0,     0,   189,     0,     0,     0,     0,     0,     0,     0,
       0,   288,   288,     0,     0,     0,     0,     0,   288,     0,
     121,     0,   288,   288,     0,     0,     0,     0,     0,   287,
       0,   287,     0,     2,     0,     0,   287,     0,   287,     0,
       0,     0,     0,     0,   287,     0,   287,     0,     0,   411,
       0,     0,   411,     0,     0,     0,     0,     0,     0,   238,
       0,     0,   246,   141,     0,     0,     0,   411,   253,   411,
       0,     0,   253,   433,     0,   246,     0,   295,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   121,   288,     0,   121,   288,     0,
     287,     0,   287,   287,     0,   320,     0,     0,     0,     0,
     287,   287,     0,   288,     0,   288,     0,     0,     0,   288,
     461,     0,   463,     0,     0,     0,     0,   467,     0,   469,
     287,   287,     0,     0,   287,   470,     0,   472,     0,     0,
       0,     0,   287,     0,     0,     0,     0,     0,     0,   253,
       0,   340,     0,     0,     0,   121,   349,   121,   121,     0,
       0,     0,     0,     0,     0,   148,   288,   150,   288,     0,
     152,   153,   154,   288,     0,   288,     0,     0,     0,     0,
       0,   288,     0,   288,     0,   155,   156,   157,   158,   159,
     160,   510,   253,   512,   513,     0,     0,   162,   163,   164,
       0,   520,   521,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   528,   529,     0,     0,   530,     0,   253,     0,     0,
       0,     0,     0,   536,   408,     0,     0,   288,     0,   288,
     288,     0,     0,     0,     0,     0,   349,   288,   288,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   342,     0,   437,   438,   288,   288,     0,
       0,   288,     0,     0,     0,     0,     0,     0,     0,   288,
     259,     0,   260,     0,   261,   262,   263,     8,   264,   265,
     266,     0,   267,     0,     0,   268,     0,     0,     0,     0,
     340,     0,   269,    50,    51,    52,     0,     0,     0,     0,
     349,    54,    55,     0,    56,     0,    57,     0,   270,     0,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,   345,     0,     0,     0,     0,     0,     0,
       0,   271,     0,    60,    61,    62,    63,    64,    65,     9,
     259,     0,   260,     0,   261,   262,   263,     8,   264,   265,
     266,     0,   267,     0,     0,   268,     0,     0,     0,     0,
       0,     0,   269,    50,    51,    52,     0,     0,     0,     0,
       0,    54,    55,     0,    56,     0,    57,     0,   270,     0,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,   360,     0,     0,     0,     0,     0,     0,
       0,   271,     0,    60,    61,    62,    63,    64,    65,     9,
     259,     0,   260,     0,   261,   262,   263,     8,   264,   265,
     266,     0,   267,     0,     0,   268,     0,     0,     0,     0,
       0,     0,   269,    50,    51,    52,     0,     0,     0,     0,
       0,    54,    55,     0,    56,     0,    57,     0,   270,     0,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,   362,     0,     0,     0,     0,     0,     0,
       0,   271,     0,    60,    61,    62,    63,    64,    65,     9,
     259,     0,   260,     0,   261,   262,   263,     8,   264,   265,
     266,     0,   267,     0,     0,   268,     0,     0,     0,     0,
       0,     0,   269,    50,    51,    52,     0,     0,     0,     0,
       0,    54,    55,     0,    56,     0,    57,     0,   270,     0,
       0,     0,     0,     0,    59,     0,     0,     0,   489,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   271,     0,    60,    61,    62,    63,    64,    65,     9,
      45,     0,     8,    46,    47,     0,     0,    48,     0,     0,
       0,     0,   490,     0,    49,     0,     0,     0,    50,    51,
      52,     0,     0,     0,     0,    53,    54,    55,     0,    56,
       0,    57,     0,     0,     0,     0,     0,   491,    58,    59,
       0,     0,     0,   142,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,    61,
      62,    63,    64,    65,     9,    45,     0,     8,    46,    47,
       0,     0,    48,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,    50,    51,    52,     0,     0,     0,     0,
      53,    54,    55,     0,    56,     0,    57,   143,     0,     0,
       0,     0,     0,    58,    59,     0,     0,     0,   239,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    61,    62,    63,    64,    65,     9,
      45,     0,     8,    46,    47,     0,     0,    48,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,    50,    51,
      52,     0,     0,     0,     0,    53,    54,    55,     0,    56,
     240,    57,     0,     0,     0,     0,     0,     0,    58,    59,
       0,     0,     0,   243,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,    61,
      62,    63,    64,    65,     9,    45,     0,     8,    46,    47,
       0,     0,    48,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,    50,    51,    52,     0,     0,     0,     0,
      53,    54,    55,     0,    56,   244,    57,     0,     0,     0,
       0,     0,     0,    58,    59,     0,     0,     0,   398,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    61,    62,    63,    64,    65,     9,
      45,     0,     8,    46,    47,     0,     0,    48,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,    50,    51,
      52,     0,     0,     0,     0,    53,    54,    55,     0,    56,
     399,    57,     0,     0,     0,     0,     0,     0,    58,    59,
       0,     0,     0,   136,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,    61,
      62,    63,    64,    65,     9,    45,     0,     8,    46,    47,
       0,     0,    48,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,    50,    51,    52,     0,     0,     0,     0,
      53,    54,    55,     0,    56,     0,    57,     0,     0,     0,
       0,     0,     0,    58,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    61,    62,    63,    64,    65,     9,
     259,   410,   260,     0,   261,   262,   263,     8,   264,   265,
     266,     0,   267,     0,     0,   268,     0,     0,     0,     0,
       0,     0,   269,    50,    51,    52,     0,     0,     0,     0,
       0,    54,    55,     0,    56,     0,    57,     0,   270,     0,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   271,     0,    60,    61,    62,    63,    64,    65,     9,
     259,     0,   260,   413,   261,   262,   263,     8,   264,   265,
     266,     0,   267,     0,     0,   268,     0,     0,     0,     0,
       0,     0,   269,    50,    51,    52,     0,     0,     0,     0,
       0,    54,    55,     0,    56,     0,    57,     0,   270,     0,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   271,     0,    60,    61,    62,    63,    64,    65,     9,
     259,     0,   260,     0,   261,   262,   263,     8,   264,   265,
     266,     0,   267,     0,     0,   268,     0,     0,     0,     0,
       0,     0,   269,    50,    51,    52,     0,     0,     0,     0,
       0,    54,    55,     0,    56,     0,    57,     0,   270,   425,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   271,     0,    60,    61,    62,    63,    64,    65,     9,
     259,     0,   260,     0,   261,   262,   263,     8,   264,   265,
     266,     0,   267,     0,     0,   268,     0,     0,     0,     0,
       0,     0,   269,    50,    51,    52,     0,     0,     0,     0,
       0,    54,    55,     0,    56,     0,    57,     0,   270,     0,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   271,   427,    60,    61,    62,    63,    64,    65,     9,
     259,     0,   260,     0,   261,   262,   263,     8,   264,   265,
     266,     0,   267,     0,     0,   268,     0,     0,     0,     0,
       0,     0,   269,    50,    51,    52,     0,     0,     0,     0,
       0,    54,    55,     0,    56,     0,    57,     0,   270,     0,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   271,     0,    60,    61,    62,    63,    64,    65,     9,
      45,     0,     8,    46,    47,     0,     0,    48,     0,     0,
       0,     0,   490,     0,    49,     0,     0,     0,    50,    51,
      52,     0,     0,     0,     0,    53,    54,    55,     0,    56,
       0,    57,     0,     0,   517,     0,     0,   491,    58,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,    61,
      62,    63,    64,    65,     9,    45,     0,     8,    46,    47,
       0,     0,    48,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,    50,    51,    52,     0,     0,     0,     0,
      53,    54,    55,     0,    56,     0,    57,     0,     0,     0,
       0,     0,     0,    58,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    61,    62,    63,    64,    65,     9,
      45,     0,     8,    46,    47,     0,     0,    48,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,    50,    51,
      52,     0,     0,     0,     0,    53,    54,    55,     0,   170,
       0,    57,   485,     0,     0,     0,     0,     0,    58,    59,
       0,   486,     0,     0,     0,     0,     0,   148,   149,   150,
     151,     0,   152,   153,   154,     0,     0,     0,    60,    61,
      62,    63,    64,    65,     9,     0,     0,   155,   156,   157,
     158,   159,   160,   393,     0,     0,     0,   161,     0,   162,
     163,   164,     0,     0,     0,     0,     0,     0,   148,   149,
     150,   151,     0,   152,   153,   154,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   155,   156,
     157,   158,   159,   160,   423,     0,     0,     0,   161,     0,
     162,   163,   164,     0,     0,     0,     0,     0,     0,   148,
     149,   150,   151,     0,   152,   153,   154,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   155,
     156,   157,   158,   159,   160,   487,     0,     0,     0,   161,
       0,   162,   163,   164,     0,     0,     0,     0,     0,     0,
     148,   149,   150,   151,     0,   152,   153,   154,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,   527,     0,     0,     0,
     161,     0,   162,   163,   164,     0,     0,     0,     0,     0,
       0,   148,   149,   150,   151,     0,   152,   153,   154,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   155,   156,   157,   158,   159,   160,   206,     0,     0,
       0,   161,     0,   162,   163,   164,     0,     0,     0,     0,
     148,   149,   150,   151,     0,   152,   153,   154,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     155,   156,   157,   158,   159,   160,   421,     0,     0,     0,
     161,     0,   162,   163,   164,     0,     0,     0,     0,   148,
     149,   150,   151,     0,   152,   153,   154,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   155,
     156,   157,   158,   159,   160,   394,     0,     0,     0,   161,
       0,   162,   163,   164,     0,     0,     0,   148,   149,   150,
     151,     0,   152,   153,   154,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   155,   156,   157,
     158,   159,   160,   422,     0,     0,     0,   161,     0,   162,
     163,   164,     0,   148,   149,   150,   151,     0,   152,   153,
     154,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,   156,   157,   158,   159,   160,     0,
     392,     0,     0,   161,     0,   162,   163,   164,   148,   149,
     150,   151,     0,   152,   153,   154,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   155,   156,
     157,   158,   159,   160,     0,     0,     0,   395,   161,     0,
     162,   163,   164,   148,   149,   150,   151,     0,   152,   153,
     154,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,   156,   157,   158,   159,   160,     0,
       0,     0,     0,   161,     0,   162,   163,   164,   148,   149,
     150,   151,     0,   152,   153,   154,     0,   210,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   155,   156,
     157,   158,   159,   160,     0,     0,     0,     0,   161,     0,
     162,   163,   164,   148,   149,   150,   151,     0,   152,   153,
     154,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,   156,   157,   158,   159,   160,     0,
     217,     0,     0,   161,     0,   162,   163,   164,   148,   149,
     150,   151,     0,   152,   153,   154,     0,   329,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   155,   156,
     157,   158,   159,   160,     0,     0,     0,     0,   161,     0,
     162,   163,   164,   148,   149,   150,   151,     0,   152,   153,
     154,     0,   396,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,   156,   157,   158,   159,   160,     0,
       0,     0,     0,   161,     0,   162,   163,   164,   148,   149,
     150,   151,     0,   152,   153,   154,     0,     0,     0,   397,
       0,     0,     0,     0,     0,     0,     0,     0,   155,   156,
     157,   158,   159,   160,     0,     0,     0,     0,   161,     0,
     162,   163,   164,   148,   149,   150,   151,     0,   152,   153,
     154,     0,     0,     0,     0,     0,     0,   519,     0,     0,
       0,     0,     0,   155,   156,   157,   158,   159,   160,     0,
       0,     0,     0,   161,     0,   162,   163,   164,   148,   149,
     150,   151,     0,   152,   153,   154,     0,     0,     0,     0,
       0,   533,     0,     0,     0,     0,     0,     0,   155,   156,
     157,   158,   159,   160,     0,     0,     0,     0,   161,     0,
     162,   163,   164,   148,   149,   150,   151,     0,   152,   153,
     154,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,   156,   157,   158,   159,   160,     0,
       0,     0,     0,   161,     0,   162,   163,   164,   148,   149,
     150,     0,     0,   152,   153,   154,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   155,   156,
     157,   158,   159,   160,     0,     0,     0,     0,   148,     0,
     162,   163,   164,   152,   153,   154,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   155,   156,
     157,   158,   159,   160,     0,     0,     0,     0,     0,     0,
     162,   163,   164
  };

  const short
  Parser::yycheck_[] =
  {
      15,    98,    24,   197,    19,    25,    21,    57,    47,    24,
      49,   297,    45,     1,   300,     5,   296,    25,    25,     1,
      25,     1,     1,   109,    25,     1,    25,    16,   384,    39,
      39,    25,     5,    25,     7,    16,    56,    25,   297,    25,
      52,   300,     0,    25,    59,    25,    25,    52,     0,    25,
      59,    41,     4,    54,     5,     3,     7,    10,    66,     3,
      53,    73,    72,    25,    14,    54,    54,    87,    57,    63,
      63,    63,    54,    54,    26,    54,    83,    63,    54,    87,
      87,    54,    87,     5,    57,     7,    87,   109,    87,   175,
     446,   371,   378,   179,   109,    48,    57,    52,   384,    87,
      53,    63,    63,    56,    57,    87,    54,    87,    87,    59,
      54,    87,    54,    55,    64,    55,    58,   167,   168,   378,
      70,    52,    51,     0,     1,   384,    25,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,   127,   260,    16,
       5,    72,     7,   165,    73,    51,    25,    25,   270,   271,
     165,    61,    25,   250,   176,    55,    51,    52,   180,   181,
     446,   176,    72,    58,    63,   180,   181,    73,   201,    57,
     256,   204,   194,   195,    55,    63,   198,    54,    73,   194,
     195,    52,   197,   198,    63,    63,    66,   446,    59,    54,
      63,   477,    59,    73,   474,   148,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,    51,   299,   167,   168,    52,   170,   477,    51,
      52,   415,    58,   175,    53,   264,   265,   179,    59,   262,
     183,    51,    53,    64,    63,    53,   178,    73,    57,    70,
      51,    73,    63,   196,    63,    63,   199,   200,   334,    53,
     203,    53,   205,   206,   207,    51,   209,    55,    59,    63,
     213,    63,    53,   216,   217,    63,   256,    54,    55,    49,
      50,    51,    54,    55,   324,    25,   298,    66,    67,    68,
      69,   475,   476,   298,    64,    65,    66,    67,    68,    69,
      51,    41,    42,    43,    51,   248,    76,    77,    78,    49,
      50,    63,    52,    65,    54,    58,   258,    58,    51,    63,
      58,   263,    62,    55,   267,   268,   269,   259,   260,    56,
      56,    73,    56,    63,   266,    63,    56,    52,   270,   271,
      69,    81,    82,    83,    84,    85,    86,    87,     1,    49,
      50,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   341,    53,    16,    53,    53,    66,    67,    68,    69,
      51,    72,    75,   353,    53,   387,    51,   389,   390,   391,
      51,   324,   387,    66,   389,   390,   391,    49,    50,    73,
     402,   403,   334,   336,    19,    73,    73,   402,   403,    21,
      73,    54,    64,    65,    66,    67,    68,    69,    73,    58,
     415,   343,    57,   178,   346,    77,    78,    80,   430,    54,
     432,   364,    53,    53,    57,   430,   368,   432,    65,   361,
      56,   363,   374,    53,    17,   367,    51,    56,   525,    51,
      32,    73,    51,    51,    16,    51,    57,    57,    26,   392,
     393,   394,   395,    56,   434,    73,    58,    58,   401,   439,
      73,    56,    41,   407,   371,   407,   477,   378,   492,   166,
     475,   476,   484,   212,   195,   417,   419,   420,   509,   484,
     179,   526,   414,   525,   416,   127,   250,   334,   262,   421,
     201,   423,   417,   353,   259,   260,    -1,   429,    -1,   431,
      -1,   266,    -1,    -1,   178,   270,   271,    -1,    -1,    -1,
     522,   523,    -1,    -1,    -1,     2,    -1,   522,   523,    -1,
      -1,    -1,    -1,    -1,    -1,   468,    -1,    -1,    -1,    16,
      17,    18,    19,    20,    -1,    22,    23,    -1,    25,   482,
     483,    -1,    -1,   486,    -1,    -1,    -1,    -1,    -1,   492,
     178,    -1,    -1,   485,    -1,   487,   488,    -1,    45,    46,
      47,   504,    49,   495,   496,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   343,    -1,
      -1,   346,    -1,   515,   516,    -1,    -1,   519,    -1,    -1,
      -1,    -1,   266,    -1,    -1,   527,   361,    -1,   363,    -1,
      -1,    -1,   367,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    -1,    -1,    16,    -1,    -1,    -1,    -1,
      -1,    -1,   109,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   259,   260,    -1,    -1,    -1,    -1,    -1,   266,    -1,
     127,    -1,   270,   271,    -1,    -1,    -1,    -1,    -1,   414,
      -1,   416,    -1,    54,    -1,    -1,   421,    -1,   423,    -1,
      -1,    -1,    -1,    -1,   429,    -1,   431,    -1,    -1,   343,
      -1,    -1,   346,    -1,    -1,    -1,    -1,    -1,    -1,   166,
      -1,    -1,   169,   170,    -1,    -1,    -1,   361,   175,   363,
      -1,    -1,   179,   367,    -1,   182,    -1,   184,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   201,   343,    -1,   204,   346,    -1,
     485,    -1,   487,   488,    -1,   212,    -1,    -1,    -1,    -1,
     495,   496,    -1,   361,    -1,   363,    -1,    -1,    -1,   367,
     414,    -1,   416,    -1,    -1,    -1,    -1,   421,    -1,   423,
     515,   516,    -1,    -1,   519,   429,    -1,   431,    -1,    -1,
      -1,    -1,   527,    -1,    -1,    -1,    -1,    -1,    -1,   256,
      -1,   258,    -1,    -1,    -1,   262,   263,   264,   265,    -1,
      -1,    -1,    -1,    -1,    -1,    44,   414,    46,   416,    -1,
      49,    50,    51,   421,    -1,   423,    -1,    -1,    -1,    -1,
      -1,   429,    -1,   431,    -1,    64,    65,    66,    67,    68,
      69,   485,   299,   487,   488,    -1,    -1,    76,    77,    78,
      -1,   495,   496,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   515,   516,    -1,    -1,   519,    -1,   334,    -1,    -1,
      -1,    -1,    -1,   527,   341,    -1,    -1,   485,    -1,   487,
     488,    -1,    -1,    -1,    -1,    -1,   353,   495,   496,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,   372,   373,   515,   516,    -1,
      -1,   519,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   527,
      18,    -1,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
     407,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
     417,    49,    50,    -1,    52,    -1,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      18,    -1,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    50,    -1,    52,    -1,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      18,    -1,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    50,    -1,    52,    -1,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      18,    -1,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    50,    -1,    52,    -1,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      23,    -1,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    35,    -1,    37,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    61,    62,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    23,    -1,    25,    26,    27,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    52,    -1,    54,    55,    -1,    -1,
      -1,    -1,    -1,    61,    62,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      23,    -1,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    23,    -1,    25,    26,    27,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      23,    -1,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      53,    54,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    23,    -1,    25,    26,    27,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    52,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      18,    19,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    50,    -1,    52,    -1,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      18,    -1,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    50,    -1,    52,    -1,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      18,    -1,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    50,    -1,    52,    -1,    54,    -1,    56,    57,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      18,    -1,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    50,    -1,    52,    -1,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      18,    -1,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    -1,    -1,    33,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    50,    -1,    52,    -1,    54,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    -1,    81,    82,    83,    84,    85,    86,    87,
      23,    -1,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    35,    -1,    37,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      -1,    54,    -1,    -1,    57,    -1,    -1,    60,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    23,    -1,    25,    26,    27,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    52,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      23,    -1,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      -1,    54,    29,    -1,    -1,    -1,    -1,    -1,    61,    62,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    44,    45,    46,
      47,    -1,    49,    50,    51,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    -1,    -1,    64,    65,    66,
      67,    68,    69,    29,    -1,    -1,    -1,    74,    -1,    76,
      77,    78,    -1,    -1,    -1,    -1,    -1,    -1,    44,    45,
      46,    47,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    29,    -1,    -1,    -1,    74,    -1,
      76,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      45,    46,    47,    -1,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    69,    29,    -1,    -1,    -1,    74,
      -1,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    29,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    45,    46,    47,    -1,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    69,    31,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,
      44,    45,    46,    47,    -1,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    31,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    -1,    -1,    -1,    -1,    44,
      45,    46,    47,    -1,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    69,    32,    -1,    -1,    -1,    74,
      -1,    76,    77,    78,    -1,    -1,    -1,    44,    45,    46,
      47,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
      67,    68,    69,    34,    -1,    -1,    -1,    74,    -1,    76,
      77,    78,    -1,    44,    45,    46,    47,    -1,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
      36,    -1,    -1,    74,    -1,    76,    77,    78,    44,    45,
      46,    47,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    38,    74,    -1,
      76,    77,    78,    44,    45,    46,    47,    -1,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    74,    -1,    76,    77,    78,    44,    45,
      46,    47,    -1,    49,    50,    51,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    74,    -1,
      76,    77,    78,    44,    45,    46,    47,    -1,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
      71,    -1,    -1,    74,    -1,    76,    77,    78,    44,    45,
      46,    47,    -1,    49,    50,    51,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    74,    -1,
      76,    77,    78,    44,    45,    46,    47,    -1,    49,    50,
      51,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    74,    -1,    76,    77,    78,    44,    45,
      46,    47,    -1,    49,    50,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    74,    -1,
      76,    77,    78,    44,    45,    46,    47,    -1,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    58,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    74,    -1,    76,    77,    78,    44,    45,
      46,    47,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    74,    -1,
      76,    77,    78,    44,    45,    46,    47,    -1,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
      -1,    -1,    -1,    74,    -1,    76,    77,    78,    44,    45,
      46,    -1,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    44,    -1,
      76,    77,    78,    49,    50,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    78
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    54,    94,    95,   196,   197,     1,    25,    87,
     183,   198,   199,     0,     1,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    16,    96,    97,    98,    99,
     100,   101,   102,   103,   106,   107,   108,   109,   110,   113,
     116,   196,     3,   197,    55,    23,    26,    27,    30,    37,
      41,    42,    43,    48,    49,    50,    52,    54,    61,    62,
      81,    82,    83,    84,    85,    86,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   183,   184,    55,    55,    56,   184,
     183,   183,   183,   183,   184,   183,   184,   183,   183,    52,
     169,   170,   171,   172,   173,   174,   175,   184,   183,    97,
      98,   183,   185,   188,   189,   191,   192,   196,   186,   189,
     186,   138,   186,   138,   139,   139,     1,   137,   138,   166,
     167,   183,     1,    55,   137,   138,   139,   184,    44,    45,
      46,    47,    49,    50,    51,    64,    65,    66,    67,    68,
      69,    74,    76,    77,    78,    39,    72,    52,    52,    59,
      52,   138,   164,   181,   182,    52,    73,    51,    51,    52,
      73,    51,    59,    51,    39,    51,    51,   168,   169,   183,
     184,   187,   188,    51,    14,    64,    70,    58,    58,    51,
      25,    63,   185,    25,    63,    25,    31,    25,    53,    63,
      53,    53,    63,    58,    55,    55,    63,    71,    61,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,   169,   156,   183,     1,
      53,   137,   138,     1,    53,   137,   183,   138,    73,    57,
      63,     1,   178,   183,   188,   190,   196,   169,    56,    18,
      20,    22,    23,    24,    26,    27,    28,    30,    33,    40,
      56,    79,   121,   122,   123,   124,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   139,   141,   142,     1,
     178,   169,   169,    66,   138,   183,    56,    56,    63,    63,
      56,   169,   168,   169,   176,   177,   138,   169,   177,   169,
     138,   138,   192,   138,   189,   138,   138,   138,   138,   167,
     183,   138,   138,   138,    52,    53,    53,    53,    53,    53,
     138,   182,    53,    53,    63,   188,    51,     1,   104,   105,
     183,   196,     1,   120,   121,     1,   120,   191,     1,   183,
     193,   194,   195,   196,   186,   186,   121,   138,   138,   138,
       1,   120,     1,   120,    75,    53,    53,    51,    54,   103,
     111,   112,     5,     7,    54,   101,   102,   114,   115,   119,
     169,   188,   101,   102,   117,   118,    51,    63,    65,    66,
      73,    73,    36,    29,    32,    38,    53,    55,     1,    53,
     137,    73,    73,    73,   190,   138,    57,    63,   183,    19,
      19,   121,    21,    21,    25,    58,    25,    63,   195,    25,
      25,    31,    34,    29,    57,    57,    80,    80,   138,    51,
      73,    51,    73,   121,   196,    57,   111,   183,   183,   196,
      57,   114,    53,    53,   118,    57,    56,   169,   169,   169,
     169,   138,   138,   138,   138,    53,    53,   138,   169,   169,
     104,   121,   177,   121,   194,   138,   138,   121,    56,   121,
     121,   169,   121,   169,    55,    58,    58,    55,   118,    65,
      17,   179,    51,    51,    73,    29,    38,    29,    32,     1,
      35,    60,   125,   126,   138,    51,    51,   103,   177,   177,
     101,   102,   119,    57,    56,    51,   180,   138,   138,   169,
     121,   138,   121,   121,    57,    58,    58,    57,   126,    58,
     121,   121,    73,    73,   138,    56,   179,    29,   121,   121,
     121,   169,   169,    57,   181,   180,   121,    57
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    93,    94,    95,    95,    96,    96,    97,    97,    97,
      98,    98,    98,    98,    98,    98,    98,    98,    98,    98,
      98,    98,    99,    99,   100,   101,   101,   101,   102,   102,
     102,   102,   102,   102,   103,   104,   104,   104,   105,   105,
     106,   107,   107,   108,   109,   109,   110,   111,   111,   112,
     112,   113,   114,   114,   114,   114,   114,   114,   115,   115,
     116,   116,   117,   117,   118,   118,   119,   119,   120,   120,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   122,   123,   123,   124,   124,   125,   125,
     126,   126,   126,   127,   128,   129,   129,   130,   131,   132,
     132,   132,   132,   133,   133,   133,   133,   134,   135,   136,
     137,   137,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   139,   139,   139,   139,   139,   139,   139,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   141,   141,   141,   142,
     142,   142,   142,   143,   143,   143,   143,   144,   145,   145,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   153,
     153,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     154,   155,   155,   156,   157,   158,   159,   159,   160,   161,
     162,   162,   162,   163,   164,   165,   166,   166,   167,   168,
     168,   169,   169,   169,   169,   169,   169,   170,   171,   172,
     173,   174,   175,   176,   176,   177,   177,   178,   178,   179,
     179,   180,   180,   181,   181,   182,   182,   182,   183,   183,
     184,   184,   185,   185,   186,   186,   187,   187,   188,   189,
     189,   190,   190,   191,   191,   192,   193,   193,   194,   194,
     194,   195,   196,   196,   197,   197,   197,   198,   199
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     4,     6,     6,     9,     9,     4,     6,
       7,     9,     7,     9,     8,     1,     2,     1,     3,     1,
       4,     2,     4,     4,     2,     4,     6,     4,     1,     2,
       1,     6,     4,     1,     4,     1,     4,     1,     2,     1,
       8,     6,     1,     1,     2,     1,     6,     6,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     4,     6,     6,     6,     2,     1,
       3,     3,     3,     4,     4,     6,     8,     6,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     4,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     1,     1,     1,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     1,     1,
       3,     4,     4,     3,     5,     6,     6,     3,     3,     4,
       4,     3,     4,     6,     6,     6,     6,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     3,     3,     5,     5,     3,     3,     1,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     5,     5,
       4,     6,     3,     3,     1,     1,     0,     3,     1,     4,
       0,     4,     0,     3,     1,     1,     5,     3,     1,     1,
       3,     1,     1,     1,     3,     1,     3,     1,     3,     2,
       1,     2,     1,     3,     1,     3,     3,     1,     2,     1,
       1,     7,     2,     1,     3,     3,     3,     1,     2
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
  "ImportDefinition", "StructureDefinition", "StructureDefinitionElement",
  "StructureDefinitionList", "FeatureDefinition",
  "FeatureDefinitionElement", "FeatureDefinitionList",
  "ImplementationDefinition", "ImplementationDefinitionDefinition",
  "ImplementationDefinitionDefinitions", "Declaration", "Rules", "Rule",
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
  "Parameters", "MaybeDefined", "MaybeInitially", "Initializers",
  "Initializer", "Identifier", "IdentifierPath", "Variable",
  "AttributedVariables", "TypedVariables", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "VariableBindings",
  "VariableBinding", "LocalFunctionDefinitions",
  "AttributedLocalFunctionDefinition", "LocalFunctionDefinition",
  "Attributes", "Attribute", "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   434,   434,   444,   450,   458,   464,   474,   480,   484,
     492,   496,   500,   504,   508,   512,   516,   520,   524,   528,
     532,   536,   544,   548,   556,   564,   569,   575,   583,   589,
     594,   601,   607,   611,   635,   650,   654,   660,   668,   675,
     685,   693,   697,   705,   717,   721,   729,   738,   744,   752,
     758,   772,   781,   787,   791,   797,   801,   807,   815,   821,
     835,   839,   849,   853,   861,   867,   881,   887,   901,   907,
     917,   921,   925,   929,   933,   937,   941,   945,   949,   953,
     957,   961,   965,   973,   981,   985,   993,   997,  1005,  1011,
    1021,  1025,  1029,  1037,  1045,  1053,  1057,  1065,  1073,  1081,
    1085,  1089,  1094,  1103,  1107,  1111,  1116,  1125,  1133,  1141,
    1153,  1160,  1170,  1174,  1178,  1182,  1186,  1190,  1194,  1198,
    1202,  1210,  1214,  1218,  1222,  1226,  1230,  1234,  1246,  1250,
    1254,  1258,  1262,  1266,  1270,  1274,  1278,  1282,  1286,  1290,
    1294,  1298,  1302,  1306,  1310,  1314,  1322,  1326,  1330,  1338,
    1343,  1350,  1356,  1364,  1369,  1376,  1382,  1390,  1398,  1405,
    1411,  1419,  1427,  1435,  1443,  1451,  1459,  1467,  1480,  1484,
    1488,  1492,  1496,  1500,  1504,  1508,  1512,  1516,  1520,  1524,
    1532,  1541,  1547,  1557,  1565,  1573,  1581,  1585,  1593,  1601,
    1609,  1616,  1622,  1630,  1639,  1650,  1659,  1666,  1675,  1687,
    1694,  1703,  1707,  1711,  1715,  1719,  1723,  1731,  1739,  1750,
    1761,  1769,  1777,  1789,  1796,  1806,  1810,  1818,  1825,  1839,
    1843,  1851,  1855,  1864,  1871,  1881,  1886,  1892,  1907,  1911,
    1920,  1927,  1939,  1943,  1952,  1959,  1969,  1976,  1986,  1995,
    2001,  2009,  2015,  2027,  2034,  2043,  2055,  2062,  2071,  2077,
    2081,  2088,  2108,  2114,  2123,  2130,  2137,  2144,  2151
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
#line 6354 "GrammarParser.cpp"

#line 2157 "../../obj/src/GrammarParser.y"


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
