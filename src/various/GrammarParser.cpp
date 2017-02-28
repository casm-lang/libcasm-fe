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
      case 98: // BasicType
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

      case 99: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 126: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 77: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 78: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 89: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 120: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 90: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 81: // MaybeDefined
      case 103: // Atom
      case 114: // Expression
      case 115: // Term
        value.move< Expression::Ptr > (that.value);
        break;

      case 116: // Expressions
      case 117: // MaybeExpressions
      case 118: // Arguments
      case 119: // MaybeArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 100: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 131: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 79: // FunctionDefinition
      case 85: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 91: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
        break;

      case 121: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 132: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 130: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 113: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 84: // MaybeFunctionAttributes
      case 92: // Identifiers
      case 93: // MaybeIdentifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 80: // MaybeInitially
      case 87: // Initializers
      case 88: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 95: // Parameters
      case 96: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 112: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 101: // RangedType
        value.move< RangedType::Ptr > (that.value);
        break;

      case 123: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 122: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 111: // RuleReference
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

      case 76: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 97: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 82: // FunctionParameters
      case 83: // MaybeFunctionParameters
      case 102: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 104: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 86: // Initializer
      case 135: // UpdateRule
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
      case 98: // BasicType
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

      case 99: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 126: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 77: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 78: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 89: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 120: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 90: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 81: // MaybeDefined
      case 103: // Atom
      case 114: // Expression
      case 115: // Term
        value.copy< Expression::Ptr > (that.value);
        break;

      case 116: // Expressions
      case 117: // MaybeExpressions
      case 118: // Arguments
      case 119: // MaybeArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 100: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 131: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 79: // FunctionDefinition
      case 85: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 91: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
        break;

      case 121: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 132: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 130: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 113: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 84: // MaybeFunctionAttributes
      case 92: // Identifiers
      case 93: // MaybeIdentifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 80: // MaybeInitially
      case 87: // Initializers
      case 88: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 95: // Parameters
      case 96: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 112: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 101: // RangedType
        value.copy< RangedType::Ptr > (that.value);
        break;

      case 123: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 122: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 111: // RuleReference
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

      case 76: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 97: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 82: // FunctionParameters
      case 83: // MaybeFunctionParameters
      case 102: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 104: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 86: // Initializer
      case 135: // UpdateRule
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

#line 912 "GrammarParser.cpp" // lalr1.cc:741

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
      case 98: // BasicType
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

      case 99: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 126: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 77: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 78: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 89: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 120: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 90: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 81: // MaybeDefined
      case 103: // Atom
      case 114: // Expression
      case 115: // Term
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 116: // Expressions
      case 117: // MaybeExpressions
      case 118: // Arguments
      case 119: // MaybeArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 100: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 131: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 79: // FunctionDefinition
      case 85: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 91: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
        break;

      case 121: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 132: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 130: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 113: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 84: // MaybeFunctionAttributes
      case 92: // Identifiers
      case 93: // MaybeIdentifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 80: // MaybeInitially
      case 87: // Initializers
      case 88: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 95: // Parameters
      case 96: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 112: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 101: // RangedType
        yylhs.value.build< RangedType::Ptr > ();
        break;

      case 123: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 122: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 111: // RuleReference
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

      case 76: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 97: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 82: // FunctionParameters
      case 83: // MaybeFunctionParameters
      case 102: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 104: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 86: // Initializer
      case 135: // UpdateRule
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
#line 354 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1227 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1235 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 375 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1243 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 379 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1251 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 383 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1259 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1269 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1302 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 426 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1310 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1318 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1326 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1334 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1342 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 458 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 464 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1362 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 474 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1370 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = make< Types >( yylhs.location );
  }
#line 1378 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 486 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1386 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 490 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1394 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 498 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 515 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto arguments = make< Expressions >( yylhs.location );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, arguments );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1445 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto arguments = make< Expressions >( yylhs.location );
      arguments->add( yystack_[2].value.as< Expression::Ptr > () );

      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, args );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 552 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1472 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 564 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1482 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1492 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 580 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1500 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 584 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1508 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 592 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1516 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 600 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1524 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1532 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1542 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = make< NodeList< Identifier > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1552 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 632 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[0].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1560 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 636 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< Identifier > >( yylhs.location );
  }
#line 1568 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 644 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1576 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 648 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), ... ); // TODO
  }
