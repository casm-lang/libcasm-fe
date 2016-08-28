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
      case 135: // STATEMENTS
        value.move< AstListNode* > (that.value);
        break;

      case 84: // BODY_ELEMENT
      case 116: // RULE_STMT
      case 117: // RULE_SYNTAX
      case 120: // SIMPLE_STMT
      case 121: // STATEMENT
      case 125: // IMPOSSIBLE_SYNTAX
        value.move< AstNode* > (that.value);
        break;

      case 103: // VALUE
      case 104: // BOOLEAN
      case 105: // NUMBER
      case 110: // NUMBER_RANGE
        value.move< AtomNode* > (that.value);
        break;

      case 115: // FUNCTION_SYNTAX
        value.move< BaseFunctionAtom* > (that.value);
        break;

      case 132: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 129: // CASE_SYNTAX
        value.move< CaseNode* > (that.value);
        break;

      case 124: // DIEDIE_SYNTAX
        value.move< DiedieNode* > (that.value);
        break;

      case 87: // ENUM_SYNTAX
        value.move< Enum* > (that.value);
        break;

      case 102: // ATOM
      case 114: // EXPRESSION
        value.move< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.move< FLOATING_T > (that.value);
        break;

      case 107: // FLOATING_NUMBER
        value.move< FloatingAtom* > (that.value);
        break;

      case 142: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 76: // "integer"
        value.move< INTEGER_T > (that.value);
        break;

      case 136: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 85: // INIT_SYNTAX
        value.move< InitNode* > (that.value);
        break;

      case 106: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 137: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 141: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 126: // PRINT_SYNTAX
      case 127: // DEBUG_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 140: // PUSH_SYNTAX
        value.move< PushNode* > (that.value);
        break;

      case 108: // RATIONAL_NUMBER
        value.move< RationalAtom* > (that.value);
        break;

      case 82: // HEADER
        value.move< SpecificationNode* > (that.value);
        break;

      case 93: // PARAM
      case 97: // TYPE_SYNTAX
        value.move< Type* > (that.value);
        break;

      case 122: // ASSERT_SYNTAX
      case 123: // ASSURE_SYNTAX
      case 133: // SEQ_SYNTAX
      case 134: // PAR_SYNTAX
      case 143: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 128: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.move< rational_t > (that.value);
        break;

      case 131: // CASE_LABEL
        value.move< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 101: // INITIALIZER
        value.move< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 119: // DUMPSPEC
        value.move< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 92: // FUNCTION_SIGNATURE
        value.move< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 109: // RULEREF
        value.move< std::string > (that.value);
        break;

      case 111: // LISTCONST
      case 112: // EXPRESSION_LIST
      case 113: // EXPRESSION_LIST_NO_COMMA
        value.move< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 94: // PARAM_LIST
      case 95: // PARAM_LIST_NO_COMMA
      case 96: // TYPE_IDENTIFIER_STARLIST
      case 98: // TYPE_SYNTAX_LIST
        value.move< std::vector<Type*> > (that.value);
        break;

      case 130: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 99: // INITIALIZERS
      case 100: // INITIALIZER_LIST
        value.move< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 118: // DUMPSPEC_LIST
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
      case 135: // STATEMENTS
        value.copy< AstListNode* > (that.value);
        break;

      case 84: // BODY_ELEMENT
      case 116: // RULE_STMT
      case 117: // RULE_SYNTAX
      case 120: // SIMPLE_STMT
      case 121: // STATEMENT
      case 125: // IMPOSSIBLE_SYNTAX
        value.copy< AstNode* > (that.value);
        break;

      case 103: // VALUE
      case 104: // BOOLEAN
      case 105: // NUMBER
      case 110: // NUMBER_RANGE
        value.copy< AtomNode* > (that.value);
        break;

      case 115: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (that.value);
        break;

      case 132: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 129: // CASE_SYNTAX
        value.copy< CaseNode* > (that.value);
        break;

      case 124: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (that.value);
        break;

      case 87: // ENUM_SYNTAX
        value.copy< Enum* > (that.value);
        break;

      case 102: // ATOM
      case 114: // EXPRESSION
        value.copy< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.copy< FLOATING_T > (that.value);
        break;

      case 107: // FLOATING_NUMBER
        value.copy< FloatingAtom* > (that.value);
        break;

      case 142: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 76: // "integer"
        value.copy< INTEGER_T > (that.value);
        break;

      case 136: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 85: // INIT_SYNTAX
        value.copy< InitNode* > (that.value);
        break;

      case 106: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 137: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 141: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 126: // PRINT_SYNTAX
      case 127: // DEBUG_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 140: // PUSH_SYNTAX
        value.copy< PushNode* > (that.value);
        break;

      case 108: // RATIONAL_NUMBER
        value.copy< RationalAtom* > (that.value);
        break;

      case 82: // HEADER
        value.copy< SpecificationNode* > (that.value);
        break;

      case 93: // PARAM
      case 97: // TYPE_SYNTAX
        value.copy< Type* > (that.value);
        break;

      case 122: // ASSERT_SYNTAX
      case 123: // ASSURE_SYNTAX
      case 133: // SEQ_SYNTAX
      case 134: // PAR_SYNTAX
      case 143: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 128: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.copy< rational_t > (that.value);
        break;

      case 131: // CASE_LABEL
        value.copy< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 101: // INITIALIZER
        value.copy< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 119: // DUMPSPEC
        value.copy< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 92: // FUNCTION_SIGNATURE
        value.copy< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 109: // RULEREF
        value.copy< std::string > (that.value);
        break;

      case 111: // LISTCONST
      case 112: // EXPRESSION_LIST
      case 113: // EXPRESSION_LIST_NO_COMMA
        value.copy< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 94: // PARAM_LIST
      case 95: // PARAM_LIST_NO_COMMA
      case 96: // TYPE_IDENTIFIER_STARLIST
      case 98: // TYPE_SYNTAX_LIST
        value.copy< std::vector<Type*> > (that.value);
        break;

      case 130: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 99: // INITIALIZERS
      case 100: // INITIALIZER_LIST
        value.copy< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 118: // DUMPSPEC_LIST
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

