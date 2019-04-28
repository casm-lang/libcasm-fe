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


#line 69 "GrammarParser.cpp" // lalr1.cc:435


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
#line 164 "GrammarParser.cpp" // lalr1.cc:510

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
      case 10: // "import"
      case 11: // "function"
      case 12: // "initially"
      case 13: // "defined"
      case 14: // "seq"
      case 15: // "endseq"
      case 16: // "par"
      case 17: // "endpar"
      case 18: // "skip"
      case 19: // "let"
      case 20: // "in"
      case 21: // "forall"
      case 22: // "choose"
      case 23: // "iterate"
      case 24: // "do"
      case 25: // "if"
      case 26: // "then"
      case 27: // "else"
      case 28: // "case"
      case 29: // "of"
      case 30: // "default"
      case 31: // "holds"
      case 32: // "exists"
      case 33: // "with"
      case 34: // "as"
      case 35: // "while"
      case 36: // "undef"
      case 37: // "false"
      case 38: // "true"
      case 39: // "and"
      case 40: // "or"
      case 41: // "xor"
      case 42: // "implies"
      case 43: // "not"
      case 44: // "+"
      case 45: // "-"
      case 46: // "="
      case 47: // "("
      case 48: // ")"
      case 49: // "["
      case 50: // "]"
      case 51: // "{"
      case 52: // "}"
      case 53: // ":"
      case 54: // "::"
      case 55: // "_"
      case 56: // "|"
      case 57: // "@"
      case 58: // ","
      case 59: // "<"
      case 60: // ">"
      case 61: // "*"
      case 62: // "/"
      case 63: // "%"
      case 64: // "^"
      case 65: // "'"
      case 66: // ".."
      case 67: // "."
      case 68: // "->"
      case 69: // "=>"
      case 70: // ":="
      case 71: // "!="
      case 72: // "<="
      case 73: // ">="
      case 74: // "{|"
      case 75: // "|}"
        value.YY_MOVE_OR_COPY< Ast::Token::Ptr > (YY_MOVE (that.value));
        break;

      case 177: // Attribute
        value.YY_MOVE_OR_COPY< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case 176: // Attributes
        value.YY_MOVE_OR_COPY< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case 178: // BasicAttribute
        value.YY_MOVE_OR_COPY< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 153: // BasicType
        value.YY_MOVE_OR_COPY< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case 115: // BlockRule
        value.YY_MOVE_OR_COPY< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case 124: // CallExpression
        value.YY_MOVE_OR_COPY< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 118: // CallRule
        value.YY_MOVE_OR_COPY< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 135: // CardinalityExpression
        value.YY_MOVE_OR_COPY< CardinalityExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 110: // CaseLabel
        value.YY_MOVE_OR_COPY< Case::Ptr > (YY_MOVE (that.value));
        break;

      case 108: // CaseRule
        value.YY_MOVE_OR_COPY< CaseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 109: // CaseLabels
        value.YY_MOVE_OR_COPY< Cases::Ptr > (YY_MOVE (that.value));
        break;

      case 132: // ChooseExpression
        value.YY_MOVE_OR_COPY< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 113: // ChooseRule
        value.YY_MOVE_OR_COPY< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 131: // ConditionalExpression
        value.YY_MOVE_OR_COPY< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 107: // ConditionalRule
        value.YY_MOVE_OR_COPY< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 162: // MaybeDefined
        value.YY_MOVE_OR_COPY< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case 92: // AttributedDefinition
      case 93: // Definition
        value.YY_MOVE_OR_COPY< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case 91: // Definitions
        value.YY_MOVE_OR_COPY< Definitions::Ptr > (YY_MOVE (that.value));
        break;

      case 96: // DerivedDefinition
        value.YY_MOVE_OR_COPY< DerivedDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 125: // DirectCallExpression
        value.YY_MOVE_OR_COPY< DirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 95: // EnumerationDefinition
        value.YY_MOVE_OR_COPY< EnumerationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 99: // EnumeratorDefinition
        value.YY_MOVE_OR_COPY< EnumeratorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 100: // Enumerators
        value.YY_MOVE_OR_COPY< Enumerators::Ptr > (YY_MOVE (that.value));
        break;

      case 134: // ExistentialQuantifierExpression
        value.YY_MOVE_OR_COPY< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 121: // Term
      case 122: // SimpleOrClaspedTerm
      case 123: // OperatorExpression
        value.YY_MOVE_OR_COPY< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case 179: // ExpressionAttribute
        value.YY_MOVE_OR_COPY< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 120: // Terms
        value.YY_MOVE_OR_COPY< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case 158: // FixedSizedType
        value.YY_MOVE_OR_COPY< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case 112: // ForallRule
        value.YY_MOVE_OR_COPY< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 98: // FunctionDefinition
        value.YY_MOVE_OR_COPY< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 90: // Header
        value.YY_MOVE_OR_COPY< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 82: // "identifier"
      case 166: // Identifier
        value.YY_MOVE_OR_COPY< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case 167: // IdentifierPath
        value.YY_MOVE_OR_COPY< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // ImportDefinition
        value.YY_MOVE_OR_COPY< ImportDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 128: // IndirectCallExpression
        value.YY_MOVE_OR_COPY< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 94: // InitDefinition
        value.YY_MOVE_OR_COPY< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 165: // Initializer
        value.YY_MOVE_OR_COPY< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case 164: // Initializers
        value.YY_MOVE_OR_COPY< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case 163: // MaybeInitially
        value.YY_MOVE_OR_COPY< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case 102: // InvariantDefinition
        value.YY_MOVE_OR_COPY< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 114: // IterateRule
        value.YY_MOVE_OR_COPY< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 130: // LetExpression
        value.YY_MOVE_OR_COPY< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 111: // LetRule
        value.YY_MOVE_OR_COPY< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case 145: // ListLiteral
        value.YY_MOVE_OR_COPY< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 136: // Literal
        value.YY_MOVE_OR_COPY< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case 127: // LiteralCallExpression
        value.YY_MOVE_OR_COPY< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 126: // MethodCallExpression
        value.YY_MOVE_OR_COPY< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 150: // Assignment
        value.YY_MOVE_OR_COPY< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 149: // Assignments
        value.YY_MOVE_OR_COPY< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case 146: // RangeLiteral
        value.YY_MOVE_OR_COPY< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 148: // RecordLiteral
        value.YY_MOVE_OR_COPY< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 155: // RecordType
        value.YY_MOVE_OR_COPY< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case 144: // ReferenceLiteral
        value.YY_MOVE_OR_COPY< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 157: // RelationType
        value.YY_MOVE_OR_COPY< RelationType::Ptr > (YY_MOVE (that.value));
        break;

      case 105: // Rule
        value.YY_MOVE_OR_COPY< Rule::Ptr > (YY_MOVE (that.value));
        break;

      case 97: // RuleDefinition
        value.YY_MOVE_OR_COPY< RuleDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 104: // Rules
        value.YY_MOVE_OR_COPY< Rules::Ptr > (YY_MOVE (that.value));
        break;

      case 116: // SequenceRule
        value.YY_MOVE_OR_COPY< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case 106: // SkipRule
        value.YY_MOVE_OR_COPY< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Specification
        value.YY_MOVE_OR_COPY< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case 156: // TemplateType
        value.YY_MOVE_OR_COPY< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case 147: // TupleLiteral
        value.YY_MOVE_OR_COPY< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 154: // TupleType
        value.YY_MOVE_OR_COPY< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case 129: // TypeCastingExpression
        value.YY_MOVE_OR_COPY< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 151: // Types
      case 159: // FunctionParameters
      case 160: // MaybeFunctionParameters
        value.YY_MOVE_OR_COPY< Types::Ptr > (YY_MOVE (that.value));
        break;

      case 137: // UndefinedLiteral
        value.YY_MOVE_OR_COPY< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 133: // UniversalQuantifierExpression
        value.YY_MOVE_OR_COPY< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 117: // UpdateRule
        value.YY_MOVE_OR_COPY< UpdateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 101: // UsingDefinition
        value.YY_MOVE_OR_COPY< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 138: // BooleanLiteral
      case 139: // IntegerLiteral
      case 140: // RationalLiteral
      case 141: // DecimalLiteral
      case 142: // BinaryLiteral
      case 143: // StringLiteral
        value.YY_MOVE_OR_COPY< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 175: // VariableBinding
        value.YY_MOVE_OR_COPY< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case 174: // VariableBindings
        value.YY_MOVE_OR_COPY< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case 168: // Variable
      case 171: // TypedVariable
      case 172: // AttributedVariable
      case 173: // TypedAttributedVariable
        value.YY_MOVE_OR_COPY< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 161: // Parameters
      case 169: // AttributedVariables
      case 170: // TypedVariables
        value.YY_MOVE_OR_COPY< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 119: // WhileRule
        value.YY_MOVE_OR_COPY< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case 152: // Type
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
      case 10: // "import"
      case 11: // "function"
      case 12: // "initially"
      case 13: // "defined"
      case 14: // "seq"
      case 15: // "endseq"
      case 16: // "par"
      case 17: // "endpar"
      case 18: // "skip"
      case 19: // "let"
      case 20: // "in"
      case 21: // "forall"
      case 22: // "choose"
      case 23: // "iterate"
      case 24: // "do"
      case 25: // "if"
      case 26: // "then"
      case 27: // "else"
      case 28: // "case"
      case 29: // "of"
      case 30: // "default"
      case 31: // "holds"
      case 32: // "exists"
      case 33: // "with"
      case 34: // "as"
      case 35: // "while"
      case 36: // "undef"
      case 37: // "false"
      case 38: // "true"
      case 39: // "and"
      case 40: // "or"
      case 41: // "xor"
      case 42: // "implies"
      case 43: // "not"
      case 44: // "+"
      case 45: // "-"
      case 46: // "="
      case 47: // "("
      case 48: // ")"
      case 49: // "["
      case 50: // "]"
      case 51: // "{"
      case 52: // "}"
      case 53: // ":"
      case 54: // "::"
      case 55: // "_"
      case 56: // "|"
      case 57: // "@"
      case 58: // ","
      case 59: // "<"
      case 60: // ">"
      case 61: // "*"
      case 62: // "/"
      case 63: // "%"
      case 64: // "^"
      case 65: // "'"
      case 66: // ".."
      case 67: // "."
      case 68: // "->"
      case 69: // "=>"
      case 70: // ":="
      case 71: // "!="
      case 72: // "<="
      case 73: // ">="
      case 74: // "{|"
      case 75: // "|}"
        value.move< Ast::Token::Ptr > (YY_MOVE (that.value));
        break;

      case 177: // Attribute
        value.move< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case 176: // Attributes
        value.move< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case 178: // BasicAttribute
        value.move< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 153: // BasicType
        value.move< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case 115: // BlockRule
        value.move< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case 124: // CallExpression
        value.move< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 118: // CallRule
        value.move< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 135: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 110: // CaseLabel
        value.move< Case::Ptr > (YY_MOVE (that.value));
        break;

      case 108: // CaseRule
        value.move< CaseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 109: // CaseLabels
        value.move< Cases::Ptr > (YY_MOVE (that.value));
        break;

      case 132: // ChooseExpression
        value.move< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 113: // ChooseRule
        value.move< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 131: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 107: // ConditionalRule
        value.move< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 162: // MaybeDefined
        value.move< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case 92: // AttributedDefinition
      case 93: // Definition
        value.move< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case 91: // Definitions
        value.move< Definitions::Ptr > (YY_MOVE (that.value));
        break;

      case 96: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 125: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 95: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 99: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 100: // Enumerators
        value.move< Enumerators::Ptr > (YY_MOVE (that.value));
        break;

      case 134: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 121: // Term
      case 122: // SimpleOrClaspedTerm
      case 123: // OperatorExpression
        value.move< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case 179: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 120: // Terms
        value.move< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case 158: // FixedSizedType
        value.move< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case 112: // ForallRule
        value.move< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 98: // FunctionDefinition
        value.move< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 90: // Header
        value.move< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 82: // "identifier"
      case 166: // Identifier
        value.move< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case 167: // IdentifierPath
        value.move< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // ImportDefinition
        value.move< ImportDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 128: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 94: // InitDefinition
        value.move< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 165: // Initializer
        value.move< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case 164: // Initializers
        value.move< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case 163: // MaybeInitially
        value.move< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case 102: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 114: // IterateRule
        value.move< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 130: // LetExpression
        value.move< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 111: // LetRule
        value.move< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case 145: // ListLiteral
        value.move< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 136: // Literal
        value.move< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case 127: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 126: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 150: // Assignment
        value.move< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 149: // Assignments
        value.move< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case 146: // RangeLiteral
        value.move< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 148: // RecordLiteral
        value.move< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 155: // RecordType
        value.move< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case 144: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 157: // RelationType
        value.move< RelationType::Ptr > (YY_MOVE (that.value));
        break;

      case 105: // Rule
        value.move< Rule::Ptr > (YY_MOVE (that.value));
        break;

      case 97: // RuleDefinition
        value.move< RuleDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 104: // Rules
        value.move< Rules::Ptr > (YY_MOVE (that.value));
        break;

      case 116: // SequenceRule
        value.move< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case 106: // SkipRule
        value.move< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Specification
        value.move< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case 156: // TemplateType
        value.move< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case 147: // TupleLiteral
        value.move< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 154: // TupleType
        value.move< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case 129: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 151: // Types
      case 159: // FunctionParameters
      case 160: // MaybeFunctionParameters
        value.move< Types::Ptr > (YY_MOVE (that.value));
        break;

      case 137: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 133: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 117: // UpdateRule
        value.move< UpdateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 101: // UsingDefinition
        value.move< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 138: // BooleanLiteral
      case 139: // IntegerLiteral
      case 140: // RationalLiteral
      case 141: // DecimalLiteral
      case 142: // BinaryLiteral
      case 143: // StringLiteral
        value.move< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 175: // VariableBinding
        value.move< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case 174: // VariableBindings
        value.move< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case 168: // Variable
      case 171: // TypedVariable
      case 172: // AttributedVariable
      case 173: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 161: // Parameters
      case 169: // AttributedVariables
      case 170: // TypedVariables
        value.move< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 119: // WhileRule
        value.move< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case 152: // Type
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
      case 10: // "import"
      case 11: // "function"
      case 12: // "initially"
      case 13: // "defined"
      case 14: // "seq"
      case 15: // "endseq"
      case 16: // "par"
      case 17: // "endpar"
      case 18: // "skip"
      case 19: // "let"
      case 20: // "in"
      case 21: // "forall"
      case 22: // "choose"
      case 23: // "iterate"
      case 24: // "do"
      case 25: // "if"
      case 26: // "then"
      case 27: // "else"
      case 28: // "case"
      case 29: // "of"
      case 30: // "default"
      case 31: // "holds"
      case 32: // "exists"
      case 33: // "with"
      case 34: // "as"
      case 35: // "while"
      case 36: // "undef"
      case 37: // "false"
      case 38: // "true"
      case 39: // "and"
      case 40: // "or"
      case 41: // "xor"
      case 42: // "implies"
      case 43: // "not"
      case 44: // "+"
      case 45: // "-"
      case 46: // "="
      case 47: // "("
      case 48: // ")"
      case 49: // "["
      case 50: // "]"
      case 51: // "{"
      case 52: // "}"
      case 53: // ":"
      case 54: // "::"
      case 55: // "_"
      case 56: // "|"
      case 57: // "@"
      case 58: // ","
      case 59: // "<"
      case 60: // ">"
      case 61: // "*"
      case 62: // "/"
      case 63: // "%"
      case 64: // "^"
      case 65: // "'"
      case 66: // ".."
      case 67: // "."
      case 68: // "->"
      case 69: // "=>"
      case 70: // ":="
      case 71: // "!="
      case 72: // "<="
      case 73: // ">="
      case 74: // "{|"
      case 75: // "|}"
        value.move< Ast::Token::Ptr > (that.value);
        break;

      case 177: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 176: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 178: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 153: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 115: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 124: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
        break;

      case 118: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 135: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (that.value);
        break;

      case 110: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 108: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 109: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 132: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 113: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 131: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 107: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 162: // MaybeDefined
        value.move< Defined::Ptr > (that.value);
        break;

      case 92: // AttributedDefinition
      case 93: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 91: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 96: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 125: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 95: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 99: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 100: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 134: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 121: // Term
      case 122: // SimpleOrClaspedTerm
      case 123: // OperatorExpression
        value.move< Expression::Ptr > (that.value);
        break;

      case 179: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 120: // Terms
        value.move< Expressions::Ptr > (that.value);
        break;

      case 158: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 112: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 98: // FunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 90: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 82: // "identifier"
      case 166: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 167: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 103: // ImportDefinition
        value.move< ImportDefinition::Ptr > (that.value);
        break;

      case 128: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 94: // InitDefinition
        value.move< InitDefinition::Ptr > (that.value);
        break;

      case 165: // Initializer
        value.move< Initializer::Ptr > (that.value);
        break;

      case 164: // Initializers
        value.move< Initializers::Ptr > (that.value);
        break;

      case 163: // MaybeInitially
        value.move< Initially::Ptr > (that.value);
        break;

      case 102: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (that.value);
        break;

      case 114: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 130: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 111: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 145: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 136: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 127: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 126: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 150: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 149: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 146: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 148: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 155: // RecordType
        value.move< RecordType::Ptr > (that.value);
        break;

      case 144: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 157: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 105: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 97: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 104: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 116: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 106: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 89: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 156: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 147: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 154: // TupleType
        value.move< TupleType::Ptr > (that.value);
        break;

      case 129: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 151: // Types
      case 159: // FunctionParameters
      case 160: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 137: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 133: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 117: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 101: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 138: // BooleanLiteral
      case 139: // IntegerLiteral
      case 140: // RationalLiteral
      case 141: // DecimalLiteral
      case 142: // BinaryLiteral
      case 143: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 175: // VariableBinding
        value.move< VariableBinding::Ptr > (that.value);
        break;

      case 174: // VariableBindings
        value.move< VariableBindings::Ptr > (that.value);
        break;

      case 168: // Variable
      case 171: // TypedVariable
      case 172: // AttributedVariable
      case 173: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 161: // Parameters
      case 169: // AttributedVariables
      case 170: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 119: // WhileRule
        value.move< WhileRule::Ptr > (that.value);
        break;

      case 152: // Type
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
      case 10: // "import"
      case 11: // "function"
      case 12: // "initially"
      case 13: // "defined"
      case 14: // "seq"
      case 15: // "endseq"
      case 16: // "par"
      case 17: // "endpar"
      case 18: // "skip"
      case 19: // "let"
      case 20: // "in"
      case 21: // "forall"
      case 22: // "choose"
      case 23: // "iterate"
      case 24: // "do"
      case 25: // "if"
      case 26: // "then"
      case 27: // "else"
      case 28: // "case"
      case 29: // "of"
      case 30: // "default"
      case 31: // "holds"
      case 32: // "exists"
      case 33: // "with"
      case 34: // "as"
      case 35: // "while"
      case 36: // "undef"
      case 37: // "false"
      case 38: // "true"
      case 39: // "and"
      case 40: // "or"
      case 41: // "xor"
      case 42: // "implies"
      case 43: // "not"
      case 44: // "+"
      case 45: // "-"
      case 46: // "="
      case 47: // "("
      case 48: // ")"
      case 49: // "["
      case 50: // "]"
      case 51: // "{"
      case 52: // "}"
      case 53: // ":"
      case 54: // "::"
      case 55: // "_"
      case 56: // "|"
      case 57: // "@"
      case 58: // ","
      case 59: // "<"
      case 60: // ">"
      case 61: // "*"
      case 62: // "/"
      case 63: // "%"
      case 64: // "^"
      case 65: // "'"
      case 66: // ".."
      case 67: // "."
      case 68: // "->"
      case 69: // "=>"
      case 70: // ":="
      case 71: // "!="
      case 72: // "<="
      case 73: // ">="
      case 74: // "{|"
      case 75: // "|}"
        yylhs.value.emplace< Ast::Token::Ptr > ();
        break;

      case 177: // Attribute
        yylhs.value.emplace< Attribute::Ptr > ();
        break;

      case 176: // Attributes
        yylhs.value.emplace< Attributes::Ptr > ();
        break;

      case 178: // BasicAttribute
        yylhs.value.emplace< BasicAttribute::Ptr > ();
        break;

      case 153: // BasicType
        yylhs.value.emplace< BasicType::Ptr > ();
        break;

      case 115: // BlockRule
        yylhs.value.emplace< BlockRule::Ptr > ();
        break;

      case 124: // CallExpression
        yylhs.value.emplace< CallExpression::Ptr > ();
        break;

      case 118: // CallRule
        yylhs.value.emplace< CallRule::Ptr > ();
        break;

      case 135: // CardinalityExpression
        yylhs.value.emplace< CardinalityExpression::Ptr > ();
        break;

      case 110: // CaseLabel
        yylhs.value.emplace< Case::Ptr > ();
        break;

      case 108: // CaseRule
        yylhs.value.emplace< CaseRule::Ptr > ();
        break;

      case 109: // CaseLabels
        yylhs.value.emplace< Cases::Ptr > ();
        break;

      case 132: // ChooseExpression
        yylhs.value.emplace< ChooseExpression::Ptr > ();
        break;

      case 113: // ChooseRule
        yylhs.value.emplace< ChooseRule::Ptr > ();
        break;

      case 131: // ConditionalExpression
        yylhs.value.emplace< ConditionalExpression::Ptr > ();
        break;

      case 107: // ConditionalRule
        yylhs.value.emplace< ConditionalRule::Ptr > ();
        break;

      case 162: // MaybeDefined
        yylhs.value.emplace< Defined::Ptr > ();
        break;

      case 92: // AttributedDefinition
      case 93: // Definition
        yylhs.value.emplace< Definition::Ptr > ();
        break;

      case 91: // Definitions
        yylhs.value.emplace< Definitions::Ptr > ();
        break;

      case 96: // DerivedDefinition
        yylhs.value.emplace< DerivedDefinition::Ptr > ();
        break;

      case 125: // DirectCallExpression
        yylhs.value.emplace< DirectCallExpression::Ptr > ();
        break;

      case 95: // EnumerationDefinition
        yylhs.value.emplace< EnumerationDefinition::Ptr > ();
        break;

      case 99: // EnumeratorDefinition
        yylhs.value.emplace< EnumeratorDefinition::Ptr > ();
        break;

      case 100: // Enumerators
        yylhs.value.emplace< Enumerators::Ptr > ();
        break;

      case 134: // ExistentialQuantifierExpression
        yylhs.value.emplace< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 121: // Term
      case 122: // SimpleOrClaspedTerm
      case 123: // OperatorExpression
        yylhs.value.emplace< Expression::Ptr > ();
        break;

      case 179: // ExpressionAttribute
        yylhs.value.emplace< ExpressionAttribute::Ptr > ();
        break;

      case 120: // Terms
        yylhs.value.emplace< Expressions::Ptr > ();
        break;

      case 158: // FixedSizedType
        yylhs.value.emplace< FixedSizedType::Ptr > ();
        break;

      case 112: // ForallRule
        yylhs.value.emplace< ForallRule::Ptr > ();
        break;

      case 98: // FunctionDefinition
        yylhs.value.emplace< FunctionDefinition::Ptr > ();
        break;

      case 90: // Header
        yylhs.value.emplace< HeaderDefinition::Ptr > ();
        break;

      case 82: // "identifier"
      case 166: // Identifier
        yylhs.value.emplace< Identifier::Ptr > ();
        break;

      case 167: // IdentifierPath
        yylhs.value.emplace< IdentifierPath::Ptr > ();
        break;

      case 103: // ImportDefinition
        yylhs.value.emplace< ImportDefinition::Ptr > ();
        break;

      case 128: // IndirectCallExpression
        yylhs.value.emplace< IndirectCallExpression::Ptr > ();
        break;

      case 94: // InitDefinition
        yylhs.value.emplace< InitDefinition::Ptr > ();
        break;

      case 165: // Initializer
        yylhs.value.emplace< Initializer::Ptr > ();
        break;

      case 164: // Initializers
        yylhs.value.emplace< Initializers::Ptr > ();
        break;

      case 163: // MaybeInitially
        yylhs.value.emplace< Initially::Ptr > ();
        break;

      case 102: // InvariantDefinition
        yylhs.value.emplace< InvariantDefinition::Ptr > ();
        break;

      case 114: // IterateRule
        yylhs.value.emplace< IterateRule::Ptr > ();
        break;

      case 130: // LetExpression
        yylhs.value.emplace< LetExpression::Ptr > ();
        break;

      case 111: // LetRule
        yylhs.value.emplace< LetRule::Ptr > ();
        break;

      case 145: // ListLiteral
        yylhs.value.emplace< ListLiteral::Ptr > ();
        break;

      case 136: // Literal
        yylhs.value.emplace< Literal::Ptr > ();
        break;

      case 127: // LiteralCallExpression
        yylhs.value.emplace< LiteralCallExpression::Ptr > ();
        break;

      case 126: // MethodCallExpression
        yylhs.value.emplace< MethodCallExpression::Ptr > ();
        break;

      case 150: // Assignment
        yylhs.value.emplace< NamedExpression::Ptr > ();
        break;

      case 149: // Assignments
        yylhs.value.emplace< NamedExpressions::Ptr > ();
        break;

      case 146: // RangeLiteral
        yylhs.value.emplace< RangeLiteral::Ptr > ();
        break;

      case 148: // RecordLiteral
        yylhs.value.emplace< RecordLiteral::Ptr > ();
        break;

      case 155: // RecordType
        yylhs.value.emplace< RecordType::Ptr > ();
        break;

      case 144: // ReferenceLiteral
        yylhs.value.emplace< ReferenceLiteral::Ptr > ();
        break;

      case 157: // RelationType
        yylhs.value.emplace< RelationType::Ptr > ();
        break;

      case 105: // Rule
        yylhs.value.emplace< Rule::Ptr > ();
        break;

      case 97: // RuleDefinition
        yylhs.value.emplace< RuleDefinition::Ptr > ();
        break;

      case 104: // Rules
        yylhs.value.emplace< Rules::Ptr > ();
        break;

      case 116: // SequenceRule
        yylhs.value.emplace< SequenceRule::Ptr > ();
        break;

      case 106: // SkipRule
        yylhs.value.emplace< SkipRule::Ptr > ();
        break;

      case 89: // Specification
        yylhs.value.emplace< Specification::Ptr > ();
        break;

      case 156: // TemplateType
        yylhs.value.emplace< TemplateType::Ptr > ();
        break;

      case 147: // TupleLiteral
        yylhs.value.emplace< TupleLiteral::Ptr > ();
        break;

      case 154: // TupleType
        yylhs.value.emplace< TupleType::Ptr > ();
        break;

      case 129: // TypeCastingExpression
        yylhs.value.emplace< TypeCastingExpression::Ptr > ();
        break;

      case 151: // Types
      case 159: // FunctionParameters
      case 160: // MaybeFunctionParameters
        yylhs.value.emplace< Types::Ptr > ();
        break;

      case 137: // UndefinedLiteral
        yylhs.value.emplace< UndefLiteral::Ptr > ();
        break;

      case 133: // UniversalQuantifierExpression
        yylhs.value.emplace< UniversalQuantifierExpression::Ptr > ();
        break;

      case 117: // UpdateRule
        yylhs.value.emplace< UpdateRule::Ptr > ();
        break;

      case 101: // UsingDefinition
        yylhs.value.emplace< UsingDefinition::Ptr > ();
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 138: // BooleanLiteral
      case 139: // IntegerLiteral
      case 140: // RationalLiteral
      case 141: // DecimalLiteral
      case 142: // BinaryLiteral
      case 143: // StringLiteral
        yylhs.value.emplace< ValueLiteral::Ptr > ();
        break;

      case 175: // VariableBinding
        yylhs.value.emplace< VariableBinding::Ptr > ();
        break;

      case 174: // VariableBindings
        yylhs.value.emplace< VariableBindings::Ptr > ();
        break;

      case 168: // Variable
      case 171: // TypedVariable
      case 172: // AttributedVariable
      case 173: // TypedAttributedVariable
        yylhs.value.emplace< VariableDefinition::Ptr > ();
        break;

      case 161: // Parameters
      case 169: // AttributedVariables
      case 170: // TypedVariables
        yylhs.value.emplace< VariableDefinitions::Ptr > ();
        break;

      case 119: // WhileRule
        yylhs.value.emplace< WhileRule::Ptr > ();
        break;

      case 152: // Type
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
#line 413 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      m_specification.setHeader( yystack_[1].value.as < HeaderDefinition::Ptr > () );
      m_specification.setDefinitions( yystack_[0].value.as < Definitions::Ptr > () );
      m_specification.setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 2188 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 3:
