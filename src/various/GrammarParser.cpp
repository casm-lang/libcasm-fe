// A Bison parser, made by GNU Bison 3.3.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.





#include "GrammarParser.tab.h"


// Unqualified %code blocks.
#line 90 "../../obj/src/GrammarParser.y" // lalr1.cc:435

    #include <libcasm-fe/Exception>
    #include <libcasm-fe/Logger>

    #include "../../src/Lexer.h"
    #include "../../src/various/GrammarToken.h"

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

    static BasicType::Ptr createRuleRefType( libstdhl::SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::RuleReferenceType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( libstdhl::SourceLocation& sourceLocation )
    {
        const auto name = Ast::make< Identifier >( sourceLocation, "Agent" );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( libstdhl::SourceLocation& sourceLocation, const Initializers::Ptr& initializers )
    {
        const auto agentType = createAgentType( sourceLocation );
        const auto ruleRefType = createRuleRefType( sourceLocation );

        const auto argTypes = Ast::make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = Ast::make< Identifier >( sourceLocation, "program" );
        const auto defined = Ast::make< Defined >(
            sourceLocation, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( sourceLocation ), Token::unresolved() );

        const auto initially = Ast::make< Initially >( sourceLocation, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );

        return Ast::make< FunctionDefinition >(
            sourceLocation, Token::unresolved(), program, Token::unresolved(), argTypes, Token::unresolved(), ruleRefType, defined, initially );
    }

    static IdentifierPath::Ptr asIdentifierPath( const Identifier::Ptr& identifier )
    {
        const auto& location = identifier->sourceLocation();
        return Ast::make< IdentifierPath >( location, identifier );
    }

#line 110 "GrammarParser.cpp" // lalr1.cc:435


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


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 50 "../../obj/src/GrammarParser.y" // lalr1.cc:510
namespace libcasm_fe {
#line 205 "GrammarParser.cpp" // lalr1.cc:510

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


  /// Build a parser object.
  Parser::Parser (Logger& m_log_yyarg, Lexer& m_lexer_yyarg, Specification& m_specification_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
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
  | Symbol types.  |
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

  Parser::symbol_number_type
  Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 3: // "CASM"
      case 4: // "init"
      case 5: // "derived"
      case 6: // "enumeration"
      case 7: // "rule"
      case 8: // "using"
      case 9: // "invariant"
      case 10: // "function"
      case 11: // "initially"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "in"
      case 20: // "forall"
      case 21: // "choose"
      case 22: // "iterate"
      case 23: // "do"
      case 24: // "if"
      case 25: // "then"
      case 26: // "else"
      case 27: // "case"
      case 28: // "of"
      case 29: // "default"
      case 30: // "holds"
      case 31: // "exists"
      case 32: // "with"
      case 33: // "as"
      case 34: // "while"
      case 35: // "undef"
      case 36: // "false"
      case 37: // "true"
      case 38: // "and"
      case 39: // "or"
      case 40: // "xor"
      case 41: // "implies"
      case 42: // "not"
      case 43: // "+"
      case 44: // "-"
      case 45: // "="
      case 46: // "("
      case 47: // ")"
      case 48: // "["
      case 49: // "]"
      case 50: // "{"
      case 51: // "}"
      case 52: // ":"
      case 53: // "::"
      case 54: // "_"
      case 55: // "|"
      case 56: // "@"
      case 57: // ","
      case 58: // "<"
      case 59: // ">"
      case 60: // "*"
      case 61: // "/"
      case 62: // "%"
      case 63: // "^"
      case 64: // "'"
      case 65: // ".."
      case 66: // "."
      case 67: // "->"
      case 68: // "=>"
      case 69: // ":="
      case 70: // "!="
      case 71: // "<="
      case 72: // ">="
      case 73: // "{|"
      case 74: // "|}"
        value.YY_MOVE_OR_COPY< Ast::Token::Ptr > (YY_MOVE (that.value));
        break;

      case 175: // Attribute
        value.YY_MOVE_OR_COPY< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case 174: // Attributes
        value.YY_MOVE_OR_COPY< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case 176: // BasicAttribute
        value.YY_MOVE_OR_COPY< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 151: // BasicType
        value.YY_MOVE_OR_COPY< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case 113: // BlockRule
        value.YY_MOVE_OR_COPY< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case 122: // CallExpression
        value.YY_MOVE_OR_COPY< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 116: // CallRule
        value.YY_MOVE_OR_COPY< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 133: // CardinalityExpression
        value.YY_MOVE_OR_COPY< CardinalityExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 108: // CaseLabel
        value.YY_MOVE_OR_COPY< Case::Ptr > (YY_MOVE (that.value));
        break;

      case 106: // CaseRule
        value.YY_MOVE_OR_COPY< CaseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 107: // CaseLabels
        value.YY_MOVE_OR_COPY< Cases::Ptr > (YY_MOVE (that.value));
        break;

      case 130: // ChooseExpression
        value.YY_MOVE_OR_COPY< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 111: // ChooseRule
        value.YY_MOVE_OR_COPY< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 129: // ConditionalExpression
        value.YY_MOVE_OR_COPY< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 105: // ConditionalRule
        value.YY_MOVE_OR_COPY< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 160: // MaybeDefined
        value.YY_MOVE_OR_COPY< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        value.YY_MOVE_OR_COPY< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case 90: // Definitions
        value.YY_MOVE_OR_COPY< Definitions::Ptr > (YY_MOVE (that.value));
        break;

      case 95: // DerivedDefinition
        value.YY_MOVE_OR_COPY< DerivedDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 123: // DirectCallExpression
        value.YY_MOVE_OR_COPY< DirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 94: // EnumerationDefinition
        value.YY_MOVE_OR_COPY< EnumerationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 98: // EnumeratorDefinition
        value.YY_MOVE_OR_COPY< EnumeratorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 99: // Enumerators
        value.YY_MOVE_OR_COPY< Enumerators::Ptr > (YY_MOVE (that.value));
        break;

      case 132: // ExistentialQuantifierExpression
        value.YY_MOVE_OR_COPY< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
        value.YY_MOVE_OR_COPY< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case 177: // ExpressionAttribute
        value.YY_MOVE_OR_COPY< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 118: // Terms
        value.YY_MOVE_OR_COPY< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case 156: // FixedSizedType
        value.YY_MOVE_OR_COPY< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case 110: // ForallRule
        value.YY_MOVE_OR_COPY< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 97: // FunctionDefinition
        value.YY_MOVE_OR_COPY< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Header
        value.YY_MOVE_OR_COPY< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 81: // "identifier"
      case 164: // Identifier
        value.YY_MOVE_OR_COPY< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case 165: // IdentifierPath
        value.YY_MOVE_OR_COPY< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 126: // IndirectCallExpression
        value.YY_MOVE_OR_COPY< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 93: // InitDefinition
        value.YY_MOVE_OR_COPY< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 163: // Initializer
        value.YY_MOVE_OR_COPY< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case 162: // Initializers
        value.YY_MOVE_OR_COPY< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case 161: // MaybeInitially
        value.YY_MOVE_OR_COPY< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case 101: // InvariantDefinition
        value.YY_MOVE_OR_COPY< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 112: // IterateRule
        value.YY_MOVE_OR_COPY< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 128: // LetExpression
        value.YY_MOVE_OR_COPY< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 109: // LetRule
        value.YY_MOVE_OR_COPY< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case 143: // ListLiteral
        value.YY_MOVE_OR_COPY< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 134: // Literal
        value.YY_MOVE_OR_COPY< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case 125: // LiteralCallExpression
        value.YY_MOVE_OR_COPY< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 124: // MethodCallExpression
        value.YY_MOVE_OR_COPY< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 148: // Assignment
        value.YY_MOVE_OR_COPY< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 147: // Assignments
        value.YY_MOVE_OR_COPY< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case 144: // RangeLiteral
        value.YY_MOVE_OR_COPY< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 146: // RecordLiteral
        value.YY_MOVE_OR_COPY< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 153: // RecordType
        value.YY_MOVE_OR_COPY< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case 142: // ReferenceLiteral
        value.YY_MOVE_OR_COPY< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 155: // RelationType
        value.YY_MOVE_OR_COPY< RelationType::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // Rule
        value.YY_MOVE_OR_COPY< Rule::Ptr > (YY_MOVE (that.value));
        break;

      case 96: // RuleDefinition
        value.YY_MOVE_OR_COPY< RuleDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 102: // Rules
        value.YY_MOVE_OR_COPY< Rules::Ptr > (YY_MOVE (that.value));
        break;

      case 114: // SequenceRule
        value.YY_MOVE_OR_COPY< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case 104: // SkipRule
        value.YY_MOVE_OR_COPY< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case 88: // Specification
        value.YY_MOVE_OR_COPY< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case 154: // TemplateType
        value.YY_MOVE_OR_COPY< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case 145: // TupleLiteral
        value.YY_MOVE_OR_COPY< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 152: // TupleType
        value.YY_MOVE_OR_COPY< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case 127: // TypeCastingExpression
        value.YY_MOVE_OR_COPY< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 149: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        value.YY_MOVE_OR_COPY< Types::Ptr > (YY_MOVE (that.value));
        break;

      case 135: // UndefinedLiteral
        value.YY_MOVE_OR_COPY< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 131: // UniversalQuantifierExpression
        value.YY_MOVE_OR_COPY< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 115: // UpdateRule
        value.YY_MOVE_OR_COPY< UpdateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 100: // UsingDefinition
        value.YY_MOVE_OR_COPY< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
      case 136: // BooleanLiteral
      case 137: // IntegerLiteral
      case 138: // RationalLiteral
      case 139: // DecimalLiteral
      case 140: // BinaryLiteral
      case 141: // StringLiteral
        value.YY_MOVE_OR_COPY< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 173: // VariableBinding
        value.YY_MOVE_OR_COPY< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case 172: // VariableBindings
        value.YY_MOVE_OR_COPY< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.YY_MOVE_OR_COPY< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 159: // Parameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        value.YY_MOVE_OR_COPY< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 117: // WhileRule
        value.YY_MOVE_OR_COPY< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case 150: // Type
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
    switch (that.type_get ())
    {
      case 3: // "CASM"
      case 4: // "init"
      case 5: // "derived"
      case 6: // "enumeration"
      case 7: // "rule"
      case 8: // "using"
      case 9: // "invariant"
      case 10: // "function"
      case 11: // "initially"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "in"
      case 20: // "forall"
      case 21: // "choose"
      case 22: // "iterate"
      case 23: // "do"
      case 24: // "if"
      case 25: // "then"
      case 26: // "else"
      case 27: // "case"
      case 28: // "of"
      case 29: // "default"
      case 30: // "holds"
      case 31: // "exists"
      case 32: // "with"
      case 33: // "as"
      case 34: // "while"
      case 35: // "undef"
      case 36: // "false"
      case 37: // "true"
      case 38: // "and"
      case 39: // "or"
      case 40: // "xor"
      case 41: // "implies"
      case 42: // "not"
      case 43: // "+"
      case 44: // "-"
      case 45: // "="
      case 46: // "("
      case 47: // ")"
      case 48: // "["
      case 49: // "]"
      case 50: // "{"
      case 51: // "}"
      case 52: // ":"
      case 53: // "::"
      case 54: // "_"
      case 55: // "|"
      case 56: // "@"
      case 57: // ","
      case 58: // "<"
      case 59: // ">"
      case 60: // "*"
      case 61: // "/"
      case 62: // "%"
      case 63: // "^"
      case 64: // "'"
      case 65: // ".."
      case 66: // "."
      case 67: // "->"
      case 68: // "=>"
      case 69: // ":="
      case 70: // "!="
      case 71: // "<="
      case 72: // ">="
      case 73: // "{|"
      case 74: // "|}"
        value.move< Ast::Token::Ptr > (YY_MOVE (that.value));
        break;

      case 175: // Attribute
        value.move< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case 174: // Attributes
        value.move< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case 176: // BasicAttribute
        value.move< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 151: // BasicType
        value.move< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case 113: // BlockRule
        value.move< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case 122: // CallExpression
        value.move< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 116: // CallRule
        value.move< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 133: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 108: // CaseLabel
        value.move< Case::Ptr > (YY_MOVE (that.value));
        break;

      case 106: // CaseRule
        value.move< CaseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 107: // CaseLabels
        value.move< Cases::Ptr > (YY_MOVE (that.value));
        break;

      case 130: // ChooseExpression
        value.move< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 111: // ChooseRule
        value.move< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 129: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 105: // ConditionalRule
        value.move< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 160: // MaybeDefined
        value.move< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        value.move< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case 90: // Definitions
        value.move< Definitions::Ptr > (YY_MOVE (that.value));
        break;

      case 95: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 123: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 94: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 98: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 99: // Enumerators
        value.move< Enumerators::Ptr > (YY_MOVE (that.value));
        break;

      case 132: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
        value.move< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case 177: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 118: // Terms
        value.move< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case 156: // FixedSizedType
        value.move< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case 110: // ForallRule
        value.move< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 97: // FunctionDefinition
        value.move< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Header
        value.move< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 81: // "identifier"
      case 164: // Identifier
        value.move< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case 165: // IdentifierPath
        value.move< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 126: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 93: // InitDefinition
        value.move< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 163: // Initializer
        value.move< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case 162: // Initializers
        value.move< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case 161: // MaybeInitially
        value.move< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case 101: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 112: // IterateRule
        value.move< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 128: // LetExpression
        value.move< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 109: // LetRule
        value.move< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case 143: // ListLiteral
        value.move< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 134: // Literal
        value.move< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case 125: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 124: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 148: // Assignment
        value.move< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 147: // Assignments
        value.move< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case 144: // RangeLiteral
        value.move< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 146: // RecordLiteral
        value.move< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 153: // RecordType
        value.move< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case 142: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 155: // RelationType
        value.move< RelationType::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // Rule
        value.move< Rule::Ptr > (YY_MOVE (that.value));
        break;

      case 96: // RuleDefinition
        value.move< RuleDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 102: // Rules
        value.move< Rules::Ptr > (YY_MOVE (that.value));
        break;

      case 114: // SequenceRule
        value.move< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case 104: // SkipRule
        value.move< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case 88: // Specification
        value.move< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case 154: // TemplateType
        value.move< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case 145: // TupleLiteral
        value.move< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 152: // TupleType
        value.move< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case 127: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 149: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        value.move< Types::Ptr > (YY_MOVE (that.value));
        break;

      case 135: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 131: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 115: // UpdateRule
        value.move< UpdateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 100: // UsingDefinition
        value.move< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
      case 136: // BooleanLiteral
      case 137: // IntegerLiteral
      case 138: // RationalLiteral
      case 139: // DecimalLiteral
      case 140: // BinaryLiteral
      case 141: // StringLiteral
        value.move< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 173: // VariableBinding
        value.move< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case 172: // VariableBindings
        value.move< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 159: // Parameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        value.move< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 117: // WhileRule
        value.move< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case 150: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 3: // "CASM"
      case 4: // "init"
      case 5: // "derived"
      case 6: // "enumeration"
      case 7: // "rule"
      case 8: // "using"
      case 9: // "invariant"
      case 10: // "function"
      case 11: // "initially"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "in"
      case 20: // "forall"
      case 21: // "choose"
      case 22: // "iterate"
      case 23: // "do"
      case 24: // "if"
      case 25: // "then"
      case 26: // "else"
      case 27: // "case"
      case 28: // "of"
      case 29: // "default"
      case 30: // "holds"
      case 31: // "exists"
      case 32: // "with"
      case 33: // "as"
      case 34: // "while"
      case 35: // "undef"
      case 36: // "false"
      case 37: // "true"
      case 38: // "and"
      case 39: // "or"
      case 40: // "xor"
      case 41: // "implies"
      case 42: // "not"
      case 43: // "+"
      case 44: // "-"
      case 45: // "="
      case 46: // "("
      case 47: // ")"
      case 48: // "["
      case 49: // "]"
      case 50: // "{"
      case 51: // "}"
      case 52: // ":"
      case 53: // "::"
      case 54: // "_"
      case 55: // "|"
      case 56: // "@"
      case 57: // ","
      case 58: // "<"
      case 59: // ">"
      case 60: // "*"
      case 61: // "/"
      case 62: // "%"
      case 63: // "^"
      case 64: // "'"
      case 65: // ".."
      case 66: // "."
      case 67: // "->"
      case 68: // "=>"
      case 69: // ":="
      case 70: // "!="
      case 71: // "<="
      case 72: // ">="
      case 73: // "{|"
      case 74: // "|}"
        value.move< Ast::Token::Ptr > (that.value);
        break;

      case 175: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 174: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 176: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 151: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 113: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 122: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
        break;

      case 116: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 133: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (that.value);
        break;

      case 108: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 106: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 107: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 130: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 111: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 129: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 105: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 160: // MaybeDefined
        value.move< Defined::Ptr > (that.value);
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 90: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 95: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 123: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 94: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 98: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 99: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 132: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
        value.move< Expression::Ptr > (that.value);
        break;

      case 177: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 118: // Terms
        value.move< Expressions::Ptr > (that.value);
        break;

      case 156: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 110: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 97: // FunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 89: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 81: // "identifier"
      case 164: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 165: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 126: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 93: // InitDefinition
        value.move< InitDefinition::Ptr > (that.value);
        break;

      case 163: // Initializer
        value.move< Initializer::Ptr > (that.value);
        break;

      case 162: // Initializers
        value.move< Initializers::Ptr > (that.value);
        break;

      case 161: // MaybeInitially
        value.move< Initially::Ptr > (that.value);
        break;

      case 101: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (that.value);
        break;

      case 112: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 128: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 109: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 143: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 134: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 125: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 124: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 148: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 147: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 144: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 146: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 153: // RecordType
        value.move< RecordType::Ptr > (that.value);
        break;

      case 142: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 155: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 103: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 96: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 102: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 114: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 104: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 88: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 154: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 145: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 152: // TupleType
        value.move< TupleType::Ptr > (that.value);
        break;

      case 127: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 149: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 135: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 131: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 115: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 100: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
      case 136: // BooleanLiteral
      case 137: // IntegerLiteral
      case 138: // RationalLiteral
      case 139: // DecimalLiteral
      case 140: // BinaryLiteral
      case 141: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 173: // VariableBinding
        value.move< VariableBinding::Ptr > (that.value);
        break;

      case 172: // VariableBindings
        value.move< VariableBindings::Ptr > (that.value);
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 159: // Parameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 117: // WhileRule
        value.move< WhileRule::Ptr > (that.value);
        break;

      case 150: // Type
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
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
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
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
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
    // State.
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
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
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

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

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
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
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
      case 3: // "CASM"
      case 4: // "init"
      case 5: // "derived"
      case 6: // "enumeration"
      case 7: // "rule"
      case 8: // "using"
      case 9: // "invariant"
      case 10: // "function"
      case 11: // "initially"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "in"
      case 20: // "forall"
      case 21: // "choose"
      case 22: // "iterate"
      case 23: // "do"
      case 24: // "if"
      case 25: // "then"
      case 26: // "else"
      case 27: // "case"
      case 28: // "of"
      case 29: // "default"
      case 30: // "holds"
      case 31: // "exists"
      case 32: // "with"
      case 33: // "as"
      case 34: // "while"
      case 35: // "undef"
      case 36: // "false"
      case 37: // "true"
      case 38: // "and"
      case 39: // "or"
      case 40: // "xor"
      case 41: // "implies"
      case 42: // "not"
      case 43: // "+"
      case 44: // "-"
      case 45: // "="
      case 46: // "("
      case 47: // ")"
      case 48: // "["
      case 49: // "]"
      case 50: // "{"
      case 51: // "}"
      case 52: // ":"
      case 53: // "::"
      case 54: // "_"
      case 55: // "|"
      case 56: // "@"
      case 57: // ","
      case 58: // "<"
      case 59: // ">"
      case 60: // "*"
      case 61: // "/"
      case 62: // "%"
      case 63: // "^"
      case 64: // "'"
      case 65: // ".."
      case 66: // "."
      case 67: // "->"
      case 68: // "=>"
      case 69: // ":="
      case 70: // "!="
      case 71: // "<="
      case 72: // ">="
      case 73: // "{|"
      case 74: // "|}"
        yylhs.value.emplace< Ast::Token::Ptr > ();
        break;

      case 175: // Attribute
        yylhs.value.emplace< Attribute::Ptr > ();
        break;

      case 174: // Attributes
        yylhs.value.emplace< Attributes::Ptr > ();
        break;

      case 176: // BasicAttribute
        yylhs.value.emplace< BasicAttribute::Ptr > ();
        break;

      case 151: // BasicType
        yylhs.value.emplace< BasicType::Ptr > ();
        break;

      case 113: // BlockRule
        yylhs.value.emplace< BlockRule::Ptr > ();
        break;

      case 122: // CallExpression
        yylhs.value.emplace< CallExpression::Ptr > ();
        break;

      case 116: // CallRule
        yylhs.value.emplace< CallRule::Ptr > ();
        break;

      case 133: // CardinalityExpression
        yylhs.value.emplace< CardinalityExpression::Ptr > ();
        break;

      case 108: // CaseLabel
        yylhs.value.emplace< Case::Ptr > ();
        break;

      case 106: // CaseRule
        yylhs.value.emplace< CaseRule::Ptr > ();
        break;

      case 107: // CaseLabels
        yylhs.value.emplace< Cases::Ptr > ();
        break;

      case 130: // ChooseExpression
        yylhs.value.emplace< ChooseExpression::Ptr > ();
        break;

      case 111: // ChooseRule
        yylhs.value.emplace< ChooseRule::Ptr > ();
        break;

      case 129: // ConditionalExpression
        yylhs.value.emplace< ConditionalExpression::Ptr > ();
        break;

      case 105: // ConditionalRule
        yylhs.value.emplace< ConditionalRule::Ptr > ();
        break;

      case 160: // MaybeDefined
        yylhs.value.emplace< Defined::Ptr > ();
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        yylhs.value.emplace< Definition::Ptr > ();
        break;

      case 90: // Definitions
        yylhs.value.emplace< Definitions::Ptr > ();
        break;

      case 95: // DerivedDefinition
        yylhs.value.emplace< DerivedDefinition::Ptr > ();
        break;

      case 123: // DirectCallExpression
        yylhs.value.emplace< DirectCallExpression::Ptr > ();
        break;

      case 94: // EnumerationDefinition
        yylhs.value.emplace< EnumerationDefinition::Ptr > ();
        break;

      case 98: // EnumeratorDefinition
        yylhs.value.emplace< EnumeratorDefinition::Ptr > ();
        break;

      case 99: // Enumerators
        yylhs.value.emplace< Enumerators::Ptr > ();
        break;

      case 132: // ExistentialQuantifierExpression
        yylhs.value.emplace< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
        yylhs.value.emplace< Expression::Ptr > ();
        break;

      case 177: // ExpressionAttribute
        yylhs.value.emplace< ExpressionAttribute::Ptr > ();
        break;

      case 118: // Terms
        yylhs.value.emplace< Expressions::Ptr > ();
        break;

      case 156: // FixedSizedType
        yylhs.value.emplace< FixedSizedType::Ptr > ();
        break;

      case 110: // ForallRule
        yylhs.value.emplace< ForallRule::Ptr > ();
        break;

      case 97: // FunctionDefinition
        yylhs.value.emplace< FunctionDefinition::Ptr > ();
        break;

      case 89: // Header
        yylhs.value.emplace< HeaderDefinition::Ptr > ();
        break;

      case 81: // "identifier"
      case 164: // Identifier
        yylhs.value.emplace< Identifier::Ptr > ();
        break;

      case 165: // IdentifierPath
        yylhs.value.emplace< IdentifierPath::Ptr > ();
        break;

      case 126: // IndirectCallExpression
        yylhs.value.emplace< IndirectCallExpression::Ptr > ();
        break;

      case 93: // InitDefinition
        yylhs.value.emplace< InitDefinition::Ptr > ();
        break;

      case 163: // Initializer
        yylhs.value.emplace< Initializer::Ptr > ();
        break;

      case 162: // Initializers
        yylhs.value.emplace< Initializers::Ptr > ();
        break;

      case 161: // MaybeInitially
        yylhs.value.emplace< Initially::Ptr > ();
        break;

      case 101: // InvariantDefinition
        yylhs.value.emplace< InvariantDefinition::Ptr > ();
        break;

      case 112: // IterateRule
        yylhs.value.emplace< IterateRule::Ptr > ();
        break;

      case 128: // LetExpression
        yylhs.value.emplace< LetExpression::Ptr > ();
        break;

      case 109: // LetRule
        yylhs.value.emplace< LetRule::Ptr > ();
        break;

      case 143: // ListLiteral
        yylhs.value.emplace< ListLiteral::Ptr > ();
        break;

      case 134: // Literal
        yylhs.value.emplace< Literal::Ptr > ();
        break;

      case 125: // LiteralCallExpression
        yylhs.value.emplace< LiteralCallExpression::Ptr > ();
        break;

      case 124: // MethodCallExpression
        yylhs.value.emplace< MethodCallExpression::Ptr > ();
        break;

      case 148: // Assignment
        yylhs.value.emplace< NamedExpression::Ptr > ();
        break;

      case 147: // Assignments
        yylhs.value.emplace< NamedExpressions::Ptr > ();
        break;

      case 144: // RangeLiteral
        yylhs.value.emplace< RangeLiteral::Ptr > ();
        break;

      case 146: // RecordLiteral
        yylhs.value.emplace< RecordLiteral::Ptr > ();
        break;

      case 153: // RecordType
        yylhs.value.emplace< RecordType::Ptr > ();
        break;

      case 142: // ReferenceLiteral
        yylhs.value.emplace< ReferenceLiteral::Ptr > ();
        break;

      case 155: // RelationType
        yylhs.value.emplace< RelationType::Ptr > ();
        break;

      case 103: // Rule
        yylhs.value.emplace< Rule::Ptr > ();
        break;

      case 96: // RuleDefinition
        yylhs.value.emplace< RuleDefinition::Ptr > ();
        break;

      case 102: // Rules
        yylhs.value.emplace< Rules::Ptr > ();
        break;

      case 114: // SequenceRule
        yylhs.value.emplace< SequenceRule::Ptr > ();
        break;

      case 104: // SkipRule
        yylhs.value.emplace< SkipRule::Ptr > ();
        break;

      case 88: // Specification
        yylhs.value.emplace< Specification::Ptr > ();
        break;

      case 154: // TemplateType
        yylhs.value.emplace< TemplateType::Ptr > ();
        break;

      case 145: // TupleLiteral
        yylhs.value.emplace< TupleLiteral::Ptr > ();
        break;

      case 152: // TupleType
        yylhs.value.emplace< TupleType::Ptr > ();
        break;

      case 127: // TypeCastingExpression
        yylhs.value.emplace< TypeCastingExpression::Ptr > ();
        break;

      case 149: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        yylhs.value.emplace< Types::Ptr > ();
        break;

      case 135: // UndefinedLiteral
        yylhs.value.emplace< UndefLiteral::Ptr > ();
        break;

      case 131: // UniversalQuantifierExpression
        yylhs.value.emplace< UniversalQuantifierExpression::Ptr > ();
        break;

      case 115: // UpdateRule
        yylhs.value.emplace< UpdateRule::Ptr > ();
        break;

      case 100: // UsingDefinition
        yylhs.value.emplace< UsingDefinition::Ptr > ();
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
      case 136: // BooleanLiteral
      case 137: // IntegerLiteral
      case 138: // RationalLiteral
      case 139: // DecimalLiteral
      case 140: // BinaryLiteral
      case 141: // StringLiteral
        yylhs.value.emplace< ValueLiteral::Ptr > ();
        break;

      case 173: // VariableBinding
        yylhs.value.emplace< VariableBinding::Ptr > ();
        break;

      case 172: // VariableBindings
        yylhs.value.emplace< VariableBindings::Ptr > ();
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        yylhs.value.emplace< VariableDefinition::Ptr > ();
        break;

      case 159: // Parameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        yylhs.value.emplace< VariableDefinitions::Ptr > ();
        break;

      case 117: // WhileRule
        yylhs.value.emplace< WhileRule::Ptr > ();
        break;

      case 150: // Type
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
  case 2:
#line 451 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      m_specification.setHeader( yystack_[1].value.as < HeaderDefinition::Ptr > () );
      m_specification.setDefinitions( yystack_[0].value.as < Definitions::Ptr > () );
      m_specification.setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 2209 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 3:
#line 461 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2219 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 4:
#line 467 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2227 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 5:
#line 475 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2237 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 6:
#line 481 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 7:
#line 491 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2257 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 8:
#line 497 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2265 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 9:
#line 501 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2273 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 10:
#line 509 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2281 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 11:
#line 513 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2289 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 12:
#line 517 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2297 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 13:
#line 521 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2305 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 14:
#line 525 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 2313 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 15:
#line 529 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 2321 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 16:
#line 533 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 2329 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 17:
#line 541 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );

      const auto singleAgentIdentifier = Ast::make< Identifier >( yylhs.location, "$" );
      auto singleAgentArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( singleAgentIdentifier ), singleAgentArguments );
      singleAgent->setTargetType( DirectCallExpression::TargetType::CONSTANT );

      const auto initializers = Ast::make< Initializers >( yylhs.location );
      const auto programFunction = createProgramFunction( yylhs.location, initializers );
      const auto programArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      programArguments->add( singleAgent );

      const auto ruleReference = Ast::make< ReferenceLiteral >( yylhs.location, Token::unresolved(), yystack_[0].value.as < IdentifierPath::Ptr > () );
      const auto initializer = Ast::make< Initializer >(
          yylhs.location, Token::unresolved(), programArguments, Token::unresolved(), Token::unresolved(), ruleReference );
      initializers->add( initializer );

      // apply the name of the program declaration to the initializer functions
      for( auto& initializer : *initializers )
      {
          initializer->updateRule()->function()->setIdentifier(
              asIdentifierPath( programFunction->identifier() ) );
      }

      yylhs.value.as < InitDefinition::Ptr > ()->setProgramFunction( programFunction );
  }
#line 2362 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 18:
#line 570 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );

      const auto programFunction = createProgramFunction( yylhs.location, yystack_[1].value.as < Initializers::Ptr > () );

      // apply the name of the program declaration to the initializer functions
      const auto initializers = programFunction->initially()->initializers();
      for( auto& initializer : *initializers )
      {
          initializer->updateRule()->function()->setIdentifier(
              asIdentifierPath( programFunction->identifier() ) );
      }

      yylhs.value.as < InitDefinition::Ptr > ()->setProgramFunction( programFunction );
  }
#line 2382 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 19:
#line 590 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2390 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 20:
#line 598 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2399 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 21:
#line 603 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2409 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 22:
#line 609 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 2417 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 23:
#line 617 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2427 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 24:
#line 623 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2436 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 25:
#line 628 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
  }
#line 2447 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 26:
#line 635 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 27:
#line 641 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 28:
#line 645 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 29:
#line 653 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < FunctionDefinition::Ptr > () = Ast::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      const auto initially = yylhs.value.as < FunctionDefinition::Ptr > ()->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->updateRule()->function()->setIdentifier( asIdentifierPath( yystack_[6].value.as < Identifier::Ptr > () ) );
      }
  }
