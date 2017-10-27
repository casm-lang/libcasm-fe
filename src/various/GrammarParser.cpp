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
      case 153: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 152: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 154: // BasicAttribute
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

      case 155: // ExpressionAttribute
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
      case 149: // TypedVariable
      case 150: // AttributedVariable
      case 151: // TypedAttributedVariable
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
      case 153: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 152: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 154: // BasicAttribute
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

      case 155: // ExpressionAttribute
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
      case 149: // TypedVariable
      case 150: // AttributedVariable
      case 151: // TypedAttributedVariable
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
      case 153: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 152: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 154: // BasicAttribute
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

      case 155: // ExpressionAttribute
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
      case 149: // TypedVariable
      case 150: // AttributedVariable
      case 151: // TypedAttributedVariable
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
#line 1316 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 380 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1326 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 386 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 400 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1378 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1386 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 426 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1394 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Identifiers::Ptr > () );
  }
#line 1402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1410 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1419 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1428 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1448 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1456 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1483 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1501 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 533 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1509 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 537 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1525 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 545 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1533 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 549 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1541 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1549 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 557 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1565 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 565 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1573 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 569 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1581 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1589 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 597 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1633 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 621 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1649 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 629 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1657 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 633 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1665 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 637 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1673 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 645 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1693 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 661 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1701 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 669 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1709 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 673 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 681 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 689 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 697 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 701 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1758 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1767 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1775 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 723 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1783 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1801 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 741 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1811 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 751 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1832 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1842 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1853 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 785 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1863 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 791 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1889 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 1897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 813 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 1913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 821 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1929 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 829 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1937 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 833 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 837 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 841 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1961 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 853 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1969 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 857 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 1977 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 861 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1985 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 865 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 1993 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 869 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2001 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 873 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2009 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 877 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2017 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 881 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2025 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 885 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2033 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 889 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 893 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2049 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 897 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2057 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 901 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2065 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 905 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2073 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 909 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2081 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 913 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2089 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 917 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2097 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 921 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2105 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 925 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2113 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 929 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2121 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 933 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2129 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 937 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2137 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2146 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2154 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2162 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2170 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2178 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2186 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1008 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2211 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1013 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2219 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1017 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2227 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1025 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2235 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1037 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 2243 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1041 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2251 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1045 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2259 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1049 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2267 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2275 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1057 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2283 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1061 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2291 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1065 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 2299 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1073 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2307 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1081 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2316 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2325 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2341 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2357 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2373 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2389 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2405 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2421 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2429 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1199 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2439 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1205 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1219 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1223 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1227 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1235 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1243 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1251 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1259 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1271 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1275 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1279 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2538 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1288 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2548 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1302 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2558 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1308 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2568 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1318 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2576 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1322 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2594 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1336 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 2612 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1350 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 2620 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1354 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 2628 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2670 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2680 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2692 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2706 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1435 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1439 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1451 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2743 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1457 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2753 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1467 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1471 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 2769 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 2777 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1483 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::RELATIVE );
  }