#line 1584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 656 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1594 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 672 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1612 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 676 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1620 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 684 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1628 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 688 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 696 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 728 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 736 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1694 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 742 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1704 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 752 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1712 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1720 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1728 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1736 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 768 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1744 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1752 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 776 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1760 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1768 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 784 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 1776 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto zero = make< ZeroAtom >( yylhs.location );
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, zero, yystack_[0].value.as< Expression::Ptr > (),
                                               libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1786 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 798 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 806 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 811 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 820 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 829 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), 2 );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 834 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), 16 );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 843 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 852 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 861 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 870 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleReferenceAtom::Ptr > () = make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1874 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 878 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1882 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 886 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 1890 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 894 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 1898 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1906 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 1914 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 1922 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 910 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 1930 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 914 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call caret builtin
  }
#line 1938 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 1946 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 922 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 1954 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 926 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 1962 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 930 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 1970 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 934 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 1978 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 1986 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 942 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 1994 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 946 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2002 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2010 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2018 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 958 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2026 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto zero = make< ZeroAtom >( yylhs.location );
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, zero, yystack_[1].value.as< Expression::Ptr > (),
                                               libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2036 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2044 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 972 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2052 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2060 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 980 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2068 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 984 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2076 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 992 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2084 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 996 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2092 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1004 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2102 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2112 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1020 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[0].value.as< Expressions::Ptr > ();
  }
#line 2120 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = make< Expressions >( yylhs.location );
  }
#line 2128 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1032 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2136 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1040 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[0].value.as< Expressions::Ptr > ();
  }
#line 2144 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1044 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = make< Expressions >( yylhs.location );
  }
#line 2152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1052 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1060 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = make< IndirectCallExpression >( yylhs.location, yystack_[1].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1068 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), nullptr,
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) ); // TODO nullptr -> void
  }
#line 2177 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1073 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2186 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1094 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2218 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2226 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1102 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1110 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2250 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1114 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2258 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1118 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1126 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1132 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2286 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1142 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = make< SkipRule >( yylhs.location );
  }
#line 2294 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2302 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2310 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1162 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< std::vector< CaseRule::Case > > () );
  }
#line 2318 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1170 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1175 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1180 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1188 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = std::move( yystack_[0].value.as< std::vector< CaseRule::Case > > () );
      yylhs.value.as< std::vector< CaseRule::Case > > ().push_back( yystack_[1].value.as< CaseRule::Case > () );
  }
#line 2353 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1193 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = { yystack_[0].value.as< CaseRule::Case > () };
  }
#line 2361 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1201 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2369 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1209 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2377 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1217 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2385 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1225 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1229 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1237 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1241 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2417 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1249 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1257 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), { CallExpression::TargetType::RULE } );
  }
#line 2433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1261 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
#line 2441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1265 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), { CallExpression::TargetType::RULE } );
  }
