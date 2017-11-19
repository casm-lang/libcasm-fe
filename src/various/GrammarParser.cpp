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
      case 155: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 154: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 156: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 132: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 105: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 108: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 99: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 98: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 100: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 116: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 103: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 133: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 115: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 97: // ConditionalRule
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

      case 112: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 87: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 92: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 93: // Enumerators
        value.move< Enumerators::Ptr > (that.value);
        break;

      case 118: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 110: // Term
      case 111: // Expression
      case 121: // Literal
      case 142: // MaybeDefined
        value.move< Expression::Ptr > (that.value);
        break;

      case 157: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 109: // Terms
      case 136: // Arguments
      case 137: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 135: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 102: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 90: // FunctionDefinition
      case 91: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 83: // Header
        value.move< HeaderDefinition::Ptr > (that.value);
        break;

      case 147: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 148: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 149: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 113: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 104: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 114: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 101: // LetRule
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

      case 94: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 89: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 95: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 106: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 96: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.move< Specification::Ptr > (that.value);
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

      case 107: // UpdateRule
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

      case 150: // Variable
      case 151: // TypedVariable
      case 152: // AttributedVariable
      case 153: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 131: // Type
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
      case 155: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 154: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 156: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 132: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 105: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 108: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 99: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 98: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 100: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 116: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 103: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 133: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 115: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 97: // ConditionalRule
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

      case 112: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 87: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 92: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (that.value);
        break;

      case 93: // Enumerators
        value.copy< Enumerators::Ptr > (that.value);
        break;

      case 118: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 110: // Term
      case 111: // Expression
      case 121: // Literal
      case 142: // MaybeDefined
        value.copy< Expression::Ptr > (that.value);
        break;

      case 157: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 109: // Terms
      case 136: // Arguments
      case 137: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 135: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 102: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 90: // FunctionDefinition
      case 91: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 83: // Header
        value.copy< HeaderDefinition::Ptr > (that.value);
        break;

      case 147: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 148: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 149: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 113: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 104: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 114: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 101: // LetRule
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

      case 94: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 89: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 95: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 106: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 96: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.copy< Specification::Ptr > (that.value);
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

      case 107: // UpdateRule
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

      case 150: // Variable
      case 151: // TypedVariable
      case 152: // AttributedVariable
      case 153: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 131: // Type
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
      case 155: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 154: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 156: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 132: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 105: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 108: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 99: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 98: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 100: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 116: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 103: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 133: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 115: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 97: // ConditionalRule
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

      case 112: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 87: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 92: // EnumeratorDefinition
        yylhs.value.build< EnumeratorDefinition::Ptr > ();
        break;

      case 93: // Enumerators
        yylhs.value.build< Enumerators::Ptr > ();
        break;

      case 118: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 110: // Term
      case 111: // Expression
      case 121: // Literal
      case 142: // MaybeDefined
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 157: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 109: // Terms
      case 136: // Arguments
      case 137: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 135: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 102: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 90: // FunctionDefinition
      case 91: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 83: // Header
        yylhs.value.build< HeaderDefinition::Ptr > ();
        break;

      case 147: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 148: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 149: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 113: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 104: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 114: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 101: // LetRule
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

      case 94: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 89: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 95: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 106: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 96: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 82: // Specification
        yylhs.value.build< Specification::Ptr > ();
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

      case 107: // UpdateRule
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

      case 150: // Variable
      case 151: // TypedVariable
      case 152: // AttributedVariable
      case 153: // TypedAttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 131: // Type
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
#line 376 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setHeader( yystack_[1].value.as< HeaderDefinition::Ptr > () );
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1350 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 385 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< HeaderDefinition::Ptr > () = definition;
  }
#line 1360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< HeaderDefinition::Ptr > () = Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
  }
#line 1368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1378 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 405 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 415 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1398 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 421 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1406 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 425 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1414 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 433 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 437 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1430 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 441 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1438 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 445 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1446 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 453 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Enumerators::Ptr > () );
  }
#line 1454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1462 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 469 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1471 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 474 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 1480 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 483 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1500 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1508 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 507 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1535 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 530 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 548 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 552 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerator = Ast::make< EnumeratorDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
      enumerator->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< EnumeratorDefinition::Ptr > () = enumerator;
  }
#line 1571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumeratorDefinition::Ptr > () = nullptr;
  }
#line 1579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 566 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = yystack_[2].value.as< Enumerators::Ptr > ();
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1589 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 572 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto enumerators = Ast::make< Enumerators >( yylhs.location );
      enumerators->add( yystack_[0].value.as< EnumeratorDefinition::Ptr > () );
      yylhs.value.as< Enumerators::Ptr > () = enumerators;
  }
#line 1599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 586 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 1607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 590 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 1615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 594 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 1623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 598 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 1631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 1639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 606 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 1647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 610 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 1655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 614 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 1663 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 618 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 1671 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 1679 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 626 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 1687 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 640 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 1707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 1715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 658 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 670 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 1739 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 674 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 1747 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 682 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 686 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1763 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 690 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 698 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[1].value.as< Cases::Ptr > ();
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 1791 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 714 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1799 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 722 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1807 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1815 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1823 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 742 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 1831 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 754 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1847 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 758 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1856 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 763 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 776 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 1881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1890 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 785 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 1899 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 794 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 804 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 808 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1925 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::RULE_CALL );
  }
