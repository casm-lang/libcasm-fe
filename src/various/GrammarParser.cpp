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
    #include "Exception.h"
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
      case 148: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 149: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 150: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 106: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 144: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 147: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 138: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 137: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 139: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 142: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 107: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 129: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 136: // ConditionalRule
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

      case 131: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // MaybeDefined
      case 111: // Atom
      case 120: // Term
      case 121: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 151: // ExpressionAttribute
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

      case 141: // ForallRule
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

      case 143: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 140: // LetRule
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

      case 133: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 132: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 134: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 145: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 135: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 105: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 89: // FunctionParameters
      case 90: // MaybeFunctionParameters
      case 110: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 112: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 130: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 92: // Initializer
      case 146: // UpdateRule
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
      case 148: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 149: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 150: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 106: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 144: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 147: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 138: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 137: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 139: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 142: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 107: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 129: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 136: // ConditionalRule
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

      case 131: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // MaybeDefined
      case 111: // Atom
      case 120: // Term
      case 121: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 151: // ExpressionAttribute
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

      case 141: // ForallRule
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

      case 143: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 140: // LetRule
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

      case 133: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 132: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 134: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 145: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 135: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 82: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 105: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 89: // FunctionParameters
      case 90: // MaybeFunctionParameters
      case 110: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 112: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 130: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 92: // Initializer
      case 146: // UpdateRule
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
      case 148: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 149: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 150: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 106: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 144: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 147: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 138: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 137: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 139: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 142: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 107: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 129: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 136: // ConditionalRule
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

      case 131: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 88: // MaybeDefined
      case 111: // Atom
      case 120: // Term
      case 121: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 151: // ExpressionAttribute
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

      case 141: // ForallRule
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

      case 143: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 140: // LetRule
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

      case 133: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 132: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 134: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 145: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 135: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 82: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 105: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 89: // FunctionParameters
      case 90: // MaybeFunctionParameters
      case 110: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 112: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 130: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 92: // Initializer
      case 146: // UpdateRule
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
#line 1291 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1299 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 362 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1307 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1323 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1331 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 402 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1369 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 428 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 436 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1421 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 452 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1429 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1439 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 1465 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1492 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1510 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1522 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 547 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 564 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1575 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 586 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1591 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 594 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Identifiers::Ptr > () );
  }
#line 1599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 606 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 1615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 614 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1635 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 630 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1645 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 636 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 1663 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::RELATIVE );
  }
#line 1671 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 658 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1679 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 1688 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 1698 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 1706 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 685 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1726 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 701 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1734 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 1742 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 709 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1750 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 717 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1758 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 721 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1766 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 725 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 1774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 729 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 737 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 1790 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 745 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1798 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 753 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< Type::Ptr > () );
  }
