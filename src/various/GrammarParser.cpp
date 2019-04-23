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

      case 104: // ImportPath
      case 168: // IdentifierPath
        value.YY_MOVE_OR_COPY< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // ImportDefinition
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

      case 102: // InvariantDefinition
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

      case 104: // ImportPath
      case 168: // IdentifierPath
        value.move< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // ImportDefinition
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

      case 102: // InvariantDefinition
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

      case 104: // ImportPath
      case 168: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 103: // ImportDefinition
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

      case 102: // InvariantDefinition
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

      case 104: // ImportPath
      case 168: // IdentifierPath
        yylhs.value.emplace< IdentifierPath::Ptr > ();
        break;

      case 103: // ImportDefinition
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

      case 102: // InvariantDefinition
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
#line 414 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      m_specification.setHeader( yystack_[1].value.as < HeaderDefinition::Ptr > () );
      m_specification.setDefinitions( yystack_[0].value.as < Definitions::Ptr > () );
      m_specification.setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 2192 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 3:
#line 424 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < HeaderDefinition::Ptr > () = definition;
  }
#line 2202 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 4:
#line 430 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2210 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 5:
#line 438 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definitions = yystack_[1].value.as < Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2220 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 6:
#line 444 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as < Definition::Ptr > () );
      yylhs.value.as < Definitions::Ptr > () = definitions;
  }
#line 2230 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 7:
#line 454 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto definition = yystack_[0].value.as < Definition::Ptr > ();
      definition->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < Definition::Ptr > () = definition;
  }
#line 2240 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 8:
#line 460 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < Definition::Ptr > ();
  }
#line 2248 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 9:
#line 464 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = nullptr;
  }
#line 2256 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 10:
#line 472 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InitDefinition::Ptr > ();
  }
#line 2264 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 11:
#line 476 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < EnumerationDefinition::Ptr > ();
  }
#line 2272 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 12:
#line 480 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < DerivedDefinition::Ptr > ();
  }
#line 2280 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 13:
#line 484 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < RuleDefinition::Ptr > ();
  }
#line 2288 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 14:
#line 488 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < FunctionDefinition::Ptr > ();
  }
#line 2296 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 15:
#line 492 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < UsingDefinition::Ptr > ();
  }
#line 2304 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 16:
#line 496 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < InvariantDefinition::Ptr > ();
  }
#line 2312 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 17:
#line 500 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Definition::Ptr > () = yystack_[0].value.as < ImportDefinition::Ptr > ();
  }
#line 2320 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 18:
#line 508 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2328 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 19:
#line 512 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < InitDefinition::Ptr > () = Ast::make< InitDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2336 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 20:
#line 520 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Enumerators::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2344 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 21:
#line 528 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2353 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 22:
#line 533 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DerivedDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2363 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 23:
#line 539 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DerivedDefinition::Ptr > () = nullptr;
  }
#line 2371 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 24:
#line 547 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), params, Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2381 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 25:
#line 553 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto params = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Identifier::Ptr > (), params, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2390 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 26:
#line 558 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto vType = createVoidType( yylhs.location );
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[6].value.as < Ast::Token::Ptr > (), yystack_[5].value.as < Identifier::Ptr > (), yystack_[3].value.as < VariableDefinitions::Ptr > (), Token::unresolved(), vType, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
  }
#line 2401 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 27:
#line 565 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[8].value.as < Ast::Token::Ptr > (), yystack_[7].value.as < Identifier::Ptr > (), yystack_[5].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setLeftBracketToken( yystack_[6].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RuleDefinition::Ptr > ()->setRightBracketToken( yystack_[4].value.as < Ast::Token::Ptr > () );
  }
#line 2411 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 28:
#line 571 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2419 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 29:
#line 575 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RuleDefinition::Ptr > () = nullptr;
  }
#line 2427 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 30:
#line 583 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < FunctionDefinition::Ptr > () = Ast::make< FunctionDefinition >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < Identifier::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Types::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[1].value.as < Defined::Ptr > (), yystack_[0].value.as < Initially::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      const auto initially = yylhs.value.as < FunctionDefinition::Ptr > ()->initially();
      for( auto& initializer : *initially->initializers() )
      {
          initializer->updateRule()->function()->setIdentifier( IdentifierPath::fromIdentifier( yystack_[6].value.as < Identifier::Ptr > () ) );
      }
  }
#line 2442 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 31:
#line 598 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 2450 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 32:
#line 602 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 2460 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 33:
#line 608 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 2468 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 34:
#line 616 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto enumerators = yystack_[2].value.as < Enumerators::Ptr > ();
      yystack_[0].value.as < EnumeratorDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2479 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 35:
#line 623 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as < EnumeratorDefinition::Ptr > () );
      yylhs.value.as < Enumerators::Ptr > () = enumerators;
  }
#line 2489 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 36:
#line 633 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UsingDefinition::Ptr > () = Ast::make< UsingDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 37:
#line 641 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < InvariantDefinition::Ptr > () = Ast::make< InvariantDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2505 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 38:
#line 649 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 2513 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 39:
#line 653 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ImportDefinition::Ptr > () = Ast::make< ImportDefinition >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 2521 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 40:
#line 660 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IdentifierPath::Ptr > () = yystack_[0].value.as < IdentifierPath::Ptr > ();
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 41:
#line 664 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), IdentifierPath::Type::RELATIVE );
  }
#line 2538 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 42:
#line 677 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto rules = yystack_[1].value.as < Rules::Ptr > ();
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 2548 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 43:
#line 683 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as < Rule::Ptr > () );
      yylhs.value.as < Rules::Ptr > () = rules;
  }
#line 2558 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 44:
#line 693 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SkipRule::Ptr > ();
  }
#line 2566 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 45:
#line 697 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ConditionalRule::Ptr > ();
  }
#line 2574 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 46:
#line 701 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CaseRule::Ptr > ();
  }
#line 2582 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 47:
#line 705 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < LetRule::Ptr > ();
  }
#line 2590 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 48:
#line 709 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ForallRule::Ptr > ();
  }
#line 2598 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 49:
#line 713 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < ChooseRule::Ptr > ();
  }
#line 2606 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 50:
#line 717 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < IterateRule::Ptr > ();
  }
#line 2614 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 51:
#line 721 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < BlockRule::Ptr > ();
  }
#line 2622 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 52:
#line 725 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < SequenceRule::Ptr > ();
  }
#line 2630 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 53:
#line 729 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < UpdateRule::Ptr > ();
  }
#line 2638 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 54:
#line 733 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < CallRule::Ptr > ();
  }
#line 2646 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 55:
#line 737 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Rule::Ptr > () = yystack_[0].value.as < WhileRule::Ptr > ();
  }
#line 2654 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 56:
#line 745 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2662 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 57:
#line 753 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2670 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 58:
#line 757 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Rule::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2678 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 59:
#line 765 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Cases::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2686 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 60:
#line 769 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CaseRule::Ptr > () = nullptr;
  }
#line 2694 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 61:
#line 777 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto cases = yystack_[1].value.as < Cases::Ptr > ();
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 2704 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 62:
#line 783 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as < Case::Ptr > () );
      yylhs.value.as < Cases::Ptr > () = cases;
  }
#line 2714 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 63:
#line 793 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2722 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 64:
#line 797 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2730 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 65:
#line 801 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2738 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 66:
#line 809 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2746 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 67:
#line 817 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2754 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 68:
#line 821 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[7].value.as < Ast::Token::Ptr > (), yystack_[6].value.as < VariableDefinitions::Ptr > (), yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2762 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 69:
#line 829 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2770 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 70:
#line 837 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2778 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 71:
#line 845 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2786 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 72:
#line 849 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2794 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 73:
#line 853 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2803 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 74:
#line 858 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2812 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 75:
#line 867 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2820 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 76:
#line 871 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Rules::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2828 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 77:
#line 875 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2837 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 78:
#line 880 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2846 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 79:
#line 889 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as < DirectCallExpression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 2854 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 80:
#line 897 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as < CallExpression::Ptr > () );
  }
#line 2862 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 81:
#line 905 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < WhileRule::Ptr > () = Ast::make< WhileRule >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Rule::Ptr > () );
  }
#line 2870 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 82:
#line 917 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto expressions = yystack_[2].value.as < Expressions::Ptr > ();
      yystack_[0].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 2881 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 83:
#line 924 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Expressions::Ptr > () = expressions;
  }
#line 2891 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 84:
#line 934 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
     yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 2899 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 85:
#line 938 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < TypeCastingExpression::Ptr > ();
  }
#line 2907 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 86:
#line 942 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Expression::Ptr > ();
  }
#line 2915 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 87:
#line 946 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LetExpression::Ptr > ();
  }
#line 2923 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 88:
#line 950 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ConditionalExpression::Ptr > ();
  }
#line 2931 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 89:
#line 954 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ChooseExpression::Ptr > ();
  }
#line 2939 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 90:
#line 958 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < UniversalQuantifierExpression::Ptr > ();
  }
#line 2947 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 91:
#line 962 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < ExistentialQuantifierExpression::Ptr > ();
  }
#line 2955 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 92:
#line 966 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CardinalityExpression::Ptr > ();
  }
#line 2963 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 93:
#line 974 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< Ast::EmbracedExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 2971 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 94:
#line 978 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = nullptr;
  }
#line 2979 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 95:
#line 982 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < CallExpression::Ptr > ();
  }
#line 2987 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 96:
#line 986 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < LiteralCallExpression::Ptr > ();
  }
#line 2995 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 97:
#line 990 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = yystack_[0].value.as < Literal::Ptr > ();
  }
#line 3003 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 98:
#line 994 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3011 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 99:
#line 998 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 3019 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 100:
#line 1010 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 3027 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 101:
#line 1014 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 3035 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 102:
#line 1018 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 3043 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 103:
#line 1022 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 3051 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 104:
#line 1026 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 3059 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 105:
#line 1030 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 3067 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 106:
#line 1034 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 3075 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 107:
#line 1038 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 3083 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 108:
#line 1042 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 3091 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 109:
#line 1046 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 3099 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 110:
#line 1050 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 3107 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 111:
#line 1054 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 3115 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 112:
#line 1058 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 3123 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 113:
#line 1062 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 3131 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 114:
#line 1066 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 3139 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 115:
#line 1070 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3147 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 116:
#line 1074 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 3155 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 117:
#line 1078 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 3163 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 118:
#line 1086 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < DirectCallExpression::Ptr > ();
  }
#line 3171 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 119:
#line 1090 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < MethodCallExpression::Ptr > ();
  }
#line 3179 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 120:
#line 1094 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CallExpression::Ptr > () = yystack_[0].value.as < IndirectCallExpression::Ptr > ();
  }
#line 3187 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 121:
#line 1102 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > (), arguments );
  }
#line 3196 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 122:
#line 1107 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), arguments );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3207 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 123:
#line 1114 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < DirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3217 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 124:
#line 1120 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < DirectCallExpression::Ptr > () = nullptr;
  }
#line 3225 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 125:
#line 1128 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Identifier::Ptr > (), arguments );
  }
#line 3234 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 126:
#line 1133 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Identifier::Ptr > (), arguments );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3245 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 127:
#line 1140 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[5].value.as < Expression::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Identifier::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < MethodCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3255 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 128:
#line 1146 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < MethodCallExpression::Ptr > () = nullptr;
  }
#line 3263 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 129:
#line 1154 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < LiteralCallExpression::Ptr > () = Ast::make< LiteralCallExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < ValueLiteral::Ptr > () );
  }
#line 3271 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 130:
#line 1162 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as < CallExpression::Ptr > (), arguments );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3282 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 131:
#line 1169 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[3].value.as < CallExpression::Ptr > (), yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setLeftBracketToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < IndirectCallExpression::Ptr > ()->setRightBracketToken( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3292 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 132:
#line 1175 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IndirectCallExpression::Ptr > () = nullptr;
  }
#line 3300 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 133:
#line 1183 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
  }
#line 3308 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 134:
#line 1191 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < VariableBindings::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3316 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 135:
#line 1199 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < Expression::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3324 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 136:
#line 1207 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3332 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 137:
#line 1215 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3340 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 138:
#line 1223 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[5].value.as < Ast::Token::Ptr > (), yystack_[4].value.as < VariableDefinitions::Ptr > (), yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Expression::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3348 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 139:
#line 1231 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < CardinalityExpression::Ptr > () = Ast::make< CardinalityExpression >( yylhs.location, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3356 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 140:
#line 1244 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < UndefLiteral::Ptr > ();
  }
#line 3364 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 141:
#line 1248 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3372 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 142:
#line 1252 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3380 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 143:
#line 1256 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3388 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 144:
#line 1260 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3396 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 145:
#line 1264 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3404 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 146:
#line 1268 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3412 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 147:
#line 1272 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ReferenceLiteral::Ptr > ();
  }
#line 3420 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 148:
#line 1276 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < ListLiteral::Ptr > ();
  }
#line 3428 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 149:
#line 1280 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RangeLiteral::Ptr > ();
  }
#line 3436 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 150:
#line 1284 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < TupleLiteral::Ptr > ();
  }
#line 3444 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 151:
#line 1288 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Literal::Ptr > () = yystack_[0].value.as < RecordLiteral::Ptr > ();
  }
#line 3452 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 152:
#line 1296 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < UndefLiteral::Ptr > () = Ast::make< UndefLiteral >( yylhs.location );
      yylhs.value.as < UndefLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3461 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 153:
#line 1305 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3471 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 154:
#line 1311 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as < ValueLiteral::Ptr > () = Ast::make< ValueLiteral >( yylhs.location, value );
      yylhs.value.as < ValueLiteral::Ptr > ()->setSpans( yystack_[0].value.as < Ast::Token::Ptr > ()->spans() );
  }
#line 3481 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 155:
#line 1321 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3489 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 156:
#line 1329 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3497 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 157:
#line 1337 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3505 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 158:
#line 1345 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3513 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 159:
#line 1349 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3521 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 160:
#line 1357 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ValueLiteral::Ptr > () = yystack_[0].value.as < ValueLiteral::Ptr > ();
  }
#line 3529 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 161:
#line 1365 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ReferenceLiteral::Ptr > () = Ast::make< ReferenceLiteral >( yylhs.location, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3537 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 162:
#line 1373 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, expressions );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[1].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3548 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 163:
#line 1380 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ListLiteral::Ptr > () = Ast::make< ListLiteral >( yylhs.location, yystack_[1].value.as < Expressions::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < ListLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3558 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 164:
#line 1386 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ListLiteral::Ptr > () = nullptr;
  }
#line 3566 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 165:
#line 1394 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RangeLiteral::Ptr > () = Ast::make< RangeLiteral >( yylhs.location, yystack_[3].value.as < Expression::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RangeLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3576 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 166:
#line 1403 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto expressions = yystack_[3].value.as < Expressions::Ptr > ();
      yystack_[1].value.as < Expression::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      expressions->add( yystack_[1].value.as < Expression::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > () = Ast::make< TupleLiteral >( yylhs.location, expressions );
      yylhs.value.as < TupleLiteral::Ptr > ()->setLeftBracket( yystack_[4].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < TupleLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3589 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 167:
#line 1414 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RecordLiteral::Ptr > () = Ast::make< RecordLiteral >( yylhs.location, yystack_[1].value.as < NamedExpressions::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setLeftBracket( yystack_[2].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < RecordLiteral::Ptr > ()->setRightBracket( yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3599 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 168:
#line 1423 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto assignments = yystack_[2].value.as < NamedExpressions::Ptr > ();
      yystack_[0].value.as < NamedExpression::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 3610 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 169:
#line 1430 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto assignments = Ast::make< NamedExpressions >( yylhs.location );
      assignments->add( yystack_[0].value.as < NamedExpression::Ptr > () );
      yylhs.value.as < NamedExpressions::Ptr > () = assignments;
  }
#line 3620 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 170:
#line 1439 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < NamedExpression::Ptr > () = Ast::make< NamedExpression >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3628 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 171:
#line 1451 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3639 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 172:
#line 1458 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3649 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 173:
#line 1467 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < BasicType::Ptr > ();
  }
#line 3657 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 174:
#line 1471 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TupleType::Ptr > ();
  }
#line 3665 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 175:
#line 1475 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RecordType::Ptr > ();
  }
#line 3673 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 176:
#line 1479 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < TemplateType::Ptr > ();
  }
#line 3681 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 177:
#line 1483 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < RelationType::Ptr > ();
  }
