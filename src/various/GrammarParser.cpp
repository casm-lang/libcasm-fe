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
      case 100: // BasicType
        value.move< BasicType::Ptr > (that.value);
        break;

      case 138: // BlockRule
        value.move< BlockRule::Ptr > (that.value);
        break;

      case 141: // CallRule
        value.move< CallRule::Ptr > (that.value);
        break;

      case 133: // CaseLabel
        value.move< CaseRule::Case > (that.value);
        break;

      case 132: // CaseRule
        value.move< CaseRule::Ptr > (that.value);
        break;

      case 101: // ComposedType
        value.move< ComposedType::Ptr > (that.value);
        break;

      case 124: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (that.value);
        break;

      case 131: // ConditionalRule
        value.move< ConditionalRule::Ptr > (that.value);
        break;

      case 79: // Definition
        value.move< Definition::Ptr > (that.value);
        break;

      case 80: // Definitions
        value.move< Definitions::Ptr > (that.value);
        break;

      case 91: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (that.value);
        break;

      case 122: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (that.value);
        break;

      case 92: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (that.value);
        break;

      case 126: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 83: // MaybeDefined
      case 105: // Atom
      case 116: // Expression
      case 117: // Term
        value.move< Expression::Ptr > (that.value);
        break;

      case 118: // Expressions
      case 119: // MaybeExpressions
      case 120: // Arguments
      case 121: // MaybeArguments
        value.move< Expressions::Ptr > (that.value);
        break;

      case 102: // FixedSizedType
        value.move< FixedSizedType::Ptr > (that.value);
        break;

      case 136: // ForallRule
        value.move< ForallRule::Ptr > (that.value);
        break;

      case 81: // FunctionDefinition
      case 87: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (that.value);
        break;

      case 93: // Identifier
        value.move< IdentifierNode::Ptr > (that.value);
        break;

      case 123: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (that.value);
        break;

      case 137: // IterateRule
        value.move< IterateRule::Ptr > (that.value);
        break;

      case 135: // LetRule
        value.move< LetRule::Ptr > (that.value);
        break;

      case 115: // List
        value.move< ListExpression::Ptr > (that.value);
        break;

      case 86: // MaybeFunctionAttributes
      case 94: // Identifiers
      case 95: // MaybeIdentifiers
        value.move< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 82: // MaybeInitially
      case 89: // Initializers
      case 90: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 97: // Parameters
      case 98: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 114: // Range
        value.move< RangeExpression::Ptr > (that.value);
        break;

      case 103: // RangedType
        value.move< RangedType::Ptr > (that.value);
        break;

      case 128: // Rule
        value.move< Rule::Ptr > (that.value);
        break;

      case 127: // RuleDefinition
        value.move< RuleDefinition::Ptr > (that.value);
        break;

      case 113: // RuleReference
        value.move< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 129: // Rules
        value.move< Rules::Ptr > (that.value);
        break;

      case 139: // SequenceRule
        value.move< SequenceRule::Ptr > (that.value);
        break;

      case 130: // SkipRule
        value.move< SkipRule::Ptr > (that.value);
        break;

      case 78: // Specification
        value.move< Specification::Ptr > (that.value);
        break;

      case 99: // Type
        value.move< Type::Ptr > (that.value);
        break;

      case 84: // FunctionParameters
      case 85: // MaybeFunctionParameters
      case 104: // Types
        value.move< Types::Ptr > (that.value);
        break;

      case 106: // Undefined
        value.move< UndefAtom::Ptr > (that.value);
        break;

      case 125: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // Initializer
      case 140: // UpdateRule
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

      case 67: // "binary"
      case 68: // "hexadecimal"
      case 69: // "integer"
      case 70: // "rational"
      case 71: // "floating"
      case 72: // "string"
      case 73: // "identifier"
        value.move< std::string > (that.value);
        break;

      case 134: // CaseLabels
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
      case 100: // BasicType
        value.copy< BasicType::Ptr > (that.value);
        break;

      case 138: // BlockRule
        value.copy< BlockRule::Ptr > (that.value);
        break;

      case 141: // CallRule
        value.copy< CallRule::Ptr > (that.value);
        break;

      case 133: // CaseLabel
        value.copy< CaseRule::Case > (that.value);
        break;

      case 132: // CaseRule
        value.copy< CaseRule::Ptr > (that.value);
        break;

      case 101: // ComposedType
        value.copy< ComposedType::Ptr > (that.value);
        break;

      case 124: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (that.value);
        break;

      case 131: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (that.value);
        break;

      case 79: // Definition
        value.copy< Definition::Ptr > (that.value);
        break;

      case 80: // Definitions
        value.copy< Definitions::Ptr > (that.value);
        break;

      case 91: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (that.value);
        break;

      case 122: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (that.value);
        break;

      case 92: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (that.value);
        break;

      case 126: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (that.value);
        break;

      case 83: // MaybeDefined
      case 105: // Atom
      case 116: // Expression
      case 117: // Term
        value.copy< Expression::Ptr > (that.value);
        break;

      case 118: // Expressions
      case 119: // MaybeExpressions
      case 120: // Arguments
      case 121: // MaybeArguments
        value.copy< Expressions::Ptr > (that.value);
        break;

      case 102: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (that.value);
        break;

      case 136: // ForallRule
        value.copy< ForallRule::Ptr > (that.value);
        break;

      case 81: // FunctionDefinition
      case 87: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (that.value);
        break;

      case 93: // Identifier
        value.copy< IdentifierNode::Ptr > (that.value);
        break;

      case 123: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (that.value);
        break;

      case 137: // IterateRule
        value.copy< IterateRule::Ptr > (that.value);
        break;

      case 135: // LetRule
        value.copy< LetRule::Ptr > (that.value);
        break;

      case 115: // List
        value.copy< ListExpression::Ptr > (that.value);
        break;

      case 86: // MaybeFunctionAttributes
      case 94: // Identifiers
      case 95: // MaybeIdentifiers
        value.copy< NodeList< IdentifierNode >::Ptr > (that.value);
        break;

      case 82: // MaybeInitially
      case 89: // Initializers
      case 90: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (that.value);
        break;

      case 97: // Parameters
      case 98: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (that.value);
        break;

      case 114: // Range
        value.copy< RangeExpression::Ptr > (that.value);
        break;

      case 103: // RangedType
        value.copy< RangedType::Ptr > (that.value);
        break;

      case 128: // Rule
        value.copy< Rule::Ptr > (that.value);
        break;

      case 127: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (that.value);
        break;

      case 113: // RuleReference
        value.copy< RuleReferenceAtom::Ptr > (that.value);
        break;

      case 129: // Rules
        value.copy< Rules::Ptr > (that.value);
        break;

      case 139: // SequenceRule
        value.copy< SequenceRule::Ptr > (that.value);
        break;

      case 130: // SkipRule
        value.copy< SkipRule::Ptr > (that.value);
        break;

      case 78: // Specification
        value.copy< Specification::Ptr > (that.value);
        break;

      case 99: // Type
        value.copy< Type::Ptr > (that.value);
        break;

      case 84: // FunctionParameters
      case 85: // MaybeFunctionParameters
      case 104: // Types
        value.copy< Types::Ptr > (that.value);
        break;

      case 106: // Undefined
        value.copy< UndefAtom::Ptr > (that.value);
        break;

      case 125: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (that.value);
        break;

      case 88: // Initializer
      case 140: // UpdateRule
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

      case 67: // "binary"
      case 68: // "hexadecimal"
      case 69: // "integer"
      case 70: // "rational"
      case 71: // "floating"
      case 72: // "string"
      case 73: // "identifier"
        value.copy< std::string > (that.value);
        break;

      case 134: // CaseLabels
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
      case 100: // BasicType
        yylhs.value.build< BasicType::Ptr > ();
        break;

      case 138: // BlockRule
        yylhs.value.build< BlockRule::Ptr > ();
        break;

      case 141: // CallRule
        yylhs.value.build< CallRule::Ptr > ();
        break;

      case 133: // CaseLabel
        yylhs.value.build< CaseRule::Case > ();
        break;

      case 132: // CaseRule
        yylhs.value.build< CaseRule::Ptr > ();
        break;

      case 101: // ComposedType
        yylhs.value.build< ComposedType::Ptr > ();
        break;

      case 124: // ConditionalExpression
        yylhs.value.build< ConditionalExpression::Ptr > ();
        break;

      case 131: // ConditionalRule
        yylhs.value.build< ConditionalRule::Ptr > ();
        break;

      case 79: // Definition
        yylhs.value.build< Definition::Ptr > ();
        break;

      case 80: // Definitions
        yylhs.value.build< Definitions::Ptr > ();
        break;

      case 91: // DerivedDefinition
        yylhs.value.build< DerivedDefinition::Ptr > ();
        break;

      case 122: // DirectCallExpression
        yylhs.value.build< DirectCallExpression::Ptr > ();
        break;

      case 92: // EnumerationDefinition
        yylhs.value.build< EnumerationDefinition::Ptr > ();
        break;

      case 126: // ExistentialQuantifierExpression
        yylhs.value.build< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 83: // MaybeDefined
      case 105: // Atom
      case 116: // Expression
      case 117: // Term
        yylhs.value.build< Expression::Ptr > ();
        break;

      case 118: // Expressions
      case 119: // MaybeExpressions
      case 120: // Arguments
      case 121: // MaybeArguments
        yylhs.value.build< Expressions::Ptr > ();
        break;

      case 102: // FixedSizedType
        yylhs.value.build< FixedSizedType::Ptr > ();
        break;

      case 136: // ForallRule
        yylhs.value.build< ForallRule::Ptr > ();
        break;

      case 81: // FunctionDefinition
      case 87: // ProgramFunctionDefinition
        yylhs.value.build< FunctionDefinition::Ptr > ();
        break;

      case 93: // Identifier
        yylhs.value.build< IdentifierNode::Ptr > ();
        break;

      case 123: // IndirectCallExpression
        yylhs.value.build< IndirectCallExpression::Ptr > ();
        break;

      case 137: // IterateRule
        yylhs.value.build< IterateRule::Ptr > ();
        break;

      case 135: // LetRule
        yylhs.value.build< LetRule::Ptr > ();
        break;

      case 115: // List
        yylhs.value.build< ListExpression::Ptr > ();
        break;

      case 86: // MaybeFunctionAttributes
      case 94: // Identifiers
      case 95: // MaybeIdentifiers
        yylhs.value.build< NodeList< IdentifierNode >::Ptr > ();
        break;

      case 82: // MaybeInitially
      case 89: // Initializers
      case 90: // MaybeInitializers
        yylhs.value.build< NodeList< UpdateRule >::Ptr > ();
        break;

      case 97: // Parameters
      case 98: // MaybeParameters
        yylhs.value.build< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 114: // Range
        yylhs.value.build< RangeExpression::Ptr > ();
        break;

      case 103: // RangedType
        yylhs.value.build< RangedType::Ptr > ();
        break;

      case 128: // Rule
        yylhs.value.build< Rule::Ptr > ();
        break;

      case 127: // RuleDefinition
        yylhs.value.build< RuleDefinition::Ptr > ();
        break;

      case 113: // RuleReference
        yylhs.value.build< RuleReferenceAtom::Ptr > ();
        break;

      case 129: // Rules
        yylhs.value.build< Rules::Ptr > ();
        break;

      case 139: // SequenceRule
        yylhs.value.build< SequenceRule::Ptr > ();
        break;

      case 130: // SkipRule
        yylhs.value.build< SkipRule::Ptr > ();
        break;

      case 78: // Specification
        yylhs.value.build< Specification::Ptr > ();
        break;

      case 99: // Type
        yylhs.value.build< Type::Ptr > ();
        break;

      case 84: // FunctionParameters
      case 85: // MaybeFunctionParameters
      case 104: // Types
        yylhs.value.build< Types::Ptr > ();
        break;

      case 106: // Undefined
        yylhs.value.build< UndefAtom::Ptr > ();
        break;

      case 125: // UniversalQuantifierExpression
        yylhs.value.build< UniversalQuantifierExpression::Ptr > ();
        break;

      case 88: // Initializer
      case 140: // UpdateRule
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

      case 67: // "binary"
      case 68: // "hexadecimal"
      case 69: // "integer"
      case 70: // "rational"
      case 71: // "floating"
      case 72: // "string"
      case 73: // "identifier"
        yylhs.value.build< std::string > ();
        break;

      case 134: // CaseLabels
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
#line 360 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 377 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > ();
  }
