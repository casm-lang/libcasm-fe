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
      case 139: // STATEMENTS
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

      case 136: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 129: // CASE_SYNTAX
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

      case 146: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 76: // "integer"
        value.move< INTEGER_T > (that.value);
        break;

      case 140: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 85: // INIT_SYNTAX
        value.move< InitNode* > (that.value);
        break;

      case 105: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 141: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 145: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 125: // DEBUG_SYNTAX
      case 127: // PRINT_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 144: // PUSH_SYNTAX
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
      case 137: // SEQ_SYNTAX
      case 138: // PAR_SYNTAX
      case 147: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 128: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.move< rational_t > (that.value);
        break;

      case 131: // CASE_LABEL
      case 132: // CASE_LABEL_DEFAULT
      case 133: // CASE_LABEL_NUMBER
      case 134: // CASE_LABEL_IDENT
      case 135: // CASE_LABEL_STRING
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

      case 126: // DEBUG_ATOM_LIST
        value.move< std::vector<ExpressionBase*> > (that.value);
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

      case 130: // CASE_LABEL_LIST
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
      case 139: // STATEMENTS
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

      case 136: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 129: // CASE_SYNTAX
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

      case 146: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 76: // "integer"
        value.copy< INTEGER_T > (that.value);
        break;

      case 140: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 85: // INIT_SYNTAX
        value.copy< InitNode* > (that.value);
        break;

      case 105: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 141: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 145: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 125: // DEBUG_SYNTAX
      case 127: // PRINT_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 144: // PUSH_SYNTAX
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
      case 137: // SEQ_SYNTAX
      case 138: // PAR_SYNTAX
      case 147: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 128: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.copy< rational_t > (that.value);
        break;

      case 131: // CASE_LABEL
      case 132: // CASE_LABEL_DEFAULT
      case 133: // CASE_LABEL_NUMBER
      case 134: // CASE_LABEL_IDENT
      case 135: // CASE_LABEL_STRING
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

      case 126: // DEBUG_ATOM_LIST
        value.copy< std::vector<ExpressionBase*> > (that.value);
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

      case 130: // CASE_LABEL_LIST
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

#line 879 "GrammarParser.cpp" // lalr1.cc:741

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
      case 139: // STATEMENTS
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

      case 136: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 129: // CASE_SYNTAX
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

      case 146: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 76: // "integer"
        yylhs.value.build< INTEGER_T > ();
        break;

      case 140: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 85: // INIT_SYNTAX
        yylhs.value.build< InitNode* > ();
        break;

      case 105: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 141: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 145: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 125: // DEBUG_SYNTAX
      case 127: // PRINT_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 144: // PUSH_SYNTAX
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
      case 137: // SEQ_SYNTAX
      case 138: // PAR_SYNTAX
      case 147: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 128: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 77: // "rational"
        yylhs.value.build< rational_t > ();
        break;

      case 131: // CASE_LABEL
      case 132: // CASE_LABEL_DEFAULT
      case 133: // CASE_LABEL_NUMBER
      case 134: // CASE_LABEL_IDENT
      case 135: // CASE_LABEL_STRING
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

      case 126: // DEBUG_ATOM_LIST
        yylhs.value.build< std::vector<ExpressionBase*> > ();
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

      case 130: // CASE_LABEL_LIST
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
#line 334 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
  }
#line 1180 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 342 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1188 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
	  yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 1197 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 354 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
	  yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
  }
#line 1206 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 363 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode(NodeType::OPTION);
  }
#line 1214 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 367 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new EnumDefNode(yylhs.location, yystack_[0].value.as< Enum* > ());
  }
#line 1222 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1246 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1267 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > ();
  }
#line 1275 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 412 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1294 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1302 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1336 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  // TODO: 2nd argument should be a reference
	  yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1345 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 483 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1353 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 487 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1361 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 491 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1369 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 495 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1377 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1385 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 507 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[4].value.as< std::vector<std::string> > ());
	  yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1394 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 512 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > ());
	  yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1403 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 517 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1411 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 521 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1419 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 528 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
  }
#line 1427 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ());
  }
#line 1435 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 540 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move( yystack_[2].value.as< std::vector<std::string> > () );
      yylhs.value.as< std::vector<std::string> > ().push_back( yystack_[0].value.as< std::string > () );
  }
