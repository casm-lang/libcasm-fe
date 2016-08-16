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
#line 63 "../../src/GrammarParser.yy" // lalr1.cc:413

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
      case 88: // SPECIFICATION
        value.move< Ast* > (that.value);
        break;

      case 90: // BODY_ELEMENTS
      case 146: // STATEMENTS
        value.move< AstListNode* > (that.value);
        break;

      case 91: // BODY_ELEMENT
      case 122: // RULE_STMT
      case 123: // RULE_SYNTAX
      case 126: // SIMPLE_STMT
      case 127: // STATEMENT
      case 131: // IMPOSSIBLE_SYNTAX
        value.move< AstNode* > (that.value);
        break;

      case 111: // VALUE
      case 113: // NUMBER
      case 115: // NUMBER_RANGE
        value.move< AtomNode* > (that.value);
        break;

      case 121: // FUNCTION_SYNTAX
        value.move< BaseFunctionAtom* > (that.value);
        break;

      case 143: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 136: // CASE_SYNTAX
        value.move< CaseNode* > (that.value);
        break;

      case 130: // DIEDIE_SYNTAX
        value.move< DiedieNode* > (that.value);
        break;

      case 95: // ENUM_SYNTAX
        value.move< Enum* > (that.value);
        break;

      case 110: // ATOM
      case 119: // EXPRESSION
      case 120: // BRACKET_EXPRESSION
        value.move< ExpressionBase* > (that.value);
        break;

      case 79: // FLOATINGCONST
        value.move< FLOATING_T > (that.value);
        break;

      case 153: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 80: // INTEGERCONST
        value.move< INTEGER_T > (that.value);
        break;

      case 147: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 92: // INIT_SYNTAX
        value.move< InitNode* > (that.value);
        break;

      case 112: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 148: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 152: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 132: // DEBUG_SYNTAX
      case 134: // PRINT_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 151: // PUSH_SYNTAX
        value.move< PushNode* > (that.value);
        break;

      case 89: // HEADER
        value.move< SpecificationNode* > (that.value);
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        value.move< Type* > (that.value);
        break;

      case 128: // ASSERT_SYNTAX
      case 129: // ASSURE_SYNTAX
      case 144: // SEQ_SYNTAX
      case 145: // PAR_SYNTAX
      case 154: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 135: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 81: // RATIONALCONST
        value.move< rational_t > (that.value);
        break;

      case 138: // CASE_LABEL
      case 139: // CASE_LABEL_DEFAULT
      case 140: // CASE_LABEL_NUMBER
      case 141: // CASE_LABEL_IDENT
      case 142: // CASE_LABEL_STRING
        value.move< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 109: // INITIALIZER
        value.move< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 125: // DUMPSPEC
        value.move< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 100: // FUNCTION_SIGNATURE
        value.move< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 82: // STRCONST
      case 83: // "identifier"
      case 114: // RULEREF
        value.move< std::string > (that.value);
        break;

      case 133: // DEBUG_ATOM_LIST
        value.move< std::vector<ExpressionBase*> > (that.value);
        break;

      case 116: // LISTCONST
      case 117: // EXPRESSION_LIST
      case 118: // EXPRESSION_LIST_NO_COMMA
        value.move< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 102: // PARAM_LIST
      case 103: // PARAM_LIST_NO_COMMA
      case 104: // TYPE_IDENTIFIER_STARLIST
      case 106: // TYPE_SYNTAX_LIST
        value.move< std::vector<Type*> > (that.value);
        break;

      case 137: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        value.move< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 124: // DUMPSPEC_LIST
        value.move< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 98: // IDENTIFIER_LIST
      case 99: // IDENTIFIER_LIST_NO_COMMA
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
      case 88: // SPECIFICATION
        value.copy< Ast* > (that.value);
        break;

      case 90: // BODY_ELEMENTS
      case 146: // STATEMENTS
        value.copy< AstListNode* > (that.value);
        break;

      case 91: // BODY_ELEMENT
      case 122: // RULE_STMT
      case 123: // RULE_SYNTAX
      case 126: // SIMPLE_STMT
      case 127: // STATEMENT
      case 131: // IMPOSSIBLE_SYNTAX
        value.copy< AstNode* > (that.value);
        break;

      case 111: // VALUE
      case 113: // NUMBER
      case 115: // NUMBER_RANGE
        value.copy< AtomNode* > (that.value);
        break;

      case 121: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (that.value);
        break;

      case 143: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 136: // CASE_SYNTAX
        value.copy< CaseNode* > (that.value);
        break;

      case 130: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (that.value);
        break;

      case 95: // ENUM_SYNTAX
        value.copy< Enum* > (that.value);
        break;

      case 110: // ATOM
      case 119: // EXPRESSION
      case 120: // BRACKET_EXPRESSION
        value.copy< ExpressionBase* > (that.value);
        break;

      case 79: // FLOATINGCONST
        value.copy< FLOATING_T > (that.value);
        break;

      case 153: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 80: // INTEGERCONST
        value.copy< INTEGER_T > (that.value);
        break;

      case 147: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 92: // INIT_SYNTAX
        value.copy< InitNode* > (that.value);
        break;

      case 112: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 148: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 152: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 132: // DEBUG_SYNTAX
      case 134: // PRINT_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 151: // PUSH_SYNTAX
        value.copy< PushNode* > (that.value);
        break;

      case 89: // HEADER
        value.copy< SpecificationNode* > (that.value);
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        value.copy< Type* > (that.value);
        break;

      case 128: // ASSERT_SYNTAX
      case 129: // ASSURE_SYNTAX
      case 144: // SEQ_SYNTAX
      case 145: // PAR_SYNTAX
      case 154: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 135: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 81: // RATIONALCONST
        value.copy< rational_t > (that.value);
        break;

      case 138: // CASE_LABEL
      case 139: // CASE_LABEL_DEFAULT
      case 140: // CASE_LABEL_NUMBER
      case 141: // CASE_LABEL_IDENT
      case 142: // CASE_LABEL_STRING
        value.copy< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 109: // INITIALIZER
        value.copy< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 125: // DUMPSPEC
        value.copy< std::pair<std::string, std::vector<std::string>> > (that.value);
        break;

      case 100: // FUNCTION_SIGNATURE
        value.copy< std::pair<std::vector<Type*>, Type*> > (that.value);
        break;

      case 82: // STRCONST
      case 83: // "identifier"
      case 114: // RULEREF
        value.copy< std::string > (that.value);
        break;

      case 133: // DEBUG_ATOM_LIST
        value.copy< std::vector<ExpressionBase*> > (that.value);
        break;

      case 116: // LISTCONST
      case 117: // EXPRESSION_LIST
      case 118: // EXPRESSION_LIST_NO_COMMA
        value.copy< std::vector<ExpressionBase*>* > (that.value);
        break;

      case 102: // PARAM_LIST
      case 103: // PARAM_LIST_NO_COMMA
      case 104: // TYPE_IDENTIFIER_STARLIST
      case 106: // TYPE_SYNTAX_LIST
        value.copy< std::vector<Type*> > (that.value);
        break;

      case 137: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        value.copy< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 124: // DUMPSPEC_LIST
        value.copy< std::vector<std::pair<std::string, std::vector<std::string>>> > (that.value);
        break;

      case 98: // IDENTIFIER_LIST
      case 99: // IDENTIFIER_LIST_NO_COMMA
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
    #line 53 "../../src/GrammarParser.yy" // lalr1.cc:741
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
      case 88: // SPECIFICATION
        yylhs.value.build< Ast* > ();
        break;

      case 90: // BODY_ELEMENTS
      case 146: // STATEMENTS
        yylhs.value.build< AstListNode* > ();
        break;

      case 91: // BODY_ELEMENT
      case 122: // RULE_STMT
      case 123: // RULE_SYNTAX
      case 126: // SIMPLE_STMT
      case 127: // STATEMENT
      case 131: // IMPOSSIBLE_SYNTAX
        yylhs.value.build< AstNode* > ();
        break;

      case 111: // VALUE
      case 113: // NUMBER
      case 115: // NUMBER_RANGE
        yylhs.value.build< AtomNode* > ();
        break;

      case 121: // FUNCTION_SYNTAX
        yylhs.value.build< BaseFunctionAtom* > ();
        break;

      case 143: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 136: // CASE_SYNTAX
        yylhs.value.build< CaseNode* > ();
        break;

      case 130: // DIEDIE_SYNTAX
        yylhs.value.build< DiedieNode* > ();
        break;

      case 95: // ENUM_SYNTAX
        yylhs.value.build< Enum* > ();
        break;

      case 110: // ATOM
      case 119: // EXPRESSION
      case 120: // BRACKET_EXPRESSION
        yylhs.value.build< ExpressionBase* > ();
        break;

      case 79: // FLOATINGCONST
        yylhs.value.build< FLOATING_T > ();
        break;

      case 153: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 80: // INTEGERCONST
        yylhs.value.build< INTEGER_T > ();
        break;

      case 147: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 92: // INIT_SYNTAX
        yylhs.value.build< InitNode* > ();
        break;

      case 112: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 148: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 152: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 132: // DEBUG_SYNTAX
      case 134: // PRINT_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 151: // PUSH_SYNTAX
        yylhs.value.build< PushNode* > ();
        break;

      case 89: // HEADER
        yylhs.value.build< SpecificationNode* > ();
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        yylhs.value.build< Type* > ();
        break;

      case 128: // ASSERT_SYNTAX
      case 129: // ASSURE_SYNTAX
      case 144: // SEQ_SYNTAX
      case 145: // PAR_SYNTAX
      case 154: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 135: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 81: // RATIONALCONST
        yylhs.value.build< rational_t > ();
        break;

      case 138: // CASE_LABEL
      case 139: // CASE_LABEL_DEFAULT
      case 140: // CASE_LABEL_NUMBER
      case 141: // CASE_LABEL_IDENT
      case 142: // CASE_LABEL_STRING
        yylhs.value.build< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 109: // INITIALIZER
        yylhs.value.build< std::pair<ExpressionBase*, ExpressionBase*> > ();
        break;

      case 125: // DUMPSPEC
        yylhs.value.build< std::pair<std::string, std::vector<std::string>> > ();
        break;

      case 100: // FUNCTION_SIGNATURE
        yylhs.value.build< std::pair<std::vector<Type*>, Type*> > ();
        break;

      case 82: // STRCONST
      case 83: // "identifier"
      case 114: // RULEREF
        yylhs.value.build< std::string > ();
        break;

      case 133: // DEBUG_ATOM_LIST
        yylhs.value.build< std::vector<ExpressionBase*> > ();
        break;

      case 116: // LISTCONST
      case 117: // EXPRESSION_LIST
      case 118: // EXPRESSION_LIST_NO_COMMA
        yylhs.value.build< std::vector<ExpressionBase*>* > ();
        break;

      case 102: // PARAM_LIST
      case 103: // PARAM_LIST_NO_COMMA
      case 104: // TYPE_IDENTIFIER_STARLIST
      case 106: // TYPE_SYNTAX_LIST
        yylhs.value.build< std::vector<Type*> > ();
        break;

      case 137: // CASE_LABEL_LIST
        yylhs.value.build< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        yylhs.value.build< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
        break;

      case 124: // DUMPSPEC_LIST
        yylhs.value.build< std::vector<std::pair<std::string, std::vector<std::string>>> > ();
        break;

      case 98: // IDENTIFIER_LIST
      case 99: // IDENTIFIER_LIST_NO_COMMA
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
#line 247 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
    driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
}
#line 1159 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 255 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
    yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, yystack_[0].value.as< std::string > () );
}
#line 1167 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 262 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
    yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
    yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
}
#line 1176 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 267 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
    yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
    yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
}
#line 1185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 274 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::PROVIDER); }
#line 1191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 275 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::OPTION); }
#line 1197 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 276 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new EnumDefNode(yylhs.location, yystack_[0].value.as< Enum* > ()); }
#line 1203 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 277 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< AstNode* > () = new FunctionDefNode(yylhs.location, yystack_[0].value.as< Function* > ());
                if (yystack_[0].value.as< Function* > ()->is_builtin()) {
                    driver.error(yylhs.location, "cannot use `"+yystack_[0].value.as< Function* > ()->name+"` as function identifier because it is a builtin name");
                }
                try {
                    driver.add(yystack_[0].value.as< Function* > ());
                } catch (const IdentifierAlreadyUsed& e) {
                    driver.error(yylhs.location, e.what());
                    // if another symbol with same name exists we need to delete
                    // the symbol here, because it is not inserted in the symbol table
                    delete yystack_[0].value.as< Function* > ();
                }
            }
