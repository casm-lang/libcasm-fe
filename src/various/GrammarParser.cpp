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
        const auto name = make< IdentifierNode >( sourceLocation, type->description() );
        const auto node = make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( Location& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::RuleReferenceType >();
        const auto name = make< IdentifierNode >( sourceLocation, type->description() );
        const auto node = make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( Location& sourceLocation )
    {
        const auto name = make< IdentifierNode >( sourceLocation, "Agent" );
        const auto node = make< BasicType >( sourceLocation, name );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( Location& sourceLocation )
    {
        const auto agentType = createAgentType( sourceLocation );
        const auto ruleRefType = createRuleRefType( sourceLocation );

        const auto argTypes = make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = make< IdentifierNode >( sourceLocation, "program" );
        return make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( (rule->id() == Node::ID::BLOCK_RULE )
                or (rule->id() == Node::ID::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        const auto& sourceLocation = rule->sourceLocation();
        const auto rules = make< Rules >( sourceLocation );
        rules->add( rule );
        return make< BlockRule >( sourceLocation, rules );
    }

#line 116 "GrammarParser.cpp" // lalr1.cc:413


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
#line 202 "GrammarParser.cpp" // lalr1.cc:479

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
      case 140: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 141: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 142: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 100: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 136: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 139: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 131: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 130: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 132: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 101: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 122: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 129: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 80: // Definition
      case 81: // AttributedDefinition
        value.move< Definition::Ptr > (that.value);
        break;

      case 82: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 120: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 93: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 124: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 85: // MaybeDefined
      case 105: // Atom
      case 114: // Term
      case 115: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 143: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 118: // Terms
      case 119: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 102: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 134: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 83: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 94: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
        break;

      case 121: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 135: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 133: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 117: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 95: // Identifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 84: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 97: // Parameters
      case 98: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 116: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 103: // RangedType
        value.move< RangedType::Ptr > (that.value);
        break;

      case 126: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 125: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 113: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 127: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 137: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 128: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 79: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 99: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 86: // FunctionParameters
      case 87: // MaybeFunctionParameters
      case 104: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 106: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 123: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 89: // Initializer
      case 138: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 107: // Boolean
      case 108: // String
      case 109: // BitNumber
      case 110: // IntegerNumber
      case 111: // FloatingNumber
      case 112: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 96: // Variable
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
      case 140: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 141: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 142: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 100: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 136: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 139: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 131: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 130: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 132: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 101: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 122: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 129: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 80: // Definition
      case 81: // AttributedDefinition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 82: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 120: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 93: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 124: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 85: // MaybeDefined
      case 105: // Atom
      case 114: // Term
      case 115: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 143: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 118: // Terms
      case 119: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 102: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 134: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 83: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 94: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
        break;

      case 121: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 135: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 133: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 117: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 95: // Identifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 84: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 97: // Parameters
      case 98: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 116: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 103: // RangedType
        value.copy< RangedType::Ptr > (that.value);
        break;

      case 126: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 125: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 113: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 127: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 137: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 128: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 79: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 99: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 86: // FunctionParameters
      case 87: // MaybeFunctionParameters
      case 104: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 106: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 123: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 89: // Initializer
      case 138: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 107: // Boolean
      case 108: // String
      case 109: // BitNumber
      case 110: // IntegerNumber
      case 111: // FloatingNumber
      case 112: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 96: // Variable
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
      case 140: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 141: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 142: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 100: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 136: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 139: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 131: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 130: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 132: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 101: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 122: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 129: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 80: // Definition
      case 81: // AttributedDefinition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 82: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 92: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 120: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 93: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 124: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 85: // MaybeDefined
      case 105: // Atom
      case 114: // Term
      case 115: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 143: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 118: // Terms
      case 119: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 102: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 134: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 83: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 94: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
        break;

      case 121: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 135: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 133: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 117: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 95: // Identifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 84: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 97: // Parameters
      case 98: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 116: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 103: // RangedType
        yylhs.value.build< RangedType::Ptr > ();
        break;

      case 126: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 125: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 113: // RuleReference
        yylhs.value.build< RuleReferenceAtom::Ptr > ();
        break;

      case 127: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 137: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 128: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 79: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 99: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 86: // FunctionParameters
      case 87: // MaybeFunctionParameters
      case 104: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 106: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 123: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 89: // Initializer
      case 138: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 107: // Boolean
      case 108: // String
      case 109: // BitNumber
      case 110: // IntegerNumber
      case 111: // FloatingNumber
      case 112: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 96: // Variable
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
#line 321 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& fileName = filePath.substr( filePath.find_last_of( "/\\" ) + 1 );
      const std::string& name = fileName.substr( 0, fileName.rfind( "." ) );

      const auto specificationName = make< IdentifierNode >( yylhs.location, name );
      result = make< Specification >( yylhs.location, specificationName, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1243 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 333 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1251 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 337 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1259 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 341 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1267 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 345 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1275 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 353 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 359 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 367 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1313 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 383 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< IdentifierNode::Ptr > ();

      auto function = make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< Type::Ptr > () );
      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
           initializer->function()->setIdentifier( identifier );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1333 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 411 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 419 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 423 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 437 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 451 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = make< Types >( yylhs.location );
  }
#line 1409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 459 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      auto arguments = make< Expressions >( yylhs.location );
      // TODO add `default` agent to arguments
      const auto program = make< DirectCallExpression >(
          yylhs.location, programDefinition->identifier(), arguments );

      const auto ruleReference = make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );

      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1430 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
          initializer->function()->setIdentifier( programDefinition->identifier() );
      }
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1447 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto arguments = make< Expressions >( yylhs.location );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 502 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 525 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 545 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 569 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 583 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = make< NodeList< IdentifierNode > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 593 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1575 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 597 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), unresolvedType );
  }
