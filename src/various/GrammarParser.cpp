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

      case 132: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.move< rational_t > (that.value);
        break;

      case 135: // CASE_LABEL
        value.move< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 103: // INITIALIZER
        value.move< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
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

      case 134: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 101: // INITIALIZERS
      case 102: // INITIALIZER_LIST
        value.move< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
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
  casmi_parser::stack_symbol_type&
  casmi_parser::stack_symbol_type::operator= (const stack_symbol_type& that)
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

      case 132: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.copy< rational_t > (that.value);
        break;

      case 135: // CASE_LABEL
        value.copy< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 103: // INITIALIZER
        value.copy< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
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

      case 134: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 101: // INITIALIZERS
      case 102: // INITIALIZER_LIST
        value.copy< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
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

      case 132: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 77: // "rational"
        yylhs.value.build< rational_t > ();
        break;

      case 135: // CASE_LABEL
        yylhs.value.build< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 103: // INITIALIZER
        yylhs.value.build< std::pair<ExpressionBase*, ExpressionBase*> > ();
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

      case 134: // CASE_LABEL_LIST
        yylhs.value.build< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 101: // INITIALIZERS
      case 102: // INITIALIZER_LIST
        yylhs.value.build< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
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
#line 340 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
  }
#line 1168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 348 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 355 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
	  yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 1185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 360 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
	  yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
  }
#line 1194 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 369 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode(NodeType::OPTION);
  }
#line 1202 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new EnumDefNode(yylhs.location, yystack_[0].value.as< Enum* > ());
  }
#line 1210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 377 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 397 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 414 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > ();
  }
#line 1263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 418 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 437 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 450 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 484 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  // TODO: 2nd argument should be a reference
	  yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1333 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 501 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 505 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 513 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[4].value.as< std::vector<std::string> > ());
	  yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 518 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > ());
	  yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 523 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 527 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 534 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
  }
#line 1415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 538 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ());
  }
#line 1423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 546 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move( yystack_[2].value.as< std::vector<std::string> > () );
	  yylhs.value.as< std::vector<std::string> > ().push_back( yystack_[0].value.as< std::string > () );
  }
#line 1432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 551 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
	  yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
  }
#line 1441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 560 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  /* this constructor is implementation dependant! */
	  std::vector<Type*> foo;
	  yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
  }
#line 1451 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 566 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ());
  }
#line 1459 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  size_t size = driver.binding_offsets.size();
	  driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
	  yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
  }
#line 1469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 580 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  size_t size = driver.binding_offsets.size();
	  driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
	  // TODO: fail for rules without types and print warnings
	  yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
  }
#line 1480 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 591 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1488 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 595 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ());
  }
#line 1496 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 603 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1505 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 608 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 616 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1522 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 621 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  // TODO: limit memory size
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
  }
#line 1531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 626 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 634 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 657 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 670 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 692 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 710 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< std::vector<Type*> > ().push_back( yystack_[2].value.as< Type* > () );
	  yylhs.value.as< std::vector<Type*> > () = std::move( yystack_[0].value.as< std::vector<Type*> > () );
  }
#line 1636 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 715 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[1].value.as< Type* > () );
  }
#line 1644 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 719 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[0].value.as< Type* > () );
  }
#line 1652 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1660 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 731 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = nullptr;
  }
#line 1668 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 739 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 743 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 747 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = new std::vector< std::pair<ExpressionBase*, ExpressionBase* > >();
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1693 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1701 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 760 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1709 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 768 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 776 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1733 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1741 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 784 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, new ZeroAtom( yylhs.location, yystack_[1].value.as< ExpressionBase* > () ), yystack_[1].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 792 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1757 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 796 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1765 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 800 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 804 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1781 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 808 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); 
  }
#line 1805 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 820 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1813 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 828 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 836 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 1829 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 840 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 1837 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 848 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1845 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 852 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1853 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 856 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 864 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 868 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1877 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 872 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = yystack_[0].value.as< IntegerAtom* > ();
      yystack_[0].value.as< IntegerAtom* > ()->val_ *= (-1);
  }
