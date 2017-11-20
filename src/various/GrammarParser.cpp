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
      case 156: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 155: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 157: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 132: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 104: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 107: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 98: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 97: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 99: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 116: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 102: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 133: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 115: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 96: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 86: // AttributedDefinition
      case 87: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 85: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 89: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 112: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 88: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 118: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 109: // Term
      case 110: // Expression
      case 121: // Literal
      case 142: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 158: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 108: // Terms
      case 136: // Arguments
      case 137: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 135: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 101: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 91: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 84: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 148: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 149: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 147: // Identifiers
      case 150: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 113: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 103: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 114: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 100: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 119: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 143: // MaybeInitially
      case 144: // Initializers
      case 146: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 140: // Parameters
      case 141: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 120: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 129: // ReferenceLiteral
        value.move< ReferenceAtom::Ptr > (that.value);
        break;

      case 134: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 93: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 90: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 94: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 105: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 95: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 83: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 111: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (that.value);
        break;

      case 130: // Types
      case 138: // FunctionParameters
      case 139: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 122: // UndefinedLiteral
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 117: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 106: // UpdateRule
      case 145: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 123: // BooleanLiteral
      case 124: // IntegerLiteral
      case 125: // RationalLiteral
      case 126: // DecimalLiteral
      case 127: // BitLiteral
      case 128: // StringLiteral
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 151: // Variable
      case 152: // TypedVariable
      case 153: // AttributedVariable
      case 154: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 131: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
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
      case 156: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 155: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 157: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 132: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 104: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 107: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 98: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 97: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 99: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 116: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 102: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 133: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 115: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 96: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 86: // AttributedDefinition
      case 87: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 85: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 89: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 112: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 88: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 118: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 109: // Term
      case 110: // Expression
      case 121: // Literal
      case 142: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 158: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 108: // Terms
      case 136: // Arguments
      case 137: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 135: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 101: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 91: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 84: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 148: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 149: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 147: // Identifiers
      case 150: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 113: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 103: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 114: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 100: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 119: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 143: // MaybeInitially
      case 144: // Initializers
      case 146: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 140: // Parameters
      case 141: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 120: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 129: // ReferenceLiteral
        value.copy< ReferenceAtom::Ptr > (that.value);
        break;

      case 134: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 93: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 90: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 94: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 105: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 95: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 83: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 111: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (that.value);
        break;

      case 130: // Types
      case 138: // FunctionParameters
      case 139: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 122: // UndefinedLiteral
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 117: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 106: // UpdateRule
      case 145: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 123: // BooleanLiteral
      case 124: // IntegerLiteral
      case 125: // RationalLiteral
      case 126: // DecimalLiteral
      case 127: // BitLiteral
      case 128: // StringLiteral
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 151: // Variable
      case 152: // TypedVariable
      case 153: // AttributedVariable
      case 154: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 131: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
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
      case 156: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 155: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 157: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 132: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 104: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 107: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 98: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 97: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 99: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 116: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 102: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 133: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 115: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 96: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 86: // AttributedDefinition
      case 87: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 85: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 89: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 112: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 88: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 118: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 109: // Term
      case 110: // Expression
      case 121: // Literal
      case 142: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 158: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 108: // Terms
      case 136: // Arguments
      case 137: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 135: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 101: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 91: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 84: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 148: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 149: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 147: // Identifiers
      case 150: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 113: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 103: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 114: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 100: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 119: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 143: // MaybeInitially
      case 144: // Initializers
      case 146: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 140: // Parameters
      case 141: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 120: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 129: // ReferenceLiteral
        yylhs.value.build< ReferenceAtom::Ptr > ();
        break;

      case 134: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 93: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 90: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 94: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 105: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 95: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 83: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 111: // TypeCastingExpression
        yylhs.value.build< TypeCastingExpression::Ptr > ();
        break;

      case 130: // Types
      case 138: // FunctionParameters
      case 139: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 122: // UndefinedLiteral
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 117: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 106: // UpdateRule
      case 145: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 123: // BooleanLiteral
      case 124: // IntegerLiteral
      case 125: // RationalLiteral
      case 126: // DecimalLiteral
      case 127: // BitLiteral
      case 128: // StringLiteral
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 151: // Variable
      case 152: // TypedVariable
      case 153: // AttributedVariable
      case 154: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 131: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "decimal"
      case 76: // "string"
      case 77: // "identifier"
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
#line 378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 387 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 401 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1369 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1379 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 423 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 435 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 439 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1421 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1429 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1437 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Identifiers::Ptr > () );
  }
#line 1445 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 463 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1453 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 471 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1462 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1471 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 485 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 501 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1526 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 554 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1552 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1560 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 562 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1568 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 566 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1576 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1592 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1600 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 582 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1608 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 586 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1616 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 590 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1624 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 594 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1632 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 618 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 626 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 630 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 642 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1692 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1700 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 654 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1708 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 658 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 666 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1726 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 672 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1736 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 682 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1744 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 690 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 694 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1760 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 702 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1768 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1776 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1784 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 722 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1801 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 731 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1810 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1818 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 744 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1826 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1835 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 753 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1844 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 762 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1854 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1862 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 776 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1870 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1878 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 784 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 796 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1896 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 802 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1906 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1914 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< TypeCastingExpression::Ptr > ();
  }
