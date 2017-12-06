// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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


// First part of user declarations.

#line 37 "GrammarParser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "GrammarParser.tab.h"

// User implementation prologue.

#line 51 "GrammarParser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 87 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    #include "SourceLocation.h"
    #include "Lexer.h"
    #include "Exception.h"
    #include "Logger.h"

    #include <libstdhl/Type>

    #undef yylex
    #define yylex lexer.nextToken

    static BasicType::Ptr createVoidType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::VoidType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::Memory::get< libcasm_ir::RuleReferenceType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( SourceLocation& sourceLocation )
    {
        const auto name = Ast::make< Identifier >( sourceLocation, "Agent" );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( SourceLocation& sourceLocation )
    {
        const auto agentType = createAgentType( sourceLocation );
        const auto ruleRefType = createRuleRefType( sourceLocation );

        const auto argTypes = Ast::make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = Ast::make< Identifier >( sourceLocation, "program" );
        return Ast::make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
    }

    static IdentifierPath::Ptr asIdentifierPath( const Identifier::Ptr& identifier )
    {
        const auto& location = identifier->sourceLocation();
        return Ast::make< IdentifierPath >( location, identifier );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( rule == nullptr )
        {
            // this can happen while recovering from a syntax error
            return nullptr;
        }

        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& sourceLocation = rule->sourceLocation();
        const auto rules = Ast::make< Rules >( sourceLocation );
        rules->add( rule );
        return Ast::make< BlockRule >( sourceLocation, rules );
    }

#line 131 "GrammarParser.cpp" // lalr1.cc:413


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
    while (/*CONSTCOND*/ false)
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
      *yycdebug_ << std::endl;                  \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:479
namespace libcasm_fe {
#line 217 "GrammarParser.cpp" // lalr1.cc:479

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
        std::string yyr = "";
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
              // Fall through.
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
  Parser::Parser (Logger& log_yyarg, Lexer& lexer_yyarg, Specification& specification_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      log (log_yyarg),
      lexer (lexer_yyarg),
      specification (specification_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 160: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 159: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 161: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 137: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 107: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 110: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 101: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 100: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 102: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 121: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 105: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 138: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 120: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 99: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 87: // AttributedDefinition
      case 88: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 86: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 90: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 116: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 89: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 94: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 95: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 123: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 112: // Term
      case 113: // SimpleOrClaspedTerm
      case 114: // Expression
      case 126: // Literal
      case 147: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 162: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 111: // Terms
      case 141: // Arguments
      case 142: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 140: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 104: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 92: // FunctionDefinition
      case 93: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 85: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 152: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 153: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 154: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 118: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 106: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 119: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 103: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 124: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 117: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (that.value);
        break;

      case 148: // MaybeInitially
      case 149: // Initializers
      case 151: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 145: // Parameters
      case 146: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 125: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 134: // ReferenceLiteral
        value.move< ReferenceAtom::Ptr > (that.value);
        break;

      case 139: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 96: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 91: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 97: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 108: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 98: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 84: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 115: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 135: // Types
      case 143: // FunctionParameters
      case 144: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 127: // UndefinedLiteral
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 122: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 109: // UpdateRule
      case 150: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 128: // BooleanLiteral
      case 129: // IntegerLiteral
      case 130: // RationalLiteral
      case 131: // DecimalLiteral
      case 132: // BinaryLiteral
      case 133: // StringLiteral
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 155: // Variable
      case 156: // TypedVariable
      case 157: // AttributedVariable
      case 158: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 136: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 72: // "binary"
      case 73: // "hexadecimal"
      case 74: // "integer"
      case 75: // "rational"
      case 76: // "decimal"
      case 77: // "string"
      case 78: // "identifier"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 160: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 159: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 161: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 137: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 107: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 110: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 101: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 100: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 102: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 121: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 105: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 138: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 120: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 99: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 87: // AttributedDefinition
      case 88: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 86: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 90: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 116: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 89: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 94: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 95: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 123: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 112: // Term
      case 113: // SimpleOrClaspedTerm
      case 114: // Expression
      case 126: // Literal
      case 147: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 162: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 111: // Terms
      case 141: // Arguments
      case 142: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 140: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 104: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 92: // FunctionDefinition
      case 93: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 85: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 152: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 153: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 154: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 118: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 106: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 119: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 103: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 124: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 117: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (that.value);
        break;

      case 148: // MaybeInitially
      case 149: // Initializers
      case 151: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 145: // Parameters
      case 146: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 125: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 134: // ReferenceLiteral
        value.copy< ReferenceAtom::Ptr > (that.value);
        break;

      case 139: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 96: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 91: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 97: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 108: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 98: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 84: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 115: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 135: // Types
      case 143: // FunctionParameters
      case 144: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 127: // UndefinedLiteral
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 122: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 109: // UpdateRule
      case 150: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 128: // BooleanLiteral
      case 129: // IntegerLiteral
      case 130: // RationalLiteral
      case 131: // DecimalLiteral
      case 132: // BinaryLiteral
      case 133: // StringLiteral
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 155: // Variable
      case 156: // TypedVariable
      case 157: // AttributedVariable
      case 158: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 136: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 72: // "binary"
      case 73: // "hexadecimal"
      case 74: // "integer"
      case 75: // "rational"
      case 76: // "decimal"
      case 77: // "string"
      case 78: // "identifier"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
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
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
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

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
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
    yypush_ ("Shifting", yyn, yyla);
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
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 160: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 159: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 161: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 137: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 107: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 110: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 101: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 100: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 102: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 121: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 105: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 138: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 120: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 99: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 87: // AttributedDefinition
      case 88: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 86: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 90: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 116: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 89: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 94: // EnumeratorDefinition
        yylhs.value.build< EnumeratorDefinition::Ptr > ();
        break;

      case 95: // Enumerators
        yylhs.value.build< Enumerators::Ptr > ();
        break;

      case 123: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 112: // Term
      case 113: // SimpleOrClaspedTerm
      case 114: // Expression
      case 126: // Literal
      case 147: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 162: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 111: // Terms
      case 141: // Arguments
      case 142: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 140: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 104: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 92: // FunctionDefinition
      case 93: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 85: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 152: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 153: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 154: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 118: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 106: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 119: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 103: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 124: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 117: // MethodCallExpression
        yylhs.value.build< MethodCallExpression::Ptr > ();
        break;

      case 148: // MaybeInitially
      case 149: // Initializers
      case 151: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 145: // Parameters
      case 146: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 125: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 134: // ReferenceLiteral
        yylhs.value.build< ReferenceAtom::Ptr > ();
        break;

      case 139: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 96: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 91: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 97: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 108: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 98: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 84: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 115: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 135: // Types
      case 143: // FunctionParameters
      case 144: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 127: // UndefinedLiteral
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 122: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 109: // UpdateRule
      case 150: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 128: // BooleanLiteral
      case 129: // IntegerLiteral
      case 130: // RationalLiteral
      case 131: // DecimalLiteral
      case 132: // BinaryLiteral
      case 133: // StringLiteral
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 155: // Variable
      case 156: // TypedVariable
      case 157: // AttributedVariable
      case 158: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 136: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 72: // "binary"
      case 73: // "hexadecimal"
      case 74: // "integer"
      case 75: // "rational"
      case 76: // "decimal"
      case 77: // "string"
      case 78: // "identifier"
        yylhs.value.build< std::string > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1377 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1387 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1395 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 405 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 411 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 421 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 439 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 451 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 459 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 467 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 475 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1498 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< Identifier::Ptr > ();

      auto function = Ast::make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > () );
      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
           initializer->function()->setIdentifier( asIdentifierPath( identifier ) );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1527 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 505 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1535 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto singleAgentIdentifier = Ast::make< Identifier >( yylhs.location, "$" );
      auto singleAgentArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( singleAgentIdentifier ), singleAgentArguments );
      singleAgent->setTargetType( CallExpression::TargetType::CONSTANT );

      auto programDefinition = createProgramFunction( yylhs.location );
      auto programArguments = libcasm_fe::Ast::make< Expressions >( yylhs.location );
      programArguments->add( singleAgent );
      const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( programDefinition->identifier() ), programArguments );
      program->setTargetType( CallExpression::TargetType::FUNCTION );

      const auto ruleReference = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );

      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 536 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier(
                asIdentifierPath( programDefinition->identifier() ) );
      }
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 554 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1598 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 564 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1606 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 572 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1616 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1626 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1634 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 596 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 600 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1650 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 604 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1658 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1666 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1674 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1682 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1690 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1698 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 628 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1706 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 632 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1714 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 640 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1724 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1734 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 656 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1742 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1750 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 668 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1758 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 676 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1766 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 680 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 688 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1790 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 696 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1798 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1808 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1818 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1826 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1834 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1842 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1850 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1874 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1883 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 769 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 782 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1908 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 786 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 791 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1926 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 800 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1936 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 810 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1944 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 814 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1952 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 818 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< MethodCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1960 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 822 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< MethodCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1968 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 826 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 830 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 842 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1994 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 848 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2004 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 858 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
     yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2012 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 862 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 866 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 870 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2036 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 874 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2044 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 878 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2052 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 882 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2060 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 886 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2068 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 894 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2076 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2084 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2092 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< MethodCallExpression::Ptr > ();
  }