#line 865 "GrammarParser.cpp" // lalr1.cc:741

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
      case 135: // STATEMENTS
        yylhs.value.build< AstListNode* > ();
        break;

      case 84: // BODY_ELEMENT
      case 116: // RULE_STMT
      case 117: // RULE_SYNTAX
      case 120: // SIMPLE_STMT
      case 121: // STATEMENT
      case 125: // IMPOSSIBLE_SYNTAX
        yylhs.value.build< AstNode* > ();
        break;

      case 103: // VALUE
      case 104: // BOOLEAN
      case 105: // NUMBER
      case 110: // NUMBER_RANGE
        yylhs.value.build< AtomNode* > ();
        break;

      case 115: // FUNCTION_SYNTAX
        yylhs.value.build< BaseFunctionAtom* > ();
        break;

      case 132: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 129: // CASE_SYNTAX
        yylhs.value.build< CaseNode* > ();
        break;

      case 124: // DIEDIE_SYNTAX
        yylhs.value.build< DiedieNode* > ();
        break;

      case 87: // ENUM_SYNTAX
        yylhs.value.build< Enum* > ();
        break;

      case 102: // ATOM
      case 114: // EXPRESSION
        yylhs.value.build< ExpressionBase* > ();
        break;

      case 75: // "floating"
        yylhs.value.build< FLOATING_T > ();
        break;

      case 107: // FLOATING_NUMBER
        yylhs.value.build< FloatingAtom* > ();
        break;

      case 142: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 76: // "integer"
        yylhs.value.build< INTEGER_T > ();
        break;

      case 136: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 85: // INIT_SYNTAX
        yylhs.value.build< InitNode* > ();
        break;

      case 106: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 137: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 141: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 126: // PRINT_SYNTAX
      case 127: // DEBUG_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 140: // PUSH_SYNTAX
        yylhs.value.build< PushNode* > ();
        break;

      case 108: // RATIONAL_NUMBER
        yylhs.value.build< RationalAtom* > ();
        break;

      case 82: // HEADER
        yylhs.value.build< SpecificationNode* > ();
        break;

      case 93: // PARAM
      case 97: // TYPE_SYNTAX
        yylhs.value.build< Type* > ();
        break;

      case 122: // ASSERT_SYNTAX
      case 123: // ASSURE_SYNTAX
      case 133: // SEQ_SYNTAX
      case 134: // PAR_SYNTAX
      case 143: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 128: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 77: // "rational"
        yylhs.value.build< rational_t > ();
        break;

      case 131: // CASE_LABEL
        yylhs.value.build< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 101: // INITIALIZER
        yylhs.value.build< std::pair<ExpressionBase*, ExpressionBase*> > ();
        break;

      case 119: // DUMPSPEC
        yylhs.value.build< std::pair<std::string, std::vector<std::string>> > ();
        break;

      case 92: // FUNCTION_SIGNATURE
        yylhs.value.build< std::pair<std::vector<Type*>, Type*> > ();
        break;

      case 78: // "string"
      case 79: // "identifier"
      case 109: // RULEREF
        yylhs.value.build< std::string > ();
        break;

      case 111: // LISTCONST
      case 112: // EXPRESSION_LIST
      case 113: // EXPRESSION_LIST_NO_COMMA
        yylhs.value.build< std::vector<ExpressionBase*>* > ();
        break;

      case 94: // PARAM_LIST
      case 95: // PARAM_LIST_NO_COMMA
      case 96: // TYPE_IDENTIFIER_STARLIST
      case 98: // TYPE_SYNTAX_LIST
        yylhs.value.build< std::vector<Type*> > ();
        break;

      case 130: // CASE_LABEL_LIST
        yylhs.value.build< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 99: // INITIALIZERS
      case 100: // INITIALIZER_LIST
        yylhs.value.build< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
        break;

      case 118: // DUMPSPEC_LIST
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
#line 336 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
  }
#line 1159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 344 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 351 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
	  yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 1176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 356 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
	  yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
  }
#line 1185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 365 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode(NodeType::OPTION);
  }
#line 1193 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 369 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new EnumDefNode(yylhs.location, yystack_[0].value.as< Enum* > ());
  }
#line 1201 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 373 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1225 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 393 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1246 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > ();
  }
#line 1254 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 414 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1273 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 433 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1281 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 446 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1315 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 480 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  // TODO: 2nd argument should be a reference
	  yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1324 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 485 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1332 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 489 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1340 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 493 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1348 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 497 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1356 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 501 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[4].value.as< std::vector<std::string> > ());
	  yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 514 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > ());
	  yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1382 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 519 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1390 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 523 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1398 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 530 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
  }