#line 3689 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 178:
#line 1487 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as < FixedSizedType::Ptr > ();
  }
#line 3697 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 179:
#line 1495 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as < IdentifierPath::Ptr > () );
  }
#line 3705 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 180:
#line 1503 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto subTypes = yystack_[3].value.as < Types::Ptr > ();
      yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      subTypes->add( yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < TupleType::Ptr > () = Ast::make< TupleType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), subTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3716 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 181:
#line 1514 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto namedSubTypes = yystack_[3].value.as < VariableDefinitions::Ptr > ();
      yystack_[1].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[2].value.as < Ast::Token::Ptr > () );
      namedSubTypes->add( yystack_[1].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < RecordType::Ptr > () = Ast::make< RecordType >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), namedSubTypes, yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3727 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 182:
#line 1525 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < TemplateType::Ptr > () = Ast::make< TemplateType >( yylhs.location, yystack_[3].value.as < IdentifierPath::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Types::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3735 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 183:
#line 1533 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as < IdentifierPath::Ptr > (), yystack_[4].value.as < Ast::Token::Ptr > (), yystack_[3].value.as < Types::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3743 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 184:
#line 1541 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as < IdentifierPath::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 3751 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 185:
#line 1553 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = yystack_[2].value.as < Types::Ptr > ();
      yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3762 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 186:
#line 1560 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < Types::Ptr > () = types;
  }
#line 3772 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 187:
#line 1570 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Types::Ptr > () = yystack_[0].value.as < Types::Ptr > ();
  }
#line 3780 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 188:
#line 1574 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 3788 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 189:
#line 1582 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto parameters = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 3799 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 190:
#line 1589 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = parameters;
  }
#line 3809 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 191:
#line 1603 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Expression::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3817 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 192:
#line 1607 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Defined::Ptr > () = Ast::make< Defined >( yylhs.location, Token::unresolved(), Token::unresolved(), Ast::make< UndefLiteral >( yylhs.location ), Token::unresolved() );
  }
#line 3825 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 193:
#line 1615 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, yystack_[3].value.as < Ast::Token::Ptr > (), yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Initializers::Ptr > (), yystack_[0].value.as < Ast::Token::Ptr > () );
  }
#line 3833 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 194:
#line 1619 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto initializers = Ast::make< Initializers >( yylhs.location );
      yylhs.value.as < Initially::Ptr > () = Ast::make< Initially >( yylhs.location, Token::unresolved(), Token::unresolved(), initializers, Token::unresolved() );
  }
#line 3842 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 195:
#line 1628 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto initializers = yystack_[2].value.as < Initializers::Ptr > ();
      yystack_[0].value.as < Initializer::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 3853 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 196:
#line 1635 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto initializers = Ast::make< Initializers >( yylhs.location );
      initializers->add( yystack_[0].value.as < Initializer::Ptr > () );
      yylhs.value.as < Initializers::Ptr > () = initializers;
  }
#line 3863 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 197:
#line 1645 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, Token::unresolved(), arguments, Token::unresolved(), Token::unresolved(), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3874 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 198:
#line 1652 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[3].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, yystack_[4].value.as < Ast::Token::Ptr > (), arguments, yystack_[2].value.as < Ast::Token::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3886 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 199:
#line 1660 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto arguments = yystack_[2].value.as < TupleLiteral::Ptr > ()->expressions();
      const auto lbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->leftBracket();
      const auto rbToken = yystack_[2].value.as < TupleLiteral::Ptr > ()->rightBracket();
      yylhs.value.as < Initializer::Ptr > () = Ast::make< Initializer >( yylhs.location, lbToken, arguments, rbToken, yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->setSourceLocation( yylhs.location );
      yylhs.value.as < Initializer::Ptr > ()->updateRule()->function()->setSourceLocation( yylhs.location );
  }
#line 3899 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 200:
#line 1677 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Identifier::Ptr > () = yystack_[0].value.as < Identifier::Ptr > ();
  }
#line 3907 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 201:
#line 1681 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
      yylhs.value.as < Identifier::Ptr > ()->setSpans( m_lexer.fetchSpansAndReset() );
  }
#line 3916 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 202:
#line 1690 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto path = yystack_[2].value.as < IdentifierPath::Ptr > ();
      yystack_[0].value.as < Identifier::Ptr > ()->setDoubleColon( yystack_[1].value.as < Ast::Token::Ptr > () );
      path->addIdentifier( yystack_[0].value.as < Identifier::Ptr > () );
      yylhs.value.as < IdentifierPath::Ptr > () = path;
  }
#line 3927 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 203:
#line 1697 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 3935 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 204:
#line 1709 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 3943 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 205:
#line 1713 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as < VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > (), Token::unresolved(), unresolvedType );
  }
#line 3952 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 206:
#line 1722 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 3963 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 207:
#line 1729 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variables = Ast::make< VariableDefinitions >( yylhs.location );
      variables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = variables;
  }
#line 3973 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 208:
#line 1739 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto typedVariables = yystack_[2].value.as < VariableDefinitions::Ptr > ();
      yystack_[0].value.as < VariableDefinition::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3984 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 209:
#line 1746 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto typedVariables = Ast::make< VariableDefinitions >( yylhs.location );
      typedVariables->add( yystack_[0].value.as < VariableDefinition::Ptr > () );
      yylhs.value.as < VariableDefinitions::Ptr > () = typedVariables;
  }
#line 3994 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 210:
#line 1756 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variable = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as < Identifier::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4003 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 211:
#line 1765 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4013 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 212:
#line 1771 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4021 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 213:
#line 1779 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variable = yystack_[0].value.as < VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[1].value.as < Attributes::Ptr > () );
      yylhs.value.as < VariableDefinition::Ptr > () = variable;
  }
#line 4031 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 214:
#line 1785 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableDefinition::Ptr > () = yystack_[0].value.as < VariableDefinition::Ptr > ();
  }
#line 4039 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 215:
#line 1797 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variableBindings = yystack_[2].value.as < VariableBindings::Ptr > ();
      yystack_[0].value.as < VariableBinding::Ptr > ()->setDelimiterToken( yystack_[1].value.as < Ast::Token::Ptr > () );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4050 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 216:
#line 1804 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto variableBindings = Ast::make< VariableBindings >( yylhs.location );
      variableBindings->add( yystack_[0].value.as < VariableBinding::Ptr > () );
      yylhs.value.as < VariableBindings::Ptr > () = variableBindings;
  }
#line 4060 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 217:
#line 1813 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < VariableBinding::Ptr > () = Ast::make< VariableBinding >( yylhs.location, yystack_[2].value.as < VariableDefinition::Ptr > (), yystack_[1].value.as < Ast::Token::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4068 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 218:
#line 1825 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attributes = yystack_[1].value.as < Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4078 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 219:
#line 1831 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as < Attribute::Ptr > () );
      yylhs.value.as < Attributes::Ptr > () = attributes;
  }
#line 4088 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 220:
#line 1840 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attribute = yystack_[1].value.as < BasicAttribute::Ptr > ();
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < BasicAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4099 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 221:
#line 1847 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      auto attribute = yystack_[1].value.as < ExpressionAttribute::Ptr > ();
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setLeftBrace( yystack_[2].value.as < Ast::Token::Ptr > () );
      yystack_[1].value.as < ExpressionAttribute::Ptr > ()->setRightBrace( yystack_[0].value.as < Ast::Token::Ptr > () );
      yylhs.value.as < Attribute::Ptr > () = attribute;
  }
#line 4110 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 222:
#line 1854 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < Attribute::Ptr > () = nullptr;
  }
#line 4118 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 223:
#line 1861 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as < Identifier::Ptr > () );
  }
#line 4126 "GrammarParser.cpp" // lalr1.cc:919
    break;

  case 224:
#line 1868 "../../obj/src/GrammarParser.y" // lalr1.cc:919
    {
      yylhs.value.as < ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as < Identifier::Ptr > (), yystack_[0].value.as < Expression::Ptr > () );
  }
#line 4134 "GrammarParser.cpp" // lalr1.cc:919
    break;


