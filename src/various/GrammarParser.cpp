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
      case symbol_kind::S_ImplementationDefinitionElement: // ImplementationDefinitionElement
        value.YY_MOVE_OR_COPY< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
      case symbol_kind::S_ImplementationDefinitionList: // ImplementationDefinitionList
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

      case symbol_kind::S_StructureLiteral: // StructureLiteral
        value.YY_MOVE_OR_COPY< StructureLiteral::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_ImplementationDefinitionElement: // ImplementationDefinitionElement
        value.move< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
      case symbol_kind::S_ImplementationDefinitionList: // ImplementationDefinitionList
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

      case symbol_kind::S_StructureLiteral: // StructureLiteral
        value.move< StructureLiteral::Ptr > (YY_MOVE (that.value));
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
      case symbol_kind::S_ImplementationDefinitionElement: // ImplementationDefinitionElement
        value.copy< Definition::Ptr > (that.value);
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
      case symbol_kind::S_ImplementationDefinitionList: // ImplementationDefinitionList
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

      case symbol_kind::S_StructureLiteral: // StructureLiteral
        value.copy< StructureLiteral::Ptr > (that.value);
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
      case symbol_kind::S_ImplementationDefinitionElement: // ImplementationDefinitionElement
        value.move< Definition::Ptr > (that.value);
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
      case symbol_kind::S_ImplementationDefinitionList: // ImplementationDefinitionList
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

      case symbol_kind::S_StructureLiteral: // StructureLiteral
        value.move< StructureLiteral::Ptr > (that.value);
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
      case symbol_kind::S_ImplementationDefinitionElement: // ImplementationDefinitionElement
        yylhs.value.emplace< Definition::Ptr > ();
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_FeatureDefinitionList: // FeatureDefinitionList
      case symbol_kind::S_ImplementationDefinitionList: // ImplementationDefinitionList
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

      case symbol_kind::S_StructureLiteral: // StructureLiteral
        yylhs.value.emplace< StructureLiteral::Ptr > ();
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
#line 2793 "GrammarParser.cpp"
    break;

  case 3: // Header: Attributes "CASM"
#line 445 "../../obj/src/GrammarParser.y"
  {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2803 "GrammarParser.cpp"
    break;

  case 4: // Header: "CASM"
#line 451 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2811 "GrammarParser.cpp"
    break;

  case 5: // Definitions: Definitions AttributedDefinition
#line 459 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2821 "GrammarParser.cpp"
    break;

  case 6: // Definitions: AttributedDefinition
#line 465 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2831 "GrammarParser.cpp"
    break;

  case 7: // AttributedDefinition: Attributes Definition
#line 475 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2841 "GrammarParser.cpp"
    break;

  case 8: // AttributedDefinition: Definition
#line 481 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2849 "GrammarParser.cpp"
    break;

  case 9: // AttributedDefinition: error
#line 485 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2857 "GrammarParser.cpp"
    break;

  case 10: // Definition: InitDefinition
#line 493 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2865 "GrammarParser.cpp"
    break;

  case 11: // Definition: EnumerationDefinition
#line 497 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2873 "GrammarParser.cpp"
    break;

  case 12: // Definition: DerivedDefinition
#line 501 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2881 "GrammarParser.cpp"
    break;

  case 13: // Definition: RuleDefinition
#line 505 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2889 "GrammarParser.cpp"
    break;

  case 14: // Definition: FunctionDefinition
#line 509 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 2897 "GrammarParser.cpp"
    break;

  case 15: // Definition: UsingDefinition
#line 513 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 2905 "GrammarParser.cpp"
    break;

  case 16: // Definition: UsingPathDefinition
#line 517 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingPathDefinition::Ptr > ();
  }
#line 2913 "GrammarParser.cpp"
    break;

  case 17: // Definition: InvariantDefinition
#line 521 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 2921 "GrammarParser.cpp"
    break;

  case 18: // Definition: ImportDefinition
#line 525 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 2929 "GrammarParser.cpp"
    break;

  case 19: // Definition: StructureDefinition
#line 529 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < StructureDefinition::Ptr > ();
  }
#line 2937 "GrammarParser.cpp"
    break;

  case 20: // Definition: FeatureDefinition
#line 533 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FeatureDefinition::Ptr > ();
  }
#line 2945 "GrammarParser.cpp"
    break;

  case 21: // Definition: ImplementationDefinition
#line 537 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImplementationDefinition::Ptr > ();
  }
#line 2953 "GrammarParser.cpp"
    break;

  case 22: // InitDefinition: "init" IdentifierPath
#line 545 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );

      const auto singleAgentIdentifier = Ast::make< Identifier >( yylhs.location, "$" );
      auto singleAgentArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( singleAgentIdentifier ), singleAgentArguments );
      singleAgent->setTargetType( DirectCallExpression::TargetType::CONSTANT );

      auto programFunction = createProgramFunction( yylhs.location );
      auto programArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      programArguments->add( singleAgent );

      const auto ruleReference = Ast::make< ReferenceLiteral >( yylhs.location, uToken, yystack_[0].value.as < IdentifierPath::Ptr > () );
      const auto initializers = Ast::make< Initializers >( yylhs.location );
      const auto initializer = Ast::make< Initializer >(
          yylhs.location, uToken, programArguments, uToken, uToken, ruleReference );
      initializers->add( initializer );

      // apply the name of the program declaration to the initializer functions
      for( auto& initializer : *initializers )
      {
          initializer->updateRule()->function()->setIdentifier(
              asIdentifierPath( programFunction->identifier() ) );
      }

      programFunction->setInitializers( initializers );
      yylhs.value.as < InitDefinition::Ptr > ()->setProgramFunction( programFunction );
  }
#line 2987 "GrammarParser.cpp"
    break;

  case 23: // InitDefinition: "init" "{" Initializers "}"
#line 575 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );

      auto programFunction = createProgramFunction( yylhs.location );

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as < Initializers::Ptr > ();
      for( auto& initializer : *initializers )
      {
          initializer->updateRule()->function()->setIdentifier(
              asIdentifierPath( programFunction->identifier() ) );
      }

      programFunction->setInitializers( initializers );
      yylhs.value.as < InitDefinition::Ptr > ()->setProgramFunction( programFunction );
  }
#line 3008 "GrammarParser.cpp"
    break;

  case 24: // EnumerationDefinition: "enumeration" Identifier "=" "{" Enumerators "}"
#line 596 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3016 "GrammarParser.cpp"
    break;

  case 25: // DerivedDefinition: "derived" Identifier "->" Type "=" Term
#line 604 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3025 "GrammarParser.cpp"
    break;

  case 26: // DerivedDefinition: "derived" Identifier "(" Parameters ")" "->" Type "=" Term
#line 609 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 3035 "GrammarParser.cpp"
    break;

  case 27: // DerivedDefinition: "derived" Identifier "(" error ")" "->" Type "=" Term
#line 615 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 3043 "GrammarParser.cpp"
    break;

  case 28: // RuleDefinition: "rule" Identifier "=" Rule
#line 623 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3053 "GrammarParser.cpp"
    break;

  case 29: // RuleDefinition: "rule" Identifier "->" Type "=" Rule
#line 629 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3062 "GrammarParser.cpp"
    break;

  case 30: // RuleDefinition: "rule" Identifier "(" Parameters ")" "=" Rule
#line 634 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
  }
#line 3073 "GrammarParser.cpp"
    break;

  case 31: // RuleDefinition: "rule" Identifier "(" Parameters ")" "->" Type "=" Rule
#line 641 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 3083 "GrammarParser.cpp"
    break;

  case 32: // RuleDefinition: "rule" Identifier "(" error ")" "=" Rule
#line 647 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3091 "GrammarParser.cpp"
    break;

  case 33: // RuleDefinition: "rule" Identifier "(" error ")" "->" Type "=" Rule
#line 651 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 3099 "GrammarParser.cpp"
    break;

  case 34: // FunctionDefinition: "function" Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 659 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = Ast::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      const auto initially = yylhs.value.as < FunctionDefinition::Ptr > ()->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->updateRule()->function()->setIdentifier( asIdentifierPath( yystack_[6].value.as < Identifier::Ptr > () ) );
      }
  }
#line 3114 "GrammarParser.cpp"
    break;

  case 35: // EnumeratorDefinition: Identifier
#line 674 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3122 "GrammarParser.cpp"
    break;

  case 36: // EnumeratorDefinition: Attributes Identifier
#line 678 "../../obj/src/GrammarParser.y"
  {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 3132 "GrammarParser.cpp"
    break;

  case 37: // EnumeratorDefinition: error
#line 684 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 3140 "GrammarParser.cpp"
    break;

  case 38: // Enumerators: Enumerators "," EnumeratorDefinition
#line 692 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3151 "GrammarParser.cpp"
    break;

  case 39: // Enumerators: EnumeratorDefinition
#line 699 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 3161 "GrammarParser.cpp"
    break;

  case 40: // UsingDefinition: "using" Identifier "=" Type
#line 709 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3169 "GrammarParser.cpp"
    break;

  case 41: // UsingPathDefinition: "using" IdentifierPath
#line 717 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3177 "GrammarParser.cpp"
    break;

  case 42: // UsingPathDefinition: "using" IdentifierPath "::" "*"
#line 721 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3185 "GrammarParser.cpp"
    break;

  case 43: // InvariantDefinition: "invariant" Identifier "=" Term
#line 729 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InvariantDefinition::Ptr > () = Ast::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3193 "GrammarParser.cpp"
    break;

  case 44: // ImportDefinition: "import" IdentifierPath
#line 741 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3201 "GrammarParser.cpp"
    break;

  case 45: // ImportDefinition: "import" IdentifierPath "as" Identifier
#line 745 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3209 "GrammarParser.cpp"
    break;

  case 46: // StructureDefinition: "structure" Identifier "=" "{" StructureDefinitionList "}"
#line 753 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, $4, and $6
      // $$ = Ast::make< StructureDefinition >( @$, $2, $5 );
  }
#line 3218 "GrammarParser.cpp"
    break;

  case 47: // StructureDefinitionElement: "[" Attributes "]" FunctionDefinition
#line 762 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 3228 "GrammarParser.cpp"
    break;

  case 48: // StructureDefinitionElement: FunctionDefinition
#line 768 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 3236 "GrammarParser.cpp"
    break;

  case 49: // StructureDefinitionList: StructureDefinitionList StructureDefinitionElement
#line 776 "../../obj/src/GrammarParser.y"
  {
      auto functions = yystack_[1].value.as < FunctionDefinitions::Ptr > ();
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3246 "GrammarParser.cpp"
    break;

  case 50: // StructureDefinitionList: StructureDefinitionElement
#line 782 "../../obj/src/GrammarParser.y"
  {
      auto functions = Ast::make< FunctionDefinitions >( yylhs.location );
      functions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = functions;
  }
#line 3256 "GrammarParser.cpp"
    break;

  case 51: // FeatureDefinition: "feature" Identifier "=" "{" FeatureDefinitionList "}"
#line 796 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, $4, and $6
      yylhs.value.as < FeatureDefinition::Ptr > () = Ast::make< FeatureDefinition >( yylhs.location, yystack_[4].value.as < Identifier::Ptr > (), yystack_[1].value.as < Definitions::Ptr > () );
  }
