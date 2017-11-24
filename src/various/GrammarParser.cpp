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
      case 159: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 158: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 160: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 136: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 108: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 111: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 102: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 101: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 103: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 120: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 106: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 137: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 119: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 100: // ConditionalRule
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

      case 122: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 113: // Term
      case 114: // Expression
      case 125: // Literal
      case 146: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 161: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 112: // Terms
      case 140: // Arguments
      case 141: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 139: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 105: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 92: // FunctionDefinition
      case 93: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 85: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 151: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 152: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 153: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 117: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 107: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 118: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 104: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 123: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 147: // MaybeInitially
      case 148: // Initializers
      case 150: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 144: // Parameters
      case 145: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 124: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 133: // ReferenceLiteral
        value.move< ReferenceAtom::Ptr > (that.value);
        break;

      case 138: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 97: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 91: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 98: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 109: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 99: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 84: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 115: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 96: // TypeDefinition
        value.move< TypeDefinition::Ptr > (that.value);
        break;

      case 134: // Types
      case 142: // FunctionParameters
      case 143: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 126: // UndefinedLiteral
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 121: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 110: // UpdateRule
      case 149: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 127: // BooleanLiteral
      case 128: // IntegerLiteral
      case 129: // RationalLiteral
      case 130: // DecimalLiteral
      case 131: // BitLiteral
      case 132: // StringLiteral
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 154: // Variable
      case 155: // TypedVariable
      case 156: // AttributedVariable
      case 157: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 135: // Type
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
      case 159: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 158: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 160: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 136: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 108: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 111: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 102: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 101: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 103: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 120: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 106: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 137: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 119: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 100: // ConditionalRule
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

      case 122: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 113: // Term
      case 114: // Expression
      case 125: // Literal
      case 146: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 161: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 112: // Terms
      case 140: // Arguments
      case 141: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 139: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 105: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 92: // FunctionDefinition
      case 93: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 85: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 151: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 152: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 153: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 117: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 107: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 118: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 104: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 123: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 147: // MaybeInitially
      case 148: // Initializers
      case 150: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 144: // Parameters
      case 145: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 124: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 133: // ReferenceLiteral
        value.copy< ReferenceAtom::Ptr > (that.value);
        break;

      case 138: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 97: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 91: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 98: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 109: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 99: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 84: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 115: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 96: // TypeDefinition
        value.copy< TypeDefinition::Ptr > (that.value);
        break;

      case 134: // Types
      case 142: // FunctionParameters
      case 143: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 126: // UndefinedLiteral
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 121: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 110: // UpdateRule
      case 149: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 127: // BooleanLiteral
      case 128: // IntegerLiteral
      case 129: // RationalLiteral
      case 130: // DecimalLiteral
      case 131: // BitLiteral
      case 132: // StringLiteral
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 154: // Variable
      case 155: // TypedVariable
      case 156: // AttributedVariable
      case 157: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 135: // Type
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
      case 159: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 158: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 160: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 136: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 108: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 111: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 102: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 101: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 103: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 120: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 106: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 137: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 119: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 100: // ConditionalRule
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

      case 122: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 113: // Term
      case 114: // Expression
      case 125: // Literal
      case 146: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 161: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 112: // Terms
      case 140: // Arguments
      case 141: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 139: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 105: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 92: // FunctionDefinition
      case 93: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 85: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 151: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 152: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 153: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 117: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 107: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 118: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 104: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 123: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 147: // MaybeInitially
      case 148: // Initializers
      case 150: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 144: // Parameters
      case 145: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 124: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 133: // ReferenceLiteral
        yylhs.value.build< ReferenceAtom::Ptr > ();
        break;

      case 138: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 97: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 91: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 98: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 109: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 99: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 84: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 115: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 96: // TypeDefinition
        yylhs.value.build< TypeDefinition::Ptr > ();
        break;

      case 134: // Types
      case 142: // FunctionParameters
      case 143: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 126: // UndefinedLiteral
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 121: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 110: // UpdateRule
      case 149: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 127: // BooleanLiteral
      case 128: // IntegerLiteral
      case 129: // RationalLiteral
      case 130: // DecimalLiteral
      case 131: // BitLiteral
      case 132: // StringLiteral
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 154: // Variable
      case 155: // TypedVariable
      case 156: // AttributedVariable
      case 157: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 135: // Type
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
#line 1374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1392 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 405 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 411 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1412 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 421 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1430 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1438 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 439 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1446 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1462 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 451 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1470 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< TypeDefinition::Ptr > ();
  }
