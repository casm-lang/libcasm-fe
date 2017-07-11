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
      case 149: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 150: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 151: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 106: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 145: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 148: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 139: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 138: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 140: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 130: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 143: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 107: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 129: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 137: // ConditionalRule
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

      case 132: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // MaybeDefined
      case 111: // Atom
      case 120: // Term
      case 121: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 152: // ExpressionAttribute
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

      case 142: // ForallRule
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

      case 144: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 141: // LetRule
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

      case 134: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 133: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 135: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 146: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 136: // SkipRule
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

      case 131: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 92: // Initializer
      case 147: // UpdateRule
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
      case 149: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 150: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 151: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 106: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 145: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 148: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 139: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 138: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 140: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 130: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 143: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 107: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 129: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 137: // ConditionalRule
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

      case 132: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // MaybeDefined
      case 111: // Atom
      case 120: // Term
      case 121: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 152: // ExpressionAttribute
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

      case 142: // ForallRule
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

      case 144: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 141: // LetRule
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

      case 134: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 133: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 135: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 146: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 136: // SkipRule
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

      case 131: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 92: // Initializer
      case 147: // UpdateRule
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
      case 149: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 150: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 151: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 106: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 145: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 148: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 139: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 138: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 140: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 130: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 143: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 107: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 129: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 137: // ConditionalRule
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

      case 132: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 88: // MaybeDefined
      case 111: // Atom
      case 120: // Term
      case 121: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 152: // ExpressionAttribute
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

      case 142: // ForallRule
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

      case 144: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 141: // LetRule
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

      case 134: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 133: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 135: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 146: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 136: // SkipRule
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

      case 131: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 92: // Initializer
      case 147: // UpdateRule
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
#line 349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& fileName = filePath.substr( filePath.find_last_of( "/\\" ) + 1 );
      const std::string& name = fileName.substr( 0, fileName.rfind( "." ) );

      const auto specificationName = make< Identifier >( yylhs.location, name );
      result = Ast::make< Specification >( yylhs.location, specificationName, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 361 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 365 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 369 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 377 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1343 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 385 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1353 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1361 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1371 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 405 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 415 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 439 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1417 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 451 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 463 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 469 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1461 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 483 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 1477 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 491 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 514 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1522 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1534 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 540 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1548 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 550 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1559 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 567 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1603 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 597 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Identifiers::Ptr > () );
  }
#line 1611 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 1627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1637 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 623 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 633 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1657 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 639 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 649 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 1675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 653 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::RELATIVE );
  }
#line 1683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 661 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 665 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 1700 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 674 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 1710 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 680 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 1718 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 688 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 694 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1738 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1746 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 708 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 1754 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1762 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1770 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 724 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1778 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 1786 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 1802 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1810 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< Type::Ptr > () );
  }