#line 423 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2198 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 4:
#line 429 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2206 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 5:
#line 437 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2216 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 6:
#line 443 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2226 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 7:
#line 453 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2236 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 8:
#line 459 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2244 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 9:
#line 463 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2252 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 10:
#line 471 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2260 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 11:
#line 475 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2268 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 12:
#line 479 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 13:
#line 483 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2284 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 14:
#line 487 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 2292 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 15:
#line 491 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 2300 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 16:
#line 495 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 2308 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 17:
#line 499 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 2316 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 18:
#line 507 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2324 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 19:
#line 511 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2332 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 20:
#line 519 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2340 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 21:
#line 527 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2349 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 22:
#line 532 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2359 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 23:
#line 538 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 2367 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 24:
#line 546 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2377 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 25:
#line 552 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2386 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 26:
#line 557 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
  }
#line 2397 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 27:
#line 564 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2407 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 28:
#line 570 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2415 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 29:
#line 574 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2423 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 30:
#line 582 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < FunctionDefinition::Ptr > () = Ast::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      const auto initially = yylhs.value.as < FunctionDefinition::Ptr > ()->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->updateRule()->function()->setIdentifier( IdentifierPath::fromIdentifier( yystack_[6].value.as < Identifier::Ptr > () ) );
      }
  }
