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

      case 99: // BasicType
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

      case 100: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 121: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 128: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 79: // Definition
      case 80: // AttributedDefinition
        value.move< Definition::Ptr > (that.value);
        break;

      case 81: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 91: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 119: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 92: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 123: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 84: // MaybeDefined
      case 104: // Atom
      case 113: // Term
      case 114: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 142: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 117: // Terms
      case 118: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 101: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 133: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 82: // FunctionDefinition
      case 87: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 93: // Identifier
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

      case 116: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 94: // Identifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 83: // MaybeInitially
      case 89: // Initializers
      case 90: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 96: // Parameters
      case 97: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 115: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 102: // RangedType
        value.move< RangedType::Ptr > (that.value);
        break;

      case 125: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 124: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 112: // RuleReference
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

      case 78: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 98: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 103: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 105: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 122: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // Initializer
      case 137: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 106: // Boolean
      case 107: // String
      case 108: // BitNumber
      case 109: // IntegerNumber
      case 110: // FloatingNumber
      case 111: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 95: // Variable
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
      case 139: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 140: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 141: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 99: // BasicType
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

      case 100: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 121: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 128: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 79: // Definition
      case 80: // AttributedDefinition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 81: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 91: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 119: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 92: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 123: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 84: // MaybeDefined
      case 104: // Atom
      case 113: // Term
      case 114: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 142: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 117: // Terms
      case 118: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 101: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 133: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 82: // FunctionDefinition
      case 87: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 93: // Identifier
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

      case 116: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 94: // Identifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 83: // MaybeInitially
      case 89: // Initializers
      case 90: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 96: // Parameters
      case 97: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 115: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 102: // RangedType
        value.copy< RangedType::Ptr > (that.value);
        break;

      case 125: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 124: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 112: // RuleReference
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

      case 78: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 98: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 103: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 105: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 122: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // Initializer
      case 137: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 106: // Boolean
      case 107: // String
      case 108: // BitNumber
      case 109: // IntegerNumber
      case 110: // FloatingNumber
      case 111: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 95: // Variable
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
      case 139: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 140: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 141: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 99: // BasicType
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

      case 100: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 121: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 128: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 79: // Definition
      case 80: // AttributedDefinition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 81: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 91: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 119: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 92: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 123: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 84: // MaybeDefined
      case 104: // Atom
      case 113: // Term
      case 114: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 142: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 117: // Terms
      case 118: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 101: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 133: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 82: // FunctionDefinition
      case 87: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 93: // Identifier
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

      case 116: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 94: // Identifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 83: // MaybeInitially
      case 89: // Initializers
      case 90: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 96: // Parameters
      case 97: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 115: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 102: // RangedType
        yylhs.value.build< RangedType::Ptr > ();
        break;

      case 125: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 124: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 112: // RuleReference
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

      case 78: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 98: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 103: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 105: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 122: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 88: // Initializer
      case 137: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 106: // Boolean
      case 107: // String
      case 108: // BitNumber
      case 109: // IntegerNumber
      case 110: // FloatingNumber
      case 111: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 95: // Variable
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
#line 318 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& fileName = filePath.substr( filePath.find_last_of( "/\\" ) + 1 );
      const std::string& name = fileName.substr( 0, fileName.rfind( "." ) );

      const auto specificationName = make< IdentifierNode >( yylhs.location, name );
      result = Ast::make< Specification >( yylhs.location, specificationName, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1243 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1251 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 334 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1259 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 338 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1267 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 342 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1275 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 350 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 356 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 364 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1313 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1333 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 420 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 428 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 1409 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1430 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1447 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1460 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 510 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = Ast::make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 522 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 528 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 538 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 542 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 550 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 566 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = Ast::make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 580 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< NodeList< IdentifierNode > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 590 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1575 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 594 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), unresolvedType );
  }