#line 3265 "GrammarParser.cpp"
    break;

  case 52: // FeatureDefinitionElement: "[" Attributes "]" Declaration
#line 805 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < DeclarationDefinition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3275 "GrammarParser.cpp"
    break;

  case 53: // FeatureDefinitionElement: Declaration
#line 811 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DeclarationDefinition::Ptr > ();
  }
#line 3283 "GrammarParser.cpp"
    break;

  case 54: // FeatureDefinitionElement: "[" Attributes "]" DerivedDefinition
#line 815 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < DerivedDefinition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3293 "GrammarParser.cpp"
    break;

  case 55: // FeatureDefinitionElement: DerivedDefinition
#line 821 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3301 "GrammarParser.cpp"
    break;

  case 56: // FeatureDefinitionElement: "[" Attributes "]" RuleDefinition
#line 825 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < RuleDefinition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3311 "GrammarParser.cpp"
    break;

  case 57: // FeatureDefinitionElement: RuleDefinition
#line 831 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3319 "GrammarParser.cpp"
    break;

  case 58: // FeatureDefinitionList: FeatureDefinitionList FeatureDefinitionElement
#line 839 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3329 "GrammarParser.cpp"
    break;

  case 59: // FeatureDefinitionList: FeatureDefinitionElement
#line 845 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3339 "GrammarParser.cpp"
    break;

  case 60: // ImplementationDefinition: "implements" IdentifierPath "for" Identifier "=" "{" ImplementationDefinitionList "}"
#line 859 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImplementationDefinition::Ptr > () = Ast::make< ImplementationDefinition >( yylhs.location, yystack_[6].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[1].value.as < Definitions::Ptr > () );
  }
#line 3347 "GrammarParser.cpp"
    break;

  case 61: // ImplementationDefinition: "implements" Identifier "=" "{" ImplementationDefinitionList "}"
#line 863 "../../obj/src/GrammarParser.y"
  {
      const auto name = Ast::make< Identifier >( yylhs.location, "" );
      const auto path = asIdentifierPath( name );
      yylhs.value.as < ImplementationDefinition::Ptr > () = Ast::make< ImplementationDefinition >( yylhs.location, path, yystack_[4].value.as < Identifier::Ptr > (), yystack_[1].value.as < Definitions::Ptr > () );
  }
#line 3357 "GrammarParser.cpp"
    break;

  case 62: // ImplementationDefinitionElement: "[" Attributes "]" DerivedDefinition
#line 873 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < DerivedDefinition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3367 "GrammarParser.cpp"
    break;

  case 63: // ImplementationDefinitionElement: DerivedDefinition
#line 879 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 3375 "GrammarParser.cpp"
    break;

  case 64: // ImplementationDefinitionElement: "[" Attributes "]" RuleDefinition
#line 883 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < RuleDefinition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 3385 "GrammarParser.cpp"
    break;

  case 65: // ImplementationDefinitionElement: RuleDefinition
#line 889 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 3393 "GrammarParser.cpp"
    break;

  case 66: // ImplementationDefinitionList: ImplementationDefinitionList ImplementationDefinitionElement
#line 897 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3403 "GrammarParser.cpp"
    break;

  case 67: // ImplementationDefinitionList: ImplementationDefinitionElement
#line 903 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 3413 "GrammarParser.cpp"
    break;

  case 68: // Declaration: "derived" Identifier ":" MaybeFunctionParameters "->" Type
#line 917 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, and $5
      yylhs.value.as < DeclarationDefinition::Ptr > () = Ast::make< DeclarationDefinition >
          ( yylhs.location, yystack_[4].value.as < Identifier::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > (), DeclarationDefinition::Kind::DERIVED );
  }
#line 3423 "GrammarParser.cpp"
    break;

  case 69: // Declaration: "rule" Identifier ":" MaybeFunctionParameters "->" Type
#line 923 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: handle AST keyword tokens $1, $3, and $5
      yylhs.value.as < DeclarationDefinition::Ptr > () = Ast::make< DeclarationDefinition >
          ( yylhs.location, yystack_[4].value.as < Identifier::Ptr > (), yystack_[2].value.as < Types::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > (), DeclarationDefinition::Kind::RULE );
  }
#line 3433 "GrammarParser.cpp"
    break;

  case 70: // Rules: Rules Rule