#line 2488 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 30:
#line 668 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 2496 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 31:
#line 672 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 2506 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 32:
#line 678 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 2514 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 33:
#line 686 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2525 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 34:
#line 693 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2535 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 35:
#line 703 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2543 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 36:
#line 711 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < InvariantDefinition::Ptr > () = Ast::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2551 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 37:
#line 723 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 38:
#line 729 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 2571 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 39:
#line 739 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 2579 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 40:
#line 743 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 2587 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 41:
#line 747 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 2595 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 42:
#line 751 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 2603 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 43:
#line 755 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 2611 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 44:
#line 759 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 2619 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 45:
#line 763 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 2627 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 46:
#line 767 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 2635 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 47:
#line 771 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 2643 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 48:
#line 775 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 2651 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 49:
#line 779 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 2659 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 50:
#line 783 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 2667 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 51:
#line 791 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2675 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 52:
#line 799 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2683 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 53:
#line 803 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2691 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 54:
#line 811 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2699 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 55:
#line 815 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 2707 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 56:
#line 823 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 2717 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 57:
#line 829 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 2727 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 58:
#line 839 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2735 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 59:
#line 843 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2743 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 60:
#line 847 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2751 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 61:
#line 855 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2759 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 62:
#line 863 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2767 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 63:
#line 867 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2775 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 64:
#line 875 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2783 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 65:
#line 883 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2791 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 66:
#line 891 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2799 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 67:
#line 895 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2807 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 68:
#line 899 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2816 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 69:
#line 904 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2825 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 70:
#line 913 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2833 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 71:
#line 917 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2841 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 72:
#line 921 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2850 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 73:
#line 926 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2859 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 74:
#line 935 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2867 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 75:
#line 943 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 2875 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 76:
#line 951 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2883 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 77:
#line 963 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 2894 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 78:
#line 970 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 2904 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 79:
#line 980 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 2912 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 80:
#line 984 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 2920 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 81:
#line 988 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 2928 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 82:
#line 992 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 2936 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 83:
#line 996 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 2944 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 84:
#line 1000 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 2952 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 85:
#line 1004 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 2960 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 86:
#line 1008 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 2968 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 87:
#line 1012 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 2976 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 88:
#line 1020 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< Ast::EmbracedExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2984 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 89:
#line 1024 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 2992 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 90:
#line 1028 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 3000 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 91:
#line 1032 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 3008 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 92:
#line 1036 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 3016 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 93:
#line 1040 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3024 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 94:
#line 1044 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 3032 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 95:
#line 1056 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3040 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 96:
#line 1060 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 3048 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 97:
#line 1064 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 3056 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 98:
#line 1068 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 3064 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 99:
#line 1072 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 3072 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 100:
#line 1076 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 3080 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 101:
#line 1080 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 3088 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 102:
#line 1084 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 3096 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 103:
#line 1088 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 3104 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 104:
#line 1092 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 3112 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 105:
#line 1096 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 3120 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 106:
#line 1100 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 3128 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 107:
#line 1104 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 3136 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 108:
#line 1108 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 3144 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 109:
#line 1112 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 3152 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 110:
#line 1116 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3160 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 111:
#line 1120 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3168 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 112:
#line 1124 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 3176 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 113:
#line 1132 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 3184 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 114:
#line 1136 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 3192 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 115:
#line 1140 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 3200 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 116:
#line 1148 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > (), arguments );
  }