#line 1584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 603 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1594 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 619 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1612 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 623 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1620 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 631 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1628 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 635 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 639 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 643 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 659 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 667 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 675 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = Ast::make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 683 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1694 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 689 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1704 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 699 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1712 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 703 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1720 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 707 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 711 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1736 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 715 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1744 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 723 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1760 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1768 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1776 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 743 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1785 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 766 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 771 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 789 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 798 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 807 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto ruleName = Ast::make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
      yylhs.value.as< RuleReferenceAtom::Ptr > () = Ast::make< RuleReferenceAtom >( yylhs.location, ruleName );
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 820 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 824 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 828 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1889 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 836 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 840 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 844 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 848 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1929 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 856 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1937 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 860 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 864 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 868 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 1961 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 872 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 1969 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 876 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1977 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 880 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 1985 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 884 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 1993 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 888 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2001 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 892 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call power builtin
  }
#line 2009 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 896 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2017 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 900 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2025 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 904 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2033 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 908 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 912 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2049 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2057 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 920 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2065 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2073 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2081 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO add implies instruction
  }
#line 2089 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2097 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2105 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2114 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2122 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2132 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 972 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2142 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2150 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 995 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), arguments );
  }
#line 2168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1000 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1008 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2184 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1016 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2192 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2200 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1032 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2208 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1040 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1045 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2226 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1054 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1058 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1062 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2250 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2258 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1070 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2274 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1078 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2298 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2316 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1104 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2326 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1114 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 2334 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1122 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2342 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1126 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2350 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2358 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1142 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2366 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1146 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1158 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2392 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1164 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1174 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2410 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1182 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2418 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1190 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2426 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1198 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2434 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1202 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1210 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1214 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2458 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1222 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2466 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1230 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2476 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1236 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1243 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1249 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2508 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1260 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2516 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1264 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2524 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1272 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2534 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1278 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1288 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 2552 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1296 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2560 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2564 "GrammarParser.cpp" // lalr1.cc:859
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
       5,    99,    11,   -42,   -52,   -52,   -52,   -52,   -52,  -164,
    -164,    99,  -164,  -164,  -164,  -164,  -164,  -164,   675,  -164,
    -164,   -20,    -7,   -20,    16,   730,  -164,   -44,  -164,  -164,
    -164,   -52,   730,   -52,  -164,  -164,  -164,   730,   730,   730,
     400,   510,   -23,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
      46,    26,    60,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,   977,  -164,  -164,  -164,    47,  -164,  -164,  -164,
    -164,  -164,   -52,    50,    73,   -26,   -52,   565,  1217,   174,
     -52,    75,   115,   786,   116,  -164,  -164,  -164,  -164,   730,
    1007,    83,     3,  -164,  1037,   -16,  -164,   675,  -164,   620,
    -164,   730,   730,   730,   730,   730,   730,   730,   730,   730,
     730,   730,   730,   730,   730,   730,   730,   730,   730,  -164,
      12,   -52,   -52,   388,   -52,    81,    77,    -5,  -164,  -164,
    -164,  -164,  -164,  1007,  -164,  -164,   -52,   730,   730,   730,
    1067,  -164,  -164,  -164,   730,   730,  -164,  -164,  1217,  1351,
    1307,  1332,  1277,    14,    14,   226,    59,    59,    82,    82,
      82,  -164,  1217,   226,    59,    59,  1217,  -164,   -52,   106,
    -164,     1,   388,   388,  -164,   -52,   -52,   388,   -40,   730,
     730,    96,   388,   388,    80,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,  -164,  -164,  -164,  -164,  -164,   118,   -52,   -52,
     -52,   730,  -164,   917,   855,   947,    60,  1217,  1097,  -164,
     730,  -164,   -52,  -164,   109,   300,   119,   144,  -164,  -164,
    -164,   821,   887,   336,   352,   730,   388,  -164,   154,  -164,
      86,  1127,   730,   730,   730,  -164,  -164,  1217,  -164,  -164,
    -164,  -164,   730,   730,   388,   120,  -164,  -164,  1217,  -164,
     123,   156,  -164,   -52,   730,   730,  -164,  1217,  -164,     4,
     751,   146,   455,   730,   125,  -164,  -164,  1247,   388,   388,
     388,   124,   127,  1157,   455,   130,  1187,   675,   730,  -164,
    -164,  -164,   388,   388,   388,  -164,  -164,  -164,   138,  -164,
    -164,  -164,  -164
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
       0,    36,     0,     0,     0,    98,    79,    81,   105,     0,
     103,    74,     0,   100,   103,     0,    68,     0,    22,     0,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    38,
       0,     0,     0,     0,     0,    19,     0,    45,    18,    41,
      42,    43,    44,     0,     7,   149,     0,     0,     0,     0,
       0,    80,    78,   104,     0,     0,   101,    26,   103,    96,
      94,    95,    97,    82,    83,    89,    90,    91,    84,    85,
      86,    87,    24,    88,    92,    93,    25,    39,     0,     0,
      34,     0,     0,     0,   126,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   144,   146,   112,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,     0,     0,     0,
       0,     0,    35,     0,     0,     0,     0,   102,     0,    37,
       0,    31,     0,   125,     0,     0,     0,     0,   137,   143,
     145,     0,     0,     0,     0,     0,     0,    17,    16,    50,
       0,     0,     0,     0,     0,   108,    99,    30,    33,   141,
     124,   139,     0,     0,     0,     0,   138,   140,   142,   113,
       0,    14,    46,     0,    47,     0,   110,   109,   111,     0,
       0,   127,     0,     0,     0,    11,    49,     0,     0,     0,
       0,     0,     0,     0,   134,     0,     0,    29,    48,   135,
     136,   128,     0,     0,     0,   133,   129,    15,     0,   130,
     131,   132,    13
  };

  const short int
  Parser::yypgoto_[] =
  {
    -164,  -164,   110,   177,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,    94,  -164,   -85,  -164,  -164,    22,  -164,   -28,  -164,
     170,  -103,  -164,  -164,  -164,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,  -164,  -164,  -164,  -164,   -25,   -39,  -164,  -164,
     153,   -50,   -13,    63,  -164,  -164,  -164,  -164,    28,  -163,
    -164,  -164,  -164,  -164,   -79,  -164,  -164,  -164,  -164,  -164,
    -164,  -164,   126,  -164,  -164,  -164
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     9,    10,    11,    12,   265,   251,   125,   126,
      13,    49,    50,    51,    14,    15,    52,   171,    82,   120,
      73,   128,   129,   130,   131,   132,   230,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      92,    66,    67,    68,    69,    70,    71,    16,   213,   214,
     187,   188,   189,   274,   275,   190,   191,   192,   193,   194,
     195,   196,    26,    27,    28,    29
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      78,    91,   100,    79,   181,    84,    18,    83,     1,    80,
     215,    17,    85,    86,    87,    90,    94,   123,   169,   223,
     224,   197,    19,   268,    72,    20,    21,    22,    23,    24,
      25,   146,    19,   202,    19,   124,    74,   144,    91,   200,
     101,   102,   103,   104,   119,   105,   106,   107,   143,   201,
     211,    96,   133,    81,   212,    81,   144,   167,   108,   109,
     110,   111,   112,   113,   140,   168,    76,   115,   116,   117,
     110,   111,   112,   113,   148,    98,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,    81,   227,   228,   229,   127,    97,
     105,   106,    25,     3,    99,     4,     5,     6,   118,     7,
     184,   121,   203,   204,   205,   110,   111,   112,   113,   207,
     208,   122,   172,   239,   173,   136,   174,   175,   142,   176,
     177,   252,   178,   179,   137,   139,   180,   198,   199,   253,
     209,   113,   225,   127,   170,     8,   127,   216,   217,   210,
     266,   186,    89,   181,   221,   222,   235,   182,   127,   184,
     184,   226,   242,   243,   184,   219,   250,   264,   262,   184,
     184,   263,   270,   277,   282,   183,   231,   283,     3,   286,
       4,     5,     6,    19,     7,   237,   185,   292,    30,   134,
      81,   147,   288,    75,    95,   285,     0,    81,    81,     0,
     248,   184,   184,     0,     0,   218,   135,   256,   257,   258,
     184,   184,     0,   184,     0,     0,     0,   259,   260,     0,
     127,   127,   127,     0,     0,     0,     0,     0,     0,   157,
     267,   184,     0,     0,   238,   185,   185,   273,   276,     0,
     185,   220,   240,   240,     0,   185,   185,     0,     0,   273,
       0,   240,   240,   157,   249,   184,   184,   184,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   105,   106,   184,
     184,   184,   261,     0,     0,   127,     0,   185,   185,     0,
     108,   109,   110,   111,   112,   113,   185,   185,     0,   185,
     116,   117,     0,     0,     0,     0,   279,   280,   281,     0,
       0,     0,     0,     0,     0,     0,     0,   185,     0,     0,
     289,   290,   291,   172,     0,   173,   241,   174,   175,     0,
     176,   177,     0,   178,   179,     0,     0,   180,     0,     0,
       0,   185,   185,   185,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   181,   185,   185,   185,   182,   172,
       0,   173,     0,   174,   175,     0,   176,   177,     0,   178,
     179,     0,     0,   180,     0,   172,   183,   173,     0,   174,
     175,     0,   176,   177,    19,   178,   179,     0,     0,   180,
     181,     0,     0,     0,   182,   246,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   181,     0,     0,     0,
     182,   172,   183,   173,     0,   174,   175,     0,   176,   177,
      19,   178,   179,     0,     0,   180,     0,     0,   183,   247,
      31,     0,     0,     0,    32,     0,    19,     0,     0,     0,
       0,    33,   181,    34,    35,    36,   182,     0,     0,     0,
      37,    38,    39,     0,    77,    88,    41,     0,     0,     0,
       0,     0,    42,     0,   183,     0,    89,     0,     0,     0,
       0,     0,    19,     0,     0,     0,     0,     0,    43,    44,
      45,    46,    47,    48,    19,    31,     0,     0,     0,    32,
       0,     0,     0,     0,   271,     0,    33,     0,    34,    35,
      36,     0,     0,     0,     0,    37,    38,    39,     0,    77,
       0,    41,     0,     0,     0,     0,   272,    42,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,    19,
      31,     0,     0,     0,    32,     0,     0,     0,     0,     0,
       0,    33,     0,    34,    35,    36,     0,     0,     0,     0,
      37,    38,    39,     0,    77,     0,    41,    93,     0,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    43,    44,
      45,    46,    47,    48,    19,    31,     0,     0,     0,    32,
       0,     0,     0,     0,     0,     0,    33,     0,    34,    35,
      36,     0,     0,     0,     0,    37,    38,    39,     0,    77,
       0,    41,     0,     0,     0,     0,     0,    42,     0,     0,
       0,    89,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,    19,
      31,     0,     0,     0,    32,     0,     0,     0,     0,     0,
       0,    33,     0,    34,    35,    36,     0,     0,     0,     0,
      37,    38,    39,     0,    77,    88,    41,     0,     0,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    43,    44,
      45,    46,    47,    48,    19,    31,     0,     0,     0,    32,
       0,     0,     0,     0,     0,     0,    33,     0,    34,    35,
      36,     0,     0,     0,     0,    37,    38,    39,     0,    40,
       0,    41,     0,     0,     0,     0,     0,    42,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    43,    44,    45,    46,    47,    48,    19,
      31,     0,     0,     0,    32,     0,     0,     0,     0,     0,
       0,    33,     0,    34,    35,    36,     0,     0,     0,     0,
      37,    38,    39,   269,    77,     0,    41,     0,     0,     0,
       0,     0,    42,     0,     0,     0,     0,   101,   102,   103,
     104,     0,   105,   106,   107,     0,     0,     0,    43,    44,
      45,    46,    47,    48,    19,   108,   109,   110,   111,   112,
     113,   138,     0,     0,   115,   116,   117,     0,     0,     0,
       0,     0,   101,   102,   103,   104,     0,   105,   106,   107,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     108,   109,   110,   111,   112,   113,   244,     0,     0,   115,
     116,   117,     0,     0,     0,     0,     0,   101,   102,   103,
     104,     0,   105,   106,   107,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   108,   109,   110,   111,   112,
     113,   233,     0,     0,   115,   116,   117,     0,     0,     0,
       0,   101,   102,   103,   104,     0,   105,   106,   107,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   108,
     109,   110,   111,   112,   113,   245,     0,     0,   115,   116,
     117,     0,     0,   101,   102,   103,   104,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,   232,     0,     0,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,     0,     0,   234,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,     0,     0,     0,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,     0,   114,     0,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,   141,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,     0,     0,     0,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,   145,     0,     0,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,   206,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,     0,     0,     0,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,     0,     0,   236,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,     0,     0,     0,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   254,   110,   111,   112,   113,   255,     0,     0,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,   284,     0,     0,
       0,   108,   109,   110,   111,   112,   113,     0,     0,     0,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,     0,     0,     0,     0,   287,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,     0,     0,     0,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,     0,     0,     0,
     115,   116,   117,   101,   102,   103,   104,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   278,   110,   111,   112,   113,     0,     0,     0,
     115,   116,   117,   101,   102,   103,     0,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,     0,     0,     0,
     115,   116,   117,   101,     0,   103,     0,     0,   105,   106,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   108,   109,   110,   111,   112,   113,     0,   101,     0,
     115,   116,   117,   105,   106,   107,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   108,   109,   110,   111,
     112,   113,   105,   106,   107,   115,   116,   117,     0,     0,
       0,     0,     0,     0,     0,   108,   109,   110,   111,   112,
     113,     0,     0,     0,   115,   116,   117
  };

  const short int
  Parser::yycheck_[] =
  {
      25,    40,    52,    47,    44,    33,    48,    32,     3,    53,
     173,     0,    37,    38,    39,    40,    41,    43,   121,   182,
     183,   124,    74,    19,    44,     3,     4,     5,     6,     7,
       8,    47,    74,   136,    74,    61,    43,    53,    77,    44,
      36,    37,    38,    39,    72,    41,    42,    43,    45,    54,
      49,    74,    77,    31,    53,    33,    53,    45,    54,    55,
      56,    57,    58,    59,    89,    53,    50,    63,    64,    65,
      56,    57,    58,    59,    99,    49,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,    72,   198,   199,   200,    76,    53,
      41,    42,    80,     4,    44,     6,     7,     8,    61,    10,
     123,    61,   137,   138,   139,    56,    57,    58,    59,   144,
     145,    48,    13,    14,    15,    50,    17,    18,    45,    20,
      21,    45,    23,    24,    19,    19,    27,    56,    61,    53,
     168,    59,    62,   121,   122,    46,   124,   175,   176,    43,
     253,   123,    56,    44,   179,   180,   206,    48,   136,   172,
     173,    43,    43,    19,   177,   178,    12,    11,    48,   182,
     183,    48,    26,    48,    50,    66,   201,    50,     4,    49,
       6,     7,     8,    74,    10,   210,   123,    49,    11,    79,
     168,    97,   277,    23,    41,   274,    -1,   175,   176,    -1,
     225,   214,   215,    -1,    -1,   177,    80,   232,   233,   234,
     223,   224,    -1,   226,    -1,    -1,    -1,   242,   243,    -1,
     198,   199,   200,    -1,    -1,    -1,    -1,    -1,    -1,   254,
     255,   244,    -1,    -1,   212,   172,   173,   262,   263,    -1,
     177,   178,   214,   215,    -1,   182,   183,    -1,    -1,   274,
      -1,   223,   224,   278,   226,   268,   269,   270,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    41,    42,   282,
     283,   284,   244,    -1,    -1,   253,    -1,   214,   215,    -1,
      54,    55,    56,    57,    58,    59,   223,   224,    -1,   226,
      64,    65,    -1,    -1,    -1,    -1,   268,   269,   270,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   244,    -1,    -1,
     282,   283,   284,    13,    -1,    15,    16,    17,    18,    -1,
      20,    21,    -1,    23,    24,    -1,    -1,    27,    -1,    -1,
      -1,   268,   269,   270,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    44,   282,   283,   284,    48,    13,
      -1,    15,    -1,    17,    18,    -1,    20,    21,    -1,    23,
      24,    -1,    -1,    27,    -1,    13,    66,    15,    -1,    17,
      18,    -1,    20,    21,    74,    23,    24,    -1,    -1,    27,
      44,    -1,    -1,    -1,    48,    49,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,
      48,    13,    66,    15,    -1,    17,    18,    -1,    20,    21,
      74,    23,    24,    -1,    -1,    27,    -1,    -1,    66,    67,
      20,    -1,    -1,    -1,    24,    -1,    74,    -1,    -1,    -1,
      -1,    31,    44,    33,    34,    35,    48,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    66,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      -1,    46,    -1,    -1,    -1,    -1,    51,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    47,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    45,    46,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    22,    44,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    54,    55,    56,    57,    58,
      59,    25,    -1,    -1,    63,    64,    65,    -1,    -1,    -1,
      -1,    -1,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    25,    -1,    -1,    63,
      64,    65,    -1,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    26,    -1,    -1,    63,    64,    65,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    28,    -1,    -1,    63,    64,
      65,    -1,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    30,    -1,    -1,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    32,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    61,    -1,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    60,    -1,    -1,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      63,    64,    65,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      63,    64,    65,    36,    37,    38,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      63,    64,    65,    36,    -1,    38,    -1,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    36,    -1,
      63,    64,    65,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    41,    42,    43,    63,    64,    65,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    63,    64,    65
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    78,     4,     6,     7,     8,    10,    46,    79,
      80,    81,    82,    87,    91,    92,   124,     0,    48,    74,
      93,    93,    93,    93,    93,    93,   139,   140,   141,   142,
      80,    20,    24,    31,    33,    34,    35,    40,    41,    42,
      44,    46,    52,    68,    69,    70,    71,    72,    73,    88,
      89,    90,    93,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   113,   114,   115,   116,   118,   119,   120,   121,
     122,   123,    44,    97,    43,    97,    50,    44,   113,    47,
      53,    93,    95,   113,    95,   113,   113,   113,    45,    56,
     113,   114,   117,    47,   113,   117,    74,    53,    49,    44,
     118,    36,    37,    38,    39,    41,    42,    43,    54,    55,
      56,    57,    58,    59,    61,    63,    64,    65,    61,    95,
      96,    61,    48,    43,    61,    85,    86,    93,    98,    99,
     100,   101,   102,   113,    79,   139,    50,    19,    25,    19,
     113,    45,    45,    45,    53,    60,    47,    88,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,    45,    53,    98,
      93,    94,    13,    15,    17,    18,    20,    21,    23,    24,
      27,    44,    48,    66,   119,   120,   125,   127,   128,   129,
     132,   133,   134,   135,   136,   137,   138,    98,    56,    61,
      44,    54,    98,   113,   113,   113,    45,   113,   113,    95,
      43,    49,    53,   125,   126,   126,    95,    95,   125,   119,
     120,   113,   113,   126,   126,    62,    43,    98,    98,    98,
     103,   113,    30,    26,    32,   118,    47,   113,    93,    14,
     125,    16,    43,    19,    25,    28,    49,    67,   113,   125,
      12,    84,    45,    53,    55,    60,   113,   113,   113,   113,
     113,   125,    48,    48,    11,    83,    98,   113,    19,    22,
      26,    29,    51,   113,   130,   131,   113,    48,    55,   125,
     125,   125,    50,    50,    50,   131,    49,    49,    90,   125,
     125,   125,    49
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    77,    78,    79,    79,    79,    79,    80,    80,    81,
      81,    82,    82,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    88,    89,    89,    90,    90,
      91,    92,    93,    94,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    98,    98,    99,   100,   101,   102,   103,
     103,   104,   104,   104,   104,   104,   104,   104,   104,   105,
     106,   106,   107,   108,   108,   109,   110,   111,   112,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   115,
     116,   116,   117,   117,   118,   118,   119,   119,   120,   121,
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
       3,     2,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     5,
       2,     3,     3,     1,     3,     2,     1,     2,     5,     6,
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
  "DirectCallExpression", "IndirectCallExpression",
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
     742,   747,   756,   765,   770,   779,   788,   797,   806,   815,
     819,   823,   827,   831,   835,   839,   843,   847,   855,   859,
     863,   867,   871,   875,   879,   883,   887,   891,   895,   899,
     903,   907,   911,   915,   919,   923,   927,   931,   935,   944,
     952,   957,   965,   971,   981,   985,   994,   999,  1007,  1015,
    1023,  1031,  1039,  1044,  1053,  1057,  1061,  1065,  1069,  1073,
    1077,  1081,  1085,  1089,  1097,  1103,  1113,  1121,  1125,  1133,
    1141,  1145,  1149,  1157,  1163,  1173,  1181,  1189,  1197,  1201,
    1209,  1213,  1221,  1229,  1235,  1242,  1248,  1259,  1263,  1271,
    1277,  1287,  1295
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
#line 3381 "GrammarParser.cpp" // lalr1.cc:1167
#line 1301 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
