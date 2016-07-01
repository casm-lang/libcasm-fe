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
#line 62 "../../src/GrammarParser.yy" // lalr1.cc:413

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
      case 144: // STATEMENTS
        value.move< AstListNode* > (that.value);
        break;

      case 91: // BODY_ELEMENT
      case 122: // RULE_SYNTAX
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
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

      case 141: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 134: // CASE_SYNTAX
        value.move< CaseNode* > (that.value);
        break;

      case 128: // DIEDIE_SYNTAX
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

      case 151: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 80: // INTEGERCONST
        value.move< INTEGER_T > (that.value);
        break;

      case 145: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 92: // INIT_SYNTAX
        value.move< InitNode* > (that.value);
        break;

      case 112: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 146: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 150: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 130: // DEBUG_SYNTAX
      case 132: // PRINT_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 149: // PUSH_SYNTAX
        value.move< PushNode* > (that.value);
        break;

      case 89: // HEADER
        value.move< SpecificationNode* > (that.value);
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        value.move< Type* > (that.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 142: // SEQ_SYNTAX
      case 143: // PAR_SYNTAX
      case 152: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 133: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 81: // RATIONALCONST
        value.move< rational_t > (that.value);
        break;

      case 136: // CASE_LABEL
      case 137: // CASE_LABEL_DEFAULT
      case 138: // CASE_LABEL_NUMBER
      case 139: // CASE_LABEL_IDENT
      case 140: // CASE_LABEL_STRING
        value.move< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 109: // INITIALIZER
        value.move< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 124: // DUMPSPEC
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

      case 131: // DEBUG_ATOM_LIST
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

      case 135: // CASE_LABEL_LIST
        value.move< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        value.move< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 123: // DUMPSPEC_LIST
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
      case 144: // STATEMENTS
        value.copy< AstListNode* > (that.value);
        break;

      case 91: // BODY_ELEMENT
      case 122: // RULE_SYNTAX
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
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

      case 141: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 134: // CASE_SYNTAX
        value.copy< CaseNode* > (that.value);
        break;

      case 128: // DIEDIE_SYNTAX
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

      case 151: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 80: // INTEGERCONST
        value.copy< INTEGER_T > (that.value);
        break;

      case 145: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 92: // INIT_SYNTAX
        value.copy< InitNode* > (that.value);
        break;

      case 112: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 146: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 150: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 130: // DEBUG_SYNTAX
      case 132: // PRINT_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 149: // PUSH_SYNTAX
        value.copy< PushNode* > (that.value);
        break;

      case 89: // HEADER
        value.copy< SpecificationNode* > (that.value);
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        value.copy< Type* > (that.value);
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 142: // SEQ_SYNTAX
      case 143: // PAR_SYNTAX
      case 152: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 133: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 81: // RATIONALCONST
        value.copy< rational_t > (that.value);
        break;

      case 136: // CASE_LABEL
      case 137: // CASE_LABEL_DEFAULT
      case 138: // CASE_LABEL_NUMBER
      case 139: // CASE_LABEL_IDENT
      case 140: // CASE_LABEL_STRING
        value.copy< std::pair<AtomNode*, AstNode*> > (that.value);
        break;

      case 109: // INITIALIZER
        value.copy< std::pair<ExpressionBase*, ExpressionBase*> > (that.value);
        break;

      case 124: // DUMPSPEC
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

      case 131: // DEBUG_ATOM_LIST
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

      case 135: // CASE_LABEL_LIST
        value.copy< std::vector<std::pair<AtomNode*, AstNode*>> > (that.value);
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        value.copy< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (that.value);
        break;

      case 123: // DUMPSPEC_LIST
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
    #line 52 "../../src/GrammarParser.yy" // lalr1.cc:741
{
  // Initialize the initial location.
  // Error messages are printed in Driver, I guess location does not
  // need to know about the filename
  // @$.begin.filename = @$.end.filename = driver.get_filename_ptr();
}

#line 861 "GrammarParser.cpp" // lalr1.cc:741

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
      case 144: // STATEMENTS
        yylhs.value.build< AstListNode* > ();
        break;

      case 91: // BODY_ELEMENT
      case 122: // RULE_SYNTAX
      case 125: // STATEMENT
      case 129: // IMPOSSIBLE_SYNTAX
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

      case 141: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 134: // CASE_SYNTAX
        yylhs.value.build< CaseNode* > ();
        break;

      case 128: // DIEDIE_SYNTAX
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

      case 151: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 96: // DERIVED_SYNTAX
      case 97: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 80: // INTEGERCONST
        yylhs.value.build< INTEGER_T > ();
        break;

      case 145: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 92: // INIT_SYNTAX
        yylhs.value.build< InitNode* > ();
        break;

      case 112: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 146: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 150: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 130: // DEBUG_SYNTAX
      case 132: // PRINT_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 149: // PUSH_SYNTAX
        yylhs.value.build< PushNode* > ();
        break;

      case 89: // HEADER
        yylhs.value.build< SpecificationNode* > ();
        break;

      case 101: // PARAM
      case 105: // TYPE_SYNTAX
        yylhs.value.build< Type* > ();
        break;

      case 126: // ASSERT_SYNTAX
      case 127: // ASSURE_SYNTAX
      case 142: // SEQ_SYNTAX
      case 143: // PAR_SYNTAX
      case 152: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 133: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 81: // RATIONALCONST
        yylhs.value.build< rational_t > ();
        break;

      case 136: // CASE_LABEL
      case 137: // CASE_LABEL_DEFAULT
      case 138: // CASE_LABEL_NUMBER
      case 139: // CASE_LABEL_IDENT
      case 140: // CASE_LABEL_STRING
        yylhs.value.build< std::pair<AtomNode*, AstNode*> > ();
        break;

      case 109: // INITIALIZER
        yylhs.value.build< std::pair<ExpressionBase*, ExpressionBase*> > ();
        break;

      case 124: // DUMPSPEC
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

      case 131: // DEBUG_ATOM_LIST
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

      case 135: // CASE_LABEL_LIST
        yylhs.value.build< std::vector<std::pair<AtomNode*, AstNode*>> > ();
        break;

      case 107: // INITIALIZERS
      case 108: // INITIALIZER_LIST
        yylhs.value.build< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
        break;

      case 123: // DUMPSPEC_LIST
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
#line 246 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
    driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
}
#line 1153 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 254 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
    yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, yystack_[0].value.as< std::string > () );
}
#line 1161 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 261 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
    yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
    yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
}
#line 1170 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 266 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
    yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
    yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
}
#line 1179 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 273 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::PROVIDER); }
#line 1185 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 274 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::OPTION); }
#line 1191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 275 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new EnumDefNode(yylhs.location, yystack_[0].value.as< Enum* > ()); }
#line 1197 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 276 "../../src/GrammarParser.yy" // lalr1.cc:859
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
#line 1216 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 290 "../../src/GrammarParser.yy" // lalr1.cc:859
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
#line 1234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 303 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > (); }
#line 1240 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 304 "../../src/GrammarParser.yy" // lalr1.cc:859
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
#line 1256 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 319 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
    yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, yystack_[0].value.as< std::string > () );
}
#line 1264 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 332 "../../src/GrammarParser.yy" // lalr1.cc:859
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
#line 1288 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 353 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  // TODO: 2nd argument should be a reference
                  yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
                }
