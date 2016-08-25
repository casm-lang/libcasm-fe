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
#line 64 "../../obj/src/GrammarParser.yy" // lalr1.cc:413

    #include "src/Driver.h"
    #include "src/Codes.h"

    std::pair<bool, bool> parse_function_attributes
    ( Driver& driver
    , const yy::location& loc
    , const std::vector<std::string>& attribute_names
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
		
        return std::pair<bool, bool>(is_static, is_symbolic);
    }

#line 139 "GrammarParser.cpp" // lalr1.cc:413


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
#line 225 "GrammarParser.cpp" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  casmi_parser::yytnamerr_ (const char *yystr)
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
  casmi_parser::casmi_parser (Driver& driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  casmi_parser::~casmi_parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  casmi_parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  casmi_parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  casmi_parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  casmi_parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  casmi_parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  casmi_parser::symbol_number_type
  casmi_parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  casmi_parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  casmi_parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 81: // SPECIFICATION
        value.move< Ast* > (that.value);
        break;

      case 83: // BODY_ELEMENTS
      case 138: // STATEMENTS
        value.move< AstListNode* > (that.value);
        break;

      case 84: // BODY_ELEMENT
      case 115: // RULE_STMT
      case 116: // RULE_SYNTAX
      case 119: // SIMPLE_STMT
      case 120: // STATEMENT
      case 124: // IMPOSSIBLE_SYNTAX
        value.move< AstNode* > (that.value);
        break;

      case 103: // VALUE
      case 104: // NUMBER
      case 109: // NUMBER_RANGE
        value.move< AtomNode* > (that.value);
        break;

      case 114: // FUNCTION_SYNTAX
        value.move< BaseFunctionAtom* > (that.value);
        break;

      case 135: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 128: // CASE_SYNTAX
        value.move< CaseNode* > (that.value);
        break;

      case 123: // DIEDIE_SYNTAX
        value.move< DiedieNode* > (that.value);
        break;

      case 87: // ENUM_SYNTAX
        value.move< Enum* > (that.value);
        break;

      case 102: // ATOM
      case 113: // EXPRESSION
        value.move< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.move< FLOATING_T > (that.value);
        break;

      case 106: // FLOATING_NUMBER
        value.move< FloatingAtom* > (that.value);
        break;

      case 145: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 76: // "integer"
        value.move< INTEGER_T > (that.value);
        break;

      case 139: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 85: // INIT_SYNTAX
        value.move< InitNode* > (that.value);
        break;

      case 105: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 140: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 144: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 125: // PRINT_SYNTAX
      case 126: // DEBUG_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 143: // PUSH_SYNTAX
        value.move< PushNode* > (that.value);
        break;

      case 107: // RATIONAL_NUMBER
        value.move< RationalAtom* > (that.value);
        break;

      case 82: // HEADER
        value.move< SpecificationNode* > (that.value);
        break;

      case 93: // PARAM
      case 97: // TYPE_SYNTAX
        value.move< Type* > (that.value);
        break;

      case 121: // ASSERT_SYNTAX
      case 122: // ASSURE_SYNTAX
      case 136: // SEQ_SYNTAX
      case 137: // PAR_SYNTAX
      case 146: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 127: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.move< rational_t > (that.value);
        break;

      case 130: // CASE_LABEL
      case 131: // CASE_LABEL_DEFAULT
      case 132: // CASE_LABEL_NUMBER
      case 133: // CASE_LABEL_IDENT
      case 134: // CASE_LABEL_STRING
        value.move< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 101: // INITIALIZER
        value.move< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 118: // DUMPSPEC
        value.move< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 92: // FUNCTION_SIGNATURE
        value.move< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 108: // RULEREF
        value.move< std::string > (that.value);
        break;

      case 110: // LISTCONST
      case 111: // EXPRESSION_LIST
      case 112: // EXPRESSION_LIST_NO_COMMA
        value.move< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 94: // PARAM_LIST
      case 95: // PARAM_LIST_NO_COMMA
      case 96: // TYPE_IDENTIFIER_STARLIST
      case 98: // TYPE_SYNTAX_LIST
        value.move< std::vector<Type*> > (that.value);
        break;

      case 129: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 99: // INITIALIZERS
      case 100: // INITIALIZER_LIST
        value.move< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 117: // DUMPSPEC_LIST
        value.move< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 90: // IDENTIFIER_LIST
      case 91: // IDENTIFIER_LIST_NO_COMMA
        value.move< std::vector<std::string> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  casmi_parser::stack_symbol_type&
  casmi_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 81: // SPECIFICATION
        value.copy< Ast* > (that.value);
        break;

      case 83: // BODY_ELEMENTS
      case 138: // STATEMENTS
        value.copy< AstListNode* > (that.value);
        break;

      case 84: // BODY_ELEMENT
      case 115: // RULE_STMT
      case 116: // RULE_SYNTAX
      case 119: // SIMPLE_STMT
      case 120: // STATEMENT
      case 124: // IMPOSSIBLE_SYNTAX
        value.copy< AstNode* > (that.value);
        break;

      case 103: // VALUE
      case 104: // NUMBER
      case 109: // NUMBER_RANGE
        value.copy< AtomNode* > (that.value);
        break;

      case 114: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (that.value);
        break;

      case 135: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 128: // CASE_SYNTAX
        value.copy< CaseNode* > (that.value);
        break;

      case 123: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (that.value);
        break;

      case 87: // ENUM_SYNTAX
        value.copy< Enum* > (that.value);
        break;

      case 102: // ATOM
      case 113: // EXPRESSION
        value.copy< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.copy< FLOATING_T > (that.value);
        break;

      case 106: // FLOATING_NUMBER
        value.copy< FloatingAtom* > (that.value);
        break;

      case 145: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 76: // "integer"
        value.copy< INTEGER_T > (that.value);
        break;

      case 139: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 85: // INIT_SYNTAX
        value.copy< InitNode* > (that.value);
        break;

      case 105: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 140: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 144: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 125: // PRINT_SYNTAX
      case 126: // DEBUG_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 143: // PUSH_SYNTAX
        value.copy< PushNode* > (that.value);
        break;

      case 107: // RATIONAL_NUMBER
        value.copy< RationalAtom* > (that.value);
        break;

      case 82: // HEADER
        value.copy< SpecificationNode* > (that.value);
        break;

      case 93: // PARAM
      case 97: // TYPE_SYNTAX
        value.copy< Type* > (that.value);
        break;

      case 121: // ASSERT_SYNTAX
      case 122: // ASSURE_SYNTAX
      case 136: // SEQ_SYNTAX
      case 137: // PAR_SYNTAX
      case 146: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 127: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.copy< rational_t > (that.value);
        break;

      case 130: // CASE_LABEL
      case 131: // CASE_LABEL_DEFAULT
      case 132: // CASE_LABEL_NUMBER
      case 133: // CASE_LABEL_IDENT
      case 134: // CASE_LABEL_STRING
        value.copy< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 101: // INITIALIZER
        value.copy< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 118: // DUMPSPEC
        value.copy< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 92: // FUNCTION_SIGNATURE
        value.copy< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 108: // RULEREF
        value.copy< std::string > (that.value);
        break;

      case 110: // LISTCONST
      case 111: // EXPRESSION_LIST
      case 112: // EXPRESSION_LIST_NO_COMMA
        value.copy< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 94: // PARAM_LIST
      case 95: // PARAM_LIST_NO_COMMA
      case 96: // TYPE_IDENTIFIER_STARLIST
      case 98: // TYPE_SYNTAX_LIST
        value.copy< std::vector<Type*> > (that.value);
        break;

      case 129: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 99: // INITIALIZERS
      case 100: // INITIALIZER_LIST
        value.copy< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 117: // DUMPSPEC_LIST
        value.copy< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 90: // IDENTIFIER_LIST
      case 91: // IDENTIFIER_LIST_NO_COMMA
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
  casmi_parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  casmi_parser::yy_print_ (std::ostream& yyo,
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
  casmi_parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  casmi_parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  casmi_parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  casmi_parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  casmi_parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  casmi_parser::debug_level_type
  casmi_parser::debug_level () const
  {
    return yydebug_;
  }

  void
  casmi_parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline casmi_parser::state_type
  casmi_parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  casmi_parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  casmi_parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  casmi_parser::parse ()
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
    #line 53 "../../obj/src/GrammarParser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
}

#line 871 "GrammarParser.cpp" // lalr1.cc:741

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
      case 81: // SPECIFICATION
        yylhs.value.build< Ast* > ();
        break;

      case 83: // BODY_ELEMENTS
      case 138: // STATEMENTS
        yylhs.value.build< AstListNode* > ();
        break;

      case 84: // BODY_ELEMENT
      case 115: // RULE_STMT
      case 116: // RULE_SYNTAX
      case 119: // SIMPLE_STMT
      case 120: // STATEMENT
      case 124: // IMPOSSIBLE_SYNTAX
        yylhs.value.build< AstNode* > ();
        break;

      case 103: // VALUE
      case 104: // NUMBER
      case 109: // NUMBER_RANGE
        yylhs.value.build< AtomNode* > ();
        break;

      case 114: // FUNCTION_SYNTAX
        yylhs.value.build< BaseFunctionAtom* > ();
        break;

      case 135: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 128: // CASE_SYNTAX
        yylhs.value.build< CaseNode* > ();
        break;

      case 123: // DIEDIE_SYNTAX
        yylhs.value.build< DiedieNode* > ();
        break;

      case 87: // ENUM_SYNTAX
        yylhs.value.build< Enum* > ();
        break;

      case 102: // ATOM
      case 113: // EXPRESSION
        yylhs.value.build< ExpressionBase* > ();
        break;

      case 75: // "floating"
        yylhs.value.build< FLOATING_T > ();
        break;

      case 106: // FLOATING_NUMBER
        yylhs.value.build< FloatingAtom* > ();
        break;

      case 145: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 76: // "integer"
        yylhs.value.build< INTEGER_T > ();
        break;

      case 139: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 85: // INIT_SYNTAX
        yylhs.value.build< InitNode* > ();
        break;

      case 105: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 140: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 144: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 125: // PRINT_SYNTAX
      case 126: // DEBUG_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 143: // PUSH_SYNTAX
        yylhs.value.build< PushNode* > ();
        break;

      case 107: // RATIONAL_NUMBER
        yylhs.value.build< RationalAtom* > ();
        break;

      case 82: // HEADER
        yylhs.value.build< SpecificationNode* > ();
        break;

      case 93: // PARAM
      case 97: // TYPE_SYNTAX
        yylhs.value.build< Type* > ();
        break;

      case 121: // ASSERT_SYNTAX
      case 122: // ASSURE_SYNTAX
      case 136: // SEQ_SYNTAX
      case 137: // PAR_SYNTAX
      case 146: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 127: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 77: // "rational"
        yylhs.value.build< rational_t > ();
        break;

      case 130: // CASE_LABEL
      case 131: // CASE_LABEL_DEFAULT
      case 132: // CASE_LABEL_NUMBER
      case 133: // CASE_LABEL_IDENT
      case 134: // CASE_LABEL_STRING
        yylhs.value.build< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 101: // INITIALIZER
        yylhs.value.build< std::pair<ExpressionBase*, ExpressionBase*> > ();
        break;

      case 118: // DUMPSPEC
        yylhs.value.build< std::pair<std::string, std::vector<std::string>> > ();
        break;

      case 92: // FUNCTION_SIGNATURE
        yylhs.value.build< std::pair<std::vector<Type*>, Type*> > ();
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 108: // RULEREF
        yylhs.value.build< std::string > ();
        break;

      case 110: // LISTCONST
      case 111: // EXPRESSION_LIST
      case 112: // EXPRESSION_LIST_NO_COMMA
        yylhs.value.build< std::vector<ExpressionBase*>* > ();
        break;

      case 94: // PARAM_LIST
      case 95: // PARAM_LIST_NO_COMMA
      case 96: // TYPE_IDENTIFIER_STARLIST
      case 98: // TYPE_SYNTAX_LIST
        yylhs.value.build< std::vector<Type*> > ();
        break;

      case 129: // CASE_LABEL_LIST
        yylhs.value.build< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 99: // INITIALIZERS
      case 100: // INITIALIZER_LIST
        yylhs.value.build< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
        break;

      case 117: // DUMPSPEC_LIST
        yylhs.value.build< std::vector<std::pair<std::string, std::vector<std::string>>> > ();
        break;

      case 90: // IDENTIFIER_LIST
      case 91: // IDENTIFIER_LIST_NO_COMMA
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
#line 333 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
  }
