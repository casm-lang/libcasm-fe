// A Bison parser, made by GNU Bison 3.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018 Free Software Foundation, Inc.

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


/**
 ** \file GrammarParser.tab.h
 ** Define the libcasm_fe::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

#ifndef YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
# define YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
// //                    "%code requires" blocks.
#line 63 "../../obj/src/GrammarParser.yy" // lalr1.cc:403

    namespace libcasm_fe
    {
        class Lexer;
        class Logger;
    }

    #include <libcasm-fe/Specification>
    #include <libcasm-fe/ast/Definition>
    #include <libcasm-fe/ast/Expression>
    #include <libcasm-fe/ast/Rule>
    #include <libcasm-fe/ast/Token>

    #include <libstdhl/SourceLocation>

    using namespace libcasm_fe;
    using namespace Ast;

    #define YY_NULLPTR nullptr

#line 69 "GrammarParser.tab.h" // lalr1.cc:403

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

// Support move semantics when possible.
#if defined __cplusplus && 201103L <= __cplusplus
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:403
namespace libcasm_fe {
#line 163 "GrammarParser.tab.h" // lalr1.cc:403

  /// A stack with random access from its top.
  template <typename T, typename S = std::vector<T> >
  class stack
  {
  public:
    // Hide our reversed order.
    typedef typename S::reverse_iterator iterator;
    typedef typename S::const_reverse_iterator const_iterator;
    typedef typename S::size_type size_type;

    stack (size_type n = 200)
      : seq_ (n)
    {}

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    T&
    operator[] (size_type i)
    {
      return seq_[size () - 1 - i];
    }

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    T&
    operator[] (int i)
    {
      return operator[] (size_type (i));
    }

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    const T&
    operator[] (size_type i) const
    {
      return seq_[size () - 1 - i];
    }

    /// Random access.
    ///
    /// Index 0 returns the topmost element.
    const T&
    operator[] (int i) const
    {
      return operator[] (size_type (i));
    }

    /// Steal the contents of \a t.
    ///
    /// Close to move-semantics.
    void
    push (YY_MOVE_REF (T) t)
    {
      seq_.push_back (T ());
      operator[](0).move (t);
    }

    void
    pop (int n = 1)
    {
      for (; 0 < n; --n)
        seq_.pop_back ();
    }

    void
    clear ()
    {
      seq_.clear ();
    }

    size_type
    size () const
    {
      return seq_.size ();
    }

    const_iterator
    begin () const
    {
      return seq_.rbegin ();
    }

    const_iterator
    end () const
    {
      return seq_.rend ();
    }

  private:
    stack (const stack&);
    stack& operator= (const stack&);
    /// The wrapped container.
    S seq_;
  };

  /// Present a slice of the top of a stack.
  template <typename T, typename S = stack<T> >
  class slice
  {
  public:
    slice (const S& stack, int range)
      : stack_ (stack)
      , range_ (range)
    {}

    const T&
    operator[] (int i) const
    {
      return stack_[range_ - i];
    }

  private:
    const S& stack_;
    int range_;
  };



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

# if defined __cplusplus && 201103L <= __cplusplus
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename U>
    T&
    emplace (U&& u)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u));
    }
# else
    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
# if defined __cplusplus && 201103L <= __cplusplus
      emplace<T> (std::move (other.as<T> ()));
# else
      emplace<T> ();
      swap<T> (other);
# endif
      other.destroy<T> ();
    }

# if defined __cplusplus && 201103L <= __cplusplus
    /// Move the content of \a other to this.
    template <typename T>
    void
    move (self_type&& other)
    {
      emplace<T> (std::move (other.as<T> ()));
      other.destroy<T> ();
    }
#endif

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      emplace<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator= (const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // "CASM"
      // "init"
      // "derived"
      // "enumeration"
      // "rule"
      // "using"
      // "invariant"
      // "function"
      // "initially"
      // "defined"
      // "seq"
      // "endseq"
      // "par"
      // "endpar"
      // "skip"
      // "let"
      // "in"
      // "forall"
      // "choose"
      // "iterate"
      // "do"
      // "if"
      // "then"
      // "else"
      // "case"
      // "of"
      // "default"
      // "holds"
      // "exists"
      // "with"
      // "as"
      // "while"
      // "undef"
      // "false"
      // "true"
      // "and"
      // "or"
      // "xor"
      // "implies"
      // "not"
      // "+"
      // "-"
      // "="
      // "("
      // ")"
      // "["
      // "]"
      // "{"
      // "}"
      // ":"
      // "::"
      // "_"
      // "|"
      // "@"
      // ","
      // "<"
      // ">"
      // "*"
      // "/"
      // "%"
      // "^"
      // "'"
      // ".."
      // "."
      // "->"
      // "=>"
      // ":="
      // "!="
      // "<="
      // ">="
      // "{|"
      // "|}"
      char dummy1[sizeof (Ast::Token::Ptr)];

      // Attribute
      char dummy2[sizeof (Attribute::Ptr)];

      // Attributes
      char dummy3[sizeof (Attributes::Ptr)];

      // BasicAttribute
      char dummy4[sizeof (BasicAttribute::Ptr)];

      // BasicType
      char dummy5[sizeof (BasicType::Ptr)];

      // BlockRule
      char dummy6[sizeof (BlockRule::Ptr)];

      // CallExpression
      char dummy7[sizeof (CallExpression::Ptr)];

      // CallRule
      char dummy8[sizeof (CallRule::Ptr)];

      // CardinalityExpression
      char dummy9[sizeof (CardinalityExpression::Ptr)];

      // CaseLabel
      char dummy10[sizeof (Case::Ptr)];

      // CaseRule
      char dummy11[sizeof (CaseRule::Ptr)];

      // CaseLabels
      char dummy12[sizeof (Cases::Ptr)];

      // ChooseExpression
      char dummy13[sizeof (ChooseExpression::Ptr)];

      // ChooseRule
      char dummy14[sizeof (ChooseRule::Ptr)];

      // ConditionalExpression
      char dummy15[sizeof (ConditionalExpression::Ptr)];

      // ConditionalRule
      char dummy16[sizeof (ConditionalRule::Ptr)];

      // MaybeDefined
      char dummy17[sizeof (Defined::Ptr)];

      // AttributedDefinition
      // Definition
      char dummy18[sizeof (Definition::Ptr)];

      // Definitions
      char dummy19[sizeof (Definitions::Ptr)];

      // DerivedDefinition
      char dummy20[sizeof (DerivedDefinition::Ptr)];

      // DirectCallExpression
      char dummy21[sizeof (DirectCallExpression::Ptr)];

      // EnumerationDefinition
      char dummy22[sizeof (EnumerationDefinition::Ptr)];

      // EnumeratorDefinition
      char dummy23[sizeof (EnumeratorDefinition::Ptr)];

      // Enumerators
      char dummy24[sizeof (Enumerators::Ptr)];

      // ExistentialQuantifierExpression
      char dummy25[sizeof (ExistentialQuantifierExpression::Ptr)];

      // Term
      // SimpleOrClaspedTerm
      // OperatorExpression
      char dummy26[sizeof (Expression::Ptr)];

      // ExpressionAttribute
      char dummy27[sizeof (ExpressionAttribute::Ptr)];

      // Terms
      char dummy28[sizeof (Expressions::Ptr)];

      // FixedSizedType
      char dummy29[sizeof (FixedSizedType::Ptr)];

      // ForallRule
      char dummy30[sizeof (ForallRule::Ptr)];

      // FunctionDefinition
      char dummy31[sizeof (FunctionDefinition::Ptr)];

      // Header
      char dummy32[sizeof (HeaderDefinition::Ptr)];

      // "identifier"
      // Identifier
      char dummy33[sizeof (Identifier::Ptr)];

      // IdentifierPath
      char dummy34[sizeof (IdentifierPath::Ptr)];

      // IndirectCallExpression
      char dummy35[sizeof (IndirectCallExpression::Ptr)];

      // InitDefinition
      char dummy36[sizeof (InitDefinition::Ptr)];

      // Initializer
      char dummy37[sizeof (Initializer::Ptr)];

      // Initializers
      char dummy38[sizeof (Initializers::Ptr)];

      // MaybeInitially
      char dummy39[sizeof (Initially::Ptr)];

      // InvariantDefinition
      char dummy40[sizeof (InvariantDefinition::Ptr)];

      // IterateRule
      char dummy41[sizeof (IterateRule::Ptr)];

      // LetExpression
      char dummy42[sizeof (LetExpression::Ptr)];

      // LetRule
      char dummy43[sizeof (LetRule::Ptr)];

      // ListLiteral
      char dummy44[sizeof (ListLiteral::Ptr)];

      // Literal
      char dummy45[sizeof (Literal::Ptr)];

      // LiteralCallExpression
      char dummy46[sizeof (LiteralCallExpression::Ptr)];

      // MethodCallExpression
      char dummy47[sizeof (MethodCallExpression::Ptr)];

      // Assignment
      char dummy48[sizeof (NamedExpression::Ptr)];

      // Assignments
      char dummy49[sizeof (NamedExpressions::Ptr)];

      // RangeLiteral
      char dummy50[sizeof (RangeLiteral::Ptr)];

      // RecordLiteral
      char dummy51[sizeof (RecordLiteral::Ptr)];

      // RecordType
      char dummy52[sizeof (RecordType::Ptr)];

      // ReferenceLiteral
      char dummy53[sizeof (ReferenceLiteral::Ptr)];

      // RelationType
      char dummy54[sizeof (RelationType::Ptr)];

      // Rule
      char dummy55[sizeof (Rule::Ptr)];

      // RuleDefinition
      char dummy56[sizeof (RuleDefinition::Ptr)];

      // Rules
      char dummy57[sizeof (Rules::Ptr)];

      // SequenceRule
      char dummy58[sizeof (SequenceRule::Ptr)];

      // SkipRule
      char dummy59[sizeof (SkipRule::Ptr)];

      // Specification
      char dummy60[sizeof (Specification::Ptr)];

      // TemplateType
      char dummy61[sizeof (TemplateType::Ptr)];

      // TupleLiteral
      char dummy62[sizeof (TupleLiteral::Ptr)];

      // TupleType
      char dummy63[sizeof (TupleType::Ptr)];

      // TypeCastingExpression
      char dummy64[sizeof (TypeCastingExpression::Ptr)];

      // Types
      // FunctionParameters
      // MaybeFunctionParameters
      char dummy65[sizeof (Types::Ptr)];

      // UndefinedLiteral
      char dummy66[sizeof (UndefLiteral::Ptr)];

      // UniversalQuantifierExpression
      char dummy67[sizeof (UniversalQuantifierExpression::Ptr)];

      // UpdateRule
      char dummy68[sizeof (UpdateRule::Ptr)];

      // UsingDefinition
      char dummy69[sizeof (UsingDefinition::Ptr)];

      // "binary"
      // "hexadecimal"
      // "integer"
      // "rational"
      // "decimal"
      // "string"
      // BooleanLiteral
      // IntegerLiteral
      // RationalLiteral
      // DecimalLiteral
      // BinaryLiteral
      // StringLiteral
      char dummy70[sizeof (ValueLiteral::Ptr)];

      // VariableBinding
      char dummy71[sizeof (VariableBinding::Ptr)];

      // VariableBindings
      char dummy72[sizeof (VariableBindings::Ptr)];

      // Variable
      // TypedVariable
      // AttributedVariable
      // TypedAttributedVariable
      char dummy73[sizeof (VariableDefinition::Ptr)];

      // Parameters
      // AttributedVariables
      // TypedVariables
      char dummy74[sizeof (VariableDefinitions::Ptr)];

      // WhileRule
      char dummy75[sizeof (WhileRule::Ptr)];

      // Type
      char dummy76[sizeof (libcasm_fe::Ast::Type::Ptr)];
};

    /// Symbol semantic values.
    typedef variant<sizeof (union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef libstdhl::SourceLocation location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        END = 0,
        CASM = 258,
        INIT = 259,
        DERIVED = 260,
        ENUMERATION = 261,
        RULE = 262,
        USING = 263,
        INVARIANT = 264,
        FUNCTION = 265,
        INITIALLY = 266,
        DEFINED = 267,
        SEQ = 268,
        ENDSEQ = 269,
        PAR = 270,
        ENDPAR = 271,
        SKIP = 272,
        LET = 273,
        IN = 274,
        FORALL = 275,
        CHOOSE = 276,
        ITERATE = 277,
        DO = 278,
        IF = 279,
        THEN = 280,
        ELSE = 281,
        CASE = 282,
        OF = 283,
        DEFAULT = 284,
        HOLDS = 285,
        EXISTS = 286,
        WITH = 287,
        AS = 288,
        WHILE = 289,
        UNDEF = 290,
        FALSE = 291,
        TRUE = 292,
        AND = 293,
        OR = 294,
        XOR = 295,
        IMPLIES = 296,
        NOT = 297,
        PLUS = 298,
        MINUS = 299,
        EQUAL = 300,
        LPAREN = 301,
        RPAREN = 302,
        LSQPAREN = 303,
        RSQPAREN = 304,
        LCURPAREN = 305,
        RCURPAREN = 306,
        COLON = 307,
        DOUBLECOLON = 308,
        UNDERLINE = 309,
        VERTICAL_BAR = 310,
        AT = 311,
        COMMA = 312,
        LESSER = 313,
        GREATER = 314,
        ASTERIX = 315,
        SLASH = 316,
        PERCENT = 317,
        CARET = 318,
        MARK = 319,
        DOTDOT = 320,
        DOT = 321,
        MAPS = 322,
        ARROW = 323,
        UPDATE = 324,
        NEQUAL = 325,
        LESSEQ = 326,
        GREATEREQ = 327,
        SEQ_BRACKET = 328,
        ENDSEQ_BRACKET = 329,
        BINARY = 330,
        HEXADECIMAL = 331,
        INTEGER = 332,
        RATIONAL = 333,
        DECIMAL = 334,
        STRING = 335,
        IDENTIFIER = 336,
        BASIC_TYPE = 337,
        CALL = 338,
        UPLUS = 339,
        UMINUS = 340,
        CALL_WITHOUT_ARGS = 341
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Move or copy constructor.
      basic_symbol (YY_RVREF (basic_symbol) other);


      /// Constructor for valueless symbols, and symbols from each type.
      basic_symbol (typename Base::kind_type t, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Ast::Token::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Attribute::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Attributes::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (BasicAttribute::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (BasicType::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (BlockRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (CallExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (CallRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (CardinalityExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Case::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (CaseRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Cases::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ChooseExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ChooseRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ConditionalExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ConditionalRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Defined::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Definition::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Definitions::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (DerivedDefinition::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (DirectCallExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (EnumerationDefinition::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (EnumeratorDefinition::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Enumerators::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ExistentialQuantifierExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Expression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ExpressionAttribute::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Expressions::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (FixedSizedType::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ForallRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (FunctionDefinition::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (HeaderDefinition::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Identifier::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (IdentifierPath::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (IndirectCallExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (InitDefinition::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Initializer::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Initializers::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Initially::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (InvariantDefinition::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (IterateRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (LetExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (LetRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ListLiteral::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Literal::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (LiteralCallExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (MethodCallExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (NamedExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (NamedExpressions::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (RangeLiteral::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (RecordLiteral::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (RecordType::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ReferenceLiteral::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (RelationType::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Rule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (RuleDefinition::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Rules::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (SequenceRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (SkipRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Specification::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (TemplateType::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (TupleLiteral::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (TupleType::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (TypeCastingExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (Types::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (UndefLiteral::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (UniversalQuantifierExpression::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (UpdateRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (UsingDefinition::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (ValueLiteral::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (VariableBinding::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (VariableBindings::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (VariableDefinition::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (VariableDefinitions::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (WhileRule::Ptr) v, YY_RVREF (location_type) l);
      basic_symbol (typename Base::kind_type t, YY_RVREF (libcasm_fe::Ast::Type::Ptr) v, YY_RVREF (location_type) l);


      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if defined __cplusplus && __cplusplus < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    /// Build a parser object.
    Parser (Logger& m_log_yyarg, Lexer& m_lexer_yyarg, Specification& m_specification_yyarg);
    virtual ~Parser ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    // Symbol constructors declarations.
    static
    symbol_type
    make_END (YY_COPY (location_type) l);

    static
    symbol_type
    make_CASM (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_INIT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_DERIVED (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_ENUMERATION (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_RULE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_USING (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_INVARIANT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_FUNCTION (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_INITIALLY (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_DEFINED (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_SEQ (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_ENDSEQ (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_PAR (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_ENDPAR (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_SKIP (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_LET (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_IN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_FORALL (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_CHOOSE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_ITERATE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_DO (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_IF (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_THEN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_ELSE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_CASE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_OF (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_DEFAULT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_HOLDS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_EXISTS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_WITH (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_AS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_WHILE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_UNDEF (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_FALSE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_TRUE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_AND (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_OR (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_XOR (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_IMPLIES (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_NOT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_PLUS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_MINUS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_EQUAL (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_LPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_RPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_LSQPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_RSQPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_LCURPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_RCURPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_COLON (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_DOUBLECOLON (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_UNDERLINE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_VERTICAL_BAR (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_AT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_COMMA (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_LESSER (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_GREATER (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_ASTERIX (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_SLASH (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_PERCENT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_CARET (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_MARK (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_DOTDOT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_DOT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_MAPS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_ARROW (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_UPDATE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_NEQUAL (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_LESSEQ (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_GREATEREQ (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_SEQ_BRACKET (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_ENDSEQ_BRACKET (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_BINARY (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_HEXADECIMAL (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_INTEGER (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_RATIONAL (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_DECIMAL (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_STRING (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_IDENTIFIER (YY_COPY (Identifier::Ptr) v, YY_COPY (location_type) l);

    static
    symbol_type
    make_BASIC_TYPE (YY_COPY (location_type) l);

    static
    symbol_type
    make_CALL (YY_COPY (location_type) l);

    static
    symbol_type
    make_UPLUS (YY_COPY (location_type) l);

    static
    symbol_type
    make_UMINUS (YY_COPY (location_type) l);

    static
    symbol_type
    make_CALL_WITHOUT_ARGS (YY_COPY (location_type) l);



  private:
    /// This class is not copyable.
    Parser (const Parser&);
    Parser& operator= (const Parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const short yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short yytable_[];

  static const short yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned char yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned char yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if defined __cplusplus && __cplusplus < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);
#endif
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 2703,     ///< Last index in yytable_.
      yynnts_ = 91,  ///< Number of nonterminal symbols.
      yyfinal_ = 13, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 87  ///< Number of tokens.
    };


    // User arguments.
    Logger& m_log;
    Lexer& m_lexer;
    Specification& m_specification;
  };

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86
    };
    const unsigned user_token_number_max_ = 341;
    const token_number_type undef_token_ = 2;

    if (static_cast<int> (t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
    , location ()
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (YY_RVREF (basic_symbol) other)
    : Base (YY_MOVE (other))
    , value ()
    , location (YY_MOVE (other.location))
  {
    switch (other.type_get ())
    {
      case 3: // "CASM"
      case 4: // "init"
      case 5: // "derived"
      case 6: // "enumeration"
      case 7: // "rule"
      case 8: // "using"
      case 9: // "invariant"
      case 10: // "function"
      case 11: // "initially"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "in"
      case 20: // "forall"
      case 21: // "choose"
      case 22: // "iterate"
      case 23: // "do"
      case 24: // "if"
      case 25: // "then"
      case 26: // "else"
      case 27: // "case"
      case 28: // "of"
      case 29: // "default"
      case 30: // "holds"
      case 31: // "exists"
      case 32: // "with"
      case 33: // "as"
      case 34: // "while"
      case 35: // "undef"
      case 36: // "false"
      case 37: // "true"
      case 38: // "and"
      case 39: // "or"
      case 40: // "xor"
      case 41: // "implies"
      case 42: // "not"
      case 43: // "+"
      case 44: // "-"
      case 45: // "="
      case 46: // "("
      case 47: // ")"
      case 48: // "["
      case 49: // "]"
      case 50: // "{"
      case 51: // "}"
      case 52: // ":"
      case 53: // "::"
      case 54: // "_"
      case 55: // "|"
      case 56: // "@"
      case 57: // ","
      case 58: // "<"
      case 59: // ">"
      case 60: // "*"
      case 61: // "/"
      case 62: // "%"
      case 63: // "^"
      case 64: // "'"
      case 65: // ".."
      case 66: // "."
      case 67: // "->"
      case 68: // "=>"
      case 69: // ":="
      case 70: // "!="
      case 71: // "<="
      case 72: // ">="
      case 73: // "{|"
      case 74: // "|}"
        value.YY_MOVE_OR_COPY< Ast::Token::Ptr > (YY_MOVE (other.value));
        break;

      case 175: // Attribute
        value.YY_MOVE_OR_COPY< Attribute::Ptr > (YY_MOVE (other.value));
        break;

      case 174: // Attributes
        value.YY_MOVE_OR_COPY< Attributes::Ptr > (YY_MOVE (other.value));
        break;

      case 176: // BasicAttribute
        value.YY_MOVE_OR_COPY< BasicAttribute::Ptr > (YY_MOVE (other.value));
        break;

      case 151: // BasicType
        value.YY_MOVE_OR_COPY< BasicType::Ptr > (YY_MOVE (other.value));
        break;

      case 113: // BlockRule
        value.YY_MOVE_OR_COPY< BlockRule::Ptr > (YY_MOVE (other.value));
        break;

      case 122: // CallExpression
        value.YY_MOVE_OR_COPY< CallExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 116: // CallRule
        value.YY_MOVE_OR_COPY< CallRule::Ptr > (YY_MOVE (other.value));
        break;

      case 133: // CardinalityExpression
        value.YY_MOVE_OR_COPY< CardinalityExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 108: // CaseLabel
        value.YY_MOVE_OR_COPY< Case::Ptr > (YY_MOVE (other.value));
        break;

      case 106: // CaseRule
        value.YY_MOVE_OR_COPY< CaseRule::Ptr > (YY_MOVE (other.value));
        break;

      case 107: // CaseLabels
        value.YY_MOVE_OR_COPY< Cases::Ptr > (YY_MOVE (other.value));
        break;

      case 130: // ChooseExpression
        value.YY_MOVE_OR_COPY< ChooseExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 111: // ChooseRule
        value.YY_MOVE_OR_COPY< ChooseRule::Ptr > (YY_MOVE (other.value));
        break;

      case 129: // ConditionalExpression
        value.YY_MOVE_OR_COPY< ConditionalExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 105: // ConditionalRule
        value.YY_MOVE_OR_COPY< ConditionalRule::Ptr > (YY_MOVE (other.value));
        break;

      case 160: // MaybeDefined
        value.YY_MOVE_OR_COPY< Defined::Ptr > (YY_MOVE (other.value));
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        value.YY_MOVE_OR_COPY< Definition::Ptr > (YY_MOVE (other.value));
        break;

      case 90: // Definitions
        value.YY_MOVE_OR_COPY< Definitions::Ptr > (YY_MOVE (other.value));
        break;

      case 95: // DerivedDefinition
        value.YY_MOVE_OR_COPY< DerivedDefinition::Ptr > (YY_MOVE (other.value));
        break;

      case 123: // DirectCallExpression
        value.YY_MOVE_OR_COPY< DirectCallExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 94: // EnumerationDefinition
        value.YY_MOVE_OR_COPY< EnumerationDefinition::Ptr > (YY_MOVE (other.value));
        break;

      case 98: // EnumeratorDefinition
        value.YY_MOVE_OR_COPY< EnumeratorDefinition::Ptr > (YY_MOVE (other.value));
        break;

      case 99: // Enumerators
        value.YY_MOVE_OR_COPY< Enumerators::Ptr > (YY_MOVE (other.value));
        break;

      case 132: // ExistentialQuantifierExpression
        value.YY_MOVE_OR_COPY< ExistentialQuantifierExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
        value.YY_MOVE_OR_COPY< Expression::Ptr > (YY_MOVE (other.value));
        break;

      case 177: // ExpressionAttribute
        value.YY_MOVE_OR_COPY< ExpressionAttribute::Ptr > (YY_MOVE (other.value));
        break;

      case 118: // Terms
        value.YY_MOVE_OR_COPY< Expressions::Ptr > (YY_MOVE (other.value));
        break;

      case 156: // FixedSizedType
        value.YY_MOVE_OR_COPY< FixedSizedType::Ptr > (YY_MOVE (other.value));
        break;

      case 110: // ForallRule
        value.YY_MOVE_OR_COPY< ForallRule::Ptr > (YY_MOVE (other.value));
        break;

      case 97: // FunctionDefinition
        value.YY_MOVE_OR_COPY< FunctionDefinition::Ptr > (YY_MOVE (other.value));
        break;

      case 89: // Header
        value.YY_MOVE_OR_COPY< HeaderDefinition::Ptr > (YY_MOVE (other.value));
        break;

      case 81: // "identifier"
      case 164: // Identifier
        value.YY_MOVE_OR_COPY< Identifier::Ptr > (YY_MOVE (other.value));
        break;

      case 165: // IdentifierPath
        value.YY_MOVE_OR_COPY< IdentifierPath::Ptr > (YY_MOVE (other.value));
        break;

      case 126: // IndirectCallExpression
        value.YY_MOVE_OR_COPY< IndirectCallExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 93: // InitDefinition
        value.YY_MOVE_OR_COPY< InitDefinition::Ptr > (YY_MOVE (other.value));
        break;

      case 163: // Initializer
        value.YY_MOVE_OR_COPY< Initializer::Ptr > (YY_MOVE (other.value));
        break;

      case 162: // Initializers
        value.YY_MOVE_OR_COPY< Initializers::Ptr > (YY_MOVE (other.value));
        break;

      case 161: // MaybeInitially
        value.YY_MOVE_OR_COPY< Initially::Ptr > (YY_MOVE (other.value));
        break;

      case 101: // InvariantDefinition
        value.YY_MOVE_OR_COPY< InvariantDefinition::Ptr > (YY_MOVE (other.value));
        break;

      case 112: // IterateRule
        value.YY_MOVE_OR_COPY< IterateRule::Ptr > (YY_MOVE (other.value));
        break;

      case 128: // LetExpression
        value.YY_MOVE_OR_COPY< LetExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 109: // LetRule
        value.YY_MOVE_OR_COPY< LetRule::Ptr > (YY_MOVE (other.value));
        break;

      case 143: // ListLiteral
        value.YY_MOVE_OR_COPY< ListLiteral::Ptr > (YY_MOVE (other.value));
        break;

      case 134: // Literal
        value.YY_MOVE_OR_COPY< Literal::Ptr > (YY_MOVE (other.value));
        break;

      case 125: // LiteralCallExpression
        value.YY_MOVE_OR_COPY< LiteralCallExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 124: // MethodCallExpression
        value.YY_MOVE_OR_COPY< MethodCallExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 148: // Assignment
        value.YY_MOVE_OR_COPY< NamedExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 147: // Assignments
        value.YY_MOVE_OR_COPY< NamedExpressions::Ptr > (YY_MOVE (other.value));
        break;

      case 144: // RangeLiteral
        value.YY_MOVE_OR_COPY< RangeLiteral::Ptr > (YY_MOVE (other.value));
        break;

      case 146: // RecordLiteral
        value.YY_MOVE_OR_COPY< RecordLiteral::Ptr > (YY_MOVE (other.value));
        break;

      case 153: // RecordType
        value.YY_MOVE_OR_COPY< RecordType::Ptr > (YY_MOVE (other.value));
        break;

      case 142: // ReferenceLiteral
        value.YY_MOVE_OR_COPY< ReferenceLiteral::Ptr > (YY_MOVE (other.value));
        break;

      case 155: // RelationType
        value.YY_MOVE_OR_COPY< RelationType::Ptr > (YY_MOVE (other.value));
        break;

      case 103: // Rule
        value.YY_MOVE_OR_COPY< Rule::Ptr > (YY_MOVE (other.value));
        break;

      case 96: // RuleDefinition
        value.YY_MOVE_OR_COPY< RuleDefinition::Ptr > (YY_MOVE (other.value));
        break;

      case 102: // Rules
        value.YY_MOVE_OR_COPY< Rules::Ptr > (YY_MOVE (other.value));
        break;

      case 114: // SequenceRule
        value.YY_MOVE_OR_COPY< SequenceRule::Ptr > (YY_MOVE (other.value));
        break;

      case 104: // SkipRule
        value.YY_MOVE_OR_COPY< SkipRule::Ptr > (YY_MOVE (other.value));
        break;

      case 88: // Specification
        value.YY_MOVE_OR_COPY< Specification::Ptr > (YY_MOVE (other.value));
        break;

      case 154: // TemplateType
        value.YY_MOVE_OR_COPY< TemplateType::Ptr > (YY_MOVE (other.value));
        break;

      case 145: // TupleLiteral
        value.YY_MOVE_OR_COPY< TupleLiteral::Ptr > (YY_MOVE (other.value));
        break;

      case 152: // TupleType
        value.YY_MOVE_OR_COPY< TupleType::Ptr > (YY_MOVE (other.value));
        break;

      case 127: // TypeCastingExpression
        value.YY_MOVE_OR_COPY< TypeCastingExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 149: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        value.YY_MOVE_OR_COPY< Types::Ptr > (YY_MOVE (other.value));
        break;

      case 135: // UndefinedLiteral
        value.YY_MOVE_OR_COPY< UndefLiteral::Ptr > (YY_MOVE (other.value));
        break;

      case 131: // UniversalQuantifierExpression
        value.YY_MOVE_OR_COPY< UniversalQuantifierExpression::Ptr > (YY_MOVE (other.value));
        break;

      case 115: // UpdateRule
        value.YY_MOVE_OR_COPY< UpdateRule::Ptr > (YY_MOVE (other.value));
        break;

      case 100: // UsingDefinition
        value.YY_MOVE_OR_COPY< UsingDefinition::Ptr > (YY_MOVE (other.value));
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
      case 136: // BooleanLiteral
      case 137: // IntegerLiteral
      case 138: // RationalLiteral
      case 139: // DecimalLiteral
      case 140: // BinaryLiteral
      case 141: // StringLiteral
        value.YY_MOVE_OR_COPY< ValueLiteral::Ptr > (YY_MOVE (other.value));
        break;

      case 173: // VariableBinding
        value.YY_MOVE_OR_COPY< VariableBinding::Ptr > (YY_MOVE (other.value));
        break;

      case 172: // VariableBindings
        value.YY_MOVE_OR_COPY< VariableBindings::Ptr > (YY_MOVE (other.value));
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.YY_MOVE_OR_COPY< VariableDefinition::Ptr > (YY_MOVE (other.value));
        break;

      case 159: // Parameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        value.YY_MOVE_OR_COPY< VariableDefinitions::Ptr > (YY_MOVE (other.value));
        break;

      case 117: // WhileRule
        value.YY_MOVE_OR_COPY< WhileRule::Ptr > (YY_MOVE (other.value));
        break;

      case 150: // Type
        value.YY_MOVE_OR_COPY< libcasm_fe::Ast::Type::Ptr > (YY_MOVE (other.value));
        break;

      default:
        break;
    }

  }


  // Implementation of basic_symbol constructor for each type.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (location_type) l)
    : Base (t)
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Ast::Token::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Attribute::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Attributes::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (BasicAttribute::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (BasicType::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (BlockRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (CallExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (CallRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (CardinalityExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Case::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (CaseRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Cases::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ChooseExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ChooseRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ConditionalExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ConditionalRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Defined::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Definition::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Definitions::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (DerivedDefinition::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (DirectCallExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (EnumerationDefinition::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (EnumeratorDefinition::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Enumerators::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ExistentialQuantifierExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Expression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ExpressionAttribute::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Expressions::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (FixedSizedType::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ForallRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (FunctionDefinition::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (HeaderDefinition::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Identifier::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (IdentifierPath::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (IndirectCallExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (InitDefinition::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Initializer::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Initializers::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Initially::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (InvariantDefinition::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (IterateRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (LetExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (LetRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ListLiteral::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Literal::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (LiteralCallExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (MethodCallExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (NamedExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (NamedExpressions::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (RangeLiteral::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (RecordLiteral::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (RecordType::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ReferenceLiteral::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (RelationType::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Rule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (RuleDefinition::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Rules::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (SequenceRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (SkipRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Specification::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (TemplateType::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (TupleLiteral::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (TupleType::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (TypeCastingExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (Types::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (UndefLiteral::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (UniversalQuantifierExpression::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (UpdateRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (UsingDefinition::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (ValueLiteral::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (VariableBinding::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (VariableBindings::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (VariableDefinition::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (VariableDefinitions::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (WhileRule::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, YY_RVREF (libcasm_fe::Ast::Type::Ptr) v, YY_RVREF (location_type) l)
    : Base (t)
    , value (YY_MOVE (v))
    , location (YY_MOVE (l))
  {}



  template <typename Base>
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
  switch (yytype)
    {
      case 3: // "CASM"
      case 4: // "init"
      case 5: // "derived"
      case 6: // "enumeration"
      case 7: // "rule"
      case 8: // "using"
      case 9: // "invariant"
      case 10: // "function"
      case 11: // "initially"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "in"
      case 20: // "forall"
      case 21: // "choose"
      case 22: // "iterate"
      case 23: // "do"
      case 24: // "if"
      case 25: // "then"
      case 26: // "else"
      case 27: // "case"
      case 28: // "of"
      case 29: // "default"
      case 30: // "holds"
      case 31: // "exists"
      case 32: // "with"
      case 33: // "as"
      case 34: // "while"
      case 35: // "undef"
      case 36: // "false"
      case 37: // "true"
      case 38: // "and"
      case 39: // "or"
      case 40: // "xor"
      case 41: // "implies"
      case 42: // "not"
      case 43: // "+"
      case 44: // "-"
      case 45: // "="
      case 46: // "("
      case 47: // ")"
      case 48: // "["
      case 49: // "]"
      case 50: // "{"
      case 51: // "}"
      case 52: // ":"
      case 53: // "::"
      case 54: // "_"
      case 55: // "|"
      case 56: // "@"
      case 57: // ","
      case 58: // "<"
      case 59: // ">"
      case 60: // "*"
      case 61: // "/"
      case 62: // "%"
      case 63: // "^"
      case 64: // "'"
      case 65: // ".."
      case 66: // "."
      case 67: // "->"
      case 68: // "=>"
      case 69: // ":="
      case 70: // "!="
      case 71: // "<="
      case 72: // ">="
      case 73: // "{|"
      case 74: // "|}"
        value.template destroy< Ast::Token::Ptr > ();
        break;

      case 175: // Attribute
        value.template destroy< Attribute::Ptr > ();
        break;

      case 174: // Attributes
        value.template destroy< Attributes::Ptr > ();
        break;

      case 176: // BasicAttribute
        value.template destroy< BasicAttribute::Ptr > ();
        break;

      case 151: // BasicType
        value.template destroy< BasicType::Ptr > ();
        break;

      case 113: // BlockRule
        value.template destroy< BlockRule::Ptr > ();
        break;

      case 122: // CallExpression
        value.template destroy< CallExpression::Ptr > ();
        break;

      case 116: // CallRule
        value.template destroy< CallRule::Ptr > ();
        break;

      case 133: // CardinalityExpression
        value.template destroy< CardinalityExpression::Ptr > ();
        break;

      case 108: // CaseLabel
        value.template destroy< Case::Ptr > ();
        break;

      case 106: // CaseRule
        value.template destroy< CaseRule::Ptr > ();
        break;

      case 107: // CaseLabels
        value.template destroy< Cases::Ptr > ();
        break;

      case 130: // ChooseExpression
        value.template destroy< ChooseExpression::Ptr > ();
        break;

      case 111: // ChooseRule
        value.template destroy< ChooseRule::Ptr > ();
        break;

      case 129: // ConditionalExpression
        value.template destroy< ConditionalExpression::Ptr > ();
        break;

      case 105: // ConditionalRule
        value.template destroy< ConditionalRule::Ptr > ();
        break;

      case 160: // MaybeDefined
        value.template destroy< Defined::Ptr > ();
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        value.template destroy< Definition::Ptr > ();
        break;

      case 90: // Definitions
        value.template destroy< Definitions::Ptr > ();
        break;

      case 95: // DerivedDefinition
        value.template destroy< DerivedDefinition::Ptr > ();
        break;

      case 123: // DirectCallExpression
        value.template destroy< DirectCallExpression::Ptr > ();
        break;

      case 94: // EnumerationDefinition
        value.template destroy< EnumerationDefinition::Ptr > ();
        break;

      case 98: // EnumeratorDefinition
        value.template destroy< EnumeratorDefinition::Ptr > ();
        break;

      case 99: // Enumerators
        value.template destroy< Enumerators::Ptr > ();
        break;

      case 132: // ExistentialQuantifierExpression
        value.template destroy< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
        value.template destroy< Expression::Ptr > ();
        break;

      case 177: // ExpressionAttribute
        value.template destroy< ExpressionAttribute::Ptr > ();
        break;

      case 118: // Terms
        value.template destroy< Expressions::Ptr > ();
        break;

      case 156: // FixedSizedType
        value.template destroy< FixedSizedType::Ptr > ();
        break;

      case 110: // ForallRule
        value.template destroy< ForallRule::Ptr > ();
        break;

      case 97: // FunctionDefinition
        value.template destroy< FunctionDefinition::Ptr > ();
        break;

      case 89: // Header
        value.template destroy< HeaderDefinition::Ptr > ();
        break;

      case 81: // "identifier"
      case 164: // Identifier
        value.template destroy< Identifier::Ptr > ();
        break;

      case 165: // IdentifierPath
        value.template destroy< IdentifierPath::Ptr > ();
        break;

      case 126: // IndirectCallExpression
        value.template destroy< IndirectCallExpression::Ptr > ();
        break;

      case 93: // InitDefinition
        value.template destroy< InitDefinition::Ptr > ();
        break;

      case 163: // Initializer
        value.template destroy< Initializer::Ptr > ();
        break;

      case 162: // Initializers
        value.template destroy< Initializers::Ptr > ();
        break;

      case 161: // MaybeInitially
        value.template destroy< Initially::Ptr > ();
        break;

      case 101: // InvariantDefinition
        value.template destroy< InvariantDefinition::Ptr > ();
        break;

      case 112: // IterateRule
        value.template destroy< IterateRule::Ptr > ();
        break;

      case 128: // LetExpression
        value.template destroy< LetExpression::Ptr > ();
        break;

      case 109: // LetRule
        value.template destroy< LetRule::Ptr > ();
        break;

      case 143: // ListLiteral
        value.template destroy< ListLiteral::Ptr > ();
        break;

      case 134: // Literal
        value.template destroy< Literal::Ptr > ();
        break;

      case 125: // LiteralCallExpression
        value.template destroy< LiteralCallExpression::Ptr > ();
        break;

      case 124: // MethodCallExpression
        value.template destroy< MethodCallExpression::Ptr > ();
        break;

      case 148: // Assignment
        value.template destroy< NamedExpression::Ptr > ();
        break;

      case 147: // Assignments
        value.template destroy< NamedExpressions::Ptr > ();
        break;

      case 144: // RangeLiteral
        value.template destroy< RangeLiteral::Ptr > ();
        break;

      case 146: // RecordLiteral
        value.template destroy< RecordLiteral::Ptr > ();
        break;

      case 153: // RecordType
        value.template destroy< RecordType::Ptr > ();
        break;

      case 142: // ReferenceLiteral
        value.template destroy< ReferenceLiteral::Ptr > ();
        break;

      case 155: // RelationType
        value.template destroy< RelationType::Ptr > ();
        break;

      case 103: // Rule
        value.template destroy< Rule::Ptr > ();
        break;

      case 96: // RuleDefinition
        value.template destroy< RuleDefinition::Ptr > ();
        break;

      case 102: // Rules
        value.template destroy< Rules::Ptr > ();
        break;

      case 114: // SequenceRule
        value.template destroy< SequenceRule::Ptr > ();
        break;

      case 104: // SkipRule
        value.template destroy< SkipRule::Ptr > ();
        break;

      case 88: // Specification
        value.template destroy< Specification::Ptr > ();
        break;

      case 154: // TemplateType
        value.template destroy< TemplateType::Ptr > ();
        break;

      case 145: // TupleLiteral
        value.template destroy< TupleLiteral::Ptr > ();
        break;

      case 152: // TupleType
        value.template destroy< TupleType::Ptr > ();
        break;

      case 127: // TypeCastingExpression
        value.template destroy< TypeCastingExpression::Ptr > ();
        break;

      case 149: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        value.template destroy< Types::Ptr > ();
        break;

      case 135: // UndefinedLiteral
        value.template destroy< UndefLiteral::Ptr > ();
        break;

      case 131: // UniversalQuantifierExpression
        value.template destroy< UniversalQuantifierExpression::Ptr > ();
        break;

      case 115: // UpdateRule
        value.template destroy< UpdateRule::Ptr > ();
        break;

      case 100: // UsingDefinition
        value.template destroy< UsingDefinition::Ptr > ();
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
      case 136: // BooleanLiteral
      case 137: // IntegerLiteral
      case 138: // RationalLiteral
      case 139: // DecimalLiteral
      case 140: // BinaryLiteral
      case 141: // StringLiteral
        value.template destroy< ValueLiteral::Ptr > ();
        break;

      case 173: // VariableBinding
        value.template destroy< VariableBinding::Ptr > ();
        break;

      case 172: // VariableBindings
        value.template destroy< VariableBindings::Ptr > ();
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.template destroy< VariableDefinition::Ptr > ();
        break;

      case 159: // Parameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        value.template destroy< VariableDefinitions::Ptr > ();
        break;

      case 117: // WhileRule
        value.template destroy< WhileRule::Ptr > ();
        break;

      case 150: // Type
        value.template destroy< libcasm_fe::Ast::Type::Ptr > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 3: // "CASM"
      case 4: // "init"
      case 5: // "derived"
      case 6: // "enumeration"
      case 7: // "rule"
      case 8: // "using"
      case 9: // "invariant"
      case 10: // "function"
      case 11: // "initially"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "in"
      case 20: // "forall"
      case 21: // "choose"
      case 22: // "iterate"
      case 23: // "do"
      case 24: // "if"
      case 25: // "then"
      case 26: // "else"
      case 27: // "case"
      case 28: // "of"
      case 29: // "default"
      case 30: // "holds"
      case 31: // "exists"
      case 32: // "with"
      case 33: // "as"
      case 34: // "while"
      case 35: // "undef"
      case 36: // "false"
      case 37: // "true"
      case 38: // "and"
      case 39: // "or"
      case 40: // "xor"
      case 41: // "implies"
      case 42: // "not"
      case 43: // "+"
      case 44: // "-"
      case 45: // "="
      case 46: // "("
      case 47: // ")"
      case 48: // "["
      case 49: // "]"
      case 50: // "{"
      case 51: // "}"
      case 52: // ":"
      case 53: // "::"
      case 54: // "_"
      case 55: // "|"
      case 56: // "@"
      case 57: // ","
      case 58: // "<"
      case 59: // ">"
      case 60: // "*"
      case 61: // "/"
      case 62: // "%"
      case 63: // "^"
      case 64: // "'"
      case 65: // ".."
      case 66: // "."
      case 67: // "->"
      case 68: // "=>"
      case 69: // ":="
      case 70: // "!="
      case 71: // "<="
      case 72: // ">="
      case 73: // "{|"
      case 74: // "|}"
        value.move< Ast::Token::Ptr > (YY_MOVE (s.value));
        break;

      case 175: // Attribute
        value.move< Attribute::Ptr > (YY_MOVE (s.value));
        break;

      case 174: // Attributes
        value.move< Attributes::Ptr > (YY_MOVE (s.value));
        break;

      case 176: // BasicAttribute
        value.move< BasicAttribute::Ptr > (YY_MOVE (s.value));
        break;

      case 151: // BasicType
        value.move< BasicType::Ptr > (YY_MOVE (s.value));
        break;

      case 113: // BlockRule
        value.move< BlockRule::Ptr > (YY_MOVE (s.value));
        break;

      case 122: // CallExpression
        value.move< CallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 116: // CallRule
        value.move< CallRule::Ptr > (YY_MOVE (s.value));
        break;

      case 133: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 108: // CaseLabel
        value.move< Case::Ptr > (YY_MOVE (s.value));
        break;

      case 106: // CaseRule
        value.move< CaseRule::Ptr > (YY_MOVE (s.value));
        break;

      case 107: // CaseLabels
        value.move< Cases::Ptr > (YY_MOVE (s.value));
        break;

      case 130: // ChooseExpression
        value.move< ChooseExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 111: // ChooseRule
        value.move< ChooseRule::Ptr > (YY_MOVE (s.value));
        break;

      case 129: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 105: // ConditionalRule
        value.move< ConditionalRule::Ptr > (YY_MOVE (s.value));
        break;

      case 160: // MaybeDefined
        value.move< Defined::Ptr > (YY_MOVE (s.value));
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        value.move< Definition::Ptr > (YY_MOVE (s.value));
        break;

      case 90: // Definitions
        value.move< Definitions::Ptr > (YY_MOVE (s.value));
        break;

      case 95: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 123: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 94: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 98: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 99: // Enumerators
        value.move< Enumerators::Ptr > (YY_MOVE (s.value));
        break;

      case 132: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
        value.move< Expression::Ptr > (YY_MOVE (s.value));
        break;

      case 177: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (YY_MOVE (s.value));
        break;

      case 118: // Terms
        value.move< Expressions::Ptr > (YY_MOVE (s.value));
        break;

      case 156: // FixedSizedType
        value.move< FixedSizedType::Ptr > (YY_MOVE (s.value));
        break;

      case 110: // ForallRule
        value.move< ForallRule::Ptr > (YY_MOVE (s.value));
        break;

      case 97: // FunctionDefinition
        value.move< FunctionDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 89: // Header
        value.move< HeaderDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 81: // "identifier"
      case 164: // Identifier
        value.move< Identifier::Ptr > (YY_MOVE (s.value));
        break;

      case 165: // IdentifierPath
        value.move< IdentifierPath::Ptr > (YY_MOVE (s.value));
        break;

      case 126: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 93: // InitDefinition
        value.move< InitDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 163: // Initializer
        value.move< Initializer::Ptr > (YY_MOVE (s.value));
        break;

      case 162: // Initializers
        value.move< Initializers::Ptr > (YY_MOVE (s.value));
        break;

      case 161: // MaybeInitially
        value.move< Initially::Ptr > (YY_MOVE (s.value));
        break;

      case 101: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 112: // IterateRule
        value.move< IterateRule::Ptr > (YY_MOVE (s.value));
        break;

      case 128: // LetExpression
        value.move< LetExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 109: // LetRule
        value.move< LetRule::Ptr > (YY_MOVE (s.value));
        break;

      case 143: // ListLiteral
        value.move< ListLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 134: // Literal
        value.move< Literal::Ptr > (YY_MOVE (s.value));
        break;

      case 125: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 124: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 148: // Assignment
        value.move< NamedExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 147: // Assignments
        value.move< NamedExpressions::Ptr > (YY_MOVE (s.value));
        break;

      case 144: // RangeLiteral
        value.move< RangeLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 146: // RecordLiteral
        value.move< RecordLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 153: // RecordType
        value.move< RecordType::Ptr > (YY_MOVE (s.value));
        break;

      case 142: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 155: // RelationType
        value.move< RelationType::Ptr > (YY_MOVE (s.value));
        break;

      case 103: // Rule
        value.move< Rule::Ptr > (YY_MOVE (s.value));
        break;

      case 96: // RuleDefinition
        value.move< RuleDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 102: // Rules
        value.move< Rules::Ptr > (YY_MOVE (s.value));
        break;

      case 114: // SequenceRule
        value.move< SequenceRule::Ptr > (YY_MOVE (s.value));
        break;

      case 104: // SkipRule
        value.move< SkipRule::Ptr > (YY_MOVE (s.value));
        break;

      case 88: // Specification
        value.move< Specification::Ptr > (YY_MOVE (s.value));
        break;

      case 154: // TemplateType
        value.move< TemplateType::Ptr > (YY_MOVE (s.value));
        break;

      case 145: // TupleLiteral
        value.move< TupleLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 152: // TupleType
        value.move< TupleType::Ptr > (YY_MOVE (s.value));
        break;

      case 127: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 149: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        value.move< Types::Ptr > (YY_MOVE (s.value));
        break;

      case 135: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 131: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 115: // UpdateRule
        value.move< UpdateRule::Ptr > (YY_MOVE (s.value));
        break;

      case 100: // UsingDefinition
        value.move< UsingDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 75: // "binary"
      case 76: // "hexadecimal"
      case 77: // "integer"
      case 78: // "rational"
      case 79: // "decimal"
      case 80: // "string"
      case 136: // BooleanLiteral
      case 137: // IntegerLiteral
      case 138: // RationalLiteral
      case 139: // DecimalLiteral
      case 140: // BinaryLiteral
      case 141: // StringLiteral
        value.move< ValueLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 173: // VariableBinding
        value.move< VariableBinding::Ptr > (YY_MOVE (s.value));
        break;

      case 172: // VariableBindings
        value.move< VariableBindings::Ptr > (YY_MOVE (s.value));
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 159: // Parameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        value.move< VariableDefinitions::Ptr > (YY_MOVE (s.value));
        break;

      case 117: // WhileRule
        value.move< WhileRule::Ptr > (YY_MOVE (s.value));
        break;

      case 150: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }

  inline
  Parser::token_type
  Parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }

  // Implementation of make_symbol for each symbol type.
  inline
  Parser::symbol_type
  Parser::make_END (YY_COPY (location_type) l)
  {
    return symbol_type (token::END, YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_CASM (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::CASM, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_INIT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::INIT, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_DERIVED (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::DERIVED, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_ENUMERATION (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::ENUMERATION, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_RULE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::RULE, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_USING (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::USING, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_INVARIANT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::INVARIANT, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_FUNCTION (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::FUNCTION, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_INITIALLY (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::INITIALLY, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_DEFINED (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::DEFINED, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_SEQ (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::SEQ, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_ENDSEQ (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::ENDSEQ, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_PAR (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::PAR, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_ENDPAR (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::ENDPAR, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_SKIP (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::SKIP, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_LET (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::LET, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_IN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::IN, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_FORALL (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::FORALL, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_CHOOSE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::CHOOSE, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_ITERATE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::ITERATE, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_DO (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::DO, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_IF (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::IF, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_THEN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::THEN, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_ELSE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::ELSE, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_CASE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::CASE, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_OF (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::OF, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_DEFAULT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::DEFAULT, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_HOLDS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::HOLDS, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_EXISTS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::EXISTS, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_WITH (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::WITH, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_AS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::AS, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_WHILE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::WHILE, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_UNDEF (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::UNDEF, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_FALSE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::FALSE, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_TRUE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::TRUE, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_AND (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::AND, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_OR (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::OR, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_XOR (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::XOR, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_IMPLIES (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::IMPLIES, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_NOT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::NOT, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_PLUS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::PLUS, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_MINUS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::MINUS, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_EQUAL (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::EQUAL, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_LPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::LPAREN, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_RPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::RPAREN, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_LSQPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::LSQPAREN, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_RSQPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::RSQPAREN, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_LCURPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::LCURPAREN, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_RCURPAREN (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::RCURPAREN, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_COLON (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::COLON, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_DOUBLECOLON (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::DOUBLECOLON, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_UNDERLINE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::UNDERLINE, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_VERTICAL_BAR (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::VERTICAL_BAR, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_AT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::AT, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_COMMA (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::COMMA, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_LESSER (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::LESSER, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_GREATER (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::GREATER, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_ASTERIX (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::ASTERIX, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_SLASH (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::SLASH, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_PERCENT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::PERCENT, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_CARET (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::CARET, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_MARK (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::MARK, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_DOTDOT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::DOTDOT, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_DOT (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::DOT, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_MAPS (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::MAPS, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_ARROW (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::ARROW, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_UPDATE (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::UPDATE, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_NEQUAL (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::NEQUAL, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_LESSEQ (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::LESSEQ, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_GREATEREQ (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::GREATEREQ, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_SEQ_BRACKET (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::SEQ_BRACKET, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_ENDSEQ_BRACKET (YY_COPY (Ast::Token::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::ENDSEQ_BRACKET, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_BINARY (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::BINARY, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_HEXADECIMAL (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::HEXADECIMAL, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_INTEGER (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::INTEGER, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_RATIONAL (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::RATIONAL, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_DECIMAL (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::DECIMAL, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_STRING (YY_COPY (ValueLiteral::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::STRING, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_IDENTIFIER (YY_COPY (Identifier::Ptr) v, YY_COPY (location_type) l)
  {
    return symbol_type (token::IDENTIFIER, YY_MOVE (v), YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_BASIC_TYPE (YY_COPY (location_type) l)
  {
    return symbol_type (token::BASIC_TYPE, YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_CALL (YY_COPY (location_type) l)
  {
    return symbol_type (token::CALL, YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_UPLUS (YY_COPY (location_type) l)
  {
    return symbol_type (token::UPLUS, YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_UMINUS (YY_COPY (location_type) l)
  {
    return symbol_type (token::UMINUS, YY_MOVE (l));
  }

  inline
  Parser::symbol_type
  Parser::make_CALL_WITHOUT_ARGS (YY_COPY (location_type) l)
  {
    return symbol_type (token::CALL_WITHOUT_ARGS, YY_MOVE (l));
  }


#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:403
} // libcasm_fe
#line 4199 "GrammarParser.tab.h" // lalr1.cc:403




#endif // !YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