#line 1933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), CallRule::Type::FUNCTION_CALL );
  }
#line 1941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 828 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1951 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 834 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 1961 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 844 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1969 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 848 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1977 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 852 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 1985 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 856 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1993 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 860 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2001 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 864 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2009 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 868 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2017 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 872 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2025 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 876 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2033 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 880 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 884 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2049 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 896 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2057 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 900 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2065 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 904 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2073 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 908 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2081 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 912 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2089 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2097 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 920 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2105 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2113 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2121 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2129 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2137 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 940 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2145 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 944 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2153 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 948 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2161 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 952 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2169 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2177 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 960 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 964 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2193 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2201 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 972 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 980 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2225 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 988 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 993 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1001 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2250 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1009 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2258 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1017 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1025 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2274 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1033 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1041 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1051 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2299 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1056 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2307 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1060 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1068 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2323 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1080 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 2331 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1084 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2339 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2347 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1092 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1096 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1100 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2371 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1104 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 2379 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1108 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 2387 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1116 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2395 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1124 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2404 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1129 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 2413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1138 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2429 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2445 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1170 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2461 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1186 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2477 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1198 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2493 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1214 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2509 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1230 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1242 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2527 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1248 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1258 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 2545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1262 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1266 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1270 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1278 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1286 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 2585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1294 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1302 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1314 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1318 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1322 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2626 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1331 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1345 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2646 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1351 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 2656 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1361 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 2664 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1365 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 2672 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2682 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1379 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 2692 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1389 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 2700 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 2708 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 2716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1409 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2724 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1413 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 2732 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1421 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1425 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1433 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2758 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1439 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 2768 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1449 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2780 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1457 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1467 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 2813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1482 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 2821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1498 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 2837 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1506 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 2845 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1510 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
  }