#line 2438 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 31:
#line 597 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 2446 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 32:
#line 601 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 2456 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 33:
#line 607 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 2464 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 34:
#line 615 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2475 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 35:
#line 622 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2485 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 36:
#line 632 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2493 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 37:
#line 640 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < InvariantDefinition::Ptr > () = Ast::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2501 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 38:
#line 648 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2509 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 39:
#line 652 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 2517 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 40:
#line 664 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 2527 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 41:
#line 670 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 2537 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 42:
#line 680 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 2545 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 43:
#line 684 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 44:
#line 688 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 45:
#line 692 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 46:
#line 696 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 2577 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 47:
#line 700 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 2585 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 48:
#line 704 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 49:
#line 708 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 2601 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 50:
#line 712 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 51:
#line 716 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 2617 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 52:
#line 720 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 2625 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 53:
#line 724 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 2633 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 54:
#line 732 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2641 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 55:
#line 740 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2649 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 56:
#line 744 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2657 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 57:
#line 752 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2665 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 58:
#line 756 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 2673 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 59:
#line 764 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 2683 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 60:
#line 770 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 2693 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 61:
#line 780 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2701 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 62:
#line 784 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2709 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 63:
#line 788 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2717 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 64:
#line 796 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2725 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 65:
#line 804 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2733 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 66:
#line 808 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2741 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 67:
#line 816 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2749 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 68:
#line 824 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2757 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 69:
#line 832 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2765 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 70:
#line 836 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2773 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 71:
#line 840 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2782 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 72:
#line 845 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2791 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 73:
#line 854 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2799 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 74:
#line 858 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2807 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 75:
#line 862 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2816 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 76:
#line 867 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2825 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 77:
#line 876 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2833 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 78:
#line 884 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 2841 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 79:
#line 892 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2849 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 80:
#line 904 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 2860 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 81:
#line 911 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 2870 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 82:
#line 921 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 2878 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 83:
#line 925 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 2886 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 84:
#line 929 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 2894 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 85:
#line 933 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 2902 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 86:
#line 937 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 2910 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 87:
#line 941 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 2918 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 88:
#line 945 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 2926 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 89:
#line 949 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 2934 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 90:
#line 953 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 2942 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 91:
#line 961 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< Ast::EmbracedExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2950 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 92:
#line 965 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 2958 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 93:
#line 969 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 2966 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 94:
#line 973 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 2974 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 95:
#line 977 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 2982 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 96:
#line 981 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2990 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 97:
#line 985 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2998 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 98:
#line 997 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3006 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 99:
#line 1001 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 3014 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 100:
#line 1005 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 3022 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 101:
#line 1009 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 3030 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 102:
#line 1013 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 3038 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 103:
#line 1017 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 3046 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 104:
#line 1021 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 3054 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 105:
#line 1025 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 3062 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 106:
#line 1029 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 3070 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 107:
#line 1033 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 3078 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 108:
#line 1037 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 3086 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 109:
#line 1041 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 3094 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 110:
#line 1045 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 3102 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 111:
#line 1049 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 3110 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 112:
#line 1053 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 3118 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 113:
#line 1057 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3126 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 114:
#line 1061 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3134 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 115:
#line 1065 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 3142 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 116:
#line 1073 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 3150 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 117:
#line 1077 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 3158 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 118:
#line 1081 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 3166 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 119:
#line 1089 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > (), arguments );
  }