#line 3209 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 117:
#line 1153 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), arguments );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3220 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 118:
#line 1160 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3230 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 119:
#line 1166 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 3238 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 120:
#line 1174 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 3247 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 121:
#line 1179 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3258 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 122:
#line 1186 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3268 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 123:
#line 1192 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 3276 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 124:
#line 1200 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 3284 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 125:
#line 1208 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3295 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 126:
#line 1215 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3305 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 127:
#line 1221 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 3313 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 128:
#line 1229 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3321 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 129:
#line 1237 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3329 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 130:
#line 1245 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3337 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 131:
#line 1253 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3345 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 132:
#line 1261 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3353 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 133:
#line 1269 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3361 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 134:
#line 1277 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3369 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 135:
#line 1290 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 3377 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 136:
#line 1294 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3385 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 137:
#line 1298 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3393 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 138:
#line 1302 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3401 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 139:
#line 1306 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3409 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 140:
#line 1310 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3417 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 141:
#line 1314 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3425 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 142:
#line 1318 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 3433 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 143:
#line 1322 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 3441 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 144:
#line 1326 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 3449 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 145:
#line 1330 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 3457 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 146:
#line 1334 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 3465 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 147:
#line 1342 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3474 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 148:
#line 1351 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3484 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 149:
#line 1357 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3494 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 150:
#line 1367 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3502 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 151:
#line 1375 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3510 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 152:
#line 1383 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3518 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 153:
#line 1391 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3526 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 154:
#line 1395 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3534 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 155:
#line 1403 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3542 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 156:
#line 1411 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3550 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 157:
#line 1419 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3561 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 158:
#line 1426 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3571 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 159:
#line 1432 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 3579 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 160:
#line 1440 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3589 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 161:
#line 1449 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3602 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 162:
#line 1460 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3612 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 163:
#line 1469 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 3623 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 164:
#line 1476 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 3633 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 165:
#line 1485 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3641 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 166:
#line 1497 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3652 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 167:
#line 1504 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3662 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 168:
#line 1513 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 3670 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 169:
#line 1517 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 3678 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 170:
#line 1521 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 3686 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 171:
#line 1525 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 3694 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 172:
#line 1529 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 3702 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 173:
#line 1533 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 3710 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 174:
#line 1541 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3718 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 175:
#line 1549 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = Ast::make< TupleType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), subTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3729 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 176:
#line 1560 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = Ast::make< RecordType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3740 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 177:
#line 1571 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3748 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 178:
#line 1579 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3756 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 179:
#line 1587 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3764 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 180:
#line 1599 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3775 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 181:
#line 1606 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3785 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 182:
#line 1616 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 3793 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 183:
#line 1620 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 3801 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 184:
#line 1628 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 3812 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 185:
#line 1635 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 3822 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 186:
#line 1649 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3830 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 187:
#line 1653 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 3838 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 188:
#line 1661 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3846 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 189:
#line 1665 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto initializers = Ast::make< Initializers >( yylhs.location );
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
#line 3855 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 190:
#line 1674 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto initializers = yystack_[2].value.as < Initializers::Ptr > ();
      yystack_[0].value.as < Initializer::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 3866 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 191:
#line 1681 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto initializers = Ast::make< Initializers >( yylhs.location );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 3876 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 192:
#line 1691 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3887 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 193:
#line 1698 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), arguments, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3899 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 194:
#line 1706 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto lbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto rbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, lbToken, arguments, rbToken, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3912 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 195:
#line 1723 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 3920 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 196:
#line 1727 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 3929 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 197:
#line 1736 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < Ast::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 3940 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 198:
#line 1743 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3948 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 199:
#line 1755 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 3956 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 200:
#line 1759 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 3965 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 201:
#line 1768 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 3976 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 202:
#line 1775 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 3986 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 203:
#line 1785 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3997 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 204:
#line 1792 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4007 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 205:
#line 1802 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variable = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4016 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 206:
#line 1811 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4026 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 207:
#line 1817 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4034 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 208:
#line 1825 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4044 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 209:
#line 1831 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4052 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 210:
#line 1843 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4063 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 211:
#line 1850 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4073 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 212:
#line 1859 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4081 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 213:
#line 1871 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4091 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 214:
#line 1877 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4101 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 215:
#line 1886 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4112 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 216:
#line 1893 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4123 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 217:
#line 1900 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 4131 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 218:
#line 1907 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4139 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 219:
#line 1914 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4147 "GrammarParser.cpp" // lalr1.cc:919
    break;


