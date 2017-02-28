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
      case 96: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 130: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 133: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 125: // CaseLabel
        value.move< CaseRule::Case > (that.value);
        break;

      case 124: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 97: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 123: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 75: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 76: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 87: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 117: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 88: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 79: // MaybeDefined
      case 101: // Atom
      case 112: // Expression
        value.move< Expression::Ptr > (that.value);
        break;

      case 113: // Expressions
      case 114: // MaybeExpressions
      case 115: // Arguments
      case 116: // MaybeArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 98: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 128: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 77: // FunctionDefinition
      case 83: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 89: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
        break;

      case 118: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 129: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 127: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 111: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 82: // MaybeFunctionAttributes
      case 90: // Identifiers
      case 91: // MaybeIdentifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 78: // MaybeInitially
      case 85: // Initializers
      case 86: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 93: // Parameters
      case 94: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 110: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 99: // RangedType
        value.move< RangedType::Ptr > (that.value);
        break;

      case 120: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 119: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 109: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 121: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 131: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 122: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 74: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 95: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 80: // FunctionParameters
      case 81: // MaybeFunctionParameters
      case 100: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 102: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 84: // Initializer
      case 132: // UpdateRule
        value.move< UpdateRule::Ptr > (that.value);
        break;

      case 103: // Boolean
      case 104: // String
      case 105: // BitNumber
      case 106: // IntegerNumber
      case 107: // FloatingNumber
      case 108: // RationalNumber
        value.move< ValueAtom::Ptr > (that.value);
        break;

      case 92: // Variable
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

      case 126: // CaseLabels
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
      case 96: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 130: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 133: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 125: // CaseLabel
        value.copy< CaseRule::Case > (that.value);
        break;

      case 124: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 97: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 123: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 75: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 76: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 87: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 117: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 88: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 79: // MaybeDefined
      case 101: // Atom
      case 112: // Expression
        value.copy< Expression::Ptr > (that.value);
        break;

      case 113: // Expressions
      case 114: // MaybeExpressions
      case 115: // Arguments
      case 116: // MaybeArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 98: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 128: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 77: // FunctionDefinition
      case 83: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 89: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
        break;

      case 118: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 129: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 127: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 111: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 82: // MaybeFunctionAttributes
      case 90: // Identifiers
      case 91: // MaybeIdentifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 78: // MaybeInitially
      case 85: // Initializers
      case 86: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 93: // Parameters
      case 94: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 110: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 99: // RangedType
        value.copy< RangedType::Ptr > (that.value);
        break;

      case 120: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 119: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 109: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 121: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 131: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 122: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 74: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 95: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 80: // FunctionParameters
      case 81: // MaybeFunctionParameters
      case 100: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 102: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 84: // Initializer
      case 132: // UpdateRule
        value.copy< UpdateRule::Ptr > (that.value);
        break;

      case 103: // Boolean
      case 104: // String
      case 105: // BitNumber
      case 106: // IntegerNumber
      case 107: // FloatingNumber
      case 108: // RationalNumber
        value.copy< ValueAtom::Ptr > (that.value);
        break;

      case 92: // Variable
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

      case 126: // CaseLabels
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

