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
      case 140: // STATEMENTS
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
      case 104: // NUMBER
      case 109: // NUMBER_RANGE
        value.move< AtomNode* > (that.value);
        break;

      case 115: // FUNCTION_SYNTAX
        value.move< BaseFunctionAtom* > (that.value);
        break;

      case 137: // CALL_SYNTAX
        value.move< CallNode* > (that.value);
        break;

      case 130: // CASE_SYNTAX
        value.move< CaseNode* > (that.value);
        break;

      case 124: // DIEDIE_SYNTAX
        value.move< DiedieNode* > (that.value);
        break;

      case 87: // ENUM_SYNTAX
        value.move< Enum* > (that.value);
        break;

      case 102: // ATOM
      case 113: // EXPRESSION
      case 114: // BRACKET_EXPRESSION
        value.move< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.move< FLOATING_T > (that.value);
        break;

      case 106: // FLOATING_NUMBER
        value.move< FloatingAtom* > (that.value);
        break;

      case 147: // FORALL_SYNTAX
        value.move< ForallNode* > (that.value);
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        value.move< Function* > (that.value);
        break;

      case 76: // "integer"
        value.move< INTEGER_T > (that.value);
        break;

      case 141: // IFTHENELSE
        value.move< IfThenElseNode* > (that.value);
        break;

      case 85: // INIT_SYNTAX
        value.move< InitNode* > (that.value);
        break;

      case 105: // INTEGER_NUMBER
        value.move< IntegerAtom* > (that.value);
        break;

      case 142: // LET_SYNTAX
        value.move< LetNode* > (that.value);
        break;

      case 146: // POP_SYNTAX
        value.move< PopNode* > (that.value);
        break;

      case 126: // DEBUG_SYNTAX
      case 128: // PRINT_SYNTAX
        value.move< PrintNode* > (that.value);
        break;

      case 145: // PUSH_SYNTAX
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

      case 122: // ASSERT_SYNTAX
      case 123: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        value.move< UnaryNode* > (that.value);
        break;

      case 129: // UPDATE_SYNTAX
        value.move< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.move< rational_t > (that.value);
        break;

      case 132: // CASE_LABEL
      case 133: // CASE_LABEL_DEFAULT
      case 134: // CASE_LABEL_NUMBER
      case 135: // CASE_LABEL_IDENT
      case 136: // CASE_LABEL_STRING
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
      case 108: // RULEREF
        value.move< std::string > (that.value);
        break;

      case 127: // DEBUG_ATOM_LIST
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

      case 131: // CASE_LABEL_LIST
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
      case 140: // STATEMENTS
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
      case 104: // NUMBER
      case 109: // NUMBER_RANGE
        value.copy< AtomNode* > (that.value);
        break;

      case 115: // FUNCTION_SYNTAX
        value.copy< BaseFunctionAtom* > (that.value);
        break;

      case 137: // CALL_SYNTAX
        value.copy< CallNode* > (that.value);
        break;

      case 130: // CASE_SYNTAX
        value.copy< CaseNode* > (that.value);
        break;

      case 124: // DIEDIE_SYNTAX
        value.copy< DiedieNode* > (that.value);
        break;

      case 87: // ENUM_SYNTAX
        value.copy< Enum* > (that.value);
        break;

      case 102: // ATOM
      case 113: // EXPRESSION
      case 114: // BRACKET_EXPRESSION
        value.copy< ExpressionBase* > (that.value);
        break;

      case 75: // "floating"
        value.copy< FLOATING_T > (that.value);
        break;

      case 106: // FLOATING_NUMBER
        value.copy< FloatingAtom* > (that.value);
        break;

      case 147: // FORALL_SYNTAX
        value.copy< ForallNode* > (that.value);
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        value.copy< Function* > (that.value);
        break;

      case 76: // "integer"
        value.copy< INTEGER_T > (that.value);
        break;

      case 141: // IFTHENELSE
        value.copy< IfThenElseNode* > (that.value);
        break;

      case 85: // INIT_SYNTAX
        value.copy< InitNode* > (that.value);
        break;

      case 105: // INTEGER_NUMBER
        value.copy< IntegerAtom* > (that.value);
        break;

      case 142: // LET_SYNTAX
        value.copy< LetNode* > (that.value);
        break;

      case 146: // POP_SYNTAX
        value.copy< PopNode* > (that.value);
        break;

      case 126: // DEBUG_SYNTAX
      case 128: // PRINT_SYNTAX
        value.copy< PrintNode* > (that.value);
        break;

      case 145: // PUSH_SYNTAX
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

      case 122: // ASSERT_SYNTAX
      case 123: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        value.copy< UnaryNode* > (that.value);
        break;

      case 129: // UPDATE_SYNTAX
        value.copy< UpdateNode* > (that.value);
        break;

      case 77: // "rational"
        value.copy< rational_t > (that.value);
        break;

      case 132: // CASE_LABEL
      case 133: // CASE_LABEL_DEFAULT
      case 134: // CASE_LABEL_NUMBER
      case 135: // CASE_LABEL_IDENT
      case 136: // CASE_LABEL_STRING
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
      case 108: // RULEREF
        value.copy< std::string > (that.value);
        break;

      case 127: // DEBUG_ATOM_LIST
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

      case 131: // CASE_LABEL_LIST
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

