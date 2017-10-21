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
      case 150: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 151: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 152: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 106: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 146: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 149: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 140: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 139: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 141: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 131: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 144: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 107: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 130: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 138: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 83: // Definition
      case 84: // AttributedDefinition
        value.move< Definition::Ptr > (that.value);
        break;

      case 85: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 95: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 127: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 96: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 133: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // MaybeDefined
      case 111: // Atom
      case 120: // Term
      case 121: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 153: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 124: // Terms
      case 125: // Arguments
      case 126: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 109: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 143: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 86: // FunctionDefinition
      case 91: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 97: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 100: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 98: // Identifiers
      case 99: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 128: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 145: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 129: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 142: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 123: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 87: // MaybeInitially
      case 93: // Initializers
      case 94: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 103: // Parameters
      case 104: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 122: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 119: // Reference
        value.move< ReferenceAtom::Ptr > (that.value);
        break;

      case 108: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 135: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 134: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 136: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 147: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 137: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 89: // FunctionParameters
      case 90: // MaybeFunctionParameters
      case 110: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 112: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 132: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 92: // Initializer
      case 148: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 113: // Boolean
      case 114: // String
      case 115: // BitNumber
      case 116: // IntegerNumber
      case 117: // FloatingNumber
      case 118: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 101: // Variable
      case 102: // AttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 105: // Type
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
      case 150: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 151: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 152: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 106: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 146: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 149: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 140: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 139: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 141: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 131: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 144: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 107: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 130: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 138: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 83: // Definition
      case 84: // AttributedDefinition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 85: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 95: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 127: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 96: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 133: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // MaybeDefined
      case 111: // Atom
      case 120: // Term
      case 121: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 153: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 124: // Terms
      case 125: // Arguments
      case 126: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 109: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 143: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 86: // FunctionDefinition
      case 91: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 97: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 100: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 98: // Identifiers
      case 99: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 128: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 145: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 129: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 142: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 123: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 87: // MaybeInitially
      case 93: // Initializers
      case 94: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 103: // Parameters
      case 104: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 122: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 119: // Reference
        value.copy< ReferenceAtom::Ptr > (that.value);
        break;

      case 108: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 135: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 134: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 136: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 147: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 137: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 89: // FunctionParameters
      case 90: // MaybeFunctionParameters
      case 110: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 112: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 132: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 92: // Initializer
      case 148: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 113: // Boolean
      case 114: // String
      case 115: // BitNumber
      case 116: // IntegerNumber
      case 117: // FloatingNumber
      case 118: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 101: // Variable
      case 102: // AttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 105: // Type
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
      case 150: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 151: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 152: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 106: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 146: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 149: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 140: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 139: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 141: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 131: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 144: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 107: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 130: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 138: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 83: // Definition
      case 84: // AttributedDefinition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 85: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 95: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 127: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 96: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 133: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 88: // MaybeDefined
      case 111: // Atom
      case 120: // Term
      case 121: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 153: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 124: // Terms
      case 125: // Arguments
      case 126: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 109: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 143: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 86: // FunctionDefinition
      case 91: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 97: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 100: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 98: // Identifiers
      case 99: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 128: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 145: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 129: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 142: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 123: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 87: // MaybeInitially
      case 93: // Initializers
      case 94: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 103: // Parameters
      case 104: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 122: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 119: // Reference
        yylhs.value.build< ReferenceAtom::Ptr > ();
        break;

      case 108: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 135: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 134: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 136: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 147: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 137: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 82: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 89: // FunctionParameters
      case 90: // MaybeFunctionParameters
      case 110: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 112: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 132: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 92: // Initializer
      case 148: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 113: // Boolean
      case 114: // String
      case 115: // BitNumber
      case 116: // IntegerNumber
      case 117: // FloatingNumber
      case 118: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 101: // Variable
      case 102: // AttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 105: // Type
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
#line 371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      specification.setDefinitions( yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1310 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 379 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1318 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 383 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1326 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 387 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1334 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1342 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 405 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 409 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1378 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 423 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 433 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 449 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1416 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 457 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1424 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 469 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1440 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 473 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1448 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 481 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1458 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 487 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1468 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1476 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 501 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 1484 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
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
#line 1511 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
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
#line 1529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 550 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1541 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 568 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1566 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 579 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1576 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 585 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1586 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 595 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1594 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1602 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 607 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1610 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Identifiers::Ptr > () );
  }