#line 910 "GrammarParser.cpp" // lalr1.cc:741

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
      case 96: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 130: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 133: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 125: // CaseLabel
        yylhs.value.build< CaseRule::Case > ();
        break;

      case 124: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 97: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 123: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 75: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 76: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 87: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 117: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 88: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 79: // MaybeDefined
      case 101: // Atom
      case 112: // Expression
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 113: // Expressions
      case 114: // MaybeExpressions
      case 115: // Arguments
      case 116: // MaybeArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 98: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 128: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 77: // FunctionDefinition
      case 83: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 89: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
        break;

      case 118: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 129: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 127: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 111: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 82: // MaybeFunctionAttributes
      case 90: // Identifiers
      case 91: // MaybeIdentifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 78: // MaybeInitially
      case 85: // Initializers
      case 86: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 93: // Parameters
      case 94: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 110: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 99: // RangedType
        yylhs.value.build< RangedType::Ptr > ();
        break;

      case 120: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 119: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 109: // RuleReference
        yylhs.value.build< RuleReferenceAtom::Ptr > ();
        break;

      case 121: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 131: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 122: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 74: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 95: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 80: // FunctionParameters
      case 81: // MaybeFunctionParameters
      case 100: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 102: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 84: // Initializer
      case 132: // UpdateRule
        yylhs.value.build< UpdateRule::Ptr > ();
        break;

      case 103: // Boolean
      case 104: // String
      case 105: // BitNumber
      case 106: // IntegerNumber
      case 107: // FloatingNumber
      case 108: // RationalNumber
        yylhs.value.build< ValueAtom::Ptr > ();
        break;

      case 92: // Variable
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

      case 126: // CaseLabels
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
#line 364 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1224 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 381 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1232 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 385 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1240 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 389 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1248 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1256 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 401 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1299 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 436 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1307 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1323 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 456 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1331 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1339 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 468 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 474 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 488 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = make< Types >( yylhs.location );
  }
#line 1375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 496 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 500 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 508 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto programDefinition = createProgramFunction();

      auto arguments = make< Expressions >( yylhs.location );
      // TODO add `default` agent to arguments
      const auto program = make< DirectCallExpression >(
          yylhs.location, programDefinition->identifier(), arguments );

      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( make< UpdateRule >( yylhs.location, program, yystack_[0].value.as< RuleReferenceAtom::Ptr > () ) );
      programDefinition->setInitializers( initializers );

      yylhs.value.as< FunctionDefinition::Ptr > () = programDefinition;
  }
#line 1410 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1427 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1440 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 549 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1452 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1462 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 567 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1472 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1480 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1488 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 585 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1496 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 593 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 601 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1512 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1520 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1530 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 623 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = make< NodeList< Identifier > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1540 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 633 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[0].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1548 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 637 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1556 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 641 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< Identifier > >( yylhs.location );
  }
#line 1564 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 649 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1572 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 657 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1582 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 663 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1592 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 673 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1600 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1608 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 681 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1616 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 689 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1624 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 693 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1632 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 697 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1640 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 701 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1648 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 709 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1656 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 717 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1664 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 725 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1672 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 733 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1680 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 741 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1690 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 747 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1700 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 757 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 1708 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 761 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 1716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 765 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1724 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 769 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1732 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 773 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto zero = make< ZeroAtom >( yylhs.location );
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, zero, yystack_[1].value.as< Expression::Ptr > (),
                                               libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1742 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 779 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1750 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 783 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1758 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 787 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1766 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 791 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 795 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1782 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 799 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1790 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 803 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 1798 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 807 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 1806 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 811 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1814 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 815 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1822 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 823 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 831 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 836 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 845 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 854 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), 2 );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 859 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), 16 );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1875 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 868 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1884 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 877 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 886 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1902 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 895 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleReferenceAtom::Ptr > () = make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1910 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 903 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1918 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 911 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 1926 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 1934 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 923 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1942 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 927 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 1950 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 931 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 1958 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 935 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 1966 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 939 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 1974 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 943 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 1982 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 947 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 1990 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 951 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 1998 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 955 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2006 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 959 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2014 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 963 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2022 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 967 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2030 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 971 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2038 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 975 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2046 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 979 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2054 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 987 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2064 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 993 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2074 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1003 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[0].value.as< Expressions::Ptr > ();
  }
#line 2082 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1007 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2090 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1011 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = make< Expressions >( yylhs.location );
  }
#line 2098 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1019 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2106 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1023 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = make< Expressions >( yylhs.location );
  }
#line 2114 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1031 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[0].value.as< Expressions::Ptr > ();
  }
#line 2122 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1035 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2132 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1041 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = make< Expressions >( yylhs.location );
  }
#line 2140 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1049 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2148 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1057 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = make< IndirectCallExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2156 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1065 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), nullptr,
                                             wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) ); // TODO nullptr -> void
  }
#line 2165 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2173 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1078 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2181 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2189 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2197 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2205 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1094 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2213 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2221 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1102 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2229 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2237 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1110 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2245 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1118 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1124 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2265 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = make< SkipRule >( yylhs.location );
  }
