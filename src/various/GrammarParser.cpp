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
      case 154: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 153: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 155: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 130: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 103: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 106: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 97: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 96: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 98: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 114: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 101: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 131: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 113: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 95: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 85: // AttributedDefinition
      case 86: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 84: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 88: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 110: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 87: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 116: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 108: // Term
      case 109: // Expression
      case 119: // Literal
      case 140: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 156: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 107: // Terms
      case 134: // Arguments
      case 135: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 133: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 100: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 90: // FunctionDefinition
      case 91: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 83: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 146: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 147: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 145: // Identifiers
      case 148: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 111: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 102: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 112: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 99: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 117: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 141: // MaybeInitially
      case 142: // Initializers
      case 144: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 138: // Parameters
      case 139: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 118: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 127: // ReferenceLiteral
        value.move< ReferenceAtom::Ptr > (that.value);
        break;

      case 132: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 92: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 89: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 93: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 104: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 94: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 128: // Types
      case 136: // FunctionParameters
      case 137: // MaybeFunctionParameters
        value.move< Types::Ptr > (that.value);
        break;

      case 120: // UndefinedLiteral
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 115: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 105: // UpdateRule
      case 143: // Initializer
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 121: // BooleanLiteral
      case 122: // IntegerLiteral
      case 123: // RationalLiteral
      case 124: // DecimalLiteral
      case 125: // BitLiteral
      case 126: // StringLiteral
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 149: // Variable
      case 150: // TypedVariable
      case 151: // AttributedVariable
      case 152: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 129: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 70: // "binary"
      case 71: // "hexadecimal"
      case 72: // "integer"
      case 73: // "rational"
      case 74: // "decimal"
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
      case 154: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 153: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 155: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 130: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 103: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 106: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 97: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 96: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 98: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 114: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 101: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 131: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 113: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 95: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 85: // AttributedDefinition
      case 86: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 84: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 88: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 110: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 87: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 116: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 108: // Term
      case 109: // Expression
      case 119: // Literal
      case 140: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 156: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 107: // Terms
      case 134: // Arguments
      case 135: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 133: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 100: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 90: // FunctionDefinition
      case 91: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 83: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 146: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 147: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 145: // Identifiers
      case 148: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 111: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 102: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 112: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 99: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 117: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 141: // MaybeInitially
      case 142: // Initializers
      case 144: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 138: // Parameters
      case 139: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 118: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 127: // ReferenceLiteral
        value.copy< ReferenceAtom::Ptr > (that.value);
        break;

      case 132: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 92: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 89: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 93: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 104: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 94: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 128: // Types
      case 136: // FunctionParameters
      case 137: // MaybeFunctionParameters
        value.copy< Types::Ptr > (that.value);
        break;

      case 120: // UndefinedLiteral
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 115: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 105: // UpdateRule
      case 143: // Initializer
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 121: // BooleanLiteral
      case 122: // IntegerLiteral
      case 123: // RationalLiteral
      case 124: // DecimalLiteral
      case 125: // BitLiteral
      case 126: // StringLiteral
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 149: // Variable
      case 150: // TypedVariable
      case 151: // AttributedVariable
      case 152: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 129: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (that.value);
        break;

      case 70: // "binary"
      case 71: // "hexadecimal"
      case 72: // "integer"
      case 73: // "rational"
      case 74: // "decimal"
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
      case 154: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 153: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 155: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 130: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 103: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 106: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 97: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 96: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 98: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 114: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 101: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 131: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 113: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 95: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 85: // AttributedDefinition
      case 86: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 84: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 88: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 110: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 87: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 116: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 108: // Term
      case 109: // Expression
      case 119: // Literal
      case 140: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 156: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 107: // Terms
      case 134: // Arguments
      case 135: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 133: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 100: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 90: // FunctionDefinition
      case 91: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 83: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 146: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 147: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 145: // Identifiers
      case 148: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 111: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 102: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 112: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 99: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 117: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 141: // MaybeInitially
      case 142: // Initializers
      case 144: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 138: // Parameters
      case 139: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 118: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 127: // ReferenceLiteral
        yylhs.value.build< ReferenceAtom::Ptr > ();
        break;

      case 132: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 92: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 89: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 93: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 104: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 94: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 82: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 128: // Types
      case 136: // FunctionParameters
      case 137: // MaybeFunctionParameters
        yylhs.value.build< Types::Ptr > ();
        break;

      case 120: // UndefinedLiteral
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 115: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 105: // UpdateRule
      case 143: // Initializer
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 121: // BooleanLiteral
      case 122: // IntegerLiteral
      case 123: // RationalLiteral
      case 124: // DecimalLiteral
      case 125: // BitLiteral
      case 126: // StringLiteral
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 149: // Variable
      case 150: // TypedVariable
      case 151: // AttributedVariable
      case 152: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 129: // Type
        yylhs.value.build< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 70: // "binary"
      case 71: // "hexadecimal"
      case 72: // "integer"
      case 73: // "rational"
      case 74: // "decimal"
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
#line 373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< Definitions::Ptr > ()->add( yystack_[0].value.as< Definitions::Ptr > ()->begin(), yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1329 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1339 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1347 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 402 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1377 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 418 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1385 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1417 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Identifiers::Ptr > () );
  }
