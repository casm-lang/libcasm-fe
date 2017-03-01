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
#line 66 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    yy::Parser::symbol_type yylex( libcasm_fe::Driver& driver );

    std::pair< FunctionDefinition::Classification, bool > parseFunctionAttributes(
        libcasm_fe::Driver& driver, const NodeList< IdentifierNode >::Ptr& attributes )
    {
        using Classification = FunctionDefinition::Classification;

        auto functionClass = Classification::CONTROLLED;
        bool symbolicFunction = false;

        bool classAttributeAlreadyUsed = false;
        IdentifierNode::Ptr classAttribute;

        bool symbolicAttributeAlreadyUsed = false;
        IdentifierNode::Ptr symbolicAttribute;

        for( auto attribute : attributes )
        {
            const auto& name = attribute->identifier();

            if( name == "symbolic" )
            {
                symbolicFunction = true;

                if( symbolicAttributeAlreadyUsed )
                {
                    driver.error
                    ( { symbolicAttribute->location(), attribute->location() }
                    , "`symbolic` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfSymbolic
                    );
                }
                else
                {
                    symbolicAttributeAlreadyUsed = true;
                    symbolicAttribute = attribute;
                }

                continue;
            }

            if( name == "in" or name == "monitored" )
            {
                functionClass = Classification::IN;
            }
            else if( name == "controlled" )
            {
                functionClass = Classification::CONTROLLED;
            }
            else if( name == "shared" )
            {
                functionClass = Classification::SHARED;
            }
            else if( name == "out" )
            {
                functionClass = Classification::OUT;
            }
            else if( name == "static" )
            {
                functionClass = Classification::STATIC;
            }
            else
            {
                driver.error
                ( attribute->location(),
                , "`" + name + "` is no valid function attribute, only in, monitored, "
                + "controlled, shared, out, static and symbolic are allowed"
                , libcasm_fe::Codes::FunctionAttributeIsInvalid
                );
            }

            if( classAttributeAlreadyUsed )
            {
                driver.error
                ( { classAttribute->location(), attribute->location() }
                , "a function classifier attribute can only be used once per function"
                , libcasm_fe::Codes::FunctionAttributeMultipleUseOfFunctionClassifier
                );
            }
            else
            {
                classAttributeAlreadyUsed = true;
                classAttribute = attribute;
            }
        }

        return { functionClass, symbolicFunction };
    }

    static FunctionDefinition::Ptr createProgramFunction( yy::location& location )
    {
        //auto argTypes = { new Type( TypeType::AGENT ) }; // TODO add args and return type
        //auto retType = new Type( TypeType::RuleReference );

        const auto program = make< IdentifierNode >( location, "program" );
        return make< FunctionDefinition >( location, program, nullptr, nullptr );
    }

    static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
    {
        if( (rule->id() == Node::BLOCK_RULE )
                or (rule->id() == Node::SEQUENCE_RULE ) )
        {
            return rule; // no need to wrap it
        }

        return make< BlockRule >( rule );
    }

#line 164 "GrammarParser.cpp" // lalr1.cc:413


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


namespace yy {
#line 250 "GrammarParser.cpp" // lalr1.cc:479

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
  Parser::Parser ()
#if YYDEBUG
     :yydebug_ (false),
      yycdebug_ (&std::cerr)
#endif
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
      case 101: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 139: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 142: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 134: // CaseLabel
        value.move< CaseRule::Case > (that.value);
        break;

      case 133: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 102: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 125: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 132: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 80: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 81: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 123: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 93: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 127: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 117: // Expression
      case 118: // Term
        value.move< Expression::Ptr > (that.value);
        break;

      case 119: // Expressions
      case 120: // MaybeExpressions
      case 121: // Arguments
      case 122: // MaybeArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 103: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 137: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 94: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
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

      case 116: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 115: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 104: // RangedType
        value.move< RangedType::Ptr > (that.value);
        break;

      case 129: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 128: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 114: // RuleReference
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

      case 79: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 100: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 107: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 126: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 89: // Initializer
      case 141: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 97: // Variable
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

      case 135: // CaseLabels
        value.move< std::vector< CaseRule::Case > > (that.value);
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
      case 101: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 139: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 142: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 134: // CaseLabel
        value.copy< CaseRule::Case > (that.value);
        break;

      case 133: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 102: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 125: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 132: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 80: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 81: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 92: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 123: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 93: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 127: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 117: // Expression
      case 118: // Term
        value.copy< Expression::Ptr > (that.value);
        break;

