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

    yy::Parser::symbol_type yylex( libcasm_fe::Driver& driver );
        
    void parse_function_attributes
    ( Driver& driver
    , const yy::location& loc
    , const std::vector<std::string>& attribute_names
    , Function* function
    )
    {
        bool is_static = false;
        bool is_symbolic = false;
        bool is_controlled = false;
        
        for( const auto& attribute_name : attribute_names )
        {
            if( attribute_name == "static" )
            {
                if( is_static )
                {
                    driver.error
                    ( loc
                    , "`static` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfStatic
                    );
                    break;
                }
                else
                {
                    is_static = true;
                }
            }
            else if( attribute_name == "symbolic" )
            {
                if( is_symbolic )
                {
                    driver.error
                    ( loc
                    , "`symbolic` attribute can only be used once per function"
                    , libcasm_fe::Codes::FunctionAttributeMultipleUseOfSymbolic
                    );
                    break;
                }
                else
                {
                    is_symbolic = true;
                }
            }
            else if( attribute_name == "controlled" )
            {
                if( is_controlled )
                {
                    driver.error
                    ( loc
                    , "`controlled` attribute can only be used once per function"
                      , libcasm_fe::Codes::FunctionAttributeMultipleUseOfControlled
                    );
                    break;
                }
                else
                {
                    is_controlled = true;
                }
            }
            else
            {
                driver.error
                ( loc
                , "`"+attribute_name+"` is no valid function attribute, only static, symbolic and controlled are allowed"
                , libcasm_fe::Codes::FunctionAttributeIsInvalid
                );
            }
        }
        if( is_static && is_controlled )
        {
            driver.error
            ( loc
            , "attributes `controlled` and `static` are mutually exclusive"
            , libcasm_fe::Codes::FunctionAttributeControlledAndStaticIsInvalid
            );
        }
        
        function->is_static = is_static;
        function->is_symbolic = is_symbolic;
    }

    static Function* createProgramFunction( yy::location& location )
    {
        auto argTypes = { new Type( TypeType::AGENT ) };
        auto retType = new Type( TypeType::RULEREF );
        return new Function( "program", location, argTypes, retType );
    }

#line 147 "GrammarParser.cpp" // lalr1.cc:413


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
#line 233 "GrammarParser.cpp" // lalr1.cc:479

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
  Parser::Parser (Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
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
      case 84: // SPECIFICATION
        value.move< Ast* > (that.value);
        break;

      case 86: // BODY_ELEMENTS
      case 141: // STATEMENTS
        value.move< AstListNode* > (that.value);
        break;

      case 87: // BODY_ELEMENT
      case 120: // SCOPE
      case 121: // RULE_STMT
      case 122: // RULE_SYNTAX
      case 125: // SIMPLE_STMT
      case 126: // STATEMENT
      case 130: // IMPOSSIBLE_SYNTAX
        value.move< AstNode* > (that.value);
        break;

      case 106: // VALUE
      case 107: // UNDEFINED
      case 108: // BOOLEAN
      case 109: // NUMBER
      case 114: // NUMBER_RANGE
      case 137: // CASE_VALUE
        value.move< AtomNode* > (that.value);
        break;

      case 119: // FUNCTION_SYNTAX
        value.move< BaseFunctionAtom* > (that.value);
        break;

      case 138: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 134: // CASE_SYNTAX
        value.move< CaseNode* > (that.value);
        break;

      case 129: // DIEDIE_SYNTAX
        value.move< DiedieNode* > (that.value);
        break;

      case 90: // ENUM_SYNTAX
        value.move< Enum* > (that.value);
        break;

      case 105: // ATOM
      case 118: // EXPRESSION
        value.move< ExpressionBase* > (that.value);
        break;

      case 76: // "floating"
        value.move< FLOATING_T > (that.value);
        break;

      case 111: // FLOATING_NUMBER
        value.move< FloatingAtom* > (that.value);
        break;

      case 148: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 91: // DERIVED_SYNTAX
      case 92: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 77: // "integer"
        value.move< INTEGER_T > (that.value);
        break;

      case 142: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 88: // INIT_SYNTAX
        value.move< InitNode* > (that.value);
        break;

      case 110: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 143: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 147: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 131: // PRINT_SYNTAX
      case 132: // DEBUG_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 146: // PUSH_SYNTAX
        value.move< PushNode* > (that.value);
        break;

      case 112: // RATIONAL_NUMBER
        value.move< RationalAtom* > (that.value);
        break;

      case 85: // HEADER
        value.move< SpecificationNode* > (that.value);
        break;

      case 96: // PARAM
      case 100: // TYPE_SYNTAX
        value.move< Type* > (that.value);
        break;

      case 127: // ASSERT_SYNTAX
      case 128: // ASSURE_SYNTAX
      case 139: // SEQ_SYNTAX
      case 140: // PAR_SYNTAX
      case 149: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 104: // INITIALIZER
      case 133: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 78: // "rational"
        value.move< rational_t > (that.value);
        break;

      case 136: // CASE_LABEL
        value.move< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 124: // DUMPSPEC
        value.move< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 95: // FUNCTION_SIGNATURE
        value.move< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 79: // "string"
      case 80: // "identifier"
      case 113: // RULEREF
        value.move< std::string > (that.value);
        break;

      case 115: // LISTCONST
      case 116: // EXPRESSION_LIST
      case 117: // EXPRESSION_LIST_NO_COMMA
        value.move< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 97: // PARAM_LIST
      case 98: // PARAM_LIST_NO_COMMA
      case 99: // TYPE_IDENTIFIER_STARLIST
      case 101: // TYPE_SYNTAX_LIST
        value.move< std::vector<Type*> > (that.value);
        break;

      case 102: // INITIALIZER_LIST
      case 103: // INITIALIZER_LIST_NO_COMMA
        value.move< std::vector<UpdateNode*> > (that.value);
        break;

      case 135: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 123: // DUMPSPEC_LIST
        value.move< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 93: // IDENTIFIER_LIST
      case 94: // IDENTIFIER_LIST_NO_COMMA
        value.move< std::vector<std::string> > (that.value);
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
      case 84: // SPECIFICATION
        value.copy< Ast* > (that.value);
        break;

      case 86: // BODY_ELEMENTS
      case 141: // STATEMENTS
        value.copy< AstListNode* > (that.value);
        break;

      case 87: // BODY_ELEMENT
      case 120: // SCOPE
      case 121: // RULE_STMT
      case 122: // RULE_SYNTAX
      case 125: // SIMPLE_STMT
      case 126: // STATEMENT
      case 130: // IMPOSSIBLE_SYNTAX
        value.copy< AstNode* > (that.value);
        break;

      case 106: // VALUE
      case 107: // UNDEFINED
      case 108: // BOOLEAN
      case 109: // NUMBER
      case 114: // NUMBER_RANGE
      case 137: // CASE_VALUE
        value.copy< AtomNode* > (that.value);
        break;

      case 119: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (that.value);
        break;

      case 138: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 134: // CASE_SYNTAX
        value.copy< CaseNode* > (that.value);
        break;

      case 129: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (that.value);
        break;

      case 90: // ENUM_SYNTAX
        value.copy< Enum* > (that.value);
        break;

      case 105: // ATOM
      case 118: // EXPRESSION
        value.copy< ExpressionBase* > (that.value);
        break;

      case 76: // "floating"
        value.copy< FLOATING_T > (that.value);
        break;

      case 111: // FLOATING_NUMBER
        value.copy< FloatingAtom* > (that.value);
        break;

      case 148: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 91: // DERIVED_SYNTAX
      case 92: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 77: // "integer"
        value.copy< INTEGER_T > (that.value);
        break;

      case 142: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 88: // INIT_SYNTAX
        value.copy< InitNode* > (that.value);
        break;

      case 110: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 143: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 147: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 131: // PRINT_SYNTAX
      case 132: // DEBUG_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 146: // PUSH_SYNTAX
        value.copy< PushNode* > (that.value);
        break;

      case 112: // RATIONAL_NUMBER
        value.copy< RationalAtom* > (that.value);
        break;

      case 85: // HEADER
        value.copy< SpecificationNode* > (that.value);
        break;

      case 96: // PARAM
      case 100: // TYPE_SYNTAX
        value.copy< Type* > (that.value);
        break;

      case 127: // ASSERT_SYNTAX
      case 128: // ASSURE_SYNTAX
      case 139: // SEQ_SYNTAX
      case 140: // PAR_SYNTAX
      case 149: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 104: // INITIALIZER
      case 133: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 78: // "rational"
        value.copy< rational_t > (that.value);
        break;

      case 136: // CASE_LABEL
        value.copy< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 124: // DUMPSPEC
        value.copy< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 95: // FUNCTION_SIGNATURE
        value.copy< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 79: // "string"
      case 80: // "identifier"
      case 113: // RULEREF
        value.copy< std::string > (that.value);
        break;

      case 115: // LISTCONST
      case 116: // EXPRESSION_LIST
      case 117: // EXPRESSION_LIST_NO_COMMA
        value.copy< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 97: // PARAM_LIST
      case 98: // PARAM_LIST_NO_COMMA
      case 99: // TYPE_IDENTIFIER_STARLIST
      case 101: // TYPE_SYNTAX_LIST
        value.copy< std::vector<Type*> > (that.value);
        break;

      case 102: // INITIALIZER_LIST
      case 103: // INITIALIZER_LIST_NO_COMMA
        value.copy< std::vector<UpdateNode*> > (that.value);
        break;

      case 135: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 123: // DUMPSPEC_LIST
        value.copy< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 93: // IDENTIFIER_LIST
      case 94: // IDENTIFIER_LIST_NO_COMMA
        value.copy< std::vector<std::string> > (that.value);
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
    #line 55 "../../obj/src/GrammarParser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
}

