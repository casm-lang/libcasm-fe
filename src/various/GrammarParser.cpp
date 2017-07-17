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
      case 152: // Attribute
        value.move< Attribute::Ptr > (that.value);
        break;

      case 153: // Attributes
        value.move< Attributes::Ptr > (that.value);
        break;

      case 154: // BasicAttribute
        value.move< BasicAttribute::Ptr > (that.value);
        break;

      case 108: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 148: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 151: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 142: // CaseLabel
        value.move< Case::Ptr > (that.value);
        break;

      case 141: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 143: // CaseLabels
        value.move< Cases::Ptr > (that.value);
        break;

      case 133: // ChooseExpression
        value.move< ChooseExpression::Ptr > (that.value);
        break;

      case 146: // ChooseRule
        value.move< ChooseRule::Ptr > (that.value);
        break;

      case 109: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 132: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 140: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 84: // Definition
      case 85: // AttributedDefinition
        value.move< Definition::Ptr > (that.value);
        break;

      case 86: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 96: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 129: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 97: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 135: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 89: // MaybeDefined
      case 113: // Atom
      case 122: // Term
      case 123: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 155: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (that.value);
        break;

      case 126: // Terms
      case 127: // Arguments
      case 128: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 111: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 145: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 87: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 99: // Identifier
        value.move< Identifier::Ptr > (that.value);
        break;

      case 102: // IdentifierPath
        value.move< IdentifierPath::Ptr > (that.value);
        break;

      case 100: // Identifiers
      case 101: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (that.value);
        break;

      case 130: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 147: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 131: // LetExpression
        value.move< LetExpression::Ptr > (that.value);
        break;

      case 144: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 125: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 88: // MaybeInitially
      case 94: // Initializers
      case 95: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 105: // Parameters
      case 106: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 124: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 121: // Reference
        value.move< ReferenceAtom::Ptr > (that.value);
        break;

      case 110: // RelationType
        value.move< RelationType::Ptr > (that.value);
        break;

      case 137: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 136: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 138: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 149: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 139: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 83: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 107: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 98: // TypeDefinition
        value.move< TypeDefinition::Ptr > (that.value);
        break;

      case 90: // FunctionParameters
      case 91: // MaybeFunctionParameters
      case 112: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 114: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 134: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 93: // Initializer
      case 150: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 115: // Boolean
      case 116: // String
      case 117: // BitNumber
      case 118: // IntegerNumber
      case 119: // FloatingNumber
      case 120: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 103: // Variable
      case 104: // AttributedVariable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "floating"
      case 76: // "string"
      case 77: // "identifier"
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
      case 152: // Attribute
        value.copy< Attribute::Ptr > (that.value);
        break;

      case 153: // Attributes
        value.copy< Attributes::Ptr > (that.value);
        break;

      case 154: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (that.value);
        break;

      case 108: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 148: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 151: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 142: // CaseLabel
        value.copy< Case::Ptr > (that.value);
        break;

      case 141: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 143: // CaseLabels
        value.copy< Cases::Ptr > (that.value);
        break;

      case 133: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (that.value);
        break;

      case 146: // ChooseRule
        value.copy< ChooseRule::Ptr > (that.value);
        break;

      case 109: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 132: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 140: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 84: // Definition
      case 85: // AttributedDefinition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 86: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 96: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 129: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 97: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 135: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 89: // MaybeDefined
      case 113: // Atom
      case 122: // Term
      case 123: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 155: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (that.value);
        break;

      case 126: // Terms
      case 127: // Arguments
      case 128: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 111: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 145: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 87: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 99: // Identifier
        value.copy< Identifier::Ptr > (that.value);
        break;

      case 102: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (that.value);
        break;

      case 100: // Identifiers
      case 101: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (that.value);
        break;

      case 130: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 147: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 131: // LetExpression
        value.copy< LetExpression::Ptr > (that.value);
        break;

      case 144: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 125: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 88: // MaybeInitially
      case 94: // Initializers
      case 95: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 105: // Parameters
      case 106: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 124: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 121: // Reference
        value.copy< ReferenceAtom::Ptr > (that.value);
        break;

      case 110: // RelationType
        value.copy< RelationType::Ptr > (that.value);
        break;

      case 137: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 136: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 138: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 149: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 139: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 83: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 107: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 98: // TypeDefinition
        value.copy< TypeDefinition::Ptr > (that.value);
        break;

      case 90: // FunctionParameters
      case 91: // MaybeFunctionParameters
      case 112: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 114: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 134: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 93: // Initializer
      case 150: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 115: // Boolean
      case 116: // String
      case 117: // BitNumber
      case 118: // IntegerNumber
      case 119: // FloatingNumber
      case 120: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 103: // Variable
      case 104: // AttributedVariable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "floating"
      case 76: // "string"
      case 77: // "identifier"
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
      case 152: // Attribute
        yylhs.value.build< Attribute::Ptr > ();
        break;

      case 153: // Attributes
        yylhs.value.build< Attributes::Ptr > ();
        break;

      case 154: // BasicAttribute
        yylhs.value.build< BasicAttribute::Ptr > ();
        break;

      case 108: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 148: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 151: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 142: // CaseLabel
        yylhs.value.build< Case::Ptr > ();
        break;

      case 141: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 143: // CaseLabels
        yylhs.value.build< Cases::Ptr > ();
        break;

      case 133: // ChooseExpression
        yylhs.value.build< ChooseExpression::Ptr > ();
        break;

      case 146: // ChooseRule
        yylhs.value.build< ChooseRule::Ptr > ();
        break;

      case 109: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 132: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 140: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 84: // Definition
      case 85: // AttributedDefinition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 86: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 96: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 129: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 97: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 135: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 89: // MaybeDefined
      case 113: // Atom
      case 122: // Term
      case 123: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 155: // ExpressionAttribute
        yylhs.value.build< ExpressionAttribute::Ptr > ();
        break;

      case 126: // Terms
      case 127: // Arguments
      case 128: // TwoOrMoreArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 111: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 145: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 87: // FunctionDefinition
      case 92: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 99: // Identifier
        yylhs.value.build< Identifier::Ptr > ();
        break;

      case 102: // IdentifierPath
        yylhs.value.build< IdentifierPath::Ptr > ();
        break;

      case 100: // Identifiers
      case 101: // DotSeparatedIdentifiers
        yylhs.value.build< Identifiers::Ptr > ();
        break;

      case 130: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 147: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 131: // LetExpression
        yylhs.value.build< LetExpression::Ptr > ();
        break;

      case 144: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 125: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 88: // MaybeInitially
      case 94: // Initializers
      case 95: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 105: // Parameters
      case 106: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 124: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 121: // Reference
        yylhs.value.build< ReferenceAtom::Ptr > ();
        break;

      case 110: // RelationType
        yylhs.value.build< RelationType::Ptr > ();
        break;

      case 137: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 136: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 138: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 149: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 139: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 83: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 107: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 98: // TypeDefinition
        yylhs.value.build< TypeDefinition::Ptr > ();
        break;

      case 90: // FunctionParameters
      case 91: // MaybeFunctionParameters
      case 112: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 114: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 134: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 93: // Initializer
      case 150: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 115: // Boolean
      case 116: // String
      case 117: // BitNumber
      case 118: // IntegerNumber
      case 119: // FloatingNumber
      case 120: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 103: // Variable
      case 104: // AttributedVariable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 71: // "binary"
      case 72: // "hexadecimal"
      case 73: // "integer"
      case 74: // "rational"
      case 75: // "floating"
      case 76: // "string"
      case 77: // "identifier"
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
#line 353 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& fileName = filePath.substr( filePath.find_last_of( "/\\" ) + 1 );
      const std::string& name = fileName.substr( 0, fileName.rfind( "." ) );

      const auto specificationName = make< Identifier >( yylhs.location, name );
      result = Ast::make< Specification >( yylhs.location, specificationName, yystack_[0].value.as< Definitions::Ptr > () );
  }
