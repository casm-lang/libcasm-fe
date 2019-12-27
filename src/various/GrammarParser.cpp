// A Bison parser, made by GNU Bison 3.5.

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

      case 125: // DirectCallExpression
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

      case 97: // FunctionDefinition
        value.YY_MOVE_OR_COPY< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Header
        value.YY_MOVE_OR_COPY< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 81: // "identifier"
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

      case 93: // InitDefinition
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

      case 96: // RuleDefinition
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

      case 88: // Specification
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

      case 100: // UsingDefinition
        value.YY_MOVE_OR_COPY< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 101: // UsingPathDefinition
        value.YY_MOVE_OR_COPY< UsingPathDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
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

      case 125: // DirectCallExpression
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

      case 97: // FunctionDefinition
        value.move< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Header
        value.move< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 81: // "identifier"
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

      case 93: // InitDefinition
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

      case 96: // RuleDefinition
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

      case 88: // Specification
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

      case 100: // UsingDefinition
        value.move< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 101: // UsingPathDefinition
        value.move< UsingPathDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
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
        value.copy< Ast::Token::Ptr > (that.value);
        break;

      case 177: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 176: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 178: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 153: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 115: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 124: // CallExpression
        value.copy< CallExpression::Ptr > (that.value);
        break;

      case 118: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 135: // CardinalityExpression
        value.copy< CardinalityExpression::Ptr > (that.value);
        break;

      case 110: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 108: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 109: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 132: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 113: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 131: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 107: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 162: // MaybeDefined
        value.copy< Defined::Ptr > (that.value);
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 90: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 95: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 125: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 94: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 98: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 99: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 134: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 121: // Term
      case 122: // SimpleOrClaspedTerm
      case 123: // OperatorExpression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 179: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 120: // Terms
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 158: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 112: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 97: // FunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 89: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 81: // "identifier"
      case 166: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 167: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 103: // ImportDefinition
        value.copy< ImportDefinition::Ptr > (that.value);
        break;

      case 128: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 93: // InitDefinition
        value.copy< InitDefinition::Ptr > (that.value);
        break;

      case 165: // Initializer
        value.copy< Initializer::Ptr > (that.value);
        break;

      case 164: // Initializers
        value.copy< Initializers::Ptr > (that.value);
        break;

      case 163: // MaybeInitially
        value.copy< Initially::Ptr > (that.value);
        break;

      case 102: // InvariantDefinition
        value.copy< InvariantDefinition::Ptr > (that.value);
        break;

      case 114: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 130: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 111: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 145: // ListLiteral
        value.copy< ListLiteral::Ptr > (that.value);
        break;

      case 136: // Literal
        value.copy< Literal::Ptr > (that.value);
        break;

      case 127: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (that.value);
        break;

      case 126: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 150: // Assignment
        value.copy< NamedExpression::Ptr > (that.value);
        break;

      case 149: // Assignments
        value.copy< NamedExpressions::Ptr > (that.value);
        break;

      case 146: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (that.value);
        break;

      case 148: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (that.value);
        break;

      case 155: // RecordType
        value.copy< RecordType::Ptr > (that.value);
        break;

      case 144: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (that.value);
        break;

      case 157: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 105: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 96: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 104: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 116: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 106: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 88: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 156: // TemplateType
        value.copy< TemplateType::Ptr > (that.value);
        break;

      case 147: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (that.value);
        break;

      case 154: // TupleType
        value.copy< TupleType::Ptr > (that.value);
        break;

      case 129: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 151: // Types
      case 159: // FunctionParameters
      case 160: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 137: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (that.value);
        break;

      case 133: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 117: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 100: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (that.value);
        break;

      case 101: // UsingPathDefinition
        value.copy< UsingPathDefinition::Ptr > (that.value);
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
      case 138: // BooleanLiteral
      case 139: // IntegerLiteral
      case 140: // RationalLiteral
      case 141: // DecimalLiteral
      case 142: // BinaryLiteral
      case 143: // StringLiteral
        value.copy< ValueLiteral::Ptr > (that.value);
        break;

      case 175: // VariableBinding
        value.copy< VariableBinding::Ptr > (that.value);
        break;

      case 174: // VariableBindings
        value.copy< VariableBindings::Ptr > (that.value);
        break;

      case 168: // Variable
      case 171: // TypedVariable
      case 172: // AttributedVariable
      case 173: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 161: // Parameters
      case 169: // AttributedVariables
      case 170: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (that.value);
        break;

      case 119: // WhileRule
        value.copy< WhileRule::Ptr > (that.value);
        break;

      case 152: // Type
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

      case 125: // DirectCallExpression
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

      case 97: // FunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 89: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 81: // "identifier"
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

      case 93: // InitDefinition
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

      case 96: // RuleDefinition
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

      case 88: // Specification
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

      case 100: // UsingDefinition
        value.move< UsingDefinition::Ptr > (that.value);
        break;

      case 101: // UsingPathDefinition
        value.move< UsingPathDefinition::Ptr > (that.value);
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
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
    yypush_ ("Shifting", static_cast<state_type> (yyn), YY_MOVE (yyla));
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

      case 125: // DirectCallExpression
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

      case 97: // FunctionDefinition
        yylhs.value.emplace< FunctionDefinition::Ptr > ();
        break;

      case 89: // Header
        yylhs.value.emplace< HeaderDefinition::Ptr > ();
        break;

      case 81: // "identifier"
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

      case 93: // InitDefinition
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

      case 96: // RuleDefinition
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

      case 88: // Specification
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

      case 100: // UsingDefinition
        yylhs.value.emplace< UsingDefinition::Ptr > ();
        break;

      case 101: // UsingPathDefinition
        yylhs.value.emplace< UsingPathDefinition::Ptr > ();
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
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
#line 408 "../../obj/src/GrammarParser.y"
  {
      m_specification.setHeader( yystack_[1].value.as < HeaderDefinition::Ptr > () );
      m_specification.setDefinitions( yystack_[0].value.as < Definitions::Ptr > () );
      m_specification.setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 2614 "GrammarParser.cpp"
    break;

  case 3:
#line 418 "../../obj/src/GrammarParser.y"
  {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2624 "GrammarParser.cpp"
    break;

  case 4:
#line 424 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2632 "GrammarParser.cpp"
    break;

  case 5:
#line 432 "../../obj/src/GrammarParser.y"
  {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2642 "GrammarParser.cpp"
    break;

  case 6:
#line 438 "../../obj/src/GrammarParser.y"
  {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2652 "GrammarParser.cpp"
    break;

  case 7:
#line 448 "../../obj/src/GrammarParser.y"
  {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2662 "GrammarParser.cpp"
    break;

  case 8:
#line 454 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2670 "GrammarParser.cpp"
    break;

  case 9:
#line 458 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2678 "GrammarParser.cpp"
    break;

  case 10:
#line 466 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2686 "GrammarParser.cpp"
    break;

  case 11:
#line 470 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2694 "GrammarParser.cpp"
    break;

  case 12:
#line 474 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2702 "GrammarParser.cpp"
    break;

  case 13:
#line 478 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2710 "GrammarParser.cpp"
    break;

  case 14:
#line 482 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 2718 "GrammarParser.cpp"
    break;

  case 15:
#line 486 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 2726 "GrammarParser.cpp"
    break;

  case 16:
#line 490 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingPathDefinition::Ptr > ();
  }
#line 2734 "GrammarParser.cpp"
    break;

  case 17:
#line 494 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 2742 "GrammarParser.cpp"
    break;

  case 18:
#line 498 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 2750 "GrammarParser.cpp"
    break;

  case 19:
#line 506 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2758 "GrammarParser.cpp"
    break;

  case 20:
#line 510 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2766 "GrammarParser.cpp"
    break;

  case 21:
#line 518 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2774 "GrammarParser.cpp"
    break;

  case 22:
#line 526 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2783 "GrammarParser.cpp"
    break;

  case 23:
#line 531 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2793 "GrammarParser.cpp"
    break;

  case 24:
#line 537 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 2801 "GrammarParser.cpp"
    break;

  case 25:
#line 545 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2811 "GrammarParser.cpp"
    break;

  case 26:
#line 551 "../../obj/src/GrammarParser.y"
  {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2820 "GrammarParser.cpp"
    break;

  case 27:
#line 556 "../../obj/src/GrammarParser.y"
  {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
  }
#line 2831 "GrammarParser.cpp"
    break;

  case 28:
#line 563 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2841 "GrammarParser.cpp"
    break;

  case 29:
#line 569 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2849 "GrammarParser.cpp"
    break;

  case 30:
#line 573 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2857 "GrammarParser.cpp"
    break;

  case 31:
#line 581 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FunctionDefinition::Ptr > () = Ast::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      const auto initially = yylhs.value.as < FunctionDefinition::Ptr > ()->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->setFunction( yylhs.value.as < FunctionDefinition::Ptr > () );
      }
  }
#line 2872 "GrammarParser.cpp"
    break;

  case 32:
#line 596 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 2880 "GrammarParser.cpp"
    break;

  case 33:
#line 600 "../../obj/src/GrammarParser.y"
  {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 2890 "GrammarParser.cpp"
    break;

  case 34:
#line 606 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 2898 "GrammarParser.cpp"
    break;

  case 35:
#line 614 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2909 "GrammarParser.cpp"
    break;

  case 36:
#line 621 "../../obj/src/GrammarParser.y"
  {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2919 "GrammarParser.cpp"
    break;

  case 37:
#line 631 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2927 "GrammarParser.cpp"
    break;

  case 38:
#line 639 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2935 "GrammarParser.cpp"
    break;

  case 39:
#line 643 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UsingPathDefinition::Ptr > () = Ast::make< UsingPathDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2943 "GrammarParser.cpp"
    break;

  case 40:
#line 651 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < InvariantDefinition::Ptr > () = Ast::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2951 "GrammarParser.cpp"
    break;

  case 41:
#line 659 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2959 "GrammarParser.cpp"
    break;

  case 42:
#line 663 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 2967 "GrammarParser.cpp"
    break;

  case 43:
#line 675 "../../obj/src/GrammarParser.y"
  {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 2977 "GrammarParser.cpp"
    break;

  case 44:
#line 681 "../../obj/src/GrammarParser.y"
  {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 2987 "GrammarParser.cpp"
    break;

  case 45:
#line 691 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 2995 "GrammarParser.cpp"
    break;

  case 46:
#line 695 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 3003 "GrammarParser.cpp"
    break;

  case 47:
#line 699 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 3011 "GrammarParser.cpp"
    break;

  case 48:
#line 703 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 3019 "GrammarParser.cpp"
    break;

  case 49:
#line 707 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 3027 "GrammarParser.cpp"
    break;

  case 50:
#line 711 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 3035 "GrammarParser.cpp"
    break;

  case 51:
#line 715 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 3043 "GrammarParser.cpp"
    break;

  case 52:
#line 719 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 3051 "GrammarParser.cpp"
    break;

  case 53:
#line 723 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 3059 "GrammarParser.cpp"
    break;

  case 54:
#line 727 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 3067 "GrammarParser.cpp"
    break;

  case 55:
#line 731 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 3075 "GrammarParser.cpp"
    break;

  case 56:
#line 735 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 3083 "GrammarParser.cpp"
    break;

  case 57:
#line 743 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3091 "GrammarParser.cpp"
    break;

  case 58:
#line 751 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3099 "GrammarParser.cpp"
    break;

  case 59:
#line 755 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3107 "GrammarParser.cpp"
    break;

  case 60:
#line 763 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3115 "GrammarParser.cpp"
    break;

  case 61:
#line 767 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 3123 "GrammarParser.cpp"
    break;

  case 62:
#line 775 "../../obj/src/GrammarParser.y"
  {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3133 "GrammarParser.cpp"
    break;

  case 63:
#line 781 "../../obj/src/GrammarParser.y"
  {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 3143 "GrammarParser.cpp"
    break;

  case 64:
#line 791 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3151 "GrammarParser.cpp"
    break;

  case 65:
#line 795 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3159 "GrammarParser.cpp"
    break;

  case 66:
#line 799 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3167 "GrammarParser.cpp"
    break;

  case 67:
#line 807 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3175 "GrammarParser.cpp"
    break;

  case 68:
#line 815 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3183 "GrammarParser.cpp"
    break;

  case 69:
#line 819 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3191 "GrammarParser.cpp"
    break;

  case 70:
#line 827 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3199 "GrammarParser.cpp"
    break;

  case 71:
#line 835 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3207 "GrammarParser.cpp"
    break;

  case 72:
#line 843 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3215 "GrammarParser.cpp"
    break;

  case 73:
#line 847 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3223 "GrammarParser.cpp"
    break;

  case 74:
#line 851 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3232 "GrammarParser.cpp"
    break;

  case 75:
#line 856 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3241 "GrammarParser.cpp"
    break;

  case 76:
#line 865 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3249 "GrammarParser.cpp"
    break;

  case 77:
#line 869 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3257 "GrammarParser.cpp"
    break;

  case 78:
#line 873 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3266 "GrammarParser.cpp"
    break;

  case 79:
#line 878 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 3275 "GrammarParser.cpp"
    break;

  case 80:
#line 887 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3283 "GrammarParser.cpp"
    break;

  case 81:
#line 895 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 3291 "GrammarParser.cpp"
    break;

  case 82:
#line 903 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 3299 "GrammarParser.cpp"
    break;

  case 83:
#line 915 "../../obj/src/GrammarParser.y"
  {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3310 "GrammarParser.cpp"
    break;

  case 84:
#line 922 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 3320 "GrammarParser.cpp"
    break;

  case 85:
#line 932 "../../obj/src/GrammarParser.y"
  {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3328 "GrammarParser.cpp"
    break;

  case 86:
#line 936 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 3336 "GrammarParser.cpp"
    break;

  case 87:
#line 940 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 3344 "GrammarParser.cpp"
    break;

  case 88:
#line 944 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 3352 "GrammarParser.cpp"
    break;

  case 89:
#line 948 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 3360 "GrammarParser.cpp"
    break;

  case 90:
#line 952 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 3368 "GrammarParser.cpp"
    break;

  case 91:
#line 956 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 3376 "GrammarParser.cpp"
    break;

  case 92:
#line 960 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 3384 "GrammarParser.cpp"
    break;

  case 93:
#line 964 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 3392 "GrammarParser.cpp"
    break;

  case 94:
#line 972 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< Ast::EmbracedExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3400 "GrammarParser.cpp"
    break;

  case 95:
#line 976 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 3408 "GrammarParser.cpp"
    break;

  case 96:
#line 980 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 3416 "GrammarParser.cpp"
    break;

  case 97:
#line 984 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 3424 "GrammarParser.cpp"
    break;

  case 98:
#line 988 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 3432 "GrammarParser.cpp"
    break;

  case 99:
#line 992 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3440 "GrammarParser.cpp"
    break;

  case 100:
#line 996 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 3448 "GrammarParser.cpp"
    break;

  case 101:
#line 1008 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3456 "GrammarParser.cpp"
    break;

  case 102:
#line 1012 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 3464 "GrammarParser.cpp"
    break;

  case 103:
#line 1016 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 3472 "GrammarParser.cpp"
    break;

  case 104:
#line 1020 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 3480 "GrammarParser.cpp"
    break;

  case 105:
#line 1024 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 3488 "GrammarParser.cpp"
    break;

  case 106:
#line 1028 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 3496 "GrammarParser.cpp"
    break;

  case 107:
#line 1032 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 3504 "GrammarParser.cpp"
    break;

  case 108:
#line 1036 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 3512 "GrammarParser.cpp"
    break;

  case 109:
#line 1040 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 3520 "GrammarParser.cpp"
    break;

  case 110:
#line 1044 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 3528 "GrammarParser.cpp"
    break;

  case 111:
#line 1048 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 3536 "GrammarParser.cpp"
    break;

  case 112:
#line 1052 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 3544 "GrammarParser.cpp"
    break;

  case 113:
#line 1056 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 3552 "GrammarParser.cpp"
    break;

  case 114:
#line 1060 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 3560 "GrammarParser.cpp"
    break;

  case 115:
#line 1064 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 3568 "GrammarParser.cpp"
    break;

  case 116:
#line 1068 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3576 "GrammarParser.cpp"
    break;

  case 117:
#line 1072 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3584 "GrammarParser.cpp"
    break;

  case 118:
#line 1076 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 3592 "GrammarParser.cpp"
    break;

  case 119:
#line 1084 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 3600 "GrammarParser.cpp"
    break;

  case 120:
#line 1088 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 3608 "GrammarParser.cpp"
    break;

  case 121:
#line 1092 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 3616 "GrammarParser.cpp"
    break;

  case 122:
#line 1100 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > (), arguments );
  }
#line 3625 "GrammarParser.cpp"
    break;

  case 123:
#line 1105 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), arguments );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3636 "GrammarParser.cpp"
    break;

  case 124:
#line 1112 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3646 "GrammarParser.cpp"
    break;

  case 125:
#line 1118 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 3654 "GrammarParser.cpp"
    break;

  case 126:
#line 1126 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 3663 "GrammarParser.cpp"
    break;

  case 127:
#line 1131 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3674 "GrammarParser.cpp"
    break;

  case 128:
#line 1138 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3684 "GrammarParser.cpp"
    break;

  case 129:
#line 1144 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 3692 "GrammarParser.cpp"
    break;

  case 130:
#line 1152 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 3700 "GrammarParser.cpp"
    break;

  case 131:
#line 1160 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3711 "GrammarParser.cpp"
    break;

  case 132:
#line 1167 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3721 "GrammarParser.cpp"
    break;

  case 133:
#line 1173 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 3729 "GrammarParser.cpp"
    break;

  case 134:
#line 1181 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3737 "GrammarParser.cpp"
    break;

  case 135:
#line 1189 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3745 "GrammarParser.cpp"
    break;

  case 136:
#line 1197 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3753 "GrammarParser.cpp"
    break;

  case 137:
#line 1205 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3761 "GrammarParser.cpp"
    break;

  case 138:
#line 1213 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3769 "GrammarParser.cpp"
    break;

  case 139:
#line 1221 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3777 "GrammarParser.cpp"
    break;

  case 140:
#line 1229 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3785 "GrammarParser.cpp"
    break;

  case 141:
#line 1242 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 3793 "GrammarParser.cpp"
    break;

  case 142:
#line 1246 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3801 "GrammarParser.cpp"
    break;

  case 143:
#line 1250 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3809 "GrammarParser.cpp"
    break;

  case 144:
#line 1254 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3817 "GrammarParser.cpp"
    break;

  case 145:
#line 1258 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3825 "GrammarParser.cpp"
    break;

  case 146:
#line 1262 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3833 "GrammarParser.cpp"
    break;

  case 147:
#line 1266 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3841 "GrammarParser.cpp"
    break;

  case 148:
#line 1270 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 3849 "GrammarParser.cpp"
    break;

  case 149:
#line 1274 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 3857 "GrammarParser.cpp"
    break;

  case 150:
#line 1278 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 3865 "GrammarParser.cpp"
    break;

  case 151:
#line 1282 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 3873 "GrammarParser.cpp"
    break;

  case 152:
#line 1286 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 3881 "GrammarParser.cpp"
    break;

  case 153:
#line 1294 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3890 "GrammarParser.cpp"
    break;

  case 154:
#line 1303 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3900 "GrammarParser.cpp"
    break;

  case 155:
#line 1309 "../../obj/src/GrammarParser.y"
  {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3910 "GrammarParser.cpp"
    break;

  case 156:
#line 1319 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3918 "GrammarParser.cpp"
    break;

  case 157:
#line 1327 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3926 "GrammarParser.cpp"
    break;

  case 158:
#line 1335 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3934 "GrammarParser.cpp"
    break;

  case 159:
#line 1343 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3942 "GrammarParser.cpp"
    break;

  case 160:
#line 1347 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3950 "GrammarParser.cpp"
    break;

  case 161:
#line 1355 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3958 "GrammarParser.cpp"
    break;

  case 162:
#line 1363 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3966 "GrammarParser.cpp"
    break;

  case 163:
#line 1371 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3977 "GrammarParser.cpp"
    break;

  case 164:
#line 1378 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3987 "GrammarParser.cpp"
    break;

  case 165:
#line 1384 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 3995 "GrammarParser.cpp"
    break;

  case 166:
#line 1392 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4005 "GrammarParser.cpp"
    break;

  case 167:
#line 1401 "../../obj/src/GrammarParser.y"
  {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4018 "GrammarParser.cpp"
    break;

  case 168:
#line 1412 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4028 "GrammarParser.cpp"
    break;

  case 169:
#line 1421 "../../obj/src/GrammarParser.y"
  {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4039 "GrammarParser.cpp"
    break;

  case 170:
#line 1428 "../../obj/src/GrammarParser.y"
  {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 4049 "GrammarParser.cpp"
    break;

  case 171:
#line 1437 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4057 "GrammarParser.cpp"
    break;

  case 172:
#line 1449 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4068 "GrammarParser.cpp"
    break;

  case 173:
#line 1456 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4078 "GrammarParser.cpp"
    break;

  case 174:
#line 1465 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 4086 "GrammarParser.cpp"
    break;

  case 175:
#line 1469 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 4094 "GrammarParser.cpp"
    break;

  case 176:
#line 1473 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 4102 "GrammarParser.cpp"
    break;

  case 177:
#line 1477 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 4110 "GrammarParser.cpp"
    break;

  case 178:
#line 1481 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 4118 "GrammarParser.cpp"
    break;

  case 179:
#line 1485 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 4126 "GrammarParser.cpp"
    break;

  case 180:
#line 1493 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 4134 "GrammarParser.cpp"
    break;

  case 181:
#line 1501 "../../obj/src/GrammarParser.y"
  {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = Ast::make< TupleType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), subTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4145 "GrammarParser.cpp"
    break;

  case 182:
#line 1512 "../../obj/src/GrammarParser.y"
  {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = Ast::make< RecordType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4156 "GrammarParser.cpp"
    break;

  case 183:
#line 1523 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4164 "GrammarParser.cpp"
    break;

  case 184:
#line 1531 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4172 "GrammarParser.cpp"
    break;

  case 185:
#line 1539 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4180 "GrammarParser.cpp"
    break;

  case 186:
#line 1551 "../../obj/src/GrammarParser.y"
  {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4191 "GrammarParser.cpp"
    break;

  case 187:
#line 1558 "../../obj/src/GrammarParser.y"
  {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 4201 "GrammarParser.cpp"
    break;

  case 188:
#line 1568 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 4209 "GrammarParser.cpp"
    break;

  case 189:
#line 1572 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 4217 "GrammarParser.cpp"
    break;

  case 190:
#line 1580 "../../obj/src/GrammarParser.y"
  {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4228 "GrammarParser.cpp"
    break;

  case 191:
#line 1587 "../../obj/src/GrammarParser.y"
  {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 4238 "GrammarParser.cpp"
    break;

  case 192:
#line 1601 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4246 "GrammarParser.cpp"
    break;

  case 193:
#line 1605 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 4254 "GrammarParser.cpp"
    break;

  case 194:
#line 1613 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 4262 "GrammarParser.cpp"
    break;

  case 195:
#line 1617 "../../obj/src/GrammarParser.y"
  {
      const auto initializers = Ast::make< Initializers >( yylhs.location );
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
#line 4271 "GrammarParser.cpp"
    break;

  case 196:
#line 1626 "../../obj/src/GrammarParser.y"
  {
      auto initializers = yystack_[2].value.as < Initializers::Ptr > ();
      yystack_[0].value.as < Initializer::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4282 "GrammarParser.cpp"
    break;

  case 197:
#line 1633 "../../obj/src/GrammarParser.y"
  {
      auto initializers = Ast::make< Initializers >( yylhs.location );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 4292 "GrammarParser.cpp"
    break;

  case 198:
#line 1643 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4301 "GrammarParser.cpp"
    break;

  case 199:
#line 1648 "../../obj/src/GrammarParser.y"
  {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), arguments, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4311 "GrammarParser.cpp"
    break;

  case 200:
#line 1654 "../../obj/src/GrammarParser.y"
  {
      const auto arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto lbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto rbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, lbToken, arguments, rbToken, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4322 "GrammarParser.cpp"
    break;

  case 201:
#line 1669 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 4330 "GrammarParser.cpp"
    break;

  case 202:
#line 1673 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 4339 "GrammarParser.cpp"
    break;

  case 203:
#line 1682 "../../obj/src/GrammarParser.y"
  {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < Ast::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 4350 "GrammarParser.cpp"
    break;

  case 204:
#line 1689 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4358 "GrammarParser.cpp"
    break;

  case 205:
#line 1701 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4366 "GrammarParser.cpp"
    break;

  case 206:
#line 1705 "../../obj/src/GrammarParser.y"
  {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 4375 "GrammarParser.cpp"
    break;

  case 207:
#line 1714 "../../obj/src/GrammarParser.y"
  {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 4386 "GrammarParser.cpp"
    break;

  case 208:
#line 1721 "../../obj/src/GrammarParser.y"
  {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 4396 "GrammarParser.cpp"
    break;

  case 209:
#line 1731 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4407 "GrammarParser.cpp"
    break;

  case 210:
#line 1738 "../../obj/src/GrammarParser.y"
  {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 4417 "GrammarParser.cpp"
    break;

  case 211:
#line 1748 "../../obj/src/GrammarParser.y"
  {
      auto variable = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4426 "GrammarParser.cpp"
    break;

  case 212:
#line 1757 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4436 "GrammarParser.cpp"
    break;

  case 213:
#line 1763 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4444 "GrammarParser.cpp"
    break;

  case 214:
#line 1771 "../../obj/src/GrammarParser.y"
  {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4454 "GrammarParser.cpp"
    break;

  case 215:
#line 1777 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4462 "GrammarParser.cpp"
    break;

  case 216:
#line 1789 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4473 "GrammarParser.cpp"
    break;

  case 217:
#line 1796 "../../obj/src/GrammarParser.y"
  {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4483 "GrammarParser.cpp"
    break;

  case 218:
#line 1805 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4491 "GrammarParser.cpp"
    break;

  case 219:
#line 1817 "../../obj/src/GrammarParser.y"
  {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4501 "GrammarParser.cpp"
    break;

  case 220:
#line 1823 "../../obj/src/GrammarParser.y"
  {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4511 "GrammarParser.cpp"
    break;

  case 221:
#line 1832 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4522 "GrammarParser.cpp"
    break;

  case 222:
#line 1839 "../../obj/src/GrammarParser.y"
  {
      auto attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4533 "GrammarParser.cpp"
    break;

  case 223:
#line 1846 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 4541 "GrammarParser.cpp"
    break;

  case 224:
#line 1853 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4549 "GrammarParser.cpp"
    break;

  case 225:
#line 1860 "../../obj/src/GrammarParser.y"
  {
      yylhs.value.as < ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4557 "GrammarParser.cpp"
    break;


#line 4561 "GrammarParser.cpp"

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
      error_token.state = static_cast<state_type> (yyn);
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


  const short Parser::yypact_ninf_ = -144;

  const short Parser::yytable_ninf_ = -188;

  const short
  Parser::yypact_[] =
  {
      -1,  -144,    16,    46,   217,     6,  -144,    26,  -144,  -144,
    1757,    40,    70,  -144,  -144,     2,    14,    14,    14,    14,
      14,    14,    14,   102,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,   250,  -144,  -144,  -144,     3,
       3,     3,  1757,     3,  -144,  -144,  -144,  1757,   529,   529,
    1284,  1028,   529,    14,  -144,  -144,  -144,  -144,  -144,  -144,
    2470,    12,  -144,   -32,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,    24,
    -144,  -144,  1821,    20,    92,    75,    13,   118,    93,   127,
     116,    10,  -144,  -144,   124,  -144,  -144,   135,    29,  -144,
       3,    30,  -144,    34,  2007,    36,  -144,  -144,  -144,   107,
     155,  2225,    22,  -144,   131,   170,  -144,    96,  2260,     5,
      20,  1757,  1757,  1757,  1757,  1757,  1757,  1757,  1757,  1757,
    1757,  1757,  1757,  1757,  1757,  1757,  1757,  1757,    -7,     4,
    1092,  1156,    14,  1284,  2470,   162,   144,  -144,     9,    -7,
     183,  1629,    15,    -7,    -7,     7,  1757,    14,    -7,    -7,
    1757,  1757,     3,  -144,  1757,     3,  1757,  1757,  1757,  -144,
    1757,  -144,  -144,    14,  1757,  -144,  -144,  1757,  1757,  -144,
     293,  2540,  2570,  2505,   184,   184,   599,   206,   206,   168,
     168,   168,  -144,  2505,   599,   206,   206,    -7,  -144,  -144,
    -144,  -144,  -144,  -144,  -144,   126,  -144,   188,   193,  -144,
      25,  2470,   195,  -144,   101,  -144,  2295,  1757,  -144,  1821,
     215,   105,   124,  -144,  -144,     3,   207,    17,   693,   762,
    -144,     3,     3,     3,  1629,  1757,  1757,  1757,   831,   900,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,   197,   109,   201,   224,   149,   228,  -144,
    -144,  2470,  -144,  -144,   214,   209,  -144,  2470,  2470,  -144,
    2155,  -144,  1845,  2084,  2190,  2330,  -144,   131,  2470,  2470,
    2365,   221,  -144,   124,   222,  -144,    -7,  1757,  1220,  -144,
    -144,  -144,  -144,   213,  2470,  -144,   216,   218,     3,  -144,
    1757,  -144,  -144,   163,  -144,     3,   267,  1353,  -144,   266,
    1422,    37,    42,    47,  -144,  2046,  2120,  1886,   238,  1491,
     225,  1560,  1757,    72,   106,  1629,    -7,    -7,  1757,  1757,
    1757,  1757,  -144,  -144,    -7,    14,   152,   121,   229,  -144,
     254,  -144,   153,  1757,    -7,    -7,  -144,  2470,  -144,    17,
    -144,  -144,  -144,  -144,  -144,  -144,  1629,  1757,  1757,  1629,
     252,  1629,  -144,  -144,  -144,  -144,  2470,  1629,    -7,  1629,
      -7,  -144,  -144,   291,  2470,  2470,  2470,  2470,   257,   258,
      -7,  -144,    -7,  -144,  -144,  2470,   261,   262,  -144,  -144,
     425,  1927,   282,   964,  -144,  -144,   264,  -144,   265,   263,
     272,  -144,  -144,  -144,   253,  1757,  1757,  1629,  1757,  1629,
    1629,   260,   268,   287,  1693,  -144,  2400,  1629,  1629,  1757,
     277,  -144,  -144,  2470,  2470,  -144,  1968,  -144,  -144,  -144,
    1629,  1629,  -144,  -144,  1629,  -144,  -144,  2435,  1821,  1629,
    -144,  -144,  -144,  -144,   181,  -144,  -144
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
    -144,  -144,  -144,  -144,   317,   307,  -144,  -144,  -144,  -144,
    -144,   -18,  -144,  -144,  -144,  -144,  -144,  -134,   306,  -144,
    -144,  -144,  -144,   -80,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,   -50,   -10,   -45,  -144,   172,   205,  -144,
    -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
    -144,  -144,   196,  -144,  -144,  -144,  -144,  -144,  -144,  -144,
     -87,  -144,  -144,   164,    50,  -139,  -144,  -144,  -144,  -144,
    -144,  -144,  -144,    52,   187,  -144,  -144,   -98,   133,   275,
      23,   259,   -35,  -144,  -143,   -28,    60,   129,   199,    27,
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
      60,   127,     1,   117,   118,   155,   113,   129,   115,    36,
     230,   107,     8,    37,   150,   233,   266,     7,   311,   233,
     236,     8,     8,     8,   268,   269,     8,     5,     8,   273,
     276,    35,   114,     8,     8,     8,     8,   116,    93,   207,
     121,   128,    98,    37,   100,   148,    13,     2,   171,   174,
      35,     2,    92,   176,     2,   178,   366,     2,   161,   162,
     189,   367,   168,     2,   295,     2,   368,   270,   292,   182,
     151,   149,   300,   152,     9,    38,   130,   152,   149,   183,
     163,    56,   187,     9,     9,     9,   172,   175,     9,    90,
       9,   175,   309,   175,   172,     9,     9,     9,     9,   175,
     220,   224,    -2,    14,   175,   320,    15,    16,    17,    18,
      19,    20,    21,    22,   329,   331,   263,   377,    37,    91,
     160,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   158,   378,
     221,   221,   155,   226,   107,   186,   165,   281,   302,   167,
       2,   379,   307,   187,   179,   150,   271,   347,   187,   159,
     277,   278,   308,   164,   280,   233,   282,   283,   284,   152,
     285,   215,   166,   380,   288,   -96,   169,   289,   290,   152,
     170,  -187,   215,   184,   296,   235,   215,   215,  -187,   235,
     297,   215,   215,   263,   263,   228,   334,   382,   383,   263,
     394,   229,   389,   263,   263,   388,   308,   322,   323,   390,
     187,   391,   180,   107,   358,   396,   397,   304,    14,   185,
     359,    15,    16,    17,    18,    19,    20,    21,    22,   227,
     215,   143,   456,   237,   298,   325,   326,   327,   229,   406,
     299,   408,   301,    37,   140,   141,   142,   143,   352,   135,
     136,   413,   310,   414,    15,    16,    17,    18,    19,    20,
      21,    22,   306,   149,   315,     2,   140,   141,   142,   143,
     332,   333,   263,   335,   336,   263,   337,    10,   344,   345,
     353,   361,   364,   354,   263,   355,   263,   349,   221,   372,
     263,    94,    95,    96,    97,    99,   392,   101,     2,   374,
     357,   393,   403,   409,   411,   412,   415,   416,   420,   427,
     428,   439,   432,   429,   104,   104,   104,   430,   104,   215,
     440,   263,   376,    37,   263,   124,   263,   448,   384,   385,
     386,   387,   263,   264,   263,   235,   135,   136,   137,   441,
     102,   398,   103,   395,   443,   216,   346,   286,   348,   267,
     454,   138,   139,   140,   141,   142,   143,   400,   401,   215,
     215,   155,   305,   145,   146,   147,   265,   215,   356,   173,
     321,   279,   263,     0,   263,   263,     0,   215,   215,     0,
       0,     0,   263,   263,     0,   104,   315,     0,     0,     0,
       0,     0,     0,   426,     0,   263,   263,     0,     0,   263,
       0,   215,     0,   215,   263,   433,   434,     0,   436,     0,
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
     265,   264,     0,   264,     0,     0,     0,     0,     8,   264,
     324,   264,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    44,    45,    46,     0,     0,     0,
       0,   265,    48,    49,   265,    50,   265,    51,     0,     0,
       0,     0,   265,   232,   265,    53,     0,     0,     0,   264,
     360,   264,   264,     0,     0,     0,     0,     0,     0,   264,
     264,     0,     0,     0,    54,    55,    56,    57,    58,    59,
       9,     0,   264,   264,     0,     0,   264,     0,     0,     0,
     232,   264,   265,   363,   265,   265,   363,     0,     0,     0,
       0,     0,   265,   265,   314,   363,     0,   363,     0,     0,
       0,   381,   135,   136,     0,   265,   265,     0,     0,   265,
       0,     0,     0,     0,   265,     0,     0,   138,   139,   140,
     141,   142,   143,     0,     0,     0,     0,     0,     0,     0,
     146,   147,   399,     0,     0,   402,     0,   404,     0,     0,
       0,     0,     0,   405,     0,   407,     0,     0,     0,     0,
       0,     0,     0,     0,   316,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   238,     0,   239,     0,
     240,   241,     8,   242,   243,   244,     0,   245,     0,     0,
     246,     0,     0,   435,     0,   437,   438,   247,    44,    45,
      46,     0,     0,   445,   446,     0,    48,    49,     0,    50,
       0,    51,     0,   248,     0,     0,   450,   451,     0,    53,
     452,     0,     0,     0,     0,   455,     0,     0,     0,     0,
       0,     0,     0,   319,     0,     0,   249,     0,    54,    55,
      56,    57,    58,    59,     9,   238,     0,   239,     0,   240,
     241,     8,   242,   243,   244,     0,   245,     0,     0,   246,
       0,     0,     0,     0,     0,     0,   247,    44,    45,    46,
       0,     0,     0,     0,     0,    48,    49,     0,    50,     0,
      51,     0,   248,     0,     0,     0,     0,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   328,     0,     0,   249,     0,    54,    55,    56,
      57,    58,    59,     9,   238,     0,   239,     0,   240,   241,
       8,   242,   243,   244,     0,   245,     0,     0,   246,     0,
       0,     0,     0,     0,     0,   247,    44,    45,    46,     0,
       0,     0,     0,     0,    48,    49,     0,    50,     0,    51,
       0,   248,     0,     0,     0,     0,     0,    53,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   330,     0,     0,   249,     0,    54,    55,    56,    57,
      58,    59,     9,   238,     0,   239,     0,   240,   241,     8,
     242,   243,   244,     0,   245,     0,     0,   246,     0,     0,
       0,     0,     0,     0,   247,    44,    45,    46,     0,     0,
       0,     0,     0,    48,    49,     0,    50,     0,    51,     0,
     248,     0,     0,     0,     0,     0,    53,     0,     0,     0,
       0,     0,     0,     0,     0,   421,     0,     0,     0,     0,
       0,     0,     0,   249,     0,    54,    55,    56,    57,    58,
      59,     9,    39,     8,    40,    41,     0,     0,    42,     0,
       0,     0,     0,   422,     0,    43,     0,     0,     0,    44,
      45,    46,     0,     0,     0,     0,    47,    48,    49,     0,
      50,     0,    51,     0,     0,     0,     0,     0,   423,    52,
      53,     0,     0,     0,     0,     0,     0,     0,     0,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    54,
      55,    56,    57,    58,    59,     9,    39,     8,    40,    41,
       0,     0,    42,     0,     0,     0,     0,     0,     0,    43,
       0,     0,     0,    44,    45,    46,     0,     0,     0,     0,
      47,    48,    49,     0,    50,     0,    51,   126,     0,     0,
       0,     0,     0,    52,    53,     0,     0,     0,     0,     0,
       0,     0,     0,   218,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    55,    56,    57,    58,    59,     9,
      39,     8,    40,    41,     0,     0,    42,     0,     0,     0,
       0,     0,     0,    43,     0,     0,     0,    44,    45,    46,
       0,     0,     0,     0,    47,    48,    49,     0,    50,   219,
      51,     0,     0,     0,     0,     0,     0,    52,    53,     0,
       0,     0,     0,     0,     0,     0,     0,   222,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,    55,    56,
      57,    58,    59,     9,    39,     8,    40,    41,     0,     0,
      42,     0,     0,     0,     0,     0,     0,    43,     0,     0,
       0,    44,    45,    46,     0,     0,     0,     0,    47,    48,
      49,     0,    50,   223,    51,     0,     0,     0,     0,     0,
       0,    52,    53,     0,     0,     0,     0,     0,     0,     0,
       0,   350,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    54,    55,    56,    57,    58,    59,     9,    39,     8,
      40,    41,     0,     0,    42,     0,     0,     0,     0,     0,
       0,    43,     0,     0,     0,    44,    45,    46,     0,     0,
       0,     0,    47,    48,    49,     0,    50,   351,    51,     0,
       0,     0,     0,     0,     0,    52,    53,     0,     0,     0,
       0,     0,     0,     0,     0,   119,     0,     0,     0,     0,
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
       0,     0,     0,     0,     0,   145,   146,   147,   131,     0,
     133,     0,     0,   135,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
     140,   141,   142,   143,     0,     0,     0,     0,   131,     0,
     145,   146,   147,   135,   136,   137,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   138,   139,
     140,   141,   142,   143,     0,     0,     0,     0,     0,     0,
     145,   146,   147
  };

  const short
  Parser::yycheck_[] =
  {
      10,    51,     3,    48,    49,    92,    41,    52,    43,     3,
       1,    39,    19,     5,    46,   158,     1,     1,     1,   162,
     159,    19,    19,    19,   163,   164,    19,     0,    19,   168,
     169,     4,    42,    19,    19,    19,    19,    47,    15,    46,
      50,    51,    19,    35,    21,    33,     0,    48,    19,    19,
      23,    48,    50,    19,    48,    19,    19,    48,    45,    46,
      55,    19,    52,    48,   207,    48,    19,    60,   207,    47,
      46,    66,    47,    53,    81,    49,    53,    53,    66,    57,
      67,    77,    57,    81,    81,    81,    57,    57,    81,    49,
      81,    57,   235,    57,    57,    81,    81,    81,    81,    57,
     150,   151,     0,     1,    57,   239,     4,     5,     6,     7,
       8,     9,    10,    11,   248,   249,   161,    45,   110,    49,
      45,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,    46,    67,
     150,   151,   229,   153,   172,    49,    53,   175,    47,    33,
      48,    45,    47,    57,    47,    46,   166,   296,    57,    67,
     170,   171,    57,    45,   174,   308,   176,   177,   178,    53,
     180,   148,    45,    67,   184,    66,    52,   187,   188,    53,
      45,    60,   159,    52,    58,   158,   163,   164,    67,   162,
      64,   168,   169,   238,   239,    51,    47,   336,   337,   244,
      47,    57,   345,   248,   249,   344,    57,   242,   243,    57,
      57,    59,    57,   241,    51,   354,   355,   227,     1,    49,
      57,     4,     5,     6,     7,     8,     9,    10,    11,    67,
     207,    63,    51,    50,    46,   245,   246,   247,    57,   378,
      47,   380,    47,   235,    60,    61,    62,    63,   298,    43,
      44,   390,    45,   392,     4,     5,     6,     7,     8,     9,
      10,    11,    47,    66,   237,    48,    60,    61,    62,    63,
      69,    47,   317,    45,    60,   320,    67,     2,    57,    57,
      67,    14,    16,    67,   329,    67,   331,   297,   298,    51,
     335,    16,    17,    18,    19,    20,    67,    22,    48,    74,
     310,    47,    50,    12,    47,    47,    45,    45,    26,    45,
      45,    51,    59,    50,    39,    40,    41,    45,    43,   296,
      52,   366,   332,   315,   369,    50,   371,    50,   338,   339,
     340,   341,   377,   161,   379,   308,    43,    44,    45,    52,
      23,   359,    35,   353,   424,   149,   296,   183,   296,   162,
     448,    58,    59,    60,    61,    62,    63,   367,   368,   336,
     337,   448,   229,    70,    71,    72,   161,   344,   308,   110,
     241,   172,   417,    -1,   419,   420,    -1,   354,   355,    -1,
      -1,    -1,   427,   428,    -1,   110,   359,    -1,    -1,    -1,
      -1,    -1,    -1,   403,    -1,   440,   441,    -1,    -1,   444,
      -1,   378,    -1,   380,   449,   415,   416,    -1,   418,    -1,
     238,   239,    -1,   390,   424,   392,   244,    -1,    -1,   429,
     248,   249,    -1,    -1,   149,    -1,    -1,   152,   153,    -1,
      -1,    -1,    -1,   158,    -1,    -1,    -1,   162,    -1,    -1,
     165,    -1,   167,   238,   239,    -1,    -1,   172,    23,   244,
     175,    -1,    -1,   248,   249,    -1,    -1,    32,   183,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,   161,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   207,    58,    59,    60,    61,    62,    63,   317,
      -1,    -1,   320,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,   329,    -1,   331,    -1,    -1,    -1,   335,    -1,    -1,
     235,    -1,   237,    -1,    -1,    -1,   241,   242,   243,    -1,
      -1,    -1,   317,    -1,    -1,   320,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   329,    -1,   331,    -1,   366,    -1,
     335,   369,    -1,   371,    -1,    -1,    -1,    -1,    19,   377,
     244,   379,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,
      -1,   366,    43,    44,   369,    46,   371,    48,    -1,    -1,
      -1,    -1,   377,   308,   379,    56,    -1,    -1,    -1,   417,
     315,   419,   420,    -1,    -1,    -1,    -1,    -1,    -1,   427,
     428,    -1,    -1,    -1,    75,    76,    77,    78,    79,    80,
      81,    -1,   440,   441,    -1,    -1,   444,    -1,    -1,    -1,
     345,   449,   417,   317,   419,   420,   320,    -1,    -1,    -1,
      -1,    -1,   427,   428,   359,   329,    -1,   331,    -1,    -1,
      -1,   335,    43,    44,    -1,   440,   441,    -1,    -1,   444,
      -1,    -1,    -1,    -1,   449,    -1,    -1,    58,    59,    60,
      61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,   366,    -1,    -1,   369,    -1,   371,    -1,    -1,
      -1,    -1,    -1,   377,    -1,   379,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    13,    -1,    15,    -1,
      17,    18,    19,    20,    21,    22,    -1,    24,    -1,    -1,
      27,    -1,    -1,   417,    -1,   419,   420,    34,    35,    36,
      37,    -1,    -1,   427,   428,    -1,    43,    44,    -1,    46,
      -1,    48,    -1,    50,    -1,    -1,   440,   441,    -1,    56,
     444,    -1,    -1,    -1,    -1,   449,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    13,    -1,    15,    -1,    17,
      18,    19,    20,    21,    22,    -1,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    46,    -1,
      48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    13,    -1,    15,    -1,    17,    18,
      19,    20,    21,    22,    -1,    24,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    46,    -1,    48,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    -1,    -1,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    13,    -1,    15,    -1,    17,    18,    19,
      20,    21,    22,    -1,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    46,    -1,    48,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    -1,    75,    76,    77,    78,    79,
      80,    81,    18,    19,    20,    21,    -1,    -1,    24,    -1,
      -1,    -1,    -1,    29,    -1,    31,    -1,    -1,    -1,    35,
      36,    37,    -1,    -1,    -1,    -1,    42,    43,    44,    -1,
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    81,    18,    19,    20,    21,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,
      42,    43,    44,    -1,    46,    -1,    48,    49,    -1,    -1,
      -1,    -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    80,    81,
      18,    19,    20,    21,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    -1,    35,    36,    37,
      -1,    -1,    -1,    -1,    42,    43,    44,    -1,    46,    47,
      48,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    80,    81,    18,    19,    20,    21,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    -1,
      -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,    43,
      44,    -1,    46,    47,    48,    -1,    -1,    -1,    -1,    -1,
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
      46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    80,    81,    13,    14,    15,    -1,
      17,    18,    19,    20,    21,    22,    -1,    24,    -1,    -1,
      27,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    46,
      -1,    48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,    75,    76,
      77,    78,    79,    80,    81,    13,    -1,    15,    16,    17,
      18,    19,    20,    21,    22,    -1,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      -1,    -1,    -1,    -1,    -1,    43,    44,    -1,    46,    -1,
      48,    -1,    50,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    73,    -1,    75,    76,    77,
      78,    79,    80,    81,    13,    -1,    15,    -1,    17,    18,
      19,    20,    21,    22,    -1,    24,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,
      -1,    -1,    -1,    -1,    43,    44,    -1,    46,    -1,    48,
      -1,    50,    51,    -1,    -1,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    -1,    75,    76,    77,    78,
      79,    80,    81,    13,    -1,    15,    -1,    17,    18,    19,
      20,    21,    22,    -1,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,
      -1,    -1,    -1,    43,    44,    -1,    46,    -1,    48,    -1,
      50,    -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    13,    -1,    15,    -1,    17,    18,    19,    20,
      21,    22,    -1,    24,    -1,    -1,    27,    -1,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    -1,    -1,
      -1,    -1,    43,    44,    -1,    46,    -1,    48,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    73,    -1,    75,    76,    77,    78,    79,    80,
      81,    18,    19,    20,    21,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    29,    -1,    31,    -1,    -1,    -1,    35,    36,
      37,    -1,    -1,    -1,    -1,    42,    43,    44,    -1,    46,
      -1,    48,    -1,    -1,    51,    -1,    -1,    54,    55,    56,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    78,    79,    80,    81,    18,    19,    20,    21,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      -1,    -1,    35,    36,    37,    -1,    -1,    -1,    -1,    42,
      43,    44,    -1,    46,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    80,    81,    18,
      19,    20,    21,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    -1,    -1,    35,    36,    37,    -1,
      -1,    -1,    -1,    42,    43,    44,    -1,    46,    23,    48,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    -1,    -1,
      -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    80,    81,    58,    59,    60,    61,    62,    63,    23,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      23,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,    23,    -1,    -1,    -1,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    38,    39,    40,    41,
      -1,    43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,
      62,    63,    25,    -1,    -1,    -1,    68,    -1,    70,    71,
      72,    -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,
      43,    44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,
      63,    25,    -1,    -1,    -1,    68,    -1,    70,    71,    72,
      -1,    -1,    -1,    -1,    38,    39,    40,    41,    -1,    43,
      44,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    58,    59,    60,    61,    62,    63,
      26,    -1,    -1,    -1,    68,    -1,    70,    71,    72,    -1,
      -1,    -1,    38,    39,    40,    41,    -1,    43,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    58,    59,    60,    61,    62,    63,    28,    -1,
      -1,    -1,    68,    -1,    70,    71,    72,    -1,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    30,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    32,    68,    -1,    70,    71,    72,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    65,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    68,    -1,    70,    71,    72,    38,    39,
      40,    41,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    68,    -1,
      70,    71,    72,    38,    39,    40,    -1,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58,    59,    60,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    38,    -1,
      40,    -1,    -1,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    38,    -1,
      70,    71,    72,    43,    44,    45,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    58,    59,
      60,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    48,    88,    89,   176,   177,     1,    19,    81,
     166,   178,   179,     0,     1,     4,     5,     6,     7,     8,
       9,    10,    11,    90,    91,    92,    93,    94,    95,    96,
      97,   100,   101,   102,   103,   176,     3,   177,    49,    18,
      20,    21,    24,    31,    35,    36,    37,    42,    43,    44,
      46,    48,    55,    56,    75,    76,    77,    78,    79,    80,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   166,   167,
      49,    49,    50,   167,   166,   166,   166,   166,   167,   166,
     167,   166,    91,    92,   166,   168,   171,   172,   174,   175,
     176,   169,   172,   169,   121,   169,   121,   122,   122,     1,
     120,   121,   149,   150,   166,     1,    49,   120,   121,   122,
     167,    38,    39,    40,    41,    43,    44,    45,    58,    59,
      60,    61,    62,    63,    68,    70,    71,    72,    33,    66,
      46,    46,    53,    46,   121,   147,   164,   165,    46,    67,
      45,    45,    46,    67,    45,    53,    45,    33,    52,    52,
      45,    19,    57,   168,    19,    57,    19,    25,    19,    47,
      57,    47,    47,    57,    52,    49,    49,    57,    65,    55,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,    46,   152,   153,
     154,   155,   156,   157,   158,   167,   139,   166,     1,    47,
     120,   121,     1,    47,   120,   166,   121,    67,    51,    57,
       1,   161,   166,   171,   173,   176,   152,    50,    13,    15,
      17,    18,    20,    21,    22,    24,    27,    34,    50,    73,
     105,   106,   107,   108,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   122,   124,   125,     1,   161,   152,   152,
      60,   121,   166,   152,   159,   160,   152,   121,   121,   175,
     121,   172,   121,   121,   121,   121,   150,   166,   121,   121,
     121,   151,   152,   166,   170,   171,    58,    64,    46,    47,
      47,    47,    47,    47,   121,   165,    47,    47,    57,   171,
      45,     1,    98,    99,   166,   176,     1,   104,   105,     1,
     104,   174,   169,   169,   105,   121,   121,   121,     1,   104,
       1,   104,    69,    47,    47,    45,    60,    67,    30,    23,
      26,    32,    47,    49,    57,    57,   151,   152,   160,   121,
       1,    47,   120,    67,    67,    67,   173,   121,    51,    57,
     166,    14,    14,   105,    16,    16,    19,    19,    19,    25,
      28,    23,    51,    51,    74,    74,   121,    45,    67,    45,
      67,   105,   152,   152,   121,   121,   121,   121,   152,   171,
      57,    59,    67,    47,    47,   121,   152,   152,    98,   105,
     121,   121,   105,    50,   105,   105,   152,   105,   152,    12,
     162,    47,    47,   152,   152,    45,    45,    23,    32,    23,
      26,     1,    29,    54,   109,   110,   121,    45,    45,    50,
      45,   163,    59,   121,   121,   105,   121,   105,   105,    51,
      52,    52,    51,   110,    52,   105,   105,   121,    50,    23,
     105,   105,   105,    51,   164,   105,    51
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    87,    88,    89,    89,    90,    90,    91,    91,    91,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    93,
      93,    94,    95,    95,    95,    96,    96,    96,    96,    96,
      96,    97,    98,    98,    98,    99,    99,   100,   101,   101,
     102,   103,   103,   104,   104,   105,   105,   105,   105,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   107,   107,
     108,   108,   109,   109,   110,   110,   110,   111,   112,   112,
     113,   114,   115,   115,   115,   115,   116,   116,   116,   116,
     117,   118,   119,   120,   120,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   122,   122,   122,   122,   122,   122,
     122,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   124,
     124,   124,   125,   125,   125,   125,   126,   126,   126,   126,
     127,   128,   128,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   137,   138,   138,   139,   140,   141,   142,
     142,   143,   144,   145,   145,   145,   146,   147,   148,   149,
     149,   150,   151,   151,   152,   152,   152,   152,   152,   152,
     153,   154,   155,   156,   157,   158,   159,   159,   160,   160,
     161,   161,   162,   162,   163,   163,   164,   164,   165,   165,
     165,   166,   166,   167,   167,   168,   168,   169,   169,   170,
     170,   171,   172,   172,   173,   173,   174,   174,   175,   176,
     176,   177,   177,   177,   178,   179
  };

  const signed char
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
  "\"invariant\"", "\"import\"", "\"function\"", "\"defined\"", "\"seq\"",
  "\"endseq\"", "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"",
  "\"forall\"", "\"choose\"", "\"iterate\"", "\"do\"", "\"if\"",
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
  "UsingPathDefinition", "InvariantDefinition", "ImportDefinition",
  "Rules", "Rule", "SkipRule", "ConditionalRule", "CaseRule", "CaseLabels",
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
  const short
  Parser::yyrline_[] =
  {
       0,   407,   407,   417,   423,   431,   437,   447,   453,   457,
     465,   469,   473,   477,   481,   485,   489,   493,   497,   505,
     509,   517,   525,   530,   536,   544,   550,   555,   562,   568,
     572,   580,   595,   599,   605,   613,   620,   630,   638,   642,
     650,   658,   662,   674,   680,   690,   694,   698,   702,   706,
     710,   714,   718,   722,   726,   730,   734,   742,   750,   754,
     762,   766,   774,   780,   790,   794,   798,   806,   814,   818,
     826,   834,   842,   846,   850,   855,   864,   868,   872,   877,
     886,   894,   902,   914,   921,   931,   935,   939,   943,   947,
     951,   955,   959,   963,   971,   975,   979,   983,   987,   991,
     995,  1007,  1011,  1015,  1019,  1023,  1027,  1031,  1035,  1039,
    1043,  1047,  1051,  1055,  1059,  1063,  1067,  1071,  1075,  1083,
    1087,  1091,  1099,  1104,  1111,  1117,  1125,  1130,  1137,  1143,
    1151,  1159,  1166,  1172,  1180,  1188,  1196,  1204,  1212,  1220,
    1228,  1241,  1245,  1249,  1253,  1257,  1261,  1265,  1269,  1273,
    1277,  1281,  1285,  1293,  1302,  1308,  1318,  1326,  1334,  1342,
    1346,  1354,  1362,  1370,  1377,  1383,  1391,  1400,  1411,  1420,
    1427,  1436,  1448,  1455,  1464,  1468,  1472,  1476,  1480,  1484,
    1492,  1500,  1511,  1522,  1530,  1538,  1550,  1557,  1567,  1571,
    1579,  1586,  1600,  1604,  1612,  1616,  1625,  1632,  1642,  1647,
    1653,  1668,  1672,  1681,  1688,  1700,  1704,  1713,  1720,  1730,
    1737,  1747,  1756,  1762,  1770,  1776,  1788,  1795,  1804,  1816,
    1822,  1831,  1838,  1845,  1852,  1859
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
#line 5726 "GrammarParser.cpp"

#line 1865 "../../obj/src/GrammarParser.y"


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