#line 1886 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 881 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1894 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 885 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1902 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 889 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< FloatingAtom* > () = yystack_[0].value.as< FloatingAtom* > ();
      yystack_[0].value.as< FloatingAtom* > ()->val_ *= (-1);
  }
#line 1911 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 898 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1919 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 902 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< RationalAtom* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1927 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 906 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< rational_t > ().numerator *= -1;
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1936 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 915 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 1944 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 923 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1960 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 939 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1968 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 943 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 1976 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 951 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1984 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 955 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1992 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 963 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
	  yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2001 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
	  yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2010 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 977 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::ADD );
  }
#line 2018 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 2026 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 985 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MUL );
  }
#line 2034 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 989 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::DIV );
  }
#line 2042 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 993 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MOD );
  }
#line 2050 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 997 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::RAT_DIV );
  }
#line 2058 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1001 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::NEQ );
  }
#line 2066 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1005 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::EQ );
  }
#line 2074 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1009 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSER );
  }
#line 2082 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1013 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATER );
  }
#line 2090 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1017 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSEREQ );
  }
#line 2098 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1021 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATEREQ );
  }
#line 2106 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1025 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::OR );
  }
#line 2114 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1029 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::XOR );
  }
#line 2122 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1033 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::AND );
  }
#line 2130 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1037 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), nullptr, ExpressionOperation::NOT );
  }
#line 2138 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1041 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2146 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1049 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2154 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1053 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2162 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1057 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2177 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1072 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1076 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2193 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1084 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2201 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
	  stmts->add( yystack_[0].value.as< AstNode* > () );
	  yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2211 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1098 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2219 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1102 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2227 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2235 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1110 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2244 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1115 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2253 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1120 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2262 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1129 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2280 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2288 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1151 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2296 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2304 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1159 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2312 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1163 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2320 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1167 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2328 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1171 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1175 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2344 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1179 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1183 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2360 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2368 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1191 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1195 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2384 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1199 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2392 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1203 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2400 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1207 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2408 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1211 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2416 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.error
	  ( yylhs.location
	  , "invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
	  , libcasm_fe::Codes::SyntaxErrorInvalidStatement
	  );
  }
#line 2428 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1235 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2436 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1239 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2444 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1247 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2452 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1255 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1263 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2468 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1267 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2476 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1283 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2484 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1291 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2492 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1299 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[1].value.as< std::string > () );
  }
#line 2500 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1307 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2521 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1328 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1336 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[0].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[1].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2538 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1341 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::vector< std::pair< AtomNode*, AstNode* > >();
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2547 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1350 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2555 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = nullptr;
  }
