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
#line 67 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    #include "SourceLocation.h"
    #include "Lexer.h"
    #include "Exceptions.h"
    #include "Logger.h"

    #include "../stdhl/cpp/Type.h"

    #undef yylex
    #define yylex lexer.nextToken

    static BasicType::Ptr createVoidType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::VoidType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
        const auto node = Ast::make< BasicType >( sourceLocation, path );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( SourceLocation& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::RuleReferenceType >();
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

#line 31 "../../obj/src/GrammarParser.yy" // lalr1.cc:479
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
  Parser::Parser (Logger& log_yyarg, Lexer& lexer_yyarg, const std::string& filePath_yyarg, Specification::Ptr& result_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      log (log_yyarg),
      lexer (lexer_yyarg),
      filePath (filePath_yyarg),
      result (result_yyarg)
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
      case 147: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 148: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 149: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 105: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 143: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 146: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 137: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 136: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 138: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 141: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 106: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 128: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 135: // ConditionalRule
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

      case 126: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 96: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 130: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // MaybeDefined
      case 110: // Atom
      case 119: // Term
      case 120: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 150: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 123: // Terms
      case 124: // Arguments
      case 125: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 108: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 140: // ForallRule
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

      case 127: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 142: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 139: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 122: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 87: // MaybeInitially
      case 93: // Initializers
      case 94: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 102: // Parameters
      case 103: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 121: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 118: // Reference
        value.move< ReferenceAtom::Ptr > (that.value);
        break;

      case 107: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 132: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 131: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 133: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 144: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 134: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 104: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 89: // FunctionParameters
      case 90: // MaybeFunctionParameters
      case 109: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 111: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 129: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 92: // Initializer
      case 145: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 112: // Boolean
      case 113: // String
      case 114: // BitNumber
      case 115: // IntegerNumber
      case 116: // FloatingNumber
      case 117: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 101: // Variable
        value.move< VariableDefinition::Ptr > (that.value);
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
      case 147: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 148: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 149: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 105: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 143: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 146: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 137: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 136: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 138: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 141: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 106: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 128: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 135: // ConditionalRule
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

      case 126: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 96: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 130: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // MaybeDefined
      case 110: // Atom
      case 119: // Term
      case 120: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 150: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 123: // Terms
      case 124: // Arguments
      case 125: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 108: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 140: // ForallRule
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

      case 127: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 142: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 139: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 122: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 87: // MaybeInitially
      case 93: // Initializers
      case 94: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 102: // Parameters
      case 103: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 121: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 118: // Reference
        value.copy< ReferenceAtom::Ptr > (that.value);
        break;

      case 107: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 132: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 131: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 133: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 144: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 134: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 104: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 89: // FunctionParameters
      case 90: // MaybeFunctionParameters
      case 109: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 111: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 129: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 92: // Initializer
      case 145: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 112: // Boolean
      case 113: // String
      case 114: // BitNumber
      case 115: // IntegerNumber
      case 116: // FloatingNumber
      case 117: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 101: // Variable
        value.copy< VariableDefinition::Ptr > (that.value);
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
      case 147: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 148: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 149: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 105: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 143: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 146: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 137: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 136: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 138: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 141: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 106: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 128: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 135: // ConditionalRule
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

      case 126: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 96: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 130: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 88: // MaybeDefined
      case 110: // Atom
      case 119: // Term
      case 120: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 150: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 123: // Terms
      case 124: // Arguments
      case 125: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 108: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 140: // ForallRule
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

      case 127: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 142: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 139: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 122: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 87: // MaybeInitially
      case 93: // Initializers
      case 94: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 102: // Parameters
      case 103: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 121: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 118: // Reference
        yylhs.value.build< ReferenceAtom::Ptr > ();
        break;

      case 107: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 132: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 131: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 133: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 144: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 134: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 82: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 104: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 89: // FunctionParameters
      case 90: // MaybeFunctionParameters
      case 109: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 111: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 129: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 92: // Initializer
      case 145: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 112: // Boolean
      case 113: // String
      case 114: // BitNumber
      case 115: // IntegerNumber
      case 116: // FloatingNumber
      case 117: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 101: // Variable
        yylhs.value.build< VariableDefinition::Ptr > ();
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
#line 346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& fileName = filePath.substr( filePath.find_last_of( "/\\" ) + 1 );
      const std::string& name = fileName.substr( 0, fileName.rfind( "." ) );

      const auto specificationName = make< Identifier >( yylhs.location, name );
      result = Ast::make< Specification >( yylhs.location, specificationName, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1288 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 362 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1312 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1356 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 402 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1366 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< Identifier::Ptr > ();

      auto function = Ast::make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< Type::Ptr > () );
      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
           initializer->function()->setIdentifier( asIdentifierPath( identifier ) );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1386 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 428 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1394 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 436 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1410 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1418 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 452 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1426 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1436 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1446 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 1462 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
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
#line 1489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
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
#line 1507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 529 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1519 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 537 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1533 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 547 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1554 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 564 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1564 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1572 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 586 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 594 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Identifiers::Ptr > () );
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 610 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1614 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1624 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 626 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1634 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 632 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 642 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 1652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::RELATIVE );
  }
