// A Bison parser, made by GNU Bison 3.3.2.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

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
#line 64 "../../obj/src/GrammarParser.y" // lalr1.cc:401

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

#line 69 "GrammarParser.tab.h" // lalr1.cc:401

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
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

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
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

#line 50 "../../obj/src/GrammarParser.y" // lalr1.cc:401
namespace libcasm_fe {
#line 185 "GrammarParser.tab.h" // lalr1.cc:401



  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
      , yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YYASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= size);
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
    as () YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *that.yytypeid_);
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
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
    semantic_type (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

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

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef libstdhl::SourceLocation location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

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
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that);
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Ast::Token::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Ast::Token::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Attribute::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Attribute::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Attributes::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Attributes::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, BasicAttribute::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const BasicAttribute::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, BasicType::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const BasicType::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, BlockRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const BlockRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, CallExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const CallExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, CallRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const CallRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, CardinalityExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const CardinalityExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Case::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Case::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, CaseRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const CaseRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Cases::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Cases::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ChooseExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ChooseExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ChooseRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ChooseRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ConditionalExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ConditionalExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ConditionalRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ConditionalRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Defined::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Defined::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Definition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Definition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Definitions::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Definitions::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, DerivedDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const DerivedDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, DirectCallExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const DirectCallExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, EnumerationDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const EnumerationDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, EnumeratorDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const EnumeratorDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Enumerators::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Enumerators::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ExistentialQuantifierExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ExistentialQuantifierExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Expression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Expression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ExpressionAttribute::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ExpressionAttribute::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Expressions::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Expressions::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, FixedSizedType::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const FixedSizedType::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ForallRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ForallRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, FunctionDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const FunctionDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, HeaderDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const HeaderDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Identifier::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Identifier::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, IdentifierPath::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const IdentifierPath::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, IndirectCallExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const IndirectCallExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, InitDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const InitDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Initializer::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Initializer::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Initializers::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Initializers::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Initially::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Initially::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, InvariantDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const InvariantDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, IterateRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const IterateRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, LetExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const LetExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, LetRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const LetRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ListLiteral::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ListLiteral::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Literal::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Literal::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, LiteralCallExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const LiteralCallExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, MethodCallExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const MethodCallExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, NamedExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const NamedExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, NamedExpressions::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const NamedExpressions::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, RangeLiteral::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const RangeLiteral::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, RecordLiteral::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const RecordLiteral::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, RecordType::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const RecordType::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ReferenceLiteral::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ReferenceLiteral::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, RelationType::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const RelationType::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Rule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Rule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, RuleDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const RuleDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Rules::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Rules::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, SequenceRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const SequenceRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, SkipRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const SkipRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Specification::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Specification::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TemplateType::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TemplateType::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TupleLiteral::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TupleLiteral::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TupleType::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TupleType::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, TypeCastingExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const TypeCastingExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, Types::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Types::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, UndefLiteral::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const UndefLiteral::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, UniversalQuantifierExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const UniversalQuantifierExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, UpdateRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const UpdateRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, UsingDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const UsingDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, ValueLiteral::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ValueLiteral::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VariableBinding::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VariableBinding::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VariableBindings::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VariableBindings::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VariableDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VariableDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, VariableDefinitions::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VariableDefinitions::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, WhileRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const WhileRule::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, libcasm_fe::Ast::Type::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const libcasm_fe::Ast::Type::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
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

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_type (by_type&& that);
#endif

      /// Copy constructor.
      by_type (const by_type& that);

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
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The token.
      token_type token () const YY_NOEXCEPT;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_type>
    {
      /// Superclass.
      typedef basic_symbol<by_type> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YYASSERT (tok == token::END || tok == token::BASIC_TYPE || tok == token::CALL || tok == token::UPLUS || tok == token::UMINUS || tok == token::CALL_WITHOUT_ARGS);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YYASSERT (tok == token::END || tok == token::BASIC_TYPE || tok == token::CALL || tok == token::UPLUS || tok == token::UMINUS || tok == token::CALL_WITHOUT_ARGS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Ast::Token::Ptr v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YYASSERT (tok == token::CASM || tok == token::INIT || tok == token::DERIVED || tok == token::ENUMERATION || tok == token::RULE || tok == token::USING || tok == token::INVARIANT || tok == token::FUNCTION || tok == token::INITIALLY || tok == token::DEFINED || tok == token::SEQ || tok == token::ENDSEQ || tok == token::PAR || tok == token::ENDPAR || tok == token::SKIP || tok == token::LET || tok == token::IN || tok == token::FORALL || tok == token::CHOOSE || tok == token::ITERATE || tok == token::DO || tok == token::IF || tok == token::THEN || tok == token::ELSE || tok == token::CASE || tok == token::OF || tok == token::DEFAULT || tok == token::HOLDS || tok == token::EXISTS || tok == token::WITH || tok == token::AS || tok == token::WHILE || tok == token::UNDEF || tok == token::FALSE || tok == token::TRUE || tok == token::AND || tok == token::OR || tok == token::XOR || tok == token::IMPLIES || tok == token::NOT || tok == token::PLUS || tok == token::MINUS || tok == token::EQUAL || tok == token::LPAREN || tok == token::RPAREN || tok == token::LSQPAREN || tok == token::RSQPAREN || tok == token::LCURPAREN || tok == token::RCURPAREN || tok == token::COLON || tok == token::DOUBLECOLON || tok == token::UNDERLINE || tok == token::VERTICAL_BAR || tok == token::AT || tok == token::COMMA || tok == token::LESSER || tok == token::GREATER || tok == token::ASTERIX || tok == token::SLASH || tok == token::PERCENT || tok == token::CARET || tok == token::MARK || tok == token::DOTDOT || tok == token::DOT || tok == token::MAPS || tok == token::ARROW || tok == token::UPDATE || tok == token::NEQUAL || tok == token::LESSEQ || tok == token::GREATEREQ || tok == token::SEQ_BRACKET || tok == token::ENDSEQ_BRACKET);
      }
#else
      symbol_type (int tok, const Ast::Token::Ptr& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YYASSERT (tok == token::CASM || tok == token::INIT || tok == token::DERIVED || tok == token::ENUMERATION || tok == token::RULE || tok == token::USING || tok == token::INVARIANT || tok == token::FUNCTION || tok == token::INITIALLY || tok == token::DEFINED || tok == token::SEQ || tok == token::ENDSEQ || tok == token::PAR || tok == token::ENDPAR || tok == token::SKIP || tok == token::LET || tok == token::IN || tok == token::FORALL || tok == token::CHOOSE || tok == token::ITERATE || tok == token::DO || tok == token::IF || tok == token::THEN || tok == token::ELSE || tok == token::CASE || tok == token::OF || tok == token::DEFAULT || tok == token::HOLDS || tok == token::EXISTS || tok == token::WITH || tok == token::AS || tok == token::WHILE || tok == token::UNDEF || tok == token::FALSE || tok == token::TRUE || tok == token::AND || tok == token::OR || tok == token::XOR || tok == token::IMPLIES || tok == token::NOT || tok == token::PLUS || tok == token::MINUS || tok == token::EQUAL || tok == token::LPAREN || tok == token::RPAREN || tok == token::LSQPAREN || tok == token::RSQPAREN || tok == token::LCURPAREN || tok == token::RCURPAREN || tok == token::COLON || tok == token::DOUBLECOLON || tok == token::UNDERLINE || tok == token::VERTICAL_BAR || tok == token::AT || tok == token::COMMA || tok == token::LESSER || tok == token::GREATER || tok == token::ASTERIX || tok == token::SLASH || tok == token::PERCENT || tok == token::CARET || tok == token::MARK || tok == token::DOTDOT || tok == token::DOT || tok == token::MAPS || tok == token::ARROW || tok == token::UPDATE || tok == token::NEQUAL || tok == token::LESSEQ || tok == token::GREATEREQ || tok == token::SEQ_BRACKET || tok == token::ENDSEQ_BRACKET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Identifier::Ptr v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YYASSERT (tok == token::IDENTIFIER);
      }
#else
      symbol_type (int tok, const Identifier::Ptr& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YYASSERT (tok == token::IDENTIFIER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, ValueLiteral::Ptr v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YYASSERT (tok == token::BINARY || tok == token::HEXADECIMAL || tok == token::INTEGER || tok == token::RATIONAL || tok == token::DECIMAL || tok == token::STRING);
      }
#else
      symbol_type (int tok, const ValueLiteral::Ptr& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YYASSERT (tok == token::BINARY || tok == token::HEXADECIMAL || tok == token::INTEGER || tok == token::RATIONAL || tok == token::DECIMAL || tok == token::STRING);
      }
#endif
    };

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

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END (location_type l)
      {
        return symbol_type (token::END, std::move (l));
      }
#else
      static
      symbol_type
      make_END (const location_type& l)
      {
        return symbol_type (token::END, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASM (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::CASM, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CASM (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::CASM, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INIT (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::INIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INIT (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::INIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DERIVED (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DERIVED, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DERIVED (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DERIVED, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENUMERATION (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ENUMERATION, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ENUMERATION (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ENUMERATION, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RULE (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::RULE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RULE (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::RULE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USING (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::USING, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_USING (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::USING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INVARIANT (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::INVARIANT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INVARIANT (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::INVARIANT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FUNCTION (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::FUNCTION, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FUNCTION (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::FUNCTION, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INITIALLY (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::INITIALLY, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INITIALLY (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::INITIALLY, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEFINED (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DEFINED, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DEFINED (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DEFINED, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEQ (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::SEQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SEQ (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::SEQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENDSEQ (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ENDSEQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ENDSEQ (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ENDSEQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PAR (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::PAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PAR (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::PAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENDPAR (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ENDPAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ENDPAR (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ENDPAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SKIP (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::SKIP, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SKIP (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::SKIP, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LET (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LET, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LET (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LET, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IN (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::IN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IN (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::IN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FORALL (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::FORALL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FORALL (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::FORALL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHOOSE (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::CHOOSE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CHOOSE (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::CHOOSE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ITERATE (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ITERATE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ITERATE (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ITERATE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DO (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DO, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DO (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DO, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::IF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::IF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THEN (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::THEN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_THEN (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::THEN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ELSE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ELSE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASE (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::CASE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CASE (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::CASE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OF (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::OF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OF (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::OF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEFAULT (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DEFAULT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DEFAULT (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DEFAULT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOLDS (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::HOLDS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_HOLDS (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::HOLDS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXISTS (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::EXISTS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EXISTS (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::EXISTS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WITH (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::WITH, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WITH (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::WITH, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AS (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::AS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AS (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::AS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::WHILE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WHILE (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::WHILE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNDEF (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::UNDEF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNDEF (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::UNDEF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FALSE (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::FALSE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FALSE (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::FALSE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRUE (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::TRUE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TRUE (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::TRUE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::AND, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AND (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::AND, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::OR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OR (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::OR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_XOR (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::XOR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_XOR (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::XOR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IMPLIES (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::IMPLIES, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IMPLIES (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::IMPLIES, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::NOT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NOT (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::NOT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::PLUS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::PLUS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::MINUS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MINUS (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::MINUS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::EQUAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EQUAL (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::EQUAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LPAREN (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::RPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RPAREN (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::RPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LSQPAREN (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LSQPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LSQPAREN (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LSQPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RSQPAREN (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::RSQPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RSQPAREN (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::RSQPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LCURPAREN (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LCURPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LCURPAREN (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LCURPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RCURPAREN (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::RCURPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RCURPAREN (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::RCURPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::COLON, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::COLON, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOUBLECOLON (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DOUBLECOLON, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DOUBLECOLON (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DOUBLECOLON, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNDERLINE (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::UNDERLINE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNDERLINE (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::UNDERLINE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VERTICAL_BAR (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::VERTICAL_BAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_VERTICAL_BAR (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::VERTICAL_BAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AT (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::AT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AT (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::AT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::COMMA, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::COMMA, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESSER (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LESSER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LESSER (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LESSER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATER (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::GREATER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_GREATER (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::GREATER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASTERIX (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ASTERIX, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASTERIX (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ASTERIX, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SLASH (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::SLASH, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SLASH (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::SLASH, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PERCENT (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::PERCENT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PERCENT (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::PERCENT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CARET (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::CARET, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CARET (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::CARET, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MARK (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::MARK, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MARK (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::MARK, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOTDOT (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DOTDOT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DOTDOT (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DOTDOT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DOT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DOT (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DOT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAPS (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::MAPS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MAPS (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::MAPS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARROW (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ARROW, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ARROW (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ARROW, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UPDATE (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::UPDATE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UPDATE (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::UPDATE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEQUAL (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::NEQUAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NEQUAL (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::NEQUAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESSEQ (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LESSEQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LESSEQ (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LESSEQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATEREQ (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::GREATEREQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_GREATEREQ (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::GREATEREQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEQ_BRACKET (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::SEQ_BRACKET, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SEQ_BRACKET (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::SEQ_BRACKET, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENDSEQ_BRACKET (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ENDSEQ_BRACKET, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ENDSEQ_BRACKET (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ENDSEQ_BRACKET, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BINARY (ValueLiteral::Ptr v, location_type l)
      {
        return symbol_type (token::BINARY, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BINARY (const ValueLiteral::Ptr& v, const location_type& l)
      {
        return symbol_type (token::BINARY, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HEXADECIMAL (ValueLiteral::Ptr v, location_type l)
      {
        return symbol_type (token::HEXADECIMAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_HEXADECIMAL (const ValueLiteral::Ptr& v, const location_type& l)
      {
        return symbol_type (token::HEXADECIMAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTEGER (ValueLiteral::Ptr v, location_type l)
      {
        return symbol_type (token::INTEGER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INTEGER (const ValueLiteral::Ptr& v, const location_type& l)
      {
        return symbol_type (token::INTEGER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RATIONAL (ValueLiteral::Ptr v, location_type l)
      {
        return symbol_type (token::RATIONAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RATIONAL (const ValueLiteral::Ptr& v, const location_type& l)
      {
        return symbol_type (token::RATIONAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DECIMAL (ValueLiteral::Ptr v, location_type l)
      {
        return symbol_type (token::DECIMAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DECIMAL (const ValueLiteral::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DECIMAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRING (ValueLiteral::Ptr v, location_type l)
      {
        return symbol_type (token::STRING, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRING (const ValueLiteral::Ptr& v, const location_type& l)
      {
        return symbol_type (token::STRING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IDENTIFIER (Identifier::Ptr v, location_type l)
      {
        return symbol_type (token::IDENTIFIER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IDENTIFIER (const Identifier::Ptr& v, const location_type& l)
      {
        return symbol_type (token::IDENTIFIER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BASIC_TYPE (location_type l)
      {
        return symbol_type (token::BASIC_TYPE, std::move (l));
      }
#else
      static
      symbol_type
      make_BASIC_TYPE (const location_type& l)
      {
        return symbol_type (token::BASIC_TYPE, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CALL (location_type l)
      {
        return symbol_type (token::CALL, std::move (l));
      }
#else
      static
      symbol_type
      make_CALL (const location_type& l)
      {
        return symbol_type (token::CALL, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UPLUS (location_type l)
      {
        return symbol_type (token::UPLUS, std::move (l));
      }
#else
      static
      symbol_type
      make_UPLUS (const location_type& l)
      {
        return symbol_type (token::UPLUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UMINUS (location_type l)
      {
        return symbol_type (token::UMINUS, std::move (l));
      }
#else
      static
      symbol_type
      make_UMINUS (const location_type& l)
      {
        return symbol_type (token::UMINUS, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CALL_WITHOUT_ARGS (location_type l)
      {
        return symbol_type (token::CALL_WITHOUT_ARGS, std::move (l));
      }
#else
      static
      symbol_type
      make_CALL_WITHOUT_ARGS (const location_type& l)
      {
        return symbol_type (token::CALL_WITHOUT_ARGS, l);
      }
#endif


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

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
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
      by_state () YY_NOEXCEPT;

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

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
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);
#endif
    };

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
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (int n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      size_type
      size () const YY_NOEXCEPT
      {
        return seq_.size ();
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.rbegin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.rend ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, int range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (int i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        int range_;
      };

    private:
      stack (const stack&);
      stack& operator= (const stack&);
      /// The wrapped container.
      S seq_;
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

  inline
  Parser::token_number_type
  Parser::yytranslate_ (token_type t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
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

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
    , location (std::move (that.location))
  {
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
        value.move< Ast::Token::Ptr > (std::move (that.value));
        break;

      case 175: // Attribute
        value.move< Attribute::Ptr > (std::move (that.value));
        break;

      case 174: // Attributes
        value.move< Attributes::Ptr > (std::move (that.value));
        break;

      case 176: // BasicAttribute
        value.move< BasicAttribute::Ptr > (std::move (that.value));
        break;

      case 151: // BasicType
        value.move< BasicType::Ptr > (std::move (that.value));
        break;

      case 113: // BlockRule
        value.move< BlockRule::Ptr > (std::move (that.value));
        break;

      case 122: // CallExpression
        value.move< CallExpression::Ptr > (std::move (that.value));
        break;

      case 116: // CallRule
        value.move< CallRule::Ptr > (std::move (that.value));
        break;

      case 133: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (std::move (that.value));
        break;

      case 108: // CaseLabel
        value.move< Case::Ptr > (std::move (that.value));
        break;

      case 106: // CaseRule
        value.move< CaseRule::Ptr > (std::move (that.value));
        break;

      case 107: // CaseLabels
        value.move< Cases::Ptr > (std::move (that.value));
        break;

      case 130: // ChooseExpression
        value.move< ChooseExpression::Ptr > (std::move (that.value));
        break;

      case 111: // ChooseRule
        value.move< ChooseRule::Ptr > (std::move (that.value));
        break;

      case 129: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (std::move (that.value));
        break;

      case 105: // ConditionalRule
        value.move< ConditionalRule::Ptr > (std::move (that.value));
        break;

      case 160: // MaybeDefined
        value.move< Defined::Ptr > (std::move (that.value));
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        value.move< Definition::Ptr > (std::move (that.value));
        break;

      case 90: // Definitions
        value.move< Definitions::Ptr > (std::move (that.value));
        break;

      case 95: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (std::move (that.value));
        break;

      case 123: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (std::move (that.value));
        break;

      case 94: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (std::move (that.value));
        break;

      case 98: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (std::move (that.value));
        break;

      case 99: // Enumerators
        value.move< Enumerators::Ptr > (std::move (that.value));
        break;

      case 132: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (std::move (that.value));
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
        value.move< Expression::Ptr > (std::move (that.value));
        break;

      case 177: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (std::move (that.value));
        break;

      case 118: // Terms
        value.move< Expressions::Ptr > (std::move (that.value));
        break;

      case 156: // FixedSizedType
        value.move< FixedSizedType::Ptr > (std::move (that.value));
        break;

      case 110: // ForallRule
        value.move< ForallRule::Ptr > (std::move (that.value));
        break;

      case 97: // FunctionDefinition
        value.move< FunctionDefinition::Ptr > (std::move (that.value));
        break;

      case 89: // Header
        value.move< HeaderDefinition::Ptr > (std::move (that.value));
        break;

      case 81: // "identifier"
      case 164: // Identifier
        value.move< Identifier::Ptr > (std::move (that.value));
        break;

      case 165: // IdentifierPath
        value.move< IdentifierPath::Ptr > (std::move (that.value));
        break;

      case 126: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (std::move (that.value));
        break;

      case 93: // InitDefinition
        value.move< InitDefinition::Ptr > (std::move (that.value));
        break;

      case 163: // Initializer
        value.move< Initializer::Ptr > (std::move (that.value));
        break;

      case 162: // Initializers
        value.move< Initializers::Ptr > (std::move (that.value));
        break;

      case 161: // MaybeInitially
        value.move< Initially::Ptr > (std::move (that.value));
        break;

      case 101: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (std::move (that.value));
        break;

      case 112: // IterateRule
        value.move< IterateRule::Ptr > (std::move (that.value));
        break;

      case 128: // LetExpression
        value.move< LetExpression::Ptr > (std::move (that.value));
        break;

      case 109: // LetRule
        value.move< LetRule::Ptr > (std::move (that.value));
        break;

      case 143: // ListLiteral
        value.move< ListLiteral::Ptr > (std::move (that.value));
        break;

      case 134: // Literal
        value.move< Literal::Ptr > (std::move (that.value));
        break;

      case 125: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (std::move (that.value));
        break;

      case 124: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (std::move (that.value));
        break;

      case 148: // Assignment
        value.move< NamedExpression::Ptr > (std::move (that.value));
        break;

      case 147: // Assignments
        value.move< NamedExpressions::Ptr > (std::move (that.value));
        break;

      case 144: // RangeLiteral
        value.move< RangeLiteral::Ptr > (std::move (that.value));
        break;

      case 146: // RecordLiteral
        value.move< RecordLiteral::Ptr > (std::move (that.value));
        break;

      case 153: // RecordType
        value.move< RecordType::Ptr > (std::move (that.value));
        break;

      case 142: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (std::move (that.value));
        break;

      case 155: // RelationType
        value.move< RelationType::Ptr > (std::move (that.value));
        break;

      case 103: // Rule
        value.move< Rule::Ptr > (std::move (that.value));
        break;

      case 96: // RuleDefinition
        value.move< RuleDefinition::Ptr > (std::move (that.value));
        break;

      case 102: // Rules
        value.move< Rules::Ptr > (std::move (that.value));
        break;

      case 114: // SequenceRule
        value.move< SequenceRule::Ptr > (std::move (that.value));
        break;

      case 104: // SkipRule
        value.move< SkipRule::Ptr > (std::move (that.value));
        break;

      case 88: // Specification
        value.move< Specification::Ptr > (std::move (that.value));
        break;

      case 154: // TemplateType
        value.move< TemplateType::Ptr > (std::move (that.value));
        break;

      case 145: // TupleLiteral
        value.move< TupleLiteral::Ptr > (std::move (that.value));
        break;

      case 152: // TupleType
        value.move< TupleType::Ptr > (std::move (that.value));
        break;

      case 127: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (std::move (that.value));
        break;

      case 149: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        value.move< Types::Ptr > (std::move (that.value));
        break;

      case 135: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (std::move (that.value));
        break;

      case 131: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (std::move (that.value));
        break;

      case 115: // UpdateRule
        value.move< UpdateRule::Ptr > (std::move (that.value));
        break;

      case 100: // UsingDefinition
        value.move< UsingDefinition::Ptr > (std::move (that.value));
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
        value.move< ValueLiteral::Ptr > (std::move (that.value));
        break;

      case 173: // VariableBinding
        value.move< VariableBinding::Ptr > (std::move (that.value));
        break;

      case 172: // VariableBindings
        value.move< VariableBindings::Ptr > (std::move (that.value));
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (std::move (that.value));
        break;

      case 159: // Parameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        value.move< VariableDefinitions::Ptr > (std::move (that.value));
        break;

      case 117: // WhileRule
        value.move< WhileRule::Ptr > (std::move (that.value));
        break;

      case 150: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
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
        value.copy< Ast::Token::Ptr > (YY_MOVE (that.value));
        break;

      case 175: // Attribute
        value.copy< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case 174: // Attributes
        value.copy< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case 176: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 151: // BasicType
        value.copy< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case 113: // BlockRule
        value.copy< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case 122: // CallExpression
        value.copy< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 116: // CallRule
        value.copy< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 133: // CardinalityExpression
        value.copy< CardinalityExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 108: // CaseLabel
        value.copy< Case::Ptr > (YY_MOVE (that.value));
        break;

      case 106: // CaseRule
        value.copy< CaseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 107: // CaseLabels
        value.copy< Cases::Ptr > (YY_MOVE (that.value));
        break;

      case 130: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 111: // ChooseRule
        value.copy< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 129: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 105: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 160: // MaybeDefined
        value.copy< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case 91: // AttributedDefinition
      case 92: // Definition
        value.copy< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case 90: // Definitions
        value.copy< Definitions::Ptr > (YY_MOVE (that.value));
        break;

      case 95: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 123: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 94: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 98: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 99: // Enumerators
        value.copy< Enumerators::Ptr > (YY_MOVE (that.value));
        break;

      case 132: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 119: // Term
      case 120: // SimpleOrClaspedTerm
      case 121: // OperatorExpression
        value.copy< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case 177: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 118: // Terms
        value.copy< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case 156: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case 110: // ForallRule
        value.copy< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 97: // FunctionDefinition
        value.copy< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Header
        value.copy< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 81: // "identifier"
      case 164: // Identifier
        value.copy< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case 165: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 126: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 93: // InitDefinition
        value.copy< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 163: // Initializer
        value.copy< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case 162: // Initializers
        value.copy< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case 161: // MaybeInitially
        value.copy< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case 101: // InvariantDefinition
        value.copy< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 112: // IterateRule
        value.copy< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 128: // LetExpression
        value.copy< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 109: // LetRule
        value.copy< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case 143: // ListLiteral
        value.copy< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 134: // Literal
        value.copy< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case 125: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 124: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 148: // Assignment
        value.copy< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 147: // Assignments
        value.copy< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case 144: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 146: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 153: // RecordType
        value.copy< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case 142: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 155: // RelationType
        value.copy< RelationType::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // Rule
        value.copy< Rule::Ptr > (YY_MOVE (that.value));
        break;

      case 96: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 102: // Rules
        value.copy< Rules::Ptr > (YY_MOVE (that.value));
        break;

      case 114: // SequenceRule
        value.copy< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case 104: // SkipRule
        value.copy< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case 88: // Specification
        value.copy< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case 154: // TemplateType
        value.copy< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case 145: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 152: // TupleType
        value.copy< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case 127: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 149: // Types
      case 157: // FunctionParameters
      case 158: // MaybeFunctionParameters
        value.copy< Types::Ptr > (YY_MOVE (that.value));
        break;

      case 135: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 131: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 115: // UpdateRule
        value.copy< UpdateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 100: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (YY_MOVE (that.value));
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
        value.copy< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 173: // VariableBinding
        value.copy< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case 172: // VariableBindings
        value.copy< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case 166: // Variable
      case 169: // TypedVariable
      case 170: // AttributedVariable
      case 171: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 159: // Parameters
      case 167: // AttributedVariables
      case 168: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 117: // WhileRule
        value.copy< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case 150: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
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

#if 201103L <= YY_CPLUSPLUS
  inline
  Parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  inline
  Parser::by_type::by_type (const by_type& that)
    : type (that.type)
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
  Parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }

  inline
  Parser::token_type
  Parser::by_type::token () const YY_NOEXCEPT
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
    return token_type (yytoken_number_[type]);
  }

#line 50 "../../obj/src/GrammarParser.y" // lalr1.cc:401
} // libcasm_fe
#line 5435 "GrammarParser.tab.h" // lalr1.cc:401




#endif // !YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
