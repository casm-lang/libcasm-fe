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
      case 151: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 150: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 152: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 129: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 102: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 105: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 96: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 95: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 97: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 113: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 100: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 130: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 112: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 94: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 84: // Definition
      case 85: // AttributedDefinition
        value.move< Definition::Ptr > (that.value);
        break;

      case 83: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 87: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 109: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 86: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 115: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 107: // Term
      case 108: // Expression
      case 118: // Literal
      case 139: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 153: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 106: // Terms
      case 133: // Arguments
      case 134: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 132: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 99: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 89: // FunctionDefinition
      case 90: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 145: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 146: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 144: // Identifiers
      case 147: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 110: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 101: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 111: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 98: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 116: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 140: // MaybeInitially
      case 141: // Initializers
      case 143: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 137: // Parameters
      case 138: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 117: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 126: // ReferenceLiteral
        value.move< ReferenceAtom::Ptr > (that.value);
        break;

      case 131: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 91: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 88: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 92: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 103: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 93: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 127: // Types
      case 135: // FunctionParameters
      case 136: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 119: // UndefinedLiteral
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 114: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 104: // UpdateRule
      case 142: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 120: // BooleanLiteral
      case 121: // IntegerLiteral
      case 122: // RationalLiteral
      case 123: // FloatingLiteral
      case 124: // BitLiteral
      case 125: // StringLiteral
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 148: // Variable
      case 149: // AttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 128: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 70: // "binary"
      case 71: // "hexadecimal"
      case 72: // "integer"
      case 73: // "rational"
      case 74: // "floating"
      case 75: // "string"
      case 76: // "identifier"
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
      case 151: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 150: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 152: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 129: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 102: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 105: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 96: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 95: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 97: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 113: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 100: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 130: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 112: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 94: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 84: // Definition
      case 85: // AttributedDefinition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 83: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 87: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 109: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 86: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 115: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 107: // Term
      case 108: // Expression
      case 118: // Literal
      case 139: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 153: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 106: // Terms
      case 133: // Arguments
      case 134: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 132: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 99: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 89: // FunctionDefinition
      case 90: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 145: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 146: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 144: // Identifiers
      case 147: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 110: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 101: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 111: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 98: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 116: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 140: // MaybeInitially
      case 141: // Initializers
      case 143: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 137: // Parameters
      case 138: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 117: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 126: // ReferenceLiteral
        value.copy< ReferenceAtom::Ptr > (that.value);
        break;

      case 131: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 91: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 88: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 92: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 103: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 93: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 127: // Types
      case 135: // FunctionParameters
      case 136: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 119: // UndefinedLiteral
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 114: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 104: // UpdateRule
      case 142: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 120: // BooleanLiteral
      case 121: // IntegerLiteral
      case 122: // RationalLiteral
      case 123: // FloatingLiteral
      case 124: // BitLiteral
      case 125: // StringLiteral
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 148: // Variable
      case 149: // AttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 128: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 70: // "binary"
      case 71: // "hexadecimal"
      case 72: // "integer"
      case 73: // "rational"
      case 74: // "floating"
      case 75: // "string"
      case 76: // "identifier"
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
      case 151: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 150: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 152: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 129: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 102: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 105: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 96: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 95: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 97: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 113: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 100: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 130: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 112: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 94: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 84: // Definition
      case 85: // AttributedDefinition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 83: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 87: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 109: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 86: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 115: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 107: // Term
      case 108: // Expression
      case 118: // Literal
      case 139: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 153: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 106: // Terms
      case 133: // Arguments
      case 134: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 132: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 99: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 89: // FunctionDefinition
      case 90: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 145: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 146: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 144: // Identifiers
      case 147: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 110: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 101: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 111: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 98: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 116: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 140: // MaybeInitially
      case 141: // Initializers
      case 143: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 137: // Parameters
      case 138: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 117: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 126: // ReferenceLiteral
        yylhs.value.build< ReferenceAtom::Ptr > ();
        break;

      case 131: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 91: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 88: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 92: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 103: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 93: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 82: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 127: // Types
      case 135: // FunctionParameters
      case 136: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 119: // UndefinedLiteral
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 114: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 104: // UpdateRule
      case 142: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 120: // BooleanLiteral
      case 121: // IntegerLiteral
      case 122: // RationalLiteral
      case 123: // FloatingLiteral
      case 124: // BitLiteral
      case 125: // StringLiteral
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 148: // Variable
      case 149: // AttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 128: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 70: // "binary"
      case 71: // "hexadecimal"
      case 72: // "integer"
      case 73: // "rational"
      case 74: // "floating"
      case 75: // "string"
      case 76: // "identifier"
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
#line 372 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1310 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 380 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 386 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1330 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 400 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1354 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1362 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1372 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1380 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 426 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Identifiers::Ptr > () );
  }