#line 1584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 606 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1594 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1612 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 626 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1620 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1628 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 642 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 654 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 670 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 678 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 686 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1694 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1704 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 702 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1712 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 706 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1720 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 714 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1736 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1744 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 722 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1760 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 730 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1768 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 738 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1776 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 746 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1785 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 751 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 769 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 774 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 783 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 792 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 810 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto ruleName = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
      yylhs.value.as< RuleReferenceAtom::Ptr > () = make< RuleReferenceAtom >( yylhs.location, ruleName );
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 819 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 823 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 827 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 831 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1889 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 835 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 839 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 843 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 847 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 851 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1929 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 859 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1937 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 863 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 867 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 871 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 1961 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 875 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 1969 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 879 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1977 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 883 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 1985 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 1993 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 891 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2001 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 895 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call power builtin
  }
#line 2009 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 899 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2017 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 903 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2025 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 907 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2033 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 911 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 915 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2049 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2057 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 923 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2065 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 927 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2073 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 931 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2081 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 935 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO add implies instruction
  }
#line 2089 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 939 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2097 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 948 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2105 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, expressions );
  }
#line 2114 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 961 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[1].value.as< Expression::Ptr > () );
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, expressions );
  }
#line 2124 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 967 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2132 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2142 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 980 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2169 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1003 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), arguments );
  }
#line 2178 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1008 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2186 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1016 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1032 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1040 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2218 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1048 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2227 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2236 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1062 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2244 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2252 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1070 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2260 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1078 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2284 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2292 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2300 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1094 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2308 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2316 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2326 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1112 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1122 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = make< SkipRule >( yylhs.location );
  }