#line 1327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 365 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 369 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1343 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 377 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 381 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< TypeDefinition::Ptr > ();
  }
#line 1367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 385 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = nullptr;
  }
#line 1375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definition = yystack_[0].value.as< Definition::Ptr > ();
      definition->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< Definition::Ptr > () = definition;
  }
#line 1385 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< Definition::Ptr > ();
  }
#line 1393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1403 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 413 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = Ast::make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 423 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 439 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 451 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 459 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 463 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 471 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1483 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 477 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1493 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 487 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1501 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 491 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = Ast::make< Types >( yylhs.location );
  }
#line 1509 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 522 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1554 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 540 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1566 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 548 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = Ast::make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, arguments );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto function = Ast::make< DirectCallExpression >( yylhs.location, nullptr, yystack_[2].value.as< Expressions::Ptr > () );
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1591 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 569 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 575 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = Ast::make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1611 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 585 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = Ast::make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 597 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = Ast::make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1635 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 605 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = Ast::make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< Identifier::Ptr > (), yystack_[1].value.as< Identifiers::Ptr > () );
  }
#line 1643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 613 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< TypeDefinition::Ptr > () = Ast::make< TypeDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 621 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 625 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Identifier::Ptr > () = Ast::make< Identifier >( yylhs.location, "in" );
  }
#line 1667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 633 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1677 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 639 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1687 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 649 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< Identifiers::Ptr > ();
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 655 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = Ast::make< Identifiers >( yylhs.location );
      identifiers->add( yystack_[0].value.as< Identifier::Ptr > () );
      yylhs.value.as< Identifiers::Ptr > () = identifiers;
  }
#line 1707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 665 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::ABSOLUTE );
  }
#line 1715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 669 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierPath::Ptr > () = Ast::make< IdentifierPath >( yylhs.location, yystack_[0].value.as< Identifiers::Ptr > (), IdentifierPath::Type::RELATIVE );
  }
#line 1723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[2].value.as< Identifier::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 681 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto unresolvedType = Ast::make< UnresolvedType >( yylhs.location );
      yylhs.value.as< VariableDefinition::Ptr > () = Ast::make< VariableDefinition >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > (), unresolvedType );
  }
#line 1740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 690 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto variable = yystack_[0].value.as< VariableDefinition::Ptr > ();
      variable->setAttributes( yystack_[2].value.as< Attributes::Ptr > () );
      yylhs.value.as< VariableDefinition::Ptr > () = variable;
  }
#line 1750 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 696 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = yystack_[0].value.as< VariableDefinition::Ptr > ();
  }
#line 1758 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1768 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1778 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1786 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 724 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = nullptr;
  }
#line 1794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = Ast::make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1802 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 736 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1810 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1818 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 744 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RelationType::Ptr > ();
  }
#line 1826 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1834 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = Ast::make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 1842 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = Ast::make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierPath::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1850 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RelationType::Ptr > () = Ast::make< RelationType >( yylhs.location, yystack_[5].value.as< IdentifierPath::Ptr > (), yystack_[3].value.as< Types::Ptr > (), yystack_[1].value.as< Type::Ptr > () );
  }
#line 1858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = Ast::make< FixedSizedType >( yylhs.location, yystack_[2].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 794 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = Ast::make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 804 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ReferenceAtom::Ptr > ();
  }
#line 1894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 808 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1902 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1910 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1918 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 820 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1926 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 824 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1934 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 828 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1942 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1950 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 840 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = Ast::make< UndefAtom >( yylhs.location );
  }
#line 1958 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 848 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1967 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 853 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = Ast::make< ValueAtom >( yylhs.location, value );
  }
#line 1976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 862 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 878 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2008 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2024 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2040 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 922 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2056 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2072 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ReferenceAtom::Ptr > () = Ast::make< ReferenceAtom >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > () );
  }
#line 2080 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2088 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2096 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< LetExpression::Ptr > ();
  }
#line 2104 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2112 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ChooseExpression::Ptr > ();
  }
#line 2120 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2128 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2136 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2144 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = nullptr;
  }
#line 2184 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2192 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::INV_INSTRUCTION );
  }
#line 2200 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2208 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1030 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2216 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1034 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2224 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1038 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2232 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1042 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2240 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1046 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::POW_INSTRUCTION );
  }
#line 2248 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1050 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2256 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1054 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2264 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1058 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2272 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1062 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2280 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2288 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1070 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1078 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2312 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::IMP_INSTRUCTION );
  }
#line 2336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1094 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = Ast::make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1102 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = Ast::make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 2352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1110 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, expressions );
  }
#line 2361 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1115 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = Ast::make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 2369 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1119 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = nullptr;
  }
#line 2377 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1127 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2387 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1147 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = nullptr;
  }