#line 1396 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1404 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 464 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 488 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1477 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 511 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1495 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 533 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1503 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 537 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1511 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1519 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 545 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1527 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 549 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1535 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1543 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 557 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1551 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1559 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 565 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 569 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1575 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1603 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 597 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1611 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1635 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 621 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 629 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 633 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 637 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 645 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1677 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1687 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 661 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 669 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1703 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 673 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1711 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 681 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1719 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 689 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1727 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 697 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1735 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 701 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1743 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1769 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 723 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1777 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1786 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1795 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 741 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 751 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1815 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1826 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1836 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1847 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 785 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 791 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1867 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1875 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1883 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 1891 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 813 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1899 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 1907 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 821 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1915 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1923 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 829 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1931 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 833 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1939 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 837 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1947 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 841 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1955 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 853 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1963 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 857 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 1971 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 861 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1979 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 865 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 1987 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 869 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 1995 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 873 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2003 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 877 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2011 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 881 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2019 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 885 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2027 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 889 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2035 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 893 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2043 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 897 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2051 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 901 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2059 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 905 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2067 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 909 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2075 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 913 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2083 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 917 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2091 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 921 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2099 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 925 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2107 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 929 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2115 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 933 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2123 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 937 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2131 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2140 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2148 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2156 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2164 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2172 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2180 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2188 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2196 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1008 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2205 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1013 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2213 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1017 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2221 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1025 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2229 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1037 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 2237 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1041 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2245 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1045 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2253 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1049 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2261 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2269 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1057 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2277 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1061 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1065 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 2293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1073 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2301 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1081 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2310 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1111 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1127 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::Memory::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 2367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1171 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1199 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1205 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2443 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1219 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1223 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2467 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1227 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1235 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2483 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1243 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1251 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1259 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1271 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1275 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1279 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2532 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1288 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2542 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1302 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2552 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1308 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1318 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2570 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1322 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2578 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1336 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2598 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 2606 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1350 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 2614 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1354 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 2622 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2630 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2638 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2646 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2654 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2664 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2674 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2686 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1414 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2700 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2711 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1435 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2719 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1439 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2727 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1451 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1457 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2747 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1467 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1471 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 2763 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 2771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1483 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::RELATIVE );
  }