#line 1478 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 463 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1486 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 471 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1494 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1503 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1512 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1532 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1540 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 517 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 540 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 562 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1603 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 568 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1611 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 576 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1621 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 582 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeDefinition::Ptr > () = Ast::make< TypeDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 604 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1663 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1671 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1679 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1687 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 628 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 632 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1703 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 636 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1711 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 640 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1719 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 644 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1727 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 652 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 658 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1747 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 668 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 676 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1763 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 680 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 688 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1779 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1787 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 700 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1795 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 708 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1811 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 716 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 722 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1831 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1847 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 744 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1855 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 752 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1863 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1871 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 768 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1879 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1887 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 776 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1896 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 781 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 790 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 794 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 798 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1930 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 803 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1939 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 822 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 826 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 830 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1973 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 834 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1981 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 846 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1991 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 852 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2001 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 862 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2009 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 866 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 2017 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 870 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2025 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 874 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2033 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 878 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 882 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2049 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 886 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2057 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2065 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 894 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2073 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2081 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2089 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2097 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2105 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 922 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2113 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 926 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2121 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 930 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2129 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 934 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2137 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2145 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 942 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2153 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 946 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2161 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2169 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2177 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2193 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2201 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2225 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2233 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2241 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2249 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2257 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2265 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2281 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1023 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2298 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1031 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1039 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1047 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2322 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1055 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2330 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1063 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1071 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1079 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1084 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2371 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1096 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2379 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1108 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 2387 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1112 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2395 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1116 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2403 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1120 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2411 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1124 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2419 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1128 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2427 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1132 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2435 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1136 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 2443 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1144 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1152 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1157 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1166 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2485 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1182 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2501 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1198 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1214 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2533 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1226 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2549 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1242 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2565 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1258 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2573 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1270 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1276 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1286 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1290 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1294 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1298 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1306 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2633 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1314 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1322 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2649 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2657 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1342 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2665 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2673 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1350 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2682 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1359 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2692 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2702 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1379 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2712 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1389 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2720 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1401 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2738 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1421 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1425 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 2772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1437 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2780 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1441 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1449 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2796 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1453 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2804 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2814 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1467 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2824 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1477 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2836 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1485 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2850 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1495 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1506 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1510 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1522 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1526 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 2893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1534 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 2901 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1538 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 2911 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1548 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1554 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2931 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1568 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2939 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1572 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 2948 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2956 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2966 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1595 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2974 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1603 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1621 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3002 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1627 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 3012 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 186:
#line 1636 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 3020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 187:
#line 1640 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 3028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 188:
#line 1648 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 3036 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 189:
#line 1656 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 3044 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 3048 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -218;

  const short int Parser::yytable_ninf_ = -153;

  const short int
  Parser::yypact_[] =
  {
       0,  -218,    -6,    22,   262,  -218,  -218,   970,   -29,  -218,
    -218,  -218,  -218,  -218,    -8,    -6,    -6,    -6,    -6,    -6,
      -6,   160,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
     -11,   -11,   -11,   970,   -11,  -218,  -218,  -218,   970,   970,
     970,   416,   479,    -4,    -6,  -218,  -218,  -218,  -218,  -218,
    -218,  1779,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,    11,   -25,    36,    -6,  1032,  -218,    52,
      -2,    52,    40,    35,     6,  -218,    -6,    48,  -218,  -218,
      47,    82,   106,  1304,   108,  -218,  -218,  -218,    83,   970,
    1515,    85,  -218,    31,  1548,  -218,  -218,    -4,   970,   970,
     970,   970,   970,   970,   970,   970,   970,   970,   970,   970,
     970,   970,   970,   970,   970,   542,  -218,    -6,  -218,  -218,
     416,  1581,    66,    90,  -218,    97,     3,    86,   102,   -27,
      -4,    -4,   282,    34,    -4,   970,   970,   970,   970,   970,
    -218,  1614,  -218,  -218,  -218,   970,   970,  -218,  -218,  -218,
    -218,  -218,   -12,  1846,  1812,  1840,   370,   118,   118,   778,
      77,    77,    92,    92,    92,  -218,   370,   778,    77,    77,
     110,  -218,   -30,  1779,  -218,   100,  1515,   970,   970,  1032,
    -218,   112,    -6,    -1,    48,  -218,  -218,    -4,     5,   870,
      -4,  -218,  -218,   105,    99,  -218,    -6,  -218,  1078,  1444,
    1189,  1378,  1482,    11,  1779,  1647,    -4,   970,  -218,  -218,
     970,  1779,  1779,  -218,  -218,    39,  -218,    -3,   126,  -218,
      -6,  -218,    71,  -218,   580,   621,  -218,   -11,   -11,   -11,
     870,    -5,   970,   970,   114,   655,   689,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,   113,
    -218,   128,    -4,    -4,  -218,   970,   970,   970,   970,   970,
    -218,  -218,    15,   -37,   121,  -218,  1680,    -6,  -218,   970,
      41,  -218,     5,   173,  -218,   723,   175,   761,   147,   174,
     178,  -218,  -218,  -218,  1341,  1411,   143,   795,   127,   836,
     970,   870,  -218,   186,  1779,  1779,  1779,  1779,  1779,    -4,
    -218,    -4,  -218,  -218,  1779,    -6,  -218,  -218,  -218,  -218,
    -218,  -218,   970,   970,   970,   870,   152,  -218,  -218,  -218,
    -218,  1779,  -218,   153,   194,  -218,   155,  -218,  1111,  1150,
    1228,   191,   328,   970,   171,  -218,  -218,   870,   870,   970,
     870,   870,   176,   170,   172,  -218,   908,  1713,  1746,  1032,
    -218,  -218,  1267,  -218,  -218,  -218,   870,   870,  -218,  -218,
     870,  -218,   177,   870,  -218,  -218,  -218,  -218,  -218
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,   172,   171,   188,     0,   185,
     186,   187,     1,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     6,     8,    10,    11,    12,    13,    20,    14,
       0,     0,     0,     0,     0,   127,   129,   128,     0,     0,
       0,     0,     0,     0,     0,   133,   134,   130,   131,   132,
     135,   189,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,   119,   120,   121,   122,   123,   124,
     125,   126,   176,   107,   173,     0,     0,   170,    21,   159,
       0,   159,     0,     0,     0,     5,     0,   178,   181,   177,
       0,     0,     0,     0,     0,   105,    86,    87,     0,     0,
       0,     0,   115,     0,    71,   136,   174,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,     0,     3,   184,
       0,   166,     0,   169,   165,     0,     0,     0,     0,     0,
       0,   154,     0,     0,     0,     0,     0,     0,     0,     0,
      85,     0,    84,   117,   116,     0,     0,   106,   139,   140,
     141,   142,   143,   102,   100,   101,   104,    88,    89,    95,
      96,    97,    90,    91,    92,    93,   103,    94,    98,    99,
       0,   149,     0,    71,   175,     0,    71,     0,     0,     0,
      22,     0,     0,     0,     0,   183,   156,     0,     0,     0,
       0,    28,   152,   153,     0,     7,     0,   179,     0,     0,
       0,     0,     0,     0,    70,     0,   154,     0,   148,   147,
       0,   167,   168,   164,   158,     0,   157,     0,     0,    25,
       0,    27,     0,    23,     0,     0,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    17,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    67,
      69,     0,     0,     0,   180,     0,     0,     0,     0,     0,
     109,   118,     0,   138,     0,   146,    70,     0,   155,     0,
       0,    15,     0,     0,    41,     0,     0,     0,     0,     0,
       0,    56,    66,    68,     0,     0,     0,     0,     0,     0,
       0,     0,   151,   161,   110,   113,   112,   111,   114,     0,
     144,     0,   150,   182,    16,     0,    26,    64,    62,    40,
      60,    58,     0,     0,     0,     0,     0,    59,    57,    63,
      61,    65,    18,     0,   163,   137,     0,    24,     0,     0,
       0,    43,     0,     0,     0,    19,   145,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,   170,
      52,    53,     0,    55,    44,    46,     0,     0,    45,    50,
       0,   160,     0,     0,    47,    48,    49,   162,    54
  };

  const short int
  Parser::yypgoto_[] =
  {
    -218,  -218,  -218,  -218,   208,    88,  -218,  -218,  -218,  -218,
    -218,   -50,  -218,  -218,  -142,  -217,  -218,  -218,  -218,  -123,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,   -79,
      -7,  -218,  -218,   -46,    98,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,  -218,
    -218,  -218,    78,  -218,  -218,  -218,  -218,    21,  -218,  -218,
      24,  -218,   156,  -218,  -218,  -218,    53,  -116,    46,   -13,
    -218,    42,  -131,   -23,    18,   -18,   180,  -218,  -218
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    21,    22,    23,    24,    25,    26,    27,
      28,   231,   232,    29,   284,   285,   248,   249,   250,   355,
     356,   251,   252,   253,   254,   255,   256,   257,   258,   103,
     131,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,   272,   157,   158,   159,   160,   161,   126,   132,   203,
     204,   193,   137,   334,   345,   133,   134,   135,    72,    73,
      74,    88,    89,    90,   196,     8,     9,    10,    11
  };

  const short int
  Parser::yytable_[] =
  {
      51,    78,    84,     1,   191,   195,   229,     5,    91,    92,
       5,    94,     5,     5,     5,     5,   219,   199,   287,    75,
    -152,     5,    12,     5,   155,    76,    93,  -152,   297,   299,
     105,    95,    96,    97,   100,   104,    86,   200,   127,   128,
     244,    77,   138,   216,   192,   226,   182,     2,     7,   217,
     192,   185,   230,   227,   142,    44,   125,   247,    44,    44,
      76,    79,    80,    81,    82,    83,     7,     6,   143,   309,
       6,   310,     6,     6,     6,     6,    87,    87,    87,   154,
      87,     6,   206,     6,   140,   155,   141,   277,    76,   315,
     106,   145,   151,    76,   162,    76,   195,   136,   291,   144,
     146,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   173,   174,   175,   176,   177,   178,   179,   183,   112,
     113,   281,     7,   186,   147,   282,   149,   162,   162,   150,
     188,   162,     7,   153,   117,   118,   119,   120,   208,   209,
     210,   211,   212,   319,   189,   319,   313,   190,   214,   215,
     197,   198,   120,   259,   220,   319,   218,   319,   224,   332,
      -2,    13,   262,   263,    14,    15,    16,    17,    18,    19,
     279,    99,   301,   184,   225,   117,   118,   119,   120,   300,
     221,   222,   194,   341,   162,   311,   317,   162,   259,   259,
     320,   322,   323,   327,   259,   292,   324,   333,   329,   259,
     259,   342,   343,   162,   344,   360,   361,    20,   363,   364,
     275,   346,   280,   276,   288,   289,   290,   351,   201,   202,
     359,   366,   207,   367,   374,   375,   365,   377,   376,    85,
     205,   378,   316,   369,   270,   294,   295,   139,     7,   259,
     274,   259,   223,   372,   233,   278,     0,     0,   264,   162,
     162,   259,    87,   259,     0,   259,   129,     0,   304,   305,
     306,   307,   308,    13,     0,     0,    14,    15,    16,    17,
      18,    19,   314,   194,     0,   228,     7,     0,   261,   259,
       0,     0,     0,    87,    87,    87,    14,    15,    16,    17,
      18,    19,     0,   331,   273,     0,   162,   260,   162,     0,
       0,   259,   259,     0,   259,   259,     0,     0,     0,    20,
       0,     0,     0,     0,     0,   338,   339,   340,     0,     0,
     259,   259,     0,   194,   259,     0,     0,   259,   233,   352,
       0,     0,   260,   260,     0,   357,   358,     0,   260,   293,
     302,   303,   362,   260,   260,    30,     5,    31,    32,   357,
       0,     0,    33,     0,     0,     0,     0,   353,     0,    34,
       0,   337,    35,    36,    37,     0,     0,     0,     0,    38,
      39,    40,     0,    41,     0,    42,     0,     0,     0,     0,
     354,    43,     0,   260,     0,   260,     0,   335,     0,   336,
       0,    44,     0,     0,     0,   260,     0,   260,     0,   260,
      45,    46,    47,    48,    49,    50,     6,   108,   109,   110,
       0,     0,   112,   113,   114,     0,     0,    98,     0,     0,
       0,     0,     0,   260,     0,   115,   116,   117,   118,   119,
     120,     0,     0,    30,     5,    31,    32,   122,   123,   124,
      33,     0,     0,     0,     0,   260,   260,    34,   260,   260,
      35,    36,    37,     0,     0,     0,     0,    38,    39,    40,
       0,    41,     0,    42,   260,   260,     0,     0,   260,    43,
       0,   260,     0,    99,     0,     0,     0,     0,     0,    44,
     101,     0,     0,     0,     0,     0,     0,     0,    45,    46,
      47,    48,    49,    50,     6,     0,    30,     5,    31,    32,
       0,     0,     0,    33,     0,     0,     0,     0,     0,     0,
      34,     0,     0,    35,    36,    37,     0,     0,     0,     0,
      38,    39,    40,     0,    41,     0,    42,   102,     0,     0,
       0,     0,    43,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    44,   180,     0,     0,     0,     0,     0,     0,
       0,    45,    46,    47,    48,    49,    50,     6,     0,    30,
       5,    31,    32,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,    34,     0,     0,    35,    36,    37,     0,
       0,   283,     0,    38,    39,    40,     0,    41,   181,    42,
       0,     0,   234,     0,   235,    43,   236,   237,     5,   238,
     239,   240,     0,   241,   242,    44,     0,   243,     0,     0,
       0,     0,     0,     0,    45,    46,    47,    48,    49,    50,
       6,     0,   286,     0,     0,   244,     0,     0,     0,   245,
       0,     0,     0,   234,     0,   235,     0,   236,   237,     5,
     238,   239,   240,    44,   241,   242,     0,     0,   243,     0,
     246,     0,     0,     0,     0,     0,   296,     0,     6,     0,
       0,     0,     0,     0,     0,     0,   244,   234,     0,   235,
     245,   236,   237,     5,   238,   239,   240,     0,   241,   242,
       0,     0,   243,     0,    44,     0,     0,     0,     0,     0,
     298,   246,     0,     0,     0,     0,     0,     0,     0,     6,
     244,   234,     0,   235,   245,   236,   237,     5,   238,   239,
     240,     0,   241,   242,     0,     0,   243,     0,    44,     0,
       0,     0,     0,     0,     0,   246,     0,     0,     0,     0,
       0,     0,     0,     6,   244,   234,   318,   235,   245,   236,
     237,     5,   238,   239,   240,     0,   241,   242,     0,     0,
     243,     0,    44,     0,     0,     0,     0,     0,     0,   246,
       0,     0,     0,     0,     0,     0,     0,     6,   244,     0,
       0,     0,   245,   234,     0,   235,   321,   236,   237,     5,
     238,   239,   240,     0,   241,   242,    44,     0,   243,     0,
       0,     0,     0,   246,     0,     0,     0,     0,     0,     0,
       0,     6,     0,     0,     0,     0,   244,   234,     0,   235,
     245,   236,   237,     5,   238,   239,   240,     0,   241,   242,
     112,   113,   243,     0,    44,     0,     0,     0,     0,     0,
       0,   246,     0,   115,   116,   117,   118,   119,   120,     6,
     244,     0,     0,     0,   245,   328,   123,   124,   234,     0,
     235,     0,   236,   237,     5,   238,   239,   240,    44,   241,
     242,     0,     0,   243,     0,   246,     0,     0,     0,     0,
       0,     0,     0,     6,     0,     0,     0,     0,     0,     0,
       0,   244,   234,     0,   235,   245,   236,   237,     5,   238,
     239,   240,     0,   241,   242,     0,     0,   243,     0,    44,
       0,     0,     0,     0,     0,     0,   246,   330,     0,     0,
       0,     0,     0,     0,     6,   244,     0,     0,     0,   245,
       0,     0,     0,     0,     0,    30,     5,    31,    32,     0,
       0,     0,    33,    44,     0,     0,     0,   353,     0,    34,
     246,     0,    35,    36,    37,     0,     0,     0,     6,    38,
      39,    40,     0,    41,     0,    42,     0,     0,   368,     0,
     354,    43,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    44,     0,     0,     0,     0,     0,     0,     0,     0,
      45,    46,    47,    48,    49,    50,     6,    30,     5,    31,
      32,     0,     0,     0,    33,     0,     0,     0,     0,     0,
       0,    34,     0,     0,    35,    36,    37,     0,     0,     0,
       0,    38,    39,    40,     0,    41,     0,    42,     0,     0,
       0,     0,     0,    43,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    44,     0,     0,     0,     0,     0,     0,
       0,     0,    45,    46,    47,    48,    49,    50,     6,    30,
       5,    31,    32,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,    34,     0,     0,    35,    36,    37,     0,
       0,     0,     0,    38,    39,    40,     0,   130,     0,    42,
       0,     0,     0,     0,     0,    43,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    44,   265,     0,     0,     0,
       0,     0,     0,     0,    45,    46,    47,    48,    49,    50,
       6,   107,     0,     0,     0,   108,   109,   110,   111,     0,
     112,   113,   114,     0,     0,     0,     0,     0,     0,   347,
       0,     0,     0,   115,   116,   117,   118,   119,   120,     0,
       0,     0,     0,   121,   107,   122,   123,   124,   108,   109,
     110,   111,     0,   112,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,   348,     0,     0,     0,   121,     0,   122,   123,
     124,     0,   349,   107,     0,     0,     0,   108,   109,   110,
     111,     0,   112,   113,   114,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   116,   117,   118,   119,
     120,   267,     0,     0,     0,   121,     0,   122,   123,   124,
       0,     0,   107,     0,     0,     0,   108,   109,   110,   111,
       0,   112,   113,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,   116,   117,   118,   119,   120,
     350,     0,     0,     0,   121,     0,   122,   123,   124,     0,
       0,   107,     0,     0,     0,   108,   109,   110,   111,     0,
     112,   113,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   373,
       0,     0,     0,   121,     0,   122,   123,   124,     0,     0,
     107,     0,     0,     0,   108,   109,   110,   111,     0,   112,
     113,   114,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   115,   116,   117,   118,   119,   120,     0,   148,
       0,     0,   121,     0,   122,   123,   124,   107,     0,     0,
       0,   108,   109,   110,   111,     0,   112,   113,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,     0,   325,     0,     0,   121,
       0,   122,   123,   124,   107,     0,     0,     0,   108,   109,
     110,   111,     0,   112,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,     0,     0,   268,     0,   121,     0,   122,   123,
     124,   107,     0,     0,     0,   108,   109,   110,   111,     0,
     112,   113,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   326,
       0,     0,     0,   121,   107,   122,   123,   124,   108,   109,
     110,   111,     0,   112,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,     0,     0,   266,     0,   121,   107,   122,   123,
     124,   108,   109,   110,   111,     0,   112,   113,   114,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,     0,     0,     0,     0,   121,
       0,   122,   123,   124,   269,   107,     0,     0,     0,   108,
     109,   110,   111,     0,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,   116,   117,
     118,   119,   120,     0,     0,     0,     0,   121,   107,   122,
     123,   124,   108,   109,   110,   111,     0,   112,   113,   114,
       0,   152,     0,     0,     0,     0,     0,     0,     0,     0,
     115,   116,   117,   118,   119,   120,     0,     0,     0,     0,
     121,   107,   122,   123,   124,   108,   109,   110,   111,     0,
     112,   113,   114,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,   116,   117,   118,   119,   120,     0,
     156,     0,     0,   121,   107,   122,   123,   124,   108,   109,
     110,   111,     0,   112,   113,   114,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   115,   116,   117,   118,
     119,   120,     0,     0,     0,   187,   121,   107,   122,   123,
     124,   108,   109,   110,   111,     0,   112,   113,   114,     0,
     213,     0,     0,     0,     0,     0,     0,     0,     0,   115,
     116,   117,   118,   119,   120,     0,     0,     0,     0,   121,
     107,   122,   123,   124,   108,   109,   110,   111,     0,   112,
     113,   114,     0,     0,     0,   271,     0,     0,     0,     0,
       0,     0,   115,   116,   117,   118,   119,   120,     0,     0,
       0,     0,   121,   107,   122,   123,   124,   108,   109,   110,
     111,     0,   112,   113,   114,     0,   312,     0,     0,     0,
       0,     0,     0,     0,     0,   115,   116,   117,   118,   119,
     120,     0,     0,     0,     0,   121,   107,   122,   123,   124,
     108,   109,   110,   111,     0,   112,   113,   114,     0,     0,
       0,     0,     0,     0,   370,     0,     0,     0,   115,   116,
     117,   118,   119,   120,     0,     0,     0,     0,   121,   107,
     122,   123,   124,   108,   109,   110,   111,     0,   112,   113,
     114,     0,     0,     0,     0,     0,   371,     0,     0,     0,
       0,   115,   116,   117,   118,   119,   120,     0,     0,     0,
       0,   121,   107,   122,   123,   124,   108,   109,   110,   111,
       0,   112,   113,   114,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   115,   116,   117,   118,   119,   120,
       0,     0,     0,     0,   121,     0,   122,   123,   124,   108,
       0,   110,     0,     0,   112,   113,   114,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   115,   116,   117,
     118,   119,   120,     0,     0,     0,     0,   108,     0,   122,
     123,   124,   112,   113,   114,     0,     0,     0,   112,   113,
     114,     0,     0,     0,     0,   115,   116,   117,   118,   119,
     120,   115,   116,   117,   118,   119,   120,   122,   123,   124,
       0,     0,     0,   122,   123,   124
  };

  const short int
  Parser::yycheck_[] =
  {
       7,    14,    20,     3,     1,   136,     1,    18,    31,    32,
      18,    34,    18,    18,    18,    18,    46,    44,   235,    48,
      57,    18,     0,    18,    54,    54,    33,    64,   245,   246,
      43,    38,    39,    40,    41,    42,    47,    64,    63,     3,
      45,    49,    44,    55,    47,    46,   125,    47,     2,    61,
      47,   130,    47,    54,    48,    63,    45,   199,    63,    63,
      54,    15,    16,    17,    18,    19,    20,    78,    86,    54,
      78,    56,    78,    78,    78,    78,    30,    31,    32,    48,
      34,    78,    48,    78,    44,    54,    51,    48,    54,    48,
      44,    44,    99,    54,   107,    54,   227,    45,   240,    51,
      18,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,    42,
      43,    50,    76,   130,    18,    54,    18,   140,   141,    46,
      64,   144,    86,    48,    57,    58,    59,    60,   145,   146,
     147,   148,   149,   285,    54,   287,   277,    50,   155,   156,
      64,    49,    60,   199,    54,   297,    46,   299,    46,   301,
       0,     1,    57,    64,     4,     5,     6,     7,     8,     9,
      44,    57,    44,   127,   192,    57,    58,    59,    60,    66,
     187,   188,   136,   325,   197,    64,    13,   200,   234,   235,
      15,    44,    18,    50,   240,   241,    18,    11,    71,   245,
     246,    49,    49,   216,    10,   347,   348,    47,   350,   351,
     217,    56,   230,   220,   237,   238,   239,    26,   140,   141,
      49,    51,   144,    51,   366,   367,    50,    50,   370,    21,
     142,   373,   282,   356,   213,   242,   243,    81,   192,   285,
     216,   287,   189,   359,   198,   227,    -1,    -1,   206,   262,
     263,   297,   206,   299,    -1,   301,    76,    -1,   265,   266,
     267,   268,   269,     1,    -1,    -1,     4,     5,     6,     7,
       8,     9,   279,   227,    -1,   197,   230,    -1,   200,   325,
      -1,    -1,    -1,   237,   238,   239,     4,     5,     6,     7,
       8,     9,    -1,   300,   216,    -1,   309,   199,   311,    -1,
      -1,   347,   348,    -1,   350,   351,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,   322,   323,   324,    -1,    -1,
     366,   367,    -1,   277,   370,    -1,    -1,   373,   282,     1,
      -1,    -1,   234,   235,    -1,   342,   343,    -1,   240,   241,
     262,   263,   349,   245,   246,    17,    18,    19,    20,   356,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    29,    -1,    31,
      -1,   315,    34,    35,    36,    -1,    -1,    -1,    -1,    41,
      42,    43,    -1,    45,    -1,    47,    -1,    -1,    -1,    -1,
      52,    53,    -1,   285,    -1,   287,    -1,   309,    -1,   311,
      -1,    63,    -1,    -1,    -1,   297,    -1,   299,    -1,   301,
      72,    73,    74,    75,    76,    77,    78,    37,    38,    39,
      -1,    -1,    42,    43,    44,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,   325,    -1,    55,    56,    57,    58,    59,
      60,    -1,    -1,    17,    18,    19,    20,    67,    68,    69,
      24,    -1,    -1,    -1,    -1,   347,   348,    31,   350,   351,
      34,    35,    36,    -1,    -1,    -1,    -1,    41,    42,    43,
      -1,    45,    -1,    47,   366,   367,    -1,    -1,   370,    53,
      -1,   373,    -1,    57,    -1,    -1,    -1,    -1,    -1,    63,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    72,    73,
      74,    75,    76,    77,    78,    -1,    17,    18,    19,    20,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,    -1,
      41,    42,    43,    -1,    45,    -1,    47,    48,    -1,    -1,
      -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    63,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    72,    73,    74,    75,    76,    77,    78,    -1,    17,
      18,    19,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    34,    35,    36,    -1,
      -1,     1,    -1,    41,    42,    43,    -1,    45,    46,    47,
      -1,    -1,    12,    -1,    14,    53,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    63,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    -1,     1,    -1,    -1,    45,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    12,    -1,    14,    -1,    16,    17,    18,
      19,    20,    21,    63,    23,    24,    -1,    -1,    27,    -1,
      70,    -1,    -1,    -1,    -1,    -1,     1,    -1,    78,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    45,    12,    -1,    14,
      49,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      -1,    -1,    27,    -1,    63,    -1,    -1,    -1,    -1,    -1,
       1,    70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      45,    12,    -1,    14,    49,    16,    17,    18,    19,    20,
      21,    -1,    23,    24,    -1,    -1,    27,    -1,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    45,    12,    13,    14,    49,    16,
      17,    18,    19,    20,    21,    -1,    23,    24,    -1,    -1,
      27,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    45,    -1,
      -1,    -1,    49,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    63,    -1,    27,    -1,
      -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    78,    -1,    -1,    -1,    -1,    45,    12,    -1,    14,
      49,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      42,    43,    27,    -1,    63,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    -1,    55,    56,    57,    58,    59,    60,    78,
      45,    -1,    -1,    -1,    49,    50,    68,    69,    12,    -1,
      14,    -1,    16,    17,    18,    19,    20,    21,    63,    23,
      24,    -1,    -1,    27,    -1,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    78,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    45,    12,    -1,    14,    49,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    -1,    -1,    27,    -1,    63,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    -1,    -1,
      -1,    -1,    -1,    -1,    78,    45,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    -1,    17,    18,    19,    20,    -1,
      -1,    -1,    24,    63,    -1,    -1,    -1,    29,    -1,    31,
      70,    -1,    34,    35,    36,    -1,    -1,    -1,    78,    41,
      42,    43,    -1,    45,    -1,    47,    -1,    -1,    50,    -1,
      52,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      72,    73,    74,    75,    76,    77,    78,    17,    18,    19,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    -1,    34,    35,    36,    -1,    -1,    -1,
      -1,    41,    42,    43,    -1,    45,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    72,    73,    74,    75,    76,    77,    78,    17,
      18,    19,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    -1,    34,    35,    36,    -1,
      -1,    -1,    -1,    41,    42,    43,    -1,    45,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    18,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    73,    74,    75,    76,    77,
      78,    33,    -1,    -1,    -1,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    18,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    -1,
      -1,    -1,    -1,    65,    33,    67,    68,    69,    37,    38,
      39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    22,    -1,    -1,    -1,    65,    -1,    67,    68,
      69,    -1,    32,    33,    -1,    -1,    -1,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    22,    -1,    -1,    -1,    65,    -1,    67,    68,    69,
      -1,    -1,    33,    -1,    -1,    -1,    37,    38,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      22,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,
      -1,    33,    -1,    -1,    -1,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    22,
      -1,    -1,    -1,    65,    -1,    67,    68,    69,    -1,    -1,
      33,    -1,    -1,    -1,    37,    38,    39,    40,    -1,    42,
      43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    25,
      -1,    -1,    65,    -1,    67,    68,    69,    33,    -1,    -1,
      -1,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    25,    -1,    -1,    65,
      -1,    67,    68,    69,    33,    -1,    -1,    -1,    37,    38,
      39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    26,    -1,    65,    -1,    67,    68,
      69,    33,    -1,    -1,    -1,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    28,
      -1,    -1,    -1,    65,    33,    67,    68,    69,    37,    38,
      39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    30,    -1,    65,    33,    67,    68,
      69,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      -1,    67,    68,    69,    32,    33,    -1,    -1,    -1,    37,
      38,    39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    65,    33,    67,
      68,    69,    37,    38,    39,    40,    -1,    42,    43,    44,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,
      65,    33,    67,    68,    69,    37,    38,    39,    40,    -1,
      42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    55,    56,    57,    58,    59,    60,    -1,
      62,    -1,    -1,    65,    33,    67,    68,    69,    37,    38,
      39,    40,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,
      59,    60,    -1,    -1,    -1,    64,    65,    33,    67,    68,
      69,    37,    38,    39,    40,    -1,    42,    43,    44,    -1,
      46,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,
      56,    57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,
      33,    67,    68,    69,    37,    38,    39,    40,    -1,    42,
      43,    44,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      -1,    -1,    55,    56,    57,    58,    59,    60,    -1,    -1,
      -1,    -1,    65,    33,    67,    68,    69,    37,    38,    39,
      40,    -1,    42,    43,    44,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    -1,    -1,    -1,    -1,    65,    33,    67,    68,    69,
      37,    38,    39,    40,    -1,    42,    43,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    55,    56,
      57,    58,    59,    60,    -1,    -1,    -1,    -1,    65,    33,
      67,    68,    69,    37,    38,    39,    40,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      -1,    55,    56,    57,    58,    59,    60,    -1,    -1,    -1,
      -1,    65,    33,    67,    68,    69,    37,    38,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,    60,
      -1,    -1,    -1,    -1,    65,    -1,    67,    68,    69,    37,
      -1,    39,    -1,    -1,    42,    43,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    55,    56,    57,
      58,    59,    60,    -1,    -1,    -1,    -1,    37,    -1,    67,
      68,    69,    42,    43,    44,    -1,    -1,    -1,    42,    43,
      44,    -1,    -1,    -1,    -1,    55,    56,    57,    58,    59,
      60,    55,    56,    57,    58,    59,    60,    67,    68,    69,
      -1,    -1,    -1,    67,    68,    69
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    47,    84,    85,    18,    78,   151,   158,   159,
     160,   161,     0,     1,     4,     5,     6,     7,     8,     9,
      47,    86,    87,    88,    89,    90,    91,    92,    93,    96,
      17,    19,    20,    24,    31,    34,    35,    36,    41,    42,
      43,    45,    47,    53,    63,    72,    73,    74,    75,    76,
      77,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   151,   152,   153,    48,    54,    49,   152,   151,
     151,   151,   151,   151,   158,    87,    47,   151,   154,   155,
     156,   156,   156,   113,   156,   113,   113,   113,     1,    57,
     113,     1,    48,   112,   113,   152,   151,    33,    37,    38,
      39,    40,    42,    43,    44,    55,    56,    57,    58,    59,
      60,    65,    67,    68,    69,    45,   140,    63,     3,   159,
      45,   113,   141,   148,   149,   150,    45,   145,    44,   145,
      44,    51,    48,   158,    51,    44,    18,    18,    25,    18,
      46,   113,    46,    48,    48,    54,    62,   135,   136,   137,
     138,   139,   152,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
       1,    46,   112,   113,   151,   112,   113,    64,    64,    54,
      50,     1,    47,   144,   151,   155,   157,    64,    49,    44,
      64,   135,   135,   142,   143,    88,    48,   135,   113,   113,
     113,   113,   113,    46,   113,   113,    55,    61,    46,    46,
      54,   113,   113,   149,    46,   158,    46,    54,   135,     1,
      47,    94,    95,   151,    12,    14,    16,    17,    19,    20,
      21,    23,    24,    27,    45,    49,    70,    97,    99,   100,
     101,   104,   105,   106,   107,   108,   109,   110,   111,   116,
     117,   135,    57,    64,   154,    18,    30,    22,    26,    32,
     140,    48,   134,   135,   143,   113,   113,    48,   157,    44,
     158,    50,    54,     1,    97,    98,     1,    98,   156,   156,
     156,    97,   116,   117,   113,   113,     1,    98,     1,    98,
      66,    44,   135,   135,   113,   113,   113,   113,   113,    54,
      56,    64,    46,   155,   113,    48,    94,    13,    13,    97,
      15,    15,    44,    18,    18,    25,    28,    50,    50,    71,
      71,   113,    97,    11,   146,   135,   135,   151,   113,   113,
     113,    97,    49,    49,    10,   147,    56,    18,    22,    32,
      22,    26,     1,    29,    52,   102,   103,   113,   113,    49,
      97,    97,   113,    97,    97,    50,    51,    51,    50,   102,
      51,    50,   150,    22,    97,    97,    97,    50,    97
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    83,    84,    85,    85,    86,    86,    87,    87,    87,
      88,    88,    88,    88,    88,    89,    90,    91,    91,    92,
      92,    93,    93,    94,    94,    94,    95,    95,    96,    97,
      97,    97,    97,    97,    97,    97,    97,    97,    97,    97,
      98,    98,    99,   100,   100,   101,   101,   102,   102,   102,
     103,   103,   104,   105,   105,   106,   107,   108,   108,   108,
     108,   109,   109,   109,   109,   110,   111,   111,   111,   111,
     112,   112,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   115,   116,   116,   117,
     118,   119,   120,   121,   122,   123,   123,   123,   124,   125,
     125,   125,   125,   125,   125,   125,   125,   126,   127,   127,
     128,   129,   130,   131,   131,   132,   133,   134,   134,   135,
     135,   135,   135,   136,   137,   138,   139,   140,   140,   140,
     141,   142,   142,   143,   143,   144,   144,   145,   145,   145,
     146,   146,   147,   147,   148,   148,   149,   149,   149,   150,
     150,   151,   151,   152,   152,   153,   153,   154,   154,   155,
     156,   156,   157,   157,   158,   158,   159,   159,   160,   161
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     4,     1,     2,     1,     4,     1,     1,
       1,     1,     1,     1,     1,     6,     7,     5,     7,     8,
       1,     2,     4,     1,     4,     1,     3,     1,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     4,     6,     6,     6,     3,     3,     3,
       2,     1,     6,     6,     8,     6,     2,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     1,     2,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     3,     1,     2,     5,
       6,     6,     6,     6,     6,     2,     3,     3,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     3,     1,     1,
       1,     1,     1,     1,     4,     6,     3,     3,     3,     2,
       5,     3,     1,     1,     0,     3,     1,     3,     3,     0,
       4,     0,     4,     0,     3,     1,     1,     3,     3,     1,
       0,     1,     1,     1,     2,     3,     1,     1,     1,     3,
       4,     1,     4,     1,     3,     1,     1,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enumeration\"", "\"rule\"", "\"type\"", "\"function\"",
  "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"", "\"par\"",
  "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
  "\"choose\"", "\"iterate\"", "\"do\"", "\"call\"", "\"if\"", "\"then\"",
  "\"else\"", "\"case\"", "\"of\"", "\"default\"", "\"holds\"",
  "\"exists\"", "\"with\"", "\"as\"", "\"undef\"", "\"false\"", "\"true\"",
  "\"and\"", "\"or\"", "\"xor\"", "\"implies\"", "\"not\"", "\"+\"",
  "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"",
  "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"",
  "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"", "\"=>\"",
  "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"decimal\"",
  "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header", "Definitions",
  "AttributedDefinition", "Definition", "EnumerationDefinition",
  "DerivedDefinition", "RuleDefinition", "FunctionDefinition",
  "ProgramFunctionDefinition", "EnumeratorDefinition", "Enumerators",
  "TypeDefinition", "Rule", "Rules", "SkipRule", "ConditionalRule",
  "CaseRule", "CaseLabel", "CaseLabels", "LetRule", "ForallRule",
  "ChooseRule", "IterateRule", "BlockRule", "SequenceRule", "UpdateRule",
  "CallRule", "Terms", "Term", "Expression", "TypeCastingExpression",
  "DirectCallExpression", "IndirectCallExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "List", "Range", "Literal", "UndefinedLiteral", "BooleanLiteral",
  "IntegerLiteral", "RationalLiteral", "DecimalLiteral", "BitLiteral",
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
     438,   442,   446,   450,   454,   462,   470,   478,   483,   492,
     508,   516,   539,   557,   561,   567,   575,   581,   591,   603,
     607,   611,   615,   619,   623,   627,   631,   635,   639,   643,
     651,   657,   667,   675,   679,   687,   691,   699,   703,   707,
     715,   721,   731,   739,   743,   751,   759,   767,   771,   775,
     780,   789,   793,   797,   802,   811,   821,   825,   829,   833,
     845,   851,   861,   865,   869,   873,   877,   881,   885,   889,
     893,   897,   901,   905,   917,   921,   925,   929,   933,   937,
     941,   945,   949,   953,   957,   961,   965,   969,   973,   977,
     981,   985,   989,   993,   997,  1001,  1009,  1017,  1022,  1030,
    1038,  1046,  1054,  1062,  1070,  1078,  1083,  1087,  1095,  1107,
    1111,  1115,  1119,  1123,  1127,  1131,  1135,  1143,  1151,  1156,
    1165,  1181,  1197,  1213,  1225,  1241,  1257,  1269,  1275,  1285,
    1289,  1293,  1297,  1305,  1313,  1321,  1329,  1341,  1345,  1349,
    1358,  1372,  1378,  1388,  1392,  1400,  1406,  1416,  1420,  1424,
    1436,  1440,  1448,  1452,  1460,  1466,  1476,  1484,  1494,  1505,
    1509,  1521,  1525,  1533,  1537,  1547,  1553,  1567,  1571,  1580,
    1588,  1594,  1602,  1608,  1620,  1626,  1635,  1639,  1647,  1655
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
#line 4005 "GrammarParser.cpp" // lalr1.cc:1167
#line 1661 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