#line 1222 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 291 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yystack_[0].value.as< Function* > ()->binding_offsets = std::move(driver.binding_offsets);
                driver.binding_offsets.clear();
                yylhs.value.as< AstNode* > () = new FunctionDefNode(yylhs.location, yystack_[0].value.as< Function* > ());
                try {
                    driver.add(yystack_[0].value.as< Function* > ());
                } catch (const IdentifierAlreadyUsed& e) {
                    driver.error(yylhs.location, e.what());
                    // if another symbol with same name exists we need to delete
                    // the symbol here, because it is not inserted in the symbol table
                    delete yystack_[0].value.as< Function* > ();
                }
            }
#line 1240 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 304 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > (); }
#line 1246 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 305 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
                // TODO check, we trust bison to pass only RuleNodes up
                try {
                    driver.add(reinterpret_cast<RuleNode*>(yystack_[0].value.as< AstNode* > ()));
                } catch (const IdentifierAlreadyUsed& e) {
                    driver.error(yylhs.location, e.what());
                    // we do not need to delete $1 here, because it's already in
                    // the AST, so it will be deleted later
                }
           }
#line 1262 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 320 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
    yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, yystack_[0].value.as< std::string > () );
}
#line 1270 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 333 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< Enum* > () = new Enum(yystack_[4].value.as< std::string > (), yylhs.location);
                try {
                    driver.function_table.add(yylhs.value.as< Enum* > ());
                } catch (const SymbolAlreadyExists& e) {
                    driver.error(yylhs.location, e.what());
                }
                for (const std::string& name : yystack_[1].value.as< std::vector<std::string> > ()) {
                    if (yylhs.value.as< Enum* > ()->add_enum_element(name)) {
                        try {
                            driver.function_table.add_enum_element(name, yylhs.value.as< Enum* > ());
                        } catch (const SymbolAlreadyExists& e) {
                            driver.error(yylhs.location, e.what());
                        }
                    } else {
                        driver.error(yylhs.location, "name `"+name+"` already used in enum");
                    }
                }
           }
#line 1294 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 354 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  // TODO: 2nd argument should be a reference
                  yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
                }
#line 1303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 358 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
                }
#line 1311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 361 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
                }
#line 1319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 365 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
                }
#line 1327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 368 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
                }
#line 1335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 371 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
                }
#line 1343 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 376 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[4].value.as< std::vector<std::string> > ());
                      yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
                   }
#line 1352 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 380 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > ());
                      yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
                   }
#line 1361 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 384 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
                   }