#line 2779 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1491 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2799 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1511 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2807 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1515 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 2816 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1524 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2826 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1530 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2834 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1542 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2844 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1548 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2854 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1557 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2862 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2870 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1569 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2878 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2886 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2890 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -188;

  const short int Parser::yytable_ninf_ = -142;

  const short int
  Parser::yypact_[] =
  {
      -1,    36,    48,  -188,    -8,   -11,   -11,   -11,   -11,   -11,
     120,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    1002,   -11,  -188,  -188,  -188,   -35,    33,    16,    33,    30,
    1063,    32,  -188,  -188,  -188,  -188,   -16,   -16,   -16,  1063,
     -16,  -188,  -188,  -188,  1063,  1063,  1063,   485,   546,    -9,
    -188,  -188,  -188,  -188,  -188,  -188,  1511,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,    18,    52,  -188,    59,
      71,  -188,   -11,    29,    53,    72,   -15,    -9,   485,  1775,
     142,   -11,   -11,    74,  -188,   102,   136,   138,  1310,   151,
    -188,  -188,  -188,    90,  1063,   124,  1544,   131,  -188,    91,
    1577,  -188,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,
    1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,  1063,
    1063,  1002,  -188,   607,  -188,  -188,   134,     5,  -188,    -9,
     -11,   909,    -9,  -188,  -188,  -188,  -188,  -188,   127,   121,
      63,  1544,  -188,  -188,    93,    -9,  1063,  1063,  1063,  1063,
    1063,  -188,  1610,  1063,  -188,  -188,  -188,  1063,  1063,  1879,
    1808,  1860,   273,   117,   117,   186,    15,    15,   128,   128,
     128,  -188,  1775,   273,   186,    15,    15,  1775,  -188,   135,
    -188,     7,  1775,  -188,  -188,   -16,   147,   -37,  -188,   141,
     644,  -188,   -16,   -16,   -16,   909,    -7,  1063,  1063,   137,
     684,   721,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,   126,  -188,   149,    -9,    -9,    -9,
    1063,   -11,  -188,  1090,  1445,  1199,  1379,  1478,    71,  1643,
    1775,  1676,  -188,  -188,  -188,  1063,  -188,   -11,   181,  -188,
     758,   180,   795,   153,   182,   183,  -188,  -188,  -188,  1345,
    1412,   150,   832,   132,   872,  1063,   909,  -188,   187,   -38,
      20,   143,  1841,  -188,  1063,  1063,  1063,  1063,  1063,  -188,
    -188,  -188,  1775,  -188,  -188,  -188,  -188,  -188,  -188,  1063,
    1063,  1063,   909,   157,  -188,  -188,  -188,  -188,  1775,  -188,
     159,   198,    -9,  -188,    -9,  1775,  1775,  1775,  1775,  1775,
    1123,  1161,  1237,   185,   424,  1063,   161,  -188,  -188,   158,
     909,   909,  1063,   909,   909,   165,   166,   167,   941,   171,
    1709,  1742,  1002,  -188,  -188,  -188,  1275,  -188,  -188,  -188,
     909,   909,  -188,  -188,   909,  -188,   172,   909,  -188,  -188,
    -188,  -188,  -188
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,    11,     0,     0,     0,     0,     0,     0,
       0,    10,     4,     5,     6,     7,     8,    17,     1,   163,
     159,     0,   162,   167,    18,   164,   148,     0,   148,     0,
     176,     0,   173,   174,   175,     3,     0,     0,     0,     0,
       0,   116,   118,   117,     0,     0,     0,     0,     0,     0,
     122,   123,   119,   120,   121,   124,   155,    70,    63,    64,
      65,    66,    67,    68,    69,    71,    72,    73,   108,   109,
     110,   111,   112,   113,   114,   115,     0,   158,   154,     0,
      96,   165,     0,     0,     0,     0,     0,   143,     0,   177,
       0,     0,     0,   169,   171,     0,     0,     0,     0,     0,
      95,    76,    77,     0,     0,     0,    62,     0,   104,     0,
      62,   125,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    19,     0,    97,   166,     0,     0,   145,     0,
       0,     0,     0,   141,   128,   129,   130,   131,   142,     0,
     132,     0,     9,   172,     0,     0,     0,     0,     0,     0,
       0,    75,     0,     0,    74,   106,   105,     0,     0,    92,
      90,    91,    94,    78,    79,    85,    86,    87,    80,    81,
      82,    83,   156,    93,    84,    88,    89,   157,   153,     0,
     138,     0,    62,   147,   146,     0,     0,     0,   161,     0,
       0,    33,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    14,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    58,    60,     0,     0,     0,   143,
       0,     0,   168,     0,     0,     0,     0,     0,     0,    61,
      61,     0,   137,   136,   144,     0,    12,     0,     0,    32,
       0,     0,     0,     0,     0,     0,    47,    57,    59,     0,
       0,     0,     0,     0,     0,     0,     0,   140,   150,     0,
     127,     0,   135,   170,     0,     0,     0,     0,     0,    98,
     139,   107,    13,   160,    55,    53,    31,    51,    49,     0,
       0,     0,     0,     0,    50,    48,    54,    52,    56,    15,
       0,   152,     0,   133,     0,    99,   102,   101,   100,   103,
       0,     0,     0,    34,     0,     0,     0,    16,   126,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,     0,
       0,     0,   159,   134,    43,    44,     0,    46,    35,    37,
       0,     0,    41,    36,     0,   149,     0,     0,    38,    39,
      40,   151,    45
  };

  const short int
  Parser::yypgoto_[] =
  {
    -188,  -188,  -188,   144,   204,  -188,  -188,  -188,  -188,  -188,
      92,  -187,  -188,  -188,  -188,  -188,  -106,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,   -20,   -27,  -188,    55,    70,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,  -188,
    -188,  -188,  -188,  -188,  -188,  -188,  -188,  -117,  -188,  -188,
    -188,  -188,    -6,  -188,  -188,     2,  -188,   207,  -188,  -188,
    -188,   105,   -95,  -188,    26,    -4,   224,    25,   -33,   154,
     168,  -188,  -188
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,    10,    11,    12,    13,    14,    15,    16,    17,
     249,   250,   213,   214,   215,   328,   329,   216,   217,   218,
     219,   220,   221,   222,   223,   105,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,   269,   143,   144,   145,
     146,   147,   134,    76,   148,   149,   137,    84,   301,   317,
      77,    78,    79,   197,    23,    80,    25,    94,    95,    31,
      32,    33,    34
  };

  const short int
  Parser::yytable_[] =
  {
      24,    19,     1,    89,    96,    97,    19,    99,    19,    19,
      19,   246,    98,   252,   302,   247,   303,   100,   101,   102,
     106,   110,   196,   262,   264,   226,    82,   141,   109,    92,
     136,    26,    27,    28,    29,    30,   209,     3,   232,    20,
       4,     5,     6,     7,     8,   111,    19,   142,    18,   194,
     138,   243,    21,    21,    21,   116,   117,   195,    85,   167,
      22,   151,    93,    93,    93,    22,    93,    22,    22,    22,
     121,   122,   123,   124,    92,  -141,    83,   162,    90,    87,
     130,     9,  -141,   150,    91,   169,   170,   171,   172,   173,
     174,   175,   176,   177,   178,   179,   180,   181,   182,   183,
     184,   185,   186,   187,   131,    22,   192,   132,   135,    93,
     267,   268,   270,   191,   133,   139,   229,    30,    30,   140,
      -2,     3,   230,   155,     4,     5,     6,     7,     8,   233,
     234,   235,   236,   237,   161,   150,   239,   166,   150,   231,
     240,   241,   248,   167,   156,    91,     4,     5,     6,     7,
       8,   150,   199,   157,   200,   158,   201,   202,    19,   203,
     204,   205,   244,   206,   207,     9,   198,   208,   160,   253,
     254,   255,   121,   122,   123,   124,   163,   165,   193,   242,
     259,   260,   227,   228,   209,   318,   124,   319,   210,   245,
     265,   266,   104,   284,   287,   289,   224,   300,   294,   290,
     291,   296,    21,   272,   314,   304,   315,   316,   332,   211,
     324,   225,   333,   339,    35,   340,   341,    22,   282,   343,
     351,    93,   342,   150,   150,   150,   116,   117,    93,    93,
      93,   271,   279,   212,   152,    86,   188,   346,   298,   119,
     120,   121,   122,   123,   124,    81,   154,   305,   306,   307,
     308,   309,   128,   129,   224,   224,   273,    93,     0,   153,
     224,   257,   310,   311,   312,   224,   224,     0,     0,   225,
     225,     0,     0,   283,     0,   225,   258,     0,     0,     0,
     225,   225,     0,     0,     0,     0,     0,   330,   331,     0,
       0,     0,     0,     0,     0,   336,     0,   256,   150,     0,
     150,   330,     0,     0,     0,   224,     0,   224,   112,   113,
     114,     0,     0,   116,   117,   118,     0,   224,     0,   224,
     225,   224,   225,     0,     0,     0,   119,   120,   121,   122,
     123,   124,   225,     0,   225,     0,   225,     0,   127,   128,
     129,     0,   286,     0,   286,     0,     0,   224,     0,     0,
       0,     0,     0,     0,   286,     0,   286,     0,   299,     0,
       0,     0,   225,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   224,   224,     0,   224,   224,
       0,     0,     0,     0,   313,     0,     0,     0,     0,     0,
     225,   225,     0,   225,   225,   224,   224,     0,     0,   224,
       0,     0,   224,     0,     0,     0,     0,     0,     0,     0,
     225,   225,   334,   335,   225,   337,   338,   225,     0,     0,
       0,     0,     0,     0,     0,   325,     0,     0,     0,     0,
       0,     0,   348,   349,     0,     0,   350,     0,     0,   352,
      36,    19,    37,    38,     0,     0,     0,    39,     0,     0,
       0,     0,   326,     0,    40,     0,    41,    42,    43,     0,
       0,     0,     0,    44,    45,    46,     0,    88,     0,    48,
       0,     0,     0,     0,   327,    49,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,   103,     0,     0,     0,
       0,     0,     0,     0,    50,    51,    52,    53,    54,    55,
      22,    36,    19,    37,    38,     0,     0,     0,    39,     0,
       0,     0,     0,     0,     0,    40,     0,    41,    42,    43,
       0,     0,     0,     0,    44,    45,    46,     0,    88,     0,
      48,     0,     0,     0,     0,     0,    49,     0,     0,     0,
     104,     0,     0,     0,     0,     0,    21,   107,     0,     0,
       0,     0,     0,     0,     0,    50,    51,    52,    53,    54,
      55,    22,    36,    19,    37,    38,     0,     0,     0,    39,
       0,     0,     0,     0,     0,     0,    40,     0,    41,    42,
      43,     0,     0,     0,     0,    44,    45,    46,     0,    88,
       0,    48,   108,     0,     0,     0,     0,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,   189,     0,
       0,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    22,    36,    19,    37,    38,     0,     0,     0,
      39,     0,     0,     0,     0,     0,     0,    40,     0,    41,
      42,    43,     0,     0,     0,   251,    44,    45,    46,     0,
      88,   190,    48,     0,     0,   199,     0,   200,    49,   201,
     202,    19,   203,   204,   205,     0,   206,   207,    21,     0,
     208,     0,     0,     0,     0,     0,     0,    50,    51,    52,
      53,    54,    55,    22,     0,   261,     0,   209,     0,     0,
       0,   210,     0,     0,     0,   199,     0,   200,     0,   201,
     202,    19,   203,   204,   205,    21,   206,   207,     0,     0,
     208,     0,   211,     0,     0,     0,     0,     0,     0,     0,
      22,     0,   263,     0,     0,     0,     0,   209,     0,     0,
       0,   210,   199,     0,   200,     0,   201,   202,    19,   203,
     204,   205,     0,   206,   207,    21,     0,   208,     0,     0,
       0,     0,   211,     0,     0,     0,     0,     0,     0,     0,
      22,     0,     0,     0,   209,     0,     0,     0,   210,   199,
     285,   200,     0,   201,   202,    19,   203,   204,   205,     0,
     206,   207,    21,     0,   208,     0,     0,     0,     0,   211,
       0,     0,     0,     0,     0,     0,     0,    22,     0,     0,
       0,   209,     0,     0,     0,   210,   199,     0,   200,   288,
     201,   202,    19,   203,   204,   205,     0,   206,   207,    21,
       0,   208,     0,     0,     0,     0,   211,     0,     0,     0,
       0,     0,     0,     0,    22,     0,     0,     0,   209,     0,
       0,     0,   210,   199,     0,   200,     0,   201,   202,    19,
     203,   204,   205,     0,   206,   207,    21,     0,   208,     0,
       0,     0,     0,   211,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     0,     0,   209,     0,     0,     0,   210,
     295,     0,     0,   199,     0,   200,     0,   201,   202,    19,
     203,   204,   205,    21,   206,   207,     0,     0,   208,     0,
     211,     0,     0,     0,     0,     0,     0,     0,    22,     0,
       0,     0,     0,     0,     0,   209,     0,     0,     0,   210,
     199,     0,   200,     0,   201,   202,    19,   203,   204,   205,
       0,   206,   207,    21,     0,   208,     0,     0,     0,     0,
     211,   297,     0,     0,     0,     0,     0,     0,    22,     0,
       0,     0,   209,     0,     0,     0,   210,    36,    19,    37,
      38,     0,     0,     0,    39,     0,     0,     0,     0,   326,
      21,    40,     0,    41,    42,    43,     0,   211,     0,     0,
      44,    45,    46,     0,    88,    22,    48,     0,     0,     0,
       0,   327,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,     0,     0,     0,     0,     0,     0,     0,
       0,    50,    51,    52,    53,    54,    55,    22,    36,    19,
      37,    38,     0,     0,     0,    39,     0,     0,     0,     0,
       0,     0,    40,     0,    41,    42,    43,     0,     0,     0,
       0,    44,    45,    46,     0,    47,     0,    48,     0,     0,
       0,     0,     0,    49,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    22,    36,
      19,    37,    38,     0,     0,     0,    39,     0,     0,     0,
       0,     0,     0,    40,     0,    41,    42,    43,     0,     0,
       0,     0,    44,    45,    46,     0,    88,   274,    48,     0,
       0,     0,     0,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,   112,   113,   114,   115,     0,
     116,   117,   118,    50,    51,    52,    53,    54,    55,    22,
     320,     0,     0,   119,   120,   121,   122,   123,   124,     0,
       0,     0,     0,   126,     0,   127,   128,   129,   112,   113,
     114,   115,     0,   116,   117,   118,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   119,   120,   121,   122,
     123,   124,   321,     0,     0,     0,   126,     0,   127,   128,
     129,     0,   322,     0,     0,     0,   112,   113,   114,   115,
       0,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   119,   120,   121,   122,   123,   124,
     276,     0,     0,     0,   126,     0,   127,   128,   129,     0,
       0,     0,     0,     0,   112,   113,   114,   115,     0,   116,
     117,   118,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   119,   120,   121,   122,   123,   124,   323,     0,
       0,     0,   126,     0,   127,   128,   129,     0,     0,     0,
       0,     0,   112,   113,   114,   115,     0,   116,   117,   118,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     119,   120,   121,   122,   123,   124,   347,     0,     0,     0,
     126,     0,   127,   128,   129,     0,     0,     0,     0,     0,
     112,   113,   114,   115,     0,   116,   117,   118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   120,
     121,   122,   123,   124,   159,     0,     0,     0,   126,     0,
     127,   128,   129,     0,     0,   112,   113,   114,   115,     0,
     116,   117,   118,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   119,   120,   121,   122,   123,   124,   292,
       0,     0,     0,   126,     0,   127,   128,   129,     0,     0,
     112,   113,   114,   115,     0,   116,   117,   118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   120,
     121,   122,   123,   124,   277,     0,     0,     0,   126,     0,
     127,   128,   129,     0,   112,   113,   114,   115,     0,   116,
     117,   118,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   119,   120,   121,   122,   123,   124,     0,   293,
       0,     0,   126,     0,   127,   128,   129,   112,   113,   114,
     115,     0,   116,   117,   118,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   119,   120,   121,   122,   123,
     124,     0,     0,     0,   275,   126,     0,   127,   128,   129,
     112,   113,   114,   115,     0,   116,   117,   118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   120,
     121,   122,   123,   124,     0,     0,     0,     0,   126,   278,
     127,   128,   129,   112,   113,   114,   115,     0,   116,   117,
     118,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   119,   120,   121,   122,   123,   124,     0,     0,     0,
       0,   126,     0,   127,   128,   129,   112,   113,   114,   115,
       0,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   119,   120,   121,   122,   123,   124,
       0,     0,     0,   125,   126,     0,   127,   128,   129,   112,
     113,   114,   115,     0,   116,   117,   118,     0,   164,     0,
       0,     0,     0,     0,     0,     0,     0,   119,   120,   121,
     122,   123,   124,     0,     0,     0,     0,   126,     0,   127,
     128,   129,   112,   113,   114,   115,     0,   116,   117,   118,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     119,   120,   121,   122,   123,   124,     0,   168,     0,     0,
     126,     0,   127,   128,   129,   112,   113,   114,   115,     0,
     116,   117,   118,     0,   238,     0,     0,     0,     0,     0,
       0,     0,     0,   119,   120,   121,   122,   123,   124,     0,
       0,     0,     0,   126,     0,   127,   128,   129,   112,   113,
     114,   115,     0,   116,   117,   118,     0,   280,     0,     0,
       0,     0,     0,     0,     0,     0,   119,   120,   121,   122,
     123,   124,     0,     0,     0,     0,   126,     0,   127,   128,
     129,   112,   113,   114,   115,     0,   116,   117,   118,     0,
       0,     0,   281,     0,     0,     0,     0,     0,     0,   119,
     120,   121,   122,   123,   124,     0,     0,     0,     0,   126,
       0,   127,   128,   129,   112,   113,   114,   115,     0,   116,
     117,   118,     0,     0,     0,     0,     0,     0,   344,     0,
       0,     0,   119,   120,   121,   122,   123,   124,     0,     0,
       0,     0,   126,     0,   127,   128,   129,   112,   113,   114,
     115,     0,   116,   117,   118,     0,     0,     0,     0,     0,
     345,     0,     0,     0,     0,   119,   120,   121,   122,   123,
     124,     0,     0,     0,     0,   126,     0,   127,   128,   129,
     112,   113,   114,   115,     0,   116,   117,   118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   120,
     121,   122,   123,   124,     0,     0,     0,     0,   126,     0,
     127,   128,   129,   112,     0,   114,     0,     0,   116,   117,
     118,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   119,   120,   121,   122,   123,   124,     0,     0,     0,
       0,     0,     0,   127,   128,   129,   112,   113,   114,   115,
       0,   116,   117,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   119,   112,     0,   122,   123,   124,
     116,   117,   118,     0,   126,     0,   127,   128,   129,     0,
       0,     0,     0,   119,   120,   121,   122,   123,   124,   116,
     117,   118,     0,     0,     0,   127,   128,   129,     0,     0,
       0,     0,   119,   120,   121,   122,   123,   124,     0,     0,
       0,     0,     0,     0,   127,   128,   129
  };

  const short int
  Parser::yycheck_[] =
  {
       4,    17,     3,    30,    37,    38,    17,    40,    17,    17,
      17,    48,    39,   200,    52,    52,    54,    44,    45,    46,
      47,    48,   139,   210,   211,   142,    61,    42,    48,    45,
       1,     5,     6,     7,     8,     9,    43,     1,   155,    47,
       4,     5,     6,     7,     8,    49,    17,    62,     0,    44,
      83,    44,    61,    61,    61,    40,    41,    52,    42,    52,
      76,    88,    36,    37,    38,    76,    40,    76,    76,    76,
      55,    56,    57,    58,    45,    55,    43,   104,    46,    49,
      62,    45,    62,    87,    52,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,    52,    76,   133,    48,    82,    83,
     227,   228,   229,   133,    43,    62,    53,    91,    92,    47,
       0,     1,    59,    49,     4,     5,     6,     7,     8,   156,
     157,   158,   159,   160,    44,   139,   163,    46,   142,    46,
     167,   168,     1,    52,    42,    52,     4,     5,     6,     7,
       8,   155,    11,    17,    13,    17,    15,    16,    17,    18,
      19,    20,   195,    22,    23,    45,   140,    26,    17,   202,
     203,   204,    55,    56,    57,    58,    52,    46,    44,    44,
     207,   208,    55,    62,    43,   302,    58,   304,    47,    42,
      64,    42,    55,    12,    14,    42,   141,    10,    48,    17,
      17,    69,    61,   230,    47,    62,    47,     9,    47,    68,
      25,   141,    54,    48,    10,    49,    49,    76,   245,    48,
      48,   195,   328,   227,   228,   229,    40,    41,   202,   203,
     204,   229,   238,   141,    90,    28,   131,   332,   265,    53,
      54,    55,    56,    57,    58,    21,    92,   274,   275,   276,
     277,   278,    66,    67,   199,   200,   231,   231,    -1,    91,
     205,   206,   289,   290,   291,   210,   211,    -1,    -1,   199,
     200,    -1,    -1,   247,    -1,   205,   206,    -1,    -1,    -1,
     210,   211,    -1,    -1,    -1,    -1,    -1,   314,   315,    -1,
      -1,    -1,    -1,    -1,    -1,   322,    -1,   205,   302,    -1,
     304,   328,    -1,    -1,    -1,   250,    -1,   252,    35,    36,
      37,    -1,    -1,    40,    41,    42,    -1,   262,    -1,   264,
     250,   266,   252,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,   262,    -1,   264,    -1,   266,    -1,    65,    66,
      67,    -1,   250,    -1,   252,    -1,    -1,   292,    -1,    -1,
      -1,    -1,    -1,    -1,   262,    -1,   264,    -1,   266,    -1,
      -1,    -1,   292,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   320,   321,    -1,   323,   324,
      -1,    -1,    -1,    -1,   292,    -1,    -1,    -1,    -1,    -1,
     320,   321,    -1,   323,   324,   340,   341,    -1,    -1,   344,
      -1,    -1,   347,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     340,   341,   320,   321,   344,   323,   324,   347,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    -1,    -1,    -1,    -1,
      -1,    -1,   340,   341,    -1,    -1,   344,    -1,    -1,   347,
      16,    17,    18,    19,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    28,    -1,    30,    -1,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,    40,    41,    -1,    43,    -1,    45,
      -1,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    16,    17,    18,    19,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    40,    41,    -1,    43,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    61,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    16,    17,    18,    19,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,
      34,    -1,    -1,    -1,    -1,    39,    40,    41,    -1,    43,
      -1,    45,    46,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    16,    17,    18,    19,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    34,    -1,    -1,    -1,     1,    39,    40,    41,    -1,
      43,    44,    45,    -1,    -1,    11,    -1,    13,    51,    15,
      16,    17,    18,    19,    20,    -1,    22,    23,    61,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    -1,     1,    -1,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    11,    -1,    13,    -1,    15,
      16,    17,    18,    19,    20,    61,    22,    23,    -1,    -1,
      26,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,     1,    -1,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    47,    11,    -1,    13,    -1,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    61,    -1,    26,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,    11,
      12,    13,    -1,    15,    16,    17,    18,    19,    20,    -1,
      22,    23,    61,    -1,    26,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    43,    -1,    -1,    -1,    47,    11,    -1,    13,    14,
      15,    16,    17,    18,    19,    20,    -1,    22,    23,    61,
      -1,    26,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    47,    11,    -1,    13,    -1,    15,    16,    17,
      18,    19,    20,    -1,    22,    23,    61,    -1,    26,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,
      48,    -1,    -1,    11,    -1,    13,    -1,    15,    16,    17,
      18,    19,    20,    61,    22,    23,    -1,    -1,    26,    -1,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,
      11,    -1,    13,    -1,    15,    16,    17,    18,    19,    20,
      -1,    22,    23,    61,    -1,    26,    -1,    -1,    -1,    -1,
      68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    43,    -1,    -1,    -1,    47,    16,    17,    18,
      19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,
      61,    30,    -1,    32,    33,    34,    -1,    68,    -1,    -1,
      39,    40,    41,    -1,    43,    76,    45,    -1,    -1,    -1,
      -1,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    16,    17,
      18,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,    40,    41,    -1,    43,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    16,
      17,    18,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    34,    -1,    -1,
      -1,    -1,    39,    40,    41,    -1,    43,    17,    45,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    35,    36,    37,    38,    -1,
      40,    41,    42,    70,    71,    72,    73,    74,    75,    76,
      17,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    63,    -1,    65,    66,    67,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    21,    -1,    -1,    -1,    63,    -1,    65,    66,
      67,    -1,    31,    -1,    -1,    -1,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      21,    -1,    -1,    -1,    63,    -1,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    21,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    21,    -1,    -1,    -1,
      63,    -1,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    24,    -1,    -1,    -1,    63,    -1,
      65,    66,    67,    -1,    -1,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    24,
      -1,    -1,    -1,    63,    -1,    65,    66,    67,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    25,    -1,    -1,    -1,    63,    -1,
      65,    66,    67,    -1,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    27,
      -1,    -1,    63,    -1,    65,    66,    67,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    29,    63,    -1,    65,    66,    67,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,    31,
      65,    66,    67,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    -1,    65,    66,    67,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    62,    63,    -1,    65,    66,    67,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    60,    -1,    -1,
      63,    -1,    65,    66,    67,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    63,    -1,    65,    66,    67,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,    66,
      67,    35,    36,    37,    38,    -1,    40,    41,    42,    -1,
      -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      -1,    65,    66,    67,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      48,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    63,    -1,    65,    66,    67,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,
      65,    66,    67,    35,    -1,    37,    -1,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    35,    36,    37,    38,
      -1,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    35,    -1,    56,    57,    58,
      40,    41,    42,    -1,    63,    -1,    65,    66,    67,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    40,
      41,    42,    -1,    -1,    -1,    65,    66,    67,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    65,    66,    67
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    82,     1,     4,     5,     6,     7,     8,    45,
      83,    84,    85,    86,    87,    88,    89,    90,     0,    17,
      47,    61,    76,   145,   146,   147,   145,   145,   145,   145,
     145,   150,   151,   152,   153,    85,    16,    18,    19,    23,
      30,    32,    33,    34,    39,    40,    41,    43,    45,    51,
      70,    71,    72,    73,    74,    75,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   134,   141,   142,   143,
     146,   147,    61,    43,   138,    42,   138,    49,    43,   107,
      46,    52,    45,   145,   148,   149,   149,   149,   107,   149,
     107,   107,   107,     1,    55,   106,   107,     1,    46,   106,
     107,   146,    35,    36,    37,    38,    40,    41,    42,    53,
      54,    55,    56,    57,    58,    62,    63,    65,    66,    67,
      62,    52,    48,    43,   133,   145,     1,   137,   149,    62,
      47,    42,    62,   128,   129,   130,   131,   132,   135,   136,
     146,   107,    84,   151,   150,    49,    42,    17,    17,    24,
      17,    44,   107,    52,    44,    46,    46,    52,    60,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   142,     1,
      44,   106,   107,    44,    44,    52,   128,   144,   145,    11,
      13,    15,    16,    18,    19,    20,    22,    23,    26,    43,
      47,    68,    91,    93,    94,    95,    98,    99,   100,   101,
     102,   103,   104,   105,   109,   110,   128,    55,    62,    53,
      59,    46,   128,   107,   107,   107,   107,   107,    44,   107,
     107,   107,    44,    44,   149,    42,    48,    52,     1,    91,
      92,     1,    92,   149,   149,   149,    91,   109,   110,   107,
     107,     1,    92,     1,    92,    64,    42,   128,   128,   127,
     128,   136,   107,   148,    17,    29,    21,    25,    31,   133,
      44,    46,   107,   145,    12,    12,    91,    14,    14,    42,
      17,    17,    24,    27,    48,    48,    69,    69,   107,    91,
      10,   139,    52,    54,    62,   107,   107,   107,   107,   107,
     107,   107,   107,    91,    47,    47,     9,   140,   128,   128,
      17,    21,    31,    21,    25,     1,    28,    50,    96,    97,
     107,   107,    47,    54,    91,    91,   107,    91,    91,    48,
      49,    49,    97,    48,    49,    48,   143,    21,    91,    91,
      91,    48,    91
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    81,    82,    83,    83,    84,    84,    84,    84,    85,
      85,    85,    86,    87,    88,    88,    89,    89,    90,    90,
      91,    91,    91,    91,    91,    91,    91,    91,    91,    91,
      91,    92,    92,    93,    94,    94,    95,    95,    96,    96,
      96,    97,    97,    98,    99,    99,   100,   101,   102,   102,
     102,   102,   103,   103,   103,   103,   104,   105,   105,   105,
     105,   106,   106,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   109,   109,   110,   111,
     112,   113,   114,   115,   116,   116,   116,   117,   118,   118,
     118,   118,   118,   118,   118,   118,   119,   120,   120,   121,
     122,   123,   124,   124,   125,   126,   127,   127,   128,   128,
     128,   128,   129,   130,   131,   132,   133,   133,   133,   134,
     135,   135,   136,   136,   137,   137,   138,   138,   138,   139,
     139,   140,   140,   141,   141,   142,   142,   142,   143,   143,
     144,   144,   145,   145,   146,   146,   147,   147,   148,   148,
     149,   149,   150,   150,   151,   151,   152,   153
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     2,     1,     1,     1,     1,     1,     4,
       1,     1,     6,     7,     5,     7,     8,     1,     2,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     4,     6,     6,     6,     3,     3,
       3,     2,     1,     6,     6,     8,     6,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     2,     5,     6,
       6,     6,     6,     6,     2,     3,     3,     5,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     3,     1,     1,     1,
       1,     1,     1,     4,     6,     3,     3,     3,     2,     5,
       3,     1,     1,     0,     3,     1,     3,     3,     0,     4,
       0,     4,     0,     3,     1,     1,     3,     3,     1,     0,
       3,     1,     1,     1,     1,     2,     3,     1,     3,     1,
       4,     1,     3,     1,     1,     1,     1,     2
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
  "\"exists\"", "\"with\"", "\"undef\"", "\"false\"", "\"true\"",
  "\"and\"", "\"or\"", "\"xor\"", "\"implies\"", "\"not\"", "\"+\"",
  "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"",
  "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"",
  "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"", "\"=>\"",
  "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"floating\"",
  "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Definitions",
  "Definition", "AttributedDefinition", "EnumerationDefinition",
  "DerivedDefinition", "RuleDefinition", "FunctionDefinition",
  "ProgramFunctionDefinition", "Rule", "Rules", "SkipRule",
  "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels", "LetRule",
  "ForallRule", "ChooseRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", "Terms", "Term", "Expression",
  "DirectCallExpression", "IndirectCallExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "List", "Range", "Literal", "UndefinedLiteral", "BooleanLiteral",
  "IntegerLiteral", "RationalLiteral", "FloatingLiteral", "BitLiteral",
  "StringLiteral", "ReferenceLiteral", "Types", "Type", "BasicType",
  "ComposedType", "RelationType", "FixedSizedType", "Arguments",
  "TwoOrMoreArguments", "FunctionParameters", "MaybeFunctionParameters",
  "Parameters", "MaybeParameters", "MaybeDefined", "MaybeInitially",
  "Initializers", "Initializer", "MaybeInitializers", "Identifiers",
  "Identifier", "IdentifierPath", "DotSeparatedIdentifiers", "Variable",
  "AttributedVariable", "Attributes", "Attribute", "BasicAttribute",
  "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   371,   371,   379,   385,   395,   399,   403,   407,   415,
     421,   425,   433,   441,   449,   454,   463,   479,   487,   510,
     532,   536,   540,   544,   548,   552,   556,   560,   564,   568,
     572,   580,   586,   596,   604,   608,   616,   620,   628,   632,
     636,   644,   650,   660,   668,   672,   680,   688,   696,   700,
     704,   709,   718,   722,   726,   731,   740,   750,   756,   763,
     769,   784,   790,   800,   804,   808,   812,   816,   820,   824,
     828,   832,   836,   840,   852,   856,   860,   864,   868,   872,
     876,   880,   884,   888,   892,   896,   900,   904,   908,   912,
     916,   920,   924,   928,   932,   936,   944,   949,   957,   965,
     973,   981,   989,   997,  1007,  1012,  1016,  1024,  1036,  1040,
    1044,  1048,  1052,  1056,  1060,  1064,  1072,  1080,  1085,  1094,
    1110,  1126,  1142,  1154,  1170,  1186,  1198,  1204,  1214,  1218,
    1222,  1226,  1234,  1242,  1250,  1258,  1270,  1274,  1278,  1287,
    1301,  1307,  1317,  1321,  1329,  1335,  1345,  1349,  1353,  1365,
    1369,  1377,  1381,  1389,  1395,  1405,  1413,  1423,  1434,  1438,
    1450,  1456,  1466,  1470,  1478,  1482,  1490,  1496,  1510,  1514,
    1523,  1529,  1541,  1547,  1556,  1560,  1568,  1576
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
#line 3843 "GrammarParser.cpp" // lalr1.cc:1167
#line 1582 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