      case 119: // Expressions
      case 120: // MaybeExpressions
      case 121: // Arguments
      case 122: // MaybeArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 103: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 137: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 94: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
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

      case 116: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 115: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 104: // RangedType
        value.copy< RangedType::Ptr > (that.value);
        break;

      case 129: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 128: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 114: // RuleReference
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

      case 79: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 100: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 107: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 126: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 89: // Initializer
      case 141: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 97: // Variable
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

      case 135: // CaseLabels
        value.copy< std::vector< CaseRule::Case > > (that.value);
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


    // User initialization code.
    #line 54 "../../obj/src/GrammarParser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
}

#line 936 "GrammarParser.cpp" // lalr1.cc:741

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
      case 101: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 139: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 142: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 134: // CaseLabel
        yylhs.value.build< CaseRule::Case > ();
        break;

      case 133: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 102: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 125: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 132: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 80: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 81: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 92: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 123: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 93: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 127: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 84: // MaybeDefined
      case 106: // Atom
      case 117: // Expression
      case 118: // Term
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 119: // Expressions
      case 120: // MaybeExpressions
      case 121: // Arguments
      case 122: // MaybeArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 103: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 137: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 82: // FunctionDefinition
      case 88: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 94: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
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

      case 116: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 87: // MaybeFunctionAttributes
      case 95: // Identifiers
      case 96: // MaybeIdentifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 83: // MaybeInitially
      case 90: // Initializers
      case 91: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 98: // Parameters
      case 99: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 115: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 104: // RangedType
        yylhs.value.build< RangedType::Ptr > ();
        break;

      case 129: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 128: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 114: // RuleReference
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

      case 79: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 100: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 85: // FunctionParameters
      case 86: // MaybeFunctionParameters
      case 105: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 107: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 126: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 89: // Initializer
      case 141: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 108: // Boolean
      case 109: // String
      case 110: // BitNumber
      case 111: // IntegerNumber
      case 112: // FloatingNumber
      case 113: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 97: // Variable
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

      case 135: // CaseLabels
        yylhs.value.build< std::vector< CaseRule::Case > > ();
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
#line 362 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& filepath = driver.get_filename();
      const std::string& filename
          = filepath.substr( filepath.find_last_of( "/\\" ) + 1 );
      const std::string& filenameWithoutExtension
          = filename.substr( 0, filename.rfind( "." ) );

      const auto name = make< IdentifierNode >( filenameWithoutExtension );
      const auto specification = make< Specification >( yylhs.location, name, yystack_[0].value.as< Definitions::Ptr > () );

      //driver.result = specification; TODO
  }
#line 1263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 379 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 383 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 387 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1287 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1305 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 405 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 415 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = make< FunctionDefinition >( yylhs.location, yystack_[6].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< Types::Ptr > (), yystack_[2].value.as< Type::Ptr > () );

      const auto attributes = parseFunctionAttributes( driver, yystack_[7].value.as< NodeList< IdentifierNode >::Ptr > () );
      function->setClassification( attributes.first );
      function->setSymbolic( attributes.second );

      function->setDefaultValue( yystack_[1].value.as< Expression::Ptr > () );

      // apply the name of the function declaration to the initializer functions
      auto initializers = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto initializer : *initializers) {
           initializer->function()->setIdentifier( functionDefinition->identifier() );
      }
      function->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = function;
  }
#line 1338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1354 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1362 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 454 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1370 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1378 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 466 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1398 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 482 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1406 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 486 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = make< Types >( yylhs.location );
  }
#line 1414 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 498 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1430 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 506 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction();

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
#line 1451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 523 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction();

      // apply the name of the program declaration to the initializer functions
      auto initializers = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
      for (auto initializer : *initializers) {
          initializer->function()->setIdentifier( programDefinition->identifier() );
      }
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1468 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 540 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto arguments = make< Expressions >( yylhs.location );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 549 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, args );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1496 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 560 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1508 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 572 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1518 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1528 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 588 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 600 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1552 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1560 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1568 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1578 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 630 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = make< NodeList< Identifier > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 640 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[0].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 644 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< Identifier > >( yylhs.location );
  }
#line 1604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 652 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1612 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 656 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), ... ); // TODO
  }