#line 1444 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 545 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
	  yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
  }
#line 1453 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 554 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  /* this constructor is implementation dependant! */
	  std::vector<Type*> foo;
	  yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
  }
#line 1463 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 560 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ());
  }
#line 1471 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 568 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  size_t size = driver.binding_offsets.size();
	  driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
	  yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
  }
#line 1481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  size_t size = driver.binding_offsets.size();
	  driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
	  // TODO: fail for rules without types and print warnings
	  yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
  }
#line 1492 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 585 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1500 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ());
  }
#line 1508 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 597 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1517 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1525 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 610 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1534 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  // TODO: limit memory size
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
  }
#line 1543 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1551 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 628 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1578 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 651 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1595 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 664 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1621 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 686 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1639 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< std::vector<Type*> > ().push_back( yystack_[2].value.as< Type* > () );
	  yylhs.value.as< std::vector<Type*> > () = std::move( yystack_[0].value.as< std::vector<Type*> > () );
  }
#line 1648 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 709 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[1].value.as< Type* > () );
  }
#line 1656 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 713 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[0].value.as< Type* > () );
  }
#line 1664 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 721 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1672 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 725 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = nullptr;
  }
#line 1680 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 733 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1688 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 737 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1696 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 741 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = new std::vector< std::pair<ExpressionBase*, ExpressionBase* > >();
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1705 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1713 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 754 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1721 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 762 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1729 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 766 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1737 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1745 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 774 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 1753 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, new ZeroAtom( yylhs.location, yystack_[1].value.as< ExpressionBase* > () ), yystack_[1].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 1761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 823 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1769 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 827 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1777 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 831 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1785 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 835 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1793 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 839 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1801 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 843 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1809 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 847 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1817 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 851 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 1825 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 855 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 1833 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 863 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1841 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 867 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1849 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 871 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1857 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 879 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1865 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 883 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1873 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 887 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, (-1) * yystack_[0].value.as< INTEGER_T > () );
  }
#line 1881 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 895 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1889 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 899 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1897 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 903 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, (-1) * yystack_[0].value.as< FLOATING_T > () );
  }
#line 1905 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 911 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1913 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 915 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1921 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< rational_t > ().numerator *= -1;
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1930 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 80:
#line 928 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 1938 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 1954 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 952 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1962 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 956 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 1970 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 964 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1978 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 968 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1986 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 976 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
	  yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1995 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
	  yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2004 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 990 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::ADD );
  }
#line 2012 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 994 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 2020 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 998 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MUL );
  }
#line 2028 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 1002 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::DIV );
  }
#line 2036 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 1006 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MOD );
  }
#line 2044 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 1010 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::RAT_DIV );
  }
#line 2052 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 1014 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::NEQ );
  }
#line 2060 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 1018 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::EQ );
  }
#line 2068 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 1022 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSER );
  }
#line 2076 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 1026 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATER );
  }
#line 2084 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 1030 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSEREQ );
  }
#line 2092 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 1034 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATEREQ );
  }
#line 2100 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1038 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::OR );
  }
#line 2108 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1042 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::XOR );
  }
#line 2116 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1046 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::AND );
  }
#line 2124 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1050 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), nullptr, ExpressionOperation::NOT );
  }
#line 2132 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1054 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2140 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1062 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2148 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1066 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2156 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1070 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2171 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1084 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2179 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1088 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2187 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1092 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
	  stmts->add( yystack_[0].value.as< AstNode* > () );
	  yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2197 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1102 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2205 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1106 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2213 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1110 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2221 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1114 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2230 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1119 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2239 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1124 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2248 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1133 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2257 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1138 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2266 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1147 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2274 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1155 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2282 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1159 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2290 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1163 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2298 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1167 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2306 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1171 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2314 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1175 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2322 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1179 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2330 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1183 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2338 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1187 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2346 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1191 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2354 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1195 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2362 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1199 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2370 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1203 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2378 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1207 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2386 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1211 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2394 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1215 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2402 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1219 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.error
	  ( yylhs.location
	  , "syntax error: invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
	  , libcasm_fe::Codes::SyntaxErrorInvalidStatement
	  );
  }
#line 2414 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1239 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1243 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2430 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1247 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2438 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1255 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2446 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1263 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2454 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1271 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2462 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1275 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2470 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1291 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2478 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1299 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::vector<ExpressionBase*> > () );
  }
