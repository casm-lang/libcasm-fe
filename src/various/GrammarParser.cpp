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
      case 97: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 133: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 136: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 128: // CaseLabel
        value.move< CaseRule::Case > (that.value);
        break;

      case 127: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 98: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 121: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 126: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 76: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 77: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 88: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 119: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 89: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 80: // MaybeDefined
      case 102: // Atom
      case 113: // Expression
      case 114: // Term
        value.move< Expression::Ptr > (that.value);
        break;

      case 115: // Expressions
      case 116: // MaybeExpressions
      case 117: // Arguments
      case 118: // MaybeArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 99: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 131: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 78: // FunctionDefinition
      case 84: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 90: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
        break;

      case 120: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 132: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 130: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 112: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 83: // MaybeFunctionAttributes
      case 91: // Identifiers
      case 92: // MaybeIdentifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 79: // MaybeInitially
      case 86: // Initializers
      case 87: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 94: // Parameters
      case 95: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 111: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 100: // RangedType
        value.move< RangedType::Ptr > (that.value);
        break;

      case 123: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 122: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 110: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 124: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 134: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 125: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 75: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 96: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 81: // FunctionParameters
      case 82: // MaybeFunctionParameters
      case 101: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 103: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 85: // Initializer
      case 135: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 104: // Boolean
      case 105: // String
      case 106: // BitNumber
      case 107: // IntegerNumber
      case 108: // FloatingNumber
      case 109: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 93: // Variable
        value.move< VariableDefinition::Ptr > (that.value);
        break;

      case 64: // "binary"
      case 65: // "hexadecimal"
      case 66: // "integer"
      case 67: // "rational"
      case 68: // "floating"
      case 69: // "string"
      case 70: // "identifier"
        value.move< std::string > (that.value);
        break;

      case 129: // CaseLabels
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
      case 97: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 133: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 136: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 128: // CaseLabel
        value.copy< CaseRule::Case > (that.value);
        break;

      case 127: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 98: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 121: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 126: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 76: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 77: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 88: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 119: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 89: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 80: // MaybeDefined
      case 102: // Atom
      case 113: // Expression
      case 114: // Term
        value.copy< Expression::Ptr > (that.value);
        break;

      case 115: // Expressions
      case 116: // MaybeExpressions
      case 117: // Arguments
      case 118: // MaybeArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 99: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 131: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 78: // FunctionDefinition
      case 84: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 90: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
        break;

      case 120: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 132: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 130: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 112: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 83: // MaybeFunctionAttributes
      case 91: // Identifiers
      case 92: // MaybeIdentifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 79: // MaybeInitially
      case 86: // Initializers
      case 87: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 94: // Parameters
      case 95: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 111: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 100: // RangedType
        value.copy< RangedType::Ptr > (that.value);
        break;

      case 123: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 122: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 110: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 124: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 134: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 125: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 75: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 96: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 81: // FunctionParameters
      case 82: // MaybeFunctionParameters
      case 101: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 103: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 85: // Initializer
      case 135: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 104: // Boolean
      case 105: // String
      case 106: // BitNumber
      case 107: // IntegerNumber
      case 108: // FloatingNumber
      case 109: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 93: // Variable
        value.copy< VariableDefinition::Ptr > (that.value);
        break;

      case 64: // "binary"
      case 65: // "hexadecimal"
      case 66: // "integer"
      case 67: // "rational"
      case 68: // "floating"
      case 69: // "string"
      case 70: // "identifier"
        value.copy< std::string > (that.value);
        break;

      case 129: // CaseLabels
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