#line 2785 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1491 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2795 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1511 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1515 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 2822 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1524 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2840 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1538 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1546 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1552 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1564 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1579 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1583 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2902 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1591 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2910 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2918 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2922 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -177;

  const short int Parser::yytable_ninf_ = -142;

  const short int
  Parser::yypact_[] =
  {
       2,   123,    16,  -177,   -11,    -7,    -7,    -7,    -7,    -7,
     115,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
    1056,    -7,  -177,  -177,  -177,   -34,   -15,   -12,   -15,     8,
    1117,    -5,  -177,  -177,  -177,  -177,    -3,    -3,    -3,  1117,
      -3,  -177,  -177,  -177,  1117,  1117,  1117,   502,   563,    -8,
    -177,  -177,  -177,  -177,  -177,  -177,  1565,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,   -13,    28,  -177,    10,
      11,  -177,    -7,     6,    43,    37,   -16,    -8,   502,  1829,
     142,    -7,    -7,    57,  -177,  -177,    72,   121,   139,  1364,
     140,  -177,  -177,  -177,   114,  1117,   107,  1598,   116,  -177,
      25,  1631,  -177,  1117,  1117,  1117,  1117,  1117,  1117,  1117,
    1117,  1117,  1117,  1117,  1117,  1117,  1117,  1117,  1117,  1117,
    1117,  1117,  1056,  -177,   624,  -177,  -177,   117,    -7,     0,
      57,  -177,  -177,    -8,    -7,   963,    -8,  -177,  -177,  -177,
    -177,  -177,   108,   103,    22,  1598,  -177,  -177,    33,    -8,
    1117,  1117,  1117,  1117,  1117,  -177,  1664,  1117,  -177,  -177,
    -177,  1117,  1117,   138,  1862,  1914,   286,    96,    96,   328,
     126,   126,   111,   111,   111,  -177,  1829,   286,   328,   126,
     126,  1829,  -177,   131,  -177,     4,  1829,  -177,    80,  -177,
      -2,   134,    24,  -177,   661,   701,  -177,    -3,    -3,    -3,
     963,    -6,  1117,  1117,   122,   738,   775,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,   125,
    -177,   145,    -8,    -8,    -8,  1117,    -7,  -177,  1144,  1499,
    1253,  1433,  1532,    11,  1697,  1829,  1730,  -177,  -177,    -7,
    -177,  1117,  -177,    -7,   185,  -177,   812,   184,   849,   157,
     183,   189,  -177,  -177,  -177,  1399,  1466,   153,   886,   133,
     926,  1117,   963,  -177,   199,    89,     5,   148,  1895,  -177,
    1117,  1117,  1117,  1117,  1117,  -177,  -177,  -177,  -177,  1829,
    -177,  -177,  -177,  -177,  -177,  -177,  1117,  1117,  1117,   963,
     164,  -177,  -177,  -177,  -177,  1829,  -177,   165,   204,    -8,
    -177,    -8,  1829,  1829,  1829,  1829,  1829,  1177,  1215,  1291,
     190,   441,  1117,   167,  -177,  -177,   162,   963,   963,  1117,
     963,   963,   169,   170,   171,  -177,   995,  1763,  1796,  1056,
    -177,  -177,  -177,  1329,  -177,  -177,  -177,   963,   963,  -177,
    -177,   963,  -177,   173,   963,  -177,  -177,  -177,  -177,  -177
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,    11,     0,     0,     0,     0,     0,     0,
       0,    10,     4,     5,     6,     7,     8,    17,     1,   163,
     159,     0,   162,   167,    18,   164,   148,     0,   148,     0,
     179,     0,   176,   177,   178,     3,     0,     0,     0,     0,
       0,   116,   118,   117,     0,     0,     0,     0,     0,     0,
     122,   123,   119,   120,   121,   124,   155,    70,    63,    64,
      65,    66,    67,    68,    69,    71,    72,    73,   108,   109,
     110,   111,   112,   113,   114,   115,     0,   158,   154,     0,
      96,   165,     0,     0,     0,     0,     0,   143,     0,   180,
       0,     0,     0,   169,   172,   168,     0,     0,     0,     0,
       0,    95,    76,    77,     0,     0,     0,    62,     0,   104,
       0,    62,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,    97,   166,     0,     0,     0,
       0,   174,   145,     0,     0,     0,     0,   141,   128,   129,
     130,   131,   142,     0,   132,     0,     9,   175,     0,     0,
       0,     0,     0,     0,     0,    75,     0,     0,    74,   106,
     105,     0,     0,    92,    90,    91,    94,    78,    79,    85,
      86,    87,    80,    81,    82,    83,   156,    93,    84,    88,
      89,   157,   153,     0,   138,     0,    62,   147,     0,   146,
       0,     0,     0,   161,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    14,    20,    21,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    58,
      60,     0,     0,     0,   143,     0,     0,   170,     0,     0,
       0,     0,     0,     0,    61,    61,     0,   137,   136,     0,
     144,     0,    12,     0,     0,    32,     0,     0,     0,     0,
       0,     0,    47,    57,    59,     0,     0,     0,     0,     0,
       0,     0,     0,   140,   150,     0,   127,     0,   135,   171,
       0,     0,     0,     0,     0,    98,   139,   107,   173,    13,
     160,    55,    53,    31,    51,    49,     0,     0,     0,     0,
       0,    50,    48,    54,    52,    56,    15,     0,   152,     0,
     133,     0,    99,   102,   101,   100,   103,     0,     0,     0,
      34,     0,     0,     0,    16,   126,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,     0,     0,     0,   159,
     134,    43,    44,     0,    46,    35,    37,     0,     0,    36,
      41,     0,   149,     0,     0,    38,    39,    40,   151,    45
  };

  const short int
  Parser::yypgoto_[] =
  {
    -177,  -177,  -177,   128,   213,  -177,  -177,  -177,  -177,  -177,
     102,  -176,  -177,  -177,  -177,  -111,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,   -24,   -27,  -177,    62,    77,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,  -177,
    -177,  -177,  -177,  -177,  -177,  -177,  -177,  -121,  -177,  -177,
    -177,  -177,    -1,  -177,  -177,     3,  -177,   203,  -177,  -177,
    -177,    95,  -107,  -177,    26,    -4,   215,     7,   -75,   -36,
      38,   -79,   149,  -177,  -177
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,    10,    11,    12,    13,    14,    15,    16,    17,
     255,   256,   218,   219,   220,   335,   336,   221,   222,   223,
     224,   225,   226,   227,   228,   106,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,   275,   147,   148,   149,
     150,   151,   135,    76,   152,   153,   139,    84,   308,   324,
      77,    78,    79,   202,    23,    80,    25,    94,    95,    96,
     142,    31,    32,    33,    34
  };

  const short int
  Parser::yytable_[] =
  {
      24,    97,    98,    89,   100,     1,    19,   137,   141,    19,
      19,    19,    99,   158,    19,    19,    18,   101,   102,   103,
     107,   111,   201,    19,   110,   231,   145,    82,    83,   258,
      85,    26,    27,    28,    29,    30,    20,   214,   237,   268,
     270,    90,    92,   138,   199,   112,   146,    91,   248,   131,
      21,   138,   200,    21,   134,    21,   171,    87,   133,   198,
    -141,   155,    93,    93,    93,    22,    93,  -141,    22,    22,
      22,   170,   252,    22,    22,   234,   253,   171,   166,   236,
     132,   235,    22,   154,   144,    91,   173,   174,   175,   176,
     177,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   143,   159,   196,   136,   140,
     195,   273,   274,   276,   160,    -2,     3,    30,    30,     4,
       5,     6,     7,     8,     3,   141,   249,     4,     5,     6,
       7,     8,    91,   238,   239,   240,   241,   242,   161,   154,
     244,   309,   154,   310,   245,   246,     4,     5,     6,     7,
       8,   122,   123,   124,   125,   154,   162,   164,   165,   167,
       9,   197,   169,   232,    30,   233,   117,   118,     9,   125,
     203,   259,   260,   261,   288,   247,   251,   105,   117,   118,
     119,   122,   123,   124,   125,   265,   266,   272,   325,   271,
     326,   120,   121,   122,   123,   124,   125,   291,   294,   296,
     297,   301,   303,   128,   129,   130,   298,   229,   278,   307,
     311,   321,   322,   323,   339,   331,   340,   346,   156,   347,
     348,   358,   230,    35,   289,   350,   140,   192,   154,   154,
     154,    86,   353,    93,    93,    93,    81,   277,   250,     0,
     157,     0,   285,   279,   305,     0,     0,   217,     0,     0,
       0,     0,     0,   312,   313,   314,   315,   316,     0,     0,
       0,     0,    93,     0,     0,     0,   229,   229,     0,   317,
     318,   319,   229,   263,     0,   140,     0,   229,   229,   290,
       0,   230,   230,     0,     0,     0,     0,   230,   264,     0,
       0,     0,   230,   230,   337,   338,     0,     0,     0,     0,
       0,     0,   343,     0,     0,   154,     0,   154,     0,   337,
       0,     0,   262,     0,     0,     0,     0,     0,   229,     0,
     229,   113,   114,   115,     0,     0,   117,   118,   119,     0,
     229,     0,   229,   230,   229,   230,     0,     0,     0,   120,
     121,   122,   123,   124,   125,   230,     0,   230,     0,   230,
       0,   128,   129,   130,     0,     0,     0,     0,   293,     0,
     293,   229,     0,     0,     0,     0,     0,     0,   117,   118,
     293,     0,   293,     0,   306,     0,   230,     0,     0,     0,
       0,   120,   121,   122,   123,   124,   125,     0,     0,   229,
     229,     0,   229,   229,   129,   130,     0,     0,     0,     0,
       0,   320,     0,     0,   230,   230,     0,   230,   230,   229,
     229,     0,     0,   229,     0,     0,   229,     0,     0,     0,
       0,     0,     0,     0,   230,   230,     0,     0,   230,   341,
     342,   230,   344,   345,     0,     0,     0,     0,     0,     0,
       0,     0,   332,     0,     0,     0,     0,     0,     0,   355,
     356,     0,     0,   357,     0,     0,   359,    36,    19,    37,
      38,     0,     0,     0,    39,     0,     0,     0,     0,   333,
       0,    40,     0,    41,    42,    43,     0,     0,     0,     0,
      44,    45,    46,     0,    88,     0,    48,     0,     0,     0,
       0,   334,    49,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,   104,     0,     0,     0,     0,     0,     0,
       0,    50,    51,    52,    53,    54,    55,    22,    36,    19,
      37,    38,     0,     0,     0,    39,     0,     0,     0,     0,
       0,     0,    40,     0,    41,    42,    43,     0,     0,     0,
       0,    44,    45,    46,     0,    88,     0,    48,     0,     0,
       0,     0,     0,    49,     0,     0,     0,   105,     0,     0,
       0,     0,     0,    21,   108,     0,     0,     0,     0,     0,
       0,     0,    50,    51,    52,    53,    54,    55,    22,    36,
      19,    37,    38,     0,     0,     0,    39,     0,     0,     0,
       0,     0,     0,    40,     0,    41,    42,    43,     0,     0,
       0,     0,    44,    45,    46,     0,    88,     0,    48,   109,
       0,     0,     0,     0,    49,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    21,   193,     0,     0,     0,     0,
       0,     0,     0,    50,    51,    52,    53,    54,    55,    22,
      36,    19,    37,    38,     0,     0,     0,    39,     0,     0,
       0,     0,     0,     0,    40,     0,    41,    42,    43,     0,
       0,     0,   254,    44,    45,    46,     0,    88,   194,    48,
       0,     0,   204,     0,   205,    49,   206,   207,    19,   208,
     209,   210,     0,   211,   212,    21,     0,   213,     0,     0,
       0,     0,     0,     0,    50,    51,    52,    53,    54,    55,
      22,     0,   257,     0,   214,     0,     0,     0,   215,     0,
       0,     0,   204,     0,   205,     0,   206,   207,    19,   208,
     209,   210,    21,   211,   212,     0,     0,   213,     0,   216,
       0,     0,     0,     0,     0,     0,     0,    22,     0,   267,
       0,     0,     0,     0,   214,     0,     0,     0,   215,   204,
       0,   205,     0,   206,   207,    19,   208,   209,   210,     0,
     211,   212,    21,     0,   213,     0,     0,     0,     0,   216,
       0,     0,     0,     0,     0,     0,   269,    22,     0,     0,
       0,   214,     0,     0,     0,   215,   204,     0,   205,     0,
     206,   207,    19,   208,   209,   210,     0,   211,   212,    21,
       0,   213,     0,     0,     0,     0,   216,     0,     0,     0,
       0,     0,     0,     0,    22,     0,     0,     0,   214,     0,
       0,     0,   215,   204,   292,   205,     0,   206,   207,    19,
     208,   209,   210,     0,   211,   212,    21,     0,   213,     0,
       0,     0,     0,   216,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     0,     0,   214,     0,     0,     0,   215,
     204,     0,   205,   295,   206,   207,    19,   208,   209,   210,
       0,   211,   212,    21,     0,   213,     0,     0,     0,     0,
     216,     0,     0,     0,     0,     0,     0,     0,    22,     0,
       0,     0,   214,     0,     0,     0,   215,   204,     0,   205,
       0,   206,   207,    19,   208,   209,   210,     0,   211,   212,
      21,     0,   213,     0,     0,     0,     0,   216,     0,     0,
       0,     0,     0,     0,     0,    22,     0,     0,     0,   214,
       0,     0,     0,   215,   302,     0,     0,   204,     0,   205,
       0,   206,   207,    19,   208,   209,   210,    21,   211,   212,
       0,     0,   213,     0,   216,     0,     0,     0,     0,     0,
       0,     0,    22,     0,     0,     0,     0,     0,     0,   214,
       0,     0,     0,   215,   204,     0,   205,     0,   206,   207,
      19,   208,   209,   210,     0,   211,   212,    21,     0,   213,
       0,     0,     0,     0,   216,   304,     0,     0,     0,     0,
       0,     0,    22,     0,     0,     0,   214,     0,     0,     0,
     215,    36,    19,    37,    38,     0,     0,     0,    39,     0,
       0,     0,     0,   333,    21,    40,     0,    41,    42,    43,
       0,   216,     0,     0,    44,    45,    46,     0,    88,    22,
      48,     0,     0,   349,     0,   334,    49,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,     0,     0,     0,
       0,     0,     0,     0,     0,    50,    51,    52,    53,    54,
      55,    22,    36,    19,    37,    38,     0,     0,     0,    39,
       0,     0,     0,     0,     0,     0,    40,     0,    41,    42,
      43,     0,     0,     0,     0,    44,    45,    46,     0,    47,
       0,    48,     0,     0,     0,     0,     0,    49,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,     0,     0,
       0,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    22,    36,    19,    37,    38,     0,     0,     0,
      39,     0,     0,     0,     0,     0,     0,    40,     0,    41,
      42,    43,     0,     0,     0,     0,    44,    45,    46,     0,
      88,   280,    48,     0,     0,     0,     0,     0,    49,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    21,   113,
     114,   115,   116,     0,   117,   118,   119,    50,    51,    52,
      53,    54,    55,    22,   327,     0,     0,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,   127,     0,   128,
     129,   130,   113,   114,   115,   116,     0,   117,   118,   119,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     120,   121,   122,   123,   124,   125,   328,     0,     0,     0,
     127,     0,   128,   129,   130,     0,   329,     0,     0,     0,
     113,   114,   115,   116,     0,   117,   118,   119,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   120,   121,
     122,   123,   124,   125,   282,     0,     0,     0,   127,     0,
     128,   129,   130,     0,     0,     0,     0,     0,   113,   114,
     115,   116,     0,   117,   118,   119,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   120,   121,   122,   123,
     124,   125,   330,     0,     0,     0,   127,     0,   128,   129,
     130,     0,     0,     0,     0,     0,   113,   114,   115,   116,
       0,   117,   118,   119,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   120,   121,   122,   123,   124,   125,
     354,     0,     0,     0,   127,     0,   128,   129,   130,     0,
       0,     0,     0,     0,   113,   114,   115,   116,     0,   117,
     118,   119,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   120,   121,   122,   123,   124,   125,   163,     0,
       0,     0,   127,     0,   128,   129,   130,     0,     0,   113,
     114,   115,   116,     0,   117,   118,   119,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   120,   121,   122,
     123,   124,   125,   299,     0,     0,     0,   127,     0,   128,
     129,   130,     0,     0,   113,   114,   115,   116,     0,   117,
     118,   119,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   120,   121,   122,   123,   124,   125,   283,     0,
       0,     0,   127,     0,   128,   129,   130,     0,   113,   114,
     115,   116,     0,   117,   118,   119,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   120,   121,   122,   123,
     124,   125,     0,   300,     0,     0,   127,     0,   128,   129,
     130,   113,   114,   115,   116,     0,   117,   118,   119,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   120,
     121,   122,   123,   124,   125,     0,     0,     0,   281,   127,
       0,   128,   129,   130,   113,   114,   115,   116,     0,   117,
     118,   119,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,   127,   284,   128,   129,   130,   113,   114,   115,
     116,     0,   117,   118,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   120,   121,   122,   123,   124,
     125,     0,     0,     0,     0,   127,     0,   128,   129,   130,
     113,   114,   115,   116,     0,   117,   118,   119,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   120,   121,
     122,   123,   124,   125,     0,     0,     0,   126,   127,     0,
     128,   129,   130,   113,   114,   115,   116,     0,   117,   118,
     119,     0,   168,     0,     0,     0,     0,     0,     0,     0,
       0,   120,   121,   122,   123,   124,   125,     0,     0,     0,
       0,   127,     0,   128,   129,   130,   113,   114,   115,   116,
       0,   117,   118,   119,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   120,   121,   122,   123,   124,   125,
       0,   172,     0,     0,   127,     0,   128,   129,   130,   113,
     114,   115,   116,     0,   117,   118,   119,     0,   243,     0,
       0,     0,     0,     0,     0,     0,     0,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,   127,     0,   128,
     129,   130,   113,   114,   115,   116,     0,   117,   118,   119,
       0,   286,     0,     0,     0,     0,     0,     0,     0,     0,
     120,   121,   122,   123,   124,   125,     0,     0,     0,     0,
     127,     0,   128,   129,   130,   113,   114,   115,   116,     0,
     117,   118,   119,     0,     0,     0,   287,     0,     0,     0,
       0,     0,     0,   120,   121,   122,   123,   124,   125,     0,
       0,     0,     0,   127,     0,   128,   129,   130,   113,   114,
     115,   116,     0,   117,   118,   119,     0,     0,     0,     0,
       0,     0,   351,     0,     0,     0,   120,   121,   122,   123,
     124,   125,     0,     0,     0,     0,   127,     0,   128,   129,
     130,   113,   114,   115,   116,     0,   117,   118,   119,     0,
       0,     0,     0,     0,   352,     0,     0,     0,     0,   120,
     121,   122,   123,   124,   125,     0,     0,     0,     0,   127,
       0,   128,   129,   130,   113,   114,   115,   116,     0,   117,
     118,   119,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   120,   121,   122,   123,   124,   125,     0,     0,
       0,     0,   127,     0,   128,   129,   130,   113,     0,   115,
       0,     0,   117,   118,   119,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   120,   121,   122,   123,   124,
     125,     0,     0,     0,     0,     0,     0,   128,   129,   130,
     113,   114,   115,   116,     0,   117,   118,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   120,   113,
       0,   123,   124,   125,   117,   118,   119,     0,   127,     0,
     128,   129,   130,     0,     0,     0,     0,   120,   121,   122,
     123,   124,   125,     0,     0,     0,     0,     0,     0,   128,
     129,   130
  };

  const short int
  Parser::yycheck_[] =
  {
       4,    37,    38,    30,    40,     3,    17,     1,    83,    17,
      17,    17,    39,    92,    17,    17,     0,    44,    45,    46,
      47,    48,   143,    17,    48,   146,    42,    61,    43,   205,
      42,     5,     6,     7,     8,     9,    47,    43,   159,   215,
     216,    46,    45,    45,    44,    49,    62,    52,    44,    62,
      61,    45,    52,    61,    43,    61,    52,    49,    48,   138,
      55,    88,    36,    37,    38,    76,    40,    62,    76,    76,
      76,    46,    48,    76,    76,    53,    52,    52,   105,    46,
      52,    59,    76,    87,    47,    52,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   129,   130,   131,    62,    49,   134,    82,    83,
     134,   232,   233,   234,    42,     0,     1,    91,    92,     4,
       5,     6,     7,     8,     1,   200,    46,     4,     5,     6,
       7,     8,    52,   160,   161,   162,   163,   164,    17,   143,
     167,    52,   146,    54,   171,   172,     4,     5,     6,     7,
       8,    55,    56,    57,    58,   159,    17,    17,    44,    52,
      45,    44,    46,    55,   138,    62,    40,    41,    45,    58,
     144,   207,   208,   209,   249,    44,    42,    55,    40,    41,
      42,    55,    56,    57,    58,   212,   213,    42,   309,    64,
     311,    53,    54,    55,    56,    57,    58,    12,    14,    42,
      17,    48,    69,    65,    66,    67,    17,   145,   235,    10,
      62,    47,    47,     9,    47,    25,    54,    48,    90,    49,
      49,    48,   145,    10,   251,   336,   200,   132,   232,   233,
     234,    28,   339,   207,   208,   209,    21,   234,   200,    -1,
      91,    -1,   243,   236,   271,    -1,    -1,   145,    -1,    -1,
      -1,    -1,    -1,   280,   281,   282,   283,   284,    -1,    -1,
      -1,    -1,   236,    -1,    -1,    -1,   204,   205,    -1,   296,
     297,   298,   210,   211,    -1,   249,    -1,   215,   216,   253,
      -1,   204,   205,    -1,    -1,    -1,    -1,   210,   211,    -1,
      -1,    -1,   215,   216,   321,   322,    -1,    -1,    -1,    -1,
      -1,    -1,   329,    -1,    -1,   309,    -1,   311,    -1,   336,
      -1,    -1,   210,    -1,    -1,    -1,    -1,    -1,   256,    -1,
     258,    35,    36,    37,    -1,    -1,    40,    41,    42,    -1,
     268,    -1,   270,   256,   272,   258,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,   268,    -1,   270,    -1,   272,
      -1,    65,    66,    67,    -1,    -1,    -1,    -1,   256,    -1,
     258,   299,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,
     268,    -1,   270,    -1,   272,    -1,   299,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,   327,
     328,    -1,   330,   331,    66,    67,    -1,    -1,    -1,    -1,
      -1,   299,    -1,    -1,   327,   328,    -1,   330,   331,   347,
     348,    -1,    -1,   351,    -1,    -1,   354,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   347,   348,    -1,    -1,   351,   327,
     328,   354,   330,   331,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,     1,    -1,    -1,    -1,    -1,    -1,    -1,   347,
     348,    -1,    -1,   351,    -1,    -1,   354,    16,    17,    18,
      19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,
      -1,    30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,    40,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,
      -1,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    16,    17,
      18,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,    40,    41,    -1,    43,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,
      -1,    -1,    -1,    61,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    16,
      17,    18,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    34,    -1,    -1,
      -1,    -1,    39,    40,    41,    -1,    43,    -1,    45,    46,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,     1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      16,    17,    18,    19,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,    -1,
      -1,    -1,     1,    39,    40,    41,    -1,    43,    44,    45,
      -1,    -1,    11,    -1,    13,    51,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    61,    -1,    26,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    -1,     1,    -1,    43,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    11,    -1,    13,    -1,    15,    16,    17,    18,
      19,    20,    61,    22,    23,    -1,    -1,    26,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,     1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,    11,
      -1,    13,    -1,    15,    16,    17,    18,    19,    20,    -1,
      22,    23,    61,    -1,    26,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,     1,    76,    -1,    -1,
      -1,    43,    -1,    -1,    -1,    47,    11,    -1,    13,    -1,
      15,    16,    17,    18,    19,    20,    -1,    22,    23,    61,
      -1,    26,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    47,    11,    12,    13,    -1,    15,    16,    17,
      18,    19,    20,    -1,    22,    23,    61,    -1,    26,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,
      11,    -1,    13,    14,    15,    16,    17,    18,    19,    20,
      -1,    22,    23,    61,    -1,    26,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      -1,    -1,    43,    -1,    -1,    -1,    47,    11,    -1,    13,
      -1,    15,    16,    17,    18,    19,    20,    -1,    22,    23,
      61,    -1,    26,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    47,    48,    -1,    -1,    11,    -1,    13,
      -1,    15,    16,    17,    18,    19,    20,    61,    22,    23,
      -1,    -1,    26,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    47,    11,    -1,    13,    -1,    15,    16,
      17,    18,    19,    20,    -1,    22,    23,    61,    -1,    26,
      -1,    -1,    -1,    -1,    68,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      47,    16,    17,    18,    19,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    28,    61,    30,    -1,    32,    33,    34,
      -1,    68,    -1,    -1,    39,    40,    41,    -1,    43,    76,
      45,    -1,    -1,    48,    -1,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    16,    17,    18,    19,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,
      34,    -1,    -1,    -1,    -1,    39,    40,    41,    -1,    43,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    16,    17,    18,    19,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    34,    -1,    -1,    -1,    -1,    39,    40,    41,    -1,
      43,    17,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    35,
      36,    37,    38,    -1,    40,    41,    42,    70,    71,    72,
      73,    74,    75,    76,    17,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    21,    -1,    -1,    -1,
      63,    -1,    65,    66,    67,    -1,    31,    -1,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    21,    -1,    -1,    -1,    63,    -1,
      65,    66,    67,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    21,    -1,    -1,    -1,    63,    -1,    65,    66,
      67,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      21,    -1,    -1,    -1,    63,    -1,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    24,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    -1,    -1,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    24,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,    -1,    -1,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    25,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    -1,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    27,    -1,    -1,    63,    -1,    65,    66,
      67,    35,    36,    37,    38,    -1,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    29,    63,
      -1,    65,    66,    67,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    31,    65,    66,    67,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    63,    -1,    65,    66,    67,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    62,    63,    -1,
      65,    66,    67,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    -1,    65,    66,    67,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    60,    -1,    -1,    63,    -1,    65,    66,    67,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      63,    -1,    65,    66,    67,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    63,    -1,    65,    66,    67,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,    66,
      67,    35,    36,    37,    38,    -1,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      -1,    65,    66,    67,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    35,    -1,    37,
      -1,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,
      35,    36,    37,    38,    -1,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    35,
      -1,    56,    57,    58,    40,    41,    42,    -1,    63,    -1,
      65,    66,    67,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    82,     1,     4,     5,     6,     7,     8,    45,
      83,    84,    85,    86,    87,    88,    89,    90,     0,    17,
      47,    61,    76,   145,   146,   147,   145,   145,   145,   145,
     145,   152,   153,   154,   155,    85,    16,    18,    19,    23,
      30,    32,    33,    34,    39,    40,    41,    43,    45,    51,
      70,    71,    72,    73,    74,    75,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   134,   141,   142,   143,
     146,   147,    61,    43,   138,    42,   138,    49,    43,   107,
      46,    52,    45,   145,   148,   149,   150,   150,   150,   107,
     150,   107,   107,   107,     1,    55,   106,   107,     1,    46,
     106,   107,   146,    35,    36,    37,    38,    40,    41,    42,
      53,    54,    55,    56,    57,    58,    62,    63,    65,    66,
      67,    62,    52,    48,    43,   133,   145,     1,    45,   137,
     145,   149,   151,    62,    47,    42,    62,   128,   129,   130,
     131,   132,   135,   136,   146,   107,    84,   153,   152,    49,
      42,    17,    17,    24,    17,    44,   107,    52,    44,    46,
      46,    52,    60,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   107,   107,   107,   107,   107,   107,   107,   107,
     107,   107,   142,     1,    44,   106,   107,    44,   152,    44,
      52,   128,   144,   145,    11,    13,    15,    16,    18,    19,
      20,    22,    23,    26,    43,    47,    68,    91,    93,    94,
      95,    98,    99,   100,   101,   102,   103,   104,   105,   109,
     110,   128,    55,    62,    53,    59,    46,   128,   107,   107,
     107,   107,   107,    44,   107,   107,   107,    44,    44,    46,
     151,    42,    48,    52,     1,    91,    92,     1,    92,   150,
     150,   150,    91,   109,   110,   107,   107,     1,    92,     1,
      92,    64,    42,   128,   128,   127,   128,   136,   107,   148,
      17,    29,    21,    25,    31,   133,    44,    46,   149,   107,
     145,    12,    12,    91,    14,    14,    42,    17,    17,    24,
      27,    48,    48,    69,    69,   107,    91,    10,   139,    52,
      54,    62,   107,   107,   107,   107,   107,   107,   107,   107,
      91,    47,    47,     9,   140,   128,   128,    17,    21,    31,
      21,    25,     1,    28,    50,    96,    97,   107,   107,    47,
      54,    91,    91,   107,    91,    91,    48,    49,    49,    48,
      96,    49,    48,   143,    21,    91,    91,    91,    48,    91
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
     149,   150,   150,   151,   151,   152,   152,   153,   153,   154,
     155
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
       3,     1,     1,     1,     1,     2,     3,     1,     1,     1,
       3,     4,     1,     4,     1,     3,     1,     1,     1,     1,
       2
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
  "TypedVariable", "AttributedVariable", "TypedAttributedVariable",
  "Attributes", "Attribute", "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
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
    1523,  1531,  1537,  1545,  1551,  1563,  1569,  1578,  1582,  1590,
    1598
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
#line 3886 "GrammarParser.cpp" // lalr1.cc:1167
#line 1604 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
