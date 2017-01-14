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

      case 101: // INITIALIZERS
      case 102: // INITIALIZER_LIST
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

      case 101: // INITIALIZERS
      case 102: // INITIALIZER_LIST
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

      case 101: // INITIALIZERS
      case 102: // INITIALIZER_LIST
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
      auto node = new FunctionDefNode( yylhs.location, yystack_[1].value.as< Function* > () );

      auto initializers = yystack_[0].value.as< std::vector<UpdateNode*> > ();
      for (auto initializer : initializers) {
          initializer->func->name = yystack_[1].value.as< Function* > ()->name;
      }
      node->setInitializers( initializers );

      try
      {
          driver.add( yystack_[1].value.as< Function* > () );
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
          delete yystack_[1].value.as< Function* > ();
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
      yylhs.value.as< std::vector<UpdateNode*> > () = yystack_[1].value.as< std::vector<UpdateNode*> > ();
  }
#line 1731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = {};
  }
#line 1739 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto initializers = std::move(yystack_[2].value.as< std::vector<UpdateNode*> > ());
      initializers.push_back( yystack_[0].value.as< UpdateNode* > () );
      yylhs.value.as< std::vector<UpdateNode*> > () = std::move(initializers);
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 831 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = yystack_[1].value.as< std::vector<UpdateNode*> > ();
  }
#line 1757 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 835 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<UpdateNode*> > () = { yystack_[0].value.as< UpdateNode* > () };
  }
#line 1765 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 843 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new FunctionAtom( yylhs.location, "" );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1774 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 848 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto args = new std::vector< ExpressionBase* >;
      args->push_back(yystack_[2].value.as< ExpressionBase* > ());

      auto function = new FunctionAtom( yylhs.location, "", args );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1786 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 856 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto function = new FunctionAtom( yylhs.location, "", yystack_[3].value.as< std::vector<ExpressionBase*>* > () );
      yylhs.value.as< UpdateNode* > () = new UpdateNode( yylhs.location, function, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1795 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 865 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 869 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1811 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 873 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1819 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 877 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1827 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 881 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, new ZeroAtom( yylhs.location, yystack_[1].value.as< ExpressionBase* > () ), yystack_[1].value.as< ExpressionBase* > (),
                                 libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 1836 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1844 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 894 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1852 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1860 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1868 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 910 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1884 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 914 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); 
  }
#line 1892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 926 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1908 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 934 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 1916 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 1924 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 946 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1932 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 950 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1940 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 954 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1948 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1956 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1964 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
      yystack_[0].value.as< IntegerAtom* > ()->val_ *= (-1);
  }
#line 1973 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 979 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1981 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 983 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1989 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 987 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
      yystack_[0].value.as< FloatingAtom* > ()->val_ *= (-1);
  }
#line 1998 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 996 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 2006 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 1000 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 2014 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 1004 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[0].value.as< rational_t > ().numerator *= -1;
      yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 1013 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 2031 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 1021 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new NumberRangeAtom( yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2039 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 1029 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2047 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 1033 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 2055 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 1041 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2063 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 1045 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 2071 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2080 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 1058 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
      yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2089 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 1067 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::ADD_INSTRUCTION );
  }
#line 2097 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 1071 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::SUB_INSTRUCTION );
  }
#line 2105 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1075 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::MUL_INSTRUCTION );
  }
#line 2113 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1079 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::DIV_INSTRUCTION );
  }
#line 2121 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1083 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::MOD_INSTRUCTION );
  }
#line 2129 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1087 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::NEQ_INSTRUCTION );
  }
#line 2137 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1091 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::EQU_INSTRUCTION );
  }
#line 2145 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::LTH_INSTRUCTION );
  }
#line 2153 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1099 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::GTH_INSTRUCTION );
  }
#line 2161 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1103 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::LEQ_INSTRUCTION );
  }
#line 2169 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1107 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::GEQ_INSTRUCTION );
  }
#line 2177 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1111 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::OR_INSTRUCTION );
  }
#line 2185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1115 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::XOR_INSTRUCTION );
  }
#line 2193 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1119 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new BinaryExpression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::AND_INSTRUCTION );
  }
#line 2201 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1123 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = new UnaryExpression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), libcasm_ir::Value::NOT_INSTRUCTION );
  }