#line 1818 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1826 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1836 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1846 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 1854 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 792 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1862 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 796 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1870 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 800 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1878 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 804 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 808 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1902 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1910 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 824 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1918 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1927 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 837 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1936 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 846 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1952 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 862 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1968 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 874 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2000 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2016 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 922 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2032 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2040 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 946 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2048 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2056 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2064 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2072 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2080 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2088 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2096 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2104 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2112 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2120 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2128 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2136 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2144 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2184 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2192 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2200 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1030 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2208 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1034 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2216 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1038 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2224 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1042 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2232 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1046 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2240 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1050 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2248 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1054 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2256 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1058 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2264 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1062 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2272 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2280 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1070 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2288 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2313 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2321 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1099 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2329 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1107 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2339 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1113 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1123 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1127 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1131 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1140 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[1].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[3].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1163 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1171 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2417 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1179 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1195 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1203 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1208 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1217 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2467 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1221 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1225 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2483 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1229 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1233 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1237 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 2507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1241 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1245 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1249 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1253 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1257 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1265 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1271 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1281 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 2575 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1289 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1293 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2591 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1301 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1305 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 2607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1313 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1317 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1321 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1329 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1335 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1345 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1353 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1361 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1369 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1377 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1381 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2699 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1385 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2708 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1403 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2742 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2751 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1421 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1437 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2792 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2811 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1465 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2819 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1473 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1479 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2847 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2855 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2859 "GrammarParser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -113;

  const signed char Parser::yytable_ninf_ = -60;

  const short int
  Parser::yypact_[] =
  {
      -2,   144,    16,  -113,   -11,    -6,    -6,    -6,    -6,    -6,
    -113,  -113,    72,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
     910,    -6,  -113,  -113,   -33,  -113,    -1,     6,    -1,    36,
     970,  -113,    -3,  -113,  -113,  -113,    -7,    -7,   970,    -7,
    -113,  -113,  -113,   970,   970,   970,   394,   455,   -10,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,    57,    68,    77,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  1380,  -113,
    -113,  -113,   -17,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
      -6,     7,    59,    76,   -40,   -10,   394,  1611,   166,    -6,
      -6,    87,  -113,   108,   122,  1146,   124,  -113,  -113,  -113,
      98,   970,  1347,    97,  -113,  1413,    61,  -113,   910,  -113,
     516,  -113,   970,   970,   970,   970,   970,   970,   970,   970,
     970,   970,   970,   970,   970,   970,   970,   970,   970,   970,
     970,  -113,   100,  -113,   -15,   -10,    -6,   818,   -10,    91,
      92,    71,  -113,  -113,  -113,  -113,  -113,  1446,  -113,  -113,
      86,   -10,   970,   970,   970,   970,  -113,  1479,  -113,   970,
    -113,   970,  -113,   970,  -113,   109,  -113,  1611,     2,  1748,
    1677,  1729,  1644,   102,   102,  1767,     0,     0,   104,   104,
     104,  -113,  1611,  1644,  1767,     0,     0,  1611,  -113,  -113,
      -7,   113,  -113,    19,   553,   593,  -113,    -7,    -7,    -7,
     818,    -8,   970,   970,   114,   630,   667,   111,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,
    -113,   137,   -10,   -10,   -10,   970,    -6,  -113,  1281,  1035,
    1215,  1314,    77,    30,  1512,  1611,  -113,  -113,  -113,   970,
    -113,    -6,   169,  -113,   284,   171,   704,   145,   173,   174,
    -113,  -113,  -113,  1181,  1248,   138,   741,   119,   781,   970,
     818,  -113,   182,   131,   -39,   -27,  1710,  -113,   970,   970,
     970,   970,  -113,  -113,  -113,  1611,  -113,  -113,  -113,  -113,
    -113,  -113,   970,   970,   970,   818,   147,  -113,  -113,  -113,
    -113,  1611,  -113,   148,   187,   -10,   -10,  -113,  -113,  1611,
    1611,  -113,   997,  1073,  1111,   175,   331,   970,   154,  -113,
     151,  -113,   818,   818,   818,   818,   158,   153,   161,  1545,
     850,   163,  1578,   910,  -113,  -113,  -113,  -113,  -113,  -113,
     818,   818,   818,  -113,  -113,  -113,   164,  -113,  -113,  -113,
    -113
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     7,     0,     0,     0,     0,     0,     0,
       9,    11,     0,     3,    13,     4,     6,     5,     1,    34,
      30,     0,    33,    38,    39,    22,    49,     0,    49,     0,
     173,   172,     0,   169,   170,    10,     0,     0,     0,     0,
      68,    70,    69,     0,     0,     0,     0,     0,     0,    72,
      73,    74,    76,    75,    71,    28,    29,     0,   120,    87,
      66,    67,    65,    61,    62,    63,    64,    60,    24,    84,
      86,    85,     0,    78,    79,    80,    81,    82,    83,    40,
       0,     0,     0,     0,     0,    21,     0,   174,     0,     0,
       0,    42,    44,     0,     0,     0,     0,   109,    90,    91,
       0,     0,     0,     0,   111,   115,     0,    77,     0,    23,
       0,   121,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    37,     0,    46,     0,     0,     0,     0,     0,    20,
       0,    54,    19,    50,    51,    52,    53,     0,     8,   171,
       0,     0,     0,     0,     0,     0,    89,     0,    88,     0,
     113,     0,   112,     0,    27,     0,   118,   115,     0,   106,
     104,   105,   108,    92,    93,    99,   100,   101,    94,    95,
      96,    97,    25,   107,    98,   102,   103,    26,    48,    47,
       0,     0,    36,     0,     0,     0,   142,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   166,   168,   127,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,     0,     0,     0,    21,     0,     0,    41,     0,     0,
       0,     0,     0,     0,     0,   114,   117,   116,    45,     0,
      32,     0,     0,   141,     0,     0,     0,     0,     0,     0,
     155,   165,   167,     0,     0,     0,     0,     0,     0,     0,
       0,    18,    17,     0,    19,     0,    57,    43,     0,     0,
       0,     0,   122,   119,   110,    31,    35,   163,   161,   140,
     159,   157,     0,     0,     0,     0,     0,   158,   156,   162,
     160,   164,   128,     0,    15,     0,     0,    55,   125,   124,
     123,   126,     0,     0,     0,   143,     0,     0,     0,    12,
       0,    58,     0,     0,     0,     0,     0,     0,     0,     0,
     151,     0,     0,    30,    56,   152,   153,   154,   144,   146,
       0,     0,     0,   150,   145,    16,     0,   147,   148,   149,
      14
  };

  const short int
  Parser::yypgoto_[] =
  {
    -113,  -113,   126,   204,  -113,  -113,  -113,  -113,  -113,     1,
    -113,   118,  -113,  -106,  -113,  -113,    25,  -113,   206,    -4,
       4,   -34,  -113,   200,  -112,  -113,  -113,  -113,  -113,  -113,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,   -26,
    -113,  -113,  -113,   -96,     8,  -113,     3,    84,  -113,  -113,
    -113,  -113,  -113,   -78,   -87,  -113,  -113,  -113,  -113,   -91,
    -113,  -113,  -113,  -113,  -113,  -113,  -113,  -113,   142,   149,
    -113,  -113
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,    10,    11,    12,    13,   309,   294,   139,   140,
      14,    55,    56,    57,    15,    16,    23,   193,    24,    58,
      92,    93,   134,    82,   142,   143,   144,   145,   146,   265,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    68,
      69,    70,    71,   106,   111,    72,    73,    74,    75,    76,
      77,    78,    17,   243,   244,   210,   211,   212,   320,   321,
     213,   214,   215,   216,   217,   218,   219,   220,    31,    32,
      33,    34
  };

  const short int
  Parser::yytable_[] =
  {
      25,     1,   137,    94,    87,    96,    19,    19,   132,    19,
      19,    19,    95,   -59,   168,   -59,    18,    97,    98,    99,
     102,   105,   138,   191,    19,   296,   221,   297,    80,   189,
      26,    27,    28,    29,    30,   204,    20,   190,    90,   227,
     116,   117,    81,    88,   107,   130,   237,   133,    83,    89,
      21,    21,    90,    21,   163,   121,   122,   123,   124,   209,
     147,    91,    91,   233,    91,    22,    22,   240,    22,    22,
      22,   241,    -2,     3,   273,   157,     4,     5,     6,     7,
       8,   141,   163,    22,   167,    85,   169,   170,   171,   172,
     173,   174,   175,   176,   177,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   131,    91,   162,   246,   108,
     261,   262,   264,   163,    30,    30,   109,     9,   256,   258,
     110,   135,   250,   136,   224,   152,   228,   229,   230,   231,
     225,   141,   226,   167,   141,   234,   151,   235,    89,   153,
     207,   155,   156,   160,   188,     3,   222,   141,     4,     5,
       6,     7,     8,   236,   223,   239,   238,   121,   122,   123,
     124,   192,   124,   247,   248,   249,   279,     3,   279,   101,
       4,     5,     6,     7,     8,   259,   253,   254,   279,   260,
     279,   277,   292,   310,   311,   280,   287,   282,   289,     9,
     283,   284,   293,   295,   306,   307,   308,   207,   207,   266,
     315,   323,   330,   207,   251,   324,   329,   305,   207,   207,
     331,   334,   340,   275,   148,    91,    35,   336,   141,   141,
     141,   208,    91,    91,    91,   263,   164,    79,    84,   333,
     267,   149,     0,   291,   325,   326,   327,   328,     0,   150,
     272,     0,   298,   299,   300,   301,     0,   207,     0,   207,
       0,    91,   337,   338,   339,     0,   302,   303,   304,   207,
       0,   207,     0,   207,     0,     0,   276,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   208,   208,
     319,   322,     0,     0,   208,   252,     0,     0,   207,   208,
     208,   141,   141,     0,   319,   194,   278,   195,     0,   196,
     197,    19,   198,   199,   200,     0,   201,   202,     0,     0,
     203,     0,     0,     0,     0,   207,   207,   207,   207,     0,
       0,     0,     0,     0,     0,     0,     0,   204,   208,     0,
     208,   205,   316,   207,   207,   207,     0,     0,     0,     0,
     208,     0,   208,     0,   208,    21,     0,     0,    19,    36,
      37,     0,   206,     0,    38,     0,     0,     0,     0,   317,
      22,    39,     0,    40,    41,    42,     0,     0,     0,   208,
      43,    44,    45,     0,    86,     0,    47,     0,     0,     0,
       0,   318,    48,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    21,     0,     0,   100,   208,   208,   208,   208,
       0,    49,    50,    51,    52,    53,    54,    22,     0,     0,
       0,    19,    36,    37,   208,   208,   208,    38,     0,     0,
       0,     0,     0,     0,    39,     0,    40,    41,    42,     0,
       0,     0,     0,    43,    44,    45,     0,    86,     0,    47,
       0,     0,     0,     0,     0,    48,     0,     0,     0,   101,
       0,     0,     0,     0,     0,    21,   103,     0,     0,     0,
       0,     0,     0,     0,    49,    50,    51,    52,    53,    54,
      22,     0,    19,    36,    37,     0,     0,     0,    38,     0,
       0,     0,     0,     0,     0,    39,     0,    40,    41,    42,
       0,     0,     0,     0,    43,    44,    45,     0,    86,     0,
      47,   104,     0,     0,     0,     0,    48,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    21,   165,     0,     0,
       0,     0,     0,     0,     0,    49,    50,    51,    52,    53,
      54,    22,     0,    19,    36,    37,     0,     0,     0,    38,
       0,     0,     0,     0,     0,     0,    39,     0,    40,    41,
      42,     0,     0,     0,   242,    43,    44,    45,     0,    86,
     166,    47,     0,     0,   194,     0,   195,    48,   196,   197,
      19,   198,   199,   200,     0,   201,   202,    21,     0,   203,
       0,     0,     0,     0,     0,     0,    49,    50,    51,    52,
      53,    54,    22,     0,   245,     0,   204,     0,     0,     0,
     205,     0,     0,     0,   194,     0,   195,     0,   196,   197,
      19,   198,   199,   200,    21,   201,   202,     0,     0,   203,
       0,   206,     0,     0,     0,     0,     0,     0,     0,    22,
       0,   255,     0,     0,     0,     0,   204,     0,     0,     0,
     205,   194,     0,   195,     0,   196,   197,    19,   198,   199,
     200,     0,   201,   202,    21,     0,   203,     0,     0,     0,
       0,   206,     0,     0,     0,     0,     0,     0,   257,    22,
       0,     0,     0,   204,     0,     0,     0,   205,   194,     0,
     195,     0,   196,   197,    19,   198,   199,   200,     0,   201,
     202,    21,     0,   203,     0,     0,     0,     0,   206,     0,
       0,     0,     0,     0,     0,     0,    22,     0,     0,     0,
     204,     0,     0,     0,   205,   194,     0,   195,   281,   196,
     197,    19,   198,   199,   200,     0,   201,   202,    21,     0,
     203,     0,     0,     0,     0,   206,     0,     0,     0,     0,
       0,     0,     0,    22,     0,     0,     0,   204,     0,     0,
       0,   205,   194,     0,   195,     0,   196,   197,    19,   198,
     199,   200,     0,   201,   202,    21,     0,   203,     0,     0,
       0,     0,   206,     0,     0,     0,     0,     0,     0,     0,
      22,     0,     0,     0,   204,     0,     0,     0,   205,   288,
       0,     0,   194,     0,   195,     0,   196,   197,    19,   198,
     199,   200,    21,   201,   202,     0,     0,   203,     0,   206,
       0,     0,     0,     0,     0,     0,     0,    22,     0,     0,
       0,     0,     0,     0,   204,     0,     0,     0,   205,   194,
       0,   195,     0,   196,   197,    19,   198,   199,   200,     0,
     201,   202,    21,     0,   203,     0,     0,     0,     0,   206,
     290,     0,     0,     0,     0,     0,     0,    22,     0,     0,
       0,   204,     0,     0,     0,   205,     0,    19,    36,    37,
       0,     0,     0,    38,     0,     0,     0,     0,   317,    21,
      39,     0,    40,    41,    42,     0,   206,     0,     0,    43,
      44,    45,     0,    86,    22,    47,     0,     0,     0,     0,
     318,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,    51,    52,    53,    54,    22,    19,    36,    37,
       0,     0,     0,    38,     0,     0,     0,     0,     0,     0,
      39,     0,    40,    41,    42,     0,     0,     0,     0,    43,
      44,    45,     0,    46,     0,    47,     0,     0,     0,     0,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,     0,     0,     0,     0,     0,
      49,    50,    51,    52,    53,    54,    22,    19,    36,    37,
       0,     0,     0,    38,     0,     0,     0,     0,     0,     0,
      39,     0,    40,    41,    42,     0,     0,     0,     0,    43,
      44,    45,     0,    86,   312,    47,     0,     0,     0,     0,
       0,    48,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    21,   112,   113,   114,   115,     0,   116,   117,   118,
      49,    50,    51,    52,    53,    54,    22,     0,     0,     0,
     119,   120,   121,   122,   123,   124,   269,     0,     0,     0,
     126,     0,   127,   128,   129,     0,     0,     0,     0,     0,
     112,   113,   114,   115,     0,   116,   117,   118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   120,
     121,   122,   123,   124,   313,     0,     0,     0,   126,     0,
     127,   128,   129,     0,     0,     0,     0,     0,   112,   113,
     114,   115,     0,   116,   117,   118,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   119,   120,   121,   122,
     123,   124,   314,     0,     0,     0,   126,     0,   127,   128,
     129,     0,     0,     0,     0,     0,   112,   113,   114,   115,
       0,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   119,   120,   121,   122,   123,   124,
     154,     0,     0,     0,   126,     0,   127,   128,   129,     0,
       0,   112,   113,   114,   115,     0,   116,   117,   118,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   119,
     120,   121,   122,   123,   124,   285,     0,     0,     0,   126,
       0,   127,   128,   129,     0,     0,   112,   113,   114,   115,
       0,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   119,   120,   121,   122,   123,   124,
     270,     0,     0,     0,   126,     0,   127,   128,   129,     0,
     112,   113,   114,   115,     0,   116,   117,   118,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   119,   120,
     121,   122,   123,   124,     0,   286,     0,     0,   126,     0,
     127,   128,   129,   112,   113,   114,   115,     0,   116,   117,
     118,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   119,   120,   121,   122,   123,   124,     0,     0,     0,
     268,   126,     0,   127,   128,   129,   112,   113,   114,   115,
       0,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   119,   120,   121,   122,   123,   124,
       0,     0,     0,     0,   126,   271,   127,   128,   129,   112,
     113,   114,   115,     0,   116,   117,   118,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   119,   120,   121,
     122,   123,   124,     0,     0,     0,     0,   126,     0,   127,
     128,   129,   112,   113,   114,   115,     0,   116,   117,   118,
       0,   158,     0,     0,     0,     0,     0,     0,     0,   159,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
     126,     0,   127,   128,   129,   112,   113,   114,   115,     0,
     116,   117,   118,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   119,   120,   121,   122,   123,   124,     0,
       0,     0,   125,   126,     0,   127,   128,   129,   112,   113,
     114,   115,     0,   116,   117,   118,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   119,   120,   121,   122,
     123,   124,     0,   161,     0,     0,   126,     0,   127,   128,
     129,   112,   113,   114,   115,     0,   116,   117,   118,     0,
     158,     0,     0,     0,     0,     0,     0,     0,     0,   119,
     120,   121,   122,   123,   124,     0,     0,     0,     0,   126,
       0,   127,   128,   129,   112,   113,   114,   115,     0,   116,
     117,   118,     0,   232,     0,     0,     0,     0,     0,     0,
       0,     0,   119,   120,   121,   122,   123,   124,     0,     0,
       0,     0,   126,     0,   127,   128,   129,   112,   113,   114,
     115,     0,   116,   117,   118,     0,     0,     0,   274,     0,
       0,     0,     0,     0,     0,   119,   120,   121,   122,   123,
     124,     0,     0,     0,     0,   126,     0,   127,   128,   129,
     112,   113,   114,   115,     0,   116,   117,   118,     0,     0,
       0,     0,     0,     0,   332,     0,     0,     0,   119,   120,
     121,   122,   123,   124,     0,     0,     0,     0,   126,     0,
     127,   128,   129,   112,   113,   114,   115,     0,   116,   117,
     118,     0,     0,     0,     0,     0,   335,     0,     0,     0,
       0,   119,   120,   121,   122,   123,   124,     0,     0,     0,
       0,   126,     0,   127,   128,   129,   112,   113,   114,   115,
       0,   116,   117,   118,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   119,   120,   121,   122,   123,   124,
       0,     0,     0,     0,   126,     0,   127,   128,   129,   112,
     113,   114,     0,     0,   116,   117,   118,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   119,   120,   121,
     122,   123,   124,     0,     0,     0,     0,     0,     0,   127,
     128,   129,   112,     0,   114,     0,     0,   116,   117,   118,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,     0,   127,   128,   129,   112,   113,   114,   115,     0,
     116,   117,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   119,   112,     0,   122,   123,   124,   116,
     117,   118,     0,   126,     0,   127,   128,   129,     0,     0,
       0,     0,   119,   120,   121,   122,   123,   124,   116,   117,
     118,     0,     0,     0,   127,   128,   129,     0,     0,     0,
       0,   119,   120,   121,   122,   123,   124,   116,   117,     0,
       0,     0,     0,   127,   128,   129,     0,     0,     0,     0,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,     0,     0,   128,   129
  };

  const short int
  Parser::yycheck_[] =
  {
       4,     3,    42,    37,    30,    39,    17,    17,     1,    17,
      17,    17,    38,    52,   110,    54,     0,    43,    44,    45,
      46,    47,    62,   135,    17,    52,   138,    54,    61,    44,
       5,     6,     7,     8,     9,    43,    47,    52,    45,   151,
      40,    41,    43,    46,    48,    62,    44,    81,    42,    52,
      61,    61,    45,    61,    52,    55,    56,    57,    58,   137,
      86,    36,    37,   159,    39,    76,    76,    48,    76,    76,
      76,    52,     0,     1,    44,   101,     4,     5,     6,     7,
       8,    85,    52,    76,   110,    49,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,    80,    81,    46,   195,    52,
     222,   223,   224,    52,    89,    90,    48,    45,   205,   206,
      43,    62,   200,    47,    53,    17,   152,   153,   154,   155,
      59,   135,    46,   159,   138,   161,    49,   163,    52,    17,
     137,    17,    44,    46,    44,     1,    55,   151,     4,     5,
       6,     7,     8,    44,    62,    42,   190,    55,    56,    57,
      58,   136,    58,   197,   198,   199,   244,     1,   246,    55,
       4,     5,     6,     7,     8,    64,   202,   203,   256,    42,
     258,    12,   260,   295,   296,    14,    48,    42,    69,    45,
      17,    17,    10,    62,    47,    47,     9,   194,   195,   225,
      25,    47,    49,   200,   201,    54,    48,   285,   205,   206,
      49,    48,    48,   239,    88,   190,    12,   323,   222,   223,
     224,   137,   197,   198,   199,   224,   108,    21,    28,   320,
     226,    89,    -1,   259,   312,   313,   314,   315,    -1,    90,
     232,    -1,   268,   269,   270,   271,    -1,   244,    -1,   246,
      -1,   226,   330,   331,   332,    -1,   282,   283,   284,   256,
      -1,   258,    -1,   260,    -1,    -1,   241,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   194,   195,
     306,   307,    -1,    -1,   200,   201,    -1,    -1,   285,   205,
     206,   295,   296,    -1,   320,    11,    12,    13,    -1,    15,
      16,    17,    18,    19,    20,    -1,    22,    23,    -1,    -1,
      26,    -1,    -1,    -1,    -1,   312,   313,   314,   315,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    43,   244,    -1,
     246,    47,     1,   330,   331,   332,    -1,    -1,    -1,    -1,
     256,    -1,   258,    -1,   260,    61,    -1,    -1,    17,    18,
      19,    -1,    68,    -1,    23,    -1,    -1,    -1,    -1,    28,
      76,    30,    -1,    32,    33,    34,    -1,    -1,    -1,   285,
      39,    40,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,
      -1,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    61,    -1,    -1,     1,   312,   313,   314,   315,
      -1,    70,    71,    72,    73,    74,    75,    76,    -1,    -1,
      -1,    17,    18,    19,   330,   331,   332,    23,    -1,    -1,
      -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,    -1,
      -1,    -1,    -1,    39,    40,    41,    -1,    43,    -1,    45,
      -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    61,     1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
      76,    -1,    17,    18,    19,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    40,    41,    -1,    43,    -1,
      45,    46,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,     1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
      75,    76,    -1,    17,    18,    19,    -1,    -1,    -1,    23,
      -1,    -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,
      34,    -1,    -1,    -1,     1,    39,    40,    41,    -1,    43,
      44,    45,    -1,    -1,    11,    -1,    13,    51,    15,    16,
      17,    18,    19,    20,    -1,    22,    23,    61,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
      74,    75,    76,    -1,     1,    -1,    43,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    11,    -1,    13,    -1,    15,    16,
      17,    18,    19,    20,    61,    22,    23,    -1,    -1,    26,
      -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    76,
      -1,     1,    -1,    -1,    -1,    -1,    43,    -1,    -1,    -1,
      47,    11,    -1,    13,    -1,    15,    16,    17,    18,    19,
      20,    -1,    22,    23,    61,    -1,    26,    -1,    -1,    -1,
      -1,    68,    -1,    -1,    -1,    -1,    -1,    -1,     1,    76,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    47,    11,    -1,
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
      -1,    43,    -1,    -1,    -1,    47,    -1,    17,    18,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    61,
      30,    -1,    32,    33,    34,    -1,    68,    -1,    -1,    39,
      40,    41,    -1,    43,    76,    45,    -1,    -1,    -1,    -1,
      50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    17,    18,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
      40,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      70,    71,    72,    73,    74,    75,    76,    17,    18,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
      40,    41,    -1,    43,    17,    45,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    35,    36,    37,    38,    -1,    40,    41,    42,
      70,    71,    72,    73,    74,    75,    76,    -1,    -1,    -1,
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
      -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      63,    -1,    65,    66,    67,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    62,    63,    -1,    65,    66,    67,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    60,    -1,    -1,    63,    -1,    65,    66,
      67,    35,    36,    37,    38,    -1,    40,    41,    42,    -1,
      44,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,    63,
      -1,    65,    66,    67,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    44,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    -1,    63,    -1,    65,    66,    67,    35,    36,    37,
      38,    -1,    40,    41,    42,    -1,    -1,    -1,    46,    -1,
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
      -1,    -1,    -1,    53,    35,    -1,    56,    57,    58,    40,
      41,    42,    -1,    63,    -1,    65,    66,    67,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    40,    41,
      42,    -1,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    40,    41,    -1,
      -1,    -1,    -1,    65,    66,    67,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    66,    67
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    82,     1,     4,     5,     6,     7,     8,    45,
      83,    84,    85,    86,    91,    95,    96,   133,     0,    17,
      47,    61,    76,    97,    99,   100,    97,    97,    97,    97,
      97,   149,   150,   151,   152,    84,    18,    19,    23,    30,
      32,    33,    34,    39,    40,    41,    43,    45,    51,    70,
      71,    72,    73,    74,    75,    92,    93,    94,   100,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   126,   127,   128,   129,   130,   131,   132,    99,
      61,    43,   104,    42,   104,    49,    43,   120,    46,    52,
      45,    97,   101,   102,   102,   120,   102,   120,   120,   120,
       1,    55,   120,     1,    46,   120,   124,   100,    52,    48,
      43,   125,    35,    36,    37,    38,    40,    41,    42,    53,
      54,    55,    56,    57,    58,    62,    63,    65,    66,    67,
      62,    97,     1,   102,   103,    62,    47,    42,    62,    89,
      90,   100,   105,   106,   107,   108,   109,   120,    83,   149,
     150,    49,    17,    17,    24,    17,    44,   120,    44,    52,
      46,    60,    46,    52,    92,     1,    44,   120,   124,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,    44,    44,
      52,   105,    97,    98,    11,    13,    15,    16,    18,    19,
      20,    22,    23,    26,    43,    47,    68,   127,   128,   134,
     136,   137,   138,   141,   142,   143,   144,   145,   146,   147,
     148,   105,    55,    62,    53,    59,    46,   105,   120,   120,
     120,   120,    44,   124,   120,   120,    44,    44,   102,    42,
      48,    52,     1,   134,   135,     1,   135,   102,   102,   102,
     134,   127,   128,   120,   120,     1,   135,     1,   135,    64,
      42,   105,   105,    90,   105,   110,   120,   101,    29,    21,
      25,    31,   125,    44,    46,   120,    97,    12,    12,   134,
      14,    14,    42,    17,    17,    24,    27,    48,    48,    69,
      69,   120,   134,    10,    88,    62,    52,    54,   120,   120,
     120,   120,   120,   120,   120,   134,    47,    47,     9,    87,
     105,   105,    17,    21,    21,    25,     1,    28,    50,   120,
     139,   140,   120,    47,    54,   134,   134,   134,   134,    48,
      49,    49,    49,   140,    48,    48,    94,   134,   134,   134,
      48
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
     120,   120,   120,   120,   120,   120,   120,   120,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     121,   121,   121,   121,   121,   121,   121,   121,   121,   121,
     122,   123,   123,   123,   124,   124,   125,   125,   125,   126,
     127,   127,   128,   129,   130,   131,   132,   133,   133,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     135,   135,   136,   137,   137,   138,   138,   139,   139,   139,
     140,   140,   141,   142,   143,   144,   145,   145,   145,   145,
     146,   146,   146,   146,   147,   148,   148,   148,   148,   149,
     149,   150,   150,   151,   152
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
       1,     1,     1,     1,     1,     1,     1,     1,     3,     3,
       2,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       5,     2,     3,     3,     3,     1,     3,     3,     2,     5,
       1,     2,     5,     6,     6,     6,     6,     5,     7,     1,
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
  "DotSeparatedIdentifiers", "IdentifierPath", "Variable",
  "AttributedVariable", "Parameters", "MaybeParameters", "Type",
  "BasicType", "ComposedType", "RelationType", "FixedSizedType", "Types",
  "Atom", "Undefined", "Boolean", "String", "BitNumber", "IntegerNumber",
  "FloatingNumber", "RationalNumber", "Reference", "Term", "Expression",
  "Range", "List", "Terms", "Arguments", "TwoOrMoreArguments",
  "DirectCallExpression", "IndirectCallExpression",
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
       0,   348,   348,   360,   364,   368,   372,   376,   384,   390,
     398,   404,   414,   430,   438,   442,   450,   454,   462,   468,
     478,   482,   490,   513,   531,   539,   549,   560,   566,   576,
     580,   588,   596,   604,   608,   616,   622,   632,   638,   648,
     652,   660,   664,   673,   679,   687,   693,   703,   707,   711,
     719,   723,   727,   731,   739,   747,   755,   763,   771,   777,
     787,   791,   795,   799,   803,   807,   811,   815,   823,   831,
     836,   845,   861,   873,   889,   905,   921,   937,   945,   949,
     953,   957,   961,   965,   969,   973,   977,   981,   989,   993,
     997,  1001,  1005,  1009,  1013,  1017,  1021,  1025,  1029,  1033,
    1037,  1041,  1045,  1049,  1053,  1057,  1061,  1065,  1069,  1073,
    1081,  1089,  1094,  1098,  1106,  1112,  1122,  1126,  1130,  1139,
    1149,  1154,  1162,  1170,  1178,  1186,  1194,  1202,  1207,  1216,
    1220,  1224,  1228,  1232,  1236,  1240,  1244,  1248,  1252,  1256,
    1264,  1270,  1280,  1288,  1292,  1300,  1304,  1312,  1316,  1320,
    1328,  1334,  1344,  1352,  1360,  1368,  1376,  1380,  1384,  1389,
    1398,  1402,  1406,  1411,  1420,  1430,  1436,  1443,  1449,  1460,
    1464,  1472,  1478,  1488,  1496
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
#line 3787 "GrammarParser.cpp" // lalr1.cc:1167
#line 1502 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
