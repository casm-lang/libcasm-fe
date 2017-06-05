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

    #include "src/SourceLocation.h"
    #include "src/Lexer.h"
    #include "src/Exceptions.h"
    #include "src/Logger.h"

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
#line 378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1330 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 384 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 392 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1348 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1358 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1378 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 424 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1386 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 432 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1394 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 436 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1410 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1418 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 456 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1428 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 462 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1438 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1446 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 1454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 507 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 525 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1511 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 533 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1525 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 543 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 554 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1546 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 560 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1556 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1564 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1572 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 582 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 590 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Identifiers::Ptr > () );
  }
#line 1588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 598 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 606 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1606 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1616 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1626 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 628 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 642 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::RELATIVE );
  }
#line 1652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 654 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 1669 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 663 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1679 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 669 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1689 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 679 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 683 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1705 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1713 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 695 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1721 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 699 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 1729 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 703 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 711 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 1745 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1753 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< Type::Ptr > () );
  }
#line 1761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1769 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 743 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1779 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 749 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 759 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 763 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 767 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
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
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
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
#line 795 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 803 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1870 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 808 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1879 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1895 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 833 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1911 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 845 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1927 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 861 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1943 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 877 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1959 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 893 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1975 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 909 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 1983 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 917 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1991 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 921 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1999 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 925 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 929 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2015 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 933 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 937 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2031 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 941 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2039 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2047 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2055 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 957 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2063 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 961 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2071 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 965 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2079 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 969 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2087 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 973 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2095 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 977 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2103 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 985 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 989 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 993 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 997 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1001 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1005 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1009 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1013 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1017 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1021 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1025 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2199 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1029 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2207 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1033 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1037 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1045 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2231 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2240 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1058 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2248 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2258 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1072 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[1].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[3].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1105 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1110 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2312 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1118 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1126 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1142 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2353 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2362 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1164 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2370 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1168 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2378 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1172 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2386 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1176 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2394 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1180 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1184 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 2410 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1188 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2418 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2426 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1196 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2434 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1200 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1204 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1212 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1218 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2470 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1228 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 2478 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1236 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2486 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1240 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2494 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1248 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2502 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1252 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 2510 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1260 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2518 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1264 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2526 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1268 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2534 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1276 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1282 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2554 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1292 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1300 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2570 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1308 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2578 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1316 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2586 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1324 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2594 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1328 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2602 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1332 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
  }
#line 2610 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1336 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
  }
#line 2618 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1344 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2626 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1348 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2634 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1352 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
  }
#line 2642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1356 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
  }