#line 1406 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 534 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ());
  }
#line 1414 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 542 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move( yystack_[2].value.as< std::vector<std::string> > () );
	  yylhs.value.as< std::vector<std::string> > ().push_back( yystack_[0].value.as< std::string > () );
  }
#line 1423 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 547 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
	  yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
  }
#line 1432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 556 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  /* this constructor is implementation dependant! */
	  std::vector<Type*> foo;
	  yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
  }
#line 1442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 562 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ());
  }
#line 1450 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  size_t size = driver.binding_offsets.size();
	  driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
	  yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
  }
#line 1460 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 576 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  size_t size = driver.binding_offsets.size();
	  driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
	  // TODO: fail for rules without types and print warnings
	  yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
  }
#line 1471 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 587 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1479 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 591 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ());
  }
#line 1487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 599 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1496 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 604 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1504 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 612 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1513 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 617 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  // TODO: limit memory size
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
  }
#line 1522 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 622 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1530 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 630 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 653 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1574 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 666 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1600 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 688 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1618 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 706 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< std::vector<Type*> > ().push_back( yystack_[2].value.as< Type* > () );
	  yylhs.value.as< std::vector<Type*> > () = std::move( yystack_[0].value.as< std::vector<Type*> > () );
  }
#line 1627 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 711 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[1].value.as< Type* > () );
  }
#line 1635 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 715 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[0].value.as< Type* > () );
  }
#line 1643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 723 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 727 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = nullptr;
  }
#line 1659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 735 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 739 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 743 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = new std::vector< std::pair<ExpressionBase*, ExpressionBase* > >();
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1684 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 752 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1692 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 756 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1700 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 764 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1708 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 768 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 772 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1724 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 776 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1732 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 780 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, new ZeroAtom( yylhs.location, yystack_[1].value.as< ExpressionBase* > () ), yystack_[1].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 1740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 788 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 792 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 796 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 800 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 804 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1780 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 808 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 812 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1796 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 816 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1804 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 824 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 1812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 828 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 1820 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 835 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1828 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 839 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1836 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 843 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1844 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 851 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1852 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 855 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1860 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 859 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, (-1) * yystack_[0].value.as< INTEGER_T > () );
  }
#line 1868 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 867 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 871 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1884 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 875 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, (-1) * yystack_[0].value.as< FLOATING_T > () );
  }
#line 1892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 883 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1908 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 891 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< rational_t > ().numerator *= -1;
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 900 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 1925 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 908 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1941 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 924 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 1957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 940 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1973 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 948 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
	  yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1982 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
	  yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1991 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 962 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::ADD );
  }
#line 1999 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 966 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 970 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MUL );
  }
#line 2015 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 974 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::DIV );
  }
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 978 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MOD );
  }
#line 2031 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 982 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::RAT_DIV );
  }
#line 2039 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 986 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::NEQ );
  }
#line 2047 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::EQ );
  }
#line 2055 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSER );
  }
#line 2063 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATER );
  }
#line 2071 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSEREQ );
  }
#line 2079 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATEREQ );
  }
#line 2087 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::OR );
  }
#line 2095 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::XOR );
  }
#line 2103 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::AND );
  }
#line 2111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), nullptr, ExpressionOperation::NOT );
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1034 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1038 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1042 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2158 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1056 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2166 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1060 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2174 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1064 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
	  stmts->add( yystack_[0].value.as< AstNode* > () );
	  yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2184 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1074 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2192 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1078 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2200 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2208 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1086 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1091 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2226 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1096 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2235 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1105 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2244 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1110 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2253 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1119 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2261 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1127 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2269 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1131 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2277 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1135 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1139 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1143 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2301 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1147 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2309 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1151 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2317 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2325 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1159 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2333 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1163 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1167 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1171 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1175 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1179 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1183 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1191 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.error
	  ( yylhs.location
	  , "invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
	  , libcasm_fe::Codes::SyntaxErrorInvalidStatement
	  );
  }
#line 2401 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1211 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2417 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1219 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1227 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1235 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1243 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1247 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1263 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1271 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1279 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[1].value.as< std::string > () );
  }
#line 2481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1287 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2502 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1308 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2510 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1316 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2519 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1321 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::vector< std::pair< AtomNode*, AstNode* > >();
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2528 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1330 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( nullptr, yystack_[0].value.as< AstNode* > () );
  }
#line 2536 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1334 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1338 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2552 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1342 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( new StringAtom( yylhs.location, std::move( yystack_[2].value.as< std::string > () ) ), yystack_[0].value.as< AstNode* > () );
  }