#line 1922 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 820 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1930 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 824 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1938 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 828 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 1946 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1954 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 836 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 1962 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 840 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1970 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 844 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1978 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 848 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1986 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 852 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1994 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 856 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2002 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 868 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2010 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 872 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2018 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 876 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2026 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 880 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2034 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 884 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2042 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 888 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2050 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 892 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2058 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 896 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2066 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 900 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2074 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 904 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2082 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 908 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2090 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 912 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2098 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2106 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 920 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2114 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2122 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2130 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2138 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2146 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 940 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2154 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 944 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2162 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 948 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2170 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 952 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2178 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 960 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeCastingExpression::Ptr > () = Ast::make< TypeCastingExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2186 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2195 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 973 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2203 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2211 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 989 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2219 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 997 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2227 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1005 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2235 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1013 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2243 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1021 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2251 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1029 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2260 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1034 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1038 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1046 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2284 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1058 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 2292 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1062 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2300 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2308 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1070 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2316 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2324 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1078 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2332 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2340 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 2348 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1094 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2356 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1102 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1107 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1116 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2390 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1132 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2406 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1148 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1164 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2438 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1176 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2470 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1208 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2478 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1220 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2488 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1226 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2498 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1236 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2506 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1240 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2514 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1244 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2522 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1248 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2530 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1256 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2538 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1264 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2546 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1272 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2554 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1280 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1292 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2570 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1296 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2578 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1300 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1309 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2597 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1323 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1329 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1339 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1343 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2633 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1351 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1357 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2653 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1367 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 2661 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 2669 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1375 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 2677 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1387 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2685 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2693 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2701 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1403 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2709 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1411 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2719 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2729 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1435 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1445 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2766 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1456 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2802 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1488 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2810 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1492 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 2818 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1500 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 2826 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1504 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 2836 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1514 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2846 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1520 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2856 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1534 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2864 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1538 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 2873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1547 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1555 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2891 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2899 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1569 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1575 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2927 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1593 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2937 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1606 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1614 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2961 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2969 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2973 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -202;

  const short int Parser::yytable_ninf_ = -146;

  const short int
  Parser::yypact_[] =
  {
       5,  -202,     2,    27,   185,  -202,  -202,  1043,    -4,  -202,
    -202,  -202,  -202,  -202,    -8,     2,     2,     2,     2,     2,
     125,  -202,  -202,  -202,  -202,  -202,  -202,  -202,    -5,    -5,
      -5,  1043,    -5,  -202,  -202,  -202,  1043,  1043,  1043,   487,
     549,     3,     2,  -202,  -202,  -202,  -202,  -202,  -202,  1852,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,    11,   -23,    43,     2,  1105,  -202,    13,    15,    13,
       9,    -3,  -202,     2,    44,  -202,  -202,    24,    68,    76,
    1377,    80,  -202,  -202,  -202,    72,  1043,  1588,    74,  -202,
      35,  1621,  -202,  -202,     3,  1043,  1043,  1043,  1043,  1043,
    1043,  1043,  1043,  1043,  1043,  1043,  1043,  1043,  1043,  1043,
    1043,  1043,   611,  -202,     2,  -202,  -202,   487,  1654,    60,
      88,  -202,    94,     6,    83,   109,   -29,     3,   212,    37,
       3,  1043,  1043,  1043,  1043,  1043,  -202,  1687,  -202,  -202,
    -202,  1043,  1043,  -202,  -202,  -202,  -202,  -202,    32,  1887,
     305,  1881,   341,    95,    95,   851,   106,   106,    99,    99,
      99,  -202,   341,   851,   106,   106,   114,  -202,   -35,  1852,
    -202,   113,  1588,  1043,  1043,  1105,  -202,   122,     2,   -32,
      44,  -202,  -202,     3,     2,   943,     3,  -202,   112,   107,
    -202,     2,  -202,  1151,  1517,  1262,  1451,  1555,    11,  1852,
    1720,     3,  1043,  -202,  -202,  1043,  1852,  1852,  -202,  -202,
      69,  -202,    -1,   129,    17,  -202,   649,   690,  -202,    -5,
      -5,    -5,   943,    -6,  1043,  1043,   118,   724,   762,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,   110,  -202,   136,     3,     3,  -202,  1043,  1043,  1043,
    1043,  1043,  -202,  -202,   -38,   -21,   119,  -202,  1753,     2,
    -202,  1043,  -202,     2,   169,  -202,   796,   170,   834,   145,
     177,   178,  -202,  -202,  -202,  1414,  1484,   147,   868,   127,
     909,  1043,   943,  -202,   190,  1852,  1852,  1852,  1852,  1852,
       3,  -202,     3,  -202,  -202,  1852,  -202,  -202,  -202,  -202,
    -202,  -202,  1043,  1043,  1043,   943,   158,  -202,  -202,  -202,
    -202,  1852,  -202,   159,   200,  -202,   155,  1184,  1223,  1301,
     187,   425,  1043,   166,  -202,  -202,   943,   943,  1043,   943,
     943,   172,   173,   174,  -202,   981,  1786,  1819,  1105,  -202,
    -202,  1340,  -202,  -202,  -202,   943,   943,  -202,  -202,   943,
    -202,   176,   943,  -202,  -202,  -202,  -202,  -202
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,   167,   166,   183,     0,   180,
     181,   182,     1,     9,     0,     0,     0,     0,     0,     0,
       0,     6,     8,    10,    11,    12,    13,    19,     0,     0,
       0,     0,     0,   120,   122,   121,     0,     0,     0,     0,
       0,     0,     0,   126,   127,   123,   124,   125,   128,   184,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,   112,   113,   114,   115,   116,   117,   118,   119,
     171,   100,   168,     0,     0,   163,    20,   152,     0,   152,
       0,     0,     5,     0,   173,   176,   172,     0,     0,     0,
       0,     0,    98,    79,    80,     0,     0,     0,     0,   108,
       0,    64,   129,   169,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   101,     0,     3,   179,     0,   159,     0,
     162,   158,     0,     0,     0,     0,     0,   147,     0,     0,
       0,     0,     0,     0,     0,     0,    78,     0,    77,   110,
     109,     0,     0,    99,   132,   133,   134,   135,   136,    95,
      93,    94,    97,    81,    82,    88,    89,    90,    83,    84,
      85,    86,    96,    87,    91,    92,     0,   142,     0,    64,
     170,     0,    64,     0,     0,     0,    21,     0,     0,     0,
       0,   178,   149,     0,     0,     0,     0,   145,   146,     0,
       7,     0,   174,     0,     0,     0,     0,     0,     0,    63,
       0,   147,     0,   141,   140,     0,   160,   161,   157,   151,
       0,   150,     0,     0,     0,   165,     0,     0,    35,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    16,
      22,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    60,    62,     0,     0,     0,   175,     0,     0,     0,
       0,     0,   102,   111,     0,   131,     0,   139,    63,     0,
     148,     0,    14,     0,     0,    34,     0,     0,     0,     0,
       0,     0,    49,    59,    61,     0,     0,     0,     0,     0,
       0,     0,     0,   144,   154,   103,   106,   105,   104,   107,
       0,   137,     0,   143,   177,    15,   164,    57,    55,    33,
      53,    51,     0,     0,     0,     0,     0,    52,    50,    56,
      54,    58,    17,     0,   156,   130,     0,     0,     0,     0,
      36,     0,     0,     0,    18,   138,     0,     0,     0,     0,
       0,     0,     0,     0,    44,     0,     0,     0,   163,    45,
      46,     0,    48,    37,    39,     0,     0,    38,    43,     0,
     153,     0,     0,    40,    41,    42,   155,    47
  };

  const short int
  Parser::yypgoto_[] =
  {
    -202,  -202,  -202,  -202,   202,    91,  -202,  -202,  -202,  -202,
    -202,    77,  -201,  -202,  -202,  -202,  -119,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,   -74,    -7,  -202,  -202,
     -77,    66,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -115,
    -202,  -202,  -202,  -202,    22,  -202,  -202,    21,  -202,   156,
    -202,  -202,  -202,    49,  -112,  -202,    45,   -13,  -202,    36,
    -127,   -27,    18,   -15,   171,  -202,  -202
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    20,    21,    22,    23,    24,    25,    26,
      27,   275,   276,   240,   241,   242,   344,   345,   243,   244,
     245,   246,   247,   248,   249,   250,   100,   128,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,   264,   153,
     154,   155,   156,   157,   123,   129,   198,   199,   189,   134,
     324,   334,   130,   131,   132,   224,    70,    71,    72,    85,
      86,    87,   192,     8,     9,    10,    11
  };

  const short int
  Parser::yytable_[] =
  {
      49,    76,    88,    89,    81,    91,   191,   187,     1,     5,
     214,     5,     5,   221,   195,   300,     5,   301,   151,     5,
       5,   222,   197,     5,    90,   202,   278,    12,   102,    92,
      93,    94,    97,   101,   196,  -145,   288,   290,   236,   124,
      75,    83,  -145,    73,   138,   188,   125,     7,   178,    74,
      74,     2,   188,   181,    42,   122,    42,   133,   135,   137,
      77,    78,    79,    80,     7,    42,   272,   141,   139,     6,
     273,     6,     6,    84,    84,    84,     6,    84,   223,     6,
       6,   253,   150,     6,   201,   142,   211,   103,   151,   147,
      74,   158,   212,   143,   140,   191,   265,   145,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   179,   269,   146,   251,     7,
     182,   149,    74,   184,   158,    -2,    13,   158,     7,    14,
      15,    16,    17,    18,   203,   204,   205,   206,   207,   293,
     294,   185,   304,   186,   209,   210,   193,   109,   110,   251,
     251,   114,   115,   116,   117,   251,   283,   194,   117,   213,
     251,   251,   114,   115,   116,   117,   215,   219,   254,   180,
     255,    19,   271,   220,    96,   291,   216,   217,   190,   292,
     158,   307,   302,   158,   310,   325,    13,   326,   312,    14,
      15,    16,    17,    18,   313,   314,   317,   319,   158,   251,
     323,   251,   279,   280,   281,   267,   331,   332,   268,   333,
     335,   251,   340,   251,   348,   251,    14,    15,    16,    17,
      18,   354,    82,   355,   356,   366,   358,   285,   286,   200,
     262,    19,   266,     7,   218,   136,   361,   256,   251,   225,
     270,   158,   158,     0,     0,   126,    84,     0,     0,     0,
     295,   296,   297,   298,   299,     0,     0,     0,     0,   251,
     251,   252,   251,   251,   305,     0,     0,   190,     0,     0,
       0,     0,   239,     0,    84,    84,    84,     0,   251,   251,
       0,     0,   251,     0,   321,   251,     0,   158,     0,   158,
       0,     0,   252,   252,     0,     0,     0,     0,   252,   284,
       0,     0,     0,   252,   252,   327,   328,   329,     0,   282,
       0,     0,     0,     0,   190,     0,     0,     0,   306,     0,
       0,     0,     0,     0,   346,   347,     0,     0,     0,     0,
       0,   351,     0,     0,     0,     0,     0,     0,   346,     0,
       0,   105,   252,   107,   252,     0,   109,   110,   111,     0,
       0,     0,     0,   309,   252,   309,   252,     0,   252,   112,
     113,   114,   115,   116,   117,   309,     0,   309,     0,   322,
       0,   119,   120,   121,     0,     0,     0,   105,   106,   107,
       0,   252,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,   330,     0,     0,   112,   113,   114,   115,   116,
     117,     0,   252,   252,     0,   252,   252,   119,   120,   121,
       0,     0,     0,   349,   350,     0,   352,   353,     0,     0,
       0,   252,   252,     0,     0,   252,   341,     0,   252,     0,
       0,     0,   363,   364,     0,     0,   365,     0,     0,   367,
       0,    28,     5,    29,    30,     0,     0,     0,    31,     0,
       0,     0,     0,   342,     0,    32,     0,     0,    33,    34,
      35,     0,     0,     0,     0,    36,    37,    38,     0,    39,
       0,    40,     0,     0,     0,     0,   343,    41,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    95,     0,
       0,     0,     0,     0,     0,     0,    43,    44,    45,    46,
      47,    48,     6,    28,     5,    29,    30,     0,     0,     0,
      31,     0,     0,     0,     0,     0,     0,    32,     0,     0,
      33,    34,    35,     0,     0,     0,     0,    36,    37,    38,
       0,    39,     0,    40,     0,     0,     0,     0,     0,    41,
       0,     0,     0,    96,     0,     0,     0,     0,     0,    42,
      98,     0,     0,     0,     0,     0,     0,     0,    43,    44,
      45,    46,    47,    48,     6,    28,     5,    29,    30,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,    32,
       0,     0,    33,    34,    35,     0,     0,     0,     0,    36,
      37,    38,     0,    39,     0,    40,    99,     0,     0,     0,
       0,    41,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,   176,     0,     0,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48,     6,    28,     5,    29,
      30,     0,     0,     0,    31,     0,     0,     0,     0,     0,
       0,    32,     0,     0,    33,    34,    35,     0,     0,     0,
     274,    36,    37,    38,     0,    39,   177,    40,     0,     0,
     226,     0,   227,    41,   228,   229,     5,   230,   231,   232,
       0,   233,   234,    42,     0,   235,     0,     0,     0,     0,
       0,     0,    43,    44,    45,    46,    47,    48,     6,     0,
       0,   277,     0,   236,     0,     0,     0,   237,     0,     0,
       0,   226,     0,   227,     0,   228,   229,     5,   230,   231,
     232,    42,   233,   234,     0,     0,   235,     0,   238,     0,
       0,     0,     0,     0,     0,   287,     6,     0,     0,     0,
       0,     0,     0,     0,   236,   226,     0,   227,   237,   228,
     229,     5,   230,   231,   232,     0,   233,   234,     0,     0,
     235,     0,    42,     0,     0,     0,     0,     0,     0,   238,
       0,     0,     0,   289,     0,     0,     0,     6,   236,     0,
       0,     0,   237,   226,     0,   227,     0,   228,   229,     5,
     230,   231,   232,     0,   233,   234,    42,     0,   235,     0,
       0,     0,     0,   238,     0,     0,     0,     0,     0,     0,
       0,     6,     0,     0,     0,     0,   236,   226,   308,   227,
     237,   228,   229,     5,   230,   231,   232,     0,   233,   234,
       0,     0,   235,     0,    42,     0,     0,     0,     0,     0,
       0,   238,     0,     0,     0,     0,     0,     0,     0,     6,
     236,     0,     0,     0,   237,   226,     0,   227,   311,   228,
     229,     5,   230,   231,   232,     0,   233,   234,    42,     0,
     235,     0,     0,     0,     0,   238,     0,     0,     0,     0,
       0,     0,     0,     6,     0,     0,     0,     0,   236,   226,
       0,   227,   237,   228,   229,     5,   230,   231,   232,     0,
     233,   234,   109,   110,   235,     0,    42,     0,     0,     0,
       0,     0,     0,   238,     0,   112,   113,   114,   115,   116,
     117,     6,   236,     0,     0,     0,   237,   318,   120,   121,
     226,     0,   227,     0,   228,   229,     5,   230,   231,   232,
      42,   233,   234,     0,     0,   235,     0,   238,     0,     0,
       0,     0,     0,     0,     0,     6,     0,     0,     0,     0,
       0,     0,     0,   236,   226,     0,   227,   237,   228,   229,
       5,   230,   231,   232,     0,   233,   234,     0,     0,   235,
       0,    42,     0,     0,     0,     0,     0,     0,   238,   320,
       0,     0,     0,     0,     0,     0,     6,   236,     0,     0,
       0,   237,     0,     0,     0,     0,     0,    28,     5,    29,
      30,     0,     0,     0,    31,    42,     0,     0,     0,   342,
       0,    32,   238,     0,    33,    34,    35,     0,     0,     0,
       6,    36,    37,    38,     0,    39,     0,    40,     0,     0,
     357,     0,   343,    41,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    42,     0,     0,     0,     0,     0,     0,
       0,     0,    43,    44,    45,    46,    47,    48,     6,    28,
       5,    29,    30,     0,     0,     0,    31,     0,     0,     0,
       0,     0,     0,    32,     0,     0,    33,    34,    35,     0,
       0,     0,     0,    36,    37,    38,     0,    39,     0,    40,
       0,     0,     0,     0,     0,    41,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,     0,     0,     0,     0,
       0,     0,     0,     0,    43,    44,    45,    46,    47,    48,
       6,    28,     5,    29,    30,     0,     0,     0,    31,     0,
       0,     0,     0,     0,     0,    32,     0,     0,    33,    34,
      35,     0,     0,     0,     0,    36,    37,    38,     0,   127,
       0,    40,     0,     0,     0,     0,     0,    41,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,   257,     0,
       0,     0,     0,     0,     0,     0,    43,    44,    45,    46,
      47,    48,     6,   104,     0,     0,     0,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,   336,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,     0,     0,     0,   118,   104,   119,   120,   121,
     105,   106,   107,   108,     0,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   113,
     114,   115,   116,   117,   337,     0,     0,     0,   118,     0,
     119,   120,   121,     0,   338,   104,     0,     0,     0,   105,
     106,   107,   108,     0,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   113,   114,
     115,   116,   117,   259,     0,     0,     0,   118,     0,   119,
     120,   121,     0,     0,   104,     0,     0,     0,   105,   106,
     107,   108,     0,   109,   110,   111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   113,   114,   115,
     116,   117,   339,     0,     0,     0,   118,     0,   119,   120,
     121,     0,     0,   104,     0,     0,     0,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,   362,     0,     0,     0,   118,     0,   119,   120,   121,
       0,     0,   104,     0,     0,     0,   105,   106,   107,   108,
       0,   109,   110,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   112,   113,   114,   115,   116,   117,
       0,   144,     0,     0,   118,     0,   119,   120,   121,   104,
       0,     0,     0,   105,   106,   107,   108,     0,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,   114,   115,   116,   117,     0,   315,     0,
       0,   118,     0,   119,   120,   121,   104,     0,     0,     0,
     105,   106,   107,   108,     0,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   113,
     114,   115,   116,   117,     0,     0,   260,     0,   118,     0,
     119,   120,   121,   104,     0,     0,     0,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,   316,     0,     0,     0,   118,   104,   119,   120,   121,
     105,   106,   107,   108,     0,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   113,
     114,   115,   116,   117,     0,     0,   258,     0,   118,   104,
     119,   120,   121,   105,   106,   107,   108,     0,   109,   110,
     111,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,   114,   115,   116,   117,     0,     0,     0,
       0,   118,     0,   119,   120,   121,   261,   104,     0,     0,
       0,   105,   106,   107,   108,     0,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   112,
     113,   114,   115,   116,   117,     0,     0,     0,     0,   118,
     104,   119,   120,   121,   105,   106,   107,   108,     0,   109,
     110,   111,     0,   148,     0,     0,     0,     0,     0,     0,
       0,     0,   112,   113,   114,   115,   116,   117,     0,     0,
       0,     0,   118,   104,   119,   120,   121,   105,   106,   107,
     108,     0,   109,   110,   111,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,     0,   152,     0,     0,   118,   104,   119,   120,   121,
     105,   106,   107,   108,     0,   109,   110,   111,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   112,   113,
     114,   115,   116,   117,     0,     0,     0,   183,   118,   104,
     119,   120,   121,   105,   106,   107,   108,     0,   109,   110,
     111,     0,   208,     0,     0,     0,     0,     0,     0,     0,
       0,   112,   113,   114,   115,   116,   117,     0,     0,     0,
       0,   118,   104,   119,   120,   121,   105,   106,   107,   108,
       0,   109,   110,   111,     0,     0,     0,   263,     0,     0,
       0,     0,     0,     0,   112,   113,   114,   115,   116,   117,
       0,     0,     0,     0,   118,   104,   119,   120,   121,   105,
     106,   107,   108,     0,   109,   110,   111,     0,   303,     0,
       0,     0,     0,     0,     0,     0,     0,   112,   113,   114,
     115,   116,   117,     0,     0,     0,     0,   118,   104,   119,
     120,   121,   105,   106,   107,   108,     0,   109,   110,   111,
       0,     0,     0,     0,     0,     0,   359,     0,     0,     0,
     112,   113,   114,   115,   116,   117,     0,     0,     0,     0,
     118,   104,   119,   120,   121,   105,   106,   107,   108,     0,
     109,   110,   111,     0,     0,     0,     0,     0,   360,     0,
       0,     0,     0,   112,   113,   114,   115,   116,   117,     0,
       0,     0,     0,   118,   104,   119,   120,   121,   105,   106,
     107,   108,     0,   109,   110,   111,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   112,   113,   114,   115,
     116,   117,     0,     0,     0,     0,   118,   105,   119,   120,
     121,     0,   109,   110,   111,     0,     0,     0,   109,   110,
     111,     0,     0,     0,     0,   112,   113,   114,   115,   116,
     117,   112,   113,   114,   115,   116,   117,   119,   120,   121,
       0,     0,     0,   119,   120,   121
  };

  const short int
  Parser::yycheck_[] =
  {
       7,    14,    29,    30,    19,    32,   133,     1,     3,    17,
      45,    17,    17,    45,    43,    53,    17,    55,    53,    17,
      17,    53,   137,    17,    31,   140,   227,     0,    41,    36,
      37,    38,    39,    40,    63,    56,   237,   238,    44,    62,
      48,    46,    63,    47,    47,    46,     3,     2,   122,    53,
      53,    46,    46,   127,    62,    44,    62,    44,    43,    50,
      15,    16,    17,    18,    19,    62,    49,    43,    83,    77,
      53,    77,    77,    28,    29,    30,    77,    32,   193,    77,
      77,   196,    47,    77,    47,    17,    54,    42,    53,    96,
      53,   104,    60,    17,    50,   222,   211,    17,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,    47,    45,   195,    74,
     127,    47,    53,    63,   137,     0,     1,   140,    83,     4,
       5,     6,     7,     8,   141,   142,   143,   144,   145,   254,
     255,    53,   269,    49,   151,   152,    63,    41,    42,   226,
     227,    56,    57,    58,    59,   232,   233,    48,    59,    45,
     237,   238,    56,    57,    58,    59,    53,    45,    56,   124,
      63,    46,    43,   188,    56,    65,   183,   184,   133,    43,
     193,    12,    63,   196,    14,   300,     1,   302,    43,     4,
       5,     6,     7,     8,    17,    17,    49,    70,   211,   276,
      10,   278,   229,   230,   231,   212,    48,    48,   215,     9,
      55,   288,    25,   290,    48,   292,     4,     5,     6,     7,
       8,    49,    20,    50,    50,    49,   345,   234,   235,   138,
     208,    46,   211,   188,   185,    79,   348,   201,   315,   194,
     222,   254,   255,    -1,    -1,    74,   201,    -1,    -1,    -1,
     257,   258,   259,   260,   261,    -1,    -1,    -1,    -1,   336,
     337,   195,   339,   340,   271,    -1,    -1,   222,    -1,    -1,
      -1,    -1,   195,    -1,   229,   230,   231,    -1,   355,   356,
      -1,    -1,   359,    -1,   291,   362,    -1,   300,    -1,   302,
      -1,    -1,   226,   227,    -1,    -1,    -1,    -1,   232,   233,
      -1,    -1,    -1,   237,   238,   312,   313,   314,    -1,   232,
      -1,    -1,    -1,    -1,   269,    -1,    -1,    -1,   273,    -1,
      -1,    -1,    -1,    -1,   331,   332,    -1,    -1,    -1,    -1,
      -1,   338,    -1,    -1,    -1,    -1,    -1,    -1,   345,    -1,
      -1,    36,   276,    38,   278,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,   276,   288,   278,   290,    -1,   292,    54,
      55,    56,    57,    58,    59,   288,    -1,   290,    -1,   292,
      -1,    66,    67,    68,    -1,    -1,    -1,    36,    37,    38,
      -1,   315,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   315,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,   336,   337,    -1,   339,   340,    66,    67,    68,
      -1,    -1,    -1,   336,   337,    -1,   339,   340,    -1,    -1,
      -1,   355,   356,    -1,    -1,   359,     1,    -1,   362,    -1,
      -1,    -1,   355,   356,    -1,    -1,   359,    -1,    -1,   362,
      -1,    16,    17,    18,    19,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    28,    -1,    30,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      -1,    46,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    16,    17,    18,    19,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    62,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    16,    17,    18,    19,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77,    16,    17,    18,
      19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    -1,    33,    34,    35,    -1,    -1,    -1,
       1,    40,    41,    42,    -1,    44,    45,    46,    -1,    -1,
      11,    -1,    13,    52,    15,    16,    17,    18,    19,    20,
      -1,    22,    23,    62,    -1,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    -1,
      -1,     1,    -1,    44,    -1,    -1,    -1,    48,    -1,    -1,
      -1,    11,    -1,    13,    -1,    15,    16,    17,    18,    19,
      20,    62,    22,    23,    -1,    -1,    26,    -1,    69,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    77,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,    11,    -1,    13,    48,    15,
      16,    17,    18,    19,    20,    -1,    22,    23,    -1,    -1,
      26,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,     1,    -1,    -1,    -1,    77,    44,    -1,
      -1,    -1,    48,    11,    -1,    13,    -1,    15,    16,    17,
      18,    19,    20,    -1,    22,    23,    62,    -1,    26,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    -1,    44,    11,    12,    13,
      48,    15,    16,    17,    18,    19,    20,    -1,    22,    23,
      -1,    -1,    26,    -1,    62,    -1,    -1,    -1,    -1,    -1,
      -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,
      44,    -1,    -1,    -1,    48,    11,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    -1,    22,    23,    62,    -1,
      26,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,    44,    11,
      -1,    13,    48,    15,    16,    17,    18,    19,    20,    -1,
      22,    23,    41,    42,    26,    -1,    62,    -1,    -1,    -1,
      -1,    -1,    -1,    69,    -1,    54,    55,    56,    57,    58,
      59,    77,    44,    -1,    -1,    -1,    48,    49,    67,    68,
      11,    -1,    13,    -1,    15,    16,    17,    18,    19,    20,
      62,    22,    23,    -1,    -1,    26,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    44,    11,    -1,    13,    48,    15,    16,
      17,    18,    19,    20,    -1,    22,    23,    -1,    -1,    26,
      -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,    69,    70,
      -1,    -1,    -1,    -1,    -1,    -1,    77,    44,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    16,    17,    18,
      19,    -1,    -1,    -1,    23,    62,    -1,    -1,    -1,    28,
      -1,    30,    69,    -1,    33,    34,    35,    -1,    -1,    -1,
      77,    40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,
      49,    -1,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    16,
      17,    18,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    -1,    33,    34,    35,    -1,
      -1,    -1,    -1,    40,    41,    42,    -1,    44,    -1,    46,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      77,    16,    17,    18,    19,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    17,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    64,    32,    66,    67,    68,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    21,    -1,    -1,    -1,    64,    -1,
      66,    67,    68,    -1,    31,    32,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    21,    -1,    -1,    -1,    64,    -1,    66,
      67,    68,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    21,    -1,    -1,    -1,    64,    -1,    66,    67,
      68,    -1,    -1,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    21,    -1,    -1,    -1,    64,    -1,    66,    67,    68,
      -1,    -1,    32,    -1,    -1,    -1,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    24,    -1,    -1,    64,    -1,    66,    67,    68,    32,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    24,    -1,
      -1,    64,    -1,    66,    67,    68,    32,    -1,    -1,    -1,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    25,    -1,    64,    -1,
      66,    67,    68,    32,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    27,    -1,    -1,    -1,    64,    32,    66,    67,    68,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    29,    -1,    64,    32,
      66,    67,    68,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    64,    -1,    66,    67,    68,    31,    32,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    64,
      32,    66,    67,    68,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    64,    32,    66,    67,    68,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    61,    -1,    -1,    64,    32,    66,    67,    68,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    63,    64,    32,
      66,    67,    68,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    64,    32,    66,    67,    68,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    64,    32,    66,    67,    68,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    64,    32,    66,
      67,    68,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      64,    32,    66,    67,    68,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    49,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    64,    32,    66,    67,    68,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    -1,    64,    36,    66,    67,
      68,    -1,    41,    42,    43,    -1,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    54,    55,    56,    57,    58,    59,    66,    67,    68,
      -1,    -1,    -1,    66,    67,    68
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    46,    83,    84,    17,    77,   148,   155,   156,
     157,   158,     0,     1,     4,     5,     6,     7,     8,    46,
      85,    86,    87,    88,    89,    90,    91,    92,    16,    18,
      19,    23,    30,    33,    34,    35,    40,    41,    42,    44,
      46,    52,    62,    71,    72,    73,    74,    75,    76,   109,
     110,   111,   112,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     148,   149,   150,    47,    53,    48,   149,   148,   148,   148,
     148,   155,    86,    46,   148,   151,   152,   153,   153,   153,
     109,   153,   109,   109,   109,     1,    56,   109,     1,    47,
     108,   109,   149,   148,    32,    36,    37,    38,    39,    41,
      42,    43,    54,    55,    56,    57,    58,    59,    64,    66,
      67,    68,    44,   136,    62,     3,   156,    44,   109,   137,
     144,   145,   146,    44,   141,    43,   141,    50,    47,   155,
      50,    43,    17,    17,    24,    17,    45,   109,    45,    47,
      47,    53,    61,   131,   132,   133,   134,   135,   149,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,     1,    45,   108,   109,
     148,   108,   109,    63,    63,    53,    49,     1,    46,   140,
     148,   152,   154,    63,    48,    43,    63,   131,   138,   139,
      87,    47,   131,   109,   109,   109,   109,   109,    45,   109,
     109,    54,    60,    45,    45,    53,   109,   109,   145,    45,
     155,    45,    53,   131,   147,   148,    11,    13,    15,    16,
      18,    19,    20,    22,    23,    26,    44,    48,    69,    93,
      95,    96,    97,   100,   101,   102,   103,   104,   105,   106,
     107,   112,   113,   131,    56,    63,   151,    17,    29,    21,
      25,    31,   136,    47,   130,   131,   139,   109,   109,    47,
     154,    43,    49,    53,     1,    93,    94,     1,    94,   153,
     153,   153,    93,   112,   113,   109,   109,     1,    94,     1,
      94,    65,    43,   131,   131,   109,   109,   109,   109,   109,
      53,    55,    63,    45,   152,   109,   148,    12,    12,    93,
      14,    14,    43,    17,    17,    24,    27,    49,    49,    70,
      70,   109,    93,    10,   142,   131,   131,   109,   109,   109,
      93,    48,    48,     9,   143,    55,    17,    21,    31,    21,
      25,     1,    28,    51,    98,    99,   109,   109,    48,    93,
      93,   109,    93,    93,    49,    50,    50,    49,    98,    50,
      49,   146,    21,    93,    93,    93,    49,    93
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    82,    83,    84,    84,    85,    85,    86,    86,    86,
      87,    87,    87,    87,    88,    89,    90,    90,    91,    91,
      92,    92,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    94,    94,    95,    96,    96,    97,    97,
      98,    98,    98,    99,    99,   100,   101,   101,   102,   103,
     104,   104,   104,   104,   105,   105,   105,   105,   106,   107,
     107,   107,   107,   108,   108,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   111,
     112,   112,   113,   114,   115,   116,   117,   118,   119,   119,
     119,   120,   121,   121,   121,   121,   121,   121,   121,   121,
     122,   123,   123,   124,   125,   126,   127,   127,   128,   129,
     130,   130,   131,   131,   131,   131,   132,   133,   134,   135,
     136,   136,   136,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   141,   142,   142,   143,   143,   144,   144,   145,
     145,   145,   146,   146,   147,   147,   148,   148,   149,   149,
     150,   150,   151,   151,   152,   153,   153,   154,   154,   155,
     155,   156,   156,   157,   158
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     4,     1,     2,     1,     4,     1,     1,
       1,     1,     1,     1,     6,     7,     5,     7,     8,     1,
       2,     4,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     4,     6,     6,     6,
       3,     3,     3,     2,     1,     6,     6,     8,     6,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       1,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     3,
       1,     2,     5,     6,     6,     6,     6,     6,     2,     3,
       3,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       3,     1,     1,     1,     1,     1,     1,     4,     6,     3,
       3,     3,     2,     5,     3,     1,     1,     0,     3,     1,
       3,     3,     0,     4,     0,     4,     0,     3,     1,     1,
       3,     3,     1,     0,     3,     1,     1,     1,     1,     2,
       3,     1,     1,     1,     3,     4,     1,     4,     1,     3,
       1,     1,     1,     1,     2
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
  "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"",
  "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"", "\"=>\"",
  "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"decimal\"",
  "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header", "Definitions",
  "AttributedDefinition", "Definition", "EnumerationDefinition",
  "DerivedDefinition", "RuleDefinition", "FunctionDefinition",
  "ProgramFunctionDefinition", "Rule", "Rules", "SkipRule",
  "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels", "LetRule",
  "ForallRule", "ChooseRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", "Terms", "Term", "Expression",
  "TypeCastingExpression", "DirectCallExpression",
  "IndirectCallExpression", "LetExpression", "ConditionalExpression",
  "ChooseExpression", "UniversalQuantifierExpression",
  "ExistentialQuantifierExpression", "List", "Range", "Literal",
  "UndefinedLiteral", "BooleanLiteral", "IntegerLiteral",
  "RationalLiteral", "DecimalLiteral", "BitLiteral", "StringLiteral",
  "ReferenceLiteral", "Types", "Type", "BasicType", "ComposedType",
  "RelationType", "FixedSizedType", "Arguments", "TwoOrMoreArguments",
  "FunctionParameters", "MaybeFunctionParameters", "Parameters",
  "MaybeParameters", "MaybeDefined", "MaybeInitially", "Initializers",
  "Initializer", "MaybeInitializers", "Identifiers", "Identifier",
  "IdentifierPath", "DotSeparatedIdentifiers", "Variable", "TypedVariable",
  "AttributedVariable", "TypedAttributedVariable", "Attributes",
  "Attribute", "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   377,   377,   386,   392,   400,   406,   416,   422,   426,
     434,   438,   442,   446,   454,   462,   470,   475,   484,   500,
     508,   531,   553,   557,   561,   565,   569,   573,   577,   581,
     585,   589,   593,   601,   607,   617,   625,   629,   637,   641,
     649,   653,   657,   665,   671,   681,   689,   693,   701,   709,
     717,   721,   725,   730,   739,   743,   747,   752,   761,   771,
     775,   779,   783,   795,   801,   811,   815,   819,   823,   827,
     831,   835,   839,   843,   847,   851,   855,   867,   871,   875,
     879,   883,   887,   891,   895,   899,   903,   907,   911,   915,
     919,   923,   927,   931,   935,   939,   943,   947,   951,   959,
     967,   972,   980,   988,   996,  1004,  1012,  1020,  1028,  1033,
    1037,  1045,  1057,  1061,  1065,  1069,  1073,  1077,  1081,  1085,
    1093,  1101,  1106,  1115,  1131,  1147,  1163,  1175,  1191,  1207,
    1219,  1225,  1235,  1239,  1243,  1247,  1255,  1263,  1271,  1279,
    1291,  1295,  1299,  1308,  1322,  1328,  1338,  1342,  1350,  1356,
    1366,  1370,  1374,  1386,  1390,  1398,  1402,  1410,  1416,  1426,
    1434,  1444,  1455,  1459,  1471,  1477,  1487,  1491,  1499,  1503,
    1513,  1519,  1533,  1537,  1546,  1554,  1560,  1568,  1574,  1586,
    1592,  1601,  1605,  1613,  1621
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
#line 3935 "GrammarParser.cpp" // lalr1.cc:1167
#line 1627 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