#line 873 "GrammarParser.cpp" // lalr1.cc:741

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
            symbol_type yylookahead (yylex (driver));
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
      case 84: // SPECIFICATION
        yylhs.value.build< Ast* > ();
        break;

      case 86: // BODY_ELEMENTS
      case 141: // STATEMENTS
        yylhs.value.build< AstListNode* > ();
        break;

      case 87: // BODY_ELEMENT
      case 120: // SCOPE
      case 121: // RULE_STMT
      case 122: // RULE_SYNTAX
      case 125: // SIMPLE_STMT
      case 126: // STATEMENT
      case 130: // IMPOSSIBLE_SYNTAX
        yylhs.value.build< AstNode* > ();
        break;

      case 106: // VALUE
      case 107: // UNDEFINED
      case 108: // BOOLEAN
      case 109: // NUMBER
      case 114: // NUMBER_RANGE
      case 137: // CASE_VALUE
        yylhs.value.build< AtomNode* > ();
        break;

      case 119: // FUNCTION_SYNTAX
        yylhs.value.build< BaseFunctionAtom* > ();
        break;

      case 138: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 134: // CASE_SYNTAX
        yylhs.value.build< CaseNode* > ();
        break;

      case 129: // DIEDIE_SYNTAX
        yylhs.value.build< DiedieNode* > ();
        break;

      case 90: // ENUM_SYNTAX
        yylhs.value.build< Enum* > ();
        break;

      case 105: // ATOM
      case 118: // EXPRESSION
        yylhs.value.build< ExpressionBase* > ();
        break;

      case 76: // "floating"
        yylhs.value.build< FLOATING_T > ();
        break;

      case 111: // FLOATING_NUMBER
        yylhs.value.build< FloatingAtom* > ();
        break;

      case 148: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 91: // DERIVED_SYNTAX
      case 92: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 77: // "integer"
        yylhs.value.build< INTEGER_T > ();
        break;

      case 142: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 88: // INIT_SYNTAX
        yylhs.value.build< InitNode* > ();
        break;

      case 110: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 143: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 147: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 131: // PRINT_SYNTAX
      case 132: // DEBUG_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 146: // PUSH_SYNTAX
        yylhs.value.build< PushNode* > ();
        break;

      case 112: // RATIONAL_NUMBER
        yylhs.value.build< RationalAtom* > ();
        break;

      case 85: // HEADER
        yylhs.value.build< SpecificationNode* > ();
        break;

      case 96: // PARAM
      case 100: // TYPE_SYNTAX
        yylhs.value.build< Type* > ();
        break;

      case 127: // ASSERT_SYNTAX
      case 128: // ASSURE_SYNTAX
      case 139: // SEQ_SYNTAX
      case 140: // PAR_SYNTAX
      case 149: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 104: // INITIALIZER
      case 133: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 78: // "rational"
        yylhs.value.build< rational_t > ();
        break;

      case 136: // CASE_LABEL
        yylhs.value.build< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 124: // DUMPSPEC
        yylhs.value.build< std::pair<std::string, std::vector<std::string>> > ();
        break;

      case 95: // FUNCTION_SIGNATURE
        yylhs.value.build< std::pair<std::vector<Type*>, Type*> > ();
        break;

      case 79: // "string"
      case 80: // "identifier"
      case 113: // RULEREF
        yylhs.value.build< std::string > ();
        break;

      case 115: // LISTCONST
      case 116: // EXPRESSION_LIST
      case 117: // EXPRESSION_LIST_NO_COMMA
        yylhs.value.build< std::vector<ExpressionBase*>* > ();
        break;

      case 97: // PARAM_LIST
      case 98: // PARAM_LIST_NO_COMMA
      case 99: // TYPE_IDENTIFIER_STARLIST
      case 101: // TYPE_SYNTAX_LIST
        yylhs.value.build< std::vector<Type*> > ();
        break;

      case 102: // INITIALIZER_LIST
      case 103: // INITIALIZER_LIST_NO_COMMA
        yylhs.value.build< std::vector<UpdateNode*> > ();
        break;

      case 135: // CASE_LABEL_LIST
        yylhs.value.build< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 123: // DUMPSPEC_LIST
        yylhs.value.build< std::vector<std::pair<std::string, std::vector<std::string>>> > ();
        break;

      case 93: // IDENTIFIER_LIST
      case 94: // IDENTIFIER_LIST_NO_COMMA
        yylhs.value.build< std::vector<std::string> > ();
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
#line 350 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
  }
#line 1167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& filepath = driver.get_filename();
      
      const std::string& filename
          = filepath.substr( filepath.find_last_of( "/\\" ) + 1 );
      
      const std::string& filename_without_extension
          = filename.substr( 0, filename.rfind( "." ) );
      
      yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, filename_without_extension );
  }
#line 1183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 1192 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
      yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
  }
#line 1201 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 387 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( NodeType::OPTION );
  }
#line 1209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new EnumDefNode( yylhs.location, yystack_[0].value.as< Enum* > () );
  }
#line 1217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 395 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new FunctionDefNode( yylhs.location, yystack_[0].value.as< Function* > () );

      try
      {
          driver.add( yystack_[0].value.as< Function* > () );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );

          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[0].value.as< Function* > ();
      }
  }
#line 1242 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto node = new FunctionDefNode( yylhs.location, yystack_[4].value.as< Function* > () );

      auto initializers = yystack_[1].value.as< std::vector<UpdateNode*> > ();
      for (auto initializer : initializers) {
          initializer->func->name = yystack_[4].value.as< Function* > ()->name;
      }
      node->setInitializers( initializers );

      try
      {
          driver.add( yystack_[4].value.as< Function* > () );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );

          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[4].value.as< Function* > ();
      }

      yylhs.value.as< AstNode* > () = node;
  }
