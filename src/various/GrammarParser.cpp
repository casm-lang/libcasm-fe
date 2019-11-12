// A Bison parser, made by GNU Bison 3.4.2.

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
#line 90 "../../obj/src/GrammarParser.y"

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


#line 69 "GrammarParser.cpp"


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

#line 50 "../../obj/src/GrammarParser.y"
namespace libcasm_fe {
#line 161 "GrammarParser.cpp"


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

      case 178: // Attribute
        value.YY_MOVE_OR_COPY< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case 177: // Attributes
        value.YY_MOVE_OR_COPY< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case 179: // BasicAttribute
        value.YY_MOVE_OR_COPY< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 154: // BasicType
        value.YY_MOVE_OR_COPY< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case 116: // BlockRule
        value.YY_MOVE_OR_COPY< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case 125: // CallExpression
        value.YY_MOVE_OR_COPY< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 119: // CallRule
        value.YY_MOVE_OR_COPY< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 136: // CardinalityExpression
        value.YY_MOVE_OR_COPY< CardinalityExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 111: // CaseLabel
        value.YY_MOVE_OR_COPY< Case::Ptr > (YY_MOVE (that.value));
        break;

      case 109: // CaseRule
        value.YY_MOVE_OR_COPY< CaseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 110: // CaseLabels
        value.YY_MOVE_OR_COPY< Cases::Ptr > (YY_MOVE (that.value));
        break;

      case 133: // ChooseExpression
        value.YY_MOVE_OR_COPY< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 114: // ChooseRule
        value.YY_MOVE_OR_COPY< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 132: // ConditionalExpression
        value.YY_MOVE_OR_COPY< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 108: // ConditionalRule
        value.YY_MOVE_OR_COPY< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 163: // MaybeDefined
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

      case 126: // DirectCallExpression
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

      case 135: // ExistentialQuantifierExpression
        value.YY_MOVE_OR_COPY< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 122: // Term
      case 123: // SimpleOrClaspedTerm
      case 124: // OperatorExpression
        value.YY_MOVE_OR_COPY< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case 180: // ExpressionAttribute
        value.YY_MOVE_OR_COPY< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 121: // Terms
        value.YY_MOVE_OR_COPY< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case 159: // FixedSizedType
        value.YY_MOVE_OR_COPY< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case 113: // ForallRule
        value.YY_MOVE_OR_COPY< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 98: // FunctionDefinition
        value.YY_MOVE_OR_COPY< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 90: // Header
        value.YY_MOVE_OR_COPY< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 82: // "identifier"
      case 167: // Identifier
        value.YY_MOVE_OR_COPY< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case 168: // IdentifierPath
        value.YY_MOVE_OR_COPY< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 104: // ImportDefinition
        value.YY_MOVE_OR_COPY< ImportDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 129: // IndirectCallExpression
        value.YY_MOVE_OR_COPY< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 94: // InitDefinition
        value.YY_MOVE_OR_COPY< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 166: // Initializer
        value.YY_MOVE_OR_COPY< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case 165: // Initializers
        value.YY_MOVE_OR_COPY< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case 164: // MaybeInitially
        value.YY_MOVE_OR_COPY< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // InvariantDefinition
        value.YY_MOVE_OR_COPY< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 115: // IterateRule
        value.YY_MOVE_OR_COPY< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 131: // LetExpression
        value.YY_MOVE_OR_COPY< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 112: // LetRule
        value.YY_MOVE_OR_COPY< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case 146: // ListLiteral
        value.YY_MOVE_OR_COPY< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 137: // Literal
        value.YY_MOVE_OR_COPY< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case 128: // LiteralCallExpression
        value.YY_MOVE_OR_COPY< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 127: // MethodCallExpression
        value.YY_MOVE_OR_COPY< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 151: // Assignment
        value.YY_MOVE_OR_COPY< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 150: // Assignments
        value.YY_MOVE_OR_COPY< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case 147: // RangeLiteral
        value.YY_MOVE_OR_COPY< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 149: // RecordLiteral
        value.YY_MOVE_OR_COPY< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 156: // RecordType
        value.YY_MOVE_OR_COPY< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case 145: // ReferenceLiteral
        value.YY_MOVE_OR_COPY< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 158: // RelationType
        value.YY_MOVE_OR_COPY< RelationType::Ptr > (YY_MOVE (that.value));
        break;

      case 106: // Rule
        value.YY_MOVE_OR_COPY< Rule::Ptr > (YY_MOVE (that.value));
        break;

      case 97: // RuleDefinition
        value.YY_MOVE_OR_COPY< RuleDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 105: // Rules
        value.YY_MOVE_OR_COPY< Rules::Ptr > (YY_MOVE (that.value));
        break;

      case 117: // SequenceRule
        value.YY_MOVE_OR_COPY< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case 107: // SkipRule
        value.YY_MOVE_OR_COPY< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Specification
        value.YY_MOVE_OR_COPY< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case 157: // TemplateType
        value.YY_MOVE_OR_COPY< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case 148: // TupleLiteral
        value.YY_MOVE_OR_COPY< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 155: // TupleType
        value.YY_MOVE_OR_COPY< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case 130: // TypeCastingExpression
        value.YY_MOVE_OR_COPY< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 152: // Types
      case 160: // FunctionParameters
      case 161: // MaybeFunctionParameters
        value.YY_MOVE_OR_COPY< Types::Ptr > (YY_MOVE (that.value));
        break;

      case 138: // UndefinedLiteral
        value.YY_MOVE_OR_COPY< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 134: // UniversalQuantifierExpression
        value.YY_MOVE_OR_COPY< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 118: // UpdateRule
        value.YY_MOVE_OR_COPY< UpdateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 101: // UsingDefinition
        value.YY_MOVE_OR_COPY< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 102: // UsingPathDefinition
        value.YY_MOVE_OR_COPY< UsingPathDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 139: // BooleanLiteral
      case 140: // IntegerLiteral
      case 141: // RationalLiteral
      case 142: // DecimalLiteral
      case 143: // BinaryLiteral
      case 144: // StringLiteral
        value.YY_MOVE_OR_COPY< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 176: // VariableBinding
        value.YY_MOVE_OR_COPY< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case 175: // VariableBindings
        value.YY_MOVE_OR_COPY< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case 169: // Variable
      case 172: // TypedVariable
      case 173: // AttributedVariable
      case 174: // TypedAttributedVariable
        value.YY_MOVE_OR_COPY< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 162: // Parameters
      case 170: // AttributedVariables
      case 171: // TypedVariables
        value.YY_MOVE_OR_COPY< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 120: // WhileRule
        value.YY_MOVE_OR_COPY< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case 153: // Type
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

      case 178: // Attribute
        value.move< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case 177: // Attributes
        value.move< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case 179: // BasicAttribute
        value.move< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 154: // BasicType
        value.move< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case 116: // BlockRule
        value.move< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case 125: // CallExpression
        value.move< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 119: // CallRule
        value.move< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 136: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 111: // CaseLabel
        value.move< Case::Ptr > (YY_MOVE (that.value));
        break;

      case 109: // CaseRule
        value.move< CaseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 110: // CaseLabels
        value.move< Cases::Ptr > (YY_MOVE (that.value));
        break;

      case 133: // ChooseExpression
        value.move< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 114: // ChooseRule
        value.move< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 132: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 108: // ConditionalRule
        value.move< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 163: // MaybeDefined
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

      case 126: // DirectCallExpression
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

      case 135: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 122: // Term
      case 123: // SimpleOrClaspedTerm
      case 124: // OperatorExpression
        value.move< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case 180: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 121: // Terms
        value.move< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case 159: // FixedSizedType
        value.move< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case 113: // ForallRule
        value.move< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 98: // FunctionDefinition
        value.move< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 90: // Header
        value.move< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 82: // "identifier"
      case 167: // Identifier
        value.move< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case 168: // IdentifierPath
        value.move< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 104: // ImportDefinition
        value.move< ImportDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 129: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 94: // InitDefinition
        value.move< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 166: // Initializer
        value.move< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case 165: // Initializers
        value.move< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case 164: // MaybeInitially
        value.move< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 115: // IterateRule
        value.move< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 131: // LetExpression
        value.move< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 112: // LetRule
        value.move< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case 146: // ListLiteral
        value.move< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 137: // Literal
        value.move< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case 128: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 127: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 151: // Assignment
        value.move< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 150: // Assignments
        value.move< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case 147: // RangeLiteral
        value.move< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 149: // RecordLiteral
        value.move< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 156: // RecordType
        value.move< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case 145: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 158: // RelationType
        value.move< RelationType::Ptr > (YY_MOVE (that.value));
        break;

      case 106: // Rule
        value.move< Rule::Ptr > (YY_MOVE (that.value));
        break;

      case 97: // RuleDefinition
        value.move< RuleDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 105: // Rules
        value.move< Rules::Ptr > (YY_MOVE (that.value));
        break;

      case 117: // SequenceRule
        value.move< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case 107: // SkipRule
        value.move< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Specification
        value.move< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case 157: // TemplateType
        value.move< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case 148: // TupleLiteral
        value.move< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 155: // TupleType
        value.move< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case 130: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 152: // Types
      case 160: // FunctionParameters
      case 161: // MaybeFunctionParameters
        value.move< Types::Ptr > (YY_MOVE (that.value));
        break;

      case 138: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 134: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 118: // UpdateRule
        value.move< UpdateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 101: // UsingDefinition
        value.move< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 102: // UsingPathDefinition
        value.move< UsingPathDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 139: // BooleanLiteral
      case 140: // IntegerLiteral
      case 141: // RationalLiteral
      case 142: // DecimalLiteral
      case 143: // BinaryLiteral
      case 144: // StringLiteral
        value.move< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 176: // VariableBinding
        value.move< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case 175: // VariableBindings
        value.move< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case 169: // Variable
      case 172: // TypedVariable
      case 173: // AttributedVariable
      case 174: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 162: // Parameters
      case 170: // AttributedVariables
      case 171: // TypedVariables
        value.move< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 120: // WhileRule
        value.move< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case 153: // Type
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

      case 178: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 177: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 179: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 154: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 116: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 125: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
        break;

      case 119: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 136: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (that.value);
        break;

      case 111: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 109: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 110: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 133: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 114: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 132: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 108: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 163: // MaybeDefined
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

      case 126: // DirectCallExpression
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

      case 135: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 122: // Term
      case 123: // SimpleOrClaspedTerm
      case 124: // OperatorExpression
        value.move< Expression::Ptr > (that.value);
        break;