#line 920 "GrammarParser.cpp" // lalr1.cc:741

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
      case 97: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 133: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 136: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 128: // CaseLabel
        yylhs.value.build< CaseRule::Case > ();
        break;

      case 127: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 98: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 121: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 126: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 76: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 77: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 88: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 119: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 89: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 80: // MaybeDefined
      case 102: // Atom
      case 113: // Expression
      case 114: // Term
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 115: // Expressions
      case 116: // MaybeExpressions
      case 117: // Arguments
      case 118: // MaybeArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 99: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 131: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 78: // FunctionDefinition
      case 84: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 90: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
        break;

      case 120: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 132: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 130: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 112: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 83: // MaybeFunctionAttributes
      case 91: // Identifiers
      case 92: // MaybeIdentifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 79: // MaybeInitially
      case 86: // Initializers
      case 87: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 94: // Parameters
      case 95: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 111: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 100: // RangedType
        yylhs.value.build< RangedType::Ptr > ();
        break;

      case 123: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 122: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 110: // RuleReference
        yylhs.value.build< RuleReferenceAtom::Ptr > ();
        break;

      case 124: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 134: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 125: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 75: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 96: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 81: // FunctionParameters
      case 82: // MaybeFunctionParameters
      case 101: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 103: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 85: // Initializer
      case 135: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 104: // Boolean
      case 105: // String
      case 106: // BitNumber
      case 107: // IntegerNumber
      case 108: // FloatingNumber
      case 109: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 93: // Variable
        yylhs.value.build< VariableDefinition::Ptr > ();
        break;

      case 64: // "binary"
      case 65: // "hexadecimal"
      case 66: // "integer"
      case 67: // "rational"
      case 68: // "floating"
      case 69: // "string"
      case 70: // "identifier"
        yylhs.value.build< std::string > ();
        break;

      case 129: // CaseLabels
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
#line 353 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 382 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1281 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1291 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 425 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1322 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 433 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1330 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 437 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 445 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 449 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1354 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 457 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 463 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 473 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 477 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = make< Types >( yylhs.location );
  }
#line 1390 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 485 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1398 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1406 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1427 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 514 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1444 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto arguments = make< Expressions >( yylhs.location );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 540 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, args );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1472 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 551 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1484 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 563 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1494 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 569 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 579 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1512 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 583 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1520 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 591 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1528 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 607 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1554 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 621 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = make< NodeList< Identifier > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1564 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 631 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[0].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1572 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 635 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< Identifier > >( yylhs.location );
  }
#line 1580 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 643 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 647 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), ... ); // TODO
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 655 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1606 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 661 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1616 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 671 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1624 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 675 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1632 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 683 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1640 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 687 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1648 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 691 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1656 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 695 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1664 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 703 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1672 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 711 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1680 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1688 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1696 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1706 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 741 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 751 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1724 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 755 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1732 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 759 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 763 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 767 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 771 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 775 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 779 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1780 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 787 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 795 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 800 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1806 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1815 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 818 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), 2 );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1824 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 823 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), 16 );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1833 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 832 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1842 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 841 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1851 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 850 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1860 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 859 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleReferenceAtom::Ptr > () = make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1868 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 867 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 875 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 1884 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 883 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 1892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 891 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 1908 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 895 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 1916 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 899 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 1924 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 903 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call caret builtin
  }
#line 1932 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 907 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 1940 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 911 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 1948 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 915 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 1956 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 1964 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 923 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 1972 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 927 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 1980 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 931 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 1988 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 935 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 1996 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 939 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2004 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 943 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2012 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 947 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 955 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 959 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2036 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 963 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto zero = make< ZeroAtom >( yylhs.location );
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, zero, yystack_[0].value.as< Expression::Ptr > (),
                                               libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2046 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 969 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2054 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 973 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2062 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 977 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2070 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 985 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2086 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 989 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2094 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 997 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2104 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1003 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2114 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1013 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[0].value.as< Expressions::Ptr > ();
  }
#line 2122 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1017 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = make< Expressions >( yylhs.location );
  }
#line 2130 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1025 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2138 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1033 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[0].value.as< Expressions::Ptr > ();
  }
#line 2146 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1037 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = make< Expressions >( yylhs.location );
  }
#line 2154 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1045 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2162 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = make< IndirectCallExpression >( yylhs.location, yystack_[1].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2170 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1061 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2178 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1069 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), nullptr,
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) ); // TODO nullptr -> void
  }