#line 1275 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 445 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto node = new FunctionDefNode( yylhs.location, yystack_[4].value.as< Function* > () );
      node->setDefaultValue( yystack_[1].value.as< AtomNode* > () );

      try
      {
          driver.add( yystack_[4].value.as< Function* > () );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );

          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[4].value.as< Function* > ();
      }

      yylhs.value.as< AstNode* > () = node;
  }
#line 1303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 469 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto node = new FunctionDefNode( yylhs.location, yystack_[8].value.as< Function* > () );
      node->setDefaultValue( yystack_[5].value.as< AtomNode* > () );

      auto initializers = yystack_[1].value.as< std::vector<UpdateNode*> > ();
      for (auto initializer : initializers) {
          initializer->func->name = yystack_[8].value.as< Function* > ()->name;
      }
      node->setInitializers( initializers );

      try
      {
          driver.add( yystack_[8].value.as< Function* > () );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );

          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[8].value.as< Function* > ();
      }

      yylhs.value.as< AstNode* > () = node;
  }
#line 1337 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< Function* > ()->binding_offsets = std::move( driver.binding_offsets );
      driver.binding_offsets.clear();
      
      yylhs.value.as< AstNode* > () = new DerivedDefNode( yylhs.location, yystack_[0].value.as< Function* > () );
      try
      {
          driver.add( yystack_[0].value.as< Function* > () );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );

          // if another symbol with same name exists we need to delete
          // the symbol here, because it is not inserted in the symbol table
          delete yystack_[0].value.as< Function* > ();
      }
  }
#line 1364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 522 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > ();
  }
#line 1372 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 526 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
      // TODO: check, we trust bison to pass only RuleNodes up
      
      try
      {
          driver.add( reinterpret_cast< RuleNode* >( yystack_[0].value.as< AstNode* > () ) );
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
          
          // we do not need to delete $1 here, because it's already in
          // the AST, so it will be deleted later
      }
  }
#line 1397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 551 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
    auto program = createProgramFunction( yylhs.location );
    try
    {
        driver.add( program );
    }
    catch( const Exception& e )
    {
        driver.error
        ( yylhs.location
        , "multiple definition of 'init' node"
        , libcasm_fe::Codes::AgentInitRuleMultipleDefinitions
        );
    }

    // create initial update: program(self) := @identifier
    auto args = new std::vector< ExpressionBase* >;
    args->push_back( new SelfAtom( yylhs.location ) );
    auto programAtom = new FunctionAtom( yylhs.location, program->name, args );
    auto update = new UpdateNode( yylhs.location, programAtom, new RuleAtom( yylhs.location , yystack_[0].value.as< std::string > () ) );

    auto programDef = new FunctionDefNode( yylhs.location, program );
    programDef->setInitializers( { update } );
    yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, programDef );
  }
#line 1427 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
    auto program = createProgramFunction( yylhs.location );
    try
    {
        driver.add( program );
    }
    catch( const Exception& e )
    {
        driver.error
        ( yylhs.location
        , "multiple definition of 'init' node"
        , libcasm_fe::Codes::AgentInitRuleMultipleDefinitions
        );
    }

    // initializer updates don't have function names -> apply the correct name
    auto initializers = yystack_[1].value.as< std::vector<UpdateNode*> > ();
    for (auto initializer : initializers) {
        initializer->func->name = program->name;
    }

    auto programDef = new FunctionDefNode( yylhs.location, program );
    programDef->setInitializers( initializers );
    yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, programDef );
  }
#line 1457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Enum* > () = new Enum(yystack_[4].value.as< std::string > (), yylhs.location);
      try
      {
          driver.function_table.add(yylhs.value.as< Enum* > ());
      }
      catch( const Exception& e )
      {
          driver.error
          ( e.getLocations()
          , e.what()
          , e.getErrorCode()
          );
      }
      for( const std::string& name : yystack_[1].value.as< std::vector<std::string> > () )
      {
          if( yylhs.value.as< Enum* > ()->add_enum_element(name) )
          {
              try
              {
                  driver.function_table.add_enum_element( name, yylhs.value.as< Enum* > () );
              }
              catch( const Exception& e )
              {
                  driver.error
                  ( e.getLocations()
                  , e.what()
                  , e.getErrorCode()
                  );
              }
          }
          else
          {
              driver.error
              ( yylhs.location
              , "name '"
                + name
                + "' already used in enum"
              );
          }
      }
  }
#line 1504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 659 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: 2nd argument should be a reference
      yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 668 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 672 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 676 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 680 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 688 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second);
      parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > (), function);
      yylhs.value.as< Function* > () = function;
  }
#line 1563 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 694 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second);
  }
#line 1571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 701 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
  }
#line 1579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 705 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ());
  }
#line 1587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 713 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move( yystack_[2].value.as< std::vector<std::string> > () );
      yylhs.value.as< std::vector<std::string> > ().push_back( yystack_[0].value.as< std::string > () );
  }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 718 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
      yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
  }
#line 1605 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      /* this constructor is implementation dependant! */
      std::vector<Type*> foo;
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
  }
#line 1615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 733 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ());
  }
#line 1623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 741 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
  }
#line 1633 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 747 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
      // TODO: fail for rules without types and print warnings
      yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 758 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 762 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ());
  }
#line 1660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1669 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 775 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1677 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 783 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1686 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: limit memory size
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
  }
#line 1695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 793 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1703 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[0].value.as< std::string > () );
      
      // TODO: FUTURE: integrate the IR-based type-list here to perform checks!,
      //               or maybe we should check everything in the typecheckpass?
      if( yystack_[0].value.as< std::string > ().compare( "Bit" ) == 0 )
      {
          driver.error
          ( yylhs.location
          , "missing bit-size for Bit type 'Bit(<bitsize>)'"
          , libcasm_fe::Codes::TypeBitSyntaxError
          );
      }
      else if( yystack_[0].value.as< std::string > ().compare( "List" ) == 0 )
      {
          driver.error
          ( yylhs.location
          , "unsupported type '" + yystack_[0].value.as< std::string > () + "'"
          , libcasm_fe::Codes::TypeUnsupported
          );
      }      
  }
#line 1730 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 824 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[3].value.as< std::string > () );
      yylhs.value.as< Type* > ()->bitsize = yystack_[1].value.as< IntegerAtom* > ()->val_;
      if( yylhs.value.as< Type* > ()->bitsize <= 0 || yylhs.value.as< Type* > ()->bitsize > 256 )
      {
          driver.error
          ( yylhs.location
          , "invalid bit-size for Bit type, must between 1 <= x <= 256"
          , libcasm_fe::Codes::TypeBitSizeIsInvalid
          );
      }
  }
#line 1747 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 837 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<Type*> > () );

      if( yystack_[3].value.as< std::string > ().compare( "List" ) == 0 )
      {
          driver.error
          ( yylhs.location
          , "unsupported type '" + yystack_[3].value.as< std::string > () + "'"
          , libcasm_fe::Codes::TypeUnsupported
          );
      }
      // TODO: FUTURE: PPA: better and generic type checking in the type check pass
      else if( yystack_[3].value.as< std::string > ().compare( "Tuple" ) != 0 )
      {
          driver.error
          ( yylhs.location
          , "unknown type '" + yystack_[3].value.as< std::string > () + "'"
          , libcasm_fe::Codes::TypeUnknown
          );
      }      
  }