#line 2413 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1151 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1160 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto expressions = yystack_[1].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[3].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1170 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto arguments = Ast::make< Expressions >( yylhs.location );
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[0].value.as< IdentifierPath::Ptr > (), arguments );
  }
#line 2441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1175 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = Ast::make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierPath::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1183 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = Ast::make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1191 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetExpression::Ptr > () = Ast::make< LetExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1199 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = Ast::make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1207 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseExpression::Ptr > () = Ast::make< ChooseExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = Ast::make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1223 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = Ast::make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1231 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[3].value.as< Identifier::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), createVoidType( yylhs.location ),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2506 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1236 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = Ast::make< RuleDefinition >( yylhs.location, yystack_[5].value.as< Identifier::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1245 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1249 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1253 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1257 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1261 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1265 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ChooseRule::Ptr > ();
  }
#line 2563 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1269 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1273 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1277 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1281 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1285 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2603 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1293 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2613 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1299 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = Ast::make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1309 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = Ast::make< SkipRule >( yylhs.location );
  }
#line 2631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1317 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1321 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = Ast::make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1329 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = Ast::make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< Cases::Ptr > () );
  }
#line 2655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1333 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = nullptr;
  }
#line 2663 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1341 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2671 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1345 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< DefaultCase >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2679 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Case::Ptr > () = Ast::make< ExpressionCase >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2687 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1357 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = yystack_[0].value.as< Cases::Ptr > ();
      cases->add( yystack_[1].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1363 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto cases = Ast::make< Cases >( yylhs.location );
      cases->add( yystack_[0].value.as< Case::Ptr > () );
      yylhs.value.as< Cases::Ptr > () = cases;
  }
#line 2707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = Ast::make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1381 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = Ast::make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1389 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ChooseRule::Ptr > () = Ast::make< ChooseRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = Ast::make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2739 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1405 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2747 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1409 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = Ast::make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1413 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1418 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = Ast::make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1435 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2798 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = nullptr;
      yyerrok;
  }
#line 2807 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1449 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto function = yystack_[2].value.as< DirectCallExpression::Ptr > ();
      function->setTargetType( CallExpression::TargetType::FUNCTION );
      yylhs.value.as< UpdateRule::Ptr > () = Ast::make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2817 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1459 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2827 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1465 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2838 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::RULE };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::set< CallExpression::TargetType >
          allowedCallTargetTypes{ CallExpression::TargetType::DERIVED,
                                  CallExpression::TargetType::BUILTIN };
      yylhs.value.as< CallRule::Ptr > () = Ast::make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), allowedCallTargetTypes );
  }
#line 2859 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< BasicAttribute::Ptr > ();
  }
#line 2867 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Attribute::Ptr > () = yystack_[0].value.as< ExpressionAttribute::Ptr > ();
  }
#line 2875 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1501 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = yystack_[2].value.as< Attributes::Ptr > ();
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1507 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto attributes = Ast::make< Attributes >( yylhs.location );
      attributes->add( yystack_[0].value.as< Attribute::Ptr > () );
      yylhs.value.as< Attributes::Ptr > () = attributes;
  }
#line 2895 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1517 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicAttribute::Ptr > () = Ast::make< BasicAttribute >( yylhs.location, yystack_[0].value.as< Identifier::Ptr > () );
  }