#line 1297 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 357 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
                }
#line 1305 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 360 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
                }
#line 1313 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 364 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
                }
#line 1321 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 367 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
                }
#line 1329 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 370 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
                }
#line 1337 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 375 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[4].value.as< std::vector<std::string> > ());
                      yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
                   }
#line 1346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 379 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > ());
                      yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
                   }
#line 1355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 383 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
                   }
#line 1363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 387 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr); }
#line 1369 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 390 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ()); }
#line 1375 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 391 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ()); }
#line 1381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 394 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[2].value.as< std::vector<std::string> > ());
                            yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
                        }
#line 1390 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 398 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
                            yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
                        }
#line 1399 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 404 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    /* this constructor is implementation dependant! */
                    std::vector<Type*> foo;
                    yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
                  }
#line 1409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 410 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ()); }
#line 1415 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 413 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
        size_t size = driver.binding_offsets.size();
        driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
        yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
     }
#line 1425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 418 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
        size_t size = driver.binding_offsets.size();
        driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
        // TODO: fail for rules without types and print warnings
        yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
     }
#line 1436 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 427 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ()); }
#line 1442 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 428 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ()); }
#line 1448 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 430 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                        yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
                        yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
                   }
#line 1457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 434 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ()); }
#line 1463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 438 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
                            yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
                        }
#line 1472 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 442 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                          // TODO: limit memory size
                            yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
                        }
#line 1481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 446 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                            yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
                        }
#line 1489 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 451 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< Type* > () = new Type(yystack_[0].value.as< std::string > ()); /* TODO check invalid types */}
#line 1495 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 452 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
               yylhs.value.as< Type* > () = new Type(yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<Type*> > ());
           }
#line 1503 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 455 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
               yylhs.value.as< Type* > () = new Type(yystack_[5].value.as< std::string > ());
               yylhs.value.as< Type* > ()->subrange_start = yystack_[3].value.as< IntegerAtom* > ()->val_;
               yylhs.value.as< Type* > ()->subrange_end = yystack_[1].value.as< IntegerAtom* > ()->val_;
               if (yylhs.value.as< Type* > ()->subrange_start >= yylhs.value.as< Type* > ()->subrange_end) {
                   driver.error(yylhs.location, "start of subrange must be smaller than the end");
               }
           }
#line 1516 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 465 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
               yylhs.value.as< Type* > () = new Type( yystack_[3].value.as< std::string > () );
               yylhs.value.as< Type* > ()->bitsize = yystack_[1].value.as< IntegerAtom* > ()->val_;
               if( yylhs.value.as< Type* > ()->bitsize < 0 || yylhs.value.as< Type* > ()->bitsize > 256 )
               {
                   driver.error(yylhs.location, "invalid size for Bit type");
               }
           }
#line 1529 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 475 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                      yystack_[0].value.as< std::vector<Type*> > ().push_back(yystack_[2].value.as< Type* > ());
                      yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
                    }
#line 1538 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 479 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ()); }
#line 1544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 480 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ()); }
#line 1550 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 483 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); }
#line 1556 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 484 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = nullptr; }
#line 1562 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 487 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back(yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > ()); }
#line 1568 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 488 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); }
#line 1574 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 489 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = new std::vector<std::pair<ExpressionBase*, ExpressionBase*>>();
                    yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back(yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > ());
                }
#line 1583 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 496 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, yystack_[0].value.as< ExpressionBase* > ()); }
#line 1589 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 497 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > ()); }
#line 1595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 500 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > (); }
#line 1601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 501 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > (); }
#line 1607 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 502 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > (); }
#line 1613 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 505 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new RuleAtom(yylhs.location, std::move(yystack_[0].value.as< std::string > ())); }
#line 1619 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 506 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); }
#line 1625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 507 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new StringAtom(yylhs.location, std::move(yystack_[0].value.as< std::string > ())); }
#line 1631 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 508 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new ListAtom(yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > ()); }
#line 1637 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 509 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > (); }
#line 1643 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 510 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new IntegerAtom(yylhs.location, 0); }
#line 1649 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 511 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new SelfAtom(yylhs.location); }
#line 1655 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 512 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new UndefAtom(yylhs.location); }
#line 1661 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 513 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new BooleanAtom(yylhs.location, true); }
#line 1667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 514 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new BooleanAtom(yylhs.location, false); }
#line 1673 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 517 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< IntegerAtom* > () = new IntegerAtom(yylhs.location, yystack_[0].value.as< INTEGER_T > ()); }
#line 1679 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 518 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< IntegerAtom* > () = new IntegerAtom(yylhs.location, (-1) * yystack_[0].value.as< INTEGER_T > ()); }
#line 1685 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 519 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< IntegerAtom* > () = new IntegerAtom(yylhs.location, yystack_[0].value.as< INTEGER_T > ()); }
#line 1691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 520 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > (); }
#line 1697 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 521 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new FloatingAtom(yylhs.location, yystack_[0].value.as< FLOATING_T > ()); }
#line 1703 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 522 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new FloatingAtom(yylhs.location, (-1) * yystack_[0].value.as< FLOATING_T > ()); }
#line 1709 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 523 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new FloatingAtom(yylhs.location, yystack_[0].value.as< FLOATING_T > ()); }
#line 1715 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 524 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new RationalAtom(yylhs.location, yystack_[0].value.as< rational_t > ()); }
#line 1721 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 525 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
          yystack_[0].value.as< rational_t > ().numerator *= -1;
          yylhs.value.as< AtomNode* > () = new RationalAtom(yylhs.location, yystack_[0].value.as< rational_t > ());
        }