#line 2855 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1520 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1526 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 2875 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1540 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2883 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1544 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 2892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 2900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2910 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1567 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2918 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1575 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 2928 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 2936 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1593 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2946 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2956 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 1608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2964 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 183:
#line 1612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2972 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 184:
#line 1620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2980 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 185:
#line 1628 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2988 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2992 "GrammarParser.cpp" // lalr1.cc:859
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

  const short int Parser::yytable_ninf_ = -149;

  const short int
  Parser::yypact_[] =
  {
       4,  -215,     1,    13,   211,  -215,  -215,  1071,     5,  -215,
    -215,  -215,  -215,  -215,    -9,     1,     1,     1,     1,     1,
     147,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    -5,    -5,
      -5,  1071,    -5,  -215,  -215,  -215,  1071,  1071,  1071,   517,
     578,    -1,     1,  -215,  -215,  -215,  -215,  -215,  -215,  1810,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
     -18,   -22,    50,     1,  1132,  -215,    15,    40,    15,     7,
      32,  -215,     1,    41,  -215,  -215,    49,    76,    77,  1379,
      78,  -215,  -215,  -215,    71,  1071,  1546,    70,  -215,    34,
    1579,  -215,  -215,  1071,  1071,  1071,  1071,  1071,  1071,  1071,
    1071,  1071,  1071,  1071,  1071,  1071,  1071,  1071,  1071,  1071,
     639,  -215,     1,  -215,  -215,   517,  1612,    55,    67,  -215,
      73,     3,    61,    94,   -28,    -1,   122,    35,    -1,  1071,
    1071,  1071,  1071,  1071,  -215,  1645,  -215,  -215,  -215,  1071,
    1071,  1947,  1876,  1928,  1843,   101,   101,  1966,     6,     6,
      66,    66,    66,  -215,  1843,  1966,     6,     6,    87,  -215,
     -25,  1810,  -215,    92,  1546,  1071,  1071,  1132,  -215,   102,
       1,    -8,    41,  -215,  -215,    -1,     9,   978,    -1,  -215,
    -215,  -215,  -215,  -215,   105,    99,   -16,  -215,     1,  -215,
    1159,  1480,  1268,   374,  1513,   -18,  1810,  1678,  -215,  -215,
    1071,  1810,  1810,  -215,  -215,    37,  -215,     0,   107,  -215,
       1,  -215,    17,  -215,   676,   716,  -215,    -5,    -5,    -5,
     978,    -2,  1071,  1071,   116,   753,   790,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,    98,
    -215,   131,    -1,    -1,    -1,  1071,  -215,  1071,  1071,  1071,
    1071,  1071,  -215,  -215,  1711,     1,  -215,  1071,    68,  -215,
       9,   162,  -215,   827,   165,   864,   139,   167,   168,  -215,
    -215,  -215,  1414,  1447,   138,   901,   118,   941,  1071,   978,
    -215,   181,    14,   -20,   133,  1909,  1810,  1810,  1810,  1810,
    1810,  -215,  -215,  1810,     1,  -215,  -215,  -215,  -215,  -215,
    -215,  1071,  1071,  1071,   978,   149,  -215,  -215,  -215,  -215,
    1810,  -215,   150,   189,    -1,  -215,    -1,  -215,  1192,  1230,
    1306,   174,   456,  1071,   157,  -215,  -215,   151,   978,   978,
    1071,   978,   978,   158,   159,   164,  -215,  1010,  1744,  1777,
    1132,  -215,  -215,  -215,  1344,  -215,  -215,  -215,   978,   978,
    -215,  -215,   978,  -215,   166,   978,  -215,  -215,  -215,  -215,
    -215
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     4,     0,     0,     0,   168,   167,   184,     0,   181,
     182,   183,     1,     9,     0,     0,     0,     0,     0,     0,
       0,     6,     8,    10,    11,    12,    13,    19,     0,     0,
       0,     0,     0,   123,   125,   124,     0,     0,     0,     0,
       0,     0,     0,   129,   130,   126,   127,   128,   131,   185,
      77,    70,    71,    72,    73,    74,    75,    76,    78,    79,
      80,   115,   116,   117,   118,   119,   120,   121,   122,   172,
     103,   169,     0,     0,   166,    20,   155,     0,   155,     0,
       0,     5,     0,   174,   177,   173,     0,     0,     0,     0,
       0,   102,    83,    84,     0,     0,     0,     0,   111,     0,
      69,   132,   170,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   104,     0,     3,   180,     0,   162,     0,   165,   161,
       0,     0,     0,     0,     0,   150,     0,     0,     0,     0,
       0,     0,     0,     0,    82,     0,    81,   113,   112,     0,
       0,    99,    97,    98,   101,    85,    86,    92,    93,    94,
      87,    88,    89,    90,   100,    91,    95,    96,     0,   145,
       0,    69,   171,     0,    69,     0,     0,     0,    21,     0,
       0,     0,     0,   179,   152,     0,     0,     0,     0,   148,
     135,   136,   137,   138,   149,     0,   139,     7,     0,   175,
       0,     0,     0,     0,     0,     0,    68,     0,   144,   143,
       0,   163,   164,   160,   154,     0,   153,     0,     0,    24,
       0,    26,     0,    22,     0,     0,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    65,
      67,     0,     0,     0,   150,     0,   176,     0,     0,     0,
       0,     0,   105,   114,    68,     0,   151,     0,     0,    14,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    54,
      64,    66,     0,     0,     0,     0,     0,     0,     0,     0,
     147,   157,     0,   134,     0,   142,   106,   109,   108,   107,
     110,   146,   178,    15,     0,    25,    62,    60,    38,    58,
      56,     0,     0,     0,     0,     0,    57,    55,    61,    59,
      63,    17,     0,   159,     0,   140,     0,    23,     0,     0,
       0,    41,     0,     0,     0,    18,   133,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    49,     0,     0,     0,
     166,   141,    50,    51,     0,    53,    42,    44,     0,     0,
      43,    48,     0,   156,     0,     0,    45,    46,    47,   158,
      52
  };

  const short int
  Parser::yypgoto_[] =
  {
    -215,  -215,  -215,  -215,   187,    86,  -215,  -215,  -215,  -215,
    -215,   -50,  -215,    84,  -214,  -215,  -215,  -215,  -124,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,   -70,    -7,
    -215,   -42,   106,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,  -215,
    -115,  -215,  -215,  -215,  -215,    19,  -215,  -215,   -26,  -215,
     154,  -215,  -215,  -215,    52,  -123,   148,   -13,  -215,    36,
    -125,   -27,    18,   -10,   163,  -215,  -215
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     3,     4,    20,    21,    22,    23,    24,    25,    26,
      27,   221,   222,   272,   273,   238,   239,   240,   346,   347,
     241,   242,   243,   244,   245,   246,   247,   248,    99,   126,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,   292,
     189,   190,   191,   192,   193,   121,   127,   194,   195,   181,
     132,   323,   335,   128,   129,   130,    69,    70,    71,    84,
      85,    86,   184,     8,     9,    10,    11
  };

  const short int
  Parser::yytable_[] =
  {
      49,    75,    87,    88,   179,    90,   183,     1,     5,    80,
     219,   275,     5,    12,   187,     5,     5,     5,     5,   209,
       5,   285,   287,   199,    89,   120,     5,   149,   101,    91,
      92,    93,    96,   100,   188,  -148,   216,   254,    74,   122,
      82,   234,  -148,   255,   217,   180,   107,   108,   180,     2,
     170,    72,    42,   123,   220,   173,   135,    73,   131,    42,
      42,   112,   113,   114,   115,   269,   324,     6,   325,   270,
     218,     6,   137,   251,     6,     6,     6,     6,   136,     6,
     148,   198,   133,   265,    73,     6,   149,    73,   145,    73,
     138,   139,   183,   140,   141,   143,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   171,   304,   144,   147,   176,   174,   177,
      73,   178,   196,   185,   115,   196,    14,    15,    16,    17,
      18,   208,   200,   201,   202,   203,   204,   290,   291,   293,
     302,   186,   206,   207,   210,   249,   214,    -2,    13,   267,
       7,    14,    15,    16,    17,    18,   112,   113,   114,   115,
     252,   253,   288,    76,    77,    78,    79,     7,   211,   212,
     215,    95,   196,   289,   306,   196,    83,    83,    83,   309,
      83,   311,   249,   249,   312,   313,   316,   318,   249,   280,
     102,   322,    19,   249,   249,   326,   332,   333,   334,   342,
     276,   277,   278,   264,   350,   351,   357,    81,   358,   336,
     268,   337,    13,   359,   369,    14,    15,    16,    17,    18,
     305,     7,   197,   361,   262,   282,   283,   364,   294,   213,
       7,   249,   134,   249,   256,   266,   124,     0,     0,   196,
     196,   196,     0,   249,     0,   249,     0,   249,   295,     0,
     296,   297,   298,   299,   300,     0,    19,     0,     0,     0,
     303,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     172,   237,   249,     0,     0,     0,     0,     0,     0,   182,
       0,   320,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   250,     0,     0,   249,   249,     0,   249,
     249,     0,     0,     0,   328,   329,   330,     0,     0,     0,
       0,   196,     0,   196,   279,     0,   249,   249,     0,     0,
     249,     0,     0,   249,     0,   348,   349,     0,     7,     0,
     250,   250,     0,   354,   223,     0,   250,   281,     0,     0,
     348,   250,   250,     0,     0,     0,    83,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   308,     0,   308,
       0,     0,     0,     0,     0,   182,     0,     0,     7,   308,
       0,   308,     0,   321,     0,    83,    83,    83,     0,   250,
       0,   250,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   250,     0,   250,     0,   250,     0,     0,   331,   260,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   103,
     104,   105,   106,   182,   107,   108,   109,     0,   223,     0,
     250,     0,   352,   353,     0,   355,   356,   110,   111,   112,
     113,   114,   115,     0,     0,     0,     0,   116,     0,   117,
     118,   119,   366,   367,   250,   250,   368,   250,   250,   370,
       0,     0,   327,     0,     0,     0,     0,   343,     0,     0,
       0,     0,     0,     0,   250,   250,     0,     0,   250,     0,
       0,   250,    28,     5,    29,    30,     0,     0,     0,    31,
       0,     0,     0,     0,   344,     0,    32,     0,    33,    34,
      35,     0,     0,     0,     0,    36,    37,    38,     0,    39,
       0,    40,     0,     0,     0,     0,   345,    41,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    94,     0,
       0,     0,     0,     0,     0,     0,    43,    44,    45,    46,
      47,    48,     6,    28,     5,    29,    30,     0,     0,     0,
      31,     0,     0,     0,     0,     0,     0,    32,     0,    33,
      34,    35,     0,     0,     0,     0,    36,    37,    38,     0,
      39,     0,    40,     0,     0,     0,     0,     0,    41,     0,
       0,     0,    95,     0,     0,     0,     0,     0,    42,    97,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,     6,    28,     5,    29,    30,     0,     0,
       0,    31,     0,     0,     0,     0,     0,     0,    32,     0,
      33,    34,    35,     0,     0,     0,     0,    36,    37,    38,
       0,    39,     0,    40,    98,     0,     0,     0,     0,    41,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
     168,     0,     0,     0,     0,     0,     0,     0,    43,    44,
      45,    46,    47,    48,     6,    28,     5,    29,    30,     0,
       0,     0,    31,     0,     0,     0,     0,     0,     0,    32,
       0,    33,    34,    35,     0,     0,     0,   271,    36,    37,
      38,     0,    39,   169,    40,     0,     0,   224,     0,   225,
      41,   226,   227,     5,   228,   229,   230,     0,   231,   232,
      42,     0,   233,     0,     0,     0,     0,     0,     0,    43,
      44,    45,    46,    47,    48,     6,     0,   274,     0,   234,
       0,     0,     0,   235,     0,     0,     0,   224,     0,   225,
       0,   226,   227,     5,   228,   229,   230,    42,   231,   232,
       0,     0,   233,     0,   236,     0,     0,     0,     0,     0,
       0,     0,     6,     0,   284,     0,     0,     0,     0,   234,
       0,     0,     0,   235,   224,     0,   225,     0,   226,   227,
       5,   228,   229,   230,     0,   231,   232,    42,     0,   233,
       0,     0,     0,     0,   236,     0,     0,     0,     0,     0,
       0,   286,     6,     0,     0,     0,   234,     0,     0,     0,
     235,   224,     0,   225,     0,   226,   227,     5,   228,   229,
     230,     0,   231,   232,    42,     0,   233,     0,     0,     0,
       0,   236,     0,     0,     0,     0,     0,     0,     0,     6,
       0,     0,     0,   234,     0,     0,     0,   235,   224,   307,
     225,     0,   226,   227,     5,   228,   229,   230,     0,   231,
     232,    42,     0,   233,     0,     0,     0,     0,   236,     0,
       0,     0,     0,     0,     0,     0,     6,     0,     0,     0,
     234,     0,     0,     0,   235,   224,     0,   225,   310,   226,
     227,     5,   228,   229,   230,     0,   231,   232,    42,     0,
     233,     0,     0,     0,     0,   236,     0,     0,     0,     0,
       0,     0,     0,     6,     0,     0,     0,   234,     0,     0,
       0,   235,   224,     0,   225,     0,   226,   227,     5,   228,
     229,   230,     0,   231,   232,    42,     0,   233,     0,     0,
       0,     0,   236,     0,     0,     0,     0,     0,     0,     0,
       6,     0,     0,     0,   234,     0,     0,     0,   235,   317,
       0,     0,   224,     0,   225,     0,   226,   227,     5,   228,
     229,   230,    42,   231,   232,     0,     0,   233,     0,   236,
       0,     0,     0,     0,     0,     0,     0,     6,     0,     0,
       0,     0,     0,     0,   234,     0,     0,     0,   235,   224,
       0,   225,     0,   226,   227,     5,   228,   229,   230,     0,
     231,   232,    42,     0,   233,     0,     0,     0,     0,   236,
     319,     0,     0,     0,     0,     0,     0,     6,     0,     0,
       0,   234,     0,     0,     0,   235,    28,     5,    29,    30,
       0,     0,     0,    31,     0,     0,     0,     0,   344,    42,
      32,     0,    33,    34,    35,     0,   236,     0,     0,    36,
      37,    38,     0,    39,     6,    40,     0,     0,   360,     0,
     345,    41,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48,     6,    28,     5,    29,
      30,     0,     0,     0,    31,     0,     0,     0,     0,     0,
       0,    32,     0,    33,    34,    35,     0,     0,     0,     0,
      36,    37,    38,     0,    39,     0,    40,     0,     0,     0,
       0,     0,    41,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,     0,
       0,    43,    44,    45,    46,    47,    48,     6,    28,     5,
      29,    30,     0,     0,     0,    31,     0,     0,     0,     0,
       0,     0,    32,     0,    33,    34,    35,     0,     0,     0,
       0,    36,    37,    38,     0,   125,   257,    40,     0,     0,
       0,     0,     0,    41,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    42,   103,   104,   105,   106,     0,   107,
     108,   109,    43,    44,    45,    46,    47,    48,     6,   338,
       0,     0,   110,   111,   112,   113,   114,   115,     0,     0,
       0,     0,   116,     0,   117,   118,   119,   103,   104,   105,
     106,     0,   107,   108,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   114,
     115,   339,     0,     0,     0,   116,     0,   117,   118,   119,
       0,   340,     0,     0,     0,   103,   104,   105,   106,     0,
     107,   108,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,   115,   259,
       0,     0,     0,   116,     0,   117,   118,   119,     0,     0,
       0,     0,     0,   103,   104,   105,   106,     0,   107,   108,
     109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,   341,     0,     0,
       0,   116,     0,   117,   118,   119,     0,     0,     0,     0,
       0,   103,   104,   105,   106,     0,   107,   108,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,   365,     0,     0,     0,   116,
       0,   117,   118,   119,     0,     0,     0,     0,     0,   103,
     104,   105,   106,     0,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,   142,     0,     0,     0,   116,     0,   117,
     118,   119,     0,     0,   103,   104,   105,   106,     0,   107,
     108,   109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   114,   115,   314,     0,
       0,     0,   116,     0,   117,   118,   119,     0,     0,   103,
     104,   105,   106,     0,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,     0,   315,     0,     0,   116,     0,   117,
     118,   119,   103,   104,   105,   106,     0,   107,   108,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,     0,     0,     0,   258,
     116,     0,   117,   118,   119,   103,   104,   105,   106,     0,
     107,   108,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,   115,     0,
       0,     0,     0,   116,   261,   117,   118,   119,   103,   104,
     105,   106,     0,   107,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   111,   112,   113,
     114,   115,     0,     0,     0,     0,   116,     0,   117,   118,
     119,   103,   104,   105,   106,     0,   107,   108,   109,     0,
     146,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,     0,     0,     0,     0,   116,
       0,   117,   118,   119,   103,   104,   105,   106,     0,   107,
     108,   109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   114,   115,     0,   150,
       0,     0,   116,     0,   117,   118,   119,   103,   104,   105,
     106,     0,   107,   108,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   114,
     115,     0,     0,     0,   175,   116,     0,   117,   118,   119,
     103,   104,   105,   106,     0,   107,   108,   109,     0,   205,
       0,     0,     0,     0,     0,     0,     0,     0,   110,   111,
     112,   113,   114,   115,     0,     0,     0,     0,   116,     0,
     117,   118,   119,   103,   104,   105,   106,     0,   107,   108,
     109,     0,     0,     0,   263,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,     0,     0,     0,
       0,   116,     0,   117,   118,   119,   103,   104,   105,   106,
       0,   107,   108,   109,     0,   301,     0,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
       0,     0,     0,     0,   116,     0,   117,   118,   119,   103,
     104,   105,   106,     0,   107,   108,   109,     0,     0,     0,
       0,     0,     0,   362,     0,     0,     0,   110,   111,   112,
     113,   114,   115,     0,     0,     0,     0,   116,     0,   117,
     118,   119,   103,   104,   105,   106,     0,   107,   108,   109,
       0,     0,     0,     0,     0,   363,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,     0,     0,     0,     0,
     116,     0,   117,   118,   119,   103,   104,   105,   106,     0,
     107,   108,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,   115,     0,
       0,     0,     0,   116,     0,   117,   118,   119,   103,   104,
     105,     0,     0,   107,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   111,   112,   113,
     114,   115,     0,     0,     0,     0,     0,     0,   117,   118,
     119,   103,     0,   105,     0,     0,   107,   108,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,     0,     0,     0,     0,     0,
       0,   117,   118,   119,   103,   104,   105,   106,     0,   107,
     108,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   103,     0,   113,   114,   115,   107,   108,
     109,     0,   116,     0,   117,   118,   119,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,   107,   108,   109,
       0,     0,     0,   117,   118,   119,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,   107,   108,     0,     0,
       0,     0,   117,   118,   119,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,     0,     0,     0,     0,     0,
       0,     0,   118,   119
  };

  const short int
  Parser::yycheck_[] =
  {
       7,    14,    29,    30,     1,    32,   131,     3,    17,    19,
       1,   225,    17,     0,    42,    17,    17,    17,    17,    44,
      17,   235,   236,   138,    31,    43,    17,    52,    41,    36,
      37,    38,    39,    40,    62,    55,    44,    53,    47,    61,
      45,    43,    62,    59,    52,    45,    40,    41,    45,    45,
     120,    46,    61,     3,    45,   125,    49,    52,    43,    61,
      61,    55,    56,    57,    58,    48,    52,    76,    54,    52,
     185,    76,    82,   188,    76,    76,    76,    76,    46,    76,
      46,    46,    42,    46,    52,    76,    52,    52,    95,    52,
      49,    42,   217,    17,    17,    17,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    46,    44,    46,    62,   125,    52,
      52,    48,   135,    62,    58,   138,     4,     5,     6,     7,
       8,    44,   139,   140,   141,   142,   143,   252,   253,   254,
     265,    47,   149,   150,    52,   187,    44,     0,     1,    42,
       2,     4,     5,     6,     7,     8,    55,    56,    57,    58,
      55,    62,    64,    15,    16,    17,    18,    19,   175,   176,
     180,    55,   185,    42,    12,   188,    28,    29,    30,    14,
      32,    42,   224,   225,    17,    17,    48,    69,   230,   231,
      42,    10,    45,   235,   236,    62,    47,    47,     9,    25,
     227,   228,   229,   210,    47,    54,    48,    20,    49,   324,
     220,   326,     1,    49,    48,     4,     5,     6,     7,     8,
     270,    73,   136,   347,   205,   232,   233,   350,   254,   177,
      82,   273,    78,   275,   198,   217,    73,    -1,    -1,   252,
     253,   254,    -1,   285,    -1,   287,    -1,   289,   255,    -1,
     257,   258,   259,   260,   261,    -1,    45,    -1,    -1,    -1,
     267,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     122,   187,   314,    -1,    -1,    -1,    -1,    -1,    -1,   131,
      -1,   288,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   187,    -1,    -1,   338,   339,    -1,   341,
     342,    -1,    -1,    -1,   311,   312,   313,    -1,    -1,    -1,
      -1,   324,    -1,   326,   230,    -1,   358,   359,    -1,    -1,
     362,    -1,    -1,   365,    -1,   332,   333,    -1,   180,    -1,
     224,   225,    -1,   340,   186,    -1,   230,   231,    -1,    -1,
     347,   235,   236,    -1,    -1,    -1,   198,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   273,    -1,   275,
      -1,    -1,    -1,    -1,    -1,   217,    -1,    -1,   220,   285,
      -1,   287,    -1,   289,    -1,   227,   228,   229,    -1,   273,
      -1,   275,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   285,    -1,   287,    -1,   289,    -1,    -1,   314,    25,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,   265,    40,    41,    42,    -1,   270,    -1,
     314,    -1,   338,   339,    -1,   341,   342,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,   358,   359,   338,   339,   362,   341,   342,   365,
      -1,    -1,   304,    -1,    -1,    -1,    -1,     1,    -1,    -1,
      -1,    -1,    -1,    -1,   358,   359,    -1,    -1,   362,    -1,
      -1,   365,    16,    17,    18,    19,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    28,    -1,    30,    -1,    32,    33,
      34,    -1,    -1,    -1,    -1,    39,    40,    41,    -1,    43,
      -1,    45,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,     1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    16,    17,    18,    19,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    34,    -1,    -1,    -1,    -1,    39,    40,    41,    -1,
      43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,    61,     1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    16,    17,    18,    19,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,    40,    41,
      -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    16,    17,    18,    19,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    32,    33,    34,    -1,    -1,    -1,     1,    39,    40,
      41,    -1,    43,    44,    45,    -1,    -1,    11,    -1,    13,
      51,    15,    16,    17,    18,    19,    20,    -1,    22,    23,
      61,    -1,    26,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    -1,     1,    -1,    43,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    11,    -1,    13,
      -1,    15,    16,    17,    18,    19,    20,    61,    22,    23,
      -1,    -1,    26,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    76,    -1,     1,    -1,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    47,    11,    -1,    13,    -1,    15,    16,
      17,    18,    19,    20,    -1,    22,    23,    61,    -1,    26,
      -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,
      -1,     1,    76,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      47,    11,    -1,    13,    -1,    15,    16,    17,    18,    19,
      20,    -1,    22,    23,    61,    -1,    26,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    47,    11,    12,
      13,    -1,    15,    16,    17,    18,    19,    20,    -1,    22,
      23,    61,    -1,    26,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    47,    11,    -1,    13,    14,    15,
      16,    17,    18,    19,    20,    -1,    22,    23,    61,    -1,
      26,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    47,    11,    -1,    13,    -1,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    61,    -1,    26,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,    48,
      -1,    -1,    11,    -1,    13,    -1,    15,    16,    17,    18,
      19,    20,    61,    22,    23,    -1,    -1,    26,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,    11,
      -1,    13,    -1,    15,    16,    17,    18,    19,    20,    -1,
      22,    23,    61,    -1,    26,    -1,    -1,    -1,    -1,    68,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    43,    -1,    -1,    -1,    47,    16,    17,    18,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    61,
      30,    -1,    32,    33,    34,    -1,    68,    -1,    -1,    39,
      40,    41,    -1,    43,    76,    45,    -1,    -1,    48,    -1,
      50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    16,    17,    18,
      19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,    40,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    16,    17,
      18,    19,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,    40,    41,    -1,    43,    17,    45,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    35,    36,    37,    38,    -1,    40,
      41,    42,    70,    71,    72,    73,    74,    75,    76,    17,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    21,    -1,    -1,    -1,    63,    -1,    65,    66,    67,
      -1,    31,    -1,    -1,    -1,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    21,
      -1,    -1,    -1,    63,    -1,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    21,    -1,    -1,
      -1,    63,    -1,    65,    66,    67,    -1,    -1,    -1,    -1,
      -1,    35,    36,    37,    38,    -1,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    21,    -1,    -1,    -1,    63,
      -1,    65,    66,    67,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    24,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,    -1,    -1,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    24,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    -1,    -1,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    27,    -1,    -1,    63,    -1,    65,
      66,    67,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    29,
      63,    -1,    65,    66,    67,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    63,    31,    65,    66,    67,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,    66,
      67,    35,    36,    37,    38,    -1,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      -1,    65,    66,    67,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    60,
      -1,    -1,    63,    -1,    65,    66,    67,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    62,    63,    -1,    65,    66,    67,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,
      65,    66,    67,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    -1,    65,    66,    67,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    -1,    65,    66,    67,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      63,    -1,    65,    66,    67,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    63,    -1,    65,    66,    67,    35,    36,
      37,    -1,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    35,    -1,    37,    -1,    -1,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    65,    66,    67,    35,    36,    37,    38,    -1,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    35,    -1,    56,    57,    58,    40,    41,
      42,    -1,    63,    -1,    65,    66,    67,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    40,    41,    42,
      -1,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    40,    41,    -1,    -1,
      -1,    -1,    65,    66,    67,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    45,    82,    83,    17,    76,   147,   154,   155,
     156,   157,     0,     1,     4,     5,     6,     7,     8,    45,
      84,    85,    86,    87,    88,    89,    90,    91,    16,    18,
      19,    23,    30,    32,    33,    34,    39,    40,    41,    43,
      45,    51,    61,    70,    71,    72,    73,    74,    75,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   147,
     148,   149,    46,    52,    47,   148,   147,   147,   147,   147,
     154,    85,    45,   147,   150,   151,   152,   152,   152,   110,
     152,   110,   110,   110,     1,    55,   110,     1,    46,   109,
     110,   148,   147,    35,    36,    37,    38,    40,    41,    42,
      53,    54,    55,    56,    57,    58,    63,    65,    66,    67,
      43,   136,    61,     3,   155,    43,   110,   137,   144,   145,
     146,    43,   141,    42,   141,    49,    46,   154,    49,    42,
      17,    17,    24,    17,    44,   110,    44,    46,    46,    52,
      60,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   110,   110,   110,   110,   110,   110,   110,     1,    44,
     109,   110,   147,   109,   110,    62,    62,    52,    48,     1,
      45,   140,   147,   151,   153,    62,    47,    42,    62,   131,
     132,   133,   134,   135,   138,   139,   148,    86,    46,   131,
     110,   110,   110,   110,   110,    44,   110,   110,    44,    44,
      52,   110,   110,   145,    44,   154,    44,    52,   131,     1,
      45,    92,    93,   147,    11,    13,    15,    16,    18,    19,
      20,    22,    23,    26,    43,    47,    68,    94,    96,    97,
      98,   101,   102,   103,   104,   105,   106,   107,   108,   112,
     113,   131,    55,    62,    53,    59,   150,    17,    29,    21,
      25,    31,   136,    46,   110,    46,   153,    42,   154,    48,
      52,     1,    94,    95,     1,    95,   152,   152,   152,    94,
     112,   113,   110,   110,     1,    95,     1,    95,    64,    42,
     131,   131,   130,   131,   139,   110,   110,   110,   110,   110,
     110,    44,   151,   110,    46,    92,    12,    12,    94,    14,
      14,    42,    17,    17,    24,    27,    48,    48,    69,    69,
     110,    94,    10,   142,    52,    54,    62,   147,   110,   110,
     110,    94,    47,    47,     9,   143,   131,   131,    17,    21,
      31,    21,    25,     1,    28,    50,    99,   100,   110,   110,
      47,    54,    94,    94,   110,    94,    94,    48,    49,    49,
      48,    99,    49,    48,   146,    21,    94,    94,    94,    48,
      94
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    81,    82,    83,    83,    84,    84,    85,    85,    85,
      86,    86,    86,    86,    87,    88,    89,    89,    90,    90,
      91,    91,    92,    92,    92,    93,    93,    94,    94,    94,
      94,    94,    94,    94,    94,    94,    94,    94,    95,    95,
      96,    97,    97,    98,    98,    99,    99,    99,   100,   100,
     101,   102,   102,   103,   104,   105,   105,   105,   105,   106,
     106,   106,   106,   107,   108,   108,   108,   108,   109,   109,
     110,   110,   110,   110,   110,   110,   110,   110,   110,   110,
     110,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   111,
     111,   111,   111,   112,   112,   113,   114,   115,   116,   117,
     118,   119,   119,   119,   120,   121,   121,   121,   121,   121,
     121,   121,   121,   122,   123,   123,   124,   125,   126,   127,
     127,   128,   129,   130,   130,   131,   131,   131,   131,   132,
     133,   134,   135,   136,   136,   136,   137,   138,   138,   139,
     139,   140,   140,   141,   141,   141,   142,   142,   143,   143,
     144,   144,   145,   145,   145,   146,   146,   147,   147,   148,
     148,   149,   149,   150,   150,   151,   152,   152,   153,   153,
     154,   154,   155,   155,   156,   157
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
       3,     3,     3,     3,     2,     1,     2,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     1,     2,     5,     6,     6,     6,     6,
       6,     2,     3,     3,     5,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     3,     1,     1,     1,     1,     1,     1,
       4,     6,     3,     3,     3,     2,     5,     3,     1,     1,
       0,     3,     1,     3,     3,     0,     4,     0,     4,     0,
       3,     1,     1,     3,     3,     1,     0,     1,     1,     1,
       2,     3,     1,     1,     1,     3,     4,     1,     4,     1,
       3,     1,     1,     1,     1,     2
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
  "ProgramFunctionDefinition", "EnumeratorDefinition", "Enumerators",
  "Rule", "Rules", "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel",
  "CaseLabels", "LetRule", "ForallRule", "ChooseRule", "IterateRule",
  "BlockRule", "SequenceRule", "UpdateRule", "CallRule", "Terms", "Term",
  "Expression", "DirectCallExpression", "IndirectCallExpression",
  "LetExpression", "ConditionalExpression", "ChooseExpression",
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
       0,   375,   375,   384,   390,   398,   404,   414,   420,   424,
     432,   436,   440,   444,   452,   460,   468,   473,   482,   498,
     506,   529,   547,   551,   557,   565,   571,   585,   589,   593,
     597,   601,   605,   609,   613,   617,   621,   625,   633,   639,
     649,   657,   661,   669,   673,   681,   685,   689,   697,   703,
     713,   721,   725,   733,   741,   749,   753,   757,   762,   771,
     775,   779,   784,   793,   803,   807,   811,   815,   827,   833,
     843,   847,   851,   855,   859,   863,   867,   871,   875,   879,
     883,   895,   899,   903,   907,   911,   915,   919,   923,   927,
     931,   935,   939,   943,   947,   951,   955,   959,   963,   967,
     971,   975,   979,   987,   992,  1000,  1008,  1016,  1024,  1032,
    1040,  1050,  1055,  1059,  1067,  1079,  1083,  1087,  1091,  1095,
    1099,  1103,  1107,  1115,  1123,  1128,  1137,  1153,  1169,  1185,
    1197,  1213,  1229,  1241,  1247,  1257,  1261,  1265,  1269,  1277,
    1285,  1293,  1301,  1313,  1317,  1321,  1330,  1344,  1350,  1360,
    1364,  1372,  1378,  1388,  1392,  1396,  1408,  1412,  1420,  1424,
    1432,  1438,  1448,  1456,  1466,  1477,  1481,  1493,  1497,  1505,
    1509,  1519,  1525,  1539,  1543,  1552,  1560,  1566,  1574,  1580,
    1592,  1598,  1607,  1611,  1619,  1627
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
#line 3972 "GrammarParser.cpp" // lalr1.cc:1167
#line 1633 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