#line 2209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1127 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1135 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2225 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1139 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2233 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2248 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1158 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2256 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1162 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2264 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1170 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2272 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1174 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      stmts->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1184 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1188 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2298 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1192 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1196 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1201 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2324 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1206 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      std::vector< Type* > tmp;
      yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2333 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2342 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1220 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
      yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2351 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1229 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1237 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1241 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1245 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1249 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1253 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1257 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1261 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1265 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1269 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2431 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1273 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2439 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1277 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2447 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1281 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2455 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1285 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1289 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2471 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1293 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2479 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1297 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1301 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.error
      ( yylhs.location
      , "invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
      , libcasm_fe::Codes::SyntaxErrorInvalidStatement
      );
  }
#line 2499 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1321 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2507 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1325 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2515 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1333 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2523 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1341 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1353 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1369 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1377 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2563 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1385 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[1].value.as< std::string > () );
  }
#line 2571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2592 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1414 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2600 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[0].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[1].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::vector< std::pair< AtomNode*, AstNode* > >();
      yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2618 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1436 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2626 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2634 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      // equivalent to 'default' 
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1453 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1457 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1461 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1465 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 2675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1469 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 2683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1477 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1481 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2699 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1485 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2723 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1501 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2739 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2747 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1521 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
      yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1526 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
      yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2765 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1535 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1539 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1548 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1560 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[5].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2806 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1565 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2822 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1577 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      driver.function_table.remove( yystack_[7].value.as< std::string > () );
      yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2831 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1586 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2846 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1601 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1624 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2885 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2889 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int Parser::yypact_ninf_ = -198;

  const signed char Parser::yytable_ninf_ = -107;

  const short int
  Parser::yypact_[] =
  {
      17,  -198,    29,   337,  -198,   -62,    -4,    -2,     2,    18,
     -10,   337,  -198,  -198,  -198,  -198,  -198,    25,  -198,  -198,
      11,   154,    37,    12,    27,    67,  -198,    90,  -198,    65,
     680,    20,    91,   124,   129,   474,    78,  -198,   131,   148,
      14,  -198,   598,   137,  -198,  -198,  -198,  -198,   680,    35,
      41,   680,   638,   147,  -198,  -198,  -198,  -198,   178,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
     940,  -198,   -26,   173,  -198,   183,   175,   186,   193,    27,
      27,    89,  -198,   474,   474,   680,   680,   680,  -198,  -198,
     161,   168,   474,    40,   680,   680,   680,   179,   680,   185,
     474,   474,    16,   180,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,  -198,  -198,     0,   200,   187,   194,    91,   206,
     201,   680,  -198,    82,  -198,   104,   773,  -198,  -198,   -30,
      56,   680,  -198,  -198,  -198,    80,    80,   680,  -198,  -198,
    -198,   802,  -198,   221,   215,   813,  -198,   659,   680,   680,
     680,   680,   680,   680,   680,   680,   680,   680,   680,   680,
     680,   680,   680,    91,    91,   108,   199,    -5,   680,   223,
     229,   474,   129,  -198,  -198,  -198,   336,   363,   940,   940,
     940,   170,   261,  -198,   680,   233,   554,   565,   940,   680,
     744,   248,   405,   432,   680,   129,   474,     6,    67,  -198,
    -198,    91,    91,   234,   802,  -198,   701,   722,   842,   871,
    -198,  -198,   680,   680,  -198,   236,   940,   257,   979,   968,
     -39,   149,   454,   190,   159,  -198,   225,   -42,   998,   197,
     247,   940,   241,  -198,   680,    91,  -198,    72,    72,   231,
     263,    21,   940,  -198,   232,  -198,  -198,  -198,  -198,  -198,
    -198,    91,   680,   900,   680,   474,   238,   940,   185,   185,
    -198,  -198,   940,   113,  -198,   129,   474,  -198,  -198,  -198,
     249,  -198,  -198,  -198,  -198,   940,   929,  -198,   680,   940,
     275,    91,  -198,  -198,    72,   251,   680,   276,   521,   280,
     281,   305,   502,  -198,  -198,   474,   123,  -198,   722,  -198,
     940,   680,  -198,   284,  -198,   -11,  -198,   474,   680,  -198,
     474,  -198,  -198,  -198,  -198,  -198,  -198,  -198,   282,   502,
     279,  -198,   474,  -198,   940,  -198,   474,   680,  -198,   288,
    -198,  -198,  -198,   474,  -198,  -198,   492,  -198,  -198,   474,
    -198
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     3,     0,     0,     1,     0,     0,     0,     0,     0,
       0,     2,     5,    11,     6,     7,    10,     8,    12,    13,
       0,     0,     0,     0,     0,     0,     4,     0,     9,     0,
       0,     0,     0,     0,     0,     0,     0,    27,     0,    25,
       0,    23,     0,     0,    64,    67,    69,    68,     0,     0,
       0,     0,     0,     0,    76,    73,    79,    61,   106,   105,
      55,    65,    66,    60,    70,    71,    72,    59,    63,    62,
      17,    54,     0,    31,    35,     0,    32,    39,     0,     0,
       0,     0,   120,     0,     0,     0,     0,   144,   145,   137,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   138,     0,   111,   113,   112,   122,   123,   124,
     125,   127,   126,   128,   129,   130,   109,   110,   131,   132,
     133,   134,   135,   136,     0,     0,     0,    24,     0,     0,
      38,     0,    47,     0,    50,   105,     0,    14,   104,     0,
       0,     0,    74,    77,    80,     0,     0,     0,    81,    75,
      78,     0,    85,     0,    86,    89,    82,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,   139,   140,   169,     0,     0,   141,   142,
     143,     0,     0,   179,     0,   163,     0,     0,   146,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    26,
      28,     0,    37,     0,    89,    46,    49,     0,     0,     0,
      56,    84,    87,     0,   107,     0,    89,   103,   101,   102,
      90,    91,    96,    97,    98,    92,    93,    94,    95,    99,
     100,    18,     0,    30,     0,     0,    34,     0,     0,    45,
       0,     0,    20,    15,     0,   116,   119,   165,   168,   167,
     172,     0,     0,     0,     0,     0,     0,   147,     0,     0,
     166,   164,   148,     0,   114,     0,     0,    22,    29,    36,
       0,    48,    52,    57,    58,    88,     0,   108,     0,    16,
       0,    44,    41,    40,     0,     0,     0,     0,     0,   161,
       0,   170,     0,   176,   177,     0,     0,   115,     0,    83,
      21,     0,    43,     0,   121,     0,   174,     0,     0,   162,
       0,   153,   154,   158,   155,   156,   157,   159,     0,   151,
       0,   117,     0,    53,    19,    42,     0,     0,   178,     0,
     171,   149,   150,     0,   118,   173,     0,   160,   152,     0,
     175
  };

  const short int
  Parser::yypgoto_[] =
  {
    -198,  -198,  -198,  -198,   335,  -198,  -198,  -198,  -198,  -198,
      62,  -198,   153,   191,   332,  -198,   157,     8,    85,  -198,
    -198,   169,   -40,  -198,  -168,  -167,  -165,   -37,   -45,   -43,
    -198,  -198,  -198,  -115,  -198,    28,   -35,   -34,  -178,  -198,
    -197,   210,   -28,    15,  -198,  -198,  -198,  -198,  -198,  -198,
    -198,  -198,    44,  -198,  -198,  -198,  -198,  -198,   -70,  -198,
    -198,  -198,  -198,  -198,  -198,  -198,  -198
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,    11,    12,    13,    14,    15,    16,    17,
      38,    39,    41,    74,    75,    76,   129,   130,   250,    28,
     133,   134,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,   153,   154,   226,    71,   183,   105,    18,
      81,    82,   184,   185,   107,   108,   109,   110,   111,   112,
     113,   114,   328,   329,   330,   115,   116,   117,   186,   118,
     119,   296,   337,   120,   121,   122,   123
  };

  const short int
  Parser::yytable_[] =
  {
     103,   104,   135,   255,   143,   150,   144,   106,   273,   205,
     162,   336,   142,   149,   187,   275,   213,    19,   139,   140,
       1,    34,   166,   167,   172,   166,   167,   168,   274,     4,
     202,   203,   173,   158,   159,   160,    27,   161,   162,   163,
      78,    24,   225,   247,   248,    54,    55,    56,   103,   103,
     206,   164,   165,   166,   167,   168,   276,   103,    70,   169,
     170,   171,    35,    36,   201,   103,   103,   157,    29,    25,
     136,    55,    72,   293,    77,    20,   138,    21,   306,   151,
     155,    22,   128,   139,   140,  -106,   141,    33,   294,   145,
     146,   194,   147,    77,   143,   150,   144,    23,   307,    73,
     143,   150,   142,   149,   145,   146,    37,   193,   142,   149,
      54,    55,    56,   188,   189,   190,    54,    55,   148,   195,
     247,   248,   196,   197,   198,    40,   200,   331,   145,   146,
     124,    54,    55,   148,   324,   325,   210,   326,   215,   181,
     251,   179,   180,   216,    43,    42,   103,   104,    55,   300,
     182,   103,   103,   106,   344,    54,    55,    73,   244,   214,
     -51,   324,   325,   305,   326,   -51,   245,   103,   103,   218,
      77,   103,   104,   332,   182,   219,   135,   282,   106,    79,
      80,   242,   243,   126,   182,   249,   227,   228,   229,   230,
     231,   232,   233,   234,   235,   236,   237,   238,   239,   240,
     241,   258,   258,   339,    30,    31,   252,   161,   162,   127,
     142,   149,    32,   166,   167,   168,   137,   258,   258,   278,
     260,   164,   263,   166,   167,   168,   156,   267,   261,   157,
     103,   174,   272,   303,   304,   175,   176,   177,   161,   162,
     191,   103,   104,   178,   136,   161,   162,   192,   106,   204,
     285,   286,   207,   290,   166,   167,   168,   313,   199,   164,
     165,   166,   167,   168,    58,   212,   208,   327,   333,   297,
     103,   104,   289,   209,   211,   221,   222,   106,    73,   253,
     301,   254,   103,   262,   264,   103,   280,   269,   287,   166,
     298,   288,   291,   302,   327,   161,   162,   103,   104,   249,
     295,   103,   159,   160,   106,   161,   162,   163,   103,   164,
     165,   166,   167,   168,   103,   292,   310,   308,   170,   164,
     165,   166,   167,   168,   315,   311,   316,   169,   170,   171,
     314,   318,   338,   319,   320,   340,   335,   343,   341,   334,
     347,     5,     6,     7,     8,     9,    26,    10,    83,   257,
      84,   345,    85,    86,    87,    88,    89,    90,   348,    91,
      92,   277,    93,    94,   350,   346,    95,   246,   125,   279,
      96,    97,    98,   342,    99,    83,   312,    84,   259,    85,
      86,    87,    88,    89,    90,   281,    91,    92,     0,    93,
      94,   100,   256,    95,     0,     0,     0,    96,    97,    98,
       0,    99,     0,     0,     0,     0,     0,     0,     0,   101,
       0,     0,     0,     0,     0,   102,     0,    83,   100,    84,
       0,    85,    86,    87,    88,    89,    90,     0,    91,    92,
       0,    93,    94,     0,     0,    95,   101,     0,     0,    96,
      97,    98,   102,    99,    83,     0,    84,     0,    85,    86,
      87,    88,    89,    90,     0,    91,    92,     0,    93,    94,
     100,   270,    95,     0,     0,     0,    96,    97,    98,     0,
      99,     0,     0,     0,     0,     0,     0,     0,   101,     0,
       0,     0,     0,     0,   102,     0,    83,   100,    84,     0,
      85,    86,    87,    88,    89,    90,     0,    91,    92,     0,
      93,    94,   161,   162,    95,   101,   271,     0,    96,    97,
      98,   102,    99,     0,   349,     0,   164,   165,   166,   167,
     168,     0,     0,     0,   169,   170,   171,     0,     0,   100,
       0,     0,     0,     0,   321,     0,   158,   159,   160,     0,
     161,   162,   163,    45,    46,    47,   317,   101,     0,     0,
     139,   140,     0,   102,   164,   165,   166,   167,   168,     0,
       0,   322,   169,   170,   171,   158,   159,   160,     0,   161,
     162,   163,     0,     0,     0,     0,     0,    54,    55,    56,
     323,    58,   265,   164,   165,   166,   167,   168,     0,     0,
       0,   169,   170,   171,     0,     0,   266,     0,   158,   159,
     160,     0,   161,   162,   163,     0,     0,     0,     0,   158,
     159,   160,     0,   161,   162,   163,   164,   165,   166,   167,
     168,     0,     0,     0,   169,   170,   171,   164,   165,   166,
     167,   168,     0,     0,     0,   169,   170,   171,    44,    45,
      46,    47,     0,     0,     0,    48,    49,    50,     0,   131,
       0,    52,     0,     0,   132,     0,     0,     0,    53,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    55,    56,    57,    58,    44,    45,
      46,    47,     0,     0,     0,    48,    49,    50,     0,    51,
       0,    52,   152,     0,     0,     0,     0,     0,    53,    44,
      45,    46,    47,     0,     0,     0,    48,    49,    50,     0,
      51,   224,    52,    54,    55,    56,    57,    58,     0,    53,
      44,    45,    46,    47,     0,     0,     0,    48,    49,    50,
       0,    51,     0,    52,    54,    55,    56,    57,    58,     0,
      53,    44,    45,    46,    47,     0,     0,     0,    48,    49,
      50,     0,   131,     0,    52,    54,    55,    56,    57,    58,
       0,    53,    44,    45,    46,    47,     0,     0,     0,     0,
      49,    50,     0,    51,     0,    52,    54,    55,    56,    57,
      58,   268,    53,     0,     0,     0,     0,     0,   158,   159,
     160,     0,   161,   162,   163,     0,     0,    54,    55,    56,
      57,    58,     0,     0,     0,     0,   164,   165,   166,   167,
     168,     0,     0,     0,   169,   170,   171,   158,   159,   160,
       0,   161,   162,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   164,   165,   166,   167,   168,
       0,   217,     0,   169,   170,   171,   158,   159,   160,     0,
     161,   162,   163,     0,   220,     0,     0,   158,   159,   160,
       0,   161,   162,   163,   164,   165,   166,   167,   168,     0,
       0,     0,   169,   170,   171,   164,   165,   166,   167,   168,
     223,     0,     0,   169,   170,   171,   158,   159,   160,     0,
     161,   162,   163,     0,   283,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,     0,
       0,     0,   169,   170,   171,   158,   159,   160,     0,   161,
     162,   163,     0,   284,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   164,   165,   166,   167,   168,     0,     0,
       0,   169,   170,   171,   158,   159,   160,     0,   161,   162,
     163,     0,   299,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   164,   165,   166,   167,   168,     0,     0,     0,
     169,   170,   171,   158,   159,   160,     0,   161,   162,   163,
       0,     0,     0,   309,   158,   159,   160,     0,   161,   162,
     163,   164,   165,   166,   167,   168,     0,     0,     0,   169,
     170,   171,   164,   165,   166,   167,   168,     0,     0,     0,
     169,   170,   171,   159,     0,     0,   161,   162,   163,     0,
       0,     0,     0,     0,     0,     0,     0,   161,   162,   163,
     164,   165,   166,   167,   168,     0,     0,     0,   169,   170,
     171,   164,   165,   166,   167,   168,   161,   162,     0,   169,
     170,   171,     0,     0,     0,     0,     0,     0,     0,     0,
     164,   165,   166,   167,   168,     0,     0,     0,     0,   170,
     171
  };

  const short int
  Parser::yycheck_[] =
  {
      35,    35,    42,   181,    49,    50,    49,    35,   205,     9,
      49,    22,    49,    50,    84,     9,   131,    79,    48,    49,
       3,     9,    64,    65,    50,    64,    65,    66,   206,     0,
     100,   101,    58,    44,    45,    46,    11,    48,    49,    50,
      32,    51,   157,    48,    49,    75,    76,    77,    83,    84,
      50,    62,    63,    64,    65,    66,    50,    92,    30,    70,
      71,    72,    50,    51,    99,   100,   101,    51,    57,    79,
      42,    76,    52,    52,    79,    79,    48,    79,   275,    51,
      52,    79,    68,    48,    49,    69,    51,    50,    67,    48,
      49,    51,    51,    79,   139,   140,   139,    79,   276,    79,
     145,   146,   139,   140,    48,    49,    79,    92,   145,   146,
      75,    76,    77,    85,    86,    87,    75,    76,    77,    79,
      48,    49,    94,    95,    96,    58,    98,   305,    48,    49,
      52,    75,    76,    77,   302,   302,   128,   302,    56,    50,
     177,    79,    80,    61,    79,    55,   181,   181,    76,   264,
      61,   186,   187,   181,   332,    75,    76,    79,    50,   131,
      56,   329,   329,    50,   329,    61,    58,   202,   203,   141,
      79,   206,   206,    50,    61,   147,   216,   217,   206,    55,
      51,   173,   174,    52,    61,   177,   158,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   186,   187,   318,    50,    51,   178,    48,    49,    61,
     247,   248,    58,    64,    65,    66,    79,   202,   203,   211,
      50,    62,   194,    64,    65,    66,    79,   199,    58,    51,
     265,    58,   204,   268,   269,    52,    61,    51,    48,    49,
      79,   276,   276,    50,   216,    48,    49,    79,   276,    69,
     222,   223,    52,   245,    64,    65,    66,   294,    79,    62,
      63,    64,    65,    66,    79,    64,    79,   302,   308,   261,
     305,   305,   244,    79,    68,    54,    61,   305,    79,    56,
     265,    52,   317,    22,    51,   320,    52,    39,    52,    64,
     262,    50,    61,    55,   329,    48,    49,   332,   332,   291,
      68,   336,    45,    46,   332,    48,    49,    50,   343,    62,
      63,    64,    65,    66,   349,    52,   288,    68,    71,    62,
      63,    64,    65,    66,   296,    50,    50,    70,    71,    72,
      79,    51,   317,    52,    29,   320,    52,    58,    56,   311,
      52,     4,     5,     6,     7,     8,    11,    10,    12,    13,
      14,   336,    16,    17,    18,    19,    20,    21,   343,    23,
      24,   208,    26,    27,   349,   337,    30,   176,    36,   212,
      34,    35,    36,   329,    38,    12,   291,    14,    15,    16,
      17,    18,    19,    20,    21,   216,    23,    24,    -1,    26,
      27,    55,   182,    30,    -1,    -1,    -1,    34,    35,    36,
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
      -1,    53,    -1,    -1,    56,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    40,    41,
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
      79,    79,    79,    79,    51,    79,    86,    11,   101,    57,
      50,    51,    58,    50,     9,    50,    51,    79,    92,    93,
      58,    94,    55,    79,    40,    41,    42,    43,    47,    48,
      49,    51,    53,    60,    75,    76,    77,    78,    79,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     117,   118,    52,    79,    95,    96,    97,    79,    99,    55,
      51,   122,   123,    12,    14,    16,    17,    18,    19,    20,
      21,    23,    24,    26,    27,    30,    34,    35,    36,    38,
      55,    73,    79,   118,   119,   120,   124,   126,   127,   128,
     129,   130,   131,   132,   133,   137,   138,   139,   141,   142,
     145,   146,   147,   148,    52,    96,    52,    61,    68,    98,
      99,    51,    56,   102,   103,   104,   117,    79,   117,    48,
      49,    51,   109,   110,   111,    48,    49,    51,    77,   109,
     110,   117,    54,   115,   116,   117,    79,    51,    44,    45,
      46,    48,    49,    50,    62,    63,    64,    65,    66,    70,
      71,    72,    50,    58,    58,    52,    61,    51,    50,    92,
      92,    50,    61,   119,   124,   125,   140,   140,   117,   117,
     117,    79,    79,   125,    51,    79,   117,   117,   117,    79,
     117,   118,   140,   140,    69,     9,    50,    52,    79,    79,
      99,    68,    64,   115,   117,    56,    61,    68,   117,   117,
      52,    54,    61,    67,    52,   115,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,    99,    99,    50,    58,    95,    48,    49,    99,
     100,   109,   117,    56,    52,   120,   123,    13,   125,    15,
      50,    58,    22,   117,    51,    28,    31,   117,    37,    39,
      56,    74,   117,   122,   120,     9,    50,    94,    99,    98,
      52,   103,   104,    52,    52,   117,   117,    52,    50,   117,
      99,    61,    52,    52,    67,    68,   143,    99,   117,    52,
     115,   125,    55,   118,   118,    50,   122,   120,    68,    54,
     117,    50,   100,   109,    79,   117,    50,    25,    51,    52,
      29,    32,    59,    78,   106,   107,   108,   118,   134,   135,
     136,   120,    50,   104,   117,    52,    22,   144,   125,   115,
     125,    56,   134,    58,   120,   125,   117,    52,   125,    22,
     125
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    82,    83,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    86,    87,    88,    89,    90,    90,    90,    90,
      90,    90,    91,    91,    92,    92,    93,    93,    94,    94,
      95,    95,    96,    96,    97,    97,    98,    98,    98,    99,
      99,    99,    99,   100,   100,   100,   101,   101,   102,   102,
     102,   103,   103,   103,   104,   104,   104,   104,   104,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   107,   107,
     108,   108,   108,   109,   109,   109,   110,   110,   110,   111,
     111,   111,   112,   113,   114,   114,   115,   115,   116,   116,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   118,   118,   118,   119,
     119,   120,   120,   121,   121,   121,   121,   121,   121,   122,
     122,   123,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   125,
     125,   126,   127,   128,   128,   129,   130,   131,   132,   133,
     134,   134,   135,   136,   136,   136,   136,   136,   136,   136,
     137,   137,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   143,   142,   144,   142,   145,   146,   147,   148
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,     1,     2,     1,     1,     1,     1,     2,
       1,     1,     1,     2,     5,     6,     7,     4,     6,     9,
       6,     8,     6,     3,     2,     1,     3,     1,     3,     4,
       3,     1,     1,     2,     3,     1,     3,     2,     1,     1,
       4,     4,     6,     3,     2,     1,     4,     3,     3,     2,
       1,     1,     3,     5,     1,     1,     3,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     2,     5,     3,     2,     1,     2,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     1,     3,     4,     1,
       1,     1,     1,     4,     6,     7,     6,     8,     9,     3,
       1,     5,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     1,     1,     2,     3,     3,     6,
       2,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       7,     4,     5,     2,     3,     3,     3,     3,     2,     1,
       4,     6,     0,     7,     0,     9,     4,     4,     6,     2
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
  "INITIALIZERS", "INITIALIZER_LIST", "INITIALIZER", "ATOM", "VALUE",
  "UNDEFINED", "BOOLEAN", "NUMBER", "INTEGER_NUMBER", "FLOATING_NUMBER",
  "RATIONAL_NUMBER", "RULEREF", "NUMBER_RANGE", "LISTCONST",
  "EXPRESSION_LIST", "EXPRESSION_LIST_NO_COMMA", "EXPRESSION",
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
     742,   755,   777,   795,   800,   804,   812,   816,   824,   830,
     834,   842,   847,   855,   864,   868,   872,   876,   880,   889,
     893,   897,   901,   905,   909,   913,   917,   925,   933,   937,
     945,   949,   953,   961,   965,   969,   978,   982,   986,   995,
     999,  1003,  1012,  1020,  1028,  1032,  1040,  1044,  1052,  1057,
    1066,  1070,  1074,  1078,  1082,  1086,  1090,  1094,  1098,  1102,
    1106,  1110,  1114,  1118,  1122,  1126,  1134,  1138,  1142,  1157,
    1161,  1169,  1173,  1183,  1187,  1191,  1195,  1200,  1205,  1214,
    1219,  1228,  1236,  1240,  1244,  1248,  1252,  1256,  1260,  1264,
    1268,  1272,  1276,  1280,  1284,  1288,  1292,  1296,  1300,  1320,
    1324,  1332,  1340,  1348,  1352,  1368,  1376,  1384,  1392,  1413,
    1421,  1426,  1435,  1443,  1447,  1452,  1456,  1460,  1464,  1468,
    1476,  1480,  1484,  1488,  1496,  1500,  1508,  1512,  1520,  1525,
    1534,  1538,  1548,  1547,  1565,  1564,  1585,  1600,  1623,  1633
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
#line 3662 "GrammarParser.cpp" // lalr1.cc:1167
#line 1639 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