#line 1730 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 529 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AtomNode* > () = new RationalAtom(yylhs.location, yystack_[0].value.as< rational_t > ()); }
#line 1736 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 532 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1742 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 535 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              if (yystack_[3].value.as< AtomNode* > ()->node_type_ == NodeType::INTEGER_ATOM && yystack_[1].value.as< AtomNode* > ()->node_type_ == NodeType::INTEGER_ATOM) {
                yylhs.value.as< AtomNode* > () = new NumberRangeAtom(yylhs.location, reinterpret_cast<IntegerAtom*>(yystack_[3].value.as< AtomNode* > ()), reinterpret_cast<IntegerAtom*>(yystack_[1].value.as< AtomNode* > ()));
              } else {
                driver.error(yylhs.location, "numbers in range expression must be Integer");
                yylhs.value.as< AtomNode* > () = nullptr;
              }
            }
#line 1755 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 546 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > (); }
#line 1761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 547 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector<ExpressionBase*>(); }
#line 1767 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 551 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > (); }
#line 1773 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 552 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > (); }
#line 1779 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 554 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
                          yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back(yystack_[0].value.as< ExpressionBase* > ());
                        }
#line 1788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 558 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                          yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector<ExpressionBase*>;
                          yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back(yystack_[0].value.as< ExpressionBase* > ());
                        }
#line 1797 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 566 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::ADD); }
#line 1803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 568 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::SUB); }
#line 1809 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 570 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MUL); }
#line 1815 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 572 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::DIV); }
#line 1821 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 574 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MOD); }
#line 1827 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 576 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::RAT_DIV); }
#line 1833 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 578 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::NEQ); }
#line 1839 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 580 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::EQ); }
#line 1845 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 582 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSER); }
#line 1851 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 584 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATER); }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 586 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSEREQ); }
#line 1863 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 588 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATEREQ); }
#line 1869 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 590 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::OR); }
#line 1875 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 592 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::XOR); }
#line 1881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 594 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::AND); }
#line 1887 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 596 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = new Expression(yylhs.location, yystack_[0].value.as< ExpressionBase* > (), nullptr, ExpressionOperation::NOT);}
#line 1893 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 597 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > (); }
#line 1899 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 600 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > (); }
#line 1905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 603 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom(yylhs.location, yystack_[0].value.as< std::string > ()); }
#line 1911 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 604 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom(yylhs.location, yystack_[2].value.as< std::string > ()); }
#line 1917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 606 "../../src/GrammarParser.yy" // lalr1.cc:859
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
#line 1932 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 618 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > ()); }
#line 1938 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 619 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > ());
           }
#line 1946 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 622 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > ());
           }
#line 1954 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 626 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                std::vector<Type*> tmp;
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ());
           }
#line 1963 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 630 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                std::vector<Type*> tmp;
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ());
           }
#line 1972 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 634 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                std::vector<Type*> tmp;
                yylhs.value.as< AstNode* > () = new RuleNode(yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ());
           }
#line 1981 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 640 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move(yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ()); yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back(yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > ()); }
#line 1987 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 641 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector<std::pair<std::string,std::vector<std::string>>>();
                yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back(std::move(yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > ()));
             }
#line 1996 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 647 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
            yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair<std::string, std::vector<std::string>>(yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > ());
        }
#line 2004 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 652 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2010 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 653 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2016 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 654 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > (); }
#line 2022 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 655 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > (); }
#line 2028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 656 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > (); }
#line 2034 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 657 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > (); }
#line 2040 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 658 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > (); }
#line 2046 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 659 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > (); }
#line 2052 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 660 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > (); }
#line 2058 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 661 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2064 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 662 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2070 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 663 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > (); }
#line 2076 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 664 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > (); }
#line 2082 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 665 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > (); }
#line 2088 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 666 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > (); }
#line 2094 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 667 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > (); }
#line 2100 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 668 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > (); }
#line 2106 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 669 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::SKIP); }
#line 2112 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 670 "../../src/GrammarParser.yy" // lalr1.cc:859
    { driver.error(yylhs.location, "this call syntax is obsolete, use `call "+yystack_[0].value.as< std::string > ()+"`"); }
