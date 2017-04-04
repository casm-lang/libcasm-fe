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
        const auto name = Ast::make< IdentifierNode >( sourceLocation, type->description() );
        const auto node = Ast::make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createRuleRefType( Location& sourceLocation )
    {
        const auto type = libstdhl::get< libcasm_ir::RuleReferenceType >();
        const auto name = Ast::make< IdentifierNode >( sourceLocation, type->description() );
        const auto node = Ast::make< BasicType >( sourceLocation, name );
        node->setType( type );
        return node;
    }

    static BasicType::Ptr createAgentType( Location& sourceLocation )
    {
        const auto name = Ast::make< IdentifierNode >( sourceLocation, "Agent" );
        const auto node = Ast::make< BasicType >( sourceLocation, name );
        return node;
    }

    static FunctionDefinition::Ptr createProgramFunction( Location& sourceLocation )
    {
        const auto agentType = createAgentType( sourceLocation );
        const auto ruleRefType = createRuleRefType( sourceLocation );

        const auto argTypes = Ast::make< Types >( sourceLocation );
        argTypes->add( agentType );

        const auto program = Ast::make< IdentifierNode >( sourceLocation, "program" );
        return Ast::make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
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
      case 139: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 140: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 141: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 98: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 135: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 138: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 130: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 129: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 131: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 99: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 121: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 128: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 78: // Definition
      case 79: // AttributedDefinition
        value.move< Definition::Ptr > (that.value);
        break;

      case 80: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 90: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 119: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 91: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 123: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 83: // MaybeDefined
      case 103: // Atom
      case 112: // Term
      case 113: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 142: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 116: // Terms
      case 117: // Arguments
      case 118: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 100: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 133: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 81: // FunctionDefinition
      case 86: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 92: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
        break;

      case 120: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 134: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 132: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 115: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 93: // Identifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 82: // MaybeInitially
      case 88: // Initializers
      case 89: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 95: // Parameters
      case 96: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 114: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 101: // RangedType
        value.move< RangedType::Ptr > (that.value);
        break;

      case 125: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 124: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 111: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 126: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 136: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 127: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 77: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 97: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 84: // FunctionParameters
      case 85: // MaybeFunctionParameters
      case 102: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 104: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 122: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 87: // Initializer
      case 137: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 105: // Boolean
      case 106: // String
      case 107: // BitNumber
      case 108: // IntegerNumber
      case 109: // FloatingNumber
      case 110: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 94: // Variable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 66: // "binary"
      case 67: // "hexadecimal"
      case 68: // "integer"
      case 69: // "rational"
      case 70: // "floating"
      case 71: // "string"
      case 72: // "identifier"
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
      case 139: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 140: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 141: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 98: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 135: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 138: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 130: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 129: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 131: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 99: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 121: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 128: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 78: // Definition
      case 79: // AttributedDefinition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 80: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 90: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 119: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 91: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 123: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 83: // MaybeDefined
      case 103: // Atom
      case 112: // Term
      case 113: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 142: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 116: // Terms
      case 117: // Arguments
      case 118: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 100: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 133: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 81: // FunctionDefinition
      case 86: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 92: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
        break;

      case 120: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 134: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 132: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 115: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 93: // Identifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 82: // MaybeInitially
      case 88: // Initializers
      case 89: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 95: // Parameters
      case 96: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 114: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 101: // RangedType
        value.copy< RangedType::Ptr > (that.value);
        break;

      case 125: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 124: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 111: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 126: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 136: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 127: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 77: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 97: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 84: // FunctionParameters
      case 85: // MaybeFunctionParameters
      case 102: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 104: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 122: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 87: // Initializer
      case 137: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 105: // Boolean
      case 106: // String
      case 107: // BitNumber
      case 108: // IntegerNumber
      case 109: // FloatingNumber
      case 110: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 94: // Variable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 66: // "binary"
      case 67: // "hexadecimal"
      case 68: // "integer"
      case 69: // "rational"
      case 70: // "floating"
      case 71: // "string"
      case 72: // "identifier"
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
      case 139: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 140: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 141: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 98: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 135: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 138: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 130: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 129: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 131: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 99: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 121: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 128: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 78: // Definition
      case 79: // AttributedDefinition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 80: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 90: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 119: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 91: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 123: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 83: // MaybeDefined
      case 103: // Atom
      case 112: // Term
      case 113: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 142: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 116: // Terms
      case 117: // Arguments
      case 118: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 100: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 133: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 81: // FunctionDefinition
      case 86: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 92: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
        break;

      case 120: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 134: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 132: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 115: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 93: // Identifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 82: // MaybeInitially
      case 88: // Initializers
      case 89: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 95: // Parameters
      case 96: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 114: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 101: // RangedType
        yylhs.value.build< RangedType::Ptr > ();
        break;

      case 125: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 124: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 111: // RuleReference
        yylhs.value.build< RuleReferenceAtom::Ptr > ();
        break;

      case 126: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 136: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 127: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 77: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 97: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 84: // FunctionParameters
      case 85: // MaybeFunctionParameters
      case 102: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 104: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 122: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 87: // Initializer
      case 137: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 105: // Boolean
      case 106: // String
      case 107: // BitNumber
      case 108: // IntegerNumber
      case 109: // FloatingNumber
      case 110: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 94: // Variable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 66: // "binary"
      case 67: // "hexadecimal"
      case 68: // "integer"
      case 69: // "rational"
      case 70: // "floating"
      case 71: // "string"
      case 72: // "identifier"
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
#line 318 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& fileName = filePath.substr( filePath.find_last_of( "/\\" ) + 1 );
      const std::string& name = fileName.substr( 0, fileName.rfind( "." ) );

      const auto specificationName = make< IdentifierNode >( yylhs.location, name );
      result = Ast::make< Specification >( yylhs.location, specificationName, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1246 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1254 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 334 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1262 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 338 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1270 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 342 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1278 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 350 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1288 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 356 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 364 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1316 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 380 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto identifier = yystack_[6].value.as< IdentifierNode::Ptr > ();

      auto function = Ast::make< FunctionDefinition >( yylhs.location, identifier, yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< Type::Ptr > () );
      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto& initializer : *initializers) {
           initializer->function()->setIdentifier( identifier );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 428 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1386 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1396 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1404 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 1412 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 456 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction( yylhs.location );

      auto arguments = Ast::make< Expressions >( yylhs.location );
      // TODO add `default` agent to arguments
      const auto program = Ast::make< DirectCallExpression >(
          yylhs.location, programDefinition->identifier(), arguments );

      const auto ruleReference = Ast::make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );

      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 473 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 490 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = Ast::make< IdentifierNode >( yylhs.location, std::string() );
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = Ast::make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1478 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 510 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = Ast::make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1490 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 522 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1500 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 528 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1510 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 538 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1518 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 542 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1526 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 550 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1534 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1542 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 566 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = Ast::make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1550 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1560 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 580 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< NodeList< IdentifierNode > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1570 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 590 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1578 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 594 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), unresolvedType );
  }