#line 1168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 341 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 348 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
	  yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 1185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 353 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
	  yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
  }
#line 1194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 362 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode(NodeType::OPTION);
  }
#line 1202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new EnumDefNode(yylhs.location, yystack_[0].value.as< Enum* > ());
  }
#line 1210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new FunctionDefNode(yylhs.location, yystack_[0].value.as< Function* > ());
	  
	  if( yystack_[0].value.as< Function* > ()->is_builtin() )
	  {
		  driver.error(yylhs.location, "cannot use `"+yystack_[0].value.as< Function* > ()->name+"` as function identifier because it is a builtin name");
	  }
	  try
	  {
		  driver.add(yystack_[0].value.as< Function* > ());
	  }
	  catch( const IdentifierAlreadyUsed& e )
	  {
		  driver.error(yylhs.location, e.what());
		  // if another symbol with same name exists we need to delete
		  // the symbol here, because it is not inserted in the symbol table
		  delete yystack_[0].value.as< Function* > ();
	  }
  }
#line 1234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< Function* > ()->binding_offsets = std::move(driver.binding_offsets);
	  driver.binding_offsets.clear();
	  yylhs.value.as< AstNode* > () = new FunctionDefNode(yylhs.location, yystack_[0].value.as< Function* > ());
	  try
	  {
		  driver.add(yystack_[0].value.as< Function* > ());
	  }
	  catch( const IdentifierAlreadyUsed& e )
	  {
		  driver.error(yylhs.location, e.what());
		  // if another symbol with same name exists we need to delete
		  // the symbol here, because it is not inserted in the symbol table
		  delete yystack_[0].value.as< Function* > ();
	  }
  }