      case 180: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 121: // Terms
        value.move< Expressions::Ptr > (that.value);
        break;

      case 159: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 113: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 98: // FunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 90: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 82: // "identifier"
      case 167: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 168: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 104: // ImportDefinition
        value.move< ImportDefinition::Ptr > (that.value);
        break;

      case 129: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 94: // InitDefinition
        value.move< InitDefinition::Ptr > (that.value);
        break;

      case 166: // Initializer
        value.move< Initializer::Ptr > (that.value);
        break;

      case 165: // Initializers
        value.move< Initializers::Ptr > (that.value);
        break;

      case 164: // MaybeInitially
        value.move< Initially::Ptr > (that.value);
        break;

      case 103: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (that.value);
        break;

      case 115: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 131: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 112: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 146: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 137: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 128: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 127: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 151: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 150: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 147: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 149: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 156: // RecordType
        value.move< RecordType::Ptr > (that.value);
        break;

      case 145: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 158: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 106: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 97: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 105: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 117: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 107: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 89: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 157: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 148: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 155: // TupleType
        value.move< TupleType::Ptr > (that.value);
        break;

      case 130: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 152: // Types
      case 160: // FunctionParameters
      case 161: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 138: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 134: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 118: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 101: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 102: // UsingPathDefinition
        value.move< UsingPathDefinition::Ptr > (that.value);
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 139: // BooleanLiteral
      case 140: // IntegerLiteral
      case 141: // RationalLiteral
      case 142: // DecimalLiteral
      case 143: // BinaryLiteral
      case 144: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 176: // VariableBinding
        value.move< VariableBinding::Ptr > (that.value);
        break;

      case 175: // VariableBindings
        value.move< VariableBindings::Ptr > (that.value);
        break;

      case 169: // Variable
      case 172: // TypedVariable
      case 173: // AttributedVariable
      case 174: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 162: // Parameters
      case 170: // AttributedVariables
      case 171: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 120: // WhileRule
        value.move< WhileRule::Ptr > (that.value);
        break;

      case 153: // Type
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

      case 178: // Attribute
        yylhs.value.emplace< Attribute::Ptr > ();
        break;

      case 177: // Attributes
        yylhs.value.emplace< Attributes::Ptr > ();
        break;

      case 179: // BasicAttribute
        yylhs.value.emplace< BasicAttribute::Ptr > ();
        break;

      case 154: // BasicType
        yylhs.value.emplace< BasicType::Ptr > ();
        break;

      case 116: // BlockRule
        yylhs.value.emplace< BlockRule::Ptr > ();
        break;

      case 125: // CallExpression
        yylhs.value.emplace< CallExpression::Ptr > ();
        break;

      case 119: // CallRule
        yylhs.value.emplace< CallRule::Ptr > ();
        break;

      case 136: // CardinalityExpression
        yylhs.value.emplace< CardinalityExpression::Ptr > ();
        break;

      case 111: // CaseLabel
        yylhs.value.emplace< Case::Ptr > ();
        break;

      case 109: // CaseRule
        yylhs.value.emplace< CaseRule::Ptr > ();
        break;

      case 110: // CaseLabels
        yylhs.value.emplace< Cases::Ptr > ();
        break;

      case 133: // ChooseExpression
        yylhs.value.emplace< ChooseExpression::Ptr > ();
        break;

      case 114: // ChooseRule
        yylhs.value.emplace< ChooseRule::Ptr > ();
        break;

      case 132: // ConditionalExpression
        yylhs.value.emplace< ConditionalExpression::Ptr > ();
        break;

      case 108: // ConditionalRule
        yylhs.value.emplace< ConditionalRule::Ptr > ();
        break;

      case 163: // MaybeDefined
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

      case 126: // DirectCallExpression
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

      case 135: // ExistentialQuantifierExpression
        yylhs.value.emplace< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 122: // Term
      case 123: // SimpleOrClaspedTerm
      case 124: // OperatorExpression
        yylhs.value.emplace< Expression::Ptr > ();
        break;

      case 180: // ExpressionAttribute
        yylhs.value.emplace< ExpressionAttribute::Ptr > ();
        break;

      case 121: // Terms
        yylhs.value.emplace< Expressions::Ptr > ();
        break;

      case 159: // FixedSizedType
        yylhs.value.emplace< FixedSizedType::Ptr > ();
        break;

      case 113: // ForallRule
        yylhs.value.emplace< ForallRule::Ptr > ();
        break;

      case 98: // FunctionDefinition
        yylhs.value.emplace< FunctionDefinition::Ptr > ();
        break;

      case 90: // Header
        yylhs.value.emplace< HeaderDefinition::Ptr > ();
        break;

      case 82: // "identifier"
      case 167: // Identifier
        yylhs.value.emplace< Identifier::Ptr > ();
        break;

      case 168: // IdentifierPath
        yylhs.value.emplace< IdentifierPath::Ptr > ();
        break;

      case 104: // ImportDefinition
        yylhs.value.emplace< ImportDefinition::Ptr > ();
        break;

      case 129: // IndirectCallExpression
        yylhs.value.emplace< IndirectCallExpression::Ptr > ();
        break;

      case 94: // InitDefinition
        yylhs.value.emplace< InitDefinition::Ptr > ();
        break;

      case 166: // Initializer
        yylhs.value.emplace< Initializer::Ptr > ();
        break;

      case 165: // Initializers
        yylhs.value.emplace< Initializers::Ptr > ();
        break;

      case 164: // MaybeInitially
        yylhs.value.emplace< Initially::Ptr > ();
        break;

      case 103: // InvariantDefinition
        yylhs.value.emplace< InvariantDefinition::Ptr > ();
        break;

      case 115: // IterateRule
        yylhs.value.emplace< IterateRule::Ptr > ();
        break;

      case 131: // LetExpression
        yylhs.value.emplace< LetExpression::Ptr > ();
        break;

      case 112: // LetRule
        yylhs.value.emplace< LetRule::Ptr > ();
        break;

      case 146: // ListLiteral
        yylhs.value.emplace< ListLiteral::Ptr > ();
        break;

      case 137: // Literal
        yylhs.value.emplace< Literal::Ptr > ();
        break;

      case 128: // LiteralCallExpression
        yylhs.value.emplace< LiteralCallExpression::Ptr > ();
        break;

      case 127: // MethodCallExpression
        yylhs.value.emplace< MethodCallExpression::Ptr > ();
        break;

      case 151: // Assignment
        yylhs.value.emplace< NamedExpression::Ptr > ();
        break;

      case 150: // Assignments
        yylhs.value.emplace< NamedExpressions::Ptr > ();
        break;

      case 147: // RangeLiteral
        yylhs.value.emplace< RangeLiteral::Ptr > ();
        break;

      case 149: // RecordLiteral
        yylhs.value.emplace< RecordLiteral::Ptr > ();
        break;

      case 156: // RecordType
        yylhs.value.emplace< RecordType::Ptr > ();
        break;

      case 145: // ReferenceLiteral
        yylhs.value.emplace< ReferenceLiteral::Ptr > ();
        break;

      case 158: // RelationType
        yylhs.value.emplace< RelationType::Ptr > ();
        break;

      case 106: // Rule
        yylhs.value.emplace< Rule::Ptr > ();
        break;

      case 97: // RuleDefinition
        yylhs.value.emplace< RuleDefinition::Ptr > ();
        break;

      case 105: // Rules
        yylhs.value.emplace< Rules::Ptr > ();
        break;

      case 117: // SequenceRule
        yylhs.value.emplace< SequenceRule::Ptr > ();
        break;

      case 107: // SkipRule
        yylhs.value.emplace< SkipRule::Ptr > ();
        break;

      case 89: // Specification
        yylhs.value.emplace< Specification::Ptr > ();
        break;

      case 157: // TemplateType
        yylhs.value.emplace< TemplateType::Ptr > ();
        break;

      case 148: // TupleLiteral
        yylhs.value.emplace< TupleLiteral::Ptr > ();
        break;

      case 155: // TupleType
        yylhs.value.emplace< TupleType::Ptr > ();
        break;

      case 130: // TypeCastingExpression
        yylhs.value.emplace< TypeCastingExpression::Ptr > ();
        break;

      case 152: // Types
      case 160: // FunctionParameters
      case 161: // MaybeFunctionParameters
        yylhs.value.emplace< Types::Ptr > ();
        break;

      case 138: // UndefinedLiteral
        yylhs.value.emplace< UndefLiteral::Ptr > ();
        break;

      case 134: // UniversalQuantifierExpression
        yylhs.value.emplace< UniversalQuantifierExpression::Ptr > ();
        break;

      case 118: // UpdateRule
        yylhs.value.emplace< UpdateRule::Ptr > ();
        break;

      case 101: // UsingDefinition
        yylhs.value.emplace< UsingDefinition::Ptr > ();
        break;

      case 102: // UsingPathDefinition
        yylhs.value.emplace< UsingPathDefinition::Ptr > ();
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 139: // BooleanLiteral
      case 140: // IntegerLiteral
      case 141: // RationalLiteral
      case 142: // DecimalLiteral
      case 143: // BinaryLiteral
      case 144: // StringLiteral
        yylhs.value.emplace< ValueLiteral::Ptr > ();
        break;

      case 176: // VariableBinding
        yylhs.value.emplace< VariableBinding::Ptr > ();
        break;

      case 175: // VariableBindings
        yylhs.value.emplace< VariableBindings::Ptr > ();
        break;

      case 169: // Variable
      case 172: // TypedVariable
      case 173: // AttributedVariable
      case 174: // TypedAttributedVariable
        yylhs.value.emplace< VariableDefinition::Ptr > ();
        break;

      case 162: // Parameters
      case 170: // AttributedVariables
      case 171: // TypedVariables
        yylhs.value.emplace< VariableDefinitions::Ptr > ();
        break;

      case 120: // WhileRule
        yylhs.value.emplace< WhileRule::Ptr > ();
        break;