#line 2273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1142 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2281 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1146 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2289 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< std::vector< CaseRule::Case > > () );
  }
#line 2297 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1162 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1167 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1172 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2323 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1180 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = std::move( yystack_[0].value.as< std::vector< CaseRule::Case > > () );
      yylhs.value.as< std::vector< CaseRule::Case > > ().push_back( yystack_[1].value.as< CaseRule::Case > () );
  }
#line 2332 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1185 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = { yystack_[0].value.as< CaseRule::Case > () };
  }
#line 2340 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1193 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2348 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1201 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2356 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1209 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1217 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2372 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1221 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2380 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1229 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1233 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2396 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1241 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2404 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1249 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), { CallExpression::TargetType::RULE } );
  }
#line 2412 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1253 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
#line 2420 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1257 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), { CallExpression::TargetType::RULE } );
  }
#line 2428 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1261 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
#line 2436 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2440 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -141;

  const signed char Parser::yytable_ninf_ = -107;

  const short int
  Parser::yypact_[] =
  {
       3,   364,    12,    68,   -52,   -52,   -52,   -18,  -141,   364,
    -141,  -141,  -141,  -141,  -141,  -141,   465,   -46,  -141,  -141,
       9,     2,     9,   -52,   -52,  -141,  -141,  -141,  -141,   520,
      17,    37,   479,   520,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,    31,    38,   534,    73,  -141,  -141,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,   751,  -141,    45,  -141,  -141,
    -141,   -33,    57,    67,    74,  -141,    65,    96,    93,   520,
    -141,  -141,   520,   520,  -141,   653,   -22,    85,   751,    92,
     100,   465,  -141,  -141,   520,   520,   520,   520,   520,   520,
     520,   520,   520,   520,   520,   520,   520,   520,   575,  -141,
      99,  -141,    29,   -52,   -52,   421,   -52,  -141,   -52,   653,
     682,   711,   107,  -141,   520,   575,   520,  -141,  -141,   779,
     196,   790,    21,    81,   809,   -28,    13,  -141,    95,    72,
     133,    -7,   225,  -141,   -52,  -141,   -52,   109,   111,  -141,
    -141,  -141,  -141,   116,   421,   421,  -141,   -52,   -52,   421,
     -27,   520,   520,   520,   421,   421,   108,  -141,  -141,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
     114,   115,  -141,  -141,  -141,   479,  -141,   751,   134,  -141,
    -141,   575,   520,  -141,  -141,   325,   340,   137,   160,  -141,
    -141,  -141,   595,   624,   740,   373,   388,   520,   -52,   -52,
    -141,   263,  -141,    30,    22,   751,  -141,  -141,  -141,   520,
     520,   421,   139,   107,  -141,  -141,   751,  -141,   169,   479,
    -141,   -52,  -141,   575,   433,     1,   163,    90,   146,   180,
      22,  -141,   157,   421,   421,   421,   152,   153,   154,    90,
     161,   575,   158,  -141,  -141,  -141,  -141,  -141,   421,   421,
     421,  -141,  -141,   167,   465,  -141,  -141,  -141,  -141,   168,
    -141
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,    20,     8,     2,
       3,    10,     4,     6,     5,     1,    29,     0,    21,    32,
      43,     0,    43,    37,     0,     7,    69,    71,    70,     0,
       0,     0,     0,   101,    73,    74,    75,    77,    76,    72,
      26,    27,     0,   106,    96,    67,    68,    64,    60,    61,
      62,    63,    59,    66,    65,   105,   104,     0,    54,    55,
      78,     0,     0,     0,     0,    34,    35,     0,     0,     0,
      96,    95,     0,     0,   103,    98,     0,    96,    98,    99,
       0,    28,    22,   107,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
       0,    40,     0,     0,    37,     0,    36,    19,    18,     0,
       0,     0,    56,   102,     0,     0,   100,    80,    25,    94,
      92,    93,    81,    82,    87,    88,    89,    83,    84,    85,
      86,    90,    91,    24,     0,    41,     0,    48,     0,    44,
      45,    46,    47,     0,     0,     0,   122,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   140,   142,   109,   110,
     111,   112,   113,   114,   115,   116,   117,   118,   119,    33,
      17,     0,    16,    57,    58,     0,   108,    97,     0,    38,
      39,     0,     0,    31,   121,     0,     0,     0,     0,   133,
     139,   141,     0,     0,     0,     0,     0,     0,     0,     0,
      79,   106,    53,     0,     0,    30,   137,   120,   135,     0,
       0,     0,     0,     0,   134,   136,   138,    15,    14,     0,
      49,     0,    50,     0,     0,     0,   123,     0,     0,    12,
      96,    52,     0,     0,     0,     0,     0,     0,     0,   130,
       0,     0,     0,     9,    51,   131,   132,   124,     0,     0,
       0,   129,   125,     0,    29,   126,   127,   128,    13,     0,
      11
  };

  const short int
  Parser::yypgoto_[] =
  {
    -141,  -141,   199,  -141,  -141,  -141,  -141,  -141,  -141,  -141,
    -141,   136,  -141,   -34,  -141,  -141,    -3,  -141,   117,   -38,
    -141,   200,   -92,  -141,  -141,  -141,  -141,  -141,   -16,  -141,
    -141,  -141,  -141,  -141,  -141,  -141,   223,  -141,  -141,     0,
     194,  -141,  -105,   -39,    19,    87,  -141,    75,  -140,  -141,
    -141,  -141,  -141,   -11,  -141,  -141,  -141,  -141,  -141,  -141,
    -141
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     8,     9,    10,   243,   229,   170,   171,    24,
      11,    40,    41,    42,    12,    13,    43,    66,    67,   101,
     102,    62,   202,   139,   140,   141,   142,   203,    70,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      76,    80,    56,    57,    58,    59,    14,   184,   185,   159,
     160,   161,   239,   240,   162,   163,   164,   165,   166,   167,
     168
  };

  const short int
  Parser::yytable_[] =
  {
      44,    20,    21,    22,    83,   186,     1,   176,    99,    87,
      88,   138,    15,   153,   195,   196,   172,    77,    19,   113,
      65,    68,    23,   234,    60,    92,    93,    94,   114,    71,
      87,    88,    75,    78,    84,    85,    86,    19,    87,    88,
      89,    63,   179,    19,    90,    91,    92,    93,    94,    61,
      87,    88,    90,    91,    92,    93,    94,    72,   100,    88,
      95,    96,    97,   222,    90,    44,    92,    93,    94,   109,
     135,   220,   110,   111,    92,    93,    94,    73,   223,   136,
     221,    81,   133,    82,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   180,   178,
     137,    65,    98,   169,   103,   137,   217,   218,   176,   187,
     188,   104,    16,   105,   177,   106,   177,    17,   -23,   236,
      26,    27,    28,   -23,   156,    92,    93,    30,    31,   231,
      69,   137,    33,   100,    92,    93,    94,   107,   237,    17,
     108,   115,   116,   117,   100,   100,   134,   175,    92,   181,
     182,   192,   193,   194,    34,    35,    36,    37,    38,    39,
      19,   183,    83,   156,   156,   204,   197,   198,   156,   190,
      87,    88,   199,   156,   156,    78,   209,   200,   201,   210,
     158,   228,   205,   227,    90,    91,    92,    93,    94,   235,
     241,   242,   157,    96,    97,   137,   137,   216,   244,   248,
     249,   250,   254,   230,   156,   156,   252,   232,    25,   224,
     225,   238,   258,   260,   156,   156,   201,   118,   137,    75,
     259,   143,    64,   238,   189,   253,    18,    79,   251,     0,
     156,   157,   157,    87,    88,    89,   157,   191,    44,     0,
       0,   157,   157,     0,     0,     0,     0,    90,    91,    92,
      93,    94,   156,   156,   156,    95,    96,    97,     0,     0,
     207,   207,    87,    88,     0,     0,     0,   156,   156,   156,
     207,   207,   157,   157,     0,     0,    90,    91,    92,    93,
      94,     0,   157,   157,     0,    96,   226,     0,     0,     0,
       0,     0,     0,    26,    27,    28,     0,     0,   157,    29,
      30,    31,     0,   219,   -48,    33,     0,     0,   245,   246,
     247,     0,    17,   -48,     0,     0,     0,     0,     0,     0,
     157,   157,   157,   255,   256,   257,     0,    34,    35,    36,
      37,    38,    39,    19,     0,   157,   157,   157,   144,   206,
     145,     0,   146,   147,     0,   148,   149,     0,   150,   151,
       0,     0,   152,   144,     0,   145,   208,   146,   147,     0,
     148,   149,     0,   150,   151,   153,     0,   152,     3,   154,
       4,     5,     6,     0,     7,     0,     0,     0,     0,     0,
     153,     0,     0,     0,   154,     0,   144,   155,   145,     0,
     146,   147,     0,   148,   149,    19,   150,   151,     0,     0,
     152,   144,   155,   145,     0,   146,   147,     0,   148,   149,
      19,   150,   151,   153,     0,   152,     0,   154,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   153,     0,
       0,     0,   154,     0,   144,   155,   145,     0,   146,   147,
       0,   148,   149,    19,   150,   151,     0,     0,   152,     0,
     155,   215,   233,     0,     0,     0,     0,     0,    19,     0,
       0,   153,     0,     0,     0,   154,    84,    85,    86,     0,
      87,    88,    89,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   155,    90,    91,    92,    93,    94,     0,
       0,    19,    95,    96,    97,    26,    27,    28,     0,     0,
       0,    29,    30,    31,     0,    32,     0,    33,     0,    26,
      27,    28,     0,     0,    17,    29,    30,    31,     0,    69,
      74,    33,  -106,     0,     0,     0,     0,     0,    17,    34,
      35,    36,    37,    38,    39,    19,     0,     0,     0,     0,
       0,     0,     0,    34,    35,    36,    37,    38,    39,    19,
      26,    27,    28,     0,     0,     0,    29,    30,    31,     0,
      69,     0,    33,     0,    26,    27,    28,     0,     0,    17,
      29,    30,    31,     0,    32,     0,    33,     0,     0,     0,
       0,     0,     0,    17,    34,    35,    36,    37,    38,    39,
      19,     0,     0,     0,     0,     0,     0,     0,    34,    35,
      36,    37,    38,    39,    19,    26,    27,    28,     0,     0,
       0,     0,    30,    31,     0,    69,     0,    33,     0,     0,
     211,     0,     0,     0,    17,     0,     0,     0,    84,    85,
      86,     0,    87,    88,    89,     0,     0,     0,     0,    34,
      35,    36,    37,    38,    39,    19,    90,    91,    92,    93,
      94,     0,   212,     0,    95,    96,    97,    84,    85,    86,
       0,    87,    88,    89,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    90,    91,    92,    93,    94,
       0,     0,     0,    95,    96,    97,    84,    85,    86,     0,
      87,    88,    89,     0,   112,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    90,    91,    92,    93,    94,     0,
       0,     0,    95,    96,    97,    84,    85,    86,     0,    87,
      88,    89,     0,   173,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    90,    91,    92,    93,    94,     0,     0,
       0,    95,    96,    97,    84,    85,    86,     0,    87,    88,
      89,     0,   174,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    90,    91,    92,    93,    94,     0,     0,     0,
      95,    96,    97,    84,    85,    86,     0,    87,    88,    89,
       0,   213,     0,     0,    84,    85,    86,     0,    87,    88,
      89,    90,    91,    92,    93,    94,     0,     0,     0,    95,
      96,    97,    90,    91,    92,    93,    94,     0,     0,     0,
      95,    96,    97,    85,    86,     0,    87,    88,    89,     0,
       0,     0,     0,     0,    85,     0,     0,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,     0,    95,    96,
      97,    90,    91,    92,    93,    94,    87,    88,     0,    95,
      96,    97,     0,     0,     0,     0,     0,     0,     0,     0,
      90,    91,    92,    93,    94,     0,     0,     0,    95,    96,
      97
  };

  const short int
  Parser::yycheck_[] =
  {
      16,     4,     5,     6,    43,   145,     3,   112,    41,    37,
      38,   103,     0,    40,   154,   155,   108,    33,    70,    41,
      23,    24,    40,    22,    70,    53,    54,    55,    50,    29,
      37,    38,    32,    33,    33,    34,    35,    70,    37,    38,
      39,    39,   134,    70,    51,    52,    53,    54,    55,    40,
      37,    38,    51,    52,    53,    54,    55,    40,    61,    38,
      59,    60,    61,    41,    51,    81,    53,    54,    55,    69,
      41,    41,    72,    73,    53,    54,    55,    40,    56,    50,
      50,    50,    98,    45,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    93,    94,    95,    96,    97,   136,   115,
     103,   104,    57,   106,    47,   108,   198,   199,   213,   147,
     148,    44,    44,    39,   114,    50,   116,    49,    45,    29,
      30,    31,    32,    50,   105,    53,    54,    37,    38,   221,
      40,   134,    42,   136,    53,    54,    55,    41,    48,    49,
      47,    56,    50,    43,   147,   148,    47,    40,    53,    40,
      39,   151,   152,   153,    64,    65,    66,    67,    68,    69,
      70,    45,   201,   144,   145,   181,    58,    53,   149,   150,
      37,    38,    57,   154,   155,   175,    39,    43,   181,    19,
     105,    12,   182,    44,    51,    52,    53,    54,    55,    26,
      44,    11,   105,    60,    61,   198,   199,   197,    41,    47,
      47,    47,    44,   219,   185,   186,    45,   223,     9,   209,
     210,   227,    45,    45,   195,   196,   219,    81,   221,   219,
     254,   104,    22,   239,   149,   241,     3,    33,   239,    -1,
     211,   144,   145,    37,    38,    39,   149,   150,   254,    -1,
      -1,   154,   155,    -1,    -1,    -1,    -1,    51,    52,    53,
      54,    55,   233,   234,   235,    59,    60,    61,    -1,    -1,
     185,   186,    37,    38,    -1,    -1,    -1,   248,   249,   250,
     195,   196,   185,   186,    -1,    -1,    51,    52,    53,    54,
      55,    -1,   195,   196,    -1,    60,   211,    -1,    -1,    -1,
      -1,    -1,    -1,    30,    31,    32,    -1,    -1,   211,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,   233,   234,
     235,    -1,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,
     233,   234,   235,   248,   249,   250,    -1,    64,    65,    66,
      67,    68,    69,    70,    -1,   248,   249,   250,    13,    14,
      15,    -1,    17,    18,    -1,    20,    21,    -1,    23,    24,
      -1,    -1,    27,    13,    -1,    15,    16,    17,    18,    -1,
      20,    21,    -1,    23,    24,    40,    -1,    27,     4,    44,
       6,     7,     8,    -1,    10,    -1,    -1,    -1,    -1,    -1,
      40,    -1,    -1,    -1,    44,    -1,    13,    62,    15,    -1,
      17,    18,    -1,    20,    21,    70,    23,    24,    -1,    -1,
      27,    13,    62,    15,    -1,    17,    18,    -1,    20,    21,
      70,    23,    24,    40,    -1,    27,    -1,    44,    45,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,
      -1,    -1,    44,    -1,    13,    62,    15,    -1,    17,    18,
      -1,    20,    21,    70,    23,    24,    -1,    -1,    27,    -1,
      62,    63,    19,    -1,    -1,    -1,    -1,    -1,    70,    -1,
      -1,    40,    -1,    -1,    -1,    44,    33,    34,    35,    -1,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    51,    52,    53,    54,    55,    -1,
      -1,    70,    59,    60,    61,    30,    31,    32,    -1,    -1,
      -1,    36,    37,    38,    -1,    40,    -1,    42,    -1,    30,
      31,    32,    -1,    -1,    49,    36,    37,    38,    -1,    40,
      41,    42,    57,    -1,    -1,    -1,    -1,    -1,    49,    64,
      65,    66,    67,    68,    69,    70,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    70,
      30,    31,    32,    -1,    -1,    -1,    36,    37,    38,    -1,
      40,    -1,    42,    -1,    30,    31,    32,    -1,    -1,    49,
      36,    37,    38,    -1,    40,    -1,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    49,    64,    65,    66,    67,    68,    69,
      70,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
      66,    67,    68,    69,    70,    30,    31,    32,    -1,    -1,
      -1,    -1,    37,    38,    -1,    40,    -1,    42,    -1,    -1,
      25,    -1,    -1,    -1,    49,    -1,    -1,    -1,    33,    34,
      35,    -1,    37,    38,    39,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    69,    70,    51,    52,    53,    54,
      55,    -1,    28,    -1,    59,    60,    61,    33,    34,    35,
      -1,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    59,    60,    61,    33,    34,    35,    -1,
      37,    38,    39,    -1,    41,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    59,    60,    61,    33,    34,    35,    -1,    37,
      38,    39,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    51,    52,    53,    54,    55,    -1,    -1,
      -1,    59,    60,    61,    33,    34,    35,    -1,    37,    38,
      39,    -1,    41,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      59,    60,    61,    33,    34,    35,    -1,    37,    38,    39,
      -1,    41,    -1,    -1,    33,    34,    35,    -1,    37,    38,
      39,    51,    52,    53,    54,    55,    -1,    -1,    -1,    59,
      60,    61,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      59,    60,    61,    34,    35,    -1,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    34,    -1,    -1,    37,    38,    39,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    59,    60,
      61,    51,    52,    53,    54,    55,    37,    38,    -1,    59,
      60,    61,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      51,    52,    53,    54,    55,    -1,    -1,    -1,    59,    60,
      61
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    74,     4,     6,     7,     8,    10,    75,    76,
      77,    83,    87,    88,   119,     0,    44,    49,   109,    70,
      89,    89,    89,    40,    82,    75,    30,    31,    32,    36,
      37,    38,    40,    42,    64,    65,    66,    67,    68,    69,
      84,    85,    86,    89,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   115,   116,   117,   118,
      70,    40,    94,    39,    94,    89,    90,    91,    89,    40,
     101,   112,    40,    40,    41,   112,   113,   101,   112,   113,
     114,    50,    45,   116,    33,    34,    35,    37,    38,    39,
      51,    52,    53,    54,    55,    59,    60,    61,    57,    41,
      89,    92,    93,    47,    44,    39,    50,    41,    47,   112,
     112,   112,    41,    41,    50,    56,    50,    43,    84,   112,
     112,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   101,    47,    41,    50,    89,    95,    96,
      97,    98,    99,    91,    13,    15,    17,    18,    20,    21,
      23,    24,    27,    40,    44,    62,   117,   118,   120,   122,
     123,   124,   127,   128,   129,   130,   131,   132,   133,    89,
      80,    81,    95,    41,    41,    40,   115,   112,   101,    95,
      92,    40,    39,    45,   120,   121,   121,    92,    92,   120,
     117,   118,   112,   112,   112,   121,   121,    58,    53,    57,
      43,    89,    95,   100,   101,   112,    14,   120,    16,    39,
      19,    25,    28,    41,    45,    63,   112,    95,    95,    40,
      41,    50,    41,    56,   112,   112,   120,    44,    12,    79,
     101,    95,   101,    19,    22,    26,    29,    48,   101,   125,
     126,    44,    11,    78,    41,   120,   120,   120,    47,    47,
      47,   126,    45,   101,    44,   120,   120,   120,    45,    86,
      45
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    73,    74,    75,    75,    75,    75,    76,    76,    77,
      77,    78,    78,    79,    79,    80,    80,    81,    81,    82,
      82,    83,    83,    84,    84,    85,    85,    86,    86,    86,
      87,    88,    89,    90,    90,    91,    91,    91,    92,    93,
      93,    94,    94,    94,    95,    95,    95,    95,    96,    97,
      98,    99,   100,   100,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,   101,   102,
     103,   103,   104,   105,   105,   106,   107,   108,   109,   110,
     111,   112,   112,   112,   112,   112,   112,   112,   112,   112,
     112,   112,   112,   112,   112,   112,   112,   113,   113,   114,
     114,   114,   115,   115,   116,   116,   116,   117,   118,   119,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     121,   121,   122,   123,   123,   124,   125,   125,   125,   126,
     126,   127,   128,   129,   130,   130,   131,   131,   132,   133,
     133,   133,   133
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     1,     1,     1,     2,     1,     9,
       1,     4,     0,     4,     0,     3,     1,     1,     0,     3,
       0,     2,     4,     1,     3,     3,     1,     1,     2,     0,
       7,     6,     1,     3,     1,     1,     2,     0,     3,     3,
       1,     3,     2,     0,     1,     1,     1,     1,     1,     4,
       4,     6,     3,     1,     1,     1,     3,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     2,     5,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     3,     1,     1,
       2,     0,     3,     2,     1,     1,     0,     2,     4,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     1,     1,     4,     6,     6,     3,     3,     3,     2,
       1,     6,     6,     2,     3,     3,     3,     3,     3,     2,
       1,     2,     1
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
  "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\".\"",
  "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"",
  "\"%\"", "\"..\"", "\"->\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"",
  "\"{|\"", "\"|}\"", "\"binary\"", "\"hexadecimal\"", "\"integer\"",
  "\"rational\"", "\"floating\"", "\"string\"", "\"identifier\"", "UPLUS",
  "UMINUS", "$accept", "Specification", "Definition", "Definitions",
  "FunctionDefinition", "MaybeInitially", "MaybeDefined",
  "FunctionParameters", "MaybeFunctionParameters",
  "MaybeFunctionAttributes", "ProgramFunctionDefinition", "Initializer",
  "Initializers", "MaybeInitializers", "DerivedDefinition",
  "EnumerationDefinition", "Identifier", "Identifiers", "MaybeIdentifiers",
  "Variable", "Parameters", "MaybeParameters", "Type", "BasicType",
  "ComposedType", "FixedSizedType", "RangedType", "Types", "Atom",
  "Undefined", "Boolean", "String", "BitNumber", "IntegerNumber",
  "FloatingNumber", "RationalNumber", "RuleReference", "Range", "List",
  "Expression", "Expressions", "MaybeExpressions", "Arguments",
  "MaybeArguments", "DirectCallExpression", "IndirectCallExpression",
  "RuleDefinition", "Rule", "Rules", "SkipRule", "ConditionalRule",
  "CaseRule", "CaseLabel", "CaseLabels", "LetRule", "ForallRule",
  "IterateRule", "BlockRule", "SequenceRule", "UpdateRule", "CallRule", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   363,   363,   380,   384,   388,   392,   400,   406,   416,
     435,   443,   447,   455,   459,   467,   473,   483,   487,   495,
     499,   507,   522,   539,   548,   560,   566,   576,   580,   584,
     592,   600,   608,   616,   622,   632,   636,   640,   648,   656,
     662,   672,   676,   680,   688,   692,   696,   700,   708,   716,
     724,   732,   740,   746,   756,   760,   764,   768,   772,   778,
     782,   786,   790,   794,   798,   802,   806,   810,   814,   822,
     830,   835,   844,   853,   858,   867,   876,   885,   894,   902,
     910,   918,   922,   926,   930,   934,   938,   942,   946,   950,
     954,   958,   962,   966,   970,   974,   978,   986,   992,  1002,
    1006,  1010,  1018,  1022,  1030,  1034,  1040,  1048,  1056,  1064,
    1073,  1077,  1081,  1085,  1089,  1093,  1097,  1101,  1105,  1109,
    1117,  1123,  1133,  1141,  1145,  1153,  1161,  1166,  1171,  1179,
    1184,  1192,  1200,  1208,  1216,  1220,  1228,  1232,  1240,  1248,
    1252,  1256,  1260
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
#line 3134 "GrammarParser.cpp" // lalr1.cc:1167
#line 1266 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
