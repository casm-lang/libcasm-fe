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

    #include "src/Location.h"
    #include "src/Lexer.h"
    #include "src/Exceptions.h"
    #include "src/Logger.h"

    #include "../stdhl/cpp/Type.h"

    #undef yylex
    #define yylex lexer.nextToken

    static BasicType::Ptr createVoidType( Location& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::VoidType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto node = Ast::make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( Location& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::RuleReferenceType >();
        const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
        const auto node = Ast::make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( Location& sourceLocation )
    {
        const auto name = Ast::make< Identifier >( sourceLocation, "Agent" );
        const auto node = Ast::make< BasicType >( sourceLocation, name );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( Location& sourceLocation )
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
        const auto identifiers = Ast::make< Identifiers >( location );
        identifiers->add( identifier );
        return Ast::make< IdentifierPath >( location, identifiers,
                IdentifierPath::Type::ABSOLUTE );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
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

#line 125 "GrammarParser.cpp" // lalr1.cc:413


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
#line 211 "GrammarParser.cpp" // lalr1.cc:479

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
      case 143: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 144: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 145: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 103: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 139: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 142: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 134: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 133: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 135: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 104: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 125: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 132: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 81: // Definition
      case 82: // AttributedDefinition
        value.move< Definition::Ptr > (that.value);
        break;

      case 83: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 93: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 123: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 94: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 127: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 86: // MaybeDefined
      case 107: // Atom
      case 116: // Term
      case 117: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 146: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 120: // Terms
      case 121: // Arguments
      case 122: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 105: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 137: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 84: // FunctionDefinition
      case 89: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 95: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 98: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 96: // Identifiers
      case 97: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 124: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 138: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 136: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 119: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 85: // MaybeInitially
      case 91: // Initializers
      case 92: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 100: // Parameters
      case 101: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 118: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 129: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 128: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 115: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 130: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 140: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 131: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 80: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 102: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 87: // FunctionParameters
      case 88: // MaybeFunctionParameters
      case 106: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 108: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 126: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 90: // Initializer
      case 141: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 109: // Boolean
      case 110: // String
      case 111: // BitNumber
      case 112: // IntegerNumber
      case 113: // FloatingNumber
      case 114: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 99: // Variable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
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
      case 143: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 144: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 145: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 103: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 139: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 142: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 134: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 133: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 135: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 104: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 125: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 132: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 81: // Definition
      case 82: // AttributedDefinition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 83: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 93: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 123: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 94: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 127: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 86: // MaybeDefined
      case 107: // Atom
      case 116: // Term
      case 117: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 146: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 120: // Terms
      case 121: // Arguments
      case 122: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 105: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 137: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 84: // FunctionDefinition
      case 89: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 95: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 98: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 96: // Identifiers
      case 97: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 124: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 138: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 136: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 119: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 85: // MaybeInitially
      case 91: // Initializers
      case 92: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 100: // Parameters
      case 101: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 118: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 129: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 128: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 115: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 130: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 140: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 131: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 80: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 102: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 87: // FunctionParameters
      case 88: // MaybeFunctionParameters
      case 106: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 108: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 126: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 90: // Initializer
      case 141: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 109: // Boolean
      case 110: // String
      case 111: // BitNumber
      case 112: // IntegerNumber
      case 113: // FloatingNumber
      case 114: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 99: // Variable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
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
      case 143: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 144: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 145: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 103: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 139: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 142: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 134: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 133: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 135: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 104: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 125: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 132: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 81: // Definition
      case 82: // AttributedDefinition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 83: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 93: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 123: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 94: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 127: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 86: // MaybeDefined
      case 107: // Atom
      case 116: // Term
      case 117: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 146: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 120: // Terms
      case 121: // Arguments
      case 122: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 105: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 137: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 84: // FunctionDefinition
      case 89: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 95: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 98: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 96: // Identifiers
      case 97: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 124: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 138: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 136: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 119: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 85: // MaybeInitially
      case 91: // Initializers
      case 92: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 100: // Parameters
      case 101: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 118: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 129: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 128: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 115: // RuleReference
        yylhs.value.build< RuleReferenceAtom::Ptr > ();
        break;

      case 130: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 140: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 131: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 80: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 102: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 87: // FunctionParameters
      case 88: // MaybeFunctionParameters
      case 106: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 108: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 126: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 90: // Initializer
      case 141: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 109: // Boolean
      case 110: // String
      case 111: // BitNumber
      case 112: // IntegerNumber
      case 113: // FloatingNumber
      case 114: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 99: // Variable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 68: // "binary"
      case 69: // "hexadecimal"
      case 70: // "integer"
      case 71: // "rational"
      case 72: // "floating"
      case 73: // "string"
      case 74: // "identifier"
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
#line 336 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& fileName = filePath.substr( filePath.find_last_of( "/\\" ) + 1 );
      const std::string& name = fileName.substr( 0, fileName.rfind( "." ) );

      const auto specificationName = make< Identifier >( yylhs.location, name );
      result = Ast::make< Specification >( yylhs.location, specificationName, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1258 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 348 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 352 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1274 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 356 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 360 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 368 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1300 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1308 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1318 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1348 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 414 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1356 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 426 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1372 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1380 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1398 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 452 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 462 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1416 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 1424 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 474 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      auto arguments = Ast::make< Expressions >( yylhs.location );
      // TODO add `default` agent to arguments
      const auto program = Ast::make< DirectCallExpression >(
          yylhs.location, asIdentifierPath( programDefinition->identifier() ), arguments );

      const auto ruleReference = Ast::make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );

      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1445 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 491 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1474 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 516 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 525 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 535 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 551 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1525 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 555 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1533 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 563 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1541 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 571 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Identifiers::Ptr > () );
  }
#line 1549 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 579 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 593 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 604 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 610 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1597 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 1605 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::RELATIVE );
  }