#line 2903 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1525 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionAttribute::Ptr > () = Ast::make< ExpressionAttribute >( yylhs.location, yystack_[1].value.as< Identifier::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2911 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2915 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -178;

  const signed char Parser::yytable_ninf_ = -62;

  const short int
  Parser::yypact_[] =
  {
      10,   122,    40,  -178,    -7,   -14,   -14,   -14,   -14,   -14,
     -14,  -178,  -178,   185,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,   978,   -14,  -178,  -178,   -18,  -178,     1,     8,
       1,    36,     3,  1039,  -178,     9,  -178,  -178,  -178,   -16,
     -16,   -16,  1039,   -16,  -178,  -178,  -178,  1039,  1039,  1039,
     459,   521,    -3,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
      30,    35,    41,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
    -178,  -178,  1482,  -178,  -178,  -178,    27,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,   -14,     0,    56,    72,   -35,
      -3,    -3,   459,  1713,   109,   -14,   -14,    74,  -178,    82,
     121,   138,  1248,   139,  -178,  -178,  -178,    92,  1039,  1449,
     115,  -178,  1515,    25,  -178,   978,  -178,   583,  -178,  1039,
    1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,
    1039,  1039,  1039,  1039,  1039,  1039,  1039,  1039,  -178,   118,
    -178,    -6,    -3,   -14,   885,    -3,   -11,  -178,  -178,  -178,
    -178,  -178,   108,   103,  -178,  1548,  -178,  -178,    29,    -3,
    1039,  1039,  1039,  1039,  1039,  -178,  1581,  -178,  1039,  -178,
    1039,  -178,  1039,  -178,   125,  -178,  1713,     5,  1813,  1779,
    1807,  1746,    93,    93,  1835,   119,   119,   112,   112,   112,
    -178,  1713,  1746,  1835,   119,   119,  1713,  -178,  -178,   -16,
     124,  -178,   -24,   297,   620,  -178,   -16,   -16,   -16,   885,
      -2,  1039,  1039,   123,   660,   697,   116,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
     137,    -3,  1039,    -3,    -3,   -14,  -178,  1066,  1383,  1137,
    1317,  1416,    41,    28,  1614,  1713,  -178,  -178,  -178,  1039,
    -178,   -14,   169,  -178,   734,   172,   771,   145,   177,   178,
    -178,  -178,  -178,  1283,  1350,   148,   808,   129,   848,  1039,
     885,   140,   -43,   -29,   319,  -178,   190,  -178,  1039,  1039,
    1039,  1039,  1039,  -178,  -178,  -178,  1713,  -178,  -178,  -178,
    -178,  -178,  -178,  1039,  1039,  1039,   885,   154,  -178,  -178,
    -178,  -178,  1713,  -178,    -3,    -3,  -178,   157,   196,  1713,
    -178,  1713,  1713,  -178,  1099,  1175,  1213,   181,   397,   153,
    -178,  1039,   161,  -178,   885,   885,   885,   885,   162,   165,
     168,  1647,   917,   170,  -178,  1680,   978,  -178,  -178,  -178,
    -178,  -178,   885,   885,   885,  -178,  -178,  -178,   173,  -178,
    -178,  -178,  -178
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     8,     0,     0,     0,     0,     0,     0,
       0,    10,    12,     0,     3,    14,     4,     6,     7,     5,
       1,    36,    31,     0,    35,    40,    41,    23,    51,     0,
      51,     0,     0,   177,   176,     0,   173,   174,    11,     0,
       0,     0,     0,     0,    70,    72,    71,     0,     0,     0,
       0,     0,     0,    74,    75,    76,    78,    77,    73,    29,
      30,     0,   123,    90,    68,    69,    67,    63,    64,    65,
      66,    62,    25,    87,    89,    88,     0,    80,    81,    82,
      83,    84,    85,    86,    42,     0,     0,     0,     0,     0,
       0,    22,     0,   178,     0,     0,     0,    44,    46,     0,
       0,     0,     0,     0,   112,    93,    94,     0,     0,     0,
       0,   114,   118,     0,    79,     0,    24,     0,   124,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    39,     0,
      48,     0,     0,     0,     0,     0,    56,    34,    52,    53,
      54,    55,    21,     0,    20,     0,     9,   175,     0,     0,
       0,     0,     0,     0,     0,    92,     0,    91,     0,   116,
       0,   115,     0,    28,     0,   121,   118,     0,   109,   107,
     108,   111,    95,    96,   102,   103,   104,    97,    98,    99,
     100,    26,   110,   101,   105,   106,    27,    50,    49,     0,
       0,    38,     0,     0,     0,   146,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   170,   172,   131,   133,
     134,   135,   136,   137,   138,   139,   140,   141,   142,   143,
       0,    22,     0,     0,     0,     0,    43,     0,     0,     0,
       0,     0,     0,     0,     0,   117,   120,   119,    47,     0,
      33,     0,     0,   145,     0,     0,     0,     0,     0,     0,
     159,   169,   171,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,     0,    59,    19,    18,    45,     0,     0,
       0,     0,     0,   125,   122,   113,    32,    37,   167,   165,
     144,   163,   161,     0,     0,     0,     0,     0,   162,   160,
     166,   164,   168,   132,     0,     0,    57,     0,    16,   126,
     129,   128,   127,   130,     0,     0,     0,   147,     0,     0,
      60,     0,     0,    13,     0,     0,     0,     0,     0,     0,
       0,     0,   155,     0,    58,     0,    31,   156,   157,   158,
     148,   150,     0,     0,     0,   154,   149,    17,     0,   151,
     152,   153,    15
  };

  const short int
  Parser::yypgoto_[] =
  {
    -178,  -178,   130,   210,  -178,  -178,  -178,  -178,  -178,    -5,
    -178,   113,  -178,  -101,  -178,  -178,  -178,    26,  -178,   213,
      -4,     2,   -34,  -178,   208,   -88,  -178,  -178,  -178,  -178,
    -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
     -28,  -178,  -178,  -178,  -100,     4,  -178,   -56,    69,  -178,
    -178,  -178,  -178,  -178,  -178,    76,  -177,  -178,  -178,  -178,
    -178,   -93,  -178,  -178,  -178,  -178,  -178,  -178,  -178,  -178,
     147,   149,  -178,  -178
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,    11,    12,    13,    14,   323,   308,   152,   153,
      15,    59,    60,    61,    16,    17,    18,    25,   202,    26,
      62,    98,    99,   141,    87,   147,   148,   149,   150,   151,
     273,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,   113,   118,    76,    77,    78,    79,
      80,    81,    82,    83,    19,   253,   254,   219,   220,   221,
     332,   333,   222,   223,   224,   225,   226,   227,   228,   229,
      34,    35,    36,    37
  };

  const short int
  Parser::yytable_[] =
  {
      27,   139,    21,   154,    21,    93,   100,   101,   144,   103,
     -61,    21,   -61,     1,   102,    21,    21,   177,    21,   104,
     105,   106,   109,   112,   305,   250,   306,   256,   145,   251,
      96,    28,    29,    30,    31,    32,    33,   266,   268,   198,
      20,    22,   213,   231,    85,    86,    96,   199,   114,   232,
     247,    88,   140,    91,   200,    23,    94,   230,   172,    23,
      23,    24,    95,    24,   155,    97,    97,    97,   243,    97,
      24,   236,   171,   284,    24,    24,   235,    24,   172,    90,
     166,   172,    95,   115,   116,   117,   146,   146,   216,   176,
     137,   178,   179,   180,   181,   182,   183,   184,   185,   186,
     187,   188,   189,   190,   191,   192,   193,   194,   195,   196,
       3,   138,    97,     4,     5,     6,     7,     8,     9,   142,
     143,    33,    33,     3,   159,   160,     4,     5,     6,     7,
       8,     9,   237,   238,   239,   240,   241,   165,   146,   161,
     176,   146,   244,   272,   245,   275,   276,   216,   216,   128,
     129,   130,   131,   216,   261,   146,   162,   164,   216,   216,
     123,   124,   169,   197,   233,   248,   234,   249,    10,   201,
     246,   131,   257,   258,   259,   128,   129,   130,   131,   108,
     270,   269,   288,   263,   264,    -2,     3,   291,   293,     4,
       5,     6,     7,     8,     9,   294,   295,   298,   216,   300,
     216,   307,   318,   304,   274,   321,   322,   327,   334,   336,
     216,   341,   216,   217,   216,   342,   319,   320,   343,   346,
     218,   286,   352,    38,   156,    97,   271,   146,   173,   146,
     146,    10,    97,    97,    97,   348,    84,   277,    89,   345,
     216,   302,   157,     0,     0,   158,   283,     0,     0,     0,
     309,   310,   311,   312,   313,     0,     0,     0,     0,     0,
       0,    97,     0,     0,     0,   314,   315,   316,   216,   216,
     216,   216,   217,   217,     0,     0,     0,   287,   217,   262,
       0,     0,     0,   217,   217,   260,   216,   216,   216,     0,
     331,     0,     0,   335,     0,     0,     0,     0,   252,     0,
     146,   146,     0,     0,   331,     0,     0,     0,     0,   203,
       0,   204,     0,   205,   206,    21,   207,   208,   209,     0,
     210,   211,     0,   217,   212,   217,     0,     0,     0,     0,
     290,     0,   290,     0,     0,   217,     0,   217,     0,   217,
       0,   213,   290,     0,   290,   214,   303,     0,     0,     0,
       0,     0,     0,     0,     0,   119,   120,   121,   122,    23,
     123,   124,     0,     0,     0,   217,   215,     0,     0,     0,
       0,     0,   317,   126,    24,     0,   129,   130,   131,     0,
       0,     0,     0,   133,     0,   134,   135,   136,     0,     0,
       0,     0,     0,   217,   217,   217,   217,     0,   328,     0,
     337,   338,   339,   340,     0,     0,     0,     0,     0,     0,
       0,   217,   217,   217,    39,    21,    40,    41,   349,   350,
     351,    42,     0,     0,     0,     0,   329,     0,    43,     0,
      44,    45,    46,     0,     0,     0,     0,    47,    48,    49,
       0,    92,     0,    51,     0,     0,     0,     0,   330,    52,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    23,
     107,     0,     0,     0,     0,     0,     0,     0,    53,    54,
      55,    56,    57,    58,    24,     0,    39,    21,    40,    41,
       0,     0,     0,    42,     0,     0,     0,     0,     0,     0,
      43,     0,    44,    45,    46,     0,     0,     0,     0,    47,
      48,    49,     0,    92,     0,    51,     0,     0,     0,     0,
       0,    52,     0,     0,     0,   108,     0,     0,     0,     0,
       0,    23,   110,     0,     0,     0,     0,     0,     0,     0,
      53,    54,    55,    56,    57,    58,    24,     0,    39,    21,
      40,    41,     0,     0,     0,    42,     0,     0,     0,     0,
       0,     0,    43,     0,    44,    45,    46,     0,     0,     0,
       0,    47,    48,    49,     0,    92,     0,    51,   111,     0,
       0,     0,     0,    52,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    23,   174,     0,     0,     0,     0,     0,
       0,     0,    53,    54,    55,    56,    57,    58,    24,     0,
      39,    21,    40,    41,     0,     0,     0,    42,     0,     0,
       0,     0,     0,     0,    43,     0,    44,    45,    46,     0,
       0,   255,     0,    47,    48,    49,     0,    92,   175,    51,
       0,     0,   203,     0,   204,    52,   205,   206,    21,   207,
     208,   209,     0,   210,   211,    23,     0,   212,     0,     0,
       0,     0,     0,     0,    53,    54,    55,    56,    57,    58,
      24,   265,     0,     0,   213,     0,     0,     0,   214,     0,
       0,     0,   203,     0,   204,     0,   205,   206,    21,   207,
     208,   209,    23,   210,   211,     0,     0,   212,     0,   215,
       0,     0,     0,     0,     0,     0,     0,    24,   267,     0,
       0,     0,     0,     0,   213,     0,     0,     0,   214,   203,
       0,   204,     0,   205,   206,    21,   207,   208,   209,     0,
     210,   211,    23,     0,   212,     0,     0,     0,     0,   215,
       0,     0,     0,     0,     0,     0,     0,    24,     0,     0,
       0,   213,     0,     0,     0,   214,   203,   289,   204,     0,
     205,   206,    21,   207,   208,   209,     0,   210,   211,    23,
       0,   212,     0,     0,     0,     0,   215,     0,     0,     0,
       0,     0,     0,     0,    24,     0,     0,     0,   213,     0,
       0,     0,   214,   203,     0,   204,   292,   205,   206,    21,
     207,   208,   209,     0,   210,   211,    23,     0,   212,     0,
       0,     0,     0,   215,     0,     0,     0,     0,     0,     0,
       0,    24,     0,     0,     0,   213,     0,     0,     0,   214,
     203,     0,   204,     0,   205,   206,    21,   207,   208,   209,
       0,   210,   211,    23,     0,   212,     0,     0,     0,     0,
     215,     0,     0,     0,     0,     0,     0,     0,    24,     0,
       0,     0,   213,     0,     0,     0,   214,   299,     0,     0,
     203,     0,   204,     0,   205,   206,    21,   207,   208,   209,
      23,   210,   211,     0,     0,   212,     0,   215,     0,     0,
       0,     0,     0,     0,     0,    24,     0,     0,     0,     0,
       0,     0,   213,     0,     0,     0,   214,   203,     0,   204,
       0,   205,   206,    21,   207,   208,   209,     0,   210,   211,
      23,     0,   212,     0,     0,     0,     0,   215,   301,     0,
       0,     0,     0,     0,     0,    24,     0,     0,     0,   213,
       0,     0,     0,   214,    39,    21,    40,    41,     0,     0,
       0,    42,     0,     0,     0,     0,   329,    23,    43,     0,
      44,    45,    46,     0,   215,     0,     0,    47,    48,    49,
       0,    92,    24,    51,     0,     0,     0,     0,   330,    52,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    23,
       0,     0,     0,     0,     0,     0,     0,     0,    53,    54,
      55,    56,    57,    58,    24,    39,    21,    40,    41,     0,
       0,     0,    42,     0,     0,     0,     0,     0,     0,    43,
       0,    44,    45,    46,     0,     0,     0,     0,    47,    48,
      49,     0,    50,     0,    51,     0,     0,     0,     0,     0,
      52,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      23,     0,     0,     0,     0,     0,     0,     0,     0,    53,
      54,    55,    56,    57,    58,    24,    39,    21,    40,    41,
       0,     0,     0,    42,     0,     0,     0,     0,     0,     0,
      43,     0,    44,    45,    46,     0,     0,     0,     0,    47,
      48,    49,     0,    92,   278,    51,     0,     0,     0,     0,
       0,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    23,   119,   120,   121,   122,     0,   123,   124,   125,
      53,    54,    55,    56,    57,    58,    24,   324,     0,     0,
     126,   127,   128,   129,   130,   131,     0,     0,     0,     0,
     133,     0,   134,   135,   136,   119,   120,   121,   122,     0,
     123,   124,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,   280,
       0,     0,     0,   133,     0,   134,   135,   136,     0,     0,
       0,     0,     0,   119,   120,   121,   122,     0,   123,   124,
     125,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   128,   129,   130,   131,   325,     0,     0,
       0,   133,     0,   134,   135,   136,     0,     0,     0,     0,
       0,   119,   120,   121,   122,     0,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   126,
     127,   128,   129,   130,   131,   326,     0,     0,     0,   133,
       0,   134,   135,   136,     0,     0,     0,     0,     0,   119,
     120,   121,   122,     0,   123,   124,   125,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   126,   127,   128,
     129,   130,   131,   163,     0,     0,     0,   133,     0,   134,
     135,   136,     0,     0,   119,   120,   121,   122,     0,   123,
     124,   125,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   126,   127,   128,   129,   130,   131,   296,     0,
       0,     0,   133,     0,   134,   135,   136,     0,     0,   119,
     120,   121,   122,     0,   123,   124,   125,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   126,   127,   128,
     129,   130,   131,   281,     0,     0,     0,   133,     0,   134,
     135,   136,     0,   119,   120,   121,   122,     0,   123,   124,
     125,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   126,   127,   128,   129,   130,   131,     0,   297,     0,
       0,   133,     0,   134,   135,   136,   119,   120,   121,   122,
       0,   123,   124,   125,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   126,   127,   128,   129,   130,   131,
       0,     0,     0,   279,   133,     0,   134,   135,   136,   119,
     120,   121,   122,     0,   123,   124,   125,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   126,   127,   128,
     129,   130,   131,     0,     0,     0,     0,   133,   282,   134,
     135,   136,   119,   120,   121,   122,     0,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     126,   127,   128,   129,   130,   131,     0,     0,     0,     0,
     133,     0,   134,   135,   136,   119,   120,   121,   122,     0,
     123,   124,   125,     0,   167,     0,     0,     0,     0,     0,
       0,     0,   168,   126,   127,   128,   129,   130,   131,     0,
       0,     0,     0,   133,     0,   134,   135,   136,   119,   120,
     121,   122,     0,   123,   124,   125,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   126,   127,   128,   129,
     130,   131,     0,     0,     0,   132,   133,     0,   134,   135,
     136,   119,   120,   121,   122,     0,   123,   124,   125,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   126,
     127,   128,   129,   130,   131,     0,   170,     0,     0,   133,
       0,   134,   135,   136,   119,   120,   121,   122,     0,   123,
     124,   125,     0,   167,     0,     0,     0,     0,     0,     0,
       0,     0,   126,   127,   128,   129,   130,   131,     0,     0,
       0,     0,   133,     0,   134,   135,   136,   119,   120,   121,
     122,     0,   123,   124,   125,     0,   242,     0,     0,     0,
       0,     0,     0,     0,     0,   126,   127,   128,   129,   130,
     131,     0,     0,     0,     0,   133,     0,   134,   135,   136,
     119,   120,   121,   122,     0,   123,   124,   125,     0,     0,
       0,   285,     0,     0,     0,     0,     0,     0,   126,   127,
     128,   129,   130,   131,     0,     0,     0,     0,   133,     0,
     134,   135,   136,   119,   120,   121,   122,     0,   123,   124,
     125,     0,     0,     0,     0,     0,     0,   344,     0,     0,
       0,   126,   127,   128,   129,   130,   131,     0,     0,     0,
       0,   133,     0,   134,   135,   136,   119,   120,   121,   122,
       0,   123,   124,   125,     0,     0,     0,     0,     0,   347,
       0,     0,     0,     0,   126,   127,   128,   129,   130,   131,
       0,     0,     0,     0,   133,     0,   134,   135,   136,   119,
     120,   121,   122,     0,   123,   124,   125,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   126,   127,   128,
     129,   130,   131,     0,     0,     0,     0,   133,     0,   134,
     135,   136,   119,   120,   121,     0,     0,   123,   124,   125,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     126,   127,   128,   129,   130,   131,     0,     0,     0,     0,
       0,     0,   134,   135,   136,   119,     0,   121,     0,     0,
     123,   124,   125,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   126,   127,   128,   129,   130,   131,     0,
       0,     0,     0,   119,     0,   134,   135,   136,   123,   124,
     125,     0,     0,     0,   123,   124,   125,     0,     0,     0,
       0,   126,   127,   128,   129,   130,   131,   126,   127,   128,
     129,   130,   131,   134,   135,   136,   123,   124,     0,   134,
     135,   136,     0,     0,     0,     0,     0,     0,     0,   126,
     127,   128,   129,   130,   131,     0,     0,     0,     0,     0,
       0,     0,   135,   136
  };

  const short int
  Parser::yycheck_[] =
  {
       4,     1,    18,    91,    18,    33,    40,    41,    43,    43,
      53,    18,    55,     3,    42,    18,    18,   117,    18,    47,
      48,    49,    50,    51,    53,    49,    55,   204,    63,    53,
      46,     5,     6,     7,     8,     9,    10,   214,   215,    45,
       0,    48,    44,    54,    62,    44,    46,    53,    52,    60,
      45,    43,    86,    50,   142,    62,    47,   145,    53,    62,
      62,    77,    53,    77,    92,    39,    40,    41,   168,    43,
      77,   159,    47,    45,    77,    77,    47,    77,    53,    43,
     108,    53,    53,    53,    49,    44,    90,    91,   144,   117,
      63,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
       1,    85,    86,     4,     5,     6,     7,     8,     9,    63,
      48,    95,    96,     1,    50,    43,     4,     5,     6,     7,
       8,     9,   160,   161,   162,   163,   164,    45,   142,    18,
     168,   145,   170,   231,   172,   233,   234,   203,   204,    56,
      57,    58,    59,   209,   210,   159,    18,    18,   214,   215,
      41,    42,    47,    45,    56,   199,    63,    43,    46,   143,
      45,    59,   206,   207,   208,    56,    57,    58,    59,    56,
      43,    65,    13,   211,   212,     0,     1,    15,    43,     4,
       5,     6,     7,     8,     9,    18,    18,    49,   254,    70,
     256,    11,    48,    63,   232,    48,    10,    26,    55,    48,
     266,    49,   268,   144,   270,    50,   304,   305,    50,    49,
     144,   249,    49,    13,    94,   199,   231,   231,   115,   233,
     234,    46,   206,   207,   208,   336,    23,   235,    30,   332,
     296,   269,    95,    -1,    -1,    96,   242,    -1,    -1,    -1,
     278,   279,   280,   281,   282,    -1,    -1,    -1,    -1,    -1,
      -1,   235,    -1,    -1,    -1,   293,   294,   295,   324,   325,
     326,   327,   203,   204,    -1,    -1,    -1,   251,   209,   210,
      -1,    -1,    -1,   214,   215,   209,   342,   343,   344,    -1,
     318,    -1,    -1,   321,    -1,    -1,    -1,    -1,     1,    -1,
     304,   305,    -1,    -1,   332,    -1,    -1,    -1,    -1,    12,
      -1,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      23,    24,    -1,   254,    27,   256,    -1,    -1,    -1,    -1,
     254,    -1,   256,    -1,    -1,   266,    -1,   268,    -1,   270,
      -1,    44,   266,    -1,   268,    48,   270,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    36,    37,    38,    39,    62,
      41,    42,    -1,    -1,    -1,   296,    69,    -1,    -1,    -1,
      -1,    -1,   296,    54,    77,    -1,    57,    58,    59,    -1,
      -1,    -1,    -1,    64,    -1,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,   324,   325,   326,   327,    -1,     1,    -1,
     324,   325,   326,   327,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   342,   343,   344,    17,    18,    19,    20,   342,   343,
     344,    24,    -1,    -1,    -1,    -1,    29,    -1,    31,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    42,
      -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
       1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    -1,    17,    18,    19,    20,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    -1,    44,    -1,    46,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,
      -1,    62,     1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      71,    72,    73,    74,    75,    76,    77,    -1,    17,    18,
      19,    20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,
      -1,    40,    41,    42,    -1,    44,    -1,    46,    47,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,     1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    71,    72,    73,    74,    75,    76,    77,    -1,
      17,    18,    19,    20,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    33,    34,    35,    -1,
      -1,     1,    -1,    40,    41,    42,    -1,    44,    45,    46,
      -1,    -1,    12,    -1,    14,    52,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    62,    -1,    27,    -1,    -1,
      -1,    -1,    -1,    -1,    71,    72,    73,    74,    75,    76,
      77,     1,    -1,    -1,    44,    -1,    -1,    -1,    48,    -1,
      -1,    -1,    12,    -1,    14,    -1,    16,    17,    18,    19,
      20,    21,    62,    23,    24,    -1,    -1,    27,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,     1,    -1,
      -1,    -1,    -1,    -1,    44,    -1,    -1,    -1,    48,    12,
      -1,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      23,    24,    62,    -1,    27,    -1,    -1,    -1,    -1,    69,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    48,    12,    13,    14,    -1,
      16,    17,    18,    19,    20,    21,    -1,    23,    24,    62,
      -1,    27,    -1,    -1,    -1,    -1,    69,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    48,    12,    -1,    14,    15,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    62,    -1,    27,    -1,
      -1,    -1,    -1,    69,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    77,    -1,    -1,    -1,    44,    -1,    -1,    -1,    48,
      12,    -1,    14,    -1,    16,    17,    18,    19,    20,    21,
      -1,    23,    24,    62,    -1,    27,    -1,    -1,    -1,    -1,
      69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    77,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    48,    49,    -1,    -1,
      12,    -1,    14,    -1,    16,    17,    18,    19,    20,    21,
      62,    23,    24,    -1,    -1,    27,    -1,    69,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    -1,
      -1,    -1,    44,    -1,    -1,    -1,    48,    12,    -1,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      62,    -1,    27,    -1,    -1,    -1,    -1,    69,    70,    -1,
      -1,    -1,    -1,    -1,    -1,    77,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    48,    17,    18,    19,    20,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    29,    62,    31,    -1,
      33,    34,    35,    -1,    69,    -1,    -1,    40,    41,    42,
      -1,    44,    77,    46,    -1,    -1,    -1,    -1,    51,    52,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,    72,
      73,    74,    75,    76,    77,    17,    18,    19,    20,    -1,
      -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,
      -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,
      42,    -1,    44,    -1,    46,    -1,    -1,    -1,    -1,    -1,
      52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    71,
      72,    73,    74,    75,    76,    77,    17,    18,    19,    20,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,    40,
      41,    42,    -1,    44,    18,    46,    -1,    -1,    -1,    -1,
      -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    36,    37,    38,    39,    -1,    41,    42,    43,
      71,    72,    73,    74,    75,    76,    77,    18,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      64,    -1,    66,    67,    68,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    22,
      -1,    -1,    -1,    64,    -1,    66,    67,    68,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    22,    -1,    -1,
      -1,    64,    -1,    66,    67,    68,    -1,    -1,    -1,    -1,
      -1,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    22,    -1,    -1,    -1,    64,
      -1,    66,    67,    68,    -1,    -1,    -1,    -1,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    25,    -1,    -1,    -1,    64,    -1,    66,
      67,    68,    -1,    -1,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    25,    -1,
      -1,    -1,    64,    -1,    66,    67,    68,    -1,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    26,    -1,    -1,    -1,    64,    -1,    66,
      67,    68,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    28,    -1,
      -1,    64,    -1,    66,    67,    68,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    30,    64,    -1,    66,    67,    68,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    64,    32,    66,
      67,    68,    36,    37,    38,    39,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      64,    -1,    66,    67,    68,    36,    37,    38,    39,    -1,
      41,    42,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    64,    -1,    66,    67,    68,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    64,    -1,    66,    67,
      68,    36,    37,    38,    39,    -1,    41,    42,    43,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    61,    -1,    -1,    64,
      -1,    66,    67,    68,    36,    37,    38,    39,    -1,    41,
      42,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    54,    55,    56,    57,    58,    59,    -1,    -1,
      -1,    -1,    64,    -1,    66,    67,    68,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    45,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    -1,    -1,    -1,    -1,    64,    -1,    66,    67,    68,
      36,    37,    38,    39,    -1,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,
      56,    57,    58,    59,    -1,    -1,    -1,    -1,    64,    -1,
      66,    67,    68,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    64,    -1,    66,    67,    68,    36,    37,    38,    39,
      -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,    49,
      -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,    59,
      -1,    -1,    -1,    -1,    64,    -1,    66,    67,    68,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    -1,    64,    -1,    66,
      67,    68,    36,    37,    38,    -1,    -1,    41,    42,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      54,    55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    66,    67,    68,    36,    -1,    38,    -1,    -1,
      41,    42,    43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    54,    55,    56,    57,    58,    59,    -1,
      -1,    -1,    -1,    36,    -1,    66,    67,    68,    41,    42,
      43,    -1,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    54,    55,    56,
      57,    58,    59,    66,    67,    68,    41,    42,    -1,    66,
      67,    68,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,
      55,    56,    57,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    83,     1,     4,     5,     6,     7,     8,     9,
      46,    84,    85,    86,    87,    92,    96,    97,    98,   136,
       0,    18,    48,    62,    77,    99,   101,   102,    99,    99,
      99,    99,    99,    99,   152,   153,   154,   155,    85,    17,
      19,    20,    24,    31,    33,    34,    35,    40,    41,    42,
      44,    46,    52,    71,    72,    73,    74,    75,    76,    93,
      94,    95,   102,   113,   114,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   128,   129,   130,   131,
     132,   133,   134,   135,   101,    62,    44,   106,    43,   106,
      43,    50,    44,   122,    47,    53,    46,    99,   103,   104,
     104,   104,   122,   104,   122,   122,   122,     1,    56,   122,
       1,    47,   122,   126,   102,    53,    49,    44,   127,    36,
      37,    38,    39,    41,    42,    43,    54,    55,    56,    57,
      58,    59,    63,    64,    66,    67,    68,    63,    99,     1,
     104,   105,    63,    48,    43,    63,   102,   107,   108,   109,
     110,   111,    90,    91,   107,   122,    84,   152,   153,    50,
      43,    18,    18,    25,    18,    45,   122,    45,    53,    47,
      61,    47,    53,    93,     1,    45,   122,   126,   122,   122,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   122,   122,   122,   122,   122,   122,    45,    45,    53,
     107,    99,   100,    12,    14,    16,    17,    19,    20,    21,
      23,    24,    27,    44,    48,    69,   129,   130,   137,   139,
     140,   141,   144,   145,   146,   147,   148,   149,   150,   151,
     107,    54,    60,    56,    63,    47,   107,   122,   122,   122,
     122,   122,    45,   126,   122,   122,    45,    45,   104,    43,
      49,    53,     1,   137,   138,     1,   138,   104,   104,   104,
     137,   129,   130,   122,   122,     1,   138,     1,   138,    65,
      43,    91,   107,   112,   122,   107,   107,   103,    18,    30,
      22,    26,    32,   127,    45,    47,   122,    99,    13,    13,
     137,    15,    15,    43,    18,    18,    25,    28,    49,    49,
      70,    70,   122,   137,    63,    53,    55,    11,    89,   122,
     122,   122,   122,   122,   122,   122,   122,   137,    48,   107,
     107,    48,    10,    88,    18,    22,    22,    26,     1,    29,
      51,   122,   142,   143,    55,   122,    48,   137,   137,   137,
     137,    49,    50,    50,    50,   143,    49,    49,    95,   137,
     137,   137,    49
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    82,    83,    84,    84,    84,    84,    84,    84,    85,
      85,    86,    86,    87,    87,    88,    88,    89,    89,    90,
      90,    91,    91,    92,    92,    93,    93,    93,    94,    94,
      95,    95,    96,    97,    98,    99,    99,   100,   100,   101,
     101,   102,   102,   103,   103,   104,   104,   105,   105,   106,
     106,   106,   107,   107,   107,   107,   108,   109,   110,   111,
     112,   112,   113,   113,   113,   113,   113,   113,   113,   113,
     114,   115,   115,   116,   117,   117,   118,   119,   120,   121,
     122,   122,   122,   122,   122,   122,   122,   122,   122,   122,
     122,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   123,   123,   124,   125,   125,   125,   126,   126,   127,
     127,   127,   128,   129,   129,   130,   131,   132,   133,   134,
     135,   136,   136,   137,   137,   137,   137,   137,   137,   137,
     137,   137,   137,   137,   138,   138,   139,   140,   140,   141,
     141,   142,   142,   142,   143,   143,   144,   145,   146,   147,
     148,   148,   148,   148,   149,   149,   149,   149,   150,   151,
     151,   151,   151,   152,   152,   153,   153,   154,   155
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     1,     1,     4,
       1,     2,     1,     8,     1,     4,     0,     4,     0,     3,
       1,     1,     0,     2,     4,     1,     3,     3,     3,     1,
       1,     0,     7,     6,     4,     1,     1,     3,     1,     3,
       1,     1,     2,     3,     1,     4,     1,     3,     1,     3,
       3,     0,     1,     1,     1,     1,     1,     4,     6,     3,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     2,     2,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     5,     2,     3,     3,     3,     1,     3,
       3,     2,     5,     1,     2,     5,     6,     6,     6,     6,
       6,     5,     7,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     1,     1,     4,     6,     6,
       6,     3,     3,     3,     2,     1,     6,     6,     6,     2,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       1,     2,     1,     1,     1,     3,     1,     1,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"derived\"", "\"enum\"", "\"rule\"", "\"type\"", "\"function\"",
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
  "EnumerationDefinition", "TypeDefinition", "Identifier", "Identifiers",
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
       0,   352,   352,   364,   368,   372,   376,   380,   384,   392,
     398,   406,   412,   422,   438,   446,   450,   458,   462,   470,
     476,   486,   490,   498,   521,   539,   547,   557,   568,   574,
     584,   588,   596,   604,   612,   620,   624,   632,   638,   648,
     654,   664,   668,   676,   680,   689,   695,   703,   709,   719,
     723,   727,   735,   739,   743,   747,   755,   763,   771,   779,
     787,   793,   803,   807,   811,   815,   819,   823,   827,   831,
     839,   847,   852,   861,   877,   889,   905,   921,   937,   953,
     961,   965,   969,   973,   977,   981,   985,   989,   993,   997,
    1001,  1009,  1013,  1017,  1021,  1025,  1029,  1033,  1037,  1041,
    1045,  1049,  1053,  1057,  1061,  1065,  1069,  1073,  1077,  1081,
    1085,  1089,  1093,  1101,  1109,  1114,  1118,  1126,  1132,  1142,
    1146,  1150,  1159,  1169,  1174,  1182,  1190,  1198,  1206,  1214,
    1222,  1230,  1235,  1244,  1248,  1252,  1256,  1260,  1264,  1268,
    1272,  1276,  1280,  1284,  1292,  1298,  1308,  1316,  1320,  1328,
    1332,  1340,  1344,  1348,  1356,  1362,  1372,  1380,  1388,  1396,
    1404,  1408,  1412,  1417,  1426,  1430,  1434,  1439,  1448,  1458,
    1464,  1471,  1477,  1488,  1492,  1500,  1506,  1516,  1524
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
#line 3860 "GrammarParser.cpp" // lalr1.cc:1167
#line 1530 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