      case 153: // Type
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
#line 414 "../../obj/src/GrammarParser.y"
    {
      m_specification.setHeader( yystack_[1].value.as < HeaderDefinition::Ptr > () );
      m_specification.setDefinitions( yystack_[0].value.as < Definitions::Ptr > () );
      m_specification.setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 2202 "GrammarParser.cpp"
    break;

  case 3:
#line 424 "../../obj/src/GrammarParser.y"
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2212 "GrammarParser.cpp"
    break;

  case 4:
#line 430 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2220 "GrammarParser.cpp"
    break;

  case 5:
#line 438 "../../obj/src/GrammarParser.y"
    {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2230 "GrammarParser.cpp"
    break;

  case 6:
#line 444 "../../obj/src/GrammarParser.y"
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2240 "GrammarParser.cpp"
    break;

  case 7:
#line 454 "../../obj/src/GrammarParser.y"
    {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2250 "GrammarParser.cpp"
    break;

  case 8:
#line 460 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2258 "GrammarParser.cpp"
    break;

  case 9:
#line 464 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2266 "GrammarParser.cpp"
    break;

  case 10:
#line 472 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2274 "GrammarParser.cpp"
    break;

  case 11:
#line 476 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2282 "GrammarParser.cpp"
    break;

  case 12:
#line 480 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2290 "GrammarParser.cpp"
    break;

  case 13:
#line 484 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2298 "GrammarParser.cpp"
    break;

  case 14:
#line 488 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 2306 "GrammarParser.cpp"
    break;

  case 15:
#line 492 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 2314 "GrammarParser.cpp"
    break;

  case 16:
#line 496 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingPathDefinition::Ptr > ();
  }
#line 2322 "GrammarParser.cpp"
    break;

  case 17:
#line 500 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 2330 "GrammarParser.cpp"
    break;

  case 18:
#line 504 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 2338 "GrammarParser.cpp"
    break;

  case 19:
#line 512 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2346 "GrammarParser.cpp"
    break;

  case 20:
#line 516 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2354 "GrammarParser.cpp"
    break;

  case 21:
#line 524 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2362 "GrammarParser.cpp"
    break;

  case 22:
#line 532 "../../obj/src/GrammarParser.y"
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2371 "GrammarParser.cpp"
    break;

  case 23:
#line 537 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2381 "GrammarParser.cpp"
    break;

  case 24:
#line 543 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 2389 "GrammarParser.cpp"
    break;

  case 25:
#line 551 "../../obj/src/GrammarParser.y"
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2399 "GrammarParser.cpp"
    break;

  case 26:
#line 557 "../../obj/src/GrammarParser.y"
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2408 "GrammarParser.cpp"
    break;

  case 27:
#line 562 "../../obj/src/GrammarParser.y"
    {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
  }
#line 2419 "GrammarParser.cpp"
    break;

  case 28:
#line 569 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2429 "GrammarParser.cpp"
    break;

  case 29:
#line 575 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2437 "GrammarParser.cpp"
    break;

  case 30:
#line 579 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2445 "GrammarParser.cpp"
    break;

  case 31:
#line 587 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < FunctionDefinition::Ptr > () = Ast::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      const auto initially = yylhs.value.as < FunctionDefinition::Ptr > ()->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->updateRule()->function()->setIdentifier( IdentifierPath::fromIdentifier( yystack_[6].value.as < Identifier::Ptr > () ) );
      }
  }
#line 2460 "GrammarParser.cpp"
    break;

  case 32:
#line 602 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 2468 "GrammarParser.cpp"
    break;

  case 33:
#line 606 "../../obj/src/GrammarParser.y"
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 2478 "GrammarParser.cpp"
    break;

  case 34:
#line 612 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 2486 "GrammarParser.cpp"
    break;