#line 1271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 381 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< DerivedDefinition::Ptr > ();
  }
#line 1279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 385 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< RuleDefinition::Ptr > ();
  }
#line 1287 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 389 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Definition::Ptr > () = yystack_[0].value.as< EnumerationDefinition::Ptr > ();
  }
#line 1295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = yystack_[1].value.as< Definitions::Ptr > ();
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1305 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 403 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto definitions = make< Definitions >( yylhs.location );
      definitions->add( yystack_[0].value.as< Definition::Ptr > () );
      yylhs.value.as< Definitions::Ptr > () = definitions;
  }
#line 1315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 413 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 432 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FunctionDefinition::Ptr > () = yystack_[0].value.as< FunctionDefinition::Ptr > (); // `init` special case
  }
#line 1346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 440 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[1].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1354 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1362 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 452 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 1370 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 456 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1378 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 464 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 470 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1398 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = yystack_[0].value.as< Types::Ptr > ();
  }
#line 1406 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Types::Ptr > () = make< Types >( yylhs.location );
  }
#line 1414 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 492 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 496 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< IdentifierNode > >( yylhs.location );
  }
#line 1430 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 504 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 521 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 538 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 547 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 558 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // the unknown function identifier will be replaced in FunctionDefinition
      const auto unknown = make< IdentifierNode >( yylhs.location, std::string() );
      const auto function = make< DirectCallExpression >( yylhs.location, unknown, yystack_[2].value.as< Expressions::Ptr > () );

      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, function, yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1508 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = yystack_[2].value.as< NodeList< UpdateRule >::Ptr > ();
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1518 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 576 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = make< NodeList< UpdateRule > >( yylhs.location );
      initializers->add( yystack_[0].value.as< UpdateRule::Ptr > () );
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = initializers;
  }