#line 1618 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 623 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1626 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 627 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 1634 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 635 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 641 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1654 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1664 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 657 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1674 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 667 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 1682 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::RELATIVE );
  }
#line 1690 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 679 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1698 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 683 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 1707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 1717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 698 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 1725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 706 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1735 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1745 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 722 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1753 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 1761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 730 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1769 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 738 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1777 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 742 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1785 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 746 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 1793 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< libcasm_fe::Ast::Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1801 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 758 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 1809 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 766 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1817 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 774 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< libcasm_fe::Ast::Type::Ptr > () );
  }
#line 1825 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 782 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1833 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 790 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1843 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 796 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< libcasm_fe::Ast::Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1853 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 806 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 1861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 810 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 814 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 818 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 822 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 826 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1901 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 830 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 834 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 842 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1925 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 850 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1934 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 855 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1943 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 864 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1959 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 880 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1975 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 892 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1991 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 908 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 940 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2039 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2047 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 964 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2055 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2063 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 972 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2071 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2079 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 980 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2087 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 984 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2095 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 988 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2103 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 992 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 996 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 1000 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 1004 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 1012 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 1016 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 1020 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1028 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1032 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1036 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1040 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2199 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1044 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2207 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1048 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1052 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1056 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2231 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1060 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1064 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1068 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1072 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1076 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1080 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1084 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2287 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1092 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1096 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1104 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1112 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1117 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1121 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1129 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2354 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1135 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1145 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2372 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1149 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2380 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1153 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1162 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[3].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1172 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1177 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2416 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1185 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2424 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1193 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1201 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2440 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1209 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2448 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1217 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2456 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1225 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2464 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1233 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< libcasm_fe::Ast::Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2482 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1247 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2490 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1251 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2498 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1255 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2506 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1259 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2514 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1263 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2522 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1267 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 2530 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1271 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2538 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1275 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2546 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1279 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2554 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1283 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1287 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2570 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1295 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1301 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2590 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1311 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 2598 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1319 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2606 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1323 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2614 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1331 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2622 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1335 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 2630 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1343 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2638 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1347 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2646 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1351 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2654 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1359 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2664 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1365 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2674 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1375 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2682 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1383 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2690 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1387 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[6].value.as< VariableDefinition::Ptr > (), yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2698 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1395 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2706 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1403 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2714 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1411 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2722 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1415 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2730 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1419 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2739 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1433 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1437 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1441 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1465 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2802 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1471 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2823 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2834 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1495 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2842 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2850 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1507 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2860 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2870 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1523 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2878 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -182;

  const signed char Parser::yytable_ninf_ = -60;

  const short int
  Parser::yypact_[] =
  {
       5,    38,    36,  -182,    -7,     3,     3,     3,     3,     3,
    -182,  -182,   115,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
     992,     3,  -182,  -182,   -56,  -182,     9,     8,     9,    19,
    1053,  -182,   -25,  -182,  -182,  -182,    -4,    -4,    -4,  1053,
      -4,  -182,  -182,  -182,  1053,  1053,  1053,   475,   536,    -5,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,    28,    57,    63,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  1501,
    -182,  -182,  -182,    52,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,     3,     6,    62,    78,   -14,    -5,   475,  1765,
     167,     3,     3,    90,  -182,   100,   134,   135,  1300,   138,
    -182,  -182,  -182,   123,  1053,  1534,   124,   113,  -182,  1567,
       7,  -182,   992,  -182,   597,  -182,  1053,  1053,  1053,  1053,
    1053,  1053,  1053,  1053,  1053,  1053,  1053,  1053,  1053,  1053,
    1053,  1053,  1053,  1053,  1053,  -182,   136,  -182,    13,    -5,
       3,   899,    -5,   128,   120,    54,  -182,  -182,  -182,  -182,
    -182,  1534,  -182,  -182,    89,    -5,  1053,  1053,  1053,  1053,
    1053,  -182,  1600,  -182,  1053,  -182,  1053,  -182,  1053,  -182,
     140,  -182,  1765,    29,    91,  1831,  1883,  1798,   107,   107,
     222,    20,    20,   129,   129,   129,  -182,  1765,  1798,   222,
      20,    20,  1765,  -182,  -182,    -4,   146,  -182,   102,   352,
     634,  -182,    -4,    -4,    -4,   899,    -6,  1053,  1053,   137,
     674,   711,   125,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,   148,    -5,    -5,    -5,
    1053,     3,  -182,  1080,  1435,  1189,  1369,  1468,    63,  1633,
    1666,  1765,  -182,  -182,  -182,  1053,  -182,     3,   179,  -182,
     748,   180,   785,   151,   178,   181,  -182,  -182,  -182,  1335,
    1402,   149,   822,   130,   862,  1053,   899,  -182,   186,   141,
     -28,   127,  1864,  -182,  1053,  1053,  1053,  1053,  1053,  -182,
    -182,  -182,  1765,  -182,  -182,  -182,  -182,  -182,  -182,  1053,
    1053,  1053,   899,   157,  -182,  -182,  -182,  -182,  1765,  -182,
     158,   200,    -5,    -5,  -182,  1765,  1765,  1765,  1765,  1765,
    1113,  1151,  1227,   185,   414,  1053,   164,  -182,   160,  -182,
     899,   899,  1053,   899,   899,   168,   169,   170,  1699,   931,
     172,  1732,   992,  -182,  -182,  -182,  1265,  -182,  -182,  -182,
     899,   899,   899,  -182,  -182,  -182,   174,   899,  -182,  -182,
    -182,  -182,  -182
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     9,     0,     0,     0,     0,     0,     0,
       8,    11,     0,     3,    13,     4,     6,     5,     1,    34,
      30,     0,    33,    38,    39,    22,    49,     0,    49,     0,
     176,   175,     0,   172,   173,    10,     0,     0,     0,     0,
       0,    68,    70,    69,     0,     0,     0,     0,     0,     0,
      72,    73,    74,    76,    75,    71,    28,    29,     0,   121,
      88,    66,    67,    65,    61,    62,    63,    64,    60,    24,
      85,    87,    86,     0,    78,    79,    80,    81,    82,    83,
      84,    40,     0,     0,     0,     0,     0,    21,     0,   177,
       0,     0,     0,    42,    44,     0,     0,     0,     0,     0,
     110,    91,    92,     0,     0,   116,     0,     0,   112,   116,
       0,    77,     0,    23,     0,   122,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    37,     0,    46,     0,     0,
       0,     0,     0,    20,     0,    54,    19,    50,    51,    52,
      53,     0,     7,   174,     0,     0,     0,     0,     0,     0,
       0,    90,     0,    89,     0,   114,     0,   113,     0,    27,
       0,   119,   116,     0,   107,   105,   106,   109,    93,    94,
     100,   101,   102,    95,    96,    97,    98,    25,   108,    99,
     103,   104,    26,    48,    47,     0,     0,    36,     0,     0,
       0,   144,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   169,   171,   129,   131,   132,   133,   134,   135,
     136,   137,   138,   139,   140,   141,     0,     0,     0,    21,
       0,     0,    41,     0,     0,     0,     0,     0,     0,   115,
       0,   115,   118,   117,    45,     0,    32,     0,     0,   143,
       0,     0,     0,     0,     0,     0,   158,   168,   170,     0,
       0,     0,     0,     0,     0,     0,     0,    18,    17,     0,
      19,     0,    57,    43,     0,     0,     0,     0,     0,   123,
     120,   111,    31,    35,   166,   164,   142,   162,   160,     0,
       0,     0,     0,     0,   161,   159,   165,   163,   167,   130,
       0,    15,     0,     0,    55,   124,   127,   126,   125,   128,
       0,     0,     0,   145,     0,     0,     0,    12,     0,    58,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   153,
       0,     0,    30,    56,   154,   155,     0,   157,   146,   148,
       0,     0,     0,   152,   147,    16,     0,     0,   149,   150,
     151,    14,   156
  };

  const short int
  Parser::yypgoto_[] =
  {
    -182,  -182,   133,   205,  -182,  -182,  -182,  -182,  -182,     4,
    -182,   112,  -182,  -101,  -182,  -182,    26,  -182,   211,    -2,
      10,   -34,  -182,   206,  -117,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,   -30,
    -182,  -182,  -182,   -47,    -1,  -182,     2,    98,  -182,  -182,
    -182,  -182,  -182,  -182,    65,  -181,  -182,  -182,  -182,  -182,
     -93,  -182,  -182,  -182,  -182,  -182,  -182,  -182,  -182,   147,
     150,  -182,  -182
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,    10,    11,    12,    13,   317,   301,   143,   144,
      14,    56,    57,    58,    15,    16,    23,   198,    24,    59,
      94,    95,   138,    84,   146,   147,   148,   149,   150,   271,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,   106,   115,    73,    74,    75,    76,    77,
      78,    79,    80,    17,   249,   250,   215,   216,   217,   329,
     330,   218,   219,   220,   221,   222,   223,   224,   225,    31,
      32,    33,    34
  };

  const short int
  Parser::yytable_[] =
  {
      89,   110,    25,    96,    97,    82,    99,   136,     1,    98,
      19,    19,    19,    19,   100,   101,   102,   105,   109,   252,
      19,    90,   196,    19,   -59,   226,   -59,    91,   141,   262,
     264,    26,    27,    28,    29,    30,    18,   209,   232,     3,
      20,    92,     4,     5,     6,     7,     8,   111,   142,   137,
      85,    92,    83,   167,    21,    21,    21,   194,   151,   168,
     120,   121,    93,    93,    93,   195,    93,   173,    87,    22,
      22,    22,    22,   243,   162,   125,   126,   127,   128,    22,
     112,   168,    22,     9,   172,   145,   174,   175,   176,   177,
     178,   179,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   113,   114,   229,   135,    93,
     267,   268,   270,   230,   134,    -2,     3,    30,    30,     4,
       5,     6,     7,     8,   139,   140,   233,   234,   235,   236,
     237,   120,   121,   122,   239,   231,   240,   145,   241,   155,
     145,    91,   156,   212,   123,   124,   125,   126,   127,   128,
     246,   157,   158,   145,   247,   160,   131,   132,   133,   165,
       9,   244,   125,   126,   127,   128,   197,   161,   253,   254,
     255,     4,     5,     6,     7,     8,   164,   259,   260,   303,
     193,   304,   228,   227,   242,   318,   319,   128,   245,   265,
     266,   284,   104,   289,   287,   290,   300,   294,   291,   296,
     272,   212,   212,   302,   314,   315,   214,   212,   257,   316,
     324,   332,   212,   212,   333,   282,   339,    35,   340,   341,
     344,    93,   351,   152,   169,   145,   145,   145,    93,    93,
      93,   346,    81,   269,    86,   298,   343,   279,   153,   213,
       0,   273,   154,     0,   305,   306,   307,   308,   309,     0,
       0,     0,   212,     0,   212,     0,     0,    93,     0,   310,
     311,   312,   120,   121,   212,     0,   212,     0,   212,     0,
     256,     0,     0,   283,     0,   123,   124,   125,   126,   127,
     128,     0,     0,     0,   328,   331,     0,     0,   132,   133,
       0,     0,   336,     0,   212,     0,     0,   213,   213,   328,
     145,   145,     0,   213,   258,     0,     0,     0,   213,   213,
       0,     0,     0,     0,     0,   286,     0,   286,     0,     0,
       0,     0,   212,   212,     0,   212,   212,   286,     0,   286,
       0,   299,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   212,   212,   212,     0,     0,     0,   213,   212,
     213,     0,     0,   248,     0,     0,     0,   313,     0,     0,
     213,     0,   213,   199,   213,   200,     0,   201,   202,    19,
     203,   204,   205,     0,   206,   207,     0,     0,   208,     0,
       0,     0,     0,     0,     0,   334,   335,     0,   337,   338,
     213,     0,     0,     0,     0,   209,     0,     0,     0,   210,
       0,     0,     0,     0,     0,   348,   349,   350,     0,     0,
       0,     0,   352,    21,     0,   325,     0,     0,   213,   213,
     211,   213,   213,     0,     0,     0,     0,     0,    22,     0,
      36,    19,    37,    38,     0,     0,     0,    39,   213,   213,
     213,     0,   326,     0,    40,   213,    41,    42,    43,     0,
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
       0,     0,     0,     0,     0,     0,     0,    21,   170,     0,
       0,     0,     0,     0,     0,     0,    50,    51,    52,    53,
      54,    55,    22,    36,    19,    37,    38,     0,     0,     0,
      39,     0,     0,     0,     0,     0,     0,    40,     0,    41,
      42,    43,     0,     0,     0,   251,    44,    45,    46,     0,
      88,   171,    48,     0,     0,   199,     0,   200,    49,   201,
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
       0,     0,     0,     0,    21,   116,   117,   118,   119,     0,
     120,   121,   122,    50,    51,    52,    53,    54,    55,    22,
     320,     0,     0,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,   130,     0,   131,   132,   133,   116,   117,
     118,   119,     0,   120,   121,   122,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   123,   124,   125,   126,
     127,   128,   321,     0,     0,     0,   130,     0,   131,   132,
     133,     0,   322,     0,     0,     0,   116,   117,   118,   119,
       0,   120,   121,   122,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   123,   124,   125,   126,   127,   128,
     276,     0,     0,     0,   130,     0,   131,   132,   133,     0,
       0,     0,     0,     0,   116,   117,   118,   119,     0,   120,
     121,   122,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   123,   124,   125,   126,   127,   128,   323,     0,
       0,     0,   130,     0,   131,   132,   133,     0,     0,     0,
       0,     0,   116,   117,   118,   119,     0,   120,   121,   122,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     123,   124,   125,   126,   127,   128,   347,     0,     0,     0,
     130,     0,   131,   132,   133,     0,     0,     0,     0,     0,
     116,   117,   118,   119,     0,   120,   121,   122,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   123,   124,
     125,   126,   127,   128,   159,     0,     0,     0,   130,     0,
     131,   132,   133,     0,     0,   116,   117,   118,   119,     0,
     120,   121,   122,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   123,   124,   125,   126,   127,   128,   292,
       0,     0,     0,   130,     0,   131,   132,   133,     0,     0,
     116,   117,   118,   119,     0,   120,   121,   122,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   123,   124,
     125,   126,   127,   128,   277,     0,     0,     0,   130,     0,
     131,   132,   133,     0,   116,   117,   118,   119,     0,   120,
     121,   122,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   123,   124,   125,   126,   127,   128,     0,   293,
       0,     0,   130,     0,   131,   132,   133,   116,   117,   118,
     119,     0,   120,   121,   122,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   123,   124,   125,   126,   127,
     128,     0,     0,     0,   275,   130,     0,   131,   132,   133,
     116,   117,   118,   119,     0,   120,   121,   122,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   123,   124,
     125,   126,   127,   128,     0,     0,     0,     0,   130,   278,
     131,   132,   133,   116,   117,   118,   119,     0,   120,   121,
     122,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   123,   124,   125,   126,   127,   128,     0,     0,     0,
       0,   130,     0,   131,   132,   133,   116,   117,   118,   119,
       0,   120,   121,   122,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   123,   124,   125,   126,   127,   128,
       0,     0,     0,   129,   130,     0,   131,   132,   133,   116,
     117,   118,   119,     0,   120,   121,   122,     0,   163,     0,
       0,     0,     0,     0,     0,     0,     0,   123,   124,   125,
     126,   127,   128,     0,     0,     0,     0,   130,     0,   131,
     132,   133,   116,   117,   118,   119,     0,   120,   121,   122,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     123,   124,   125,   126,   127,   128,     0,   166,     0,     0,
     130,     0,   131,   132,   133,   116,   117,   118,   119,     0,
     120,   121,   122,     0,   238,     0,     0,     0,     0,     0,
       0,     0,     0,   123,   124,   125,   126,   127,   128,     0,
       0,     0,     0,   130,     0,   131,   132,   133,   116,   117,
     118,   119,     0,   120,   121,   122,     0,   280,     0,     0,
       0,     0,     0,     0,     0,     0,   123,   124,   125,   126,
     127,   128,     0,     0,     0,     0,   130,     0,   131,   132,
     133,   116,   117,   118,   119,     0,   120,   121,   122,     0,
       0,     0,   281,     0,     0,     0,     0,     0,     0,   123,
     124,   125,   126,   127,   128,     0,     0,     0,     0,   130,
       0,   131,   132,   133,   116,   117,   118,   119,     0,   120,
     121,   122,     0,     0,     0,     0,     0,     0,   342,     0,
       0,     0,   123,   124,   125,   126,   127,   128,     0,     0,
       0,     0,   130,     0,   131,   132,   133,   116,   117,   118,
     119,     0,   120,   121,   122,     0,     0,     0,     0,     0,
     345,     0,     0,     0,     0,   123,   124,   125,   126,   127,
     128,     0,     0,     0,     0,   130,     0,   131,   132,   133,
     116,   117,   118,   119,     0,   120,   121,   122,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   123,   124,
     125,   126,   127,   128,     0,     0,     0,     0,   130,     0,
     131,   132,   133,   116,   117,   118,     0,     0,   120,   121,
     122,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   123,   124,   125,   126,   127,   128,     0,     0,     0,
       0,     0,     0,   131,   132,   133,   116,     0,   118,     0,
       0,   120,   121,   122,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   123,   124,   125,   126,   127,   128,
       0,     0,     0,     0,     0,     0,   131,   132,   133,   116,
     117,   118,   119,     0,   120,   121,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   123,   116,     0,
     126,   127,   128,   120,   121,   122,     0,   130,     0,   131,
     132,   133,     0,     0,     0,     0,   123,   124,   125,   126,
     127,   128,     0,     0,     0,     0,     0,     0,   131,   132,
     133
  };

  const short int
  Parser::yycheck_[] =
  {
      30,    48,     4,    37,    38,    61,    40,     1,     3,    39,
      17,    17,    17,    17,    44,    45,    46,    47,    48,   200,
      17,    46,   139,    17,    52,   142,    54,    52,    42,   210,
     211,     5,     6,     7,     8,     9,     0,    43,   155,     1,
      47,    45,     4,     5,     6,     7,     8,    49,    62,    83,
      42,    45,    43,    46,    61,    61,    61,    44,    88,    52,
      40,    41,    36,    37,    38,    52,    40,   114,    49,    76,
      76,    76,    76,    44,   104,    55,    56,    57,    58,    76,
      52,    52,    76,    45,   114,    87,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   133,   134,    48,    43,    53,    82,    83,
     227,   228,   229,    59,    62,     0,     1,    91,    92,     4,
       5,     6,     7,     8,    62,    47,   156,   157,   158,   159,
     160,    40,    41,    42,   164,    46,   166,   139,   168,    49,
     142,    52,    42,   141,    53,    54,    55,    56,    57,    58,
      48,    17,    17,   155,    52,    17,    65,    66,    67,    46,
      45,   195,    55,    56,    57,    58,   140,    44,   202,   203,
     204,     4,     5,     6,     7,     8,    52,   207,   208,    52,
      44,    54,    62,    55,    44,   302,   303,    58,    42,    64,
      42,    12,    55,    42,    14,    17,    10,    48,    17,    69,
     230,   199,   200,    62,    47,    47,   141,   205,   206,     9,
      25,    47,   210,   211,    54,   245,    48,    12,    49,    49,
      48,   195,    48,    90,   112,   227,   228,   229,   202,   203,
     204,   332,    21,   229,    28,   265,   329,   238,    91,   141,
      -1,   231,    92,    -1,   274,   275,   276,   277,   278,    -1,
      -1,    -1,   250,    -1,   252,    -1,    -1,   231,    -1,   289,
     290,   291,    40,    41,   262,    -1,   264,    -1,   266,    -1,
     205,    -1,    -1,   247,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,   314,   315,    -1,    -1,    66,    67,
      -1,    -1,   322,    -1,   292,    -1,    -1,   199,   200,   329,
     302,   303,    -1,   205,   206,    -1,    -1,    -1,   210,   211,
      -1,    -1,    -1,    -1,    -1,   250,    -1,   252,    -1,    -1,
      -1,    -1,   320,   321,    -1,   323,   324,   262,    -1,   264,
      -1,   266,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   340,   341,   342,    -1,    -1,    -1,   250,   347,
     252,    -1,    -1,     1,    -1,    -1,    -1,   292,    -1,    -1,
     262,    -1,   264,    11,   266,    13,    -1,    15,    16,    17,
      18,    19,    20,    -1,    22,    23,    -1,    -1,    26,    -1,
      -1,    -1,    -1,    -1,    -1,   320,   321,    -1,   323,   324,
     292,    -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,   340,   341,   342,    -1,    -1,
      -1,    -1,   347,    61,    -1,     1,    -1,    -1,   320,   321,
      68,   323,   324,    -1,    -1,    -1,    -1,    -1,    76,    -1,
      16,    17,    18,    19,    -1,    -1,    -1,    23,   340,   341,
     342,    -1,    28,    -1,    30,   347,    32,    33,    34,    -1,
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
      65,    66,    67,    35,    36,    37,    -1,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    -1,    -1,    65,    66,    67,    35,    -1,    37,    -1,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    35,
      36,    37,    38,    -1,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    35,    -1,
      56,    57,    58,    40,    41,    42,    -1,    63,    -1,    65,
      66,    67,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    82,     1,     4,     5,     6,     7,     8,    45,
      83,    84,    85,    86,    91,    95,    96,   134,     0,    17,
      47,    61,    76,    97,    99,   100,    97,    97,    97,    97,
      97,   150,   151,   152,   153,    84,    16,    18,    19,    23,
      30,    32,    33,    34,    39,    40,    41,    43,    45,    51,
      70,    71,    72,    73,    74,    75,    92,    93,    94,   100,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   126,   127,   128,   129,   130,   131,   132,
     133,    99,    61,    43,   104,    42,   104,    49,    43,   120,
      46,    52,    45,    97,   101,   102,   102,   102,   120,   102,
     120,   120,   120,     1,    55,   120,   124,     1,    46,   120,
     124,   100,    52,    48,    43,   125,    35,    36,    37,    38,
      40,    41,    42,    53,    54,    55,    56,    57,    58,    62,
      63,    65,    66,    67,    62,    97,     1,   102,   103,    62,
      47,    42,    62,    89,    90,   100,   105,   106,   107,   108,
     109,   120,    83,   150,   151,    49,    42,    17,    17,    24,
      17,    44,   120,    44,    52,    46,    60,    46,    52,    92,
       1,    44,   120,   124,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,    44,    44,    52,   105,    97,    98,    11,
      13,    15,    16,    18,    19,    20,    22,    23,    26,    43,
      47,    68,   127,   128,   135,   137,   138,   139,   142,   143,
     144,   145,   146,   147,   148,   149,   105,    55,    62,    53,
      59,    46,   105,   120,   120,   120,   120,   120,    44,   120,
     120,   120,    44,    44,   102,    42,    48,    52,     1,   135,
     136,     1,   136,   102,   102,   102,   135,   127,   128,   120,
     120,     1,   136,     1,   136,    64,    42,   105,   105,    90,
     105,   110,   120,   101,    17,    29,    21,    25,    31,   125,
      44,    46,   120,    97,    12,    12,   135,    14,    14,    42,
      17,    17,    24,    27,    48,    48,    69,    69,   120,   135,
      10,    88,    62,    52,    54,   120,   120,   120,   120,   120,
     120,   120,   120,   135,    47,    47,     9,    87,   105,   105,
      17,    21,    31,    21,    25,     1,    28,    50,   120,   140,
     141,   120,    47,    54,   135,   135,   120,   135,   135,    48,
      49,    49,    49,   141,    48,    48,    94,    21,   135,   135,
     135,    48,   135
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    81,    82,    83,    83,    83,    83,    84,    84,    84,
      85,    85,    86,    86,    87,    87,    88,    88,    89,    89,
      90,    90,    91,    91,    92,    92,    92,    93,    93,    94,
      94,    95,    96,    97,    97,    98,    98,    99,    99,   100,
     100,   101,   101,   102,   102,   103,   103,   104,   104,   104,
     105,   105,   105,   105,   106,   107,   108,   109,   110,   110,
     111,   111,   111,   111,   111,   111,   111,   111,   112,   113,
     113,   114,   115,   115,   116,   117,   118,   119,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   122,   123,   123,   123,   124,   124,   125,   125,   125,
     126,   127,   127,   128,   129,   130,   131,   132,   133,   134,
     134,   135,   135,   135,   135,   135,   135,   135,   135,   135,
     135,   135,   136,   136,   137,   138,   138,   139,   139,   140,
     140,   140,   141,   141,   142,   143,   143,   144,   145,   146,
     146,   146,   146,   147,   147,   147,   147,   148,   149,   149,
     149,   149,   150,   150,   151,   151,   152,   153
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     4,     1,     1,
       2,     1,     8,     1,     4,     0,     4,     0,     3,     1,
       1,     0,     2,     4,     1,     3,     3,     3,     1,     1,
       0,     7,     6,     1,     1,     3,     1,     3,     1,     1,
       2,     3,     1,     4,     1,     3,     1,     3,     3,     0,
       1,     1,     1,     1,     1,     4,     6,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     5,     2,     3,     3,     3,     1,     3,     3,     2,
       5,     1,     2,     5,     6,     6,     6,     6,     6,     5,
       7,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     4,     6,     6,     6,     3,
       3,     3,     2,     1,     6,     6,     8,     6,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       2,     1,     1,     1,     3,     1,     1,     2
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
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Definition",
  "AttributedDefinition", "Definitions", "FunctionDefinition",
  "MaybeInitially", "MaybeDefined", "FunctionParameters",
  "MaybeFunctionParameters", "ProgramFunctionDefinition", "Initializer",
  "Initializers", "MaybeInitializers", "DerivedDefinition",
  "EnumerationDefinition", "Identifier", "Identifiers",
  "DotSeparatedIdentifiers", "IdentifierPath", "Variable",
  "AttributedVariable", "Parameters", "MaybeParameters", "Type",
  "BasicType", "ComposedType", "RelationType", "FixedSizedType", "Types",
  "Atom", "Undefined", "Boolean", "String", "BitNumber", "IntegerNumber",
  "FloatingNumber", "RationalNumber", "Reference", "Term", "Expression",
  "Range", "List", "Terms", "Arguments", "TwoOrMoreArguments",
  "DirectCallExpression", "IndirectCallExpression", "LetExpression",
  "ConditionalExpression", "ChooseExpression",
  "UniversalQuantifierExpression", "ExistentialQuantifierExpression",
  "RuleDefinition", "Rule", "Rules", "SkipRule", "ConditionalRule",
  "CaseRule", "CaseLabel", "CaseLabels", "LetRule", "ForallRule",
  "ChooseRule", "IterateRule", "BlockRule", "SequenceRule", "UpdateRule",
  "CallRule", "Attribute", "Attributes", "BasicAttribute",
  "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   370,   370,   378,   382,   386,   390,   398,   404,   408,
     416,   422,   432,   448,   456,   460,   468,   472,   480,   486,
     496,   500,   508,   531,   549,   557,   567,   578,   584,   594,
     598,   606,   614,   622,   626,   634,   640,   650,   656,   666,
     670,   678,   682,   691,   697,   705,   711,   721,   725,   729,
     737,   741,   745,   749,   757,   765,   773,   781,   789,   795,
     805,   809,   813,   817,   821,   825,   829,   833,   841,   849,
     854,   863,   879,   891,   907,   923,   939,   955,   963,   967,
     971,   975,   979,   983,   987,   991,   995,   999,  1003,  1011,
    1015,  1019,  1023,  1027,  1031,  1035,  1039,  1043,  1047,  1051,
    1055,  1059,  1063,  1067,  1071,  1075,  1079,  1083,  1087,  1091,
    1095,  1103,  1111,  1116,  1120,  1128,  1134,  1144,  1148,  1152,
    1161,  1171,  1176,  1184,  1192,  1200,  1208,  1216,  1224,  1232,
    1237,  1246,  1250,  1254,  1258,  1262,  1266,  1270,  1274,  1278,
    1282,  1286,  1294,  1300,  1310,  1318,  1322,  1330,  1334,  1342,
    1346,  1350,  1358,  1364,  1374,  1382,  1386,  1394,  1402,  1410,
    1414,  1418,  1423,  1432,  1436,  1440,  1445,  1454,  1464,  1470,
    1477,  1483,  1494,  1498,  1506,  1512,  1522,  1530
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
#line 3845 "GrammarParser.cpp" // lalr1.cc:1167
#line 1536 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