#line 1587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 603 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1597 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 619 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 623 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 631 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 635 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 639 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 643 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1663 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 659 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1671 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 667 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1679 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 675 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = Ast::make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1687 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 683 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 689 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 699 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 703 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 707 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 711 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1739 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 715 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1747 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 723 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1763 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1771 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1779 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 743 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 773 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 785 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1845 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 833 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 849 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto ruleName = Ast::make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
      yylhs.value.as< RuleReferenceAtom::Ptr > () = Ast::make< RuleReferenceAtom >( yylhs.location, ruleName );
  }
#line 1902 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 858 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1910 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 862 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1918 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 866 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1926 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 870 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1934 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 874 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1942 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 878 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1950 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 882 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1958 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 886 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1966 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1974 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1982 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1990 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 1998 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 910 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2006 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 914 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2014 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2022 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 922 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2030 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 926 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2038 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 930 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call power builtin
  }
#line 2046 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 934 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2054 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2062 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 942 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2070 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 946 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2086 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2094 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2102 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2110 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2118 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO add implies instruction
  }
#line 2126 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2134 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2142 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 995 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1003 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2169 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1009 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2179 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1019 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2187 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1023 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2196 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1032 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[1].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[3].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2206 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1042 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), arguments );
  }
#line 2215 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1047 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1055 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2231 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1063 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1071 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1079 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1087 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2264 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1092 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1101 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2281 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1105 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2289 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1109 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2297 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1113 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2305 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1117 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2313 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1121 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2321 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1125 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2329 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1129 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2337 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2345 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1137 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2353 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1145 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1151 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1161 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 2381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1169 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1173 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1181 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1189 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1193 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2421 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1197 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2429 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1205 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2439 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1211 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1221 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1229 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1237 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1245 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1249 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1257 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1261 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1269 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1277 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1283 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2534 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1290 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1296 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1307 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2563 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1311 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1319 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2581 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1325 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2591 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1335 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 2599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1343 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2607 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2611 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -164;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      -1,    61,     4,   -37,   -61,   -61,   -61,   -61,   -61,  -164,
    -164,    61,  -164,  -164,  -164,  -164,  -164,  -164,   604,  -164,
    -164,   -21,    -5,   -21,     1,   659,  -164,     9,  -164,  -164,
    -164,   -61,   659,   -61,  -164,  -164,  -164,   659,   659,   659,
     439,   494,   -13,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
      19,    15,    30,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,   969,  -164,  -164,  -164,    44,  -164,  -164,  -164,
    -164,  -164,   -61,    48,    66,   -36,   -61,   439,  1209,   130,
     -61,    65,    99,   748,   101,  -164,  -164,  -164,   659,   939,
    -164,   999,    50,  -164,   604,  -164,   549,  -164,   659,   659,
     659,   659,   659,   659,   659,   659,   659,   659,   659,   659,
     659,   659,   659,   659,   659,   659,  -164,     0,   -61,   -61,
     372,   -61,    68,    69,   -32,  -164,  -164,  -164,  -164,  -164,
    1029,  -164,  -164,   -61,   659,   659,   659,  1059,  -164,   659,
     659,  -164,   659,  -164,  -164,  1209,     7,   -15,  1299,  1324,
    1269,    37,    37,  1343,   121,   121,    75,    75,    75,  -164,
    1209,  1343,   121,   121,  1209,  -164,   -61,    84,  -164,    55,
     372,   372,  -164,   -61,   -61,   372,   -39,   659,   659,    86,
     372,   372,    81,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,  -164,  -164,  -164,   103,   -61,   -61,   -61,   659,
    -164,   879,   817,   909,    30,    10,  1089,  1209,  -164,  -164,
     659,  -164,   -61,  -164,   108,   304,   107,   134,  -164,  -164,
    -164,   783,   849,   317,   336,   659,   372,  -164,   146,  -164,
      13,  1119,   659,   659,   659,  -164,  -164,  -164,  1209,  -164,
    -164,  -164,  -164,   659,   659,   372,   116,  -164,  -164,  1209,
    -164,   119,   157,  -164,   -61,   659,   659,  -164,  1209,  -164,
     683,   713,   143,   384,   659,   124,  -164,  -164,  1239,   372,
     372,   372,   123,   125,  1149,   384,   132,  1179,   604,   659,
    -164,  -164,  -164,   372,   372,   372,  -164,  -164,  -164,   136,
    -164,  -164,  -164,  -164
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
      10,     2,     3,    12,     4,     6,     5,     1,    29,    32,
      21,    40,     0,    40,     0,   151,   150,     0,   147,   148,
       9,     0,     0,     0,    59,    61,    60,     0,     0,     0,
       0,     0,     0,    63,    64,    65,    67,    66,    62,    27,
      28,     0,   106,    77,    57,    58,    56,    52,    53,    54,
      55,    51,    23,    74,    76,    75,     0,    69,    70,    71,
      72,    73,     0,     0,     0,     0,    20,     0,   152,     0,
       0,    36,     0,     0,     0,    97,    79,    80,     0,     0,
      99,   102,     0,    68,     0,    22,     0,   107,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,     0,     0,     0,
       0,     0,    19,     0,    45,    18,    41,    42,    43,    44,
       0,     7,   149,     0,     0,     0,     0,     0,    78,     0,
       0,   100,     0,    26,   104,   102,     0,    95,    93,    94,
      96,    81,    82,    88,    89,    90,    83,    84,    85,    86,
      24,    87,    91,    92,    25,    39,     0,     0,    34,     0,
       0,     0,   126,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   144,   146,   112,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,     0,     0,     0,     0,     0,
      35,     0,     0,     0,     0,     0,     0,   101,   103,    37,
       0,    31,     0,   125,     0,     0,     0,     0,   137,   143,
     145,     0,     0,     0,     0,     0,     0,    17,    16,    50,
       0,     0,     0,     0,     0,   108,   105,    98,    30,    33,
     141,   124,   139,     0,     0,     0,     0,   138,   140,   142,
     113,     0,    14,    46,     0,    47,     0,   110,   109,   111,
       0,     0,   127,     0,     0,     0,    11,    49,     0,     0,
       0,     0,     0,     0,     0,   134,     0,     0,    29,    48,
     135,   136,   128,     0,     0,     0,   133,   129,    15,     0,
     130,   131,   132,    13
  };

  const short int
  Parser::yypgoto_[] =
  {
    -164,  -164,   105,   177,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,    95,  -164,   -85,  -164,  -164,    24,  -164,   -27,  -164,
     171,   -99,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,  -164,  -164,  -164,  -164,   -25,  -164,  -164,  -164,
     -95,    -9,  -164,   -12,    11,  -164,  -164,  -164,  -164,    29,
    -163,  -164,  -164,  -164,  -164,   -79,  -164,  -164,  -164,  -164,
    -164,  -164,  -164,   126,  -164,  -164,  -164
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     9,    10,    11,    12,   266,   252,   122,   123,
      13,    49,    50,    51,    14,    15,    52,   169,    82,   117,
      73,   125,   126,   127,   128,   129,   230,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      92,    97,    66,    67,    68,    69,    70,    71,    16,   213,
     214,   185,   186,   187,   275,   276,   188,   189,   190,   191,
     192,   193,   194,    26,    27,    28,    29
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      78,   146,     1,   179,    17,   120,    84,    83,   215,    18,
     198,    19,    85,    86,    87,    89,    91,   223,   224,   167,
     199,    72,   195,   121,   102,   103,   104,    20,    21,    22,
      23,    24,    25,    19,   200,    19,    74,   105,   106,   107,
     108,   109,   110,   165,   205,   116,   112,   113,   114,    76,
     208,   166,   130,   236,    79,    81,   253,    81,   142,    93,
      80,   142,    95,   137,   254,     3,     4,     5,     6,     7,
      94,   145,    96,   147,   148,   149,   150,   151,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   107,   108,   109,   110,   141,    81,   227,   228,   229,
     124,   142,   211,   115,    25,     8,   212,   118,   182,   201,
     202,   203,   119,   133,   145,   206,   134,   207,   136,   170,
     240,   171,   196,   172,   173,   210,   174,   175,   197,   176,
     177,   183,   110,   178,     3,     4,     5,     6,     7,   209,
      88,   225,   124,   168,   226,   124,   216,   217,   243,   184,
     179,   244,   221,   222,   180,   267,   251,   124,   182,   182,
     102,   103,   263,   182,   219,   264,   265,   271,   182,   182,
     278,   283,   181,   284,   231,   107,   108,   109,   110,   287,
      19,   183,   183,   293,   131,   238,   183,   220,    30,   143,
      81,   183,   183,   289,    75,   235,   286,    81,    81,     0,
     249,     0,   182,   182,   218,     0,   132,   257,   258,   259,
       0,   182,   182,     0,   182,     0,     0,     0,   260,   261,
     124,   124,   124,     0,     0,   183,   183,     0,     0,     0,
     155,   268,     0,   182,   183,   183,   239,   183,   274,   277,
       0,     0,     0,   241,   241,     0,     0,     0,     0,     0,
     274,     0,   241,   241,   155,   250,   183,   182,   182,   182,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   182,   182,   182,   262,     0,     0,     0,   124,     0,
     183,   183,   183,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   183,   183,   183,     0,   280,   281,
     282,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   290,   291,   292,   170,     0,   171,   242,   172,
     173,     0,   174,   175,     0,   176,   177,     0,   170,   178,
     171,     0,   172,   173,     0,   174,   175,     0,   176,   177,
       0,     0,   178,     0,     0,     0,   179,   170,     0,   171,
     180,   172,   173,     0,   174,   175,     0,   176,   177,   179,
       0,   178,     0,   180,   247,     0,     0,     0,   181,     0,
       0,     0,     0,     0,     0,     0,    19,     0,   179,     0,
       0,   181,   180,   170,     0,   171,     0,   172,   173,    19,
     174,   175,     0,   176,   177,     0,     0,   178,     0,     0,
     181,   248,    31,     0,     0,     0,    32,     0,    19,     0,
       0,   272,     0,    33,   179,    34,    35,    36,   180,     0,
       0,     0,    37,    38,    39,     0,    77,     0,    41,     0,
       0,     0,     0,   273,    42,     0,   181,     0,     0,     0,
       0,     0,     0,     0,    19,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48,    19,    31,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,    33,     0,
      34,    35,    36,     0,     0,     0,     0,    37,    38,    39,
       0,    77,     0,    41,     0,     0,     0,     0,     0,    42,
       0,     0,     0,    88,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,    19,    31,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,    33,     0,    34,    35,    36,     0,     0,
       0,     0,    37,    38,    39,     0,    77,     0,    41,    90,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48,    19,    31,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,    33,     0,
      34,    35,    36,     0,     0,     0,     0,    37,    38,    39,
       0,    77,   144,    41,     0,     0,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    43,    44,    45,    46,    47,
      48,    19,    31,     0,     0,     0,    32,     0,     0,     0,
       0,     0,     0,    33,     0,    34,    35,    36,     0,     0,
       0,     0,    37,    38,    39,     0,    40,     0,    41,     0,
       0,     0,     0,     0,    42,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      43,    44,    45,    46,    47,    48,    19,    31,     0,     0,
       0,    32,     0,     0,     0,     0,     0,     0,    33,     0,
      34,    35,    36,     0,     0,     0,     0,    37,    38,    39,
     269,    77,     0,    41,     0,     0,     0,     0,     0,    42,
       0,     0,     0,     0,     0,     0,     0,    98,    99,   100,
     101,     0,   102,   103,   104,    43,    44,    45,    46,    47,
      48,    19,     0,   270,     0,   105,   106,   107,   108,   109,
     110,     0,     0,     0,   112,   113,   114,    98,    99,   100,
     101,     0,   102,   103,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,   107,   108,   109,
     110,   135,     0,     0,   112,   113,   114,     0,     0,     0,
       0,     0,    98,    99,   100,   101,     0,   102,   103,   104,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     105,   106,   107,   108,   109,   110,   245,     0,     0,   112,
     113,   114,     0,     0,     0,     0,     0,    98,    99,   100,
     101,     0,   102,   103,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   105,   106,   107,   108,   109,
     110,   233,     0,     0,   112,   113,   114,     0,     0,     0,
       0,    98,    99,   100,   101,     0,   102,   103,   104,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   105,
     106,   107,   108,   109,   110,   246,     0,     0,   112,   113,
     114,     0,     0,    98,    99,   100,   101,     0,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,   232,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,   234,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,   138,     0,     0,     0,     0,     0,     0,     0,
     139,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,   111,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,   140,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,   138,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,   204,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,     0,     0,   237,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   255,   107,   108,   109,   110,   256,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,     0,     0,     0,     0,     0,   285,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,     0,     0,     0,     0,   288,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     112,   113,   114,    98,    99,   100,   101,     0,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   279,   107,   108,   109,   110,     0,     0,     0,
     112,   113,   114,    98,    99,   100,     0,     0,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,     0,     0,
     112,   113,   114,    98,     0,   100,     0,     0,   102,   103,
     104,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   105,   106,   107,   108,   109,   110,     0,    98,     0,
     112,   113,   114,   102,   103,   104,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   105,   106,   107,   108,
     109,   110,   102,   103,     0,   112,   113,   114,     0,     0,
       0,     0,     0,     0,     0,   105,   106,   107,   108,   109,
     110,     0,     0,     0,     0,   113,   114
  };

  const short int
  Parser::yycheck_[] =
  {
      25,    96,     3,    42,     0,    41,    33,    32,   171,    46,
      42,    72,    37,    38,    39,    40,    41,   180,   181,   118,
      52,    42,   121,    59,    39,    40,    41,     3,     4,     5,
       6,     7,     8,    72,   133,    72,    41,    52,    53,    54,
      55,    56,    57,    43,   139,    72,    61,    62,    63,    48,
      43,    51,    77,    43,    45,    31,    43,    33,    51,    72,
      51,    51,    47,    88,    51,     4,     5,     6,     7,     8,
      51,    96,    42,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,    54,    55,    56,    57,    45,    72,   196,   197,   198,
      76,    51,    47,    59,    80,    44,    51,    59,   120,   134,
     135,   136,    46,    48,   139,   140,    17,   142,    17,    11,
      12,    13,    54,    15,    16,    41,    18,    19,    59,    21,
      22,   120,    57,    25,     4,     5,     6,     7,     8,   166,
      54,    60,   118,   119,    41,   121,   173,   174,    41,   120,
      42,    17,   177,   178,    46,   254,    10,   133,   170,   171,
      39,    40,    46,   175,   176,    46,     9,    24,   180,   181,
      46,    48,    64,    48,   199,    54,    55,    56,    57,    47,
      72,   170,   171,    47,    79,   210,   175,   176,    11,    94,
     166,   180,   181,   278,    23,   204,   275,   173,   174,    -1,
     225,    -1,   214,   215,   175,    -1,    80,   232,   233,   234,
      -1,   223,   224,    -1,   226,    -1,    -1,    -1,   243,   244,
     196,   197,   198,    -1,    -1,   214,   215,    -1,    -1,    -1,
     255,   256,    -1,   245,   223,   224,   212,   226,   263,   264,
      -1,    -1,    -1,   214,   215,    -1,    -1,    -1,    -1,    -1,
     275,    -1,   223,   224,   279,   226,   245,   269,   270,   271,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   283,   284,   285,   245,    -1,    -1,    -1,   254,    -1,
     269,   270,   271,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   283,   284,   285,    -1,   269,   270,
     271,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   283,   284,   285,    11,    -1,    13,    14,    15,
      16,    -1,    18,    19,    -1,    21,    22,    -1,    11,    25,
      13,    -1,    15,    16,    -1,    18,    19,    -1,    21,    22,
      -1,    -1,    25,    -1,    -1,    -1,    42,    11,    -1,    13,
      46,    15,    16,    -1,    18,    19,    -1,    21,    22,    42,
      -1,    25,    -1,    46,    47,    -1,    -1,    -1,    64,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    72,    -1,    42,    -1,
      -1,    64,    46,    11,    -1,    13,    -1,    15,    16,    72,
      18,    19,    -1,    21,    22,    -1,    -1,    25,    -1,    -1,
      64,    65,    18,    -1,    -1,    -1,    22,    -1,    72,    -1,
      -1,    27,    -1,    29,    42,    31,    32,    33,    46,    -1,
      -1,    -1,    38,    39,    40,    -1,    42,    -1,    44,    -1,
      -1,    -1,    -1,    49,    50,    -1,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    18,    -1,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      31,    32,    33,    -1,    -1,    -1,    -1,    38,    39,    40,
      -1,    42,    -1,    44,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    54,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    31,    32,    33,    -1,    -1,
      -1,    -1,    38,    39,    40,    -1,    42,    -1,    44,    45,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    18,    -1,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      31,    32,    33,    -1,    -1,    -1,    -1,    38,    39,    40,
      -1,    42,    43,    44,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    66,    67,    68,    69,    70,
      71,    72,    18,    -1,    -1,    -1,    22,    -1,    -1,    -1,
      -1,    -1,    -1,    29,    -1,    31,    32,    33,    -1,    -1,
      -1,    -1,    38,    39,    40,    -1,    42,    -1,    44,    -1,
      -1,    -1,    -1,    -1,    50,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      66,    67,    68,    69,    70,    71,    72,    18,    -1,    -1,
      -1,    22,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
      31,    32,    33,    -1,    -1,    -1,    -1,    38,    39,    40,
      17,    42,    -1,    44,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    -1,    39,    40,    41,    66,    67,    68,    69,    70,
      71,    72,    -1,    20,    -1,    52,    53,    54,    55,    56,
      57,    -1,    -1,    -1,    61,    62,    63,    34,    35,    36,
      37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    23,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36,    37,    -1,    39,    40,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      52,    53,    54,    55,    56,    57,    23,    -1,    -1,    61,
      62,    63,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    -1,    39,    40,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    24,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    -1,    39,    40,    41,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    52,
      53,    54,    55,    56,    57,    26,    -1,    -1,    61,    62,
      63,    -1,    -1,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    28,    -1,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    30,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    59,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    58,    -1,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    34,    35,    36,    37,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    -1,    -1,
      61,    62,    63,    34,    -1,    36,    -1,    -1,    39,    40,
      41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    52,    53,    54,    55,    56,    57,    -1,    34,    -1,
      61,    62,    63,    39,    40,    41,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,
      56,    57,    39,    40,    -1,    61,    62,    63,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    53,    54,    55,    56,
      57,    -1,    -1,    -1,    -1,    62,    63
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    77,     4,     5,     6,     7,     8,    44,    78,
      79,    80,    81,    86,    90,    91,   124,     0,    46,    72,
      92,    92,    92,    92,    92,    92,   139,   140,   141,   142,
      79,    18,    22,    29,    31,    32,    33,    38,    39,    40,
      42,    44,    50,    66,    67,    68,    69,    70,    71,    87,
      88,    89,    92,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   118,   119,   120,   121,
     122,   123,    42,    96,    41,    96,    48,    42,   112,    45,
      51,    92,    94,   112,    94,   112,   112,   112,    54,   112,
      45,   112,   116,    72,    51,    47,    42,   117,    34,    35,
      36,    37,    39,    40,    41,    52,    53,    54,    55,    56,
      57,    59,    61,    62,    63,    59,    94,    95,    59,    46,
      41,    59,    84,    85,    92,    97,    98,    99,   100,   101,
     112,    78,   139,    48,    17,    23,    17,   112,    43,    51,
      58,    45,    51,    87,    43,   112,   116,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,    43,    51,    97,    92,    93,
      11,    13,    15,    16,    18,    19,    21,    22,    25,    42,
      46,    64,   119,   120,   125,   127,   128,   129,   132,   133,
     134,   135,   136,   137,   138,    97,    54,    59,    42,    52,
      97,   112,   112,   112,    43,   116,   112,   112,    43,    94,
      41,    47,    51,   125,   126,   126,    94,    94,   125,   119,
     120,   112,   112,   126,   126,    60,    41,    97,    97,    97,
     102,   112,    28,    24,    30,   117,    43,    45,   112,    92,
      12,   125,    14,    41,    17,    23,    26,    47,    65,   112,
     125,    10,    83,    43,    51,    53,    58,   112,   112,   112,
     112,   112,   125,    46,    46,     9,    82,    97,   112,    17,
      20,    24,    27,    49,   112,   130,   131,   112,    46,    53,
     125,   125,   125,    48,    48,    48,   131,    47,    47,    89,
     125,   125,   125,    47
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    76,    77,    78,    78,    78,    78,    79,    79,    80,
      80,    81,    81,    82,    82,    83,    83,    84,    84,    85,
      85,    86,    86,    87,    87,    87,    88,    88,    89,    89,
      90,    91,    92,    93,    93,    94,    94,    95,    95,    96,
      96,    97,    97,    97,    97,    98,    99,   100,   101,   102,
     102,   103,   103,   103,   103,   103,   103,   103,   103,   104,
     105,   105,   106,   107,   107,   108,   109,   110,   111,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   114,   115,
     115,   116,   116,   117,   117,   118,   119,   119,   120,   121,
     122,   123,   124,   124,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   126,   126,   127,   128,   128,   129,
     130,   130,   130,   131,   131,   132,   133,   134,   135,   135,
     136,   136,   137,   138,   138,   138,   138,   139,   139,   140,
     140,   141,   142
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
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     5,     2,
       3,     3,     1,     3,     2,     5,     1,     2,     5,     6,
       6,     6,     5,     7,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     4,     6,     6,
       3,     3,     3,     2,     1,     6,     6,     2,     3,     3,
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
  "\"skip\"", "\"let\"", "\"in\"", "\"forall\"", "\"iterate\"", "\"do\"",
  "\"call\"", "\"if\"", "\"then\"", "\"else\"", "\"case\"", "\"of\"",
  "\"default\"", "\"holds\"", "\"exists\"", "\"with\"", "\"undef\"",
  "\"false\"", "\"true\"", "\"and\"", "\"or\"", "\"xor\"", "\"implies\"",
  "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"",
  "\"*\"", "\"/\"", "\"%\"", "\"^\"", "\"..\"", "\"->\"", "\":=\"",
  "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"floating\"",
  "\"string\"", "\"identifier\"", "UPLUS", "UMINUS", "CALL_WITHOUT_ARGS",
  "$accept", "Specification", "Definition", "AttributedDefinition",
  "Definitions", "FunctionDefinition", "MaybeInitially", "MaybeDefined",
  "FunctionParameters", "MaybeFunctionParameters",
  "ProgramFunctionDefinition", "Initializer", "Initializers",
  "MaybeInitializers", "DerivedDefinition", "EnumerationDefinition",
  "Identifier", "Identifiers", "Variable", "Parameters", "MaybeParameters",
  "Type", "BasicType", "ComposedType", "FixedSizedType", "RangedType",
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
       0,   317,   317,   329,   333,   337,   341,   349,   355,   363,
     369,   379,   395,   403,   407,   415,   419,   427,   433,   443,
     447,   455,   472,   489,   498,   509,   521,   527,   537,   541,
     549,   557,   565,   573,   579,   589,   593,   602,   608,   618,
     622,   630,   634,   638,   642,   650,   658,   666,   674,   682,
     688,   698,   702,   706,   710,   714,   718,   722,   726,   734,
     742,   747,   756,   772,   784,   800,   816,   832,   848,   857,
     861,   865,   869,   873,   877,   881,   885,   889,   897,   901,
     905,   909,   913,   917,   921,   925,   929,   933,   937,   941,
     945,   949,   953,   957,   961,   965,   969,   973,   981,   989,
     994,  1002,  1008,  1018,  1022,  1031,  1041,  1046,  1054,  1062,
    1070,  1078,  1086,  1091,  1100,  1104,  1108,  1112,  1116,  1120,
    1124,  1128,  1132,  1136,  1144,  1150,  1160,  1168,  1172,  1180,
    1188,  1192,  1196,  1204,  1210,  1220,  1228,  1236,  1244,  1248,
    1256,  1260,  1268,  1276,  1282,  1289,  1295,  1306,  1310,  1318,
    1324,  1334,  1342
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
#line 3426 "GrammarParser.cpp" // lalr1.cc:1167
#line 1348 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