#line 1613 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 632 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1621 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 636 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 1630 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 645 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1640 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1650 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 661 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1658 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 665 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1666 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 673 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1674 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1682 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 681 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1690 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 689 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 1698 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 697 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1706 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1714 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 713 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1724 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1734 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 729 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1742 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 733 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1750 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 737 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1758 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 741 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1766 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 745 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 749 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 753 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1790 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1798 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 765 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1806 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 773 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1815 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1824 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 787 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1840 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 803 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1856 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 815 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1872 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 831 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1888 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 847 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1904 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 863 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1920 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 879 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleReferenceAtom::Ptr > () = Ast::make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 1928 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1936 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 891 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1944 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 895 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1952 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 899 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1960 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 903 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1968 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 907 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 911 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 915 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2000 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 927 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2008 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 931 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2016 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 935 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2024 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 939 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2032 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 943 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2040 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 947 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2048 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 951 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2056 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 955 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2064 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 959 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call power builtin
  }
#line 2072 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 963 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2080 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 967 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2088 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 971 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2096 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 975 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2104 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 979 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2112 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 983 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2120 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 987 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2128 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 991 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2136 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 995 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2144 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 999 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO add implies instruction
  }
#line 2152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1003 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1011 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1019 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2177 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1032 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2195 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1038 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2205 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1048 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2213 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1052 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2222 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1061 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[1].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[3].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2232 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1071 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2241 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1076 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2249 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1084 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2257 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1092 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2265 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1100 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1108 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2281 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1116 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1121 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2299 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1130 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2307 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1138 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2323 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1142 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2331 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1146 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2339 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2347 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1158 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1162 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2371 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1166 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2379 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1174 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1180 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1190 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 2407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1198 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1202 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1210 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2431 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1218 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2439 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1222 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2447 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1226 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2455 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1234 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1240 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1250 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2483 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1258 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1266 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1274 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1278 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1286 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1290 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1298 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1306 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2549 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1312 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2560 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1319 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2570 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1325 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2581 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1336 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2589 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1340 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2597 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1348 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1354 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1364 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1372 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2633 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2637 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -159;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      36,    59,    42,   -17,   -13,   -13,   -13,   -13,   -13,  -159,
    -159,    59,  -159,  -159,  -159,  -159,  -159,  -159,   661,   -13,
    -159,  -159,     9,  -159,    37,    41,    37,    51,   718,  -159,
      46,  -159,  -159,  -159,   -13,   718,   -13,  -159,  -159,  -159,
     718,   718,   718,   490,   547,   -39,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,    58,    48,    72,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  1023,  -159,  -159,  -159,    40,
    -159,  -159,  -159,  -159,  -159,  -159,   -13,   -13,    61,    73,
     -24,   -13,   490,  1247,   201,   -13,    78,   107,   794,   110,
    -159,  -159,  -159,   718,   991,  -159,  1055,    47,  -159,   661,
    -159,   604,  -159,   718,   718,   718,   718,   718,   718,   718,
     718,   718,   718,   718,   718,   718,   718,   718,   718,   718,
     718,  -159,  -159,   -20,   -13,   -13,   421,   -13,    81,    77,
      44,  -159,  -159,  -159,  -159,  1087,  -159,  -159,   -13,   718,
     718,   718,  1119,  -159,   718,   718,  -159,   718,  -159,  -159,
    1247,   -10,  1330,  1311,   139,  1279,    50,    50,   348,   189,
     189,    80,    80,    80,  -159,  1247,   348,   189,   189,  1247,
    -159,   -13,   101,  -159,    23,   421,   421,  -159,   -13,   -13,
     421,   -16,   718,   718,    89,   421,   421,   102,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,  -159,
     124,   -13,   -13,   -13,   718,  -159,   927,   863,   959,    72,
      -5,  1151,  1247,  -159,  -159,   718,  -159,   -13,  -159,    -6,
      34,   125,   151,  -159,  -159,  -159,   829,   895,   351,   364,
     718,   421,  -159,   160,  -159,   -29,   279,   718,   718,   718,
    -159,  -159,  -159,  1247,  -159,  -159,  -159,  -159,   718,   718,
     421,   140,  -159,  -159,  1247,  -159,   143,   162,   -13,  -159,
    -159,  1247,  -159,    76,   759,   161,   433,   718,   154,  -159,
    -159,   421,   421,   421,   166,   167,  1183,   433,   163,  1215,
     661,  -159,  -159,  -159,   421,   421,   421,  -159,  -159,  -159,
     169,  -159,  -159,  -159,  -159
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
      10,     2,     3,    12,     4,     6,     5,     1,    29,     0,
      32,    36,    37,    21,    44,     0,    44,     0,   153,   152,
       0,   149,   150,     9,     0,     0,     0,    61,    63,    62,
       0,     0,     0,     0,     0,     0,    65,    66,    67,    69,
      68,    64,    27,    28,     0,   108,    79,    59,    60,    58,
      54,    55,    56,    57,    53,    23,    76,    78,    77,     0,
      71,    72,    73,    74,    75,    38,     0,     0,     0,     0,
       0,    20,     0,   154,     0,     0,    40,     0,     0,     0,
      99,    81,    82,     0,     0,   101,   104,     0,    70,     0,
      22,     0,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    35,    42,     0,     0,     0,     0,     0,    19,     0,
      48,    18,    45,    46,    47,     0,     7,   151,     0,     0,
       0,     0,     0,    80,     0,     0,   102,     0,    26,   106,
     104,     0,    97,    95,    96,    98,    83,    84,    90,    91,
      92,    85,    86,    87,    88,    24,    89,    93,    94,    25,
      43,     0,     0,    34,     0,     0,     0,   128,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   146,   148,   114,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
       0,     0,     0,     0,     0,    39,     0,     0,     0,     0,
       0,     0,   103,   105,    41,     0,    31,     0,   127,     0,
       0,     0,     0,   139,   145,   147,     0,     0,     0,     0,
       0,     0,    17,    16,    52,     0,    50,     0,     0,     0,
     110,   107,   100,    30,    33,   143,   126,   141,     0,     0,
       0,     0,   140,   142,   144,   115,     0,    14,     0,    49,
     112,   111,   113,     0,     0,   129,     0,     0,     0,    11,
      51,     0,     0,     0,     0,     0,     0,   136,     0,     0,
      29,   137,   138,   130,     0,     0,     0,   135,   131,    15,
       0,   132,   133,   134,    13
  };

  const short int
  Parser::yypgoto_[] =
  {
    -159,  -159,   133,   207,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,   120,  -159,   -58,  -159,  -159,    -4,  -159,   205,    17,
      -2,  -159,   206,  -113,  -159,  -159,  -159,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,  -159,  -159,  -159,    43,  -159,  -159,
    -159,   -93,    18,  -159,    55,    75,  -159,  -159,  -159,  -159,
      -8,  -158,  -159,  -159,  -159,  -159,   -44,  -159,  -159,  -159,
    -159,  -159,  -159,  -159,   149,  -159,  -159,  -159
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     9,    10,    11,    12,   269,   257,   128,   129,
      13,    52,    53,    54,    14,    15,    21,   174,    22,    55,
      87,   123,    78,   131,   132,   133,   134,   235,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    97,   102,    69,    70,    71,    72,    73,    74,    16,
     218,   219,   190,   191,   192,   277,   278,   193,   194,   195,
     196,   197,   198,   199,    29,    30,    31,    32
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      24,    25,    26,    27,    28,   175,   245,   176,   151,   177,
     178,   172,   179,   180,   200,   181,   182,   126,   220,   183,
      23,    19,   258,   170,   259,   205,   184,   228,   229,    18,
      86,   171,    86,   213,    89,    20,   184,   127,   241,     1,
     185,   147,    17,    19,    19,   175,   147,   176,   247,   177,
     178,   210,   179,   180,    19,   181,   182,    20,    20,   183,
     186,    20,    98,     3,     4,     5,     6,     7,    20,    76,
     216,    83,   121,    86,   217,   122,   184,   130,    88,    77,
     185,    28,    79,    90,    91,    92,    94,    96,   232,   233,
     234,    84,   146,   271,    19,   100,   203,    85,   147,    81,
     186,   120,   204,     8,   112,   113,   114,   115,    20,    99,
     103,   104,   105,   106,   101,   107,   108,   109,   189,   125,
     130,   173,   124,   130,   139,   135,   138,   141,   110,   111,
     112,   113,   114,   115,   130,   201,   142,   115,   202,   117,
     118,   119,   215,    93,   150,   270,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     166,   167,   168,   169,   230,   231,   248,    86,   249,   214,
     256,   268,   223,   103,    86,    86,   221,   222,   107,   108,
     109,   187,   206,   207,   208,   273,   266,   150,   211,   267,
     212,   110,   111,   112,   113,   114,   115,   130,   130,   130,
     280,   188,   117,   118,   119,     3,     4,     5,     6,     7,
     288,   246,   246,   244,   284,   285,   294,   136,    33,   148,
     246,   246,   290,   255,    75,   226,   227,   240,   107,   108,
     187,   187,    80,   287,   137,   187,   224,     0,     0,     0,
     187,   187,   265,   112,   113,   114,   115,   236,     0,     0,
     188,   188,     0,     0,   130,   188,   225,     0,   243,     0,
     188,   188,     0,   281,   282,   283,     0,     0,     0,     0,
       0,     0,     0,   254,   187,   187,   291,   292,   293,     0,
     260,   261,   262,   187,   187,     0,   187,     0,     0,     0,
       0,   263,   264,     0,   188,   188,     0,     0,     0,     0,
       0,     0,     0,   188,   188,   187,   188,     0,     0,   276,
     279,     0,     0,   103,   104,   105,   106,     0,   107,   108,
     276,     0,     0,     0,     0,   188,   187,   187,   187,     0,
       0,   110,     0,     0,   113,   114,   115,     0,     0,   187,
     187,   187,   117,   118,   119,     0,   188,   188,   188,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   188,
     188,   188,   175,     0,   176,     0,   177,   178,     0,   179,
     180,     0,   181,   182,     0,   175,   183,   176,     0,   177,
     178,     0,   179,   180,     0,   181,   182,   107,   108,   183,
       0,     0,     0,   184,     0,     0,     0,   185,   252,     0,
     110,   111,   112,   113,   114,   115,   184,     0,     0,     0,
     185,    19,   118,   119,     0,     0,     0,   186,     0,     0,
       0,     0,     0,     0,    19,    20,     0,     0,     0,     0,
     186,   253,   175,     0,   176,     0,   177,   178,    20,   179,
     180,     0,   181,   182,     0,     0,   183,     0,     0,     0,
       0,    34,     0,     0,     0,    35,     0,     0,     0,     0,
     274,     0,    36,   184,    37,    38,    39,   185,     0,     0,
       0,    40,    41,    42,     0,    82,     0,    44,     0,     0,
       0,    19,   275,    45,     0,     0,     0,   186,     0,     0,
       0,     0,     0,    19,     0,    20,     0,     0,     0,     0,
       0,    46,    47,    48,    49,    50,    51,    20,    34,     0,
       0,     0,    35,     0,     0,     0,     0,     0,     0,    36,
       0,    37,    38,    39,     0,     0,     0,     0,    40,    41,
      42,     0,    82,     0,    44,     0,     0,     0,     0,     0,
      45,     0,     0,     0,    93,     0,     0,     0,     0,     0,
      19,     0,     0,     0,     0,     0,     0,     0,    46,    47,
      48,    49,    50,    51,    20,    34,     0,     0,     0,    35,
       0,     0,     0,     0,     0,     0,    36,     0,    37,    38,
      39,     0,     0,     0,     0,    40,    41,    42,     0,    82,
       0,    44,    95,     0,     0,     0,     0,    45,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    19,     0,     0,
       0,     0,     0,     0,     0,    46,    47,    48,    49,    50,
      51,    20,    34,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     0,    36,     0,    37,    38,    39,     0,     0,
       0,     0,    40,    41,    42,     0,    82,   149,    44,     0,
       0,     0,     0,     0,    45,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
       0,     0,    46,    47,    48,    49,    50,    51,    20,    34,
       0,     0,     0,    35,     0,     0,     0,     0,     0,     0,
      36,     0,    37,    38,    39,     0,     0,     0,     0,    40,
      41,    42,     0,    43,     0,    44,     0,     0,     0,     0,
       0,    45,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    19,     0,     0,     0,     0,     0,     0,     0,    46,
      47,    48,    49,    50,    51,    20,    34,     0,     0,     0,
      35,     0,     0,     0,     0,     0,     0,    36,     0,    37,
      38,    39,     0,     0,     0,     0,    40,    41,    42,     0,
      82,     0,    44,     0,     0,     0,     0,     0,    45,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    19,   272,
       0,     0,     0,     0,     0,     0,    46,    47,    48,    49,
      50,    51,    20,   103,   104,   105,   106,     0,   107,   108,
     109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,   140,     0,     0,
       0,     0,   117,   118,   119,     0,     0,     0,   103,   104,
     105,   106,     0,   107,   108,   109,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   110,   111,   112,   113,
     114,   115,   250,     0,     0,     0,     0,   117,   118,   119,
       0,     0,     0,   103,   104,   105,   106,     0,   107,   108,
     109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,   238,     0,     0,
       0,     0,   117,   118,   119,     0,     0,   103,   104,   105,
     106,     0,   107,   108,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   114,
     115,   251,     0,     0,     0,     0,   117,   118,   119,   103,
     104,   105,   106,     0,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,     0,     0,   237,     0,     0,   117,   118,
     119,   103,   104,   105,   106,     0,   107,   108,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,     0,     0,     0,     0,   239,
     117,   118,   119,   103,   104,   105,   106,     0,   107,   108,
     109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,     0,     0,     0,
       0,     0,   117,   118,   119,   103,   104,   105,   106,     0,
     107,   108,   109,     0,   143,     0,     0,     0,     0,     0,
       0,     0,   144,   110,   111,   112,   113,   114,   115,     0,
       0,     0,     0,     0,   117,   118,   119,   103,   104,   105,
     106,     0,   107,   108,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   110,   111,   112,   113,   114,
     115,     0,     0,     0,   116,     0,   117,   118,   119,   103,
     104,   105,   106,     0,   107,   108,   109,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,     0,   145,     0,     0,     0,   117,   118,
     119,   103,   104,   105,   106,     0,   107,   108,   109,     0,
     143,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,     0,     0,     0,     0,     0,
     117,   118,   119,   103,   104,   105,   106,     0,   107,   108,
     109,     0,   209,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,     0,     0,     0,
       0,     0,   117,   118,   119,   103,   104,   105,   106,     0,
     107,   108,   109,     0,     0,     0,   242,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,   115,     0,
       0,     0,     0,     0,   117,   118,   119,   103,   104,   105,
     106,     0,   107,   108,   109,     0,     0,     0,     0,     0,
       0,   286,     0,     0,     0,   110,   111,   112,   113,   114,
     115,     0,     0,     0,     0,     0,   117,   118,   119,   103,
     104,   105,   106,     0,   107,   108,   109,     0,     0,     0,
       0,     0,   289,     0,     0,     0,     0,   110,   111,   112,
     113,   114,   115,     0,     0,     0,     0,     0,   117,   118,
     119,   103,   104,   105,   106,     0,   107,   108,   109,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   110,
     111,   112,   113,   114,   115,     0,     0,     0,     0,     0,
     117,   118,   119,   103,   104,   105,     0,     0,   107,   108,
     109,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   110,   111,   112,   113,   114,   115,     0,     0,     0,
       0,     0,   117,   118,   119,   103,     0,   105,     0,     0,
     107,   108,   109,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   110,   111,   112,   113,   114,   115,   107,
     108,   109,     0,     0,   117,   118,   119,     0,     0,     0,
       0,     0,   110,   111,   112,   113,   114,   115,     0,     0,
       0,     0,     0,   117,   118,   119
  };

  const short int
  Parser::yycheck_[] =
  {
       4,     5,     6,     7,     8,    11,    12,    13,   101,    15,
      16,   124,    18,    19,   127,    21,    22,    41,   176,    25,
       3,    60,    51,    43,    53,   138,    42,   185,   186,    46,
      34,    51,    36,    43,    36,    74,    42,    61,    43,     3,
      46,    51,     0,    60,    60,    11,    51,    13,    14,    15,
      16,   144,    18,    19,    60,    21,    22,    74,    74,    25,
      66,    74,    45,     4,     5,     6,     7,     8,    74,    60,
      47,    28,    76,    77,    51,    77,    42,    81,    35,    42,
      46,    85,    41,    40,    41,    42,    43,    44,   201,   202,
     203,    45,    45,    17,    60,    47,    52,    51,    51,    48,
      66,    61,    58,    44,    54,    55,    56,    57,    74,    51,
      34,    35,    36,    37,    42,    39,    40,    41,   126,    46,
     124,   125,    61,   127,    17,    82,    48,    17,    52,    53,
      54,    55,    56,    57,   138,    54,    93,    57,    61,    63,
      64,    65,    41,    54,   101,   258,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   120,    62,    41,    41,   171,    17,   171,
      10,     9,   180,    34,   178,   179,   178,   179,    39,    40,
      41,   126,   139,   140,   141,    24,    46,   144,   145,    46,
     147,    52,    53,    54,    55,    56,    57,   201,   202,   203,
      46,   126,    63,    64,    65,     4,     5,     6,     7,     8,
      47,   219,   220,   217,    48,    48,    47,    84,    11,    99,
     228,   229,   280,   231,    19,   182,   183,   209,    39,    40,
     175,   176,    26,   277,    85,   180,   181,    -1,    -1,    -1,
     185,   186,   250,    54,    55,    56,    57,   204,    -1,    -1,
     175,   176,    -1,    -1,   258,   180,   181,    -1,   215,    -1,
     185,   186,    -1,   271,   272,   273,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   230,   219,   220,   284,   285,   286,    -1,
     237,   238,   239,   228,   229,    -1,   231,    -1,    -1,    -1,
      -1,   248,   249,    -1,   219,   220,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   228,   229,   250,   231,    -1,    -1,   266,
     267,    -1,    -1,    34,    35,    36,    37,    -1,    39,    40,
     277,    -1,    -1,    -1,    -1,   250,   271,   272,   273,    -1,
      -1,    52,    -1,    -1,    55,    56,    57,    -1,    -1,   284,
     285,   286,    63,    64,    65,    -1,   271,   272,   273,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   284,
     285,   286,    11,    -1,    13,    -1,    15,    16,    -1,    18,
      19,    -1,    21,    22,    -1,    11,    25,    13,    -1,    15,
      16,    -1,    18,    19,    -1,    21,    22,    39,    40,    25,
      -1,    -1,    -1,    42,    -1,    -1,    -1,    46,    47,    -1,
      52,    53,    54,    55,    56,    57,    42,    -1,    -1,    -1,
      46,    60,    64,    65,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    74,    -1,    -1,    -1,    -1,
      66,    67,    11,    -1,    13,    -1,    15,    16,    74,    18,
      19,    -1,    21,    22,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,
      27,    -1,    29,    42,    31,    32,    33,    46,    -1,    -1,
      -1,    38,    39,    40,    -1,    42,    -1,    44,    -1,    -1,
      -1,    60,    49,    50,    -1,    -1,    -1,    66,    -1,    -1,
      -1,    -1,    -1,    60,    -1,    74,    -1,    -1,    -1,    -1,
      -1,    68,    69,    70,    71,    72,    73,    74,    18,    -1,
      -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,
      -1,    31,    32,    33,    -1,    -1,    -1,    -1,    38,    39,
      40,    -1,    42,    -1,    44,    -1,    -1,    -1,    -1,    -1,
      50,    -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    18,    -1,    -1,    -1,    22,
      -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,    32,
      33,    -1,    -1,    -1,    -1,    38,    39,    40,    -1,    42,
      -1,    44,    45,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    31,    32,    33,    -1,    -1,
      -1,    -1,    38,    39,    40,    -1,    42,    43,    44,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    68,    69,    70,    71,    72,    73,    74,    18,
      -1,    -1,    -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,
      29,    -1,    31,    32,    33,    -1,    -1,    -1,    -1,    38,
      39,    40,    -1,    42,    -1,    44,    -1,    -1,    -1,    -1,
      -1,    50,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,
      69,    70,    71,    72,    73,    74,    18,    -1,    -1,    -1,
      22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,    31,
      32,    33,    -1,    -1,    -1,    -1,    38,    39,    40,    -1,
      42,    -1,    44,    -1,    -1,    -1,    -1,    -1,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    60,    20,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,
      72,    73,    74,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    23,    -1,    -1,
      -1,    -1,    63,    64,    65,    -1,    -1,    -1,    34,    35,
      36,    37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,
      56,    57,    23,    -1,    -1,    -1,    -1,    63,    64,    65,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    24,    -1,    -1,
      -1,    -1,    63,    64,    65,    -1,    -1,    34,    35,    36,
      37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    26,    -1,    -1,    -1,    -1,    63,    64,    65,    34,
      35,    36,    37,    -1,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    57,    -1,    -1,    28,    -1,    -1,    63,    64,
      65,    34,    35,    36,    37,    -1,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    57,    -1,    -1,    -1,    -1,    30,
      63,    64,    65,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    34,    35,    36,    37,    -1,
      39,    40,    41,    -1,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    34,    35,    36,
      37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    -1,    -1,    -1,    61,    -1,    63,    64,    65,    34,
      35,    36,    37,    -1,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    57,    -1,    59,    -1,    -1,    -1,    63,    64,
      65,    34,    35,    36,    37,    -1,    39,    40,    41,    -1,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    34,    35,    36,    37,    -1,
      39,    40,    41,    -1,    -1,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    53,    54,    55,    56,    57,    -1,
      -1,    -1,    -1,    -1,    63,    64,    65,    34,    35,    36,
      37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,    34,
      35,    36,    37,    -1,    39,    40,    41,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    52,    53,    54,
      55,    56,    57,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    34,    35,    36,    37,    -1,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    57,    -1,    -1,    -1,    -1,    -1,
      63,    64,    65,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      -1,    -1,    63,    64,    65,    34,    -1,    36,    -1,    -1,
      39,    40,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    53,    54,    55,    56,    57,    39,
      40,    41,    -1,    -1,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    52,    53,    54,    55,    56,    57,    -1,    -1,
      -1,    -1,    -1,    63,    64,    65
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    80,     4,     5,     6,     7,     8,    44,    81,
      82,    83,    84,    89,    93,    94,   128,     0,    46,    60,
      74,    95,    97,    98,    95,    95,    95,    95,    95,   143,
     144,   145,   146,    82,    18,    22,    29,    31,    32,    33,
      38,    39,    40,    42,    44,    50,    68,    69,    70,    71,
      72,    73,    90,    91,    92,    98,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,   122,
     123,   124,   125,   126,   127,    97,    60,    42,   101,    41,
     101,    48,    42,   116,    45,    51,    95,    99,   116,    99,
     116,   116,   116,    54,   116,    45,   116,   120,    98,    51,
      47,    42,   121,    34,    35,    36,    37,    39,    40,    41,
      52,    53,    54,    55,    56,    57,    61,    63,    64,    65,
      61,    95,    99,   100,    61,    46,    41,    61,    87,    88,
      95,   102,   103,   104,   105,   116,    81,   143,    48,    17,
      23,    17,   116,    43,    51,    59,    45,    51,    90,    43,
     116,   120,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
      43,    51,   102,    95,    96,    11,    13,    15,    16,    18,
      19,    21,    22,    25,    42,    46,    66,   123,   124,   129,
     131,   132,   133,   136,   137,   138,   139,   140,   141,   142,
     102,    54,    61,    52,    58,   102,   116,   116,   116,    43,
     120,   116,   116,    43,    99,    41,    47,    51,   129,   130,
     130,    99,    99,   129,   123,   124,   116,   116,   130,   130,
      62,    41,   102,   102,   102,   106,   116,    28,    24,    30,
     121,    43,    45,   116,    95,    12,   129,    14,    41,    17,
      23,    26,    47,    67,   116,   129,    10,    86,    51,    53,
     116,   116,   116,   116,   116,   129,    46,    46,     9,    85,
     102,    17,    20,    24,    27,    49,   116,   134,   135,   116,
      46,   129,   129,   129,    48,    48,    48,   135,    47,    47,
      92,   129,   129,   129,    47
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    79,    80,    81,    81,    81,    81,    82,    82,    83,
      83,    84,    84,    85,    85,    86,    86,    87,    87,    88,
      88,    89,    89,    90,    90,    90,    91,    91,    92,    92,
      93,    94,    95,    96,    96,    97,    97,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   102,   103,   104,
     105,   106,   106,   107,   107,   107,   107,   107,   107,   107,
     107,   108,   109,   109,   110,   111,   111,   112,   113,   114,
     115,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     118,   119,   119,   120,   120,   121,   121,   122,   123,   123,
     124,   125,   126,   127,   128,   128,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   130,   130,   131,   132,
     132,   133,   134,   134,   134,   135,   135,   136,   137,   138,
     139,   139,   140,   140,   141,   142,   142,   142,   142,   143,
     143,   144,   144,   145,   146
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     4,     1,     2,
       1,     8,     1,     4,     0,     4,     0,     3,     1,     1,
       0,     2,     4,     1,     3,     3,     3,     1,     1,     0,
       7,     6,     1,     3,     1,     3,     1,     1,     2,     3,
       1,     3,     1,     3,     0,     1,     1,     1,     1,     4,
       3,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     2,     2,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       5,     2,     3,     3,     1,     3,     2,     5,     1,     2,
       5,     6,     6,     6,     5,     7,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     4,
       6,     6,     3,     3,     3,     2,     1,     6,     6,     2,
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
  "\"skip\"", "\"let\"", "\"in\"", "\"forall\"", "\"iterate\"", "\"do\"",
  "\"call\"", "\"if\"", "\"then\"", "\"else\"", "\"case\"", "\"of\"",
  "\"default\"", "\"holds\"", "\"exists\"", "\"with\"", "\"undef\"",
  "\"false\"", "\"true\"", "\"and\"", "\"or\"", "\"xor\"", "\"implies\"",
  "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"",
  "\"*\"", "\"/\"", "\"%\"", "\"^\"", "\"'\"", "\"..\"", "\".\"", "\"->\"",
  "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"floating\"",
  "\"string\"", "\"identifier\"", "ABSOLUTE_PATH", "UPLUS", "UMINUS",
  "CALL_WITHOUT_ARGS", "$accept", "Specification", "Definition",
  "AttributedDefinition", "Definitions", "FunctionDefinition",
  "MaybeInitially", "MaybeDefined", "FunctionParameters",
  "MaybeFunctionParameters", "ProgramFunctionDefinition", "Initializer",
  "Initializers", "MaybeInitializers", "DerivedDefinition",
  "EnumerationDefinition", "Identifier", "Identifiers",
  "DotSeparatedIdentifiers", "IdentifierPath", "Variable", "Parameters",
  "MaybeParameters", "Type", "BasicType", "ComposedType", "FixedSizedType",
  "Types", "Atom", "Undefined", "Boolean", "String", "BitNumber",
  "IntegerNumber", "FloatingNumber", "RationalNumber", "RuleReference",
  "Term", "Expression", "Range", "List", "Terms", "Arguments",
  "TwoOrMoreArguments", "DirectCallExpression", "IndirectCallExpression",
  "ConditionalExpression", "UniversalQuantifierExpression",
  "ExistentialQuantifierExpression", "RuleDefinition", "Rule", "Rules",
  "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels",
  "LetRule", "ForallRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", "Attribute", "Attributes", "BasicAttribute",
  "ExpressionAttribute", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   335,   335,   347,   351,   355,   359,   367,   373,   381,
     387,   397,   413,   421,   425,   433,   437,   445,   451,   461,
     465,   473,   490,   508,   515,   524,   534,   540,   550,   554,
     562,   570,   578,   586,   592,   603,   609,   619,   623,   631,
     635,   644,   650,   660,   664,   672,   676,   680,   688,   696,
     704,   712,   718,   728,   732,   736,   740,   744,   748,   752,
     756,   764,   772,   777,   786,   802,   814,   830,   846,   862,
     878,   886,   890,   894,   898,   902,   906,   910,   914,   918,
     926,   930,   934,   938,   942,   946,   950,   954,   958,   962,
     966,   970,   974,   978,   982,   986,   990,   994,   998,  1002,
    1010,  1018,  1023,  1031,  1037,  1047,  1051,  1060,  1070,  1075,
    1083,  1091,  1099,  1107,  1115,  1120,  1129,  1133,  1137,  1141,
    1145,  1149,  1153,  1157,  1161,  1165,  1173,  1179,  1189,  1197,
    1201,  1209,  1217,  1221,  1225,  1233,  1239,  1249,  1257,  1265,
    1273,  1277,  1285,  1289,  1297,  1305,  1311,  1318,  1324,  1335,
    1339,  1347,  1353,  1363,  1371
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
#line 3451 "GrammarParser.cpp" // lalr1.cc:1167
#line 1377 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void Parser::error( const Location& location, const std::string& message )
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