#line 881 "GrammarParser.cpp" // lalr1.cc:741

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
      case 140: // STATEMENTS
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
      case 104: // NUMBER
      case 109: // NUMBER_RANGE
        yylhs.value.build< AtomNode* > ();
        break;

      case 115: // FUNCTION_SYNTAX
        yylhs.value.build< BaseFunctionAtom* > ();
        break;

      case 137: // CALL_SYNTAX
        yylhs.value.build< CallNode* > ();
        break;

      case 130: // CASE_SYNTAX
        yylhs.value.build< CaseNode* > ();
        break;

      case 124: // DIEDIE_SYNTAX
        yylhs.value.build< DiedieNode* > ();
        break;

      case 87: // ENUM_SYNTAX
        yylhs.value.build< Enum* > ();
        break;

      case 102: // ATOM
      case 113: // EXPRESSION
      case 114: // BRACKET_EXPRESSION
        yylhs.value.build< ExpressionBase* > ();
        break;

      case 75: // "floating"
        yylhs.value.build< FLOATING_T > ();
        break;

      case 106: // FLOATING_NUMBER
        yylhs.value.build< FloatingAtom* > ();
        break;

      case 147: // FORALL_SYNTAX
        yylhs.value.build< ForallNode* > ();
        break;

      case 88: // DERIVED_SYNTAX
      case 89: // FUNCTION_DEFINITION
        yylhs.value.build< Function* > ();
        break;

      case 76: // "integer"
        yylhs.value.build< INTEGER_T > ();
        break;

      case 141: // IFTHENELSE
        yylhs.value.build< IfThenElseNode* > ();
        break;

      case 85: // INIT_SYNTAX
        yylhs.value.build< InitNode* > ();
        break;

      case 105: // INTEGER_NUMBER
        yylhs.value.build< IntegerAtom* > ();
        break;

      case 142: // LET_SYNTAX
        yylhs.value.build< LetNode* > ();
        break;

      case 146: // POP_SYNTAX
        yylhs.value.build< PopNode* > ();
        break;

      case 126: // DEBUG_SYNTAX
      case 128: // PRINT_SYNTAX
        yylhs.value.build< PrintNode* > ();
        break;

      case 145: // PUSH_SYNTAX
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

      case 122: // ASSERT_SYNTAX
      case 123: // ASSURE_SYNTAX
      case 138: // SEQ_SYNTAX
      case 139: // PAR_SYNTAX
      case 148: // ITERATE_SYNTAX
        yylhs.value.build< UnaryNode* > ();
        break;

      case 129: // UPDATE_SYNTAX
        yylhs.value.build< UpdateNode* > ();
        break;

      case 77: // "rational"
        yylhs.value.build< rational_t > ();
        break;

      case 132: // CASE_LABEL
      case 133: // CASE_LABEL_DEFAULT
      case 134: // CASE_LABEL_NUMBER
      case 135: // CASE_LABEL_IDENT
      case 136: // CASE_LABEL_STRING
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
      case 108: // RULEREF
        yylhs.value.build< std::string > ();
        break;

      case 127: // DEBUG_ATOM_LIST
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

      case 131: // CASE_LABEL_LIST
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
#line 334 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.result = new Ast( yylhs.location, yystack_[1].value.as< SpecificationNode* > (), yystack_[0].value.as< AstListNode* > () );
  }
#line 1183 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 342 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< SpecificationNode* > () = new SpecificationNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1191 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 349 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[1].value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
	  yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 1200 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 354 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstListNode* > () = new AstListNode(yylhs.location, NodeType::BODY_ELEMENTS);
	  yylhs.value.as< AstListNode* > ()->add(yystack_[0].value.as< AstNode* > ());
  }
#line 1209 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 363 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode(NodeType::OPTION);
  }
#line 1217 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 367 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new EnumDefNode(yylhs.location, yystack_[0].value.as< Enum* > ());
  }
#line 1225 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1249 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1270 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 408 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< InitNode* > ();
  }
#line 1278 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1297 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 431 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< InitNode* > () = new InitNode( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 1305 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1339 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 478 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  // TODO: 2nd argument should be a reference
	  yylhs.value.as< Function* > () = new Function(yystack_[5].value.as< std::string > (), yylhs.location, yystack_[3].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1348 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 483 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1356 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 487 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), new Type(TypeType::UNKNOWN));
  }
#line 1364 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 491 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[7].value.as< std::string > (), yylhs.location, yystack_[5].value.as< std::vector<Type*> > (), yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1372 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 495 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[4].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1380 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 499 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[6].value.as< std::string > (), yylhs.location, yystack_[0].value.as< ExpressionBase* > (), yystack_[2].value.as< Type* > ());
  }
#line 1388 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 507 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[4].value.as< std::vector<std::string> > ());
	  yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 512 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto attrs = parse_function_attributes(driver, yylhs.location, yystack_[3].value.as< std::vector<std::string> > ());
	  yylhs.value.as< Function* > () = new Function(attrs.first, attrs.second, yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1406 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 517 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[2].value.as< std::string > (), yylhs.location, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[1].value.as< std::pair<std::vector<Type*>, Type*> > ().second, yystack_[0].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ());
  }
#line 1414 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 521 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< Function* > () = new Function(yystack_[1].value.as< std::string > (), yylhs.location, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().first, yystack_[0].value.as< std::pair<std::vector<Type*>, Type*> > ().second, nullptr);
  }
#line 1422 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 528 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[1].value.as< std::vector<std::string> > ());
  }
#line 1430 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 532 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::move(yystack_[0].value.as< std::vector<std::string> > ());
  }
#line 1438 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 540 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
      yylhs.value.as< std::vector<std::string> > () = std::move( yystack_[2].value.as< std::vector<std::string> > () );
      yylhs.value.as< std::vector<std::string> > ().push_back( yystack_[0].value.as< std::string > () );
  }
#line 1447 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 545 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::string> > () = std::vector<std::string>();
	  yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ());
  }
#line 1456 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 554 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  /* this constructor is implementation dependant! */
	  std::vector<Type*> foo;
	  yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(foo, yystack_[0].value.as< Type* > ());
  }
#line 1466 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 560 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<std::vector<Type*>, Type*> > () = std::pair<std::vector<Type*>, Type*>(yystack_[2].value.as< std::vector<Type*> > (), yystack_[0].value.as< Type* > ());
  }
#line 1474 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 568 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  size_t size = driver.binding_offsets.size();
	  driver.binding_offsets[yystack_[2].value.as< std::string > ()] = size;
	  yylhs.value.as< Type* > () = yystack_[0].value.as< Type* > ();
  }
#line 1484 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 574 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  size_t size = driver.binding_offsets.size();
	  driver.binding_offsets[yystack_[0].value.as< std::string > ()] = size;
	  // TODO: fail for rules without types and print warnings
	  yylhs.value.as< Type* > () = new Type(TypeType::INTEGER);
  }
#line 1495 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 585 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1503 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 589 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[1].value.as< std::vector<Type*> > ());
  }
#line 1511 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 597 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[2].value.as< std::vector<Type*> > ());
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1520 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 602 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1528 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 610 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< std::vector<Type*> > ().insert(yystack_[0].value.as< std::vector<Type*> > ().begin(), yystack_[2].value.as< Type* > ());
	  yylhs.value.as< std::vector<Type*> > () = std::move(yystack_[0].value.as< std::vector<Type*> > ());
  }
#line 1537 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 615 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  // TODO: limit memory size
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[1].value.as< Type* > ());
  }
#line 1546 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 620 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back(yystack_[0].value.as< Type* > ());
  }
#line 1554 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1581 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1598 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1624 "GrammarParser.cpp" // lalr1.cc:859
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
#line 1642 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 704 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< std::vector<Type*> > ().push_back( yystack_[2].value.as< Type* > () );
	  yylhs.value.as< std::vector<Type*> > () = std::move( yystack_[0].value.as< std::vector<Type*> > () );
  }