#line 3175 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 120:
#line 1094 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), arguments );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3186 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 121:
#line 1101 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3196 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 122:
#line 1107 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 3204 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 123:
#line 1115 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 3213 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 124:
#line 1120 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3224 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 125:
#line 1127 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3234 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 126:
#line 1133 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 3242 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 127:
#line 1141 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 3250 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 128:
#line 1149 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3261 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 129:
#line 1156 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3271 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 130:
#line 1162 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 3279 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 131:
#line 1170 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3287 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 132:
#line 1178 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3295 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 133:
#line 1186 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3303 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 134:
#line 1194 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3311 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 135:
#line 1202 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3319 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 136:
#line 1210 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3327 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 137:
#line 1218 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3335 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 138:
#line 1231 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 3343 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 139:
#line 1235 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3351 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 140:
#line 1239 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3359 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 141:
#line 1243 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3367 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 142:
#line 1247 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3375 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 143:
#line 1251 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3383 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 144:
#line 1255 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3391 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 145:
#line 1259 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 3399 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 146:
#line 1263 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 3407 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 147:
#line 1267 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 3415 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 148:
#line 1271 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 3423 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 149:
#line 1275 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 3431 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 150:
#line 1283 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3440 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 151:
#line 1292 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3450 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 152:
#line 1298 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3460 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 153:
#line 1308 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3468 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 154:
#line 1316 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3476 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 155:
#line 1324 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3484 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 156:
#line 1332 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3492 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 157:
#line 1336 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3500 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 158:
#line 1344 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3508 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 159:
#line 1352 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3516 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 160:
#line 1360 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3527 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 161:
#line 1367 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3537 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 162:
#line 1373 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 3545 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 163:
#line 1381 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3555 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 164:
#line 1390 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3568 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 165:
#line 1401 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3578 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 166:
#line 1410 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 3589 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 167:
#line 1417 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 3599 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 168:
#line 1426 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3607 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 169:
#line 1438 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3618 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 170:
#line 1445 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3628 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 171:
#line 1454 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 3636 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 172:
#line 1458 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 3644 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 173:
#line 1462 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 3652 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 174:
#line 1466 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 3660 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 175:
#line 1470 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 3668 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 176:
#line 1474 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 3676 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 177:
#line 1482 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3684 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 178:
#line 1490 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = Ast::make< TupleType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), subTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3695 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 179:
#line 1501 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = Ast::make< RecordType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3706 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 180:
#line 1512 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3714 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 181:
#line 1520 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3722 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 182:
#line 1528 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3730 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 183:
#line 1540 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3741 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 184:
#line 1547 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3751 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 185:
#line 1557 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 3759 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 186:
#line 1561 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 3767 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 187:
#line 1569 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 3778 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 188:
#line 1576 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 3788 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 189:
#line 1590 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3796 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 190:
#line 1594 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 3804 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 191:
#line 1602 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3812 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 192:
#line 1606 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto initializers = Ast::make< Initializers >( yylhs.location );
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
#line 3821 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 193:
#line 1615 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto initializers = yystack_[2].value.as < Initializers::Ptr > ();
      yystack_[0].value.as < Initializer::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 3832 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 194:
#line 1622 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto initializers = Ast::make< Initializers >( yylhs.location );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 3842 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 195:
#line 1632 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3853 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 196:
#line 1639 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), arguments, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3865 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 197:
#line 1647 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto lbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto rbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, lbToken, arguments, rbToken, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3878 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 198:
#line 1664 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 3886 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 199:
#line 1668 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 3895 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 200:
#line 1677 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < Ast::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 3906 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 201:
#line 1684 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3914 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 202:
#line 1696 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 3922 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 203:
#line 1700 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 3931 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 204:
#line 1709 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 3942 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 205:
#line 1716 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 3952 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 206:
#line 1726 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3963 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 207:
#line 1733 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3973 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 208:
#line 1743 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variable = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 3982 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 209:
#line 1752 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 3992 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 210:
#line 1758 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4000 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 211:
#line 1766 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4010 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 212:
#line 1772 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4018 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 213:
#line 1784 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4029 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 214:
#line 1791 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4039 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 215:
#line 1800 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4047 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 216:
#line 1812 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4057 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 217:
#line 1818 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4067 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 218:
#line 1827 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4078 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 219:
#line 1834 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4089 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 220:
#line 1841 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 4097 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 221:
#line 1848 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4105 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 222:
#line 1855 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4113 "GrammarParser.cpp" // lalr1.cc:919
    break;