#line 2449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1269 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2461 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -134;

  const signed char Parser::yytable_ninf_ = -102;

  const short int
  Parser::yypact_[] =
  {
      14,   121,    19,   -37,   -42,   -42,   -42,   -10,  -134,   121,
    -134,  -134,  -134,  -134,  -134,  -134,   476,  -134,  -134,    10,
      15,    10,   -42,   -42,  -134,  -134,  -134,  -134,   517,   564,
     576,   517,   517,   -14,   517,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,     6,    24,    27,  -134,  -134,  -134,  -134,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,  -134,   683,    11,  -134,
    -134,   -42,    16,    30,   -30,  -134,    45,    55,    51,   517,
    -134,   588,   588,   517,  -134,   517,  -134,    54,   857,    58,
      59,    22,   712,    73,  -134,   741,   476,  -134,   517,  -134,
    -134,   517,   517,   517,   517,   517,   517,   517,   517,   517,
     517,   517,   517,   517,   517,   517,   517,   517,    72,  -134,
      65,   -42,   -42,   406,   -42,   -42,  -134,   -42,    79,    81,
      89,  -134,   517,  -134,   517,  -134,  -134,  -134,   -15,   915,
     940,    80,    80,   211,   127,   127,    66,    66,    66,  -134,
     857,   211,   127,   127,   857,   -42,  -134,   -42,     1,   102,
    -134,  -134,  -134,  -134,   -34,   406,   406,  -134,   -42,   -42,
     406,   -39,   517,   517,   406,   406,    90,  -134,  -134,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,   111,
    -134,    99,   101,  -134,  -134,  -134,    23,   770,  -134,  -134,
     -42,   517,   517,  -134,  -134,   281,   294,   120,   141,  -134,
    -134,  -134,   625,   654,   342,   355,   517,   406,   -42,   -42,
    -134,  -134,    70,   799,   857,  -134,  -134,  -134,   517,   517,
     406,   117,  -134,  -134,   857,  -134,  -134,   150,  -134,   -42,
     517,   517,   401,   538,   137,   435,   122,   156,  -134,   886,
     406,   406,   406,   124,   125,   828,   435,   138,   588,   128,
    -134,   517,  -134,  -134,  -134,   406,   406,   406,  -134,  -134,
     139,   476,  -134,  -134,  -134,  -134,   140,  -134
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,    20,     8,     2,
       3,    10,     4,     6,     5,     1,    29,    32,    21,    42,
       0,    42,    36,     0,     7,    63,    65,    64,     0,     0,
       0,   103,   103,     0,     0,    67,    68,    69,    71,    70,
      66,    27,    28,     0,   106,    97,    59,    60,    58,    54,
      55,    56,    57,    53,    96,    95,    99,    23,     0,    93,
      94,     0,     0,     0,     0,    34,    35,     0,     0,     0,
      90,     0,     0,     0,    61,     0,    62,    99,     0,   102,
       0,    99,     0,     0,    72,     0,     0,    22,   103,   105,
     107,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    38,    40,
       0,     0,     0,     0,     0,     0,    19,    18,    99,    99,
      99,    98,     0,   104,     0,    74,   108,    26,    89,    87,
      88,    75,    76,    82,    83,    84,    77,    78,    79,    80,
      24,    81,    85,    86,    25,     0,    41,     0,    47,     0,
      43,    44,    45,    46,     0,     0,     0,   123,     0,     0,
       0,     0,     0,     0,     0,     0,   141,   143,   109,   111,
     112,   113,   114,   115,   116,   117,   118,   119,   120,     0,
      33,    17,     0,    16,    91,    92,    99,     0,    37,    39,
       0,     0,     0,    31,   122,     0,     0,     0,     0,   134,
     140,   142,     0,     0,     0,     0,     0,     0,     0,     0,
      73,    52,     0,     0,    30,   138,   121,   136,     0,     0,
       0,     0,   135,   137,   139,   110,    15,    14,    48,     0,
      49,     0,     0,     0,   124,     0,     0,    12,    51,     0,
       0,     0,     0,     0,     0,     0,   131,     0,     0,     0,
       9,    50,   132,   133,   125,     0,     0,     0,   130,   126,
       0,    29,   127,   128,   129,    13,     0,    11
  };

  const short int
  Parser::yypgoto_[] =
  {
    -134,  -134,   177,  -134,  -134,  -134,  -134,  -134,  -134,  -134,
    -134,   105,  -134,   -74,  -134,  -134,    -2,    82,  -134,  -133,
    -134,   171,   -85,  -134,  -134,  -134,  -134,  -134,   -24,  -134,
    -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,  -134,    67,
     -16,  -134,   161,   -36,  -134,  -103,    13,  -134,    36,  -122,
    -134,  -134,  -134,  -134,   -51,  -134,  -134,  -134,  -134,  -134,
    -134,  -134
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     8,     9,    10,   250,   237,   181,   182,    23,
      11,    41,    42,    43,    12,    13,    44,    66,    67,   109,
     110,    62,   149,   150,   151,   152,   153,   212,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      78,    79,    80,    58,    90,    59,    60,    14,   194,   195,
     169,   170,   171,   246,   247,   172,   173,   174,   175,   176,
     177,   178
  };

  const short int
  Parser::yytable_[] =
  {
      57,    18,    19,    20,    21,    74,    76,    16,    89,   113,
     166,   193,    70,    34,   189,   115,    82,     1,    85,    15,
      65,    68,    94,    95,    96,   197,   198,   114,    17,   179,
      22,    17,   183,    17,   196,    97,    98,    99,   100,   101,
     102,   190,   204,   205,   104,   105,   106,    74,    76,   126,
      61,   191,   166,   166,    63,    86,    84,   166,   200,   108,
     188,   166,   166,  -101,  -100,  -101,  -100,    88,   107,    87,
      57,  -101,  -100,   111,   112,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   139,   140,   141,   142,
     143,   144,   166,   166,   115,   121,   116,   117,    77,    81,
     123,   166,   166,  -101,   166,   211,   146,   122,   187,   148,
      65,   228,   148,   180,   147,   148,   125,   166,   145,   229,
     121,   102,   184,   226,   227,     3,   167,     4,     5,     6,
     185,     7,    99,   100,   101,   102,   118,   166,   166,   166,
     119,   192,   120,   148,   238,   108,   202,   203,   206,   168,
     207,   208,   166,   166,   166,    81,   108,   108,   209,   218,
     219,   235,   236,   242,    94,    95,   248,   249,   167,   167,
     255,   256,   261,   167,   201,   213,   214,   167,   167,    99,
     100,   101,   102,   259,   265,   267,    24,   266,   148,   186,
     224,   127,    64,    83,   154,   258,   199,     0,     0,     0,
       0,     0,   232,   233,     0,     0,   148,   148,   167,   167,
       0,     0,     0,     0,   135,   239,     0,   167,   167,   245,
     167,     0,     0,     0,   260,     0,     0,   148,     0,     0,
     245,   216,   216,   167,     0,   135,     0,     0,     0,     0,
     216,   216,     0,   225,     0,    57,     0,     0,    94,    95,
       0,     0,     0,   167,   167,   167,   234,     0,     0,     0,
       0,    97,    98,    99,   100,   101,   102,     0,   167,   167,
     167,   105,   106,     0,     0,     0,   252,   253,   254,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   262,   263,   264,   155,   215,   156,     0,   157,   158,
       0,   159,   160,     0,   161,   162,     0,   155,   163,   156,
     217,   157,   158,     0,   159,   160,     0,   161,   162,     0,
       0,   163,     0,     0,     0,   164,     0,     0,     0,     0,
       0,     0,     0,    34,     0,     0,     0,     0,   164,     0,
       0,     0,     0,   165,     0,     0,    34,     0,     0,     0,
       0,    17,     0,     0,     0,   155,   165,   156,     0,   157,
     158,     0,   159,   160,    17,   161,   162,     0,   155,   163,
     156,     0,   157,   158,     0,   159,   160,     0,   161,   162,
       0,     0,   163,     0,     0,     0,   164,   222,     0,     0,
       0,     0,     0,     0,    34,     0,     0,     0,     0,   164,
       0,     0,     0,     0,   165,     0,     0,    34,     0,     0,
       0,     0,    17,     0,     0,     0,     0,   165,   223,   155,
     240,   156,     0,   157,   158,    17,   159,   160,     0,   161,
     162,     0,     0,   163,    91,    92,    93,     0,    94,    95,
      96,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     164,    97,    98,    99,   100,   101,   102,     0,    34,     0,
     104,   105,   106,     0,   243,    25,    26,    27,   165,     0,
       0,    28,    29,    30,     0,    69,    17,    32,     0,     0,
       0,     0,   244,    33,     0,     0,     0,    34,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    35,
      36,    37,    38,    39,    40,    17,    25,    26,    27,     0,
       0,     0,    28,    29,    30,     0,    31,     0,    32,     0,
       0,     0,     0,     0,    33,     0,     0,     0,    34,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    37,    38,    39,    40,    17,    25,    26,    27,
       0,     0,     0,    28,    29,    30,     0,    69,     0,    32,
     241,     0,     0,     0,     0,    33,     0,     0,     0,    34,
       0,    91,    92,    93,     0,    94,    95,    96,     0,     0,
       0,    35,    36,    37,    38,    39,    40,    17,    97,    98,
      99,   100,   101,   102,    25,    26,    27,   104,   105,   106,
       0,    71,    72,     0,    73,     0,    25,    26,    27,     0,
       0,     0,    33,    71,    72,     0,    75,     0,    25,    26,
      27,     0,     0,     0,    33,    71,    72,     0,    35,    36,
      37,    38,    39,    40,     0,     0,    33,     0,     0,     0,
      35,    36,    37,    38,    39,    40,     0,     0,     0,     0,
     220,     0,    35,    36,    37,    38,    39,    40,    91,    92,
      93,     0,    94,    95,    96,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    97,    98,    99,   100,   101,
     102,     0,   221,     0,   104,   105,   106,    91,    92,    93,
       0,    94,    95,    96,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    97,    98,    99,   100,   101,   102,
       0,     0,     0,   104,   105,   106,    91,    92,    93,     0,
      94,    95,    96,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    97,    98,    99,   100,   101,   102,     0,
     103,     0,   104,   105,   106,    91,    92,    93,     0,    94,
      95,    96,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    97,    98,    99,   100,   101,   102,   124,     0,
       0,   104,   105,   106,    91,    92,    93,     0,    94,    95,
      96,    88,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    97,    98,    99,   100,   101,   102,     0,     0,     0,
     104,   105,   106,    91,    92,    93,     0,    94,    95,    96,
       0,     0,     0,   210,     0,     0,     0,     0,     0,     0,
      97,    98,    99,   100,   101,   102,     0,     0,     0,   104,
     105,   106,    91,    92,    93,     0,    94,    95,    96,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    97,
     230,    99,   100,   101,   102,   231,     0,     0,   104,   105,
     106,    91,    92,    93,     0,    94,    95,    96,     0,     0,
       0,     0,     0,     0,   257,     0,     0,     0,    97,    98,
      99,   100,   101,   102,     0,     0,     0,   104,   105,   106,
      91,    92,    93,     0,    94,    95,    96,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    97,    98,    99,
     100,   101,   102,     0,     0,     0,   104,   105,   106,    91,
      92,    93,     0,    94,    95,    96,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    97,   251,    99,   100,
     101,   102,     0,     0,     0,   104,   105,   106,    91,     0,
      93,     0,    94,    95,    96,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    97,    98,    99,   100,   101,
     102,     0,     0,    91,   104,   105,   106,    94,    95,    96,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      97,    98,    99,   100,   101,   102,     0,     0,     0,   104,
     105,   106
  };

  const short int
  Parser::yycheck_[] =
  {
      16,     3,     4,     5,     6,    29,    30,    44,    44,    39,
     113,    45,    28,    52,   147,    49,    32,     3,    34,     0,
      22,    23,    37,    38,    39,   158,   159,    57,    70,   114,
      40,    70,   117,    70,   156,    50,    51,    52,    53,    54,
      55,    40,   164,   165,    59,    60,    61,    71,    72,    85,
      40,    50,   155,   156,    39,    49,    70,   160,   161,    61,
     145,   164,   165,    41,    41,    43,    43,    40,    57,    45,
      86,    49,    49,    57,    44,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   195,   196,    49,    41,    41,    46,    31,    32,
      41,   204,   205,    49,   207,   190,    41,    49,   124,   111,
     112,    41,   114,   115,    49,   117,    43,   220,    46,    49,
      41,    55,    41,   208,   209,     4,   113,     6,     7,     8,
      41,    10,    52,    53,    54,    55,    69,   240,   241,   242,
      73,    39,    75,   145,   229,   147,   162,   163,    58,   113,
      39,    52,   255,   256,   257,    88,   158,   159,    57,    39,
      19,    44,    12,    26,    37,    38,    44,    11,   155,   156,
      46,    46,    44,   160,   161,   191,   192,   164,   165,    52,
      53,    54,    55,    45,    45,    45,     9,   261,   190,   122,
     206,    86,    21,    32,   112,   246,   160,    -1,    -1,    -1,
      -1,    -1,   218,   219,    -1,    -1,   208,   209,   195,   196,
      -1,    -1,    -1,    -1,   230,   231,    -1,   204,   205,   235,
     207,    -1,    -1,    -1,   248,    -1,    -1,   229,    -1,    -1,
     246,   195,   196,   220,    -1,   251,    -1,    -1,    -1,    -1,
     204,   205,    -1,   207,    -1,   261,    -1,    -1,    37,    38,
      -1,    -1,    -1,   240,   241,   242,   220,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    -1,   255,   256,
     257,    60,    61,    -1,    -1,    -1,   240,   241,   242,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   255,   256,   257,    13,    14,    15,    -1,    17,    18,
      -1,    20,    21,    -1,    23,    24,    -1,    13,    27,    15,
      16,    17,    18,    -1,    20,    21,    -1,    23,    24,    -1,
      -1,    27,    -1,    -1,    -1,    44,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    44,    -1,
      -1,    -1,    -1,    62,    -1,    -1,    52,    -1,    -1,    -1,
      -1,    70,    -1,    -1,    -1,    13,    62,    15,    -1,    17,
      18,    -1,    20,    21,    70,    23,    24,    -1,    13,    27,
      15,    -1,    17,    18,    -1,    20,    21,    -1,    23,    24,
      -1,    -1,    27,    -1,    -1,    -1,    44,    45,    -1,    -1,
      -1,    -1,    -1,    -1,    52,    -1,    -1,    -1,    -1,    44,
      -1,    -1,    -1,    -1,    62,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    70,    -1,    -1,    -1,    -1,    62,    63,    13,
      19,    15,    -1,    17,    18,    70,    20,    21,    -1,    23,
      24,    -1,    -1,    27,    33,    34,    35,    -1,    37,    38,
      39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      44,    50,    51,    52,    53,    54,    55,    -1,    52,    -1,
      59,    60,    61,    -1,    29,    30,    31,    32,    62,    -1,
      -1,    36,    37,    38,    -1,    40,    70,    42,    -1,    -1,
      -1,    -1,    47,    48,    -1,    -1,    -1,    52,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
      65,    66,    67,    68,    69,    70,    30,    31,    32,    -1,
      -1,    -1,    36,    37,    38,    -1,    40,    -1,    42,    -1,
      -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    70,    30,    31,    32,
      -1,    -1,    -1,    36,    37,    38,    -1,    40,    -1,    42,
      22,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    52,
      -1,    33,    34,    35,    -1,    37,    38,    39,    -1,    -1,
      -1,    64,    65,    66,    67,    68,    69,    70,    50,    51,
      52,    53,    54,    55,    30,    31,    32,    59,    60,    61,
      -1,    37,    38,    -1,    40,    -1,    30,    31,    32,    -1,
      -1,    -1,    48,    37,    38,    -1,    40,    -1,    30,    31,
      32,    -1,    -1,    -1,    48,    37,    38,    -1,    64,    65,
      66,    67,    68,    69,    -1,    -1,    48,    -1,    -1,    -1,
      64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
      25,    -1,    64,    65,    66,    67,    68,    69,    33,    34,
      35,    -1,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      55,    -1,    28,    -1,    59,    60,    61,    33,    34,    35,
      -1,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,    55,
      -1,    -1,    -1,    59,    60,    61,    33,    34,    35,    -1,
      37,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    50,    51,    52,    53,    54,    55,    -1,
      57,    -1,    59,    60,    61,    33,    34,    35,    -1,    37,
      38,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    50,    51,    52,    53,    54,    55,    56,    -1,
      -1,    59,    60,    61,    33,    34,    35,    -1,    37,    38,
      39,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    50,    51,    52,    53,    54,    55,    -1,    -1,    -1,
      59,    60,    61,    33,    34,    35,    -1,    37,    38,    39,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    -1,    -1,    -1,    59,
      60,    61,    33,    34,    35,    -1,    37,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,
      51,    52,    53,    54,    55,    56,    -1,    -1,    59,    60,
      61,    33,    34,    35,    -1,    37,    38,    39,    -1,    -1,
      -1,    -1,    -1,    -1,    46,    -1,    -1,    -1,    50,    51,
      52,    53,    54,    55,    -1,    -1,    -1,    59,    60,    61,
      33,    34,    35,    -1,    37,    38,    39,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,
      53,    54,    55,    -1,    -1,    -1,    59,    60,    61,    33,
      34,    35,    -1,    37,    38,    39,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,
      54,    55,    -1,    -1,    -1,    59,    60,    61,    33,    -1,
      35,    -1,    37,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    50,    51,    52,    53,    54,
      55,    -1,    -1,    33,    59,    60,    61,    37,    38,    39,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      50,    51,    52,    53,    54,    55,    -1,    -1,    -1,    59,
      60,    61
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    76,     4,     6,     7,     8,    10,    77,    78,
      79,    85,    89,    90,   122,     0,    44,    70,    91,    91,
      91,    91,    40,    84,    77,    30,    31,    32,    36,    37,
      38,    40,    42,    48,    52,    64,    65,    66,    67,    68,
      69,    86,    87,    88,    91,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   118,   120,
     121,    40,    96,    39,    96,    91,    92,    93,    91,    40,
     115,    37,    38,    40,   103,    40,   103,   114,   115,   116,
     117,   114,   115,   117,    70,   115,    49,    45,    40,   118,
     119,    33,    34,    35,    37,    38,    39,    50,    51,    52,
      53,    54,    55,    57,    59,    60,    61,    57,    91,    94,
      95,    57,    44,    39,    57,    49,    41,    46,   114,   114,
     114,    41,    49,    41,    56,    43,   118,    86,   115,   115,
     115,   115,   115,   115,   115,   115,   115,   115,   115,   115,
     115,   115,   115,   115,   115,    46,    41,    49,    91,    97,
      98,    99,   100,   101,    92,    13,    15,    17,    18,    20,
      21,    23,    24,    27,    44,    62,   120,   121,   123,   125,
     126,   127,   130,   131,   132,   133,   134,   135,   136,    97,
      91,    82,    83,    97,    41,    41,   114,   115,    97,    94,
      40,    50,    39,    45,   123,   124,   124,    94,    94,   123,
     120,   121,   115,   115,   124,   124,    58,    39,    52,    57,
      43,    97,   102,   115,   115,    14,   123,    16,    39,    19,
      25,    28,    45,    63,   115,   123,    97,    97,    41,    49,
      51,    56,   115,   115,   123,    44,    12,    81,    97,   115,
      19,    22,    26,    29,    47,   115,   128,   129,    44,    11,
      80,    51,   123,   123,   123,    46,    46,    46,   129,    45,
     103,    44,   123,   123,   123,    45,    88,    45
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    75,    76,    77,    77,    77,    77,    78,    78,    79,
      79,    80,    80,    81,    81,    82,    82,    83,    83,    84,
      84,    85,    85,    86,    86,    86,    87,    87,    88,    88,
      89,    90,    91,    92,    92,    93,    93,    94,    94,    95,
      95,    96,    96,    97,    97,    97,    97,    98,    99,   100,
     101,   102,   102,   103,   103,   103,   103,   103,   103,   103,
     103,   103,   103,   104,   105,   105,   106,   107,   107,   108,
     109,   110,   111,   112,   113,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   115,   115,
     116,   116,   117,   117,   118,   119,   119,   120,   121,   122,
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
       1,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     5,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     4,     4,     1,     1,     1,     1,     1,     3,     1,
       3,     1,     1,     0,     3,     1,     0,     2,     3,     5,
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
  "UMINUS", "UASTERIX", "DIRECT_CALL", "$accept", "Specification",
  "Definition", "Definitions", "FunctionDefinition", "MaybeInitially",
  "MaybeDefined", "FunctionParameters", "MaybeFunctionParameters",
  "MaybeFunctionAttributes", "ProgramFunctionDefinition", "Initializer",
  "Initializers", "MaybeInitializers", "DerivedDefinition",
  "EnumerationDefinition", "Identifier", "Identifiers", "MaybeIdentifiers",
  "Variable", "Parameters", "MaybeParameters", "Type", "BasicType",
  "ComposedType", "FixedSizedType", "RangedType", "Types", "Atom",
  "Undefined", "Boolean", "String", "BitNumber", "IntegerNumber",
  "FloatingNumber", "RationalNumber", "RuleReference", "Range", "List",
  "Expression", "Term", "Expressions", "MaybeExpressions", "Arguments",
  "MaybeArguments", "DirectCallExpression", "IndirectCallExpression",
  "RuleDefinition", "Rule", "Rules", "SkipRule", "ConditionalRule",
  "CaseRule", "CaseLabel", "CaseLabels", "LetRule", "ForallRule",
  "IterateRule", "BlockRule", "SequenceRule", "UpdateRule", "CallRule", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   353,   353,   370,   374,   378,   382,   390,   396,   406,
     425,   433,   437,   445,   449,   457,   463,   473,   477,   485,
     489,   497,   514,   531,   540,   551,   563,   569,   579,   583,
     591,   599,   607,   615,   621,   631,   635,   643,   647,   655,
     661,   671,   675,   683,   687,   691,   695,   703,   711,   719,
     727,   735,   741,   751,   755,   759,   763,   767,   771,   775,
     779,   783,   787,   797,   805,   810,   819,   828,   833,   842,
     851,   860,   869,   877,   885,   893,   897,   901,   905,   909,
     913,   917,   921,   925,   929,   933,   937,   941,   945,   949,
     953,   957,   961,   967,   971,   975,   979,   983,   991,   995,
    1003,  1009,  1019,  1023,  1031,  1039,  1043,  1051,  1059,  1067,
    1072,  1081,  1085,  1089,  1093,  1097,  1101,  1105,  1109,  1113,
    1117,  1125,  1131,  1141,  1149,  1153,  1161,  1169,  1174,  1179,
    1187,  1192,  1200,  1208,  1216,  1224,  1228,  1236,  1240,  1248,
    1256,  1260,  1264,  1268
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
#line 3181 "GrammarParser.cpp" // lalr1.cc:1167
#line 1274 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