#line 1620 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1630 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 670 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1640 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 680 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1648 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 684 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1656 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1664 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 696 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1672 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 700 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1680 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1688 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1696 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1704 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1712 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 736 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1720 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 744 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1730 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 768 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 776 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1780 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 784 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1796 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1804 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 796 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 804 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 818 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 827 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), 2 );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), 16 );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 841 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 850 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1875 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 859 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1884 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 868 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleReferenceAtom::Ptr > () = make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 876 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 884 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 1908 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 892 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 1916 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 896 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1924 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 900 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 1932 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 904 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 1940 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 908 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 1948 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 912 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call power builtin
  }
#line 1956 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 916 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 1964 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 920 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 1972 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 1980 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 1988 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 1996 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2004 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 940 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2012 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 944 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 948 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 952 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO add implies instruction
  }
#line 2036 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2044 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 960 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2052 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2060 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 972 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2068 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto zero = make< ZeroAtom >( yylhs.location );
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, zero, yystack_[0].value.as< Expression::Ptr > (),
                                               libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2086 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2094 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2102 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2110 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2118 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2126 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2134 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2142 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2162 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1034 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[0].value.as< Expressions::Ptr > ();
  }
#line 2170 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1038 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = make< Expressions >( yylhs.location );
  }
#line 2178 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1046 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2186 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1054 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[0].value.as< Expressions::Ptr > ();
  }
#line 2194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1058 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = make< Expressions >( yylhs.location );
  }
#line 2202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = make< IndirectCallExpression >( yylhs.location, yystack_[1].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2218 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2226 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), nullptr,
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) ); // TODO nullptr -> void
  }
#line 2251 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1111 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2260 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1120 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1124 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1128 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2284 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1132 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2292 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1136 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2300 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1140 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2308 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1144 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2316 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1148 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2324 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1152 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2332 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1156 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2340 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1164 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2350 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1170 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1180 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = make< SkipRule >( yylhs.location );
  }
#line 2368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1188 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1200 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< std::vector< CaseRule::Case > > () );
  }
#line 2392 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1208 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1213 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2410 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1218 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2418 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1226 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = std::move( yystack_[0].value.as< std::vector< CaseRule::Case > > () );
      yylhs.value.as< std::vector< CaseRule::Case > > ().push_back( yystack_[1].value.as< CaseRule::Case > () );
  }
#line 2427 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1231 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = { yystack_[0].value.as< CaseRule::Case > () };
  }
#line 2435 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1239 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2443 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1247 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1255 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1263 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2467 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1267 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1275 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2483 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1279 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1287 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1295 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), { CallExpression::TargetType::RULE } );
  }
#line 2507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1299 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
#line 2515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1303 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), { CallExpression::TargetType::RULE } );
  }