#line 2100 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 910 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2108 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 914 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2116 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2124 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 922 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2132 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 934 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2140 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2148 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 942 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2156 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 946 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2164 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2172 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2180 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2188 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2196 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2204 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2212 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2220 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2228 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2236 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2244 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2252 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2260 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2284 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2292 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2300 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2309 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1031 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2317 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1039 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Identifier::Ptr > (), arguments );
  }
#line 2326 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1044 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< MethodCallExpression::Ptr > () = Ast::make< MethodCallExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2334 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1052 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2342 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1060 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2350 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1068 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2358 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1076 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2366 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1084 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1092 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1100 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1105 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1109 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1117 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1129 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 2423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2431 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1137 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2439 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1141 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2447 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1145 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2455 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1149 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1153 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2471 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1157 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 2479 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1165 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1173 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2496 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1178 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1203 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1219 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::DecimalConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1235 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1247 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BinaryConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1263 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1279 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1291 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1297 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2629 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1307 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2637 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1311 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2645 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1315 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2653 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1319 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2661 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1327 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2669 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1335 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2677 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1343 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2685 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1351 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2693 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1363 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2701 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1367 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2709 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2718 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1380 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1394 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2738 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1400 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1414 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1428 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2784 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 2792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 2800 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 2808 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2816 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1462 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2824 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1470 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2832 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1474 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2840 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1482 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2850 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1488 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2860 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1498 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2872 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1506 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1516 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1527 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1543 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1547 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 2929 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1555 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 2937 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1559 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 2947 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1569 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1575 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2967 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2975 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1593 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 2984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1610 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3002 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3010 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 3020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1630 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 3028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1642 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3038 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1648 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3048 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 190:
#line 1657 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 3056 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 191:
#line 1661 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3064 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 192:
#line 1669 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3072 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 193:
#line 1677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3080 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3084 "GrammarParser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
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
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

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
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
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
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
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


  const short int Parser::yypact_ninf_ = -227;

  const short int Parser::yytable_ninf_ = -157;

  const short int
  Parser::yypact_[] =
  {
      -1,  -227,    -3,    16,   160,  -227,  -227,  1473,   -26,  -227,
    -227,  -227,  -227,  -227,    -5,    -3,    -3,    -3,    -3,    -3,
     151,  -227,  -227,  -227,  -227,  -227,  -227,  -227,     6,     6,
       6,  1473,     6,  -227,  -227,  -227,  1473,  1473,  1473,   881,
     944,    -3,    -4,  -227,  -227,  -227,  -227,  -227,  -227,  2293,
     -46,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,     5,   -13,    37,    -3,  1536,  -227,    13,
      17,    13,    21,     8,  -227,    -3,    22,  -227,  -227,    38,
      66,    68,  1804,    77,  -227,  -227,  -227,    50,  1473,  2021,
      49,  -227,    39,  2055,  -227,  -227,    -4,  1473,  1473,  1473,
    1473,  1473,  1473,  1473,  1473,  1473,  1473,  1473,  1473,  1473,
    1473,  1473,  1473,  1473,    -3,  1007,  -227,    -3,  -227,  -227,
     881,  2089,    35,    63,  -227,    76,    10,    62,    82,   -38,
      -4,   214,    73,    -4,  1473,  1473,  1473,  1473,  1473,  -227,
    2123,  -227,  -227,  -227,  1473,  1473,  -227,  -227,  -227,  -227,
    -227,    -2,   550,  2327,  2356,   465,   207,   207,   618,   192,
     192,    71,    71,    71,  -227,   465,   618,   192,   192,     5,
      89,  -227,   -10,  2293,  -227,    90,  2021,  1473,  1473,  1536,
    -227,   105,    -3,    -6,    22,  -227,  -227,    -4,    41,  1347,
      -4,  -227,    96,    98,  -227,    -3,  -227,  1562,  1948,  1686,
    1880,  1987,     5,  2293,  2157,    -4,  1473,  -227,  -227,  -227,
    1473,  2293,  2293,  -227,  -227,    74,  -227,    44,   111,  -227,
      -3,  -227,   -34,  -227,   551,   619,  -227,     6,     6,     6,
    1347,   152,  1473,  1473,   687,   755,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,   -46,   -12,
      97,   100,   127,    -4,    -4,  -227,  1473,  1473,  1473,  1473,
    1473,  -227,  -227,    14,    72,   107,  -227,  2191,    -3,  -227,
    1473,    95,  -227,    41,   161,  -227,  1075,   163,  1143,   131,
     162,   165,  -227,   115,    97,   100,  1842,  1914,   134,  1211,
     117,  1279,  1473,  1347,  -227,   180,  2293,  2293,  2293,  2293,
    2293,    -4,  -227,    -4,  -227,  -227,  2293,    -3,  -227,  -227,
    -227,  -227,  -227,  -227,  1473,  1473,  1473,  1347,   143,  -227,
    -227,  -227,  -227,  2293,  -227,   146,   190,  -227,   144,  -227,
    1606,  1646,  1726,   176,   818,  1473,   156,  -227,  -227,  1347,
    1347,  1473,  1347,  1347,   159,   173,   181,  -227,  1410,  2225,
    2259,  1536,  -227,  -227,  1766,  -227,  -227,  -227,  1347,  1347,
    -227,  -227,  1347,  -227,   183,  1347,  -227,  -227,  -227,  -227,
    -227
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,   176,   175,   192,     0,   189,
     190,   191,     1,     9,     0,     0,     0,     0,     0,     0,
       0,     6,     8,    10,    11,    12,    13,    19,     0,     0,
       0,     0,     0,   131,   133,   132,     0,     0,     0,     0,
       0,     0,     0,   137,   138,   134,   135,   136,   139,   193,
      72,    73,    79,    82,    83,    84,    74,    75,    76,    77,
      78,    85,    86,    87,   123,   124,   125,   126,   127,   128,
     129,   130,   180,   109,   177,     0,     0,   174,    20,   163,
       0,   163,     0,     0,     5,     0,   182,   185,   181,     0,
       0,     0,     0,     0,   107,    88,    89,     0,     0,     0,
       0,   119,     0,    71,   178,   140,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,     0,     3,   188,
       0,   170,     0,   173,   169,     0,     0,     0,     0,     0,
     158,     0,     0,     0,     0,     0,     0,     0,     0,    81,
       0,    80,   121,   120,     0,     0,   108,   143,   144,   145,
     146,   147,   104,   102,   103,   106,    90,    91,    97,    98,
      99,    92,    93,    94,    95,   105,    96,   100,   101,   111,
       0,   153,     0,    71,   179,     0,    71,     0,     0,     0,
      21,     0,     0,     0,     0,   187,   160,     0,     0,     0,
       0,   156,   157,     0,     7,     0,   183,     0,     0,     0,
       0,     0,     0,    70,     0,   158,     0,   112,   152,   151,
       0,   171,   172,   168,   162,     0,   161,     0,     0,    24,
       0,    26,     0,    22,     0,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,     0,    65,
      67,    69,     0,     0,     0,   184,     0,     0,     0,     0,
       0,   113,   122,     0,   142,     0,   150,    70,     0,   159,
       0,     0,    14,     0,     0,    39,     0,     0,     0,     0,
       0,     0,    54,    64,    66,    68,     0,     0,     0,     0,
       0,     0,     0,     0,   155,   165,   114,   117,   116,   115,
     118,     0,   148,     0,   154,   186,    15,     0,    25,    62,
      60,    38,    58,    56,     0,     0,     0,     0,     0,    57,
      55,    61,    59,    63,    17,     0,   167,   141,     0,    23,
       0,     0,     0,    41,     0,     0,     0,    18,   149,     0,
       0,     0,     0,     0,     0,     0,     0,    49,     0,     0,
       0,   174,    50,    51,     0,    53,    42,    44,     0,     0,
      43,    48,     0,   164,     0,     0,    45,    46,    47,   166,
      52
  };

  const short int
  Parser::yypgoto_[] =
  {
    -227,  -227,  -227,  -227,   191,    69,  -227,  -227,  -227,  -227,
    -227,   -71,  -227,   186,  -226,  -227,  -227,  -227,  -119,  -227,
    -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,   -89,    -7,
       3,  -227,  -227,    80,   101,   178,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,  -227,
    -227,  -227,  -227,  -118,  -227,  -227,  -227,  -227,  -175,  -227,
    -227,    26,  -227,   164,  -227,  -227,  -227,    53,  -107,    48,
      -8,  -227,    52,  -135,   -22,    31,   -16,   193,  -227,  -227
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    20,    21,    22,    23,    24,    25,    26,
      27,   231,   232,   285,   286,   247,   248,   249,   357,   358,
     250,   251,   252,   253,   254,   255,   256,   257,   102,   131,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,   273,   156,   157,   158,   159,   160,   126,   132,
     202,   203,   193,   137,   336,   347,   133,   134,   135,    72,
      73,    74,    87,    88,    89,   196,     8,     9,    10,    11
  };

  const short int
  Parser::yytable_[] =
  {
      49,   195,     1,    83,   217,   199,    78,    90,    91,   288,
      93,   191,     5,     5,     5,   282,    12,   124,   299,   301,
     283,    75,   201,     5,    92,   206,   200,     5,    76,    94,
      95,    96,    99,   103,   105,   219,   182,   271,   127,   226,
     128,   185,   229,    77,   154,     2,    41,    41,   227,   125,
       7,   -82,    85,   215,   302,   141,   192,   136,     5,   216,
     138,     5,    76,    79,    80,    81,    82,     7,   311,   142,
     312,   140,   143,     6,     6,     6,    86,    86,    86,   228,
      86,   144,   262,   145,     6,   146,   153,   230,     6,   104,
     192,   150,   195,   154,   148,   149,   152,   274,   161,   188,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   189,   183,     6,
     205,   278,     6,   186,     7,   190,   197,    76,    76,  -156,
     198,   119,   161,     7,   218,   161,  -156,   207,   208,   209,
     210,   211,   317,   315,   220,   304,   305,   213,   214,    76,
     224,    -2,    13,   263,   280,    14,    15,    16,    17,    18,
     -83,    13,   264,   -84,    14,    15,    16,    17,    18,     5,
     303,   313,   179,   319,   324,   184,   225,   322,   -82,   325,
     221,   222,   326,   329,   194,    33,    34,    35,   331,   161,
     335,   344,   161,   337,   345,   338,    39,    19,    40,   346,
     348,   353,   258,    41,   361,    42,    19,   161,   367,   276,
     204,    84,   318,   277,   281,   289,   290,   291,    14,    15,
      16,    17,    18,   368,    43,    44,    45,    46,    47,    48,
       6,   369,   379,   111,   112,   296,   297,   258,   258,   371,
       7,   275,   223,   258,   258,   139,   233,   258,   258,   116,
     117,   118,   119,    86,   374,   161,   161,   265,   279,   306,
     307,   308,   309,   310,   116,   117,   118,   119,     0,   129,
       0,     0,     0,   316,     0,   194,     0,     0,     7,   259,
       0,     0,     0,     0,     0,    86,    86,    86,     0,   258,
       0,   258,     0,     0,     0,   333,     0,     0,     0,     0,
     260,     0,   258,   161,   258,   161,   258,     0,     0,     0,
       0,     0,     0,     0,   259,   259,     0,   340,   341,   342,
     259,   293,     0,     0,   259,   259,   194,     0,     0,     0,
     258,   233,     0,     0,     0,   260,   260,   359,   360,     0,
       0,   260,   294,     0,   364,   260,   260,     0,     0,     0,
       0,   359,   258,   258,     0,   258,   258,     0,     0,     0,
       0,     0,     0,     0,     0,   339,   259,     0,   259,     0,
       0,   258,   258,     0,     0,   258,     0,   261,   258,   259,
       0,   259,     0,   259,     0,   246,     0,   260,     0,   260,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     260,     0,   260,     0,   260,     0,     0,   259,     0,     0,
       0,     0,   261,   261,     0,     0,     0,     0,   261,   295,
       0,     0,   261,   261,     0,     0,   292,     0,   260,   259,
     259,     0,   259,   259,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   259,   259,
     260,   260,   259,   260,   260,   259,     0,     0,     0,     0,
       0,     0,     0,     0,   261,     0,   261,     0,     0,   260,
     260,     0,   321,   260,   321,     0,   260,   261,     0,   261,
       0,   261,     0,     0,     0,   321,     0,   321,     0,   334,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   107,   108,   109,     0,   261,   111,   112,   113,     0,
       0,     0,     0,   343,     0,     0,     0,     0,     0,     0,
     114,   115,   116,   117,   118,   119,     0,   261,   261,     0,
     261,   261,   121,   122,   123,   362,   363,     0,   365,   366,
       0,     0,     0,     0,     0,     0,   261,   261,     0,     0,
     261,     0,   284,   261,   376,   377,     0,     0,   378,     0,
       0,   380,   234,     0,   235,     0,   236,   237,     5,   238,
     239,   240,     0,   241,   242,     0,     0,   243,     0,     0,
       0,     0,     0,     0,    33,    34,    35,     0,     0,     0,
       0,   111,   112,   113,     0,    39,     0,    40,     0,   244,
       0,     0,    41,     0,    42,   114,   115,   116,   117,   118,
     119,     0,     0,     0,     0,     0,     0,   121,   122,   123,
     287,   245,     0,    43,    44,    45,    46,    47,    48,     6,
     234,     0,   235,     0,   236,   237,     5,   238,   239,   240,
       0,   241,   242,     0,     0,   243,     0,     0,     0,     0,
       0,     0,    33,    34,    35,     0,     0,     0,     0,   111,
     112,     0,     0,    39,     0,    40,     0,   244,     0,     0,
      41,     0,    42,   114,   115,   116,   117,   118,   119,     0,
       0,     0,     0,     0,     0,     0,   122,   123,   298,   245,
       0,    43,    44,    45,    46,    47,    48,     6,   234,     0,
     235,     0,   236,   237,     5,   238,   239,   240,     0,   241,
     242,     0,     0,   243,     0,     0,     0,     0,     0,     0,
      33,    34,    35,     0,     0,     0,     0,     0,     0,     0,
       0,    39,     0,    40,     0,   244,     0,     0,    41,     0,
      42,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   300,   245,     0,    43,
      44,    45,    46,    47,    48,     6,   234,     0,   235,     0,
     236,   237,     5,   238,   239,   240,     0,   241,   242,     0,
       0,   243,     0,     0,     0,     0,     0,     0,    33,    34,
      35,     0,     0,     0,     0,     0,     0,     0,     0,    39,
       0,    40,     0,   244,     0,     0,    41,     0,    42,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   354,
       0,     0,     0,     0,     0,   245,     0,    43,    44,    45,
      46,    47,    48,     6,    28,     5,    29,    30,     0,     0,
       0,    31,     0,     0,     0,     0,   355,     0,    32,     0,
       0,    33,    34,    35,     0,     0,     0,     0,    36,    37,
      38,     0,    39,     0,    40,     0,     0,     0,     0,    41,
     356,    42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    97,     0,     0,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48,     6,    28,     5,    29,
      30,     0,     0,     0,    31,     0,     0,     0,     0,     0,
       0,    32,     0,     0,    33,    34,    35,     0,     0,     0,
       0,    36,    37,    38,     0,    39,     0,    40,     0,     0,
       0,     0,    41,     0,    42,     0,     0,     0,    98,     0,
       0,     0,     0,     0,     0,   100,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,     6,
      28,     5,    29,    30,     0,     0,     0,    31,     0,     0,
       0,     0,     0,     0,    32,     0,     0,    33,    34,    35,
       0,     0,     0,     0,    36,    37,    38,     0,    39,     0,
      40,   101,     0,     0,     0,    41,     0,    42,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   180,     0,
       0,     0,     0,     0,     0,     0,    43,    44,    45,    46,
      47,    48,     6,    28,     5,    29,    30,     0,     0,     0,
      31,     0,     0,     0,     0,     0,     0,    32,     0,     0,
      33,    34,    35,     0,     0,     0,     0,    36,    37,    38,
       0,    39,   181,    40,     0,     0,     0,     0,    41,     0,
      42,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    43,
      44,    45,    46,    47,    48,     6,   234,   320,   235,     0,
     236,   237,     5,   238,   239,   240,     0,   241,   242,     0,
       0,   243,     0,     0,     0,     0,     0,     0,    33,    34,
      35,     0,     0,     0,     0,     0,     0,     0,     0,    39,
       0,    40,     0,   244,     0,     0,    41,     0,    42,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   245,     0,    43,    44,    45,
      46,    47,    48,     6,   234,     0,   235,   323,   236,   237,
       5,   238,   239,   240,     0,   241,   242,     0,     0,   243,
       0,     0,     0,     0,     0,     0,    33,    34,    35,     0,
       0,     0,     0,     0,     0,     0,     0,    39,     0,    40,
       0,   244,     0,     0,    41,     0,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   245,     0,    43,    44,    45,    46,    47,
      48,     6,   234,     0,   235,     0,   236,   237,     5,   238,
     239,   240,     0,   241,   242,     0,     0,   243,     0,     0,
       0,     0,     0,     0,    33,    34,    35,     0,     0,     0,
       0,     0,     0,     0,     0,    39,     0,    40,     0,   244,
     330,     0,    41,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   245,     0,    43,    44,    45,    46,    47,    48,     6,
     234,     0,   235,     0,   236,   237,     5,   238,   239,   240,
       0,   241,   242,     0,     0,   243,     0,     0,     0,     0,
       0,     0,    33,    34,    35,     0,     0,     0,     0,     0,
       0,     0,     0,    39,     0,    40,     0,   244,     0,     0,
      41,     0,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   245,
     332,    43,    44,    45,    46,    47,    48,     6,   234,     0,
     235,     0,   236,   237,     5,   238,   239,   240,     0,   241,
     242,     0,     0,   243,     0,     0,     0,     0,     0,     0,
      33,    34,    35,     0,     0,     0,     0,     0,     0,     0,
       0,    39,     0,    40,     0,   244,     0,     0,    41,     0,
      42,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   245,     0,    43,
      44,    45,    46,    47,    48,     6,    28,     5,    29,    30,
       0,     0,     0,    31,     0,     0,     0,     0,   355,     0,
      32,     0,     0,    33,    34,    35,     0,     0,     0,     0,
      36,    37,    38,     0,    39,     0,    40,     0,     0,   370,
       0,    41,   356,    42,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    43,    44,    45,    46,    47,    48,     6,    28,
       5,    29,    30,     0,     0,     0,    31,     0,     0,     0,
       0,     0,     0,    32,     0,     0,    33,    34,    35,     0,
       0,     0,     0,    36,    37,    38,     0,    39,     0,    40,
       0,     0,     0,     0,    41,     0,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,     6,    28,     5,    29,    30,     0,     0,     0,    31,
       0,     0,     0,     0,     0,     0,    32,     0,     0,    33,
      34,    35,     0,     0,     0,     0,    36,    37,    38,   266,
     130,     0,    40,     0,     0,     0,     0,    41,     0,    42,
       0,     0,     0,     0,   106,     0,     0,     0,   107,   108,
     109,   110,     0,   111,   112,   113,     0,     0,    43,    44,
      45,    46,    47,    48,     6,     0,     0,   114,   115,   116,
     117,   118,   119,   349,     0,     0,     0,   120,     0,   121,
     122,   123,     0,     0,     0,     0,     0,     0,   106,     0,
       0,     0,   107,   108,   109,   110,     0,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   350,     0,     0,
       0,   120,     0,   121,   122,   123,     0,   351,   106,     0,
       0,     0,   107,   108,   109,   110,     0,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   268,     0,     0,
       0,   120,     0,   121,   122,   123,     0,     0,   106,     0,
       0,     0,   107,   108,   109,   110,     0,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   352,     0,     0,
       0,   120,     0,   121,   122,   123,     0,     0,   106,     0,
       0,     0,   107,   108,   109,   110,     0,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,   375,     0,     0,
       0,   120,     0,   121,   122,   123,     0,     0,   106,     0,
       0,     0,   107,   108,   109,   110,     0,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,     0,   147,     0,
       0,   120,     0,   121,   122,   123,   106,     0,     0,     0,
     107,   108,   109,   110,     0,   111,   112,   113,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   114,
     115,   116,   117,   118,   119,     0,   327,     0,     0,   120,
       0,   121,   122,   123,   106,     0,     0,     0,   107,   108,
     109,   110,     0,   111,   112,   113,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   114,   115,   116,
     117,   118,   119,     0,     0,   269,     0,   120,     0,   121,
     122,   123,   106,     0,     0,     0,   107,   108,   109,   110,
       0,   111,   112,   113,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   114,   115,   116,   117,   118,
     119,   328,     0,     0,     0,   120,   106,   121,   122,   123,
     107,   108,   109,   110,     0,   111,   112,   113,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   114,
     115,   116,   117,   118,   119,     0,     0,   267,     0,   120,
     106,   121,   122,   123,   107,   108,   109,   110,     0,   111,
     112,   113,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   114,   115,   116,   117,   118,   119,     0,
       0,     0,     0,   120,     0,   121,   122,   123,   270,   106,
       0,     0,     0,   107,   108,   109,   110,     0,   111,   112,
     113,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,   115,   116,   117,   118,   119,     0,     0,
       0,     0,   120,   106,   121,   122,   123,   107,   108,   109,
     110,     0,   111,   112,   113,     0,   151,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,   115,   116,   117,
     118,   119,     0,     0,     0,     0,   120,   106,   121,   122,
     123,   107,   108,   109,   110,     0,   111,   112,   113,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     114,   115,   116,   117,   118,   119,     0,   155,     0,     0,
     120,   106,   121,   122,   123,   107,   108,   109,   110,     0,
     111,   112,   113,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   114,   115,   116,   117,   118,   119,
       0,     0,     0,   187,   120,   106,   121,   122,   123,   107,
     108,   109,   110,     0,   111,   112,   113,     0,   212,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   114,   115,
     116,   117,   118,   119,     0,     0,     0,     0,   120,   106,
     121,   122,   123,   107,   108,   109,   110,     0,   111,   112,
     113,     0,     0,     0,   272,     0,     0,     0,     0,     0,
       0,     0,   114,   115,   116,   117,   118,   119,     0,     0,
       0,     0,   120,   106,   121,   122,   123,   107,   108,   109,
     110,     0,   111,   112,   113,     0,   314,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   114,   115,   116,   117,
     118,   119,     0,     0,     0,     0,   120,   106,   121,   122,
     123,   107,   108,   109,   110,     0,   111,   112,   113,     0,
       0,     0,     0,     0,     0,   372,     0,     0,     0,     0,
     114,   115,   116,   117,   118,   119,     0,     0,     0,     0,
     120,   106,   121,   122,   123,   107,   108,   109,   110,     0,
     111,   112,   113,     0,     0,     0,     0,     0,   373,     0,
       0,     0,     0,     0,   114,   115,   116,   117,   118,   119,
       0,     0,     0,     0,   120,   106,   121,   122,   123,   107,
     108,   109,   110,     0,   111,   112,   113,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   114,   115,
     116,   117,   118,   119,     0,     0,     0,     0,   120,     0,
     121,   122,   123,   107,     0,   109,     0,     0,   111,   112,
     113,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   114,   115,   116,   117,   118,   119,     0,     0,
       0,     0,   107,     0,   121,   122,   123,   111,   112,   113,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   114,   115,   116,   117,   118,   119,     0,     0,     0,
       0,     0,     0,   121,   122,   123
  };

  const short int
  Parser::yycheck_[] =
  {
       7,   136,     3,    19,   179,    43,    14,    29,    30,   235,
      32,     1,    17,    17,    17,    49,     0,    63,   244,   245,
      54,    47,   140,    17,    31,   143,    64,    17,    54,    36,
      37,    38,    39,    40,    42,    45,   125,   212,    51,    45,
       3,   130,     1,    48,    54,    46,    51,    51,    54,    44,
       2,    63,    46,    55,    66,    47,    46,    44,    17,    61,
      43,    17,    54,    15,    16,    17,    18,    19,    54,    85,
      56,    50,    50,    78,    78,    78,    28,    29,    30,   197,
      32,    43,   200,    17,    78,    17,    47,    46,    78,    41,
      46,    98,   227,    54,    17,    45,    47,   215,   106,    64,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,    54,   125,    78,
      47,    47,    78,   130,    76,    49,    64,    54,    54,    57,
      48,    60,   140,    85,    45,   143,    64,   144,   145,   146,
     147,   148,    47,   278,    54,   263,   264,   154,   155,    54,
      45,     0,     1,    57,    43,     4,     5,     6,     7,     8,
      63,     1,    64,    63,     4,     5,     6,     7,     8,    17,
      43,    64,   124,    12,    43,   127,   192,    14,    63,    17,
     187,   188,    17,    49,   136,    33,    34,    35,    71,   197,
      10,    48,   200,   311,    48,   313,    44,    46,    46,     9,
      56,    25,   199,    51,    48,    53,    46,   215,    49,   216,
     141,    20,   283,   220,   230,   237,   238,   239,     4,     5,
       6,     7,     8,    50,    72,    73,    74,    75,    76,    77,
      78,    50,    49,    41,    42,   242,   243,   234,   235,   358,
     192,   215,   189,   240,   241,    81,   198,   244,   245,    57,
      58,    59,    60,   205,   361,   263,   264,   205,   227,   266,
     267,   268,   269,   270,    57,    58,    59,    60,    -1,    76,
      -1,    -1,    -1,   280,    -1,   227,    -1,    -1,   230,   199,
      -1,    -1,    -1,    -1,    -1,   237,   238,   239,    -1,   286,
      -1,   288,    -1,    -1,    -1,   302,    -1,    -1,    -1,    -1,
     199,    -1,   299,   311,   301,   313,   303,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   234,   235,    -1,   324,   325,   326,
     240,   241,    -1,    -1,   244,   245,   278,    -1,    -1,    -1,
     327,   283,    -1,    -1,    -1,   234,   235,   344,   345,    -1,
      -1,   240,   241,    -1,   351,   244,   245,    -1,    -1,    -1,
      -1,   358,   349,   350,    -1,   352,   353,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   317,   286,    -1,   288,    -1,
      -1,   368,   369,    -1,    -1,   372,    -1,   199,   375,   299,
      -1,   301,    -1,   303,    -1,   199,    -1,   286,    -1,   288,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     299,    -1,   301,    -1,   303,    -1,    -1,   327,    -1,    -1,
      -1,    -1,   234,   235,    -1,    -1,    -1,    -1,   240,   241,
      -1,    -1,   244,   245,    -1,    -1,   240,    -1,   327,   349,
     350,    -1,   352,   353,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   368,   369,
     349,   350,   372,   352,   353,   375,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   286,    -1,   288,    -1,    -1,   368,
     369,    -1,   286,   372,   288,    -1,   375,   299,    -1,   301,
      -1,   303,    -1,    -1,    -1,   299,    -1,   301,    -1,   303,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    -1,   327,    41,    42,    43,    -1,
      -1,    -1,    -1,   327,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,   349,   350,    -1,
     352,   353,    67,    68,    69,   349,   350,    -1,   352,   353,
      -1,    -1,    -1,    -1,    -1,    -1,   368,   369,    -1,    -1,
     372,    -1,     1,   375,   368,   369,    -1,    -1,   372,    -1,
      -1,   375,    11,    -1,    13,    -1,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    41,    42,    43,    -1,    44,    -1,    46,    -1,    48,
      -1,    -1,    51,    -1,    53,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
       1,    70,    -1,    72,    73,    74,    75,    76,    77,    78,
      11,    -1,    13,    -1,    15,    16,    17,    18,    19,    20,
      -1,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    41,
      42,    -1,    -1,    44,    -1,    46,    -1,    48,    -1,    -1,
      51,    -1,    53,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,     1,    70,
      -1,    72,    73,    74,    75,    76,    77,    78,    11,    -1,
      13,    -1,    15,    16,    17,    18,    19,    20,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    46,    -1,    48,    -1,    -1,    51,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    70,    -1,    72,
      73,    74,    75,    76,    77,    78,    11,    -1,    13,    -1,
      15,    16,    17,    18,    19,    20,    -1,    22,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    46,    -1,    48,    -1,    -1,    51,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,    74,
      75,    76,    77,    78,    16,    17,    18,    19,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    30,    -1,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    51,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    16,    17,    18,
      19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,
      -1,    -1,    51,    -1,    53,    -1,    -1,    -1,    57,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    72,    73,    74,    75,    76,    77,    78,
      16,    17,    18,    19,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    -1,    33,    34,    35,
      -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,    -1,
      46,    47,    -1,    -1,    -1,    51,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,
      76,    77,    78,    16,    17,    18,    19,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      -1,    44,    45,    46,    -1,    -1,    -1,    -1,    51,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,
      73,    74,    75,    76,    77,    78,    11,    12,    13,    -1,
      15,    16,    17,    18,    19,    20,    -1,    22,    23,    -1,
      -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    46,    -1,    48,    -1,    -1,    51,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    72,    73,    74,
      75,    76,    77,    78,    11,    -1,    13,    14,    15,    16,
      17,    18,    19,    20,    -1,    22,    23,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    33,    34,    35,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    46,
      -1,    48,    -1,    -1,    51,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    -1,    72,    73,    74,    75,    76,
      77,    78,    11,    -1,    13,    -1,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    -1,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    44,    -1,    46,    -1,    48,
      49,    -1,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    72,    73,    74,    75,    76,    77,    78,
      11,    -1,    13,    -1,    15,    16,    17,    18,    19,    20,
      -1,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    -1,    46,    -1,    48,    -1,    -1,
      51,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    77,    78,    11,    -1,
      13,    -1,    15,    16,    17,    18,    19,    20,    -1,    22,
      23,    -1,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    44,    -1,    46,    -1,    48,    -1,    -1,    51,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,    72,
      73,    74,    75,    76,    77,    78,    16,    17,    18,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    -1,
      30,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,    49,
      -1,    51,    52,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    16,
      17,    18,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    -1,    44,    -1,    46,
      -1,    -1,    -1,    -1,    51,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,
      77,    78,    16,    17,    18,    19,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    33,
      34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,    17,
      44,    -1,    46,    -1,    -1,    -1,    -1,    51,    -1,    53,
      -1,    -1,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    -1,    -1,    55,    56,    57,
      58,    59,    60,    17,    -1,    -1,    -1,    65,    -1,    67,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    21,    -1,    -1,
      -1,    65,    -1,    67,    68,    69,    -1,    31,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    21,    -1,    -1,
      -1,    65,    -1,    67,    68,    69,    -1,    -1,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    21,    -1,    -1,
      -1,    65,    -1,    67,    68,    69,    -1,    -1,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    21,    -1,    -1,
      -1,    65,    -1,    67,    68,    69,    -1,    -1,    32,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    -1,    24,    -1,
      -1,    65,    -1,    67,    68,    69,    32,    -1,    -1,    -1,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    24,    -1,    -1,    65,
      -1,    67,    68,    69,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    25,    -1,    65,    -1,    67,
      68,    69,    32,    -1,    -1,    -1,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    27,    -1,    -1,    -1,    65,    32,    67,    68,    69,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    29,    -1,    65,
      32,    67,    68,    69,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    65,    -1,    67,    68,    69,    31,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    65,    32,    67,    68,    69,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    65,    32,    67,    68,
      69,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,    62,    -1,    -1,
      65,    32,    67,    68,    69,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    64,    65,    32,    67,    68,    69,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    32,
      67,    68,    69,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    65,    32,    67,    68,    69,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    -1,    65,    32,    67,    68,
      69,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      65,    32,    67,    68,    69,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    65,    32,    67,    68,    69,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    -1,
      67,    68,    69,    36,    -1,    38,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    36,    -1,    67,    68,    69,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    67,    68,    69
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    46,    84,    85,    17,    78,   152,   159,   160,
     161,   162,     0,     1,     4,     5,     6,     7,     8,    46,
      86,    87,    88,    89,    90,    91,    92,    93,    16,    18,
      19,    23,    30,    33,    34,    35,    40,    41,    42,    44,
      46,    51,    53,    72,    73,    74,    75,    76,    77,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   152,   153,   154,    47,    54,    48,   153,   152,
     152,   152,   152,   159,    87,    46,   152,   155,   156,   157,
     157,   157,   112,   157,   112,   112,   112,     1,    57,   112,
       1,    47,   111,   112,   152,   153,    32,    36,    37,    38,
      39,    41,    42,    43,    55,    56,    57,    58,    59,    60,
      65,    67,    68,    69,    63,    44,   141,    51,     3,   160,
      44,   112,   142,   149,   150,   151,    44,   146,    43,   146,
      50,    47,   159,    50,    43,    17,    17,    24,    17,    45,
     112,    45,    47,    47,    54,    62,   136,   137,   138,   139,
     140,   153,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   152,
       1,    45,   111,   112,   152,   111,   112,    64,    64,    54,
      49,     1,    46,   145,   152,   156,   158,    64,    48,    43,
      64,   136,   143,   144,    88,    47,   136,   112,   112,   112,
     112,   112,    45,   112,   112,    55,    61,   141,    45,    45,
      54,   112,   112,   150,    45,   159,    45,    54,   136,     1,
      46,    94,    95,   152,    11,    13,    15,    16,    18,    19,
      20,    22,    23,    26,    48,    70,    96,    98,    99,   100,
     103,   104,   105,   106,   107,   108,   109,   110,   113,   116,
     117,   118,   136,    57,    64,   155,    17,    29,    21,    25,
      31,   141,    47,   135,   136,   144,   112,   112,    47,   158,
      43,   159,    49,    54,     1,    96,    97,     1,    97,   157,
     157,   157,    96,   116,   117,   118,   112,   112,     1,    97,
       1,    97,    66,    43,   136,   136,   112,   112,   112,   112,
     112,    54,    56,    64,    45,   156,   112,    47,    94,    12,
      12,    96,    14,    14,    43,    17,    17,    24,    27,    49,
      49,    71,    71,   112,    96,    10,   147,   136,   136,   152,
     112,   112,   112,    96,    48,    48,     9,   148,    56,    17,
      21,    31,    21,    25,     1,    28,    52,   101,   102,   112,
     112,    48,    96,    96,   112,    96,    96,    49,    50,    50,
      49,   101,    50,    49,   151,    21,    96,    96,    96,    49,
      96
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    83,    84,    85,    85,    86,    86,    87,    87,    87,
      88,    88,    88,    88,    89,    90,    91,    91,    92,    92,
      93,    93,    94,    94,    94,    95,    95,    96,    96,    96,
      96,    96,    96,    96,    96,    96,    96,    96,    97,    97,
      98,    99,    99,   100,   100,   101,   101,   101,   102,   102,
     103,   104,   104,   105,   106,   107,   107,   107,   107,   108,
     108,   108,   108,   109,   110,   110,   110,   110,   110,   110,
     111,   111,   112,   112,   112,   112,   112,   112,   112,   112,
     113,   113,   113,   113,   113,   113,   113,   113,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   115,   116,
     116,   117,   117,   118,   119,   120,   121,   122,   123,   124,
     124,   124,   125,   126,   126,   126,   126,   126,   126,   126,
     126,   127,   128,   128,   129,   130,   131,   132,   132,   133,
     134,   135,   135,   136,   136,   136,   136,   137,   138,   139,
     140,   141,   141,   141,   142,   143,   143,   144,   144,   145,
     145,   146,   146,   146,   147,   147,   148,   148,   149,   149,
     150,   150,   150,   151,   151,   152,   152,   153,   153,   154,
     154,   155,   155,   156,   157,   157,   158,   158,   159,   159,
     160,   160,   161,   162
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     4,     1,     2,     1,     4,     1,     1,
       1,     1,     1,     1,     6,     7,     5,     7,     8,     1,
       2,     4,     1,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     4,     6,     6,     6,     3,     3,     3,     2,     1,
       6,     6,     8,     6,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     2,     1,     2,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     3,     1,     1,     1,     1,     1,     1,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     3,     1,
       2,     3,     4,     5,     6,     6,     6,     6,     6,     2,
       3,     3,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     3,     1,     1,     1,     1,     1,     1,     4,     6,
       3,     3,     3,     2,     5,     3,     1,     1,     0,     3,
       1,     3,     3,     0,     4,     0,     4,     0,     3,     1,
       1,     3,     3,     1,     0,     1,     1,     1,     2,     3,
       1,     1,     1,     3,     4,     1,     4,     1,     3,     1,
       1,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"function\"",
  "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"", "\"par\"",
  "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
  "\"choose\"", "\"iterate\"", "\"do\"", "\"call\"", "\"if\"", "\"then\"",
  "\"else\"", "\"case\"", "\"of\"", "\"default\"", "\"holds\"",
  "\"exists\"", "\"with\"", "\"as\"", "\"undef\"", "\"false\"", "\"true\"",
  "\"and\"", "\"or\"", "\"xor\"", "\"implies\"", "\"not\"", "\"+\"",
  "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"",
  "\":\"", "\"::\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"",
  "\"/\"", "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"",
  "\"=>\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"",
  "\"binary\"", "\"hexadecimal\"", "\"integer\"", "\"rational\"",
  "\"decimal\"", "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "UPLUS",
  "UMINUS", "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header",
  "Definitions", "AttributedDefinition", "Definition",
  "EnumerationDefinition", "DerivedDefinition", "RuleDefinition",
  "FunctionDefinition", "ProgramFunctionDefinition",
  "EnumeratorDefinition", "Enumerators", "Rule", "Rules", "SkipRule",
  "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels", "LetRule",
  "ForallRule", "ChooseRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", "Terms", "Term", "SimpleOrClaspedTerm",
  "Expression", "TypeCastingExpression", "DirectCallExpression",
  "MethodCallExpression", "IndirectCallExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "List", "Range", "Literal", "UndefinedLiteral", "BooleanLiteral",
  "IntegerLiteral", "RationalLiteral", "DecimalLiteral", "BinaryLiteral",
  "StringLiteral", "ReferenceLiteral", "Types", "Type", "BasicType",
  "ComposedType", "RelationType", "FixedSizedType", "Arguments",
  "TwoOrMoreArguments", "FunctionParameters", "MaybeFunctionParameters",
  "Parameters", "MaybeParameters", "MaybeDefined", "MaybeInitially",
  "Initializers", "Initializer", "MaybeInitializers", "Identifier",
  "IdentifierPath", "DotSeparatedIdentifiers", "Variable", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "Attributes",
  "Attribute", "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   381,   381,   390,   396,   404,   410,   420,   426,   430,
     438,   442,   446,   450,   458,   466,   474,   479,   488,   504,
     512,   535,   553,   557,   563,   571,   577,   591,   595,   599,
     603,   607,   611,   615,   619,   623,   627,   631,   639,   645,
     655,   663,   667,   675,   679,   687,   691,   695,   703,   709,
     719,   727,   731,   739,   747,   755,   759,   763,   768,   777,
     781,   785,   790,   799,   809,   813,   817,   821,   825,   829,
     841,   847,   857,   861,   865,   869,   873,   877,   881,   885,
     893,   897,   901,   905,   909,   913,   917,   921,   933,   937,
     941,   945,   949,   953,   957,   961,   965,   969,   973,   977,
     981,   985,   989,   993,   997,  1001,  1005,  1009,  1017,  1025,
    1030,  1038,  1043,  1051,  1059,  1067,  1075,  1083,  1091,  1099,
    1104,  1108,  1116,  1128,  1132,  1136,  1140,  1144,  1148,  1152,
    1156,  1164,  1172,  1177,  1186,  1202,  1218,  1234,  1246,  1262,
    1278,  1290,  1296,  1306,  1310,  1314,  1318,  1326,  1334,  1342,
    1350,  1362,  1366,  1370,  1379,  1393,  1399,  1409,  1413,  1421,
    1427,  1437,  1441,  1445,  1457,  1461,  1469,  1473,  1481,  1487,
    1497,  1505,  1515,  1526,  1530,  1542,  1546,  1554,  1558,  1568,
    1574,  1588,  1592,  1601,  1609,  1615,  1623,  1629,  1641,  1647,
    1656,  1660,  1668,  1676
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
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:1167
} // libcasm_fe
#line 4150 "GrammarParser.cpp" // lalr1.cc:1167
#line 1682 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void Parser::error( const SourceLocation& location, const std::string& message )
{
    log.error( {location}, message, Code::SyntaxError );
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