#line 1528 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 586 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = yystack_[0].value.as< NodeList< UpdateRule >::Ptr > ();
  }
#line 1536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 590 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< UpdateRule >::Ptr > () = make< NodeList< UpdateRule > >( yylhs.location );
  }
#line 1544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 598 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DerivedDefinition::Ptr > () = make< DerivedDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 1552 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 606 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< EnumerationDefinition::Ptr > () = make< EnumerationDefinition >( yylhs.location, yystack_[4].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< NodeList< IdentifierNode >::Ptr > () );
  }
#line 1560 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 614 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IdentifierNode::Ptr > () = make< IdentifierNode >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1568 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = yystack_[2].value.as< NodeList< IdentifierNode >::Ptr > ();
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1578 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 628 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto identifiers = make< NodeList< Identifier > >( yylhs.location );
      identifiers->add( yystack_[0].value.as< IdentifierNode::Ptr > () );
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = identifiers;
  }
#line 1588 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 638 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = yystack_[0].value.as< NodeList< IdentifierNode >::Ptr > ();
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 642 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< IdentifierNode >::Ptr > () = make< NodeList< Identifier > >( yylhs.location );
  }
#line 1604 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[2].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Type::Ptr > () );
  }
#line 1612 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 654 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< VariableDefinition::Ptr > () = make< VariableDefinition >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > (), ... ); // TODO
  }
#line 1620 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > ();
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1630 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 668 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto parameters = make< NodeList< VariableDefinition > >( yylhs.location );
      parameters->add( yystack_[0].value.as< VariableDefinition::Ptr > () );
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = parameters;
  }
#line 1640 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 678 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = yystack_[1].value.as< NodeList< VariableDefinition >::Ptr > ();
  }
#line 1648 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 682 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< NodeList< VariableDefinition >::Ptr > () = make< NodeList< VariableDefinition > >( yylhs.location );
  }
#line 1656 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 690 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< BasicType::Ptr > ();
  }
#line 1664 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 694 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< ComposedType::Ptr > ();
  }
#line 1672 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 698 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< FixedSizedType::Ptr > ();
  }
#line 1680 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 702 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type::Ptr > () = yystack_[0].value.as< RangedType::Ptr > ();
  }
#line 1688 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BasicType::Ptr > () = make< BasicType >( yylhs.location, yystack_[0].value.as< IdentifierNode::Ptr > () );
  }
#line 1696 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ComposedType::Ptr > () = make< ComposedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Types::Ptr > () );
  }
#line 1704 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 726 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FixedSizedType::Ptr > () = make< FixedSizedType >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1712 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 734 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangedType::Ptr > () = make< RangedType >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1720 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 742 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = yystack_[2].value.as< Types::Ptr > ();
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1730 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 748 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto types = make< Types >( yylhs.location );
      types->add( yystack_[0].value.as< Type::Ptr > () );
      yylhs.value.as< Types::Ptr > () = types;
  }
#line 1740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 758 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RuleReferenceAtom::Ptr > ();
  }
#line 1748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 762 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 766 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 774 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1780 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 782 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UndefAtom::Ptr > ();
  }
#line 1796 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 786 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ValueAtom::Ptr > ();
  }
#line 1804 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 794 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UndefAtom::Ptr > () = make< UndefAtom >( yylhs.location );
  }
#line 1812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 802 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( true );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 807 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BooleanConstant >( false );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1830 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::StringConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), 2 );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1848 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 830 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::BitConstant >( yystack_[0].value.as< std::string > (), 16 );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 839 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::IntegerConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1866 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 848 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::FloatingConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1875 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 857 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto value = libstdhl::get< libcasm_ir::RationalConstant >( yystack_[0].value.as< std::string > () );
      yylhs.value.as< ValueAtom::Ptr > () = make< ValueAtom >( yylhs.location, value );
  }
#line 1884 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 866 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleReferenceAtom::Ptr > () = make< RuleReferenceAtom >( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 874 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RangeExpression::Ptr > () = make< RangeExpression >( yylhs.location, yystack_[3].value.as< Expression::Ptr > (), yystack_[1].value.as< Expression::Ptr > () );
  }
#line 1900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 882 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ListExpression::Ptr > () = make< ListExpression >( yylhs.location, yystack_[1].value.as< Expressions::Ptr > () );
  }
#line 1908 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 1916 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 894 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1924 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 1932 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 1940 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 1948 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 910 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO call caret builtin
  }
#line 1956 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 914 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 1964 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 1972 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 922 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 1980 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 926 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 1988 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 930 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 1996 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 934 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2004 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2012 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 942 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 946 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = make< UnaryExpression >( yylhs.location, yystack_[0].value.as< Expression::Ptr > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2036 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2044 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[1].value.as< Expression::Ptr > ();
  }
