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

#line 140 "GrammarParser.cpp" // lalr1.cc:413


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
#line 226 "GrammarParser.cpp" // lalr1.cc:479

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
      case 83: // SPECIFICATION
        value.move< Ast* > (that.value);
        break;

      case 85: // BODY_ELEMENTS
      case 140: // STATEMENTS
        value.move< AstListNode* > (that.value);
        break;

      case 86: // BODY_ELEMENT
      case 119: // SCOPE
      case 120: // RULE_STMT
      case 121: // RULE_SYNTAX
      case 124: // SIMPLE_STMT
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.move< AstNode* > (that.value);
        break;

      case 105: // VALUE
      case 106: // UNDEFINED
      case 107: // BOOLEAN
      case 108: // NUMBER
      case 113: // NUMBER_RANGE
      case 136: // CASE_VALUE
        value.move< AtomNode* > (that.value);
        break;

      case 118: // FUNCTION_SYNTAX
        value.move< BaseFunctionAtom* > (that.value);
        break;

      case 137: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 133: // CASE_SYNTAX
        value.move< CaseNode* > (that.value);
        break;

      case 128: // DIEDIE_SYNTAX
        value.move< DiedieNode* > (that.value);
        break;

      case 89: // ENUM_SYNTAX
        value.move< Enum* > (that.value);
        break;

      case 104: // ATOM
      case 117: // EXPRESSION
        value.move< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.move< FLOATING_T > (that.value);
        break;

      case 110: // FLOATING_NUMBER
        value.move< FloatingAtom* > (that.value);
        break;

      case 147: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 90: // DERIVED_SYNTAX
      case 91: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 76: // "integer"
        value.move< INTEGER_T > (that.value);
        break;

      case 141: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 87: // INIT_SYNTAX
        value.move< InitNode* > (that.value);
        break;

      case 109: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 142: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 146: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 130: // PRINT_SYNTAX
      case 131: // DEBUG_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 145: // PUSH_SYNTAX
        value.move< PushNode* > (that.value);
        break;

      case 111: // RATIONAL_NUMBER
        value.move< RationalAtom* > (that.value);
        break;

      case 84: // HEADER
        value.move< SpecificationNode* > (that.value);
        break;

      case 95: // PARAM
      case 99: // TYPE_SYNTAX
        value.move< Type* > (that.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 103: // INITIALIZER
      case 132: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.move< rational_t > (that.value);
        break;

      case 135: // CASE_LABEL
        value.move< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 123: // DUMPSPEC
        value.move< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 94: // FUNCTION_SIGNATURE
        value.move< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 112: // RULEREF
        value.move< std::string > (that.value);
        break;

      case 114: // LISTCONST
      case 115: // EXPRESSION_LIST
      case 116: // EXPRESSION_LIST_NO_COMMA
        value.move< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 96: // PARAM_LIST
      case 97: // PARAM_LIST_NO_COMMA
      case 98: // TYPE_IDENTIFIER_STARLIST
      case 100: // TYPE_SYNTAX_LIST
        value.move< std::vector<Type*> > (that.value);
        break;

      case 101: // INITIALIZER_LIST
      case 102: // INITIALIZER_LIST_NO_COMMA
        value.move< std::vector<UpdateNode*> > (that.value);
        break;

      case 134: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 122: // DUMPSPEC_LIST
        value.move< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 92: // IDENTIFIER_LIST
      case 93: // IDENTIFIER_LIST_NO_COMMA
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
      case 83: // SPECIFICATION
        value.copy< Ast* > (that.value);
        break;

      case 85: // BODY_ELEMENTS
      case 140: // STATEMENTS
        value.copy< AstListNode* > (that.value);
        break;

      case 86: // BODY_ELEMENT
      case 119: // SCOPE
      case 120: // RULE_STMT
      case 121: // RULE_SYNTAX
      case 124: // SIMPLE_STMT
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        value.copy< AstNode* > (that.value);
        break;

      case 105: // VALUE
      case 106: // UNDEFINED
      case 107: // BOOLEAN
      case 108: // NUMBER
      case 113: // NUMBER_RANGE
      case 136: // CASE_VALUE
        value.copy< AtomNode* > (that.value);
        break;

      case 118: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (that.value);
        break;

      case 137: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 133: // CASE_SYNTAX
        value.copy< CaseNode* > (that.value);
        break;

      case 128: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (that.value);
        break;

      case 89: // ENUM_SYNTAX
        value.copy< Enum* > (that.value);
        break;

      case 104: // ATOM
      case 117: // EXPRESSION
        value.copy< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.copy< FLOATING_T > (that.value);
        break;

      case 110: // FLOATING_NUMBER
        value.copy< FloatingAtom* > (that.value);
        break;

      case 147: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 90: // DERIVED_SYNTAX
      case 91: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 76: // "integer"
        value.copy< INTEGER_T > (that.value);
        break;

      case 141: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 87: // INIT_SYNTAX
        value.copy< InitNode* > (that.value);
        break;

      case 109: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 142: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 146: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 130: // PRINT_SYNTAX
      case 131: // DEBUG_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 145: // PUSH_SYNTAX
        value.copy< PushNode* > (that.value);
        break;

      case 111: // RATIONAL_NUMBER
        value.copy< RationalAtom* > (that.value);
        break;

      case 84: // HEADER
        value.copy< SpecificationNode* > (that.value);
        break;

      case 95: // PARAM
      case 99: // TYPE_SYNTAX
        value.copy< Type* > (that.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 103: // INITIALIZER
      case 132: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.copy< rational_t > (that.value);
        break;

      case 135: // CASE_LABEL
        value.copy< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 123: // DUMPSPEC
        value.copy< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 94: // FUNCTION_SIGNATURE
        value.copy< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 112: // RULEREF
        value.copy< std::string > (that.value);
        break;

      case 114: // LISTCONST
      case 115: // EXPRESSION_LIST
      case 116: // EXPRESSION_LIST_NO_COMMA
        value.copy< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 96: // PARAM_LIST
      case 97: // PARAM_LIST_NO_COMMA
      case 98: // TYPE_IDENTIFIER_STARLIST
      case 100: // TYPE_SYNTAX_LIST
        value.copy< std::vector<Type*> > (that.value);
        break;

      case 101: // INITIALIZER_LIST
      case 102: // INITIALIZER_LIST_NO_COMMA
        value.copy< std::vector<UpdateNode*> > (that.value);
        break;

      case 134: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 122: // DUMPSPEC_LIST
        value.copy< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 92: // IDENTIFIER_LIST
      case 93: // IDENTIFIER_LIST_NO_COMMA
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

#line 866 "GrammarParser.cpp" // lalr1.cc:741

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
      case 83: // SPECIFICATION
        yylhs.value.build< Ast* > ();
        break;

      case 85: // BODY_ELEMENTS
      case 140: // STATEMENTS
        yylhs.value.build< AstListNode* > ();
        break;

      case 86: // BODY_ELEMENT
      case 119: // SCOPE
      case 120: // RULE_STMT
      case 121: // RULE_SYNTAX
      case 124: // SIMPLE_STMT
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
        yylhs.value.build< AstNode* > ();
        break;

      case 105: // VALUE
      case 106: // UNDEFINED
      case 107: // BOOLEAN
      case 108: // NUMBER
      case 113: // NUMBER_RANGE
      case 136: // CASE_VALUE
        yylhs.value.build< AtomNode* > ();
        break;

      case 118: // FUNCTION_SYNTAX
        yylhs.value.build< BaseFunctionAtom* > ();
        break;

      case 137: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 133: // CASE_SYNTAX
        yylhs.value.build< CaseNode* > ();
        break;

      case 128: // DIEDIE_SYNTAX
        yylhs.value.build< DiedieNode* > ();
        break;

      case 89: // ENUM_SYNTAX
        yylhs.value.build< Enum* > ();
        break;

      case 104: // ATOM
      case 117: // EXPRESSION
        yylhs.value.build< ExpressionBase* > ();
        break;

      case 75: // "floating"
        yylhs.value.build< FLOATING_T > ();
        break;

      case 110: // FLOATING_NUMBER
        yylhs.value.build< FloatingAtom* > ();
        break;

      case 147: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 90: // DERIVED_SYNTAX
      case 91: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 76: // "integer"
        yylhs.value.build< INTEGER_T > ();
        break;

      case 141: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 87: // INIT_SYNTAX
        yylhs.value.build< InitNode* > ();
        break;

      case 109: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 142: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 146: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 130: // PRINT_SYNTAX
      case 131: // DEBUG_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 145: // PUSH_SYNTAX
        yylhs.value.build< PushNode* > ();
        break;

      case 111: // RATIONAL_NUMBER
        yylhs.value.build< RationalAtom* > ();
        break;

      case 84: // HEADER
        yylhs.value.build< SpecificationNode* > ();
        break;

      case 95: // PARAM
      case 99: // TYPE_SYNTAX
        yylhs.value.build< Type* > ();
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 103: // INITIALIZER
      case 132: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 77: // "rational"
        yylhs.value.build< rational_t > ();
        break;

      case 135: // CASE_LABEL
        yylhs.value.build< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 123: // DUMPSPEC
        yylhs.value.build< std::pair<std::string, std::vector<std::string>> > ();
        break;

      case 94: // FUNCTION_SIGNATURE
        yylhs.value.build< std::pair<std::vector<Type*>, Type*> > ();
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 112: // RULEREF
        yylhs.value.build< std::string > ();
        break;

      case 114: // LISTCONST
      case 115: // EXPRESSION_LIST
      case 116: // EXPRESSION_LIST_NO_COMMA
        yylhs.value.build< std::vector<ExpressionBase*>* > ();
        break;

      case 96: // PARAM_LIST
      case 97: // PARAM_LIST_NO_COMMA
      case 98: // TYPE_IDENTIFIER_STARLIST
      case 100: // TYPE_SYNTAX_LIST
        yylhs.value.build< std::vector<Type*> > ();
        break;

      case 101: // INITIALIZER_LIST
      case 102: // INITIALIZER_LIST_NO_COMMA
        yylhs.value.build< std::vector<UpdateNode*> > ();
        break;

      case 134: // CASE_LABEL_LIST
        yylhs.value.build< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 122: // DUMPSPEC_LIST
        yylhs.value.build< std::vector<std::pair<std::string, std::vector<std::string>>> > ();
        break;

      case 92: // IDENTIFIER_LIST
      case 93: // IDENTIFIER_LIST_NO_COMMA
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
#line 343 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
  }
#line 1160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 351 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      const std::string& filepath = driver.get_filename();
      
      const std::string& filename
          = filepath.substr( filepath.find_last_of( "/\\" ) + 1 );
      
      const std::string& filename_without_extension
          = filename.substr( 0, filename.rfind( "." ) );
      
      yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, filename_without_extension );
  }
