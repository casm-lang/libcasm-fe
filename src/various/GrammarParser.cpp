// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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
#line 91 "../../obj/src/GrammarParser.y"

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

#line 64 "GrammarParser.cpp"


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
#line 156 "GrammarParser.cpp"


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
      return yystos_[+state];
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
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "local"
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

      case 182: // Attribute
        value.YY_MOVE_OR_COPY< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case 181: // Attributes
        value.YY_MOVE_OR_COPY< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case 183: // BasicAttribute
        value.YY_MOVE_OR_COPY< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 155: // BasicType
        value.YY_MOVE_OR_COPY< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case 117: // BlockRule
        value.YY_MOVE_OR_COPY< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case 126: // CallExpression
        value.YY_MOVE_OR_COPY< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 120: // CallRule
        value.YY_MOVE_OR_COPY< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 137: // CardinalityExpression
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

      case 134: // ChooseExpression
        value.YY_MOVE_OR_COPY< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 115: // ChooseRule
        value.YY_MOVE_OR_COPY< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 133: // ConditionalExpression
        value.YY_MOVE_OR_COPY< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 108: // ConditionalRule
        value.YY_MOVE_OR_COPY< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 164: // MaybeDefined
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

      case 127: // DirectCallExpression
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

      case 136: // ExistentialQuantifierExpression
        value.YY_MOVE_OR_COPY< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 123: // Term
      case 124: // SimpleOrClaspedTerm
      case 125: // OperatorExpression
        value.YY_MOVE_OR_COPY< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case 184: // ExpressionAttribute
        value.YY_MOVE_OR_COPY< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 122: // Terms
        value.YY_MOVE_OR_COPY< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case 160: // FixedSizedType
        value.YY_MOVE_OR_COPY< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case 114: // ForallRule
        value.YY_MOVE_OR_COPY< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 98: // FunctionDefinition
      case 179: // AttributedLocalFunctionDefinition
      case 180: // LocalFunctionDefinition
        value.YY_MOVE_OR_COPY< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 178: // LocalFunctionDefinitions
        value.YY_MOVE_OR_COPY< FunctionDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 90: // Header
        value.YY_MOVE_OR_COPY< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 82: // "identifier"
      case 168: // Identifier
        value.YY_MOVE_OR_COPY< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case 169: // IdentifierPath
        value.YY_MOVE_OR_COPY< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 104: // ImportDefinition
        value.YY_MOVE_OR_COPY< ImportDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 130: // IndirectCallExpression
        value.YY_MOVE_OR_COPY< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 94: // InitDefinition
        value.YY_MOVE_OR_COPY< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 167: // Initializer
        value.YY_MOVE_OR_COPY< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case 166: // Initializers
        value.YY_MOVE_OR_COPY< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case 165: // MaybeInitially
        value.YY_MOVE_OR_COPY< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // InvariantDefinition
        value.YY_MOVE_OR_COPY< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 116: // IterateRule
        value.YY_MOVE_OR_COPY< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 132: // LetExpression
        value.YY_MOVE_OR_COPY< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 112: // LetRule
        value.YY_MOVE_OR_COPY< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case 147: // ListLiteral
        value.YY_MOVE_OR_COPY< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 138: // Literal
        value.YY_MOVE_OR_COPY< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case 129: // LiteralCallExpression
        value.YY_MOVE_OR_COPY< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 113: // LocalRule
        value.YY_MOVE_OR_COPY< LocalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 128: // MethodCallExpression
        value.YY_MOVE_OR_COPY< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 152: // Assignment
        value.YY_MOVE_OR_COPY< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 151: // Assignments
        value.YY_MOVE_OR_COPY< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case 148: // RangeLiteral
        value.YY_MOVE_OR_COPY< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 150: // RecordLiteral
        value.YY_MOVE_OR_COPY< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 157: // RecordType
        value.YY_MOVE_OR_COPY< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case 146: // ReferenceLiteral
        value.YY_MOVE_OR_COPY< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 159: // RelationType
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

      case 118: // SequenceRule
        value.YY_MOVE_OR_COPY< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case 107: // SkipRule
        value.YY_MOVE_OR_COPY< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Specification
        value.YY_MOVE_OR_COPY< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case 158: // TemplateType
        value.YY_MOVE_OR_COPY< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case 149: // TupleLiteral
        value.YY_MOVE_OR_COPY< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 156: // TupleType
        value.YY_MOVE_OR_COPY< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case 131: // TypeCastingExpression
        value.YY_MOVE_OR_COPY< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 153: // Types
      case 161: // FunctionParameters
      case 162: // MaybeFunctionParameters
        value.YY_MOVE_OR_COPY< Types::Ptr > (YY_MOVE (that.value));
        break;

      case 139: // UndefinedLiteral
        value.YY_MOVE_OR_COPY< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 135: // UniversalQuantifierExpression
        value.YY_MOVE_OR_COPY< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 119: // UpdateRule
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
      case 140: // BooleanLiteral
      case 141: // IntegerLiteral
      case 142: // RationalLiteral
      case 143: // DecimalLiteral
      case 144: // BinaryLiteral
      case 145: // StringLiteral
        value.YY_MOVE_OR_COPY< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 177: // VariableBinding
        value.YY_MOVE_OR_COPY< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case 176: // VariableBindings
        value.YY_MOVE_OR_COPY< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        value.YY_MOVE_OR_COPY< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 163: // Parameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        value.YY_MOVE_OR_COPY< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 121: // WhileRule
        value.YY_MOVE_OR_COPY< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case 154: // Type
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
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "local"
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

      case 182: // Attribute
        value.move< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case 181: // Attributes
        value.move< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case 183: // BasicAttribute
        value.move< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 155: // BasicType
        value.move< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case 117: // BlockRule
        value.move< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case 126: // CallExpression
        value.move< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 120: // CallRule
        value.move< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 137: // CardinalityExpression
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

      case 134: // ChooseExpression
        value.move< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 115: // ChooseRule
        value.move< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 133: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 108: // ConditionalRule
        value.move< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 164: // MaybeDefined
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

      case 127: // DirectCallExpression
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

      case 136: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 123: // Term
      case 124: // SimpleOrClaspedTerm
      case 125: // OperatorExpression
        value.move< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case 184: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 122: // Terms
        value.move< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case 160: // FixedSizedType
        value.move< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case 114: // ForallRule
        value.move< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 98: // FunctionDefinition
      case 179: // AttributedLocalFunctionDefinition
      case 180: // LocalFunctionDefinition
        value.move< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 178: // LocalFunctionDefinitions
        value.move< FunctionDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 90: // Header
        value.move< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 82: // "identifier"
      case 168: // Identifier
        value.move< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case 169: // IdentifierPath
        value.move< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 104: // ImportDefinition
        value.move< ImportDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 130: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 94: // InitDefinition
        value.move< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 167: // Initializer
        value.move< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case 166: // Initializers
        value.move< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case 165: // MaybeInitially
        value.move< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 116: // IterateRule
        value.move< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 132: // LetExpression
        value.move< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 112: // LetRule
        value.move< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case 147: // ListLiteral
        value.move< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 138: // Literal
        value.move< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case 129: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 113: // LocalRule
        value.move< LocalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 128: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 152: // Assignment
        value.move< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 151: // Assignments
        value.move< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case 148: // RangeLiteral
        value.move< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 150: // RecordLiteral
        value.move< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 157: // RecordType
        value.move< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case 146: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 159: // RelationType
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

      case 118: // SequenceRule
        value.move< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case 107: // SkipRule
        value.move< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Specification
        value.move< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case 158: // TemplateType
        value.move< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case 149: // TupleLiteral
        value.move< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 156: // TupleType
        value.move< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case 131: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 153: // Types
      case 161: // FunctionParameters
      case 162: // MaybeFunctionParameters
        value.move< Types::Ptr > (YY_MOVE (that.value));
        break;

      case 139: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 135: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 119: // UpdateRule
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
      case 140: // BooleanLiteral
      case 141: // IntegerLiteral
      case 142: // RationalLiteral
      case 143: // DecimalLiteral
      case 144: // BinaryLiteral
      case 145: // StringLiteral
        value.move< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 177: // VariableBinding
        value.move< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case 176: // VariableBindings
        value.move< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 163: // Parameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        value.move< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 121: // WhileRule
        value.move< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case 154: // Type
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
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
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
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "local"
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
        value.copy< Ast::Token::Ptr > (that.value);
        break;

      case 182: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 181: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 183: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 155: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 117: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 126: // CallExpression
        value.copy< CallExpression::Ptr > (that.value);
        break;

      case 120: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 137: // CardinalityExpression
        value.copy< CardinalityExpression::Ptr > (that.value);
        break;

      case 111: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 109: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 110: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 134: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 115: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 133: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 108: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 164: // MaybeDefined
        value.copy< Defined::Ptr > (that.value);
        break;

      case 92: // AttributedDefinition
      case 93: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 91: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 96: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 127: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 95: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 99: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 100: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 136: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 123: // Term
      case 124: // SimpleOrClaspedTerm
      case 125: // OperatorExpression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 184: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 122: // Terms
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 160: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 114: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 98: // FunctionDefinition
      case 179: // AttributedLocalFunctionDefinition
      case 180: // LocalFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 178: // LocalFunctionDefinitions
        value.copy< FunctionDefinitions::Ptr > (that.value);
        break;

      case 90: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 82: // "identifier"
      case 168: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 169: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 104: // ImportDefinition
        value.copy< ImportDefinition::Ptr > (that.value);
        break;

      case 130: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 94: // InitDefinition
        value.copy< InitDefinition::Ptr > (that.value);
        break;

      case 167: // Initializer
        value.copy< Initializer::Ptr > (that.value);
        break;

      case 166: // Initializers
        value.copy< Initializers::Ptr > (that.value);
        break;

      case 165: // MaybeInitially
        value.copy< Initially::Ptr > (that.value);
        break;

      case 103: // InvariantDefinition
        value.copy< InvariantDefinition::Ptr > (that.value);
        break;

      case 116: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 132: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 112: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 147: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case 138: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case 129: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case 113: // LocalRule
        value.copy< LocalRule::Ptr > (that.value);
        break;

      case 128: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 152: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case 151: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case 148: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case 150: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case 157: // RecordType
        value.copy< RecordType::Ptr > (that.value);
        break;

      case 146: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case 159: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 106: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 97: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 105: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 118: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 107: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 89: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 158: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case 149: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case 156: // TupleType
        value.copy< TupleType::Ptr > (that.value);
        break;

      case 131: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 153: // Types
      case 161: // FunctionParameters
      case 162: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 139: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case 135: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 119: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 101: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case 102: // UsingPathDefinition
        value.copy< UsingPathDefinition::Ptr > (that.value);
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 140: // BooleanLiteral
      case 141: // IntegerLiteral
      case 142: // RationalLiteral
      case 143: // DecimalLiteral
      case 144: // BinaryLiteral
      case 145: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case 177: // VariableBinding
        value.copy< VariableBinding::Ptr > (that.value);
        break;

      case 176: // VariableBindings
        value.copy< VariableBindings::Ptr > (that.value);
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 163: // Parameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case 121: // WhileRule
        value.copy< WhileRule::Ptr > (that.value);
        break;

      case 154: // Type
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
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "local"
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

      case 182: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 181: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 183: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 155: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 117: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 126: // CallExpression
        value.move< CallExpression::Ptr > (that.value);
        break;

      case 120: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 137: // CardinalityExpression
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

      case 134: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 115: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 133: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 108: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 164: // MaybeDefined
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

      case 127: // DirectCallExpression
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

      case 136: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 123: // Term
      case 124: // SimpleOrClaspedTerm
      case 125: // OperatorExpression
        value.move< Expression::Ptr > (that.value);
        break;

      case 184: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 122: // Terms
        value.move< Expressions::Ptr > (that.value);
        break;

      case 160: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 114: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 98: // FunctionDefinition
      case 179: // AttributedLocalFunctionDefinition
      case 180: // LocalFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 178: // LocalFunctionDefinitions
        value.move< FunctionDefinitions::Ptr > (that.value);
        break;

      case 90: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 82: // "identifier"
      case 168: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 169: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 104: // ImportDefinition
        value.move< ImportDefinition::Ptr > (that.value);
        break;

      case 130: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 94: // InitDefinition
        value.move< InitDefinition::Ptr > (that.value);
        break;

      case 167: // Initializer
        value.move< Initializer::Ptr > (that.value);
        break;

      case 166: // Initializers
        value.move< Initializers::Ptr > (that.value);
        break;

      case 165: // MaybeInitially
        value.move< Initially::Ptr > (that.value);
        break;

      case 103: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (that.value);
        break;

      case 116: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 132: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 112: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 147: // ListLiteral
        value.move< ListLiteral::Ptr > (that.value);
        break;

      case 138: // Literal
        value.move< Literal::Ptr > (that.value);
        break;

      case 129: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (that.value);
        break;

      case 113: // LocalRule
        value.move< LocalRule::Ptr > (that.value);
        break;

      case 128: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 152: // Assignment
        value.move< NamedExpression::Ptr > (that.value);
        break;

      case 151: // Assignments
        value.move< NamedExpressions::Ptr > (that.value);
        break;

      case 148: // RangeLiteral
        value.move< RangeLiteral::Ptr > (that.value);
        break;

      case 150: // RecordLiteral
        value.move< RecordLiteral::Ptr > (that.value);
        break;

      case 157: // RecordType
        value.move< RecordType::Ptr > (that.value);
        break;

      case 146: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (that.value);
        break;

      case 159: // RelationType
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

      case 118: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 107: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 89: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 158: // TemplateType
        value.move< TemplateType::Ptr > (that.value);
        break;

      case 149: // TupleLiteral
        value.move< TupleLiteral::Ptr > (that.value);
        break;

      case 156: // TupleType
        value.move< TupleType::Ptr > (that.value);
        break;

      case 131: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 153: // Types
      case 161: // FunctionParameters
      case 162: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 139: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (that.value);
        break;

      case 135: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 119: // UpdateRule
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
      case 140: // BooleanLiteral
      case 141: // IntegerLiteral
      case 142: // RationalLiteral
      case 143: // DecimalLiteral
      case 144: // BinaryLiteral
      case 145: // StringLiteral
        value.move< ValueLiteral::Ptr > (that.value);
        break;

      case 177: // VariableBinding
        value.move< VariableBinding::Ptr > (that.value);
        break;

      case 176: // VariableBindings
        value.move< VariableBindings::Ptr > (that.value);
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 163: // Parameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        value.move< VariableDefinitions::Ptr > (that.value);
        break;

      case 121: // WhileRule
        value.move< WhileRule::Ptr > (that.value);
        break;

      case 154: // Type
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
      case 3: // "CASM"
      case 4: // "init"
      case 5: // "derived"
      case 6: // "enumeration"
      case 7: // "rule"
      case 8: // "using"
      case 9: // "invariant"
      case 10: // "import"
      case 11: // "function"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "local"
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

      case 182: // Attribute
        yylhs.value.emplace< Attribute::Ptr > ();
        break;

      case 181: // Attributes
        yylhs.value.emplace< Attributes::Ptr > ();
        break;

      case 183: // BasicAttribute
        yylhs.value.emplace< BasicAttribute::Ptr > ();
        break;

      case 155: // BasicType
        yylhs.value.emplace< BasicType::Ptr > ();
        break;

      case 117: // BlockRule
        yylhs.value.emplace< BlockRule::Ptr > ();
        break;

      case 126: // CallExpression
        yylhs.value.emplace< CallExpression::Ptr > ();
        break;

      case 120: // CallRule
        yylhs.value.emplace< CallRule::Ptr > ();
        break;

      case 137: // CardinalityExpression
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

      case 134: // ChooseExpression
        yylhs.value.emplace< ChooseExpression::Ptr > ();
        break;

      case 115: // ChooseRule
        yylhs.value.emplace< ChooseRule::Ptr > ();
        break;

      case 133: // ConditionalExpression
        yylhs.value.emplace< ConditionalExpression::Ptr > ();
        break;

      case 108: // ConditionalRule
        yylhs.value.emplace< ConditionalRule::Ptr > ();
        break;

      case 164: // MaybeDefined
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

      case 127: // DirectCallExpression
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

      case 136: // ExistentialQuantifierExpression
        yylhs.value.emplace< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 123: // Term
      case 124: // SimpleOrClaspedTerm
      case 125: // OperatorExpression
        yylhs.value.emplace< Expression::Ptr > ();
        break;

      case 184: // ExpressionAttribute
        yylhs.value.emplace< ExpressionAttribute::Ptr > ();
        break;

      case 122: // Terms
        yylhs.value.emplace< Expressions::Ptr > ();
        break;

      case 160: // FixedSizedType
        yylhs.value.emplace< FixedSizedType::Ptr > ();
        break;

      case 114: // ForallRule
        yylhs.value.emplace< ForallRule::Ptr > ();
        break;

      case 98: // FunctionDefinition
      case 179: // AttributedLocalFunctionDefinition
      case 180: // LocalFunctionDefinition
        yylhs.value.emplace< FunctionDefinition::Ptr > ();
        break;

      case 178: // LocalFunctionDefinitions
        yylhs.value.emplace< FunctionDefinitions::Ptr > ();
        break;

      case 90: // Header
        yylhs.value.emplace< HeaderDefinition::Ptr > ();
        break;

      case 82: // "identifier"
      case 168: // Identifier
        yylhs.value.emplace< Identifier::Ptr > ();
        break;

      case 169: // IdentifierPath
        yylhs.value.emplace< IdentifierPath::Ptr > ();
        break;

      case 104: // ImportDefinition
        yylhs.value.emplace< ImportDefinition::Ptr > ();
        break;

      case 130: // IndirectCallExpression
        yylhs.value.emplace< IndirectCallExpression::Ptr > ();
        break;

      case 94: // InitDefinition
        yylhs.value.emplace< InitDefinition::Ptr > ();
        break;

      case 167: // Initializer
        yylhs.value.emplace< Initializer::Ptr > ();
        break;

      case 166: // Initializers
        yylhs.value.emplace< Initializers::Ptr > ();
        break;

      case 165: // MaybeInitially
        yylhs.value.emplace< Initially::Ptr > ();
        break;

      case 103: // InvariantDefinition
        yylhs.value.emplace< InvariantDefinition::Ptr > ();
        break;

      case 116: // IterateRule
        yylhs.value.emplace< IterateRule::Ptr > ();
        break;

      case 132: // LetExpression
        yylhs.value.emplace< LetExpression::Ptr > ();
        break;

      case 112: // LetRule
        yylhs.value.emplace< LetRule::Ptr > ();
        break;

      case 147: // ListLiteral
        yylhs.value.emplace< ListLiteral::Ptr > ();
        break;

      case 138: // Literal
        yylhs.value.emplace< Literal::Ptr > ();
        break;

      case 129: // LiteralCallExpression
        yylhs.value.emplace< LiteralCallExpression::Ptr > ();
        break;

      case 113: // LocalRule
        yylhs.value.emplace< LocalRule::Ptr > ();
        break;

      case 128: // MethodCallExpression
        yylhs.value.emplace< MethodCallExpression::Ptr > ();
        break;

      case 152: // Assignment
        yylhs.value.emplace< NamedExpression::Ptr > ();
        break;

      case 151: // Assignments
        yylhs.value.emplace< NamedExpressions::Ptr > ();
        break;

      case 148: // RangeLiteral
        yylhs.value.emplace< RangeLiteral::Ptr > ();
        break;

      case 150: // RecordLiteral
        yylhs.value.emplace< RecordLiteral::Ptr > ();
        break;

      case 157: // RecordType
        yylhs.value.emplace< RecordType::Ptr > ();
        break;

      case 146: // ReferenceLiteral
        yylhs.value.emplace< ReferenceLiteral::Ptr > ();
        break;

      case 159: // RelationType
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

      case 118: // SequenceRule
        yylhs.value.emplace< SequenceRule::Ptr > ();
        break;

      case 107: // SkipRule
        yylhs.value.emplace< SkipRule::Ptr > ();
        break;

      case 89: // Specification
        yylhs.value.emplace< Specification::Ptr > ();
        break;

      case 158: // TemplateType
        yylhs.value.emplace< TemplateType::Ptr > ();
        break;

      case 149: // TupleLiteral
        yylhs.value.emplace< TupleLiteral::Ptr > ();
        break;

      case 156: // TupleType
        yylhs.value.emplace< TupleType::Ptr > ();
        break;

      case 131: // TypeCastingExpression
        yylhs.value.emplace< TypeCastingExpression::Ptr > ();
        break;

      case 153: // Types
      case 161: // FunctionParameters
      case 162: // MaybeFunctionParameters
        yylhs.value.emplace< Types::Ptr > ();
        break;

      case 139: // UndefinedLiteral
        yylhs.value.emplace< UndefLiteral::Ptr > ();
        break;

      case 135: // UniversalQuantifierExpression
        yylhs.value.emplace< UniversalQuantifierExpression::Ptr > ();
        break;

      case 119: // UpdateRule
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
      case 140: // BooleanLiteral
      case 141: // IntegerLiteral
      case 142: // RationalLiteral
      case 143: // DecimalLiteral
      case 144: // BinaryLiteral
      case 145: // StringLiteral
        yylhs.value.emplace< ValueLiteral::Ptr > ();
        break;

      case 177: // VariableBinding
        yylhs.value.emplace< VariableBinding::Ptr > ();
        break;

      case 176: // VariableBindings
        yylhs.value.emplace< VariableBindings::Ptr > ();
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        yylhs.value.emplace< VariableDefinition::Ptr > ();
        break;

      case 163: // Parameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        yylhs.value.emplace< VariableDefinitions::Ptr > ();
        break;

      case 121: // WhileRule
        yylhs.value.emplace< WhileRule::Ptr > ();
        break;

      case 154: // Type
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
#line 413 "../../obj/src/GrammarParser.y"
  {
      m_specification.setHeader( yystack_[1].value.as < HeaderDefinition::Ptr > () );
      m_specification.setDefinitions( yystack_[0].value.as < Definitions::Ptr > () );
      m_specification.setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 2669 "GrammarParser.cpp"
    break;

  case 3:
#line 423 "../../obj/src/GrammarParser.y"
  {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2679 "GrammarParser.cpp"
    break;

  case 4:
#line 429 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2687 "GrammarParser.cpp"
    break;

  case 5:
#line 437 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2697 "GrammarParser.cpp"
    break;

  case 6:
#line 443 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2707 "GrammarParser.cpp"
    break;

  case 7:
#line 453 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2717 "GrammarParser.cpp"
    break;

  case 8:
#line 459 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2725 "GrammarParser.cpp"
    break;

  case 9:
#line 463 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2733 "GrammarParser.cpp"
    break;

  case 10:
#line 471 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2741 "GrammarParser.cpp"
    break;

  case 11:
#line 475 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2749 "GrammarParser.cpp"
    break;

  case 12:
#line 479 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2757 "GrammarParser.cpp"
    break;

  case 13:
#line 483 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2765 "GrammarParser.cpp"
    break;

  case 14:
#line 487 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 2773 "GrammarParser.cpp"
    break;

  case 15:
#line 491 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 2781 "GrammarParser.cpp"
    break;

  case 16:
#line 495 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingPathDefinition::Ptr > ();
  }
#line 2789 "GrammarParser.cpp"
    break;

  case 17:
#line 499 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 2797 "GrammarParser.cpp"
    break;

  case 18:
#line 503 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 2805 "GrammarParser.cpp"
    break;

  case 19:
#line 511 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2813 "GrammarParser.cpp"
    break;

  case 20:
#line 515 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2821 "GrammarParser.cpp"
    break;

  case 21:
#line 523 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2829 "GrammarParser.cpp"
    break;

  case 22:
#line 531 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2838 "GrammarParser.cpp"
    break;

  case 23:
#line 536 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2848 "GrammarParser.cpp"
    break;

  case 24:
#line 542 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 2856 "GrammarParser.cpp"
    break;

  case 25:
#line 550 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2866 "GrammarParser.cpp"
    break;

  case 26:
#line 556 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2875 "GrammarParser.cpp"
    break;

  case 27:
#line 561 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
  }