#line 2052 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2060 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const auto zero = make< ZeroAtom >( yylhs.location );
      yylhs.value.as< Expression::Ptr > () = make< BinaryExpression >( yylhs.location, zero, yystack_[0].value.as< Expression::Ptr > (),
                                               libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2070 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< DirectCallExpression::Ptr > ();
  }
#line 2078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 980 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< IndirectCallExpression::Ptr > ();
  }
#line 2086 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 984 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ConditionalExpression::Ptr > ();
  }
#line 2094 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 988 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< UniversalQuantifierExpression::Ptr > ();
  }
#line 2102 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 992 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ExistentialQuantifierExpression::Ptr > ();
  }
#line 2110 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 996 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< ListExpression::Ptr > ();
  }
#line 2118 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1000 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< RangeExpression::Ptr > ();
  }
#line 2126 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1004 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expression::Ptr > () = yystack_[0].value.as< Expression::Ptr > ();
  }
#line 2134 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1012 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = yystack_[2].value.as< Expressions::Ptr > ();
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2144 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto expressions = make< Expressions >( yylhs.location );
      expressions->add( yystack_[0].value.as< Expression::Ptr > () );
      yylhs.value.as< Expressions::Ptr > () = expressions;
  }
#line 2154 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1028 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[0].value.as< Expressions::Ptr > ();
  }
#line 2162 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1032 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = make< Expressions >( yylhs.location );
  }
#line 2170 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1040 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[1].value.as< Expressions::Ptr > ();
  }
#line 2178 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1048 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = yystack_[0].value.as< Expressions::Ptr > ();
  }
#line 2186 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1052 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Expressions::Ptr > () = make< Expressions >( yylhs.location );
  }
#line 2194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1060 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DirectCallExpression::Ptr > () = make< DirectCallExpression >( yylhs.location, yystack_[1].value.as< IdentifierNode::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1068 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IndirectCallExpression::Ptr > () = make< IndirectCallExpression >( yylhs.location, yystack_[1].value.as< Expression::Ptr > (), yystack_[0].value.as< Expressions::Ptr > () );
  }
#line 2210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1076 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalExpression::Ptr > () = make< ConditionalExpression >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2218 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1084 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UniversalQuantifierExpression::Ptr > () = make< UniversalQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2226 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1092 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExistentialQuantifierExpression::Ptr > () = make< ExistentialQuantifierExpression >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1100 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[3].value.as< IdentifierNode::Ptr > (), yystack_[2].value.as< NodeList< VariableDefinition >::Ptr > (), nullptr,
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) ); // TODO nullptr -> void
  }
#line 2243 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1105 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RuleDefinition::Ptr > () = make< RuleDefinition >( yylhs.location, yystack_[5].value.as< IdentifierNode::Ptr > (), yystack_[4].value.as< NodeList< VariableDefinition >::Ptr > (), yystack_[2].value.as< Type::Ptr > (),
                                   wrapInBlockRule( yystack_[0].value.as< Rule::Ptr > () ) );
  }
#line 2252 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1114 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SkipRule::Ptr > ();
  }
#line 2260 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1118 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ConditionalRule::Ptr > ();
  }
#line 2268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1122 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CaseRule::Ptr > ();
  }
#line 2276 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1126 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< LetRule::Ptr > ();
  }
#line 2284 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1130 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< ForallRule::Ptr > ();
  }
#line 2292 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< IterateRule::Ptr > ();
  }
#line 2300 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1138 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< BlockRule::Ptr > ();
  }
#line 2308 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1142 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< SequenceRule::Ptr > ();
  }
#line 2316 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1146 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< UpdateRule::Ptr > ();
  }
#line 2324 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Rule::Ptr > () = yystack_[0].value.as< CallRule::Ptr > ();
  }
#line 2332 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1158 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = yystack_[1].value.as< Rules::Ptr > ();
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2342 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1164 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto rules = make< Rules >( yylhs.location );
      rules->add( yystack_[0].value.as< Rule::Ptr > () );
      yylhs.value.as< Rules::Ptr > () = rules;
  }
#line 2352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1174 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SkipRule::Ptr > () = make< SkipRule >( yylhs.location );
  }
#line 2360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1182 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1186 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ConditionalRule::Ptr > () = make< ConditionalRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[2].value.as< Rule::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1194 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Ptr > () = make< CaseRule >( yylhs.location, yystack_[4].value.as< Expression::Ptr > (), yystack_[1].value.as< std::vector< CaseRule::Case > > () );
  }
#line 2384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1202 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2393 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1207 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // default case
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( nullptr, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1212 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseRule::Case > () = CaseRule::Case( yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2410 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1220 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = std::move( yystack_[0].value.as< std::vector< CaseRule::Case > > () );
      yylhs.value.as< std::vector< CaseRule::Case > > ().push_back( yystack_[1].value.as< CaseRule::Case > () );
  }
#line 2419 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1225 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector< CaseRule::Case > > () = { yystack_[0].value.as< CaseRule::Case > () };
  }
#line 2427 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1233 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< LetRule::Ptr > () = make< LetRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2435 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1241 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallRule::Ptr > () = make< ForallRule >( yylhs.location, yystack_[4].value.as< VariableDefinition::Ptr > (), yystack_[2].value.as< Expression::Ptr > (), yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2443 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1249 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IterateRule::Ptr > () = make< IterateRule >( yylhs.location, yystack_[0].value.as< Rule::Ptr > () );
  }
#line 2451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1257 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1261 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BlockRule::Ptr > () = make< BlockRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2467 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1269 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1273 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< SequenceRule::Ptr > () = make< SequenceRule >( yylhs.location, yystack_[1].value.as< Rules::Ptr > () );
  }
#line 2483 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1281 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UpdateRule::Ptr > () = make< UpdateRule >( yylhs.location, yystack_[2].value.as< DirectCallExpression::Ptr > (), yystack_[0].value.as< Expression::Ptr > () );
  }
#line 2491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1289 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), { CallExpression::TargetType::RULE } );
  }
#line 2499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1293 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< DirectCallExpression::Ptr > (), { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
#line 2507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1297 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), { CallExpression::TargetType::RULE } );
  }
#line 2515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1301 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallRule::Ptr > () = make< CallRule >( yylhs.location, yystack_[0].value.as< IndirectCallExpression::Ptr > (), { CallExpression::TargetType::DERIVED, CallExpression::TargetType::BUILTIN } );
  }