#line 1651 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 709 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[1].value.as< Type* > () );
  }
#line 1659 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 713 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<Type*> > ().push_back( yystack_[0].value.as< Type* > () );
  }
#line 1667 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 721 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1675 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 725 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = nullptr;
  }
#line 1683 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 733 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > (); yystack_[2].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1691 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 737 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = yystack_[1].value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ();
  }
#line 1699 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 741 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > () = new std::vector< std::pair<ExpressionBase*, ExpressionBase* > >();
	  yylhs.value.as< std::vector<std::pair<ExpressionBase*, ExpressionBase*>>* > ()->push_back( yystack_[0].value.as< std::pair<ExpressionBase*, ExpressionBase*> > () );
  }
#line 1708 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 750 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(nullptr, yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1716 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 754 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<ExpressionBase*, ExpressionBase*> > () = std::pair<ExpressionBase*, ExpressionBase*>(yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > ());
  }
#line 1724 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 762 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< BaseFunctionAtom* > ();
  }
#line 1732 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 766 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1740 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 56:
#line 770 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 1748 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 57:
#line 778 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new RuleAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 58:
#line 782 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1764 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 59:
#line 786 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new StringAtom( yylhs.location, std::move( yystack_[0].value.as< std::string > () ) );
  }
#line 1772 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 60:
#line 790 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new ListAtom( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 1780 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 61:
#line 794 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< AtomNode* > ();
  }
#line 1788 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 62:
#line 798 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new SelfAtom( yylhs.location );
  }
#line 1796 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 63:
#line 802 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new UndefAtom( yylhs.location );
  }
#line 1804 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 64:
#line 806 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, true );
  }
#line 1812 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 65:
#line 810 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = new BooleanAtom( yylhs.location, false );
  }
#line 1820 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 66:
#line 818 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< IntegerAtom* > ();
  }
#line 1828 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 67:
#line 822 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< FloatingAtom* > ();
  }
#line 1836 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 68:
#line 826 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AtomNode* > () = yystack_[0].value.as< RationalAtom* > ();
  }
#line 1844 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 69:
#line 834 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1852 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 70:
#line 838 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, (-1) * yystack_[0].value.as< INTEGER_T > () );
  }
#line 1860 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 71:
#line 842 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IntegerAtom* > () = new IntegerAtom( yylhs.location, yystack_[0].value.as< INTEGER_T > () );
  }
#line 1868 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 72:
#line 850 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1876 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 73:
#line 854 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, (-1) * yystack_[0].value.as< FLOATING_T > () );
  }
#line 1884 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 74:
#line 858 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< FloatingAtom* > () = new FloatingAtom( yylhs.location, yystack_[0].value.as< FLOATING_T > () );
  }
#line 1892 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 75:
#line 866 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1900 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 76:
#line 870 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[0].value.as< rational_t > ().numerator *= -1;
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1909 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 77:
#line 875 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< RationalAtom* > () = new RationalAtom( yylhs.location, yystack_[0].value.as< rational_t > () );
  }
#line 1917 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 78:
#line 883 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ();
  }
#line 1925 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 79:
#line 891 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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

  case 80:
#line 907 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1949 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 81:
#line 911 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >();
  }
#line 1957 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 82:
#line 919 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[0].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1965 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 83:
#line 923 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[1].value.as< std::vector<ExpressionBase*>* > ();
  }
#line 1973 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 84:
#line 931 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = yystack_[2].value.as< std::vector<ExpressionBase*>* > ();
	  yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1982 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 85:
#line 936 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*>* > () = new std::vector< ExpressionBase* >;
	  yylhs.value.as< std::vector<ExpressionBase*>* > ()->push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 1991 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 86:
#line 945 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::ADD );
  }
#line 1999 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 87:
#line 949 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::SUB );
  }
#line 2007 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 88:
#line 953 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MUL );
  }
#line 2015 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 89:
#line 957 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::DIV );
  }
#line 2023 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 90:
#line 961 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::MOD );
  }
#line 2031 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 91:
#line 965 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::RAT_DIV );
  }
#line 2039 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 92:
#line 969 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::NEQ );
  }
#line 2047 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 93:
#line 973 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::EQ );
  }
#line 2055 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 94:
#line 977 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSER );
  }
#line 2063 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 95:
#line 981 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATER );
  }
#line 2071 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 96:
#line 985 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::LESSEREQ );
  }
#line 2079 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 97:
#line 989 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::GREATEREQ );
  }
#line 2087 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 98:
#line 993 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::OR );
  }
#line 2095 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 99:
#line 997 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::XOR );
  }
#line 2103 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 100:
#line 1001 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< ExpressionBase* > (), ExpressionOperation::AND );
  }
#line 2111 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 101:
#line 1005 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = new Expression( yylhs.location, yystack_[0].value.as< ExpressionBase* > (), nullptr, ExpressionOperation::NOT );
  }
#line 2119 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 102:
#line 1009 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[0].value.as< ExpressionBase* > ();
  }
#line 2127 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 103:
#line 1017 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ExpressionBase* > () = yystack_[1].value.as< ExpressionBase* > ();
  }
#line 2135 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 104:
#line 1025 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[0].value.as< std::string > () );
  }
#line 2143 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 105:
#line 1029 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< BaseFunctionAtom* > () = new FunctionAtom( yylhs.location, yystack_[2].value.as< std::string > () );
  }
#line 2151 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 106:
#line 1033 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2166 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 107:
#line 1047 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2174 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 108:
#line 1051 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2182 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 109:
#line 1055 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  auto stmts = new AstListNode( yylhs.location, NodeType::STATEMENTS );
	  stmts->add( yystack_[0].value.as< AstNode* > () );
	  yylhs.value.as< AstNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, stmts );
  }
#line 2192 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 110:
#line 1065 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[2].value.as< std::string > () );
  }
#line 2200 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 111:
#line 1069 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > () );
  }
#line 2208 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 112:
#line 1073 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<Type*> > () );
  }
#line 2216 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 113:
#line 1077 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[4].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2225 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 114:
#line 1082 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[6].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2234 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 115:
#line 1087 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  std::vector< Type* > tmp;
	  yylhs.value.as< AstNode* > () = new RuleNode( yylhs.location, yystack_[0].value.as< AstNode* > (), yystack_[7].value.as< std::string > (), tmp, yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
  }
#line 2243 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 116:
#line 1096 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::move( yystack_[2].value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () );
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () );
  }