#line 1806 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 761 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1814 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 769 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1824 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 775 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1834 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 785 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 1842 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 789 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1850 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 793 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 797 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1874 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1882 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1890 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 813 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1898 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 821 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1906 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 829 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1915 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 834 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1924 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 843 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1940 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 859 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1956 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 871 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1972 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1988 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 903 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2004 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 935 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 943 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2036 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 947 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2044 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 951 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2052 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 955 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2060 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 959 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2068 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 963 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2076 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 967 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2084 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 971 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2092 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 975 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2100 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 983 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2108 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 987 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2116 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 991 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2124 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 995 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2132 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 999 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2140 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1003 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2148 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1007 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2156 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1011 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2164 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1015 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2172 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1019 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2180 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1023 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2188 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1027 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2196 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1031 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2204 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1035 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2212 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1039 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2220 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1043 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2228 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1047 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2236 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1051 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2244 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1055 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2252 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1059 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2260 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1063 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1067 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1075 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2284 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1083 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2301 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1092 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2309 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1100 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2329 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1116 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2337 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1120 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2345 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1124 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2354 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[1].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[3].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1148 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1156 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1164 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1172 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1180 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1188 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1193 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2431 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1202 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2439 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1206 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2447 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1210 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2455 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1214 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1218 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2471 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1222 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 2479 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1226 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1230 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2495 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1234 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2503 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2511 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1242 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2519 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1250 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1256 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1266 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 2547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1274 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1278 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2563 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1286 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1290 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 2579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1298 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1302 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1306 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2603 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1314 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2613 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1320 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1338 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1354 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1362 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2663 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2671 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2680 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1375 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2689 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1384 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2705 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1392 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2714 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2743 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2754 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1429 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1435 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2775 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2783 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2791 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2801 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1464 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2811 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1474 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2819 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1482 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2827 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2831 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -176;

  const signed char Parser::yytable_ninf_ = -60;

  const short int
  Parser::yypact_[] =
  {
      -1,   132,    13,  -176,   -11,   -16,   -16,   -16,   -16,   -16,
    -176,  -176,    70,  -176,  -176,  -176,  -176,  -176,  -176,  -176,
     904,   -16,  -176,  -176,   -47,  -176,   -20,     9,   -20,   -21,
     964,  -176,    77,  -176,  -176,  -176,   -10,   964,   -10,  -176,
    -176,  -176,   964,   964,   964,   371,   432,    -8,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,   -13,    16,     1,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  1336,  -176,  -176,
    -176,    10,  -176,  -176,  -176,  -176,  -176,  -176,   -16,     7,
      18,     8,    -5,    -8,   371,  1567,   113,   -16,   -16,    32,
    -176,    90,  1102,    94,  -176,  -176,  -176,    62,   964,  1303,
      96,  -176,  1369,    89,  -176,   904,  -176,   493,  -176,   964,
     964,   964,   964,   964,   964,   964,   964,   964,   964,   964,
     964,   964,   964,   964,   964,   964,   964,   964,  -176,   101,
    -176,    -3,    -8,   -16,   832,    -8,    91,    88,    63,  -176,
    -176,  -176,  -176,  -176,  1402,  -176,  -176,    97,    -8,   964,
     964,   964,  -176,  1435,  -176,   964,  -176,   964,  -176,   964,
    -176,   122,  -176,  1567,     2,  1704,  1633,  1685,  1600,    98,
      98,  1723,   107,   107,    93,    93,    93,  -176,  1567,  1600,
    1723,   107,   107,  1567,  -176,  -176,   -10,   115,  -176,   -37,
     530,   570,  -176,   -10,   -10,   -10,   832,   -14,   964,   964,
     114,   607,   644,   104,  -176,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,   128,    -8,    -8,
      -8,   964,   -16,  -176,  1237,  1171,  1270,     1,     4,  1468,
    1567,  -176,  -176,  -176,   964,  -176,   -16,   159,  -176,   681,
     158,   718,   133,   161,   164,  -176,  -176,  -176,  1137,  1204,
     134,   755,   116,   795,   964,   832,  -176,   166,   124,   -12,
      15,  1666,  -176,   964,   964,   964,  -176,  -176,  -176,  1567,
    -176,  -176,  -176,  -176,  -176,  -176,   964,   964,   964,   832,
     140,  -176,  -176,  -176,  -176,  1567,  -176,   141,   182,    -8,
      -8,  -176,  -176,  1567,  -176,   991,  1029,  1067,   167,   309,
     964,   146,  -176,   143,  -176,   832,   832,   832,   832,   150,
     151,   152,  1501,   844,   155,  1534,   904,  -176,  -176,  -176,
    -176,  -176,  -176,   832,   832,   832,  -176,  -176,  -176,   156,
    -176,  -176,  -176,  -176
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     7,     0,     0,     0,     0,     0,     0,
       9,    11,     0,     3,    13,     4,     6,     5,     1,    34,
      30,     0,    33,    38,    39,    22,    49,     0,    49,     0,
     171,   170,     0,   167,   168,    10,     0,     0,     0,    68,
      70,    69,     0,     0,     0,     0,     0,     0,    72,    73,
      74,    76,    75,    71,    28,    29,     0,   119,    86,    66,
      67,    65,    61,    62,    63,    64,    60,    24,    83,    85,
      84,     0,    78,    79,    80,    81,    82,    40,     0,     0,
       0,     0,     0,    21,     0,   172,     0,     0,     0,    42,
      44,     0,     0,     0,   108,    89,    90,     0,     0,     0,
       0,   110,   114,     0,    77,     0,    23,     0,   120,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    37,     0,
      46,     0,     0,     0,     0,     0,    20,     0,    54,    19,
      50,    51,    52,    53,     0,     8,   169,     0,     0,     0,
       0,     0,    88,     0,    87,     0,   112,     0,   111,     0,
      27,     0,   117,   114,     0,   105,   103,   104,   107,    91,
      92,    98,    99,   100,    93,    94,    95,    96,    25,   106,
      97,   101,   102,    26,    48,    47,     0,     0,    36,     0,
       0,     0,   140,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   164,   166,   125,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,     0,     0,     0,
      21,     0,     0,    41,     0,     0,     0,     0,     0,     0,
     113,   116,   115,    45,     0,    32,     0,     0,   139,     0,
       0,     0,     0,     0,     0,   153,   163,   165,     0,     0,
       0,     0,     0,     0,     0,     0,    18,    17,     0,    19,
       0,    57,    43,     0,     0,     0,   121,   118,   109,    31,
      35,   161,   159,   138,   157,   155,     0,     0,     0,     0,
       0,   156,   154,   160,   158,   162,   126,     0,    15,     0,
       0,    55,   123,   122,   124,     0,     0,     0,   141,     0,
       0,     0,    12,     0,    58,     0,     0,     0,     0,     0,
       0,     0,     0,   149,     0,     0,    30,    56,   150,   151,
     152,   142,   144,     0,     0,     0,   148,   143,    16,     0,
     145,   146,   147,    14
  };

  const short int
  Parser::yypgoto_[] =
  {
    -176,  -176,   119,   187,  -176,  -176,  -176,  -176,  -176,     3,
    -176,   102,  -176,  -108,  -176,  -176,    25,  -176,   185,    -4,
      -9,   -34,  -176,   189,  -110,  -176,  -176,  -176,  -176,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,  -176,   -25,
    -176,  -176,  -176,   -97,    -6,  -176,    -7,    68,  -176,  -176,
    -176,  -176,   -29,  -175,  -176,  -176,  -176,  -176,   -88,  -176,
    -176,  -176,  -176,  -176,  -176,  -176,  -176,   144,   139,  -176,
    -176
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,    10,    11,    12,    13,   302,   288,   136,   137,
      14,    54,    55,    56,    15,    16,    23,   189,    24,    57,
      90,    91,   131,    80,   139,   140,   141,   142,   143,   260,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,   103,   108,    71,    72,    73,    74,    75,
      76,    17,   238,   239,   206,   207,   208,   313,   314,   209,
     210,   211,   212,   213,   214,   215,   216,    31,    32,    33,
      34
  };

  const short int
  Parser::yytable_[] =
  {
      25,    19,     1,    19,    93,    85,    19,    19,   129,    19,
     164,   235,    92,    18,    78,   236,   241,    94,    95,    96,
      99,   102,   187,    79,    19,   217,   251,   253,    83,   200,
      26,    27,    28,    29,    30,    88,    20,   134,   223,   105,
     -59,   185,   -59,   104,   107,   130,   232,    21,   267,   186,
      21,    81,    88,    21,   159,   133,   159,   135,   228,   144,
      22,    89,    22,    89,   106,    22,    22,   290,    22,   291,
      -2,     3,   127,   153,     4,     5,     6,     7,     8,   138,
     132,   148,   163,    22,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
     181,   182,   183,   128,    89,   205,   152,   149,   256,   257,
     259,   151,    30,    30,     3,     9,   220,     4,     5,     6,
       7,     8,   221,    86,   224,   225,   226,   203,   138,    87,
     163,   138,   229,     3,   230,   158,     4,     5,     6,     7,
       8,   159,   156,   222,   138,   184,   218,   113,   114,    87,
     219,   121,   233,   118,   119,   120,   121,   234,   188,   242,
     243,   244,   118,   119,   120,   121,   231,   245,   254,    98,
     255,   271,   274,   248,   249,   276,   287,     9,   277,   303,
     304,   278,   281,   203,   203,   283,   289,   299,   300,   203,
     246,   301,   308,   316,   203,   203,   261,   317,   322,    35,
     323,   324,   204,   327,   333,   145,    77,   160,   329,   269,
     273,    89,   273,   262,   138,   138,   138,    82,    89,    89,
      89,   266,   273,   258,   273,   326,   286,   147,     0,   285,
       0,   146,   203,     0,   203,     0,     0,     0,   292,   293,
     294,     0,     0,     0,   203,     0,   203,    89,   203,     0,
     298,   295,   296,   297,     0,     0,     0,     0,   204,   204,
       0,   270,     0,     0,   204,   247,     0,     0,     0,   204,
     204,     0,   203,     0,   312,   315,   318,   319,   320,   321,
       0,     0,     0,     0,     0,   138,   138,     0,   312,     0,
       0,     0,     0,     0,   330,   331,   332,     0,   203,   203,
     203,   203,     0,     0,     0,     0,     0,   204,     0,   204,
     309,     0,     0,     0,     0,     0,   203,   203,   203,   204,
       0,   204,     0,   204,     0,     0,    19,    36,     0,     0,
       0,     0,    37,     0,     0,     0,     0,   310,     0,    38,
       0,    39,    40,    41,     0,     0,     0,   204,    42,    43,
      44,     0,    84,     0,    46,     0,     0,     0,     0,   311,
      47,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      21,     0,    97,   204,   204,   204,   204,     0,     0,    48,
      49,    50,    51,    52,    53,    22,     0,     0,    19,    36,
       0,   204,   204,   204,    37,     0,     0,     0,     0,     0,
       0,    38,     0,    39,    40,    41,     0,     0,     0,     0,
      42,    43,    44,     0,    84,     0,    46,     0,     0,     0,
       0,     0,    47,     0,     0,     0,    98,     0,     0,     0,
       0,     0,    21,   100,     0,     0,     0,     0,     0,     0,
       0,    48,    49,    50,    51,    52,    53,    22,     0,    19,
      36,     0,     0,     0,     0,    37,     0,     0,     0,     0,
       0,     0,    38,     0,    39,    40,    41,     0,     0,     0,
       0,    42,    43,    44,     0,    84,     0,    46,   101,     0,
       0,     0,     0,    47,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,   161,     0,     0,     0,     0,     0,
       0,     0,    48,    49,    50,    51,    52,    53,    22,     0,
      19,    36,     0,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,    38,     0,    39,    40,    41,     0,     0,
       0,   237,    42,    43,    44,     0,    84,   162,    46,     0,
       0,   190,     0,   191,    47,   192,   193,    19,   194,   195,
     196,     0,   197,   198,    21,     0,   199,     0,     0,     0,
       0,     0,     0,    48,    49,    50,    51,    52,    53,    22,
       0,   240,     0,   200,     0,     0,     0,   201,     0,     0,
       0,   190,     0,   191,     0,   192,   193,    19,   194,   195,
     196,    21,   197,   198,     0,     0,   199,     0,   202,     0,
       0,     0,     0,     0,     0,     0,    22,     0,   250,     0,
       0,     0,     0,   200,     0,     0,     0,   201,   190,     0,
     191,     0,   192,   193,    19,   194,   195,   196,     0,   197,
     198,    21,     0,   199,     0,     0,     0,     0,   202,     0,
       0,     0,     0,     0,     0,   252,    22,     0,     0,     0,
     200,     0,     0,     0,   201,   190,     0,   191,     0,   192,
     193,    19,   194,   195,   196,     0,   197,   198,    21,     0,
     199,     0,     0,     0,     0,   202,     0,     0,     0,     0,
       0,     0,     0,    22,     0,     0,     0,   200,     0,     0,
       0,   201,   190,   272,   191,     0,   192,   193,    19,   194,
     195,   196,     0,   197,   198,    21,     0,   199,     0,     0,
       0,     0,   202,     0,     0,     0,     0,     0,     0,     0,
      22,     0,     0,     0,   200,     0,     0,     0,   201,   190,
       0,   191,   275,   192,   193,    19,   194,   195,   196,     0,
     197,   198,    21,     0,   199,     0,     0,     0,     0,   202,
       0,     0,     0,     0,     0,     0,     0,    22,     0,     0,
       0,   200,     0,     0,     0,   201,   190,     0,   191,     0,
     192,   193,    19,   194,   195,   196,     0,   197,   198,    21,
       0,   199,     0,     0,     0,     0,   202,     0,     0,     0,
       0,     0,     0,     0,    22,     0,     0,     0,   200,     0,
       0,     0,   201,   282,     0,     0,   190,     0,   191,     0,
     192,   193,    19,   194,   195,   196,    21,   197,   198,     0,
       0,   199,     0,   202,     0,     0,     0,     0,     0,     0,
       0,    22,     0,     0,     0,     0,     0,     0,   200,     0,
       0,     0,   201,   190,     0,   191,     0,   192,   193,    19,
     194,   195,   196,     0,   197,   198,    21,     0,   199,     0,
       0,    19,    36,   202,   284,     0,     0,    37,     0,     0,
       0,    22,   310,     0,    38,   200,    39,    40,    41,   201,
       0,     0,     0,    42,    43,    44,     0,    84,     0,    46,
       0,     0,     0,    21,   311,    47,     0,     0,     0,     0,
     202,     0,     0,     0,     0,    21,     0,     0,    22,     0,
       0,     0,     0,     0,    48,    49,    50,    51,    52,    53,
      22,    19,    36,     0,     0,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    38,     0,    39,    40,    41,     0,
       0,     0,     0,    42,    43,    44,     0,    45,     0,    46,
       0,     0,     0,     0,     0,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,     0,     0,     0,     0,
       0,     0,     0,     0,    48,    49,    50,    51,    52,    53,
      22,    19,    36,     0,     0,     0,     0,    37,     0,     0,
       0,     0,     0,     0,    38,     0,    39,    40,    41,     0,
       0,     0,     0,    42,    43,    44,     0,    84,   305,    46,
       0,     0,     0,     0,     0,    47,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    21,   109,   110,   111,   112,
       0,   113,   114,   115,    48,    49,    50,    51,    52,    53,
      22,     0,     0,     0,   116,   117,   118,   119,   120,   121,
     306,     0,     0,     0,   123,     0,   124,   125,   126,     0,
       0,     0,     0,     0,   109,   110,   111,   112,     0,   113,
     114,   115,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   116,   117,   118,   119,   120,   121,   307,     0,
       0,     0,   123,     0,   124,   125,   126,     0,     0,     0,
       0,     0,   109,   110,   111,   112,     0,   113,   114,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     116,   117,   118,   119,   120,   121,   150,     0,     0,     0,
     123,     0,   124,   125,   126,     0,     0,   109,   110,   111,
     112,     0,   113,   114,   115,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   116,   117,   118,   119,   120,
     121,   279,     0,     0,     0,   123,     0,   124,   125,   126,
       0,     0,   109,   110,   111,   112,     0,   113,   114,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     116,   117,   118,   119,   120,   121,   264,     0,     0,     0,
     123,     0,   124,   125,   126,     0,   109,   110,   111,   112,
       0,   113,   114,   115,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   116,   117,   118,   119,   120,   121,
       0,   280,     0,     0,   123,     0,   124,   125,   126,   109,
     110,   111,   112,     0,   113,   114,   115,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   116,   117,   118,
     119,   120,   121,     0,     0,     0,   263,   123,     0,   124,
     125,   126,   109,   110,   111,   112,     0,   113,   114,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     116,   117,   118,   119,   120,   121,     0,     0,     0,     0,
     123,   265,   124,   125,   126,   109,   110,   111,   112,     0,
     113,   114,   115,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,   123,     0,   124,   125,   126,   109,   110,
     111,   112,     0,   113,   114,   115,     0,   154,     0,     0,
       0,     0,     0,     0,     0,   155,   116,   117,   118,   119,
     120,   121,     0,     0,     0,     0,   123,     0,   124,   125,
     126,   109,   110,   111,   112,     0,   113,   114,   115,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   116,
     117,   118,   119,   120,   121,     0,     0,     0,   122,   123,
       0,   124,   125,   126,   109,   110,   111,   112,     0,   113,
     114,   115,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   116,   117,   118,   119,   120,   121,     0,   157,
       0,     0,   123,     0,   124,   125,   126,   109,   110,   111,
     112,     0,   113,   114,   115,     0,   154,     0,     0,     0,
       0,     0,     0,     0,     0,   116,   117,   118,   119,   120,
     121,     0,     0,     0,     0,   123,     0,   124,   125,   126,
     109,   110,   111,   112,     0,   113,   114,   115,     0,   227,
       0,     0,     0,     0,     0,     0,     0,     0,   116,   117,
     118,   119,   120,   121,     0,     0,     0,     0,   123,     0,
     124,   125,   126,   109,   110,   111,   112,     0,   113,   114,
     115,     0,     0,     0,   268,     0,     0,     0,     0,     0,
       0,   116,   117,   118,   119,   120,   121,     0,     0,     0,
       0,   123,     0,   124,   125,   126,   109,   110,   111,   112,
       0,   113,   114,   115,     0,     0,     0,     0,     0,     0,
     325,     0,     0,     0,   116,   117,   118,   119,   120,   121,
       0,     0,     0,     0,   123,     0,   124,   125,   126,   109,
     110,   111,   112,     0,   113,   114,   115,     0,     0,     0,
       0,     0,   328,     0,     0,     0,     0,   116,   117,   118,
     119,   120,   121,     0,     0,     0,     0,   123,     0,   124,
     125,   126,   109,   110,   111,   112,     0,   113,   114,   115,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     116,   117,   118,   119,   120,   121,     0,     0,     0,     0,
     123,     0,   124,   125,   126,   109,   110,   111,     0,     0,
     113,   114,   115,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   116,   117,   118,   119,   120,   121,     0,
       0,     0,     0,     0,     0,   124,   125,   126,   109,     0,
     111,     0,     0,   113,   114,   115,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   116,   117,   118,   119,
     120,   121,     0,     0,     0,     0,     0,     0,   124,   125,
     126,   109,   110,   111,   112,     0,   113,   114,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   116,
     109,     0,   119,   120,   121,   113,   114,   115,     0,   123,
       0,   124,   125,   126,     0,     0,     0,     0,   116,   117,
     118,   119,   120,   121,   113,   114,   115,     0,     0,     0,
     124,   125,   126,     0,     0,     0,     0,   116,   117,   118,
     119,   120,   121,   113,   114,     0,     0,     0,     0,   124,
     125,   126,     0,     0,     0,     0,   116,   117,   118,   119,
     120,   121,     0,     0,     0,     0,     0,     0,     0,   125,
     126
  };

  const short int
  Parser::yycheck_[] =
  {
       4,    17,     3,    17,    38,    30,    17,    17,     1,    17,
     107,    48,    37,     0,    61,    52,   191,    42,    43,    44,
      45,    46,   132,    43,    17,   135,   201,   202,    49,    43,
       5,     6,     7,     8,     9,    45,    47,    42,   148,    52,
      52,    44,    54,    47,    43,    79,    44,    61,    44,    52,
      61,    42,    45,    61,    52,    47,    52,    62,   155,    84,
      76,    36,    76,    38,    48,    76,    76,    52,    76,    54,
       0,     1,    62,    98,     4,     5,     6,     7,     8,    83,
      62,    49,   107,    76,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,    78,    79,   134,    44,    17,   218,   219,
     220,    17,    87,    88,     1,    45,    53,     4,     5,     6,
       7,     8,    59,    46,   149,   150,   151,   134,   132,    52,
     155,   135,   157,     1,   159,    46,     4,     5,     6,     7,
       8,    52,    46,    46,   148,    44,    55,    40,    41,    52,
      62,    58,   186,    55,    56,    57,    58,    42,   133,   193,
     194,   195,    55,    56,    57,    58,    44,   196,    64,    55,
      42,    12,    14,   198,   199,    42,    10,    45,    17,   289,
     290,    17,    48,   190,   191,    69,    62,    47,    47,   196,
     197,     9,    25,    47,   201,   202,   221,    54,    48,    12,
      49,    49,   134,    48,    48,    86,    21,   105,   316,   234,
     239,   186,   241,   222,   218,   219,   220,    28,   193,   194,
     195,   227,   251,   220,   253,   313,   255,    88,    -1,   254,
      -1,    87,   239,    -1,   241,    -1,    -1,    -1,   263,   264,
     265,    -1,    -1,    -1,   251,    -1,   253,   222,   255,    -1,
     279,   276,   277,   278,    -1,    -1,    -1,    -1,   190,   191,
      -1,   236,    -1,    -1,   196,   197,    -1,    -1,    -1,   201,
     202,    -1,   279,    -1,   299,   300,   305,   306,   307,   308,
      -1,    -1,    -1,    -1,    -1,   289,   290,    -1,   313,    -1,
      -1,    -1,    -1,    -1,   323,   324,   325,    -1,   305,   306,
     307,   308,    -1,    -1,    -1,    -1,    -1,   239,    -1,   241,
       1,    -1,    -1,    -1,    -1,    -1,   323,   324,   325,   251,
      -1,   253,    -1,   255,    -1,    -1,    17,    18,    -1,    -1,
      -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    -1,    30,
      -1,    32,    33,    34,    -1,    -1,    -1,   279,    39,    40,
      41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      61,    -1,     1,   305,   306,   307,   308,    -1,    -1,    70,
      71,    72,    73,    74,    75,    76,    -1,    -1,    17,    18,
      -1,   323,   324,   325,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,
      39,    40,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    -1,    61,     1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    70,    71,    72,    73,    74,    75,    76,    -1,    17,
      18,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    30,    -1,    32,    33,    34,    -1,    -1,    -1,
      -1,    39,    40,    41,    -1,    43,    -1,    45,    46,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    61,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    70,    71,    72,    73,    74,    75,    76,    -1,
      17,    18,    -1,    -1,    -1,    -1,    23,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    -1,    32,    33,    34,    -1,    -1,
      -1,     1,    39,    40,    41,    -1,    43,    44,    45,    -1,
      -1,    11,    -1,    13,    51,    15,    16,    17,    18,    19,
      20,    -1,    22,    23,    61,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    70,    71,    72,    73,    74,    75,    76,
      -1,     1,    -1,    43,    -1,    -1,    -1,    47,    -1,    -1,
      -1,    11,    -1,    13,    -1,    15,    16,    17,    18,    19,
      20,    61,    22,    23,    -1,    -1,    26,    -1,    68,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,     1,    -1,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    47,    11,    -1,
      13,    -1,    15,    16,    17,    18,    19,    20,    -1,    22,
      23,    61,    -1,    26,    -1,    -1,    -1,    -1,    68,    -1,
      -1,    -1,    -1,    -1,    -1,     1,    76,    -1,    -1,    -1,
      43,    -1,    -1,    -1,    47,    11,    -1,    13,    -1,    15,
      16,    17,    18,    19,    20,    -1,    22,    23,    61,    -1,
      26,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    76,    -1,    -1,    -1,    43,    -1,    -1,
      -1,    47,    11,    12,    13,    -1,    15,    16,    17,    18,
      19,    20,    -1,    22,    23,    61,    -1,    26,    -1,    -1,
      -1,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      76,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,    11,
      -1,    13,    14,    15,    16,    17,    18,    19,    20,    -1,
      22,    23,    61,    -1,    26,    -1,    -1,    -1,    -1,    68,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,    -1,    -1,
      -1,    43,    -1,    -1,    -1,    47,    11,    -1,    13,    -1,
      15,    16,    17,    18,    19,    20,    -1,    22,    23,    61,
      -1,    26,    -1,    -1,    -1,    -1,    68,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    76,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    47,    48,    -1,    -1,    11,    -1,    13,    -1,
      15,    16,    17,    18,    19,    20,    61,    22,    23,    -1,
      -1,    26,    -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    76,    -1,    -1,    -1,    -1,    -1,    -1,    43,    -1,
      -1,    -1,    47,    11,    -1,    13,    -1,    15,    16,    17,
      18,    19,    20,    -1,    22,    23,    61,    -1,    26,    -1,
      -1,    17,    18,    68,    69,    -1,    -1,    23,    -1,    -1,
      -1,    76,    28,    -1,    30,    43,    32,    33,    34,    47,
      -1,    -1,    -1,    39,    40,    41,    -1,    43,    -1,    45,
      -1,    -1,    -1,    61,    50,    51,    -1,    -1,    -1,    -1,
      68,    -1,    -1,    -1,    -1,    61,    -1,    -1,    76,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    17,    18,    -1,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,    40,    41,    -1,    43,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    17,    18,    -1,    -1,    -1,    -1,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,    40,    41,    -1,    43,    17,    45,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    61,    35,    36,    37,    38,
      -1,    40,    41,    42,    70,    71,    72,    73,    74,    75,
      76,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      21,    -1,    -1,    -1,    63,    -1,    65,    66,    67,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    21,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    24,    -1,    -1,    -1,
      63,    -1,    65,    66,    67,    -1,    -1,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    24,    -1,    -1,    -1,    63,    -1,    65,    66,    67,
      -1,    -1,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    25,    -1,    -1,    -1,
      63,    -1,    65,    66,    67,    -1,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    27,    -1,    -1,    63,    -1,    65,    66,    67,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    29,    63,    -1,    65,
      66,    67,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      63,    31,    65,    66,    67,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    63,    -1,    65,    66,    67,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,    66,
      67,    35,    36,    37,    38,    -1,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    62,    63,
      -1,    65,    66,    67,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    60,
      -1,    -1,    63,    -1,    65,    66,    67,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    -1,    63,    -1,    65,    66,    67,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,
      65,    66,    67,    35,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      -1,    63,    -1,    65,    66,    67,    35,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      49,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      -1,    -1,    -1,    -1,    63,    -1,    65,    66,    67,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    -1,    63,    -1,    65,
      66,    67,    35,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      63,    -1,    65,    66,    67,    35,    36,    37,    -1,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    -1,    -1,    -1,    65,    66,    67,    35,    -1,
      37,    -1,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    65,    66,
      67,    35,    36,    37,    38,    -1,    40,    41,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      35,    -1,    56,    57,    58,    40,    41,    42,    -1,    63,
      -1,    65,    66,    67,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    40,    41,    42,    -1,    -1,    -1,
      65,    66,    67,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    40,    41,    -1,    -1,    -1,    -1,    65,
      66,    67,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    66,
      67
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    82,     1,     4,     5,     6,     7,     8,    45,
      83,    84,    85,    86,    91,    95,    96,   132,     0,    17,
      47,    61,    76,    97,    99,   100,    97,    97,    97,    97,
      97,   148,   149,   150,   151,    84,    18,    23,    30,    32,
      33,    34,    39,    40,    41,    43,    45,    51,    70,    71,
      72,    73,    74,    75,    92,    93,    94,   100,   111,   112,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   126,   127,   128,   129,   130,   131,    99,    61,    43,
     104,    42,   104,    49,    43,   120,    46,    52,    45,    97,
     101,   102,   120,   102,   120,   120,   120,     1,    55,   120,
       1,    46,   120,   124,   100,    52,    48,    43,   125,    35,
      36,    37,    38,    40,    41,    42,    53,    54,    55,    56,
      57,    58,    62,    63,    65,    66,    67,    62,    97,     1,
     102,   103,    62,    47,    42,    62,    89,    90,   100,   105,
     106,   107,   108,   109,   120,    83,   148,   149,    49,    17,
      24,    17,    44,   120,    44,    52,    46,    60,    46,    52,
      92,     1,    44,   120,   124,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,    44,    44,    52,   105,    97,    98,
      11,    13,    15,    16,    18,    19,    20,    22,    23,    26,
      43,    47,    68,   127,   128,   133,   135,   136,   137,   140,
     141,   142,   143,   144,   145,   146,   147,   105,    55,    62,
      53,    59,    46,   105,   120,   120,   120,    44,   124,   120,
     120,    44,    44,   102,    42,    48,    52,     1,   133,   134,
       1,   134,   102,   102,   102,   133,   127,   128,   120,   120,
       1,   134,     1,   134,    64,    42,   105,   105,    90,   105,
     110,   120,   101,    29,    25,    31,   125,    44,    46,   120,
      97,    12,    12,   133,    14,    14,    42,    17,    17,    24,
      27,    48,    48,    69,    69,   120,   133,    10,    88,    62,
      52,    54,   120,   120,   120,   120,   120,   120,   133,    47,
      47,     9,    87,   105,   105,    17,    21,    21,    25,     1,
      28,    50,   120,   138,   139,   120,    47,    54,   133,   133,
     133,   133,    48,    49,    49,    49,   139,    48,    48,    94,
     133,   133,   133,    48
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    81,    82,    83,    83,    83,    83,    83,    84,    84,
      85,    85,    86,    86,    87,    87,    88,    88,    89,    89,
      90,    90,    91,    91,    92,    92,    92,    93,    93,    94,
      94,    95,    96,    97,    97,    98,    98,    99,    99,   100,
     100,   101,   101,   102,   102,   103,   103,   104,   104,   104,
     105,   105,   105,   105,   106,   107,   108,   109,   110,   110,
     111,   111,   111,   111,   111,   111,   111,   111,   112,   113,
     113,   114,   115,   115,   116,   117,   118,   119,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   122,
     123,   123,   123,   124,   124,   125,   125,   125,   126,   127,
     127,   128,   129,   130,   131,   132,   132,   133,   133,   133,
     133,   133,   133,   133,   133,   133,   133,   133,   134,   134,
     135,   136,   136,   137,   137,   138,   138,   138,   139,   139,
     140,   141,   142,   143,   144,   144,   144,   144,   145,   145,
     145,   145,   146,   147,   147,   147,   147,   148,   148,   149,
     149,   150,   151
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     1,     4,     1,
       2,     1,     8,     1,     4,     0,     4,     0,     3,     1,
       1,     0,     2,     4,     1,     3,     3,     3,     1,     1,
       0,     7,     6,     1,     1,     3,     1,     3,     1,     1,
       2,     3,     1,     4,     1,     3,     1,     3,     3,     0,
       1,     1,     1,     1,     1,     4,     6,     3,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     3,     2,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     5,
       2,     3,     3,     3,     1,     3,     3,     2,     5,     1,
       2,     5,     6,     6,     6,     5,     7,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     4,     6,     6,     6,     3,     3,     3,     2,     1,
       6,     6,     6,     2,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     2,     1,     1,     1,     3,
       1,     1,     2
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
  "DotSeparatedIdentifiers", "IdentifierPath", "Variable",
  "AttributedVariable", "Parameters", "MaybeParameters", "Type",
  "BasicType", "ComposedType", "RelationType", "FixedSizedType", "Types",
  "Atom", "Undefined", "Boolean", "String", "BitNumber", "IntegerNumber",
  "FloatingNumber", "RationalNumber", "Reference", "Term", "Expression",
  "Range", "List", "Terms", "Arguments", "TwoOrMoreArguments",
  "DirectCallExpression", "IndirectCallExpression",
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
     577,   585,   593,   601,   605,   613,   619,   629,   635,   645,
     649,   657,   661,   670,   676,   684,   690,   700,   704,   708,
     716,   720,   724,   728,   736,   744,   752,   760,   768,   774,
     784,   788,   792,   796,   800,   804,   808,   812,   820,   828,
     833,   842,   858,   870,   886,   902,   918,   934,   942,   946,
     950,   954,   958,   962,   966,   970,   974,   982,   986,   990,
     994,   998,  1002,  1006,  1010,  1014,  1018,  1022,  1026,  1030,
    1034,  1038,  1042,  1046,  1050,  1054,  1058,  1062,  1066,  1074,
    1082,  1087,  1091,  1099,  1105,  1115,  1119,  1123,  1132,  1142,
    1147,  1155,  1163,  1171,  1179,  1187,  1192,  1201,  1205,  1209,
    1213,  1217,  1221,  1225,  1229,  1233,  1237,  1241,  1249,  1255,
    1265,  1273,  1277,  1285,  1289,  1297,  1301,  1305,  1313,  1319,
    1329,  1337,  1345,  1353,  1361,  1365,  1369,  1374,  1383,  1387,
    1391,  1396,  1405,  1415,  1421,  1428,  1434,  1445,  1449,  1457,
    1463,  1473,  1481
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
#line 3747 "GrammarParser.cpp" // lalr1.cc:1167
#line 1487 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