#line 1176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 1185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
      yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
  }
#line 1194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 380 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( NodeType::OPTION );
  }
#line 1202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 384 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new EnumDefNode( yylhs.location, yystack_[0].value.as< Enum* > () );
  }
#line 1210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1235 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 409 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1268 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 438 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1295 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > ();
  }
#line 1303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 465 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 490 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      static InitNode* init_node = 0;

      if( not init_node )
      {
          init_node = new InitNode( yylhs.location, yystack_[0].value.as< std::string > () );
      }
      else
      {
          static u1 flag = true;
          
          if( flag )
          {
              flag = false;
              
              driver.error
              ( init_node->location
              , "multiple definition of 'init' node"
              , libcasm_fe::Codes::AgentInitRuleMultipleDefinitions
              );
          }
          
          driver.error
          ( yylhs.location
          , "multiple definition of 'init' node"
          , libcasm_fe::Codes::AgentInitRuleMultipleDefinitions
          );
      }
      
      yylhs.value.as< InitNode* > () = init_node;
  }
#line 1364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1411 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: 2nd argument should be a reference
      yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1420 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 583 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1428 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1436 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 591 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1444 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 595 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1452 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 607 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second);
      parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > (), function);
      yylhs.value.as< Function* > () = function;
  }
#line 1470 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 613 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second);
  }