#line 2252 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 117:
#line 1101 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > () = std::vector< std::pair< std::string, std::vector<std::string> > >();
	  yylhs.value.as< std::vector<std::pair<std::string, std::vector<std::string>>> > ().push_back( std::move( yystack_[0].value.as< std::pair<std::string, std::vector<std::string>> > () ) );
  }
#line 2261 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 118:
#line 1110 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<std::string, std::vector<std::string>> > () = std::pair< std::string, std::vector< std::string > >( yystack_[0].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > () );
  }
#line 2269 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 119:
#line 1118 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2277 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 120:
#line 1122 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2285 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 121:
#line 1126 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< DiedieNode* > ();
  }
#line 2293 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 122:
#line 1130 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2301 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 123:
#line 1134 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2309 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 124:
#line 1138 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PrintNode* > ();
  }
#line 2317 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 125:
#line 1142 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UpdateNode* > ();
  }
#line 2325 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 126:
#line 1146 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< CaseNode* > ();
  }
#line 2333 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 127:
#line 1150 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< CallNode* > ();
  }
#line 2341 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 128:
#line 1154 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< IfThenElseNode* > ();
  }
#line 2349 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 129:
#line 1158 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< LetNode* > ();
  }
#line 2357 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 130:
#line 1162 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PushNode* > ();
  }
#line 2365 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 131:
#line 1166 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< PopNode* > ();
  }
#line 2373 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 132:
#line 1170 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< ForallNode* > ();
  }
#line 2381 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 133:
#line 1174 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2389 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 134:
#line 1178 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode( NodeType::SKIP );
  }
#line 2397 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 135:
#line 1182 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.error
	  ( yylhs.location
	  , "syntax error: invalid statement '" + yystack_[0].value.as< std::string > () + "' found"
	  , libcasm_fe::Codes::SyntaxErrorInvalidStatement
	  );
  }
#line 2409 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 136:
#line 1202 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< AstNode* > ();
  }
#line 2417 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 137:
#line 1206 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2425 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 138:
#line 1210 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = yystack_[0].value.as< UnaryNode* > ();
  }
#line 2433 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 139:
#line 1218 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSERT, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2441 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 140:
#line 1226 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ASSURE, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2449 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 141:
#line 1234 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2457 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 142:
#line 1238 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< DiedieNode* > () = new DiedieNode( yylhs.location, nullptr );
  }
#line 2465 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 143:
#line 1254 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstNode* > () = new AstNode( yylhs.location, NodeType::IMPOSSIBLE );
  }
#line 2473 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 144:
#line 1262 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::vector<ExpressionBase*> > () );
  }
#line 2481 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 145:
#line 1270 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*> > () = std::move( yystack_[2].value.as< std::vector<ExpressionBase*> > () );
	  yylhs.value.as< std::vector<ExpressionBase*> > ().push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2490 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 146:
#line 1275 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<ExpressionBase*> > ().push_back( yystack_[0].value.as< ExpressionBase* > () );
  }
#line 2498 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 147:
#line 1283 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< PrintNode* > () = new PrintNode( yylhs.location, yystack_[0].value.as< std::vector<ExpressionBase*> > () );
  }
#line 2506 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 148:
#line 1291 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
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
#line 2527 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 149:
#line 1312 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CaseNode* > () = new CaseNode( yylhs.location, yystack_[3].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
  }
#line 2535 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 150:
#line 1320 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( yystack_[1].value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () );
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2544 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 151:
#line 1325 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > () = std::move( std::vector< std::pair< AtomNode*, AstNode* > >() );
	  yylhs.value.as< std::vector<std::pair<AtomNode*, AstNode*>> > ().push_back( yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > () );
  }
#line 2553 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 152:
#line 1334 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () =yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2561 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 153:
#line 1338 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2569 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 154:
#line 1342 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2577 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 155:
#line 1346 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = yystack_[0].value.as< std::pair<AtomNode*, AstNode*> > ();
  }
#line 2585 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 156:
#line 1354 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( nullptr, yystack_[0].value.as< AstNode* > () );
  }
#line 2593 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 157:
#line 1362 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< AtomNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2601 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 158:
#line 1370 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( yystack_[2].value.as< BaseFunctionAtom* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2609 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 159:
#line 1378 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< std::pair<AtomNode*, AstNode*> > () = std::pair< AtomNode*, AstNode* >( new StringAtom( yylhs.location, std::move( yystack_[2].value.as< std::string > () ) ), yystack_[0].value.as< AstNode* > () );
  }
#line 2617 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 160:
#line 1386 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[4].value.as< ExpressionBase* > (), yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2625 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 161:
#line 1390 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, "", yystack_[1].value.as< ExpressionBase* > () );
  }
#line 2633 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 162:
#line 1394 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[3].value.as< std::string > (), nullptr, yystack_[1].value.as< std::vector<ExpressionBase*>* > () );
  }
#line 2641 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 163:
#line 1398 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< CallNode* > () = new CallNode( yylhs.location, yystack_[0].value.as< std::string > (), nullptr );
  }
#line 2649 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 164:
#line 1406 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2657 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 165:
#line 1410 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::SEQBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2665 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 166:
#line 1418 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2673 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 167:
#line 1422 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::PARBLOCK, yystack_[1].value.as< AstListNode* > () );
  }
#line 2681 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 168:
#line 1430 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yystack_[1].value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
	  yylhs.value.as< AstListNode* > () = yystack_[1].value.as< AstListNode* > ();
  }
#line 2690 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 169:
#line 1435 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< AstListNode* > () = new AstListNode( yylhs.location, NodeType::STATEMENTS );
	  yylhs.value.as< AstListNode* > ()->add( yystack_[0].value.as< AstNode* > () );
  }
#line 2699 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 170:
#line 1444 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > (), nullptr );
  }
#line 2707 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 171:
#line 1448 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< IfThenElseNode* > () = new IfThenElseNode( yylhs.location, yystack_[4].value.as< ExpressionBase* > (), yystack_[2].value.as< AstNode* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2715 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2731 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 173:
#line 1469 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.function_table.remove( yystack_[5].value.as< std::string > () );
	  yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, Type( TypeType::UNKNOWN ), yystack_[5].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2740 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2756 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 175:
#line 1486 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  driver.function_table.remove( yystack_[7].value.as< std::string > () );
	  yylhs.value.as< LetNode* > () = new LetNode( yylhs.location, yystack_[5].value.as< Type* > (), yystack_[7].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2765 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2780 "GrammarParser.cpp" // lalr1.cc:859
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
#line 2803 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 178:
#line 1533 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< ForallNode* > () = new ForallNode( yylhs.location, yystack_[4].value.as< std::string > (), yystack_[2].value.as< ExpressionBase* > (), yystack_[0].value.as< AstNode* > () );
  }