#line 1255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > ();
  }
#line 1263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 411 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
	  // TODO check, we trust bison to pass only RuleNodes up
	  try
	  {
		  driver.add(reinterpret_cast<RuleNode*>(yystack_[0].value.as< AstNode* > ()));
	  }
	  catch( const IdentifierAlreadyUsed& e )
	  {
		  driver.error( yylhs.location, e.what() );
		  // we do not need to delete $1 here, because it's already in
		  // the AST, so it will be deleted later
	  }
  }
#line 1282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Enum* > () = new Enum(yystack_[4].value.as< std::string > (), yylhs.location);
	  try
	  {
		  driver.function_table.add(yylhs.value.as< Enum* > ());
	  }
	  catch( const SymbolAlreadyExists& e )
	  {
		  driver.error( yylhs.location, e.what() );
	  }
	  for( const std::string& name : yystack_[1].value.as< std::vector<std::string> > () )
	  {
		  if( yylhs.value.as< Enum* > ()->add_enum_element(name) )
		  {
			  try
			  {
				  driver.function_table.add_enum_element( name, yylhs.value.as< Enum* > () );
			  }
			  catch( const SymbolAlreadyExists& e )
			  {
				  driver.error( yylhs.location, e.what() );
			  }
		  }
		  else
		  {
			  driver.error( yylhs.location, "name `"+name+"` already used in enum" );
		  }
	  }
  }
#line 1324 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 477 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  // TODO: 2nd argument should be a reference
	  yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1333 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 482 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 486 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 490 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 498 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 506 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[4].value.as< std::vector<std::string> > ());
	  yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 511 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > ());
	  yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 516 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 520 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 527 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
  }
#line 1415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 531 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ());
  }
#line 1423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 539 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move( yystack_[2].value.as< std::vector<std::string> > () );
	  yylhs.value.as< std::vector<std::string> > ().push_back( yystack_[0].value.as< std::string > () );
  }
#line 1432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 544 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
	  yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
  }
#line 1441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 553 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  /* this constructor is implementation dependant! */
	  std::vector<Type*> foo;
	  yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
  }
#line 1451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 559 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ());
  }
#line 1459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 567 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  size_t size = driver.binding_offsets.size();
	  driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
	  yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
  }
#line 1469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 573 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  size_t size = driver.binding_offsets.size();
	  driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
	  // TODO: fail for rules without types and print warnings
	  yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
  }
#line 1480 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 584 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1488 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 588 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ());
  }
#line 1496 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 596 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 601 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 609 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1522 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 614 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  // TODO: limit memory size
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
  }
#line 1531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 619 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 627 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1566 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 650 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 663 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 685 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 703 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< std::vector<Type*> > ().push_back( yystack_[2].value.as< Type* > () );
	  yylhs.value.as< std::vector<Type*> > () = std::move( yystack_[0].value.as< std::vector<Type*> > () );
  }
#line 1636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 708 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[1].value.as< Type* > () );
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 712 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[0].value.as< Type* > () );
  }
#line 1652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 720 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 724 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = nullptr;
  }
#line 1668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 732 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 736 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 740 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = new std::vector< std::pair<ExpressionBase*, ExpressionBase* > >();
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1693 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 749 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1701 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 753 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1709 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 761 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 765 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 769 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 773 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 777 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, new ZeroAtom( yylhs.location, yystack_[1].value.as< ExpressionBase* > () ), yystack_[1].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 785 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1757 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 789 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1765 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 793 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 797 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 801 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 805 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 809 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 813 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 1813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 817 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 825 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 829 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1837 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 833 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1845 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 841 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1853 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 845 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 849 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, (-1) * yystack_[0].value.as< INTEGER_T > () );
  }
#line 1869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 857 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 861 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 865 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, (-1) * yystack_[0].value.as< FLOATING_T > () );
  }
#line 1893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 873 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1901 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 877 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 881 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< rational_t > ().numerator *= -1;
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1918 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 890 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 1926 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  if( yystack_[3].value.as< AtomNode* > ()->node_type_ == NodeType::INTEGER_ATOM && yystack_[1].value.as< AtomNode* > ()->node_type_ == NodeType::INTEGER_ATOM )
	  {
		  yylhs.value.as< AtomNode* > () = new NumberRangeAtom( yylhs.location, reinterpret_cast<IntegerAtom*>( yystack_[3].value.as< AtomNode* > () ), reinterpret_cast<IntegerAtom*>( yystack_[1].value.as< AtomNode* > () ));
	  }
	  else
	  {
		  driver.error( yylhs.location, "numbers in range expression must be Integer" );
		  yylhs.value.as< AtomNode* > () = nullptr;
	  }
  }
#line 1942 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 914 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1950 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 918 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 1958 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 926 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1966 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 930 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1974 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 938 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
	  yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1983 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 943 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
	  yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 952 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::ADD );
  }
#line 2000 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 2008 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 960 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MUL );
  }
#line 2016 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 964 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::DIV );
  }
#line 2024 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MOD );
  }
#line 2032 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 972 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::RAT_DIV );
  }
#line 2040 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::NEQ );
  }
#line 2048 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 980 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::EQ );
  }
#line 2056 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 984 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSER );
  }
#line 2064 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 988 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATER );
  }