#line 2886 "GrammarParser.cpp"
    break;

  case 28:
#line 568 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2896 "GrammarParser.cpp"
    break;

  case 29:
#line 574 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2904 "GrammarParser.cpp"
    break;

  case 30:
#line 578 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2912 "GrammarParser.cpp"
    break;

  case 31:
#line 586 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = Ast::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      const auto initially = yylhs.value.as < FunctionDefinition::Ptr > ()->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->setFunction( yylhs.value.as < FunctionDefinition::Ptr > () );
      }
  }
#line 2927 "GrammarParser.cpp"
    break;

  case 32:
#line 601 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 2935 "GrammarParser.cpp"
    break;

  case 33:
#line 605 "../../obj/src/GrammarParser.y"
  {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 2945 "GrammarParser.cpp"
    break;

  case 34:
#line 611 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 2953 "GrammarParser.cpp"
    break;

  case 35:
#line 619 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2964 "GrammarParser.cpp"
    break;

  case 36:
#line 626 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2974 "GrammarParser.cpp"
    break;

  case 37:
#line 636 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2982 "GrammarParser.cpp"
    break;

  case 38:
#line 644 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2990 "GrammarParser.cpp"
    break;

  case 39:
#line 648 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2998 "GrammarParser.cpp"
    break;

  case 40:
#line 656 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InvariantDefinition::Ptr > () = Ast::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3006 "GrammarParser.cpp"
    break;

  case 41:
#line 664 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3014 "GrammarParser.cpp"
    break;

  case 42:
#line 668 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3022 "GrammarParser.cpp"
    break;

  case 43:
#line 680 "../../obj/src/GrammarParser.y"
  {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3032 "GrammarParser.cpp"
    break;

  case 44:
#line 686 "../../obj/src/GrammarParser.y"
  {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 3042 "GrammarParser.cpp"
    break;

  case 45:
#line 696 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 3050 "GrammarParser.cpp"
    break;

  case 46:
#line 700 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 3058 "GrammarParser.cpp"
    break;

  case 47:
#line 704 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 3066 "GrammarParser.cpp"
    break;

  case 48:
#line 708 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 3074 "GrammarParser.cpp"
    break;

  case 49:
#line 712 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LocalRule::Ptr > ();
  }
#line 3082 "GrammarParser.cpp"
    break;

  case 50:
#line 716 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 3090 "GrammarParser.cpp"
    break;

  case 51:
#line 720 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 3098 "GrammarParser.cpp"
    break;

  case 52:
#line 724 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 3106 "GrammarParser.cpp"
    break;

  case 53:
#line 728 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 3114 "GrammarParser.cpp"
    break;

  case 54:
#line 732 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 3122 "GrammarParser.cpp"
    break;

  case 55:
#line 736 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 3130 "GrammarParser.cpp"
    break;

  case 56:
#line 740 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 3138 "GrammarParser.cpp"
    break;

  case 57:
#line 744 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 3146 "GrammarParser.cpp"
    break;

  case 58:
#line 752 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3154 "GrammarParser.cpp"
    break;

  case 59:
#line 760 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3162 "GrammarParser.cpp"
    break;

  case 60:
#line 764 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3170 "GrammarParser.cpp"
    break;

  case 61:
#line 772 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3178 "GrammarParser.cpp"
    break;

  case 62:
#line 776 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 3186 "GrammarParser.cpp"
    break;

  case 63:
#line 784 "../../obj/src/GrammarParser.y"
  {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3196 "GrammarParser.cpp"
    break;

  case 64:
#line 790 "../../obj/src/GrammarParser.y"
  {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3206 "GrammarParser.cpp"
    break;

  case 65:
#line 800 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3214 "GrammarParser.cpp"
    break;

  case 66:
#line 804 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3222 "GrammarParser.cpp"
    break;

  case 67:
#line 808 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3230 "GrammarParser.cpp"
    break;

  case 68:
#line 816 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3238 "GrammarParser.cpp"
    break;

  case 69:
#line 824 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LocalRule::Ptr > () = Ast::make< LocalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < FunctionDefinitions::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3246 "GrammarParser.cpp"
    break;

  case 70:
#line 832 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3254 "GrammarParser.cpp"
    break;

  case 71:
#line 836 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3262 "GrammarParser.cpp"
    break;

  case 72:
#line 844 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3270 "GrammarParser.cpp"
    break;

  case 73:
#line 852 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3278 "GrammarParser.cpp"
    break;

  case 74:
#line 860 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3286 "GrammarParser.cpp"
    break;

  case 75:
#line 864 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3294 "GrammarParser.cpp"
    break;

  case 76:
#line 868 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3303 "GrammarParser.cpp"
    break;

  case 77:
#line 873 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3312 "GrammarParser.cpp"
    break;

  case 78:
#line 882 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3320 "GrammarParser.cpp"
    break;

  case 79:
#line 886 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3328 "GrammarParser.cpp"
    break;

  case 80:
#line 890 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3337 "GrammarParser.cpp"
    break;

  case 81:
#line 895 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3346 "GrammarParser.cpp"
    break;

  case 82:
#line 904 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3354 "GrammarParser.cpp"
    break;

  case 83:
#line 912 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 3362 "GrammarParser.cpp"
    break;

  case 84:
#line 920 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3370 "GrammarParser.cpp"
    break;

  case 85:
#line 932 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3381 "GrammarParser.cpp"
    break;

  case 86:
#line 939 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3391 "GrammarParser.cpp"
    break;

  case 87:
#line 949 "../../obj/src/GrammarParser.y"
  {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3399 "GrammarParser.cpp"
    break;

  case 88:
#line 953 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 3407 "GrammarParser.cpp"
    break;

  case 89:
#line 957 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3415 "GrammarParser.cpp"
    break;

  case 90:
#line 961 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 3423 "GrammarParser.cpp"
    break;

  case 91:
#line 965 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 3431 "GrammarParser.cpp"
    break;

  case 92:
#line 969 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 3439 "GrammarParser.cpp"
    break;

  case 93:
#line 973 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 3447 "GrammarParser.cpp"
    break;

  case 94:
#line 977 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 3455 "GrammarParser.cpp"
    break;

  case 95:
#line 981 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 3463 "GrammarParser.cpp"
    break;

  case 96:
#line 989 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< Ast::EmbracedExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3471 "GrammarParser.cpp"
    break;

  case 97:
#line 993 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 3479 "GrammarParser.cpp"
    break;

  case 98:
#line 997 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 3487 "GrammarParser.cpp"
    break;

  case 99:
#line 1001 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 3495 "GrammarParser.cpp"
    break;

  case 100:
#line 1005 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 3503 "GrammarParser.cpp"
    break;

  case 101:
#line 1009 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3511 "GrammarParser.cpp"
    break;

  case 102:
#line 1013 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 3519 "GrammarParser.cpp"
    break;

  case 103:
#line 1025 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3527 "GrammarParser.cpp"
    break;

  case 104:
#line 1029 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 3535 "GrammarParser.cpp"
    break;

  case 105:
#line 1033 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 3543 "GrammarParser.cpp"
    break;

  case 106:
#line 1037 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 3551 "GrammarParser.cpp"
    break;

  case 107:
#line 1041 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 3559 "GrammarParser.cpp"
    break;

  case 108:
#line 1045 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 3567 "GrammarParser.cpp"
    break;

  case 109:
#line 1049 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 3575 "GrammarParser.cpp"
    break;

  case 110:
#line 1053 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 3583 "GrammarParser.cpp"
    break;

  case 111:
#line 1057 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 3591 "GrammarParser.cpp"
    break;

  case 112:
#line 1061 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 3599 "GrammarParser.cpp"
    break;

  case 113:
#line 1065 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 3607 "GrammarParser.cpp"
    break;

  case 114:
#line 1069 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 3615 "GrammarParser.cpp"
    break;

  case 115:
#line 1073 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 3623 "GrammarParser.cpp"
    break;

  case 116:
#line 1077 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 3631 "GrammarParser.cpp"
    break;

  case 117:
#line 1081 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 3639 "GrammarParser.cpp"
    break;

  case 118:
#line 1085 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3647 "GrammarParser.cpp"
    break;

  case 119:
#line 1089 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3655 "GrammarParser.cpp"
    break;

  case 120:
#line 1093 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 3663 "GrammarParser.cpp"
    break;

  case 121:
#line 1101 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 3671 "GrammarParser.cpp"
    break;

  case 122:
#line 1105 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 3679 "GrammarParser.cpp"
    break;

  case 123:
#line 1109 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 3687 "GrammarParser.cpp"
    break;

  case 124:
#line 1117 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > (), arguments );
  }
#line 3696 "GrammarParser.cpp"
    break;

  case 125:
#line 1122 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), arguments );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3707 "GrammarParser.cpp"
    break;

  case 126:
#line 1129 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3717 "GrammarParser.cpp"
    break;

  case 127:
#line 1135 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 3725 "GrammarParser.cpp"
    break;

  case 128:
#line 1143 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 3734 "GrammarParser.cpp"
    break;

  case 129:
#line 1148 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3745 "GrammarParser.cpp"
    break;

  case 130:
#line 1155 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3755 "GrammarParser.cpp"
    break;

  case 131:
#line 1161 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 3763 "GrammarParser.cpp"
    break;

  case 132:
#line 1169 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 3771 "GrammarParser.cpp"
    break;

  case 133:
#line 1177 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3782 "GrammarParser.cpp"
    break;

  case 134:
#line 1184 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3792 "GrammarParser.cpp"
    break;

  case 135:
#line 1190 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 3800 "GrammarParser.cpp"
    break;

  case 136:
#line 1198 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3808 "GrammarParser.cpp"
    break;

  case 137:
#line 1206 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3816 "GrammarParser.cpp"
    break;

  case 138:
#line 1214 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3824 "GrammarParser.cpp"
    break;

  case 139:
#line 1222 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3832 "GrammarParser.cpp"
    break;

  case 140:
#line 1230 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3840 "GrammarParser.cpp"
    break;

  case 141:
#line 1238 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3848 "GrammarParser.cpp"
    break;

  case 142:
#line 1246 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3856 "GrammarParser.cpp"
    break;

  case 143:
#line 1259 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 3864 "GrammarParser.cpp"
    break;

  case 144:
#line 1263 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3872 "GrammarParser.cpp"
    break;

  case 145:
#line 1267 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3880 "GrammarParser.cpp"
    break;

  case 146:
#line 1271 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3888 "GrammarParser.cpp"
    break;

  case 147:
#line 1275 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3896 "GrammarParser.cpp"
    break;

  case 148:
#line 1279 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3904 "GrammarParser.cpp"
    break;

  case 149:
#line 1283 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3912 "GrammarParser.cpp"
    break;

  case 150:
#line 1287 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 3920 "GrammarParser.cpp"
    break;

  case 151:
#line 1291 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 3928 "GrammarParser.cpp"
    break;

  case 152:
#line 1295 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 3936 "GrammarParser.cpp"
    break;

  case 153:
#line 1299 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 3944 "GrammarParser.cpp"
    break;

  case 154:
#line 1303 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 3952 "GrammarParser.cpp"
    break;

  case 155:
#line 1311 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3961 "GrammarParser.cpp"
    break;

  case 156:
#line 1320 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3971 "GrammarParser.cpp"
    break;

  case 157:
#line 1326 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3981 "GrammarParser.cpp"
    break;

  case 158:
#line 1336 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3989 "GrammarParser.cpp"
    break;

  case 159:
#line 1344 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3997 "GrammarParser.cpp"
    break;

  case 160:
#line 1352 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4005 "GrammarParser.cpp"
    break;

  case 161:
#line 1360 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4013 "GrammarParser.cpp"
    break;

  case 162:
#line 1364 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4021 "GrammarParser.cpp"
    break;

  case 163:
#line 1372 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 4029 "GrammarParser.cpp"
    break;

  case 164:
#line 1380 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4037 "GrammarParser.cpp"
    break;

  case 165:
#line 1388 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4048 "GrammarParser.cpp"
    break;

  case 166:
#line 1395 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4058 "GrammarParser.cpp"
    break;

  case 167:
#line 1401 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 4066 "GrammarParser.cpp"
    break;

  case 168:
#line 1409 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4076 "GrammarParser.cpp"
    break;

  case 169:
#line 1418 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4089 "GrammarParser.cpp"
    break;

  case 170:
#line 1429 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4099 "GrammarParser.cpp"
    break;

  case 171:
#line 1438 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4110 "GrammarParser.cpp"
    break;

  case 172:
#line 1445 "../../obj/src/GrammarParser.y"
  {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4120 "GrammarParser.cpp"
    break;

  case 173:
#line 1454 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4128 "GrammarParser.cpp"
    break;

  case 174:
#line 1466 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4139 "GrammarParser.cpp"
    break;

  case 175:
#line 1473 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4149 "GrammarParser.cpp"
    break;

  case 176:
#line 1482 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4157 "GrammarParser.cpp"
    break;

  case 177:
#line 1486 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4165 "GrammarParser.cpp"
    break;

  case 178:
#line 1490 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4173 "GrammarParser.cpp"
    break;

  case 179:
#line 1494 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4181 "GrammarParser.cpp"
    break;

  case 180:
#line 1498 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4189 "GrammarParser.cpp"
    break;

  case 181:
#line 1502 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4197 "GrammarParser.cpp"
    break;

  case 182:
#line 1510 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4205 "GrammarParser.cpp"
    break;

  case 183:
#line 1518 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = Ast::make< TupleType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), subTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4216 "GrammarParser.cpp"
    break;

  case 184:
#line 1529 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = Ast::make< RecordType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4227 "GrammarParser.cpp"
    break;

  case 185:
#line 1540 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4235 "GrammarParser.cpp"
    break;

  case 186:
#line 1548 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4243 "GrammarParser.cpp"
    break;

  case 187:
#line 1556 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4251 "GrammarParser.cpp"
    break;

  case 188:
#line 1568 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4262 "GrammarParser.cpp"
    break;

  case 189:
#line 1575 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4272 "GrammarParser.cpp"
    break;

  case 190:
#line 1585 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 4280 "GrammarParser.cpp"
    break;

  case 191:
#line 1589 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 4288 "GrammarParser.cpp"
    break;

  case 192:
#line 1597 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4299 "GrammarParser.cpp"
    break;

  case 193:
#line 1604 "../../obj/src/GrammarParser.y"
  {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4309 "GrammarParser.cpp"
    break;

  case 194:
#line 1618 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4317 "GrammarParser.cpp"
    break;

  case 195:
#line 1622 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 4325 "GrammarParser.cpp"
    break;

  case 196:
#line 1630 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4333 "GrammarParser.cpp"
    break;

  case 197:
#line 1634 "../../obj/src/GrammarParser.y"
  {
      const auto initializers = Ast::make< Initializers >( yylhs.location );
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
#line 4342 "GrammarParser.cpp"
    break;

  case 198:
#line 1643 "../../obj/src/GrammarParser.y"
  {
      auto initializers = yystack_[2].value.as < Initializers::Ptr > ();
      yystack_[0].value.as < Initializer::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4353 "GrammarParser.cpp"
    break;

  case 199:
#line 1650 "../../obj/src/GrammarParser.y"
  {
      auto initializers = Ast::make< Initializers >( yylhs.location );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4363 "GrammarParser.cpp"
    break;

  case 200:
#line 1660 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4372 "GrammarParser.cpp"
    break;

  case 201:
#line 1665 "../../obj/src/GrammarParser.y"
  {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), arguments, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4382 "GrammarParser.cpp"
    break;

  case 202:
#line 1671 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto lbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto rbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, lbToken, arguments, rbToken, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4393 "GrammarParser.cpp"
    break;

  case 203:
#line 1686 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 4401 "GrammarParser.cpp"
    break;

  case 204:
#line 1690 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 4410 "GrammarParser.cpp"
    break;

  case 205:
#line 1699 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < Ast::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 4421 "GrammarParser.cpp"
    break;

  case 206:
#line 1706 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4429 "GrammarParser.cpp"
    break;

  case 207:
#line 1718 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4437 "GrammarParser.cpp"
    break;

  case 208:
#line 1722 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 4446 "GrammarParser.cpp"
    break;

  case 209:
#line 1731 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 4457 "GrammarParser.cpp"
    break;

  case 210:
#line 1738 "../../obj/src/GrammarParser.y"
  {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 4467 "GrammarParser.cpp"
    break;

  case 211:
#line 1748 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4478 "GrammarParser.cpp"
    break;

  case 212:
#line 1755 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4488 "GrammarParser.cpp"
    break;

  case 213:
#line 1765 "../../obj/src/GrammarParser.y"
  {
      auto variable = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4497 "GrammarParser.cpp"
    break;

  case 214:
#line 1774 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4507 "GrammarParser.cpp"
    break;

  case 215:
#line 1780 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4515 "GrammarParser.cpp"
    break;

  case 216:
#line 1788 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4525 "GrammarParser.cpp"
    break;

  case 217:
#line 1794 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4533 "GrammarParser.cpp"
    break;

  case 218:
#line 1806 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4544 "GrammarParser.cpp"
    break;

  case 219:
#line 1813 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4554 "GrammarParser.cpp"
    break;

  case 220:
#line 1822 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4562 "GrammarParser.cpp"
    break;

  case 221:
#line 1834 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[2].value.as < FunctionDefinitions::Ptr > ();
      yystack_[0].value.as < FunctionDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 4573 "GrammarParser.cpp"
    break;

  case 222:
#line 1841 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< FunctionDefinitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < FunctionDefinition::Ptr > () );
      yylhs.value.as < FunctionDefinitions::Ptr > () = definitions;
  }
#line 4583 "GrammarParser.cpp"
    break;

  case 223:
#line 1850 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < FunctionDefinition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < FunctionDefinition::Ptr > () = definition;
  }
#line 4593 "GrammarParser.cpp"
    break;

  case 224:
#line 1856 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 4601 "GrammarParser.cpp"
    break;

  case 225:
#line 1860 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = nullptr;
  }
#line 4609 "GrammarParser.cpp"
    break;

  case 226:
#line 1867 "../../obj/src/GrammarParser.y"
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
#line 4625 "GrammarParser.cpp"
    break;

  case 227:
#line 1887 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4635 "GrammarParser.cpp"
    break;

  case 228:
#line 1893 "../../obj/src/GrammarParser.y"
  {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4645 "GrammarParser.cpp"
    break;

  case 229:
#line 1902 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4656 "GrammarParser.cpp"
    break;

  case 230:
#line 1909 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4667 "GrammarParser.cpp"
    break;

  case 231:
#line 1916 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 4675 "GrammarParser.cpp"
    break;

  case 232:
#line 1923 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4683 "GrammarParser.cpp"
    break;

  case 233:
#line 1930 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4691 "GrammarParser.cpp"
    break;


#line 4695 "GrammarParser.cpp"

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
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
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
    std::ptrdiff_t yycount = 0;
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
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
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
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
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
    std::ptrdiff_t yyi = 0;
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


  const short Parser::yypact_ninf_ = -294;

  const short Parser::yytable_ninf_ = -190;

  const short
  Parser::yypact_[] =
  {
      12,  -294,    37,    63,   143,    17,  -294,    -3,  -294,  -294,
    1792,    20,    35,  -294,  -294,    -6,    -7,    -7,    -7,    -7,
      -7,    -7,    -7,   348,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,   356,  -294,  -294,  -294,     2,
       2,     2,  1792,     2,  -294,  -294,  -294,  1792,  1871,  1871,
    1377,  1117,  1871,    -7,  -294,  -294,  -294,  -294,  -294,  -294,
    2541,    25,  -294,    39,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,   140,
    -294,  -294,  1857,    33,    31,    58,    71,    74,    41,   109,
      49,   118,  -294,  -294,   123,  -294,  -294,   138,    19,  -294,
       2,    23,  -294,    38,  2078,    42,  -294,  -294,  -294,   137,
     130,  2296,   111,  -294,   148,   139,  -294,   -40,  2331,    90,
      33,  1792,  1792,  1792,  1792,  1792,  1792,  1792,  1792,  1792,
    1792,  1792,  1792,  1792,  1792,  1792,  1792,  1792,     7,    -9,
    1182,  1247,    -7,  1377,  2541,   125,   166,  -294,     6,     7,
     151,  1727,    11,     7,     7,    29,  1792,    -7,     7,     7,
    1792,  1792,     2,  -294,  1792,     2,  1792,  1792,  1792,  -294,
    1792,  -294,  -294,    -7,  1792,  -294,  -294,  1792,  1792,  -294,
    2612,  2576,  2606,   488,   208,   208,   629,   136,   136,   163,
     163,   163,  -294,   488,   629,   136,   136,     7,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,   149,  -294,   183,   184,  -294,
     114,  2541,   192,  -294,   115,  -294,  2366,  1792,  -294,  1857,
     193,   161,   123,  -294,  -294,     2,   185,    15,   777,   847,
    -294,     2,    16,     2,     2,  1727,  1792,  1792,  1792,   917,
     987,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -294,   179,    47,   174,   199,   162,
     202,  -294,  -294,  2541,  -294,  -294,   194,   188,  -294,  2541,
    2541,  -294,  2226,  -294,  1916,  2155,  2261,  2401,  -294,   148,
    2541,  2541,  2436,   203,  -294,   123,   207,  -294,     7,  1792,
    1312,  -294,  -294,  -294,  -294,   189,  2541,  -294,   198,   205,
       2,  -294,  1792,  -294,  -294,   177,  -294,     2,   246,  1447,
    -294,   262,  1517,    48,  -294,   214,    51,  -294,  -294,     2,
      52,    54,  -294,  2117,  2191,  1957,   230,  1587,   209,  1657,
    1792,   -18,    45,  1727,     7,     7,  1792,  1792,  1792,  1792,
    -294,  -294,     7,    -7,   155,   160,   215,  -294,   237,  -294,
     168,  1792,     7,     7,  -294,  2541,  -294,    15,  -294,  -294,
    -294,  -294,  -294,  -294,  1727,     7,  1727,    16,  -294,  1792,
    1792,  1727,   236,  1727,  -294,  -294,  -294,  -294,  2541,  1727,
       7,  1727,     7,  -294,  -294,   274,  2541,  2541,  2541,  2541,
     240,   243,     7,  -294,     7,  -294,  -294,  2541,   247,   254,
    -294,  -294,   233,  -294,  -294,   235,  1998,   276,  1052,  -294,
    -294,   259,  -294,   263,   260,   264,  -294,  -294,  -294,   252,
    1792,  1792,     7,  1727,  1792,  1727,  1727,   261,   265,   266,
     461,  -294,  2471,  1727,  1727,  1792,   269,  -294,  -294,  2541,
    2541,   274,  -294,  2039,  -294,  -294,  -294,  1727,  1727,  -294,
    -294,  1727,  -294,  -294,  2506,  1857,   264,  1727,  -294,  -294,
    -294,  -294,   187,  -294,  -294,  -294
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   228,     0,   204,   203,
     232,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     8,    10,    11,    12,    13,
      14,    15,    16,    17,    18,     0,     3,   227,   231,     0,
       0,     0,     0,     0,   155,   157,   156,     0,     0,     0,
       0,     0,     0,     0,   161,   162,   158,   159,   160,   163,
     233,    87,    89,    98,   121,   122,    99,   123,    88,    90,
      91,    92,    93,    94,    95,   100,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   206,   124,
     229,   230,     0,    19,     0,     0,     0,   206,    38,     0,
      41,     0,     5,     7,   208,   215,   207,     0,     0,   219,
       0,     0,   210,     0,     0,     0,   120,   101,   102,     0,
       0,    86,     0,   172,   206,     0,   165,     0,    86,     0,
     164,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   200,   153,     0,   199,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   191,     0,
       0,     0,     0,   214,     0,     0,     0,     0,     0,    97,
       0,    96,   170,     0,     0,   167,   166,     0,     0,   142,
     117,   115,   116,   119,   103,   104,   110,   111,   112,   105,
     106,   107,   108,   118,   109,   113,   114,     0,   136,   176,
     177,   178,   179,   180,   181,   182,   132,   128,     0,   133,
       0,    86,     0,   125,     0,   205,    86,     0,    20,     0,
       0,     0,     0,   217,   193,     0,     0,     0,     0,     0,
      58,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    25,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    57,     0,    83,   121,     0,     0,
       0,    37,    39,    40,    42,   189,   190,     0,   213,   220,
     137,   218,     0,   209,     0,     0,     0,    85,   171,     0,
     173,    85,     0,     0,   175,   206,     0,   212,   191,     0,
       0,   135,   134,   127,   126,    96,   202,   198,     0,     0,
       0,   216,     0,    34,    36,     0,    32,     0,     0,     0,
      44,     0,     0,     0,   225,     0,     0,   222,   224,     0,
       0,     0,    73,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     169,   168,     0,     0,     0,   175,     0,   187,     0,   129,
       0,     0,     0,     0,   192,    22,    21,     0,    33,    81,
      79,    43,    77,    75,     0,   191,     0,     0,   223,     0,
       0,     0,     0,     0,    76,    74,    80,    78,    82,     0,
       0,     0,     0,    26,   188,   195,   140,   139,   138,   141,
     174,   211,     0,   185,     0,   131,   130,   201,     0,     0,
      35,    68,     0,    69,   221,     0,     0,    59,     0,    84,
      29,     0,    27,     0,     0,   197,   183,   184,   174,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    64,     0,     0,     0,     0,     0,    31,   186,    24,
      23,   195,    70,     0,    72,    60,    62,     0,     0,    61,
      63,     0,    30,    28,     0,     0,   197,     0,    65,    66,
      67,   194,     0,   226,    71,   196
  };

  const short
  Parser::yypgoto_[] =
  {
    -294,  -294,  -294,  -294,   291,   282,  -294,  -294,  -294,  -294,
    -294,   -51,  -294,  -294,  -294,  -294,  -294,  -134,   324,  -294,
    -294,  -294,  -294,  -119,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,   -49,   -10,     4,  -294,   251,   281,
    -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,  -294,  -294,   173,  -294,  -294,  -294,  -294,  -294,  -294,
    -294,   -91,  -294,  -294,   141,    30,  -140,  -294,  -294,  -294,
    -294,  -294,  -294,  -294,  -293,   167,  -118,  -132,  -133,   106,
     434,    27,   232,   -37,  -294,  -128,   -30,    34,    99,   178,
    -294,   -32,    44,    21,    -2,  -294,  -294
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    23,    24,    25,    26,    27,    28,    29,
      30,   314,   315,    31,    32,    33,    34,   319,   320,   252,
     253,   254,   440,   441,   255,   256,   257,   258,   259,   260,
     261,   262,   263,   264,   120,   154,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,   122,   123,   293,   275,   209,   210,   211,
     212,   213,   214,   276,   277,   231,   425,   447,   156,   157,
      88,    89,   105,   111,   296,   106,   112,   234,   108,   109,
     326,   327,   328,   110,     6,    11,    12
  };

  const short
  Parser::yytable_[] =
  {
      60,   155,   127,    37,   113,   356,   115,   230,   208,   107,
     186,     8,   268,     8,     8,     1,   313,   324,   187,   236,
      36,     5,     8,   270,   271,    35,     8,     8,   389,   278,
     233,     8,   114,    37,   233,     8,     8,   116,     7,   171,
     121,   128,    93,   174,    35,    92,    98,    38,   100,     8,
     390,     2,   117,   118,   207,     2,   129,     8,   176,   148,
       2,     2,   178,    13,     2,     2,     2,   294,   374,    56,
      90,   376,   379,     9,   380,     9,     9,   172,   158,   297,
     130,   175,   412,   167,     9,    91,   150,   152,     9,     9,
     272,   391,   149,     9,   150,   165,   175,     9,     9,   159,
     175,   220,   224,   152,   160,   322,   172,   311,    37,   377,
     175,     9,   175,   392,   -98,   337,   339,   161,   162,     9,
     164,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   155,   163,
     221,   221,   107,   226,    14,   283,   189,    15,    16,    17,
      18,    19,    20,    21,    22,   166,   273,   149,   355,   182,
     279,   280,   302,   304,   282,   265,   284,   285,   286,   183,
     287,   168,   187,   187,   290,   215,   169,   291,   292,   235,
     135,   136,   233,   235,   170,   179,   215,   151,   180,   185,
     215,   215,     2,   227,   152,   215,   215,   140,   141,   142,
     143,   184,   237,   152,   394,   395,   330,   331,   298,   309,
     342,   107,   400,   402,   299,   403,   406,   306,   228,   310,
     310,  -189,   408,   409,   229,   401,   187,   143,  -189,   366,
     300,   312,   301,    37,   215,   367,   333,   334,   335,   475,
     303,   308,   265,   265,   340,   229,   149,   341,   343,   265,
     421,   360,   423,   265,   265,   344,   345,   361,   317,   433,
     369,   352,   428,   329,   429,   353,   362,   375,   434,   140,
     141,   142,   143,   363,   131,   132,   133,   134,   372,   135,
     136,   137,   384,   404,   386,   405,   424,   418,   426,   357,
     221,   427,   451,   430,   138,   139,   140,   141,   142,   143,
     431,   432,   365,   436,   144,   443,   145,   146,   147,   444,
     446,   445,   448,   456,   102,    37,   410,   103,   457,   458,
     465,   460,   216,   265,   288,   215,   265,    37,   354,   269,
     388,   235,   472,   466,   473,   307,   396,   397,   398,   399,
     323,   265,   173,   265,   364,   414,     0,   265,    -2,    14,
     281,   407,    15,    16,    17,    18,    19,    20,    21,    22,
      15,    16,    17,    18,    19,    20,    21,    22,     0,   415,
     416,   215,   215,   378,   155,     0,     0,     0,   265,   215,
     265,     0,     0,     0,     0,   265,     0,   265,   317,   215,
     215,     0,     0,   265,     0,   265,     0,     2,   329,     0,
       0,     0,   215,     0,     0,     2,     0,     0,   442,     0,
       0,     0,   266,     0,     0,     0,     0,   215,     0,   215,
     449,   450,     0,     0,   453,     0,     0,     0,     0,   215,
     442,   215,     0,     0,     0,   464,    10,   265,     0,   265,
     265,     0,   267,     0,     0,     0,     0,   265,   265,     0,
      94,    95,    96,    97,    99,     0,   101,     0,     0,   215,
       0,   265,   265,     0,     0,   265,     0,     0,     0,     0,
       0,   265,     0,   104,   104,   104,     0,   104,     0,    39,
       0,     8,    40,    41,   124,   251,    42,     0,     0,   266,
     266,   438,     0,    43,     0,     0,   266,    44,    45,    46,
     266,   266,     0,     0,    47,    48,    49,     0,    50,     0,
      51,     0,     0,   459,     0,     0,   439,    52,    53,   267,
     267,     0,     0,     0,     0,     0,   267,   131,   132,   133,
     267,   267,   135,   136,   137,     0,     0,    54,    55,    56,
      57,    58,    59,     9,   104,     0,     0,   138,   139,   140,
     141,   142,   143,     0,     0,     0,     0,     0,     0,   145,
     146,   147,     0,     0,     0,     0,     0,     0,     0,   332,
     266,     0,     0,   266,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   217,     0,     0,   225,   124,   266,     0,
     266,     0,   232,     0,   266,     0,   232,     0,     0,   225,
     267,   274,     0,   267,     0,     0,   104,     0,     0,   104,
       0,     0,     0,     0,     0,     0,     0,   289,   267,     0,
     267,     0,     0,     0,   267,   266,     0,   266,     0,     0,
       0,     0,   266,     0,   266,     0,     0,     0,     0,     0,
     266,   295,   266,   371,     0,     0,   371,     0,     0,     0,
       0,     0,     0,     0,     0,   267,     0,   267,     0,     0,
       0,   371,   267,   371,   267,     0,     0,   393,     0,   232,
     267,   316,   267,   135,   136,   104,   325,   104,   104,     0,
       0,     0,     0,     0,   266,     0,   266,   266,   138,   139,
     140,   141,   142,   143,   266,   266,     0,     0,   411,     0,
     413,   146,   147,     0,     0,   417,     0,   419,   266,   266,
       0,     0,   266,   420,   267,   422,   267,   267,   266,     0,
       0,     0,     0,     0,   267,   267,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   267,   267,
       0,     0,   267,     0,   232,     0,     0,     0,   267,     0,
       0,   368,     0,     0,     0,     0,     0,   452,     0,   454,
     455,     0,     0,   325,     0,     0,     0,   462,   463,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   318,     0,
       0,   468,   469,     0,     0,   470,     0,   232,     0,     0,
     238,   474,   239,     0,   240,   241,   242,     8,   243,   244,
     245,   316,   246,     0,     0,   247,     0,     0,     0,     0,
       0,   325,   248,    44,    45,    46,     0,     0,     0,     0,
       0,    48,    49,     0,    50,     0,    51,     0,   249,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   321,     0,
       0,   250,     0,    54,    55,    56,    57,    58,    59,     9,
     238,     0,   239,     0,   240,   241,   242,     8,   243,   244,
     245,     0,   246,     0,     0,   247,     0,     0,     0,     0,
       0,     0,   248,    44,    45,    46,     0,     0,     0,     0,
       0,    48,    49,     0,    50,     0,    51,     0,   249,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   336,     0,
       0,   250,     0,    54,    55,    56,    57,    58,    59,     9,
     238,     0,   239,     0,   240,   241,   242,     8,   243,   244,
     245,     0,   246,     0,     0,   247,     0,     0,     0,     0,
       0,     0,   248,    44,    45,    46,     0,     0,     0,     0,
       0,    48,    49,     0,    50,     0,    51,     0,   249,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   338,     0,
       0,   250,     0,    54,    55,    56,    57,    58,    59,     9,
     238,     0,   239,     0,   240,   241,   242,     8,   243,   244,
     245,     0,   246,     0,     0,   247,     0,     0,     0,     0,
       0,     0,   248,    44,    45,    46,     0,     0,     0,     0,
       0,    48,    49,     0,    50,     0,    51,     0,   249,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,   437,     0,     0,     0,     0,     0,     0,
       0,   250,     0,    54,    55,    56,    57,    58,    59,     9,
      39,     0,     8,    40,    41,     0,     0,    42,     0,     0,
       0,     0,   438,     0,    43,     0,     0,     0,    44,    45,
      46,     0,     0,     0,     0,    47,    48,    49,     0,    50,
       0,    51,     0,     0,     0,     0,     0,   439,    52,    53,
       0,     0,     0,     0,     0,     0,     0,     0,   125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,    55,
      56,    57,    58,    59,     9,    39,     0,     8,    40,    41,
       0,     0,    42,     0,     0,     0,     0,     0,     0,    43,
       0,     0,     0,    44,    45,    46,     0,     0,     0,     0,
      47,    48,    49,     0,    50,     0,    51,   126,     0,     0,
       0,     0,     0,    52,    53,     0,     0,     0,     0,     0,
       0,     0,     0,   218,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    55,    56,    57,    58,    59,     9,
      39,     0,     8,    40,    41,     0,     0,    42,     0,     0,
       0,     0,     0,     0,    43,     0,     0,     0,    44,    45,
      46,     0,     0,     0,     0,    47,    48,    49,     0,    50,
     219,    51,     0,     0,     0,     0,     0,     0,    52,    53,
       0,     0,     0,     0,     0,     0,     0,     0,   222,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,    55,
      56,    57,    58,    59,     9,    39,     0,     8,    40,    41,
       0,     0,    42,     0,     0,     0,     0,     0,     0,    43,
       0,     0,     0,    44,    45,    46,     0,     0,     0,     0,
      47,    48,    49,     0,    50,   223,    51,     0,     0,     0,
       0,     0,     0,    52,    53,     0,     0,     0,     0,     0,
       0,     0,     0,   358,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    55,    56,    57,    58,    59,     9,
      39,     0,     8,    40,    41,     0,     0,    42,     0,     0,
       0,     0,     0,     0,    43,     0,     0,     0,    44,    45,
      46,     0,     0,     0,     0,    47,    48,    49,     0,    50,
     359,    51,     0,     0,     0,     0,     0,     0,    52,    53,
       0,     0,     0,     0,     0,     0,     0,     0,   119,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,    55,
      56,    57,    58,    59,     9,    39,     0,     8,    40,    41,
       0,     0,    42,     0,     0,     0,     0,     0,     0,    43,
       0,     0,     0,    44,    45,    46,     0,     0,     0,     0,
      47,    48,    49,     0,    50,     0,    51,     0,     0,     0,
       0,     0,     0,    52,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    55,    56,    57,    58,    59,     9,
     238,   370,   239,     0,   240,   241,   242,     8,   243,   244,
     245,     0,   246,     0,     0,   247,     0,     0,     0,     0,
       0,     0,   248,    44,    45,    46,     0,     0,     0,     0,
       0,    48,    49,     0,    50,     0,    51,     0,   249,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   250,     0,    54,    55,    56,    57,    58,    59,     9,
     238,     0,   239,   373,   240,   241,   242,     8,   243,   244,
     245,     0,   246,     0,     0,   247,     0,     0,     0,     0,
       0,     0,   248,    44,    45,    46,     0,     0,     0,     0,
       0,    48,    49,     0,    50,     0,    51,     0,   249,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   250,     0,    54,    55,    56,    57,    58,    59,     9,
     238,     0,   239,     0,   240,   241,   242,     8,   243,   244,
     245,     0,   246,     0,     0,   247,     0,     0,     0,     0,
       0,     0,   248,    44,    45,    46,     0,     0,     0,     0,
       0,    48,    49,     0,    50,     0,    51,     0,   249,   385,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   250,     0,    54,    55,    56,    57,    58,    59,     9,
     238,     0,   239,     0,   240,   241,   242,     8,   243,   244,
     245,     0,   246,     0,     0,   247,     0,     0,     0,     0,
       0,     0,   248,    44,    45,    46,     0,     0,     0,     0,
       0,    48,    49,     0,    50,     0,    51,     0,   249,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   250,   387,    54,    55,    56,    57,    58,    59,     9,
     238,     0,   239,     0,   240,   241,   242,     8,   243,   244,
     245,     0,   246,     0,     0,   247,     0,     0,     0,     0,
       0,     0,   248,    44,    45,    46,     0,     0,     0,     0,
       0,    48,    49,     0,    50,     0,    51,     0,   249,     0,
       0,     0,     0,     0,    53,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   250,     0,    54,    55,    56,    57,    58,    59,     9,
      39,     0,     8,    40,    41,     0,     0,    42,     0,     0,
       0,     0,     0,     0,    43,     0,     0,     0,    44,    45,
      46,     0,     0,     0,     0,    47,    48,    49,     0,    50,
       0,    51,     0,     0,     0,     0,     0,     0,    52,    53,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    54,    55,
      56,    57,    58,    59,     9,    39,     0,     8,    40,    41,
       0,     0,    42,     0,     0,     0,     0,     0,     0,    43,
       0,     8,     0,    44,    45,    46,     0,     0,     0,     0,
      47,    48,    49,     0,   153,     0,    51,    44,    45,    46,
       0,     0,     0,    52,    53,    48,    49,     0,    50,     0,
      51,     0,     0,     0,     0,     0,     0,     0,    53,     0,
       0,     0,     0,    54,    55,    56,    57,    58,    59,     9,
     347,     0,     0,     0,     0,     0,     0,    54,    55,    56,
      57,    58,    59,     9,     0,   131,   132,   133,   134,     0,
     135,   136,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,   383,     0,     0,     0,   144,     0,   145,   146,   147,
       0,     0,     0,     0,     0,     0,   131,   132,   133,   134,
       0,   135,   136,   137,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   138,   139,   140,   141,
     142,   143,   435,     0,     0,     0,   144,     0,   145,   146,
     147,     0,     0,     0,     0,     0,     0,   131,   132,   133,
     134,     0,   135,   136,   137,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   138,   139,   140,
     141,   142,   143,   467,     0,     0,     0,   144,     0,   145,
     146,   147,     0,     0,     0,     0,     0,     0,   131,   132,
     133,   134,     0,   135,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
     140,   141,   142,   143,   177,     0,     0,     0,   144,     0,
     145,   146,   147,     0,     0,     0,     0,   131,   132,   133,
     134,     0,   135,   136,   137,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   138,   139,   140,
     141,   142,   143,   381,     0,     0,     0,   144,     0,   145,
     146,   147,     0,     0,     0,     0,   131,   132,   133,   134,
       0,   135,   136,   137,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   138,   139,   140,   141,
     142,   143,   348,     0,     0,     0,   144,     0,   145,   146,
     147,     0,     0,     0,   131,   132,   133,   134,     0,   135,
     136,   137,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
     382,     0,     0,     0,   144,     0,   145,   146,   147,     0,
     131,   132,   133,   134,     0,   135,   136,   137,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     138,   139,   140,   141,   142,   143,     0,   346,     0,     0,
     144,     0,   145,   146,   147,   131,   132,   133,   134,     0,
     135,   136,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,     0,     0,     0,   349,   144,     0,   145,   146,   147,
     131,   132,   133,   134,     0,   135,   136,   137,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     138,   139,   140,   141,   142,   143,     0,     0,     0,     0,
     144,     0,   145,   146,   147,   131,   132,   133,   134,     0,
     135,   136,   137,     0,   181,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,     0,     0,     0,     0,   144,     0,   145,   146,   147,
     131,   132,   133,   134,     0,   135,   136,   137,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     138,   139,   140,   141,   142,   143,     0,   188,     0,     0,
     144,     0,   145,   146,   147,   131,   132,   133,   134,     0,
     135,   136,   137,     0,   305,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,     0,     0,     0,     0,   144,     0,   145,   146,   147,
     131,   132,   133,   134,     0,   135,   136,   137,     0,   350,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     138,   139,   140,   141,   142,   143,     0,     0,     0,     0,
     144,     0,   145,   146,   147,   131,   132,   133,   134,     0,
     135,   136,   137,     0,     0,     0,   351,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,     0,     0,     0,     0,   144,     0,   145,   146,   147,
     131,   132,   133,   134,     0,   135,   136,   137,     0,     0,
       0,     0,     0,     0,   461,     0,     0,     0,     0,     0,
     138,   139,   140,   141,   142,   143,     0,     0,     0,     0,
     144,     0,   145,   146,   147,   131,   132,   133,   134,     0,
     135,   136,   137,     0,     0,     0,     0,     0,   471,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,     0,     0,     0,     0,   144,     0,   145,   146,   147,
     131,   132,   133,   134,     0,   135,   136,   137,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     138,   139,   140,   141,   142,   143,     0,     0,     0,     0,
     144,     0,   145,   146,   147,   131,     0,   133,     0,     0,
     135,   136,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,     0,     0,     0,     0,   131,     0,   145,   146,   147,
     135,   136,   137,     0,     0,     0,   135,   136,   137,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,   138,   139,   140,   141,   142,   143,   145,   146,   147,
       0,     0,     0,   145,   146,   147
  };

  const short
  Parser::yycheck_[] =
  {
      10,    92,    51,     5,    41,   298,    43,     1,   148,    39,
      50,    20,     1,    20,    20,     3,     1,     1,    58,   159,
       3,     0,    20,   163,   164,     4,    20,    20,    46,   169,
     158,    20,    42,    35,   162,    20,    20,    47,     1,    20,
      50,    51,    15,    20,    23,    51,    19,    50,    21,    20,
      68,    49,    48,    49,    47,    49,    52,    20,    20,    34,
      49,    49,    20,     0,    49,    49,    49,   207,    20,    78,
      50,    20,    20,    82,    20,    82,    82,    58,    47,   207,
      53,    58,   375,    34,    82,    50,    47,    54,    82,    82,
      61,    46,    67,    82,    47,    54,    58,    82,    82,    68,
      58,   150,   151,    54,    46,   239,    58,   235,   110,    58,
      58,    82,    58,    68,    67,   249,   250,    46,    47,    82,
      46,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   229,    68,
     150,   151,   172,   153,     1,   175,    56,     4,     5,     6,
       7,     8,     9,    10,    11,    46,   166,    67,   298,    48,
     170,   171,    48,    48,   174,   161,   176,   177,   178,    58,
     180,    53,    58,    58,   184,   148,    53,   187,   188,   158,
      44,    45,   310,   162,    46,    48,   159,    47,    58,    50,
     163,   164,    49,    68,    54,   168,   169,    61,    62,    63,
      64,    53,    51,    54,   344,   345,   243,   244,    59,    48,
      48,   241,   352,    58,    65,    60,    48,   227,    52,    58,
      58,    61,   362,   363,    58,   353,    58,    64,    68,    52,
      47,    46,    48,   235,   207,    58,   246,   247,   248,    52,
      48,    48,   238,   239,    70,    58,    67,    48,    46,   245,
     390,   300,   392,   249,   250,    61,    68,    68,   237,    24,
      14,    58,   402,   242,   404,    58,    68,    53,    33,    61,
      62,    63,    64,    68,    39,    40,    41,    42,    16,    44,
      45,    46,    52,    68,    75,    48,    12,    51,    48,   299,
     300,    48,   432,    46,    59,    60,    61,    62,    63,    64,
      46,    68,   312,    27,    69,    46,    71,    72,    73,    46,
      46,    51,    60,    52,    23,   317,   367,    35,    53,    53,
      51,   440,   149,   319,   183,   298,   322,   329,   298,   162,
     340,   310,   465,   451,   466,   229,   346,   347,   348,   349,
     241,   337,   110,   339,   310,   377,    -1,   343,     0,     1,
     172,   361,     4,     5,     6,     7,     8,     9,    10,    11,
       4,     5,     6,     7,     8,     9,    10,    11,    -1,   379,
     380,   344,   345,   329,   465,    -1,    -1,    -1,   374,   352,
     376,    -1,    -1,    -1,    -1,   381,    -1,   383,   367,   362,
     363,    -1,    -1,   389,    -1,   391,    -1,    49,   377,    -1,
      -1,    -1,   375,    -1,    -1,    49,    -1,    -1,   418,    -1,
      -1,    -1,   161,    -1,    -1,    -1,    -1,   390,    -1,   392,
     430,   431,    -1,    -1,   434,    -1,    -1,    -1,    -1,   402,
     440,   404,    -1,    -1,    -1,   445,     2,   433,    -1,   435,
     436,    -1,   161,    -1,    -1,    -1,    -1,   443,   444,    -1,
      16,    17,    18,    19,    20,    -1,    22,    -1,    -1,   432,
      -1,   457,   458,    -1,    -1,   461,    -1,    -1,    -1,    -1,
      -1,   467,    -1,    39,    40,    41,    -1,    43,    -1,    18,
      -1,    20,    21,    22,    50,   161,    25,    -1,    -1,   238,
     239,    30,    -1,    32,    -1,    -1,   245,    36,    37,    38,
     249,   250,    -1,    -1,    43,    44,    45,    -1,    47,    -1,
      49,    -1,    -1,    52,    -1,    -1,    55,    56,    57,   238,
     239,    -1,    -1,    -1,    -1,    -1,   245,    39,    40,    41,
     249,   250,    44,    45,    46,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,   110,    -1,    -1,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   245,
     319,    -1,    -1,   322,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   149,    -1,    -1,   152,   153,   337,    -1,
     339,    -1,   158,    -1,   343,    -1,   162,    -1,    -1,   165,
     319,   167,    -1,   322,    -1,    -1,   172,    -1,    -1,   175,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   183,   337,    -1,
     339,    -1,    -1,    -1,   343,   374,    -1,   376,    -1,    -1,
      -1,    -1,   381,    -1,   383,    -1,    -1,    -1,    -1,    -1,
     389,   207,   391,   319,    -1,    -1,   322,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   374,    -1,   376,    -1,    -1,
      -1,   337,   381,   339,   383,    -1,    -1,   343,    -1,   235,
     389,   237,   391,    44,    45,   241,   242,   243,   244,    -1,
      -1,    -1,    -1,    -1,   433,    -1,   435,   436,    59,    60,
      61,    62,    63,    64,   443,   444,    -1,    -1,   374,    -1,
     376,    72,    73,    -1,    -1,   381,    -1,   383,   457,   458,
      -1,    -1,   461,   389,   433,   391,   435,   436,   467,    -1,
      -1,    -1,    -1,    -1,   443,   444,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   457,   458,
      -1,    -1,   461,    -1,   310,    -1,    -1,    -1,   467,    -1,
      -1,   317,    -1,    -1,    -1,    -1,    -1,   433,    -1,   435,
     436,    -1,    -1,   329,    -1,    -1,    -1,   443,   444,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,   457,   458,    -1,    -1,   461,    -1,   353,    -1,    -1,
      13,   467,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,   367,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,   377,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      13,    -1,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      13,    -1,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      13,    -1,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      18,    -1,    20,    21,    22,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    30,    -1,    32,    -1,    -1,    -1,    36,    37,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    47,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    82,    18,    -1,    20,    21,    22,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    47,    -1,    49,    50,    -1,    -1,
      -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      18,    -1,    20,    21,    22,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    82,    18,    -1,    20,    21,    22,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    47,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      18,    -1,    20,    21,    22,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    47,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    82,    18,    -1,    20,    21,    22,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    -1,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    47,    -1,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      13,    14,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      13,    -1,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      13,    -1,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,    52,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      13,    -1,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      13,    -1,    15,    -1,    17,    18,    19,    20,    21,    22,
      23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      18,    -1,    20,    21,    22,    -1,    -1,    25,    -1,    -1,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,
      38,    -1,    -1,    -1,    -1,    43,    44,    45,    -1,    47,
      -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,
      78,    79,    80,    81,    82,    18,    -1,    20,    21,    22,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    32,
      -1,    20,    -1,    36,    37,    38,    -1,    -1,    -1,    -1,
      43,    44,    45,    -1,    47,    -1,    49,    36,    37,    38,
      -1,    -1,    -1,    56,    57,    44,    45,    -1,    47,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,    -1,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    24,    -1,    -1,    -1,    69,    -1,    71,    72,    73,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    24,    -1,    -1,    -1,    69,    -1,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,
      42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    64,    24,    -1,    -1,    -1,    69,    -1,    71,
      72,    73,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,
      41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,
      61,    62,    63,    64,    26,    -1,    -1,    -1,    69,    -1,
      71,    72,    73,    -1,    -1,    -1,    -1,    39,    40,    41,
      42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    64,    26,    -1,    -1,    -1,    69,    -1,    71,
      72,    73,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    27,    -1,    -1,    -1,    69,    -1,    71,    72,
      73,    -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      29,    -1,    -1,    -1,    69,    -1,    71,    72,    73,    -1,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    31,    -1,    -1,
      69,    -1,    71,    72,    73,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    33,    69,    -1,    71,    72,    73,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      69,    -1,    71,    72,    73,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    66,    -1,    -1,
      69,    -1,    71,    72,    73,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      69,    -1,    71,    72,    73,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      69,    -1,    71,    72,    73,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,
      39,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      59,    60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,
      69,    -1,    71,    72,    73,    39,    -1,    41,    -1,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    39,    -1,    71,    72,    73,
      44,    45,    46,    -1,    -1,    -1,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    59,    60,    61,    62,    63,    64,    71,    72,    73,
      -1,    -1,    -1,    71,    72,    73
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    49,    89,    90,   181,   182,     1,    20,    82,
     168,   183,   184,     0,     1,     4,     5,     6,     7,     8,
       9,    10,    11,    91,    92,    93,    94,    95,    96,    97,
      98,   101,   102,   103,   104,   181,     3,   182,    50,    18,
      21,    22,    25,    32,    36,    37,    38,    43,    44,    45,
      47,    49,    56,    57,    76,    77,    78,    79,    80,    81,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   150,   168,   169,
      50,    50,    51,   169,   168,   168,   168,   168,   169,   168,
     169,   168,    92,    93,   168,   170,   173,   174,   176,   177,
     181,   171,   174,   171,   123,   171,   123,   124,   124,     1,
     122,   123,   151,   152,   168,     1,    50,   122,   123,   124,
     169,    39,    40,    41,    42,    44,    45,    46,    59,    60,
      61,    62,    63,    64,    69,    71,    72,    73,    34,    67,
      47,    47,    54,    47,   123,   149,   166,   167,    47,    68,
      46,    46,    47,    68,    46,    54,    46,    34,    53,    53,
      46,    20,    58,   170,    20,    58,    20,    26,    20,    48,
      58,    48,    48,    58,    53,    50,    50,    58,    66,    56,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,    47,   154,   155,
     156,   157,   158,   159,   160,   169,   141,   168,     1,    48,
     122,   123,     1,    48,   122,   168,   123,    68,    52,    58,
       1,   163,   168,   173,   175,   181,   154,    51,    13,    15,
      17,    18,    19,    21,    22,    23,    25,    28,    35,    51,
      74,   106,   107,   108,   109,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   124,   126,   127,     1,   163,
     154,   154,    61,   123,   168,   154,   161,   162,   154,   123,
     123,   177,   123,   174,   123,   123,   123,   123,   152,   168,
     123,   123,   123,   153,   154,   168,   172,   173,    59,    65,
      47,    48,    48,    48,    48,    48,   123,   167,    48,    48,
      58,   173,    46,     1,    99,   100,   168,   181,     1,   105,
     106,     1,   105,   176,     1,   168,   178,   179,   180,   181,
     171,   171,   106,   123,   123,   123,     1,   105,     1,   105,
      70,    48,    48,    46,    61,    68,    31,    24,    27,    33,
      48,    50,    58,    58,   153,   154,   162,   123,     1,    48,
     122,    68,    68,    68,   175,   123,    52,    58,   168,    14,
      14,   106,    16,    16,    20,    53,    20,    58,   180,    20,
      20,    26,    29,    24,    52,    52,    75,    75,   123,    46,
      68,    46,    68,   106,   154,   154,   123,   123,   123,   123,
     154,   173,    58,    60,    68,    48,    48,   123,   154,   154,
      99,   106,   162,   106,   179,   123,   123,   106,    51,   106,
     106,   154,   106,   154,    12,   164,    48,    48,   154,   154,
      46,    46,    68,    24,    33,    24,    27,     1,    30,    55,
     110,   111,   123,    46,    46,    51,    46,   165,    60,   123,
     123,   154,   106,   123,   106,   106,    52,    53,    53,    52,
     111,    53,   106,   106,   123,    51,   164,    24,   106,   106,
     106,    52,   166,   165,   106,    52
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    88,    89,    90,    90,    91,    91,    92,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    94,
      94,    95,    96,    96,    96,    97,    97,    97,    97,    97,
      97,    98,    99,    99,    99,   100,   100,   101,   102,   102,
     103,   104,   104,   105,   105,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   106,   106,   107,   108,
     108,   109,   109,   110,   110,   111,   111,   111,   112,   113,
     114,   114,   115,   116,   117,   117,   117,   117,   118,   118,
     118,   118,   119,   120,   121,   122,   122,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   124,   124,   124,   124,
     124,   124,   124,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   126,   126,   126,   127,   127,   127,   127,   128,   128,
     128,   128,   129,   130,   130,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   138,   138,   138,   138,   138,   138,
     138,   138,   138,   138,   138,   139,   140,   140,   141,   142,
     143,   144,   144,   145,   146,   147,   147,   147,   148,   149,
     150,   151,   151,   152,   153,   153,   154,   154,   154,   154,
     154,   154,   155,   156,   157,   158,   159,   160,   161,   161,
     162,   162,   163,   163,   164,   164,   165,   165,   166,   166,
     167,   167,   167,   168,   168,   169,   169,   170,   170,   171,
     171,   172,   172,   173,   174,   174,   175,   175,   176,   176,
     177,   178,   178,   179,   179,   179,   180,   181,   181,   182,
     182,   182,   183,   184
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       4,     6,     6,     9,     9,     4,     6,     7,     9,     7,
       9,     8,     1,     2,     1,     3,     1,     4,     2,     4,
       4,     2,     4,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       6,     6,     6,     2,     1,     3,     3,     3,     4,     4,
       6,     8,     6,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     4,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     1,     1,
       1,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     1,     1,     1,     3,     4,     4,     3,     5,
       6,     6,     3,     3,     4,     4,     3,     4,     6,     6,
       6,     6,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     3,     3,     5,     5,
       3,     3,     1,     3,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     5,     4,     6,     3,     3,     1,
       1,     0,     3,     1,     4,     0,     4,     0,     3,     1,
       1,     5,     3,     1,     1,     3,     1,     1,     1,     3,
       1,     3,     1,     3,     2,     1,     2,     1,     3,     1,
       3,     3,     1,     2,     1,     1,     7,     2,     1,     3,
       3,     3,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"using\"",
  "\"invariant\"", "\"import\"", "\"function\"", "\"defined\"", "\"seq\"",
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
  "ImportDefinition", "Rules", "Rule", "SkipRule", "ConditionalRule",
  "CaseRule", "CaseLabels", "CaseLabel", "LetRule", "LocalRule",
  "ForallRule", "ChooseRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", "WhileRule", "Terms", "Term",
  "SimpleOrClaspedTerm", "OperatorExpression", "CallExpression",
  "DirectCallExpression", "MethodCallExpression", "LiteralCallExpression",
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
  "VariableBindings", "VariableBinding", "LocalFunctionDefinitions",
  "AttributedLocalFunctionDefinition", "LocalFunctionDefinition",
  "Attributes", "Attribute", "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   412,   412,   422,   428,   436,   442,   452,   458,   462,
     470,   474,   478,   482,   486,   490,   494,   498,   502,   510,
     514,   522,   530,   535,   541,   549,   555,   560,   567,   573,
     577,   585,   600,   604,   610,   618,   625,   635,   643,   647,
     655,   663,   667,   679,   685,   695,   699,   703,   707,   711,
     715,   719,   723,   727,   731,   735,   739,   743,   751,   759,
     763,   771,   775,   783,   789,   799,   803,   807,   815,   823,
     831,   835,   843,   851,   859,   863,   867,   872,   881,   885,
     889,   894,   903,   911,   919,   931,   938,   948,   952,   956,
     960,   964,   968,   972,   976,   980,   988,   992,   996,  1000,
    1004,  1008,  1012,  1024,  1028,  1032,  1036,  1040,  1044,  1048,
    1052,  1056,  1060,  1064,  1068,  1072,  1076,  1080,  1084,  1088,
    1092,  1100,  1104,  1108,  1116,  1121,  1128,  1134,  1142,  1147,
    1154,  1160,  1168,  1176,  1183,  1189,  1197,  1205,  1213,  1221,
    1229,  1237,  1245,  1258,  1262,  1266,  1270,  1274,  1278,  1282,
    1286,  1290,  1294,  1298,  1302,  1310,  1319,  1325,  1335,  1343,
    1351,  1359,  1363,  1371,  1379,  1387,  1394,  1400,  1408,  1417,
    1428,  1437,  1444,  1453,  1465,  1472,  1481,  1485,  1489,  1493,
    1497,  1501,  1509,  1517,  1528,  1539,  1547,  1555,  1567,  1574,
    1584,  1588,  1596,  1603,  1617,  1621,  1629,  1633,  1642,  1649,
    1659,  1664,  1670,  1685,  1689,  1698,  1705,  1717,  1721,  1730,
    1737,  1747,  1754,  1764,  1773,  1779,  1787,  1793,  1805,  1812,
    1821,  1833,  1840,  1849,  1855,  1859,  1866,  1886,  1892,  1901,
    1908,  1915,  1922,  1929
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
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
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


#line 50 "../../obj/src/GrammarParser.y"
} // libcasm_fe
#line 5878 "GrammarParser.cpp"

#line 1935 "../../obj/src/GrammarParser.y"


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
