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
      case 138: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 139: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 140: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 98: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 134: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 137: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 129: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 128: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 130: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 99: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 120: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 127: // ConditionalRule
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

      case 118: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 91: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 122: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 83: // MaybeDefined
      case 103: // Atom
      case 112: // Term
      case 113: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 141: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 116: // Terms
      case 117: // Arguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 100: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 132: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 81: // FunctionDefinition
      case 86: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 92: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
        break;

      case 119: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 133: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 131: // LetRule
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

      case 124: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 123: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 111: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 125: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 135: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 126: // SkipRule
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

      case 121: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 87: // Initializer
      case 136: // UpdateRule
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

      case 67: // "binary"
      case 68: // "hexadecimal"
      case 69: // "integer"
      case 70: // "rational"
      case 71: // "floating"
      case 72: // "string"
      case 73: // "identifier"
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
      case 138: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 139: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 140: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 98: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 134: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 137: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 129: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 128: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 130: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 99: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 120: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 127: // ConditionalRule
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

      case 118: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 91: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 122: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 83: // MaybeDefined
      case 103: // Atom
      case 112: // Term
      case 113: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 141: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 116: // Terms
      case 117: // Arguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 100: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 132: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 81: // FunctionDefinition
      case 86: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 92: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
        break;

      case 119: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 133: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 131: // LetRule
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

      case 124: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 123: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 111: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 125: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 135: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 126: // SkipRule
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

      case 121: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 87: // Initializer
      case 136: // UpdateRule
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

      case 67: // "binary"
      case 68: // "hexadecimal"
      case 69: // "integer"
      case 70: // "rational"
      case 71: // "floating"
      case 72: // "string"
      case 73: // "identifier"
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
      case 138: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 139: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 140: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 98: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 134: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 137: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 129: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 128: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 130: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 99: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 120: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 127: // ConditionalRule
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

      case 118: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 91: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 122: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 83: // MaybeDefined
      case 103: // Atom
      case 112: // Term
      case 113: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 141: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 116: // Terms
      case 117: // Arguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 100: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 132: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 81: // FunctionDefinition
      case 86: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 92: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
        break;

      case 119: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 133: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 131: // LetRule
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

      case 124: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 123: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 111: // RuleReference
        yylhs.value.build< RuleReferenceAtom::Ptr > ();
        break;

      case 125: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 135: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 126: // SkipRule
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

      case 121: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 87: // Initializer
      case 136: // UpdateRule
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

      case 67: // "binary"
      case 68: // "hexadecimal"
      case 69: // "integer"
      case 70: // "rational"
      case 71: // "floating"
      case 72: // "string"
      case 73: // "identifier"
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
#line 317 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& fileName = filePath.substr( filePath.find_last_of( "/\\" ) + 1 );
      const std::string& name = fileName.substr( 0, fileName.rfind( "." ) );

      const auto specificationName = make< IdentifierNode >( yylhs.location, name );
      result = Ast::make< Specification >( yylhs.location, specificationName, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1243 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 329 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1251 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 333 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1259 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 337 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1267 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 341 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1275 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 355 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 363 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 369 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1313 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 379 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 395 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 403 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 415 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 419 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 433 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 1409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 498 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = Ast::make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 521 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 527 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 537 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 549 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 557 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 565 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = Ast::make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 579 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< NodeList< IdentifierNode > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1575 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 593 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), unresolvedType );
  }
#line 1584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1594 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 618 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1612 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1620 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 630 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1628 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 642 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 658 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 666 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 674 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = Ast::make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 682 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1694 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 688 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1704 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 698 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1712 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 702 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1720 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 706 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1736 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 714 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1744 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 722 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1760 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1768 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1776 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 742 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1785 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 747 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 765 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::BINARY );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::HEXADECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 779 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > (), libstdhl::Type::DECIMAL );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 797 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 806 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto ruleName = Ast::make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
      yylhs.value.as< RuleReferenceAtom::Ptr > () = Ast::make< RuleReferenceAtom >( yylhs.location, ruleName );
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 815 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 819 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 823 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 1881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 827 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 1889 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 831 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 1897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 835 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 839 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 843 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 847 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1929 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 855 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1937 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 859 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 863 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 1953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 867 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 1961 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 871 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1969 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 875 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 1977 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 879 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 1985 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 883 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 1993 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call power builtin
  }