#line 4117 "GrammarParser.cpp" // lalr1.cc:919
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


  const short Parser::yypact_ninf_ = -149;

  const short Parser::yytable_ninf_ = -185;

  const short
  Parser::yypact_[] =
  {
      19,  -149,    17,    28,   294,    20,  -149,    -9,  -149,  -149,
    1780,    -5,    21,  -149,  -149,    -1,     0,     0,     0,     0,
       0,     0,     0,   245,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,   377,  -149,  -149,  -149,    -3,    -3,
      -3,  1780,    -3,  -149,  -149,  -149,  1780,    29,    29,  1307,
    1051,    29,     0,  -149,  -149,  -149,  -149,  -149,  -149,  2536,
      24,  -149,    25,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,   163,  -149,
    -149,  1844,    16,   108,    55,    69,    67,    71,   114,    90,
    -149,  -149,    91,  -149,  -149,   101,     1,  -149,    -3,     4,
    -149,    22,  2073,    34,  -149,  -149,  -149,   133,    94,  2291,
      88,  -149,   109,   144,  -149,    27,  2326,    33,    16,  1780,
    1780,  1780,  1780,  1780,  1780,  1780,  1780,  1780,  1780,  1780,
    1780,  1780,  1780,  1780,  1780,  1780,     6,     5,  1115,  1179,
       0,  1307,  2536,   115,    60,  -149,    12,     6,   146,  1652,
      14,     6,     6,  1780,     0,     6,     6,  1780,  1780,    -3,
    -149,  1780,    -3,  1780,  1780,  1780,  -149,  1780,  -149,  -149,
       0,  1780,  -149,  -149,  1780,  1780,  -149,   288,   523,  2567,
     458,   178,   178,   583,   159,   159,   149,   149,   149,  -149,
     458,   583,   159,   159,     6,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,    95,  -149,   168,   195,  -149,   134,  2536,   199,
    -149,   147,  -149,  2361,  1780,  -149,  1844,   209,   150,    91,
    -149,  -149,    -3,   179,    15,   716,   785,  -149,    -3,    -3,
      -3,  1652,  1780,  1780,  1780,   854,   923,  -149,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
     191,   112,   193,   213,   151,   218,  -149,  2536,  -149,  -149,
     155,   197,  -149,  2536,  2536,  -149,  2221,  -149,  1911,  2150,
    2256,  2396,  -149,   109,  2536,  2536,  2431,   208,  -149,    91,
     211,  -149,     6,  1780,  1243,  -149,  -149,  -149,  -149,   202,
    2536,  -149,   205,   207,    -3,  -149,  1780,  -149,  -149,   172,
    -149,    -3,   252,  1376,  -149,   259,  1445,    35,    37,    40,
    -149,  2112,  2186,  1952,   225,  1514,   203,  1583,  1780,   104,
     105,  1652,     6,     6,  1780,  1780,  1780,  1780,  -149,  -149,
       6,     0,   -31,   170,   217,  -149,   231,  -149,   154,  1780,
       6,     6,  -149,  2536,  -149,    15,  -149,  -149,  -149,  -149,
    -149,  -149,  1652,  1780,  1780,  1652,   230,  1652,  -149,  -149,
    -149,  -149,  2536,  1652,     6,  1652,     6,  -149,  -149,   274,
    2536,  2536,  2536,  2536,   240,   241,     6,  -149,     6,  -149,
    -149,  2536,   244,   246,  -149,  -149,  1870,  1993,   264,   987,
    -149,  -149,   251,  -149,   260,   242,   296,  -149,  -149,  -149,
     249,  1780,  1780,  1652,  1780,  1652,  1652,   258,   263,   266,
    1716,  -149,  2466,  1652,  1652,  1780,   261,  -149,  -149,  2536,
    2536,  -149,  2034,  -149,  -149,  -149,  1652,  1652,  -149,  -149,
    1652,  -149,  -149,  2501,  1844,  1652,  -149,  -149,  -149,  -149,
     177,  -149,  -149
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   217,     0,   199,   198,
     221,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     8,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     3,   216,   220,     0,     0,
       0,     0,     0,   150,   152,   151,     0,     0,     0,     0,
       0,     0,     0,   156,   157,   153,   154,   155,   158,   222,
      82,    84,    93,   116,   117,    94,   118,    83,    85,    86,
      87,    88,    89,    90,    95,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   201,   119,   218,
     219,     0,    18,     0,     0,     0,     0,     0,    38,     0,
       5,     7,   203,   210,   202,     0,     0,   214,     0,     0,
     205,     0,     0,     0,   115,    96,    97,     0,     0,    81,
       0,   167,   201,     0,   160,     0,    81,     0,   159,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   195,   148,     0,   194,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   186,     0,     0,     0,     0,
     209,     0,     0,     0,     0,     0,    92,     0,    91,   165,
       0,     0,   162,   161,     0,     0,   137,   112,   110,   111,
     114,    98,    99,   105,   106,   107,   100,   101,   102,   103,
     113,   104,   108,   109,     0,   131,   171,   172,   173,   174,
     175,   176,   177,   127,   123,     0,   128,     0,    81,     0,
     120,     0,   200,    81,     0,    19,     0,     0,     0,     0,
     212,   188,     0,     0,     0,     0,     0,    54,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    24,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
       0,    78,   116,     0,     0,     0,    36,    37,    39,   184,
     185,     0,   208,   215,   132,   213,     0,   204,     0,     0,
       0,    80,   166,     0,   168,    80,     0,     0,   170,   201,
       0,   207,   186,     0,     0,   130,   129,   122,   121,    91,
     197,   193,     0,     0,     0,   211,     0,    33,    35,     0,
      31,     0,     0,     0,    41,     0,     0,     0,     0,     0,
      68,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   164,   163,
       0,     0,     0,   170,     0,   182,     0,   124,     0,     0,
       0,     0,   187,    21,    20,     0,    32,    76,    74,    40,
      72,    70,     0,     0,     0,     0,     0,     0,    71,    69,
      75,    73,    77,     0,     0,     0,     0,    25,   183,   190,
     135,   134,   133,   136,   169,   206,     0,   180,     0,   126,
     125,   196,     0,     0,    34,    64,     0,     0,    55,     0,
      79,    28,     0,    26,     0,     0,   192,   178,   179,   169,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    60,     0,     0,     0,     0,     0,    30,   181,    23,
      22,    65,     0,    67,    56,    58,     0,     0,    57,    59,
       0,    29,    27,     0,     0,     0,    61,    62,    63,   189,
       0,    66,   191
  };

  const short
  Parser::yypgoto_[] =
  {
    -149,  -149,  -149,  -149,   290,   277,  -149,  -149,  -149,  -149,
    -149,   -34,  -149,  -149,  -149,  -149,   -59,   286,  -149,  -149,
    -149,  -149,   -97,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,   -46,   -10,   -45,  -149,   100,   247,  -149,  -149,
    -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,  -149,
    -149,   182,  -149,  -149,  -149,  -149,  -149,  -149,  -149,   -86,
    -149,  -149,   157,    39,  -114,  -149,  -149,  -149,  -149,  -149,
    -149,  -149,    46,   180,  -149,  -149,  -102,   118,   401,    23,
     254,   -33,  -149,  -148,   -27,    53,   126,   198,    10,    -4,
    -149,  -149
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    23,    24,    25,    26,    27,    28,    29,
      30,   308,   309,    31,    32,    33,   313,   314,   248,   249,
     250,   420,   421,   251,   252,   253,   254,   255,   256,   257,
     258,   259,   118,   152,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,   120,   121,   287,   205,   206,   207,   208,   209,   210,
     211,   270,   271,   228,   406,   427,   154,   155,    87,    88,
     103,   109,   290,   104,   110,   231,   106,   107,   108,     6,
      11,    12
  };

  const short
  Parser::yytable_[] =
  {
      59,    36,   115,   116,   125,   153,   127,   111,   230,   113,
       5,   105,   230,   227,    34,   263,   307,     8,     7,     8,
       8,   168,     1,    35,   171,     8,     8,   386,    13,   387,
      36,   112,     8,    34,     8,     8,   114,     8,    92,   119,
     126,    37,   173,   233,    98,    89,     2,   265,   266,     8,
      91,   269,   272,   204,   175,   362,   291,   363,   146,   169,
     364,     2,   172,     2,     2,    43,    44,    45,     2,     2,
     150,    90,   148,    47,    48,   128,    49,   183,    50,     9,
     172,     9,     9,    55,   305,   184,    52,     9,     9,   186,
     288,   147,   172,   169,     9,   172,     9,     9,   172,     9,
     147,   158,   217,   221,    36,    53,    54,    55,    56,    57,
      58,     9,   225,   162,   260,   159,   160,   163,   226,   187,
     188,   189,   190,   191,   192,   193,   194,   195,   196,   197,
     198,   199,   200,   201,   202,   203,   179,   161,   218,   218,
     153,   223,   105,   165,   166,   277,   180,   167,   164,   150,
     373,   375,   177,   267,   292,   156,   230,   273,   274,   148,
     293,   276,   181,   278,   279,   280,   232,   281,   150,   212,
     232,   284,   374,   376,   285,   286,   157,   316,   343,   -93,
     212,   176,   296,   224,   212,   212,   325,   327,   212,   212,
     260,   260,   184,   385,   182,   298,   260,   234,   303,   330,
     260,   260,   390,   133,   134,   184,   318,   319,   304,   304,
     149,   105,   184,   141,   300,   294,   332,   150,   378,   379,
     138,   139,   140,   141,   354,   306,   384,   212,    36,   452,
     355,  -184,   321,   322,   323,   226,   392,   393,  -184,   138,
     139,   140,   141,   295,   311,    -2,    14,   297,   348,    15,
      16,    17,    18,    19,    20,    21,    22,   302,   147,   261,
     402,   329,   404,   328,   331,   333,   340,   357,   260,   341,
     349,   260,   409,   350,   410,   351,   360,   368,   370,   389,
     260,   399,   260,   345,   218,   388,   260,   405,   407,   408,
     411,   416,   412,   425,     2,    14,   353,   423,    15,    16,
      17,    18,    19,    20,    21,    22,   424,    36,   426,   428,
     435,   101,   444,   100,   232,   212,   436,   260,   372,   437,
     260,   394,   260,   439,   380,   381,   382,   383,   260,   213,
     260,   342,   133,   134,   135,   261,   261,   282,   344,   391,
     264,   261,   450,     2,   301,   261,   261,   136,   137,   138,
     139,   140,   141,   396,   397,   212,   212,   352,   153,   143,
     144,   145,   170,   212,   317,   311,     0,   275,   260,     0,
     260,   260,     0,   212,   212,     0,     0,     0,   260,   260,
       0,    15,    16,    17,    18,    19,    20,    21,    22,   422,
       0,   260,   260,     0,     0,   260,     0,   212,     0,   212,
     260,   429,   430,    10,   432,     0,   262,     0,     0,   212,
     422,   212,     0,   261,     0,   443,   261,    93,    94,    95,
      96,    97,     0,    99,     0,   261,     2,   261,     0,     0,
       0,   261,     0,     0,     0,     0,     0,     0,     0,   102,
     102,   102,     0,   102,     0,   247,     0,     0,     0,     0,
     122,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   261,     0,     0,   261,     0,   261,     0,     0,
       0,     0,     0,   261,     0,   261,     0,     0,     0,     0,
       0,     0,   262,   262,     0,     0,     0,     0,   262,     0,
       0,     0,   262,   262,     0,     0,     0,   129,   130,   131,
       0,     0,   133,   134,   135,     0,     0,     0,     0,   102,
       0,     0,     0,   261,     0,   261,   261,   136,   137,   138,
     139,   140,   141,   261,   261,     0,     0,   320,     0,   143,
     144,   145,     0,     0,     0,     0,   261,   261,     0,     0,
     261,     0,     0,     0,     0,   261,     0,     0,   214,     0,
       0,   222,   122,     0,     0,     0,     0,   229,     0,     0,
     262,   229,   129,   262,   131,   268,     0,   133,   134,   135,
     102,     0,   262,   102,   262,     0,     0,     0,   262,     0,
       0,   283,   136,   137,   138,   139,   140,   141,     0,     0,
       0,     0,     0,     0,   143,   144,   145,     0,     0,   359,
       0,     0,   359,     0,     0,   289,     0,     0,     0,   262,
       0,   359,   262,   359,   262,     0,     0,   377,     0,     0,
     262,     0,   262,     0,     0,     0,     0,   133,   134,     0,
       0,     0,     0,   229,     0,   310,     0,     0,     0,   102,
     102,   102,   136,   137,   138,   139,   140,   141,   395,     0,
       0,   398,     0,   400,     0,   144,   145,     0,     0,   401,
     262,   403,   262,   262,     0,     0,     0,     0,     0,     0,
     262,   262,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   262,   262,     0,     0,   262,     0,     0,
       0,     0,   262,     0,     0,     0,     0,     0,     0,   431,
       0,   433,   434,     0,     0,   229,     0,     0,     0,   441,
     442,     0,   356,     0,     0,     0,     0,   312,     0,     0,
       0,     0,   446,   447,     0,     0,   448,     0,     0,     0,
     235,   451,   236,     0,   237,   238,     8,   239,   240,   241,
       0,   242,   229,     0,   243,     0,     0,     0,     0,     0,
       0,   244,    43,    44,    45,     0,   310,     0,     0,     0,
      47,    48,     0,    49,     0,    50,     0,   245,     0,     0,
       0,     0,     0,    52,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   315,     0,     0,     0,
     246,     0,    53,    54,    55,    56,    57,    58,     9,   235,
       0,   236,     0,   237,   238,     8,   239,   240,   241,     0,
     242,     0,     0,   243,     0,     0,     0,     0,     0,     0,
     244,    43,    44,    45,     0,     0,     0,     0,     0,    47,
      48,     0,    49,     0,    50,     0,   245,     0,     0,     0,
       0,     0,    52,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   324,     0,     0,     0,   246,
       0,    53,    54,    55,    56,    57,    58,     9,   235,     0,
     236,     0,   237,   238,     8,   239,   240,   241,     0,   242,
       0,     0,   243,     0,     0,     0,     0,     0,     0,   244,
      43,    44,    45,     0,     0,     0,     0,     0,    47,    48,
       0,    49,     0,    50,     0,   245,     0,     0,     0,     0,
       0,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   326,     0,     0,     0,   246,     0,
      53,    54,    55,    56,    57,    58,     9,   235,     0,   236,
       0,   237,   238,     8,   239,   240,   241,     0,   242,     0,
       0,   243,     0,     0,     0,     0,     0,     0,   244,    43,
      44,    45,     0,     0,     0,     0,     0,    47,    48,     0,
      49,     0,    50,     0,   245,     0,     0,     0,     0,     0,
      52,     0,     0,     0,     0,     0,     0,     0,   417,     0,
       0,     0,     0,     0,     0,     0,     0,   246,     0,    53,
      54,    55,    56,    57,    58,     9,    38,     8,    39,    40,
       0,     0,    41,     0,     0,     0,     0,   418,     0,    42,
       0,     0,     0,    43,    44,    45,     0,     0,     0,     0,
      46,    47,    48,     0,    49,     0,    50,     0,     0,     0,
       0,     0,   419,    51,    52,     0,     0,     0,     0,     0,
       0,     0,   123,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    53,    54,    55,    56,    57,    58,     9,
      38,     8,    39,    40,     0,     0,    41,     0,     0,     0,
       0,     0,     0,    42,     0,     0,     0,    43,    44,    45,
       0,     0,     0,     0,    46,    47,    48,     0,    49,     0,
      50,   124,     0,     0,     0,     0,     0,    51,    52,     0,
       0,     0,     0,     0,     0,     0,   215,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    53,    54,    55,
      56,    57,    58,     9,    38,     8,    39,    40,     0,     0,
      41,     0,     0,     0,     0,     0,     0,    42,     0,     0,
       0,    43,    44,    45,     0,     0,     0,     0,    46,    47,
      48,     0,    49,   216,    50,     0,     0,     0,     0,     0,
       0,    51,    52,     0,     0,     0,     0,     0,     0,     0,
     219,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    53,    54,    55,    56,    57,    58,     9,    38,     8,
      39,    40,     0,     0,    41,     0,     0,     0,     0,     0,
       0,    42,     0,     0,     0,    43,    44,    45,     0,     0,
       0,     0,    46,    47,    48,     0,    49,   220,    50,     0,
       0,     0,     0,     0,     0,    51,    52,     0,     0,     0,
       0,     0,     0,     0,   346,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    53,    54,    55,    56,    57,
      58,     9,    38,     8,    39,    40,     0,     0,    41,     0,
       0,     0,     0,     0,     0,    42,     0,     0,     0,    43,
      44,    45,     0,     0,     0,     0,    46,    47,    48,     0,
      49,   347,    50,     0,     0,     0,     0,     0,     0,    51,
      52,     0,     0,     0,     0,     0,     0,     0,   117,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
      54,    55,    56,    57,    58,     9,    38,     8,    39,    40,
       0,     0,    41,     0,     0,     0,     0,     0,     0,    42,
       0,     0,     0,    43,    44,    45,     0,     0,     0,     0,
      46,    47,    48,     0,    49,     0,    50,     0,     0,     0,
       0,     0,     0,    51,    52,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    53,    54,    55,    56,    57,    58,     9,
     235,   358,   236,     0,   237,   238,     8,   239,   240,   241,
       0,   242,     0,     0,   243,     0,     0,     0,     0,     0,
       0,   244,    43,    44,    45,     0,     0,     0,     0,     0,
      47,    48,     0,    49,     0,    50,     0,   245,     0,     0,
       0,     0,     0,    52,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     246,     0,    53,    54,    55,    56,    57,    58,     9,   235,
       0,   236,   361,   237,   238,     8,   239,   240,   241,     0,
     242,     0,     0,   243,     0,     0,     0,     0,     0,     0,
     244,    43,    44,    45,     0,     0,     0,     0,     0,    47,
      48,     0,    49,     0,    50,     0,   245,     0,     0,     0,
       0,     0,    52,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   246,
       0,    53,    54,    55,    56,    57,    58,     9,   235,     0,
     236,     0,   237,   238,     8,   239,   240,   241,     0,   242,
       0,     0,   243,     0,     0,     0,     0,     0,     0,   244,
      43,    44,    45,     0,     0,     0,     0,     0,    47,    48,
       0,    49,     0,    50,     0,   245,   369,     0,     0,     0,
       0,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   246,     0,
      53,    54,    55,    56,    57,    58,     9,   235,     0,   236,
       0,   237,   238,     8,   239,   240,   241,     0,   242,     0,
       0,   243,     0,     0,     0,     0,     0,     0,   244,    43,
      44,    45,     0,     0,     0,     0,     0,    47,    48,     0,
      49,     0,    50,     0,   245,     0,     0,     0,     0,     0,
      52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   246,   371,    53,
      54,    55,    56,    57,    58,     9,   235,     0,   236,     0,
     237,   238,     8,   239,   240,   241,     0,   242,     0,     0,
     243,     0,     0,     0,     0,     0,     0,   244,    43,    44,
      45,     0,     0,     0,     0,     0,    47,    48,     0,    49,
       0,    50,     0,   245,     0,     0,     0,     0,     0,    52,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   246,     0,    53,    54,
      55,    56,    57,    58,     9,    38,     8,    39,    40,     0,
       0,    41,     0,     0,     0,     0,   418,     0,    42,     0,
       0,     0,    43,    44,    45,     0,     0,     0,     0,    46,
      47,    48,     0,    49,     0,    50,     0,     0,   438,     0,
       0,   419,    51,    52,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    53,    54,    55,    56,    57,    58,     9,    38,
       8,    39,    40,     0,     0,    41,     0,     0,     0,     0,
       0,     0,    42,     0,     0,     0,    43,    44,    45,     0,
       0,     0,     0,    46,    47,    48,     0,    49,     0,    50,
       0,     0,     0,     0,     0,     0,    51,    52,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    53,    54,    55,    56,
      57,    58,     9,    38,     8,    39,    40,     0,     0,    41,
       0,     0,     0,     0,     0,     0,    42,     0,     0,     0,
      43,    44,    45,     0,     0,     0,     0,    46,    47,    48,
       0,   151,     0,    50,   413,     0,     0,     0,     0,     0,
      51,    52,     0,   414,     0,     0,     0,     0,     0,   129,
     130,   131,   132,     0,   133,   134,   135,     0,     0,     0,
      53,    54,    55,    56,    57,    58,     9,     0,     0,   136,
     137,   138,   139,   140,   141,   335,     0,     0,     0,   142,
       0,   143,   144,   145,     0,     0,     0,     0,     0,     0,
     129,   130,   131,   132,     0,   133,   134,   135,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     136,   137,   138,   139,   140,   141,   367,     0,     0,     0,
     142,     0,   143,   144,   145,     0,     0,     0,     0,     0,
       0,   129,   130,   131,   132,     0,   133,   134,   135,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   136,   137,   138,   139,   140,   141,   415,     0,     0,
       0,   142,     0,   143,   144,   145,     0,     0,     0,     0,
       0,     0,   129,   130,   131,   132,     0,   133,   134,   135,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   136,   137,   138,   139,   140,   141,   445,     0,
       0,     0,   142,     0,   143,   144,   145,     0,     0,     0,
       0,     0,     0,   129,   130,   131,   132,     0,   133,   134,
     135,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   136,   137,   138,   139,   140,   141,   174,
       0,     0,     0,   142,     0,   143,   144,   145,     0,     0,
       0,     0,   129,   130,   131,   132,     0,   133,   134,   135,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   136,   137,   138,   139,   140,   141,   365,     0,
       0,     0,   142,     0,   143,   144,   145,     0,     0,     0,
       0,   129,   130,   131,   132,     0,   133,   134,   135,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   136,   137,   138,   139,   140,   141,   336,     0,     0,
       0,   142,     0,   143,   144,   145,     0,     0,     0,   129,
     130,   131,   132,     0,   133,   134,   135,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   136,
     137,   138,   139,   140,   141,   366,     0,     0,     0,   142,
       0,   143,   144,   145,     0,   129,   130,   131,   132,     0,
     133,   134,   135,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   136,   137,   138,   139,   140,
     141,     0,   334,     0,     0,   142,     0,   143,   144,   145,
     129,   130,   131,   132,     0,   133,   134,   135,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     136,   137,   138,   139,   140,   141,     0,     0,     0,   337,
     142,     0,   143,   144,   145,   129,   130,   131,   132,     0,
     133,   134,   135,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   136,   137,   138,   139,   140,
     141,     0,     0,     0,     0,   142,     0,   143,   144,   145,
     129,   130,   131,   132,     0,   133,   134,   135,     0,   178,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     136,   137,   138,   139,   140,   141,     0,     0,     0,     0,
     142,     0,   143,   144,   145,   129,   130,   131,   132,     0,
     133,   134,   135,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   136,   137,   138,   139,   140,
     141,     0,   185,     0,     0,   142,     0,   143,   144,   145,
     129,   130,   131,   132,     0,   133,   134,   135,     0,   299,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     136,   137,   138,   139,   140,   141,     0,     0,     0,     0,
     142,     0,   143,   144,   145,   129,   130,   131,   132,     0,
     133,   134,   135,     0,   338,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   136,   137,   138,   139,   140,
     141,     0,     0,     0,     0,   142,     0,   143,   144,   145,
     129,   130,   131,   132,     0,   133,   134,   135,     0,     0,
       0,   339,     0,     0,     0,     0,     0,     0,     0,     0,
     136,   137,   138,   139,   140,   141,     0,     0,     0,     0,
     142,     0,   143,   144,   145,   129,   130,   131,   132,     0,
     133,   134,   135,     0,     0,     0,     0,     0,     0,   440,
       0,     0,     0,     0,     0,   136,   137,   138,   139,   140,
     141,     0,     0,     0,     0,   142,     0,   143,   144,   145,
     129,   130,   131,   132,     0,   133,   134,   135,     0,     0,
       0,     0,     0,   449,     0,     0,     0,     0,     0,     0,
     136,   137,   138,   139,   140,   141,     0,     0,     0,     0,
     142,     0,   143,   144,   145,   129,   130,   131,   132,     0,
     133,   134,   135,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   136,   137,   138,   139,   140,
     141,     0,     0,     0,     0,   142,   129,   143,   144,   145,
       0,   133,   134,   135,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   136,   137,   138,   139,
     140,   141,     0,     0,     0,     0,     0,     0,   143,   144,
     145
  };

  const short
  Parser::yycheck_[] =
  {
      10,     5,    47,    48,    50,    91,    51,    40,   156,    42,
       0,    38,   160,     1,     4,     1,     1,    20,     1,    20,
      20,    20,     3,     3,    20,    20,    20,    58,     0,    60,
      34,    41,    20,    23,    20,    20,    46,    20,    15,    49,
      50,    50,    20,   157,    21,    50,    49,   161,   162,    20,
      51,   165,   166,    47,    20,    20,   204,    20,    34,    58,
      20,    49,    58,    49,    49,    36,    37,    38,    49,    49,
      54,    50,    47,    44,    45,    52,    47,    50,    49,    82,
      58,    82,    82,    78,   232,    58,    57,    82,    82,    56,
     204,    67,    58,    58,    82,    58,    82,    82,    58,    82,
      67,    46,   148,   149,   108,    76,    77,    78,    79,    80,
      81,    82,    52,    46,   159,    46,    47,    46,    58,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,    48,    68,   148,   149,
     226,   151,   169,    53,    53,   172,    58,    46,    34,    54,
      46,    46,    58,   163,    59,    47,   304,   167,   168,    47,
      65,   171,    53,   173,   174,   175,   156,   177,    54,   146,
     160,   181,    68,    68,   184,   185,    68,   236,   292,    67,
     157,    48,    48,    68,   161,   162,   245,   246,   165,   166,
     235,   236,    58,   341,    50,    48,   241,    51,    48,    48,
     245,   246,    48,    44,    45,    58,   239,   240,    58,    58,
      47,   238,    58,    64,   224,    47,    61,    54,   332,   333,
      61,    62,    63,    64,    52,    46,   340,   204,   232,    52,
      58,    61,   242,   243,   244,    58,   350,   351,    68,    61,
      62,    63,    64,    48,   234,     0,     1,    48,   294,     4,
       5,     6,     7,     8,     9,    10,    11,    48,    67,   159,
     374,    48,   376,    70,    46,    68,    58,    15,   313,    58,
      68,   316,   386,    68,   388,    68,    17,    52,    75,    48,
     325,    51,   327,   293,   294,    68,   331,    13,    48,    48,
      46,    27,    46,    51,    49,     1,   306,    46,     4,     5,
       6,     7,     8,     9,    10,    11,    46,   311,    12,    60,
      52,    34,    51,    23,   304,   292,    53,   362,   328,    53,
     365,   355,   367,   420,   334,   335,   336,   337,   373,   147,
     375,   292,    44,    45,    46,   235,   236,   180,   292,   349,
     160,   241,   444,    49,   226,   245,   246,    59,    60,    61,
      62,    63,    64,   363,   364,   332,   333,   304,   444,    71,
      72,    73,   108,   340,   238,   355,    -1,   169,   413,    -1,
     415,   416,    -1,   350,   351,    -1,    -1,    -1,   423,   424,
      -1,     4,     5,     6,     7,     8,     9,    10,    11,   399,
      -1,   436,   437,    -1,    -1,   440,    -1,   374,    -1,   376,
     445,   411,   412,     2,   414,    -1,   159,    -1,    -1,   386,
     420,   388,    -1,   313,    -1,   425,   316,    16,    17,    18,
      19,    20,    -1,    22,    -1,   325,    49,   327,    -1,    -1,
      -1,   331,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,
      39,    40,    -1,    42,    -1,   159,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   362,    -1,    -1,   365,    -1,   367,    -1,    -1,
      -1,    -1,    -1,   373,    -1,   375,    -1,    -1,    -1,    -1,
      -1,    -1,   235,   236,    -1,    -1,    -1,    -1,   241,    -1,
      -1,    -1,   245,   246,    -1,    -1,    -1,    39,    40,    41,
      -1,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,   108,
      -1,    -1,    -1,   413,    -1,   415,   416,    59,    60,    61,
      62,    63,    64,   423,   424,    -1,    -1,   241,    -1,    71,
      72,    73,    -1,    -1,    -1,    -1,   436,   437,    -1,    -1,
     440,    -1,    -1,    -1,    -1,   445,    -1,    -1,   147,    -1,
      -1,   150,   151,    -1,    -1,    -1,    -1,   156,    -1,    -1,
     313,   160,    39,   316,    41,   164,    -1,    44,    45,    46,
     169,    -1,   325,   172,   327,    -1,    -1,    -1,   331,    -1,
      -1,   180,    59,    60,    61,    62,    63,    64,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    -1,    -1,   313,
      -1,    -1,   316,    -1,    -1,   204,    -1,    -1,    -1,   362,
      -1,   325,   365,   327,   367,    -1,    -1,   331,    -1,    -1,
     373,    -1,   375,    -1,    -1,    -1,    -1,    44,    45,    -1,
      -1,    -1,    -1,   232,    -1,   234,    -1,    -1,    -1,   238,
     239,   240,    59,    60,    61,    62,    63,    64,   362,    -1,
      -1,   365,    -1,   367,    -1,    72,    73,    -1,    -1,   373,
     413,   375,   415,   416,    -1,    -1,    -1,    -1,    -1,    -1,
     423,   424,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   436,   437,    -1,    -1,   440,    -1,    -1,
      -1,    -1,   445,    -1,    -1,    -1,    -1,    -1,    -1,   413,
      -1,   415,   416,    -1,    -1,   304,    -1,    -1,    -1,   423,
     424,    -1,   311,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,   436,   437,    -1,    -1,   440,    -1,    -1,    -1,
      14,   445,    16,    -1,    18,    19,    20,    21,    22,    23,
      -1,    25,   341,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    -1,   355,    -1,    -1,    -1,
      44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    79,    80,    81,    82,    14,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    44,
      45,    -1,    47,    -1,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    14,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    -1,    25,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    44,    45,
      -1,    47,    -1,    49,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    74,    -1,
      76,    77,    78,    79,    80,    81,    82,    14,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    -1,    25,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,
      47,    -1,    49,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    76,
      77,    78,    79,    80,    81,    82,    19,    20,    21,    22,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    30,    -1,    32,
      -1,    -1,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      19,    20,    21,    22,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,    38,
      -1,    -1,    -1,    -1,    43,    44,    45,    -1,    47,    -1,
      49,    50,    -1,    -1,    -1,    -1,    -1,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,    19,    20,    21,    22,    -1,    -1,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,
      -1,    36,    37,    38,    -1,    -1,    -1,    -1,    43,    44,
      45,    -1,    47,    48,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    77,    78,    79,    80,    81,    82,    19,    20,
      21,    22,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    32,    -1,    -1,    -1,    36,    37,    38,    -1,    -1,
      -1,    -1,    43,    44,    45,    -1,    47,    48,    49,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,    80,
      81,    82,    19,    20,    21,    22,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    36,
      37,    38,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,
      47,    48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    81,    82,    19,    20,    21,    22,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      14,    15,    16,    -1,    18,    19,    20,    21,    22,    23,
      -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    79,    80,    81,    82,    14,
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    44,
      45,    -1,    47,    -1,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
      -1,    76,    77,    78,    79,    80,    81,    82,    14,    -1,
      16,    -1,    18,    19,    20,    21,    22,    23,    -1,    25,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    -1,    -1,    -1,    -1,    -1,    44,    45,
      -1,    47,    -1,    49,    -1,    51,    52,    -1,    -1,    -1,
      -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,
      76,    77,    78,    79,    80,    81,    82,    14,    -1,    16,
      -1,    18,    19,    20,    21,    22,    23,    -1,    25,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,
      47,    -1,    49,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
      77,    78,    79,    80,    81,    82,    14,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    -1,    25,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    47,
      -1,    49,    -1,    51,    -1,    -1,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    76,    77,
      78,    79,    80,    81,    82,    19,    20,    21,    22,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    30,    -1,    32,    -1,
      -1,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,    43,
      44,    45,    -1,    47,    -1,    49,    -1,    -1,    52,    -1,
      -1,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    81,    82,    19,
      20,    21,    22,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    47,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    81,    82,    19,    20,    21,    22,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      36,    37,    38,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    47,    -1,    49,    24,    -1,    -1,    -1,    -1,    -1,
      56,    57,    -1,    33,    -1,    -1,    -1,    -1,    -1,    39,
      40,    41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,
      76,    77,    78,    79,    80,    81,    82,    -1,    -1,    59,
      60,    61,    62,    63,    64,    24,    -1,    -1,    -1,    69,
      -1,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,    -1,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    24,    -1,    -1,    -1,
      69,    -1,    71,    72,    73,    -1,    -1,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    -1,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    60,    61,    62,    63,    64,    24,    -1,    -1,
      -1,    69,    -1,    71,    72,    73,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    40,    41,    42,    -1,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    60,    61,    62,    63,    64,    24,    -1,
      -1,    -1,    69,    -1,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    26,
      -1,    -1,    -1,    69,    -1,    71,    72,    73,    -1,    -1,
      -1,    -1,    39,    40,    41,    42,    -1,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    60,    61,    62,    63,    64,    26,    -1,
      -1,    -1,    69,    -1,    71,    72,    73,    -1,    -1,    -1,
      -1,    39,    40,    41,    42,    -1,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    60,    61,    62,    63,    64,    27,    -1,    -1,
      -1,    69,    -1,    71,    72,    73,    -1,    -1,    -1,    39,
      40,    41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    29,    -1,    -1,    -1,    69,
      -1,    71,    72,    73,    -1,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    31,    -1,    -1,    69,    -1,    71,    72,    73,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    33,
      69,    -1,    71,    72,    73,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      69,    -1,    71,    72,    73,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    66,    -1,    -1,    69,    -1,    71,    72,    73,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      69,    -1,    71,    72,    73,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      69,    -1,    71,    72,    73,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      69,    -1,    71,    72,    73,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    69,    39,    71,    72,    73,
      -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    49,    89,    90,   176,   177,     1,    20,    82,
     166,   178,   179,     0,     1,     4,     5,     6,     7,     8,
       9,    10,    11,    91,    92,    93,    94,    95,    96,    97,
      98,   101,   102,   103,   176,     3,   177,    50,    19,    21,
      22,    25,    32,    36,    37,    38,    43,    44,    45,    47,
      49,    56,    57,    76,    77,    78,    79,    80,    81,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   166,   167,    50,
      50,    51,   167,   166,   166,   166,   166,   166,   167,   166,
      92,    93,   166,   168,   171,   172,   174,   175,   176,   169,
     172,   169,   121,   169,   121,   122,   122,     1,   120,   121,
     149,   150,   166,     1,    50,   120,   121,   122,   167,    39,
      40,    41,    42,    44,    45,    46,    59,    60,    61,    62,
      63,    64,    69,    71,    72,    73,    34,    67,    47,    47,
      54,    47,   121,   147,   164,   165,    47,    68,    46,    46,
      47,    68,    46,    46,    34,    53,    53,    46,    20,    58,
     168,    20,    58,    20,    26,    20,    48,    58,    48,    48,
      58,    53,    50,    50,    58,    66,    56,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,    47,   152,   153,   154,   155,   156,
     157,   158,   167,   139,   166,     1,    48,   120,   121,     1,
      48,   120,   166,   121,    68,    52,    58,     1,   161,   166,
     171,   173,   176,   152,    51,    14,    16,    18,    19,    21,
      22,    23,    25,    28,    35,    51,    74,   105,   106,   107,
     108,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     122,   124,   125,     1,   161,   152,   152,   121,   166,   152,
     159,   160,   152,   121,   121,   175,   121,   172,   121,   121,
     121,   121,   150,   166,   121,   121,   121,   151,   152,   166,
     170,   171,    59,    65,    47,    48,    48,    48,    48,    48,
     121,   165,    48,    48,    58,   171,    46,     1,    99,   100,
     166,   176,     1,   104,   105,     1,   104,   174,   169,   169,
     105,   121,   121,   121,     1,   104,     1,   104,    70,    48,
      48,    46,    61,    68,    31,    24,    27,    33,    48,    50,
      58,    58,   151,   152,   160,   121,     1,    48,   120,    68,
      68,    68,   173,   121,    52,    58,   166,    15,    15,   105,
      17,    17,    20,    20,    20,    26,    29,    24,    52,    52,
      75,    75,   121,    46,    68,    46,    68,   105,   152,   152,
     121,   121,   121,   121,   152,   171,    58,    60,    68,    48,
      48,   121,   152,   152,    99,   105,   121,   121,   105,    51,
     105,   105,   152,   105,   152,    13,   162,    48,    48,   152,
     152,    46,    46,    24,    33,    24,    27,     1,    30,    55,
     109,   110,   121,    46,    46,    51,    12,   163,    60,   121,
     121,   105,   121,   105,   105,    52,    53,    53,    52,   110,
      53,   105,   105,   121,    51,    24,   105,   105,   105,    52,
     164,   105,    52
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    88,    89,    90,    90,    91,    91,    92,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    94,    94,
      95,    96,    96,    96,    97,    97,    97,    97,    97,    97,
      98,    99,    99,    99,   100,   100,   101,   102,   103,   103,
     104,   104,   105,   105,   105,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   106,   107,   107,   108,   108,   109,
     109,   110,   110,   110,   111,   112,   112,   113,   114,   115,
     115,   115,   115,   116,   116,   116,   116,   117,   118,   119,
     120,   120,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   122,   122,   122,   122,   122,   122,   122,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   124,   124,   124,   125,
     125,   125,   125,   126,   126,   126,   126,   127,   128,   128,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   136,
     136,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     137,   138,   138,   139,   140,   141,   142,   142,   143,   144,
     145,   145,   145,   146,   147,   148,   149,   149,   150,   151,
     151,   152,   152,   152,   152,   152,   152,   153,   154,   155,
     156,   157,   158,   159,   159,   160,   160,   161,   161,   162,
     162,   163,   163,   164,   164,   165,   165,   165,   166,   166,
     167,   167,   168,   168,   169,   169,   170,   170,   171,   172,
     172,   173,   173,   174,   174,   175,   176,   176,   177,   177,
     177,   178,   179
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     4,
       6,     6,     9,     9,     4,     6,     7,     9,     7,     9,
       8,     1,     2,     1,     3,     1,     4,     4,     2,     4,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     4,     6,     6,     6,     2,
       1,     3,     3,     3,     4,     6,     8,     6,     2,     3,
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
       1,     2,     1,     3,     1,     3,     2,     1,     3,     3,
       3,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"using\"",
  "\"invariant\"", "\"import\"", "\"function\"", "\"initially\"",
  "\"defined\"", "\"seq\"", "\"endseq\"", "\"par\"", "\"endpar\"",
  "\"skip\"", "\"let\"", "\"in\"", "\"forall\"", "\"choose\"",
  "\"iterate\"", "\"do\"", "\"if\"", "\"then\"", "\"else\"", "\"case\"",
  "\"of\"", "\"default\"", "\"holds\"", "\"exists\"", "\"with\"", "\"as\"",
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
  "UsingDefinition", "InvariantDefinition", "ImportDefinition", "Rules",
  "Rule", "SkipRule", "ConditionalRule", "CaseRule", "CaseLabels",
  "CaseLabel", "LetRule", "ForallRule", "ChooseRule", "IterateRule",
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
  "VariableBinding", "Attributes", "Attribute", "BasicAttribute",
  "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short
  Parser::yyrline_[] =
  {
       0,   412,   412,   422,   428,   436,   442,   452,   458,   462,
     470,   474,   478,   482,   486,   490,   494,   498,   506,   510,
     518,   526,   531,   537,   545,   551,   556,   563,   569,   573,
     581,   596,   600,   606,   614,   621,   631,   639,   647,   651,
     663,   669,   679,   683,   687,   691,   695,   699,   703,   707,
     711,   715,   719,   723,   731,   739,   743,   751,   755,   763,
     769,   779,   783,   787,   795,   803,   807,   815,   823,   831,
     835,   839,   844,   853,   857,   861,   866,   875,   883,   891,
     903,   910,   920,   924,   928,   932,   936,   940,   944,   948,
     952,   960,   964,   968,   972,   976,   980,   984,   996,  1000,
    1004,  1008,  1012,  1016,  1020,  1024,  1028,  1032,  1036,  1040,
    1044,  1048,  1052,  1056,  1060,  1064,  1072,  1076,  1080,  1088,
    1093,  1100,  1106,  1114,  1119,  1126,  1132,  1140,  1148,  1155,
    1161,  1169,  1177,  1185,  1193,  1201,  1209,  1217,  1230,  1234,
    1238,  1242,  1246,  1250,  1254,  1258,  1262,  1266,  1270,  1274,
    1282,  1291,  1297,  1307,  1315,  1323,  1331,  1335,  1343,  1351,
    1359,  1366,  1372,  1380,  1389,  1400,  1409,  1416,  1425,  1437,
    1444,  1453,  1457,  1461,  1465,  1469,  1473,  1481,  1489,  1500,
    1511,  1519,  1527,  1539,  1546,  1556,  1560,  1568,  1575,  1589,
    1593,  1601,  1605,  1614,  1621,  1631,  1638,  1646,  1663,  1667,
    1676,  1683,  1695,  1699,  1708,  1715,  1725,  1732,  1742,  1751,
    1757,  1765,  1771,  1783,  1790,  1799,  1811,  1817,  1826,  1833,
    1840,  1847,  1854
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
#line 5281 "GrammarParser.cpp" // lalr1.cc:1242
#line 1860 "../../obj/src/GrammarParser.y" // lalr1.cc:1243


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