  case 35:
#line 620 "../../obj/src/GrammarParser.y"
    {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2497 "GrammarParser.cpp"
    break;

  case 36:
#line 627 "../../obj/src/GrammarParser.y"
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2507 "GrammarParser.cpp"
    break;

  case 37:
#line 637 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2515 "GrammarParser.cpp"
    break;

  case 38:
#line 645 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2523 "GrammarParser.cpp"
    break;

  case 39:
#line 649 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2531 "GrammarParser.cpp"
    break;

  case 40:
#line 657 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < InvariantDefinition::Ptr > () = Ast::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2539 "GrammarParser.cpp"
    break;

  case 41:
#line 665 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2547 "GrammarParser.cpp"
    break;

  case 42:
#line 669 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 2555 "GrammarParser.cpp"
    break;

  case 43:
#line 681 "../../obj/src/GrammarParser.y"
    {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 2565 "GrammarParser.cpp"
    break;

  case 44:
#line 687 "../../obj/src/GrammarParser.y"
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 2575 "GrammarParser.cpp"
    break;

  case 45:
#line 697 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 2583 "GrammarParser.cpp"
    break;

  case 46:
#line 701 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 2591 "GrammarParser.cpp"
    break;

  case 47:
#line 705 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 2599 "GrammarParser.cpp"
    break;

  case 48:
#line 709 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 2607 "GrammarParser.cpp"
    break;

  case 49:
#line 713 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 2615 "GrammarParser.cpp"
    break;

  case 50:
#line 717 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 2623 "GrammarParser.cpp"
    break;

  case 51:
#line 721 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 2631 "GrammarParser.cpp"
    break;

  case 52:
#line 725 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 2639 "GrammarParser.cpp"
    break;

  case 53:
#line 729 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 2647 "GrammarParser.cpp"
    break;

  case 54:
#line 733 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 2655 "GrammarParser.cpp"
    break;

  case 55:
#line 737 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 2663 "GrammarParser.cpp"
    break;

  case 56:
#line 741 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 2671 "GrammarParser.cpp"
    break;

  case 57:
#line 749 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2679 "GrammarParser.cpp"
    break;

  case 58:
#line 757 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2687 "GrammarParser.cpp"
    break;

  case 59:
#line 761 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2695 "GrammarParser.cpp"
    break;

  case 60:
#line 769 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2703 "GrammarParser.cpp"
    break;

  case 61:
#line 773 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 2711 "GrammarParser.cpp"
    break;

  case 62:
#line 781 "../../obj/src/GrammarParser.y"
    {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 2721 "GrammarParser.cpp"
    break;

  case 63:
#line 787 "../../obj/src/GrammarParser.y"
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 2731 "GrammarParser.cpp"
    break;

  case 64:
#line 797 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2739 "GrammarParser.cpp"
    break;

  case 65:
#line 801 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2747 "GrammarParser.cpp"
    break;

  case 66:
#line 805 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2755 "GrammarParser.cpp"
    break;

  case 67:
#line 813 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2763 "GrammarParser.cpp"
    break;

  case 68:
#line 821 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2771 "GrammarParser.cpp"
    break;

  case 69:
#line 825 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2779 "GrammarParser.cpp"
    break;

  case 70:
#line 833 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2787 "GrammarParser.cpp"
    break;

  case 71:
#line 841 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2795 "GrammarParser.cpp"
    break;

  case 72:
#line 849 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2803 "GrammarParser.cpp"
    break;

  case 73:
#line 853 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2811 "GrammarParser.cpp"
    break;

  case 74:
#line 857 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2820 "GrammarParser.cpp"
    break;

  case 75:
#line 862 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2829 "GrammarParser.cpp"
    break;

  case 76:
#line 871 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2837 "GrammarParser.cpp"
    break;

  case 77:
#line 875 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2845 "GrammarParser.cpp"
    break;

  case 78:
#line 879 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2854 "GrammarParser.cpp"
    break;

  case 79:
#line 884 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2863 "GrammarParser.cpp"
    break;

  case 80:
#line 893 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2871 "GrammarParser.cpp"
    break;

  case 81:
#line 901 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 2879 "GrammarParser.cpp"
    break;

  case 82:
#line 909 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2887 "GrammarParser.cpp"
    break;

  case 83:
#line 921 "../../obj/src/GrammarParser.y"
    {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 2898 "GrammarParser.cpp"
    break;

  case 84:
#line 928 "../../obj/src/GrammarParser.y"
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 2908 "GrammarParser.cpp"
    break;

  case 85:
#line 938 "../../obj/src/GrammarParser.y"
    {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 2916 "GrammarParser.cpp"
    break;

  case 86:
#line 942 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 2924 "GrammarParser.cpp"
    break;

  case 87:
#line 946 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 2932 "GrammarParser.cpp"
    break;

  case 88:
#line 950 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 2940 "GrammarParser.cpp"
    break;

  case 89:
#line 954 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 2948 "GrammarParser.cpp"
    break;

  case 90:
#line 958 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 2956 "GrammarParser.cpp"
    break;

  case 91:
#line 962 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 2964 "GrammarParser.cpp"
    break;

  case 92:
#line 966 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 2972 "GrammarParser.cpp"
    break;

  case 93:
#line 970 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 2980 "GrammarParser.cpp"
    break;

  case 94:
#line 978 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< Ast::EmbracedExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2988 "GrammarParser.cpp"
    break;

  case 95:
#line 982 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 2996 "GrammarParser.cpp"
    break;

  case 96:
#line 986 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 3004 "GrammarParser.cpp"
    break;

  case 97:
#line 990 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 3012 "GrammarParser.cpp"
    break;

  case 98:
#line 994 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 3020 "GrammarParser.cpp"
    break;

  case 99:
#line 998 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3028 "GrammarParser.cpp"
    break;

  case 100:
#line 1002 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 3036 "GrammarParser.cpp"
    break;

  case 101:
#line 1014 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3044 "GrammarParser.cpp"
    break;

  case 102:
#line 1018 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 3052 "GrammarParser.cpp"
    break;

  case 103:
#line 1022 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 3060 "GrammarParser.cpp"
    break;

  case 104:
#line 1026 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 3068 "GrammarParser.cpp"
    break;

  case 105:
#line 1030 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 3076 "GrammarParser.cpp"
    break;

  case 106:
#line 1034 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 3084 "GrammarParser.cpp"
    break;

  case 107:
#line 1038 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 3092 "GrammarParser.cpp"
    break;

  case 108:
#line 1042 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 3100 "GrammarParser.cpp"
    break;

  case 109:
#line 1046 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 3108 "GrammarParser.cpp"
    break;

  case 110:
#line 1050 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 3116 "GrammarParser.cpp"
    break;

  case 111:
#line 1054 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 3124 "GrammarParser.cpp"
    break;

  case 112:
#line 1058 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 3132 "GrammarParser.cpp"
    break;

  case 113:
#line 1062 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 3140 "GrammarParser.cpp"
    break;

  case 114:
#line 1066 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 3148 "GrammarParser.cpp"
    break;

  case 115:
#line 1070 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 3156 "GrammarParser.cpp"
    break;

  case 116:
#line 1074 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3164 "GrammarParser.cpp"
    break;

  case 117:
#line 1078 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3172 "GrammarParser.cpp"
    break;

  case 118:
#line 1082 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 3180 "GrammarParser.cpp"
    break;

  case 119:
#line 1090 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 3188 "GrammarParser.cpp"
    break;

  case 120:
#line 1094 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 3196 "GrammarParser.cpp"
    break;

  case 121:
#line 1098 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 3204 "GrammarParser.cpp"
    break;

  case 122:
#line 1106 "../../obj/src/GrammarParser.y"
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > (), arguments );
  }
#line 3213 "GrammarParser.cpp"
    break;

  case 123:
#line 1111 "../../obj/src/GrammarParser.y"
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), arguments );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3224 "GrammarParser.cpp"
    break;

  case 124:
#line 1118 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3234 "GrammarParser.cpp"
    break;

  case 125:
#line 1124 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 3242 "GrammarParser.cpp"
    break;

  case 126:
#line 1132 "../../obj/src/GrammarParser.y"
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 3251 "GrammarParser.cpp"
    break;

  case 127:
#line 1137 "../../obj/src/GrammarParser.y"
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3262 "GrammarParser.cpp"
    break;

  case 128:
#line 1144 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3272 "GrammarParser.cpp"
    break;

  case 129:
#line 1150 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 3280 "GrammarParser.cpp"
    break;

  case 130:
#line 1158 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 3288 "GrammarParser.cpp"
    break;

  case 131:
#line 1166 "../../obj/src/GrammarParser.y"
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3299 "GrammarParser.cpp"
    break;

  case 132:
#line 1173 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3309 "GrammarParser.cpp"
    break;

  case 133:
#line 1179 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 3317 "GrammarParser.cpp"
    break;

  case 134:
#line 1187 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3325 "GrammarParser.cpp"
    break;

  case 135:
#line 1195 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3333 "GrammarParser.cpp"
    break;

  case 136:
#line 1203 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3341 "GrammarParser.cpp"
    break;

  case 137:
#line 1211 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3349 "GrammarParser.cpp"
    break;

  case 138:
#line 1219 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3357 "GrammarParser.cpp"
    break;

  case 139:
#line 1227 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3365 "GrammarParser.cpp"
    break;

  case 140:
#line 1235 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3373 "GrammarParser.cpp"
    break;

  case 141:
#line 1248 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 3381 "GrammarParser.cpp"
    break;

  case 142:
#line 1252 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3389 "GrammarParser.cpp"
    break;

  case 143:
#line 1256 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3397 "GrammarParser.cpp"
    break;

  case 144:
#line 1260 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3405 "GrammarParser.cpp"
    break;

  case 145:
#line 1264 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3413 "GrammarParser.cpp"
    break;

  case 146:
#line 1268 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3421 "GrammarParser.cpp"
    break;

  case 147:
#line 1272 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3429 "GrammarParser.cpp"
    break;

  case 148:
#line 1276 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 3437 "GrammarParser.cpp"
    break;

  case 149:
#line 1280 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 3445 "GrammarParser.cpp"
    break;

  case 150:
#line 1284 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 3453 "GrammarParser.cpp"
    break;

  case 151:
#line 1288 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 3461 "GrammarParser.cpp"
    break;

  case 152:
#line 1292 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 3469 "GrammarParser.cpp"
    break;

  case 153:
#line 1300 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3478 "GrammarParser.cpp"
    break;

  case 154:
#line 1309 "../../obj/src/GrammarParser.y"
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3488 "GrammarParser.cpp"
    break;

  case 155:
#line 1315 "../../obj/src/GrammarParser.y"
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3498 "GrammarParser.cpp"
    break;

  case 156:
#line 1325 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3506 "GrammarParser.cpp"
    break;

  case 157:
#line 1333 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3514 "GrammarParser.cpp"
    break;

  case 158:
#line 1341 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3522 "GrammarParser.cpp"
    break;

  case 159:
#line 1349 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3530 "GrammarParser.cpp"
    break;

  case 160:
#line 1353 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3538 "GrammarParser.cpp"
    break;

  case 161:
#line 1361 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3546 "GrammarParser.cpp"
    break;

  case 162:
#line 1369 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3554 "GrammarParser.cpp"
    break;

  case 163:
#line 1377 "../../obj/src/GrammarParser.y"
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3565 "GrammarParser.cpp"
    break;

  case 164:
#line 1384 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3575 "GrammarParser.cpp"
    break;

  case 165:
#line 1390 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 3583 "GrammarParser.cpp"
    break;

  case 166:
#line 1398 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3593 "GrammarParser.cpp"
    break;

  case 167:
#line 1407 "../../obj/src/GrammarParser.y"
    {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3606 "GrammarParser.cpp"
    break;

  case 168:
#line 1418 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3616 "GrammarParser.cpp"
    break;

  case 169:
#line 1427 "../../obj/src/GrammarParser.y"
    {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 3627 "GrammarParser.cpp"
    break;

  case 170:
#line 1434 "../../obj/src/GrammarParser.y"
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 3637 "GrammarParser.cpp"
    break;

  case 171:
#line 1443 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3645 "GrammarParser.cpp"
    break;

  case 172:
#line 1455 "../../obj/src/GrammarParser.y"
    {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3656 "GrammarParser.cpp"
    break;

  case 173:
#line 1462 "../../obj/src/GrammarParser.y"
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3666 "GrammarParser.cpp"
    break;

  case 174:
#line 1471 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 3674 "GrammarParser.cpp"
    break;

  case 175:
#line 1475 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 3682 "GrammarParser.cpp"
    break;

  case 176:
#line 1479 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 3690 "GrammarParser.cpp"
    break;

  case 177:
#line 1483 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 3698 "GrammarParser.cpp"
    break;

  case 178:
#line 1487 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 3706 "GrammarParser.cpp"
    break;

  case 179:
#line 1491 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 3714 "GrammarParser.cpp"
    break;

  case 180:
#line 1499 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3722 "GrammarParser.cpp"
    break;

  case 181:
#line 1507 "../../obj/src/GrammarParser.y"
    {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = Ast::make< TupleType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), subTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3733 "GrammarParser.cpp"
    break;

  case 182:
#line 1518 "../../obj/src/GrammarParser.y"
    {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = Ast::make< RecordType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3744 "GrammarParser.cpp"
    break;

  case 183:
#line 1529 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3752 "GrammarParser.cpp"
    break;

  case 184:
#line 1537 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3760 "GrammarParser.cpp"
    break;

  case 185:
#line 1545 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3768 "GrammarParser.cpp"
    break;

  case 186:
#line 1557 "../../obj/src/GrammarParser.y"
    {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3779 "GrammarParser.cpp"
    break;

  case 187:
#line 1564 "../../obj/src/GrammarParser.y"
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3789 "GrammarParser.cpp"
    break;

  case 188:
#line 1574 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 3797 "GrammarParser.cpp"
    break;

  case 189:
#line 1578 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 3805 "GrammarParser.cpp"
    break;

  case 190:
#line 1586 "../../obj/src/GrammarParser.y"
    {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 3816 "GrammarParser.cpp"
    break;

  case 191:
#line 1593 "../../obj/src/GrammarParser.y"
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 3826 "GrammarParser.cpp"
    break;

  case 192:
#line 1607 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3834 "GrammarParser.cpp"
    break;

  case 193:
#line 1611 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 3842 "GrammarParser.cpp"
    break;

  case 194:
#line 1619 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3850 "GrammarParser.cpp"
    break;

  case 195:
#line 1623 "../../obj/src/GrammarParser.y"
    {
      const auto initializers = Ast::make< Initializers >( yylhs.location );
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
#line 3859 "GrammarParser.cpp"
    break;

  case 196:
#line 1632 "../../obj/src/GrammarParser.y"
    {
      auto initializers = yystack_[2].value.as < Initializers::Ptr > ();
      yystack_[0].value.as < Initializer::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 3870 "GrammarParser.cpp"
    break;

  case 197:
#line 1639 "../../obj/src/GrammarParser.y"
    {
      auto initializers = Ast::make< Initializers >( yylhs.location );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 3880 "GrammarParser.cpp"
    break;

  case 198:
#line 1649 "../../obj/src/GrammarParser.y"
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3891 "GrammarParser.cpp"
    break;

  case 199:
#line 1656 "../../obj/src/GrammarParser.y"
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), arguments, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3903 "GrammarParser.cpp"
    break;

  case 200:
#line 1664 "../../obj/src/GrammarParser.y"
    {
      const auto arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto lbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto rbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, lbToken, arguments, rbToken, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3916 "GrammarParser.cpp"
    break;

  case 201:
#line 1681 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 3924 "GrammarParser.cpp"
    break;

  case 202:
#line 1685 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 3933 "GrammarParser.cpp"
    break;

  case 203:
#line 1694 "../../obj/src/GrammarParser.y"
    {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < Ast::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 3944 "GrammarParser.cpp"
    break;

  case 204:
#line 1701 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3952 "GrammarParser.cpp"
    break;

  case 205:
#line 1713 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 3960 "GrammarParser.cpp"
    break;

  case 206:
#line 1717 "../../obj/src/GrammarParser.y"
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 3969 "GrammarParser.cpp"
    break;

  case 207:
#line 1726 "../../obj/src/GrammarParser.y"
    {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 3980 "GrammarParser.cpp"
    break;

  case 208:
#line 1733 "../../obj/src/GrammarParser.y"
    {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 3990 "GrammarParser.cpp"
    break;

  case 209:
#line 1743 "../../obj/src/GrammarParser.y"
    {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4001 "GrammarParser.cpp"
    break;

  case 210:
#line 1750 "../../obj/src/GrammarParser.y"
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4011 "GrammarParser.cpp"
    break;

  case 211:
#line 1760 "../../obj/src/GrammarParser.y"
    {
      auto variable = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4020 "GrammarParser.cpp"
    break;

  case 212:
#line 1769 "../../obj/src/GrammarParser.y"
    {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4030 "GrammarParser.cpp"
    break;

  case 213:
#line 1775 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4038 "GrammarParser.cpp"
    break;

  case 214:
#line 1783 "../../obj/src/GrammarParser.y"
    {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4048 "GrammarParser.cpp"
    break;

  case 215:
#line 1789 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4056 "GrammarParser.cpp"
    break;

  case 216:
#line 1801 "../../obj/src/GrammarParser.y"
    {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4067 "GrammarParser.cpp"
    break;

  case 217:
#line 1808 "../../obj/src/GrammarParser.y"
    {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4077 "GrammarParser.cpp"
    break;

  case 218:
#line 1817 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4085 "GrammarParser.cpp"
    break;

  case 219:
#line 1829 "../../obj/src/GrammarParser.y"
    {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4095 "GrammarParser.cpp"
    break;

  case 220:
#line 1835 "../../obj/src/GrammarParser.y"
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4105 "GrammarParser.cpp"
    break;

  case 221:
#line 1844 "../../obj/src/GrammarParser.y"
    {
      auto attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4116 "GrammarParser.cpp"
    break;

  case 222:
#line 1851 "../../obj/src/GrammarParser.y"
    {
      auto attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4127 "GrammarParser.cpp"
    break;

  case 223:
#line 1858 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 4135 "GrammarParser.cpp"
    break;

  case 224:
#line 1865 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4143 "GrammarParser.cpp"
    break;

  case 225:
#line 1872 "../../obj/src/GrammarParser.y"
    {
      yylhs.value.as < ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4151 "GrammarParser.cpp"
    break;


#line 4155 "GrammarParser.cpp"

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


  const short Parser::yypact_ninf_ = -144;

  const short Parser::yytable_ninf_ = -188;

  const short
  Parser::yypact_[] =
  {
       7,  -144,     1,    59,   297,     9,  -144,   -22,  -144,  -144,
    1756,    10,    53,  -144,  -144,     3,    35,    35,    35,    35,
      35,    35,    35,   218,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,   250,  -144,  -144,  -144,     2,
       2,     2,  1756,     2,  -144,  -144,  -144,  1756,    33,    33,
    1283,  1027,    33,    35,  -144,  -144,  -144,  -144,  -144,  -144,
    2469,   -18,  -144,   102,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,   134,
    -144,  -144,  1820,    19,   -29,    17,   104,    29,    52,   137,
      18,    95,  -144,  -144,   127,  -144,  -144,   149,   -11,  -144,
       2,    28,  -144,    46,  2006,    47,  -144,  -144,  -144,   161,
     154,  2224,   115,  -144,   180,   188,  -144,    44,  2259,    32,
      19,  1756,  1756,  1756,  1756,  1756,  1756,  1756,  1756,  1756,
    1756,  1756,  1756,  1756,  1756,  1756,  1756,  1756,    14,    15,
    1091,  1155,    35,  1283,  2469,   181,    94,  -144,    13,    14,
     199,  1628,    16,    14,    14,    26,  1756,    35,    14,    14,
    1756,  1756,     2,  -144,  1756,     2,  1756,  1756,  1756,  -144,
    1756,  -144,  -144,    35,  1756,  -144,  -144,  1756,  1756,  -144,
     292,   534,  2534,  2504,   183,   183,   598,   326,   326,   198,
     198,   198,  -144,  2504,   598,   326,   326,    14,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,   125,  -144,   216,   204,  -144,
     148,  2469,   217,  -144,   152,  -144,  2294,  1756,  -144,  1820,
     220,   153,   127,  -144,  -144,     2,   223,    25,   692,   761,
    -144,     2,     2,     2,  1628,  1756,  1756,  1756,   830,   899,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,   203,    92,   196,   225,   173,   228,  -144,
    -144,  2469,  -144,  -144,   210,   208,  -144,  2469,  2469,  -144,
    2154,  -144,  1844,  2083,  2189,  2329,  -144,   180,  2469,  2469,
    2364,   221,  -144,   127,   222,  -144,    14,  1756,  1219,  -144,
    -144,  -144,  -144,   213,  2469,  -144,   214,   215,     2,  -144,
    1756,  -144,  -144,   162,  -144,     2,   263,  1352,  -144,   268,
    1421,    61,   100,   118,  -144,  2045,  2119,  1885,   237,  1490,
     234,  1559,  1756,    11,   107,  1628,    14,    14,  1756,  1756,
    1756,  1756,  -144,  -144,    14,    35,    31,   101,   242,  -144,
     248,  -144,   184,  1756,    14,    14,  -144,  2469,  -144,    25,
    -144,  -144,  -144,  -144,  -144,  -144,  1628,  1756,  1756,  1628,
     260,  1628,  -144,  -144,  -144,  -144,  2469,  1628,    14,  1628,
      14,  -144,  -144,   299,  2469,  2469,  2469,  2469,   265,   269,
      14,  -144,    14,  -144,  -144,  2469,   274,   281,  -144,  -144,
     424,  1926,   312,   963,  -144,  -144,   294,  -144,   295,   291,
     332,  -144,  -144,  -144,   285,  1756,  1756,  1628,  1756,  1628,
    1628,   296,   309,   315,  1692,  -144,  2399,  1628,  1628,  1756,
     298,  -144,  -144,  2469,  2469,  -144,  1967,  -144,  -144,  -144,
    1628,  1628,  -144,  -144,  1628,  -144,  -144,  2434,  1820,  1628,
    -144,  -144,  -144,  -144,   182,  -144,  -144
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   220,     0,   202,   201,
     224,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     8,    10,    11,    12,    13,
      14,    15,    16,    17,    18,     0,     3,   219,   223,     0,
       0,     0,     0,     0,   153,   155,   154,     0,     0,     0,
       0,     0,     0,     0,   159,   160,   156,   157,   158,   161,
     225,    85,    87,    96,   119,   120,    97,   121,    86,    88,
      89,    90,    91,    92,    93,    98,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   204,   122,
     221,   222,     0,    19,     0,     0,     0,   204,    38,     0,
      41,     0,     5,     7,   206,   213,   205,     0,     0,   217,
       0,     0,   208,     0,     0,     0,   118,    99,   100,     0,
       0,    84,     0,   170,   204,     0,   163,     0,    84,     0,
     162,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   198,   151,     0,   197,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   189,     0,
       0,     0,     0,   212,     0,     0,     0,     0,     0,    95,
       0,    94,   168,     0,     0,   165,   164,     0,     0,   140,
     115,   113,   114,   117,   101,   102,   108,   109,   110,   103,
     104,   105,   106,   116,   107,   111,   112,     0,   134,   174,
     175,   176,   177,   178,   179,   180,   130,   126,     0,   131,
       0,    84,     0,   123,     0,   203,    84,     0,    20,     0,
       0,     0,     0,   215,   191,     0,     0,     0,     0,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      25,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,     0,    81,   119,     0,     0,     0,    37,
      39,    40,    42,   187,   188,     0,   211,   218,   135,   216,
       0,   207,     0,     0,     0,    83,   169,     0,   171,    83,
       0,     0,   173,   204,     0,   210,   189,     0,     0,   133,
     132,   125,   124,    94,   200,   196,     0,     0,     0,   214,
       0,    34,    36,     0,    32,     0,     0,     0,    44,     0,
       0,     0,     0,     0,    71,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   167,   166,     0,     0,     0,   173,     0,   185,
       0,   127,     0,     0,     0,     0,   190,    22,    21,     0,
      33,    79,    77,    43,    75,    73,     0,     0,     0,     0,
       0,     0,    74,    72,    78,    76,    80,     0,     0,     0,
       0,    26,   186,   193,   138,   137,   136,   139,   172,   209,
       0,   183,     0,   129,   128,   199,     0,     0,    35,    67,
       0,     0,    58,     0,    82,    29,     0,    27,     0,     0,
     195,   181,   182,   172,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    63,     0,     0,     0,     0,
       0,    31,   184,    24,    23,    68,     0,    70,    59,    61,
       0,     0,    60,    62,     0,    30,    28,     0,     0,     0,
      64,    65,    66,   192,     0,    69,   194
  };

  const short
  Parser::yypgoto_[] =
  {
    -144,  -144,  -144,  -144,   324,   334,  -144,  -144,  -144,  -144,
    -144,    -9,  -144,  -144,  -144,  -144,  -144,   -94,   306,  -144,
    -144,  -144,  -144,   -51,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,   -50,   -10,   -45,  -144,   172,   205,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,   227,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
     -87,  -144,  -144,   197,    83,  -139,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,    85,   229,  -144,  -144,   -64,   163,   275,
      23,   284,   -35,  -144,  -143,   -28,    89,   157,   230,    27,
       8,  -144,  -144
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    23,    24,    25,    26,    27,    28,    29,
      30,   312,   313,    31,    32,    33,    34,   317,   318,   251,
     252,   253,   424,   425,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   120,   154,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,   122,   123,   291,   208,   209,   210,   211,   212,
     213,   214,   274,   275,   231,   410,   431,   156,   157,    88,
      89,   105,   111,   294,   106,   112,   234,   108,   109,   110,
       6,    11,    12
  };

  const short
  Parser::yytable_[] =
  {
      60,   127,     7,   117,   118,   155,   113,   129,   115,   171,
       1,   107,    36,    37,   230,   233,   148,   266,   158,   233,
     236,     8,     8,     8,   268,   269,   311,     5,    38,   273,
     276,    35,   114,     8,     8,     8,     8,   116,    93,   159,
     121,   128,    98,    37,   100,     8,     8,   172,   174,   149,
      35,     2,   167,     8,    92,     8,     2,   377,     2,    13,
      90,   207,     2,   160,   295,     2,   176,   178,   292,    44,
      45,    46,   152,   152,     2,   164,   130,    48,    49,   378,
      50,   366,    51,     9,     9,     9,   175,   270,   189,   390,
      53,   391,   309,    56,   186,     9,     9,     9,     9,   149,
     220,   224,   187,    91,   175,   175,   165,     9,     9,    54,
      55,    56,    57,    58,    59,     9,   263,     9,    37,   172,
     367,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   368,   150,
     221,   221,   155,   226,   107,   320,   228,   281,   168,   150,
     161,   162,   229,   379,   329,   331,   271,   347,   175,   -96,
     277,   278,  -187,   182,   280,   233,   282,   283,   284,  -187,
     285,   215,   163,   183,   288,   380,   175,   289,   290,   152,
     169,   151,   215,   166,   296,   235,   215,   215,   152,   235,
     297,   215,   215,   263,   263,   170,   300,   382,   383,   263,
     302,   307,   389,   263,   263,   388,   187,   322,   323,   179,
     187,   308,   180,   107,   358,   396,   397,   304,    -2,    14,
     359,   334,    15,    16,    17,    18,    19,    20,    21,    22,
     215,   308,   394,   184,   456,   325,   326,   327,   185,   406,
     229,   408,   187,    37,   140,   141,   142,   143,   352,   227,
     237,   413,   299,   414,    15,    16,    17,    18,    19,    20,
      21,    22,   143,   298,   315,   301,   332,     2,   306,   310,
     149,   336,   263,   333,   335,   263,   337,    10,   361,   344,
     345,   353,   354,   355,   263,   364,   263,   349,   221,   372,
     263,    94,    95,    96,    97,    99,   393,   101,    14,     2,
     357,    15,    16,    17,    18,    19,    20,    21,    22,   374,
     392,   403,   409,   411,   104,   104,   104,   412,   104,   215,
     415,   263,   376,    37,   263,   124,   263,   416,   384,   385,
     386,   387,   263,   264,   263,   235,   135,   136,   137,   420,
     427,   428,   429,   395,   430,   432,     2,   102,   439,   448,
     398,   138,   139,   140,   141,   142,   143,   400,   401,   215,
     215,   155,   440,   145,   146,   147,   265,   215,   441,   103,
     135,   136,   263,   443,   263,   263,   216,   215,   215,   346,
     286,   348,   263,   263,   454,   104,   315,   140,   141,   142,
     143,   267,   305,   426,   173,   263,   263,   356,   321,   263,
       0,   215,   279,   215,   263,   433,   434,     0,   436,     0,
     264,   264,     0,   215,   426,   215,   264,     0,     0,   447,
     264,   264,     0,     0,   217,     0,     0,   225,   124,     0,
       0,     0,     0,   232,     0,     0,     0,   232,     0,     0,
     225,     0,   272,   265,   265,     0,     0,   104,   417,   265,
     104,     0,     0,   265,   265,     0,     0,   418,   287,     0,
       0,     0,     0,   131,   132,   133,   134,   250,   135,   136,
     137,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   293,   138,   139,   140,   141,   142,   143,   264,
       0,     0,   264,   144,     0,   145,   146,   147,     0,     0,
       0,   264,     0,   264,     0,     0,     0,   264,     0,     0,
     232,     0,   314,     0,     0,     0,   104,   104,   104,     0,
       0,     0,   265,     0,     0,   265,     0,     0,     0,     0,
       0,     0,     0,     0,   265,     0,   265,     0,   264,     0,
     265,   264,     0,   264,     0,     0,     0,     0,     0,   264,
     324,   264,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   265,     0,   131,   265,   133,   265,     0,   135,   136,
     137,     0,   265,   232,   265,     0,     0,     0,     0,   264,
     360,   264,   264,   138,   139,   140,   141,   142,   143,   264,
     264,     0,     0,     0,     0,   145,   146,   147,     0,     0,
       0,     0,   264,   264,     0,     0,   264,     0,     0,     0,
     232,   264,   265,   363,   265,   265,   363,     0,     0,     0,
       0,     0,   265,   265,   314,   363,     0,   363,     0,     0,
       0,   381,   135,   136,     0,   265,   265,     0,     0,   265,
       0,     0,     0,     0,   265,     0,     0,   138,   139,   140,
     141,   142,   143,     0,     0,     0,     0,     0,     0,     0,
     146,   147,   399,     0,     0,   402,     0,   404,     0,     0,
       0,     0,     0,   405,     0,   407,     0,     0,     0,     0,
       0,     0,     0,   316,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   238,     0,   239,     0,
     240,   241,     8,   242,   243,   244,     0,   245,     0,     0,
     246,     0,     0,   435,     0,   437,   438,   247,    44,    45,
      46,     0,     0,   445,   446,     0,    48,    49,     0,    50,
       0,    51,     0,   248,     0,     0,   450,   451,     0,    53,
     452,     0,     0,     0,     0,   455,     0,     0,     0,     0,
       0,     0,   319,     0,     0,     0,   249,     0,    54,    55,
      56,    57,    58,    59,     9,   238,     0,   239,     0,   240,
     241,     8,   242,   243,   244,     0,   245,     0,     0,   246,
       0,     0,     0,     0,     0,     0,   247,    44,    45,    46,
       0,     0,     0,     0,     0,    48,    49,     0,    50,     0,
      51,     0,   248,     0,     0,     0,     0,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   328,     0,     0,     0,   249,     0,    54,    55,    56,
      57,    58,    59,     9,   238,     0,   239,     0,   240,   241,
       8,   242,   243,   244,     0,   245,     0,     0,   246,     0,
       0,     0,     0,     0,     0,   247,    44,    45,    46,     0,
       0,     0,     0,     0,    48,    49,     0,    50,     0,    51,
       0,   248,     0,     0,     0,     0,     0,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     330,     0,     0,     0,   249,     0,    54,    55,    56,    57,
      58,    59,     9,   238,     0,   239,     0,   240,   241,     8,
     242,   243,   244,     0,   245,     0,     0,   246,     0,     0,
       0,     0,     0,     0,   247,    44,    45,    46,     0,     0,
       0,     0,     0,    48,    49,     0,    50,     0,    51,     0,
     248,     0,     0,     0,     0,     0,    53,     0,     0,     0,
       0,     0,     0,     0,   421,     0,     0,     0,     0,     0,
       0,     0,     0,   249,     0,    54,    55,    56,    57,    58,
      59,     9,    39,     8,    40,    41,     0,     0,    42,     0,
       0,     0,     0,   422,     0,    43,     0,     0,     0,    44,
      45,    46,     0,     0,     0,     0,    47,    48,    49,     0,
      50,     0,    51,     0,     0,     0,     0,     0,   423,    52,
      53,     0,     0,     0,     0,     0,     0,     0,   125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
      55,    56,    57,    58,    59,     9,    39,     8,    40,    41,
       0,     0,    42,     0,     0,     0,     0,     0,     0,    43,
       0,     0,     0,    44,    45,    46,     0,     0,     0,     0,
      47,    48,    49,     0,    50,     0,    51,   126,     0,     0,
       0,     0,     0,    52,    53,     0,     0,     0,     0,     0,
       0,     0,   218,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    55,    56,    57,    58,    59,     9,
      39,     8,    40,    41,     0,     0,    42,     0,     0,     0,
       0,     0,     0,    43,     0,     0,     0,    44,    45,    46,
       0,     0,     0,     0,    47,    48,    49,     0,    50,   219,
      51,     0,     0,     0,     0,     0,     0,    52,    53,     0,
       0,     0,     0,     0,     0,     0,   222,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,    55,    56,
      57,    58,    59,     9,    39,     8,    40,    41,     0,     0,
      42,     0,     0,     0,     0,     0,     0,    43,     0,     0,
       0,    44,    45,    46,     0,     0,     0,     0,    47,    48,
      49,     0,    50,   223,    51,     0,     0,     0,     0,     0,
       0,    52,    53,     0,     0,     0,     0,     0,     0,     0,
     350,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,    55,    56,    57,    58,    59,     9,    39,     8,
      40,    41,     0,     0,    42,     0,     0,     0,     0,     0,
       0,    43,     0,     0,     0,    44,    45,    46,     0,     0,
       0,     0,    47,    48,    49,     0,    50,   351,    51,     0,
       0,     0,     0,     0,     0,    52,    53,     0,     0,     0,
       0,     0,     0,     0,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    54,    55,    56,    57,    58,
      59,     9,    39,     8,    40,    41,     0,     0,    42,     0,
       0,     0,     0,     0,     0,    43,     0,     0,     0,    44,
      45,    46,     0,     0,     0,     0,    47,    48,    49,     0,
      50,     0,    51,     0,     0,     0,     0,     0,     0,    52,
      53,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
      55,    56,    57,    58,    59,     9,   238,   362,   239,     0,
     240,   241,     8,   242,   243,   244,     0,   245,     0,     0,
     246,     0,     0,     0,     0,     0,     0,   247,    44,    45,
      46,     0,     0,     0,     0,     0,    48,    49,     0,    50,
       0,    51,     0,   248,     0,     0,     0,     0,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   249,     0,    54,    55,
      56,    57,    58,    59,     9,   238,     0,   239,   365,   240,
     241,     8,   242,   243,   244,     0,   245,     0,     0,   246,
       0,     0,     0,     0,     0,     0,   247,    44,    45,    46,
       0,     0,     0,     0,     0,    48,    49,     0,    50,     0,
      51,     0,   248,     0,     0,     0,     0,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   249,     0,    54,    55,    56,
      57,    58,    59,     9,   238,     0,   239,     0,   240,   241,
       8,   242,   243,   244,     0,   245,     0,     0,   246,     0,
       0,     0,     0,     0,     0,   247,    44,    45,    46,     0,
       0,     0,     0,     0,    48,    49,     0,    50,     0,    51,
       0,   248,   373,     0,     0,     0,     0,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   249,     0,    54,    55,    56,    57,
      58,    59,     9,   238,     0,   239,     0,   240,   241,     8,
     242,   243,   244,     0,   245,     0,     0,   246,     0,     0,
       0,     0,     0,     0,   247,    44,    45,    46,     0,     0,
       0,     0,     0,    48,    49,     0,    50,     0,    51,     0,
     248,     0,     0,     0,     0,     0,    53,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   249,   375,    54,    55,    56,    57,    58,
      59,     9,   238,     0,   239,     0,   240,   241,     8,   242,
     243,   244,     0,   245,     0,     0,   246,     0,     0,     0,
       0,     0,     0,   247,    44,    45,    46,     0,     0,     0,
       0,     0,    48,    49,     0,    50,     0,    51,     0,   248,
       0,     0,     0,     0,     0,    53,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   249,     0,    54,    55,    56,    57,    58,    59,
       9,    39,     8,    40,    41,     0,     0,    42,     0,     0,
       0,     0,   422,     0,    43,     0,     0,     0,    44,    45,
      46,     0,     0,     0,     0,    47,    48,    49,     0,    50,
       0,    51,     0,     0,   442,     0,     0,   423,    52,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,    55,
      56,    57,    58,    59,     9,    39,     8,    40,    41,     0,
       0,    42,     0,     0,     0,     0,     0,     0,    43,     0,
       0,     0,    44,    45,    46,     0,     0,     0,     0,    47,
      48,    49,     0,    50,     0,    51,     0,     0,     0,     0,
       0,     0,    52,    53,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    54,    55,    56,    57,    58,    59,     9,    39,
       8,    40,    41,     0,     0,    42,     0,     0,     0,     0,
       0,     0,    43,     0,     0,     0,    44,    45,    46,     0,
       0,     0,     0,    47,    48,    49,     0,   153,   339,    51,
       0,     0,     0,     0,     0,     0,    52,    53,     0,     0,
       0,     0,     0,   131,   132,   133,   134,     0,   135,   136,
     137,     0,     0,     0,     0,     0,    54,    55,    56,    57,
      58,    59,     9,   138,   139,   140,   141,   142,   143,   371,
       0,     0,     0,   144,     0,   145,   146,   147,     0,     0,
       0,     0,     0,     0,   131,   132,   133,   134,     0,   135,
     136,   137,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
     419,     0,     0,     0,   144,     0,   145,   146,   147,     0,
       0,     0,     0,     0,     0,   131,   132,   133,   134,     0,
     135,   136,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,   449,     0,     0,     0,   144,     0,   145,   146,   147,
       0,     0,     0,     0,     0,     0,   131,   132,   133,   134,
       0,   135,   136,   137,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   138,   139,   140,   141,
     142,   143,   177,     0,     0,     0,   144,     0,   145,   146,
     147,     0,     0,     0,     0,   131,   132,   133,   134,     0,
     135,   136,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,   369,     0,     0,     0,   144,     0,   145,   146,   147,
       0,     0,     0,     0,   131,   132,   133,   134,     0,   135,
     136,   137,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
     340,     0,     0,     0,   144,     0,   145,   146,   147,     0,
       0,     0,   131,   132,   133,   134,     0,   135,   136,   137,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   138,   139,   140,   141,   142,   143,   370,     0,
       0,     0,   144,     0,   145,   146,   147,     0,   131,   132,
     133,   134,     0,   135,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
     140,   141,   142,   143,     0,   338,     0,     0,   144,     0,
     145,   146,   147,   131,   132,   133,   134,     0,   135,   136,
     137,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   138,   139,   140,   141,   142,   143,     0,
       0,     0,   341,   144,     0,   145,   146,   147,   131,   132,
     133,   134,     0,   135,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
     140,   141,   142,   143,     0,     0,     0,     0,   144,     0,
     145,   146,   147,   131,   132,   133,   134,     0,   135,   136,
     137,     0,   181,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   138,   139,   140,   141,   142,   143,     0,
       0,     0,     0,   144,     0,   145,   146,   147,   131,   132,
     133,   134,     0,   135,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
     140,   141,   142,   143,     0,   188,     0,     0,   144,     0,
     145,   146,   147,   131,   132,   133,   134,     0,   135,   136,
     137,     0,   303,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   138,   139,   140,   141,   142,   143,     0,
       0,     0,     0,   144,     0,   145,   146,   147,   131,   132,
     133,   134,     0,   135,   136,   137,     0,   342,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
     140,   141,   142,   143,     0,     0,     0,     0,   144,     0,
     145,   146,   147,   131,   132,   133,   134,     0,   135,   136,
     137,     0,     0,     0,   343,     0,     0,     0,     0,     0,
       0,     0,     0,   138,   139,   140,   141,   142,   143,     0,
       0,     0,     0,   144,     0,   145,   146,   147,   131,   132,
     133,   134,     0,   135,   136,   137,     0,     0,     0,     0,
       0,     0,   444,     0,     0,     0,     0,     0,   138,   139,
     140,   141,   142,   143,     0,     0,     0,     0,   144,     0,
     145,   146,   147,   131,   132,   133,   134,     0,   135,   136,
     137,     0,     0,     0,     0,     0,   453,     0,     0,     0,
       0,     0,     0,   138,   139,   140,   141,   142,   143,     0,
       0,     0,     0,   144,     0,   145,   146,   147,   131,   132,
     133,   134,     0,   135,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
     140,   141,   142,   143,     0,     0,     0,     0,   144,     0,
     145,   146,   147,   131,   132,   133,     0,     0,   135,   136,
     137,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   138,   139,   140,   141,   142,   143,     0,
       0,     0,     0,   131,     0,   145,   146,   147,   135,   136,
     137,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   138,   139,   140,   141,   142,   143,     0,
       0,     0,     0,     0,     0,   145,   146,   147
  };

  const short
  Parser::yycheck_[] =
  {
      10,    51,     1,    48,    49,    92,    41,    52,    43,    20,
       3,    39,     3,     5,     1,   158,    34,     1,    47,   162,
     159,    20,    20,    20,   163,   164,     1,     0,    50,   168,
     169,     4,    42,    20,    20,    20,    20,    47,    15,    68,
      50,    51,    19,    35,    21,    20,    20,    58,    20,    67,
      23,    49,    34,    20,    51,    20,    49,    46,    49,     0,
      50,    47,    49,    46,   207,    49,    20,    20,   207,    36,
      37,    38,    54,    54,    49,    46,    53,    44,    45,    68,
      47,    20,    49,    82,    82,    82,    58,    61,    56,    58,
      57,    60,   235,    78,    50,    82,    82,    82,    82,    67,
     150,   151,    58,    50,    58,    58,    54,    82,    82,    76,
      77,    78,    79,    80,    81,    82,   161,    82,   110,    58,
      20,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,    20,    47,
     150,   151,   229,   153,   172,   239,    52,   175,    53,    47,
      46,    47,    58,    46,   248,   249,   166,   296,    58,    67,
     170,   171,    61,    48,   174,   308,   176,   177,   178,    68,
     180,   148,    68,    58,   184,    68,    58,   187,   188,    54,
      53,    47,   159,    46,    59,   158,   163,   164,    54,   162,
      65,   168,   169,   238,   239,    46,    48,   336,   337,   244,
      48,    48,   345,   248,   249,   344,    58,   242,   243,    48,
      58,    58,    58,   241,    52,   354,   355,   227,     0,     1,
      58,    48,     4,     5,     6,     7,     8,     9,    10,    11,
     207,    58,    48,    53,    52,   245,   246,   247,    50,   378,
      58,   380,    58,   235,    61,    62,    63,    64,   298,    68,
      51,   390,    48,   392,     4,     5,     6,     7,     8,     9,
      10,    11,    64,    47,   237,    48,    70,    49,    48,    46,
      67,    61,   317,    48,    46,   320,    68,     2,    15,    58,
      58,    68,    68,    68,   329,    17,   331,   297,   298,    52,
     335,    16,    17,    18,    19,    20,    48,    22,     1,    49,
     310,     4,     5,     6,     7,     8,     9,    10,    11,    75,
      68,    51,    13,    48,    39,    40,    41,    48,    43,   296,
      46,   366,   332,   315,   369,    50,   371,    46,   338,   339,
     340,   341,   377,   161,   379,   308,    44,    45,    46,    27,
      46,    46,    51,   353,    12,    60,    49,    23,    52,    51,
     359,    59,    60,    61,    62,    63,    64,   367,   368,   336,
     337,   448,    53,    71,    72,    73,   161,   344,    53,    35,
      44,    45,   417,   424,   419,   420,   149,   354,   355,   296,
     183,   296,   427,   428,   448,   110,   359,    61,    62,    63,
      64,   162,   229,   403,   110,   440,   441,   308,   241,   444,
      -1,   378,   172,   380,   449,   415,   416,    -1,   418,    -1,
     238,   239,    -1,   390,   424,   392,   244,    -1,    -1,   429,
     248,   249,    -1,    -1,   149,    -1,    -1,   152,   153,    -1,
      -1,    -1,    -1,   158,    -1,    -1,    -1,   162,    -1,    -1,
     165,    -1,   167,   238,   239,    -1,    -1,   172,    24,   244,
     175,    -1,    -1,   248,   249,    -1,    -1,    33,   183,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,   161,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   207,    59,    60,    61,    62,    63,    64,   317,
      -1,    -1,   320,    69,    -1,    71,    72,    73,    -1,    -1,
      -1,   329,    -1,   331,    -1,    -1,    -1,   335,    -1,    -1,
     235,    -1,   237,    -1,    -1,    -1,   241,   242,   243,    -1,
      -1,    -1,   317,    -1,    -1,   320,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   329,    -1,   331,    -1,   366,    -1,
     335,   369,    -1,   371,    -1,    -1,    -1,    -1,    -1,   377,
     244,   379,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   366,    -1,    39,   369,    41,   371,    -1,    44,    45,
      46,    -1,   377,   308,   379,    -1,    -1,    -1,    -1,   417,
     315,   419,   420,    59,    60,    61,    62,    63,    64,   427,
     428,    -1,    -1,    -1,    -1,    71,    72,    73,    -1,    -1,
      -1,    -1,   440,   441,    -1,    -1,   444,    -1,    -1,    -1,
     345,   449,   417,   317,   419,   420,   320,    -1,    -1,    -1,
      -1,    -1,   427,   428,   359,   329,    -1,   331,    -1,    -1,
      -1,   335,    44,    45,    -1,   440,   441,    -1,    -1,   444,
      -1,    -1,    -1,    -1,   449,    -1,    -1,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,   366,    -1,    -1,   369,    -1,   371,    -1,    -1,
      -1,    -1,    -1,   377,    -1,   379,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    14,    -1,    16,    -1,
      18,    19,    20,    21,    22,    23,    -1,    25,    -1,    -1,
      28,    -1,    -1,   417,    -1,   419,   420,    35,    36,    37,
      38,    -1,    -1,   427,   428,    -1,    44,    45,    -1,    47,
      -1,    49,    -1,    51,    -1,    -1,   440,   441,    -1,    57,
     444,    -1,    -1,    -1,    -1,   449,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    74,    -1,    76,    77,
      78,    79,    80,    81,    82,    14,    -1,    16,    -1,    18,
      19,    20,    21,    22,    23,    -1,    25,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    47,    -1,
      49,    -1,    51,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    14,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    -1,    25,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    47,    -1,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    74,    -1,    76,    77,    78,    79,
      80,    81,    82,    14,    -1,    16,    -1,    18,    19,    20,
      21,    22,    23,    -1,    25,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    44,    45,    -1,    47,    -1,    49,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    19,    20,    21,    22,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    30,    -1,    32,    -1,    -1,    -1,    36,
      37,    38,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,
      47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    81,    82,    19,    20,    21,    22,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    47,    -1,    49,    50,    -1,    -1,
      -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      19,    20,    21,    22,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,    38,
      -1,    -1,    -1,    -1,    43,    44,    45,    -1,    47,    48,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    -1,
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
      47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      77,    78,    79,    80,    81,    82,    14,    15,    16,    -1,
      18,    19,    20,    21,    22,    23,    -1,    25,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,
      38,    -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    47,
      -1,    49,    -1,    51,    -1,    -1,    -1,    -1,    -1,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    76,    77,
      78,    79,    80,    81,    82,    14,    -1,    16,    17,    18,
      19,    20,    21,    22,    23,    -1,    25,    -1,    -1,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,
      -1,    -1,    -1,    -1,    -1,    44,    45,    -1,    47,    -1,
      49,    -1,    51,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    74,    -1,    76,    77,    78,
      79,    80,    81,    82,    14,    -1,    16,    -1,    18,    19,
      20,    21,    22,    23,    -1,    25,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    47,    -1,    49,
      -1,    51,    52,    -1,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    76,    77,    78,    79,
      80,    81,    82,    14,    -1,    16,    -1,    18,    19,    20,
      21,    22,    23,    -1,    25,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    44,    45,    -1,    47,    -1,    49,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    14,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    76,    77,    78,    79,    80,    81,
      82,    19,    20,    21,    22,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    30,    -1,    32,    -1,    -1,    -1,    36,    37,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    47,
      -1,    49,    -1,    -1,    52,    -1,    -1,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    82,    19,    20,    21,    22,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,    43,
      44,    45,    -1,    47,    -1,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    77,    78,    79,    80,    81,    82,    19,
      20,    21,    22,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      -1,    -1,    32,    -1,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    47,    24,    49,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    -1,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    81,    82,    59,    60,    61,    62,    63,    64,    24,
      -1,    -1,    -1,    69,    -1,    71,    72,    73,    -1,    -1,
      -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      24,    -1,    -1,    -1,    69,    -1,    71,    72,    73,    -1,
      -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    24,    -1,    -1,    -1,    69,    -1,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    26,    -1,    -1,    -1,    69,    -1,    71,    72,
      73,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    26,    -1,    -1,    -1,    69,    -1,    71,    72,    73,
      -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      27,    -1,    -1,    -1,    69,    -1,    71,    72,    73,    -1,
      -1,    -1,    39,    40,    41,    42,    -1,    44,    45,    46,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    59,    60,    61,    62,    63,    64,    29,    -1,
      -1,    -1,    69,    -1,    71,    72,    73,    -1,    39,    40,
      41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    -1,    31,    -1,    -1,    69,    -1,
      71,    72,    73,    39,    40,    41,    42,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    33,    69,    -1,    71,    72,    73,    39,    40,
      41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    69,    -1,
      71,    72,    73,    39,    40,    41,    42,    -1,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    69,    -1,    71,    72,    73,    39,    40,
      41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    -1,    66,    -1,    -1,    69,    -1,
      71,    72,    73,    39,    40,    41,    42,    -1,    44,    45,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    69,    -1,    71,    72,    73,    39,    40,
      41,    42,    -1,    44,    45,    46,    -1,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    69,    -1,
      71,    72,    73,    39,    40,    41,    42,    -1,    44,    45,
      46,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    69,    -1,    71,    72,    73,    39,    40,
      41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    69,    -1,
      71,    72,    73,    39,    40,    41,    42,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    69,    -1,    71,    72,    73,    39,    40,
      41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    -1,    -1,    -1,    -1,    69,    -1,
      71,    72,    73,    39,    40,    41,    -1,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    39,    -1,    71,    72,    73,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    71,    72,    73
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    49,    89,    90,   177,   178,     1,    20,    82,
     167,   179,   180,     0,     1,     4,     5,     6,     7,     8,
       9,    10,    11,    91,    92,    93,    94,    95,    96,    97,
      98,   101,   102,   103,   104,   177,     3,   178,    50,    19,
      21,    22,    25,    32,    36,    37,    38,    43,    44,    45,
      47,    49,    56,    57,    76,    77,    78,    79,    80,    81,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   167,   168,
      50,    50,    51,   168,   167,   167,   167,   167,   168,   167,
     168,   167,    92,    93,   167,   169,   172,   173,   175,   176,
     177,   170,   173,   170,   122,   170,   122,   123,   123,     1,
     121,   122,   150,   151,   167,     1,    50,   121,   122,   123,
     168,    39,    40,    41,    42,    44,    45,    46,    59,    60,
      61,    62,    63,    64,    69,    71,    72,    73,    34,    67,
      47,    47,    54,    47,   122,   148,   165,   166,    47,    68,
      46,    46,    47,    68,    46,    54,    46,    34,    53,    53,
      46,    20,    58,   169,    20,    58,    20,    26,    20,    48,
      58,    48,    48,    58,    53,    50,    50,    58,    66,    56,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,    47,   153,   154,
     155,   156,   157,   158,   159,   168,   140,   167,     1,    48,
     121,   122,     1,    48,   121,   167,   122,    68,    52,    58,
       1,   162,   167,   172,   174,   177,   153,    51,    14,    16,
      18,    19,    21,    22,    23,    25,    28,    35,    51,    74,
     106,   107,   108,   109,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   123,   125,   126,     1,   162,   153,   153,
      61,   122,   167,   153,   160,   161,   153,   122,   122,   176,
     122,   173,   122,   122,   122,   122,   151,   167,   122,   122,
     122,   152,   153,   167,   171,   172,    59,    65,    47,    48,
      48,    48,    48,    48,   122,   166,    48,    48,    58,   172,
      46,     1,    99,   100,   167,   177,     1,   105,   106,     1,
     105,   175,   170,   170,   106,   122,   122,   122,     1,   105,
       1,   105,    70,    48,    48,    46,    61,    68,    31,    24,
      27,    33,    48,    50,    58,    58,   152,   153,   161,   122,
       1,    48,   121,    68,    68,    68,   174,   122,    52,    58,
     167,    15,    15,   106,    17,    17,    20,    20,    20,    26,
      29,    24,    52,    52,    75,    75,   122,    46,    68,    46,
      68,   106,   153,   153,   122,   122,   122,   122,   153,   172,
      58,    60,    68,    48,    48,   122,   153,   153,    99,   106,
     122,   122,   106,    51,   106,   106,   153,   106,   153,    13,
     163,    48,    48,   153,   153,    46,    46,    24,    33,    24,
      27,     1,    30,    55,   110,   111,   122,    46,    46,    51,
      12,   164,    60,   122,   122,   106,   122,   106,   106,    52,
      53,    53,    52,   111,    53,   106,   106,   122,    51,    24,
     106,   106,   106,    52,   165,   106,    52
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    88,    89,    90,    90,    91,    91,    92,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    94,
      94,    95,    96,    96,    96,    97,    97,    97,    97,    97,
      97,    98,    99,    99,    99,   100,   100,   101,   102,   102,
     103,   104,   104,   105,   105,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   107,   108,   108,
     109,   109,   110,   110,   111,   111,   111,   112,   113,   113,
     114,   115,   116,   116,   116,   116,   117,   117,   117,   117,
     118,   119,   120,   121,   121,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   123,   123,   123,   123,   123,   123,
     123,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   125,   126,   126,   126,   126,   127,   127,   127,   127,
     128,   129,   129,   129,   130,   131,   132,   133,   134,   135,
     136,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   138,   139,   139,   140,   141,   142,   143,
     143,   144,   145,   146,   146,   146,   147,   148,   149,   150,
     150,   151,   152,   152,   153,   153,   153,   153,   153,   153,
     154,   155,   156,   157,   158,   159,   160,   160,   161,   161,
     162,   162,   163,   163,   164,   164,   165,   165,   166,   166,
     166,   167,   167,   168,   168,   169,   169,   170,   170,   171,
     171,   172,   173,   173,   174,   174,   175,   175,   176,   177,
     177,   178,   178,   178,   179,   180
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       4,     6,     6,     9,     9,     4,     6,     7,     9,     7,
       9,     8,     1,     2,     1,     3,     1,     4,     2,     4,
       4,     2,     4,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     4,     6,
       6,     6,     2,     1,     3,     3,     3,     4,     6,     8,
       6,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     4,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     1,     1,     1,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       1,     1,     1,     3,     4,     4,     3,     5,     6,     6,
       3,     3,     4,     4,     3,     4,     6,     6,     6,     6,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     3,     3,     5,     5,     3,     3,
       1,     3,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     5,     5,     4,     6,     3,     3,     1,     1,     0,
       3,     1,     4,     0,     4,     0,     3,     1,     1,     5,
       3,     1,     1,     3,     1,     1,     1,     3,     1,     3,
       1,     3,     2,     1,     2,     1,     3,     1,     3,     2,
       1,     3,     3,     3,     1,     2
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
  "UsingDefinition", "UsingPathDefinition", "InvariantDefinition",
  "ImportDefinition", "Rules", "Rule", "SkipRule", "ConditionalRule",
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
       0,   413,   413,   423,   429,   437,   443,   453,   459,   463,
     471,   475,   479,   483,   487,   491,   495,   499,   503,   511,
     515,   523,   531,   536,   542,   550,   556,   561,   568,   574,
     578,   586,   601,   605,   611,   619,   626,   636,   644,   648,
     656,   664,   668,   680,   686,   696,   700,   704,   708,   712,
     716,   720,   724,   728,   732,   736,   740,   748,   756,   760,
     768,   772,   780,   786,   796,   800,   804,   812,   820,   824,
     832,   840,   848,   852,   856,   861,   870,   874,   878,   883,
     892,   900,   908,   920,   927,   937,   941,   945,   949,   953,
     957,   961,   965,   969,   977,   981,   985,   989,   993,   997,
    1001,  1013,  1017,  1021,  1025,  1029,  1033,  1037,  1041,  1045,
    1049,  1053,  1057,  1061,  1065,  1069,  1073,  1077,  1081,  1089,
    1093,  1097,  1105,  1110,  1117,  1123,  1131,  1136,  1143,  1149,
    1157,  1165,  1172,  1178,  1186,  1194,  1202,  1210,  1218,  1226,
    1234,  1247,  1251,  1255,  1259,  1263,  1267,  1271,  1275,  1279,
    1283,  1287,  1291,  1299,  1308,  1314,  1324,  1332,  1340,  1348,
    1352,  1360,  1368,  1376,  1383,  1389,  1397,  1406,  1417,  1426,
    1433,  1442,  1454,  1461,  1470,  1474,  1478,  1482,  1486,  1490,
    1498,  1506,  1517,  1528,  1536,  1544,  1556,  1563,  1573,  1577,
    1585,  1592,  1606,  1610,  1618,  1622,  1631,  1638,  1648,  1655,
    1663,  1680,  1684,  1693,  1700,  1712,  1716,  1725,  1732,  1742,
    1749,  1759,  1768,  1774,  1782,  1788,  1800,  1807,  1816,  1828,
    1834,  1843,  1850,  1857,  1864,  1871
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


#line 50 "../../obj/src/GrammarParser.y"
} // libcasm_fe
#line 5312 "GrammarParser.cpp"

#line 1877 "../../obj/src/GrammarParser.y"


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