#line 1773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 859 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Type* > () = new Type( yystack_[5].value.as< std::string > () );
      yylhs.value.as< Type* > ()->subrange_start = yystack_[3].value.as< IntegerAtom* > ()->val_;
      yylhs.value.as< Type* > ()->subrange_end = yystack_[1].value.as< IntegerAtom* > ()->val_;
      if( yylhs.value.as< Type* > ()->subrange_start >= yylhs.value.as< Type* > ()->subrange_end )
      {
          driver.error
          ( yylhs.location
          , "start of subrange must be smaller than the end"
          , libcasm_fe::Codes::TypeIntegerRangedInvalidInterval
          );
      }
  }
#line 1791 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 877 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().push_back( yystack_[2].value.as< Type* > () );
      yylhs.value.as< std::vector<Type*> > () = std::move( yystack_[0].value.as< std::vector<Type*> > () );
  }
#line 1800 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 882 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[1].value.as< Type* > () );
  }
#line 1808 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 886 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[0].value.as< Type* > () );
  }
#line 1816 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 894 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = std::move(yystack_[0].value.as< std::vector<UpdateNode*> > ());
  }
#line 1824 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = std::move(yystack_[1].value.as< std::vector<UpdateNode*> > ());
  }
#line 1832 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = std::move(yystack_[2].value.as< std::vector<UpdateNode*> > ());
      yylhs.value.as< std::vector<UpdateNode*> > ().push_back(yystack_[0].value.as< UpdateNode* > ());
  }
#line 1841 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 911 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = { yystack_[0].value.as< UpdateNode* > () };
  }
#line 1849 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new FunctionAtom( yylhs.location, "" );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1858 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto args = new std::vector< ExpressionBase* >;
      args->push_back(yystack_[2].value.as< ExpressionBase* > ());

      auto function = new FunctionAtom( yylhs.location, "", args );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1870 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 932 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new FunctionAtom( yylhs.location, "", yystack_[3].value.as< std::vector<ExpressionBase*>* > () );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1879 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 941 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1887 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1895 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1903 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1911 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 957 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, new ZeroAtom( yylhs.location, yystack_[1].value.as< ExpressionBase* > () ), yystack_[1].value.as< ExpressionBase* > (),
                                 libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1920 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1928 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1936 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1944 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1952 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1960 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1968 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); 
  }
#line 1976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 2000 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 2008 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 2016 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 2024 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 1030 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 2032 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 1038 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 2040 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 1042 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 2048 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 1046 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
      yystack_[0].value.as< IntegerAtom* > ()->val_ *= (-1);
  }
#line 2057 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 1055 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 2065 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 1059 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 2073 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 1063 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
      yystack_[0].value.as< FloatingAtom* > ()->val_ *= (-1);
  }
#line 2082 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 1072 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 2090 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 1076 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 2098 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 1080 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< rational_t > ().numerator *= -1;
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 2107 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 1089 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 2115 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 1097 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new NumberRangeAtom( yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2123 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 1105 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2131 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 1109 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 2139 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 1117 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2147 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 1121 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2155 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 1129 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2164 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2173 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2181 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1147 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2189 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1151 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2197 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2205 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1159 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2213 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1163 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2221 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1167 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2229 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1171 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2237 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1175 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2245 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1179 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2253 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1183 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2261 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2269 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1191 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2277 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1195 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1199 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new UnaryExpression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1203 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2301 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1211 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2309 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2317 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1219 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( Builtin::isBuiltin( yystack_[3].value.as< std::string > () ) )
      {
          yylhs.value.as< BaseFunctionAtom* > () = new BuiltinAtom( yylhs.location, yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
      }
      else
      {
          yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
      }
  }
#line 2332 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1234 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2340 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2348 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1246 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2356 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1250 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      stmts->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2366 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1260 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1264 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1268 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2390 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1272 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1277 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1282 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2417 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1291 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2426 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1296 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2435 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1305 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2443 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1313 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1317 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1321 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2467 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1325 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1329 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2483 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1333 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2491 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1337 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1341 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1345 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1353 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1357 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1361 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1365 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1369 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2563 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1377 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.error
      ( yylhs.location
      , "invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
      , libcasm_fe::Codes::SyntaxErrorInvalidStatement
      );
  }
#line 2583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2591 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1401 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2599 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1409 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2615 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1425 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1429 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1445 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1453 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[1].value.as< std::string > () );
  }
#line 2655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1469 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::FUNCTION_ATOM )
      {
          yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, reinterpret_cast< FunctionAtom* >( yystack_[2].value.as< BaseFunctionAtom* > () ), yystack_[0].value.as< ExpressionBase* > () );
      }
      else
      {
          driver.error
          ( yylhs.location
          , "can only use functions for updates but '"
            + yystack_[2].value.as< BaseFunctionAtom* > ()->to_str()
            + "` is a '"
            + type_to_str( yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ )
          );
      }
  }
#line 2676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1490 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1498 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[0].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[1].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2693 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1503 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::vector< std::pair< AtomNode*, AstNode* > >();
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2702 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1512 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2710 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1520 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2718 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1524 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // equivalent to 'default' 
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2727 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1529 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2735 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1533 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2743 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1537 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2751 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 2759 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1545 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 2767 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2775 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1557 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2783 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1561 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2791 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1565 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2799 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2807 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2815 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1585 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2823 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2831 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1597 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2840 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2849 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1611 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto var = Symbol( yystack_[1].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET );
      try
      {
          driver.function_table.add( &var );      
      }
      catch( const Exception& e)
      {
          driver.error( yylhs.location, e.what() );
      }
  }
#line 2881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1636 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[5].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2890 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1641 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto var = Symbol( yystack_[3].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET );
      try
      {
          driver.function_table.add( &var );
      }
      catch( const Exception& e)
      {
          driver.error( yylhs.location, e.what() );
      }
  }
#line 2906 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1653 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[7].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2915 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1662 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( yylhs.location, "cannot push to builtin '" + yystack_[0].value.as< BaseFunctionAtom* > ()->to_str() + "'" );
      }
      else
      {
          yylhs.value.as< PushNode* > () = new PushNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), reinterpret_cast< FunctionAtom* >( yystack_[0].value.as< BaseFunctionAtom* > () ) );
      }
  }
#line 2930 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      if( yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( yylhs.location, "cannot pop to builtin '" + yystack_[2].value.as< BaseFunctionAtom* > ()->to_str() + "'" );
      }
      else if( yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM )
      {
          driver.error( yylhs.location, "cannot pop from builtin '" + yystack_[0].value.as< BaseFunctionAtom* > ()->to_str() + "'" );
      }
      else
      {
          yylhs.value.as< PopNode* > () = new PopNode
          ( yylhs.location
          , reinterpret_cast< FunctionAtom* >( yystack_[2].value.as< BaseFunctionAtom* > () )
          , reinterpret_cast< FunctionAtom* >( yystack_[0].value.as< BaseFunctionAtom* > () )
          );
      }
  }