#line 1369 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 388 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr); }
#line 1375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 391 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ()); }
#line 1381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 392 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ()); }
#line 1387 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 395 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[2].value.as< std::vector<std::string> > ());
                            yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
                        }
#line 1396 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 399 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
                            yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
                        }
#line 1405 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 405 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    /* this constructor is implementation dependant! */
                    std::vector<Type*> foo;
                    yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
                  }
#line 1415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 411 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ()); }
#line 1421 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 414 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
        size_t size = driver.binding_offsets.size();
        driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
        yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
     }
#line 1431 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 419 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
        size_t size = driver.binding_offsets.size();
        driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
        // TODO: fail for rules without types and print warnings
        yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
     }
#line 1442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 428 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ()); }
#line 1448 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 429 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ()); }
#line 1454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 431 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                        yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
                        yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
                   }
#line 1463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 435 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ()); }
#line 1469 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 439 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
                            yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
                        }
#line 1478 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 443 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                          // TODO: limit memory size
                            yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
                        }
#line 1487 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 447 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
                        }
#line 1495 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 454 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Type* > () = new Type( yystack_[0].value.as< std::string > () );
	  
	  // TODO: FUTURE: integrate the IR-based type-list here to perform checks!,
	  //               or maybe we should check everything in the typecheckpass?
	  if( yystack_[0].value.as< std::string > ().compare( "Bit" ) == 0 )
	  {
		  driver.error
		  ( yylhs.location
		  , "missing bit-size for Bit type"
		  , libcasm_fe::Codes::TypeBitSyntaxError
		  );
	  }
  }
#line 1514 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 469 "../../src/GrammarParser.yy" // lalr1.cc:859
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
#line 1531 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 482 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Type* > () = new Type( yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<Type*> > () );
  }
#line 1539 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 486 "../../src/GrammarParser.yy" // lalr1.cc:859
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
#line 1557 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 502 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      yystack_[0].value.as< std::vector<Type*> > ().push_back(yystack_[2].value.as< Type* > ());
                      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
                    }
#line 1566 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 506 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ()); }
#line 1572 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 507 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ()); }
#line 1578 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 510 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); }
#line 1584 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 511 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = nullptr; }
#line 1590 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 514 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back(yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > ()); }
#line 1596 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 515 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); }
#line 1602 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 516 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = new std::vector<std::pair<ExpressionBase*, ExpressionBase*>>();
                    yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back(yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > ());
                }
#line 1611 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 523 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, yystack_[0].value.as< ExpressionBase* > ()); }
#line 1617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 524 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > ()); }
#line 1623 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 527 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > (); }
#line 1629 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 528 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > (); }
#line 1635 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 529 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > (); }
#line 1641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 532 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new RuleAtom(yylhs.location, std::move(yystack_[0].value.as< std::string > ())); }
#line 1647 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 533 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); }
#line 1653 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 534 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new StringAtom(yylhs.location, std::move(yystack_[0].value.as< std::string > ())); }
#line 1659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 535 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new ListAtom(yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > ()); }
#line 1665 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 536 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); }
#line 1671 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 537 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new IntegerAtom(yylhs.location, 0); }
#line 1677 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 538 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new SelfAtom(yylhs.location); }
#line 1683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 539 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new UndefAtom(yylhs.location); }
#line 1689 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 540 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new BooleanAtom(yylhs.location, true); }
#line 1695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 541 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new BooleanAtom(yylhs.location, false); }
#line 1701 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 544 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< IntegerAtom* > () = new IntegerAtom(yylhs.location, yystack_[0].value.as< INTEGER_T > ()); }
#line 1707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 545 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< IntegerAtom* > () = new IntegerAtom(yylhs.location, (-1) * yystack_[0].value.as< INTEGER_T > ()); }
#line 1713 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 546 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< IntegerAtom* > () = new IntegerAtom(yylhs.location, yystack_[0].value.as< INTEGER_T > ()); }
#line 1719 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 547 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > (); }
#line 1725 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 548 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new FloatingAtom(yylhs.location, yystack_[0].value.as< FLOATING_T > ()); }
#line 1731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 549 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new FloatingAtom(yylhs.location, (-1) * yystack_[0].value.as< FLOATING_T > ()); }
#line 1737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 550 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new FloatingAtom(yylhs.location, yystack_[0].value.as< FLOATING_T > ()); }
#line 1743 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 551 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new RationalAtom(yylhs.location, yystack_[0].value.as< rational_t > ()); }
#line 1749 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 552 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
          yystack_[0].value.as< rational_t > ().numerator *= -1;
          yylhs.value.as< AtomNode* > () = new RationalAtom(yylhs.location, yystack_[0].value.as< rational_t > ());
        }
#line 1758 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 556 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new RationalAtom(yylhs.location, yystack_[0].value.as< rational_t > ()); }
#line 1764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 559 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1770 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 562 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              if (yystack_[3].value.as< AtomNode* > ()->node_type_ == NodeType::INTEGER_ATOM && yystack_[1].value.as< AtomNode* > ()->node_type_ == NodeType::INTEGER_ATOM) {
                yylhs.value.as< AtomNode* > () = new NumberRangeAtom(yylhs.location, reinterpret_cast<IntegerAtom*>(yystack_[3].value.as< AtomNode* > ()), reinterpret_cast<IntegerAtom*>(yystack_[1].value.as< AtomNode* > ()));
              } else {
                driver.error(yylhs.location, "numbers in range expression must be Integer");
                yylhs.value.as< AtomNode* > () = nullptr;
              }
            }
#line 1783 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 573 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > (); }
#line 1789 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 574 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector<ExpressionBase*>(); }
#line 1795 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 578 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > (); }
#line 1801 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 579 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > (); }
#line 1807 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 581 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
                          yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back(yystack_[0].value.as< ExpressionBase* > ());
                        }
#line 1816 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 585 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector<ExpressionBase*>;
                          yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back(yystack_[0].value.as< ExpressionBase* > ());
                        }
#line 1825 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 593 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::ADD); }
#line 1831 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 595 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::SUB); }
#line 1837 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 597 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MUL); }
#line 1843 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 599 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::DIV); }
#line 1849 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 601 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MOD); }
#line 1855 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 603 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::RAT_DIV); }
#line 1861 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 605 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::NEQ); }
#line 1867 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 607 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::EQ); }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 609 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSER); }
#line 1879 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 611 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATER); }
#line 1885 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 613 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSEREQ); }
#line 1891 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 615 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATEREQ); }
#line 1897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 617 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::OR); }
#line 1903 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 619 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::XOR); }
#line 1909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 621 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::AND); }
#line 1915 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 623 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[0].value.as< ExpressionBase* > (), nullptr, ExpressionOperation::NOT);}
#line 1921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 624 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > (); }
#line 1927 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 627 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > (); }
#line 1933 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 630 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom(yylhs.location, yystack_[0].value.as< std::string > ()); }
#line 1939 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 631 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom(yylhs.location, yystack_[2].value.as< std::string > ()); }
#line 1945 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 633 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                   if( Builtin::isBuiltin( yystack_[3].value.as< std::string > () ) )
                   {
                       yylhs.value.as< BaseFunctionAtom* > () = new BuiltinAtom(yylhs.location, yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > ());
                   }
                   else
                   {
                       yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom(yylhs.location, yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > ());
                   }
               }
#line 1960 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 645 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 1966 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 646 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 1972 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 647 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              auto stmts = new AstListNode(yylhs.location, NodeType::STATEMENTS);
              stmts->add(yystack_[0].value.as< AstNode* > ());
              yylhs.value.as< AstNode* > () = new UnaryNode(yylhs.location, NodeType::PARBLOCK, stmts);
          }
#line 1982 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 654 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > ()); }
#line 1988 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 655 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > ());
           }