#line 2187 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2196 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1083 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2204 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1087 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2212 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1091 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2220 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2228 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1099 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2236 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1103 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2244 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1107 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2252 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1111 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2260 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1115 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1119 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1127 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2286 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = make< SkipRule >( yylhs.location );
  }
#line 2304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1151 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2312 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1163 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< std::vector< CaseRule::Case > > () );
  }
#line 2328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1171 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2337 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1176 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1181 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2354 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1189 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = std::move( yystack_[0].value.as< std::vector< CaseRule::Case > > () );
      yylhs.value.as< std::vector< CaseRule::Case > > ().push_back( yystack_[1].value.as< CaseRule::Case > () );
  }
#line 2363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1194 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = { yystack_[0].value.as< CaseRule::Case > () };
  }
#line 2371 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1202 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2379 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1210 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2387 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1218 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2395 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1226 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2403 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1230 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2411 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2419 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1242 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2427 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1250 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2435 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1258 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), { CallExpression::TargetType::RULE } );
  }
#line 2443 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1262 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
#line 2451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1266 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), { CallExpression::TargetType::RULE } );
  }
#line 2459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1270 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
#line 2467 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2471 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -142;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
       2,   111,    17,   -42,   -52,   -52,   -52,   -16,  -142,   111,
    -142,  -142,  -142,  -142,  -142,  -142,   494,  -142,  -142,    -9,
      20,    -9,   -52,   -52,  -142,   541,  -142,  -142,  -142,   541,
     588,   588,   541,   541,    10,   588,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,    45,    53,    56,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,    51,  -142,    40,
    -142,  -142,  -142,   -52,    59,    65,   -38,  -142,    71,    82,
      78,   541,   609,  -142,  -142,  -142,   728,    77,    84,   757,
      89,  -142,    56,   494,  -142,   541,  -142,  -142,   541,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   541,    81,  -142,    12,   -52,   -52,
     438,   -52,   -52,  -142,   -52,   728,   541,  -142,   541,  -142,
     541,  -142,  -142,  -142,   902,  1004,   960,   985,     3,     3,
     114,    76,    76,    87,    87,    87,  -142,   902,   114,    76,
      76,   902,   -52,  -142,   -52,   -20,    94,  -142,  -142,  -142,
    -142,   -33,   438,   438,  -142,   -52,   -52,   438,   -41,   541,
     541,   438,   438,    86,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,    97,  -142,    93,    90,
    -142,   670,   902,   786,  -142,  -142,   -52,   541,   541,  -142,
    -142,   313,   326,   100,   127,  -142,  -142,  -142,   640,   699,
     374,   387,   541,   438,   -52,   -52,   541,  -142,  -142,    13,
     815,   902,  -142,  -142,  -142,   541,   541,   438,   109,  -142,
    -142,   902,  -142,  -142,   144,   902,  -142,   -52,   541,   541,
     246,   -12,   131,   447,   116,   150,  -142,   931,   438,   438,
     438,   124,   126,   844,   447,   133,   541,   132,  -142,   541,
    -142,  -142,  -142,   438,   438,   438,  -142,  -142,   873,   494,
    -142,  -142,  -142,  -142,   134,  -142
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,    20,     8,     2,
       3,    10,     4,     6,     5,     1,    29,    32,    21,    42,
       0,    42,    36,     0,     7,     0,    61,    63,    62,     0,
       0,     0,   102,   102,     0,     0,    65,    66,    67,    69,
      68,    64,    27,    28,     0,   105,    98,    59,    60,    58,
      54,    55,    56,    57,    53,    97,    96,    23,    89,     0,
      93,    94,    95,     0,     0,     0,     0,    34,    35,     0,
       0,     0,     0,    88,    91,    92,   100,   101,     0,   100,
       0,    70,     0,     0,    22,   102,   104,   106,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    38,    40,     0,     0,     0,
       0,     0,     0,    19,    18,     0,     0,    90,     0,   103,
       0,    72,   107,    26,   100,    87,    85,    86,    73,    74,
      80,    81,    82,    75,    76,    77,    78,    24,    79,    83,
      84,    25,     0,    41,     0,    47,     0,    43,    44,    45,
      46,     0,     0,     0,   123,     0,     0,     0,     0,     0,
       0,     0,     0,   141,   143,   109,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,     0,    33,    17,     0,
      16,     0,    99,     0,    37,    39,     0,     0,     0,    31,
     122,     0,     0,     0,     0,   134,   140,   142,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    71,    52,     0,
       0,    30,   138,   121,   136,     0,     0,     0,     0,   135,
     137,   139,   110,    15,    14,   108,    48,     0,    49,     0,
       0,     0,   124,     0,     0,    12,    51,     0,     0,     0,
       0,     0,     0,     0,   131,     0,     0,     0,     9,    50,
     132,   133,   125,     0,     0,     0,   130,   126,     0,    29,
     127,   128,   129,    13,     0,    11
  };

  const short int
  Parser::yypgoto_[] =
  {
    -142,  -142,   173,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,   103,  -142,   -76,  -142,  -142,    29,    83,  -142,  -141,
    -142,   166,  -105,  -142,  -142,  -142,  -142,  -142,  -142,  -142,
    -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,  -142,   -25,
      52,  -142,   160,   -32,  -142,    -3,    70,  -142,  -142,    38,
    -117,  -142,  -142,  -142,  -142,   -50,  -142,  -142,  -142,  -142,
    -142,  -142,  -142
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     8,     9,    10,   248,   235,   178,   179,    23,
      11,    42,    43,    44,    12,    13,    45,    68,    69,   106,
     107,    64,   146,   147,   148,   149,   150,   209,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,    57,
      58,    77,    78,    59,    87,    60,    61,    62,    14,   190,
     191,   166,   167,   168,   244,   245,   169,   170,   171,   172,
     173,   174,   175
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      72,   110,    16,   185,    73,     1,   176,    76,    79,   180,
     239,    35,   189,    86,   193,   194,   112,    15,    17,   111,
     186,    88,    89,    90,    22,    91,    92,    93,    17,    17,
     187,    63,    18,    19,    20,    21,   192,   184,    94,    95,
      96,    97,    98,    99,   200,   201,   115,   101,   102,   103,
     122,    67,    70,   143,   226,    96,    97,    98,    99,    65,
     124,   144,   227,   125,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,   140,   141,
      81,   208,    74,    75,    88,    89,    90,    82,    91,    92,
      93,   181,   105,   182,    83,   183,    85,   104,    84,   223,
     224,    94,    95,    96,    97,    98,    99,   163,   100,   109,
     101,   102,   103,    91,    92,     3,   108,     4,     5,     6,
     112,     7,   236,   113,   114,   119,   118,   142,    96,    97,
      98,    99,   121,   188,   198,   199,   203,   145,    67,   215,
     145,   177,    99,   145,   202,   204,   216,   205,   165,   163,
     163,    91,    92,   233,   163,   196,   234,   240,   163,   163,
     246,   247,   210,   211,    94,    95,    96,    97,    98,    99,
     253,   145,   254,   105,   102,   103,   259,   221,   257,   265,
     164,   225,    24,   264,   105,   105,   123,    66,   163,   163,
     230,   231,   151,    80,   256,   195,     0,   163,   163,     0,
     163,     0,     0,   132,   237,     0,     0,     0,   243,     0,
       0,     0,     0,     0,   163,   145,     0,     0,     0,   243,
       0,   258,   164,   164,   132,     0,     0,   164,   197,   213,
     213,   164,   164,   145,   145,   163,   163,   163,   213,   213,
       0,   222,     0,     0,     0,     0,     0,     0,     0,     0,
     163,   163,   163,     0,     0,   232,   145,     0,     0,     0,
       0,   164,   164,     0,     0,   238,     0,     0,     0,     0,
     164,   164,     0,   164,     0,     0,   250,   251,   252,    88,
      89,    90,     0,    91,    92,    93,     0,   164,     0,     0,
       0,   260,   261,   262,     0,     0,    94,    95,    96,    97,
      98,    99,     0,     0,     0,   101,   102,   103,   164,   164,
     164,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   164,   164,   164,   152,   212,   153,     0,
     154,   155,     0,   156,   157,     0,   158,   159,     0,   152,
     160,   153,   214,   154,   155,     0,   156,   157,     0,   158,
     159,     0,     0,   160,     0,     0,     0,   161,     0,     0,
       0,     0,     0,     0,     0,    35,     0,     0,     0,     0,
     161,     0,     0,     0,     0,   162,     0,     0,    35,     0,
       0,     0,     0,    17,     0,     0,     0,   152,   162,   153,
       0,   154,   155,     0,   156,   157,    17,   158,   159,     0,
     152,   160,   153,     0,   154,   155,     0,   156,   157,     0,
     158,   159,     0,     0,   160,     0,     0,     0,   161,   219,
       0,     0,     0,     0,     0,     0,    35,     0,     0,     0,
       0,   161,     0,     0,     0,     0,   162,     0,     0,    35,
       0,     0,     0,     0,    17,     0,     0,     0,     0,   162,
     220,   152,     0,   153,     0,   154,   155,    17,   156,   157,
       0,   158,   159,     0,     0,   160,     0,     0,     0,     0,
       0,    25,     0,     0,     0,     0,   241,    26,    27,    28,
       0,     0,   161,    29,    30,    31,     0,    71,     0,    33,
      35,     0,     0,     0,   242,    34,     0,     0,     0,    35,
     162,     0,     0,     0,     0,     0,     0,     0,    17,     0,
       0,    36,    37,    38,    39,    40,    41,    17,    25,     0,
       0,     0,     0,     0,    26,    27,    28,     0,     0,     0,
      29,    30,    31,     0,    32,     0,    33,     0,     0,     0,
       0,     0,    34,     0,     0,     0,    35,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    36,    37,
      38,    39,    40,    41,    17,    25,     0,     0,     0,     0,
       0,    26,    27,    28,     0,     0,     0,    29,    30,    31,
       0,    71,     0,    33,     0,     0,     0,     0,     0,    34,
       0,     0,     0,    35,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    36,    37,    38,    39,    40,
      41,    17,    25,     0,     0,     0,     0,     0,    26,    27,
      28,     0,     0,     0,     0,    30,    31,     0,    71,     0,
      33,     0,     0,     0,   116,     0,    34,     0,     0,     0,
      35,     0,    88,    89,    90,     0,    91,    92,    93,     0,
       0,     0,    36,    37,    38,    39,    40,    41,    17,    94,
      95,    96,    97,    98,    99,   217,     0,     0,   101,   102,
     103,     0,     0,    88,    89,    90,     0,    91,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,    95,    96,    97,    98,    99,   206,     0,     0,   101,
     102,   103,     0,    88,    89,    90,     0,    91,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,    95,    96,    97,    98,    99,     0,   218,     0,   101,
     102,   103,    88,    89,    90,     0,    91,    92,    93,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    94,
      95,    96,    97,    98,    99,     0,     0,     0,   101,   102,
     103,    88,    89,    90,     0,    91,    92,    93,     0,   117,
       0,     0,     0,     0,     0,     0,     0,     0,    94,    95,
      96,    97,    98,    99,     0,     0,     0,   101,   102,   103,
      88,    89,    90,     0,    91,    92,    93,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94,    95,    96,
      97,    98,    99,   120,     0,     0,   101,   102,   103,    88,
      89,    90,     0,    91,    92,    93,     0,     0,     0,   207,
       0,     0,     0,     0,     0,     0,    94,    95,    96,    97,
      98,    99,     0,     0,     0,   101,   102,   103,    88,    89,
      90,     0,    91,    92,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,   228,    96,    97,    98,
      99,   229,     0,     0,   101,   102,   103,    88,    89,    90,
       0,    91,    92,    93,     0,     0,     0,     0,     0,     0,
     255,     0,     0,     0,    94,    95,    96,    97,    98,    99,
       0,     0,     0,   101,   102,   103,    88,    89,    90,     0,
      91,    92,    93,     0,     0,     0,     0,     0,   263,     0,
       0,     0,     0,    94,    95,    96,    97,    98,    99,     0,
       0,     0,   101,   102,   103,    88,    89,    90,     0,    91,
      92,    93,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    94,    95,    96,    97,    98,    99,     0,     0,
       0,   101,   102,   103,    88,    89,    90,     0,    91,    92,
      93,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    94,   249,    96,    97,    98,    99,     0,     0,     0,
     101,   102,   103,    88,     0,    90,     0,    91,    92,    93,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      94,    95,    96,    97,    98,    99,     0,     0,    88,   101,
     102,   103,    91,    92,    93,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    94,    95,    96,    97,    98,
      99,    91,    92,    93,   101,   102,   103,     0,     0,     0,
       0,     0,     0,     0,    94,    95,    96,    97,    98,    99,
       0,     0,     0,   101,   102,   103
  };

  const short int
  Parser::yycheck_[] =
  {
      25,    39,    44,   144,    29,     3,   111,    32,    33,   114,
      22,    52,    45,    45,   155,   156,    49,     0,    70,    57,
      40,    33,    34,    35,    40,    37,    38,    39,    70,    70,
      50,    40,     3,     4,     5,     6,   153,   142,    50,    51,
      52,    53,    54,    55,   161,   162,    71,    59,    60,    61,
      82,    22,    23,    41,    41,    52,    53,    54,    55,    39,
      85,    49,    49,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
      70,   186,    30,    31,    33,    34,    35,    35,    37,    38,
      39,   116,    63,   118,    49,   120,    40,    57,    45,   204,
     205,    50,    51,    52,    53,    54,    55,   110,    57,    44,
      59,    60,    61,    37,    38,     4,    57,     6,     7,     8,
      49,    10,   227,    41,    46,    41,    49,    46,    52,    53,
      54,    55,    43,    39,   159,   160,    39,   108,   109,    39,
     111,   112,    55,   114,    58,    52,    19,    57,   110,   152,
     153,    37,    38,    44,   157,   158,    12,    26,   161,   162,
      44,    11,   187,   188,    50,    51,    52,    53,    54,    55,
      46,   142,    46,   144,    60,    61,    44,   202,    45,    45,
     110,   206,     9,   259,   155,   156,    83,    21,   191,   192,
     215,   216,   109,    33,   244,   157,    -1,   200,   201,    -1,
     203,    -1,    -1,   228,   229,    -1,    -1,    -1,   233,    -1,
      -1,    -1,    -1,    -1,   217,   186,    -1,    -1,    -1,   244,
      -1,   246,   152,   153,   249,    -1,    -1,   157,   158,   191,
     192,   161,   162,   204,   205,   238,   239,   240,   200,   201,
      -1,   203,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     253,   254,   255,    -1,    -1,   217,   227,    -1,    -1,    -1,
      -1,   191,   192,    -1,    -1,    19,    -1,    -1,    -1,    -1,
     200,   201,    -1,   203,    -1,    -1,   238,   239,   240,    33,
      34,    35,    -1,    37,    38,    39,    -1,   217,    -1,    -1,
      -1,   253,   254,   255,    -1,    -1,    50,    51,    52,    53,
      54,    55,    -1,    -1,    -1,    59,    60,    61,   238,   239,
     240,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   253,   254,   255,    13,    14,    15,    -1,
      17,    18,    -1,    20,    21,    -1,    23,    24,    -1,    13,
      27,    15,    16,    17,    18,    -1,    20,    21,    -1,    23,
      24,    -1,    -1,    27,    -1,    -1,    -1,    44,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,
      44,    -1,    -1,    -1,    -1,    62,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    70,    -1,    -1,    -1,    13,    62,    15,
      -1,    17,    18,    -1,    20,    21,    70,    23,    24,    -1,
      13,    27,    15,    -1,    17,    18,    -1,    20,    21,    -1,
      23,    24,    -1,    -1,    27,    -1,    -1,    -1,    44,    45,
      -1,    -1,    -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    44,    -1,    -1,    -1,    -1,    62,    -1,    -1,    52,
      -1,    -1,    -1,    -1,    70,    -1,    -1,    -1,    -1,    62,
      63,    13,    -1,    15,    -1,    17,    18,    70,    20,    21,
      -1,    23,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
      -1,    -1,    44,    36,    37,    38,    -1,    40,    -1,    42,
      52,    -1,    -1,    -1,    47,    48,    -1,    -1,    -1,    52,
      62,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      -1,    64,    65,    66,    67,    68,    69,    70,    24,    -1,
      -1,    -1,    -1,    -1,    30,    31,    32,    -1,    -1,    -1,
      36,    37,    38,    -1,    40,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    48,    -1,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    70,    24,    -1,    -1,    -1,    -1,
      -1,    30,    31,    32,    -1,    -1,    -1,    36,    37,    38,
      -1,    40,    -1,    42,    -1,    -1,    -1,    -1,    -1,    48,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
      69,    70,    24,    -1,    -1,    -1,    -1,    -1,    30,    31,
      32,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,    -1,
      42,    -1,    -1,    -1,    25,    -1,    48,    -1,    -1,    -1,
      52,    -1,    33,    34,    35,    -1,    37,    38,    39,    -1,
      -1,    -1,    64,    65,    66,    67,    68,    69,    70,    50,
      51,    52,    53,    54,    55,    25,    -1,    -1,    59,    60,
      61,    -1,    -1,    33,    34,    35,    -1,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    26,    -1,    -1,    59,
      60,    61,    -1,    33,    34,    35,    -1,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    -1,    28,    -1,    59,
      60,    61,    33,    34,    35,    -1,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    59,    60,
      61,    33,    34,    35,    -1,    37,    38,    39,    -1,    41,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    -1,    -1,    -1,    59,    60,    61,
      33,    34,    35,    -1,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    56,    -1,    -1,    59,    60,    61,    33,
      34,    35,    -1,    37,    38,    39,    -1,    -1,    -1,    43,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    -1,    -1,    -1,    59,    60,    61,    33,    34,
      35,    -1,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      55,    56,    -1,    -1,    59,    60,    61,    33,    34,    35,
      -1,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    -1,    -1,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    59,    60,    61,    33,    34,    35,    -1,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    59,    60,    61,    33,    34,    35,    -1,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    59,    60,    61,    33,    34,    35,    -1,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      59,    60,    61,    33,    -1,    35,    -1,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    -1,    -1,    33,    59,
      60,    61,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      55,    37,    38,    39,    59,    60,    61,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    59,    60,    61
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    75,     4,     6,     7,     8,    10,    76,    77,
      78,    84,    88,    89,   122,     0,    44,    70,    90,    90,
      90,    90,    40,    83,    76,    24,    30,    31,    32,    36,
      37,    38,    40,    42,    48,    52,    64,    65,    66,    67,
      68,    69,    85,    86,    87,    90,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   117,
     119,   120,   121,    40,    95,    39,    95,    90,    91,    92,
      90,    40,   113,   113,   114,   114,   113,   115,   116,   113,
     116,    70,   114,    49,    45,    40,   117,   118,    33,    34,
      35,    37,    38,    39,    50,    51,    52,    53,    54,    55,
      57,    59,    60,    61,    57,    90,    93,    94,    57,    44,
      39,    57,    49,    41,    46,   113,    25,    41,    49,    41,
      56,    43,   117,    85,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,    46,    41,    49,    90,    96,    97,    98,    99,
     100,    91,    13,    15,    17,    18,    20,    21,    23,    24,
      27,    44,    62,   119,   120,   123,   125,   126,   127,   130,
     131,   132,   133,   134,   135,   136,    96,    90,    81,    82,
      96,   113,   113,   113,    96,    93,    40,    50,    39,    45,
     123,   124,   124,    93,    93,   123,   119,   120,   113,   113,
     124,   124,    58,    39,    52,    57,    26,    43,    96,   101,
     113,   113,    14,   123,    16,    39,    19,    25,    28,    45,
      63,   113,   123,    96,    96,   113,    41,    49,    51,    56,
     113,   113,   123,    44,    12,    80,    96,   113,    19,    22,
      26,    29,    47,   113,   128,   129,    44,    11,    79,    51,
     123,   123,   123,    46,    46,    46,   129,    45,   113,    44,
     123,   123,   123,    45,    87,    45
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    74,    75,    76,    76,    76,    76,    77,    77,    78,
      78,    79,    79,    80,    80,    81,    81,    82,    82,    83,
      83,    84,    84,    85,    85,    85,    86,    86,    87,    87,
      88,    89,    90,    91,    91,    92,    92,    93,    93,    94,
      94,    95,    95,    96,    96,    96,    96,    97,    98,    99,
     100,   101,   101,   102,   102,   102,   102,   102,   102,   102,
     102,   103,   104,   104,   105,   106,   106,   107,   108,   109,
     110,   111,   112,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   115,
     115,   116,   116,   117,   118,   118,   119,   120,   121,   122,
     122,   123,   123,   123,   123,   123,   123,   123,   123,   123,
     123,   124,   124,   125,   126,   126,   127,   128,   128,   128,
     129,   129,   130,   131,   132,   133,   133,   134,   134,   135,
     136,   136,   136,   136
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
       3,     3,     3,     3,     3,     3,     3,     3,     2,     1,
       3,     2,     2,     1,     1,     1,     1,     1,     1,     3,
       1,     1,     0,     3,     1,     0,     2,     3,     6,     5,
       7,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     1,     1,     4,     6,     6,     3,     3,     3,
       2,     1,     6,     6,     2,     3,     3,     3,     3,     3,
       2,     1,     2,     1
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
  "\"case\"", "\"of\"", "\"default\"", "\"undef\"", "\"false\"",
  "\"true\"", "\"and\"", "\"or\"", "\"xor\"", "\"not\"", "\"+\"", "\"-\"",
  "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\":\"",
  "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"",
  "\"^\"", "\"..\"", "\"->\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"",
  "\"{|\"", "\"|}\"", "\"binary\"", "\"hexadecimal\"", "\"integer\"",
  "\"rational\"", "\"floating\"", "\"string\"", "\"identifier\"", "UPLUS",
  "UMINUS", "UASTERIX", "$accept", "Specification", "Definition",
  "Definitions", "FunctionDefinition", "MaybeInitially", "MaybeDefined",
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
  "ConditionalExpression", "RuleDefinition", "Rule", "Rules", "SkipRule",
  "ConditionalRule", "CaseRule", "CaseLabel", "CaseLabels", "LetRule",
  "ForallRule", "IterateRule", "BlockRule", "SequenceRule", "UpdateRule",
  "CallRule", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   352,   352,   369,   373,   377,   381,   389,   395,   405,
     424,   432,   436,   444,   448,   456,   462,   472,   476,   484,
     488,   496,   513,   530,   539,   550,   562,   568,   578,   582,
     590,   598,   606,   614,   620,   630,   634,   642,   646,   654,
     660,   670,   674,   682,   686,   690,   694,   702,   710,   718,
     726,   734,   740,   750,   754,   758,   762,   766,   770,   774,
     778,   786,   794,   799,   808,   817,   822,   831,   840,   849,
     858,   866,   874,   882,   886,   890,   894,   898,   902,   906,
     910,   914,   918,   922,   926,   930,   934,   938,   942,   946,
     954,   958,   962,   968,   972,   976,   980,   984,   988,   996,
    1002,  1012,  1016,  1024,  1032,  1036,  1044,  1052,  1060,  1068,
    1073,  1082,  1086,  1090,  1094,  1098,  1102,  1106,  1110,  1114,
    1118,  1126,  1132,  1142,  1150,  1154,  1162,  1170,  1175,  1180,
    1188,  1193,  1201,  1209,  1217,  1225,  1229,  1237,  1241,  1249,
    1257,  1261,  1265,  1269
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
#line 3204 "GrammarParser.cpp" // lalr1.cc:1167
#line 1275 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