#line 2811 "GrammarParser.cpp" // lalr1.cc:859
    break;

  case 179:
#line 1541 "../../obj/src/GrammarParser.yy" // lalr1.cc:859
    {
	  yylhs.value.as< UnaryNode* > () = new UnaryNode( yylhs.location, NodeType::ITERATE, yystack_[0].value.as< AstNode* > () );
  }
#line 2819 "GrammarParser.cpp" // lalr1.cc:859
    break;


#line 2823 "GrammarParser.cpp" // lalr1.cc:859
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


  const short int casmi_parser::yypact_ninf_ = -191;

  const signed char casmi_parser::yytable_ninf_ = -105;

  const short int
  casmi_parser::yypact_[] =
  {
       9,   -43,    54,   379,  -191,  -191,   -13,    20,    25,    34,
      61,   -48,   379,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,    17,    60,    28,    -2,    70,    89,  -191,    75,   634,
     -39,   112,   136,   155,   416,    -8,  -191,   141,   137,    12,
     188,   153,  -191,  -191,  -191,  -191,   634,   146,   149,   634,
     554,   154,  -191,  -191,  -191,  -191,   166,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,   801,  -191,  -191,   -17,
     186,  -191,   196,   192,   202,   204,    70,    70,    47,  -191,
     416,   416,   634,   634,   634,  -191,  -191,   189,   191,   416,
     -44,   634,   634,   696,   194,   634,   195,   416,   416,    -4,
     206,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,
       0,   218,   197,   203,   112,   209,   217,   233,  -191,  -191,
    -191,  -191,  -191,  -191,  -191,  -191,  -191,   743,  -191,   227,
     245,   240,   801,  -191,   594,   634,   634,   634,   634,   634,
     634,   634,   634,   634,   634,   634,   634,   634,   634,   634,
     634,   112,   112,    22,   223,    18,   634,   253,   264,   416,
     155,  -191,  -191,  -191,  -191,     3,   309,   801,   801,   801,
      69,   297,  -191,   634,   270,   492,   521,  -191,   285,   696,
     714,   298,   343,   391,   634,   155,   416,     2,    89,  -191,
    -191,   112,   112,   665,  -191,    46,  -191,   634,  -191,   287,
     829,   882,   857,    13,   198,    36,   893,   193,   147,  -191,
     274,    91,   912,   411,   249,   801,   290,  -191,   634,   112,
    -191,   266,   272,   288,   293,   -35,   801,  -191,   282,  -191,
    -191,  -191,  -191,  -191,  -191,   112,   634,   772,   634,   416,
     229,   696,   285,   195,   195,  -191,  -191,   801,   139,  -191,
     155,   416,   188,  -191,  -191,  -191,   100,  -191,   283,   301,
     801,  -191,   634,   801,   302,   112,  -191,  -191,     7,   273,
     634,   307,   463,   316,   318,   345,   313,   317,   321,   331,
      11,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191,   416,
     142,  -191,  -191,  -191,   696,   696,  -191,   801,   634,  -191,
     322,  -191,    81,  -191,   416,   634,  -191,   416,   416,   416,
     416,   416,  -191,  -191,  -191,   416,  -191,  -191,   801,  -191,
     416,   634,  -191,   338,  -191,  -191,  -191,  -191,  -191,  -191,
    -191,   434,  -191,   416,  -191
  };

  const unsigned char
  casmi_parser::yydefact_[] =
  {
       0,     0,     0,     0,     3,     1,     0,     0,     0,     0,
       0,     0,     2,     5,    10,     6,     7,     9,     8,    11,
      12,     0,     0,     0,     0,     0,     0,     4,     0,     0,
       0,     0,     0,     0,     0,     0,    28,     0,    26,     0,
      24,     0,    62,    63,    65,    64,     0,     0,     0,     0,
       0,     0,    74,    71,    77,    59,   104,   102,    55,    58,
      66,    67,    68,    57,    61,    60,    16,    56,    54,     0,
      32,    36,     0,    33,    40,     0,     0,     0,     0,   117,
       0,     0,     0,     0,   142,   143,   134,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   135,
       0,   110,   109,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   107,   108,   128,   129,   130,   131,   132,   133,
       0,     0,     0,    25,     0,     0,    39,     0,    23,    13,
     101,    72,    69,    75,    73,    70,    76,     0,    81,    58,
       0,    82,    85,    78,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    34,     0,     0,     0,     0,     0,
       0,   136,   169,   137,   138,     0,     0,   139,   140,   141,
       0,     0,   179,     0,   163,     0,     0,   146,   147,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    27,
      29,     0,    38,     0,   103,     0,    80,    83,   105,     0,
     100,    98,    99,    91,    86,    87,    93,    94,    95,    88,
      89,    90,    92,    96,    97,    17,     0,    31,     0,     0,
      35,     0,     0,    46,     0,     0,    19,    14,     0,   113,
     116,   165,   168,   167,   172,     0,     0,     0,     0,     0,
       0,     0,   144,     0,     0,   166,   164,   148,     0,   111,
       0,     0,    22,    30,    37,    48,     0,    51,    52,     0,
      84,   106,     0,    15,     0,    45,    42,    41,     0,     0,
       0,     0,     0,   161,     0,   170,     0,     0,     0,     0,
       0,   151,   152,   153,   154,   155,   145,   176,   177,     0,
       0,   112,    21,    47,    50,     0,    79,    20,     0,    44,
       0,   118,     0,   174,     0,     0,   162,     0,     0,     0,
       0,     0,   149,   150,   114,     0,    49,    53,    18,    43,
       0,     0,   178,     0,   171,   156,   159,   157,   158,   115,
     173,     0,   160,     0,   175
  };

  const short int
  casmi_parser::yypgoto_[] =
  {
    -191,  -191,  -191,  -191,   380,  -191,  -191,  -191,  -191,  -191,
      57,  -191,   199,   230,   358,  -191,   200,    43,   120,   134,
    -191,    94,   -65,  -191,   -40,  -162,  -191,  -191,  -191,  -191,
    -191,  -131,  -191,    23,  -191,   -34,  -111,  -191,  -190,   231,
     -33,   -83,  -191,  -191,  -191,  -191,  -191,   215,  -191,  -191,
    -191,  -191,   116,  -191,  -191,  -191,  -191,  -191,   -32,    -9,
     104,  -191,  -191,  -191,  -191,  -191,  -191,  -191,  -191
  };

  const short int
  casmi_parser::yydefgoto_[] =
  {
      -1,     2,     3,    12,    13,    14,    15,    16,    17,    18,
      37,    38,    40,    71,    72,    73,   125,   126,   234,   128,
     266,   267,    57,    58,    59,    60,    61,    62,    63,    64,
      65,   140,   141,   142,    67,    68,   101,    19,    78,    79,
     171,   172,   103,   104,   105,   106,   107,   188,   108,   109,
     110,   290,   291,   292,   293,   294,   295,   111,   173,   174,
     175,   114,   115,   280,   331,   116,   117,   118,   119
  };

  const short int
  casmi_parser::yytable_[] =
  {
     100,   102,   112,   235,    25,   258,   182,    33,   183,   195,
     139,   260,     1,   209,    69,    80,   241,    81,   277,    82,
      83,    84,    85,    86,    87,   113,    88,    89,   187,    90,
      91,    26,   278,    92,   160,   184,     4,    93,    94,    95,
      70,    96,   161,   286,   322,   120,   100,   100,   144,    34,
      35,   196,    66,   261,     5,   100,   231,   232,   239,    97,
      47,    48,   191,   100,   100,  -104,    20,   231,   232,   130,
     300,    70,   137,   228,    75,    28,    98,   154,   155,    32,
     124,   229,    99,    53,   148,   259,    52,    53,    54,   287,
      56,    74,   242,   242,    53,    47,    48,    74,   169,    21,
     154,   155,   156,   330,    22,   177,   178,   179,   170,   242,
     242,    29,    30,    23,   185,   186,   310,   284,   190,    31,
     244,    52,    53,    54,   187,   145,   146,   147,   245,   148,
     149,   150,   151,   167,   168,   100,   102,   112,   268,   148,
      24,   100,   100,   152,   153,   154,   155,   156,    39,    36,
     301,   157,   158,   159,    41,   154,   155,   303,   100,   100,
     113,   304,   100,   102,   112,   269,   285,   200,   210,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   333,   176,   296,   113,   324,   236,
     299,    74,    76,   325,   122,   148,   149,   150,   123,   127,
     170,   192,   193,   170,   226,   227,   247,    77,   233,   152,
     288,   154,   155,   156,   339,   100,   289,   257,   144,   297,
     298,   131,   132,   133,   134,   135,   136,   100,   102,   112,
     270,   332,   129,   143,   334,   335,   336,   337,   338,   268,
     327,   148,   149,   150,   263,   162,   148,   340,   150,   163,
     288,   273,   113,   164,   165,   166,   289,   154,   155,   156,
     344,   286,   154,   155,   156,   100,   102,   112,   180,   282,
     181,   197,   274,   189,    56,   194,   198,   201,    47,    48,
     100,   202,   199,   100,   100,   100,   100,   100,   281,   203,
     113,   100,   102,   112,   205,   307,   100,   148,   149,   150,
     206,   207,    70,   312,    52,    53,    54,   287,    56,   100,
     237,   152,   153,   154,   155,   156,   113,   238,   233,   246,
     158,    80,   248,    81,   243,    82,    83,    84,    85,    86,
      87,   328,    88,    89,   251,    90,    91,   254,   154,    92,
     271,   272,   132,    93,    94,    95,   276,    96,   135,   275,
     279,   305,   311,   308,   341,    80,   306,    81,   313,    82,
      83,    84,    85,    86,    87,    97,    88,    89,   315,    90,
      91,   316,   318,    92,   317,   329,   319,    93,    94,    95,
     320,    96,    98,     6,     7,     8,     9,    10,    99,    11,
     321,   342,    27,   121,   230,   309,   302,   262,   326,    97,
     255,   240,   264,    80,   252,    81,   323,    82,    83,    84,
      85,    86,    87,     0,    88,    89,    98,    90,    91,     0,
       0,    92,    99,     0,     0,    93,    94,    95,    80,    96,
      81,     0,    82,    83,    84,    85,    86,    87,     0,    88,
      89,     0,    90,    91,     0,     0,    92,    97,     0,     0,
      93,    94,    95,     0,    96,     0,   343,     0,     0,   148,
     149,   150,     0,     0,    98,   256,     0,     0,     0,     0,
      99,     0,    97,   152,   153,   154,   155,   156,   145,   146,
     147,     0,   148,   149,   150,   151,     0,     0,   314,    98,
       0,     0,     0,     0,     0,    99,   152,   153,   154,   155,
     156,     0,     0,     0,   157,   158,   159,   145,   146,   147,
       0,   148,   149,   150,   151,     0,     0,     0,     0,     0,
     249,     0,     0,     0,     0,   152,   153,   154,   155,   156,
       0,     0,     0,   157,   158,   159,   145,   146,   147,     0,
     148,   149,   150,   151,     0,     0,     0,     0,     0,     0,
       0,     0,   250,     0,   152,   153,   154,   155,   156,     0,
       0,     0,   157,   158,   159,   145,   146,   147,     0,   148,
     149,   150,   151,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,     0,     0,
       0,   157,   158,   159,    42,    43,    44,    45,     0,     0,
       0,    46,     0,    47,    48,     0,    49,     0,    50,   138,
       0,     0,     0,     0,    51,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    52,
      53,    54,    55,    56,    42,    43,    44,    45,     0,     0,
       0,    46,     0,    47,    48,     0,    49,   208,    50,     0,
       0,     0,     0,     0,    51,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    52,
      53,    54,    55,    56,    42,    43,    44,    45,     0,     0,
       0,    46,     0,    47,    48,     0,    49,     0,    50,     0,
       0,     0,     0,     0,    51,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    42,    43,    44,    45,    52,
      53,    54,    55,    56,    47,    48,     0,    49,     0,    50,
       0,     0,   265,     0,     0,    51,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    42,    43,    44,    45,
      52,    53,    54,    55,    56,    47,    48,     0,    49,     0,
      50,   253,     0,     0,     0,     0,    51,     0,   145,   146,
     147,     0,   148,   149,   150,   151,     0,     0,     0,     0,
       0,    52,    53,    54,    55,    56,   152,   153,   154,   155,
     156,     0,     0,     0,   157,   158,   159,   145,   146,   147,
       0,   148,   149,   150,   151,     0,   204,     0,     0,     0,
       0,     0,     0,     0,     0,   152,   153,   154,   155,   156,
       0,     0,     0,   157,   158,   159,   145,   146,   147,     0,
     148,   149,   150,   151,     0,   283,     0,     0,     0,     0,
       0,     0,     0,     0,   152,   153,   154,   155,   156,     0,
       0,     0,   157,   158,   159,   145,   146,   147,     0,   148,
     149,   150,   151,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   152,   153,   154,   155,   156,     0,     0,
       0,   157,   158,   159,   146,   147,     0,   148,   149,   150,
     151,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   152,   153,   154,   155,   156,     0,     0,     0,   157,
     158,   159,   146,     0,     0,   148,   149,   150,   151,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   152,
     153,   154,   155,   156,     0,     0,     0,   157,   158,   159,
     148,   149,   150,   151,     0,     0,     0,     0,     0,     0,
       0,   148,   149,   150,   152,   153,   154,   155,   156,     0,
       0,     0,   157,   158,   159,   152,   153,   154,   155,   156,
     148,   149,   150,   157,   158,   159,     0,     0,     0,     0,
       0,     0,     0,     0,   152,   153,   154,   155,   156,     0,
       0,     0,     0,   158,   159
  };

  const short int
  casmi_parser::yycheck_[] =
  {
      34,    34,    34,   165,    52,   195,    89,     9,    52,     9,
      50,     9,     3,   144,    53,    12,    13,    14,    53,    16,
      17,    18,    19,    20,    21,    34,    23,    24,    93,    26,
      27,    79,    67,    30,    51,    79,    79,    34,    35,    36,
      79,    38,    59,    32,    33,    53,    80,    81,    52,    51,
      52,    51,    29,    51,     0,    89,    49,    50,   169,    56,
      49,    50,    96,    97,    98,    69,    79,    49,    50,    46,
     260,    79,    49,    51,    31,    58,    73,    64,    65,    51,
      68,    59,    79,    76,    48,   196,    75,    76,    77,    78,
      79,    79,   175,   176,    76,    49,    50,    79,    51,    79,
      64,    65,    66,    22,    79,    82,    83,    84,    61,   192,
     193,    51,    52,    79,    91,    92,   278,   248,    95,    59,
      51,    75,    76,    77,   189,    44,    45,    46,    59,    48,
      49,    50,    51,    76,    77,   169,   169,   169,   203,    48,
      79,   175,   176,    62,    63,    64,    65,    66,    59,    79,
     261,    70,    71,    72,    79,    64,    65,    57,   192,   193,
     169,    61,   196,   196,   196,   205,   249,   124,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   158,   159,   160,   315,    81,   251,   196,   299,   166,
      51,    79,    56,    51,    53,    48,    49,    50,    61,    11,
      61,    97,    98,    61,   161,   162,   183,    52,   165,    62,
     250,    64,    65,    66,   325,   249,   250,   194,    52,   253,
     254,    75,    76,    77,    75,    76,    77,   261,   261,   261,
     207,   314,    79,    79,   317,   318,   319,   320,   321,   304,
     305,    48,    49,    50,   201,    59,    48,   330,    50,    53,
     290,   228,   261,    61,    52,    51,   290,    64,    65,    66,
     343,    32,    64,    65,    66,   299,   299,   299,    79,   246,
      79,    53,   229,    79,    79,    69,    79,    68,    49,    50,
     314,    64,    79,   317,   318,   319,   320,   321,   245,    56,
     299,   325,   325,   325,    67,   272,   330,    48,    49,    50,
      55,    61,    79,   280,    75,    76,    77,    78,    79,   343,
      57,    62,    63,    64,    65,    66,   325,    53,   275,    22,
      71,    12,    52,    14,    15,    16,    17,    18,    19,    20,
      21,   308,    23,    24,    49,    26,    27,    39,    64,    30,
      53,    51,    76,    34,    35,    36,    53,    38,    76,    61,
      68,    68,    79,    51,   331,    12,    55,    14,    51,    16,
      17,    18,    19,    20,    21,    56,    23,    24,    52,    26,
      27,    53,    59,    30,    29,    53,    59,    34,    35,    36,
      59,    38,    73,     4,     5,     6,     7,     8,    79,    10,
      59,    53,    12,    35,   164,   275,   262,   198,   304,    56,
      57,   170,   202,    12,   189,    14,   290,    16,    17,    18,
      19,    20,    21,    -1,    23,    24,    73,    26,    27,    -1,
      -1,    30,    79,    -1,    -1,    34,    35,    36,    12,    38,
      14,    -1,    16,    17,    18,    19,    20,    21,    -1,    23,
      24,    -1,    26,    27,    -1,    -1,    30,    56,    -1,    -1,
      34,    35,    36,    -1,    38,    -1,    22,    -1,    -1,    48,
      49,    50,    -1,    -1,    73,    74,    -1,    -1,    -1,    -1,
      79,    -1,    56,    62,    63,    64,    65,    66,    44,    45,
      46,    -1,    48,    49,    50,    51,    -1,    -1,    25,    73,
      -1,    -1,    -1,    -1,    -1,    79,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    71,    72,    44,    45,    46,
      -1,    48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    71,    72,    44,    45,    46,    -1,
      48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    31,    -1,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    44,    45,    46,    -1,    48,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    70,    71,    72,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    49,    50,    -1,    52,    -1,    54,    55,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    49,    50,    -1,    52,    53,    54,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    75,
      76,    77,    78,    79,    40,    41,    42,    43,    -1,    -1,
      -1,    47,    -1,    49,    50,    -1,    52,    -1,    54,    -1,
      -1,    -1,    -1,    -1,    60,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,    75,
      76,    77,    78,    79,    49,    50,    -1,    52,    -1,    54,
      -1,    -1,    57,    -1,    -1,    60,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    40,    41,    42,    43,
      75,    76,    77,    78,    79,    49,    50,    -1,    52,    -1,
      54,    37,    -1,    -1,    -1,    -1,    60,    -1,    44,    45,
      46,    -1,    48,    49,    50,    51,    -1,    -1,    -1,    -1,
      -1,    75,    76,    77,    78,    79,    62,    63,    64,    65,
      66,    -1,    -1,    -1,    70,    71,    72,    44,    45,    46,
      -1,    48,    49,    50,    51,    -1,    53,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,
      -1,    -1,    -1,    70,    71,    72,    44,    45,    46,    -1,
      48,    49,    50,    51,    -1,    53,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    44,    45,    46,    -1,    48,
      49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,    -1,
      -1,    70,    71,    72,    45,    46,    -1,    48,    49,    50,
      51,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    62,    63,    64,    65,    66,    -1,    -1,    -1,    70,
      71,    72,    45,    -1,    -1,    48,    49,    50,    51,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    62,
      63,    64,    65,    66,    -1,    -1,    -1,    70,    71,    72,
      48,    49,    50,    51,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    48,    49,    50,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    70,    71,    72,    62,    63,    64,    65,    66,
      48,    49,    50,    70,    71,    72,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    62,    63,    64,    65,    66,    -1,
      -1,    -1,    -1,    71,    72
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
     105,   106,   107,   108,   109,   110,   113,   114,   115,    53,
      79,    93,    94,    95,    79,    97,    56,    52,   118,   119,
      12,    14,    16,    17,    18,    19,    20,    21,    23,    24,
      26,    27,    30,    34,    35,    36,    38,    56,    73,    79,
     115,   116,   120,   122,   123,   124,   125,   126,   128,   129,
     130,   137,   138,   139,   141,   142,   145,   146,   147,   148,
      53,    94,    53,    61,    68,    96,    97,    11,    99,    79,
     113,    75,    76,    77,    75,    76,    77,   113,    55,   104,
     111,   112,   113,    79,    52,    44,    45,    46,    48,    49,
      50,    51,    62,    63,    64,    65,    66,    70,    71,    72,
      51,    59,    59,    53,    61,    52,    51,    90,    90,    51,
      61,   120,   121,   138,   139,   140,   140,   113,   113,   113,
      79,    79,   121,    52,    79,   113,   113,   102,   127,    79,
     113,   115,   140,   140,    69,     9,    51,    53,    79,    79,
      97,    68,    64,    56,    53,    67,    55,    61,    53,   111,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,    97,    97,    51,    59,
      93,    49,    50,    97,    98,   105,   113,    57,    53,   116,
     119,    13,   121,    15,    51,    59,    22,   113,    52,    28,
      31,    49,   127,    37,    39,    57,    74,   113,   118,   116,
       9,    51,    92,    97,    96,    57,   100,   101,   102,   104,
     113,    53,    51,   113,    97,    61,    53,    53,    67,    68,
     143,    97,   113,    53,   111,   121,    32,    78,   104,   115,
     131,   132,   133,   134,   135,   136,   102,   115,   115,    51,
     118,   116,    99,    57,    61,    68,    55,   113,    51,    98,
     105,    79,   113,    51,    25,    52,    53,    29,    59,    59,
      59,    59,    33,   132,   116,    51,   101,   102,   113,    53,
      22,   144,   121,   111,   121,   121,   121,   121,   121,   116,
     121,   113,    53,    22,   121
  };

  const unsigned char
  casmi_parser::yyr1_[] =
  {
       0,    80,    81,    82,    83,    83,    84,    84,    84,    84,
      84,    84,    85,    86,    87,    88,    88,    88,    88,    88,
      88,    89,    89,    89,    89,    90,    90,    91,    91,    92,
      92,    93,    93,    94,    94,    95,    95,    96,    96,    96,
      97,    97,    97,    97,    98,    98,    98,    99,    99,   100,
     100,   100,   101,   101,   102,   102,   102,   103,   103,   103,
     103,   103,   103,   103,   103,   103,   104,   104,   104,   105,
     105,   105,   106,   106,   106,   107,   107,   107,   108,   109,
     110,   110,   111,   111,   112,   112,   113,   113,   113,   113,
     113,   113,   113,   113,   113,   113,   113,   113,   113,   113,
     113,   113,   113,   114,   115,   115,   115,   116,   116,   116,
     117,   117,   117,   117,   117,   117,   118,   118,   119,   120,
     120,   120,   120,   120,   120,   120,   120,   120,   120,   120,
     120,   120,   120,   120,   120,   120,   121,   121,   121,   122,
     123,   124,   124,   125,   126,   127,   127,   128,   129,   130,
     131,   131,   132,   132,   132,   132,   133,   134,   135,   136,
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
       2,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     1,     2,     2,     1,     2,     2,     1,     2,     5,
       3,     2,     1,     2,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     2,     1,     3,     1,     3,     4,     1,     1,     1,
       4,     6,     7,     6,     8,     9,     3,     1,     5,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     2,
       2,     2,     1,     1,     3,     3,     1,     2,     3,     5,
       2,     1,     1,     1,     1,     1,     3,     3,     3,     3,
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
  "\"rational\"", "\"string\"", "\"identifier\"", "$accept",
  "SPECIFICATION", "HEADER", "BODY_ELEMENTS", "BODY_ELEMENT",
  "INIT_SYNTAX", "OPTION_SYNTAX", "ENUM_SYNTAX", "DERIVED_SYNTAX",
  "FUNCTION_DEFINITION", "IDENTIFIER_LIST", "IDENTIFIER_LIST_NO_COMMA",
  "FUNCTION_SIGNATURE", "PARAM", "PARAM_LIST", "PARAM_LIST_NO_COMMA",
  "TYPE_IDENTIFIER_STARLIST", "TYPE_SYNTAX", "TYPE_SYNTAX_LIST",
  "INITIALIZERS", "INITIALIZER_LIST", "INITIALIZER", "ATOM", "VALUE",
  "NUMBER", "INTEGER_NUMBER", "FLOATING_NUMBER", "RATIONAL_NUMBER",
  "RULEREF", "NUMBER_RANGE", "LISTCONST", "EXPRESSION_LIST",
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
       0,   333,   333,   341,   348,   353,   362,   366,   370,   390,
     407,   411,   430,   438,   443,   477,   482,   486,   490,   494,
     498,   506,   511,   516,   520,   527,   531,   539,   544,   553,
     559,   567,   573,   584,   588,   596,   601,   609,   614,   619,
     627,   650,   663,   685,   703,   708,   712,   720,   724,   732,
     736,   740,   749,   753,   761,   765,   769,   777,   781,   785,
     789,   793,   797,   801,   805,   809,   817,   821,   825,   833,
     837,   841,   849,   853,   857,   865,   869,   874,   882,   890,
     906,   910,   918,   922,   930,   935,   944,   948,   952,   956,
     960,   964,   968,   972,   976,   980,   984,   988,   992,   996,
    1000,  1004,  1008,  1016,  1024,  1028,  1032,  1046,  1050,  1054,
    1064,  1068,  1072,  1076,  1081,  1086,  1095,  1100,  1109,  1117,
    1121,  1125,  1129,  1133,  1137,  1141,  1145,  1149,  1153,  1157,
    1161,  1165,  1169,  1173,  1177,  1181,  1201,  1205,  1209,  1217,
    1225,  1233,  1237,  1253,  1261,  1269,  1274,  1282,  1290,  1311,
    1319,  1324,  1333,  1337,  1341,  1345,  1353,  1361,  1369,  1377,
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
#line 3576 "GrammarParser.cpp" // lalr1.cc:1167
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
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