#line 4151 "GrammarParser.cpp" // lalr1.cc:919
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
      YY_STACK_PRINT ();

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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
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

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
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

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

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
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

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
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short Parser::yypact_ninf_ = -148;

  const short Parser::yytable_ninf_ = -182;

  const short
  Parser::yypact_[] =
  {
      14,  -148,     4,    44,   138,    16,  -148,   -23,  -148,  -148,
    1805,   -14,    34,  -148,  -148,    -7,   -12,   -12,   -12,   -12,
     -12,   -12,   207,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,   173,  -148,  -148,  -148,    -3,    -3,    -3,  1805,
      -3,  -148,  -148,  -148,  1805,  1883,  1883,  1332,  1076,  1883,
     -12,  -148,  -148,  -148,  -148,  -148,  -148,  2561,    -9,  -148,
      12,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,    59,  -148,  -148,  1869,
      46,   -21,    18,    26,    63,    68,    81,  -148,  -148,   106,
    -148,  -148,   148,     9,  -148,    -3,    20,  -148,    22,  2136,
      29,  -148,  -148,  -148,   125,   146,  2316,    94,  -148,   152,
     156,  -148,    10,  2351,   -24,    46,  1805,  1805,  1805,  1805,
    1805,  1805,  1805,  1805,  1805,  1805,  1805,  1805,  1805,  1805,
    1805,  1805,  1805,     1,     3,  1140,  1204,   -12,  1332,  2561,
     142,    19,  -148,     8,     1,    25,  1677,    13,     1,     1,
    1805,     1,     1,  1805,  1805,    -3,  -148,  1805,    -3,  1805,
    1805,  1805,  -148,  1805,  -148,  -148,   -12,  1805,  -148,  -148,
    1805,  1805,  -148,   506,  2631,   621,  2596,   189,   189,   281,
     202,   202,   155,   155,   155,  -148,  2596,   281,   202,   202,
       1,  -148,  -148,  -148,  -148,  -148,  -148,  -148,    51,  -148,
     174,   172,  -148,   108,  2561,   176,  -148,   109,  -148,  2386,
    1805,  -148,  1869,   177,   127,   106,  -148,  -148,    -3,   186,
      17,   741,   810,  -148,    -3,    -3,    -3,  1677,  1805,  1805,
    1805,   879,   948,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,   166,    -6,   165,   192,
     141,   191,  -148,  2561,  -148,   180,   199,  -148,  2561,  2561,
    -148,  2246,  -148,  1974,   434,  2281,  2421,  -148,   152,  2561,
    2561,  2456,   187,  -148,   106,   210,  -148,     1,  1805,  1268,
    -148,  -148,  -148,  -148,   201,  2561,  -148,   203,   204,    -3,
    -148,  1805,  -148,  -148,   118,  -148,    -3,   242,  1401,  -148,
     243,  1470,    30,    31,    35,  -148,  2175,  2211,  2015,   218,
    1539,   198,  1608,  1805,    23,    28,  1677,     1,     1,  1805,
    1805,  1805,  1805,  -148,  -148,     1,   -12,   137,   130,   213,
    -148,   227,  -148,   145,  1805,     1,     1,  -148,  2561,  -148,
      17,  -148,  -148,  -148,  -148,  -148,  -148,  1677,  1805,  1805,
    1677,   231,  1677,  -148,  -148,  -148,  -148,  2561,  1677,     1,
    1677,     1,  -148,  -148,   265,  2561,  2561,  2561,  2561,   235,
     238,     1,  -148,     1,  -148,  -148,  2561,   241,   244,  -148,
    -148,  1933,  2056,   261,  1012,  -148,  -148,   245,  -148,   247,
     248,   277,  -148,  -148,  -148,   234,  1805,  1805,  1677,  1805,
    1677,  1677,   250,   251,   254,  1741,  -148,  2491,  1677,  1677,
    1805,   252,  -148,  -148,  2561,  2561,  -148,  2097,  -148,  -148,
    -148,  1677,  1677,  -148,  -148,  1677,  -148,  -148,  2526,  1869,
    1677,  -148,  -148,  -148,  -148,   144,  -148,  -148
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   214,     0,   196,   195,
     218,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     6,     8,    10,    11,    12,    13,    14,
      15,    16,     0,     3,   213,   217,     0,     0,     0,     0,
       0,   147,   149,   148,     0,     0,     0,     0,     0,     0,
       0,   153,   154,   150,   151,   152,   155,   219,    79,    81,
      90,   113,   114,    91,   115,    80,    82,    83,    84,    85,
      86,    87,    92,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   198,   116,   215,   216,     0,
      17,     0,     0,     0,     0,     0,     0,     5,     7,   200,
     207,   199,     0,     0,   211,     0,     0,   202,     0,     0,
       0,   112,    93,    94,     0,     0,    78,     0,   164,   198,
       0,   157,     0,    78,     0,   156,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   192,
     145,     0,   191,     0,     0,     0,     0,     0,     0,     0,
       0,   183,     0,     0,     0,     0,   206,     0,     0,     0,
       0,     0,    89,     0,    88,   162,     0,     0,   159,   158,
       0,     0,   134,   109,   107,   108,   111,    95,    96,   102,
     103,   104,    97,    98,    99,   100,   110,   101,   105,   106,
       0,   128,   168,   169,   170,   171,   172,   173,   174,   124,
     120,     0,   125,     0,    78,     0,   117,     0,   197,    78,
       0,    18,     0,     0,     0,     0,   209,   185,     0,     0,
       0,     0,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,     0,    75,   113,     0,
       0,     0,    35,    36,   181,   182,     0,   205,   212,   129,
     210,     0,   201,     0,     0,     0,    77,   163,     0,   165,
      77,     0,     0,   167,   198,     0,   204,   183,     0,     0,
     127,   126,   119,   118,    88,   194,   190,     0,     0,     0,
     208,     0,    32,    34,     0,    30,     0,     0,     0,    38,
       0,     0,     0,     0,     0,    65,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   161,   160,     0,     0,     0,   167,     0,
     179,     0,   121,     0,     0,     0,     0,   184,    20,    19,
       0,    31,    73,    71,    37,    69,    67,     0,     0,     0,
       0,     0,     0,    68,    66,    72,    70,    74,     0,     0,
       0,     0,    24,   180,   187,   132,   131,   130,   133,   166,
     203,     0,   177,     0,   123,   122,   193,     0,     0,    33,
      61,     0,     0,    52,     0,    76,    27,     0,    25,     0,
       0,   189,   175,   176,   166,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    57,     0,     0,     0,
       0,     0,    29,   178,    22,    21,    62,     0,    64,    53,
      55,     0,     0,    54,    56,     0,    28,    26,     0,     0,
       0,    58,    59,    60,   186,     0,    63,   188
  };

  const short
  Parser::yypgoto_[] =
  {
    -148,  -148,  -148,  -148,   272,   263,  -148,  -148,  -148,  -148,
    -148,   -43,  -148,  -148,  -148,  -141,   301,  -148,  -148,  -148,
    -148,  -107,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,   -35,   -10,     6,  -148,  -135,   222,  -148,  -148,  -148,
    -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,  -148,
     167,  -148,  -148,  -148,  -148,  -148,  -148,  -148,   -88,  -148,
    -148,   133,    36,   400,  -148,  -148,  -148,  -148,  -148,  -148,
    -148,    40,   158,  -148,  -148,  -127,    96,   371,    99,   211,
     -36,  -148,  -147,   -28,    32,    95,   168,    11,    -2,  -148,
    -148
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    22,    23,    24,    25,    26,    27,    28,
      29,   303,   304,    30,    31,   308,   309,   244,   245,   246,
     415,   416,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   115,   149,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
     117,   118,   282,   201,   202,   203,   204,   205,   206,   207,
     265,   266,   224,   401,   422,   151,   152,    85,    86,   100,
     106,   285,   101,   107,   227,   103,   104,   105,     6,    11,
      12
  };

  const short
  Parser::yytable_[] =
  {
      57,   150,   108,    34,   110,     7,   226,     8,   102,   223,
     226,     5,     8,   122,   259,    32,     8,     1,   302,    33,
       8,   257,     8,     8,   143,   153,    35,     8,   164,   109,
      34,   182,     8,    32,   111,    87,     8,   116,   123,   167,
     145,   169,   144,    89,    13,     2,   154,   200,   171,   357,
     358,   112,   113,   286,   359,   124,     2,   144,   145,   179,
     -90,     2,     2,   155,     2,     2,   165,   180,   368,     9,
     221,   156,   157,   370,     9,   230,   222,   168,     9,   168,
      53,   300,     9,    88,     9,     9,   168,   165,   168,     9,
     369,   311,   168,   158,     9,   371,   257,   257,     9,   147,
     320,   322,   257,    34,   147,   146,   257,   257,   159,   287,
     213,   217,   147,   160,    90,   288,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   161,   150,   214,   214,   102,   219,    14,
     272,   175,    15,    16,    17,    18,    19,    20,    21,   125,
     263,   176,   226,   268,   269,   291,   293,   271,   162,   273,
     274,   275,   256,   276,   228,   180,   180,   279,   228,   349,
     280,   281,   172,   257,   298,   350,   257,    15,    16,    17,
      18,    19,    20,    21,   299,   257,     2,   257,   325,   380,
    -181,   257,   385,   163,   381,   447,   382,  -181,   299,   313,
     314,   222,   180,   173,   177,   178,   102,    -2,    14,   220,
     295,    15,    16,    17,    18,    19,    20,    21,   138,   290,
     289,     2,   257,   292,   297,   257,    34,   257,   316,   317,
     318,   301,   144,   257,   323,   257,   326,   256,   256,   324,
     327,   306,   208,   256,   335,   130,   131,   256,   256,   135,
     136,   137,   138,   208,   343,     2,   352,   208,   208,   355,
     208,   208,   135,   136,   137,   138,   328,   336,   344,   363,
     345,   346,   365,   257,   384,   257,   257,   400,   340,   214,
     383,   394,   402,   257,   257,   403,   406,   411,   421,   407,
     418,   348,   419,   423,    97,    98,   257,   257,   420,   208,
     257,   430,   439,   431,    34,   257,   432,   389,   434,   277,
     228,   209,   445,   367,   256,   260,   166,   256,   296,   375,
     376,   377,   378,   337,   130,   131,   256,   339,   256,   312,
       0,   347,   256,   270,   386,     0,     0,     0,     0,   133,
     134,   135,   136,   137,   138,     0,     0,     0,   391,   392,
       0,   150,   141,   142,     0,     0,     0,     0,     0,     0,
       0,   306,     0,   256,     0,     0,   256,     0,   256,     0,
       0,     0,     0,    10,   256,     0,   256,     0,   258,     0,
       0,     0,     0,     0,   417,     0,   208,    91,    92,    93,
      94,    95,    96,     0,     0,     0,   424,   425,     0,   427,
       0,     0,     0,     0,     0,   417,     0,    99,    99,    99,
     438,    99,     0,     0,   256,     0,   256,   256,   119,     0,
       0,     0,     0,     0,   256,   256,   208,   208,     0,     0,
       0,     0,     0,     0,   208,     0,     0,   256,   256,     0,
       0,   256,     0,     0,   208,   208,   256,     0,     0,     0,
       0,     0,     0,   258,   258,     0,     0,   243,     0,   258,
     331,     0,     0,   258,   258,     0,     0,     0,   208,     0,
     208,     0,   126,   127,   128,   129,    99,   130,   131,   132,
     208,     0,   208,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   133,   134,   135,   136,   137,   138,     0,     0,
       0,     0,   139,     0,   140,   141,   142,     0,     0,     0,
       0,     0,     0,     0,     0,   210,     0,     0,   218,   119,
       0,     0,     0,     0,   225,     0,     0,     0,   225,     0,
     258,     0,     0,   258,     0,     0,    99,     0,   315,    99,
       0,     0,   258,     0,   258,     0,     0,   278,   258,   130,
     131,   132,     0,     0,   229,     0,     0,     0,   261,   262,
       0,   264,   267,     0,   133,   134,   135,   136,   137,   138,
       0,   284,     0,     0,     0,     0,   140,   141,   142,   258,
       0,     0,   258,     0,   258,     0,     0,     0,     0,     0,
     258,     0,   258,     0,     0,     0,     0,     0,     0,   225,
     283,   305,     0,     0,     0,    99,    99,    99,     0,   354,
       0,     0,   354,     0,     0,     0,     0,     0,     0,     0,
       0,   354,     0,   354,     0,     0,     0,   372,     0,     0,
     258,     0,   258,   258,     0,     0,     0,     0,     0,     0,
     258,   258,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   258,   258,     0,     0,   258,   390,   126,
       0,   393,   258,   395,   130,   131,   132,     0,     0,   396,
     225,   398,     0,     0,     0,     0,     0,   351,     0,   133,
     134,   135,   136,   137,   138,     0,     0,   338,     0,     0,
       0,   140,   141,   142,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   225,     0,   426,
       0,   428,   429,     0,     0,     0,     0,     0,     0,   436,
     437,   305,     0,     0,     0,     0,     0,   373,   374,     0,
       0,     0,   441,   442,     0,   379,   443,     0,     0,     0,
       0,   446,   307,     0,     0,   387,   388,     0,     0,     0,
       0,     0,     0,     0,   231,     0,   232,     0,   233,   234,
       8,   235,   236,   237,     0,   238,     0,     0,   239,   397,
       0,   399,     0,     0,     0,   240,    41,    42,    43,     0,
       0,   404,     0,   405,    45,    46,     0,    47,     0,    48,
       0,   241,     0,     0,     0,     0,     0,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   310,     0,     0,   242,     0,    51,    52,    53,    54,
      55,    56,     9,   231,     0,   232,     0,   233,   234,     8,
     235,   236,   237,     0,   238,     0,     0,   239,     0,     0,
       0,     0,     0,     0,   240,    41,    42,    43,     0,     0,
       0,     0,     0,    45,    46,     0,    47,     0,    48,     0,
     241,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     319,     0,     0,   242,     0,    51,    52,    53,    54,    55,
      56,     9,   231,     0,   232,     0,   233,   234,     8,   235,
     236,   237,     0,   238,     0,     0,   239,     0,     0,     0,
       0,     0,     0,   240,    41,    42,    43,     0,     0,     0,
       0,     0,    45,    46,     0,    47,     0,    48,     0,   241,
       0,     0,     0,     0,     0,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   321,
       0,     0,   242,     0,    51,    52,    53,    54,    55,    56,
       9,   231,     0,   232,     0,   233,   234,     8,   235,   236,
     237,     0,   238,     0,     0,   239,     0,     0,     0,     0,
       0,     0,   240,    41,    42,    43,     0,     0,     0,     0,
       0,    45,    46,     0,    47,     0,    48,     0,   241,     0,
       0,     0,     0,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,   412,     0,     0,     0,     0,     0,     0,
       0,   242,     0,    51,    52,    53,    54,    55,    56,     9,
      36,     8,    37,    38,     0,     0,    39,     0,     0,     0,
       0,   413,     0,    40,     0,     0,     0,    41,    42,    43,
       0,     0,     0,     0,    44,    45,    46,     0,    47,     0,
      48,     0,     0,     0,     0,     0,   414,    49,    50,     0,
       0,     0,     0,     0,     0,     0,     0,   120,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    53,
      54,    55,    56,     9,    36,     8,    37,    38,     0,     0,
      39,     0,     0,     0,     0,     0,     0,    40,     0,     0,
       0,    41,    42,    43,     0,     0,     0,     0,    44,    45,
      46,     0,    47,     0,    48,   121,     0,     0,     0,     0,
       0,    49,    50,     0,     0,     0,     0,     0,     0,     0,
       0,   211,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,    52,    53,    54,    55,    56,     9,    36,     8,
      37,    38,     0,     0,    39,     0,     0,     0,     0,     0,
       0,    40,     0,     0,     0,    41,    42,    43,     0,     0,
       0,     0,    44,    45,    46,     0,    47,   212,    48,     0,
       0,     0,     0,     0,     0,    49,    50,     0,     0,     0,
       0,     0,     0,     0,     0,   215,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,    52,    53,    54,    55,
      56,     9,    36,     8,    37,    38,     0,     0,    39,     0,
       0,     0,     0,     0,     0,    40,     0,     0,     0,    41,
      42,    43,     0,     0,     0,     0,    44,    45,    46,     0,
      47,   216,    48,     0,     0,     0,     0,     0,     0,    49,
      50,     0,     0,     0,     0,     0,     0,     0,     0,   341,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    51,
      52,    53,    54,    55,    56,     9,    36,     8,    37,    38,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    40,
       0,     0,     0,    41,    42,    43,     0,     0,     0,     0,
      44,    45,    46,     0,    47,   342,    48,     0,     0,     0,
       0,     0,     0,    49,    50,     0,     0,     0,     0,     0,
       0,     0,     0,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,    52,    53,    54,    55,    56,     9,
      36,     8,    37,    38,     0,     0,    39,     0,     0,     0,
       0,     0,     0,    40,     0,     0,     0,    41,    42,    43,
       0,     0,     0,     0,    44,    45,    46,     0,    47,     0,
      48,     0,     0,     0,     0,     0,     0,    49,    50,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,    52,    53,
      54,    55,    56,     9,   231,   353,   232,     0,   233,   234,
       8,   235,   236,   237,     0,   238,     0,     0,   239,     0,
       0,     0,     0,     0,     0,   240,    41,    42,    43,     0,
       0,     0,     0,     0,    45,    46,     0,    47,     0,    48,
       0,   241,     0,     0,     0,     0,     0,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   242,     0,    51,    52,    53,    54,
      55,    56,     9,   231,     0,   232,   356,   233,   234,     8,
     235,   236,   237,     0,   238,     0,     0,   239,     0,     0,
       0,     0,     0,     0,   240,    41,    42,    43,     0,     0,
       0,     0,     0,    45,    46,     0,    47,     0,    48,     0,
     241,     0,     0,     0,     0,     0,    50,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   242,     0,    51,    52,    53,    54,    55,
      56,     9,   231,     0,   232,     0,   233,   234,     8,   235,
     236,   237,     0,   238,     0,     0,   239,     0,     0,     0,
       0,     0,     0,   240,    41,    42,    43,     0,     0,     0,
       0,     0,    45,    46,     0,    47,     0,    48,     0,   241,
     364,     0,     0,     0,     0,    50,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   242,     0,    51,    52,    53,    54,    55,    56,
       9,   231,     0,   232,     0,   233,   234,     8,   235,   236,
     237,     0,   238,     0,     0,   239,     0,     0,     0,     0,
       0,     0,   240,    41,    42,    43,     0,     0,     0,     0,
       0,    45,    46,     0,    47,     0,    48,     0,   241,     0,
       0,     0,     0,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   242,   366,    51,    52,    53,    54,    55,    56,     9,
     231,     0,   232,     0,   233,   234,     8,   235,   236,   237,
       0,   238,     0,     0,   239,     0,     0,     0,     0,     0,
       0,   240,    41,    42,    43,     0,     0,     0,     0,     0,
      45,    46,     0,    47,     0,    48,     0,   241,     0,     0,
       0,     0,     0,    50,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     242,     0,    51,    52,    53,    54,    55,    56,     9,    36,
       8,    37,    38,     0,     0,    39,     0,     0,     0,     0,
     413,     0,    40,     0,     0,     0,    41,    42,    43,     0,
       0,     0,     0,    44,    45,    46,     0,    47,     0,    48,
       0,     0,   433,     0,     0,   414,    49,    50,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,    52,    53,    54,
      55,    56,     9,    36,     8,    37,    38,     0,     0,    39,
       0,     0,     0,     0,     0,     0,    40,     0,     0,     0,
      41,    42,    43,     0,     0,     0,     0,    44,    45,    46,
       0,    47,     0,    48,     0,     0,     0,     0,     0,     0,
      49,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,    52,    53,    54,    55,    56,     9,    36,     8,    37,
      38,     0,     0,    39,     0,     0,     0,     0,     0,     0,
      40,     0,     8,     0,    41,    42,    43,     0,     0,     0,
       0,    44,    45,    46,     0,   148,     0,    48,    41,    42,
      43,     0,     0,     0,    49,    50,    45,    46,     0,    47,
       0,    48,     0,     0,     0,     0,     0,     0,     0,    50,
       0,     0,     0,     0,    51,    52,    53,    54,    55,    56,
       9,     0,     0,     0,     0,     0,   408,     0,    51,    52,
      53,    54,    55,    56,     9,   409,     0,     0,     0,     0,
       0,   126,   127,   128,   129,     0,   130,   131,   132,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   133,   134,   135,   136,   137,   138,   330,     0,     0,
       0,   139,     0,   140,   141,   142,     0,     0,     0,     0,
       0,     0,   126,   127,   128,   129,     0,   130,   131,   132,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   133,   134,   135,   136,   137,   138,   362,     0,
       0,     0,   139,     0,   140,   141,   142,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,     0,   130,   131,
     132,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,   410,
       0,     0,     0,   139,     0,   140,   141,   142,     0,     0,
       0,     0,     0,     0,   126,   127,   128,   129,     0,   130,
     131,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,   134,   135,   136,   137,   138,
     440,     0,     0,     0,   139,     0,   140,   141,   142,     0,
       0,     0,     0,     0,     0,   126,   127,   128,   129,     0,
     130,   131,   132,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   133,   134,   135,   136,   137,
     138,   170,     0,     0,     0,   139,     0,   140,   141,   142,
       0,     0,     0,     0,   126,   127,   128,   129,     0,   130,
     131,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,   134,   135,   136,   137,   138,
     360,     0,     0,     0,   139,     0,   140,   141,   142,     0,
       0,     0,     0,   126,   127,   128,   129,     0,   130,   131,
     132,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   133,   134,   135,   136,   137,   138,   361,
       0,     0,     0,   139,     0,   140,   141,   142,     0,   126,
     127,   128,   129,     0,   130,   131,   132,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   133,
     134,   135,   136,   137,   138,     0,   329,     0,     0,   139,
       0,   140,   141,   142,   126,   127,   128,   129,     0,   130,
     131,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,   134,   135,   136,   137,   138,
       0,     0,     0,   332,   139,     0,   140,   141,   142,   126,
     127,   128,   129,     0,   130,   131,   132,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   133,
     134,   135,   136,   137,   138,     0,     0,     0,     0,   139,
       0,   140,   141,   142,   126,   127,   128,   129,     0,   130,
     131,   132,     0,   174,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,   134,   135,   136,   137,   138,
       0,     0,     0,     0,   139,     0,   140,   141,   142,   126,
     127,   128,   129,     0,   130,   131,   132,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   133,
     134,   135,   136,   137,   138,     0,   181,     0,     0,   139,
       0,   140,   141,   142,   126,   127,   128,   129,     0,   130,
     131,   132,     0,   294,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,   134,   135,   136,   137,   138,
       0,     0,     0,     0,   139,     0,   140,   141,   142,   126,
     127,   128,   129,     0,   130,   131,   132,     0,   333,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   133,
     134,   135,   136,   137,   138,     0,     0,     0,     0,   139,
       0,   140,   141,   142,   126,   127,   128,   129,     0,   130,
     131,   132,     0,     0,     0,   334,     0,     0,     0,     0,
       0,     0,     0,     0,   133,   134,   135,   136,   137,   138,
       0,     0,     0,     0,   139,     0,   140,   141,   142,   126,
     127,   128,   129,     0,   130,   131,   132,     0,     0,     0,
       0,     0,     0,   435,     0,     0,     0,     0,     0,   133,
     134,   135,   136,   137,   138,     0,     0,     0,     0,   139,
       0,   140,   141,   142,   126,   127,   128,   129,     0,   130,
     131,   132,     0,     0,     0,     0,     0,   444,     0,     0,
       0,     0,     0,     0,   133,   134,   135,   136,   137,   138,
       0,     0,     0,     0,   139,     0,   140,   141,   142,   126,
     127,   128,   129,     0,   130,   131,   132,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   133,
     134,   135,   136,   137,   138,     0,     0,     0,     0,   139,
       0,   140,   141,   142,   126,   127,   128,     0,     0,   130,
     131,   132,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   133,   134,   135,   136,   137,   138,
       0,     0,     0,     0,     0,     0,   140,   141,   142,   126,
       0,   128,     0,     0,   130,   131,   132,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   133,
     134,   135,   136,   137,   138,     0,     0,     0,     0,     0,
       0,   140,   141,   142
  };

  const short
  Parser::yycheck_[] =
  {
      10,    89,    38,     5,    40,     1,   153,    19,    36,     1,
     157,     0,    19,    48,     1,     4,    19,     3,     1,     3,
      19,   156,    19,    19,    33,    46,    49,    19,    19,    39,
      32,    55,    19,    22,    44,    49,    19,    47,    48,    19,
      46,    19,    66,    50,     0,    48,    67,    46,    19,    19,
      19,    45,    46,   200,    19,    49,    48,    66,    46,    49,
      66,    48,    48,    45,    48,    48,    57,    57,    45,    81,
      51,    45,    46,    45,    81,    50,    57,    57,    81,    57,
      77,   228,    81,    49,    81,    81,    57,    57,    57,    81,
      67,   232,    57,    67,    81,    67,   231,   232,    81,    53,
     241,   242,   237,   105,    53,    46,   241,   242,    45,    58,
     145,   146,    53,    45,    15,    64,   126,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,    52,   222,   145,   146,   165,   148,     1,
     168,    47,     4,     5,     6,     7,     8,     9,    10,    50,
     160,    57,   299,   163,   164,    47,    47,   167,    52,   169,
     170,   171,   156,   173,   153,    57,    57,   177,   157,    51,
     180,   181,    47,   308,    47,    57,   311,     4,     5,     6,
       7,     8,     9,    10,    57,   320,    48,   322,    47,   336,
      60,   326,    47,    45,    57,    51,    59,    67,    57,   235,
     236,    57,    57,    57,    52,    49,   234,     0,     1,    67,
     220,     4,     5,     6,     7,     8,     9,    10,    63,    47,
      46,    48,   357,    47,    47,   360,   228,   362,   238,   239,
     240,    45,    66,   368,    69,   370,    45,   231,   232,    47,
      60,   230,   143,   237,    57,    43,    44,   241,   242,    60,
      61,    62,    63,   154,   289,    48,    14,   158,   159,    16,
     161,   162,    60,    61,    62,    63,    67,    57,    67,    51,
      67,    67,    74,   408,    47,   410,   411,    12,   288,   289,
      67,    50,    47,   418,   419,    47,    45,    26,    11,    45,
      45,   301,    45,    59,    22,    32,   431,   432,    50,   200,
     435,    51,    50,    52,   306,   440,    52,   350,   415,   176,
     299,   144,   439,   323,   308,   157,   105,   311,   222,   329,
     330,   331,   332,   287,    43,    44,   320,   287,   322,   234,
      -1,   299,   326,   165,   344,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,   358,   359,
      -1,   439,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   350,    -1,   357,    -1,    -1,   360,    -1,   362,    -1,
      -1,    -1,    -1,     2,   368,    -1,   370,    -1,   156,    -1,
      -1,    -1,    -1,    -1,   394,    -1,   287,    16,    17,    18,
      19,    20,    21,    -1,    -1,    -1,   406,   407,    -1,   409,
      -1,    -1,    -1,    -1,    -1,   415,    -1,    36,    37,    38,
     420,    40,    -1,    -1,   408,    -1,   410,   411,    47,    -1,
      -1,    -1,    -1,    -1,   418,   419,   327,   328,    -1,    -1,
      -1,    -1,    -1,    -1,   335,    -1,    -1,   431,   432,    -1,
      -1,   435,    -1,    -1,   345,   346,   440,    -1,    -1,    -1,
      -1,    -1,    -1,   231,   232,    -1,    -1,   156,    -1,   237,
      26,    -1,    -1,   241,   242,    -1,    -1,    -1,   369,    -1,
     371,    -1,    38,    39,    40,    41,   105,    43,    44,    45,
     381,    -1,   383,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    61,    62,    63,    -1,    -1,
      -1,    -1,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   144,    -1,    -1,   147,   148,
      -1,    -1,    -1,    -1,   153,    -1,    -1,    -1,   157,    -1,
     308,    -1,    -1,   311,    -1,    -1,   165,    -1,   237,   168,
      -1,    -1,   320,    -1,   322,    -1,    -1,   176,   326,    43,
      44,    45,    -1,    -1,   154,    -1,    -1,    -1,   158,   159,
      -1,   161,   162,    -1,    58,    59,    60,    61,    62,    63,
      -1,   200,    -1,    -1,    -1,    -1,    70,    71,    72,   357,
      -1,    -1,   360,    -1,   362,    -1,    -1,    -1,    -1,    -1,
     368,    -1,   370,    -1,    -1,    -1,    -1,    -1,    -1,   228,
     200,   230,    -1,    -1,    -1,   234,   235,   236,    -1,   308,
      -1,    -1,   311,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   320,    -1,   322,    -1,    -1,    -1,   326,    -1,    -1,
     408,    -1,   410,   411,    -1,    -1,    -1,    -1,    -1,    -1,
     418,   419,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   431,   432,    -1,    -1,   435,   357,    38,
      -1,   360,   440,   362,    43,    44,    45,    -1,    -1,   368,
     299,   370,    -1,    -1,    -1,    -1,    -1,   306,    -1,    58,
      59,    60,    61,    62,    63,    -1,    -1,   287,    -1,    -1,
      -1,    70,    71,    72,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   336,    -1,   408,
      -1,   410,   411,    -1,    -1,    -1,    -1,    -1,    -1,   418,
     419,   350,    -1,    -1,    -1,    -1,    -1,   327,   328,    -1,
      -1,    -1,   431,   432,    -1,   335,   435,    -1,    -1,    -1,
      -1,   440,     1,    -1,    -1,   345,   346,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    13,    -1,    15,    -1,    17,    18,
      19,    20,    21,    22,    -1,    24,    -1,    -1,    27,   369,
      -1,   371,    -1,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,   381,    -1,   383,    43,    44,    -1,    46,    -1,    48,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    13,    -1,    15,    -1,    17,    18,    19,
      20,    21,    22,    -1,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    46,    -1,    48,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    -1,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    13,    -1,    15,    -1,    17,    18,    19,    20,
      21,    22,    -1,    24,    -1,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    46,    -1,    48,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    13,    -1,    15,    -1,    17,    18,    19,    20,    21,
      22,    -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    46,    -1,    48,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    -1,    75,    76,    77,    78,    79,    80,    81,
      18,    19,    20,    21,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    29,    -1,    31,    -1,    -1,    -1,    35,    36,    37,
      -1,    -1,    -1,    -1,    42,    43,    44,    -1,    46,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    81,    18,    19,    20,    21,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,    43,
      44,    -1,    46,    -1,    48,    49,    -1,    -1,    -1,    -1,
      -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    80,    81,    18,    19,
      20,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    -1,    35,    36,    37,    -1,    -1,
      -1,    -1,    42,    43,    44,    -1,    46,    47,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      80,    81,    18,    19,    20,    21,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,    35,
      36,    37,    -1,    -1,    -1,    -1,    42,    43,    44,    -1,
      46,    47,    48,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    81,    18,    19,    20,    21,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,    43,    44,    -1,    46,    47,    48,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    81,
      18,    19,    20,    21,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    35,    36,    37,
      -1,    -1,    -1,    -1,    42,    43,    44,    -1,    46,    -1,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    81,    13,    14,    15,    -1,    17,    18,
      19,    20,    21,    22,    -1,    24,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    46,    -1,    48,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    13,    -1,    15,    16,    17,    18,    19,
      20,    21,    22,    -1,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    46,    -1,    48,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    13,    -1,    15,    -1,    17,    18,    19,    20,
      21,    22,    -1,    24,    -1,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    46,    -1,    48,    -1,    50,
      51,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    13,    -1,    15,    -1,    17,    18,    19,    20,    21,
      22,    -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,    -1,
      -1,    43,    44,    -1,    46,    -1,    48,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      13,    -1,    15,    -1,    17,    18,    19,    20,    21,    22,
      -1,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    -1,    -1,    -1,    -1,    -1,
      43,    44,    -1,    46,    -1,    48,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      73,    -1,    75,    76,    77,    78,    79,    80,    81,    18,
      19,    20,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      29,    -1,    31,    -1,    -1,    -1,    35,    36,    37,    -1,
      -1,    -1,    -1,    42,    43,    44,    -1,    46,    -1,    48,
      -1,    -1,    51,    -1,    -1,    54,    55,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    81,    18,    19,    20,    21,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,    -1,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,    43,    44,
      -1,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    80,    81,    18,    19,    20,
      21,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    19,    -1,    35,    36,    37,    -1,    -1,    -1,
      -1,    42,    43,    44,    -1,    46,    -1,    48,    35,    36,
      37,    -1,    -1,    -1,    55,    56,    43,    44,    -1,    46,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      81,    -1,    -1,    -1,    -1,    -1,    23,    -1,    75,    76,
      77,    78,    79,    80,    81,    32,    -1,    -1,    -1,    -1,
      -1,    38,    39,    40,    41,    -1,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    58,    59,    60,    61,    62,    63,    23,    -1,    -1,
      -1,    68,    -1,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    38,    39,    40,    41,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    61,    62,    63,    23,    -1,
      -1,    -1,    68,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    23,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      23,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,    25,    -1,    -1,    -1,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      25,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    28,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,    38,
      39,    40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    62,    63,    -1,    30,    -1,    -1,    68,
      -1,    70,    71,    72,    38,    39,    40,    41,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    32,    68,    -1,    70,    71,    72,    38,
      39,    40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,
      -1,    70,    71,    72,    38,    39,    40,    41,    -1,    43,
      44,    45,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,
      39,    40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    62,    63,    -1,    65,    -1,    -1,    68,
      -1,    70,    71,    72,    38,    39,    40,    41,    -1,    43,
      44,    45,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,
      39,    40,    41,    -1,    43,    44,    45,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,
      -1,    70,    71,    72,    38,    39,    40,    41,    -1,    43,
      44,    45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,
      39,    40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,
      -1,    70,    71,    72,    38,    39,    40,    41,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,
      39,    40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,
      -1,    70,    71,    72,    38,    39,    40,    -1,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    38,
      -1,    40,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,
      59,    60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    48,    88,    89,   174,   175,     1,    19,    81,
     164,   176,   177,     0,     1,     4,     5,     6,     7,     8,
       9,    10,    90,    91,    92,    93,    94,    95,    96,    97,
     100,   101,   174,     3,   175,    49,    18,    20,    21,    24,
      31,    35,    36,    37,    42,    43,    44,    46,    48,    55,
      56,    75,    76,    77,    78,    79,    80,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   164,   165,    49,    49,    50,
     165,   164,   164,   164,   164,   164,   164,    91,    92,   164,
     166,   169,   170,   172,   173,   174,   167,   170,   167,   119,
     167,   119,   120,   120,     1,   118,   119,   147,   148,   164,
       1,    49,   118,   119,   120,   165,    38,    39,    40,    41,
      43,    44,    45,    58,    59,    60,    61,    62,    63,    68,
      70,    71,    72,    33,    66,    46,    46,    53,    46,   119,
     145,   162,   163,    46,    67,    45,    45,    46,    67,    45,
      45,    52,    52,    45,    19,    57,   166,    19,    57,    19,
      25,    19,    47,    57,    47,    47,    57,    52,    49,    49,
      57,    65,    55,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
      46,   150,   151,   152,   153,   154,   155,   156,   165,   137,
     164,     1,    47,   118,   119,     1,    47,   118,   164,   119,
      67,    51,    57,     1,   159,   164,   169,   171,   174,   150,
      50,    13,    15,    17,    18,    20,    21,    22,    24,    27,
      34,    50,    73,   103,   104,   105,   106,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   120,   122,   123,     1,
     159,   150,   150,   119,   150,   157,   158,   150,   119,   119,
     173,   119,   170,   119,   119,   119,   119,   148,   164,   119,
     119,   119,   149,   150,   164,   168,   169,    58,    64,    46,
      47,    47,    47,    47,    47,   119,   163,    47,    47,    57,
     169,    45,     1,    98,    99,   164,   174,     1,   102,   103,
       1,   102,   172,   167,   167,   103,   119,   119,   119,     1,
     102,     1,   102,    69,    47,    47,    45,    60,    67,    30,
      23,    26,    32,    47,    49,    57,    57,   149,   150,   158,
     119,     1,    47,   118,    67,    67,    67,   171,   119,    51,
      57,   164,    14,    14,   103,    16,    16,    19,    19,    19,
      25,    28,    23,    51,    51,    74,    74,   119,    45,    67,
      45,    67,   103,   150,   150,   119,   119,   119,   119,   150,
     169,    57,    59,    67,    47,    47,   119,   150,   150,    98,
     103,   119,   119,   103,    50,   103,   103,   150,   103,   150,
      12,   160,    47,    47,   150,   150,    45,    45,    23,    32,
      23,    26,     1,    29,    54,   107,   108,   119,    45,    45,
      50,    11,   161,    59,   119,   119,   103,   119,   103,   103,
      51,    52,    52,    51,   108,    52,   103,   103,   119,    50,
      23,   103,   103,   103,    51,   162,   103,    51
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    87,    88,    89,    89,    90,    90,    91,    91,    91,
      92,    92,    92,    92,    92,    92,    92,    93,    93,    94,
      95,    95,    95,    96,    96,    96,    96,    96,    96,    97,
      98,    98,    98,    99,    99,   100,   101,   102,   102,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   103,   103,
     103,   104,   105,   105,   106,   106,   107,   107,   108,   108,
     108,   109,   110,   110,   111,   112,   113,   113,   113,   113,
     114,   114,   114,   114,   115,   116,   117,   118,   118,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   120,   120,
     120,   120,   120,   120,   120,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   122,   122,   122,   123,   123,   123,   123,
     124,   124,   124,   124,   125,   126,   126,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   135,   136,   136,
     137,   138,   139,   140,   140,   141,   142,   143,   143,   143,
     144,   145,   146,   147,   147,   148,   149,   149,   150,   150,
     150,   150,   150,   150,   151,   152,   153,   154,   155,   156,
     157,   157,   158,   158,   159,   159,   160,   160,   161,   161,
     162,   162,   163,   163,   163,   164,   164,   165,   165,   166,
     166,   167,   167,   168,   168,   169,   170,   170,   171,   171,
     172,   172,   173,   174,   174,   175,   175,   175,   176,   177
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     6,
       6,     9,     9,     4,     6,     7,     9,     7,     9,     8,
       1,     2,     1,     3,     1,     4,     4,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     4,     6,     6,     6,     2,     1,     3,     3,
       3,     4,     6,     8,     6,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     1,     4,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       1,     1,     1,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     1,     1,     1,     1,     3,     4,     4,
       3,     5,     6,     6,     3,     3,     4,     4,     3,     4,
       6,     6,     6,     6,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     3,     3,
       5,     5,     3,     3,     1,     3,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     5,     5,     4,     6,     3,
       3,     1,     1,     0,     3,     1,     4,     0,     4,     0,
       3,     1,     1,     5,     3,     1,     1,     3,     1,     1,
       1,     3,     1,     3,     1,     3,     2,     1,     2,     1,
       3,     1,     3,     2,     1,     3,     3,     3,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"using\"",
  "\"invariant\"", "\"function\"", "\"initially\"", "\"defined\"",
  "\"seq\"", "\"endseq\"", "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"",
  "\"in\"", "\"forall\"", "\"choose\"", "\"iterate\"", "\"do\"", "\"if\"",
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
  "InvariantDefinition", "Rules", "Rule", "SkipRule", "ConditionalRule",
  "CaseRule", "CaseLabels", "CaseLabel", "LetRule", "ForallRule",
  "ChooseRule", "IterateRule", "BlockRule", "SequenceRule", "UpdateRule",
  "CallRule", "WhileRule", "Terms", "Term", "SimpleOrClaspedTerm",
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
  "VariableBindings", "VariableBinding", "Attributes", "Attribute",
  "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short
  Parser::yyrline_[] =
  {
       0,   450,   450,   460,   466,   474,   480,   490,   496,   500,
     508,   512,   516,   520,   524,   528,   532,   540,   569,   589,
     597,   602,   608,   616,   622,   627,   634,   640,   644,   652,
     667,   671,   677,   685,   692,   702,   710,   722,   728,   738,
     742,   746,   750,   754,   758,   762,   766,   770,   774,   778,
     782,   790,   798,   802,   810,   814,   822,   828,   838,   842,
     846,   854,   862,   866,   874,   882,   890,   894,   898,   903,
     912,   916,   920,   925,   934,   942,   950,   962,   969,   979,
     983,   987,   991,   995,   999,  1003,  1007,  1011,  1019,  1023,
    1027,  1031,  1035,  1039,  1043,  1055,  1059,  1063,  1067,  1071,
    1075,  1079,  1083,  1087,  1091,  1095,  1099,  1103,  1107,  1111,
    1115,  1119,  1123,  1131,  1135,  1139,  1147,  1152,  1159,  1165,
    1173,  1178,  1185,  1191,  1199,  1207,  1214,  1220,  1228,  1236,
    1244,  1252,  1260,  1268,  1276,  1289,  1293,  1297,  1301,  1305,
    1309,  1313,  1317,  1321,  1325,  1329,  1333,  1341,  1350,  1356,
    1366,  1374,  1382,  1390,  1394,  1402,  1410,  1418,  1425,  1431,
    1439,  1448,  1459,  1468,  1475,  1484,  1496,  1503,  1512,  1516,
    1520,  1524,  1528,  1532,  1540,  1548,  1559,  1570,  1578,  1586,
    1598,  1605,  1615,  1619,  1627,  1634,  1648,  1652,  1660,  1664,
    1673,  1680,  1690,  1697,  1705,  1722,  1726,  1735,  1742,  1754,
    1758,  1767,  1774,  1784,  1791,  1801,  1810,  1816,  1824,  1830,
    1842,  1849,  1858,  1870,  1876,  1885,  1892,  1899,  1906,  1913
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
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


#line 50 "../../obj/src/GrammarParser.y" // lalr1.cc:1242
} // libcasm_fe
#line 5320 "GrammarParser.cpp" // lalr1.cc:1242
#line 1919 "../../obj/src/GrammarParser.y" // lalr1.cc:1243


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