#line 1996 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 658 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > ());
           }
#line 2004 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 662 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                std::vector<Type*> tmp;
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ());
           }
#line 2013 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 666 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                std::vector<Type*> tmp;
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ());
           }
#line 2022 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 670 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                std::vector<Type*> tmp;
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ());
           }
#line 2031 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 676 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move(yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ()); yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back(yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > ()); }
#line 2037 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 677 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector<std::pair<std::string,std::vector<std::string>>>();
                yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back(std::move(yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > ()));
             }
#line 2046 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 683 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair<std::string, std::vector<std::string>>(yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > ());
        }
#line 2054 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 688 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2060 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 689 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2066 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 690 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > (); }
#line 2072 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 691 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > (); }
#line 2078 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 692 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > (); }
#line 2084 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 693 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > (); }
#line 2090 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 694 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > (); }
#line 2096 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 695 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > (); }
#line 2102 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 696 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > (); }
#line 2108 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 697 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > (); }
#line 2114 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 698 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > (); }
#line 2120 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 699 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > (); }
#line 2126 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 700 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > (); }
#line 2132 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 701 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > (); }
#line 2138 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 702 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2144 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 703 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::SKIP); }
#line 2150 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 704 "../../src/GrammarParser.yy" // lalr1.cc:859
    { driver.error(yylhs.location, "this call syntax is obsolete, use `call "+yystack_[0].value.as< std::string > ()+"`"); }
#line 2156 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 705 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::STATEMENT); }
#line 2162 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 706 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::STATEMENT);}
#line 2168 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 709 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > (); }
#line 2174 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 710 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2180 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 711 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2186 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 714 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > ()); }
#line 2192 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 716 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > ()); }
#line 2198 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 719 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< DiedieNode* > () = new DiedieNode(yylhs.location, yystack_[0].value.as< ExpressionBase* > ()); }
#line 2204 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 720 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< DiedieNode* > () = new DiedieNode(yylhs.location, nullptr); }
#line 2210 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 730 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(yylhs.location, NodeType::IMPOSSIBLE); }
#line 2216 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 733 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< PrintNode* > () = new PrintNode(yylhs.location, yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::vector<ExpressionBase*> > ()); }
#line 2222 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 736 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*> > () = std::move(yystack_[2].value.as< std::vector<ExpressionBase*> > ()); yylhs.value.as< std::vector<ExpressionBase*> > ().push_back(yystack_[0].value.as< ExpressionBase* > ()); }
#line 2228 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 737 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*> > ().push_back(yystack_[0].value.as< ExpressionBase* > ()); }
#line 2234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 739 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< PrintNode* > () = new PrintNode(yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*> > ()); }
#line 2240 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 742 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  if (yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::FUNCTION_ATOM) {
                    yylhs.value.as< UpdateNode* > () = new UpdateNode(yylhs.location, reinterpret_cast<FunctionAtom*>(yystack_[2].value.as< BaseFunctionAtom* > ()), yystack_[0].value.as< ExpressionBase* > ());
                  } else {
                    driver.error(yylhs.location, "can only use functions for updates but `"+
                                     yystack_[2].value.as< BaseFunctionAtom* > ()->to_str()+"` is a `"+type_to_str(yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_));
                  }
                }
#line 2253 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 752 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< CaseNode* > () = new CaseNode(yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ());
           }
#line 2261 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 757 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move(yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ());
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back(yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ());
               }
#line 2270 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 761 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move(std::vector<std::pair<AtomNode*, AstNode*>>());
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back(yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ());
               }
#line 2279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 767 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () =yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 768 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2291 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 769 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2297 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 770 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 773 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(nullptr, yystack_[0].value.as< AstNode* > ());
                  }
#line 2311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 778 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > ());
                 }
#line 2319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 783 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(yystack_[2].value.as< BaseFunctionAtom* > (), yystack_[0].value.as< AstNode* > ());
                }
#line 2327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 788 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(new StringAtom(yylhs.location, std::move(yystack_[2].value.as< std::string > ())), yystack_[0].value.as< AstNode* > ());
                 }
#line 2335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 793 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > ()); }
#line 2341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 794 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, "", yystack_[1].value.as< ExpressionBase* > ()); }
#line 2347 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 795 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > ()); }
#line 2353 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 796 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, yystack_[0].value.as< std::string > (), nullptr); }
#line 2359 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 799 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > ());
          }
#line 2367 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 802 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > ());
          }
#line 2375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 807 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > ());
          }
#line 2383 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 810 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > ());
          }
#line 2391 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 815 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ()); yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > (); }
#line 2397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 816 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::STATEMENTS); yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ()); }
#line 2403 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 819 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr);
          }
#line 2411 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 822 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode(yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > ());
          }
#line 2419 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 828 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                auto var = Symbol(yystack_[1].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET);
                try {
                    driver.function_table.add(&var);
                } catch (const SymbolAlreadyExists& e) {
                    driver.error(yylhs.location, e.what());
                }
            }
#line 2432 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 836 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              driver.function_table.remove(yystack_[5].value.as< std::string > ());
              yylhs.value.as< LetNode* > () = new LetNode(yylhs.location, Type(TypeType::UNKNOWN), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > ());
          }
#line 2441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 841 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                auto var = Symbol(yystack_[3].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET);
                try {
                    driver.function_table.add(&var);
                } catch (const SymbolAlreadyExists& e) {
                    driver.error(yylhs.location, e.what());
                }
            }
#line 2454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 849 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              driver.function_table.remove(yystack_[7].value.as< std::string > ());
              yylhs.value.as< LetNode* > () = new LetNode(yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > ());
          }
#line 2463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 855 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                if (yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(yylhs.location, "cannot push to builtin `"+yystack_[0].value.as< BaseFunctionAtom* > ()->to_str()+"`");
                } else {
                    yylhs.value.as< PushNode* > () = new PushNode(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), reinterpret_cast<FunctionAtom*>(yystack_[0].value.as< BaseFunctionAtom* > ()));
                }
          }
#line 2475 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 865 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                if (yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(yylhs.location, "cannot pop to builtin `"+yystack_[2].value.as< BaseFunctionAtom* > ()->to_str()+"`");
                } else if (yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(yylhs.location, "cannot pop from builtin `"+yystack_[0].value.as< BaseFunctionAtom* > ()->to_str()+"`");
                } else {
                    yylhs.value.as< PopNode* > () = new PopNode(yylhs.location, reinterpret_cast<FunctionAtom*>(yystack_[2].value.as< BaseFunctionAtom* > ()), reinterpret_cast<FunctionAtom*>(yystack_[0].value.as< BaseFunctionAtom* > ()));
                }
          }
#line 2489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 181:
#line 876 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< ForallNode* > () = new ForallNode(yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > ());
             }