#line 1660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 654 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 658 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 1677 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 667 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1687 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 673 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 683 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1705 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 687 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 1713 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1721 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 699 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1729 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 703 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 707 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 1745 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 711 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1753 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 1761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1769 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< Type::Ptr > () );
  }
#line 1777 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 743 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1785 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 751 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1795 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 767 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 1813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 771 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 775 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 779 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1837 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 783 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1845 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 787 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1853 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 791 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 795 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 803 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 811 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1895 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 1911 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 841 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 1927 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 853 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
          yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
      }
      catch( const std::domain_error& e )
      {
          throw syntax_error( yylhs.location, e.what() );
      }
  }
#line 1943 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 869 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
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
#line 885 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
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
#line 901 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      try
      {
          const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
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
#line 917 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 1999 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 925 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 929 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2015 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 933 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 937 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2031 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 941 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2039 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2047 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2055 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2063 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 957 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2071 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 965 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2079 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 969 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2087 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 973 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2095 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 977 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2103 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 985 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 989 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 993 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 997 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1001 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1005 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1009 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1013 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1017 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1021 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1025 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2199 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1029 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2207 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1033 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1037 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1041 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2231 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1045 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1049 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1057 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1065 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2264 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1070 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2272 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2280 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2300 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2308 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1102 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2316 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2325 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1115 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[1].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[3].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1125 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1130 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1138 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1146 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1162 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1170 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1175 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1184 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2410 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1188 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2418 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2426 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1196 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2434 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1200 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1204 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 2450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1208 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2458 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1212 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2466 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1216 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2474 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1220 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2482 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1224 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2490 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1232 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2500 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2510 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1248 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 2518 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1256 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2526 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1260 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2534 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1268 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2542 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1272 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 2550 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1280 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2558 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1284 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2566 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1288 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2574 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1296 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1302 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2594 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1312 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2602 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1320 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2610 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1328 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2618 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1336 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2626 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1344 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2634 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1348 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1352 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1357 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2685 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1379 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2694 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2704 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2714 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1411 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2735 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2746 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1428 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2754 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1432 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2762 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1456 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2790 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1464 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2798 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2802 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -185;

  const signed char Parser::yytable_ninf_ = -57;

  const short int
  Parser::yypact_[] =
  {
      12,    60,    45,  -185,   -38,   -60,   -60,   -60,   -60,   -60,
    -185,  -185,   112,  -185,  -185,  -185,  -185,  -185,  -185,   866,
     -60,  -185,  -185,    -3,  -185,    13,    28,    13,    23,   925,
    -185,   -42,  -185,  -185,  -185,   -60,   925,   -60,  -185,  -185,
    -185,   925,   925,   925,   379,   438,   -50,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,    22,    31,    34,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,  1297,  -185,  -185,  -185,
      39,  -185,  -185,  -185,  -185,  -185,  -185,   -60,     0,    42,
      59,   -34,   -50,   379,  1528,   129,   -60,    61,    97,  1063,
      98,  -185,  -185,  -185,    82,   925,  1264,    92,  -185,  1330,
      11,  -185,   866,  -185,   497,  -185,   925,   925,   925,   925,
     925,   925,   925,   925,   925,   925,   925,   925,   925,   925,
     925,   925,   925,   925,   925,  -185,    88,  -185,     2,   -50,
     -60,   777,   -50,    84,    83,    16,  -185,  -185,  -185,  -185,
    -185,  1363,  -185,  -185,   -50,   925,   925,   925,  -185,  1396,
    -185,   925,  -185,   925,  -185,   925,  -185,   102,  -185,  1528,
       3,  1665,  1594,  1646,  1561,    86,    86,   231,    -5,    -5,
      89,    89,    89,  -185,  1528,  1561,   231,    -5,    -5,  1528,
    -185,  -185,   -60,   106,  -185,    -8,   534,   574,  -185,   -60,
     -60,   -60,   777,   -37,   925,   925,    94,   600,   640,    87,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,   108,   -50,   -50,   -50,   925,  -185,  1198,
    1132,  1231,    34,    29,  1429,  1528,  -185,  -185,  -185,   925,
    -185,   -60,   141,  -185,   659,   140,   699,   114,   145,   146,
    -185,  -185,  -185,  1098,  1165,   116,   718,    96,   758,   925,
     777,  -185,   156,   105,   -25,   -11,  1627,   925,   925,   925,
    -185,  -185,  -185,  1528,  -185,  -185,  -185,  -185,  -185,  -185,
     925,   925,   925,   777,   121,  -185,  -185,  -185,  -185,  1528,
    -185,   122,   163,   -50,   -50,  -185,  -185,  1528,  -185,   952,
     990,  1028,   148,   320,   925,   127,  -185,   124,  -185,   777,
     777,   777,   777,   133,   126,   134,  1462,   807,   136,  1495,
     866,  -185,  -185,  -185,  -185,  -185,  -185,   777,   777,   777,
    -185,  -185,  -185,   139,  -185,  -185,  -185,  -185
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     7,     0,     0,     0,     0,     0,     0,
       9,    11,     0,     3,    13,     4,     6,     5,     1,    30,
       0,    33,    37,    38,    22,    46,     0,    46,     0,   168,
     167,     0,   164,   165,    10,     0,     0,     0,    65,    67,
      66,     0,     0,     0,     0,     0,     0,    69,    70,    71,
      73,    72,    68,    28,    29,     0,   116,    83,    63,    64,
      62,    58,    59,    60,    61,    57,    24,    80,    82,    81,
       0,    75,    76,    77,    78,    79,    39,     0,     0,     0,
       0,     0,    21,     0,   169,     0,     0,    41,     0,     0,
       0,   105,    86,    87,     0,     0,     0,     0,   107,   111,
       0,    74,     0,    23,     0,   117,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,     0,    43,     0,     0,
       0,     0,     0,    20,     0,    51,    19,    47,    48,    49,
      50,     0,     8,   166,     0,     0,     0,     0,    85,     0,
      84,     0,   109,     0,   108,     0,    27,     0,   114,   111,
       0,   102,   100,   101,   104,    88,    89,    95,    96,    97,
      90,    91,    92,    93,    25,   103,    94,    98,    99,    26,
      45,    44,     0,     0,    35,     0,     0,     0,   137,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   161,
     163,   122,   124,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,     0,     0,     0,    21,     0,    40,     0,
       0,     0,     0,     0,     0,   110,   113,   112,    42,     0,
      32,     0,     0,   136,     0,     0,     0,     0,     0,     0,
     150,   160,   162,     0,     0,     0,     0,     0,     0,     0,
       0,    18,    17,     0,    19,     0,    54,     0,     0,     0,
     118,   115,   106,    31,    34,   158,   156,   135,   154,   152,
       0,     0,     0,     0,     0,   153,   151,   157,   155,   159,
     123,     0,    15,     0,     0,    52,   120,   119,   121,     0,
       0,     0,   138,     0,     0,     0,    12,     0,    55,     0,
       0,     0,     0,     0,     0,     0,     0,   146,     0,     0,
      30,    53,   147,   148,   149,   139,   141,     0,     0,     0,
     145,   140,    16,     0,   142,   143,   144,    14
  };

  const short int
  Parser::yypgoto_[] =
  {
    -185,  -185,   103,   170,  -185,  -185,  -185,  -185,  -185,   -27,
    -185,    90,  -185,  -116,  -185,  -185,    25,  -185,   175,    -4,
     -30,  -185,   169,  -107,  -185,  -185,  -185,  -185,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,  -185,  -185,   -24,  -185,
    -185,  -185,  -102,   -23,  -185,    -7,    67,  -185,  -185,  -185,
    -185,    27,  -184,  -185,  -185,  -185,  -185,  -110,  -185,  -185,
    -185,  -185,  -185,  -185,  -185,  -185,   115,  -185,  -185,  -185
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,    10,    11,    12,    13,   296,   282,   133,   134,
      14,    53,    54,    55,    15,    16,    22,   185,    23,    56,
      88,   128,    79,   136,   137,   138,   139,   140,   255,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,   100,   105,    70,    71,    72,    73,    74,    75,
      17,   233,   234,   202,   203,   204,   307,   308,   205,   206,
     207,   208,   209,   210,   211,   212,    30,    31,    32,    33
  };

  const short int
  Parser::yytable_[] =
  {
      24,   126,   160,   236,    85,    84,   196,    90,   131,    19,
      86,    20,    89,   246,   248,     1,    21,    91,    92,    93,
      96,    99,   183,    20,    20,   213,    21,   -56,   132,   -56,
      25,    26,    27,    28,    29,   110,   111,   218,    21,    21,
     230,   284,   101,   285,   231,    18,   181,   227,   127,   223,
     115,   116,   117,   118,   182,   155,    78,   154,    77,   141,
      87,     3,    87,   155,     4,     5,     6,     7,     8,   216,
      80,   149,    82,   261,   102,   217,    21,   104,   135,   103,
     159,   155,   161,   162,   163,   164,   165,   166,   167,   168,
     169,   170,   171,   172,   173,   174,   175,   176,   177,   178,
     179,   124,   125,    87,   129,     9,   130,   251,   252,   254,
     144,    29,    -2,     3,   145,   147,     4,     5,     6,     7,
       8,   219,   220,   221,   199,   135,   148,   159,   135,   224,
       3,   225,   180,     4,     5,     6,     7,     8,   152,   214,
     135,   115,   116,   117,   118,   215,   226,   118,   229,    95,
     250,   249,   228,   265,   268,   184,   270,     9,   201,   237,
     238,   239,   271,   272,   275,   277,   281,   283,   293,   294,
     243,   244,   295,   302,   310,   317,   297,   298,   311,   199,
     199,   316,    34,   318,   321,   199,   241,   327,   142,   253,
     199,   199,   156,   256,   323,    76,    81,   320,   200,   260,
       0,   143,     0,     0,     0,   263,     0,    87,     0,     0,
     135,   135,   135,     0,    87,    87,    87,     0,     0,   240,
       0,     0,     0,     0,     0,   279,     0,   199,     0,   199,
       0,     0,     0,   286,   287,   288,     0,     0,     0,   199,
       0,   199,     0,   199,     0,     0,   289,   290,   291,     0,
       0,     0,     0,   200,   200,     0,   264,     0,     0,   200,
     242,   267,     0,   267,   200,   200,   199,     0,     0,   306,
     309,   110,   111,   267,     0,   267,     0,   280,     0,   135,
     135,     0,     0,   306,   113,   114,   115,   116,   117,   118,
       0,     0,   199,   199,   199,   199,     0,   122,   123,     0,
     292,   200,     0,   200,     0,     0,     0,     0,     0,     0,
     199,   199,   199,   200,     0,   200,     0,   200,     0,     0,
       0,   303,     0,     0,     0,     0,   312,   313,   314,   315,
       0,     0,     0,     0,     0,     0,     0,     0,    35,     0,
     200,     0,     0,    36,   324,   325,   326,     0,   304,     0,
      37,     0,    38,    39,    40,     0,     0,     0,     0,    41,
      42,    43,     0,    83,     0,    45,   200,   200,   200,   200,
     305,    46,     0,     0,     0,     0,     0,     0,     0,     0,
      94,    20,     0,     0,   200,   200,   200,     0,     0,     0,
      47,    48,    49,    50,    51,    52,    21,    35,     0,     0,
       0,     0,    36,     0,     0,     0,     0,     0,     0,    37,
       0,    38,    39,    40,     0,     0,     0,     0,    41,    42,
      43,     0,    83,     0,    45,     0,     0,     0,     0,     0,
      46,     0,     0,     0,    95,     0,     0,     0,     0,    97,
      20,     0,     0,     0,     0,     0,     0,     0,     0,    47,
      48,    49,    50,    51,    52,    21,    35,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,    37,     0,
      38,    39,    40,     0,     0,     0,     0,    41,    42,    43,
       0,    83,     0,    45,    98,     0,     0,     0,     0,    46,
       0,     0,     0,     0,     0,     0,     0,     0,   157,    20,
       0,     0,     0,     0,     0,     0,     0,     0,    47,    48,
      49,    50,    51,    52,    21,    35,     0,     0,     0,     0,
      36,     0,     0,     0,     0,     0,     0,    37,     0,    38,
      39,    40,     0,     0,     0,   232,    41,    42,    43,     0,
      83,   158,    45,     0,     0,   186,     0,   187,    46,   188,
     189,     0,   190,   191,   192,     0,   193,   194,    20,     0,
     195,     0,     0,     0,     0,     0,     0,    47,    48,    49,
      50,    51,    52,    21,     0,   235,     0,   196,     0,     0,
       0,   197,     0,     0,     0,   186,     0,   187,     0,   188,
     189,     0,   190,   191,   192,    20,   193,   194,     0,     0,
     195,   245,   198,     0,     0,     0,     0,     0,     0,     0,
      21,   186,     0,   187,     0,   188,   189,   196,   190,   191,
     192,   197,   193,   194,     0,     0,   195,     0,     0,     0,
       0,     0,     0,     0,     0,    20,     0,     0,     0,     0,
       0,   247,   198,   196,     0,     0,     0,   197,     0,     0,
      21,   186,     0,   187,     0,   188,   189,     0,   190,   191,
     192,    20,   193,   194,     0,     0,   195,     0,   198,     0,
     186,   266,   187,     0,   188,   189,    21,   190,   191,   192,
       0,   193,   194,   196,     0,   195,     0,   197,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    20,   196,     0,     0,     0,   197,     0,   198,     0,
     186,     0,   187,   269,   188,   189,    21,   190,   191,   192,
      20,   193,   194,     0,     0,   195,     0,   198,     0,   186,
       0,   187,     0,   188,   189,    21,   190,   191,   192,     0,
     193,   194,   196,     0,   195,     0,   197,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,   196,     0,     0,     0,   197,   276,   198,     0,   186,
       0,   187,     0,   188,   189,    21,   190,   191,   192,    20,
     193,   194,     0,     0,   195,     0,   198,     0,   186,     0,
     187,     0,   188,   189,    21,   190,   191,   192,     0,   193,
     194,   196,     0,   195,     0,   197,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
     196,     0,     0,     0,   197,    35,   198,   278,     0,     0,
      36,     0,     0,     0,    21,   304,     0,    37,    20,    38,
      39,    40,     0,     0,     0,   198,    41,    42,    43,     0,
      83,     0,    45,    21,     0,     0,     0,   305,    46,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    20,     0,
       0,     0,     0,     0,     0,     0,     0,    47,    48,    49,
      50,    51,    52,    21,    35,     0,     0,     0,     0,    36,
       0,     0,     0,     0,     0,     0,    37,     0,    38,    39,
      40,     0,     0,     0,     0,    41,    42,    43,     0,    44,
       0,    45,     0,     0,     0,     0,     0,    46,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,     0,     0,
       0,     0,     0,     0,     0,     0,    47,    48,    49,    50,
      51,    52,    21,    35,     0,     0,     0,     0,    36,     0,
       0,     0,     0,     0,     0,    37,     0,    38,    39,    40,
       0,     0,     0,     0,    41,    42,    43,     0,    83,   299,
      45,     0,     0,     0,     0,     0,    46,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    20,   106,   107,   108,
     109,     0,   110,   111,   112,    47,    48,    49,    50,    51,
      52,    21,     0,     0,     0,   113,   114,   115,   116,   117,
     118,   300,     0,     0,     0,   120,     0,   121,   122,   123,
       0,     0,     0,     0,     0,   106,   107,   108,   109,     0,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,   114,   115,   116,   117,   118,   301,
       0,     0,     0,   120,     0,   121,   122,   123,     0,     0,
       0,     0,     0,   106,   107,   108,   109,     0,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   146,     0,     0,
       0,   120,     0,   121,   122,   123,     0,     0,   106,   107,
     108,   109,     0,   110,   111,   112,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   273,     0,     0,     0,   120,     0,   121,   122,
     123,     0,     0,   106,   107,   108,   109,     0,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,   258,     0,     0,
       0,   120,     0,   121,   122,   123,     0,   106,   107,   108,
     109,     0,   110,   111,   112,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   113,   114,   115,   116,   117,
     118,     0,   274,     0,     0,   120,     0,   121,   122,   123,
     106,   107,   108,   109,     0,   110,   111,   112,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   114,
     115,   116,   117,   118,     0,     0,     0,   257,   120,     0,
     121,   122,   123,   106,   107,   108,   109,     0,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,     0,     0,     0,
       0,   120,   259,   121,   122,   123,   106,   107,   108,   109,
       0,   110,   111,   112,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   114,   115,   116,   117,   118,
       0,     0,     0,     0,   120,     0,   121,   122,   123,   106,
     107,   108,   109,     0,   110,   111,   112,     0,   150,     0,
       0,     0,     0,     0,     0,     0,   151,   113,   114,   115,
     116,   117,   118,     0,     0,     0,     0,   120,     0,   121,
     122,   123,   106,   107,   108,   109,     0,   110,   111,   112,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,   114,   115,   116,   117,   118,     0,     0,     0,   119,
     120,     0,   121,   122,   123,   106,   107,   108,   109,     0,
     110,   111,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   113,   114,   115,   116,   117,   118,     0,
     153,     0,     0,   120,     0,   121,   122,   123,   106,   107,
     108,   109,     0,   110,   111,   112,     0,   150,     0,     0,
       0,     0,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,     0,     0,     0,     0,   120,     0,   121,   122,
     123,   106,   107,   108,   109,     0,   110,   111,   112,     0,
     222,     0,     0,     0,     0,     0,     0,     0,     0,   113,
     114,   115,   116,   117,   118,     0,     0,     0,     0,   120,
       0,   121,   122,   123,   106,   107,   108,   109,     0,   110,
     111,   112,     0,     0,     0,   262,     0,     0,     0,     0,
       0,     0,   113,   114,   115,   116,   117,   118,     0,     0,
       0,     0,   120,     0,   121,   122,   123,   106,   107,   108,
     109,     0,   110,   111,   112,     0,     0,     0,     0,     0,
       0,   319,     0,     0,     0,   113,   114,   115,   116,   117,
     118,     0,     0,     0,     0,   120,     0,   121,   122,   123,
     106,   107,   108,   109,     0,   110,   111,   112,     0,     0,
       0,     0,     0,   322,     0,     0,     0,     0,   113,   114,
     115,   116,   117,   118,     0,     0,     0,     0,   120,     0,
     121,   122,   123,   106,   107,   108,   109,     0,   110,   111,
     112,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   113,   114,   115,   116,   117,   118,     0,     0,     0,
       0,   120,     0,   121,   122,   123,   106,   107,   108,     0,
       0,   110,   111,   112,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   113,   114,   115,   116,   117,   118,
       0,     0,     0,     0,     0,     0,   121,   122,   123,   106,
       0,   108,     0,     0,   110,   111,   112,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   113,   114,   115,
     116,   117,   118,     0,     0,     0,     0,     0,     0,   121,
     122,   123,   106,   107,   108,   109,     0,   110,   111,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     113,   106,     0,   116,   117,   118,   110,   111,   112,     0,
     120,     0,   121,   122,   123,     0,     0,     0,     0,   113,
     114,   115,   116,   117,   118,   110,   111,   112,     0,     0,
       0,   121,   122,   123,     0,     0,     0,     0,   113,   114,
     115,   116,   117,   118,     0,     0,     0,     0,     0,     0,
     121,   122,   123
  };

  const short int
  Parser::yycheck_[] =
  {
       4,     1,   104,   187,    46,    29,    43,    37,    42,    47,
      52,    61,    36,   197,   198,     3,    76,    41,    42,    43,
      44,    45,   129,    61,    61,   132,    76,    52,    62,    54,
       5,     6,     7,     8,     9,    40,    41,   144,    76,    76,
      48,    52,    46,    54,    52,     0,    44,    44,    78,   151,
      55,    56,    57,    58,    52,    52,    43,    46,    61,    83,
      35,     1,    37,    52,     4,     5,     6,     7,     8,    53,
      42,    95,    49,    44,    52,    59,    76,    43,    82,    48,
     104,    52,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,    62,    77,    78,    62,    45,    47,   214,   215,   216,
      49,    86,     0,     1,    17,    17,     4,     5,     6,     7,
       8,   145,   146,   147,   131,   129,    44,   151,   132,   153,
       1,   155,    44,     4,     5,     6,     7,     8,    46,    55,
     144,    55,    56,    57,    58,    62,    44,    58,    42,    55,
      42,    64,   182,    12,    14,   130,    42,    45,   131,   189,
     190,   191,    17,    17,    48,    69,    10,    62,    47,    47,
     194,   195,     9,    25,    47,    49,   283,   284,    54,   186,
     187,    48,    12,    49,    48,   192,   193,    48,    85,   216,
     197,   198,   102,   217,   310,    20,    27,   307,   131,   222,
      -1,    86,    -1,    -1,    -1,   229,    -1,   182,    -1,    -1,
     214,   215,   216,    -1,   189,   190,   191,    -1,    -1,   192,
      -1,    -1,    -1,    -1,    -1,   249,    -1,   234,    -1,   236,
      -1,    -1,    -1,   257,   258,   259,    -1,    -1,    -1,   246,
      -1,   248,    -1,   250,    -1,    -1,   270,   271,   272,    -1,
      -1,    -1,    -1,   186,   187,    -1,   231,    -1,    -1,   192,
     193,   234,    -1,   236,   197,   198,   273,    -1,    -1,   293,
     294,    40,    41,   246,    -1,   248,    -1,   250,    -1,   283,
     284,    -1,    -1,   307,    53,    54,    55,    56,    57,    58,
      -1,    -1,   299,   300,   301,   302,    -1,    66,    67,    -1,
     273,   234,    -1,   236,    -1,    -1,    -1,    -1,    -1,    -1,
     317,   318,   319,   246,    -1,   248,    -1,   250,    -1,    -1,
      -1,     1,    -1,    -1,    -1,    -1,   299,   300,   301,   302,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    18,    -1,
     273,    -1,    -1,    23,   317,   318,   319,    -1,    28,    -1,
      30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
      40,    41,    -1,    43,    -1,    45,   299,   300,   301,   302,
      50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       1,    61,    -1,    -1,   317,   318,   319,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    18,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,
      -1,    32,    33,    34,    -1,    -1,    -1,    -1,    39,    40,
      41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,     1,
      61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    18,    -1,    -1,    -1,
      -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,
      32,    33,    34,    -1,    -1,    -1,    -1,    39,    40,    41,
      -1,    43,    -1,    45,    46,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     1,    61,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
      72,    73,    74,    75,    76,    18,    -1,    -1,    -1,    -1,
      23,    -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,
      33,    34,    -1,    -1,    -1,     1,    39,    40,    41,    -1,
      43,    44,    45,    -1,    -1,    11,    -1,    13,    51,    15,
      16,    -1,    18,    19,    20,    -1,    22,    23,    61,    -1,
      26,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    -1,     1,    -1,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    11,    -1,    13,    -1,    15,
      16,    -1,    18,    19,    20,    61,    22,    23,    -1,    -1,
      26,     1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    11,    -1,    13,    -1,    15,    16,    43,    18,    19,
      20,    47,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,     1,    68,    43,    -1,    -1,    -1,    47,    -1,    -1,
      76,    11,    -1,    13,    -1,    15,    16,    -1,    18,    19,
      20,    61,    22,    23,    -1,    -1,    26,    -1,    68,    -1,
      11,    12,    13,    -1,    15,    16,    76,    18,    19,    20,
      -1,    22,    23,    43,    -1,    26,    -1,    47,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    43,    -1,    -1,    -1,    47,    -1,    68,    -1,
      11,    -1,    13,    14,    15,    16,    76,    18,    19,    20,
      61,    22,    23,    -1,    -1,    26,    -1,    68,    -1,    11,
      -1,    13,    -1,    15,    16,    76,    18,    19,    20,    -1,
      22,    23,    43,    -1,    26,    -1,    47,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    43,    -1,    -1,    -1,    47,    48,    68,    -1,    11,
      -1,    13,    -1,    15,    16,    76,    18,    19,    20,    61,
      22,    23,    -1,    -1,    26,    -1,    68,    -1,    11,    -1,
      13,    -1,    15,    16,    76,    18,    19,    20,    -1,    22,
      23,    43,    -1,    26,    -1,    47,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,
      43,    -1,    -1,    -1,    47,    18,    68,    69,    -1,    -1,
      23,    -1,    -1,    -1,    76,    28,    -1,    30,    61,    32,
      33,    34,    -1,    -1,    -1,    68,    39,    40,    41,    -1,
      43,    -1,    45,    76,    -1,    -1,    -1,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
      73,    74,    75,    76,    18,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,
      34,    -1,    -1,    -1,    -1,    39,    40,    41,    -1,    43,
      -1,    45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    18,    -1,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    40,    41,    -1,    43,    17,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    35,    36,    37,
      38,    -1,    40,    41,    42,    70,    71,    72,    73,    74,
      75,    76,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    21,    -1,    -1,    -1,    63,    -1,    65,    66,    67,
      -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    21,
      -1,    -1,    -1,    63,    -1,    65,    66,    67,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    24,    -1,    -1,
      -1,    63,    -1,    65,    66,    67,    -1,    -1,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    24,    -1,    -1,    -1,    63,    -1,    65,    66,
      67,    -1,    -1,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    25,    -1,    -1,
      -1,    63,    -1,    65,    66,    67,    -1,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    27,    -1,    -1,    63,    -1,    65,    66,    67,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    29,    63,    -1,
      65,    66,    67,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    31,    65,    66,    67,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    -1,    65,    66,    67,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    62,
      63,    -1,    65,    66,    67,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      60,    -1,    -1,    63,    -1,    65,    66,    67,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,    66,
      67,    35,    36,    37,    38,    -1,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      -1,    65,    66,    67,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    63,    -1,    65,    66,    67,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,
      65,    66,    67,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    -1,    65,    66,    67,    35,    36,    37,    -1,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67,    35,
      -1,    37,    -1,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    65,
      66,    67,    35,    36,    37,    38,    -1,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    35,    -1,    56,    57,    58,    40,    41,    42,    -1,
      63,    -1,    65,    66,    67,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    40,    41,    42,    -1,    -1,
      -1,    65,    66,    67,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    -1,    -1,
      65,    66,    67
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    82,     1,     4,     5,     6,     7,     8,    45,
      83,    84,    85,    86,    91,    95,    96,   131,     0,    47,
      61,    76,    97,    99,   100,    97,    97,    97,    97,    97,
     147,   148,   149,   150,    84,    18,    23,    30,    32,    33,
      34,    39,    40,    41,    43,    45,    51,    70,    71,    72,
      73,    74,    75,    92,    93,    94,   100,   110,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     125,   126,   127,   128,   129,   130,    99,    61,    43,   103,
      42,   103,    49,    43,   119,    46,    52,    97,   101,   119,
     101,   119,   119,   119,     1,    55,   119,     1,    46,   119,
     123,   100,    52,    48,    43,   124,    35,    36,    37,    38,
      40,    41,    42,    53,    54,    55,    56,    57,    58,    62,
      63,    65,    66,    67,    62,    97,     1,   101,   102,    62,
      47,    42,    62,    89,    90,   100,   104,   105,   106,   107,
     108,   119,    83,   147,    49,    17,    24,    17,    44,   119,
      44,    52,    46,    60,    46,    52,    92,     1,    44,   119,
     123,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
      44,    44,    52,   104,    97,    98,    11,    13,    15,    16,
      18,    19,    20,    22,    23,    26,    43,    47,    68,   126,
     127,   132,   134,   135,   136,   139,   140,   141,   142,   143,
     144,   145,   146,   104,    55,    62,    53,    59,   104,   119,
     119,   119,    44,   123,   119,   119,    44,    44,   101,    42,
      48,    52,     1,   132,   133,     1,   133,   101,   101,   101,
     132,   126,   127,   119,   119,     1,   133,     1,   133,    64,
      42,   104,   104,    90,   104,   109,   119,    29,    25,    31,
     124,    44,    46,   119,    97,    12,    12,   132,    14,    14,
      42,    17,    17,    24,    27,    48,    48,    69,    69,   119,
     132,    10,    88,    62,    52,    54,   119,   119,   119,   119,
     119,   119,   132,    47,    47,     9,    87,   104,   104,    17,
      21,    21,    25,     1,    28,    50,   119,   137,   138,   119,
      47,    54,   132,   132,   132,   132,    48,    49,    49,    49,
     138,    48,    48,    94,   132,   132,   132,    48
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    81,    82,    83,    83,    83,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    87,    88,    88,    89,    89,
      90,    90,    91,    91,    92,    92,    92,    93,    93,    94,
      94,    95,    96,    97,    98,    98,    99,    99,   100,   100,
     101,   101,   102,   102,   103,   103,   103,   104,   104,   104,
     104,   105,   106,   107,   108,   109,   109,   110,   110,   110,
     110,   110,   110,   110,   110,   111,   112,   112,   113,   114,
     114,   115,   116,   117,   118,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   121,   122,   122,   122,
     123,   123,   124,   124,   124,   125,   126,   126,   127,   128,
     129,   130,   131,   131,   132,   132,   132,   132,   132,   132,
     132,   132,   132,   132,   132,   133,   133,   134,   135,   135,
     136,   136,   137,   137,   137,   138,   138,   139,   140,   141,
     142,   143,   143,   143,   143,   144,   144,   144,   144,   145,
     146,   146,   146,   146,   147,   147,   148,   148,   149,   150
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     1,     4,     1,
       2,     1,     8,     1,     4,     0,     4,     0,     3,     1,
       1,     0,     2,     4,     1,     3,     3,     3,     1,     1,
       0,     7,     6,     1,     3,     1,     3,     1,     1,     2,
       3,     1,     3,     1,     3,     3,     0,     1,     1,     1,
       1,     1,     4,     6,     3,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     2,     2,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     5,     2,     3,     3,
       3,     1,     3,     3,     2,     5,     1,     2,     5,     6,
       6,     6,     5,     7,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     4,     6,
       6,     6,     3,     3,     3,     2,     1,     6,     6,     6,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     1,     2,     1,     1,     1,     3,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enum\"", "\"rule\"", "\"function\"", "\"initially\"",
  "\"defined\"", "\"seq\"", "\"endseq\"", "\"par\"", "\"endpar\"",
  "\"skip\"", "\"let\"", "\"in\"", "\"forall\"", "\"choose\"",
  "\"iterate\"", "\"do\"", "\"call\"", "\"if\"", "\"then\"", "\"else\"",
  "\"case\"", "\"of\"", "\"default\"", "\"holds\"", "\"exists\"",
  "\"with\"", "\"undef\"", "\"false\"", "\"true\"", "\"and\"", "\"or\"",
  "\"xor\"", "\"implies\"", "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"",
  "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\":\"", "\"_\"", "\"@\"",
  "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"", "\"^\"", "\"'\"",
  "\"..\"", "\".\"", "\"->\"", "\"=>\"", "\":=\"", "\"!=\"", "\"<=\"",
  "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"", "\"hexadecimal\"",
  "\"integer\"", "\"rational\"", "\"floating\"", "\"string\"",
  "\"identifier\"", "ABSOLUTE_PATH", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Definition",
  "AttributedDefinition", "Definitions", "FunctionDefinition",
  "MaybeInitially", "MaybeDefined", "FunctionParameters",
  "MaybeFunctionParameters", "ProgramFunctionDefinition", "Initializer",
  "Initializers", "MaybeInitializers", "DerivedDefinition",
  "EnumerationDefinition", "Identifier", "Identifiers",
  "DotSeparatedIdentifiers", "IdentifierPath", "Variable", "Parameters",
  "MaybeParameters", "Type", "BasicType", "ComposedType", "RelationType",
  "FixedSizedType", "Types", "Atom", "Undefined", "Boolean", "String",
  "BitNumber", "IntegerNumber", "FloatingNumber", "RationalNumber",
  "Reference", "Term", "Expression", "Range", "List", "Terms", "Arguments",
  "TwoOrMoreArguments", "DirectCallExpression", "IndirectCallExpression",
  "ConditionalExpression", "UniversalQuantifierExpression",
  "ExistentialQuantifierExpression", "RuleDefinition", "Rule", "Rules",
  "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels",
  "LetRule", "ForallRule", "ChooseRule", "IterateRule", "BlockRule",
  "SequenceRule", "UpdateRule", "CallRule", "Attribute", "Attributes",
  "BasicAttribute", "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   345,   345,   357,   361,   365,   369,   373,   381,   387,
     395,   401,   411,   427,   435,   439,   447,   451,   459,   465,
     475,   479,   487,   510,   528,   536,   546,   557,   563,   573,
     577,   585,   593,   601,   609,   615,   625,   631,   641,   645,
     653,   657,   666,   672,   682,   686,   690,   698,   702,   706,
     710,   718,   726,   734,   742,   750,   756,   766,   770,   774,
     778,   782,   786,   790,   794,   802,   810,   815,   824,   840,
     852,   868,   884,   900,   916,   924,   928,   932,   936,   940,
     944,   948,   952,   956,   964,   968,   972,   976,   980,   984,
     988,   992,   996,  1000,  1004,  1008,  1012,  1016,  1020,  1024,
    1028,  1032,  1036,  1040,  1044,  1048,  1056,  1064,  1069,  1073,
    1081,  1087,  1097,  1101,  1105,  1114,  1124,  1129,  1137,  1145,
    1153,  1161,  1169,  1174,  1183,  1187,  1191,  1195,  1199,  1203,
    1207,  1211,  1215,  1219,  1223,  1231,  1237,  1247,  1255,  1259,
    1267,  1271,  1279,  1283,  1287,  1295,  1301,  1311,  1319,  1327,
    1335,  1343,  1347,  1351,  1356,  1365,  1369,  1373,  1378,  1387,
    1397,  1403,  1410,  1416,  1427,  1431,  1439,  1445,  1455,  1463
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


#line 31 "../../obj/src/GrammarParser.yy" // lalr1.cc:1167
} // libcasm_fe
#line 3697 "GrammarParser.cpp" // lalr1.cc:1167
#line 1469 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