#line 937 "../../obj/src/GrammarParser.y"
  {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3443 "GrammarParser.cpp"
    break;

  case 71: // Rules: Rule
#line 943 "../../obj/src/GrammarParser.y"
  {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3453 "GrammarParser.cpp"
    break;

  case 72: // Rule: SkipRule
#line 953 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 3461 "GrammarParser.cpp"
    break;

  case 73: // Rule: ConditionalRule
#line 957 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 3469 "GrammarParser.cpp"
    break;

  case 74: // Rule: CaseRule
#line 961 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 3477 "GrammarParser.cpp"
    break;

  case 75: // Rule: LetRule
#line 965 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 3485 "GrammarParser.cpp"
    break;

  case 76: // Rule: LocalRule
#line 969 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LocalRule::Ptr > ();
  }
#line 3493 "GrammarParser.cpp"
    break;

  case 77: // Rule: ForallRule
#line 973 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 3501 "GrammarParser.cpp"
    break;

  case 78: // Rule: ChooseRule
#line 977 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 3509 "GrammarParser.cpp"
    break;

  case 79: // Rule: IterateRule
#line 981 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 3517 "GrammarParser.cpp"
    break;

  case 80: // Rule: BlockRule
#line 985 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 3525 "GrammarParser.cpp"
    break;

  case 81: // Rule: SequenceRule
#line 989 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 3533 "GrammarParser.cpp"
    break;

  case 82: // Rule: UpdateRule
#line 993 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 3541 "GrammarParser.cpp"
    break;

  case 83: // Rule: CallRule
#line 997 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 3549 "GrammarParser.cpp"
    break;

  case 84: // Rule: WhileRule
#line 1001 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 3557 "GrammarParser.cpp"
    break;

  case 85: // SkipRule: "skip"
#line 1009 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3565 "GrammarParser.cpp"
    break;

  case 86: // ConditionalRule: "if" Term "then" Rule
#line 1017 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3573 "GrammarParser.cpp"
    break;

  case 87: // ConditionalRule: "if" Term "then" Rule "else" Rule
#line 1021 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3581 "GrammarParser.cpp"
    break;

  case 88: // CaseRule: "case" Term "of" "{" CaseLabels "}"
#line 1029 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3589 "GrammarParser.cpp"
    break;

  case 89: // CaseRule: "case" Term "of" "{" error "}"
#line 1033 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 3597 "GrammarParser.cpp"
    break;

  case 90: // CaseLabels: CaseLabels CaseLabel
#line 1041 "../../obj/src/GrammarParser.y"
  {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3607 "GrammarParser.cpp"
    break;

  case 91: // CaseLabels: CaseLabel
#line 1047 "../../obj/src/GrammarParser.y"
  {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3617 "GrammarParser.cpp"
    break;

  case 92: // CaseLabel: "default" ":" Rule
#line 1057 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3625 "GrammarParser.cpp"
    break;

  case 93: // CaseLabel: "_" ":" Rule
#line 1061 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3633 "GrammarParser.cpp"
    break;

  case 94: // CaseLabel: Term ":" Rule
#line 1065 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3641 "GrammarParser.cpp"
    break;

  case 95: // LetRule: "let" VariableBindings "in" Rule
#line 1073 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3649 "GrammarParser.cpp"
    break;

  case 96: // LocalRule: "local" LocalFunctionDefinitions "in" Rule
#line 1081 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LocalRule::Ptr > () = Ast::make< LocalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < FunctionDefinitions::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3657 "GrammarParser.cpp"
    break;

  case 97: // ForallRule: "forall" AttributedVariables "in" Term "do" Rule
#line 1089 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3665 "GrammarParser.cpp"
    break;

  case 98: // ForallRule: "forall" AttributedVariables "in" Term "with" Term "do" Rule
#line 1093 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3673 "GrammarParser.cpp"
    break;

  case 99: // ChooseRule: "choose" AttributedVariables "in" Term "do" Rule
#line 1101 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3681 "GrammarParser.cpp"
    break;

  case 100: // IterateRule: "iterate" Rule
#line 1109 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3689 "GrammarParser.cpp"
    break;

  case 101: // BlockRule: "{" Rules "}"
#line 1117 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3697 "GrammarParser.cpp"
    break;

  case 102: // BlockRule: "par" Rules "endpar"
#line 1121 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3705 "GrammarParser.cpp"
    break;

  case 103: // BlockRule: "{" error "}"
#line 1125 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3714 "GrammarParser.cpp"
    break;

  case 104: // BlockRule: "par" error "endpar"
#line 1130 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3723 "GrammarParser.cpp"
    break;

  case 105: // SequenceRule: "{|" Rules "|}"
#line 1139 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3731 "GrammarParser.cpp"
    break;

  case 106: // SequenceRule: "seq" Rules "endseq"
#line 1143 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3739 "GrammarParser.cpp"
    break;

  case 107: // SequenceRule: "{|" error "|}"
#line 1147 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3748 "GrammarParser.cpp"
    break;

  case 108: // SequenceRule: "seq" error "endseq"
#line 1152 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3757 "GrammarParser.cpp"
    break;

  case 109: // UpdateRule: DirectCallExpression ":=" Term
#line 1161 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3765 "GrammarParser.cpp"
    break;

  case 110: // UpdateRule: MethodCallExpression ":=" Term
#line 1165 "../../obj/src/GrammarParser.y"
  {
      // TODO: FIXME: @ppaulweber: change UpdateRule to support MethodCallExpression as well
      // const auto function = $1;
      // function->setMethodType( MethodCallExpression::MethodType::FUNCTION );
      // $$ = Ast::make< UpdateRule >( @$, function, $3 );
  }
#line 3776 "GrammarParser.cpp"
    break;

  case 111: // CallRule: CallExpression
#line 1176 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 3784 "GrammarParser.cpp"
    break;

  case 112: // WhileRule: "while" Term "do" Rule
#line 1184 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3792 "GrammarParser.cpp"
    break;

  case 113: // Terms: Terms "," Term
#line 1196 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3803 "GrammarParser.cpp"
    break;

  case 114: // Terms: Term
#line 1203 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3813 "GrammarParser.cpp"
    break;

  case 115: // Term: SimpleOrClaspedTerm
#line 1213 "../../obj/src/GrammarParser.y"
  {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3821 "GrammarParser.cpp"
    break;

  case 116: // Term: TypeCastingExpression
#line 1217 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 3829 "GrammarParser.cpp"
    break;

  case 117: // Term: OperatorExpression
#line 1221 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3837 "GrammarParser.cpp"
    break;

  case 118: // Term: LetExpression
#line 1225 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 3845 "GrammarParser.cpp"
    break;

  case 119: // Term: ConditionalExpression
#line 1229 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 3853 "GrammarParser.cpp"
    break;

  case 120: // Term: ChooseExpression
#line 1233 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 3861 "GrammarParser.cpp"
    break;

  case 121: // Term: UniversalQuantifierExpression
#line 1237 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 3869 "GrammarParser.cpp"
    break;

  case 122: // Term: ExistentialQuantifierExpression
#line 1241 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 3877 "GrammarParser.cpp"
    break;

  case 123: // Term: CardinalityExpression
#line 1245 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 3885 "GrammarParser.cpp"
    break;

  case 124: // SimpleOrClaspedTerm: "(" Term ")"
#line 1253 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< Ast::EmbracedExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3893 "GrammarParser.cpp"
    break;

  case 125: // SimpleOrClaspedTerm: "(" error ")"
#line 1257 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 3901 "GrammarParser.cpp"
    break;

  case 126: // SimpleOrClaspedTerm: CallExpression
#line 1261 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 3909 "GrammarParser.cpp"
    break;

  case 127: // SimpleOrClaspedTerm: LiteralCallExpression
#line 1265 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 3917 "GrammarParser.cpp"
    break;

  case 128: // SimpleOrClaspedTerm: Literal
#line 1269 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 3925 "GrammarParser.cpp"
    break;

  case 129: // SimpleOrClaspedTerm: "+" SimpleOrClaspedTerm
#line 1273 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3933 "GrammarParser.cpp"
    break;

  case 130: // SimpleOrClaspedTerm: "-" SimpleOrClaspedTerm
#line 1277 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 3941 "GrammarParser.cpp"
    break;

  case 131: // OperatorExpression: Term "+" Term
#line 1289 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3949 "GrammarParser.cpp"
    break;

  case 132: // OperatorExpression: Term "-" Term
#line 1293 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 3957 "GrammarParser.cpp"
    break;

  case 133: // OperatorExpression: Term "*" Term
#line 1297 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 3965 "GrammarParser.cpp"
    break;

  case 134: // OperatorExpression: Term "/" Term
#line 1301 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 3973 "GrammarParser.cpp"
    break;

  case 135: // OperatorExpression: Term "%" Term
#line 1305 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 3981 "GrammarParser.cpp"
    break;

  case 136: // OperatorExpression: Term "^" Term
#line 1309 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 3989 "GrammarParser.cpp"
    break;

  case 137: // OperatorExpression: Term "!=" Term
#line 1313 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 3997 "GrammarParser.cpp"
    break;

  case 138: // OperatorExpression: Term "=" Term
#line 1317 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 4005 "GrammarParser.cpp"
    break;

  case 139: // OperatorExpression: Term "<" Term
#line 1321 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 4013 "GrammarParser.cpp"
    break;

  case 140: // OperatorExpression: Term ">" Term
#line 1325 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 4021 "GrammarParser.cpp"
    break;

  case 141: // OperatorExpression: Term "<=" Term
#line 1329 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 4029 "GrammarParser.cpp"
    break;

  case 142: // OperatorExpression: Term ">=" Term
#line 1333 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 4037 "GrammarParser.cpp"
    break;

  case 143: // OperatorExpression: Term "or" Term
#line 1337 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 4045 "GrammarParser.cpp"
    break;

  case 144: // OperatorExpression: Term "xor" Term
#line 1341 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 4053 "GrammarParser.cpp"
    break;

  case 145: // OperatorExpression: Term "and" Term
#line 1345 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 4061 "GrammarParser.cpp"
    break;

  case 146: // OperatorExpression: Term "=>" Term
#line 1349 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 4069 "GrammarParser.cpp"
    break;

  case 147: // OperatorExpression: Term "implies" Term
#line 1353 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 4077 "GrammarParser.cpp"
    break;

  case 148: // OperatorExpression: "not" Term
#line 1357 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 4085 "GrammarParser.cpp"
    break;

  case 149: // CallExpression: DirectCallExpression
#line 1365 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 4093 "GrammarParser.cpp"
    break;

  case 150: // CallExpression: MethodCallExpression
#line 1369 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 4101 "GrammarParser.cpp"
    break;

  case 151: // CallExpression: IndirectCallExpression
#line 1373 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 4109 "GrammarParser.cpp"
    break;

  case 152: // DirectCallExpression: IdentifierPath
#line 1381 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > (), arguments );
  }
#line 4118 "GrammarParser.cpp"
    break;

  case 153: // DirectCallExpression: IdentifierPath "(" ")"
#line 1386 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), arguments );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4129 "GrammarParser.cpp"
    break;

  case 154: // DirectCallExpression: IdentifierPath "(" Terms ")"
#line 1393 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4139 "GrammarParser.cpp"
    break;

  case 155: // DirectCallExpression: IdentifierPath "(" error ")"
#line 1399 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 4147 "GrammarParser.cpp"
    break;

  case 156: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier
#line 1407 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 4156 "GrammarParser.cpp"
    break;

  case 157: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" ")"
#line 1412 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4167 "GrammarParser.cpp"
    break;

  case 158: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" Terms ")"
#line 1419 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4177 "GrammarParser.cpp"
    break;

  case 159: // MethodCallExpression: SimpleOrClaspedTerm "." Identifier "(" error ")"
#line 1425 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 4185 "GrammarParser.cpp"
    break;

  case 160: // LiteralCallExpression: SimpleOrClaspedTerm "." IntegerLiteral
#line 1433 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 4193 "GrammarParser.cpp"
    break;

  case 161: // IndirectCallExpression: CallExpression "(" ")"
#line 1441 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4204 "GrammarParser.cpp"
    break;

  case 162: // IndirectCallExpression: CallExpression "(" Terms ")"
#line 1448 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4214 "GrammarParser.cpp"
    break;

  case 163: // IndirectCallExpression: CallExpression "(" error ")"
#line 1454 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 4222 "GrammarParser.cpp"
    break;

  case 164: // TypeCastingExpression: SimpleOrClaspedTerm "as" Type
#line 1462 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 4230 "GrammarParser.cpp"
    break;

  case 165: // LetExpression: "let" VariableBindings "in" Term
#line 1470 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4238 "GrammarParser.cpp"
    break;

  case 166: // ConditionalExpression: "if" Term "then" Term "else" Term
#line 1478 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4246 "GrammarParser.cpp"
    break;

  case 167: // ChooseExpression: "choose" AttributedVariables "in" Term "do" Term
#line 1486 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4254 "GrammarParser.cpp"
    break;

  case 168: // UniversalQuantifierExpression: "forall" AttributedVariables "in" Term "holds" Term
#line 1494 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4262 "GrammarParser.cpp"
    break;

  case 169: // ExistentialQuantifierExpression: "exists" AttributedVariables "in" Term "with" Term
#line 1502 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4270 "GrammarParser.cpp"
    break;

  case 170: // CardinalityExpression: "|" SimpleOrClaspedTerm "|"
#line 1510 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4278 "GrammarParser.cpp"
    break;

  case 171: // Literal: UndefinedLiteral
#line 1522 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 4286 "GrammarParser.cpp"
    break;

  case 172: // Literal: BooleanLiteral
#line 1526 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4294 "GrammarParser.cpp"
    break;

  case 173: // Literal: IntegerLiteral
#line 1530 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4302 "GrammarParser.cpp"
    break;

  case 174: // Literal: RationalLiteral
#line 1534 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4310 "GrammarParser.cpp"
    break;

  case 175: // Literal: DecimalLiteral
#line 1538 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4318 "GrammarParser.cpp"
    break;

  case 176: // Literal: BinaryLiteral
#line 1542 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4326 "GrammarParser.cpp"
    break;

  case 177: // Literal: StringLiteral
#line 1546 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4334 "GrammarParser.cpp"
    break;

  case 178: // Literal: ReferenceLiteral
#line 1550 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 4342 "GrammarParser.cpp"
    break;

  case 179: // Literal: ListLiteral
#line 1554 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 4350 "GrammarParser.cpp"
    break;

  case 180: // Literal: RangeLiteral
#line 1558 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 4358 "GrammarParser.cpp"
    break;

  case 181: // Literal: TupleLiteral
#line 1562 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 4366 "GrammarParser.cpp"
    break;

  case 182: // Literal: RecordLiteral
#line 1566 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 4374 "GrammarParser.cpp"
    break;

  case 183: // Literal: StructureLiteral
#line 1570 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < StructureLiteral::Ptr > ();
  }
#line 4382 "GrammarParser.cpp"
    break;

  case 184: // UndefinedLiteral: "undef"
#line 1578 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4391 "GrammarParser.cpp"
    break;

  case 185: // BooleanLiteral: "true"
#line 1587 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4401 "GrammarParser.cpp"
    break;

  case 186: // BooleanLiteral: "false"
#line 1593 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 4411 "GrammarParser.cpp"
    break;

  case 187: // IntegerLiteral: "integer"
#line 1603 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4419 "GrammarParser.cpp"
    break;

  case 188: // RationalLiteral: "rational"
#line 1611 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4427 "GrammarParser.cpp"
    break;

  case 189: // DecimalLiteral: "decimal"
#line 1619 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4435 "GrammarParser.cpp"
    break;

  case 190: // BinaryLiteral: "binary"
#line 1627 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4443 "GrammarParser.cpp"
    break;

  case 191: // BinaryLiteral: "hexadecimal"
#line 1631 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4451 "GrammarParser.cpp"
    break;

  case 192: // StringLiteral: "string"
#line 1639 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4459 "GrammarParser.cpp"
    break;

  case 193: // ReferenceLiteral: "@" IdentifierPath
#line 1647 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4467 "GrammarParser.cpp"
    break;

  case 194: // ListLiteral: "[" "]"
#line 1655 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4478 "GrammarParser.cpp"
    break;

  case 195: // ListLiteral: "[" Terms "]"
#line 1662 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4488 "GrammarParser.cpp"
    break;

  case 196: // ListLiteral: "[" error "]"
#line 1668 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 4496 "GrammarParser.cpp"
    break;

  case 197: // RangeLiteral: "[" Term ".." Term "]"
#line 1676 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4506 "GrammarParser.cpp"
    break;

  case 198: // TupleLiteral: "(" Terms "," Term ")"
#line 1686 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4519 "GrammarParser.cpp"
    break;

  case 199: // RecordLiteral: "(" Assignments ")"
#line 1698 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4529 "GrammarParser.cpp"
    break;

  case 200: // StructureLiteral: BasicType TupleLiteral
#line 1712 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < StructureLiteral::Ptr > () = Ast::make< StructureLiteral >( yylhs.location, yystack_[1].value.as < BasicType::Ptr > (), yystack_[0].value.as < TupleLiteral::Ptr > () );
  }
#line 4537 "GrammarParser.cpp"
    break;

  case 201: // StructureLiteral: BasicType RecordLiteral
#line 1716 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < StructureLiteral::Ptr > () = Ast::make< StructureLiteral >( yylhs.location, yystack_[1].value.as < BasicType::Ptr > (), yystack_[0].value.as < RecordLiteral::Ptr > () );
  }
#line 4545 "GrammarParser.cpp"
    break;

  case 202: // Assignments: Assignments "," Assignment