#line 2344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1130 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1142 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1158 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2392 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1166 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1172 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2412 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1182 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2420 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1190 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2428 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1198 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2436 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1206 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2444 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1210 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2452 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1218 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1222 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2468 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1230 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2476 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2486 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1244 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1251 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1257 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2518 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1268 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2526 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1272 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2534 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1280 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1286 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2554 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1296 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = make< BasicAttribute >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 2562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1304 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2570 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2574 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -167;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
       8,    27,    19,   -42,   -52,   -52,   -52,   -52,   -52,  -167,
    -167,    27,  -167,  -167,  -167,  -167,  -167,  -167,   697,  -167,
    -167,     2,    11,     2,     6,   752,  -167,     4,  -167,  -167,
    -167,   -52,   752,   -52,  -167,  -167,  -167,   752,   752,   752,
     422,   532,   -27,  -167,  -167,  -167,  -167,  -167,  -167,  -167,
      10,    26,    53,  -167,  -167,  -167,  -167,  -167,  -167,  -167,
    -167,  -167,  1062,  -167,  -167,  -167,    42,  -167,  -167,  -167,
    -167,  -167,   -52,    47,    61,   -38,   -52,   587,  1272,    62,
     -52,    65,    92,   841,    97,  -167,  -167,  -167,  -167,   752,
    1092,    75,    -5,  -167,  1032,    18,  -167,   697,  -167,   642,
    -167,   752,   752,   752,   752,   752,   752,   752,   752,   752,
     752,   752,   752,   752,   752,   752,   752,   752,   752,  -167,
      -4,   -52,   -52,   410,   -52,    68,    72,   -34,  -167,  -167,
    -167,  -167,  -167,  1092,  -167,  -167,   -52,   752,   752,   752,
    1122,  -167,  -167,  -167,   752,  -167,   752,  -167,  -167,  1272,
     278,  1362,  1387,  1332,    73,    73,  1406,     3,     3,    67,
      67,    67,  -167,  1272,  1406,     3,     3,  1272,  -167,   -52,
      91,  -167,    57,   410,   410,  -167,   -52,   -52,   410,   -35,
     752,   752,    79,   410,   410,    74,  -167,  -167,  -167,  -167,
    -167,  -167,  -167,  -167,  -167,  -167,  -167,  -167,    94,   -52,
     -52,   -52,   752,  -167,   972,   910,  1002,    53,  1272,  1152,
    -167,   752,  -167,   -52,  -167,   242,   282,    95,   120,  -167,
    -167,  -167,   876,   942,   342,   355,   752,   410,  -167,   129,
    -167,    -3,  1182,   752,   752,   752,  -167,  -167,  1272,  -167,
    -167,  -167,  -167,   752,   752,   410,   104,  -167,  -167,  1272,
    -167,   105,   131,  -167,   -52,   752,   752,  -167,  1272,  -167,
     776,   806,   119,   477,   752,   113,  -167,  -167,  1302,   410,
     410,   410,   112,   116,  1212,   477,   118,  1242,   697,   752,
    -167,  -167,  -167,   410,   410,   410,  -167,  -167,  -167,   121,
    -167,  -167,  -167,  -167
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
      10,     2,     3,    12,     4,     6,     5,     1,    29,    32,
      21,    40,     0,    40,     0,   152,   151,     0,   148,   149,
       9,     0,     0,     0,    59,    61,    60,     0,     0,     0,
       0,     0,     0,    63,    64,    65,    67,    66,    62,    27,
      28,     0,   107,    77,    57,    58,    56,    52,    53,    54,
      55,    51,    23,    74,    76,    75,     0,    69,    70,    71,
      72,    73,     0,     0,     0,     0,    20,     0,   153,     0,
       0,    36,     0,     0,     0,    98,    79,    81,   106,     0,
     104,    74,     0,   100,   104,     0,    68,     0,    22,     0,
     108,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,    19,     0,    45,    18,    41,
      42,    43,    44,     0,     7,   150,     0,     0,     0,     0,
       0,    80,    78,   105,     0,   101,     0,   102,    26,   104,
      96,    94,    95,    97,    82,    83,    89,    90,    91,    84,
      85,    86,    87,    24,    88,    92,    93,    25,    39,     0,
       0,    34,     0,     0,     0,   127,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   145,   147,   113,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,     0,     0,
       0,     0,     0,    35,     0,     0,     0,     0,   103,     0,
      37,     0,    31,     0,   126,     0,     0,     0,     0,   138,
     144,   146,     0,     0,     0,     0,     0,     0,    17,    16,
      50,     0,     0,     0,     0,     0,   109,    99,    30,    33,
     142,   125,   140,     0,     0,     0,     0,   139,   141,   143,
     114,     0,    14,    46,     0,    47,     0,   111,   110,   112,
       0,     0,   128,     0,     0,     0,    11,    49,     0,     0,
       0,     0,     0,     0,     0,   135,     0,     0,    29,    48,
     136,   137,   129,     0,     0,     0,   134,   130,    15,     0,
     131,   132,   133,    13
  };

  const short int
  Parser::yypgoto_[] =
  {
    -167,  -167,    93,   162,  -167,  -167,  -167,  -167,  -167,  -167,
    -167,    77,  -167,  -103,  -167,  -167,    22,  -167,   -29,  -167,
     153,  -100,  -167,  -167,  -167,  -167,  -167,  -167,  -167,  -167,
    -167,  -167,  -167,  -167,  -167,  -167,   -25,   -39,  -167,  -167,
     137,   -50,   -56,    69,  -167,  -167,  -167,  -167,  -120,  -166,
    -167,  -167,  -167,  -167,   -96,  -167,  -167,  -167,  -167,  -167,
    -167,  -167,   100,  -167,  -167,  -167
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     9,    10,    11,    12,   266,   252,   125,   126,
      13,    49,    50,    51,    14,    15,    52,   172,    82,   120,
      73,   128,   129,   130,   131,   132,   231,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      92,    66,    67,    68,    69,    70,    71,    16,   214,   215,
     188,   189,   190,   275,   276,   191,   192,   193,   194,   195,
     196,   197,    26,    27,    28,    29
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      78,    91,   100,   187,    84,   123,    18,    83,   216,   182,
     201,     1,    85,    86,    87,    90,    94,   224,   225,    17,
     202,   170,    19,   124,   198,    20,    21,    22,    23,    24,
      25,     3,    19,     4,     5,     6,   203,     7,    91,    19,
     143,   168,   253,   119,   105,   106,    72,    96,   144,   169,
     254,    79,   133,    81,    74,    81,    76,    80,   219,   110,
     111,   112,   113,    97,   140,   147,     3,   185,     4,     5,
       6,   144,     7,     8,   149,    98,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,    81,   241,   241,    99,   127,   228,
     229,   230,    25,   118,   241,   241,   212,   250,   121,   122,
     213,   137,   204,   205,   206,   136,   139,   185,   185,   208,
     142,   209,   185,   220,   199,   262,   113,   185,   185,   110,
     111,   112,   113,   200,   211,    89,   226,   227,   243,   244,
     210,   251,   265,   127,   171,   271,   127,   217,   218,   280,
     281,   282,   263,   264,   267,   222,   223,   236,   127,   185,
     185,   278,   283,   290,   291,   292,   284,   287,   185,   185,
     293,   185,   134,    30,   148,   289,    75,   232,    95,   286,
     135,     0,     0,     0,     0,     0,   238,     0,     0,   185,
       0,    81,   186,     0,     0,     0,     0,     0,    81,    81,
       0,   249,     0,     0,     0,     0,     0,     0,   257,   258,
     259,     0,     0,   185,   185,   185,     0,     0,   260,   261,
       0,   127,   127,   127,     0,     0,     0,   185,   185,   185,
     158,   268,     0,     0,     0,   239,     0,     0,   274,   277,
       0,     0,   186,   186,     0,     0,     0,   186,   221,     0,
     274,     0,   186,   186,   158,   173,   240,   174,     0,   175,
     176,     0,   177,   178,     0,   179,   180,     0,     0,   181,
       0,     0,     0,     0,     0,     0,   127,     0,     0,     0,
       0,     0,     0,     0,   186,   186,   182,     0,     0,     0,
     183,     0,     0,   186,   186,   173,   186,   174,   242,   175,
     176,     0,   177,   178,     0,   179,   180,     0,   184,   181,
       0,     0,     0,     0,   186,     0,    19,     0,     0,   105,
     106,   107,     0,     0,     0,     0,   182,     0,     0,     0,
     183,     0,   108,   109,   110,   111,   112,   113,   186,   186,
     186,   115,   116,   117,     0,     0,     0,     0,   184,     0,
       0,     0,   186,   186,   186,   173,    19,   174,     0,   175,
     176,     0,   177,   178,     0,   179,   180,     0,   173,   181,
     174,     0,   175,   176,     0,   177,   178,     0,   179,   180,
       0,     0,   181,     0,     0,     0,   182,     0,     0,     0,
     183,   247,     0,     0,     0,     0,     0,     0,     0,   182,
       0,     0,     0,   183,     0,     0,     0,     0,   184,     0,
       0,     0,     0,     0,     0,     0,    19,     0,     0,     0,
       0,   184,   248,   173,     0,   174,     0,   175,   176,    19,
     177,   178,     0,   179,   180,     0,     0,   181,     0,     0,
       0,     0,    31,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,    33,   182,    34,    35,    36,   183,     0,
       0,     0,    37,    38,    39,     0,    77,    88,    41,     0,
       0,     0,     0,     0,    42,     0,   184,     0,    89,     0,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48,    19,    31,     0,     0,
       0,    32,     0,     0,     0,     0,   272,     0,    33,     0,
      34,    35,    36,     0,     0,     0,     0,    37,    38,    39,
       0,    77,     0,    41,     0,     0,     0,     0,   273,    42,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,    19,    31,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,    33,     0,    34,    35,    36,     0,     0,
       0,     0,    37,    38,    39,     0,    77,     0,    41,    93,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48,    19,    31,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,    33,     0,
      34,    35,    36,     0,     0,     0,     0,    37,    38,    39,
       0,    77,     0,    41,     0,     0,     0,     0,     0,    42,
       0,     0,     0,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,    19,    31,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,    33,     0,    34,    35,    36,     0,     0,
       0,     0,    37,    38,    39,     0,    77,    88,    41,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48,    19,    31,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,    33,     0,
      34,    35,    36,     0,     0,     0,     0,    37,    38,    39,
       0,    40,     0,    41,     0,     0,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,    19,    31,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,    33,     0,    34,    35,    36,     0,     0,
       0,     0,    37,    38,    39,   269,    77,     0,    41,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,   101,   102,   103,   104,     0,   105,   106,   107,
      43,    44,    45,    46,    47,    48,    19,     0,   270,     0,
     108,   109,   110,   111,   112,   113,     0,     0,     0,   115,
     116,   117,   101,   102,   103,   104,     0,   105,   106,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   109,   110,   111,   112,   113,   138,     0,     0,   115,
     116,   117,     0,     0,     0,     0,     0,   101,   102,   103,
     104,     0,   105,   106,   107,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,   109,   110,   111,   112,
     113,   245,     0,     0,   115,   116,   117,     0,     0,     0,
       0,     0,   101,   102,   103,   104,     0,   105,   106,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   109,   110,   111,   112,   113,   234,     0,     0,   115,
     116,   117,     0,     0,     0,     0,   101,   102,   103,   104,
       0,   105,   106,   107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   108,   109,   110,   111,   112,   113,
     246,     0,     0,   115,   116,   117,     0,     0,   101,   102,
     103,   104,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,   233,     0,     0,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,     0,   235,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,     0,     0,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,     0,     0,   145,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,   146,     0,     0,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,   114,     0,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,   141,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,     0,     0,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,   207,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,     0,     0,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,     0,     0,   237,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,     0,     0,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   255,   110,   111,
     112,   113,   256,     0,     0,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,   285,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,     0,     0,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,     0,     0,     0,
       0,   288,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,     0,     0,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,     0,     0,   115,   116,   117,   101,   102,
     103,   104,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   279,   110,   111,
     112,   113,     0,     0,     0,   115,   116,   117,   101,   102,
     103,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,     0,     0,   115,   116,   117,   101,     0,
     103,     0,     0,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,     0,   101,     0,   115,   116,   117,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,   105,   106,     0,
     115,   116,   117,     0,     0,     0,     0,     0,     0,     0,
     108,   109,   110,   111,   112,   113,     0,     0,     0,     0,
     116,   117
  };

  const short int
  Parser::yycheck_[] =
  {
      25,    40,    52,   123,    33,    43,    48,    32,   174,    44,
      44,     3,    37,    38,    39,    40,    41,   183,   184,     0,
      54,   121,    74,    61,   124,     3,     4,     5,     6,     7,
       8,     4,    74,     6,     7,     8,   136,    10,    77,    74,
      45,    45,    45,    72,    41,    42,    44,    74,    53,    53,
      53,    47,    77,    31,    43,    33,    50,    53,   178,    56,
      57,    58,    59,    53,    89,    47,     4,   123,     6,     7,
       8,    53,    10,    46,    99,    49,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,    72,   215,   216,    44,    76,   199,
     200,   201,    80,    61,   224,   225,    49,   227,    61,    48,
      53,    19,   137,   138,   139,    50,    19,   173,   174,   144,
      45,   146,   178,   179,    56,   245,    59,   183,   184,    56,
      57,    58,    59,    61,    43,    56,    62,    43,    43,    19,
     169,    12,    11,   121,   122,    26,   124,   176,   177,   269,
     270,   271,    48,    48,   254,   180,   181,   207,   136,   215,
     216,    48,    50,   283,   284,   285,    50,    49,   224,   225,
      49,   227,    79,    11,    97,   278,    23,   202,    41,   275,
      80,    -1,    -1,    -1,    -1,    -1,   211,    -1,    -1,   245,
      -1,   169,   123,    -1,    -1,    -1,    -1,    -1,   176,   177,
      -1,   226,    -1,    -1,    -1,    -1,    -1,    -1,   233,   234,
     235,    -1,    -1,   269,   270,   271,    -1,    -1,   243,   244,
      -1,   199,   200,   201,    -1,    -1,    -1,   283,   284,   285,
     255,   256,    -1,    -1,    -1,   213,    -1,    -1,   263,   264,
      -1,    -1,   173,   174,    -1,    -1,    -1,   178,   179,    -1,
     275,    -1,   183,   184,   279,    13,    14,    15,    -1,    17,
      18,    -1,    20,    21,    -1,    23,    24,    -1,    -1,    27,
      -1,    -1,    -1,    -1,    -1,    -1,   254,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   215,   216,    44,    -1,    -1,    -1,
      48,    -1,    -1,   224,   225,    13,   227,    15,    16,    17,
      18,    -1,    20,    21,    -1,    23,    24,    -1,    66,    27,
      -1,    -1,    -1,    -1,   245,    -1,    74,    -1,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      48,    -1,    54,    55,    56,    57,    58,    59,   269,   270,
     271,    63,    64,    65,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,   283,   284,   285,    13,    74,    15,    -1,    17,
      18,    -1,    20,    21,    -1,    23,    24,    -1,    13,    27,
      15,    -1,    17,    18,    -1,    20,    21,    -1,    23,    24,
      -1,    -1,    27,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      48,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,
      -1,    66,    67,    13,    -1,    15,    -1,    17,    18,    74,
      20,    21,    -1,    23,    24,    -1,    -1,    27,    -1,    -1,
      -1,    -1,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    44,    33,    34,    35,    48,    -1,
      -1,    -1,    40,    41,    42,    -1,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    66,    -1,    56,    -1,
      -1,    -1,    -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    20,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    -1,    44,    -1,    46,    47,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    20,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    -1,    44,    45,    46,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    69,    70,    71,    72,    73,    74,    20,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    68,    69,    70,    71,    72,
      73,    74,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    33,    34,    35,    -1,    -1,
      -1,    -1,    40,    41,    42,    19,    44,    -1,    46,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      68,    69,    70,    71,    72,    73,    74,    -1,    22,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    63,
      64,    65,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    25,    -1,    -1,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    25,    -1,    -1,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    26,    -1,    -1,    63,
      64,    65,    -1,    -1,    -1,    -1,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      28,    -1,    -1,    63,    64,    65,    -1,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    30,    -1,    -1,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    32,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    61,    -1,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    60,    -1,    -1,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    49,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    64,    65,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    64,    65,    36,    37,
      38,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    64,    65,    36,    -1,
      38,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    36,    -1,    63,    64,    65,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    41,    42,    -1,
      63,    64,    65,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      64,    65
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    79,     4,     6,     7,     8,    10,    46,    80,
      81,    82,    83,    88,    92,    93,   125,     0,    48,    74,
      94,    94,    94,    94,    94,    94,   140,   141,   142,   143,
      81,    20,    24,    31,    33,    34,    35,    40,    41,    42,
      44,    46,    52,    68,    69,    70,    71,    72,    73,    89,
      90,    91,    94,   105,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   115,   116,   117,   119,   120,   121,   122,
     123,   124,    44,    98,    43,    98,    50,    44,   114,    47,
      53,    94,    96,   114,    96,   114,   114,   114,    45,    56,
     114,   115,   118,    47,   114,   118,    74,    53,    49,    44,
     119,    36,    37,    38,    39,    41,    42,    43,    54,    55,
      56,    57,    58,    59,    61,    63,    64,    65,    61,    96,
      97,    61,    48,    43,    61,    86,    87,    94,    99,   100,
     101,   102,   103,   114,    80,   140,    50,    19,    25,    19,
     114,    45,    45,    45,    53,    47,    60,    47,    89,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,    45,    53,
      99,    94,    95,    13,    15,    17,    18,    20,    21,    23,
      24,    27,    44,    48,    66,   120,   121,   126,   128,   129,
     130,   133,   134,   135,   136,   137,   138,   139,    99,    56,
      61,    44,    54,    99,   114,   114,   114,    45,   114,   114,
      96,    43,    49,    53,   126,   127,   127,    96,    96,   126,
     120,   121,   114,   114,   127,   127,    62,    43,    99,    99,
      99,   104,   114,    30,    26,    32,   119,    47,   114,    94,
      14,   126,    16,    43,    19,    25,    28,    49,    67,   114,
     126,    12,    85,    45,    53,    55,    60,   114,   114,   114,
     114,   114,   126,    48,    48,    11,    84,    99,   114,    19,
      22,    26,    29,    51,   114,   131,   132,   114,    48,    55,
     126,   126,   126,    50,    50,    50,   132,    49,    49,    91,
     126,   126,   126,    49
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    78,    79,    80,    80,    80,    80,    81,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    89,    89,    90,    90,    91,    91,
      92,    93,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,    99,    99,   100,   101,   102,   103,   104,
     104,   105,   105,   105,   105,   105,   105,   105,   105,   106,
     107,   107,   108,   109,   109,   110,   111,   112,   113,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   116,
     117,   117,   117,   118,   118,   119,   119,   120,   120,   121,
     122,   123,   124,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   127,   127,   128,   129,   129,
     130,   131,   131,   131,   132,   132,   133,   134,   135,   136,
     136,   137,   137,   138,   139,   139,   139,   139,   140,   140,
     141,   141,   142,   143
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     4,     1,     2,
       1,     8,     1,     4,     0,     4,     0,     3,     1,     1,
       0,     2,     4,     1,     3,     3,     3,     1,     1,     0,
       7,     6,     1,     3,     1,     3,     1,     3,     1,     3,
       0,     1,     1,     1,     1,     1,     4,     4,     6,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     2,
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     5,
       2,     3,     3,     3,     1,     3,     2,     1,     2,     5,
       6,     6,     6,     5,     7,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     4,     6,
       6,     3,     3,     3,     2,     1,     6,     6,     2,     3,
       3,     3,     3,     3,     2,     1,     2,     1,     1,     1,
       3,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"option\"", "\"derived\"", "\"enum\"", "\"rule\"", "\"dumps\"",
  "\"function\"", "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"",
  "\"par\"", "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
  "\"iterate\"", "\"do\"", "\"call\"", "\"if\"", "\"then\"", "\"else\"",
  "\"case\"", "\"of\"", "\"default\"", "\"holds\"", "\"exists\"",
  "\"with\"", "\"undef\"", "\"false\"", "\"true\"", "\"and\"", "\"or\"",
  "\"xor\"", "\"implies\"", "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"",
  "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\":\"", "\"_\"", "\"@\"",
  "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"", "\"^\"", "\"..\"",
  "\"->\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"",
  "\"binary\"", "\"hexadecimal\"", "\"integer\"", "\"rational\"",
  "\"floating\"", "\"string\"", "\"identifier\"", "UPLUS", "UMINUS",
  "DIRECT_CALL_EXPR_NO_ARG", "$accept", "Specification", "Definition",
  "AttributedDefinition", "Definitions", "FunctionDefinition",
  "MaybeInitially", "MaybeDefined", "FunctionParameters",
  "MaybeFunctionParameters", "ProgramFunctionDefinition", "Initializer",
  "Initializers", "MaybeInitializers", "DerivedDefinition",
  "EnumerationDefinition", "Identifier", "Identifiers", "Variable",
  "Parameters", "MaybeParameters", "Type", "BasicType", "ComposedType",
  "FixedSizedType", "RangedType", "Types", "Atom", "Undefined", "Boolean",
  "String", "BitNumber", "IntegerNumber", "FloatingNumber",
  "RationalNumber", "RuleReference", "Term", "Expression", "Range", "List",
  "Terms", "Arguments", "DirectCallExpression", "IndirectCallExpression",
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
       0,   320,   320,   332,   336,   340,   344,   352,   358,   366,
     372,   382,   398,   406,   410,   418,   422,   430,   436,   446,
     450,   458,   475,   492,   501,   512,   524,   530,   540,   544,
     552,   560,   568,   576,   582,   592,   596,   605,   611,   621,
     625,   633,   637,   641,   645,   653,   661,   669,   677,   685,
     691,   701,   705,   709,   713,   717,   721,   725,   729,   737,
     745,   750,   759,   768,   773,   782,   791,   800,   809,   818,
     822,   826,   830,   834,   838,   842,   846,   850,   858,   862,
     866,   870,   874,   878,   882,   886,   890,   894,   898,   902,
     906,   910,   914,   918,   922,   926,   930,   934,   938,   947,
     955,   960,   966,   973,   979,   989,   993,  1002,  1007,  1015,
    1023,  1031,  1039,  1047,  1052,  1061,  1065,  1069,  1073,  1077,
    1081,  1085,  1089,  1093,  1097,  1105,  1111,  1121,  1129,  1133,
    1141,  1149,  1153,  1157,  1165,  1171,  1181,  1189,  1197,  1205,
    1209,  1217,  1221,  1229,  1237,  1243,  1250,  1256,  1267,  1271,
    1279,  1285,  1295,  1303
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
#line 3403 "GrammarParser.cpp" // lalr1.cc:1167
#line 1309 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