#line 2560 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< BaseFunctionAtom* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2568 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1354 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2576 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1358 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1362 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2592 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1366 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2600 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1374 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2608 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2616 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1386 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2624 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2632 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
	  yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1403 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
	  yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2650 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2658 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1416 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2666 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1425 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2682 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1437 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.function_table.remove( yystack_[5].value.as< std::string > () );
	  yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1442 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1454 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.function_table.remove( yystack_[7].value.as< std::string > () );
	  yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1463 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2754 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1501 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2762 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1509 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2770 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2774 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int casmi_parser::yypact_ninf_ = -248;

  const signed char casmi_parser::yytable_ninf_ = -107;

  const short int
  casmi_parser::yypact_[] =
  {
      15,   -59,    25,   340,  -248,  -248,   -41,   -14,   -11,     3,
       6,   -44,   340,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,   -17,    90,    54,     0,    35,    -5,  -248,    57,   695,
     -46,    59,    32,    -7,   439,   -40,  -248,    76,    93,   -49,
     146,    83,  -248,  -248,  -248,  -248,   695,    45,    48,   695,
     200,    85,  -248,  -248,  -248,  -248,   157,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,   920,  -248,     8,
     152,  -248,   161,   155,   165,   169,    35,    35,   -25,  -248,
     439,   439,   695,   695,   695,  -248,  -248,   147,   159,   439,
     -42,   695,   695,   695,   160,   695,   166,   439,   439,   -29,
     162,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
       2,   174,   167,   177,    59,   168,   180,   192,  -248,  -248,
    -248,   695,  -248,  -248,  -248,   695,  -248,  -248,  -248,   804,
    -248,   194,   204,   201,   920,  -248,   655,   695,   695,   695,
     695,   695,   695,   695,   695,   695,   695,   695,   695,   695,
     695,   695,   695,    59,    59,    50,   185,   -18,   695,   208,
     213,   439,    -7,  -248,  -248,  -248,  -248,    60,   341,   920,
     920,   920,    94,   246,  -248,   695,   220,   593,   622,   920,
     695,   775,   234,   366,   414,   695,    -7,   439,     5,    -5,
    -248,  -248,    59,    59,   726,   833,   862,  -248,   -33,  -248,
     695,  -248,   227,   948,   261,   976,   130,    82,    62,   136,
     544,   255,  -248,   219,    27,   987,   434,   506,   920,   233,
    -248,   695,    59,  -248,   216,   217,   235,   247,   -38,   920,
    -248,   240,  -248,  -248,  -248,  -248,  -248,  -248,    59,   695,
     891,   695,   439,   553,   920,   166,   166,  -248,  -248,   920,
       9,  -248,    -7,   439,   146,  -248,  -248,  -248,    95,  -248,
     248,  -248,  -248,   148,   158,   259,   920,  -248,   695,   920,
     250,    59,  -248,  -248,   -28,   223,   695,   264,   516,   276,
     281,   300,   277,   278,   290,   292,   304,   541,  -248,  -248,
    -248,   439,    38,  -248,  -248,  -248,   757,   757,  -248,   920,
     695,  -248,   316,  -248,   457,  -248,   439,   695,  -248,   439,
     439,   439,   439,   439,   439,  -248,  -248,  -248,   439,  -248,
    -248,   920,  -248,   439,   695,  -248,   317,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,   487,  -248,   439,  -248
  };

  const unsigned char
  casmi_parser::yydefact_[] =
  {
       0,     0,     0,     0,     3,     1,     0,     0,     0,     0,
       0,     0,     2,     5,    10,     6,     7,     9,     8,    11,
      12,     0,     0,     0,     0,     0,     0,     4,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,    26,     0,
      24,     0,    64,    65,    68,    67,     0,     0,     0,     0,
       0,     0,    75,    72,    78,    61,   106,   105,    55,    66,
      60,    69,    70,    71,    59,    63,    62,    16,    54,     0,
      32,    36,     0,    33,    40,     0,     0,     0,     0,   119,
       0,     0,     0,     0,   144,   145,   136,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   137,
       0,   112,   111,   121,   122,   123,   124,   126,   125,   127,
     128,   129,   109,   110,   130,   131,   132,   133,   134,   135,
       0,     0,     0,    25,     0,     0,    39,     0,    23,    13,
     104,     0,    76,    73,    79,     0,    77,    74,    80,     0,
      84,    60,     0,    85,    88,    81,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    34,     0,     0,     0,
       0,     0,     0,   138,   166,   139,   140,     0,     0,   141,
     142,   143,     0,     0,   176,     0,   160,     0,     0,   146,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,    29,     0,    38,     0,     0,     0,    56,     0,    83,
      86,   107,     0,   103,   101,   102,    94,    89,    90,    96,
      97,    98,    91,    92,    93,    95,    99,   100,    17,     0,
      31,     0,     0,    35,     0,     0,    46,     0,     0,    19,
      14,     0,   115,   118,   162,   165,   164,   169,     0,     0,
       0,     0,     0,     0,   147,     0,     0,   163,   161,   148,
       0,   113,     0,     0,    22,    30,    37,    48,     0,    51,
      52,    57,    58,     0,     0,     0,    87,   108,     0,    15,
       0,    45,    42,    41,     0,     0,     0,     0,     0,   158,
       0,   167,     0,     0,     0,     0,     0,     0,   151,   173,
     174,     0,     0,   114,    21,    47,    50,     0,    82,    20,
       0,    44,     0,   120,     0,   171,     0,     0,   159,     0,
       0,     0,     0,     0,     0,   149,   150,   116,     0,    49,
      53,    18,    43,     0,     0,   175,     0,   168,   152,   155,
     153,   154,   156,   117,   170,     0,   157,     0,   172
  };

  const short int
  casmi_parser::yypgoto_[] =
  {
    -248,  -248,  -248,  -248,   360,  -248,  -248,  -248,  -248,  -248,
     127,  -248,   175,   207,   346,  -248,   188,    26,   107,   131,
    -248,    88,  -200,  -248,  -247,   -16,  -165,  -248,  -248,  -248,
    -248,  -248,  -134,  -248,    20,   -34,  -170,  -248,  -191,   226,
     -31,    19,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,   102,  -248,   -10,    -6,    37,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248
  };

  const short int
  casmi_parser::yydefgoto_[] =
  {
      -1,     2,     3,    12,    13,    14,    15,    16,    17,    18,
      37,    38,    40,    71,    72,    73,   125,   126,   237,   128,
     268,   269,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,   142,   143,   144,    68,   101,    19,    78,    79,
     173,   174,   103,   104,   105,   106,   107,   108,   109,   110,
     297,   298,   111,   175,   176,   177,   114,   115,   286,   334,
     116,   117,   118,   119
  };

  const short int
  casmi_parser::yytable_[] =
  {
     100,   242,   238,   102,   270,   260,   294,    69,    25,    33,
     185,   196,   212,   120,   262,   283,   273,   274,     1,   124,
       4,   234,   235,   146,   112,     5,   171,   261,   113,   284,
      74,   234,   235,    70,   141,    26,   172,   186,    20,    70,
    -106,    28,    52,    53,    54,    77,   100,   100,    53,    67,
     294,    34,    35,   197,    39,   100,   263,    75,    53,   162,
     301,    74,   192,   100,   100,    21,   130,   163,    22,   139,
     172,   302,    80,   244,    81,   150,    82,    83,    84,    85,
      86,    87,    23,    88,    89,    24,    90,    91,    76,   328,
      92,   156,   157,   303,    93,    94,    95,   131,    96,   172,
     135,   231,   179,   180,   181,    32,   270,   330,   184,   232,
     150,   187,   188,   189,    36,   191,    97,   290,   178,   312,
     132,   133,   134,   136,   137,   138,   156,   157,   158,   122,
     150,   327,   152,    98,   193,   194,    41,   100,    74,    99,
     102,    29,    30,   100,   100,   247,   156,   157,   158,    31,
     201,   205,   305,   248,   123,   206,   306,   127,   343,   100,
     100,   112,   129,   100,   145,   113,   102,   213,   214,   215,
     216,   217,   218,   219,   220,   221,   222,   223,   224,   225,
     226,   227,   228,   336,   150,   151,   152,   112,   239,   229,
     230,   113,   275,   236,   156,   157,   245,   245,   154,   155,
     156,   157,   158,   169,   170,   250,   159,   160,   161,   146,
     254,   164,   245,   245,   165,   259,   166,   167,   100,   296,
     168,   299,   300,   132,   133,   134,   182,   198,   265,   100,
     276,   195,   102,   136,   137,   138,   202,   295,   183,   190,
      42,    43,    44,    45,   203,    56,   199,    46,   204,    47,
      48,   279,    49,   112,    50,   140,   200,   113,   280,   209,
      51,   208,   210,   296,    70,   240,   241,   100,   249,   288,
     102,   291,   251,   256,   287,    52,    53,    54,    55,    56,
     277,   295,   100,   156,   278,   100,   100,   100,   100,   100,
     100,   112,   133,   137,   100,   113,   281,   102,   309,   100,
     282,   310,   313,   150,   151,   152,   314,   236,   285,   150,
     151,   152,   153,   100,   308,   315,   307,   154,   112,   156,
     157,   158,   113,   154,   155,   156,   157,   158,   317,   319,
     331,   159,   160,   161,   318,   335,   320,   321,   337,   338,
     339,   340,   341,   342,     6,     7,     8,     9,    10,   322,
      11,   323,   344,    80,   345,    81,   246,    82,    83,    84,
      85,    86,    87,   324,    88,    89,   348,    90,    91,   332,
     346,    92,    27,   233,   264,    93,    94,    95,    80,    96,
      81,   121,    82,    83,    84,    85,    86,    87,   311,    88,
      89,   266,    90,    91,   329,   304,    92,    97,   243,   326,
      93,    94,    95,     0,    96,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    98,     0,     0,     0,     0,     0,
      99,     0,    97,   257,     0,     0,    80,     0,    81,     0,
      82,    83,    84,    85,    86,    87,     0,    88,    89,    98,
      90,    91,     0,     0,    92,    99,     0,     0,    93,    94,
      95,    80,    96,    81,     0,    82,    83,    84,    85,    86,
      87,     0,    88,    89,     0,    90,    91,     0,     0,    92,
      97,     0,     0,    93,    94,    95,     0,    96,     0,   333,
       0,     0,   150,   151,   152,     0,     0,    98,   258,     0,
       0,     0,     0,    99,     0,    97,   154,   155,   156,   157,
     158,   147,   148,   149,     0,   150,   151,   152,   153,   347,
       0,     0,    98,     0,     0,     0,     0,     0,    99,   154,
     155,   156,   157,   158,     0,     0,     0,   159,   160,   161,
       0,   147,   148,   149,     0,   150,   151,   152,   153,     0,
       0,   316,     0,     0,     0,     0,     0,     0,     0,   154,
     155,   156,   157,   158,   150,   151,   152,   159,   160,   161,
     147,   148,   149,     0,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   292,   325,     0,     0,   160,   154,   155,
     156,   157,   158,    44,    45,   292,   159,   160,   161,     0,
     273,   274,   150,   151,   152,    44,    45,     0,     0,     0,
       0,     0,   273,   274,     0,     0,     0,     0,   156,   157,
     158,     0,     0,     0,     0,     0,    52,    53,    54,   293,
      56,   252,     0,     0,     0,     0,     0,     0,    52,    53,
      54,   293,    56,     0,     0,     0,     0,   147,   148,   149,
       0,   150,   151,   152,   153,     0,     0,     0,     0,     0,
       0,     0,     0,   253,     0,   154,   155,   156,   157,   158,
       0,     0,     0,   159,   160,   161,   147,   148,   149,     0,
     150,   151,   152,   153,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   154,   155,   156,   157,   158,     0,
       0,     0,   159,   160,   161,    42,    43,    44,    45,     0,
       0,     0,    46,     0,    47,    48,     0,    49,   211,    50,
       0,     0,     0,     0,     0,    51,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      52,    53,    54,    55,    56,    42,    43,    44,    45,     0,
       0,     0,    46,     0,    47,    48,     0,    49,     0,    50,
       0,     0,     0,     0,     0,    51,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    42,    43,    44,    45,
      52,    53,    54,    55,    56,    47,    48,     0,    49,     0,
      50,     0,     0,   267,     0,     0,    51,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    42,    43,    44,
      45,    52,    53,    54,    55,    56,    47,    48,     0,    49,
       0,    50,   255,     0,     0,     0,     0,    51,     0,   147,
     148,   149,     0,   150,   151,   152,   153,     0,     0,     0,
       0,     0,    52,    53,    54,    55,    56,   154,   155,   156,
     157,   158,     0,     0,     0,   159,   160,   161,   147,   148,
     149,     0,   150,   151,   152,   153,     0,   207,     0,     0,
       0,     0,     0,     0,     0,     0,   154,   155,   156,   157,
     158,     0,     0,     0,   159,   160,   161,   147,   148,   149,
       0,   150,   151,   152,   153,     0,   271,     0,     0,     0,
       0,     0,     0,     0,     0,   154,   155,   156,   157,   158,
       0,     0,     0,   159,   160,   161,   147,   148,   149,     0,
     150,   151,   152,   153,     0,   272,     0,     0,     0,     0,
       0,     0,     0,     0,   154,   155,   156,   157,   158,     0,
       0,     0,   159,   160,   161,   147,   148,   149,     0,   150,
     151,   152,   153,     0,   289,     0,     0,     0,     0,     0,
       0,     0,     0,   154,   155,   156,   157,   158,     0,     0,
       0,   159,   160,   161,   147,   148,   149,     0,   150,   151,
     152,   153,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   154,   155,   156,   157,   158,     0,     0,     0,
     159,   160,   161,   148,   149,     0,   150,   151,   152,   153,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     154,   155,   156,   157,   158,     0,     0,     0,   159,   160,
     161,   148,     0,     0,   150,   151,   152,   153,     0,     0,
       0,     0,     0,     0,     0,   150,   151,   152,   154,   155,
     156,   157,   158,     0,     0,     0,   159,   160,   161,   154,
     155,   156,   157,   158,     0,     0,     0,     0,   160,   161
  };

  const short int
  casmi_parser::yycheck_[] =
  {
      34,   171,   167,    34,   204,   196,   253,    53,    52,     9,
      52,     9,   146,    53,     9,    53,    49,    50,     3,    68,
      79,    49,    50,    52,    34,     0,    51,   197,    34,    67,
      79,    49,    50,    79,    50,    79,    61,    79,    79,    79,
      69,    58,    75,    76,    77,    52,    80,    81,    76,    29,
     297,    51,    52,    51,    59,    89,    51,    31,    76,    51,
      51,    79,    96,    97,    98,    79,    46,    59,    79,    49,
      61,   262,    12,    13,    14,    48,    16,    17,    18,    19,
      20,    21,    79,    23,    24,    79,    26,    27,    56,    51,
      30,    64,    65,   263,    34,    35,    36,    52,    38,    61,
      52,    51,    82,    83,    84,    51,   306,   307,    89,    59,
      48,    91,    92,    93,    79,    95,    56,   251,    81,   284,
      75,    76,    77,    75,    76,    77,    64,    65,    66,    53,
      48,   301,    50,    73,    97,    98,    79,   171,    79,    79,
     171,    51,    52,   177,   178,    51,    64,    65,    66,    59,
     124,   131,    57,    59,    61,   135,    61,    11,   328,   193,
     194,   171,    79,   197,    79,   171,   197,   147,   148,   149,
     150,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   317,    48,    49,    50,   197,   168,   163,
     164,   197,   208,   167,    64,    65,   177,   178,    62,    63,
      64,    65,    66,    76,    77,   185,    70,    71,    72,    52,
     190,    59,   193,   194,    53,   195,    61,    52,   252,   253,
      51,   255,   256,    75,    76,    77,    79,    53,   202,   263,
     210,    69,   263,    75,    76,    77,    68,   253,    79,    79,
      40,    41,    42,    43,    64,    79,    79,    47,    56,    49,
      50,   231,    52,   263,    54,    55,    79,   263,   232,    55,
      60,    67,    61,   297,    79,    57,    53,   301,    22,   249,
     301,   252,    52,    39,   248,    75,    76,    77,    78,    79,
      53,   297,   316,    64,    51,   319,   320,   321,   322,   323,
     324,   301,    76,    76,   328,   301,    61,   328,   278,   333,
      53,    51,    79,    48,    49,    50,   286,   281,    68,    48,
      49,    50,    51,   347,    55,    51,    68,    62,   328,    64,
      65,    66,   328,    62,    63,    64,    65,    66,    52,    29,
     310,    70,    71,    72,    53,   316,    59,    59,   319,   320,
     321,   322,   323,   324,     4,     5,     6,     7,     8,    59,
      10,    59,   333,    12,   334,    14,    15,    16,    17,    18,
      19,    20,    21,    59,    23,    24,   347,    26,    27,    53,
      53,    30,    12,   166,   199,    34,    35,    36,    12,    38,
      14,    35,    16,    17,    18,    19,    20,    21,   281,    23,
      24,   203,    26,    27,   306,   264,    30,    56,   172,   297,
      34,    35,    36,    -1,    38,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    73,    -1,    -1,    -1,    -1,    -1,
      79,    -1,    56,    57,    -1,    -1,    12,    -1,    14,    -1,
      16,    17,    18,    19,    20,    21,    -1,    23,    24,    73,
      26,    27,    -1,    -1,    30,    79,    -1,    -1,    34,    35,
      36,    12,    38,    14,    -1,    16,    17,    18,    19,    20,
      21,    -1,    23,    24,    -1,    26,    27,    -1,    -1,    30,
      56,    -1,    -1,    34,    35,    36,    -1,    38,    -1,    22,
      -1,    -1,    48,    49,    50,    -1,    -1,    73,    74,    -1,
      -1,    -1,    -1,    79,    -1,    56,    62,    63,    64,    65,
      66,    44,    45,    46,    -1,    48,    49,    50,    51,    22,
      -1,    -1,    73,    -1,    -1,    -1,    -1,    -1,    79,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    71,    72,
      -1,    44,    45,    46,    -1,    48,    49,    50,    51,    -1,
      -1,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    48,    49,    50,    70,    71,    72,
      44,    45,    46,    -1,    48,    49,    50,    51,    62,    63,
      64,    65,    66,    32,    33,    -1,    -1,    71,    62,    63,
      64,    65,    66,    42,    43,    32,    70,    71,    72,    -1,
      49,    50,    48,    49,    50,    42,    43,    -1,    -1,    -1,
      -1,    -1,    49,    50,    -1,    -1,    -1,    -1,    64,    65,
      66,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,
      79,    28,    -1,    -1,    -1,    -1,    -1,    -1,    75,    76,
      77,    78,    79,    -1,    -1,    -1,    -1,    44,    45,    46,
      -1,    48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    31,    -1,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    71,    72,    44,    45,    46,    -1,
      48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    -1,    49,    50,    -1,    52,    53,    54,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      75,    76,    77,    78,    79,    40,    41,    42,    43,    -1,
      -1,    -1,    47,    -1,    49,    50,    -1,    52,    -1,    54,
      -1,    -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      75,    76,    77,    78,    79,    49,    50,    -1,    52,    -1,
      54,    -1,    -1,    57,    -1,    -1,    60,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,
      43,    75,    76,    77,    78,    79,    49,    50,    -1,    52,
      -1,    54,    37,    -1,    -1,    -1,    -1,    60,    -1,    44,
      45,    46,    -1,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    75,    76,    77,    78,    79,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,    44,    45,
      46,    -1,    48,    49,    50,    51,    -1,    53,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    71,    72,    44,    45,    46,
      -1,    48,    49,    50,    51,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    71,    72,    44,    45,    46,    -1,
      48,    49,    50,    51,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    44,    45,    46,    -1,    48,
      49,    50,    51,    -1,    53,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    70,    71,    72,    44,    45,    46,    -1,    48,    49,
      50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      70,    71,    72,    45,    46,    -1,    48,    49,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    70,    71,
      72,    45,    -1,    -1,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    71,    72,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    -1,    71,    72
  };

  const unsigned char
  casmi_parser::yystos_[] =
  {
       0,     3,    81,    82,    79,     0,     4,     5,     6,     7,
       8,    10,    83,    84,    85,    86,    87,    88,    89,   117,
      79,    79,    79,    79,    79,    52,    79,    84,    58,    51,
      52,    59,    51,     9,    51,    52,    79,    90,    91,    59,
      92,    79,    40,    41,    42,    43,    47,    49,    50,    52,
      54,    60,    75,    76,    77,    78,    79,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   114,   115,    53,
      79,    93,    94,    95,    79,    97,    56,    52,   118,   119,
      12,    14,    16,    17,    18,    19,    20,    21,    23,    24,
      26,    27,    30,    34,    35,    36,    38,    56,    73,    79,
     115,   116,   120,   122,   123,   124,   125,   126,   127,   128,
     129,   132,   133,   134,   136,   137,   140,   141,   142,   143,
      53,    94,    53,    61,    68,    96,    97,    11,    99,    79,
     114,    52,    75,    76,    77,    52,    75,    76,    77,   114,
      55,   105,   112,   113,   114,    79,    52,    44,    45,    46,
      48,    49,    50,    51,    62,    63,    64,    65,    66,    70,
      71,    72,    51,    59,    59,    53,    61,    52,    51,    90,
      90,    51,    61,   120,   121,   133,   134,   135,   135,   114,
     114,   114,    79,    79,   121,    52,    79,   114,   114,   114,
      79,   114,   115,   135,   135,    69,     9,    51,    53,    79,
      79,    97,    68,    64,    56,   114,   114,    53,    67,    55,
      61,    53,   112,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,    97,
      97,    51,    59,    93,    49,    50,    97,    98,   106,   114,
      57,    53,   116,   119,    13,   121,    15,    51,    59,    22,
     114,    52,    28,    31,   114,    37,    39,    57,    74,   114,
     118,   116,     9,    51,    92,    97,    96,    57,   100,   101,
     102,    53,    53,    49,    50,   105,   114,    53,    51,   114,
      97,    61,    53,    53,    67,    68,   138,    97,   114,    53,
     112,   121,    32,    78,   104,   105,   115,   130,   131,   115,
     115,    51,   118,   116,    99,    57,    61,    68,    55,   114,
      51,    98,   106,    79,   114,    51,    25,    52,    53,    29,
      59,    59,    59,    59,    59,    33,   131,   116,    51,   101,
     102,   114,    53,    22,   139,   121,   112,   121,   121,   121,
     121,   121,   121,   116,   121,   114,    53,    22,   121
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
     103,   103,   103,   103,   103,   103,   103,   104,   104,   105,
     105,   105,   106,   106,   106,   107,   107,   107,   108,   108,
     108,   109,   110,   111,   111,   112,   112,   113,   113,   114,
     114,   114,   114,   114,   114,   114,   114,   114,   114,   114,
     114,   114,   114,   114,   114,   114,   115,   115,   115,   116,
     116,   116,   117,   117,   117,   117,   117,   117,   118,   118,
     119,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   121,   121,
     121,   122,   123,   124,   124,   125,   126,   127,   128,   129,
     130,   130,   131,   131,   131,   131,   131,   132,   132,   132,
     132,   133,   133,   134,   134,   135,   135,   136,   136,   138,
     137,   139,   137,   140,   141,   142,   143
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
       1,     1,     1,     2,     2,     1,     2,     2,     1,     2,
       2,     2,     5,     3,     2,     1,     2,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     1,     3,     4,     1,
       1,     1,     4,     6,     7,     6,     8,     9,     3,     1,
       5,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     1,     1,     2,     3,     3,     5,
       2,     1,     3,     3,     3,     3,     3,     7,     4,     5,
       2,     3,     3,     3,     3,     2,     1,     4,     6,     0,
       7,     0,     9,     4,     4,     6,     2
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
  "BOOLEAN", "NUMBER", "INTEGER_NUMBER", "FLOATING_NUMBER",
  "RATIONAL_NUMBER", "RULEREF", "NUMBER_RANGE", "LISTCONST",
  "EXPRESSION_LIST", "EXPRESSION_LIST_NO_COMMA", "EXPRESSION",
  "FUNCTION_SYNTAX", "RULE_STMT", "RULE_SYNTAX", "DUMPSPEC_LIST",
  "DUMPSPEC", "SIMPLE_STMT", "STATEMENT", "ASSERT_SYNTAX", "ASSURE_SYNTAX",
  "DIEDIE_SYNTAX", "IMPOSSIBLE_SYNTAX", "PRINT_SYNTAX", "DEBUG_SYNTAX",
  "UPDATE_SYNTAX", "CASE_SYNTAX", "CASE_LABEL_LIST", "CASE_LABEL",
  "CALL_SYNTAX", "SEQ_SYNTAX", "PAR_SYNTAX", "STATEMENTS", "IFTHENELSE",
  "LET_SYNTAX", "$@1", "$@2", "PUSH_SYNTAX", "POP_SYNTAX", "FORALL_SYNTAX",
  "ITERATE_SYNTAX", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  casmi_parser::yyrline_[] =
  {
       0,   335,   335,   343,   350,   355,   364,   368,   372,   392,
     409,   413,   432,   440,   445,   479,   484,   488,   492,   496,
     500,   508,   513,   518,   522,   529,   533,   541,   546,   555,
     561,   569,   575,   586,   590,   598,   603,   611,   616,   621,
     629,   652,   665,   687,   705,   710,   714,   722,   726,   734,
     738,   742,   751,   755,   763,   767,   771,   775,   779,   787,
     791,   795,   799,   803,   807,   811,   815,   823,   827,   834,
     838,   842,   850,   854,   858,   866,   870,   874,   882,   886,
     890,   899,   907,   923,   927,   935,   939,   947,   952,   961,
     965,   969,   973,   977,   981,   985,   989,   993,   997,  1001,
    1005,  1009,  1013,  1017,  1021,  1025,  1033,  1037,  1041,  1055,
    1059,  1063,  1073,  1077,  1081,  1085,  1090,  1095,  1104,  1109,
    1118,  1126,  1130,  1134,  1138,  1142,  1146,  1150,  1154,  1158,
    1162,  1166,  1170,  1174,  1178,  1182,  1186,  1190,  1210,  1214,
    1218,  1226,  1234,  1242,  1246,  1262,  1270,  1278,  1286,  1307,
    1315,  1320,  1329,  1333,  1337,  1341,  1345,  1353,  1357,  1361,
    1365,  1373,  1377,  1385,  1389,  1397,  1402,  1411,  1415,  1425,
    1424,  1442,  1441,  1462,  1477,  1500,  1508
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
#line 3540 "GrammarParser.cpp" // lalr1.cc:1167
#line 1514 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