#line 2563 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1362 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2571 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2579 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 2587 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 2595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< AtomNode* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 2603 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1386 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2611 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1394 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2635 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1418 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
	  yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2676 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1435 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
	  yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2685 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2693 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2701 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1457 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2717 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1469 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.function_table.remove( yystack_[5].value.as< std::string > () );
	  yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2726 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1474 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2742 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1486 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.function_table.remove( yystack_[7].value.as< std::string > () );
	  yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2751 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1495 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2766 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1510 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1533 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2805 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2809 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int casmi_parser::yypact_ninf_ = -279;

  const signed char casmi_parser::yytable_ninf_ = -108;

  const short int
  casmi_parser::yypact_[] =
  {
      15,   -49,    41,   370,  -279,  -279,     6,    24,    53,    56,
      66,   -37,   370,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,    58,   211,    99,    17,    72,    94,  -279,    78,   670,
      -4,    87,   107,   120,   462,    20,  -279,   137,   112,    10,
     180,   115,  -279,  -279,  -279,  -279,   670,    32,    84,   670,
     165,   121,  -279,  -279,  -279,  -279,   147,  -279,  -279,  -279,
    -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,   866,  -279,
      37,   142,  -279,   151,   152,   166,   173,    72,    72,   -23,
    -279,   462,   462,   670,   670,   670,  -279,  -279,   160,   169,
     462,     0,   670,   670,   670,   171,   670,   172,   462,   462,
      25,   162,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,  -279,     3,   200,   175,   177,    87,   198,   204,   218,
    -279,  -279,  -279,   153,   183,   670,  -279,  -279,  -279,   197,
     197,   670,  -279,  -279,  -279,   750,  -279,   209,   222,   219,
     866,  -279,   630,   670,   670,   670,   670,   670,   670,   670,
     670,   670,   670,   670,   670,   670,   670,   670,   670,    87,
      87,    59,   202,    -5,   670,   228,   233,   462,   120,  -279,
    -279,  -279,   300,   325,   866,   866,   866,    88,   269,  -279,
     670,   240,   568,   597,   866,   670,   394,   256,   373,   398,
     670,   120,   462,    11,    94,  -279,  -279,    87,    87,   701,
     779,   808,  -279,   153,  -279,   670,  -279,   244,   894,   947,
     922,    63,   -29,    76,   445,   318,   239,  -279,   243,   145,
     958,   558,   529,   866,   257,  -279,   670,    87,  -279,   -10,
     -10,   248,   262,    33,   866,  -279,   254,  -279,  -279,  -279,
    -279,  -279,  -279,    87,   670,   837,   670,   462,   273,   866,
     172,   172,  -279,  -279,   866,    -8,  -279,   120,   462,   180,
    -279,  -279,  -279,    26,  -279,   263,  -279,  -279,   270,   866,
    -279,   670,   866,   281,    87,  -279,  -279,   -10,   268,   670,
     282,   539,   298,   304,   324,   -18,  -279,  -279,   462,    29,
    -279,  -279,  -279,   732,   732,  -279,   866,   670,  -279,   305,
    -279,   480,  -279,   462,   670,  -279,   462,  -279,  -279,  -279,
    -279,  -279,  -279,   307,   -18,   303,  -279,   462,  -279,  -279,
     866,  -279,   462,   670,  -279,   312,  -279,  -279,  -279,    -1,
    -279,  -279,   510,  -279,  -279,   462,  -279
  };

  const unsigned char
  casmi_parser::yydefact_[] =
  {
       0,     0,     0,     0,     3,     1,     0,     0,     0,     0,
       0,     0,     2,     5,    10,     6,     7,     9,     8,    11,
      12,     0,     0,     0,     0,     0,     0,     4,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,    26,     0,
      24,     0,    64,    67,    69,    68,     0,     0,     0,     0,
       0,     0,    76,    73,    79,    61,   107,   106,    55,    65,
      66,    60,    70,    71,    72,    59,    63,    62,    16,    54,
       0,    32,    36,     0,    33,    40,     0,     0,     0,     0,
     121,     0,     0,     0,     0,   145,   146,   138,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     139,     0,   112,   114,   113,   123,   124,   125,   126,   128,
     127,   129,   130,   131,   110,   111,   132,   133,   134,   135,
     136,   137,     0,     0,     0,    25,     0,     0,    39,     0,
      23,    13,   105,     0,     0,     0,    74,    77,    80,     0,
       0,     0,    81,    75,    78,     0,    85,    60,     0,    86,
      89,    82,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    34,     0,     0,     0,     0,     0,     0,   140,
     141,   169,     0,     0,   142,   143,   144,     0,     0,   179,
       0,   163,     0,     0,   147,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    27,    29,     0,    38,     0,
       0,     0,    56,     0,    84,    87,   108,     0,   104,   102,
     103,    95,    90,    91,    97,    98,    99,    92,    93,    94,
      96,   100,   101,    17,     0,    31,     0,     0,    35,     0,
       0,    46,     0,     0,    19,    14,     0,   117,   120,   165,
     168,   167,   172,     0,     0,     0,     0,     0,     0,   148,
       0,     0,   166,   164,   149,     0,   115,     0,     0,    22,
      30,    37,    48,     0,    51,    52,    57,    58,     0,    88,
     109,     0,    15,     0,    45,    42,    41,     0,     0,     0,
       0,     0,   161,     0,   170,     0,   176,   177,     0,     0,
     116,    21,    47,    50,     0,    83,    20,     0,    44,     0,
     122,     0,   174,     0,     0,   162,     0,   154,   158,   155,
     156,   157,   159,     0,   152,     0,   118,     0,    49,    53,
      18,    43,     0,     0,   178,     0,   171,   150,   151,     0,
     119,   173,     0,   160,   153,     0,   175
  };

  const short int
  casmi_parser::yypgoto_[] =
  {
    -279,  -279,  -279,  -279,   357,  -279,  -279,  -279,  -279,  -279,
      52,  -279,   167,   214,   335,  -279,   164,   -15,   104,   126,
    -279,    98,  -202,  -279,  -278,  -273,   -46,   -42,   -14,   -38,
    -279,  -279,  -279,  -144,  -279,    21,   -34,   -33,  -175,  -279,
    -191,   224,   -31,   -61,  -279,  -279,  -279,  -279,  -279,  -279,
    -279,  -279,    81,  -279,  -279,  -279,  -279,  -279,   201,  -279,
    -279,  -279,  -279,  -279,  -279,  -279,  -279
  };

  const short int
  casmi_parser::yydefgoto_[] =
  {
      -1,     2,     3,    12,    13,    14,    15,    16,    17,    18,
      37,    38,    40,    72,    73,    74,   127,   128,   242,   130,
     273,   274,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,   148,   149,   150,    69,   179,   103,    19,
      79,    80,   180,   181,   105,   106,   107,   108,   109,   110,
     111,   112,   323,   324,   325,   113,   114,   115,   182,   116,
     117,   289,   333,   118,   119,   120,   121
  };

  const short int
  casmi_parser::yytable_[] =
  {
     101,   102,   247,   104,   147,   136,   143,   275,   217,   138,
     265,    81,   201,    82,   317,    25,    76,   319,     1,   156,
     267,   158,   320,    43,    44,    45,    33,   266,   177,   189,
       4,   133,   134,   137,   144,   162,   163,   164,   178,   239,
     240,     5,    26,   298,   239,   240,   319,   101,   101,    70,
      68,   320,   190,   178,   202,    98,   101,    52,    53,    54,
     318,    56,   268,   197,   101,   101,    53,   132,    34,    35,
     145,    53,    99,   122,    75,    71,   299,   152,   126,   191,
     327,   133,   134,   302,   135,    20,   286,   303,   168,    75,
     178,   136,   143,   300,  -107,   138,   169,   136,   143,    71,
     287,   275,   329,    21,   184,   185,   186,    52,    53,    54,
     236,   206,   293,   192,   193,   194,    28,   196,   237,   137,
     144,   250,   250,   326,   156,   137,   144,   162,   163,   175,
     176,   243,    22,   139,   140,    23,   141,   250,   250,   252,
     162,   163,   164,   101,   102,    24,   104,   253,   101,   101,
      32,    36,   340,    39,   234,   235,   210,    41,   241,    52,
      53,   142,   211,    77,   101,   101,    75,   278,   101,   102,
     335,   104,    78,   125,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   233,
     124,   129,   270,   156,   131,   244,   294,   136,   143,   152,
     151,   170,   133,   134,   171,    42,    43,    44,    45,   162,
     163,   255,    46,   172,    47,    48,   259,    49,   173,    50,
     146,   264,   283,   101,   174,    51,   296,   297,    52,    53,
      54,   200,   139,   140,   101,   102,   279,   104,   290,   187,
      52,    53,    54,    55,    56,   309,   139,   140,   188,   321,
     195,    56,   334,   203,   204,   336,   205,   282,    52,    53,
     142,   322,    29,    30,   101,   102,   207,   104,   208,   241,
      31,   341,    52,    53,   209,   291,   213,   214,   321,   101,
     215,    71,   101,   183,   346,   245,   246,   156,   157,   158,
     322,   254,   256,   101,   102,   261,   104,   280,   101,   198,
     199,   160,   306,   162,   163,   164,   344,   162,   281,   284,
     311,   101,    81,   249,    82,   285,    83,    84,    85,    86,
      87,    88,   288,    89,    90,   305,    91,    92,   330,   295,
      93,   304,   307,   312,    94,    95,    96,    81,    97,    82,
     251,    83,    84,    85,    86,    87,    88,   310,    89,    90,
     314,    91,    92,   316,   342,    93,    98,   315,   331,    94,
      95,    96,   339,    97,   337,   343,   156,   157,   158,    27,
     123,   269,   271,    99,     6,     7,     8,     9,    10,   100,
      11,    98,   162,   163,   164,    81,   238,    82,   308,    83,
      84,    85,    86,    87,    88,   301,    89,    90,    99,    91,
      92,   328,   248,    93,   100,   338,     0,    94,    95,    96,
      81,    97,    82,     0,    83,    84,    85,    86,    87,    88,
       0,    89,    90,     0,    91,    92,     0,     0,    93,    98,
     262,   260,    94,    95,    96,     0,    97,     0,   153,   154,
     155,     0,   156,   157,   158,   159,    99,     0,     0,     0,
       0,     0,   100,     0,    98,     0,   160,   161,   162,   163,
     164,     0,     0,     0,   165,   166,   167,     0,     0,     0,
       0,    99,   263,     0,    81,     0,    82,   100,    83,    84,
      85,    86,    87,    88,     0,    89,    90,     0,    91,    92,
       0,     0,    93,   156,   157,   158,    94,    95,    96,     0,
      97,     0,   332,     0,     0,     0,     0,   160,   161,   162,
     163,   164,     0,     0,     0,   165,   166,   167,    98,     0,
       0,     0,     0,     0,   153,   154,   155,     0,   156,   157,
     158,   159,   345,     0,     0,    99,     0,     0,     0,     0,
       0,   100,   160,   161,   162,   163,   164,     0,     0,     0,
     165,   166,   167,     0,   153,   154,   155,     0,   156,   157,
     158,   159,     0,     0,   313,     0,     0,     0,     0,     0,
       0,     0,   160,   161,   162,   163,   164,   156,   157,   158,
     165,   166,   167,   153,   154,   155,     0,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   257,     0,     0,     0,
     166,   160,   161,   162,   163,   164,   156,   157,   158,   165,
     166,   167,   153,   154,   155,     0,   156,   157,   158,   159,
     160,   161,   162,   163,   164,     0,     0,     0,   258,     0,
     160,   161,   162,   163,   164,     0,     0,     0,   165,   166,
     167,   153,   154,   155,     0,   156,   157,   158,   159,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   160,
     161,   162,   163,   164,     0,     0,     0,   165,   166,   167,
      42,    43,    44,    45,     0,     0,     0,    46,     0,    47,
      48,     0,    49,   216,    50,     0,     0,     0,     0,     0,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      42,    43,    44,    45,     0,     0,     0,    46,     0,    47,
      48,     0,    49,     0,    50,     0,     0,     0,     0,     0,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    43,    44,    45,    52,    53,    54,    55,    56,
      47,    48,     0,    49,     0,    50,     0,     0,   272,     0,
       0,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    43,    44,    45,    52,    53,    54,    55,
      56,    47,    48,     0,    49,     0,    50,     0,     0,     0,
       0,     0,    51,     0,   153,   154,   155,     0,   156,   157,
     158,   159,     0,   212,     0,     0,     0,    52,    53,    54,
      55,    56,   160,   161,   162,   163,   164,     0,     0,     0,
     165,   166,   167,   153,   154,   155,     0,   156,   157,   158,
     159,     0,   276,     0,     0,     0,     0,     0,     0,     0,
       0,   160,   161,   162,   163,   164,     0,     0,     0,   165,
     166,   167,   153,   154,   155,     0,   156,   157,   158,   159,
       0,   277,     0,     0,     0,     0,     0,     0,     0,     0,
     160,   161,   162,   163,   164,     0,     0,     0,   165,   166,
     167,   153,   154,   155,     0,   156,   157,   158,   159,     0,
     292,     0,     0,     0,     0,     0,     0,     0,     0,   160,
     161,   162,   163,   164,     0,     0,     0,   165,   166,   167,
     153,   154,   155,     0,   156,   157,   158,   159,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   160,   161,
     162,   163,   164,     0,     0,     0,   165,   166,   167,   154,
     155,     0,   156,   157,   158,   159,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   160,   161,   162,   163,
     164,     0,     0,     0,   165,   166,   167,   154,     0,     0,
     156,   157,   158,   159,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   160,   161,   162,   163,   164,     0,
       0,     0,   165,   166,   167,   156,   157,   158,   159,     0,
       0,     0,     0,     0,     0,     0,   156,   157,   158,   160,
     161,   162,   163,   164,     0,     0,     0,   165,   166,   167,
     160,   161,   162,   163,   164,     0,     0,     0,     0,   166,
     167
  };

  const short int
  casmi_parser::yycheck_[] =
  {
      34,    34,   177,    34,    50,    47,    48,   209,   152,    47,
     201,    12,     9,    14,    32,    52,    31,   295,     3,    48,
       9,    50,   295,    41,    42,    43,     9,   202,    51,    90,
      79,    49,    50,    47,    48,    64,    65,    66,    61,    49,
      50,     0,    79,    51,    49,    50,   324,    81,    82,    53,
      29,   324,    52,    61,    51,    56,    90,    75,    76,    77,
      78,    79,    51,    97,    98,    99,    76,    46,    51,    52,
      49,    76,    73,    53,    79,    79,   267,    52,    68,    79,
      51,    49,    50,    57,    52,    79,    53,    61,    51,    79,
      61,   133,   134,   268,    69,   133,    59,   139,   140,    79,
      67,   303,   304,    79,    83,    84,    85,    75,    76,    77,
      51,   126,   256,    92,    93,    94,    58,    96,    59,   133,
     134,   182,   183,   298,    48,   139,   140,    64,    65,    77,
      78,   173,    79,    49,    50,    79,    52,   198,   199,    51,
      64,    65,    66,   177,   177,    79,   177,    59,   182,   183,
      51,    79,   327,    59,   169,   170,   135,    79,   173,    75,
      76,    77,   141,    56,   198,   199,    79,   213,   202,   202,
     314,   202,    52,    61,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   164,   165,   166,   167,   168,
      53,    11,   207,    48,    79,   174,   257,   239,   240,    52,
      79,    59,    49,    50,    53,    40,    41,    42,    43,    64,
      65,   190,    47,    61,    49,    50,   195,    52,    52,    54,
      55,   200,   237,   257,    51,    60,   260,   261,    75,    76,
      77,    69,    49,    50,   268,   268,   215,   268,   253,    79,
      75,    76,    77,    78,    79,   287,    49,    50,    79,   295,
      79,    79,   313,    53,    79,   316,    79,   236,    75,    76,
      77,   295,    51,    52,   298,   298,    68,   298,    64,   284,
      59,   332,    75,    76,    56,   254,    67,    55,   324,   313,
      61,    79,   316,    82,   345,    57,    53,    48,    49,    50,
     324,    22,    52,   327,   327,    39,   327,    53,   332,    98,
      99,    62,   281,    64,    65,    66,   339,    64,    51,    61,
     289,   345,    12,    13,    14,    53,    16,    17,    18,    19,
      20,    21,    68,    23,    24,    55,    26,    27,   307,    56,
      30,    68,    51,    51,    34,    35,    36,    12,    38,    14,
      15,    16,    17,    18,    19,    20,    21,    79,    23,    24,
      52,    26,    27,    29,   333,    30,    56,    53,    53,    34,
      35,    36,    59,    38,    57,    53,    48,    49,    50,    12,
      35,   204,   208,    73,     4,     5,     6,     7,     8,    79,
      10,    56,    64,    65,    66,    12,   172,    14,   284,    16,
      17,    18,    19,    20,    21,   269,    23,    24,    73,    26,
      27,   303,   178,    30,    79,   324,    -1,    34,    35,    36,
      12,    38,    14,    -1,    16,    17,    18,    19,    20,    21,
      -1,    23,    24,    -1,    26,    27,    -1,    -1,    30,    56,
      57,    37,    34,    35,    36,    -1,    38,    -1,    44,    45,
      46,    -1,    48,    49,    50,    51,    73,    -1,    -1,    -1,
      -1,    -1,    79,    -1,    56,    -1,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    71,    72,    -1,    -1,    -1,
      -1,    73,    74,    -1,    12,    -1,    14,    79,    16,    17,
      18,    19,    20,    21,    -1,    23,    24,    -1,    26,    27,
      -1,    -1,    30,    48,    49,    50,    34,    35,    36,    -1,
      38,    -1,    22,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,    56,    -1,
      -1,    -1,    -1,    -1,    44,    45,    46,    -1,    48,    49,
      50,    51,    22,    -1,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    79,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      70,    71,    72,    -1,    44,    45,    46,    -1,    48,    49,
      50,    51,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    64,    65,    66,    48,    49,    50,
      70,    71,    72,    44,    45,    46,    -1,    48,    49,    50,
      51,    62,    63,    64,    65,    66,    28,    -1,    -1,    -1,
      71,    62,    63,    64,    65,    66,    48,    49,    50,    70,
      71,    72,    44,    45,    46,    -1,    48,    49,    50,    51,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    31,    -1,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    70,    71,
      72,    44,    45,    46,    -1,    48,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    71,    72,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    -1,    49,
      50,    -1,    52,    53,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    -1,    49,
      50,    -1,    52,    -1,    54,    -1,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    40,    41,    42,    43,    75,    76,    77,    78,    79,
      49,    50,    -1,    52,    -1,    54,    -1,    -1,    57,    -1,
      -1,    60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    40,    41,    42,    43,    75,    76,    77,    78,
      79,    49,    50,    -1,    52,    -1,    54,    -1,    -1,    -1,
      -1,    -1,    60,    -1,    44,    45,    46,    -1,    48,    49,
      50,    51,    -1,    53,    -1,    -1,    -1,    75,    76,    77,
      78,    79,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      70,    71,    72,    44,    45,    46,    -1,    48,    49,    50,
      51,    -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    -1,    -1,    -1,    70,
      71,    72,    44,    45,    46,    -1,    48,    49,    50,    51,
      -1,    53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    70,    71,
      72,    44,    45,    46,    -1,    48,    49,    50,    51,    -1,
      53,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    71,    72,
      44,    45,    46,    -1,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    71,    72,    45,
      46,    -1,    48,    49,    50,    51,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    71,    72,    45,    -1,    -1,
      48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    48,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    48,    49,    50,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    71,    72,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    -1,    71,
      72
  };

  const unsigned char
  casmi_parser::yystos_[] =
  {
       0,     3,    83,    84,    79,     0,     4,     5,     6,     7,
       8,    10,    85,    86,    87,    88,    89,    90,    91,   121,
      79,    79,    79,    79,    79,    52,    79,    86,    58,    51,
      52,    59,    51,     9,    51,    52,    79,    92,    93,    59,
      94,    79,    40,    41,    42,    43,    47,    49,    50,    52,
      54,    60,    75,    76,    77,    78,    79,   104,   105,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   117,   118,
      53,    79,    95,    96,    97,    79,    99,    56,    52,   122,
     123,    12,    14,    16,    17,    18,    19,    20,    21,    23,
      24,    26,    27,    30,    34,    35,    36,    38,    56,    73,
      79,   118,   119,   120,   124,   126,   127,   128,   129,   130,
     131,   132,   133,   137,   138,   139,   141,   142,   145,   146,
     147,   148,    53,    96,    53,    61,    68,    98,    99,    11,
     101,    79,   117,    49,    50,    52,   109,   110,   111,    49,
      50,    52,    77,   109,   110,   117,    55,   108,   115,   116,
     117,    79,    52,    44,    45,    46,    48,    49,    50,    51,
      62,    63,    64,    65,    66,    70,    71,    72,    51,    59,
      59,    53,    61,    52,    51,    92,    92,    51,    61,   119,
     124,   125,   140,   140,   117,   117,   117,    79,    79,   125,
      52,    79,   117,   117,   117,    79,   117,   118,   140,   140,
      69,     9,    51,    53,    79,    79,    99,    68,    64,    56,
     117,   117,    53,    67,    55,    61,    53,   115,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,    99,    99,    51,    59,    95,    49,
      50,    99,   100,   109,   117,    57,    53,   120,   123,    13,
     125,    15,    51,    59,    22,   117,    52,    28,    31,   117,
      37,    39,    57,    74,   117,   122,   120,     9,    51,    94,
      99,    98,    57,   102,   103,   104,    53,    53,   108,   117,
      53,    51,   117,    99,    61,    53,    53,    67,    68,   143,
      99,   117,    53,   115,   125,    56,   118,   118,    51,   122,
     120,   101,    57,    61,    68,    55,   117,    51,   100,   109,
      79,   117,    51,    25,    52,    53,    29,    32,    78,   106,
     107,   108,   118,   134,   135,   136,   120,    51,   103,   104,
     117,    53,    22,   144,   125,   115,   125,    57,   134,    59,
     120,   125,   117,    53,   119,    22,   125
  };

  const unsigned char
  casmi_parser::yyr1_[] =
  {
       0,    82,    83,    84,    85,    85,    86,    86,    86,    86,
      86,    86,    87,    88,    89,    90,    90,    90,    90,    90,
      90,    91,    91,    91,    91,    92,    92,    93,    93,    94,
      94,    95,    95,    96,    96,    97,    97,    98,    98,    98,
      99,    99,    99,    99,   100,   100,   100,   101,   101,   102,
     102,   102,   103,   103,   104,   104,   104,   104,   104,   105,
     105,   105,   105,   105,   105,   105,   105,   106,   107,   107,
     108,   108,   108,   109,   109,   109,   110,   110,   110,   111,
     111,   111,   112,   113,   114,   114,   115,   115,   116,   116,
     117,   117,   117,   117,   117,   117,   117,   117,   117,   117,
     117,   117,   117,   117,   117,   117,   117,   118,   118,   118,
     119,   119,   120,   120,   121,   121,   121,   121,   121,   121,
     122,   122,   123,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     125,   125,   126,   127,   128,   128,   129,   130,   131,   132,
     133,   134,   134,   135,   136,   136,   136,   136,   136,   136,
     137,   137,   137,   137,   138,   138,   139,   139,   140,   140,
     141,   141,   143,   142,   144,   142,   145,   146,   147,   148
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
       1,     1,     1,     1,     2,     2,     1,     2,     2,     1,
       2,     2,     2,     5,     3,     2,     1,     2,     3,     1,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     1,     1,     3,     4,
       1,     1,     1,     1,     4,     6,     7,     6,     8,     9,
       3,     1,     5,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     2,     2,     1,     1,     2,     3,     3,
       6,     2,     1,     3,     1,     1,     1,     1,     1,     1,
       7,     4,     5,     2,     3,     3,     3,     3,     2,     1,
       4,     6,     0,     7,     0,     9,     4,     4,     6,     2
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
  "\"rational\"", "\"string\"", "\"identifier\"", "UPLUS", "UMINUS",
  "$accept", "SPECIFICATION", "HEADER", "BODY_ELEMENTS", "BODY_ELEMENT",
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
  casmi_parser::yyrline_[] =
  {
       0,   339,   339,   347,   354,   359,   368,   372,   376,   396,
     413,   417,   436,   444,   449,   483,   488,   492,   496,   500,
     504,   512,   517,   522,   526,   533,   537,   545,   550,   559,
     565,   573,   579,   590,   594,   602,   607,   615,   620,   625,
     633,   656,   669,   691,   709,   714,   718,   726,   730,   738,
     742,   746,   755,   759,   767,   771,   775,   779,   783,   791,
     795,   799,   803,   807,   811,   815,   819,   827,   835,   839,
     847,   851,   855,   863,   867,   871,   880,   884,   888,   897,
     901,   905,   914,   922,   938,   942,   950,   954,   962,   967,
     976,   980,   984,   988,   992,   996,  1000,  1004,  1008,  1012,
    1016,  1020,  1024,  1028,  1032,  1036,  1040,  1048,  1052,  1056,
    1071,  1075,  1083,  1087,  1097,  1101,  1105,  1109,  1114,  1119,
    1128,  1133,  1142,  1150,  1154,  1158,  1162,  1166,  1170,  1174,
    1178,  1182,  1186,  1190,  1194,  1198,  1202,  1206,  1210,  1214,
    1234,  1238,  1246,  1254,  1262,  1266,  1282,  1290,  1298,  1306,
    1327,  1335,  1340,  1349,  1357,  1361,  1365,  1369,  1373,  1377,
    1385,  1389,  1393,  1397,  1405,  1409,  1417,  1421,  1429,  1434,
    1443,  1447,  1457,  1456,  1474,  1473,  1494,  1509,  1532,  1540
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
#line 3571 "GrammarParser.cpp" // lalr1.cc:1167
#line 1546 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