#line 2118 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 671 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::STATEMENT); }
#line 2124 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 672 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(NodeType::STATEMENT);}
#line 2130 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 675 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > ()); }
#line 2136 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 677 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > ()); }
#line 2142 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 680 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< DiedieNode* > () = new DiedieNode(yylhs.location, yystack_[0].value.as< ExpressionBase* > ()); }
#line 2148 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 681 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< DiedieNode* > () = new DiedieNode(yylhs.location, nullptr); }
#line 2154 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 691 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstNode* > () = new AstNode(yylhs.location, NodeType::IMPOSSIBLE); }
#line 2160 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 694 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< PrintNode* > () = new PrintNode(yylhs.location, yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::vector<ExpressionBase*> > ()); }
#line 2166 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 697 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*> > () = std::move(yystack_[2].value.as< std::vector<ExpressionBase*> > ()); yylhs.value.as< std::vector<ExpressionBase*> > ().push_back(yystack_[0].value.as< ExpressionBase* > ()); }
#line 2172 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 698 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::vector<ExpressionBase*> > ().push_back(yystack_[0].value.as< ExpressionBase* > ()); }
#line 2178 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 700 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< PrintNode* > () = new PrintNode(yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*> > ()); }
#line 2184 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 703 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                  if (yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::FUNCTION_ATOM) {
                    yylhs.value.as< UpdateNode* > () = new UpdateNode(yylhs.location, reinterpret_cast<FunctionAtom*>(yystack_[2].value.as< BaseFunctionAtom* > ()), yystack_[0].value.as< ExpressionBase* > ());
                  } else {
                    driver.error(yylhs.location, "can only use functions for updates but `"+
                                     yystack_[2].value.as< BaseFunctionAtom* > ()->to_str()+"` is a `"+type_to_str(yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_));
                  }
                }
#line 2197 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 713 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< CaseNode* > () = new CaseNode(yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ());
           }
#line 2205 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 718 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move(yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ());
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back(yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ());
               }
#line 2214 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 722 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move(std::vector<std::pair<AtomNode*, AstNode*>>());
                    yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back(yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ());
               }
#line 2223 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 728 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () =yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2229 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 729 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2235 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 730 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2241 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 731 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > (); }
#line 2247 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 734 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(nullptr, yystack_[0].value.as< AstNode* > ());
                  }
#line 2255 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 739 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > ());
                 }
#line 2263 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 744 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(yystack_[2].value.as< BaseFunctionAtom* > (), yystack_[0].value.as< AstNode* > ());
                }
#line 2271 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 749 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                    yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair<AtomNode*, AstNode*>(new StringAtom(yylhs.location, std::move(yystack_[2].value.as< std::string > ())), yystack_[0].value.as< AstNode* > ());
                 }
#line 2279 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 754 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > ()); }
#line 2285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 755 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, "", yystack_[1].value.as< ExpressionBase* > ()); }
#line 2291 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 756 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > ()); }
#line 2297 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 757 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< CallNode* > () = new CallNode(yylhs.location, yystack_[0].value.as< std::string > (), nullptr); }
#line 2303 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 760 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > ());
          }
#line 2311 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 763 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > ());
          }
#line 2319 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 768 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > ());
          }
#line 2327 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 771 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > ());
          }
#line 2335 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 776 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ()); yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > (); }
#line 2341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 777 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::STATEMENTS); yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ()); }
#line 2347 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 780 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr);
          }
#line 2355 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 783 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode(yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > ());
          }
#line 2363 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 789 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                auto var = Symbol(yystack_[1].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET);
                try {
                    driver.function_table.add(&var);
                } catch (const SymbolAlreadyExists& e) {
                    driver.error(yylhs.location, e.what());
                }
            }
#line 2376 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 797 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              driver.function_table.remove(yystack_[5].value.as< std::string > ());
              yylhs.value.as< LetNode* > () = new LetNode(yylhs.location, Type(TypeType::UNKNOWN), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > ());
          }
#line 2385 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 802 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                auto var = Symbol(yystack_[3].value.as< std::string > (), yylhs.location, Symbol::SymbolType::LET);
                try {
                    driver.function_table.add(&var);
                } catch (const SymbolAlreadyExists& e) {
                    driver.error(yylhs.location, e.what());
                }
            }
#line 2398 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 810 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
              driver.function_table.remove(yystack_[7].value.as< std::string > ());
              yylhs.value.as< LetNode* > () = new LetNode(yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > ());
          }
#line 2407 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 816 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                if (yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(yylhs.location, "cannot push to builtin `"+yystack_[0].value.as< BaseFunctionAtom* > ()->to_str()+"`");
                } else {
                    yylhs.value.as< PushNode* > () = new PushNode(yylhs.location, yystack_[2].value.as< ExpressionBase* > (), reinterpret_cast<FunctionAtom*>(yystack_[0].value.as< BaseFunctionAtom* > ()));
                }
          }
#line 2419 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 826 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                if (yystack_[2].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(yylhs.location, "cannot pop to builtin `"+yystack_[2].value.as< BaseFunctionAtom* > ()->to_str()+"`");
                } else if (yystack_[0].value.as< BaseFunctionAtom* > ()->node_type_ == NodeType::BUILTIN_ATOM) {
                  driver.error(yylhs.location, "cannot pop from builtin `"+yystack_[0].value.as< BaseFunctionAtom* > ()->to_str()+"`");
                } else {
                    yylhs.value.as< PopNode* > () = new PopNode(yylhs.location, reinterpret_cast<FunctionAtom*>(yystack_[2].value.as< BaseFunctionAtom* > ()), reinterpret_cast<FunctionAtom*>(yystack_[0].value.as< BaseFunctionAtom* > ()));
                }
          }
#line 2433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 837 "../../src/GrammarParser.yy" // lalr1.cc:859
    {
                yylhs.value.as< ForallNode* > () = new ForallNode(yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > ());
             }
#line 2441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 842 "../../src/GrammarParser.yy" // lalr1.cc:859
    { yylhs.value.as< UnaryNode* > () = new UnaryNode(yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > ()); }