#line 2497 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 182:
#line 881 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > ()); }
#line 2503 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2507 "GrammarParser.cpp" // lalr1.cc:859
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
     -18,   -69,    41,   382,  -203,  -203,   -47,   -55,   -12,   -10,
      -7,     2,     5,   382,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,     7,    71,   -42,    91,   -14,  -203,  -203,    30,
    -203,  -203,   104,    97,   -44,   137,   309,   -38,    92,   111,
     116,   628,   -23,    99,   100,   106,    92,   126,   143,   122,
     131,  -203,   309,  -203,  -203,  -203,  -203,  -203,   107,   115,
     309,    37,   124,  -203,  -203,  -203,  -203,   144,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,   820,  -203,  -203,    39,   139,
    -203,   146,   140,   151,     7,     7,    -5,  -203,   309,   309,
     309,  -203,  -203,   628,   628,   132,   309,   930,   133,   309,
     134,   136,   628,   -45,   309,   309,   156,   628,   628,   -20,
     168,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203,
     -16,   159,   145,    71,  -203,  -203,   -49,    92,    92,   901,
     820,  -203,  -203,  -203,  -203,  -203,  -203,   428,  -203,   174,
     162,   158,   820,  -203,   285,   309,   309,   309,   309,   309,
     309,   309,   309,   309,   309,   309,   309,   309,   309,   309,
     309,    92,    92,    89,   149,   309,   164,   172,   628,   116,
     820,   820,   820,  -203,  -203,  -203,  -203,   386,   449,    90,
     544,  -203,   177,   930,   607,   212,   226,  -203,   309,   180,
     668,  -203,   166,   502,   565,   309,   116,   628,     0,  -203,
     137,   165,   167,   178,   185,   -28,  -203,  -203,  -203,    82,
    -203,   198,  -203,    78,  -203,   309,  -203,   189,   853,   853,
      29,  -203,   881,   881,   881,    29,    29,   881,   881,   881,
    -203,  -203,  -203,   820,   193,  -203,   309,    92,  -203,   820,
    -203,   204,  -203,  -203,  -203,  -203,  -203,  -203,    92,   628,
     930,   177,   134,   134,   309,   696,   309,   123,   194,  -203,
    -203,   820,    16,  -203,   116,   628,  -203,    92,  -203,   -29,
    -203,  -203,   930,   930,   195,   820,  -203,   309,   820,   197,
     181,   309,   202,   241,  -203,  -203,  -203,   730,   203,   201,
     206,   208,   209,   210,    13,  -203,  -203,  -203,  -203,  -203,
    -203,   628,    24,  -203,  -203,   207,  -203,  -203,  -203,   820,
     309,  -203,   759,  -203,   628,   628,   309,  -203,   628,   628,
     628,   628,  -203,  -203,  -203,   628,  -203,   820,   628,   309,
    -203,  -203,   217,  -203,  -203,  -203,  -203,  -203,  -203,   792,
    -203,   628,  -203
  };

  const unsigned char
  casmi_parser::yydefact_[] =
  {
       0,     0,     0,     0,     3,     1,     0,     0,     0,     0,
       0,     0,     0,     2,     5,    11,     6,     7,     8,    10,
       9,    12,     0,     0,     0,     0,     0,    14,    13,     0,
       4,    30,     0,    28,     0,    26,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    27,     0,    42,     0,    41,
       0,    25,     0,    65,    66,    67,    68,    64,     0,     0,
       0,     0,     0,    75,    71,    78,    61,   105,   103,    57,
      72,    60,    59,    63,    62,    18,    58,    56,     0,    34,
      38,     0,    35,     0,     0,     0,     0,   118,     0,     0,
     145,   146,   135,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   136,
       0,   111,   110,   120,   121,   122,   123,   124,   125,   126,
     127,   128,   108,   109,   129,   130,   131,   132,   133,   134,
       0,     0,     0,     0,    29,    31,     0,     0,    40,     0,
     102,    73,    69,    76,    74,    70,    77,     0,    82,    60,
       0,    83,    86,    79,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    36,     0,     0,     0,     0,     0,
     142,   143,   144,   139,   172,   140,   141,     0,     0,     0,
       0,   149,   150,     0,     0,     0,     0,   182,     0,   166,
       0,   137,     0,     0,     0,     0,     0,     0,     0,    15,
      24,     0,     0,    48,     0,     0,    32,    39,    50,     0,
      53,    54,   104,     0,    81,    84,   106,     0,   101,    99,
     100,    92,    93,    97,    98,    87,    88,    94,    95,    96,
      89,    90,    91,    19,     0,    33,     0,     0,    37,    21,
      16,     0,   114,   117,   168,   171,   170,   175,     0,     0,
       0,   147,     0,     0,     0,     0,     0,     0,     0,   167,
     169,   151,     0,   112,     0,     0,    23,    47,    44,     0,
      43,    49,    52,     0,     0,    85,   107,     0,    17,     0,
       0,     0,     0,   173,   148,   179,   180,     0,   164,     0,
       0,     0,     0,     0,     0,   154,   155,   156,   157,   158,
     138,     0,     0,   113,    46,     0,    51,    55,    80,    22,
       0,   119,     0,   177,     0,     0,     0,   165,     0,     0,
       0,     0,   152,   153,   115,     0,    45,    20,     0,     0,
     174,   181,     0,   159,   162,   160,   161,   116,   176,     0,
     163,     0,   178
  };

  const short int
  casmi_parser::yypgoto_[] =
  {
    -203,  -203,  -203,  -203,   255,  -203,  -203,  -203,  -203,  -203,
    -203,    28,  -203,   141,    95,   231,  -203,   147,   -22,    -2,
      83,  -203,    10,   -82,  -203,  -131,   -58,  -203,  -203,  -203,
     -85,  -203,   -34,  -203,   -41,  -167,  -203,  -202,   117,   -40,
     -11,  -203,  -203,  -203,  -203,  -203,   105,  -203,  -203,  -203,
    -203,    -3,  -203,  -203,  -203,  -203,  -203,   -35,   -33,   -30,
    -203,  -203,  -203,  -203,  -203,  -203,  -203,  -203
  };

  const short int
  casmi_parser::yydefgoto_[] =
  {
      -1,     2,     3,    13,    14,    15,    16,    17,    18,    19,
      20,    32,    33,    35,    80,    81,    82,    48,    49,   214,
      51,   219,   220,    68,    69,    70,    71,    72,    73,    74,
     150,   151,   152,    76,    77,   111,    21,    86,    87,   183,
     184,   113,   114,   115,   116,   117,   192,   118,   119,   120,
     304,   305,   306,   307,   308,   309,   121,   185,   186,   187,
     124,   125,   291,   339,   126,   127,   128,   129
  };

  const short int
  casmi_parser::yytable_[] =
  {
     110,   112,    75,   149,   272,   215,   122,   206,   123,    40,
      46,   252,   211,   212,     4,   191,    83,    22,   140,   198,
     201,    36,    37,   274,   135,   279,   147,    78,    24,    38,
       1,    64,   211,   212,    47,  -105,    23,   280,   199,    47,
     273,     5,   130,    52,   154,    79,   300,   207,   332,    41,
      42,    64,   110,   110,   180,   181,   182,   221,   178,   195,
      79,   110,   190,   275,   188,   194,   110,   110,   179,   227,
     200,    25,   312,    26,    58,    59,    27,   203,   204,   311,
     158,    53,    54,    55,    56,    28,    57,   335,    29,   179,
      31,   197,    63,    64,    65,   301,    67,   179,    58,    59,
      43,    60,   170,    61,   148,   167,   168,   169,   313,    62,
     171,   191,   176,   177,   213,   216,    63,    64,    65,    66,
      67,   228,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   243,   110,   112,    58,
      59,   249,    34,   122,   334,   123,   110,   110,   315,   244,
     245,   281,   246,   257,    39,   282,   300,    63,    64,    65,
     247,   258,   110,   110,   265,   284,   110,   112,   347,    44,
      45,   271,   122,    50,   123,    47,   255,   255,   294,    84,
      85,   299,   132,   133,    58,    59,   141,   142,   143,   134,
     136,   285,   255,   255,   144,   145,   146,   137,   138,   139,
     221,   317,    63,    64,    65,   301,    67,   153,   154,   302,
     172,   173,   288,   174,   175,   189,   193,    67,   110,   196,
     202,   295,   296,   205,   208,   289,   303,   223,   209,   224,
     297,   225,    79,   250,   110,   112,   292,   251,   260,   263,
     122,   342,   123,   264,   266,   142,   302,   145,   293,   268,
     278,   277,   283,   319,   286,   213,   287,   322,   290,   310,
     320,   324,   318,   303,   321,   323,   327,   326,    30,   248,
     110,   112,   336,   131,   210,   314,   122,   328,   123,   329,
     330,   331,   350,   110,   110,   217,   337,   110,   110,   110,
     110,    52,   316,   276,   110,   112,   253,   110,   261,     0,
     122,   333,   123,     0,     0,   349,     0,     0,     0,     0,
     110,     0,     0,   340,   341,    52,     0,   343,   344,   345,
     346,     0,     0,     0,     0,     0,     0,   348,     0,    53,
      54,    55,    56,     0,    57,     0,     0,     0,     0,     0,
     352,     0,     0,     0,     0,     0,    58,    59,     0,    60,
     226,    61,     0,    53,    54,    55,    56,    62,    57,     0,
       0,     0,     0,     0,    63,    64,    65,    66,    67,     0,
      58,    59,     0,    60,     0,    61,     0,     0,     0,     0,
       0,    62,     0,     0,     0,     0,     0,     0,    63,    64,
      65,    66,    67,    88,    89,    90,    91,    92,    93,   254,
      94,     0,    95,     0,    96,     0,     0,    97,    98,     0,
      99,     0,   100,     0,   101,   102,     0,   103,   104,     6,
       7,     8,     9,    10,    11,    12,     0,     0,     0,     0,
       0,   155,   156,   157,     0,     0,   105,     0,   106,     0,
       0,     0,     0,     0,     0,   107,     0,     0,     0,     0,
       0,     0,     0,     0,   108,     0,    88,    89,    90,    91,
      92,    93,     0,    94,   256,    95,     0,    96,     0,   109,
      97,    98,     0,    99,     0,   100,     0,   101,   102,   158,
     103,   104,     0,     0,   159,   160,   161,     0,     0,   162,
     163,   164,     0,   222,     0,     0,     0,     0,     0,   105,
       0,   106,   165,   166,   167,   168,   169,     0,   107,    88,
      89,    90,    91,    92,    93,     0,    94,   108,    95,     0,
      96,     0,     0,    97,    98,     0,    99,     0,   100,     0,
     101,   102,   109,   103,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   155,   156,   157,
       0,     0,   105,     0,   106,     0,     0,     0,     0,     0,
       0,   107,   269,   259,     0,     0,     0,     0,     0,     0,
     108,     0,    88,    89,    90,    91,    92,    93,     0,    94,
       0,    95,     0,    96,     0,   109,    97,    98,     0,    99,
       0,   100,     0,   101,   102,   158,   103,   104,     0,     0,
     159,   160,   161,     0,     0,   162,   163,   164,     0,     0,
     155,   156,   157,     0,     0,   105,     0,   106,   165,   166,
     167,   168,   169,     0,   107,     0,     0,     0,     0,     0,
       0,     0,   262,   108,   270,    88,    89,    90,    91,    92,
      93,     0,    94,     0,    95,     0,    96,     0,   109,    97,
      98,     0,    99,     0,   100,     0,   101,   102,   158,   103,
     104,     0,     0,   159,   160,   161,     0,     0,   162,   163,
     164,   155,   156,   157,     0,     0,     0,     0,   105,     0,
     106,   165,   166,   167,   168,   169,     0,   107,     0,     0,
       0,     0,     0,     0,     0,     0,   108,     0,     0,   155,
     156,   157,   267,     0,     0,     0,     0,     0,     0,     0,
       0,   109,     0,     0,     0,     0,     0,     0,     0,   158,
       0,     0,     0,     0,   159,   160,   161,     0,     0,   162,
     163,   164,     0,   155,   156,   157,     0,     0,     0,     0,
       0,     0,   165,   166,   167,   168,   169,   158,     0,     0,
       0,     0,   159,   160,   161,     0,     0,   162,   163,   164,
     325,   298,   155,   156,   157,     0,     0,     0,     0,     0,
     165,   166,   167,   168,   169,     0,   338,     0,     0,     0,
       0,   158,     0,     0,     0,     0,   159,   160,   161,     0,
       0,   162,   163,   164,     0,   155,   156,   157,     0,     0,
       0,     0,     0,     0,   165,   166,   167,   168,   169,   351,
     158,     0,     0,     0,     0,   159,   160,   161,     0,     0,
     162,   163,   164,   155,   156,   157,     0,     0,     0,     0,
       0,     0,     0,   165,   166,   167,   168,   169,     0,     0,
       0,     0,     0,   158,     0,     0,     0,     0,   159,   160,
     161,     0,     0,   162,   163,   164,  -106,  -106,   157,     0,
       0,     0,     0,     0,     0,     0,   165,   166,   167,   168,
     169,   158,     0,     0,     0,     0,   159,   160,   161,     0,
       0,   162,   163,   164,     0,     0,   157,     0,     0,     0,
       0,     0,     0,     0,   165,   166,   167,   168,   169,     0,
       0,     0,     0,     0,   158,     0,     0,     0,     0,   159,
     160,   161,     0,     0,   162,   163,   164,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   165,   166,   167,
     168,   169,   158,     0,     0,     0,     0,  -106,  -106,  -106,
       0,     0,   162,   163,  -106,    53,    54,    55,    56,     0,
      57,     0,     0,     0,     0,  -106,  -106,   167,   168,   169,
       0,     0,    58,    59,     0,    60,     0,    61,     0,     0,
     218,     0,     0,    62,    53,    54,    55,    56,     0,    57,
      63,    64,    65,    66,    67,     0,     0,     0,     0,     0,
       0,    58,    59,     0,    60,     0,    61,     0,     0,     0,
       0,     0,    62,     0,     0,     0,     0,     0,     0,    63,
      64,    65,    66,    67
  };

  const short int
  casmi_parser::yycheck_[] =
  {
      41,    41,    36,    61,   206,   136,    41,    23,    41,    23,
      54,   178,    61,    62,    83,    97,    38,    64,    52,    64,
     105,    63,    64,    23,    46,    53,    60,    65,    83,    71,
      48,    80,    61,    62,    83,    55,    83,    65,    83,    83,
     207,     0,    65,     6,    64,    83,    33,    63,    35,    63,
      64,    80,    93,    94,    88,    89,    90,   139,    63,   100,
      83,   102,    96,    63,    94,    99,   107,   108,    73,   154,
     104,    83,   274,    83,    61,    62,    83,   107,   108,    63,
      51,    44,    45,    46,    47,    83,    49,    63,    83,    73,
      83,   102,    79,    80,    81,    82,    83,    73,    61,    62,
      70,    64,    63,    66,    67,    76,    77,    78,   275,    72,
      71,   193,    84,    85,   136,   137,    79,    80,    81,    82,
      83,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   166,   167,   168,   169,   170,   178,   178,    61,
      62,   175,    71,   178,   311,   178,   187,   188,   279,   171,
     172,    69,    63,    63,    63,    73,    33,    79,    80,    81,
      71,    71,   203,   204,   198,   223,   207,   207,   335,    65,
      73,   205,   207,    36,   207,    83,   187,   188,   260,    68,
      64,   266,    83,    83,    61,    62,    79,    80,    81,    83,
      64,   225,   203,   204,    79,    80,    81,    54,    76,    68,
     282,   283,    79,    80,    81,    82,    83,    83,    64,   267,
      71,    65,   246,    73,    63,    83,    83,    83,   259,    83,
      64,   262,   263,    55,    65,   247,   267,    53,    83,    67,
     264,    73,    83,    69,   275,   275,   258,    65,    61,    27,
     275,   326,   275,    17,    64,    80,   304,    80,   259,    83,
      65,    73,    54,   287,    65,   277,    63,   291,    54,    65,
      63,    20,    67,   304,    83,    63,    65,    64,    13,   174,
     311,   311,    65,    42,   133,   277,   311,    71,   311,    71,
      71,    71,    65,   324,   325,   138,   320,   328,   329,   330,
     331,     6,   282,   210,   335,   335,   179,   338,   193,    -1,
     335,   304,   335,    -1,    -1,   339,    -1,    -1,    -1,    -1,
     351,    -1,    -1,   324,   325,     6,    -1,   328,   329,   330,
     331,    -1,    -1,    -1,    -1,    -1,    -1,   338,    -1,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,
     351,    -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    64,
      65,    66,    -1,    44,    45,    46,    47,    72,    49,    -1,
      -1,    -1,    -1,    -1,    79,    80,    81,    82,    83,    -1,
      61,    62,    -1,    64,    -1,    66,    -1,    -1,    -1,    -1,
      -1,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,    80,
      81,    82,    83,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    16,    -1,    18,    -1,    -1,    21,    22,    -1,
      24,    -1,    26,    -1,    28,    29,    -1,    31,    32,    37,
      38,    39,    40,    41,    42,    43,    -1,    -1,    -1,    -1,
      -1,     3,     4,     5,    -1,    -1,    50,    -1,    52,    -1,
      -1,    -1,    -1,    -1,    -1,    59,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    68,    -1,     7,     8,     9,    10,
      11,    12,    -1,    14,    15,    16,    -1,    18,    -1,    83,
      21,    22,    -1,    24,    -1,    26,    -1,    28,    29,    51,
      31,    32,    -1,    -1,    56,    57,    58,    -1,    -1,    61,
      62,    63,    -1,    65,    -1,    -1,    -1,    -1,    -1,    50,
      -1,    52,    74,    75,    76,    77,    78,    -1,    59,     7,
       8,     9,    10,    11,    12,    -1,    14,    68,    16,    -1,
      18,    -1,    -1,    21,    22,    -1,    24,    -1,    26,    -1,
      28,    29,    83,    31,    32,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,     3,     4,     5,
      -1,    -1,    50,    -1,    52,    -1,    -1,    -1,    -1,    -1,
      -1,    59,    60,    19,    -1,    -1,    -1,    -1,    -1,    -1,
      68,    -1,     7,     8,     9,    10,    11,    12,    -1,    14,
      -1,    16,    -1,    18,    -1,    83,    21,    22,    -1,    24,
      -1,    26,    -1,    28,    29,    51,    31,    32,    -1,    -1,
      56,    57,    58,    -1,    -1,    61,    62,    63,    -1,    -1,
       3,     4,     5,    -1,    -1,    50,    -1,    52,    74,    75,
      76,    77,    78,    -1,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    25,    68,    69,     7,     8,     9,    10,    11,
      12,    -1,    14,    -1,    16,    -1,    18,    -1,    83,    21,
      22,    -1,    24,    -1,    26,    -1,    28,    29,    51,    31,
      32,    -1,    -1,    56,    57,    58,    -1,    -1,    61,    62,
      63,     3,     4,     5,    -1,    -1,    -1,    -1,    50,    -1,
      52,    74,    75,    76,    77,    78,    -1,    59,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    68,    -1,    -1,     3,
       4,     5,    34,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    83,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    51,
      -1,    -1,    -1,    -1,    56,    57,    58,    -1,    -1,    61,
      62,    63,    -1,     3,     4,     5,    -1,    -1,    -1,    -1,
      -1,    -1,    74,    75,    76,    77,    78,    51,    -1,    -1,
      -1,    -1,    56,    57,    58,    -1,    -1,    61,    62,    63,
      30,    65,     3,     4,     5,    -1,    -1,    -1,    -1,    -1,
      74,    75,    76,    77,    78,    -1,    17,    -1,    -1,    -1,
      -1,    51,    -1,    -1,    -1,    -1,    56,    57,    58,    -1,
      -1,    61,    62,    63,    -1,     3,     4,     5,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,    17,
      51,    -1,    -1,    -1,    -1,    56,    57,    58,    -1,    -1,
      61,    62,    63,     3,     4,     5,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    74,    75,    76,    77,    78,    -1,    -1,
      -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,    57,
      58,    -1,    -1,    61,    62,    63,     3,     4,     5,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,    77,
      78,    51,    -1,    -1,    -1,    -1,    56,    57,    58,    -1,
      -1,    61,    62,    63,    -1,    -1,     5,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,
      57,    58,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    74,    75,    76,
      77,    78,    51,    -1,    -1,    -1,    -1,    56,    57,    58,
      -1,    -1,    61,    62,    63,    44,    45,    46,    47,    -1,
      49,    -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,
      -1,    -1,    61,    62,    -1,    64,    -1,    66,    -1,    -1,
      69,    -1,    -1,    72,    44,    45,    46,    47,    -1,    49,
      79,    80,    81,    82,    83,    -1,    -1,    -1,    -1,    -1,
      -1,    61,    62,    -1,    64,    -1,    66,    -1,    -1,    -1,
      -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,    -1,    79,
      80,    81,    82,    83
  };

  const unsigned char
  casmi_parser::yystos_[] =
  {
       0,    48,    88,    89,    83,     0,    37,    38,    39,    40,
      41,    42,    43,    90,    91,    92,    93,    94,    95,    96,
      97,   123,    64,    83,    83,    83,    83,    83,    83,    83,
      91,    83,    98,    99,    71,   100,    63,    64,    71,    63,
      23,    63,    64,    70,    65,    73,    54,    83,   104,   105,
      36,   107,     6,    44,    45,    46,    47,    49,    61,    62,
      64,    66,    72,    79,    80,    81,    82,    83,   110,   111,
     112,   113,   114,   115,   116,   119,   120,   121,    65,    83,
     101,   102,   103,   105,    68,    64,   124,   125,     7,     8,
       9,    10,    11,    12,    14,    16,    18,    21,    22,    24,
      26,    28,    29,    31,    32,    50,    52,    59,    68,    83,
     121,   122,   126,   128,   129,   130,   131,   132,   134,   135,
     136,   143,   144,   145,   147,   148,   151,   152,   153,   154,
      65,   102,    83,    83,    83,   105,    64,    54,    76,    68,
     119,    79,    80,    81,    79,    80,    81,   119,    67,   113,
     117,   118,   119,    83,    64,     3,     4,     5,    51,    56,
      57,    58,    61,    62,    63,    74,    75,    76,    77,    78,
      63,    71,    71,    65,    73,    63,    98,    98,    63,    73,
     119,   119,   119,   126,   127,   144,   145,   146,   146,    83,
     119,   110,   133,    83,   119,   121,    83,   127,    64,    83,
     119,   117,    64,   146,   146,    55,    23,    63,    65,    83,
     100,    61,    62,   105,   106,   112,   105,   104,    69,   108,
     109,   110,    65,    53,    67,    73,    65,   117,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   105,   105,    63,    71,   101,   119,
      69,    65,   122,   125,    13,   127,    15,    63,    71,    19,
      61,   133,    25,    27,    17,   119,    64,    34,    83,    60,
      69,   119,   124,   122,    23,    63,   107,    73,    65,    53,
      65,    69,    73,    54,   113,   119,    65,    63,   119,   105,
      54,   149,   105,   127,   110,   121,   121,   119,    65,   117,
      33,    82,   113,   121,   137,   138,   139,   140,   141,   142,
      65,    63,   124,   122,   106,   112,   109,   110,    67,   119,
      63,    83,   119,    63,    20,    30,    64,    65,    71,    71,
      71,    71,    35,   138,   122,    63,    65,   119,    17,   150,
     127,   127,   117,   127,   127,   127,   127,   122,   127,   119,
      65,    17,   127
  };

  const unsigned char
  casmi_parser::yyr1_[] =
  {
       0,    87,    88,    89,    90,    90,    91,    91,    91,    91,
      91,    91,    91,    92,    93,    94,    95,    96,    96,    96,
      96,    96,    96,    97,    97,    97,    97,    98,    98,    99,
      99,   100,   100,   101,   101,   102,   102,   103,   103,   104,
     104,   104,   105,   105,   105,   105,   106,   106,   106,   107,
     107,   108,   108,   108,   109,   109,   110,   110,   110,   111,
     111,   111,   111,   111,   111,   111,   111,   111,   111,   112,
     112,   112,   113,   113,   113,   113,   113,   113,   113,   114,
     115,   116,   116,   117,   117,   118,   118,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   120,   121,   121,   121,   122,   122,
     122,   123,   123,   123,   123,   123,   123,   124,   124,   125,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   127,
     127,   127,   128,   129,   130,   130,   131,   132,   133,   133,
     134,   135,   136,   137,   137,   138,   138,   138,   138,   139,
     140,   141,   142,   143,   143,   143,   143,   144,   144,   145,
     145,   146,   146,   147,   147,   149,   148,   150,   148,   151,
     152,   153,   154
  };

  const unsigned char
  casmi_parser::yyr2_[] =
  {
       0,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     5,     6,     7,     4,     6,
       9,     6,     8,     7,     6,     4,     3,     2,     1,     3,
       1,     3,     4,     3,     1,     1,     2,     3,     1,     3,
       2,     1,     1,     4,     4,     6,     3,     2,     1,     4,
       3,     3,     2,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     2,     2,     1,     2,     2,     1,     2,
       5,     3,     2,     1,     2,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     1,     3,     1,     3,     4,     1,     1,
       1,     4,     6,     7,     6,     8,     9,     3,     1,     5,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     2,     4,     1,
       1,     1,     2,     2,     2,     1,     1,     3,     3,     1,
       2,     3,     5,     2,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     7,     4,     5,     2,     3,     3,     3,
       3,     2,     1,     4,     6,     0,     7,     0,     9,     4,
       4,     6,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const casmi_parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "AND", "OR", "XOR", "NOT",
  "ASSERT", "ASSURE", "DIEDIE", "IMPOSSIBLE", "SKIP", "SEQ", "ENDSEQ",
  "PAR", "ENDPAR", "LET", "IN", "IF", "THEN", "ELSE", "PRINT", "DEBUG",
  "DUMPS", "PUSH", "INTO", "POP", "FROM", "FORALL", "ITERATE", "DO",
  "CALL", "CASE", "DEFAULT", "OF", "ENDCASE", "INITIALLY", "FUNCTION",
  "DERIVED", "ENUM", "RULE", "PROVIDER", "INIT", "OPTION", "SELF", "UNDEF",
  "TRUE", "FALSE", "CASM", "SYMBOL", "INTERN", "RATIONAL_DIV", "OBJDUMP",
  "DOTDOT", "ARROW", "UPDATE", "NEQUAL", "LESSEQ", "GREATEREQ",
  "SEQ_BRACKET", "ENDSEQ_BRACKET", "\"+\"", "\"-\"", "\"=\"", "\"(\"",
  "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\".\"", "\":\"", "\"@\"",
  "\",\"", "\"<\"", "\">\"", "\"*\"", "\"/\"", "\"%\"", "FLOATINGCONST",
  "INTEGERCONST", "RATIONALCONST", "STRCONST", "\"identifier\"", "UMINUS",
  "UPLUS", "XIF", "$accept", "SPECIFICATION", "HEADER", "BODY_ELEMENTS",
  "BODY_ELEMENT", "INIT_SYNTAX", "PROVIDER_SYNTAX", "OPTION_SYNTAX",
  "ENUM_SYNTAX", "DERIVED_SYNTAX", "FUNCTION_DEFINITION",
  "IDENTIFIER_LIST", "IDENTIFIER_LIST_NO_COMMA", "FUNCTION_SIGNATURE",
  "PARAM", "PARAM_LIST", "PARAM_LIST_NO_COMMA", "TYPE_IDENTIFIER_STARLIST",
  "TYPE_SYNTAX", "TYPE_SYNTAX_LIST", "INITIALIZERS", "INITIALIZER_LIST",
  "INITIALIZER", "ATOM", "VALUE", "INTEGER_NUMBER", "NUMBER", "RULEREF",
  "NUMBER_RANGE", "LISTCONST", "EXPRESSION_LIST",
  "EXPRESSION_LIST_NO_COMMA", "EXPRESSION", "BRACKET_EXPRESSION",
  "FUNCTION_SYNTAX", "RULE_STMT", "RULE_SYNTAX", "DUMPSPEC_LIST",
  "DUMPSPEC", "SIMPLE_STMT", "STATEMENT", "ASSERT_SYNTAX", "ASSURE_SYNTAX",
  "DIEDIE_SYNTAX", "IMPOSSIBLE_SYNTAX", "DEBUG_SYNTAX", "DEBUG_ATOM_LIST",
  "PRINT_SYNTAX", "UPDATE_SYNTAX", "CASE_SYNTAX", "CASE_LABEL_LIST",
  "CASE_LABEL", "CASE_LABEL_DEFAULT", "CASE_LABEL_NUMBER",
  "CASE_LABEL_IDENT", "CASE_LABEL_STRING", "CALL_SYNTAX", "SEQ_SYNTAX",
  "PAR_SYNTAX", "STATEMENTS", "IFTHENELSE", "LET_SYNTAX", "$@1", "$@2",
  "PUSH_SYNTAX", "POP_SYNTAX", "FORALL_SYNTAX", "ITERATE_SYNTAX", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  casmi_parser::yyrline_[] =
  {
       0,   246,   246,   254,   261,   266,   274,   275,   276,   277,
     291,   304,   305,   319,   326,   330,   333,   354,   358,   361,
     365,   368,   371,   376,   380,   384,   387,   391,   392,   395,
     399,   405,   410,   414,   419,   428,   429,   431,   435,   439,
     443,   447,   453,   468,   481,   485,   502,   506,   507,   510,
     511,   514,   515,   516,   523,   524,   527,   528,   529,   532,
     533,   534,   535,   536,   537,   538,   539,   540,   541,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   556,   559,
     562,   573,   574,   578,   579,   581,   585,   592,   594,   596,
     598,   600,   602,   604,   606,   608,   610,   612,   614,   616,
     618,   620,   622,   624,   627,   630,   631,   632,   645,   646,
     647,   654,   655,   658,   662,   666,   670,   676,   677,   683,
     688,   689,   690,   691,   692,   693,   694,   695,   696,   697,
     698,   699,   700,   701,   702,   703,   704,   705,   706,   709,
     710,   711,   714,   716,   719,   720,   730,   733,   736,   737,
     739,   742,   752,   757,   761,   767,   768,   769,   770,   773,
     778,   783,   788,   793,   794,   795,   796,   799,   802,   807,
     810,   815,   816,   819,   822,   828,   827,   841,   840,   855,
     865,   876,   881
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
#line 3270 "GrammarParser.cpp" // lalr1.cc:1167
#line 885 "../../src/GrammarParser.yy" // lalr1.cc:1168


void yy::casmi_parser::error
( const location_type& l
, const std::string& m
)
{
    driver.error (l, m, libcasm_fe::Codes::SyntaxError );
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