#line 2953 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1700 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2961 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 1710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2969 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2973 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -247;

  const signed char Parser::yytable_ninf_ = -109;

  const short int
  Parser::yypact_[] =
  {
      27,  -247,    33,   253,  -247,   -37,   -43,    59,    68,    73,
     -36,   253,  -247,  -247,  -247,  -247,  -247,    15,  -247,   247,
    -247,    37,    95,   107,     0,    79,   109,  -247,   115,   116,
    -247,  -247,  -247,  -247,   655,    53,    66,   655,   613,    97,
    -247,  -247,  -247,  -247,   126,   144,   141,  -247,   -28,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,   727,
    -247,   124,   655,    34,   127,   167,   181,   457,    43,  -247,
     182,   177,   -45,  -247,   247,   120,   655,  -247,  -247,   139,
     164,   655,  -247,  -247,  -247,   -27,   -27,   655,  -247,  -247,
    -247,   194,   190,   756,  -247,   198,   767,  -247,   634,  -247,
     247,   655,   655,   655,   655,   655,   655,   655,   655,   655,
     655,   655,   676,   655,   655,   655,   176,   894,    50,   206,
    -247,   215,   207,   219,   224,    79,    79,   -26,  -247,   457,
     457,   655,   655,   655,  -247,  -247,   197,   205,   457,    41,
     655,   655,   655,   212,   655,   218,   457,   457,   -38,   208,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,  -247,
      11,   234,   223,   226,   127,   235,   242,   256,   257,   756,
     796,   825,   246,   655,  -247,  -247,   655,  -247,   264,   894,
    -247,   922,   569,   933,   100,   244,   437,   217,   329,  -247,
     255,    61,  -247,   952,   469,   717,  -247,   655,   127,   127,
     131,   238,   -32,   655,   265,   268,   457,   181,  -247,  -247,
    -247,   319,   346,   894,   894,   894,   185,   306,  -247,   655,
     278,   544,   580,   894,   655,   698,   305,   388,   415,   655,
     181,   457,    12,   109,  -247,  -247,   127,   127,  -247,   337,
    -247,  -247,   676,   894,   854,  -247,   894,   300,  -247,   655,
     127,  -247,    36,    36,   290,   304,   -22,   894,  -247,   284,
    -247,  -247,  -247,  -247,  -247,  -247,   127,   655,   883,   655,
     457,   313,   894,   218,   218,  -247,  -247,   894,    49,  -247,
     181,   457,  -247,  -247,  -247,   316,  -247,  -247,   655,   894,
     309,   127,  -247,  -247,    36,   296,   655,   333,   533,   328,
     334,   356,   142,  -247,  -247,   457,    83,  -247,   247,   894,
     655,  -247,   335,  -247,   475,  -247,   457,   655,  -247,   457,
    -247,  -247,  -247,  -247,  -247,  -247,  -247,   332,   142,   331,
    -247,   457,   340,   894,  -247,   457,   655,  -247,   338,  -247,
    -247,  -247,   457,  -247,  -247,  -247,   504,  -247,  -247,   457,
    -247
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     3,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     2,     5,    13,     6,     7,    12,     8,    14,     0,
      15,     0,     0,     0,     0,     0,     0,     4,     0,     0,
      66,    69,    71,    70,     0,     0,     0,     0,     0,     0,
      78,    75,    81,    63,   108,     0,    49,    52,   107,    57,
      67,    68,    62,    72,    73,    74,    61,    65,    64,     0,
      56,     0,     0,     0,     0,     0,     0,     0,     0,    30,
       0,    28,     0,    26,     0,     0,     0,   107,   106,     0,
       0,     0,    76,    79,    82,     0,     0,     0,    83,    77,
      80,     0,    88,    91,    87,     0,    91,    84,     0,    16,
      50,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    20,     0,    34,
      38,     0,    35,    42,     0,     0,     0,     0,   122,     0,
       0,     0,     0,   146,   147,   139,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   140,     0,
     113,   115,   114,   124,   125,   126,   127,   129,   128,   130,
     131,   132,   111,   112,   133,   134,   135,   136,   137,   138,
       0,     0,     0,    27,     0,     0,    41,     0,     0,     0,
       0,     0,     0,    89,    58,    86,     0,   109,     0,    91,
      51,   105,   103,   104,    92,    93,    98,    99,   100,    94,
      95,    96,    54,    97,   101,   102,    17,     0,     0,     0,
       0,    36,     0,     0,     0,     0,     0,     0,   141,   142,
     171,     0,     0,   143,   144,   145,     0,     0,   181,     0,
     165,     0,     0,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    29,    31,     0,    40,     9,    10,
      59,    60,     0,    90,     0,   110,    21,     0,    33,     0,
       0,    37,     0,     0,    48,     0,     0,    23,    18,     0,
     118,   121,   167,   170,   169,   174,     0,     0,     0,     0,
       0,     0,   149,     0,     0,   168,   166,   150,     0,   116,
       0,     0,    25,    32,    39,     0,    55,    85,     0,    19,
       0,    47,    44,    43,     0,     0,     0,     0,     0,   163,
       0,   172,     0,   178,   179,     0,     0,   117,     0,    24,
       0,    46,     0,   123,     0,   176,     0,     0,   164,     0,
     155,   156,   160,   157,   158,   159,   161,     0,   153,     0,
     119,     0,     0,    22,    45,     0,     0,   180,     0,   173,
     151,   152,     0,   120,    11,   175,     0,   162,   154,     0,
     177
  };

  const short int
  Parser::yypgoto_[] =
  {
    -247,  -247,  -247,  -247,   387,  -247,  -247,  -247,  -247,  -247,
       7,  -247,   157,   193,   343,  -247,   170,   -52,   113,   -67,
    -247,   318,   -18,   347,  -246,  -234,  -221,   -25,     4,   -20,
    -247,  -247,  -247,   -33,  -247,   -34,   -10,   -65,  -203,  -247,
    -232,   204,   -61,   -97,  -247,  -247,  -247,  -247,  -247,  -247,
    -247,  -247,    91,  -247,  -247,  -247,  -247,  -247,    63,  -247,
    -247,  -247,  -247,  -247,  -247,  -247,  -247
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,    11,    12,    13,    14,    15,    16,    17,
      70,    71,    73,   120,   121,   122,   175,   176,   265,    45,
      46,    47,    77,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    91,    92,    59,    60,   218,   151,    18,
     127,   128,   219,   220,   153,   154,   155,   156,   157,   158,
     159,   160,   337,   338,   339,   161,   162,   163,   221,   164,
     165,   306,   346,   166,   167,   168,   169
  };

  const short int
  Parser::yytable_[] =
  {
      78,    48,   150,    93,    96,    95,   152,   177,   288,    66,
      82,    89,   124,   270,    98,    84,    25,   262,   263,    19,
     240,   290,    85,    86,   174,   216,    28,    29,   117,   -53,
       1,   303,  -108,     4,   -53,   123,   217,    21,   289,    83,
      90,   228,   179,    20,    26,    41,   304,   180,   123,    40,
      41,    67,    68,   181,    82,    89,    48,   149,   316,    84,
      82,    89,   241,   291,   189,   188,   333,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   334,   203,
     204,   205,    48,    83,    90,   262,   263,   118,   317,    83,
      90,   335,   333,   229,   202,    61,   170,   223,   224,   225,
     315,   207,    79,    80,   334,    81,   231,   232,   233,   208,
     235,   217,   340,    41,   119,    85,    86,   335,    87,   149,
     149,   230,   245,   119,   273,   273,   109,   110,   149,    40,
      41,    42,   214,   215,   341,   236,   149,   149,   353,    22,
     273,   273,    40,    41,    88,   217,    62,    63,    23,   253,
     105,   150,   254,    24,    64,   152,   257,   258,    65,    69,
     264,    30,    31,    32,    33,   109,   110,   111,    72,    79,
      80,    74,    75,   256,    38,   330,   150,    97,    98,   267,
     152,    39,   259,   311,    31,    32,    33,   266,    79,    80,
     260,    79,    80,   222,   293,   278,    40,    41,    42,    43,
     282,    99,   331,   100,   116,   287,   149,   123,   300,   237,
     238,   149,   149,    85,    86,    40,    41,    42,    40,    41,
      42,   332,    44,   125,   307,   299,   150,   149,   149,   347,
     152,   149,   349,   126,   296,   172,   275,    82,    89,   173,
      40,    41,    88,   308,   276,   189,   310,   182,   355,   264,
     150,   342,   183,   185,   152,   358,   206,     5,     6,     7,
       8,     9,   360,    10,   319,   209,   104,   105,   210,   211,
     149,   212,   324,   313,   314,   213,   150,   226,   239,   322,
     152,   149,   109,   110,   111,   227,   343,   242,    30,    31,
      32,    33,   234,   189,   348,    34,    35,    36,    44,    37,
      48,    38,   336,   243,   246,   149,   244,   247,    39,   109,
     110,   111,   356,   248,   249,   252,   149,   255,   119,   149,
     109,   269,   268,    40,    41,    42,    43,    44,   336,   277,
     279,   149,   129,   272,   130,   149,   131,   132,   133,   134,
     135,   136,   149,   137,   138,   284,   139,   140,   295,   149,
     141,   298,   301,   305,   142,   143,   144,   302,   145,   129,
     320,   130,   274,   131,   132,   133,   134,   135,   136,   312,
     137,   138,   318,   139,   140,   146,   323,   141,   104,   105,
     327,   142,   143,   144,   325,   145,   329,   328,   344,   350,
     352,   357,   107,   147,   109,   110,   111,   354,    27,   148,
     292,   129,   146,   130,   261,   131,   132,   133,   134,   135,
     136,   171,   137,   138,   321,   139,   140,   294,   190,   141,
     147,   271,   178,   142,   143,   144,   148,   145,   129,   351,
     130,     0,   131,   132,   133,   134,   135,   136,     0,   137,
     138,     0,   139,   140,   146,   285,   141,     0,     0,     0,
     142,   143,   144,     0,   145,     0,     0,     0,     0,     0,
       0,     0,   147,     0,     0,     0,     0,     0,   148,     0,
     129,   146,   130,     0,   131,   132,   133,   134,   135,   136,
       0,   137,   138,     0,   139,   140,   104,   105,   141,   147,
     286,     0,   142,   143,   144,   148,   145,     0,   345,     0,
     107,   108,   109,   110,   111,     0,     0,     0,   113,   114,
     115,     0,     0,   146,     0,     0,     0,     0,   104,   105,
     101,   102,   103,     0,   104,   105,   106,   359,     0,     0,
       0,   147,   107,   108,   109,   110,   111,   148,   107,   108,
     109,   110,   111,     0,     0,     0,   113,   114,   115,   101,
     102,   103,     0,   104,   105,   106,     0,     0,     0,   326,
       0,     0,     0,     0,     0,     0,     0,   107,   108,   109,
     110,   111,     0,   280,     0,   113,   114,   115,   101,   102,
     103,     0,   104,   105,   106,     0,     0,     0,     0,   101,
     102,   103,     0,   104,   105,   106,   107,   108,   109,   110,
     111,     0,     0,     0,   113,   114,   115,   107,   108,   109,
     110,   111,   281,     0,     0,   113,   114,   115,   104,   105,
     106,     0,     0,     0,     0,   101,   102,   103,     0,   104,
     105,   106,   107,   108,   109,   110,   111,     0,     0,     0,
     113,   114,   115,   107,   108,   109,   110,   111,     0,     0,
       0,   113,   114,   115,    30,    31,    32,    33,     0,     0,
       0,    34,    35,    36,     0,    76,     0,    38,    94,     0,
       0,     0,     0,     0,    39,    30,    31,    32,    33,     0,
       0,     0,    34,    35,    36,     0,    76,   187,    38,    40,
      41,    42,    43,    44,     0,    39,    30,    31,    32,    33,
       0,     0,     0,    34,    35,    36,     0,    76,     0,    38,
      40,    41,    42,    43,    44,     0,    39,    30,    31,    32,
      33,     0,     0,     0,     0,    35,    36,     0,    76,     0,
      38,    40,    41,    42,    43,    44,   283,    39,     0,     0,
       0,     0,     0,   101,   102,   103,     0,   104,   105,   106,
       0,     0,    40,    41,    42,    43,    44,     0,     0,     0,
       0,   107,   108,   109,   110,   111,   104,   105,     0,   113,
     114,   115,   101,   102,   103,     0,   104,   105,   106,     0,
     107,   108,   109,   110,   111,     0,     0,     0,     0,   114,
     107,   108,   109,   110,   111,     0,   112,     0,   113,   114,
     115,   101,   102,   103,     0,   104,   105,   106,     0,   184,
       0,     0,   101,   102,   103,     0,   104,   105,   106,   107,
     108,   109,   110,   111,     0,     0,     0,   113,   114,   115,
     107,   108,   109,   110,   111,   186,     0,     0,   113,   114,
     115,   101,   102,   103,     0,   104,   105,   106,     0,   250,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   107,
     108,   109,   110,   111,     0,     0,     0,   113,   114,   115,
     101,   102,   103,     0,   104,   105,   106,     0,   251,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   107,   108,
     109,   110,   111,     0,     0,     0,   113,   114,   115,   101,
     102,   103,     0,   104,   105,   106,     0,     0,     0,   297,
       0,     0,     0,     0,     0,     0,     0,   107,   108,   109,
     110,   111,     0,     0,     0,   113,   114,   115,   101,   102,
     103,     0,   104,   105,   106,     0,   309,     0,     0,   101,
     102,   103,     0,   104,   105,   106,   107,   108,   109,   110,
     111,     0,     0,     0,   113,   114,   115,   107,   108,   109,
     110,   111,     0,     0,     0,   113,   114,   115,   102,   103,
       0,   104,   105,   106,     0,     0,     0,     0,     0,   102,
       0,     0,   104,   105,   106,   107,   108,   109,   110,   111,
       0,     0,     0,   113,   114,   115,   107,   108,   109,   110,
     111,   104,   105,     0,   113,   114,   115,     0,     0,     0,
       0,     0,     0,     0,     0,   107,   108,   109,   110,   111,
       0,     0,     0,     0,   114,   115
  };

  const short int
  Parser::yycheck_[] =
  {
      34,    19,    67,    37,    38,    38,    67,    74,   240,     9,
      35,    36,    64,   216,    52,    35,    52,    49,    50,    56,
       9,     9,    49,    50,    69,    51,    11,    12,    62,    57,
       3,    53,    70,     0,    62,    80,    62,    80,   241,    35,
      36,   138,    76,    80,    80,    77,    68,    81,    80,    76,
      77,    51,    52,    87,    79,    80,    74,    67,   290,    79,
      85,    86,    51,    51,    98,    98,   312,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   312,   113,
     114,   115,   100,    79,    80,    49,    50,    53,   291,    85,
      86,   312,   338,    52,   112,    58,    53,   131,   132,   133,
      51,    51,    49,    50,   338,    52,   140,   141,   142,    59,
     144,    62,   315,    77,    80,    49,    50,   338,    52,   129,
     130,    80,   174,    80,   221,   222,    65,    66,   138,    76,
      77,    78,   125,   126,    51,   145,   146,   147,   341,    80,
     237,   238,    76,    77,    78,    62,    51,    52,    80,   183,
      50,   216,   186,    80,    59,   216,   208,   209,    51,    80,
     212,    41,    42,    43,    44,    65,    66,    67,    59,    49,
      50,    56,    56,   207,    54,    33,   241,    80,    52,   213,
     241,    61,    51,   280,    42,    43,    44,   212,    49,    50,
      59,    49,    50,   130,   246,   229,    76,    77,    78,    79,
     234,    57,    60,    62,    80,   239,   216,    80,   260,   146,
     147,   221,   222,    49,    50,    76,    77,    78,    76,    77,
      78,    79,    80,    56,   276,   259,   291,   237,   238,   326,
     291,   241,   329,    52,   252,    53,    51,   262,   263,    62,
      76,    77,    78,   277,    59,   279,   279,    53,   345,   301,
     315,   318,    62,    55,   315,   352,    80,     4,     5,     6,
       7,     8,   359,    10,   298,    59,    49,    50,    53,    62,
     280,    52,   306,   283,   284,    51,   341,    80,    70,   304,
     341,   291,    65,    66,    67,    80,   320,    53,    41,    42,
      43,    44,    80,   327,   327,    48,    49,    50,    80,    52,
     318,    54,   312,    80,    69,   315,    80,    65,    61,    65,
      66,    67,   346,    57,    57,    69,   326,    53,    80,   329,
      65,    53,    57,    76,    77,    78,    79,    80,   338,    23,
      52,   341,    13,    14,    15,   345,    17,    18,    19,    20,
      21,    22,   352,    24,    25,    40,    27,    28,    11,   359,
      31,    51,    62,    69,    35,    36,    37,    53,    39,    13,
      51,    15,    16,    17,    18,    19,    20,    21,    22,    56,
      24,    25,    56,    27,    28,    56,    80,    31,    49,    50,
      52,    35,    36,    37,    51,    39,    30,    53,    53,    57,
      59,    53,    63,    74,    65,    66,    67,    57,    11,    80,
     243,    13,    56,    15,   211,    17,    18,    19,    20,    21,
      22,    68,    24,    25,   301,    27,    28,   247,   100,    31,
      74,   217,    75,    35,    36,    37,    80,    39,    13,   338,
      15,    -1,    17,    18,    19,    20,    21,    22,    -1,    24,
      25,    -1,    27,    28,    56,    57,    31,    -1,    -1,    -1,
      35,    36,    37,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    -1,    -1,    -1,    -1,    -1,    80,    -1,
      13,    56,    15,    -1,    17,    18,    19,    20,    21,    22,
      -1,    24,    25,    -1,    27,    28,    49,    50,    31,    74,
      75,    -1,    35,    36,    37,    80,    39,    -1,    23,    -1,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    71,    72,
      73,    -1,    -1,    56,    -1,    -1,    -1,    -1,    49,    50,
      45,    46,    47,    -1,    49,    50,    51,    23,    -1,    -1,
      -1,    74,    63,    64,    65,    66,    67,    80,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    71,    72,    73,    45,
      46,    47,    -1,    49,    50,    51,    -1,    -1,    -1,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    67,    -1,    29,    -1,    71,    72,    73,    45,    46,
      47,    -1,    49,    50,    51,    -1,    -1,    -1,    -1,    45,
      46,    47,    -1,    49,    50,    51,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    71,    72,    73,    63,    64,    65,
      66,    67,    32,    -1,    -1,    71,    72,    73,    49,    50,
      51,    -1,    -1,    -1,    -1,    45,    46,    47,    -1,    49,
      50,    51,    63,    64,    65,    66,    67,    -1,    -1,    -1,
      71,    72,    73,    63,    64,    65,    66,    67,    -1,    -1,
      -1,    71,    72,    73,    41,    42,    43,    44,    -1,    -1,
      -1,    48,    49,    50,    -1,    52,    -1,    54,    55,    -1,
      -1,    -1,    -1,    -1,    61,    41,    42,    43,    44,    -1,
      -1,    -1,    48,    49,    50,    -1,    52,    53,    54,    76,
      77,    78,    79,    80,    -1,    61,    41,    42,    43,    44,
      -1,    -1,    -1,    48,    49,    50,    -1,    52,    -1,    54,
      76,    77,    78,    79,    80,    -1,    61,    41,    42,    43,
      44,    -1,    -1,    -1,    -1,    49,    50,    -1,    52,    -1,
      54,    76,    77,    78,    79,    80,    38,    61,    -1,    -1,
      -1,    -1,    -1,    45,    46,    47,    -1,    49,    50,    51,
      -1,    -1,    76,    77,    78,    79,    80,    -1,    -1,    -1,
      -1,    63,    64,    65,    66,    67,    49,    50,    -1,    71,
      72,    73,    45,    46,    47,    -1,    49,    50,    51,    -1,
      63,    64,    65,    66,    67,    -1,    -1,    -1,    -1,    72,
      63,    64,    65,    66,    67,    -1,    69,    -1,    71,    72,
      73,    45,    46,    47,    -1,    49,    50,    51,    -1,    53,
      -1,    -1,    45,    46,    47,    -1,    49,    50,    51,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    71,    72,    73,
      63,    64,    65,    66,    67,    68,    -1,    -1,    71,    72,
      73,    45,    46,    47,    -1,    49,    50,    51,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,
      64,    65,    66,    67,    -1,    -1,    -1,    71,    72,    73,
      45,    46,    47,    -1,    49,    50,    51,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,
      65,    66,    67,    -1,    -1,    -1,    71,    72,    73,    45,
      46,    47,    -1,    49,    50,    51,    -1,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    71,    72,    73,    45,    46,
      47,    -1,    49,    50,    51,    -1,    53,    -1,    -1,    45,
      46,    47,    -1,    49,    50,    51,    63,    64,    65,    66,
      67,    -1,    -1,    -1,    71,    72,    73,    63,    64,    65,
      66,    67,    -1,    -1,    -1,    71,    72,    73,    46,    47,
      -1,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,    46,
      -1,    -1,    49,    50,    51,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    71,    72,    73,    63,    64,    65,    66,
      67,    49,    50,    -1,    71,    72,    73,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    63,    64,    65,    66,    67,
      -1,    -1,    -1,    -1,    72,    73
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    84,    85,     0,     4,     5,     6,     7,     8,
      10,    86,    87,    88,    89,    90,    91,    92,   122,    56,
      80,    80,    80,    80,    80,    52,    80,    87,    11,    12,
      41,    42,    43,    44,    48,    49,    50,    52,    54,    61,
      76,    77,    78,    79,    80,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   118,
     119,    58,    51,    52,    59,    51,     9,    51,    52,    80,
      93,    94,    59,    95,    56,    56,    52,   105,   118,    49,
      50,    52,   110,   111,   112,    49,    50,    52,    78,   110,
     111,   116,   117,   118,    55,   116,   118,    80,    52,    57,
      62,    45,    46,    47,    49,    50,    51,    63,    64,    65,
      66,    67,    69,    71,    72,    73,    80,   118,    53,    80,
      96,    97,    98,    80,   100,    56,    52,   123,   124,    13,
      15,    17,    18,    19,    20,    21,    22,    24,    25,    27,
      28,    31,    35,    36,    37,    39,    56,    74,    80,   119,
     120,   121,   125,   127,   128,   129,   130,   131,   132,   133,
     134,   138,   139,   140,   142,   143,   146,   147,   148,   149,
      53,    97,    53,    62,    69,    99,   100,   102,   106,   118,
     118,   118,    53,    62,    53,    55,    68,    53,   116,   118,
     104,   118,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   105,   118,   118,   118,    80,    51,    59,    59,
      53,    62,    52,    51,    93,    93,    51,    62,   120,   125,
     126,   141,   141,   118,   118,   118,    80,    80,   126,    52,
      80,   118,   118,   118,    80,   118,   119,   141,   141,    70,
       9,    51,    53,    80,    80,   100,    69,    65,    57,    57,
      53,    53,    69,   118,   118,    53,   118,   100,   100,    51,
      59,    96,    49,    50,   100,   101,   110,   118,    57,    53,
     121,   124,    14,   126,    16,    51,    59,    23,   118,    52,
      29,    32,   118,    38,    40,    57,    75,   118,   123,   121,
       9,    51,    95,   100,    99,    11,   105,    55,    51,   118,
     100,    62,    53,    53,    68,    69,   144,   100,   118,    53,
     116,   126,    56,   119,   119,    51,   123,   121,    56,   118,
      51,   101,   110,    80,   118,    51,    26,    52,    53,    30,
      33,    60,    79,   107,   108,   109,   119,   135,   136,   137,
     121,    51,   102,   118,    53,    23,   145,   126,   116,   126,
      57,   135,    59,   121,    57,   126,   118,    53,   126,    23,
     126
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    83,    84,    85,    86,    86,    87,    87,    87,    87,
      87,    87,    87,    87,    87,    88,    88,    89,    90,    91,
      91,    91,    91,    91,    91,    92,    92,    93,    93,    94,
      94,    95,    95,    96,    96,    97,    97,    98,    98,    99,
      99,    99,   100,   100,   100,   100,   101,   101,   101,   102,
     102,   103,   103,   104,   104,   104,   105,   105,   105,   105,
     105,   106,   106,   106,   106,   106,   106,   106,   106,   107,
     108,   108,   109,   109,   109,   110,   110,   110,   111,   111,
     111,   112,   112,   112,   113,   114,   115,   115,   116,   116,
     117,   117,   118,   118,   118,   118,   118,   118,   118,   118,
     118,   118,   118,   118,   118,   118,   118,   118,   119,   119,
     119,   120,   120,   121,   121,   122,   122,   122,   122,   122,
     122,   123,   123,   124,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   126,   126,   127,   128,   129,   129,   130,   131,   132,
     133,   134,   135,   135,   136,   137,   137,   137,   137,   137,
     137,   137,   138,   138,   138,   138,   139,   139,   140,   140,
     141,   141,   142,   142,   144,   143,   145,   143,   146,   147,
     148,   149
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     1,     1,     1,     1,     5,
       5,     9,     1,     1,     1,     2,     4,     5,     6,     7,
       4,     6,     9,     6,     8,     6,     3,     2,     1,     3,
       1,     3,     4,     3,     1,     1,     2,     3,     1,     3,
       2,     1,     1,     4,     4,     6,     3,     2,     1,     1,
       2,     3,     1,     1,     3,     5,     1,     1,     3,     4,
       4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     2,     1,     2,
       2,     1,     2,     2,     2,     5,     3,     2,     1,     2,
       3,     1,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     1,     1,     3,
       4,     1,     1,     1,     1,     4,     6,     7,     6,     8,
       9,     3,     1,     5,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     2,     1,     1,     2,     3,
       3,     6,     2,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     7,     4,     5,     2,     3,     3,     3,     3,
       2,     1,     4,     6,     0,     7,     0,     9,     4,     4,
       6,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"option\"", "\"derived\"", "\"enum\"", "\"rule\"", "\"dumps\"",
  "\"function\"", "\"initially\"", "\"defined\"", "\"seq\"", "\"endseq\"",
  "\"par\"", "\"endpar\"", "\"assert\"", "\"assure\"", "\"diedie\"",
  "\"impossible\"", "\"skip\"", "\"let\"", "\"in\"", "\"forall\"",
  "\"iterate\"", "\"do\"", "\"call\"", "\"if\"", "\"then\"", "\"else\"",
  "\"case\"", "\"of\"", "\"default\"", "\"endcase\"", "\"print\"",
  "\"debug\"", "\"push\"", "\"into\"", "\"pop\"", "\"from\"", "\"self\"",
  "\"undef\"", "\"false\"", "\"true\"", "\"and\"", "\"or\"", "\"xor\"",
  "\"not\"", "\"+\"", "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"",
  "\"{\"", "\"}\"", "\".\"", "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"",
  "\">\"", "\"*\"", "\"/\"", "\"%\"", "\"..\"", "\"->\"", "\":=\"",
  "\"!=\"", "\"<=\"", "\">=\"", "\"{|\"", "\"|}\"", "\"floating\"",
  "\"integer\"", "\"rational\"", "\"string\"", "\"identifier\"", "UPLUS",
  "UMINUS", "$accept", "SPECIFICATION", "HEADER", "BODY_ELEMENTS",
  "BODY_ELEMENT", "INIT_SYNTAX", "OPTION_SYNTAX", "ENUM_SYNTAX",
  "DERIVED_SYNTAX", "FUNCTION_DEFINITION", "IDENTIFIER_LIST",
  "IDENTIFIER_LIST_NO_COMMA", "FUNCTION_SIGNATURE", "PARAM", "PARAM_LIST",
  "PARAM_LIST_NO_COMMA", "TYPE_IDENTIFIER_STARLIST", "TYPE_SYNTAX",
  "TYPE_SYNTAX_LIST", "INITIALIZER_LIST", "INITIALIZER_LIST_NO_COMMA",
  "INITIALIZER", "ATOM", "VALUE", "UNDEFINED", "BOOLEAN", "NUMBER",
  "INTEGER_NUMBER", "FLOATING_NUMBER", "RATIONAL_NUMBER", "RULEREF",
  "NUMBER_RANGE", "LISTCONST", "EXPRESSION_LIST",
  "EXPRESSION_LIST_NO_COMMA", "EXPRESSION", "FUNCTION_SYNTAX", "SCOPE",
  "RULE_STMT", "RULE_SYNTAX", "DUMPSPEC_LIST", "DUMPSPEC", "SIMPLE_STMT",
  "STATEMENT", "ASSERT_SYNTAX", "ASSURE_SYNTAX", "DIEDIE_SYNTAX",
  "IMPOSSIBLE_SYNTAX", "PRINT_SYNTAX", "DEBUG_SYNTAX", "UPDATE_SYNTAX",
  "CASE_SYNTAX", "CASE_LABEL_LIST", "CASE_LABEL", "CASE_VALUE",
  "CALL_SYNTAX", "SEQ_SYNTAX", "PAR_SYNTAX", "STATEMENTS", "IFTHENELSE",
  "LET_SYNTAX", "$@1", "$@2", "PUSH_SYNTAX", "POP_SYNTAX", "FORALL_SYNTAX",
  "ITERATE_SYNTAX", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   349,   349,   357,   372,   377,   386,   390,   394,   415,
     444,   468,   498,   521,   525,   550,   576,   606,   611,   658,
     663,   667,   671,   675,   679,   687,   693,   700,   704,   712,
     717,   726,   732,   740,   746,   757,   761,   769,   774,   782,
     787,   792,   800,   823,   836,   858,   876,   881,   885,   893,
     897,   905,   910,   918,   923,   931,   940,   944,   948,   952,
     956,   965,   969,   973,   977,   981,   985,   989,   993,  1001,
    1009,  1013,  1021,  1025,  1029,  1037,  1041,  1045,  1054,  1058,
    1062,  1071,  1075,  1079,  1088,  1096,  1104,  1108,  1116,  1120,
    1128,  1133,  1142,  1146,  1150,  1154,  1158,  1162,  1166,  1170,
    1174,  1178,  1182,  1186,  1190,  1194,  1198,  1202,  1210,  1214,
    1218,  1233,  1237,  1245,  1249,  1259,  1263,  1267,  1271,  1276,
    1281,  1290,  1295,  1304,  1312,  1316,  1320,  1324,  1328,  1332,
    1336,  1340,  1344,  1348,  1352,  1356,  1360,  1364,  1368,  1372,
    1376,  1396,  1400,  1408,  1416,  1424,  1428,  1444,  1452,  1460,
    1468,  1489,  1497,  1502,  1511,  1519,  1523,  1528,  1532,  1536,
    1540,  1544,  1552,  1556,  1560,  1564,  1572,  1576,  1584,  1588,
    1596,  1601,  1610,  1614,  1624,  1623,  1641,  1640,  1661,  1676,
    1699,  1709
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
#line 3743 "GrammarParser.cpp" // lalr1.cc:1167
#line 1715 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