#line 1478 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
  }
#line 1486 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ());
  }
#line 1494 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 632 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move( yystack_[2].value.as< std::vector<std::string> > () );
      yylhs.value.as< std::vector<std::string> > ().push_back( yystack_[0].value.as< std::string > () );
  }
#line 1503 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 637 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
      yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
  }
#line 1512 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 646 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      /* this constructor is implementation dependant! */
      std::vector<Type*> foo;
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
  }
#line 1522 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 652 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ());
  }
#line 1530 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 660 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
      yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
  }
#line 1540 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 666 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      size_t size = driver.binding_offsets.size();
      driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
      // TODO: fail for rules without types and print warnings
      yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
  }
#line 1551 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 677 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1559 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 681 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ());
  }
#line 1567 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 689 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1576 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 694 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 702 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 707 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // TODO: limit memory size
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
  }
#line 1602 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1610 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1637 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 743 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1654 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1680 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1698 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 796 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< std::vector<Type*> > ().push_back( yystack_[2].value.as< Type* > () );
      yylhs.value.as< std::vector<Type*> > () = std::move( yystack_[0].value.as< std::vector<Type*> > () );
  }
#line 1707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[1].value.as< Type* > () );
  }
#line 1715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[0].value.as< Type* > () );
  }
#line 1723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 813 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = std::move(yystack_[0].value.as< std::vector<UpdateNode*> > ());
  }
#line 1731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = std::move(yystack_[1].value.as< std::vector<UpdateNode*> > ());
  }
#line 1739 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = std::move(yystack_[2].value.as< std::vector<UpdateNode*> > ());
      yylhs.value.as< std::vector<UpdateNode*> > ().push_back(yystack_[0].value.as< UpdateNode* > ());
  }
#line 1748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 830 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = { yystack_[0].value.as< UpdateNode* > () };
  }
#line 1756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 838 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new FunctionAtom( yylhs.location, "" );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1765 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 843 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto args = new std::vector< ExpressionBase* >;
      args->push_back(yystack_[2].value.as< ExpressionBase* > ());

      auto function = new FunctionAtom( yylhs.location, "", args );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1777 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 851 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new FunctionAtom( yylhs.location, "", yystack_[3].value.as< std::vector<ExpressionBase*>* > () );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1786 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 860 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1794 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 864 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1802 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 868 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1810 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 872 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1818 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 876 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, new ZeroAtom( yylhs.location, yystack_[1].value.as< ExpressionBase* > () ), yystack_[1].value.as< ExpressionBase* > (),
                                 libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1827 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 885 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1835 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 889 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1843 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 893 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1851 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 897 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1859 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 901 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1867 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 905 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1875 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 909 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); 
  }
#line 1883 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 913 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1891 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 921 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1899 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 929 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 1907 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 933 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 1915 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 941 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1923 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1931 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1939 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 957 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1947 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 961 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1955 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 965 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
      yystack_[0].value.as< IntegerAtom* > ()->val_ *= (-1);
  }
#line 1964 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1972 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1980 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
      yystack_[0].value.as< FloatingAtom* > ()->val_ *= (-1);
  }
#line 1989 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 991 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1997 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 995 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 2005 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 999 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< rational_t > ().numerator *= -1;
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 2014 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 1008 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 2022 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 1016 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new NumberRangeAtom( yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2030 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2038 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 1028 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 2046 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 1036 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2054 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 1040 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2062 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 1048 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2071 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2080 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 1062 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2088 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2096 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 1070 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2104 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2112 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1078 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2120 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2128 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2136 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1090 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2144 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1094 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2152 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1102 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1110 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2184 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1114 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2192 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1118 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new UnaryExpression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2200 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1122 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2208 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1130 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2216 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2224 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1138 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1153 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1157 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1165 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1169 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      stmts->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1179 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2281 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1183 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2289 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2297 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1191 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1196 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1201 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2324 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1210 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2333 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2342 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1224 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2350 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1232 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2358 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1236 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2366 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1240 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1244 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1248 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2390 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1252 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2398 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1256 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2406 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1260 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2414 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1264 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1268 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2430 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1272 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2438 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1276 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2446 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1280 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1284 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2462 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1288 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2470 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1292 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2478 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1296 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.error
      ( yylhs.location
      , "invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
      , libcasm_fe::Codes::SyntaxErrorInvalidStatement
      );
  }
#line 2490 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1316 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2498 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1320 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2506 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1328 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2514 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1336 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2522 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1344 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2530 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1348 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2538 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1364 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2546 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1372 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2554 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1380 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[1].value.as< std::string > () );
  }