#line 2001 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 891 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2009 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 895 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2017 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 899 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2025 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 903 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2033 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 907 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2041 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 911 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2049 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 915 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2057 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2065 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 923 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2073 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 927 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO add implies instruction
  }
#line 2081 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 931 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2089 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 939 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2097 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 947 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2106 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 952 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2114 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 960 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2124 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2134 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2142 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 980 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 989 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), arguments );
  }
#line 2160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2184 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2192 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2200 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1034 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1039 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2218 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1048 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2226 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1052 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1056 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1060 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2250 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1064 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2258 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1068 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1072 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2274 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1076 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1080 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1084 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2298 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1092 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2308 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2318 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1108 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 2326 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1116 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2334 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1120 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2342 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1128 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2350 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1136 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2358 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1140 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2366 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1144 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1152 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1158 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2394 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1168 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1176 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2410 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1184 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2418 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2426 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1196 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2434 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1204 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1208 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1216 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2458 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1224 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2468 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1230 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2479 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1237 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1243 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2500 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1254 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2508 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1258 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2516 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1266 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2526 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1272 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1282 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 2544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1290 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2552 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2556 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -133;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
       6,    29,     4,   -30,   -63,   -63,   -63,   -63,   -63,  -133,
    -133,    29,  -133,  -133,  -133,  -133,  -133,  -133,   670,  -133,
    -133,   -23,   -19,   -23,    -9,   725,  -133,   -41,  -133,  -133,
    -133,   -63,   725,   -63,  -133,  -133,  -133,   725,   725,   725,
     395,   505,   -11,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
       9,    15,    23,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  1005,  -133,  -133,  -133,     5,  -133,  -133,  -133,
    -133,  -133,   -63,     7,    46,   -39,   -63,   560,  1245,    97,
     -63,    50,    82,   814,    89,  -133,  -133,  -133,  -133,   725,
    1035,   -20,  -133,  1065,    -2,  -133,   670,  -133,   615,  -133,
     725,   725,   725,   725,   725,   725,   725,   725,   725,   725,
     725,   725,   725,   725,   725,   725,   725,   725,  -133,     2,
     -63,   -63,   359,   -63,    53,    49,   -35,  -133,  -133,  -133,
    -133,  -133,  1035,  -133,  -133,   -63,   725,   725,   725,  1095,
    -133,  -133,   725,   725,  -133,  -133,  1245,  1379,  1335,  1360,
    1305,    14,    14,   208,     1,     1,    56,    56,    56,  -133,
    1245,   208,     1,     1,  1245,  -133,   -63,    73,  -133,    -1,
     359,   359,  -133,   -63,   -63,   359,   -42,   725,   725,    61,
     359,   359,    58,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,    81,   -63,   -63,   -63,   725,
    -133,   945,   883,   975,    23,  1245,  1125,  -133,   725,  -133,
     -63,  -133,   108,   281,    84,   111,  -133,  -133,  -133,   849,
     915,   294,   346,   725,   359,  -133,   121,  -133,    16,  1155,
     725,   725,   725,  -133,  -133,  1245,  -133,  -133,  -133,  -133,
     725,   725,   359,    86,  -133,  -133,  1245,  -133,    88,   126,
    -133,   -63,   725,   725,  -133,  1245,  -133,   749,   779,   112,
     450,   725,    91,  -133,  -133,  1275,   359,   359,   359,    92,
      95,  1185,   450,   100,  1215,   670,   725,  -133,  -133,  -133,
     359,   359,   359,  -133,  -133,  -133,   101,  -133,  -133,  -133,
    -133
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,     0,     0,     8,
      10,     2,     3,    12,     4,     6,     5,     1,    29,    32,
      21,    40,     0,    40,     0,   150,   149,     0,   146,   147,
       9,     0,     0,     0,    59,    61,    60,     0,     0,     0,
       0,     0,     0,    63,    64,    65,    67,    66,    62,    27,
      28,     0,   105,    77,    57,    58,    56,    52,    53,    54,
      55,    51,    23,    74,    76,    75,     0,    69,    70,    71,
      72,    73,     0,     0,     0,     0,    20,     0,   151,     0,
       0,    36,     0,     0,     0,    97,    79,    80,   104,     0,
     102,     0,    99,   102,     0,    68,     0,    22,     0,   106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,     0,
       0,     0,     0,     0,    19,     0,    45,    18,    41,    42,
      43,    44,     0,     7,   148,     0,     0,     0,     0,     0,
      78,   103,     0,     0,   100,    26,   102,    95,    93,    94,
      96,    81,    82,    88,    89,    90,    83,    84,    85,    86,
      24,    87,    91,    92,    25,    39,     0,     0,    34,     0,
       0,     0,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   143,   145,   111,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,     0,     0,     0,     0,     0,
      35,     0,     0,     0,     0,   101,     0,    37,     0,    31,
       0,   124,     0,     0,     0,     0,   136,   142,   144,     0,
       0,     0,     0,     0,     0,    17,    16,    50,     0,     0,
       0,     0,     0,   107,    98,    30,    33,   140,   123,   138,
       0,     0,     0,     0,   137,   139,   141,   112,     0,    14,
      46,     0,    47,     0,   109,   108,   110,     0,     0,   126,
       0,     0,     0,    11,    49,     0,     0,     0,     0,     0,
       0,     0,   133,     0,     0,    29,    48,   134,   135,   127,
       0,     0,     0,   132,   128,    15,     0,   129,   130,   131,
      13
  };

  const short int
  Parser::yypgoto_[] =
  {
    -133,  -133,    77,   129,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,    64,  -133,  -114,  -133,  -133,    22,  -133,   -27,  -133,
     139,  -101,  -133,  -133,  -133,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,  -133,  -133,  -133,  -133,   -25,  -133,  -133,  -133,
     124,   -50,   -12,    63,  -133,  -133,  -133,  -133,    67,  -132,
    -133,  -133,  -133,  -133,  -106,  -133,  -133,  -133,  -133,  -133,
    -133,  -133,    87,  -133,  -133,  -133
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     9,    10,    11,    12,   263,   249,   124,   125,
      13,    49,    50,    51,    14,    15,    52,   169,    82,   119,
      73,   127,   128,   129,   130,   131,   228,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      91,    66,    67,    68,    69,    70,    71,    16,   211,   212,
     185,   186,   187,   272,   273,   188,   189,   190,   191,   192,
     193,   194,    26,    27,    28,    29
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      78,   179,    99,   122,    17,    79,    84,    83,   198,     1,
      19,    80,    85,    86,    87,    90,    93,    18,   199,   167,
      72,   123,   195,    74,   141,    20,    21,    22,    23,    24,
      25,    19,   142,     3,   200,     4,     5,     6,     7,   213,
      76,   104,   105,    19,   144,   118,   165,   209,   221,   222,
     142,   210,   132,    81,   166,    81,   109,   110,   111,   112,
     250,    96,    95,    97,   139,   117,    98,   120,   251,   109,
     110,   111,   112,   146,     8,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   164,   121,    81,   225,   226,   227,   126,   135,
     136,     3,    25,     4,     5,     6,     7,   138,   196,   197,
     182,   201,   202,   203,   112,   208,    89,   205,   206,   223,
     170,   237,   171,   224,   172,   173,   240,   174,   175,   241,
     176,   177,   248,   260,   178,   261,   262,   268,   275,   207,
      30,   280,   126,   168,   281,   126,   214,   215,   284,   290,
     264,   179,   219,   220,   233,   180,   133,   126,   182,   182,
     145,   286,    75,   182,   217,    94,   283,   134,   182,   182,
       0,     0,     0,   181,   229,     0,     0,     0,     0,     0,
       0,    19,     0,   235,     0,   183,     0,     0,    81,   184,
       0,     0,     0,     0,     0,    81,    81,     0,   246,     0,
     182,   182,     0,     0,     0,   254,   255,   256,     0,   182,
     182,     0,   182,     0,     0,   257,   258,     0,   126,   126,
     126,     0,     0,     0,     0,     0,     0,   155,   265,     0,
     182,     0,   236,   183,   183,   271,   274,     0,   183,   218,
       0,     0,   216,   183,   183,     0,     0,   271,   104,   105,
       0,   155,     0,     0,   182,   182,   182,     0,     0,     0,
       0,   107,   108,   109,   110,   111,   112,     0,   182,   182,
     182,   115,   116,   126,     0,   183,   183,     0,     0,   238,
     238,     0,     0,     0,   183,   183,     0,   183,   238,   238,
       0,   247,     0,   170,     0,   171,   239,   172,   173,     0,
     174,   175,     0,   176,   177,   183,   170,   178,   171,   259,
     172,   173,     0,   174,   175,     0,   176,   177,     0,     0,
     178,     0,     0,     0,   179,     0,     0,     0,   180,   183,
     183,   183,     0,   277,   278,   279,     0,   179,     0,     0,
       0,   180,   244,   183,   183,   183,   181,   287,   288,   289,
       0,     0,     0,     0,    19,     0,     0,     0,   170,   181,
     171,     0,   172,   173,     0,   174,   175,    19,   176,   177,
       0,   170,   178,   171,     0,   172,   173,     0,   174,   175,
       0,   176,   177,     0,     0,   178,     0,     0,     0,   179,
       0,     0,     0,   180,     0,     0,     0,     0,     0,     0,
       0,     0,   179,     0,     0,     0,   180,     0,     0,     0,
       0,   181,   245,     0,    31,     0,     0,     0,    32,    19,
       0,     0,     0,     0,   181,    33,     0,    34,    35,    36,
       0,     0,    19,     0,    37,    38,    39,     0,    77,    88,
      41,     0,     0,     0,     0,     0,    42,     0,     0,     0,
      89,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    43,    44,    45,    46,    47,    48,    19,    31,
       0,     0,     0,    32,     0,     0,     0,     0,   269,     0,
      33,     0,    34,    35,    36,     0,     0,     0,     0,    37,
      38,    39,     0,    77,     0,    41,     0,     0,     0,     0,
     270,    42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,    19,    31,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,    33,     0,    34,    35,    36,
       0,     0,     0,     0,    37,    38,    39,     0,    77,     0,
      41,    92,     0,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    43,    44,    45,    46,    47,    48,    19,    31,
       0,     0,     0,    32,     0,     0,     0,     0,     0,     0,
      33,     0,    34,    35,    36,     0,     0,     0,     0,    37,
      38,    39,     0,    77,     0,    41,     0,     0,     0,     0,
       0,    42,     0,     0,     0,    89,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,    19,    31,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,    33,     0,    34,    35,    36,
       0,     0,     0,     0,    37,    38,    39,     0,    77,    88,
      41,     0,     0,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    43,    44,    45,    46,    47,    48,    19,    31,
       0,     0,     0,    32,     0,     0,     0,     0,     0,     0,
      33,     0,    34,    35,    36,     0,     0,     0,     0,    37,
      38,    39,     0,    40,     0,    41,     0,     0,     0,     0,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    43,    44,    45,
      46,    47,    48,    19,    31,     0,     0,     0,    32,     0,
       0,     0,     0,     0,     0,    33,     0,    34,    35,    36,
       0,     0,     0,     0,    37,    38,    39,   266,    77,     0,
      41,     0,     0,     0,     0,     0,    42,     0,     0,     0,
       0,     0,     0,     0,   100,   101,   102,   103,     0,   104,
     105,   106,    43,    44,    45,    46,    47,    48,    19,     0,
     267,     0,   107,   108,   109,   110,   111,   112,     0,     0,
       0,   114,   115,   116,   100,   101,   102,   103,     0,   104,
     105,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   107,   108,   109,   110,   111,   112,   137,     0,
       0,   114,   115,   116,     0,     0,     0,     0,     0,   100,
     101,   102,   103,     0,   104,   105,   106,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   107,   108,   109,
     110,   111,   112,   242,     0,     0,   114,   115,   116,     0,
       0,     0,     0,     0,   100,   101,   102,   103,     0,   104,
     105,   106,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   107,   108,   109,   110,   111,   112,   231,     0,
       0,   114,   115,   116,     0,     0,     0,     0,   100,   101,
     102,   103,     0,   104,   105,   106,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   107,   108,   109,   110,
     111,   112,   243,     0,     0,   114,   115,   116,     0,     0,
     100,   101,   102,   103,     0,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,   230,     0,     0,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,     0,   232,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,     0,     0,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,   113,     0,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,   140,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,     0,     0,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,   143,     0,     0,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,   204,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,     0,     0,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,     0,
       0,   234,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,     0,     0,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   252,
     109,   110,   111,   112,   253,     0,     0,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,     0,
       0,     0,     0,     0,   282,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,     0,     0,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,     0,
       0,     0,     0,   285,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,     0,     0,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,     0,     0,   114,   115,   116,
     100,   101,   102,   103,     0,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   276,
     109,   110,   111,   112,     0,     0,     0,   114,   115,   116,
     100,   101,   102,     0,     0,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,     0,     0,   114,   115,   116,
     100,     0,   102,     0,     0,   104,   105,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,   112,     0,   100,     0,   114,   115,   116,
     104,   105,   106,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   107,   108,   109,   110,   111,   112,   104,
     105,   106,   114,   115,   116,     0,     0,     0,     0,     0,
       0,     0,   107,   108,   109,   110,   111,   112,     0,     0,
       0,   114,   115,   116
  };

  const short int
  Parser::yycheck_[] =
  {
      25,    43,    52,    42,     0,    46,    33,    32,    43,     3,
      73,    52,    37,    38,    39,    40,    41,    47,    53,   120,
      43,    60,   123,    42,    44,     3,     4,     5,     6,     7,
       8,    73,    52,     4,   135,     6,     7,     8,     9,   171,
      49,    40,    41,    73,    46,    72,    44,    48,   180,   181,
      52,    52,    77,    31,    52,    33,    55,    56,    57,    58,
      44,    52,    73,    48,    89,    60,    43,    60,    52,    55,
      56,    57,    58,    98,    45,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,    47,    72,   196,   197,   198,    76,    49,
      18,     4,    80,     6,     7,     8,     9,    18,    55,    60,
     122,   136,   137,   138,    58,    42,    55,   142,   143,    61,
      12,    13,    14,    42,    16,    17,    42,    19,    20,    18,
      22,    23,    11,    47,    26,    47,    10,    25,    47,   166,
      11,    49,   120,   121,    49,   123,   173,   174,    48,    48,
     251,    43,   177,   178,   204,    47,    79,   135,   170,   171,
      96,   275,    23,   175,   176,    41,   272,    80,   180,   181,
      -1,    -1,    -1,    65,   199,    -1,    -1,    -1,    -1,    -1,
      -1,    73,    -1,   208,    -1,   122,    -1,    -1,   166,   122,
      -1,    -1,    -1,    -1,    -1,   173,   174,    -1,   223,    -1,
     212,   213,    -1,    -1,    -1,   230,   231,   232,    -1,   221,
     222,    -1,   224,    -1,    -1,   240,   241,    -1,   196,   197,
     198,    -1,    -1,    -1,    -1,    -1,    -1,   252,   253,    -1,
     242,    -1,   210,   170,   171,   260,   261,    -1,   175,   176,
      -1,    -1,   175,   180,   181,    -1,    -1,   272,    40,    41,
      -1,   276,    -1,    -1,   266,   267,   268,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,   280,   281,
     282,    63,    64,   251,    -1,   212,   213,    -1,    -1,   212,
     213,    -1,    -1,    -1,   221,   222,    -1,   224,   221,   222,
      -1,   224,    -1,    12,    -1,    14,    15,    16,    17,    -1,
      19,    20,    -1,    22,    23,   242,    12,    26,    14,   242,
      16,    17,    -1,    19,    20,    -1,    22,    23,    -1,    -1,
      26,    -1,    -1,    -1,    43,    -1,    -1,    -1,    47,   266,
     267,   268,    -1,   266,   267,   268,    -1,    43,    -1,    -1,
      -1,    47,    48,   280,   281,   282,    65,   280,   281,   282,
      -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,    12,    65,
      14,    -1,    16,    17,    -1,    19,    20,    73,    22,    23,
      -1,    12,    26,    14,    -1,    16,    17,    -1,    19,    20,
      -1,    22,    23,    -1,    -1,    26,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    43,    -1,    -1,    -1,    47,    -1,    -1,    -1,
      -1,    65,    66,    -1,    19,    -1,    -1,    -1,    23,    73,
      -1,    -1,    -1,    -1,    65,    30,    -1,    32,    33,    34,
      -1,    -1,    73,    -1,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    28,    -1,
      30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
      40,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,
      50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    19,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    40,    41,    -1,    43,    -1,
      45,    46,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
      40,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    19,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    40,    41,    -1,    43,    44,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    19,
      -1,    -1,    -1,    23,    -1,    -1,    -1,    -1,    -1,    -1,
      30,    -1,    32,    33,    34,    -1,    -1,    -1,    -1,    39,
      40,    41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,
      70,    71,    72,    73,    19,    -1,    -1,    -1,    23,    -1,
      -1,    -1,    -1,    -1,    -1,    30,    -1,    32,    33,    34,
      -1,    -1,    -1,    -1,    39,    40,    41,    18,    43,    -1,
      45,    -1,    -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,    40,
      41,    42,    67,    68,    69,    70,    71,    72,    73,    -1,
      21,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    62,    63,    64,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    24,    -1,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    35,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    24,    -1,    -1,    62,    63,    64,    -1,
      -1,    -1,    -1,    -1,    35,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    25,    -1,
      -1,    62,    63,    64,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    27,    -1,    -1,    62,    63,    64,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    29,    -1,    -1,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    31,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    60,    -1,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    44,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    59,    -1,    -1,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    49,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    62,    63,    64,
      35,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    62,    63,    64,
      35,    36,    37,    -1,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    62,    63,    64,
      35,    -1,    37,    -1,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    35,    -1,    62,    63,    64,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    40,
      41,    42,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    -1,    -1,
      -1,    62,    63,    64
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    77,     4,     6,     7,     8,     9,    45,    78,
      79,    80,    81,    86,    90,    91,   123,     0,    47,    73,
      92,    92,    92,    92,    92,    92,   138,   139,   140,   141,
      79,    19,    23,    30,    32,    33,    34,    39,    40,    41,
      43,    45,    51,    67,    68,    69,    70,    71,    72,    87,
      88,    89,    92,   103,   104,   105,   106,   107,   108,   109,
     110,   111,   112,   113,   114,   115,   117,   118,   119,   120,
     121,   122,    43,    96,    42,    96,    49,    43,   112,    46,
      52,    92,    94,   112,    94,   112,   112,   112,    44,    55,
     112,   116,    46,   112,   116,    73,    52,    48,    43,   117,
      35,    36,    37,    38,    40,    41,    42,    53,    54,    55,
      56,    57,    58,    60,    62,    63,    64,    60,    94,    95,
      60,    47,    42,    60,    84,    85,    92,    97,    98,    99,
     100,   101,   112,    78,   138,    49,    18,    24,    18,   112,
      44,    44,    52,    59,    46,    87,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,    44,    52,    97,    92,    93,
      12,    14,    16,    17,    19,    20,    22,    23,    26,    43,
      47,    65,   118,   119,   124,   126,   127,   128,   131,   132,
     133,   134,   135,   136,   137,    97,    55,    60,    43,    53,
      97,   112,   112,   112,    44,   112,   112,    94,    42,    48,
      52,   124,   125,   125,    94,    94,   124,   118,   119,   112,
     112,   125,   125,    61,    42,    97,    97,    97,   102,   112,
      29,    25,    31,   117,    46,   112,    92,    13,   124,    15,
      42,    18,    24,    27,    48,    66,   112,   124,    11,    83,
      44,    52,    54,    59,   112,   112,   112,   112,   112,   124,
      47,    47,    10,    82,    97,   112,    18,    21,    25,    28,
      50,   112,   129,   130,   112,    47,    54,   124,   124,   124,
      49,    49,    49,   130,    48,    48,    89,   124,   124,   124,
      48
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
     115,   116,   116,   117,   117,   118,   118,   119,   120,   121,
     122,   123,   123,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   125,   125,   126,   127,   127,   128,   129,
     129,   129,   130,   130,   131,   132,   133,   134,   134,   135,
     135,   136,   137,   137,   137,   137,   138,   138,   139,   139,
     140,   141
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
       3,     3,     1,     3,     2,     1,     2,     5,     6,     6,
       6,     5,     7,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     1,     1,     4,     6,     6,     3,
       3,     3,     2,     1,     6,     6,     2,     3,     3,     3,
       3,     3,     2,     1,     2,     1,     1,     1,     3,     1,
       1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"option\"", "\"derived\"", "\"enum\"", "\"rule\"", "\"function\"",
  "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"", "\"par\"",
  "\"endpar\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
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
       0,   316,   316,   328,   332,   336,   340,   348,   354,   362,
     368,   378,   394,   402,   406,   414,   418,   426,   432,   442,
     446,   454,   471,   488,   497,   508,   520,   526,   536,   540,
     548,   556,   564,   572,   578,   588,   592,   601,   607,   617,
     621,   629,   633,   637,   641,   649,   657,   665,   673,   681,
     687,   697,   701,   705,   709,   713,   717,   721,   725,   733,
     741,   746,   755,   764,   769,   778,   787,   796,   805,   814,
     818,   822,   826,   830,   834,   838,   842,   846,   854,   858,
     862,   866,   870,   874,   878,   882,   886,   890,   894,   898,
     902,   906,   910,   914,   918,   922,   926,   930,   938,   946,
     951,   959,   965,   975,   979,   988,   993,  1001,  1009,  1017,
    1025,  1033,  1038,  1047,  1051,  1055,  1059,  1063,  1067,  1071,
    1075,  1079,  1083,  1091,  1097,  1107,  1115,  1119,  1127,  1135,
    1139,  1143,  1151,  1157,  1167,  1175,  1183,  1191,  1195,  1203,
    1207,  1215,  1223,  1229,  1236,  1242,  1253,  1257,  1265,  1271,
    1281,  1289
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
#line 3379 "GrammarParser.cpp" // lalr1.cc:1167
#line 1295 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