#line 2523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1307 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
#line 2531 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2535 "GrammarParser.cpp" // lalr1.cc:859
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

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      14,    89,    28,   -40,   -44,   -44,   -44,   -12,  -135,    89,
    -135,  -135,  -135,  -135,  -135,  -135,   540,  -135,  -135,   -11,
       6,   -11,   -44,   -44,  -135,   -44,   595,   -44,  -135,  -135,
    -135,   595,   650,   650,   595,   595,   -20,   650,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,     2,     8,    29,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,   863,
    -135,    11,  -135,  -135,  -135,  -135,  -135,   -44,    39,    53,
     -36,  -135,    50,    61,    58,    67,    95,   595,   672,   106,
    -135,  -135,  -135,   893,    73,    82,   923,    81,  -135,    29,
     540,  -135,   595,  -135,  -135,   595,   595,   595,   595,   595,
     595,   595,   595,   595,   595,   595,   595,   595,   595,   595,
     595,   595,   595,  -135,   -27,   -44,   -44,   476,   -44,   -44,
    -135,   -44,   -44,   595,   893,   595,   595,  -135,   595,  -135,
     595,  -135,  -135,  -135,  1073,  1182,  1163,   206,  1133,    65,
      65,   287,    -6,    -6,    70,    70,    70,  -135,  1073,   287,
      -6,    -6,  1073,  -135,   -44,   -33,    87,  -135,  -135,  -135,
    -135,    45,   476,   476,  -135,   -44,   -44,   476,   -47,   595,
     595,   476,   476,    71,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,    91,  -135,    76,    74,
    -135,  -135,   803,   741,   833,  1073,   953,  -135,   -44,   595,
     595,  -135,  -135,   343,   356,    93,   119,  -135,  -135,  -135,
     707,   773,   408,   421,   595,   476,   -44,   -44,   595,   595,
     595,  -135,  -135,   -14,   983,  1073,  -135,  -135,  -135,   595,
     595,   476,    92,  -135,  -135,  1073,  -135,  -135,   127,  -135,
    1073,  -135,  -135,   -44,   595,   595,     4,   267,   115,   485,
      96,   134,  -135,  1103,   476,   476,   476,    97,   100,  1013,
     485,   103,   595,    98,  -135,   595,  -135,  -135,  -135,   476,
     476,   476,  -135,  -135,  1043,   540,  -135,  -135,  -135,  -135,
     104,  -135
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,    20,     8,     2,
       3,    10,     4,     6,     5,     1,    29,    32,    21,    42,
       0,    42,    36,     0,     7,     0,     0,     0,    61,    63,
      62,     0,     0,     0,   105,   105,     0,     0,    65,    66,
      67,    69,    68,    64,    27,    28,     0,   108,   101,    59,
      60,    58,    54,    55,    56,    57,    53,   100,    99,    23,
      90,     0,    94,    95,    96,    97,    98,     0,     0,     0,
       0,    34,    35,     0,     0,    38,     0,     0,     0,     0,
      89,    92,    93,   103,   104,     0,   103,     0,    70,     0,
       0,    22,   105,   107,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    40,     0,     0,     0,     0,     0,     0,
      19,    18,     0,     0,     0,     0,     0,    91,     0,   106,
       0,    72,   110,    26,   103,    87,    85,    86,    88,    73,
      74,    80,    81,    82,    75,    76,    77,    78,    24,    79,
      83,    84,    25,    41,     0,    47,     0,    43,    44,    45,
      46,     0,     0,     0,   128,     0,     0,     0,     0,     0,
       0,     0,     0,   146,   148,   114,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,     0,    33,    17,     0,
      16,    37,     0,     0,     0,   102,     0,    39,     0,     0,
       0,    31,   127,     0,     0,     0,     0,   139,   145,   147,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    71,    52,     0,     0,    30,   143,   126,   141,     0,
       0,     0,     0,   140,   142,   144,   115,    15,    14,   112,
     111,   113,    48,     0,    49,     0,     0,     0,   129,     0,
       0,    12,    51,     0,     0,     0,     0,     0,     0,     0,
     136,     0,     0,     0,     9,    50,   137,   138,   130,     0,
       0,     0,   135,   131,     0,    29,   132,   133,   134,    13,
       0,    11
  };

  const short int
  Parser::yypgoto_[] =
  {
    -135,  -135,   145,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,    66,  -135,  -120,  -135,  -135,    -3,    41,  -135,   -23,
    -135,   137,  -106,  -135,  -135,  -135,  -135,  -135,  -135,  -135,
    -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,  -135,   -21,
      33,  -135,   124,   -41,  -135,     3,    64,  -135,  -135,  -135,
    -135,    84,  -134,  -135,  -135,  -135,  -135,  -100,  -135,  -135,
    -135,  -135,  -135,  -135,  -135
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     8,     9,    10,   264,   251,   188,   189,    23,
      11,    44,    45,    46,    12,    13,    47,    72,    73,    76,
     114,    68,   156,   157,   158,   159,   160,   223,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    84,    85,    61,    94,    62,    63,    64,    65,    66,
      14,   202,   203,   176,   177,   178,   260,   261,   179,   180,
     181,   182,   183,   184,   185
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      18,    19,    20,    21,    79,    78,    93,   117,    16,    37,
      80,   198,   186,    83,    86,   190,   191,     1,   153,    71,
      74,   199,    75,   254,    75,   118,   154,    17,    15,   204,
      17,   242,    22,    67,    17,    99,   100,   212,   213,   243,
      95,    96,    97,    98,   113,    99,   100,   101,   132,    69,
     104,   105,   106,   107,    88,    90,   124,    91,   102,   103,
     104,   105,   106,   107,    75,    81,    82,   109,   110,   111,
      89,   134,   112,    92,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   222,     3,   201,     4,     5,     6,   119,     7,
     115,   116,   192,   119,   193,   194,   120,   195,   121,   196,
     237,   238,   155,    71,   123,   155,   187,   122,   155,   155,
     173,   104,   105,   106,   107,   126,   128,   129,   131,   107,
     200,   197,   216,   214,   215,   217,   229,   252,   230,   250,
     249,   256,   205,   206,   262,   263,   275,   269,   210,   211,
     270,    75,   273,   281,    24,   280,   133,   161,    70,    87,
     272,     0,    75,    75,     0,   173,   173,     0,     0,     0,
     173,   208,     0,     0,   173,   173,     0,     0,   224,   225,
       0,   174,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   235,     0,   155,     0,   239,   240,   241,
       0,   175,     0,     0,     0,     0,   173,   173,   246,   247,
       0,     0,     0,   155,   155,   173,   173,     0,   173,     0,
       0,     0,     0,   143,   253,     0,   174,   174,   259,     0,
       0,   174,   209,     0,   173,   174,   174,     0,     0,   259,
     155,   274,    95,     0,   143,     0,     0,    99,   100,   101,
       0,   207,     0,     0,     0,     0,     0,   173,   173,   173,
     102,   103,   104,   105,   106,   107,     0,   174,   174,   109,
     110,   111,   173,   173,   173,     0,   174,   174,     0,   174,
       0,     0,     0,     0,     0,     0,     0,   227,   227,   255,
       0,     0,     0,     0,     0,   174,   227,   227,     0,   236,
       0,     0,     0,    95,    96,    97,    98,     0,    99,   100,
     101,     0,     0,     0,     0,   248,     0,     0,   174,   174,
     174,   102,   103,   104,   105,   106,   107,     0,    99,   100,
     109,   110,   111,   174,   174,   174,     0,     0,   266,   267,
     268,   102,   103,   104,   105,   106,   107,     0,     0,     0,
       0,   110,   111,   276,   277,   278,   162,   226,   163,     0,
     164,   165,     0,   166,   167,     0,   168,   169,     0,   162,
     170,   163,   228,   164,   165,     0,   166,   167,     0,   168,
     169,     0,     0,   170,     0,     0,     0,     0,     0,     0,
       0,   171,     0,     0,     0,     0,     0,     0,     0,    37,
       0,     0,     0,     0,   171,     0,     0,     0,     0,   172,
       0,     0,    37,     0,     0,     0,     0,    17,     0,     0,
       0,   162,   172,   163,     0,   164,   165,     0,   166,   167,
      17,   168,   169,     0,   162,   170,   163,     0,   164,   165,
       0,   166,   167,     0,   168,   169,     0,     0,   170,     0,
       0,     0,     0,     0,     0,     0,   171,   233,     0,     0,
       0,     0,     0,     0,    37,     0,     0,     0,     0,   171,
       0,     0,     0,     0,   172,     0,     0,    37,     0,     0,
       0,     0,    17,     0,     0,     0,     0,   172,   234,   162,
       0,   163,     0,   164,   165,    17,   166,   167,     0,   168,
     169,     0,     0,   170,     0,    25,     0,     0,     0,    26,
       0,     0,     0,     0,   257,     0,    27,     0,    28,    29,
      30,     0,     0,     0,   171,    31,    32,    33,     0,    77,
       0,    35,    37,     0,     0,     0,   258,    36,     0,     0,
       0,    37,   172,     0,     0,     0,     0,     0,     0,     0,
      17,     0,     0,    38,    39,    40,    41,    42,    43,    17,
      25,     0,     0,     0,    26,     0,     0,     0,     0,     0,
       0,    27,     0,    28,    29,    30,     0,     0,     0,     0,
      31,    32,    33,     0,    34,     0,    35,     0,     0,     0,
       0,     0,    36,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    39,
      40,    41,    42,    43,    17,    25,     0,     0,     0,    26,
       0,     0,     0,     0,     0,     0,    27,     0,    28,    29,
      30,     0,     0,     0,     0,    31,    32,    33,     0,    77,
       0,    35,     0,     0,     0,     0,     0,    36,     0,     0,
       0,    37,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    38,    39,    40,    41,    42,    43,    17,
      25,     0,     0,     0,    26,     0,     0,     0,     0,     0,
       0,    27,     0,    28,    29,    30,     0,     0,     0,     0,
       0,    32,    33,     0,    77,     0,    35,   125,     0,     0,
       0,     0,    36,     0,     0,     0,    37,     0,    95,    96,
      97,    98,     0,    99,   100,   101,     0,     0,    38,    39,
      40,    41,    42,    43,    17,     0,   102,   103,   104,   105,
     106,   107,   231,     0,     0,   109,   110,   111,     0,     0,
       0,     0,     0,    95,    96,    97,    98,     0,    99,   100,
     101,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   102,   103,   104,   105,   106,   107,   219,     0,     0,
     109,   110,   111,     0,     0,     0,     0,    95,    96,    97,
      98,     0,    99,   100,   101,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   102,   103,   104,   105,   106,
     107,   232,     0,     0,   109,   110,   111,     0,     0,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,   218,     0,     0,   109,   110,   111,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,     0,     0,   220,   109,   110,   111,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,     0,     0,     0,   109,   110,   111,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,     0,   108,     0,   109,   110,   111,    95,
      96,    97,    98,     0,    99,   100,   101,     0,   127,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,     0,     0,     0,   109,   110,   111,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,   130,     0,     0,   109,   110,   111,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
     221,     0,     0,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,     0,     0,     0,   109,   110,   111,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   244,   104,
     105,   106,   107,   245,     0,     0,   109,   110,   111,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,   271,     0,     0,     0,   102,   103,   104,
     105,   106,   107,     0,     0,     0,   109,   110,   111,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,   279,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,     0,     0,     0,   109,   110,   111,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,     0,     0,     0,   109,   110,   111,    95,
      96,    97,    98,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   265,   104,
     105,   106,   107,     0,     0,     0,   109,   110,   111,    95,
      96,    97,     0,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,     0,     0,     0,   109,   110,   111,    95,
       0,    97,     0,     0,    99,   100,   101,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   102,   103,   104,
     105,   106,   107,    99,   100,   101,   109,   110,   111,     0,
       0,     0,     0,     0,     0,     0,   102,   103,   104,   105,
     106,   107,     0,     0,     0,   109,   110,   111
  };

  const short int
  Parser::yycheck_[] =
  {
       3,     4,     5,     6,    27,    26,    47,    43,    48,    56,
      31,    44,   118,    34,    35,   121,   122,     3,    45,    22,
      23,    54,    25,    19,    27,    61,    53,    74,     0,   163,
      74,    45,    44,    44,    74,    41,    42,   171,   172,    53,
      36,    37,    38,    39,    67,    41,    42,    43,    89,    43,
      56,    57,    58,    59,    74,    53,    77,    49,    54,    55,
      56,    57,    58,    59,    67,    32,    33,    63,    64,    65,
      37,    92,    61,    44,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   112,   198,     4,    49,     6,     7,     8,    53,    10,
      61,    48,   123,    53,   125,   126,    45,   128,    50,   130,
     216,   217,   115,   116,    19,   118,   119,    50,   121,   122,
     117,    56,    57,    58,    59,    19,    53,    45,    47,    59,
      43,   154,    56,    62,    43,    61,    43,   243,    19,    12,
      48,    26,   165,   166,    48,    11,    48,    50,   169,   170,
      50,   154,    49,    49,     9,   275,    90,   116,    21,    35,
     260,    -1,   165,   166,    -1,   162,   163,    -1,    -1,    -1,
     167,   168,    -1,    -1,   171,   172,    -1,    -1,   199,   200,
      -1,   117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   214,    -1,   198,    -1,   218,   219,   220,
      -1,   117,    -1,    -1,    -1,    -1,   203,   204,   229,   230,
      -1,    -1,    -1,   216,   217,   212,   213,    -1,   215,    -1,
      -1,    -1,    -1,   244,   245,    -1,   162,   163,   249,    -1,
      -1,   167,   168,    -1,   231,   171,   172,    -1,    -1,   260,
     243,   262,    36,    -1,   265,    -1,    -1,    41,    42,    43,
      -1,   167,    -1,    -1,    -1,    -1,    -1,   254,   255,   256,
      54,    55,    56,    57,    58,    59,    -1,   203,   204,    63,
      64,    65,   269,   270,   271,    -1,   212,   213,    -1,   215,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   203,   204,    22,
      -1,    -1,    -1,    -1,    -1,   231,   212,   213,    -1,   215,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,   231,    -1,    -1,   254,   255,
     256,    54,    55,    56,    57,    58,    59,    -1,    41,    42,
      63,    64,    65,   269,   270,   271,    -1,    -1,   254,   255,
     256,    54,    55,    56,    57,    58,    59,    -1,    -1,    -1,
      -1,    64,    65,   269,   270,   271,    13,    14,    15,    -1,
      17,    18,    -1,    20,    21,    -1,    23,    24,    -1,    13,
      27,    15,    16,    17,    18,    -1,    20,    21,    -1,    23,
      24,    -1,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,    66,
      -1,    -1,    56,    -1,    -1,    -1,    -1,    74,    -1,    -1,
      -1,    13,    66,    15,    -1,    17,    18,    -1,    20,    21,
      74,    23,    24,    -1,    13,    27,    15,    -1,    17,    18,
      -1,    20,    21,    -1,    23,    24,    -1,    -1,    27,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    -1,    66,    -1,    -1,    56,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    66,    67,    13,
      -1,    15,    -1,    17,    18,    74,    20,    21,    -1,    23,
      24,    -1,    -1,    27,    -1,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    29,    -1,    31,    -1,    33,    34,
      35,    -1,    -1,    -1,    48,    40,    41,    42,    -1,    44,
      -1,    46,    56,    -1,    -1,    -1,    51,    52,    -1,    -1,
      -1,    56,    66,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      74,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      40,    41,    42,    -1,    44,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    20,    -1,    -1,    -1,    24,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    33,    34,
      35,    -1,    -1,    -1,    -1,    40,    41,    42,    -1,    44,
      -1,    46,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    56,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    68,    69,    70,    71,    72,    73,    74,
      20,    -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,
      -1,    31,    -1,    33,    34,    35,    -1,    -1,    -1,    -1,
      -1,    41,    42,    -1,    44,    -1,    46,    25,    -1,    -1,
      -1,    -1,    52,    -1,    -1,    -1,    56,    -1,    36,    37,
      38,    39,    -1,    41,    42,    43,    -1,    -1,    68,    69,
      70,    71,    72,    73,    74,    -1,    54,    55,    56,    57,
      58,    59,    25,    -1,    -1,    63,    64,    65,    -1,    -1,
      -1,    -1,    -1,    36,    37,    38,    39,    -1,    41,    42,
      43,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    54,    55,    56,    57,    58,    59,    26,    -1,    -1,
      63,    64,    65,    -1,    -1,    -1,    -1,    36,    37,    38,
      39,    -1,    41,    42,    43,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,    58,
      59,    28,    -1,    -1,    63,    64,    65,    -1,    -1,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    30,    -1,    -1,    63,    64,    65,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    32,    63,    64,    65,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    63,    64,    65,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    61,    -1,    63,    64,    65,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    63,    64,    65,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    64,    65,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      47,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    63,    64,    65,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    60,    -1,    -1,    63,    64,    65,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    63,    64,    65,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    63,    64,    65,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    63,    64,    65,    36,
      37,    38,    39,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    63,    64,    65,    36,
      37,    38,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    -1,    -1,    -1,    63,    64,    65,    36,
      -1,    38,    -1,    -1,    41,    42,    43,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,
      57,    58,    59,    41,    42,    43,    63,    64,    65,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    54,    55,    56,    57,
      58,    59,    -1,    -1,    -1,    63,    64,    65
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    79,     4,     6,     7,     8,    10,    80,    81,
      82,    88,    92,    93,   128,     0,    48,    74,    94,    94,
      94,    94,    44,    87,    80,    20,    24,    31,    33,    34,
      35,    40,    41,    42,    44,    46,    52,    56,    68,    69,
      70,    71,    72,    73,    89,    90,    91,    94,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   121,   123,   124,   125,   126,   127,    44,    99,    43,
      99,    94,    95,    96,    94,    94,    97,    44,   117,    97,
     117,   118,   118,   117,   119,   120,   117,   120,    74,   118,
      53,    49,    44,   121,   122,    36,    37,    38,    39,    41,
      42,    43,    54,    55,    56,    57,    58,    59,    61,    63,
      64,    65,    61,    97,    98,    61,    48,    43,    61,    53,
      45,    50,    50,    19,   117,    25,    19,    45,    53,    45,
      60,    47,   121,    89,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,    45,    53,    94,   100,   101,   102,   103,
     104,    95,    13,    15,    17,    18,    20,    21,    23,    24,
      27,    48,    66,   123,   124,   129,   131,   132,   133,   136,
     137,   138,   139,   140,   141,   142,   100,    94,    85,    86,
     100,   100,   117,   117,   117,   117,   117,    97,    44,    54,
      43,    49,   129,   130,   130,    97,    97,   129,   123,   124,
     117,   117,   130,   130,    62,    43,    56,    61,    30,    26,
      32,    47,   100,   105,   117,   117,    14,   129,    16,    43,
      19,    25,    28,    49,    67,   117,   129,   100,   100,   117,
     117,   117,    45,    53,    55,    60,   117,   117,   129,    48,
      12,    84,   100,   117,    19,    22,    26,    29,    51,   117,
     134,   135,    48,    11,    83,    55,   129,   129,   129,    50,
      50,    50,   135,    49,   117,    48,   129,   129,   129,    49,
      91,    49
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    78,    79,    80,    80,    80,    80,    81,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    87,
      87,    88,    88,    89,    89,    89,    90,    90,    91,    91,
      92,    93,    94,    95,    95,    96,    96,    97,    97,    98,
      98,    99,    99,   100,   100,   100,   100,   101,   102,   103,
     104,   105,   105,   106,   106,   106,   106,   106,   106,   106,
     106,   107,   108,   108,   109,   110,   110,   111,   112,   113,
     114,   115,   116,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   119,   119,   120,   120,   121,   122,   122,   123,
     124,   125,   126,   127,   128,   128,   129,   129,   129,   129,
     129,   129,   129,   129,   129,   129,   130,   130,   131,   132,
     132,   133,   134,   134,   134,   135,   135,   136,   137,   138,
     139,   139,   140,   140,   141,   142,   142,   142,   142
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     2,     1,     9,
       1,     4,     0,     4,     0,     3,     1,     1,     0,     3,
       0,     2,     4,     1,     3,     3,     3,     1,     1,     0,
       7,     6,     1,     3,     1,     1,     0,     3,     1,     3,
       1,     3,     0,     1,     1,     1,     1,     1,     4,     4,
       6,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       1,     3,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     1,     0,     3,     1,     0,     2,
       3,     6,     6,     6,     5,     7,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     1,     1,     4,
       6,     6,     3,     3,     3,     2,     1,     6,     6,     2,
       3,     3,     3,     3,     3,     2,     1,     2,     1
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
  "UASTERIX", "$accept", "Specification", "Definition", "Definitions",
  "FunctionDefinition", "MaybeInitially", "MaybeDefined",
  "FunctionParameters", "MaybeFunctionParameters",
  "MaybeFunctionAttributes", "ProgramFunctionDefinition", "Initializer",
  "Initializers", "MaybeInitializers", "DerivedDefinition",
  "EnumerationDefinition", "Identifier", "Identifiers", "MaybeIdentifiers",
  "Variable", "Parameters", "MaybeParameters", "Type", "BasicType",
  "ComposedType", "FixedSizedType", "RangedType", "Types", "Atom",
  "Undefined", "Boolean", "String", "BitNumber", "IntegerNumber",
  "FloatingNumber", "RationalNumber", "RuleReference", "Range", "List",
  "Expression", "Term", "Expressions", "MaybeExpressions", "Arguments",
  "MaybeArguments", "DirectCallExpression", "IndirectCallExpression",
  "ConditionalExpression", "UniversalQuantifierExpression",
  "ExistentialQuantifierExpression", "RuleDefinition", "Rule", "Rules",
  "SkipRule", "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels",
  "LetRule", "ForallRule", "IterateRule", "BlockRule", "SequenceRule",
  "UpdateRule", "CallRule", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   361,   361,   378,   382,   386,   390,   398,   404,   414,
     433,   441,   445,   453,   457,   465,   471,   481,   485,   493,
     497,   505,   522,   539,   548,   559,   571,   577,   587,   591,
     599,   607,   615,   623,   629,   639,   643,   651,   655,   663,
     669,   679,   683,   691,   695,   699,   703,   711,   719,   727,
     735,   743,   749,   759,   763,   767,   771,   775,   779,   783,
     787,   795,   803,   808,   817,   826,   831,   840,   849,   858,
     867,   875,   883,   891,   895,   899,   903,   907,   911,   915,
     919,   923,   927,   931,   935,   939,   943,   947,   951,   955,
     959,   967,   971,   975,   981,   985,   989,   993,   997,  1001,
    1005,  1009,  1017,  1023,  1033,  1037,  1045,  1053,  1057,  1065,
    1073,  1081,  1089,  1097,  1105,  1110,  1119,  1123,  1127,  1131,
    1135,  1139,  1143,  1147,  1151,  1155,  1163,  1169,  1179,  1187,
    1191,  1199,  1207,  1212,  1217,  1225,  1230,  1238,  1246,  1254,
    1262,  1266,  1274,  1278,  1286,  1294,  1298,  1302,  1306
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



} // yy
#line 3312 "GrammarParser.cpp" // lalr1.cc:1167
#line 1312 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void yy::Parser::error
( const location_type& l
, const std::string& m
)
{
    if( m.compare( "syntax error, unexpected end of file, expecting CASM" ) == 0 )
    {
        i32 pos = (l.begin.line - 1);
        pos = ( pos > 0 ? pos : 1 );

        driver.error
        ( yy::location( yy::position( 0, pos, 1 ) )
        , m
        , libcasm_fe::Codes::SyntaxError
        );
    }
    else
    {
        driver.error( l, m, libcasm_fe::Codes::SyntaxError );
    }
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