#line 1728 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4556 "GrammarParser.cpp"
    break;

  case 203: // Assignments: Assignment
#line 1735 "../../obj/src/GrammarParser.y"
  {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4566 "GrammarParser.cpp"
    break;

  case 204: // Assignment: Identifier ":" Term
#line 1744 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4574 "GrammarParser.cpp"
    break;

  case 205: // Types: Types "," Type
#line 1756 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4585 "GrammarParser.cpp"
    break;

  case 206: // Types: Type
#line 1763 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4595 "GrammarParser.cpp"
    break;

  case 207: // Type: BasicType
#line 1772 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4603 "GrammarParser.cpp"
    break;

  case 208: // Type: TupleType
#line 1776 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4611 "GrammarParser.cpp"
    break;

  case 209: // Type: RecordType
#line 1780 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4619 "GrammarParser.cpp"
    break;

  case 210: // Type: TemplateType
#line 1784 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4627 "GrammarParser.cpp"
    break;

  case 211: // Type: RelationType
#line 1788 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4635 "GrammarParser.cpp"
    break;

  case 212: // Type: FixedSizedType
#line 1792 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4643 "GrammarParser.cpp"
    break;

  case 213: // BasicType: IdentifierPath
#line 1800 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4651 "GrammarParser.cpp"
    break;

  case 214: // TupleType: "(" Types "," Type ")"
#line 1808 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = Ast::make< TupleType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), subTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4662 "GrammarParser.cpp"
    break;

  case 215: // RecordType: "(" TypedVariables "," TypedVariable ")"
#line 1819 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = Ast::make< RecordType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4673 "GrammarParser.cpp"
    break;

  case 216: // TemplateType: IdentifierPath "<" Types ">"
#line 1830 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4681 "GrammarParser.cpp"
    break;

  case 217: // RelationType: IdentifierPath "<" MaybeFunctionParameters "->" Type ">"
#line 1838 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4689 "GrammarParser.cpp"
    break;

  case 218: // FixedSizedType: IdentifierPath "'" Term
#line 1846 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4697 "GrammarParser.cpp"
    break;

  case 219: // FunctionParameters: FunctionParameters "*" Type
#line 1858 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4708 "GrammarParser.cpp"
    break;

  case 220: // FunctionParameters: Type
#line 1865 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4718 "GrammarParser.cpp"
    break;

  case 221: // MaybeFunctionParameters: FunctionParameters
#line 1875 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 4726 "GrammarParser.cpp"
    break;

  case 222: // MaybeFunctionParameters: %empty
#line 1879 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 4734 "GrammarParser.cpp"
    break;

  case 223: // Parameters: Parameters "," TypedAttributedVariable
#line 1887 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4745 "GrammarParser.cpp"
    break;

  case 224: // Parameters: TypedAttributedVariable
#line 1894 "../../obj/src/GrammarParser.y"
  {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4755 "GrammarParser.cpp"
    break;

  case 225: // MaybeDefined: "defined" "{" Term "}"
#line 1908 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4763 "GrammarParser.cpp"
    break;

  case 226: // MaybeDefined: %empty
#line 1912 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 4771 "GrammarParser.cpp"
    break;

  case 227: // MaybeInitially: "=" "{" Initializers "}"
#line 1920 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4779 "GrammarParser.cpp"
    break;

  case 228: // MaybeInitially: %empty
#line 1924 "../../obj/src/GrammarParser.y"
  {
      const auto initializers = Ast::make< Initializers >( yylhs.location );
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
#line 4788 "GrammarParser.cpp"
    break;

  case 229: // Initializers: Initializers "," Initializer
#line 1933 "../../obj/src/GrammarParser.y"
  {
      auto initializers = yystack_[2].value.as < Initializers::Ptr > ();
      yystack_[0].value.as < Initializer::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4799 "GrammarParser.cpp"
    break;

  case 230: // Initializers: Initializer
#line 1940 "../../obj/src/GrammarParser.y"
  {
      auto initializers = Ast::make< Initializers >( yylhs.location );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4809 "GrammarParser.cpp"
    break;

  case 231: // Initializer: Term
#line 1950 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4818 "GrammarParser.cpp"
    break;

  case 232: // Initializer: "(" Term ")" "->" Term
#line 1955 "../../obj/src/GrammarParser.y"
  {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), arguments, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4828 "GrammarParser.cpp"
    break;

  case 233: // Initializer: TupleLiteral "->" Term
#line 1961 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto lbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto rbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, lbToken, arguments, rbToken, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4839 "GrammarParser.cpp"
    break;

  case 234: // Identifier: "identifier"
#line 1976 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 4847 "GrammarParser.cpp"
    break;

  case 235: // Identifier: "in"
#line 1980 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 4856 "GrammarParser.cpp"
    break;

  case 236: // IdentifierPath: IdentifierPath "::" Identifier
#line 1989 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < Ast::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 4867 "GrammarParser.cpp"
    break;

  case 237: // IdentifierPath: Identifier
#line 1996 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4875 "GrammarParser.cpp"
    break;

  case 238: // Variable: TypedVariable
#line 2008 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4883 "GrammarParser.cpp"
    break;

  case 239: // Variable: Identifier
#line 2012 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 4892 "GrammarParser.cpp"
    break;

  case 240: // AttributedVariables: AttributedVariables "," AttributedVariable
#line 2021 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 4903 "GrammarParser.cpp"
    break;

  case 241: // AttributedVariables: AttributedVariable
#line 2028 "../../obj/src/GrammarParser.y"
  {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 4913 "GrammarParser.cpp"
    break;

  case 242: // TypedVariables: TypedVariables "," TypedVariable
#line 2038 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4924 "GrammarParser.cpp"
    break;

  case 243: // TypedVariables: TypedVariable
#line 2045 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4934 "GrammarParser.cpp"
    break;

  case 244: // TypedVariable: Identifier ":" Type
#line 2055 "../../obj/src/GrammarParser.y"
  {
      auto variable = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4943 "GrammarParser.cpp"
    break;

  case 245: // AttributedVariable: Attributes Variable
#line 2064 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4953 "GrammarParser.cpp"
    break;

  case 246: // AttributedVariable: Variable
#line 2070 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4961 "GrammarParser.cpp"
    break;

  case 247: // TypedAttributedVariable: Attributes TypedVariable
#line 2078 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4971 "GrammarParser.cpp"
    break;

  case 248: // TypedAttributedVariable: TypedVariable
#line 2084 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4979 "GrammarParser.cpp"
    break;

  case 249: // VariableBindings: VariableBindings "," VariableBinding
#line 2096 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4990 "GrammarParser.cpp"
    break;

  case 250: // VariableBindings: VariableBinding
#line 2103 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 5000 "GrammarParser.cpp"
    break;

  case 251: // VariableBinding: AttributedVariable "=" Term
#line 2112 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5008 "GrammarParser.cpp"
    break;

  case 252: // LocalFunctionDefinitions: LocalFunctionDefinitions "," AttributedLocalFunctionDefinition
#line 2124 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[2].value.as < FunctionDefinitions::Ptr > ();
      yystack_[0].value.as < FunctionDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5019 "GrammarParser.cpp"
    break;

  case 253: // LocalFunctionDefinitions: AttributedLocalFunctionDefinition
#line 2131 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< FunctionDefinitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 5029 "GrammarParser.cpp"
    break;

  case 254: // AttributedLocalFunctionDefinition: Attributes LocalFunctionDefinition
#line 2140 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 5039 "GrammarParser.cpp"
    break;

  case 255: // AttributedLocalFunctionDefinition: LocalFunctionDefinition
#line 2146 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 5047 "GrammarParser.cpp"
    break;

  case 256: // AttributedLocalFunctionDefinition: error
#line 2150 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = nullptr;
  }
#line 5055 "GrammarParser.cpp"
    break;

  case 257: // LocalFunctionDefinition: Identifier ":" MaybeFunctionParameters "->" Type MaybeDefined MaybeInitially
#line 2157 "../../obj/src/GrammarParser.y"
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
#line 5071 "GrammarParser.cpp"
    break;

  case 258: // Attributes: Attributes Attribute
#line 2177 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5081 "GrammarParser.cpp"
    break;

  case 259: // Attributes: Attribute
#line 2183 "../../obj/src/GrammarParser.y"
  {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 5091 "GrammarParser.cpp"
    break;

  case 260: // Attribute: "[" BasicAttribute "]"
#line 2192 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5102 "GrammarParser.cpp"
    break;

  case 261: // Attribute: "[" ExpressionAttribute "]"
#line 2199 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 5113 "GrammarParser.cpp"
    break;

  case 262: // Attribute: "[" error "]"
#line 2206 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 5121 "GrammarParser.cpp"
    break;

  case 263: // BasicAttribute: Identifier
#line 2213 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 5129 "GrammarParser.cpp"
    break;

  case 264: // ExpressionAttribute: Identifier Term
#line 2220 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 5137 "GrammarParser.cpp"
    break;


#line 5141 "GrammarParser.cpp"

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


  const short Parser::yypact_ninf_ = -381;

  const short Parser::yytable_ninf_ = -221;

  const short
  Parser::yypact_[] =
  {
      22,  -381,    25,    20,  1306,    54,  -381,   -40,  -381,  -381,
     291,     9,    41,  -381,  -381,    -2,    26,    26,    26,    26,
      26,    26,    26,    26,    26,    26,   657,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,   679,  -381,  -381,  -381,     6,     6,     6,   291,     6,
    -381,  -381,  -381,   291,   518,   518,  1567,  1307,   518,    26,
    -381,  -381,  -381,  -381,  -381,  -381,  2739,   116,  -381,    40,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,  -381,    48,  -381,   155,  -381,  -381,
    2047,    56,    28,    77,    58,   108,   146,   124,    93,   158,
     208,   210,    18,   205,  -381,  -381,   218,  -381,  -381,   239,
      34,  -381,     6,    63,  -381,    64,  2276,    98,  -381,  -381,
    -381,   242,   236,  2494,     2,  -381,   257,   272,  -381,   231,
    2529,   141,    56,   291,   291,   291,   291,   291,   291,   291,
     291,   291,   291,   291,   291,   291,   291,   291,   291,   291,
      11,    12,  1372,   291,  -381,  -381,  1437,    26,  1567,  2739,
     258,    99,  -381,    15,    11,   286,  1917,    16,    11,    11,
      17,   291,    26,   288,   294,   295,    26,    11,    11,   291,
     291,     6,  -381,   291,     6,   291,   291,   291,  -381,   291,
    -381,  -381,    26,   291,  -381,  -381,   291,   291,  -381,  2815,
    2809,   166,  2774,   269,   269,   696,   154,   154,   253,   253,
     253,  -381,  2774,   696,   154,   154,    11,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,   181,  -381,   296,   303,  -381,   148,
    2739,   304,  -381,   184,  -381,  2564,   291,  -381,  2047,   305,
     217,   218,  -381,  -381,     6,   308,    27,   989,  1102,  -381,
       6,    33,     6,     6,  1917,   291,   291,   291,  1172,  1242,
    -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,   290,   120,   285,   289,   310,   248,
     314,  -381,  -381,  2739,  -381,    13,   111,   112,   315,  -381,
     302,   298,  -381,  2739,  2739,  -381,  2424,  -381,  2114,  2353,
    2459,  2599,  -381,   257,  2739,  2739,  2634,   321,  -381,   218,
     325,  -381,    11,   291,  1502,  -381,  -381,  -381,  -381,   316,
    2739,  -381,   320,   322,     6,  -381,   291,  -381,  -381,   266,
    -381,     6,   377,  1637,  -381,   376,  1707,   104,  -381,   341,
     132,  -381,  -381,     6,   135,   143,  -381,  2315,  2389,  2155,
     343,  1777,   323,  1847,   291,   291,    -7,   100,  1917,   347,
    -381,  -381,    37,    26,    26,   347,  -381,  -381,  -381,    14,
    -381,   347,  -381,  -381,  -381,    67,   346,    11,    11,   291,
     291,   291,   291,  -381,  -381,    11,    26,   176,   152,   332,
    -381,   354,  -381,   249,   291,    11,    11,  -381,  2739,  -381,
      27,  -381,  -381,  -381,  -381,  -381,  -381,  1917,    11,  1917,
      33,  -381,   291,   291,  1917,   350,  1917,  -381,  -381,  -381,
    -381,  2739,  2739,  1917,    11,  1917,    11,  -381,   224,  -381,
    -381,   126,   216,   265,  -381,  -381,   292,  -381,  -381,   112,
    -381,   394,  2739,  2739,  2739,  2739,   361,   362,    11,  -381,
      11,  -381,  -381,  2739,   366,   367,  -381,  -381,   349,  -381,
    -381,  2073,  2196,   387,   223,  -381,  -381,   369,  -381,   372,
     408,    11,    11,   169,   247,    68,   370,   374,  -381,  -381,
    -381,   363,   291,   291,    11,  1917,   291,  1917,  1917,   373,
     371,   375,  1982,  -381,  2669,  1917,  1917,  -381,   358,   359,
    -381,  -381,  -381,  -381,  -381,  -381,   291,   378,  -381,  -381,
    2739,  2739,   394,  -381,  2237,  -381,  -381,  -381,  1917,  1917,
    -381,  -381,  1917,  -381,  -381,    11,    11,  2704,  2047,   374,
    1917,  -381,  -381,  -381,  -381,  -381,  -381,   267,  -381,  -381,
    -381
  };

  const short
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   259,     0,   235,   234,
     263,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     6,     8,    10,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,     0,     3,   258,   262,     0,     0,     0,     0,     0,
     184,   186,   185,     0,     0,     0,     0,     0,     0,     0,
     190,   191,   187,   188,   189,   192,   264,   115,   117,   126,
     149,   150,   127,   151,   116,   118,   119,   120,   121,   122,
     123,   128,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   180,   181,   182,   183,     0,   237,   152,   260,   261,
       0,    22,     0,     0,     0,   237,    41,     0,    44,     0,
       0,   237,     0,     0,     5,     7,   239,   246,   238,     0,
       0,   250,     0,     0,   241,     0,     0,     0,   148,   129,
     130,     0,     0,   114,     0,   203,   237,     0,   194,     0,
     114,     0,   193,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   200,   201,     0,     0,     0,   231,
     181,     0,   230,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   222,     0,     0,
       0,     0,   245,     0,     0,     0,     0,     0,   125,     0,
     124,   199,     0,     0,   196,   195,     0,     0,   170,   145,
     143,   144,   147,   131,   132,   138,   139,   140,   133,   134,
     135,   136,   146,   137,   141,   142,     0,   164,   207,   208,
     209,   210,   211,   212,   213,   160,   156,     0,   161,     0,
     114,     0,   153,     0,   236,   114,     0,    23,     0,     0,
       0,     0,   248,   224,     0,     0,     0,     0,     0,    85,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      28,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,     0,   111,   149,   150,     0,     0,
       0,    40,    42,    43,    45,     0,     0,     0,     0,   220,
     221,     0,   244,   251,   165,   249,     0,   240,     0,     0,
       0,   113,   202,     0,   204,   113,     0,     0,   206,   237,
       0,   243,   222,     0,     0,   163,   162,   155,   154,   124,
     233,   229,     0,     0,     0,   247,     0,    37,    39,     0,
      35,     0,     0,     0,    71,     0,     0,     0,   256,     0,
       0,   253,   255,     0,     0,     0,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      48,    50,     0,     0,     0,     0,    55,    57,    59,     0,
      53,     0,    63,    65,    67,     0,     0,     0,     0,     0,
       0,     0,     0,   198,   197,     0,     0,     0,   206,     0,
     218,     0,   157,     0,     0,     0,     0,   223,    25,    24,
       0,    36,   108,   106,    70,   104,   102,     0,   222,     0,
       0,   254,     0,     0,     0,     0,     0,   103,   101,   107,
     105,   109,   110,     0,     0,     0,     0,    29,     0,    46,
      49,     0,     0,     0,    51,    58,     0,    61,    66,     0,
     219,   226,   168,   167,   166,   169,   205,   242,     0,   216,
       0,   159,   158,   232,     0,     0,    38,    95,     0,    96,
     252,     0,     0,    86,     0,   112,    32,     0,    30,     0,
       0,   222,   222,     0,     0,     0,     0,   228,   214,   215,
     205,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    91,     0,     0,     0,    47,     0,     0,
      54,    56,    52,    62,    64,    60,     0,     0,    34,   217,
      27,    26,   226,    97,     0,    99,    87,    89,     0,     0,
      88,    90,     0,    33,    31,     0,     0,     0,     0,   228,
       0,    92,    93,    94,    68,    69,   225,     0,   257,    98,
     227
  };

  const short
  Parser::yypgoto_[] =
  {
    -381,  -381,  -381,  -381,   401,   395,  -381,  -381,     4,     7,
    -286,    30,  -381,  -381,  -381,  -381,  -381,  -381,    66,  -381,
    -381,    70,  -381,  -381,  -380,   -14,   -36,    29,   561,  -381,
    -381,  -381,  -381,   -60,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,  -381,   -55,   -10,    24,  -381,   386,   436,
     609,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,  -381,  -381,   297,  -381,  -381,  -381,  -381,  -381,  -381,
    -381,   -94,   357,  -381,  -381,   251,   138,   403,   353,  -381,
    -381,  -381,  -381,  -381,  -381,  -312,   312,   -57,   -77,   -72,
     219,   454,     3,   380,   -35,  -381,  -170,   -41,   134,   209,
     284,  -381,    60,   128,    35,     8,  -381,  -381
  };

  const short
  Parser::yydefgoto_[] =
  {
       0,     3,     4,    26,    27,    28,    29,    30,   382,   383,
      33,   338,   339,    34,    35,    36,    37,    38,   371,   372,
      39,   378,   379,    40,   384,   385,   380,   343,   344,   271,
     272,   273,   502,   503,   274,   275,   276,   277,   278,   279,
     280,   281,   282,   283,   132,   240,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,   134,   135,   317,   299,    95,   229,
     230,   231,   232,   233,   300,   301,   250,   487,   518,   171,
     172,    96,    97,   117,   123,   320,   118,   124,   253,   120,
     121,   350,   351,   352,   122,     6,    11,    12
  };

  const short
  Parser::yytable_[] =
  {
      66,   164,   139,   252,   119,   448,   170,   252,    31,   370,
     399,    32,   125,    43,   127,    44,   249,   288,   101,   373,
      13,   374,   106,     8,   108,     1,     7,   112,   337,    25,
      31,     8,   186,    32,   348,     5,     8,     8,   126,    41,
       8,     8,     8,   128,   433,    31,   133,   140,    32,    43,
       8,     8,     8,    25,   100,   201,   321,    42,     8,   190,
       2,    41,   142,   226,    98,   202,   434,   369,   375,     2,
       2,   444,    16,    16,    18,    18,     2,   167,   129,   130,
     173,     2,   141,   292,   335,     9,   370,     2,   193,   195,
     169,   369,   162,     9,   439,    62,    99,   191,     9,     9,
     163,   174,     9,     9,     9,   448,   468,   239,     2,   176,
     177,   243,     9,     9,     9,   167,   373,    16,   374,    18,
       9,   381,   381,   197,   447,   515,   194,   194,   175,   417,
      43,   178,   182,   209,   210,   211,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     119,   435,   167,   307,   170,   160,   247,   419,   245,   179,
     422,   194,   248,   234,   252,   375,   381,   191,   423,   508,
     509,   293,   162,   436,   373,   181,   374,   234,   173,   303,
     304,   234,   234,   306,   481,   308,   309,   310,   161,   311,
     234,   234,  -126,   314,   507,   420,   315,   316,   194,   174,
     284,   326,   208,   147,   148,   180,   194,   166,   254,   183,
     143,   206,   254,   161,   167,   147,   148,   149,  -220,   119,
     152,   153,   154,   155,   499,  -220,   457,   354,   355,   234,
     150,   151,   152,   153,   154,   155,   330,   328,   169,   458,
     167,   459,   157,   158,   159,   322,    45,   206,     8,    46,
      47,   323,    16,    48,    18,   357,   358,   359,   500,   184,
      49,   185,    43,   187,    50,    51,    52,   176,   177,   403,
     333,    53,    54,    55,   482,    56,   188,    57,     2,   480,
     334,   284,   284,   501,    58,    59,   205,   346,   284,   178,
     189,   341,   284,   284,   206,   198,   353,   361,   363,   199,
     376,   367,   462,   377,    60,    61,    62,    63,    64,    65,
       9,   334,   206,   400,    45,   203,     8,    46,    47,     2,
     483,    48,   155,   409,   550,   234,   408,   204,    49,   410,
     248,   246,    50,    51,    52,   152,   153,   154,   155,    53,
      54,    55,   256,    56,   295,    57,     2,   484,   324,    43,
     296,   297,    58,    59,   431,   432,   325,   327,   332,   336,
     364,    43,   161,   366,   365,   368,   386,   284,   387,   254,
     284,   388,    60,    61,    62,    63,    64,    65,     9,   452,
     453,   454,   455,   376,   395,   284,   377,   284,   396,   404,
     234,   234,   284,   405,   463,   406,   412,   415,   234,   418,
     427,     2,   449,   429,   438,   460,   474,   461,   234,   234,
     443,   486,   471,   472,   488,   489,   446,   492,   493,   498,
     505,   234,   494,   506,    25,   517,   516,   114,   519,   528,
     527,   535,   536,   529,   538,   485,   115,   234,   440,   234,
     466,   284,   531,   284,   170,   341,    43,   512,   284,   445,
     284,    43,   165,   312,    43,   353,    10,   284,   235,   284,
     397,   234,   548,   234,   504,   539,   547,   331,   407,   347,
     102,   103,   104,   105,   107,   305,   109,   110,   111,   113,
     470,   421,   520,   521,   234,   234,   524,   510,   513,   289,
     511,   514,   504,     0,     0,     0,     0,   234,     0,   116,
     116,   116,   192,   116,     0,     0,   537,     0,     0,     0,
     136,     0,     0,   228,     0,     0,     0,     0,     0,   284,
       0,   284,   284,     0,     0,     0,     0,   228,   169,   284,
     284,   228,   228,     0,     0,     0,     0,     0,   234,   234,
     228,   228,     0,     8,     0,     0,     0,     0,     0,     0,
       0,     0,   284,   284,     0,     0,   284,     0,     0,    50,
      51,    52,   285,   227,   284,     0,     0,    54,    55,     0,
      56,     0,    57,     0,     0,     0,   116,   255,     0,   228,
      59,   290,   291,     0,     0,     0,     0,     0,     0,     0,
       0,   302,     0,     0,     0,     0,     0,     0,     0,    60,
      61,    62,    63,    64,    65,     9,     0,     0,     0,     0,
       0,     0,   286,     0,     0,   236,     0,   136,     0,     0,
       0,   244,   136,     0,     0,     0,     0,   251,     0,   318,
       0,   251,     0,     0,   244,     0,   294,     0,     0,     0,
     298,     0,     0,   285,   285,   116,     0,     0,   116,     0,
     285,     0,     0,     0,   285,   285,   313,    -2,    14,     0,
       0,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     0,     0,    25,     0,   228,     0,     0,     0,     0,
     319,     0,     0,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,   286,   286,    25,     0,     0,     0,     0,
     286,     0,     0,     0,   286,   286,     0,     0,   251,     0,
     340,     2,     0,     0,   116,   349,   116,   116,     0,     0,
       0,     0,     0,     0,     0,   398,     0,     0,     0,   285,
       0,     0,   285,     2,     0,     0,     0,   270,     0,     0,
     228,   228,     0,     0,     0,   147,   148,   285,   228,   285,
       0,     0,     0,     0,   285,     0,     0,     0,   228,   228,
     150,   151,   152,   153,   154,   155,     0,     0,     0,     0,
       0,   228,     0,   158,   159,     0,     0,     0,     0,   286,
       0,     0,   286,     0,     0,   287,     0,   228,   251,   228,
     450,   451,     0,     0,     0,   411,     0,   286,   456,   286,
       0,     0,     0,   285,   286,   285,     0,   349,   464,   465,
     285,   228,   285,   228,     0,     0,     0,     0,     0,   285,
       0,   285,     0,     0,     0,   356,     0,   441,   442,     0,
       0,     0,     0,     0,   228,   228,     0,   477,     0,   479,
       0,     0,     0,     0,     0,     0,     0,   228,     0,     0,
     251,     0,     0,   286,     0,   286,     0,     0,     0,     0,
     286,   490,   286,   491,   340,     0,   287,   287,     0,   286,
       0,   286,     0,   287,   349,     0,     0,   287,   287,     0,
       0,   285,     0,   285,   285,     0,     0,     0,   228,   228,
       0,   285,   285,     0,     0,     0,     0,   522,     0,     0,
       0,     0,     0,     0,   414,     0,     0,   414,     0,     0,
       0,     0,     0,     0,   285,   285,     0,     0,   285,     0,
       0,     0,   414,     0,   414,     0,   285,     0,     0,   437,
       0,   286,     0,   286,   286,     0,     0,     0,   544,   545,
       0,   286,   286,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   287,     0,     0,   287,     0,     0,     0,     0,
       0,     0,     0,     0,   286,   286,     0,     0,   286,     0,
     287,     0,   287,     0,     0,     0,   286,   287,   467,     0,
     469,     0,     0,     0,     0,   473,     0,   475,     0,     0,
     342,     0,     0,     0,   476,     0,   478,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   257,     0,   258,
       0,   259,   260,   261,     8,   262,   263,   264,     0,   265,
       0,     0,   266,     0,     0,     0,   287,     0,   287,   267,
      50,    51,    52,   287,     0,   287,     0,     0,    54,    55,
       0,    56,   287,    57,   287,   268,     0,     0,     0,     0,
       0,    59,     0,     0,     0,     0,   523,     0,   525,   526,
       0,     0,     0,     0,     0,     0,   533,   534,   269,     0,
      60,    61,    62,    63,    64,    65,     9,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   541,
     542,     0,     0,   543,     0,     0,     0,     0,     0,     0,
       0,   549,     0,   345,   287,     0,   287,   287,     0,     0,
       0,     0,     0,     0,   287,   287,     0,     0,     0,     0,
     257,     0,   258,     0,   259,   260,   261,     8,   262,   263,
     264,     0,   265,     0,     0,   266,     0,   287,   287,     0,
       0,   287,   267,    50,    51,    52,     0,     0,     0,   287,
       0,    54,    55,     0,    56,     0,    57,     0,   268,     0,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,   360,     0,     0,     0,     0,     0,     0,
       0,   269,     0,    60,    61,    62,    63,    64,    65,     9,
     257,     0,   258,     0,   259,   260,   261,     8,   262,   263,
     264,     0,   265,     0,     0,   266,     0,     0,     0,     0,
       0,     0,   267,    50,    51,    52,     0,     0,     0,     0,
       0,    54,    55,     0,    56,     0,    57,     0,   268,     0,
       0,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,   362,     0,     0,     0,     0,     0,     0,
       0,   269,     0,    60,    61,    62,    63,    64,    65,     9,
     257,     0,   258,     0,   259,   260,   261,     8,   262,   263,
     264,     0,   265,     0,     0,   266,     0,     0,     0,     0,
       0,     0,   267,    50,    51,    52,     0,     0,     0,     0,
       0,    54,    55,     0,    56,     0,    57,     0,   268,     0,
       0,     0,     0,     0,    59,     0,     0,    14,   137,     0,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
       0,   269,    25,    60,    61,    62,    63,    64,    65,     9,
      45,     0,     8,    46,    47,     0,     0,    48,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,    50,    51,
      52,     0,     0,     0,     0,    53,    54,    55,     0,    56,
       2,    57,   138,     0,     0,     0,     0,     0,    58,    59,
       0,     0,     0,   237,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,    61,
      62,    63,    64,    65,     9,    45,     0,     8,    46,    47,
       0,     0,    48,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,    50,    51,    52,     0,     0,     0,     0,
      53,    54,    55,     0,    56,   238,    57,     0,     0,     0,
       0,     0,     0,    58,    59,     0,     0,     0,   241,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    61,    62,    63,    64,    65,     9,
      45,     0,     8,    46,    47,     0,     0,    48,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,    50,    51,
      52,     0,     0,     0,     0,    53,    54,    55,     0,    56,
     242,    57,     0,     0,     0,     0,     0,     0,    58,    59,
       0,     0,     0,   401,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,    61,
      62,    63,    64,    65,     9,    45,     0,     8,    46,    47,
       0,     0,    48,     0,     0,     0,     0,     0,     0,    49,
       0,     0,     0,    50,    51,    52,     0,     0,     0,     0,
      53,    54,    55,     0,    56,   402,    57,     0,     0,     0,
       0,     0,     0,    58,    59,     0,     0,     0,   131,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    61,    62,    63,    64,    65,     9,
      45,     0,     8,    46,    47,     0,     0,    48,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,    50,    51,
      52,     0,     0,     0,     0,    53,    54,    55,     0,    56,
       0,    57,     0,     0,     0,     0,     0,     0,    58,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    60,    61,
      62,    63,    64,    65,     9,   257,   413,   258,     0,   259,
     260,   261,     8,   262,   263,   264,     0,   265,     0,     0,
     266,     0,     0,     0,     0,     0,     0,   267,    50,    51,
      52,     0,     0,     0,     0,     0,    54,    55,     0,    56,
       0,    57,     0,   268,     0,     0,     0,     0,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   269,     0,    60,    61,
      62,    63,    64,    65,     9,   257,     0,   258,   416,   259,
     260,   261,     8,   262,   263,   264,     0,   265,     0,     0,
     266,     0,     0,     0,     0,     0,     0,   267,    50,    51,
      52,     0,     0,     0,     0,     0,    54,    55,     0,    56,
       0,    57,     0,   268,     0,     0,     0,     0,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   269,     0,    60,    61,
      62,    63,    64,    65,     9,   257,     0,   258,     0,   259,
     260,   261,     8,   262,   263,   264,     0,   265,     0,     0,
     266,     0,     0,     0,     0,     0,     0,   267,    50,    51,
      52,     0,     0,     0,     0,     0,    54,    55,     0,    56,
       0,    57,     0,   268,   428,     0,     0,     0,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   269,     0,    60,    61,
      62,    63,    64,    65,     9,   257,     0,   258,     0,   259,
     260,   261,     8,   262,   263,   264,     0,   265,     0,     0,
     266,     0,     0,     0,     0,     0,     0,   267,    50,    51,
      52,     0,     0,     0,     0,     0,    54,    55,     0,    56,
       0,    57,     0,   268,     0,     0,     0,     0,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   269,   430,    60,    61,
      62,    63,    64,    65,     9,   257,     0,   258,     0,   259,
     260,   261,     8,   262,   263,   264,     0,   265,     0,     0,
     266,     0,     0,     0,     0,     0,     0,   267,    50,    51,
      52,     0,     0,     0,     0,     0,    54,    55,     0,    56,
       0,    57,     0,   268,     0,     0,     0,     0,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   269,     0,    60,    61,
      62,    63,    64,    65,     9,    45,     0,     8,    46,    47,
       0,     0,    48,     0,     0,     0,     0,   500,     0,    49,
       0,     0,     0,    50,    51,    52,     0,     0,     0,     0,
      53,    54,    55,     0,    56,     0,    57,     0,     0,   530,
       0,     0,   501,    58,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    60,    61,    62,    63,    64,    65,     9,
      45,     0,     8,    46,    47,     0,     0,    48,     0,     0,
       0,     0,     0,     0,    49,     0,     0,     0,    50,    51,
      52,     0,     0,     0,     0,    53,    54,    55,     0,   168,
       0,    57,   495,     0,     0,     0,     0,     0,    58,    59,
       0,   496,     0,     0,     0,     0,     0,   143,   144,   145,
     146,     0,   147,   148,   149,     0,     0,     0,    60,    61,
      62,    63,    64,    65,     9,     0,     0,   150,   151,   152,
     153,   154,   155,   390,     0,     0,     0,   156,     0,   157,
     158,   159,     0,     0,     0,     0,     0,     0,   143,   144,
     145,   146,     0,   147,   148,   149,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   151,
     152,   153,   154,   155,   426,     0,     0,     0,   156,     0,
     157,   158,   159,     0,     0,     0,     0,     0,     0,   143,
     144,   145,   146,     0,   147,   148,   149,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   150,
     151,   152,   153,   154,   155,   497,     0,     0,     0,   156,
       0,   157,   158,   159,     0,     0,     0,     0,     0,     0,
     143,   144,   145,   146,     0,   147,   148,   149,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     150,   151,   152,   153,   154,   155,   540,     0,     0,     0,
     156,     0,   157,   158,   159,     0,     0,     0,     0,     0,
       0,   143,   144,   145,   146,     0,   147,   148,   149,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   150,   151,   152,   153,   154,   155,   196,     0,     0,
       0,   156,     0,   157,   158,   159,     0,     0,     0,     0,
     143,   144,   145,   146,     0,   147,   148,   149,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     150,   151,   152,   153,   154,   155,   424,     0,     0,     0,
     156,     0,   157,   158,   159,     0,     0,     0,     0,   143,
     144,   145,   146,     0,   147,   148,   149,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   150,
     151,   152,   153,   154,   155,   391,     0,     0,     0,   156,
       0,   157,   158,   159,     0,     0,     0,   143,   144,   145,
     146,     0,   147,   148,   149,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   150,   151,   152,
     153,   154,   155,   425,     0,     0,     0,   156,     0,   157,
     158,   159,     0,   143,   144,   145,   146,     0,   147,   148,
     149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,   151,   152,   153,   154,   155,     0,
     389,     0,     0,   156,     0,   157,   158,   159,   143,   144,
     145,   146,     0,   147,   148,   149,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   151,
     152,   153,   154,   155,     0,     0,     0,   392,   156,     0,
     157,   158,   159,   143,   144,   145,   146,     0,   147,   148,
     149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,   151,   152,   153,   154,   155,     0,
       0,     0,     0,   156,     0,   157,   158,   159,   143,   144,
     145,   146,     0,   147,   148,   149,     0,   200,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,   156,     0,
     157,   158,   159,   143,   144,   145,   146,     0,   147,   148,
     149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,   151,   152,   153,   154,   155,     0,
     207,     0,     0,   156,     0,   157,   158,   159,   143,   144,
     145,   146,     0,   147,   148,   149,     0,   329,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,   156,     0,
     157,   158,   159,   143,   144,   145,   146,     0,   147,   148,
     149,     0,   393,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,   151,   152,   153,   154,   155,     0,
       0,     0,     0,   156,     0,   157,   158,   159,   143,   144,
     145,   146,     0,   147,   148,   149,     0,     0,     0,   394,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,   156,     0,
     157,   158,   159,   143,   144,   145,   146,     0,   147,   148,
     149,     0,     0,     0,     0,     0,     0,   532,     0,     0,
       0,     0,     0,   150,   151,   152,   153,   154,   155,     0,
       0,     0,     0,   156,     0,   157,   158,   159,   143,   144,
     145,   146,     0,   147,   148,   149,     0,     0,     0,     0,
       0,   546,     0,     0,     0,     0,     0,     0,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,   156,     0,
     157,   158,   159,   143,   144,   145,   146,     0,   147,   148,
     149,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   150,   151,   152,   153,   154,   155,     0,
       0,     0,     0,   156,     0,   157,   158,   159,   143,   144,
     145,     0,     0,   147,   148,   149,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   150,   151,
     152,   153,   154,   155,     0,     0,     0,     0,     0,     0,
     157,   158,   159,   143,     0,   145,     0,     0,   147,   148,
     149,     0,     0,     0,   147,   148,   149,     0,     0,     0,
       0,     0,     0,   150,   151,   152,   153,   154,   155,   150,
     151,   152,   153,   154,   155,   157,   158,   159,     0,     0,
       0,   157,   158,   159
  };

  const short
  Parser::yycheck_[] =
  {
      10,    95,    57,   173,    45,   385,   100,   177,     4,   295,
     322,     4,    47,     5,    49,    55,     1,     1,    15,     5,
       0,     7,    19,    25,    21,     3,     1,    24,     1,    16,
      26,    25,    14,    26,     1,     0,    25,    25,    48,     4,
      25,    25,    25,    53,    51,    41,    56,    57,    41,    41,
      25,    25,    25,    16,    56,    53,   226,     3,    25,    25,
      54,    26,    59,    52,    55,    63,    73,    54,    54,    54,
      54,    57,     5,     5,     7,     7,    54,    59,    54,    55,
      52,    54,    58,    66,   254,    87,   372,    54,    25,    25,
     100,    54,    52,    87,    57,    83,    55,    63,    87,    87,
      52,    73,    87,    87,    87,   485,   418,   162,    54,    51,
      52,   166,    87,    87,    87,    59,     5,     5,     7,     7,
      87,    54,    54,    25,    57,    57,    63,    63,    51,    25,
     122,    73,    39,   143,   144,   145,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     191,    51,    59,   194,   248,    39,    57,    25,   168,    51,
      25,    63,    63,   160,   334,    54,    54,    63,    25,   481,
     482,   181,    52,    73,     5,    51,     7,   174,    52,   189,
     190,   178,   179,   193,    58,   195,   196,   197,    72,   199,
     187,   188,    72,   203,   480,    63,   206,   207,    63,    73,
     176,    53,    61,    49,    50,    59,    63,    52,   173,    51,
      44,    63,   177,    72,    59,    49,    50,    51,    66,   260,
      66,    67,    68,    69,     1,    73,   396,   262,   263,   226,
      64,    65,    66,    67,    68,    69,   246,    53,   248,    63,
      59,    65,    76,    77,    78,    64,    23,    63,    25,    26,
      27,    70,     5,    30,     7,   265,   266,   267,    35,    51,
      37,    51,   254,    58,    41,    42,    43,    51,    52,   324,
      53,    48,    49,    50,    58,    52,    58,    54,    54,    55,
      63,   257,   258,    60,    61,    62,    55,   258,   264,    73,
      51,   256,   268,   269,    63,    53,   261,   268,   269,    63,
     296,    53,    53,   296,    81,    82,    83,    84,    85,    86,
      87,    63,    63,   323,    23,    58,    25,    26,    27,    54,
      55,    30,    69,    57,    57,   322,   336,    55,    37,    63,
      63,    73,    41,    42,    43,    66,    67,    68,    69,    48,
      49,    50,    56,    52,    56,    54,    54,    55,    52,   341,
      56,    56,    61,    62,   364,   365,    53,    53,    53,    51,
      75,   353,    72,    53,    75,    51,    51,   343,    66,   334,
     346,    73,    81,    82,    83,    84,    85,    86,    87,   389,
     390,   391,   392,   379,    63,   361,   379,   363,    63,    73,
     387,   388,   368,    73,   404,    73,    19,    21,   395,    58,
      57,    54,    56,    80,   369,    73,    56,    53,   405,   406,
     375,    17,   422,   423,    53,    53,   381,    51,    51,    32,
      51,   418,    73,    51,    16,    51,    56,    26,    65,    58,
      57,    73,    73,    58,    56,   449,    41,   434,   372,   436,
     410,   417,   502,   419,   538,   410,   438,   483,   424,   379,
     426,   443,    95,   202,   446,   420,     2,   433,   161,   435,
     322,   458,   539,   460,   474,   522,   538,   248,   334,   260,
      16,    17,    18,    19,    20,   191,    22,    23,    24,    25,
     420,   353,   492,   493,   481,   482,   496,   483,   484,   177,
     483,   484,   502,    -1,    -1,    -1,    -1,   494,    -1,    45,
      46,    47,   122,    49,    -1,    -1,   516,    -1,    -1,    -1,
      56,    -1,    -1,   160,    -1,    -1,    -1,    -1,    -1,   495,
      -1,   497,   498,    -1,    -1,    -1,    -1,   174,   538,   505,
     506,   178,   179,    -1,    -1,    -1,    -1,    -1,   535,   536,
     187,   188,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   528,   529,    -1,    -1,   532,    -1,    -1,    41,
      42,    43,   176,   160,   540,    -1,    -1,    49,    50,    -1,
      52,    -1,    54,    -1,    -1,    -1,   122,   174,    -1,   226,
      62,   178,   179,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   188,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,
      82,    83,    84,    85,    86,    87,    -1,    -1,    -1,    -1,
      -1,    -1,   176,    -1,    -1,   161,    -1,   163,    -1,    -1,
      -1,   167,   168,    -1,    -1,    -1,    -1,   173,    -1,   226,
      -1,   177,    -1,    -1,   180,    -1,   182,    -1,    -1,    -1,
     186,    -1,    -1,   257,   258,   191,    -1,    -1,   194,    -1,
     264,    -1,    -1,    -1,   268,   269,   202,     0,     1,    -1,
      -1,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    -1,    -1,    16,    -1,   322,    -1,    -1,    -1,    -1,
     226,    -1,    -1,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,   257,   258,    16,    -1,    -1,    -1,    -1,
     264,    -1,    -1,    -1,   268,   269,    -1,    -1,   254,    -1,
     256,    54,    -1,    -1,   260,   261,   262,   263,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   322,    -1,    -1,    -1,   343,
      -1,    -1,   346,    54,    -1,    -1,    -1,   176,    -1,    -1,
     387,   388,    -1,    -1,    -1,    49,    50,   361,   395,   363,
      -1,    -1,    -1,    -1,   368,    -1,    -1,    -1,   405,   406,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      -1,   418,    -1,    77,    78,    -1,    -1,    -1,    -1,   343,
      -1,    -1,   346,    -1,    -1,   176,    -1,   434,   334,   436,
     387,   388,    -1,    -1,    -1,   341,    -1,   361,   395,   363,
      -1,    -1,    -1,   417,   368,   419,    -1,   353,   405,   406,
     424,   458,   426,   460,    -1,    -1,    -1,    -1,    -1,   433,
      -1,   435,    -1,    -1,    -1,   264,    -1,   373,   374,    -1,
      -1,    -1,    -1,    -1,   481,   482,    -1,   434,    -1,   436,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   494,    -1,    -1,
     396,    -1,    -1,   417,    -1,   419,    -1,    -1,    -1,    -1,
     424,   458,   426,   460,   410,    -1,   257,   258,    -1,   433,
      -1,   435,    -1,   264,   420,    -1,    -1,   268,   269,    -1,
      -1,   495,    -1,   497,   498,    -1,    -1,    -1,   535,   536,
      -1,   505,   506,    -1,    -1,    -1,    -1,   494,    -1,    -1,
      -1,    -1,    -1,    -1,   343,    -1,    -1,   346,    -1,    -1,
      -1,    -1,    -1,    -1,   528,   529,    -1,    -1,   532,    -1,
      -1,    -1,   361,    -1,   363,    -1,   540,    -1,    -1,   368,
      -1,   495,    -1,   497,   498,    -1,    -1,    -1,   535,   536,
      -1,   505,   506,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   343,    -1,    -1,   346,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   528,   529,    -1,    -1,   532,    -1,
     361,    -1,   363,    -1,    -1,    -1,   540,   368,   417,    -1,
     419,    -1,    -1,    -1,    -1,   424,    -1,   426,    -1,    -1,
       1,    -1,    -1,    -1,   433,    -1,   435,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,    20,
      -1,    22,    23,    24,    25,    26,    27,    28,    -1,    30,
      -1,    -1,    33,    -1,    -1,    -1,   417,    -1,   419,    40,
      41,    42,    43,   424,    -1,   426,    -1,    -1,    49,    50,
      -1,    52,   433,    54,   435,    56,    -1,    -1,    -1,    -1,
      -1,    62,    -1,    -1,    -1,    -1,   495,    -1,   497,   498,
      -1,    -1,    -1,    -1,    -1,    -1,   505,   506,    79,    -1,
      81,    82,    83,    84,    85,    86,    87,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   528,
     529,    -1,    -1,   532,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   540,    -1,     1,   495,    -1,   497,   498,    -1,    -1,
      -1,    -1,    -1,    -1,   505,   506,    -1,    -1,    -1,    -1,
      18,    -1,    20,    -1,    22,    23,    24,    25,    26,    27,
      28,    -1,    30,    -1,    -1,    33,    -1,   528,   529,    -1,
      -1,   532,    40,    41,    42,    43,    -1,    -1,    -1,   540,
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
      -1,    -1,    -1,    -1,    62,    -1,    -1,     1,     1,    -1,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      -1,    79,    16,    81,    82,    83,    84,    85,    86,    87,
      23,    -1,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      54,    54,    55,    -1,    -1,    -1,    -1,    -1,    61,    62,
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
      48,    49,    50,    -1,    52,    53,    54,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    81,    82,    83,    84,    85,    86,    87,
      23,    -1,    25,    26,    27,    -1,    -1,    30,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    48,    49,    50,    -1,    52,
      -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,    61,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    81,    82,
      83,    84,    85,    86,    87,    18,    19,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    50,    -1,    52,
      -1,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    82,
      83,    84,    85,    86,    87,    18,    -1,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    -1,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    50,    -1,    52,
      -1,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    82,
      83,    84,    85,    86,    87,    18,    -1,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    50,    -1,    52,
      -1,    54,    -1,    56,    57,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    82,
      83,    84,    85,    86,    87,    18,    -1,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    50,    -1,    52,
      -1,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    18,    -1,    20,    -1,    22,
      23,    24,    25,    26,    27,    28,    -1,    30,    -1,    -1,
      33,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    50,    -1,    52,
      -1,    54,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    79,    -1,    81,    82,
      83,    84,    85,    86,    87,    23,    -1,    25,    26,    27,
      -1,    -1,    30,    -1,    -1,    -1,    -1,    35,    -1,    37,
      -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      48,    49,    50,    -1,    52,    -1,    54,    -1,    -1,    57,
      -1,    -1,    60,    61,    62,    -1,    -1,    -1,    -1,    -1,
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
      66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    78,    44,    -1,    46,    -1,    -1,    49,    50,
      51,    -1,    -1,    -1,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    64,
      65,    66,    67,    68,    69,    76,    77,    78,    -1,    -1,
      -1,    76,    77,    78
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    54,    94,    95,   197,   198,     1,    25,    87,
     184,   199,   200,     0,     1,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    16,    96,    97,    98,    99,
     100,   101,   102,   103,   106,   107,   108,   109,   110,   113,
     116,   197,     3,   198,    55,    23,    26,    27,    30,    37,
      41,    42,    43,    48,    49,    50,    52,    54,    61,    62,
      81,    82,    83,    84,    85,    86,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   171,   184,   185,    55,    55,
      56,   185,   184,   184,   184,   184,   185,   184,   185,   184,
     184,   184,   185,   184,    97,    98,   184,   186,   189,   190,
     192,   193,   197,   187,   190,   187,   138,   187,   138,   139,
     139,     1,   137,   138,   167,   168,   184,     1,    55,   137,
     138,   139,   185,    44,    45,    46,    47,    49,    50,    51,
      64,    65,    66,    67,    68,    69,    74,    76,    77,    78,
      39,    72,    52,    52,   164,   165,    52,    59,    52,   138,
     164,   182,   183,    52,    73,    51,    51,    52,    73,    51,
      59,    51,    39,    51,    51,    51,    14,    58,    58,    51,
      25,    63,   186,    25,    63,    25,    31,    25,    53,    63,
      53,    53,    63,    58,    55,    55,    63,    71,    61,   138,
     138,   138,   138,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   138,    52,   170,   171,   172,
     173,   174,   175,   176,   185,   156,   184,     1,    53,   137,
     138,     1,    53,   137,   184,   138,    73,    57,    63,     1,
     179,   184,   189,   191,   197,   170,    56,    18,    20,    22,
      23,    24,    26,    27,    28,    30,    33,    40,    56,    79,
     121,   122,   123,   124,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   139,   141,   142,   143,     1,   179,
     170,   170,    66,   138,   184,    56,    56,    56,   184,   170,
     177,   178,   170,   138,   138,   193,   138,   190,   138,   138,
     138,   138,   168,   184,   138,   138,   138,   169,   170,   184,
     188,   189,    64,    70,    52,    53,    53,    53,    53,    53,
     138,   183,    53,    53,    63,   189,    51,     1,   104,   105,
     184,   197,     1,   120,   121,     1,   120,   192,     1,   184,
     194,   195,   196,   197,   187,   187,   121,   138,   138,   138,
       1,   120,     1,   120,    75,    75,    53,    53,    51,    54,
     103,   111,   112,     5,     7,    54,   101,   102,   114,   115,
     119,    54,   101,   102,   117,   118,    51,    66,    73,    36,
      29,    32,    38,    53,    55,    63,    63,   169,   170,   178,
     138,     1,    53,   137,    73,    73,    73,   191,   138,    57,
      63,   184,    19,    19,   121,    21,    21,    25,    58,    25,
      63,   196,    25,    25,    31,    34,    29,    57,    57,    80,
      80,   138,   138,    51,    73,    51,    73,   121,   197,    57,
     111,   184,   184,   197,    57,   114,   197,    57,   117,    56,
     170,   170,   138,   138,   138,   138,   170,   189,    63,    65,
      73,    53,    53,   138,   170,   170,   104,   121,   178,   121,
     195,   138,   138,   121,    56,   121,   121,   170,   121,   170,
      55,    58,    58,    55,    55,   118,    17,   180,    53,    53,
     170,   170,    51,    51,    73,    29,    38,    29,    32,     1,
      35,    60,   125,   126,   138,    51,    51,   103,   178,   178,
     101,   102,   119,   101,   102,    57,    56,    51,   181,    65,
     138,   138,   170,   121,   138,   121,   121,    57,    58,    58,
      57,   126,    58,   121,   121,    73,    73,   138,    56,   180,
      29,   121,   121,   121,   170,   170,    57,   182,   181,   121,
      57
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
     116,   116,   117,   117,   117,   117,   118,   118,   119,   119,
     120,   120,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   122,   123,   123,   124,   124,
     125,   125,   126,   126,   126,   127,   128,   129,   129,   130,
     131,   132,   132,   132,   132,   133,   133,   133,   133,   134,
     134,   135,   136,   137,   137,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   139,   139,   139,   139,   139,   139,
     139,   140,   140,   140,   140,   140,   140,   140,   140,   140,
     140,   140,   140,   140,   140,   140,   140,   140,   140,   141,
     141,   141,   142,   142,   142,   142,   143,   143,   143,   143,
     144,   145,   145,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   153,   153,   153,   153,   153,   153,   153,   153,
     153,   153,   153,   153,   154,   155,   155,   156,   157,   158,
     159,   159,   160,   161,   162,   162,   162,   163,   164,   165,
     166,   166,   167,   167,   168,   169,   169,   170,   170,   170,
     170,   170,   170,   171,   172,   173,   174,   175,   176,   177,
     177,   178,   178,   179,   179,   180,   180,   181,   181,   182,
     182,   183,   183,   183,   184,   184,   185,   185,   186,   186,
     187,   187,   188,   188,   189,   190,   190,   191,   191,   192,
     192,   193,   194,   194,   195,   195,   195,   196,   197,   197,
     198,   198,   198,   199,   200
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
       8,     6,     4,     1,     4,     1,     2,     1,     6,     6,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     6,     6,     6,
       2,     1,     3,     3,     3,     4,     4,     6,     8,     6,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     1,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     1,     3,     4,     4,     3,     5,     6,     6,
       3,     3,     4,     4,     3,     4,     6,     6,     6,     6,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     3,     3,     5,     5,     3,
       2,     2,     3,     1,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     5,     5,     4,     6,     3,     3,
       1,     1,     0,     3,     1,     4,     0,     4,     0,     3,
       1,     1,     5,     3,     1,     1,     3,     1,     1,     1,
       3,     1,     3,     1,     3,     2,     1,     2,     1,     3,
       1,     3,     3,     1,     2,     1,     1,     7,     2,     1,
       3,     3,     3,     1,     2
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
  "ImplementationDefinition", "ImplementationDefinitionElement",
  "ImplementationDefinitionList", "Declaration", "Rules", "Rule",
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
  "RecordLiteral", "StructureLiteral", "Assignments", "Assignment",
  "Types", "Type", "BasicType", "TupleType", "RecordType", "TemplateType",
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
       0,   434,   434,   444,   450,   458,   464,   474,   480,   484,
     492,   496,   500,   504,   508,   512,   516,   520,   524,   528,
     532,   536,   544,   574,   595,   603,   608,   614,   622,   628,
     633,   640,   646,   650,   658,   673,   677,   683,   691,   698,
     708,   716,   720,   728,   740,   744,   752,   761,   767,   775,
     781,   795,   804,   810,   814,   820,   824,   830,   838,   844,
     858,   862,   872,   878,   882,   888,   896,   902,   916,   922,
     936,   942,   952,   956,   960,   964,   968,   972,   976,   980,
     984,   988,   992,   996,  1000,  1008,  1016,  1020,  1028,  1032,
    1040,  1046,  1056,  1060,  1064,  1072,  1080,  1088,  1092,  1100,
    1108,  1116,  1120,  1124,  1129,  1138,  1142,  1146,  1151,  1160,
    1164,  1175,  1183,  1195,  1202,  1212,  1216,  1220,  1224,  1228,
    1232,  1236,  1240,  1244,  1252,  1256,  1260,  1264,  1268,  1272,
    1276,  1288,  1292,  1296,  1300,  1304,  1308,  1312,  1316,  1320,
    1324,  1328,  1332,  1336,  1340,  1344,  1348,  1352,  1356,  1364,
    1368,  1372,  1380,  1385,  1392,  1398,  1406,  1411,  1418,  1424,
    1432,  1440,  1447,  1453,  1461,  1469,  1477,  1485,  1493,  1501,
    1509,  1521,  1525,  1529,  1533,  1537,  1541,  1545,  1549,  1553,
    1557,  1561,  1565,  1569,  1577,  1586,  1592,  1602,  1610,  1618,
    1626,  1630,  1638,  1646,  1654,  1661,  1667,  1675,  1685,  1697,
    1711,  1715,  1727,  1734,  1743,  1755,  1762,  1771,  1775,  1779,
    1783,  1787,  1791,  1799,  1807,  1818,  1829,  1837,  1845,  1857,
    1864,  1874,  1878,  1886,  1893,  1907,  1911,  1919,  1923,  1932,
    1939,  1949,  1954,  1960,  1975,  1979,  1988,  1995,  2007,  2011,
    2020,  2027,  2037,  2044,  2054,  2063,  2069,  2077,  2083,  2095,
    2102,  2111,  2123,  2130,  2139,  2145,  2149,  2156,  2176,  2182,
    2191,  2198,  2205,  2212,  2219
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
#line 6485 "GrammarParser.cpp"

#line 2225 "../../obj/src/GrammarParser.y"


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