#line 2072 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 992 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSEREQ );
  }
#line 2080 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 996 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATEREQ );
  }
#line 2088 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1000 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::OR );
  }
#line 2096 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1004 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::XOR );
  }
#line 2104 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1008 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::AND );
  }
#line 2112 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1012 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), nullptr, ExpressionOperation::NOT );
  }
#line 2120 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1016 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2128 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1024 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2136 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1028 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2144 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1032 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1046 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1050 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2175 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1054 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
	  stmts->add( yystack_[0].value.as< AstNode* > () );
	  yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1064 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2193 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1068 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2201 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1072 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1076 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2218 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1081 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2227 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2236 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1095 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2245 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1100 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2254 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1109 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2262 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1117 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2270 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1121 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2278 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1125 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2286 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1129 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2294 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2302 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1137 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2310 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1141 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2318 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1145 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2326 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1149 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2334 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1153 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2342 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1157 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2350 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1161 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2358 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1165 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2366 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1169 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2374 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1173 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1177 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2390 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1181 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.error
	  ( yylhs.location
	  , "invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
	  , libcasm_fe::Codes::SyntaxErrorInvalidStatement
	  );
  }
#line 2402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1201 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2410 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1205 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2418 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1209 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2426 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1217 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2434 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1225 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1233 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1237 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2458 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1253 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2466 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1261 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2474 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1269 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[1].value.as< std::string > () );
  }
#line 2482 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1277 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2503 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1298 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2511 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1306 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2520 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1311 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::vector< std::pair< AtomNode*, AstNode* > >();
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1320 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () =yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1324 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2545 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1328 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1332 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1340 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( nullptr, yystack_[0].value.as< AstNode* > () );
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1348 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1356 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< BaseFunctionAtom* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1364 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( new StringAtom( yylhs.location, std::move( yystack_[2].value.as< std::string > () ) ), yystack_[0].value.as< AstNode* > () );
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1372 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1376 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1380 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1384 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1392 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2633 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1396 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1404 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2649 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2657 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
	  yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2666 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1421 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
	  yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1434 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto var = Symbol( yystack_[1].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET );
	  try
	  {
		  driver.function_table.add( &var );	  
	  }
	  catch( const SymbolAlreadyExists& e)
	  {
		  driver.error( yylhs.location, e.what() );
	  }
  }
#line 2707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.function_table.remove( yystack_[5].value.as< std::string > () );
	  yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1460 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto var = Symbol( yystack_[3].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET );
	  try
	  {
		  driver.function_table.add( &var );
	  }
	  catch( const SymbolAlreadyExists& e)
	  {
		  driver.error( yylhs.location, e.what() );
	  }
  }