#line 2486 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1307 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*> > () = std::move( yystack_[2].value.as< std::vector<ExpressionBase*> > () );
	  yylhs.value.as< std::vector<ExpressionBase*> > ().push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2495 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1312 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*> > ().push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2503 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1320 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*> > () );
  }
#line 2511 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1328 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2532 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2540 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1357 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2549 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1362 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( std::vector< std::pair< AtomNode*, AstNode* > >() );
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2558 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1371 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () =yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2566 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1375 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2574 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1379 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2582 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1383 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2590 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1391 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( nullptr, yystack_[0].value.as< AstNode* > () );
  }
#line 2598 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1399 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2606 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1407 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< BaseFunctionAtom* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2614 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1415 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( new StringAtom( yylhs.location, std::move( yystack_[2].value.as< std::string > () ) ), yystack_[0].value.as< AstNode* > () );
  }
#line 2622 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1423 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2630 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1427 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2638 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2646 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1435 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2654 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1443 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2662 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1447 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2670 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1455 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2678 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1459 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2686 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1467 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
	  yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2695 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1472 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
	  yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2704 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1481 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2712 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 172:
#line 1485 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2720 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1494 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2736 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 174:
#line 1506 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.function_table.remove( yystack_[5].value.as< std::string > () );
	  yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2745 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1511 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2761 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 176:
#line 1523 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.function_table.remove( yystack_[7].value.as< std::string > () );
	  yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2770 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 177:
#line 1532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2785 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1547 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2808 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1570 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2816 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 180:
#line 1578 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2824 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2828 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int casmi_parser::yypact_ninf_ = -196;

  const signed char casmi_parser::yytable_ninf_ = -106;

  const short int
  casmi_parser::yypact_[] =
  {
      37,   -61,    42,   384,  -196,  -196,   -14,     9,    25,    44,
      47,   -43,   384,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,    80,    98,    90,    -2,    65,    92,  -196,    77,   670,
     -45,   103,   142,   157,   422,   -38,  -196,   159,   149,    51,
     209,   147,  -196,  -196,  -196,  -196,   670,    30,    70,   670,
     590,   150,  -196,  -196,  -196,  -196,   169,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,   895,  -196,    78,   172,
    -196,   179,   183,   193,   195,    65,    65,   -24,  -196,   422,
     422,   670,   670,   670,  -196,  -196,   178,   185,   422,   -41,
     670,   670,   732,   186,   670,   194,   422,   422,   -36,   182,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196,     1,
     203,   196,   197,   103,   180,   213,   223,  -196,  -196,  -196,
     670,  -196,  -196,  -196,   670,  -196,  -196,  -196,   779,  -196,
     215,   225,   222,   895,  -196,   630,   670,   670,   670,   670,
     670,   670,   670,   670,   670,   670,   670,   670,   670,   670,
     670,   670,   103,   103,    81,   206,   -44,   670,   229,   235,
     422,   157,  -196,  -196,  -196,  -196,    60,   324,   895,   895,
     895,   132,   273,  -196,   670,   244,   528,   557,  -196,   250,
     732,   750,   261,   349,   397,   670,   157,   422,    15,    92,
    -196,  -196,   103,   103,   701,   808,   837,  -196,    -6,  -196,
     670,  -196,   248,   923,   976,   951,    38,   177,    27,   987,
     151,   204,  -196,   238,    49,   263,   417,   489,   895,   253,
    -196,   670,   103,  -196,   230,   231,   247,   256,   -28,   895,
    -196,   242,  -196,  -196,  -196,  -196,  -196,  -196,   103,   670,
     866,   670,   422,   158,   732,   250,   194,   194,  -196,  -196,
     895,    73,  -196,   157,   422,   209,  -196,  -196,  -196,    28,
    -196,   246,  -196,  -196,   120,   128,   262,   895,  -196,   670,
     895,   267,   103,  -196,  -196,   -21,   240,   670,   270,   499,
     272,   269,   301,   278,   293,   294,   296,   -19,  -196,  -196,
    -196,  -196,  -196,  -196,  -196,  -196,   422,    74,  -196,  -196,
    -196,   732,   732,  -196,   895,   670,  -196,   279,  -196,   440,
    -196,   422,   670,  -196,   422,   422,   422,   422,   422,  -196,
    -196,  -196,   422,  -196,  -196,   895,  -196,   422,   670,  -196,
     304,  -196,  -196,  -196,  -196,  -196,  -196,  -196,   470,  -196,
     422,  -196
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
     111,   110,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   108,   109,   129,   130,   131,   132,   133,   134,     0,
       0,     0,    25,     0,     0,    39,     0,    23,    13,   103,
       0,    75,    72,    78,     0,    76,    73,    79,     0,    83,
      60,     0,    84,    87,    80,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    34,     0,     0,     0,     0,
       0,     0,   137,   170,   138,   139,     0,     0,   140,   141,
     142,     0,     0,   180,     0,   164,     0,     0,   147,   148,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,    29,     0,    38,     0,     0,     0,    56,     0,    82,
      85,   106,     0,   102,   100,   101,    93,    88,    89,    95,
      96,    97,    90,    91,    92,    94,    98,    99,    17,     0,
      31,     0,     0,    35,     0,     0,    46,     0,     0,    19,
      14,     0,   114,   117,   166,   169,   168,   173,     0,     0,
       0,     0,     0,     0,     0,   145,     0,     0,   167,   165,
     149,     0,   112,     0,     0,    22,    30,    37,    48,     0,
      51,    52,    57,    58,     0,     0,     0,    86,   107,     0,
      15,     0,    45,    42,    41,     0,     0,     0,     0,     0,
     162,     0,   171,     0,     0,     0,     0,     0,   152,   153,
     154,   155,   156,   146,   177,   178,     0,     0,   113,    21,
      47,    50,     0,    81,    20,     0,    44,     0,   119,     0,
     175,     0,     0,   163,     0,     0,     0,     0,     0,   150,
     151,   115,     0,    49,    53,    18,    43,     0,     0,   179,
       0,   172,   157,   160,   158,   159,   116,   174,     0,   161,
       0,   176
  };

  const short int
  casmi_parser::yypgoto_[] =
  {
    -196,  -196,  -196,  -196,   319,  -196,  -196,  -196,  -196,  -196,
     117,  -196,   165,   212,   336,  -196,   171,    -8,    96,   116,
    -196,    71,   -73,  -196,   -47,  -164,  -196,  -196,  -196,  -196,
    -196,  -133,  -196,    18,   -34,  -144,  -196,  -195,   224,   -17,
     -66,  -196,  -196,  -196,  -196,  -196,   208,  -196,  -196,  -196,
    -196,    89,  -196,  -196,  -196,  -196,  -196,    14,    17,   -76,
    -196,  -196,  -196,  -196,  -196,  -196,  -196,  -196
  };

  const short int
  casmi_parser::yydefgoto_[] =
  {
      -1,     2,     3,    12,    13,    14,    15,    16,    17,    18,
      37,    38,    40,    70,    71,    72,   124,   125,   237,   127,
     269,   270,    57,    58,    59,    60,    61,    62,    63,    64,
      65,   141,   142,   143,    67,   100,    19,    77,    78,   172,
     173,   102,   103,   104,   105,   106,   189,   107,   108,   109,
     297,   298,   299,   300,   301,   302,   110,   174,   175,   176,
     113,   114,   287,   338,   115,   116,   117,   118
  };

  const short int
  casmi_parser::yytable_[] =
  {
      99,   261,   238,   140,   177,   234,   235,    33,    68,    25,
     196,   184,   212,   293,   329,   119,   145,   101,     4,   188,
     193,   194,   183,    74,   263,   284,   242,   170,   234,   235,
     274,   275,    53,  -105,    69,    73,    26,   171,   185,   285,
       1,    69,     5,   274,   275,    99,    99,    66,   111,    34,
      35,   112,   197,   262,    99,    53,    52,    53,    54,   294,
      56,   192,    99,    99,   129,    20,   264,   138,   307,    52,
      53,    54,    79,   244,    80,   149,    81,    82,    83,    84,
      85,    86,   130,    87,    88,   310,    89,    90,    21,   311,
      91,   155,   156,   157,    92,    93,    94,   149,    95,   178,
     179,   180,   155,   156,    22,   131,   132,   133,   186,   187,
     245,   245,   191,   155,   156,   201,    96,   188,   291,   123,
     308,   317,   134,    23,   306,   332,    24,   245,   245,   161,
      73,   271,   231,    97,   171,   171,    99,   162,    28,    98,
     232,    32,    99,    99,    36,   135,   136,   137,   205,    29,
      30,    39,   206,   101,   229,   230,    41,    31,   236,    99,
      99,   276,   331,    99,   213,   214,   215,   216,   217,   218,
     219,   220,   221,   222,   223,   224,   225,   226,   227,   228,
     101,   303,    73,   247,   111,   239,   292,   112,   346,   340,
     293,   248,   168,   169,   266,   131,   132,   133,    75,   149,
     150,   151,   250,   135,   136,   137,   295,   274,   275,    76,
     122,   111,   121,   260,   112,   155,   156,   157,    99,   296,
     126,   145,   304,   305,   281,   149,   128,   151,   277,   144,
      99,   163,   164,    52,    53,    54,   294,    56,   271,   334,
     288,   155,   156,   157,   165,   166,   167,   101,   202,   280,
     295,   195,   149,   150,   151,   339,   198,   181,   341,   342,
     343,   344,   345,   296,   182,   190,   153,   289,   155,   156,
     157,   347,    99,    56,   236,   199,   200,   203,   111,   204,
     209,   112,   208,   210,   351,    69,   240,    99,   241,   101,
      99,    99,    99,    99,    99,   249,   251,   314,    99,   254,
     257,   278,   155,    99,   279,   319,   132,   136,   282,   283,
     286,   149,   150,   151,   312,   101,    99,   313,   315,   318,
     111,   320,   323,   112,   322,   153,   154,   155,   156,   157,
     324,    27,   336,   335,   159,   160,    79,   325,    80,   246,
      81,    82,    83,    84,    85,    86,   111,    87,    88,   112,
      89,    90,   326,   327,    91,   328,   348,   349,    92,    93,
      94,    79,    95,    80,   265,    81,    82,    83,    84,    85,
      86,   120,    87,    88,   267,    89,    90,   233,   316,    91,
      96,   309,   333,    92,    93,    94,   330,    95,     6,     7,
       8,     9,    10,     0,    11,   243,     0,    97,   255,     0,
       0,     0,     0,    98,     0,    96,   258,     0,     0,    79,
       0,    80,     0,    81,    82,    83,    84,    85,    86,     0,
      87,    88,    97,    89,    90,     0,     0,    91,    98,     0,
       0,    92,    93,    94,    79,    95,    80,     0,    81,    82,
      83,    84,    85,    86,     0,    87,    88,     0,    89,    90,
       0,     0,    91,    96,     0,     0,    92,    93,    94,     0,
      95,     0,   337,     0,     0,   149,   150,   151,     0,     0,
      97,   259,     0,     0,     0,     0,    98,     0,    96,   153,
     154,   155,   156,   157,   146,   147,   148,     0,   149,   150,
     151,   152,   350,     0,     0,    97,     0,     0,     0,     0,
       0,    98,   153,   154,   155,   156,   157,     0,     0,     0,
     158,   159,   160,     0,   146,   147,   148,     0,   149,   150,
     151,   152,     0,     0,   321,     0,     0,     0,     0,     0,
       0,     0,   153,   154,   155,   156,   157,   149,   150,   151,
     158,   159,   160,   146,   147,   148,     0,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   252,     0,     0,     0,
     159,   153,   154,   155,   156,   157,     0,     0,     0,   158,
     159,   160,   146,   147,   148,     0,   149,   150,   151,   152,
       0,     0,     0,     0,     0,     0,     0,     0,   253,     0,
     153,   154,   155,   156,   157,     0,     0,     0,   158,   159,
     160,   146,   147,   148,     0,   149,   150,   151,   152,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   153,
     154,   155,   156,   157,     0,     0,     0,   158,   159,   160,
      42,    43,    44,    45,     0,     0,     0,    46,     0,    47,
      48,     0,    49,     0,    50,   139,     0,     0,     0,     0,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      42,    43,    44,    45,     0,     0,     0,    46,     0,    47,
      48,     0,    49,   211,    50,     0,     0,     0,     0,     0,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    52,    53,    54,    55,    56,
      42,    43,    44,    45,     0,     0,     0,    46,     0,    47,
      48,     0,    49,     0,    50,     0,     0,     0,     0,     0,
      51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    42,    43,    44,    45,    52,    53,    54,    55,    56,
      47,    48,     0,    49,     0,    50,     0,     0,   268,     0,
       0,    51,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    42,    43,    44,    45,    52,    53,    54,    55,
      56,    47,    48,     0,    49,     0,    50,   256,     0,     0,
       0,     0,    51,     0,   146,   147,   148,     0,   149,   150,
     151,   152,     0,     0,     0,     0,     0,    52,    53,    54,
      55,    56,   153,   154,   155,   156,   157,     0,     0,     0,
     158,   159,   160,   146,   147,   148,     0,   149,   150,   151,
     152,     0,   207,     0,     0,     0,     0,     0,     0,     0,
       0,   153,   154,   155,   156,   157,     0,     0,     0,   158,
     159,   160,   146,   147,   148,     0,   149,   150,   151,   152,
       0,   272,     0,     0,     0,     0,     0,     0,     0,     0,
     153,   154,   155,   156,   157,     0,     0,     0,   158,   159,
     160,   146,   147,   148,     0,   149,   150,   151,   152,     0,
     273,     0,     0,     0,     0,     0,     0,     0,     0,   153,
     154,   155,   156,   157,     0,     0,     0,   158,   159,   160,
     146,   147,   148,     0,   149,   150,   151,   152,     0,   290,
       0,     0,     0,     0,     0,     0,     0,     0,   153,   154,
     155,   156,   157,     0,     0,     0,   158,   159,   160,   146,
     147,   148,     0,   149,   150,   151,   152,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   153,   154,   155,
     156,   157,     0,     0,     0,   158,   159,   160,   147,   148,
       0,   149,   150,   151,   152,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   153,   154,   155,   156,   157,
       0,     0,     0,   158,   159,   160,   147,     0,     0,   149,
     150,   151,   152,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   153,   154,   155,   156,   157,     0,     0,
       0,   158,   159,   160,   149,   150,   151,   152,     0,     0,
       0,     0,     0,     0,     0,   149,   150,   151,   153,   154,
     155,   156,   157,     0,     0,     0,   158,   159,   160,   153,
     154,   155,   156,   157,     0,     0,     0,   158,   159,   160
  };

  const short int
  casmi_parser::yycheck_[] =
  {
      34,   196,   166,    50,    80,    49,    50,     9,    53,    52,
       9,    52,   145,    32,    33,    53,    52,    34,    79,    92,
      96,    97,    88,    31,     9,    53,   170,    51,    49,    50,
      49,    50,    76,    69,    79,    79,    79,    61,    79,    67,
       3,    79,     0,    49,    50,    79,    80,    29,    34,    51,
      52,    34,    51,   197,    88,    76,    75,    76,    77,    78,
      79,    95,    96,    97,    46,    79,    51,    49,   263,    75,
      76,    77,    12,    13,    14,    48,    16,    17,    18,    19,
      20,    21,    52,    23,    24,    57,    26,    27,    79,    61,
      30,    64,    65,    66,    34,    35,    36,    48,    38,    81,
      82,    83,    64,    65,    79,    75,    76,    77,    90,    91,
     176,   177,    94,    64,    65,   123,    56,   190,   251,    68,
     264,   285,    52,    79,    51,    51,    79,   193,   194,    51,
      79,   204,    51,    73,    61,    61,   170,    59,    58,    79,
      59,    51,   176,   177,    79,    75,    76,    77,   130,    51,
      52,    59,   134,   170,   162,   163,    79,    59,   166,   193,
     194,   208,   306,   197,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     197,   254,    79,    51,   170,   167,   252,   170,   332,   322,
      32,    59,    75,    76,   202,    75,    76,    77,    56,    48,
      49,    50,   184,    75,    76,    77,   253,    49,    50,    52,
      61,   197,    53,   195,   197,    64,    65,    66,   252,   253,
      11,    52,   256,   257,   232,    48,    79,    50,   210,    79,
     264,    59,    53,    75,    76,    77,    78,    79,   311,   312,
     248,    64,    65,    66,    61,    52,    51,   264,    68,   231,
     297,    69,    48,    49,    50,   321,    53,    79,   324,   325,
     326,   327,   328,   297,    79,    79,    62,   249,    64,    65,
      66,   337,   306,    79,   282,    79,    79,    64,   264,    56,
      55,   264,    67,    61,   350,    79,    57,   321,    53,   306,
     324,   325,   326,   327,   328,    22,    52,   279,   332,    49,
      39,    53,    64,   337,    51,   287,    76,    76,    61,    53,
      68,    48,    49,    50,    68,   332,   350,    55,    51,    79,
     306,    51,    53,   306,    52,    62,    63,    64,    65,    66,
      29,    12,    53,   315,    71,    72,    12,    59,    14,    15,
      16,    17,    18,    19,    20,    21,   332,    23,    24,   332,
      26,    27,    59,    59,    30,    59,   338,    53,    34,    35,
      36,    12,    38,    14,   199,    16,    17,    18,    19,    20,
      21,    35,    23,    24,   203,    26,    27,   165,   282,    30,
      56,   265,   311,    34,    35,    36,   297,    38,     4,     5,
       6,     7,     8,    -1,    10,   171,    -1,    73,   190,    -1,
      -1,    -1,    -1,    79,    -1,    56,    57,    -1,    -1,    12,
      -1,    14,    -1,    16,    17,    18,    19,    20,    21,    -1,
      23,    24,    73,    26,    27,    -1,    -1,    30,    79,    -1,
      -1,    34,    35,    36,    12,    38,    14,    -1,    16,    17,
      18,    19,    20,    21,    -1,    23,    24,    -1,    26,    27,
      -1,    -1,    30,    56,    -1,    -1,    34,    35,    36,    -1,
      38,    -1,    22,    -1,    -1,    48,    49,    50,    -1,    -1,
      73,    74,    -1,    -1,    -1,    -1,    79,    -1,    56,    62,
      63,    64,    65,    66,    44,    45,    46,    -1,    48,    49,
      50,    51,    22,    -1,    -1,    73,    -1,    -1,    -1,    -1,
      -1,    79,    62,    63,    64,    65,    66,    -1,    -1,    -1,
      70,    71,    72,    -1,    44,    45,    46,    -1,    48,    49,
      50,    51,    -1,    -1,    25,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    62,    63,    64,    65,    66,    48,    49,    50,
      70,    71,    72,    44,    45,    46,    -1,    48,    49,    50,
      51,    62,    63,    64,    65,    66,    28,    -1,    -1,    -1,
      71,    62,    63,    64,    65,    66,    -1,    -1,    -1,    70,
      71,    72,    44,    45,    46,    -1,    48,    49,    50,    51,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    31,    -1,
      62,    63,    64,    65,    66,    -1,    -1,    -1,    70,    71,
      72,    44,    45,    46,    -1,    48,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    71,    72,
      40,    41,    42,    43,    -1,    -1,    -1,    47,    -1,    49,
      50,    -1,    52,    -1,    54,    55,    -1,    -1,    -1,    -1,
      60,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    75,    76,    77,    78,    79,
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
      79,    49,    50,    -1,    52,    -1,    54,    37,    -1,    -1,
      -1,    -1,    60,    -1,    44,    45,    46,    -1,    48,    49,
      50,    51,    -1,    -1,    -1,    -1,    -1,    75,    76,    77,
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
      44,    45,    46,    -1,    48,    49,    50,    51,    -1,    53,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    71,    72,    44,
      45,    46,    -1,    48,    49,    50,    51,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    70,    71,    72,    45,    46,
      -1,    48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    71,    72,    45,    -1,    -1,    48,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    70,    71,    72,    48,    49,    50,    51,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    48,    49,    50,    62,    63,
      64,    65,    66,    -1,    -1,    -1,    70,    71,    72,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    71,    72
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
     115,   119,   121,   122,   123,   124,   125,   127,   128,   129,
     136,   137,   138,   140,   141,   144,   145,   146,   147,    53,
      94,    53,    61,    68,    96,    97,    11,    99,    79,   113,
      52,    75,    76,    77,    52,    75,    76,    77,   113,    55,
     104,   111,   112,   113,    79,    52,    44,    45,    46,    48,
      49,    50,    51,    62,    63,    64,    65,    66,    70,    71,
      72,    51,    59,    59,    53,    61,    52,    51,    90,    90,
      51,    61,   119,   120,   137,   138,   139,   139,   113,   113,
     113,    79,    79,   120,    52,    79,   113,   113,   102,   126,
      79,   113,   114,   139,   139,    69,     9,    51,    53,    79,
      79,    97,    68,    64,    56,   113,   113,    53,    67,    55,
      61,    53,   111,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,    97,
      97,    51,    59,    93,    49,    50,    97,    98,   105,   113,
      57,    53,   115,   118,    13,   120,    15,    51,    59,    22,
     113,    52,    28,    31,    49,   126,    37,    39,    57,    74,
     113,   117,   115,     9,    51,    92,    97,    96,    57,   100,
     101,   102,    53,    53,    49,    50,   104,   113,    53,    51,
     113,    97,    61,    53,    53,    67,    68,   142,    97,   113,
      53,   111,   120,    32,    78,   104,   114,   130,   131,   132,
     133,   134,   135,   102,   114,   114,    51,   117,   115,    99,
      57,    61,    68,    55,   113,    51,    98,   105,    79,   113,
      51,    25,    52,    53,    29,    59,    59,    59,    59,    33,
     131,   115,    51,   101,   102,   113,    53,    22,   143,   120,
     111,   120,   120,   120,   120,   120,   115,   120,   113,    53,
      22,   120
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
     121,   122,   123,   123,   124,   125,   126,   126,   127,   128,
     129,   130,   130,   131,   131,   131,   131,   132,   133,   134,
     135,   136,   136,   136,   136,   137,   137,   138,   138,   139,
     139,   140,   140,   142,   141,   143,   141,   144,   145,   146,
     147
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
       2,     2,     2,     1,     1,     3,     3,     1,     2,     3,
       5,     2,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     7,     4,     5,     2,     3,     3,     3,     3,     2,
       1,     4,     6,     0,     7,     0,     9,     4,     4,     6,
       2
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
  "DEBUG_SYNTAX", "DEBUG_ATOM_LIST", "PRINT_SYNTAX", "UPDATE_SYNTAX",
  "CASE_SYNTAX", "CASE_LABEL_LIST", "CASE_LABEL", "CASE_LABEL_DEFAULT",
  "CASE_LABEL_NUMBER", "CASE_LABEL_IDENT", "CASE_LABEL_STRING",
  "CALL_SYNTAX", "SEQ_SYNTAX", "PAR_SYNTAX", "STATEMENTS", "IFTHENELSE",
  "LET_SYNTAX", "$@1", "$@2", "PUSH_SYNTAX", "POP_SYNTAX", "FORALL_SYNTAX",
  "ITERATE_SYNTAX", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  casmi_parser::yyrline_[] =
  {
       0,   333,   333,   341,   348,   353,   362,   366,   370,   390,
     407,   411,   430,   438,   443,   477,   482,   486,   490,   494,
     498,   506,   511,   516,   520,   527,   531,   539,   544,   553,
     559,   567,   573,   584,   588,   596,   601,   609,   614,   619,
     627,   650,   663,   685,   703,   708,   712,   720,   724,   732,
     736,   740,   749,   753,   761,   765,   769,   773,   777,   822,
     826,   830,   834,   838,   842,   846,   850,   854,   862,   866,
     870,   878,   882,   886,   894,   898,   902,   910,   914,   918,
     927,   935,   951,   955,   963,   967,   975,   980,   989,   993,
     997,  1001,  1005,  1009,  1013,  1017,  1021,  1025,  1029,  1033,
    1037,  1041,  1045,  1049,  1053,  1061,  1065,  1069,  1083,  1087,
    1091,  1101,  1105,  1109,  1113,  1118,  1123,  1132,  1137,  1146,
    1154,  1158,  1162,  1166,  1170,  1174,  1178,  1182,  1186,  1190,
    1194,  1198,  1202,  1206,  1210,  1214,  1218,  1238,  1242,  1246,
    1254,  1262,  1270,  1274,  1290,  1298,  1306,  1311,  1319,  1327,
    1348,  1356,  1361,  1370,  1374,  1378,  1382,  1390,  1398,  1406,
    1414,  1422,  1426,  1430,  1434,  1442,  1446,  1454,  1458,  1466,
    1471,  1480,  1484,  1494,  1493,  1511,  1510,  1531,  1546,  1569,
    1577
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
#line 3601 "GrammarParser.cpp" // lalr1.cc:1167
#line 1583 "../../obj/src/GrammarParser.yy" // lalr1.cc:1168


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