#line 1433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 471 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1479 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 496 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 504 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1514 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 527 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1532 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 549 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1540 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1548 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 557 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1556 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1564 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 565 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1572 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 569 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 585 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1612 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1620 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 597 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1630 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 603 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1640 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 613 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1648 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 621 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1656 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 625 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1664 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 633 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1672 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 637 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1680 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 645 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1688 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 649 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1696 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 653 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1704 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 661 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1714 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 667 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1724 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1732 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 685 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 689 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 697 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 713 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 717 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1780 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 721 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1798 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1806 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 739 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1814 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 743 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1823 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1832 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1842 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 767 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1852 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 773 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1863 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 786 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 1884 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 807 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1904 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1912 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 821 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1920 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 1928 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 829 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1936 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 833 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 1944 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 837 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1952 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 841 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1960 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 845 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1968 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 849 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 853 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 857 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 869 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2000 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 873 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2008 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 877 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2016 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 881 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2024 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 885 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2032 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 889 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2040 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 893 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2048 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 897 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2056 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 901 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2064 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 905 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2072 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 909 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2080 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 913 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2088 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 917 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2096 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 921 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2104 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 925 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2112 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 929 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2120 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 933 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2128 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 937 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2136 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 941 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2144 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 961 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2177 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2193 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2201 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2225 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2233 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1029 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2250 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1033 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2258 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1041 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 2274 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1057 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1061 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1065 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2298 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1069 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1073 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1077 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2322 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1081 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 2330 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1089 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1097 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2347 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1102 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2356 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1111 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2372 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1127 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2404 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1159 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2420 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1171 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2436 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2452 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1203 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2470 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1221 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2480 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1231 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2488 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1235 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2496 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1239 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1243 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2512 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1251 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2520 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1259 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2528 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1267 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1275 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1287 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2552 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1291 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2560 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1295 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1304 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1318 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2589 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1324 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1334 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1338 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1352 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2635 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1362 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 2643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 2651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 2659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1386 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1394 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2701 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2711 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1451 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1467 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1473 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2784 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1483 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1487 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 2800 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1495 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 2808 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 2818 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2828 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1515 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2838 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1529 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2846 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1533 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 2855 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1542 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2863 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1550 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1556 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1564 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2891 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2899 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1582 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1588 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2919 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1597 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2927 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1601 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2935 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2943 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2951 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2955 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -215;

  const short int Parser::yytable_ninf_ = -144;

  const short int
  Parser::yypact_[] =
  {
      14,  -215,     3,    36,    41,  -215,  -215,  1028,    35,  -215,
    -215,  -215,  -215,  -215,    -6,     3,     3,     3,     3,     3,
     188,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    -2,    -2,
      -2,  1028,    -2,  -215,  -215,  -215,  1028,  1028,  1028,   548,
     609,    -4,     3,  -215,  -215,  -215,  -215,  -215,  -215,  1801,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
       9,   -24,    57,     3,  1089,  -215,    26,    -3,    26,    33,
      37,  -215,     3,    44,  -215,  -215,    52,    78,   102,  1336,
     107,  -215,  -215,  -215,    82,  1028,  1537,    81,  -215,    39,
    1570,  -215,  -215,  1028,  1028,  1028,  1028,  1028,  1028,  1028,
    1028,  1028,  1028,  1028,  1028,  1028,  1028,  1028,  1028,  1028,
     670,  -215,     3,  -215,  -215,   548,  1603,    66,    79,  -215,
      91,     8,    89,    94,   -35,    -4,   141,    68,    -4,  1028,
    1028,  1028,  1028,  1028,  -215,  1636,  -215,  -215,  -215,  1028,
    1028,   213,  1867,   318,  1834,   153,   153,  1919,   161,   161,
      95,    95,    95,  -215,  1834,  1919,   161,   161,   116,  -215,
     -30,  1801,  -215,   111,  1537,  1028,  1028,  1089,  -215,   120,
       3,   -18,    44,  -215,  -215,    -4,     3,   935,    -4,  -215,
    -215,  -215,  -215,  -215,   112,   104,    70,  -215,     3,  -215,
    1116,  1471,  1225,  1405,  1504,     9,  1801,  1669,  -215,  -215,
    1028,  1801,  1801,  -215,  -215,    92,  -215,    -1,   131,    10,
    -215,   139,   707,  -215,    -2,    -2,    -2,   935,    -5,  1028,
    1028,   119,   747,   784,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,   113,  -215,   136,    -4,
      -4,    -4,  1028,  -215,  1028,  1028,  1028,  1028,  1028,  -215,
    -215,  1702,     3,  -215,  1028,  -215,     3,   164,  -215,   821,
     166,   416,   142,   173,   174,  -215,  -215,  -215,  1371,  1438,
     133,   858,   114,   898,  1028,   935,  -215,   194,   -31,     6,
     144,  1900,  1801,  1801,  1801,  1801,  1801,  -215,  -215,  1801,
    -215,  -215,  -215,  -215,  -215,  -215,  1028,  1028,  1028,   935,
     158,  -215,  -215,  -215,  -215,  1801,  -215,   165,   204,    -4,
    -215,    -4,  1149,  1187,  1263,   189,   487,  1028,   177,  -215,
    -215,   167,   935,   935,  1028,   935,   935,   172,   176,   178,
    -215,   967,  1735,  1768,  1089,  -215,  -215,  -215,  1301,  -215,
    -215,  -215,   935,   935,  -215,  -215,   935,  -215,   181,   935,
    -215,  -215,  -215,  -215,  -215
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,   165,   164,   181,     0,   178,
     179,   180,     1,     9,     0,     0,     0,     0,     0,     0,
       0,     6,     8,    10,    11,    12,    13,    19,     0,     0,
       0,     0,     0,   118,   120,   119,     0,     0,     0,     0,
       0,     0,     0,   124,   125,   121,   122,   123,   126,   182,
      72,    65,    66,    67,    68,    69,    70,    71,    73,    74,
      75,   110,   111,   112,   113,   114,   115,   116,   117,   169,
      98,   166,     0,     0,   161,    20,   150,     0,   150,     0,
       0,     5,     0,   171,   174,   170,     0,     0,     0,     0,
       0,    97,    78,    79,     0,     0,     0,     0,   106,     0,
      64,   127,   167,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    99,     0,     3,   177,     0,   157,     0,   160,   156,
       0,     0,     0,     0,     0,   145,     0,     0,     0,     0,
       0,     0,     0,     0,    77,     0,    76,   108,   107,     0,
       0,    94,    92,    93,    96,    80,    81,    87,    88,    89,
      82,    83,    84,    85,    95,    86,    90,    91,     0,   140,
       0,    64,   168,     0,    64,     0,     0,     0,    21,     0,
       0,     0,     0,   176,   147,     0,     0,     0,     0,   143,
     130,   131,   132,   133,   144,     0,   134,     7,     0,   172,
       0,     0,     0,     0,     0,     0,    63,     0,   139,   138,
       0,   158,   159,   155,   149,     0,   148,     0,     0,     0,
     163,     0,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    60,    62,     0,     0,
       0,   145,     0,   173,     0,     0,     0,     0,     0,   100,
     109,    63,     0,   146,     0,    14,     0,     0,    34,     0,
       0,     0,     0,     0,     0,    49,    59,    61,     0,     0,
       0,     0,     0,     0,     0,     0,   142,   152,     0,   129,
       0,   137,   101,   104,   103,   102,   105,   141,   175,    15,
     162,    57,    55,    33,    53,    51,     0,     0,     0,     0,
       0,    52,    50,    56,    54,    58,    17,     0,   154,     0,
     135,     0,     0,     0,     0,    36,     0,     0,     0,    18,
     128,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      44,     0,     0,     0,   161,   136,    45,    46,     0,    48,
      37,    39,     0,     0,    38,    43,     0,   151,     0,     0,
      40,    41,    42,   153,    47
  };

  const short int
  Parser::yypgoto_[] =
  {
    -215,  -215,  -215,  -215,   206,    96,  -215,  -215,  -215,  -215,
    -215,   143,  -214,  -215,  -215,  -215,  -111,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,   -85,    -7,  -215,    54,
     134,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -134,  -215,
    -215,  -215,  -215,    30,  -215,  -215,   -20,  -215,   162,  -215,
    -215,  -215,    62,  -102,  -215,    48,   -13,  -215,    45,  -125,
     -27,    27,    -9,   179,  -215,  -215
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    20,    21,    22,    23,    24,    25,    26,
      27,   268,   269,   235,   236,   237,   340,   341,   238,   239,
     240,   241,   242,   243,   244,   245,    99,   126,    50,    51,
      52,    53,    54,    55,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,   288,   189,   190,
     191,   192,   193,   121,   127,   194,   195,   181,   132,   318,
     329,   128,   129,   130,   219,    69,    70,    71,    84,    85,
      86,   184,     8,     9,    10,    11
  };

  const short int
  Parser::yytable_[] =
  {
      49,    75,    87,    88,   199,    90,   183,   187,   271,   179,
      80,     5,     5,     5,   209,     5,     5,     1,   281,   283,
       5,   319,   149,   320,    89,     5,   216,   188,   101,    91,
      92,    93,    96,   100,   217,   170,    12,   122,   231,   133,
     173,    74,    13,    82,   180,    14,    15,    16,    17,    18,
       7,   218,   120,   180,   248,    42,    42,    42,   265,     2,
     123,  -143,   266,    76,    77,    78,    79,     7,  -143,   131,
       6,     6,     6,   137,     6,     6,    83,    83,    83,     6,
      83,    72,   135,   136,     6,   148,    19,    73,   145,    73,
     102,   149,   183,   138,   139,   140,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   171,   198,   286,   287,   289,   174,   141,
      73,     7,   196,   251,   143,   196,   144,   147,   176,   252,
       7,   177,   200,   201,   202,   203,   204,   298,   262,   178,
     267,   186,   206,   207,    73,    14,    15,    16,    17,    18,
     221,   185,   222,   115,   223,   224,     5,   225,   226,   227,
     208,   228,   229,   210,   214,   230,   250,   249,   211,   212,
     172,   215,   196,   264,    95,   196,   301,   284,   285,   182,
     304,   311,   231,   313,   306,   330,   232,   331,    -2,    13,
     307,   308,    14,    15,    16,    17,    18,   272,   273,   274,
      42,   107,   108,   261,   317,   326,   321,   233,   112,   113,
     114,   115,   327,   328,   336,     6,   112,   113,   114,   115,
     351,   345,   278,   279,   344,   352,    81,   353,     7,   363,
     355,   290,   197,    19,   220,   259,   196,   196,   196,   213,
     134,   246,   358,   253,   263,   291,    83,   292,   293,   294,
     295,   296,   124,   107,   108,   109,     0,   299,     0,     0,
       0,     0,     0,     0,     0,   182,   110,   111,   112,   113,
     114,   115,    83,    83,    83,   246,   246,   315,   117,   118,
     119,   246,   276,     0,     0,     0,   246,   246,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   322,
     323,   324,     0,     0,     0,     0,   196,     0,   196,     0,
     182,     0,     0,     0,   300,     0,     0,     0,     0,   342,
     343,   247,     0,   246,     0,   246,     0,   348,     0,     0,
     234,     0,     0,     0,   342,   246,     0,   246,     0,   246,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   103,     0,   247,   247,     0,   107,   108,
     109,   247,   277,   246,     0,     0,   247,   247,     0,     0,
     275,   110,   111,   112,   113,   114,   115,     0,     0,     0,
       0,     0,     0,   117,   118,   119,   246,   246,     0,   246,
     246,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   247,     0,   247,   246,   246,     0,     0,
     246,     0,   303,   246,   303,   247,     0,   247,     0,   247,
       0,     0,     0,     0,   303,     0,   303,   221,   316,   222,
     305,   223,   224,     5,   225,   226,   227,     0,   228,   229,
       0,     0,   230,   247,     0,     0,     0,     0,     0,     0,
       0,     0,   325,     0,     0,     0,     0,     0,     0,   231,
       0,     0,     0,   232,     0,     0,   247,   247,     0,   247,
     247,     0,     0,     0,     0,   346,   347,    42,   349,   350,
       0,     0,     0,     0,   233,     0,   247,   247,   337,     0,
     247,     0,     6,   247,     0,   360,   361,     0,     0,   362,
       0,     0,   364,    28,     5,    29,    30,     0,     0,     0,
      31,     0,     0,     0,     0,   338,     0,    32,     0,    33,
      34,    35,     0,     0,     0,     0,    36,    37,    38,     0,
      39,     0,    40,     0,     0,     0,     0,   339,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,    94,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,     6,    28,     5,    29,    30,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,    32,     0,
      33,    34,    35,     0,     0,     0,     0,    36,    37,    38,
       0,    39,     0,    40,     0,     0,     0,     0,     0,    41,
       0,     0,     0,    95,     0,     0,     0,     0,     0,    42,
      97,     0,     0,     0,     0,     0,     0,     0,    43,    44,
      45,    46,    47,    48,     6,    28,     5,    29,    30,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,    32,
       0,    33,    34,    35,     0,     0,     0,     0,    36,    37,
      38,     0,    39,     0,    40,    98,     0,     0,     0,     0,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,   168,     0,     0,     0,     0,     0,     0,     0,    43,
      44,    45,    46,    47,    48,     6,    28,     5,    29,    30,
       0,     0,     0,    31,     0,     0,     0,     0,     0,     0,
      32,     0,    33,    34,    35,     0,     0,     0,   270,    36,
      37,    38,     0,    39,   169,    40,     0,     0,   221,     0,
     222,    41,   223,   224,     5,   225,   226,   227,     0,   228,
     229,    42,     0,   230,     0,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48,     6,     0,   280,     0,
     231,     0,     0,     0,   232,     0,     0,     0,   221,     0,
     222,     0,   223,   224,     5,   225,   226,   227,    42,   228,
     229,     0,     0,   230,     0,   233,     0,     0,     0,     0,
       0,     0,     0,     6,     0,   282,     0,     0,     0,     0,
     231,     0,     0,     0,   232,   221,     0,   222,     0,   223,
     224,     5,   225,   226,   227,     0,   228,   229,    42,     0,
     230,     0,     0,     0,     0,   233,     0,     0,     0,     0,
       0,     0,     0,     6,     0,     0,     0,   231,     0,     0,
       0,   232,   221,   302,   222,     0,   223,   224,     5,   225,
     226,   227,     0,   228,   229,    42,     0,   230,     0,     0,
       0,     0,   233,     0,     0,     0,     0,     0,     0,     0,
       6,     0,     0,     0,   231,     0,     0,     0,   232,   221,
       0,   222,     0,   223,   224,     5,   225,   226,   227,     0,
     228,   229,    42,     0,   230,     0,     0,     0,     0,   233,
       0,     0,     0,     0,     0,     0,     0,     6,     0,     0,
       0,   231,     0,     0,     0,   232,   312,     0,     0,   221,
       0,   222,     0,   223,   224,     5,   225,   226,   227,    42,
     228,   229,     0,     0,   230,     0,   233,     0,     0,     0,
       0,     0,     0,     0,     6,     0,     0,     0,     0,     0,
       0,   231,     0,     0,     0,   232,   221,     0,   222,     0,
     223,   224,     5,   225,   226,   227,     0,   228,   229,    42,
       0,   230,     0,     0,     0,     0,   233,   314,     0,     0,
       0,     0,     0,     0,     6,     0,     0,     0,   231,     0,
       0,     0,   232,    28,     5,    29,    30,     0,     0,     0,
      31,     0,     0,     0,     0,   338,    42,    32,     0,    33,
      34,    35,     0,   233,     0,     0,    36,    37,    38,     0,
      39,     6,    40,     0,     0,   354,     0,   339,    41,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    42,     0,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,     6,    28,     5,    29,    30,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,    32,     0,
      33,    34,    35,     0,     0,     0,     0,    36,    37,    38,
       0,    39,     0,    40,     0,     0,     0,     0,     0,    41,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,     0,     0,    43,    44,
      45,    46,    47,    48,     6,    28,     5,    29,    30,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,    32,
       0,    33,    34,    35,     0,     0,     0,     0,    36,    37,
      38,     0,   125,   254,    40,     0,     0,     0,     0,     0,
      41,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,   103,   104,   105,   106,     0,   107,   108,   109,    43,
      44,    45,    46,    47,    48,     6,   332,     0,     0,   110,
     111,   112,   113,   114,   115,     0,     0,     0,     0,   116,
       0,   117,   118,   119,   103,   104,   105,   106,     0,   107,
     108,   109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   114,   115,   333,     0,
       0,     0,   116,     0,   117,   118,   119,     0,   334,     0,
       0,     0,   103,   104,   105,   106,     0,   107,   108,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,   256,     0,     0,     0,
     116,     0,   117,   118,   119,     0,     0,     0,     0,     0,
     103,   104,   105,   106,     0,   107,   108,   109,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   110,   111,
     112,   113,   114,   115,   335,     0,     0,     0,   116,     0,
     117,   118,   119,     0,     0,     0,     0,     0,   103,   104,
     105,   106,     0,   107,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   111,   112,   113,
     114,   115,   359,     0,     0,     0,   116,     0,   117,   118,
     119,     0,     0,     0,     0,     0,   103,   104,   105,   106,
       0,   107,   108,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     142,     0,     0,     0,   116,     0,   117,   118,   119,     0,
       0,   103,   104,   105,   106,     0,   107,   108,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,   309,     0,     0,     0,   116,
       0,   117,   118,   119,     0,     0,   103,   104,   105,   106,
       0,   107,   108,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
     257,     0,     0,     0,   116,     0,   117,   118,   119,     0,
     103,   104,   105,   106,     0,   107,   108,   109,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   110,   111,
     112,   113,   114,   115,     0,   310,     0,     0,   116,     0,
     117,   118,   119,   103,   104,   105,   106,     0,   107,   108,
     109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,     0,     0,     0,
     255,   116,     0,   117,   118,   119,   103,   104,   105,   106,
       0,   107,   108,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
       0,     0,     0,     0,   116,   258,   117,   118,   119,   103,
     104,   105,   106,     0,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,     0,     0,     0,     0,   116,     0,   117,
     118,   119,   103,   104,   105,   106,     0,   107,   108,   109,
       0,   146,     0,     0,     0,     0,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,     0,     0,     0,     0,
     116,     0,   117,   118,   119,   103,   104,   105,   106,     0,
     107,   108,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,   115,     0,
     150,     0,     0,   116,     0,   117,   118,   119,   103,   104,
     105,   106,     0,   107,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   111,   112,   113,
     114,   115,     0,     0,     0,   175,   116,     0,   117,   118,
     119,   103,   104,   105,   106,     0,   107,   108,   109,     0,
     205,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,     0,     0,     0,     0,   116,
       0,   117,   118,   119,   103,   104,   105,   106,     0,   107,
     108,   109,     0,     0,     0,   260,     0,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   114,   115,     0,     0,
       0,     0,   116,     0,   117,   118,   119,   103,   104,   105,
     106,     0,   107,   108,   109,     0,   297,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   114,
     115,     0,     0,     0,     0,   116,     0,   117,   118,   119,
     103,   104,   105,   106,     0,   107,   108,   109,     0,     0,
       0,     0,     0,     0,   356,     0,     0,     0,   110,   111,
     112,   113,   114,   115,     0,     0,     0,     0,   116,     0,
     117,   118,   119,   103,   104,   105,   106,     0,   107,   108,
     109,     0,     0,     0,     0,     0,   357,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,     0,     0,     0,
       0,   116,     0,   117,   118,   119,   103,   104,   105,   106,
       0,   107,   108,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
       0,     0,     0,     0,   116,     0,   117,   118,   119,   103,
     104,   105,     0,     0,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,     0,     0,     0,     0,     0,     0,   117,
     118,   119,   103,     0,   105,     0,     0,   107,   108,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,     0,     0,     0,     0,
       0,     0,   117,   118,   119,   103,   104,   105,   106,     0,
     107,   108,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,     0,     0,   113,   114,   115,   107,
     108,     0,     0,   116,     0,   117,   118,   119,     0,     0,
       0,     0,   110,   111,   112,   113,   114,   115,     0,     0,
       0,     0,     0,     0,     0,   118,   119
  };

  const short int
  Parser::yycheck_[] =
  {
       7,    14,    29,    30,   138,    32,   131,    42,   222,     1,
      19,    17,    17,    17,    44,    17,    17,     3,   232,   233,
      17,    52,    52,    54,    31,    17,    44,    62,    41,    36,
      37,    38,    39,    40,    52,   120,     0,    61,    43,    42,
     125,    47,     1,    45,    45,     4,     5,     6,     7,     8,
       2,   185,    43,    45,   188,    61,    61,    61,    48,    45,
       3,    55,    52,    15,    16,    17,    18,    19,    62,    43,
      76,    76,    76,    82,    76,    76,    28,    29,    30,    76,
      32,    46,    49,    46,    76,    46,    45,    52,    95,    52,
      42,    52,   217,    49,    42,    17,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    46,   249,   250,   251,   125,    17,
      52,    73,   135,    53,    17,   138,    44,    46,    62,    59,
      82,    52,   139,   140,   141,   142,   143,   262,    46,    48,
       1,    47,   149,   150,    52,     4,     5,     6,     7,     8,
      11,    62,    13,    58,    15,    16,    17,    18,    19,    20,
      44,    22,    23,    52,    44,    26,    62,    55,   175,   176,
     122,   180,   185,    42,    55,   188,    12,    64,    42,   131,
      14,    48,    43,    69,    42,   319,    47,   321,     0,     1,
      17,    17,     4,     5,     6,     7,     8,   224,   225,   226,
      61,    40,    41,   210,    10,    47,    62,    68,    55,    56,
      57,    58,    47,     9,    25,    76,    55,    56,    57,    58,
      48,    54,   229,   230,    47,    49,    20,    49,   180,    48,
     341,   251,   136,    45,   186,   205,   249,   250,   251,   177,
      78,   187,   344,   198,   217,   252,   198,   254,   255,   256,
     257,   258,    73,    40,    41,    42,    -1,   264,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   217,    53,    54,    55,    56,
      57,    58,   224,   225,   226,   221,   222,   284,    65,    66,
      67,   227,   228,    -1,    -1,    -1,   232,   233,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   306,
     307,   308,    -1,    -1,    -1,    -1,   319,    -1,   321,    -1,
     262,    -1,    -1,    -1,   266,    -1,    -1,    -1,    -1,   326,
     327,   187,    -1,   269,    -1,   271,    -1,   334,    -1,    -1,
     187,    -1,    -1,    -1,   341,   281,    -1,   283,    -1,   285,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    -1,   221,   222,    -1,    40,    41,
      42,   227,   228,   309,    -1,    -1,   232,   233,    -1,    -1,
     227,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,   332,   333,    -1,   335,
     336,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   269,    -1,   271,   352,   353,    -1,    -1,
     356,    -1,   269,   359,   271,   281,    -1,   283,    -1,   285,
      -1,    -1,    -1,    -1,   281,    -1,   283,    11,   285,    13,
      14,    15,    16,    17,    18,    19,    20,    -1,    22,    23,
      -1,    -1,    26,   309,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   309,    -1,    -1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    47,    -1,    -1,   332,   333,    -1,   335,
     336,    -1,    -1,    -1,    -1,   332,   333,    61,   335,   336,
      -1,    -1,    -1,    -1,    68,    -1,   352,   353,     1,    -1,
     356,    -1,    76,   359,    -1,   352,   353,    -1,    -1,   356,
      -1,    -1,   359,    16,    17,    18,    19,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    28,    -1,    30,    -1,    32,
      33,    34,    -1,    -1,    -1,    -1,    39,    40,    41,    -1,
      43,    -1,    45,    -1,    -1,    -1,    -1,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    16,    17,    18,    19,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,    40,    41,
      -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    61,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    16,    17,    18,    19,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    32,    33,    34,    -1,    -1,    -1,    -1,    39,    40,
      41,    -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    16,    17,    18,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    32,    33,    34,    -1,    -1,    -1,     1,    39,
      40,    41,    -1,    43,    44,    45,    -1,    -1,    11,    -1,
      13,    51,    15,    16,    17,    18,    19,    20,    -1,    22,
      23,    61,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    -1,     1,    -1,
      43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    11,    -1,
      13,    -1,    15,    16,    17,    18,    19,    20,    61,    22,
      23,    -1,    -1,    26,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,     1,    -1,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    47,    11,    -1,    13,    -1,    15,
      16,    17,    18,    19,    20,    -1,    22,    23,    61,    -1,
      26,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    47,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    61,    -1,    26,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,    11,
      -1,    13,    -1,    15,    16,    17,    18,    19,    20,    -1,
      22,    23,    61,    -1,    26,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    43,    -1,    -1,    -1,    47,    48,    -1,    -1,    11,
      -1,    13,    -1,    15,    16,    17,    18,    19,    20,    61,
      22,    23,    -1,    -1,    26,    -1,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    -1,    -1,    47,    11,    -1,    13,    -1,
      15,    16,    17,    18,    19,    20,    -1,    22,    23,    61,
      -1,    26,    -1,    -1,    -1,    -1,    68,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    47,    16,    17,    18,    19,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    28,    61,    30,    -1,    32,
      33,    34,    -1,    68,    -1,    -1,    39,    40,    41,    -1,
      43,    76,    45,    -1,    -1,    48,    -1,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    16,    17,    18,    19,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,    40,    41,
      -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    16,    17,    18,    19,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    32,    33,    34,    -1,    -1,    -1,    -1,    39,    40,
      41,    -1,    43,    17,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    35,    36,    37,    38,    -1,    40,    41,    42,    70,
      71,    72,    73,    74,    75,    76,    17,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      -1,    65,    66,    67,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    21,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    -1,    31,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    21,    -1,    -1,    -1,
      63,    -1,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,
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
      24,    -1,    -1,    -1,    63,    -1,    65,    66,    67,    -1,
      -1,    35,    36,    37,    38,    -1,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    24,    -1,    -1,    -1,    63,
      -1,    65,    66,    67,    -1,    -1,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      25,    -1,    -1,    -1,    63,    -1,    65,    66,    67,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    27,    -1,    -1,    63,    -1,
      65,    66,    67,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      29,    63,    -1,    65,    66,    67,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    31,    65,    66,    67,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      63,    -1,    65,    66,    67,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      60,    -1,    -1,    63,    -1,    65,    66,    67,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    62,    63,    -1,    65,    66,
      67,    35,    36,    37,    38,    -1,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      -1,    65,    66,    67,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    63,    -1,    65,    66,    67,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,
      65,    66,    67,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    -1,    65,    66,    67,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    -1,    65,    66,    67,    35,
      36,    37,    -1,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    35,    -1,    37,    -1,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    35,    36,    37,    38,    -1,
      40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    -1,    -1,    56,    57,    58,    40,
      41,    -1,    -1,    63,    -1,    65,    66,    67,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    45,    82,    83,    17,    76,   146,   153,   154,
     155,   156,     0,     1,     4,     5,     6,     7,     8,    45,
      84,    85,    86,    87,    88,    89,    90,    91,    16,    18,
      19,    23,    30,    32,    33,    34,    39,    40,    41,    43,
      45,    51,    61,    70,    71,    72,    73,    74,    75,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   146,
     147,   148,    46,    52,    47,   147,   146,   146,   146,   146,
     153,    85,    45,   146,   149,   150,   151,   151,   151,   108,
     151,   108,   108,   108,     1,    55,   108,     1,    46,   107,
     108,   147,   146,    35,    36,    37,    38,    40,    41,    42,
      53,    54,    55,    56,    57,    58,    63,    65,    66,    67,
      43,   134,    61,     3,   154,    43,   108,   135,   142,   143,
     144,    43,   139,    42,   139,    49,    46,   153,    49,    42,
      17,    17,    24,    17,    44,   108,    44,    46,    46,    52,
      60,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   108,   108,     1,    44,
     107,   108,   146,   107,   108,    62,    62,    52,    48,     1,
      45,   138,   146,   150,   152,    62,    47,    42,    62,   129,
     130,   131,   132,   133,   136,   137,   147,    86,    46,   129,
     108,   108,   108,   108,   108,    44,   108,   108,    44,    44,
      52,   108,   108,   143,    44,   153,    44,    52,   129,   145,
     146,    11,    13,    15,    16,    18,    19,    20,    22,    23,
      26,    43,    47,    68,    92,    94,    95,    96,    99,   100,
     101,   102,   103,   104,   105,   106,   110,   111,   129,    55,
      62,    53,    59,   149,    17,    29,    21,    25,    31,   134,
      46,   108,    46,   152,    42,    48,    52,     1,    92,    93,
       1,    93,   151,   151,   151,    92,   110,   111,   108,   108,
       1,    93,     1,    93,    64,    42,   129,   129,   128,   129,
     137,   108,   108,   108,   108,   108,   108,    44,   150,   108,
     146,    12,    12,    92,    14,    14,    42,    17,    17,    24,
      27,    48,    48,    69,    69,   108,    92,    10,   140,    52,
      54,    62,   108,   108,   108,    92,    47,    47,     9,   141,
     129,   129,    17,    21,    31,    21,    25,     1,    28,    50,
      97,    98,   108,   108,    47,    54,    92,    92,   108,    92,
      92,    48,    49,    49,    48,    97,    49,    48,   144,    21,
      92,    92,    92,    48,    92
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    81,    82,    83,    83,    84,    84,    85,    85,    85,
      86,    86,    86,    86,    87,    88,    89,    89,    90,    90,
      91,    91,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    93,    93,    94,    95,    95,    96,    96,
      97,    97,    97,    98,    98,    99,   100,   100,   101,   102,
     103,   103,   103,   103,   104,   104,   104,   104,   105,   106,
     106,   106,   106,   107,   107,   108,   108,   108,   108,   108,
     108,   108,   108,   108,   108,   108,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   110,   110,
     111,   112,   113,   114,   115,   116,   117,   117,   117,   118,
     119,   119,   119,   119,   119,   119,   119,   119,   120,   121,
     121,   122,   123,   124,   125,   125,   126,   127,   128,   128,
     129,   129,   129,   129,   130,   131,   132,   133,   134,   134,
     134,   135,   136,   136,   137,   137,   138,   138,   139,   139,
     139,   140,   140,   141,   141,   142,   142,   143,   143,   143,
     144,   144,   145,   145,   146,   146,   147,   147,   148,   148,
     149,   149,   150,   151,   151,   152,   152,   153,   153,   154,
     154,   155,   156
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
       1,     1,     1,     1,     1,     1,     3,     3,     2,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     1,     2,
       5,     6,     6,     6,     6,     6,     2,     3,     3,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     3,     1,
       1,     1,     1,     1,     1,     4,     6,     3,     3,     3,
       2,     5,     3,     1,     1,     0,     3,     1,     3,     3,
       0,     4,     0,     4,     0,     3,     1,     1,     3,     3,
       1,     0,     3,     1,     1,     1,     1,     2,     3,     1,
       1,     1,     3,     4,     1,     4,     1,     3,     1,     1,
       1,     1,     2
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
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"decimal\"",
  "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Header", "Definitions",
  "AttributedDefinition", "Definition", "EnumerationDefinition",
  "DerivedDefinition", "RuleDefinition", "FunctionDefinition",
  "ProgramFunctionDefinition", "Rule", "Rules", "SkipRule",
  "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels", "LetRule",
  "ForallRule", "ChooseRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", "Terms", "Term", "Expression",
  "DirectCallExpression", "IndirectCallExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "List", "Range", "Literal", "UndefinedLiteral", "BooleanLiteral",
  "IntegerLiteral", "RationalLiteral", "DecimalLiteral", "BitLiteral",
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
       0,   372,   372,   381,   387,   395,   401,   411,   417,   421,
     429,   433,   437,   441,   449,   457,   465,   470,   479,   495,
     503,   526,   548,   552,   556,   560,   564,   568,   572,   576,
     580,   584,   588,   596,   602,   612,   620,   624,   632,   636,
     644,   648,   652,   660,   666,   676,   684,   688,   696,   704,
     712,   716,   720,   725,   734,   738,   742,   747,   756,   766,
     772,   779,   785,   800,   806,   816,   820,   824,   828,   832,
     836,   840,   844,   848,   852,   856,   868,   872,   876,   880,
     884,   888,   892,   896,   900,   904,   908,   912,   916,   920,
     924,   928,   932,   936,   940,   944,   948,   952,   960,   965,
     973,   981,   989,   997,  1005,  1013,  1023,  1028,  1032,  1040,
    1052,  1056,  1060,  1064,  1068,  1072,  1076,  1080,  1088,  1096,
    1101,  1110,  1126,  1142,  1158,  1170,  1186,  1202,  1214,  1220,
    1230,  1234,  1238,  1242,  1250,  1258,  1266,  1274,  1286,  1290,
    1294,  1303,  1317,  1323,  1333,  1337,  1345,  1351,  1361,  1365,
    1369,  1381,  1385,  1393,  1397,  1405,  1411,  1421,  1429,  1439,
    1450,  1454,  1466,  1472,  1482,  1486,  1494,  1498,  1508,  1514,
    1528,  1532,  1541,  1549,  1555,  1563,  1569,  1581,  1587,  1596,
    1600,  1608,  1616
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
#line 3922 "GrammarParser.cpp" // lalr1.cc:1167
#line 1622 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