#line 2732 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.function_table.remove( yystack_[7].value.as< std::string > () );
	  yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1481 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1496 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2779 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1519 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2787 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1527 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2795 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2799 "GrammarParser.cpp" // lalr1.cc:859
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
  casmi_parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  casmi_parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short int casmi_parser::yypact_ninf_ = -203;

  const signed char casmi_parser::yytable_ninf_ = -106;

  const short int
  casmi_parser::yypact_[] =
  {
      25,   -19,    71,   382,  -203,  -203,    17,    54,    58,    74,
     109,   -22,   382,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,    21,   139,    89,     0,   113,   136,  -203,   129,   668,
     -43,   147,   171,   178,   420,   -15,  -203,   179,   172,   -47,
     223,   168,  -203,  -203,  -203,  -203,   668,    16,    23,   668,
     588,   169,  -203,  -203,  -203,  -203,   199,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,   893,  -203,    90,   194,
    -203,   201,   195,   208,   211,   113,   113,    57,  -203,   420,
     420,   668,   668,   668,  -203,  -203,   184,   185,   420,    -5,
     668,   668,   668,   187,   668,   188,   420,   420,    -2,   202,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,    -3,
     225,   200,   203,   147,   212,   219,   229,  -203,  -203,  -203,
     668,  -203,  -203,  -203,   668,  -203,  -203,  -203,   777,  -203,
     227,   237,   240,   893,  -203,   628,   668,   668,   668,   668,
     668,   668,   668,   668,   668,   668,   668,   668,   668,   668,
     668,   668,   147,   147,   148,   224,    55,   668,   245,   251,
     420,   178,  -203,  -203,  -203,  -203,    -1,   322,   893,   893,
     893,   154,   284,  -203,   668,   255,   526,   555,   893,   668,
     748,   269,   347,   395,   668,   178,   420,     5,   136,  -203,
    -203,   147,   147,   699,   806,   835,  -203,    40,  -203,   668,
    -203,   256,   921,   946,   174,    91,    82,    61,   957,   193,
     487,  -203,   252,    87,   976,   415,   262,   893,   264,  -203,
     668,   147,  -203,   241,   242,   259,   268,   -14,   893,  -203,
     261,  -203,  -203,  -203,  -203,  -203,  -203,   147,   668,   864,
     668,   420,    45,   893,   188,   188,  -203,  -203,   893,   132,
    -203,   178,   420,   223,  -203,  -203,  -203,    19,  -203,   263,
    -203,  -203,     6,   135,   275,   893,  -203,   668,   893,   272,
     147,  -203,  -203,    -6,   265,   668,   296,   497,   283,   297,
     324,   292,   295,   303,   310,     9,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,   420,   133,  -203,  -203,  -203,   730,   730,
    -203,   893,   668,  -203,   319,  -203,   438,  -203,   420,   668,
    -203,   420,   420,   420,   420,   420,  -203,  -203,  -203,   420,
    -203,  -203,   893,  -203,   420,   668,  -203,   323,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,   468,  -203,   420,  -203
  };

  const unsigned char
  casmi_parser::yydefact_[] =
  {
       0,     0,     0,     0,     3,     1,     0,     0,     0,     0,
       0,     0,     2,     5,    10,     6,     7,     9,     8,    11,
      12,     0,     0,     0,     0,     0,     0,     4,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,    26,     0,
      24,     0,    64,    65,    67,    66,     0,     0,     0,     0,
       0,     0,    74,    71,    77,    61,   105,   104,    55,    60,
      68,    69,    70,    59,    63,    62,    16,    54,     0,    32,
      36,     0,    33,    40,     0,     0,     0,     0,   118,     0,
       0,     0,     0,   143,   144,   135,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   136,     0,
     111,   110,   120,   121,   122,   123,   125,   124,   126,   127,
     128,   108,   109,   129,   130,   131,   132,   133,   134,     0,
       0,     0,    25,     0,     0,    39,     0,    23,    13,   103,
       0,    75,    72,    78,     0,    76,    73,    79,     0,    83,
      60,     0,    84,    87,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,     0,     0,     0,
       0,     0,   137,   168,   138,   139,     0,     0,   140,   141,
     142,     0,     0,   178,     0,   162,     0,     0,   145,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      29,     0,    38,     0,     0,     0,    56,     0,    82,    85,
     106,     0,   102,   100,   101,    93,    88,    89,    95,    96,
      97,    90,    91,    92,    94,    98,    99,    17,     0,    31,
       0,     0,    35,     0,     0,    46,     0,     0,    19,    14,
       0,   114,   117,   164,   167,   166,   171,     0,     0,     0,
       0,     0,     0,   146,     0,     0,   165,   163,   147,     0,
     112,     0,     0,    22,    30,    37,    48,     0,    51,    52,
      57,    58,     0,     0,     0,    86,   107,     0,    15,     0,
      45,    42,    41,     0,     0,     0,     0,     0,   160,     0,
     169,     0,     0,     0,     0,     0,   150,   151,   152,   153,
     154,   175,   176,     0,     0,   113,    21,    47,    50,     0,
      81,    20,     0,    44,     0,   119,     0,   173,     0,     0,
     161,     0,     0,     0,     0,     0,   148,   149,   115,     0,
      49,    53,    18,    43,     0,     0,   177,     0,   170,   155,
     158,   156,   157,   116,   172,     0,   159,     0,   174
  };

  const short int
  casmi_parser::yypgoto_[] =
  {
    -203,  -203,  -203,  -203,   363,  -203,  -203,  -203,  -203,  -203,
     140,  -203,   181,   215,   349,  -203,   189,    34,   114,   130,
    -203,    88,  -202,  -203,   -46,  -164,  -203,  -203,  -203,  -203,
    -203,  -137,  -203,    20,   -34,  -165,  -203,  -188,   226,   -31,
     -48,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
     103,  -203,  -203,  -203,  -203,  -203,   -10,    -7,   105,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203
  };

  const short int
  casmi_parser::yydefgoto_[] =
  {
      -1,     2,     3,    12,    13,    14,    15,    16,    17,    18,
      37,    38,    40,    70,    71,    72,   124,   125,   236,   127,
     267,   268,    57,    58,    59,    60,    61,    62,    63,    64,
      65,   141,   142,   143,    67,   100,    19,    77,    78,   172,
     173,   102,   103,   104,   105,   106,   107,   108,   109,   295,
     296,   297,   298,   299,   300,   110,   174,   175,   176,   113,
     114,   285,   335,   115,   116,   117,   118
  };

  const short int
  casmi_parser::yytable_[] =
  {
      99,   269,   237,   101,   140,   241,   195,   259,   211,    33,
      68,    79,   243,    80,   261,    81,    82,    83,    84,    85,
      86,   123,    87,    88,   111,    89,    90,   112,     1,    91,
      25,   260,    73,    92,    93,    94,    69,    95,   119,   282,
     183,   291,   326,   233,   234,    99,    99,   184,   196,    66,
     145,    34,    35,   283,    99,    96,   262,    26,   272,   273,
       4,   191,    99,    99,    69,    74,   129,  -105,   130,   138,
      53,     5,    97,   304,   185,   134,   307,   291,    98,    28,
     308,   131,   132,   133,    52,    53,    54,   292,    56,   272,
     273,   131,   132,   133,   272,   273,    20,   305,   135,   136,
     137,   178,   179,   180,   233,   234,   269,   331,   170,   149,
     186,   187,   188,   289,   190,    52,    53,    54,   171,   314,
      52,    53,    54,   292,    56,   155,   156,   157,   244,   244,
     149,    53,   151,    21,    73,   149,    99,    22,   328,   101,
      32,   161,    99,    99,   244,   244,   155,   156,   157,   162,
     204,   155,   156,    23,   205,   155,   156,   200,    99,    99,
     111,   274,    99,   112,   343,   101,   212,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   337,   303,   329,   177,   111,   238,    24,   112,
      29,    30,    36,   171,   171,    39,   228,   229,    31,   230,
     235,   192,   193,   290,   249,   246,   293,   231,    41,   253,
     135,   136,   137,   247,   258,   168,   169,    99,   294,   147,
     301,   302,   149,   150,   151,   152,    73,    75,    99,   275,
      76,   101,   121,   122,   126,   264,   153,   154,   155,   156,
     157,   149,   150,   151,   158,   159,   160,   128,   144,   293,
     278,   145,   111,   163,   164,   112,   165,   155,   156,   157,
     166,   294,   167,   181,   182,   279,   189,    56,   287,    99,
     336,   194,   101,   338,   339,   340,   341,   342,   197,   198,
     201,   286,   199,   202,    99,   203,   344,    99,    99,    99,
      99,    99,   208,   111,   207,    99,   112,   311,   101,   348,
      99,   209,   239,    69,   240,   316,   248,   250,   255,   276,
     149,   150,   151,    99,   235,   277,   155,   132,   136,   111,
     280,   281,   112,   312,   153,   154,   155,   156,   157,   284,
     310,   309,   332,   159,    79,   319,    80,   245,    81,    82,
      83,    84,    85,    86,   315,    87,    88,   317,    89,    90,
     320,   322,    91,   321,   323,   345,    92,    93,    94,    79,
      95,    80,   324,    81,    82,    83,    84,    85,    86,   325,
      87,    88,   333,    89,    90,    27,   346,    91,    96,   263,
     232,    92,    93,    94,   120,    95,     6,     7,     8,     9,
      10,   265,    11,   306,   313,    97,   330,   242,   327,     0,
       0,    98,     0,    96,   256,     0,     0,    79,     0,    80,
       0,    81,    82,    83,    84,    85,    86,     0,    87,    88,
      97,    89,    90,     0,     0,    91,    98,     0,     0,    92,
      93,    94,    79,    95,    80,     0,    81,    82,    83,    84,
      85,    86,     0,    87,    88,     0,    89,    90,     0,     0,
      91,    96,     0,     0,    92,    93,    94,     0,    95,     0,
     334,     0,     0,   149,   150,   151,     0,     0,    97,   257,
       0,     0,     0,     0,    98,     0,    96,   153,   154,   155,
     156,   157,   146,   147,   148,     0,   149,   150,   151,   152,
     347,     0,     0,    97,     0,     0,     0,     0,     0,    98,
     153,   154,   155,   156,   157,     0,     0,     0,   158,   159,
     160,     0,   146,   147,   148,     0,   149,   150,   151,   152,
       0,     0,   318,     0,     0,     0,     0,     0,     0,     0,
     153,   154,   155,   156,   157,   149,   150,   151,   158,   159,
     160,   146,   147,   148,     0,   149,   150,   151,   152,   153,
       0,   155,   156,   157,   251,     0,     0,     0,     0,   153,
     154,   155,   156,   157,     0,     0,     0,   158,   159,   160,
     146,   147,   148,     0,   149,   150,   151,   152,     0,     0,
       0,     0,     0,     0,     0,     0,   252,     0,   153,   154,
     155,   156,   157,     0,     0,     0,   158,   159,   160,   146,
     147,   148,     0,   149,   150,   151,   152,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   153,   154,   155,
     156,   157,     0,     0,     0,   158,   159,   160,    42,    43,
      44,    45,     0,     0,     0,    46,     0,    47,    48,     0,
      49,     0,    50,   139,     0,     0,     0,     0,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    52,    53,    54,    55,    56,    42,    43,
      44,    45,     0,     0,     0,    46,     0,    47,    48,     0,
      49,   210,    50,     0,     0,     0,     0,     0,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    52,    53,    54,    55,    56,    42,    43,
      44,    45,     0,     0,     0,    46,     0,    47,    48,     0,
      49,     0,    50,     0,     0,     0,     0,     0,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
      43,    44,    45,    52,    53,    54,    55,    56,    47,    48,
       0,    49,     0,    50,     0,     0,   266,     0,     0,    51,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      42,    43,    44,    45,    52,    53,    54,    55,    56,    47,
      48,     0,    49,     0,    50,   254,     0,     0,     0,     0,
      51,     0,   146,   147,   148,     0,   149,   150,   151,   152,
       0,     0,     0,     0,     0,    52,    53,    54,    55,    56,
     153,   154,   155,   156,   157,     0,     0,     0,   158,   159,
     160,   146,   147,   148,     0,   149,   150,   151,   152,     0,
     206,     0,     0,     0,     0,     0,     0,     0,     0,   153,
     154,   155,   156,   157,     0,     0,     0,   158,   159,   160,
     146,   147,   148,     0,   149,   150,   151,   152,     0,   270,
       0,     0,     0,     0,     0,     0,     0,     0,   153,   154,
     155,   156,   157,     0,     0,     0,   158,   159,   160,   146,
     147,   148,     0,   149,   150,   151,   152,     0,   271,     0,
       0,     0,     0,     0,     0,     0,     0,   153,   154,   155,
     156,   157,     0,     0,     0,   158,   159,   160,   146,   147,
     148,     0,   149,   150,   151,   152,     0,   288,     0,     0,
       0,     0,     0,     0,     0,     0,   153,   154,   155,   156,
     157,     0,     0,     0,   158,   159,   160,   146,   147,   148,
       0,   149,   150,   151,   152,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   153,   154,   155,   156,   157,
       0,     0,     0,   158,   159,   160,   147,   148,     0,   149,
     150,   151,   152,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   153,   154,   155,   156,   157,     0,     0,
       0,   158,   159,   160,   149,   150,   151,   152,     0,     0,
       0,     0,     0,     0,     0,   149,   150,   151,   153,   154,
     155,   156,   157,     0,     0,     0,   158,   159,   160,   153,
     154,   155,   156,   157,   149,   150,   151,   158,   159,   160,
       0,     0,     0,     0,     0,     0,     0,     0,   153,   154,
     155,   156,   157,     0,     0,     0,     0,   159,   160
  };

  const short int
  casmi_parser::yycheck_[] =
  {
      34,   203,   166,    34,    50,   170,     9,   195,   145,     9,
      53,    12,    13,    14,     9,    16,    17,    18,    19,    20,
      21,    68,    23,    24,    34,    26,    27,    34,     3,    30,
      52,   196,    79,    34,    35,    36,    79,    38,    53,    53,
      88,    32,    33,    49,    50,    79,    80,    52,    51,    29,
      52,    51,    52,    67,    88,    56,    51,    79,    49,    50,
      79,    95,    96,    97,    79,    31,    46,    69,    52,    49,
      76,     0,    73,   261,    79,    52,    57,    32,    79,    58,
      61,    75,    76,    77,    75,    76,    77,    78,    79,    49,
      50,    75,    76,    77,    49,    50,    79,   262,    75,    76,
      77,    81,    82,    83,    49,    50,   308,   309,    51,    48,
      90,    91,    92,   250,    94,    75,    76,    77,    61,   283,
      75,    76,    77,    78,    79,    64,    65,    66,   176,   177,
      48,    76,    50,    79,    79,    48,   170,    79,   303,   170,
      51,    51,   176,   177,   192,   193,    64,    65,    66,    59,
     130,    64,    65,    79,   134,    64,    65,   123,   192,   193,
     170,   207,   196,   170,   329,   196,   146,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   319,    51,    51,    80,   196,   167,    79,   196,
      51,    52,    79,    61,    61,    59,   162,   163,    59,    51,
     166,    96,    97,   251,   184,    51,   252,    59,    79,   189,
      75,    76,    77,    59,   194,    75,    76,   251,   252,    45,
     254,   255,    48,    49,    50,    51,    79,    56,   262,   209,
      52,   262,    53,    61,    11,   201,    62,    63,    64,    65,
      66,    48,    49,    50,    70,    71,    72,    79,    79,   295,
     230,    52,   262,    59,    53,   262,    61,    64,    65,    66,
      52,   295,    51,    79,    79,   231,    79,    79,   248,   303,
     318,    69,   303,   321,   322,   323,   324,   325,    53,    79,
      68,   247,    79,    64,   318,    56,   334,   321,   322,   323,
     324,   325,    55,   303,    67,   329,   303,   277,   329,   347,
     334,    61,    57,    79,    53,   285,    22,    52,    39,    53,
      48,    49,    50,   347,   280,    51,    64,    76,    76,   329,
      61,    53,   329,    51,    62,    63,    64,    65,    66,    68,
      55,    68,   312,    71,    12,    52,    14,    15,    16,    17,
      18,    19,    20,    21,    79,    23,    24,    51,    26,    27,
      53,    59,    30,    29,    59,   335,    34,    35,    36,    12,
      38,    14,    59,    16,    17,    18,    19,    20,    21,    59,
      23,    24,    53,    26,    27,    12,    53,    30,    56,   198,
     165,    34,    35,    36,    35,    38,     4,     5,     6,     7,
       8,   202,    10,   263,   280,    73,   308,   171,   295,    -1,
      -1,    79,    -1,    56,    57,    -1,    -1,    12,    -1,    14,
      -1,    16,    17,    18,    19,    20,    21,    -1,    23,    24,
      73,    26,    27,    -1,    -1,    30,    79,    -1,    -1,    34,
      35,    36,    12,    38,    14,    -1,    16,    17,    18,    19,
      20,    21,    -1,    23,    24,    -1,    26,    27,    -1,    -1,
      30,    56,    -1,    -1,    34,    35,    36,    -1,    38,    -1,
      22,    -1,    -1,    48,    49,    50,    -1,    -1,    73,    74,
      -1,    -1,    -1,    -1,    79,    -1,    56,    62,    63,    64,
      65,    66,    44,    45,    46,    -1,    48,    49,    50,    51,
      22,    -1,    -1,    73,    -1,    -1,    -1,    -1,    -1,    79,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    70,    71,
      72,    -1,    44,    45,    46,    -1,    48,    49,    50,    51,
      -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    48,    49,    50,    70,    71,
      72,    44,    45,    46,    -1,    48,    49,    50,    51,    62,
      -1,    64,    65,    66,    28,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    71,    72,
      44,    45,    46,    -1,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    71,    72,    44,
      45,    46,    -1,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,    40,    41,
      42,    43,    -1,    -1,    -1,    47,    -1,    49,    50,    -1,
      52,    -1,    54,    55,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    40,    41,
      42,    43,    -1,    -1,    -1,    47,    -1,    49,    50,    -1,
      52,    53,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    75,    76,    77,    78,    79,    40,    41,
      42,    43,    -1,    -1,    -1,    47,    -1,    49,    50,    -1,
      52,    -1,    54,    -1,    -1,    -1,    -1,    -1,    60,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,
      41,    42,    43,    75,    76,    77,    78,    79,    49,    50,
      -1,    52,    -1,    54,    -1,    -1,    57,    -1,    -1,    60,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    75,    76,    77,    78,    79,    49,
      50,    -1,    52,    -1,    54,    37,    -1,    -1,    -1,    -1,
      60,    -1,    44,    45,    46,    -1,    48,    49,    50,    51,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    70,    71,
      72,    44,    45,    46,    -1,    48,    49,    50,    51,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    71,    72,
      44,    45,    46,    -1,    48,    49,    50,    51,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    71,    72,    44,
      45,    46,    -1,    48,    49,    50,    51,    -1,    53,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,    44,    45,
      46,    -1,    48,    49,    50,    51,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    71,    72,    44,    45,    46,
      -1,    48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    71,    72,    45,    46,    -1,    48,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    70,    71,    72,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    71,    72,    62,
      63,    64,    65,    66,    48,    49,    50,    70,    71,    72,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    -1,    71,    72
  };

  const unsigned char
  casmi_parser::yystos_[] =
  {
       0,     3,    81,    82,    79,     0,     4,     5,     6,     7,
       8,    10,    83,    84,    85,    86,    87,    88,    89,   116,
      79,    79,    79,    79,    79,    52,    79,    84,    58,    51,
      52,    59,    51,     9,    51,    52,    79,    90,    91,    59,
      92,    79,    40,    41,    42,    43,    47,    49,    50,    52,
      54,    60,    75,    76,    77,    78,    79,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   113,   114,    53,    79,
      93,    94,    95,    79,    97,    56,    52,   117,   118,    12,
      14,    16,    17,    18,    19,    20,    21,    23,    24,    26,
      27,    30,    34,    35,    36,    38,    56,    73,    79,   114,
     115,   119,   121,   122,   123,   124,   125,   126,   127,   128,
     135,   136,   137,   139,   140,   143,   144,   145,   146,    53,
      94,    53,    61,    68,    96,    97,    11,    99,    79,   113,
      52,    75,    76,    77,    52,    75,    76,    77,   113,    55,
     104,   111,   112,   113,    79,    52,    44,    45,    46,    48,
      49,    50,    51,    62,    63,    64,    65,    66,    70,    71,
      72,    51,    59,    59,    53,    61,    52,    51,    90,    90,
      51,    61,   119,   120,   136,   137,   138,   138,   113,   113,
     113,    79,    79,   120,    52,    79,   113,   113,   113,    79,
     113,   114,   138,   138,    69,     9,    51,    53,    79,    79,
      97,    68,    64,    56,   113,   113,    53,    67,    55,    61,
      53,   111,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,    97,    97,
      51,    59,    93,    49,    50,    97,    98,   105,   113,    57,
      53,   115,   118,    13,   120,    15,    51,    59,    22,   113,
      52,    28,    31,   113,    37,    39,    57,    74,   113,   117,
     115,     9,    51,    92,    97,    96,    57,   100,   101,   102,
      53,    53,    49,    50,   104,   113,    53,    51,   113,    97,
      61,    53,    53,    67,    68,   141,    97,   113,    53,   111,
     120,    32,    78,   104,   114,   129,   130,   131,   132,   133,
     134,   114,   114,    51,   117,   115,    99,    57,    61,    68,
      55,   113,    51,    98,   105,    79,   113,    51,    25,    52,
      53,    29,    59,    59,    59,    59,    33,   130,   115,    51,
     101,   102,   113,    53,    22,   142,   120,   111,   120,   120,
     120,   120,   120,   115,   120,   113,    53,    22,   120
  };

  const unsigned char
  casmi_parser::yyr1_[] =
  {
       0,    80,    81,    82,    83,    83,    84,    84,    84,    84,
      84,    84,    85,    86,    87,    88,    88,    88,    88,    88,
      88,    89,    89,    89,    89,    90,    90,    91,    91,    92,
      92,    93,    93,    94,    94,    95,    95,    96,    96,    96,
      97,    97,    97,    97,    98,    98,    98,    99,    99,   100,
     100,   100,   101,   101,   102,   102,   102,   102,   102,   103,
     103,   103,   103,   103,   103,   103,   103,   103,   104,   104,
     104,   105,   105,   105,   106,   106,   106,   107,   107,   107,
     108,   109,   110,   110,   111,   111,   112,   112,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   114,   114,   114,   115,   115,
     115,   116,   116,   116,   116,   116,   116,   117,   117,   118,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   120,   120,   120,
     121,   122,   123,   123,   124,   125,   126,   127,   128,   129,
     129,   130,   130,   130,   130,   131,   132,   133,   134,   135,
     135,   135,   135,   136,   136,   137,   137,   138,   138,   139,
     139,   141,   140,   142,   140,   143,   144,   145,   146
  };

  const unsigned char
  casmi_parser::yyr2_[] =
  {
       0,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     2,     5,     6,     7,     4,     6,     9,     6,
       8,     7,     6,     4,     3,     2,     1,     3,     1,     3,
       4,     3,     1,     1,     2,     3,     1,     3,     2,     1,
       1,     4,     4,     6,     3,     2,     1,     4,     3,     3,
       2,     1,     1,     3,     1,     1,     3,     4,     4,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     1,     2,     2,     1,     2,     2,
       2,     5,     3,     2,     1,     2,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     2,     1,     1,     3,     4,     1,     1,
       1,     4,     6,     7,     6,     8,     9,     3,     1,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       2,     2,     2,     1,     1,     2,     3,     3,     5,     2,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     7,
       4,     5,     2,     3,     3,     3,     3,     2,     1,     4,
       6,     0,     7,     0,     9,     4,     4,     6,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const casmi_parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\"CASM\"", "\"init\"",
  "\"option\"", "\"derived\"", "\"enum\"", "\"rule\"", "\"dumps\"",
  "\"function\"", "\"initially\"", "\"seq\"", "\"endseq\"", "\"par\"",
  "\"endpar\"", "\"assert\"", "\"assure\"", "\"diedie\"", "\"impossible\"",
  "\"skip\"", "\"let\"", "\"in\"", "\"forall\"", "\"iterate\"", "\"do\"",
  "\"call\"", "\"if\"", "\"then\"", "\"else\"", "\"case\"", "\"of\"",
  "\"default\"", "\"endcase\"", "\"print\"", "\"debug\"", "\"push\"",
  "\"into\"", "\"pop\"", "\"from\"", "\"self\"", "\"undef\"", "\"false\"",
  "\"true\"", "\"and\"", "\"or\"", "\"xor\"", "\"not\"", "\"div\"",
  "\"+\"", "\"-\"", "\"=\"", "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"",
  "\"}\"", "\".\"", "\":\"", "\"@\"", "\",\"", "\"<\"", "\">\"", "\"*\"",
  "\"/\"", "\"%\"", "\"..\"", "\"->\"", "\":=\"", "\"!=\"", "\"<=\"",
  "\">=\"", "\"{|\"", "\"|}\"", "\"floating\"", "\"integer\"",
  "\"rational\"", "\"string\"", "\"identifier\"", "$accept",
  "SPECIFICATION", "HEADER", "BODY_ELEMENTS", "BODY_ELEMENT",
  "INIT_SYNTAX", "OPTION_SYNTAX", "ENUM_SYNTAX", "DERIVED_SYNTAX",
  "FUNCTION_DEFINITION", "IDENTIFIER_LIST", "IDENTIFIER_LIST_NO_COMMA",
  "FUNCTION_SIGNATURE", "PARAM", "PARAM_LIST", "PARAM_LIST_NO_COMMA",
  "TYPE_IDENTIFIER_STARLIST", "TYPE_SYNTAX", "TYPE_SYNTAX_LIST",
  "INITIALIZERS", "INITIALIZER_LIST", "INITIALIZER", "ATOM", "VALUE",
  "NUMBER", "INTEGER_NUMBER", "FLOATING_NUMBER", "RATIONAL_NUMBER",
  "RULEREF", "NUMBER_RANGE", "LISTCONST", "EXPRESSION_LIST",
  "EXPRESSION_LIST_NO_COMMA", "EXPRESSION", "FUNCTION_SYNTAX", "RULE_STMT",
  "RULE_SYNTAX", "DUMPSPEC_LIST", "DUMPSPEC", "SIMPLE_STMT", "STATEMENT",
  "ASSERT_SYNTAX", "ASSURE_SYNTAX", "DIEDIE_SYNTAX", "IMPOSSIBLE_SYNTAX",
  "PRINT_SYNTAX", "DEBUG_SYNTAX", "UPDATE_SYNTAX", "CASE_SYNTAX",
  "CASE_LABEL_LIST", "CASE_LABEL", "CASE_LABEL_DEFAULT",
  "CASE_LABEL_NUMBER", "CASE_LABEL_IDENT", "CASE_LABEL_STRING",
  "CALL_SYNTAX", "SEQ_SYNTAX", "PAR_SYNTAX", "STATEMENTS", "IFTHENELSE",
  "LET_SYNTAX", "$@1", "$@2", "PUSH_SYNTAX", "POP_SYNTAX", "FORALL_SYNTAX",
  "ITERATE_SYNTAX", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  casmi_parser::yyrline_[] =
  {
       0,   332,   332,   340,   347,   352,   361,   365,   369,   389,
     406,   410,   429,   437,   442,   476,   481,   485,   489,   493,
     497,   505,   510,   515,   519,   526,   530,   538,   543,   552,
     558,   566,   572,   583,   587,   595,   600,   608,   613,   618,
     626,   649,   662,   684,   702,   707,   711,   719,   723,   731,
     735,   739,   748,   752,   760,   764,   768,   772,   776,   784,
     788,   792,   796,   800,   804,   808,   812,   816,   824,   828,
     832,   840,   844,   848,   856,   860,   864,   872,   876,   880,
     889,   897,   913,   917,   925,   929,   937,   942,   951,   955,
     959,   963,   967,   971,   975,   979,   983,   987,   991,   995,
     999,  1003,  1007,  1011,  1015,  1023,  1027,  1031,  1045,  1049,
    1053,  1063,  1067,  1071,  1075,  1080,  1085,  1094,  1099,  1108,
    1116,  1120,  1124,  1128,  1132,  1136,  1140,  1144,  1148,  1152,
    1156,  1160,  1164,  1168,  1172,  1176,  1180,  1200,  1204,  1208,
    1216,  1224,  1232,  1236,  1252,  1260,  1268,  1276,  1297,  1305,
    1310,  1319,  1323,  1327,  1331,  1339,  1347,  1355,  1363,  1371,
    1375,  1379,  1383,  1391,  1395,  1403,  1407,  1415,  1420,  1429,
    1433,  1443,  1442,  1460,  1459,  1480,  1495,  1518,  1526
  };

  // Print the state stack on the debug stream.
  void
  casmi_parser::yystack_print_ ()
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
  casmi_parser::yy_reduce_print_ (int yyrule)
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
#line 3564 "GrammarParser.cpp" // lalr1.cc:1167
#line 1532 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


void yy::casmi_parser::error
( const location_type& l
, const std::string& m
)
{
    driver.error( l, m, libcasm_fe::Codes::SyntaxError );
}


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