#line 2650 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1364 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2670 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1380 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2681 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1387 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2702 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2710 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2718 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2738 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1432 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2746 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2754 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2758 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -135;

  const signed char Parser::yytable_ninf_ = -55;

  const short int
  Parser::yypact_[] =
  {
      25,     5,    35,   -22,   -32,   -32,   -32,   -32,   -32,  -135,
    -135,     5,  -135,  -135,  -135,  -135,  -135,  -135,   912,   -32,
    -135,  -135,    19,  -135,    24,    39,    24,    10,   971,  -135,
     -31,  -135,  -135,  -135,   -32,   971,   -32,  -135,  -135,  -135,
     971,   971,   971,   735,   794,   -35,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,    32,    38,    44,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  1343,  -135,  -135,  -135,    26,
    -135,  -135,  -135,  -135,  -135,  -135,   -32,   -32,    27,    69,
     -39,   -35,   735,  1574,   107,   -32,    42,   100,  1109,   104,
    -135,  -135,  -135,   971,  1310,  -135,  1376,    23,  -135,   912,
    -135,   853,  -135,   971,   971,   971,   971,   971,   971,   971,
     971,   971,   971,   971,   971,   971,   971,   971,   971,   971,
     971,   971,  -135,  -135,   -30,   -35,   -32,   664,   -35,    68,
      62,    -2,  -135,  -135,  -135,  -135,  -135,  1409,  -135,  -135,
     -35,   971,   971,   971,  1442,  -135,   971,   971,  -135,   971,
    -135,  -135,  1574,   -25,     7,  1640,  1692,  1607,   122,   122,
     105,   110,   110,    70,    70,    70,  -135,  1574,  1607,   105,
     110,   110,  1574,  -135,   -32,    85,  -135,    31,   377,   393,
    -135,   -32,   -32,   -32,   664,   -23,   971,   971,    74,   455,
     471,    75,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,    92,   -35,   -35,   -35,   971,
    -135,  1244,  1178,  1277,    44,    14,  1475,  1574,  -135,  -135,
     971,  -135,   -32,   129,  -135,   522,   128,   538,   101,   135,
     136,  -135,  -135,  -135,  1144,  1211,   106,   589,    87,   605,
     971,   664,  -135,   147,   102,   -36,    16,  1673,   971,   971,
     971,  -135,  -135,  -135,  1574,  -135,  -135,  -135,  -135,  -135,
    -135,   971,   971,   971,   664,   123,  -135,  -135,  -135,  -135,
    1574,  -135,   126,   160,   -35,   -35,  -135,  -135,  1574,  -135,
     998,  1036,  1074,   163,   311,   971,   142,  -135,   138,  -135,
     664,   664,   664,   664,   145,   148,   150,  1508,   676,   146,
    1541,   912,  -135,  -135,  -135,  -135,  -135,  -135,   664,   664,
     664,  -135,  -135,  -135,   152,  -135,  -135,  -135,  -135
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
      10,     2,     3,    12,     4,     6,     5,     1,    29,     0,
      32,    36,    37,    21,    44,     0,    44,     0,   163,   162,
       0,   159,   160,     9,     0,     0,     0,    63,    65,    64,
       0,     0,     0,     0,     0,     0,    67,    68,    69,    71,
      70,    66,    27,    28,     0,   111,    81,    61,    62,    60,
      56,    57,    58,    59,    55,    23,    78,    80,    79,     0,
      73,    74,    75,    76,    77,    38,     0,     0,     0,     0,
       0,    20,     0,   164,     0,     0,    40,     0,     0,     0,
     102,    83,    84,     0,     0,   104,   107,     0,    72,     0,
      22,     0,   112,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    35,    42,     0,     0,     0,     0,     0,    19,
       0,    49,    18,    45,    46,    47,    48,     0,     7,   161,
       0,     0,     0,     0,     0,    82,     0,     0,   105,     0,
      26,   109,   107,     0,    99,    97,    98,   101,    85,    86,
      92,    93,    94,    87,    88,    89,    90,    24,   100,    91,
      95,    96,    25,    43,     0,     0,    34,     0,     0,     0,
     132,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   156,   158,   117,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,     0,     0,     0,    20,     0,
      39,     0,     0,     0,     0,     0,     0,   106,   108,    41,
       0,    31,     0,     0,   131,     0,     0,     0,     0,     0,
       0,   145,   155,   157,     0,     0,     0,     0,     0,     0,
       0,     0,    17,    16,     0,    18,     0,    52,     0,     0,
       0,   113,   110,   103,    30,    33,   153,   151,   130,   149,
     147,     0,     0,     0,     0,     0,   148,   146,   152,   150,
     154,   118,     0,    14,     0,     0,    50,   115,   114,   116,
       0,     0,     0,   133,     0,     0,     0,    11,     0,    53,
       0,     0,     0,     0,     0,     0,     0,     0,   141,     0,
       0,    29,    51,   142,   143,   144,   134,   136,     0,     0,
       0,   140,   135,    15,     0,   137,   138,   139,    13
  };

  const short int
  Parser::yypgoto_[] =
  {
    -135,  -135,   118,   197,  -135,  -135,  -135,  -135,  -135,     2,
    -135,   112,  -135,   -87,  -135,  -135,     0,  -135,   196,    -3,
     -34,  -135,   190,   -88,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,   -11,  -135,
    -135,  -135,  -100,     9,  -135,     6,    28,  -135,  -135,  -135,
    -135,    17,  -134,  -135,  -135,  -135,  -135,   -79,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,   139,  -135,  -135,  -135
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     9,    10,    11,    12,   287,   273,   129,   130,
      13,    52,    53,    54,    14,    15,    21,   177,    22,    55,
      87,   124,    78,   132,   133,   134,   135,   136,   246,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    97,   102,    69,    70,    71,    72,    73,    74,
      16,   224,   225,   194,   195,   196,   298,   299,   197,   198,
     199,   200,   201,   202,   203,   204,    29,    30,    31,    32
  };

  const short int
  Parser::yytable_[] =
  {
      23,   153,    89,   127,    24,    25,    26,    27,    28,     3,
       4,     5,     6,     7,   173,    84,   -54,    83,   -54,   218,
     188,    85,   174,   128,    88,    18,    19,   149,     1,    90,
      91,    92,    94,    96,    86,    17,    86,   175,    19,    19,
     205,    20,    98,   123,    20,   227,   215,   107,   108,   109,
       8,   208,   210,    20,    20,   237,   239,   209,   252,    81,
     110,   111,   112,   113,   114,   115,   149,    77,   275,   148,
     276,   137,   118,   119,   120,   149,   122,    86,   131,   221,
      76,    79,   144,   222,    99,    28,   100,   101,   121,   125,
     152,   140,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,     3,     4,     5,     6,     7,   126,   141,   242,   243,
     245,   143,   131,   206,   207,   131,   176,   220,   115,    93,
     211,   212,   213,   191,   241,   152,   216,   131,   217,   240,
     219,   256,   259,   261,   193,   107,   108,   228,   229,   230,
     107,   108,   262,   263,   266,   192,   268,   272,   110,   111,
     112,   113,   114,   115,   274,   112,   113,   114,   115,   286,
     284,   119,   120,   285,    86,   234,   235,   112,   113,   114,
     115,    86,    86,    86,   191,   191,   288,   289,   293,   301,
     191,   232,   302,   307,   312,   191,   191,   308,   247,   309,
     318,   231,   138,   131,   131,   131,   192,   192,    33,   254,
     244,   150,   192,   233,   314,    75,    80,   192,   192,   311,
       0,     0,   255,   251,   139,     0,     0,     0,     0,   270,
       0,   191,     0,   191,     0,     0,     0,   277,   278,   279,
       0,     0,   258,   191,   258,   191,     0,   191,     0,     0,
     280,   281,   282,   192,   258,   192,   258,     0,   271,     0,
       0,     0,     0,     0,     0,   192,     0,   192,     0,   192,
     191,   131,   131,   297,   300,     0,     0,     0,     0,     0,
       0,   283,     0,     0,     0,     0,     0,   297,     0,     0,
       0,     0,   192,     0,     0,     0,   191,   191,   191,   191,
       0,     0,     0,     0,     0,     0,     0,   303,   304,   305,
     306,     0,   294,     0,   191,   191,   191,     0,   192,   192,
     192,   192,     0,     0,     0,   315,   316,   317,     0,    34,
       0,     0,     0,     0,    35,     0,   192,   192,   192,   295,
       0,    36,     0,    37,    38,    39,     0,     0,     0,     0,
      40,    41,    42,     0,    82,     0,    44,     0,     0,     0,
       0,   296,    45,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    19,     0,     0,     0,     0,     0,   223,     0,
       0,    46,    47,    48,    49,    50,    51,    20,   178,     0,
     179,     0,   180,   181,   226,   182,   183,   184,     0,   185,
     186,     0,     0,   187,   178,     0,   179,     0,   180,   181,
       0,   182,   183,   184,     0,   185,   186,     0,     0,   187,
     188,     0,     0,     0,   189,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   188,     0,    19,     0,
     189,     0,     0,     0,     0,   190,     0,     0,     0,     0,
       0,     0,     0,    20,    19,     0,   236,     0,     0,     0,
       0,   190,     0,     0,     0,     0,   178,     0,   179,    20,
     180,   181,   238,   182,   183,   184,     0,   185,   186,     0,
       0,   187,   178,     0,   179,     0,   180,   181,     0,   182,
     183,   184,     0,   185,   186,     0,     0,   187,   188,     0,
       0,     0,   189,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   188,     0,    19,     0,   189,     0,
       0,     0,     0,   190,     0,     0,     0,     0,     0,     0,
       0,    20,    19,   178,   257,   179,     0,   180,   181,   190,
     182,   183,   184,     0,   185,   186,     0,    20,   187,   178,
       0,   179,   260,   180,   181,     0,   182,   183,   184,     0,
     185,   186,     0,     0,   187,   188,     0,     0,     0,   189,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   188,     0,    19,     0,   189,     0,     0,     0,     0,
     190,     0,     0,     0,     0,     0,     0,     0,    20,    19,
     178,     0,   179,     0,   180,   181,   190,   182,   183,   184,
       0,   185,   186,     0,    20,   187,   178,     0,   179,     0,
     180,   181,     0,   182,   183,   184,     0,   185,   186,     0,
       0,   187,   188,     0,     0,     0,   189,   267,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   188,     0,
      19,     0,   189,     0,     0,     0,     0,   190,     0,     0,
       0,     0,     0,     0,     0,    20,    19,     0,     0,     0,
       0,     0,     0,   190,   269,   178,     0,   179,     0,   180,
     181,    20,   182,   183,   184,     0,   185,   186,     0,     0,
     187,     0,     0,     0,    34,     0,     0,     0,     0,    35,
       0,     0,     0,     0,   295,     0,    36,   188,    37,    38,
      39,   189,     0,     0,     0,    40,    41,    42,     0,    82,
       0,    44,     0,     0,     0,    19,   296,    45,     0,     0,
       0,     0,   190,     0,     0,     0,     0,    19,     0,     0,
      20,     0,     0,     0,     0,     0,    46,    47,    48,    49,
      50,    51,    20,    34,     0,     0,     0,     0,    35,     0,
       0,     0,     0,     0,     0,    36,     0,    37,    38,    39,
       0,     0,     0,     0,    40,    41,    42,     0,    82,     0,
      44,     0,     0,     0,     0,     0,    45,     0,     0,     0,
      93,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,     0,     0,     0,     0,    46,    47,    48,    49,    50,
      51,    20,    34,     0,     0,     0,     0,    35,     0,     0,
       0,     0,     0,     0,    36,     0,    37,    38,    39,     0,
       0,     0,     0,    40,    41,    42,     0,    82,     0,    44,
      95,     0,     0,     0,     0,    45,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    19,     0,     0,     0,     0,
       0,     0,     0,     0,    46,    47,    48,    49,    50,    51,
      20,    34,     0,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     0,    36,     0,    37,    38,    39,     0,     0,
       0,     0,    40,    41,    42,     0,    82,   151,    44,     0,
       0,     0,     0,     0,    45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
       0,     0,     0,    46,    47,    48,    49,    50,    51,    20,
      34,     0,     0,     0,     0,    35,     0,     0,     0,     0,
       0,     0,    36,     0,    37,    38,    39,     0,     0,     0,
       0,    40,    41,    42,     0,    43,     0,    44,     0,     0,
       0,     0,     0,    45,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,     0,     0,     0,     0,     0,     0,
       0,     0,    46,    47,    48,    49,    50,    51,    20,    34,
       0,     0,     0,     0,    35,     0,     0,     0,     0,     0,
       0,    36,     0,    37,    38,    39,     0,     0,     0,     0,
      40,    41,    42,     0,    82,   290,    44,     0,     0,     0,
       0,     0,    45,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    19,   103,   104,   105,   106,     0,   107,   108,
     109,    46,    47,    48,    49,    50,    51,    20,     0,     0,
       0,   110,   111,   112,   113,   114,   115,   291,     0,     0,
       0,   117,     0,   118,   119,   120,     0,     0,     0,     0,
       0,   103,   104,   105,   106,     0,   107,   108,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,   292,     0,     0,     0,   117,
       0,   118,   119,   120,     0,     0,     0,     0,     0,   103,
     104,   105,   106,     0,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,   142,     0,     0,     0,   117,     0,   118,
     119,   120,     0,     0,   103,   104,   105,   106,     0,   107,
     108,   109,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   114,   115,   264,     0,
       0,     0,   117,     0,   118,   119,   120,     0,     0,   103,
     104,   105,   106,     0,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,   249,     0,     0,     0,   117,     0,   118,
     119,   120,     0,   103,   104,   105,   106,     0,   107,   108,
     109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,     0,   265,     0,
       0,   117,     0,   118,   119,   120,   103,   104,   105,   106,
       0,   107,   108,   109,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
       0,     0,     0,   248,   117,     0,   118,   119,   120,   103,
     104,   105,   106,     0,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,     0,     0,     0,     0,   117,   250,   118,
     119,   120,   103,   104,   105,   106,     0,   107,   108,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,     0,     0,     0,     0,
     117,     0,   118,   119,   120,   103,   104,   105,   106,     0,
     107,   108,   109,     0,   145,     0,     0,     0,     0,     0,
       0,     0,   146,   110,   111,   112,   113,   114,   115,     0,
       0,     0,     0,   117,     0,   118,   119,   120,   103,   104,
     105,   106,     0,   107,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   111,   112,   113,
     114,   115,     0,     0,     0,   116,   117,     0,   118,   119,
     120,   103,   104,   105,   106,     0,   107,   108,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,     0,   147,     0,     0,   117,
       0,   118,   119,   120,   103,   104,   105,   106,     0,   107,
     108,   109,     0,   145,     0,     0,     0,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   114,   115,     0,     0,
       0,     0,   117,     0,   118,   119,   120,   103,   104,   105,
     106,     0,   107,   108,   109,     0,   214,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   114,
     115,     0,     0,     0,     0,   117,     0,   118,   119,   120,
     103,   104,   105,   106,     0,   107,   108,   109,     0,     0,
       0,   253,     0,     0,     0,     0,     0,     0,   110,   111,
     112,   113,   114,   115,     0,     0,     0,     0,   117,     0,
     118,   119,   120,   103,   104,   105,   106,     0,   107,   108,
     109,     0,     0,     0,     0,     0,     0,   310,     0,     0,
       0,   110,   111,   112,   113,   114,   115,     0,     0,     0,
       0,   117,     0,   118,   119,   120,   103,   104,   105,   106,
       0,   107,   108,   109,     0,     0,     0,     0,     0,   313,
       0,     0,     0,     0,   110,   111,   112,   113,   114,   115,
       0,     0,     0,     0,   117,     0,   118,   119,   120,   103,
     104,   105,   106,     0,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,     0,     0,     0,     0,   117,     0,   118,
     119,   120,   103,   104,   105,     0,     0,   107,   108,   109,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     110,   111,   112,   113,   114,   115,     0,     0,     0,     0,
       0,     0,   118,   119,   120,   103,     0,   105,     0,     0,
     107,   108,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,   115,     0,
       0,     0,     0,     0,     0,   118,   119,   120,   103,   104,
     105,   106,     0,   107,   108,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   103,     0,   113,
     114,   115,   107,   108,   109,     0,   117,     0,   118,   119,
     120,     0,     0,     0,     0,   110,   111,   112,   113,   114,
     115,     0,     0,     0,     0,     0,     0,   118,   119,   120
  };

  const short int
  Parser::yycheck_[] =
  {
       3,   101,    36,    42,     4,     5,     6,     7,     8,     4,
       5,     6,     7,     8,    44,    46,    52,    28,    54,    44,
      43,    52,    52,    62,    35,    47,    61,    52,     3,    40,
      41,    42,    43,    44,    34,     0,    36,   125,    61,    61,
     128,    76,    45,    77,    76,   179,   146,    40,    41,    42,
      45,    53,   140,    76,    76,   189,   190,    59,    44,    49,
      53,    54,    55,    56,    57,    58,    52,    43,    52,    46,
      54,    82,    65,    66,    67,    52,    76,    77,    81,    48,
      61,    42,    93,    52,    52,    85,    48,    43,    62,    62,
     101,    49,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   120,
     121,     4,     5,     6,     7,     8,    47,    17,   206,   207,
     208,    17,   125,    55,    62,   128,   126,    42,    58,    55,
     141,   142,   143,   127,    42,   146,   147,   140,   149,    64,
     174,    12,    14,    42,   127,    40,    41,   181,   182,   183,
      40,    41,    17,    17,    48,   127,    69,    10,    53,    54,
      55,    56,    57,    58,    62,    55,    56,    57,    58,     9,
      47,    66,    67,    47,   174,   186,   187,    55,    56,    57,
      58,   181,   182,   183,   178,   179,   274,   275,    25,    47,
     184,   185,    54,    48,    48,   189,   190,    49,   209,    49,
      48,   184,    84,   206,   207,   208,   178,   179,    11,   220,
     208,    99,   184,   185,   301,    19,    26,   189,   190,   298,
      -1,    -1,   222,   214,    85,    -1,    -1,    -1,    -1,   240,
      -1,   225,    -1,   227,    -1,    -1,    -1,   248,   249,   250,
      -1,    -1,   225,   237,   227,   239,    -1,   241,    -1,    -1,
     261,   262,   263,   225,   237,   227,   239,    -1,   241,    -1,
      -1,    -1,    -1,    -1,    -1,   237,    -1,   239,    -1,   241,
     264,   274,   275,   284,   285,    -1,    -1,    -1,    -1,    -1,
      -1,   264,    -1,    -1,    -1,    -1,    -1,   298,    -1,    -1,
      -1,    -1,   264,    -1,    -1,    -1,   290,   291,   292,   293,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   290,   291,   292,
     293,    -1,     1,    -1,   308,   309,   310,    -1,   290,   291,
     292,   293,    -1,    -1,    -1,   308,   309,   310,    -1,    18,
      -1,    -1,    -1,    -1,    23,    -1,   308,   309,   310,    28,
      -1,    30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,    40,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,
      -1,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,     1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    11,    -1,
      13,    -1,    15,    16,     1,    18,    19,    20,    -1,    22,
      23,    -1,    -1,    26,    11,    -1,    13,    -1,    15,    16,
      -1,    18,    19,    20,    -1,    22,    23,    -1,    -1,    26,
      43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,    61,    -1,
      47,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    61,    -1,     1,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    11,    -1,    13,    76,
      15,    16,     1,    18,    19,    20,    -1,    22,    23,    -1,
      -1,    26,    11,    -1,    13,    -1,    15,    16,    -1,    18,
      19,    20,    -1,    22,    23,    -1,    -1,    26,    43,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    43,    -1,    61,    -1,    47,    -1,
      -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    61,    11,    12,    13,    -1,    15,    16,    68,
      18,    19,    20,    -1,    22,    23,    -1,    76,    26,    11,
      -1,    13,    14,    15,    16,    -1,    18,    19,    20,    -1,
      22,    23,    -1,    -1,    26,    43,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    43,    -1,    61,    -1,    47,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    61,
      11,    -1,    13,    -1,    15,    16,    68,    18,    19,    20,
      -1,    22,    23,    -1,    76,    26,    11,    -1,    13,    -1,
      15,    16,    -1,    18,    19,    20,    -1,    22,    23,    -1,
      -1,    26,    43,    -1,    -1,    -1,    47,    48,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      61,    -1,    47,    -1,    -1,    -1,    -1,    68,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    76,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    11,    -1,    13,    -1,    15,
      16,    76,    18,    19,    20,    -1,    22,    23,    -1,    -1,
      26,    -1,    -1,    -1,    18,    -1,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    28,    -1,    30,    43,    32,    33,
      34,    47,    -1,    -1,    -1,    39,    40,    41,    -1,    43,
      -1,    45,    -1,    -1,    -1,    61,    50,    51,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    -1,    -1,    61,    -1,    -1,
      76,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    18,    -1,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    40,    41,    -1,    43,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    18,    -1,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,    40,    41,    -1,    43,    -1,    45,
      46,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    18,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    34,    -1,    -1,
      -1,    -1,    39,    40,    41,    -1,    43,    44,    45,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      18,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,    40,    41,    -1,    43,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    18,
      -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,    40,    41,    -1,    43,    17,    45,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    35,    36,    37,    38,    -1,    40,    41,
      42,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
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
      56,    57,    58,    25,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,    -1,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    27,    -1,
      -1,    63,    -1,    65,    66,    67,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    29,    63,    -1,    65,    66,    67,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    31,    65,
      66,    67,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      63,    -1,    65,    66,    67,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    44,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    52,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    63,    -1,    65,    66,    67,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    62,    63,    -1,    65,    66,
      67,    35,    36,    37,    38,    -1,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    60,    -1,    -1,    63,
      -1,    65,    66,    67,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    63,    -1,    65,    66,    67,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,
      65,    66,    67,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    -1,    65,    66,    67,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    -1,    65,    66,    67,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,    35,    36,    37,    -1,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    65,    66,    67,    35,    -1,    37,    -1,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    35,    36,
      37,    38,    -1,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    35,    -1,    56,
      57,    58,    40,    41,    42,    -1,    63,    -1,    65,    66,
      67,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,    67
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    82,     4,     5,     6,     7,     8,    45,    83,
      84,    85,    86,    91,    95,    96,   131,     0,    47,    61,
      76,    97,    99,   100,    97,    97,    97,    97,    97,   147,
     148,   149,   150,    84,    18,    23,    30,    32,    33,    34,
      39,    40,    41,    43,    45,    51,    70,    71,    72,    73,
      74,    75,    92,    93,    94,   100,   110,   111,   112,   113,
     114,   115,   116,   117,   118,   119,   120,   121,   122,   125,
     126,   127,   128,   129,   130,    99,    61,    43,   103,    42,
     103,    49,    43,   119,    46,    52,    97,   101,   119,   101,
     119,   119,   119,    55,   119,    46,   119,   123,   100,    52,
      48,    43,   124,    35,    36,    37,    38,    40,    41,    42,
      53,    54,    55,    56,    57,    58,    62,    63,    65,    66,
      67,    62,    97,   101,   102,    62,    47,    42,    62,    89,
      90,   100,   104,   105,   106,   107,   108,   119,    83,   147,
      49,    17,    24,    17,   119,    44,    52,    60,    46,    52,
      92,    44,   119,   123,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,    44,    52,   104,    97,    98,    11,    13,
      15,    16,    18,    19,    20,    22,    23,    26,    43,    47,
      68,   126,   127,   132,   134,   135,   136,   139,   140,   141,
     142,   143,   144,   145,   146,   104,    55,    62,    53,    59,
     104,   119,   119,   119,    44,   123,   119,   119,    44,   101,
      42,    48,    52,     1,   132,   133,     1,   133,   101,   101,
     101,   132,   126,   127,   119,   119,     1,   133,     1,   133,
      64,    42,   104,   104,    90,   104,   109,   119,    29,    25,
      31,   124,    44,    46,   119,    97,    12,    12,   132,    14,
      14,    42,    17,    17,    24,    27,    48,    48,    69,    69,
     119,   132,    10,    88,    62,    52,    54,   119,   119,   119,
     119,   119,   119,   132,    47,    47,     9,    87,   104,   104,
      17,    21,    21,    25,     1,    28,    50,   119,   137,   138,
     119,    47,    54,   132,   132,   132,   132,    48,    49,    49,
      49,   138,    48,    48,    94,   132,   132,   132,    48
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    81,    82,    83,    83,    83,    83,    84,    84,    85,
      85,    86,    86,    87,    87,    88,    88,    89,    89,    90,
      90,    91,    91,    92,    92,    92,    93,    93,    94,    94,
      95,    96,    97,    98,    98,    99,    99,   100,   100,   101,
     101,   102,   102,   103,   103,   104,   104,   104,   104,   105,
     106,   107,   108,   109,   109,   110,   110,   110,   110,   110,
     110,   110,   110,   111,   112,   112,   113,   114,   114,   115,
     116,   117,   118,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   121,   122,   122,   123,   123,   124,   124,
     125,   126,   126,   127,   128,   129,   130,   131,   131,   132,
     132,   132,   132,   132,   132,   132,   132,   132,   132,   132,
     133,   133,   134,   135,   135,   136,   136,   137,   137,   137,
     138,   138,   139,   140,   141,   142,   143,   143,   143,   143,
     144,   144,   144,   144,   145,   146,   146,   146,   146,   147,
     147,   148,   148,   149,   150
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     4,     1,     2,
       1,     8,     1,     4,     0,     4,     0,     3,     1,     1,
       0,     2,     4,     1,     3,     3,     3,     1,     1,     0,
       7,     6,     1,     3,     1,     3,     1,     1,     2,     3,
       1,     3,     1,     3,     0,     1,     1,     1,     1,     1,
       4,     6,     3,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     5,     2,     3,     3,     1,     3,     2,
       5,     1,     2,     5,     6,     6,     6,     5,     7,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     4,     6,     6,     6,     3,     3,     3,
       2,     1,     6,     6,     6,     2,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     2,     1,     1,
       1,     3,     1,     1,     2
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
       0,   345,   345,   357,   361,   365,   369,   377,   383,   391,
     397,   407,   423,   431,   435,   443,   447,   455,   461,   471,
     475,   483,   506,   524,   532,   542,   553,   559,   569,   573,
     581,   589,   597,   605,   611,   621,   627,   637,   641,   649,
     653,   662,   668,   678,   682,   690,   694,   698,   702,   710,
     718,   726,   734,   742,   748,   758,   762,   766,   770,   774,
     778,   782,   786,   794,   802,   807,   816,   832,   844,   860,
     876,   892,   908,   916,   920,   924,   928,   932,   936,   940,
     944,   948,   956,   960,   964,   968,   972,   976,   980,   984,
     988,   992,   996,  1000,  1004,  1008,  1012,  1016,  1020,  1024,
    1028,  1032,  1036,  1044,  1052,  1057,  1065,  1071,  1081,  1085,
    1094,  1104,  1109,  1117,  1125,  1133,  1141,  1149,  1154,  1163,
    1167,  1171,  1175,  1179,  1183,  1187,  1191,  1195,  1199,  1203,
    1211,  1217,  1227,  1235,  1239,  1247,  1251,  1259,  1263,  1267,
    1275,  1281,  1291,  1299,  1307,  1315,  1323,  1327,  1331,  1335,
    1343,  1347,  1351,  1355,  1363,  1373,  1379,  1386,  1392,  1403,
    1407,  1415,  1421,  1431,  1439
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
#line 3654 "GrammarParser.cpp" // lalr1.cc:1167
#line 1445 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