#line 2562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1388 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1409 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2591 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1417 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[0].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[1].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2600 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::vector< std::pair< AtomNode*, AstNode* > >();
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1439 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // equivalent to 'default' 
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2634 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1452 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2650 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1456 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2658 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 2666 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1464 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 2674 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2682 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1476 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2690 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2698 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2706 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1492 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2714 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1496 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2722 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1504 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2730 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1508 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2738 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1516 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2747 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1521 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1530 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1534 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1543 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1555 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[5].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1560 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1572 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[7].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2822 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1581 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2837 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1596 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2860 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1619 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2868 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1629 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2876 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2880 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -197;

  const signed char Parser::yytable_ninf_ = -106;

  const short int
  Parser::yypact_[] =
  {
      14,  -197,    68,   337,  -197,    -4,     8,    18,    46,    59,
     -10,   337,  -197,  -197,  -197,  -197,  -197,    74,  -197,  -197,
      36,   -28,   110,    12,    84,    48,  -197,   124,    91,   640,
      20,    95,   125,   153,   474,    78,  -197,   157,   144,   -48,
    -197,   661,   133,  -197,  -197,  -197,  -197,   640,    35,    41,
     640,   598,   134,  -197,  -197,  -197,  -197,   163,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,   900,
    -197,    23,   158,  -197,   174,   154,   177,   179,    84,    84,
     -25,  -197,   474,   474,   640,   640,   640,  -197,  -197,   152,
     161,   474,    40,   640,   640,   640,   164,   640,   168,   474,
     474,   -37,   180,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,  -197,     0,   200,   185,   186,    95,   198,   194,
     640,   217,   213,  -197,   -32,   733,  -197,  -197,   -30,    56,
     640,  -197,  -197,  -197,    80,    80,   640,  -197,  -197,  -197,
     762,  -197,   221,   215,   773,  -197,   619,   640,   640,   640,
     640,   640,   640,   640,   640,   640,   640,   640,   640,   640,
     640,   640,    95,    95,   108,   199,    -5,   640,   223,   229,
     474,   153,  -197,  -197,  -197,   336,   363,   900,   900,   900,
     115,   261,  -197,   640,   233,   554,   565,   900,   640,   704,
     248,   405,   432,   640,   153,   474,     6,    48,  -197,  -197,
      95,    95,   234,   762,  -197,   661,   682,   802,   831,  -197,
    -197,   640,   640,  -197,   236,   900,   257,   939,   928,   171,
      77,   454,   190,   159,  -197,   225,   119,   958,   197,   247,
     900,   241,  -197,   640,    95,  -197,    72,    72,   231,   263,
      15,   900,  -197,   232,  -197,  -197,  -197,  -197,  -197,  -197,
      95,   640,   860,   640,   474,   238,   900,   168,   168,  -197,
    -197,   900,    27,  -197,   153,   474,  -197,  -197,  -197,   249,
    -197,  -197,  -197,  -197,   900,   889,  -197,   640,   900,   275,
      95,  -197,  -197,    72,   251,   640,   276,   521,   280,   281,
     305,   502,  -197,  -197,   474,    89,  -197,   682,  -197,   900,
     640,  -197,   284,  -197,   -11,  -197,   474,   640,  -197,   474,
    -197,  -197,  -197,  -197,  -197,  -197,  -197,   282,   502,   279,
    -197,   474,  -197,   900,  -197,   474,   640,  -197,   288,  -197,
    -197,  -197,   474,  -197,  -197,   492,  -197,  -197,   474,  -197
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     3,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     2,     5,    11,     6,     7,    10,     8,    12,    13,
       0,     0,     0,     0,     0,     0,     4,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    27,     0,    25,     0,
      23,     0,     0,    63,    66,    68,    67,     0,     0,     0,
       0,     0,     0,    75,    72,    78,    60,   105,   104,    54,
      64,    65,    59,    69,    70,    71,    58,    62,    61,    17,
      53,     0,    31,    35,     0,    32,    39,     0,     0,     0,
       0,   119,     0,     0,     0,     0,   143,   144,   136,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   137,     0,   110,   112,   111,   121,   122,   123,   124,
     126,   125,   127,   128,   129,   108,   109,   130,   131,   132,
     133,   134,   135,     0,     0,     0,    24,     0,     0,    38,
       0,     0,    46,    49,   104,     0,    14,   103,     0,     0,
       0,    73,    76,    79,     0,     0,     0,    80,    74,    77,
       0,    84,     0,    85,    88,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    33,     0,     0,     0,     0,
       0,     0,   138,   139,   168,     0,     0,   140,   141,   142,
       0,     0,   178,     0,   162,     0,     0,   145,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    26,    28,
       0,    37,     0,    88,     9,    47,     0,     0,     0,    55,
      83,    86,     0,   106,     0,    88,   102,   100,   101,    89,
      90,    95,    96,    97,    91,    92,    93,    94,    98,    99,
      18,     0,    30,     0,     0,    34,     0,     0,    45,     0,
       0,    20,    15,     0,   115,   118,   164,   167,   166,   171,
       0,     0,     0,     0,     0,     0,   146,     0,     0,   165,
     163,   147,     0,   113,     0,     0,    22,    29,    36,     0,
      48,    51,    56,    57,    87,     0,   107,     0,    16,     0,
      44,    41,    40,     0,     0,     0,     0,     0,   160,     0,
     169,     0,   175,   176,     0,     0,   114,     0,    82,    21,
       0,    43,     0,   120,     0,   173,     0,     0,   161,     0,
     152,   153,   157,   154,   155,   156,   158,     0,   150,     0,
     116,     0,    52,    19,    42,     0,     0,   177,     0,   170,
     148,   149,     0,   117,   172,     0,   159,   151,     0,   174
  };

  const short int
  Parser::yypgoto_[] =
  {
    -197,  -197,  -197,  -197,   335,  -197,  -197,  -197,  -197,  -197,
      66,  -197,   160,   193,   326,  -197,   162,     9,    79,  -197,
    -197,   170,   -39,  -197,  -167,  -166,  -164,   -36,   -44,   -42,
    -197,  -197,  -197,  -114,  -197,    29,   -34,   -33,  -177,  -197,
    -196,   195,   -27,    16,  -197,  -197,  -197,  -197,  -197,  -197,
    -197,  -197,    60,  -197,  -197,  -197,  -197,  -197,   -73,  -197,
    -197,  -197,  -197,  -197,  -197,  -197,  -197
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,    11,    12,    13,    14,    15,    16,    17,
      37,    38,    40,    73,    74,    75,   128,   129,   249,   131,
     132,   133,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,   152,   153,   225,    70,   182,   104,    18,
      80,    81,   183,   184,   106,   107,   108,   109,   110,   111,
     112,   113,   327,   328,   329,   114,   115,   116,   185,   117,
     118,   295,   336,   119,   120,   121,   122
  };

  const short int
  Parser::yytable_[] =
  {
     102,   103,   134,   254,   142,   149,   143,   105,   272,   204,
     186,   335,   141,   148,   156,   274,   212,     1,   138,   139,
     127,    33,    29,    30,   -50,   180,   201,   202,   273,   -50,
      31,    76,  -105,   157,   158,   159,   181,   160,   161,   162,
      77,    24,   224,   246,   247,    53,    54,    55,   102,   102,
     205,   163,   164,   165,   166,   167,   275,   102,    69,   168,
     169,   170,    34,    35,   200,   102,   102,   292,     4,    25,
     135,    54,    71,   171,    76,    19,   137,   304,   305,   150,
     154,   172,   293,   138,   139,    27,   140,    20,   181,   144,
     145,   193,   146,    28,   142,   149,   143,    21,   306,    72,
     142,   149,   141,   148,   144,   145,    39,   192,   141,   148,
      53,    54,    55,   187,   188,   189,    53,    54,   147,   194,
     246,   247,   195,   196,   197,    22,   199,   330,   144,   145,
     123,    53,    54,   147,   323,   324,   209,   325,    23,   331,
     250,   165,   166,   167,   178,   179,   102,   103,    54,   299,
     181,   102,   102,   105,   343,    53,    54,    72,   243,   213,
      32,   323,   324,    36,   325,   259,   244,   102,   102,   217,
      42,   102,   103,   260,    76,   218,   134,   281,   105,    41,
      78,   241,   242,   165,   166,   248,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   257,   257,   338,    79,   126,   251,   160,   161,   125,
     141,   148,   136,   155,   156,   175,   173,   257,   257,   277,
     161,   163,   262,   165,   166,   167,   174,   266,   176,   177,
     102,   190,   271,   302,   303,   165,   166,   167,   160,   161,
     191,   102,   103,   198,   135,   160,   161,    57,   105,   203,
     284,   285,   206,   289,   165,   166,   167,   312,   211,   163,
     164,   165,   166,   167,   207,   208,   210,   326,   332,   296,
     102,   103,   288,   214,   215,   220,   221,   105,    72,   252,
     300,   253,   102,   261,   263,   102,   279,   268,   286,   165,
     297,   287,   290,   301,   326,   160,   161,   102,   103,   248,
     294,   102,   158,   159,   105,   160,   161,   162,   102,   163,
     164,   165,   166,   167,   102,   291,   309,   307,   169,   163,
     164,   165,   166,   167,   314,   310,   315,   168,   169,   170,
     313,   317,   337,   318,   319,   339,   334,   342,   340,   333,
     346,     5,     6,     7,     8,     9,    26,    10,    82,   256,
      83,   344,    84,    85,    86,    87,    88,    89,   347,    90,
      91,   124,    92,    93,   349,   345,    94,   276,   245,   311,
      95,    96,    97,   278,    98,    82,   255,    83,   258,    84,
      85,    86,    87,    88,    89,   280,    90,    91,   341,    92,
      93,    99,     0,    94,     0,     0,     0,    95,    96,    97,
       0,    98,     0,     0,     0,     0,     0,     0,     0,   100,
       0,     0,     0,     0,     0,   101,     0,    82,    99,    83,
       0,    84,    85,    86,    87,    88,    89,     0,    90,    91,
       0,    92,    93,     0,     0,    94,   100,     0,     0,    95,
      96,    97,   101,    98,    82,     0,    83,     0,    84,    85,
      86,    87,    88,    89,     0,    90,    91,     0,    92,    93,
      99,   269,    94,     0,     0,     0,    95,    96,    97,     0,
      98,     0,     0,     0,     0,     0,     0,     0,   100,     0,
       0,     0,     0,     0,   101,     0,    82,    99,    83,     0,
      84,    85,    86,    87,    88,    89,     0,    90,    91,     0,
      92,    93,   160,   161,    94,   100,   270,     0,    95,    96,
      97,   101,    98,     0,   348,     0,   163,   164,   165,   166,
     167,     0,     0,     0,   168,   169,   170,     0,     0,    99,
       0,     0,     0,     0,   320,     0,   157,   158,   159,     0,
     160,   161,   162,    44,    45,    46,   316,   100,     0,     0,
     138,   139,     0,   101,   163,   164,   165,   166,   167,     0,
       0,   321,   168,   169,   170,   157,   158,   159,     0,   160,
     161,   162,     0,     0,     0,     0,     0,    53,    54,    55,
     322,    57,   264,   163,   164,   165,   166,   167,     0,     0,
       0,   168,   169,   170,     0,     0,   265,     0,   157,   158,
     159,     0,   160,   161,   162,     0,     0,     0,     0,   157,
     158,   159,     0,   160,   161,   162,   163,   164,   165,   166,
     167,     0,     0,     0,   168,   169,   170,   163,   164,   165,
     166,   167,     0,     0,     0,   168,   169,   170,    43,    44,
      45,    46,     0,     0,     0,    47,    48,    49,     0,    50,
       0,    51,   151,     0,     0,     0,     0,     0,    52,    43,
      44,    45,    46,     0,     0,     0,    47,    48,    49,     0,
      50,   223,    51,    53,    54,    55,    56,    57,     0,    52,
      43,    44,    45,    46,     0,     0,     0,    47,    48,    49,
       0,    50,     0,    51,    53,    54,    55,    56,    57,     0,
      52,    43,    44,    45,    46,     0,     0,     0,    47,    48,
      49,     0,   130,     0,    51,    53,    54,    55,    56,    57,
       0,    52,    43,    44,    45,    46,     0,     0,     0,     0,
      48,    49,     0,    50,     0,    51,    53,    54,    55,    56,
      57,   267,    52,     0,     0,     0,     0,     0,   157,   158,
     159,     0,   160,   161,   162,     0,     0,    53,    54,    55,
      56,    57,     0,     0,     0,     0,   163,   164,   165,   166,
     167,     0,     0,     0,   168,   169,   170,   157,   158,   159,
       0,   160,   161,   162,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   163,   164,   165,   166,   167,
       0,   216,     0,   168,   169,   170,   157,   158,   159,     0,
     160,   161,   162,     0,   219,     0,     0,   157,   158,   159,
       0,   160,   161,   162,   163,   164,   165,   166,   167,     0,
       0,     0,   168,   169,   170,   163,   164,   165,   166,   167,
     222,     0,     0,   168,   169,   170,   157,   158,   159,     0,
     160,   161,   162,     0,   282,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   163,   164,   165,   166,   167,     0,
       0,     0,   168,   169,   170,   157,   158,   159,     0,   160,
     161,   162,     0,   283,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   163,   164,   165,   166,   167,     0,     0,
       0,   168,   169,   170,   157,   158,   159,     0,   160,   161,
     162,     0,   298,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   163,   164,   165,   166,   167,     0,     0,     0,
     168,   169,   170,   157,   158,   159,     0,   160,   161,   162,
       0,     0,     0,   308,   157,   158,   159,     0,   160,   161,
     162,   163,   164,   165,   166,   167,     0,     0,     0,   168,
     169,   170,   163,   164,   165,   166,   167,     0,     0,     0,
     168,   169,   170,   158,     0,     0,   160,   161,   162,     0,
       0,     0,     0,     0,     0,     0,     0,   160,   161,   162,
     163,   164,   165,   166,   167,     0,     0,     0,   168,   169,
     170,   163,   164,   165,   166,   167,   160,   161,     0,   168,
     169,   170,     0,     0,     0,     0,     0,     0,     0,     0,
     163,   164,   165,   166,   167,     0,     0,     0,     0,   169,
     170
  };

  const short int
  Parser::yycheck_[] =
  {
      34,    34,    41,   180,    48,    49,    48,    34,   204,     9,
      83,    22,    48,    49,    51,     9,   130,     3,    48,    49,
      68,     9,    50,    51,    56,    50,    99,   100,   205,    61,
      58,    79,    69,    44,    45,    46,    61,    48,    49,    50,
      31,    51,   156,    48,    49,    75,    76,    77,    82,    83,
      50,    62,    63,    64,    65,    66,    50,    91,    29,    70,
      71,    72,    50,    51,    98,    99,   100,    52,     0,    79,
      41,    76,    52,    50,    79,    79,    47,    50,   274,    50,
      51,    58,    67,    48,    49,    11,    51,    79,    61,    48,
      49,    51,    51,    57,   138,   139,   138,    79,   275,    79,
     144,   145,   138,   139,    48,    49,    58,    91,   144,   145,
      75,    76,    77,    84,    85,    86,    75,    76,    77,    79,
      48,    49,    93,    94,    95,    79,    97,   304,    48,    49,
      52,    75,    76,    77,   301,   301,   127,   301,    79,    50,
     176,    64,    65,    66,    78,    79,   180,   180,    76,   263,
      61,   185,   186,   180,   331,    75,    76,    79,    50,   130,
      50,   328,   328,    79,   328,    50,    58,   201,   202,   140,
      79,   205,   205,    58,    79,   146,   215,   216,   205,    55,
      55,   172,   173,    64,    65,   176,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   185,   186,   317,    51,    61,   177,    48,    49,    52,
     246,   247,    79,    79,    51,    61,    58,   201,   202,   210,
      49,    62,   193,    64,    65,    66,    52,   198,    51,    50,
     264,    79,   203,   267,   268,    64,    65,    66,    48,    49,
      79,   275,   275,    79,   215,    48,    49,    79,   275,    69,
     221,   222,    52,   244,    64,    65,    66,   293,    64,    62,
      63,    64,    65,    66,    79,    79,    68,   301,   307,   260,
     304,   304,   243,    56,    61,    54,    61,   304,    79,    56,
     264,    52,   316,    22,    51,   319,    52,    39,    52,    64,
     261,    50,    61,    55,   328,    48,    49,   331,   331,   290,
      68,   335,    45,    46,   331,    48,    49,    50,   342,    62,
      63,    64,    65,    66,   348,    52,   287,    68,    71,    62,
      63,    64,    65,    66,   295,    50,    50,    70,    71,    72,
      79,    51,   316,    52,    29,   319,    52,    58,    56,   310,
      52,     4,     5,     6,     7,     8,    11,    10,    12,    13,
      14,   335,    16,    17,    18,    19,    20,    21,   342,    23,
      24,    35,    26,    27,   348,   336,    30,   207,   175,   290,
      34,    35,    36,   211,    38,    12,   181,    14,    15,    16,
      17,    18,    19,    20,    21,   215,    23,    24,   328,    26,
      27,    55,    -1,    30,    -1,    -1,    -1,    34,    35,    36,
      -1,    38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,
      -1,    -1,    -1,    -1,    -1,    79,    -1,    12,    55,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      -1,    26,    27,    -1,    -1,    30,    73,    -1,    -1,    34,
      35,    36,    79,    38,    12,    -1,    14,    -1,    16,    17,
      18,    19,    20,    21,    -1,    23,    24,    -1,    26,    27,
      55,    56,    30,    -1,    -1,    -1,    34,    35,    36,    -1,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    73,    -1,
      -1,    -1,    -1,    -1,    79,    -1,    12,    55,    14,    -1,
      16,    17,    18,    19,    20,    21,    -1,    23,    24,    -1,
      26,    27,    48,    49,    30,    73,    74,    -1,    34,    35,
      36,    79,    38,    -1,    22,    -1,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    71,    72,    -1,    -1,    55,
      -1,    -1,    -1,    -1,    32,    -1,    44,    45,    46,    -1,
      48,    49,    50,    41,    42,    43,    25,    73,    -1,    -1,
      48,    49,    -1,    79,    62,    63,    64,    65,    66,    -1,
      -1,    59,    70,    71,    72,    44,    45,    46,    -1,    48,
      49,    50,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    28,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    70,    71,    72,    -1,    -1,    31,    -1,    44,    45,
      46,    -1,    48,    49,    50,    -1,    -1,    -1,    -1,    44,
      45,    46,    -1,    48,    49,    50,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    71,    72,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,    40,    41,
      42,    43,    -1,    -1,    -1,    47,    48,    49,    -1,    51,
      -1,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,    40,
      41,    42,    43,    -1,    -1,    -1,    47,    48,    49,    -1,
      51,    52,    53,    75,    76,    77,    78,    79,    -1,    60,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    48,    49,
      -1,    51,    -1,    53,    75,    76,    77,    78,    79,    -1,
      60,    40,    41,    42,    43,    -1,    -1,    -1,    47,    48,
      49,    -1,    51,    -1,    53,    75,    76,    77,    78,    79,
      -1,    60,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      48,    49,    -1,    51,    -1,    53,    75,    76,    77,    78,
      79,    37,    60,    -1,    -1,    -1,    -1,    -1,    44,    45,
      46,    -1,    48,    49,    50,    -1,    -1,    75,    76,    77,
      78,    79,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    71,    72,    44,    45,    46,
      -1,    48,    49,    50,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    68,    -1,    70,    71,    72,    44,    45,    46,    -1,
      48,    49,    50,    -1,    52,    -1,    -1,    44,    45,    46,
      -1,    48,    49,    50,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    62,    63,    64,    65,    66,
      67,    -1,    -1,    70,    71,    72,    44,    45,    46,    -1,
      48,    49,    50,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    44,    45,    46,    -1,    48,
      49,    50,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    70,    71,    72,    44,    45,    46,    -1,    48,    49,
      50,    -1,    52,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      70,    71,    72,    44,    45,    46,    -1,    48,    49,    50,
      -1,    -1,    -1,    54,    44,    45,    46,    -1,    48,    49,
      50,    62,    63,    64,    65,    66,    -1,    -1,    -1,    70,
      71,    72,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      70,    71,    72,    45,    -1,    -1,    48,    49,    50,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    70,    71,
      72,    62,    63,    64,    65,    66,    48,    49,    -1,    70,
      71,    72,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    71,
      72
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,     3,    83,    84,     0,     4,     5,     6,     7,     8,
      10,    85,    86,    87,    88,    89,    90,    91,   121,    79,
      79,    79,    79,    79,    51,    79,    86,    11,    57,    50,
      51,    58,    50,     9,    50,    51,    79,    92,    93,    58,
      94,    55,    79,    40,    41,    42,    43,    47,    48,    49,
      51,    53,    60,    75,    76,    77,    78,    79,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   117,
     118,    52,    79,    95,    96,    97,    79,    99,    55,    51,
     122,   123,    12,    14,    16,    17,    18,    19,    20,    21,
      23,    24,    26,    27,    30,    34,    35,    36,    38,    55,
      73,    79,   118,   119,   120,   124,   126,   127,   128,   129,
     130,   131,   132,   133,   137,   138,   139,   141,   142,   145,
     146,   147,   148,    52,    96,    52,    61,    68,    98,    99,
      51,   101,   102,   103,   104,   117,    79,   117,    48,    49,
      51,   109,   110,   111,    48,    49,    51,    77,   109,   110,
     117,    54,   115,   116,   117,    79,    51,    44,    45,    46,
      48,    49,    50,    62,    63,    64,    65,    66,    70,    71,
      72,    50,    58,    58,    52,    61,    51,    50,    92,    92,
      50,    61,   119,   124,   125,   140,   140,   117,   117,   117,
      79,    79,   125,    51,    79,   117,   117,   117,    79,   117,
     118,   140,   140,    69,     9,    50,    52,    79,    79,    99,
      68,    64,   115,   117,    56,    61,    68,   117,   117,    52,
      54,    61,    67,    52,   115,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,    99,    99,    50,    58,    95,    48,    49,    99,   100,
     109,   117,    56,    52,   120,   123,    13,   125,    15,    50,
      58,    22,   117,    51,    28,    31,   117,    37,    39,    56,
      74,   117,   122,   120,     9,    50,    94,    99,    98,    52,
     103,   104,    52,    52,   117,   117,    52,    50,   117,    99,
      61,    52,    52,    67,    68,   143,    99,   117,    52,   115,
     125,    55,   118,   118,    50,   122,   120,    68,    54,   117,
      50,   100,   109,    79,   117,    50,    25,    51,    52,    29,
      32,    59,    78,   106,   107,   108,   118,   134,   135,   136,
     120,    50,   104,   117,    52,    22,   144,   125,   115,   125,
      56,   134,    58,   120,   125,   117,    52,   125,    22,   125
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    82,    83,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    86,    87,    88,    89,    90,    90,    90,    90,
      90,    90,    91,    91,    92,    92,    93,    93,    94,    94,
      95,    95,    96,    96,    97,    97,    98,    98,    98,    99,
      99,    99,    99,   100,   100,   100,   101,   101,   102,   102,
     103,   103,   103,   104,   104,   104,   104,   104,   105,   105,
     105,   105,   105,   105,   105,   105,   106,   107,   107,   108,
     108,   108,   109,   109,   109,   110,   110,   110,   111,   111,
     111,   112,   113,   114,   114,   115,   115,   116,   116,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   118,   118,   118,   119,   119,
     120,   120,   121,   121,   121,   121,   121,   121,   122,   122,
     123,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   125,   125,
     126,   127,   128,   128,   129,   130,   131,   132,   133,   134,
     134,   135,   136,   136,   136,   136,   136,   136,   136,   137,
     137,   137,   137,   138,   138,   139,   139,   140,   140,   141,
     141,   143,   142,   144,   142,   145,   146,   147,   148
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     1,     1,     1,     1,     5,
       1,     1,     1,     2,     5,     6,     7,     4,     6,     9,
       6,     8,     6,     3,     2,     1,     3,     1,     3,     4,
       3,     1,     1,     2,     3,     1,     3,     2,     1,     1,
       4,     4,     6,     3,     2,     1,     1,     2,     3,     1,
       1,     3,     5,     1,     1,     3,     4,     4,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     1,     2,     2,     1,     2,
       2,     2,     5,     3,     2,     1,     2,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     3,     4,     1,     1,
       1,     1,     4,     6,     7,     6,     8,     9,     3,     1,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     1,     1,     2,     3,     3,     6,     2,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     7,
       4,     5,     2,     3,     3,     3,     3,     2,     1,     4,
       6,     0,     7,     0,     9,     4,     4,     6,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"option\"", "\"derived\"", "\"enum\"", "\"rule\"", "\"dumps\"",
  "\"function\"", "\"initially\"", "\"seq\"", "\"endseq\"", "\"par\"",
  "\"endpar\"", "\"assert\"", "\"assure\"", "\"diedie\"", "\"impossible\"",
  "\"skip\"", "\"let\"", "\"in\"", "\"forall\"", "\"iterate\"", "\"do\"",
  "\"call\"", "\"if\"", "\"then\"", "\"else\"", "\"case\"", "\"of\"",
  "\"default\"", "\"endcase\"", "\"print\"", "\"debug\"", "\"push\"",
  "\"into\"", "\"pop\"", "\"from\"", "\"self\"", "\"undef\"", "\"false\"",
  "\"true\"", "\"and\"", "\"or\"", "\"xor\"", "\"not\"", "\"+\"", "\"-\"",
  "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\".\"",
  "\":\"", "\"_\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"",
  "\"%\"", "\"..\"", "\"->\"", "\":=\"", "\"!=\"", "\"<=\"", "\">=\"",
  "\"{|\"", "\"|}\"", "\"floating\"", "\"integer\"", "\"rational\"",
  "\"string\"", "\"identifier\"", "UPLUS", "UMINUS", "$accept",
  "SPECIFICATION", "HEADER", "BODY_ELEMENTS", "BODY_ELEMENT",
  "INIT_SYNTAX", "OPTION_SYNTAX", "ENUM_SYNTAX", "DERIVED_SYNTAX",
  "FUNCTION_DEFINITION", "IDENTIFIER_LIST", "IDENTIFIER_LIST_NO_COMMA",
  "FUNCTION_SIGNATURE", "PARAM", "PARAM_LIST", "PARAM_LIST_NO_COMMA",
  "TYPE_IDENTIFIER_STARLIST", "TYPE_SYNTAX", "TYPE_SYNTAX_LIST",
  "INITIALIZER_LIST", "INITIALIZER_LIST_NO_COMMA", "INITIALIZER", "ATOM",
  "VALUE", "UNDEFINED", "BOOLEAN", "NUMBER", "INTEGER_NUMBER",
  "FLOATING_NUMBER", "RATIONAL_NUMBER", "RULEREF", "NUMBER_RANGE",
  "LISTCONST", "EXPRESSION_LIST", "EXPRESSION_LIST_NO_COMMA", "EXPRESSION",
  "FUNCTION_SYNTAX", "SCOPE", "RULE_STMT", "RULE_SYNTAX", "DUMPSPEC_LIST",
  "DUMPSPEC", "SIMPLE_STMT", "STATEMENT", "ASSERT_SYNTAX", "ASSURE_SYNTAX",
  "DIEDIE_SYNTAX", "IMPOSSIBLE_SYNTAX", "PRINT_SYNTAX", "DEBUG_SYNTAX",
  "UPDATE_SYNTAX", "CASE_SYNTAX", "CASE_LABEL_LIST", "CASE_LABEL",
  "CASE_VALUE", "CALL_SYNTAX", "SEQ_SYNTAX", "PAR_SYNTAX", "STATEMENTS",
  "IFTHENELSE", "LET_SYNTAX", "$@1", "$@2", "PUSH_SYNTAX", "POP_SYNTAX",
  "FORALL_SYNTAX", "ITERATE_SYNTAX", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   342,   342,   350,   365,   370,   379,   383,   387,   408,
     437,   460,   464,   489,   525,   530,   577,   582,   586,   590,
     594,   598,   606,   612,   619,   623,   631,   636,   645,   651,
     659,   665,   676,   680,   688,   693,   701,   706,   711,   719,
     742,   755,   777,   795,   800,   804,   812,   816,   824,   829,
     837,   842,   850,   859,   863,   867,   871,   875,   884,   888,
     892,   896,   900,   904,   908,   912,   920,   928,   932,   940,
     944,   948,   956,   960,   964,   973,   977,   981,   990,   994,
     998,  1007,  1015,  1023,  1027,  1035,  1039,  1047,  1052,  1061,
    1065,  1069,  1073,  1077,  1081,  1085,  1089,  1093,  1097,  1101,
    1105,  1109,  1113,  1117,  1121,  1129,  1133,  1137,  1152,  1156,
    1164,  1168,  1178,  1182,  1186,  1190,  1195,  1200,  1209,  1214,
    1223,  1231,  1235,  1239,  1243,  1247,  1251,  1255,  1259,  1263,
    1267,  1271,  1275,  1279,  1283,  1287,  1291,  1295,  1315,  1319,
    1327,  1335,  1343,  1347,  1363,  1371,  1379,  1387,  1408,  1416,
    1421,  1430,  1438,  1442,  1447,  1451,  1455,  1459,  1463,  1471,
    1475,  1479,  1483,  1491,  1495,  1503,  1507,  1515,  1520,  1529,
    1533,  1543,  1542,  1560,  1559,  1580,  1595,  1618,  1628
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
#line 3642 "GrammarParser.cpp" // lalr1.cc:1167
#line 1634 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