#line 4138 "GrammarParser.cpp" // lalr1.cc:919
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


  const short Parser::yypact_ninf_ = -147;

  const short Parser::yytable_ninf_ = -187;

  const short
  Parser::yypact_[] =
  {
      18,  -147,    14,    51,   428,    40,  -147,   -41,  -147,  -147,
    1664,   -23,    94,  -147,  -147,    -1,    15,    15,    15,    15,
      15,     6,    15,   258,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,   437,  -147,  -147,  -147,     5,     5,
       5,  1664,     5,  -147,  -147,  -147,  1664,   603,   603,  1191,
     259,   603,    15,  -147,  -147,  -147,  -147,  -147,  -147,  2420,
      11,  -147,   111,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,   129,  -147,
    -147,  1728,   126,   107,   113,    52,   138,   186,    15,    34,
     126,   187,  -147,  -147,   189,  -147,  -147,   195,     0,  -147,
       5,    21,  -147,    22,  1957,    35,  -147,  -147,  -147,   166,
     196,  2175,   114,  -147,   193,   197,  -147,    61,  2210,    89,
     126,  1664,  1664,  1664,  1664,  1664,  1664,  1664,  1664,  1664,
    1664,  1664,  1664,  1664,  1664,  1664,  1664,  1664,     9,    12,
     999,  1063,    15,  1191,  2420,   185,   144,  -147,     4,     9,
     205,  1536,    13,     9,     9,  1664,  -147,    15,     9,     9,
    1664,  1664,     5,  -147,  1664,     5,  1664,  1664,  1664,  -147,
    1664,  -147,  -147,    15,  1664,  -147,  -147,  1664,  1664,  -147,
     462,  2490,  2520,  2455,   188,   188,   518,   161,   161,   206,
     206,   206,  -147,  2455,   518,   161,   161,     9,  -147,  -147,
    -147,  -147,  -147,  -147,  -147,    98,  -147,   210,   213,  -147,
     137,  2420,   224,  -147,   140,  -147,  2245,  1664,  -147,  1728,
     225,   153,   189,  -147,  -147,     5,   229,    65,   728,   797,
    -147,     5,     5,     5,  1536,  1664,  1664,  1664,   866,   935,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,   209,    45,   207,   234,   168,   242,  -147,
    2420,  -147,  -147,   231,   222,  -147,  2420,  2420,  -147,  2105,
    -147,  1795,  2034,  2140,  2280,  -147,   193,  2420,  2420,  2315,
     235,  -147,   189,   236,  -147,     9,  1664,  1127,  -147,  -147,
    -147,  -147,   230,  2420,  -147,   232,   233,     5,  -147,  1664,
    -147,  -147,   163,  -147,     5,   290,  1260,  -147,   293,  1329,
      57,    80,    90,  -147,  1996,  2070,  1836,   260,  1398,   238,
    1467,  1664,    71,   105,  1536,     9,     9,  1664,  1664,  1664,
    1664,  -147,  -147,     9,    15,   121,   159,   243,  -147,   271,
    -147,   181,  1664,     9,     9,  -147,  2420,  -147,    65,  -147,
    -147,  -147,  -147,  -147,  -147,  1536,  1664,  1664,  1536,   273,
    1536,  -147,  -147,  -147,  -147,  2420,  1536,     9,  1536,     9,
    -147,  -147,   309,  2420,  2420,  2420,  2420,   278,   286,     9,
    -147,     9,  -147,  -147,  2420,   298,   299,  -147,  -147,  1754,
    1877,   324,    27,  -147,  -147,   307,  -147,   308,   304,   349,
    -147,  -147,  -147,   302,  1664,  1664,  1536,  1664,  1536,  1536,
     311,   314,   322,  1600,  -147,  2350,  1536,  1536,  1664,   313,
    -147,  -147,  2420,  2420,  -147,  1918,  -147,  -147,  -147,  1536,
    1536,  -147,  -147,  1536,  -147,  -147,  2385,  1728,  1536,  -147,
    -147,  -147,  -147,   176,  -147,  -147
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,     0,   219,     0,   201,   200,
     223,     0,     0,     1,     9,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     6,     8,    10,    11,    12,    13,
      14,    15,    16,    17,     0,     3,   218,   222,     0,     0,
       0,     0,     0,   152,   154,   153,     0,     0,     0,     0,
       0,     0,     0,   158,   159,   155,   156,   157,   160,   224,
      84,    86,    95,   118,   119,    96,   120,    85,    87,    88,
      89,    90,    91,    92,    97,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   203,   121,   220,
     221,     0,    18,     0,     0,     0,     0,     0,     0,    38,
      40,     0,     5,     7,   205,   212,   204,     0,     0,   216,
       0,     0,   207,     0,     0,     0,   117,    98,    99,     0,
       0,    83,     0,   169,   203,     0,   162,     0,    83,     0,
     161,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   197,   150,     0,   196,     0,     0,
       0,     0,     0,     0,     0,     0,    41,     0,   188,     0,
       0,     0,     0,   211,     0,     0,     0,     0,     0,    94,
       0,    93,   167,     0,     0,   164,   163,     0,     0,   139,
     114,   112,   113,   116,   100,   101,   107,   108,   109,   102,
     103,   104,   105,   115,   106,   110,   111,     0,   133,   173,
     174,   175,   176,   177,   178,   179,   129,   125,     0,   130,
       0,    83,     0,   122,     0,   202,    83,     0,    19,     0,
       0,     0,     0,   214,   190,     0,     0,     0,     0,     0,
      56,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      24,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,     0,    80,   118,     0,     0,     0,    36,
      37,    39,   186,   187,     0,   210,   217,   134,   215,     0,
     206,     0,     0,     0,    82,   168,     0,   170,    82,     0,
       0,   172,   203,     0,   209,   188,     0,     0,   132,   131,
     124,   123,    93,   199,   195,     0,     0,     0,   213,     0,
      33,    35,     0,    31,     0,     0,     0,    43,     0,     0,
       0,     0,     0,    70,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   166,   165,     0,     0,     0,   172,     0,   184,     0,
     126,     0,     0,     0,     0,   189,    21,    20,     0,    32,
      78,    76,    42,    74,    72,     0,     0,     0,     0,     0,
       0,    73,    71,    77,    75,    79,     0,     0,     0,     0,
      25,   185,   192,   137,   136,   135,   138,   171,   208,     0,
     182,     0,   128,   127,   198,     0,     0,    34,    66,     0,
       0,    57,     0,    81,    28,     0,    26,     0,     0,   194,
     180,   181,   171,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    62,     0,     0,     0,     0,     0,
      30,   183,    23,    22,    67,     0,    69,    58,    60,     0,
       0,    59,    61,     0,    29,    27,     0,     0,     0,    63,
      64,    65,   191,     0,    68,   193
  };

  const short
  Parser::yypgoto_[] =
  {
    -147,  -147,  -147,  -147,   355,   346,  -147,  -147,  -147,  -147,
    -147,    25,  -147,  -147,  -147,  -147,  -147,   -39,   343,  -147,
    -147,  -147,  -147,   -38,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,   -49,   -10,   -45,  -147,   182,   227,  -147,
    -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
    -147,  -147,   237,  -147,  -147,  -147,  -147,  -147,  -147,  -147,
     -87,  -147,  -147,   201,    92,  -146,  -147,  -147,  -147,  -147,
    -147,  -147,  -147,    95,   239,  -147,  -147,   -58,   162,   330,
      23,   283,   -30,  -147,   -89,   -22,    99,   155,   244,     7,
       3,  -147,  -147
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    23,    24,    25,    26,    27,    28,    29,
      30,   311,   312,    31,    32,    33,    99,   316,   317,   251,
     252,   253,   423,   424,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   120,   154,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,   122,   123,   290,   208,   209,   210,   211,   212,
     213,   214,   273,   274,   231,   409,   430,   156,   157,    87,
      88,   105,   111,   293,   106,   112,   234,   108,   109,   110,
       6,    11,    12
  };

  const short
  Parser::yytable_[] =
  {
      59,   127,   117,   118,   155,   230,   129,     5,    36,    37,
     113,    34,   115,   236,   266,     7,   107,   268,   269,     8,
     171,     1,   272,   275,     8,     8,     8,    89,   420,     8,
      34,   114,     8,     8,     8,     8,   116,    36,    92,   121,
     128,   174,   176,    35,   100,   148,    38,     8,    39,    40,
      91,    13,    41,     2,     2,   178,   207,   421,   172,    42,
      98,   291,     2,    43,    44,    45,   310,     2,   167,   233,
      46,    47,    48,   233,    49,   130,    50,   365,   149,   175,
     175,     9,   422,    51,    52,     8,     9,     9,     9,     2,
      55,     9,   150,   175,     9,     9,     9,     9,   161,   162,
     366,   220,   224,    53,    54,    55,    56,    57,    58,     9,
     367,   186,   -95,    36,     2,   172,   263,   376,   294,   187,
     163,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   205,   206,   175,   377,
     221,   221,   155,   226,    90,   189,   308,     9,   175,   346,
     107,   378,   152,   280,   158,   270,   149,   295,   150,   160,
     276,   277,   182,   296,   279,   235,   281,   282,   283,   235,
     284,   215,   183,   379,   287,   159,   151,   288,   289,   389,
     152,   390,   215,   152,   164,   299,   215,   215,   301,   381,
     382,   215,   215,   263,   263,   187,   228,   387,   187,   263,
     319,   306,   229,   263,   263,   135,   136,   395,   396,   328,
     330,   307,   321,   322,   179,   357,   333,   303,   233,   107,
    -186,   358,   140,   141,   142,   143,   307,  -186,   455,   393,
     215,   405,   165,   407,   229,   324,   325,   326,    36,   187,
     168,   170,   169,   412,   314,   413,   184,   185,   351,   140,
     141,   142,   143,   227,   180,   388,   237,   297,    -2,    14,
     125,   298,    15,    16,    17,    18,    19,    20,    21,    22,
     143,   263,   300,   305,   263,   309,   149,   331,    38,     8,
      39,    40,   332,   263,    41,   263,   348,   221,   334,   263,
     336,    42,   335,   343,   344,    43,    44,    45,   352,   356,
     353,   354,    46,    47,    48,   360,    49,     2,    50,   126,
     363,   391,   371,   373,   235,    51,    52,    36,   215,   392,
     263,   375,   408,   263,   402,   263,   410,   383,   384,   385,
     386,   263,    10,   263,   411,    53,    54,    55,    56,    57,
      58,     9,   394,   264,   414,   415,    93,    94,    95,    96,
      97,   419,   101,   426,   427,   428,   399,   400,   215,   215,
     155,   429,   431,   438,   447,   314,   215,   439,   104,   104,
     104,   263,   104,   263,   263,   440,   215,   215,   102,   124,
     103,   263,   263,   397,   285,   442,   216,   345,   265,   453,
     347,   304,   425,   173,   263,   263,   320,     0,   263,     0,
     215,   267,   215,   263,   432,   433,   355,   435,     0,     0,
       0,     0,   215,   425,   215,     0,   278,     0,   446,     0,
     264,   264,     0,     0,     0,     0,   264,     0,   166,    14,
     264,   264,    15,    16,    17,    18,    19,    20,    21,    22,
     104,    15,    16,    17,    18,    19,    20,    21,    22,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   265,   265,     0,     0,     0,
       0,   265,     0,     0,     0,   265,   265,     2,     0,   217,
       0,     0,   225,   124,     0,     0,     2,     0,   232,     0,
       0,     0,   232,     0,     0,     0,     0,   271,   264,     0,
       0,   264,   104,     0,   250,   104,   135,   136,   137,     0,
     264,     0,   264,   286,     0,     0,   264,     0,     0,     0,
       0,   138,   139,   140,   141,   142,   143,     0,     0,     0,
       0,     0,     0,   145,   146,   147,     0,   292,     0,     0,
       0,     0,     0,   265,     0,     0,   265,   264,     0,     0,
     264,     0,   264,     0,     0,   265,     0,   265,   264,     0,
     264,   265,   135,   136,     0,   232,     0,   313,     0,     0,
       0,   104,   104,   104,     0,     0,     0,   138,   139,   140,
     141,   142,   143,     0,     0,     0,     0,   323,     0,     0,
     146,   147,   265,     0,     0,   265,     0,   265,   264,     0,
     264,   264,     0,   265,     0,   265,     0,     0,   264,   264,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   264,   264,     8,     0,   264,     0,     0,     0,     0,
     264,     0,     0,     0,     0,     0,     0,   232,     0,    43,
      44,    45,     0,   265,   359,   265,   265,    47,    48,     0,
      49,     0,    50,   265,   265,     0,     0,     0,     0,   362,
      52,     0,   362,     0,     0,     0,   265,   265,     0,     0,
     265,   362,     0,   362,   232,   265,     0,   380,     0,    53,
      54,    55,    56,    57,    58,     9,     0,     0,   313,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   398,     0,
       0,   401,     0,   403,     0,     0,     0,     0,     0,   404,
       0,   406,     0,     0,     0,     0,     0,     0,     0,   315,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   238,     0,   239,     0,   240,   241,     8,   242,
     243,   244,     0,   245,     0,     0,   246,     0,     0,   434,
       0,   436,   437,   247,    43,    44,    45,     0,     0,   444,
     445,     0,    47,    48,     0,    49,     0,    50,     0,   248,
       0,     0,   449,   450,     0,    52,   451,     0,     0,     0,
       0,   454,     0,     0,     0,     0,     0,     0,   318,     0,
       0,     0,   249,     0,    53,    54,    55,    56,    57,    58,
       9,   238,     0,   239,     0,   240,   241,     8,   242,   243,
     244,     0,   245,     0,     0,   246,     0,     0,     0,     0,
       0,     0,   247,    43,    44,    45,     0,     0,     0,     0,
       0,    47,    48,     0,    49,     0,    50,     0,   248,     0,
       0,     0,     0,     0,    52,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   327,     0,     0,
       0,   249,     0,    53,    54,    55,    56,    57,    58,     9,
     238,     0,   239,     0,   240,   241,     8,   242,   243,   244,
       0,   245,     0,     0,   246,     0,     0,     0,     0,     0,
       0,   247,    43,    44,    45,     0,     0,     0,     0,     0,
      47,    48,     0,    49,     0,    50,     0,   248,     0,     0,
       0,     0,     0,    52,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   329,     0,     0,     0,
     249,     0,    53,    54,    55,    56,    57,    58,     9,   238,
       0,   239,     0,   240,   241,     8,   242,   243,   244,     0,
     245,     0,     0,   246,     0,     0,     0,     0,     0,     0,
     247,    43,    44,    45,     0,     0,     0,     0,     0,    47,
      48,     0,    49,     0,    50,     0,   248,     0,     0,     0,
       0,     0,    52,     0,     0,     0,     0,     0,     0,     0,
     218,     0,     0,     0,     0,     0,     0,     0,     0,   249,
       0,    53,    54,    55,    56,    57,    58,     9,    38,     8,
      39,    40,     0,     0,    41,     0,     0,     0,     0,     0,
       0,    42,     0,     0,     0,    43,    44,    45,     0,     0,
       0,     0,    46,    47,    48,     0,    49,   219,    50,     0,
       0,     0,     0,     0,     0,    51,    52,     0,     0,     0,
       0,     0,     0,     0,   222,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    53,    54,    55,    56,    57,
      58,     9,    38,     8,    39,    40,     0,     0,    41,     0,
       0,     0,     0,     0,     0,    42,     0,     0,     0,    43,
      44,    45,     0,     0,     0,     0,    46,    47,    48,     0,
      49,   223,    50,     0,     0,     0,     0,     0,     0,    51,
      52,     0,     0,     0,     0,     0,     0,     0,   349,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    53,
      54,    55,    56,    57,    58,     9,    38,     8,    39,    40,
       0,     0,    41,     0,     0,     0,     0,     0,     0,    42,
       0,     0,     0,    43,    44,    45,     0,     0,     0,     0,
      46,    47,    48,     0,    49,   350,    50,     0,     0,     0,
       0,     0,     0,    51,    52,     0,     0,     0,     0,     0,
       0,     0,   119,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    53,    54,    55,    56,    57,    58,     9,
      38,     8,    39,    40,     0,     0,    41,     0,     0,     0,
       0,     0,     0,    42,     0,     0,     0,    43,    44,    45,
       0,     0,     0,     0,    46,    47,    48,     0,    49,     0,
      50,     0,     0,     0,     0,     0,     0,    51,    52,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    53,    54,    55,
      56,    57,    58,     9,   238,   361,   239,     0,   240,   241,
       8,   242,   243,   244,     0,   245,     0,     0,   246,     0,
       0,     0,     0,     0,     0,   247,    43,    44,    45,     0,
       0,     0,     0,     0,    47,    48,     0,    49,     0,    50,
       0,   248,     0,     0,     0,     0,     0,    52,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   249,     0,    53,    54,    55,    56,
      57,    58,     9,   238,     0,   239,   364,   240,   241,     8,
     242,   243,   244,     0,   245,     0,     0,   246,     0,     0,
       0,     0,     0,     0,   247,    43,    44,    45,     0,     0,
       0,     0,     0,    47,    48,     0,    49,     0,    50,     0,
     248,     0,     0,     0,     0,     0,    52,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   249,     0,    53,    54,    55,    56,    57,
      58,     9,   238,     0,   239,     0,   240,   241,     8,   242,
     243,   244,     0,   245,     0,     0,   246,     0,     0,     0,
       0,     0,     0,   247,    43,    44,    45,     0,     0,     0,
       0,     0,    47,    48,     0,    49,     0,    50,     0,   248,
     372,     0,     0,     0,     0,    52,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   249,     0,    53,    54,    55,    56,    57,    58,
       9,   238,     0,   239,     0,   240,   241,     8,   242,   243,
     244,     0,   245,     0,     0,   246,     0,     0,     0,     0,
       0,     0,   247,    43,    44,    45,     0,     0,     0,     0,
       0,    47,    48,     0,    49,     0,    50,     0,   248,     0,
       0,     0,     0,     0,    52,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   249,   374,    53,    54,    55,    56,    57,    58,     9,
     238,     0,   239,     0,   240,   241,     8,   242,   243,   244,
       0,   245,     0,     0,   246,     0,     0,     0,     0,     0,
       0,   247,    43,    44,    45,     0,     0,     0,     0,     0,
      47,    48,     0,    49,     0,    50,     0,   248,     0,     0,
       0,     0,     0,    52,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     249,     0,    53,    54,    55,    56,    57,    58,     9,    38,
       8,    39,    40,     0,     0,    41,     0,     0,     0,     0,
     421,     0,    42,     0,     0,     0,    43,    44,    45,     0,
       0,     0,     0,    46,    47,    48,     0,    49,     0,    50,
       0,     0,   441,     0,     0,   422,    51,    52,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    53,    54,    55,    56,
      57,    58,     9,    38,     8,    39,    40,     0,     0,    41,
       0,     0,     0,     0,     0,     0,    42,     0,     0,     0,
      43,    44,    45,     0,     0,     0,     0,    46,    47,    48,
       0,    49,     0,    50,     0,     0,     0,     0,     0,     0,
      51,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      53,    54,    55,    56,    57,    58,     9,    38,     8,    39,
      40,     0,     0,    41,     0,     0,     0,     0,     0,     0,
      42,     0,     0,     0,    43,    44,    45,     0,     0,     0,
       0,    46,    47,    48,     0,   153,     0,    50,   416,     0,
       0,     0,     0,     0,    51,    52,     0,   417,     0,     0,
       0,     0,     0,   131,   132,   133,   134,     0,   135,   136,
     137,     0,     0,     0,    53,    54,    55,    56,    57,    58,
       9,     0,     0,   138,   139,   140,   141,   142,   143,   338,
       0,     0,     0,   144,     0,   145,   146,   147,     0,     0,
       0,     0,     0,     0,   131,   132,   133,   134,     0,   135,
     136,   137,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
     370,     0,     0,     0,   144,     0,   145,   146,   147,     0,
       0,     0,     0,     0,     0,   131,   132,   133,   134,     0,
     135,   136,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,   418,     0,     0,     0,   144,     0,   145,   146,   147,
       0,     0,     0,     0,     0,     0,   131,   132,   133,   134,
       0,   135,   136,   137,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   138,   139,   140,   141,
     142,   143,   448,     0,     0,     0,   144,     0,   145,   146,
     147,     0,     0,     0,     0,     0,     0,   131,   132,   133,
     134,     0,   135,   136,   137,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   138,   139,   140,
     141,   142,   143,   177,     0,     0,     0,   144,     0,   145,
     146,   147,     0,     0,     0,     0,   131,   132,   133,   134,
       0,   135,   136,   137,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   138,   139,   140,   141,
     142,   143,   368,     0,     0,     0,   144,     0,   145,   146,
     147,     0,     0,     0,     0,   131,   132,   133,   134,     0,
     135,   136,   137,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   138,   139,   140,   141,   142,
     143,   339,     0,     0,     0,   144,     0,   145,   146,   147,
       0,     0,     0,   131,   132,   133,   134,     0,   135,   136,
     137,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   138,   139,   140,   141,   142,   143,   369,
       0,     0,     0,   144,     0,   145,   146,   147,     0,   131,
     132,   133,   134,     0,   135,   136,   137,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   138,
     139,   140,   141,   142,   143,     0,   337,     0,     0,   144,
       0,   145,   146,   147,   131,   132,   133,   134,     0,   135,
     136,   137,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
       0,     0,     0,   340,   144,     0,   145,   146,   147,   131,
     132,   133,   134,     0,   135,   136,   137,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   138,
     139,   140,   141,   142,   143,     0,     0,     0,     0,   144,
       0,   145,   146,   147,   131,   132,   133,   134,     0,   135,
     136,   137,     0,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
       0,     0,     0,     0,   144,     0,   145,   146,   147,   131,
     132,   133,   134,     0,   135,   136,   137,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   138,
     139,   140,   141,   142,   143,     0,   188,     0,     0,   144,
       0,   145,   146,   147,   131,   132,   133,   134,     0,   135,
     136,   137,     0,   302,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
       0,     0,     0,     0,   144,     0,   145,   146,   147,   131,
     132,   133,   134,     0,   135,   136,   137,     0,   341,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   138,
     139,   140,   141,   142,   143,     0,     0,     0,     0,   144,
       0,   145,   146,   147,   131,   132,   133,   134,     0,   135,
     136,   137,     0,     0,     0,   342,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
       0,     0,     0,     0,   144,     0,   145,   146,   147,   131,
     132,   133,   134,     0,   135,   136,   137,     0,     0,     0,
       0,     0,     0,   443,     0,     0,     0,     0,     0,   138,
     139,   140,   141,   142,   143,     0,     0,     0,     0,   144,
       0,   145,   146,   147,   131,   132,   133,   134,     0,   135,
     136,   137,     0,     0,     0,     0,     0,   452,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
       0,     0,     0,     0,   144,     0,   145,   146,   147,   131,
     132,   133,   134,     0,   135,   136,   137,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   138,
     139,   140,   141,   142,   143,     0,     0,     0,     0,   144,
       0,   145,   146,   147,   131,   132,   133,     0,     0,   135,
     136,   137,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   138,   139,   140,   141,   142,   143,
       0,     0,     0,     0,     0,     0,   145,   146,   147,   131,
       0,   133,     0,     0,   135,   136,   137,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   138,
     139,   140,   141,   142,   143,     0,     0,     0,     0,   131,
       0,   145,   146,   147,   135,   136,   137,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   138,
     139,   140,   141,   142,   143,     0,     0,     0,     0,     0,
       0,   145,   146,   147
  };

  const short
  Parser::yycheck_[] =
  {
      10,    50,    47,    48,    91,     1,    51,     0,     5,    50,
      40,     4,    42,   159,     1,     1,    38,   163,   164,    20,
      20,     3,   168,   169,    20,    20,    20,    50,     1,    20,
      23,    41,    20,    20,    20,    20,    46,    34,    15,    49,
      50,    20,    20,     3,    21,    34,    19,    20,    21,    22,
      51,     0,    25,    49,    49,    20,    47,    30,    58,    32,
      54,   207,    49,    36,    37,    38,     1,    49,    34,   158,
      43,    44,    45,   162,    47,    52,    49,    20,    67,    58,
      58,    82,    55,    56,    57,    20,    82,    82,    82,    49,
      78,    82,    47,    58,    82,    82,    82,    82,    46,    47,
      20,   150,   151,    76,    77,    78,    79,    80,    81,    82,
      20,    50,    67,   110,    49,    58,   161,    46,   207,    58,
      68,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,    58,    68,
     150,   151,   229,   153,    50,    56,   235,    82,    58,   295,
     172,    46,    54,   175,    47,   165,    67,    59,    47,    46,
     170,   171,    48,    65,   174,   158,   176,   177,   178,   162,
     180,   148,    58,    68,   184,    68,    47,   187,   188,    58,
      54,    60,   159,    54,    46,    48,   163,   164,    48,   335,
     336,   168,   169,   238,   239,    58,    52,   343,    58,   244,
     239,    48,    58,   248,   249,    44,    45,   353,   354,   248,
     249,    58,   242,   243,    48,    52,    48,   227,   307,   241,
      61,    58,    61,    62,    63,    64,    58,    68,    52,    48,
     207,   377,    46,   379,    58,   245,   246,   247,   235,    58,
      53,    46,    53,   389,   237,   391,    53,    50,   297,    61,
      62,    63,    64,    68,    58,   344,    51,    47,     0,     1,
       1,    48,     4,     5,     6,     7,     8,     9,    10,    11,
      64,   316,    48,    48,   319,    46,    67,    70,    19,    20,
      21,    22,    48,   328,    25,   330,   296,   297,    46,   334,
      68,    32,    61,    58,    58,    36,    37,    38,    68,   309,
      68,    68,    43,    44,    45,    15,    47,    49,    49,    50,
      17,    68,    52,    75,   307,    56,    57,   314,   295,    48,
     365,   331,    13,   368,    51,   370,    48,   337,   338,   339,
     340,   376,     2,   378,    48,    76,    77,    78,    79,    80,
      81,    82,   352,   161,    46,    46,    16,    17,    18,    19,
      20,    27,    22,    46,    46,    51,   366,   367,   335,   336,
     447,    12,    60,    52,    51,   358,   343,    53,    38,    39,
      40,   416,    42,   418,   419,    53,   353,   354,    23,    49,
      34,   426,   427,   358,   183,   423,   149,   295,   161,   447,
     295,   229,   402,   110,   439,   440,   241,    -1,   443,    -1,
     377,   162,   379,   448,   414,   415,   307,   417,    -1,    -1,
      -1,    -1,   389,   423,   391,    -1,   172,    -1,   428,    -1,
     238,   239,    -1,    -1,    -1,    -1,   244,    -1,    98,     1,
     248,   249,     4,     5,     6,     7,     8,     9,    10,    11,
     110,     4,     5,     6,     7,     8,     9,    10,    11,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   238,   239,    -1,    -1,    -1,
      -1,   244,    -1,    -1,    -1,   248,   249,    49,    -1,   149,
      -1,    -1,   152,   153,    -1,    -1,    49,    -1,   158,    -1,
      -1,    -1,   162,    -1,    -1,    -1,    -1,   167,   316,    -1,
      -1,   319,   172,    -1,   161,   175,    44,    45,    46,    -1,
     328,    -1,   330,   183,    -1,    -1,   334,    -1,    -1,    -1,
      -1,    59,    60,    61,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    71,    72,    73,    -1,   207,    -1,    -1,
      -1,    -1,    -1,   316,    -1,    -1,   319,   365,    -1,    -1,
     368,    -1,   370,    -1,    -1,   328,    -1,   330,   376,    -1,
     378,   334,    44,    45,    -1,   235,    -1,   237,    -1,    -1,
      -1,   241,   242,   243,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    64,    -1,    -1,    -1,    -1,   244,    -1,    -1,
      72,    73,   365,    -1,    -1,   368,    -1,   370,   416,    -1,
     418,   419,    -1,   376,    -1,   378,    -1,    -1,   426,   427,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   439,   440,    20,    -1,   443,    -1,    -1,    -1,    -1,
     448,    -1,    -1,    -1,    -1,    -1,    -1,   307,    -1,    36,
      37,    38,    -1,   416,   314,   418,   419,    44,    45,    -1,
      47,    -1,    49,   426,   427,    -1,    -1,    -1,    -1,   316,
      57,    -1,   319,    -1,    -1,    -1,   439,   440,    -1,    -1,
     443,   328,    -1,   330,   344,   448,    -1,   334,    -1,    76,
      77,    78,    79,    80,    81,    82,    -1,    -1,   358,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   365,    -1,
      -1,   368,    -1,   370,    -1,    -1,    -1,    -1,    -1,   376,
      -1,   378,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    14,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    -1,    25,    -1,    -1,    28,    -1,    -1,   416,
      -1,   418,   419,    35,    36,    37,    38,    -1,    -1,   426,
     427,    -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,
      -1,    -1,   439,   440,    -1,    57,   443,    -1,    -1,    -1,
      -1,   448,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    74,    -1,    76,    77,    78,    79,    80,    81,
      82,    14,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    74,    -1,    76,    77,    78,    79,    80,    81,    82,
      14,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    79,    80,    81,    82,    14,
      -1,    16,    -1,    18,    19,    20,    21,    22,    23,    -1,
      25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,    44,
      45,    -1,    47,    -1,    49,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,
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
      43,    44,    45,    -1,    47,    48,    49,    -1,    -1,    -1,
      -1,    -1,    -1,    56,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    77,    78,    79,    80,    81,    82,
      19,    20,    21,    22,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,    38,
      -1,    -1,    -1,    -1,    43,    44,    45,    -1,    47,    -1,
      49,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,
      79,    80,    81,    82,    14,    15,    16,    -1,    18,    19,
      20,    21,    22,    23,    -1,    25,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,
      -1,    -1,    -1,    -1,    44,    45,    -1,    47,    -1,    49,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    76,    77,    78,    79,
      80,    81,    82,    14,    -1,    16,    17,    18,    19,    20,
      21,    22,    23,    -1,    25,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,    -1,
      -1,    -1,    -1,    44,    45,    -1,    47,    -1,    49,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    -1,    76,    77,    78,    79,    80,
      81,    82,    14,    -1,    16,    -1,    18,    19,    20,    21,
      22,    23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,
      -1,    -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,
      52,    -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    76,    77,    78,    79,    80,    81,
      82,    14,    -1,    16,    -1,    18,    19,    20,    21,    22,
      23,    -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,
      -1,    44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      14,    -1,    16,    -1,    18,    19,    20,    21,    22,    23,
      -1,    25,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    -1,    -1,    -1,    -1,    -1,
      44,    45,    -1,    47,    -1,    49,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    57,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    76,    77,    78,    79,    80,    81,    82,    19,
      20,    21,    22,    -1,    -1,    25,    -1,    -1,    -1,    -1,
      30,    -1,    32,    -1,    -1,    -1,    36,    37,    38,    -1,
      -1,    -1,    -1,    43,    44,    45,    -1,    47,    -1,    49,
      -1,    -1,    52,    -1,    -1,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    77,    78,    79,
      80,    81,    82,    19,    20,    21,    22,    -1,    -1,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,
      36,    37,    38,    -1,    -1,    -1,    -1,    43,    44,    45,
      -1,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    57,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    77,    78,    79,    80,    81,    82,    19,    20,    21,
      22,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,
      32,    -1,    -1,    -1,    36,    37,    38,    -1,    -1,    -1,
      -1,    43,    44,    45,    -1,    47,    -1,    49,    24,    -1,
      -1,    -1,    -1,    -1,    56,    57,    -1,    33,    -1,    -1,
      -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,    45,
      46,    -1,    -1,    -1,    76,    77,    78,    79,    80,    81,
      82,    -1,    -1,    59,    60,    61,    62,    63,    64,    24,
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
      63,    64,    24,    -1,    -1,    -1,    69,    -1,    71,    72,
      73,    -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,
      42,    -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,
      62,    63,    64,    26,    -1,    -1,    -1,    69,    -1,    71,
      72,    73,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      -1,    44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,
      63,    64,    26,    -1,    -1,    -1,    69,    -1,    71,    72,
      73,    -1,    -1,    -1,    -1,    39,    40,    41,    42,    -1,
      44,    45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,
      64,    27,    -1,    -1,    -1,    69,    -1,    71,    72,    73,
      -1,    -1,    -1,    39,    40,    41,    42,    -1,    44,    45,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    59,    60,    61,    62,    63,    64,    29,
      -1,    -1,    -1,    69,    -1,    71,    72,    73,    -1,    39,
      40,    41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    31,    -1,    -1,    69,
      -1,    71,    72,    73,    39,    40,    41,    42,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    33,    69,    -1,    71,    72,    73,    39,
      40,    41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    69,
      -1,    71,    72,    73,    39,    40,    41,    42,    -1,    44,
      45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,    39,
      40,    41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    66,    -1,    -1,    69,
      -1,    71,    72,    73,    39,    40,    41,    42,    -1,    44,
      45,    46,    -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,    39,
      40,    41,    42,    -1,    44,    45,    46,    -1,    48,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    69,
      -1,    71,    72,    73,    39,    40,    41,    42,    -1,    44,
      45,    46,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,    39,
      40,    41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    69,
      -1,    71,    72,    73,    39,    40,    41,    42,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    69,    -1,    71,    72,    73,    39,
      40,    41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    69,
      -1,    71,    72,    73,    39,    40,    41,    -1,    -1,    44,
      45,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    59,    60,    61,    62,    63,    64,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    39,
      -1,    41,    -1,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    39,
      -1,    71,    72,    73,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    59,
      60,    61,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    71,    72,    73
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    49,    89,    90,   177,   178,     1,    20,    82,
     167,   179,   180,     0,     1,     4,     5,     6,     7,     8,
       9,    10,    11,    91,    92,    93,    94,    95,    96,    97,
      98,   101,   102,   103,   177,     3,   178,    50,    19,    21,
      22,    25,    32,    36,    37,    38,    43,    44,    45,    47,
      49,    56,    57,    76,    77,    78,    79,    80,    81,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   145,   146,   147,   148,   149,   167,   168,    50,
      50,    51,   168,   167,   167,   167,   167,   167,    54,   104,
     168,   167,    92,    93,   167,   169,   172,   173,   175,   176,
     177,   170,   173,   170,   122,   170,   122,   123,   123,     1,
     121,   122,   150,   151,   167,     1,    50,   121,   122,   123,
     168,    39,    40,    41,    42,    44,    45,    46,    59,    60,
      61,    62,    63,    64,    69,    71,    72,    73,    34,    67,
      47,    47,    54,    47,   122,   148,   165,   166,    47,    68,
      46,    46,    47,    68,    46,    46,   167,    34,    53,    53,
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
     122,   167,   153,   160,   161,   153,   122,   122,   176,   122,
     173,   122,   122,   122,   122,   151,   167,   122,   122,   122,
     152,   153,   167,   171,   172,    59,    65,    47,    48,    48,
      48,    48,    48,   122,   166,    48,    48,    58,   172,    46,
       1,    99,   100,   167,   177,     1,   105,   106,     1,   105,
     175,   170,   170,   106,   122,   122,   122,     1,   105,     1,
     105,    70,    48,    48,    46,    61,    68,    31,    24,    27,
      33,    48,    50,    58,    58,   152,   153,   161,   122,     1,
      48,   121,    68,    68,    68,   174,   122,    52,    58,   167,
      15,    15,   106,    17,    17,    20,    20,    20,    26,    29,
      24,    52,    52,    75,    75,   122,    46,    68,    46,    68,
     106,   153,   153,   122,   122,   122,   122,   153,   172,    58,
      60,    68,    48,    48,   122,   153,   153,    99,   106,   122,
     122,   106,    51,   106,   106,   153,   106,   153,    13,   163,
      48,    48,   153,   153,    46,    46,    24,    33,    24,    27,
       1,    30,    55,   110,   111,   122,    46,    46,    51,    12,
     164,    60,   122,   122,   106,   122,   106,   106,    52,    53,
      53,    52,   111,    53,   106,   106,   122,    51,    24,   106,
     106,   106,    52,   165,   106,    52
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    88,    89,    90,    90,    91,    91,    92,    92,    92,
      93,    93,    93,    93,    93,    93,    93,    93,    94,    94,
      95,    96,    96,    96,    97,    97,    97,    97,    97,    97,
      98,    99,    99,    99,   100,   100,   101,   102,   103,   103,
     104,   104,   105,   105,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   106,   106,   106,   107,   108,   108,   109,
     109,   110,   110,   111,   111,   111,   112,   113,   113,   114,
     115,   116,   116,   116,   116,   117,   117,   117,   117,   118,
     119,   120,   121,   121,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   123,   123,   123,   123,   123,   123,   123,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   125,   125,
     125,   126,   126,   126,   126,   127,   127,   127,   127,   128,
     129,   129,   129,   130,   131,   132,   133,   134,   135,   136,
     137,   137,   137,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   138,   139,   139,   140,   141,   142,   143,   143,
     144,   145,   146,   146,   146,   147,   148,   149,   150,   150,
     151,   152,   152,   153,   153,   153,   153,   153,   153,   154,
     155,   156,   157,   158,   159,   160,   160,   161,   161,   162,
     162,   163,   163,   164,   164,   165,   165,   166,   166,   166,
     167,   167,   168,   168,   169,   169,   170,   170,   171,   171,
     172,   173,   173,   174,   174,   175,   175,   176,   177,   177,
     178,   178,   178,   179,   180
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     2,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     4,
       6,     6,     9,     9,     4,     6,     7,     9,     7,     9,
       8,     1,     2,     1,     3,     1,     4,     4,     2,     4,
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     6,     6,
       6,     2,     1,     3,     3,     3,     4,     6,     8,     6,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     4,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     3,     1,     1,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     1,
       1,     1,     3,     4,     4,     3,     5,     6,     6,     3,
       3,     4,     4,     3,     4,     6,     6,     6,     6,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     3,     3,     5,     5,     3,     3,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       5,     5,     4,     6,     3,     3,     1,     1,     0,     3,
       1,     4,     0,     4,     0,     3,     1,     1,     5,     3,
       1,     1,     3,     1,     1,     1,     3,     1,     3,     1,
       3,     2,     1,     2,     1,     3,     1,     3,     2,     1,
       3,     3,     3,     1,     2
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
  "UsingDefinition", "InvariantDefinition", "ImportDefinition",
  "ImportPath", "Rules", "Rule", "SkipRule", "ConditionalRule", "CaseRule",
  "CaseLabels", "CaseLabel", "LetRule", "ForallRule", "ChooseRule",
  "IterateRule", "BlockRule", "SequenceRule", "UpdateRule", "CallRule",
  "WhileRule", "Terms", "Term", "SimpleOrClaspedTerm",
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
     471,   475,   479,   483,   487,   491,   495,   499,   507,   511,
     519,   527,   532,   538,   546,   552,   557,   564,   570,   574,
     582,   597,   601,   607,   615,   622,   632,   640,   648,   652,
     659,   663,   676,   682,   692,   696,   700,   704,   708,   712,
     716,   720,   724,   728,   732,   736,   744,   752,   756,   764,
     768,   776,   782,   792,   796,   800,   808,   816,   820,   828,
     836,   844,   848,   852,   857,   866,   870,   874,   879,   888,
     896,   904,   916,   923,   933,   937,   941,   945,   949,   953,
     957,   961,   965,   973,   977,   981,   985,   989,   993,   997,
    1009,  1013,  1017,  1021,  1025,  1029,  1033,  1037,  1041,  1045,
    1049,  1053,  1057,  1061,  1065,  1069,  1073,  1077,  1085,  1089,
    1093,  1101,  1106,  1113,  1119,  1127,  1132,  1139,  1145,  1153,
    1161,  1168,  1174,  1182,  1190,  1198,  1206,  1214,  1222,  1230,
    1243,  1247,  1251,  1255,  1259,  1263,  1267,  1271,  1275,  1279,
    1283,  1287,  1295,  1304,  1310,  1320,  1328,  1336,  1344,  1348,
    1356,  1364,  1372,  1379,  1385,  1393,  1402,  1413,  1422,  1429,
    1438,  1450,  1457,  1466,  1470,  1474,  1478,  1482,  1486,  1494,
    1502,  1513,  1524,  1532,  1540,  1552,  1559,  1569,  1573,  1581,
    1588,  1602,  1606,  1614,  1618,  1627,  1634,  1644,  1651,  1659,
    1676,  1680,  1689,  1696,  1708,  1712,  1721,  1728,  1738,  1745,
    1755,  1764,  1770,  1778,  1784,  1796,  1803,  1812,  1824,  1830,
    1839,  1846,  1853,  1860,  1867
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
#line 5292 "GrammarParser.cpp" // lalr1.cc:1242
#line 1873 "../../obj/src/GrammarParser.y" // lalr1.cc:1243


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