#line 2523 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2527 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -132;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
       4,    88,     6,   -39,   -52,   -52,   -52,   -20,  -132,    88,
    -132,  -132,  -132,  -132,  -132,  -132,   489,  -132,  -132,    25,
     -14,    25,   -52,   -52,  -132,   -52,   543,   -52,  -132,  -132,
    -132,   543,   597,   597,   543,   543,   -27,   597,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,    20,    -1,    30,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,   803,
    -132,    37,  -132,  -132,  -132,  -132,  -132,   -52,    39,    46,
     -33,  -132,    48,    58,    56,    67,    94,   543,   618,   101,
    -132,  -132,  -132,   832,    55,    77,   861,    76,  -132,    30,
     489,  -132,   543,  -132,  -132,   543,   543,   543,   543,   543,
     543,   543,   543,   543,   543,   543,   543,   543,   543,   543,
     543,   543,  -132,    10,   -52,   -52,   398,   -52,   -52,  -132,
     -52,   -52,   543,   832,   543,   543,  -132,   543,  -132,   543,
    -132,  -132,  -132,  1006,  1108,  1064,  1089,    87,    87,  1127,
     -15,   -15,    68,    68,    68,  -132,  1006,  1127,   -15,   -15,
    1006,  -132,   -52,     2,    90,  -132,  -132,  -132,  -132,    15,
     398,   398,  -132,   -52,   -52,   398,   -44,   543,   543,   398,
     398,    74,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,    96,  -132,    84,    91,  -132,  -132,
     745,   685,   774,  1006,   890,  -132,   -52,   543,   543,  -132,
    -132,   110,   321,   106,   133,  -132,  -132,  -132,   652,   716,
     334,   385,   543,   398,   -52,   -52,   543,   543,   543,  -132,
    -132,    17,   919,  1006,  -132,  -132,  -132,   543,   543,   398,
     107,  -132,  -132,  1006,  -132,  -132,   141,  -132,  1006,  -132,
    -132,   -52,   543,   543,   242,    -5,   129,   435,   109,   147,
    -132,  1035,   398,   398,   398,   113,   117,   948,   435,   111,
     543,   120,  -132,   543,  -132,  -132,  -132,   398,   398,   398,
    -132,  -132,   977,   489,  -132,  -132,  -132,  -132,   122,  -132
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     0,     0,     0,     0,    20,     8,     2,
       3,    10,     4,     6,     5,     1,    29,    32,    21,    42,
       0,    42,    36,     0,     7,     0,     0,     0,    61,    63,
      62,     0,     0,     0,   104,   104,     0,     0,    65,    66,
      67,    69,    68,    64,    27,    28,     0,   107,   100,    59,
      60,    58,    54,    55,    56,    57,    53,    99,    98,    23,
      89,     0,    93,    94,    95,    96,    97,     0,     0,     0,
       0,    34,    35,     0,     0,    38,     0,     0,     0,     0,
      88,    91,    92,   102,   103,     0,   102,     0,    70,     0,
       0,    22,   104,   106,   108,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    40,     0,     0,     0,     0,     0,     0,    19,
      18,     0,     0,     0,     0,     0,    90,     0,   105,     0,
      72,   109,    26,   102,    87,    85,    86,    73,    74,    80,
      81,    82,    75,    76,    77,    78,    24,    79,    83,    84,
      25,    41,     0,    47,     0,    43,    44,    45,    46,     0,
       0,     0,   127,     0,     0,     0,     0,     0,     0,     0,
       0,   145,   147,   113,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,     0,    33,    17,     0,    16,    37,
       0,     0,     0,   101,     0,    39,     0,     0,     0,    31,
     126,     0,     0,     0,     0,   138,   144,   146,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    71,
      52,     0,     0,    30,   142,   125,   140,     0,     0,     0,
       0,   139,   141,   143,   114,    15,    14,   111,   110,   112,
      48,     0,    49,     0,     0,     0,   128,     0,     0,    12,
      51,     0,     0,     0,     0,     0,     0,     0,   135,     0,
       0,     0,     9,    50,   136,   137,   129,     0,     0,     0,
     134,   130,     0,    29,   131,   132,   133,    13,     0,    11
  };

  const short int
  Parser::yypgoto_[] =
  {
    -132,  -132,   162,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,    89,  -132,   -99,  -132,  -132,    -3,    63,  -132,   -23,
    -132,   160,  -105,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,   -21,
      33,  -132,   149,   -29,  -132,     3,    64,  -132,  -132,  -132,
    -132,    34,  -131,  -132,  -132,  -132,  -132,   -76,  -132,  -132,
    -132,  -132,  -132,  -132,  -132
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     8,     9,    10,   262,   249,   186,   187,    23,
      11,    44,    45,    46,    12,    13,    47,    72,    73,    76,
     113,    68,   154,   155,   156,   157,   158,   221,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    84,    85,    61,    94,    62,    63,    64,    65,    66,
      14,   200,   201,   174,   175,   176,   258,   259,   177,   178,
     179,   180,   181,   182,   183
  };

  const unsigned short int
  Parser::yytable_[] =
  {
      18,    19,    20,    21,    79,    78,    15,     1,    16,   116,
      80,    37,   184,    83,    86,   188,   189,   253,    93,    71,
      74,    17,    75,    22,    75,    98,    99,   117,    69,    17,
     202,    95,    96,    97,    17,    98,    99,   100,   210,   211,
     103,   104,   105,   106,   112,   196,    88,    91,   101,   102,
     103,   104,   105,   106,   151,   197,   123,   108,   109,   110,
     131,   240,   152,   199,    75,    81,    82,   118,    67,   241,
      89,   133,    90,    92,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,   145,   146,   147,   148,   149,
     150,   220,     3,   115,     4,     5,     6,   111,     7,   114,
     118,   190,   119,   191,   192,   120,   193,   127,   194,   235,
     236,   153,    71,   122,   153,   185,   121,   153,   153,   171,
     125,   128,   130,   160,   224,   161,   106,   162,   163,   195,
     164,   165,   198,   166,   167,   212,   250,   168,   213,   214,
     203,   204,   103,   104,   105,   106,   208,   209,   227,    75,
     173,   215,   228,   248,   247,   254,   260,   169,   261,   271,
      75,    75,   267,   171,   171,    37,   268,   273,   171,   206,
     279,    24,   171,   171,   278,   170,   222,   223,   159,   132,
     172,    70,   270,    17,    87,     0,     0,     0,     0,     0,
       0,   233,     0,   153,     0,   237,   238,   239,     0,   205,
       0,     0,     0,     0,   171,   171,   244,   245,     0,     0,
       0,   153,   153,   171,   171,     0,   171,     0,     0,     0,
       0,   141,   251,     0,   172,   172,   257,     0,     0,   172,
     207,     0,   171,   172,   172,   225,   225,   257,   153,   272,
       0,     0,   141,     0,   225,   225,     0,   234,     0,     0,
       0,     0,     0,     0,     0,   171,   171,   171,     0,     0,
       0,   252,     0,   246,     0,   172,   172,     0,     0,     0,
     171,   171,   171,     0,   172,   172,     0,   172,    95,    96,
      97,     0,    98,    99,   100,     0,   264,   265,   266,     0,
       0,     0,     0,   172,     0,   101,   102,   103,   104,   105,
     106,   274,   275,   276,   108,   109,   110,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   172,   172,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   172,   172,   172,   160,     0,   161,   226,   162,   163,
       0,   164,   165,     0,   166,   167,     0,   160,   168,   161,
       0,   162,   163,     0,   164,   165,     0,   166,   167,     0,
       0,   168,     0,     0,     0,     0,     0,     0,   169,     0,
       0,     0,     0,     0,     0,     0,    37,     0,     0,     0,
       0,   169,   231,     0,     0,     0,   170,     0,     0,    37,
       0,     0,     0,     0,    17,     0,     0,     0,   160,   170,
     161,     0,   162,   163,     0,   164,   165,    17,   166,   167,
       0,   160,   168,   161,     0,   162,   163,     0,   164,   165,
       0,   166,   167,     0,     0,   168,     0,     0,     0,     0,
       0,     0,   169,     0,     0,     0,     0,     0,     0,     0,
      37,     0,     0,     0,     0,   169,     0,     0,     0,     0,
     170,   232,     0,    37,     0,    25,     0,     0,    17,    26,
       0,     0,     0,   170,   255,     0,    27,     0,    28,    29,
      30,    17,     0,     0,    31,    32,    33,     0,    77,     0,
      35,     0,     0,     0,     0,   256,    36,     0,     0,     0,
      37,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    38,    39,    40,    41,    42,    43,    17,    25,
       0,     0,     0,    26,     0,     0,     0,     0,     0,     0,
      27,     0,    28,    29,    30,     0,     0,     0,    31,    32,
      33,     0,    34,     0,    35,     0,     0,     0,     0,     0,
      36,     0,     0,     0,    37,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
      42,    43,    17,    25,     0,     0,     0,    26,     0,     0,
       0,     0,     0,     0,    27,     0,    28,    29,    30,     0,
       0,     0,    31,    32,    33,     0,    77,     0,    35,     0,
       0,     0,     0,     0,    36,     0,     0,     0,    37,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      38,    39,    40,    41,    42,    43,    17,    25,     0,     0,
       0,    26,     0,     0,     0,     0,     0,     0,    27,     0,
      28,    29,    30,     0,     0,     0,     0,    32,    33,     0,
      77,     0,    35,   124,     0,     0,     0,     0,    36,     0,
       0,     0,    37,     0,    95,    96,    97,     0,    98,    99,
     100,     0,     0,     0,    38,    39,    40,    41,    42,    43,
      17,   101,   102,   103,   104,   105,   106,   229,     0,     0,
     108,   109,   110,     0,     0,     0,     0,     0,    95,    96,
      97,     0,    98,    99,   100,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   101,   102,   103,   104,   105,
     106,   217,     0,     0,   108,   109,   110,     0,     0,     0,
       0,    95,    96,    97,     0,    98,    99,   100,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,   102,
     103,   104,   105,   106,   230,     0,     0,   108,   109,   110,
       0,     0,    95,    96,    97,     0,    98,    99,   100,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
     102,   103,   104,   105,   106,   216,     0,     0,   108,   109,
     110,    95,    96,    97,     0,    98,    99,   100,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,   102,
     103,   104,   105,   106,     0,     0,   218,   108,   109,   110,
      95,    96,    97,     0,    98,    99,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,   102,   103,
     104,   105,   106,     0,     0,     0,   108,   109,   110,    95,
      96,    97,     0,    98,    99,   100,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   101,   102,   103,   104,
     105,   106,     0,   107,     0,   108,   109,   110,    95,    96,
      97,     0,    98,    99,   100,     0,   126,     0,     0,     0,
       0,     0,     0,     0,     0,   101,   102,   103,   104,   105,
     106,     0,     0,     0,   108,   109,   110,    95,    96,    97,
       0,    98,    99,   100,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   101,   102,   103,   104,   105,   106,
     129,     0,     0,   108,   109,   110,    95,    96,    97,     0,
      98,    99,   100,     0,     0,     0,   219,     0,     0,     0,
       0,     0,     0,   101,   102,   103,   104,   105,   106,     0,
       0,     0,   108,   109,   110,    95,    96,    97,     0,    98,
      99,   100,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,   242,   103,   104,   105,   106,   243,     0,
       0,   108,   109,   110,    95,    96,    97,     0,    98,    99,
     100,     0,     0,     0,     0,     0,     0,   269,     0,     0,
       0,   101,   102,   103,   104,   105,   106,     0,     0,     0,
     108,   109,   110,    95,    96,    97,     0,    98,    99,   100,
       0,     0,     0,     0,     0,   277,     0,     0,     0,     0,
     101,   102,   103,   104,   105,   106,     0,     0,     0,   108,
     109,   110,    95,    96,    97,     0,    98,    99,   100,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   101,
     102,   103,   104,   105,   106,     0,     0,     0,   108,   109,
     110,    95,    96,    97,     0,    98,    99,   100,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   101,   263,
     103,   104,   105,   106,     0,     0,     0,   108,   109,   110,
      95,     0,    97,     0,    98,    99,   100,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   101,   102,   103,
     104,   105,   106,     0,     0,    95,   108,   109,   110,    98,
      99,   100,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   101,   102,   103,   104,   105,   106,    98,    99,
     100,   108,   109,   110,     0,     0,     0,     0,     0,     0,
       0,   101,   102,   103,   104,   105,   106,    98,    99,     0,
     108,   109,   110,     0,     0,     0,     0,     0,     0,     0,
     101,   102,   103,   104,   105,   106,     0,     0,     0,     0,
     109,   110
  };

  const short int
  Parser::yycheck_[] =
  {
       3,     4,     5,     6,    27,    26,     0,     3,    47,    42,
      31,    55,   117,    34,    35,   120,   121,    22,    47,    22,
      23,    73,    25,    43,    27,    40,    41,    60,    42,    73,
     161,    36,    37,    38,    73,    40,    41,    42,   169,   170,
      55,    56,    57,    58,    67,    43,    73,    48,    53,    54,
      55,    56,    57,    58,    44,    53,    77,    62,    63,    64,
      89,    44,    52,    48,    67,    32,    33,    52,    43,    52,
      37,    92,    52,    43,    95,    96,    97,    98,    99,   100,
     101,   102,   103,   104,   105,   106,   107,   108,   109,   110,
     111,   196,     4,    47,     6,     7,     8,    60,    10,    60,
      52,   122,    44,   124,   125,    49,   127,    52,   129,   214,
     215,   114,   115,    19,   117,   118,    49,   120,   121,   116,
      19,    44,    46,    13,    14,    15,    58,    17,    18,   152,
      20,    21,    42,    23,    24,    61,   241,    27,    42,    55,
     163,   164,    55,    56,    57,    58,   167,   168,    42,   152,
     116,    60,    19,    12,    47,    26,    47,    47,    11,    48,
     163,   164,    49,   160,   161,    55,    49,    47,   165,   166,
      48,     9,   169,   170,   273,    65,   197,   198,   115,    90,
     116,    21,   258,    73,    35,    -1,    -1,    -1,    -1,    -1,
      -1,   212,    -1,   196,    -1,   216,   217,   218,    -1,   165,
      -1,    -1,    -1,    -1,   201,   202,   227,   228,    -1,    -1,
      -1,   214,   215,   210,   211,    -1,   213,    -1,    -1,    -1,
      -1,   242,   243,    -1,   160,   161,   247,    -1,    -1,   165,
     166,    -1,   229,   169,   170,   201,   202,   258,   241,   260,
      -1,    -1,   263,    -1,   210,   211,    -1,   213,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   252,   253,   254,    -1,    -1,
      -1,    19,    -1,   229,    -1,   201,   202,    -1,    -1,    -1,
     267,   268,   269,    -1,   210,   211,    -1,   213,    36,    37,
      38,    -1,    40,    41,    42,    -1,   252,   253,   254,    -1,
      -1,    -1,    -1,   229,    -1,    53,    54,    55,    56,    57,
      58,   267,   268,   269,    62,    63,    64,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,   252,   253,   254,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   267,   268,   269,    13,    -1,    15,    16,    17,    18,
      -1,    20,    21,    -1,    23,    24,    -1,    13,    27,    15,
      -1,    17,    18,    -1,    20,    21,    -1,    23,    24,    -1,
      -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    47,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    55,    -1,    -1,    -1,
      -1,    47,    48,    -1,    -1,    -1,    65,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,    13,    65,
      15,    -1,    17,    18,    -1,    20,    21,    73,    23,    24,
      -1,    13,    27,    15,    -1,    17,    18,    -1,    20,    21,
      -1,    23,    24,    -1,    -1,    27,    -1,    -1,    -1,    -1,
      -1,    -1,    47,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    47,    -1,    -1,    -1,    -1,
      65,    66,    -1,    55,    -1,    20,    -1,    -1,    73,    24,
      -1,    -1,    -1,    65,    29,    -1,    31,    -1,    33,    34,
      35,    73,    -1,    -1,    39,    40,    41,    -1,    43,    -1,
      45,    -1,    -1,    -1,    -1,    50,    51,    -1,    -1,    -1,
      55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    67,    68,    69,    70,    71,    72,    73,    20,
      -1,    -1,    -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,
      31,    -1,    33,    34,    35,    -1,    -1,    -1,    39,    40,
      41,    -1,    43,    -1,    45,    -1,    -1,    -1,    -1,    -1,
      51,    -1,    -1,    -1,    55,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    67,    68,    69,    70,
      71,    72,    73,    20,    -1,    -1,    -1,    24,    -1,    -1,
      -1,    -1,    -1,    -1,    31,    -1,    33,    34,    35,    -1,
      -1,    -1,    39,    40,    41,    -1,    43,    -1,    45,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    55,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      67,    68,    69,    70,    71,    72,    73,    20,    -1,    -1,
      -1,    24,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      33,    34,    35,    -1,    -1,    -1,    -1,    40,    41,    -1,
      43,    -1,    45,    25,    -1,    -1,    -1,    -1,    51,    -1,
      -1,    -1,    55,    -1,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    67,    68,    69,    70,    71,    72,
      73,    53,    54,    55,    56,    57,    58,    25,    -1,    -1,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    36,    37,
      38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    26,    -1,    -1,    62,    63,    64,    -1,    -1,    -1,
      -1,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    28,    -1,    -1,    62,    63,    64,
      -1,    -1,    36,    37,    38,    -1,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    30,    -1,    -1,    62,    63,
      64,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    32,    62,    63,    64,
      36,    37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    -1,    62,    63,    64,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,
      57,    58,    -1,    60,    -1,    62,    63,    64,    36,    37,
      38,    -1,    40,    41,    42,    -1,    44,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,
      58,    -1,    -1,    -1,    62,    63,    64,    36,    37,    38,
      -1,    40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    53,    54,    55,    56,    57,    58,
      59,    -1,    -1,    62,    63,    64,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    46,    -1,    -1,    -1,
      -1,    -1,    -1,    53,    54,    55,    56,    57,    58,    -1,
      -1,    -1,    62,    63,    64,    36,    37,    38,    -1,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    59,    -1,
      -1,    62,    63,    64,    36,    37,    38,    -1,    40,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    49,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    -1,    -1,    -1,
      62,    63,    64,    36,    37,    38,    -1,    40,    41,    42,
      -1,    -1,    -1,    -1,    -1,    48,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    62,
      63,    64,    36,    37,    38,    -1,    40,    41,    42,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,
      54,    55,    56,    57,    58,    -1,    -1,    -1,    62,    63,
      64,    36,    37,    38,    -1,    40,    41,    42,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,
      55,    56,    57,    58,    -1,    -1,    -1,    62,    63,    64,
      36,    -1,    38,    -1,    40,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    53,    54,    55,
      56,    57,    58,    -1,    -1,    36,    62,    63,    64,    40,
      41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    53,    54,    55,    56,    57,    58,    40,    41,
      42,    62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    53,    54,    55,    56,    57,    58,    40,    41,    -1,
      62,    63,    64,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      53,    54,    55,    56,    57,    58,    -1,    -1,    -1,    -1,
      63,    64
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    78,     4,     6,     7,     8,    10,    79,    80,
      81,    87,    91,    92,   127,     0,    47,    73,    93,    93,
      93,    93,    43,    86,    79,    20,    24,    31,    33,    34,
      35,    39,    40,    41,    43,    45,    51,    55,    67,    68,
      69,    70,    71,    72,    88,    89,    90,    93,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   120,   122,   123,   124,   125,   126,    43,    98,    42,
      98,    93,    94,    95,    93,    93,    96,    43,   116,    96,
     116,   117,   117,   116,   118,   119,   116,   119,    73,   117,
      52,    48,    43,   120,   121,    36,    37,    38,    40,    41,
      42,    53,    54,    55,    56,    57,    58,    60,    62,    63,
      64,    60,    96,    97,    60,    47,    42,    60,    52,    44,
      49,    49,    19,   116,    25,    19,    44,    52,    44,    59,
      46,   120,    88,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,    44,    52,    93,    99,   100,   101,   102,   103,    94,
      13,    15,    17,    18,    20,    21,    23,    24,    27,    47,
      65,   122,   123,   128,   130,   131,   132,   135,   136,   137,
     138,   139,   140,   141,    99,    93,    84,    85,    99,    99,
     116,   116,   116,   116,   116,    96,    43,    53,    42,    48,
     128,   129,   129,    96,    96,   128,   122,   123,   116,   116,
     129,   129,    61,    42,    55,    60,    30,    26,    32,    46,
      99,   104,   116,   116,    14,   128,    16,    42,    19,    25,
      28,    48,    66,   116,   128,    99,    99,   116,   116,   116,
      44,    52,    54,    59,   116,   116,   128,    47,    12,    83,
      99,   116,    19,    22,    26,    29,    50,   116,   133,   134,
      47,    11,    82,    54,   128,   128,   128,    49,    49,    49,
     134,    48,   116,    47,   128,   128,   128,    48,    90,    48
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    77,    78,    79,    79,    79,    79,    80,    80,    81,
      81,    82,    82,    83,    83,    84,    84,    85,    85,    86,
      86,    87,    87,    88,    88,    88,    89,    89,    90,    90,
      91,    92,    93,    94,    94,    95,    95,    96,    96,    97,
      97,    98,    98,    99,    99,    99,    99,   100,   101,   102,
     103,   104,   104,   105,   105,   105,   105,   105,   105,   105,
     105,   106,   107,   107,   108,   109,   109,   110,   111,   112,
     113,   114,   115,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   118,   118,   119,   119,   120,   121,   121,   122,   123,
     124,   125,   126,   127,   127,   128,   128,   128,   128,   128,
     128,   128,   128,   128,   128,   129,   129,   130,   131,   131,
     132,   133,   133,   133,   134,   134,   135,   136,   137,   138,
     138,   139,   139,   140,   141,   141,   141,   141
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
       3,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     1,     0,     3,     1,     0,     2,     3,
       6,     6,     6,     5,     7,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     2,     1,     1,     4,     6,
       6,     3,     3,     3,     2,     1,     6,     6,     2,     3,
       3,     3,     3,     3,     2,     1,     2,     1
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
  "\"xor\"", "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"", "\")\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\":\"", "\"_\"", "\"@\"", "\",\"",
  "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"", "\"^\"", "\"..\"", "\"->\"",
  "\":=\"", "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"binary\"",
  "\"hexadecimal\"", "\"integer\"", "\"rational\"", "\"floating\"",
  "\"string\"", "\"identifier\"", "UPLUS", "UMINUS", "UASTERIX", "$accept",
  "Specification", "Definition", "Definitions", "FunctionDefinition",
  "MaybeInitially", "MaybeDefined", "FunctionParameters",
  "MaybeFunctionParameters", "MaybeFunctionAttributes",
  "ProgramFunctionDefinition", "Initializer", "Initializers",
  "MaybeInitializers", "DerivedDefinition", "EnumerationDefinition",
  "Identifier", "Identifiers", "MaybeIdentifiers", "Variable",
  "Parameters", "MaybeParameters", "Type", "BasicType", "ComposedType",
  "FixedSizedType", "RangedType", "Types", "Atom", "Undefined", "Boolean",
  "String", "BitNumber", "IntegerNumber", "FloatingNumber",
  "RationalNumber", "RuleReference", "Range", "List", "Expression", "Term",
  "Expressions", "MaybeExpressions", "Arguments", "MaybeArguments",
  "DirectCallExpression", "IndirectCallExpression",
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
       0,   359,   359,   376,   380,   384,   388,   396,   402,   412,
     431,   439,   443,   451,   455,   463,   469,   479,   483,   491,
     495,   503,   520,   537,   546,   557,   569,   575,   585,   589,
     597,   605,   613,   621,   627,   637,   641,   649,   653,   661,
     667,   677,   681,   689,   693,   697,   701,   709,   717,   725,
     733,   741,   747,   757,   761,   765,   769,   773,   777,   781,
     785,   793,   801,   806,   815,   824,   829,   838,   847,   856,
     865,   873,   881,   889,   893,   897,   901,   905,   909,   913,
     917,   921,   925,   929,   933,   937,   941,   945,   949,   953,
     961,   965,   969,   975,   979,   983,   987,   991,   995,   999,
    1003,  1011,  1017,  1027,  1031,  1039,  1047,  1051,  1059,  1067,
    1075,  1083,  1091,  1099,  1104,  1113,  1117,  1121,  1125,  1129,
    1133,  1137,  1141,  1145,  1149,  1157,  1163,  1173,  1181,  1185,
    1193,  1201,  1206,  1211,  1219,  1224,  1232,  1240,  1248,  1256,
    1260,  1268,  1272,  1280,  1288,  1292,  1296,  1300
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
#line 3291 "GrammarParser.cpp" // lalr1.cc:1167
#line 1306 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