#line 2447 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2451 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int casmi_parser::yypact_ninf_ = -202;

  const signed char casmi_parser::yytable_ninf_ = -106;

  const short int
  casmi_parser::yypact_[] =
  {
     -23,   -63,    94,   168,  -202,  -202,   -13,   -21,    19,    21,
      24,    44,    46,   168,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,    47,    37,   -45,    72,   -20,  -202,  -202,    79,
    -202,  -202,    85,    78,   -44,   116,   275,   -54,    70,    88,
      93,   598,     6,    81,    82,    83,    70,    97,   113,    92,
     101,  -202,   275,  -202,  -202,  -202,  -202,  -202,    58,    66,
     275,    31,    89,  -202,  -202,  -202,  -202,   109,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,   790,  -202,  -202,    -3,   104,
    -202,   112,   105,   117,    47,    47,   -39,  -202,   275,   275,
     275,  -202,  -202,   598,   598,    96,   275,   872,   119,   275,
     120,   129,   598,    -9,   275,   275,   136,   598,   598,    35,
     160,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,  -202,   -18,
     151,   137,    37,  -202,  -202,   -48,    70,    70,   843,   790,
    -202,  -202,  -202,  -202,  -202,  -202,   398,  -202,   166,   158,
     154,   790,  -202,   191,   275,   275,   275,   275,   275,   275,
     275,   275,   275,   275,   275,   275,   275,   275,   275,   275,
      70,    70,    25,   146,   275,   162,   167,   598,    93,   790,
     790,   790,  -202,   356,   419,    62,   514,  -202,   172,   872,
     577,   207,   222,  -202,   275,   180,   638,  -202,   163,   472,
     535,   275,    93,   598,   -16,  -202,   116,   165,   169,   174,
     185,   -32,  -202,  -202,  -202,    59,  -202,   197,  -202,   -31,
    -202,   275,  -202,   189,   823,   823,   -36,  -202,   335,   335,
     335,   -36,   -36,   335,   335,   335,  -202,  -202,  -202,   790,
     195,  -202,   275,    70,  -202,   790,  -202,   206,  -202,  -202,
    -202,  -202,  -202,  -202,    70,   598,   872,   172,   120,   120,
     275,   666,   275,    39,   196,  -202,  -202,   790,    18,  -202,
      93,   598,  -202,    70,  -202,   -34,  -202,  -202,   872,   872,
     198,   790,  -202,   275,   790,   199,   181,   275,   204,   248,
    -202,  -202,  -202,   700,   211,   212,   205,   217,   218,   223,
       3,  -202,  -202,  -202,  -202,  -202,  -202,   598,    61,  -202,
    -202,   234,  -202,  -202,  -202,   790,   275,  -202,   729,  -202,
     598,   598,   275,  -202,   598,   598,   598,   598,  -202,  -202,
    -202,   598,  -202,   790,   598,   275,  -202,  -202,   235,  -202,
    -202,  -202,  -202,  -202,  -202,   762,  -202,   598,  -202
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
      38,     0,    35,     0,     0,     0,     0,   115,     0,     0,
     141,   142,   134,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
       0,   108,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,     0,
       0,     0,     0,    29,    31,     0,     0,    40,     0,   102,
      73,    69,    76,    74,    70,    77,     0,    82,    60,     0,
      83,    86,    79,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    36,     0,     0,     0,     0,     0,   138,
     139,   140,   168,     0,     0,     0,     0,   145,   146,     0,
       0,     0,     0,   178,     0,   162,     0,   136,     0,     0,
       0,     0,     0,     0,     0,    15,    24,     0,     0,    48,
       0,     0,    32,    39,    50,     0,    53,    54,   104,     0,
      81,    84,   106,     0,   101,    99,   100,    92,    93,    97,
      98,    87,    88,    94,    95,    96,    89,    90,    91,    19,
       0,    33,     0,     0,    37,    21,    16,     0,   111,   114,
     164,   167,   166,   171,     0,     0,     0,   143,     0,     0,
       0,     0,     0,     0,     0,   163,   165,   147,     0,   109,
       0,     0,    23,    47,    43,     0,    45,    49,    52,     0,
       0,    85,   107,     0,    17,     0,     0,     0,     0,   169,
     144,   175,   176,     0,   160,     0,     0,     0,     0,     0,
       0,   150,   151,   152,   153,   154,   137,     0,     0,   110,
      46,     0,    51,    55,    80,    22,     0,   116,     0,   173,
       0,     0,     0,   161,     0,     0,     0,     0,   148,   149,
     112,     0,    44,    20,     0,     0,   170,   177,     0,   155,
     158,   156,   157,   113,   172,     0,   159,     0,   174
  };

  const short int
  casmi_parser::yypgoto_[] =
  {
    -202,  -202,  -202,  -202,   269,  -202,  -202,  -202,  -202,  -202,
    -202,   -28,  -202,   171,   128,   262,  -202,   170,   -30,    36,
     102,  -202,    33,   -80,  -202,  -131,   -59,  -202,  -202,  -202,
     -99,  -202,    27,  -202,   -41,  -202,  -201,   134,   -29,  -202,
    -202,  -202,  -202,  -202,   124,  -202,  -202,  -202,  -202,    15,
    -202,  -202,  -202,  -202,  -202,  -202,  -202,   -85,  -202,  -202,
    -202,  -202,  -202,  -202,  -202,  -202
  };

  const short int
  casmi_parser::yydefgoto_[] =
  {
      -1,     2,     3,    13,    14,    15,    16,    17,    18,    19,
      20,    32,    33,    35,    80,    81,    82,    48,    49,   210,
      51,   215,   216,    68,    69,    70,    71,    72,    73,    74,
     149,   150,   151,    76,    77,    21,    86,    87,   182,   112,
     113,   114,   115,   116,   188,   117,   118,   119,   300,   301,
     302,   303,   304,   305,   120,   121,   122,   183,   123,   124,
     287,   335,   125,   126,   127,   128
  };

  const short int
  casmi_parser::yytable_[] =
  {
     110,   268,   148,    40,   211,   202,   197,   270,    83,   184,
      46,    78,   111,   207,   208,   157,   134,   187,    36,    37,
       4,   275,   199,   200,   177,     1,    38,   207,   208,    79,
      58,    59,    64,   276,   178,    47,   296,    52,   328,    47,
     166,   167,   168,    41,    42,   203,    64,   271,    63,    64,
      65,    22,   110,   110,   223,   194,   175,   176,   217,   191,
     169,   110,    24,    75,    58,    59,   110,   110,   170,   308,
      23,   129,   296,   193,   195,    53,    54,    55,    56,   139,
      57,   307,    63,    64,    65,   297,    67,   146,   242,    79,
    -105,   178,    58,    59,     5,    60,   243,    61,   147,   153,
      58,    59,    25,    62,    26,   209,   212,    27,    34,   187,
      63,    64,    65,    66,    67,   179,   180,   181,    63,    64,
      65,   297,    67,   186,   331,   253,   190,    28,   277,    29,
      31,   196,   278,   254,   178,    39,   110,   140,   141,   142,
     240,   241,   110,   110,   311,   143,   144,   145,   248,    43,
      44,    45,    50,    47,   251,   251,    84,    85,   110,   110,
     280,   135,   110,   295,   131,   132,   133,   136,   137,   138,
     251,   251,   152,   153,   269,   171,   290,   172,   173,   185,
     174,   224,   225,   226,   227,   228,   229,   230,   231,   232,
     233,   234,   235,   236,   237,   238,   239,    52,   217,   313,
     198,   245,   189,    67,   298,     6,     7,     8,     9,    10,
      11,    12,   192,   285,   110,   201,   204,   291,   292,   219,
     205,   261,   299,   338,   288,   220,   289,   221,   267,    79,
     110,   246,   247,   256,   259,    53,    54,    55,    56,   260,
      57,   298,   309,   209,   262,   141,   264,   273,   281,   144,
     274,   279,    58,    59,   282,    60,   222,    61,   283,   299,
     286,   306,   316,    62,   317,   314,   110,   319,   320,   284,
      63,    64,    65,    66,    67,   322,   324,   323,   330,   110,
     110,    52,    30,   110,   110,   110,   110,   293,   325,   326,
     110,   336,   337,   110,   327,   339,   340,   341,   342,   332,
     346,   244,   343,   206,   130,   344,   110,   213,   272,   310,
     315,   312,   249,   257,   318,   329,     0,     0,   348,    53,
      54,    55,    56,     0,    57,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    58,    59,     0,    60,
     156,    61,     0,   333,     0,     0,     0,    62,     0,     0,
       0,     0,     0,     0,    63,    64,    65,    66,    67,     0,
       0,     0,   345,    88,    89,    90,    91,    92,    93,   250,
      94,     0,    95,     0,    96,     0,     0,    97,    98,     0,
      99,     0,   100,     0,   101,   102,   157,   103,   104,     0,
       0,  -106,  -106,  -106,     0,     0,   161,   162,  -106,     0,
       0,   154,   155,   156,     0,     0,   105,     0,   106,  -106,
    -106,   166,   167,   168,     0,   107,     0,     0,     0,     0,
       0,     0,     0,     0,   108,     0,    88,    89,    90,    91,
      92,    93,     0,    94,   252,    95,     0,    96,     0,   109,
      97,    98,     0,    99,     0,   100,     0,   101,   102,   157,
     103,   104,     0,     0,   158,   159,   160,     0,     0,   161,
     162,   163,     0,   218,     0,     0,     0,     0,     0,   105,
       0,   106,   164,   165,   166,   167,   168,     0,   107,    88,
      89,    90,    91,    92,    93,     0,    94,   108,    95,     0,
      96,     0,     0,    97,    98,     0,    99,     0,   100,     0,
     101,   102,   109,   103,   104,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   154,   155,   156,
       0,     0,   105,     0,   106,     0,     0,     0,     0,     0,
       0,   107,   265,   255,     0,     0,     0,     0,     0,     0,
     108,     0,    88,    89,    90,    91,    92,    93,     0,    94,
       0,    95,     0,    96,     0,   109,    97,    98,     0,    99,
       0,   100,     0,   101,   102,   157,   103,   104,     0,     0,
     158,   159,   160,     0,     0,   161,   162,   163,     0,     0,
     154,   155,   156,     0,     0,   105,     0,   106,   164,   165,
     166,   167,   168,     0,   107,     0,     0,     0,     0,     0,
       0,     0,   258,   108,   266,    88,    89,    90,    91,    92,
      93,     0,    94,     0,    95,     0,    96,     0,   109,    97,
      98,     0,    99,     0,   100,     0,   101,   102,   157,   103,
     104,     0,     0,   158,   159,   160,     0,     0,   161,   162,
     163,   154,   155,   156,     0,     0,     0,     0,   105,     0,
     106,   164,   165,   166,   167,   168,     0,   107,     0,     0,
       0,     0,     0,     0,     0,     0,   108,     0,     0,   154,
     155,   156,   263,     0,     0,     0,     0,     0,     0,     0,
       0,   109,     0,     0,     0,     0,     0,     0,     0,   157,
       0,     0,     0,     0,   158,   159,   160,     0,     0,   161,
     162,   163,     0,   154,   155,   156,     0,     0,     0,     0,
       0,     0,   164,   165,   166,   167,   168,   157,     0,     0,
       0,     0,   158,   159,   160,     0,     0,   161,   162,   163,
     321,   294,   154,   155,   156,     0,     0,     0,     0,     0,
     164,   165,   166,   167,   168,     0,   334,     0,     0,     0,
       0,   157,     0,     0,     0,     0,   158,   159,   160,     0,
       0,   161,   162,   163,     0,   154,   155,   156,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,   347,
     157,     0,     0,     0,     0,   158,   159,   160,     0,     0,
     161,   162,   163,   154,   155,   156,     0,     0,     0,     0,
       0,     0,     0,   164,   165,   166,   167,   168,     0,     0,
       0,     0,     0,   157,     0,     0,     0,     0,   158,   159,
     160,     0,     0,   161,   162,   163,  -106,  -106,   156,     0,
       0,     0,     0,     0,     0,     0,   164,   165,   166,   167,
     168,   157,     0,     0,     0,     0,   158,   159,   160,     0,
       0,   161,   162,   163,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   164,   165,   166,   167,   168,     0,
       0,     0,     0,     0,   157,     0,     0,     0,     0,   158,
     159,   160,     0,     0,   161,   162,   163,    53,    54,    55,
      56,     0,    57,     0,     0,     0,     0,   164,   165,   166,
     167,   168,     0,     0,    58,    59,     0,    60,     0,    61,
       0,     0,   214,     0,     0,    62,    53,    54,    55,    56,
       0,    57,    63,    64,    65,    66,    67,     0,     0,     0,
       0,     0,     0,    58,    59,     0,    60,     0,    61,     0,
       0,     0,     0,     0,    62,     0,     0,     0,     0,     0,
       0,    63,    64,    65,    66,    67
  };

  const short int
  casmi_parser::yycheck_[] =
  {
      41,   202,    61,    23,   135,    23,   105,    23,    38,    94,
      54,    65,    41,    61,    62,    51,    46,    97,    63,    64,
      83,    53,   107,   108,    63,    48,    71,    61,    62,    83,
      61,    62,    80,    65,    73,    83,    33,     6,    35,    83,
      76,    77,    78,    63,    64,    63,    80,    63,    79,    80,
      81,    64,    93,    94,   153,    64,    84,    85,   138,   100,
      63,   102,    83,    36,    61,    62,   107,   108,    71,   270,
      83,    65,    33,   102,    83,    44,    45,    46,    47,    52,
      49,    63,    79,    80,    81,    82,    83,    60,    63,    83,
      55,    73,    61,    62,     0,    64,    71,    66,    67,    64,
      61,    62,    83,    72,    83,   135,   136,    83,    71,   189,
      79,    80,    81,    82,    83,    88,    89,    90,    79,    80,
      81,    82,    83,    96,    63,    63,    99,    83,    69,    83,
      83,   104,    73,    71,    73,    63,   177,    79,    80,    81,
     170,   171,   183,   184,   275,    79,    80,    81,   177,    70,
      65,    73,    36,    83,   183,   184,    68,    64,   199,   200,
     219,    64,   203,   262,    83,    83,    83,    54,    76,    68,
     199,   200,    83,    64,   203,    71,   256,    65,    73,    83,
      63,   154,   155,   156,   157,   158,   159,   160,   161,   162,
     163,   164,   165,   166,   167,   168,   169,     6,   278,   279,
      64,   174,    83,    83,   263,    37,    38,    39,    40,    41,
      42,    43,    83,   243,   255,    55,    65,   258,   259,    53,
      83,   194,   263,   322,   254,    67,   255,    73,   201,    83,
     271,    69,    65,    61,    27,    44,    45,    46,    47,    17,
      49,   300,   271,   273,    64,    80,    83,    73,   221,    80,
      65,    54,    61,    62,    65,    64,    65,    66,    63,   300,
      54,    65,    63,    72,    83,    67,   307,    63,    20,   242,
      79,    80,    81,    82,    83,    64,    71,    65,   307,   320,
     321,     6,    13,   324,   325,   326,   327,   260,    71,    71,
     331,   320,   321,   334,    71,   324,   325,   326,   327,    65,
      65,   173,   331,   132,    42,   334,   347,   137,   206,   273,
     283,   278,   178,   189,   287,   300,    -1,    -1,   347,    44,
      45,    46,    47,    -1,    49,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    61,    62,    -1,    64,
       5,    66,    -1,   316,    -1,    -1,    -1,    72,    -1,    -1,
      -1,    -1,    -1,    -1,    79,    80,    81,    82,    83,    -1,
      -1,    -1,   335,     7,     8,     9,    10,    11,    12,    13,
      14,    -1,    16,    -1,    18,    -1,    -1,    21,    22,    -1,
      24,    -1,    26,    -1,    28,    29,    51,    31,    32,    -1,
      -1,    56,    57,    58,    -1,    -1,    61,    62,    63,    -1,
      -1,     3,     4,     5,    -1,    -1,    50,    -1,    52,    74,
      75,    76,    77,    78,    -1,    59,    -1,    -1,    -1,    -1,
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
      -1,    61,    62,    63,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    74,    75,    76,    77,    78,    -1,
      -1,    -1,    -1,    -1,    51,    -1,    -1,    -1,    -1,    56,
      57,    58,    -1,    -1,    61,    62,    63,    44,    45,    46,
      47,    -1,    49,    -1,    -1,    -1,    -1,    74,    75,    76,
      77,    78,    -1,    -1,    61,    62,    -1,    64,    -1,    66,
      -1,    -1,    69,    -1,    -1,    72,    44,    45,    46,    47,
      -1,    49,    79,    80,    81,    82,    83,    -1,    -1,    -1,
      -1,    -1,    -1,    61,    62,    -1,    64,    -1,    66,    -1,
      -1,    -1,    -1,    -1,    72,    -1,    -1,    -1,    -1,    -1,
      -1,    79,    80,    81,    82,    83
  };

  const unsigned char
  casmi_parser::yystos_[] =
  {
       0,    48,    88,    89,    83,     0,    37,    38,    39,    40,
      41,    42,    43,    90,    91,    92,    93,    94,    95,    96,
      97,   122,    64,    83,    83,    83,    83,    83,    83,    83,
      91,    83,    98,    99,    71,   100,    63,    64,    71,    63,
      23,    63,    64,    70,    65,    73,    54,    83,   104,   105,
      36,   107,     6,    44,    45,    46,    47,    49,    61,    62,
      64,    66,    72,    79,    80,    81,    82,    83,   110,   111,
     112,   113,   114,   115,   116,   119,   120,   121,    65,    83,
     101,   102,   103,   105,    68,    64,   123,   124,     7,     8,
       9,    10,    11,    12,    14,    16,    18,    21,    22,    24,
      26,    28,    29,    31,    32,    50,    52,    59,    68,    83,
     121,   125,   126,   127,   128,   129,   130,   132,   133,   134,
     141,   142,   143,   145,   146,   149,   150,   151,   152,    65,
     102,    83,    83,    83,   105,    64,    54,    76,    68,   119,
      79,    80,    81,    79,    80,    81,   119,    67,   113,   117,
     118,   119,    83,    64,     3,     4,     5,    51,    56,    57,
      58,    61,    62,    63,    74,    75,    76,    77,    78,    63,
      71,    71,    65,    73,    63,    98,    98,    63,    73,   119,
     119,   119,   125,   144,   144,    83,   119,   110,   131,    83,
     119,   121,    83,   125,    64,    83,   119,   117,    64,   144,
     144,    55,    23,    63,    65,    83,   100,    61,    62,   105,
     106,   112,   105,   104,    69,   108,   109,   110,    65,    53,
      67,    73,    65,   117,   119,   119,   119,   119,   119,   119,
     119,   119,   119,   119,   119,   119,   119,   119,   119,   119,
     105,   105,    63,    71,   101,   119,    69,    65,   125,   124,
      13,   125,    15,    63,    71,    19,    61,   131,    25,    27,
      17,   119,    64,    34,    83,    60,    69,   119,   123,   125,
      23,    63,   107,    73,    65,    53,    65,    69,    73,    54,
     113,   119,    65,    63,   119,   105,    54,   147,   105,   125,
     110,   121,   121,   119,    65,   117,    33,    82,   113,   121,
     135,   136,   137,   138,   139,   140,    65,    63,   123,   125,
     106,   112,   109,   110,    67,   119,    63,    83,   119,    63,
      20,    30,    64,    65,    71,    71,    71,    71,    35,   136,
     125,    63,    65,   119,    17,   148,   125,   125,   117,   125,
     125,   125,   125,   125,   125,   119,    65,    17,   125
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
     122,   122,   122,   122,   123,   123,   124,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   125,   125,
     125,   125,   125,   125,   125,   125,   125,   125,   126,   127,
     128,   128,   129,   130,   131,   131,   132,   133,   134,   135,
     135,   136,   136,   136,   136,   137,   138,   139,   140,   141,
     141,   141,   141,   142,   142,   143,   143,   144,   144,   145,
     145,   147,   146,   148,   146,   149,   150,   151,   152
  };

  const unsigned char
  casmi_parser::yyr2_[] =
  {
       0,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     2,     2,     5,     6,     7,     4,     6,
       9,     6,     8,     7,     6,     4,     3,     2,     1,     3,
       1,     3,     4,     3,     1,     1,     2,     3,     1,     3,
       2,     1,     1,     4,     6,     4,     3,     2,     1,     4,
       3,     3,     2,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     1,     2,     2,     1,     2,     2,     1,     2,
       5,     3,     2,     1,     2,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     1,     3,     1,     3,     4,     4,     6,
       7,     6,     8,     9,     3,     1,     5,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     2,     4,     2,     2,
       2,     1,     1,     3,     3,     1,     2,     3,     5,     2,
       1,     1,     1,     1,     1,     3,     3,     3,     3,     7,
       4,     5,     2,     3,     3,     3,     3,     2,     1,     4,
       6,     0,     7,     0,     9,     4,     4,     6,     2
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
  "FUNCTION_SYNTAX", "RULE_SYNTAX", "DUMPSPEC_LIST", "DUMPSPEC",
  "STATEMENT", "ASSERT_SYNTAX", "ASSURE_SYNTAX", "DIEDIE_SYNTAX",
  "IMPOSSIBLE_SYNTAX", "DEBUG_SYNTAX", "DEBUG_ATOM_LIST", "PRINT_SYNTAX",
  "UPDATE_SYNTAX", "CASE_SYNTAX", "CASE_LABEL_LIST", "CASE_LABEL",
  "CASE_LABEL_DEFAULT", "CASE_LABEL_NUMBER", "CASE_LABEL_IDENT",
  "CASE_LABEL_STRING", "CALL_SYNTAX", "SEQ_SYNTAX", "PAR_SYNTAX",
  "STATEMENTS", "IFTHENELSE", "LET_SYNTAX", "$@1", "$@2", "PUSH_SYNTAX",
  "POP_SYNTAX", "FORALL_SYNTAX", "ITERATE_SYNTAX", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  casmi_parser::yyrline_[] =
  {
       0,   245,   245,   253,   260,   265,   273,   274,   275,   276,
     290,   303,   304,   318,   325,   329,   332,   353,   357,   360,
     364,   367,   370,   375,   379,   383,   386,   390,   391,   394,
     398,   404,   409,   413,   418,   427,   428,   430,   434,   438,
     442,   446,   451,   452,   455,   464,   475,   479,   480,   483,
     484,   487,   488,   489,   496,   497,   500,   501,   502,   505,
     506,   507,   508,   509,   510,   511,   512,   513,   514,   517,
     518,   519,   520,   521,   522,   523,   524,   525,   529,   532,
     535,   546,   547,   551,   552,   554,   558,   565,   567,   569,
     571,   573,   575,   577,   579,   581,   583,   585,   587,   589,
     591,   593,   595,   597,   600,   603,   604,   605,   618,   619,
     622,   626,   630,   634,   640,   641,   647,   652,   653,   654,
     655,   656,   657,   658,   659,   660,   661,   662,   663,   664,
     665,   666,   667,   668,   669,   670,   671,   672,   675,   677,
     680,   681,   691,   694,   697,   698,   700,   703,   713,   718,
     722,   728,   729,   730,   731,   734,   739,   744,   749,   754,
     755,   756,   757,   760,   763,   768,   771,   776,   777,   780,
     783,   789,   788,   802,   801,   816,   826,   837,   842
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
#line 3196 "GrammarParser.cpp" // lalr1.cc:1167
#line 846 "../../src/GrammarParser.yy" // lalr1.cc:1168


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
