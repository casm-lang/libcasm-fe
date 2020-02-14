// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

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
// "%code requires" blocks.
#line 63 "../../obj/src/GrammarParser.y"

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
    #include <libcasm-fe/Exception>
    #include <libcasm-fe/Logger>

    #include <libstdhl/SourceLocation>

    using namespace libcasm_fe;
    using namespace Ast;

    #define YY_NULLPTR nullptr

#line 71 "GrammarParser.tab.h"

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
#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
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

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
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

#line 50 "../../obj/src/GrammarParser.y"
namespace libcasm_fe {
#line 206 "GrammarParser.tab.h"




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
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {
      YY_ASSERT (!yytypeid_);
    }

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      YY_ASSERT (!yytypeid_);
      YY_ASSERT (sizeof (T) <= size);
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
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == typeid (T));
      YY_ASSERT (sizeof (T) <= size);
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
      YY_ASSERT (yytypeid_);
      YY_ASSERT (*yytypeid_ == *that.yytypeid_);
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
      // "import"
      // "function"
      // "defined"
      // "seq"
      // "endseq"
      // "par"
      // "endpar"
      // "skip"
      // "let"
      // "local"
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
      // AttributedLocalFunctionDefinition
      // LocalFunctionDefinition
      char dummy31[sizeof (FunctionDefinition::Ptr)];

      // LocalFunctionDefinitions
      char dummy32[sizeof (FunctionDefinitions::Ptr)];

      // Header
      char dummy33[sizeof (HeaderDefinition::Ptr)];

      // "identifier"
      // Identifier
      char dummy34[sizeof (Identifier::Ptr)];

      // IdentifierPath
      char dummy35[sizeof (IdentifierPath::Ptr)];

      // ImportDefinition
      char dummy36[sizeof (ImportDefinition::Ptr)];

      // IndirectCallExpression
      char dummy37[sizeof (IndirectCallExpression::Ptr)];

      // InitDefinition
      char dummy38[sizeof (InitDefinition::Ptr)];

      // Initializer
      char dummy39[sizeof (Initializer::Ptr)];

      // Initializers
      char dummy40[sizeof (Initializers::Ptr)];

      // MaybeInitially
      char dummy41[sizeof (Initially::Ptr)];

      // InvariantDefinition
      char dummy42[sizeof (InvariantDefinition::Ptr)];

      // IterateRule
      char dummy43[sizeof (IterateRule::Ptr)];

      // LetExpression
      char dummy44[sizeof (LetExpression::Ptr)];

      // LetRule
      char dummy45[sizeof (LetRule::Ptr)];

      // ListLiteral
      char dummy46[sizeof (ListLiteral::Ptr)];

      // Literal
      char dummy47[sizeof (Literal::Ptr)];

      // LiteralCallExpression
      char dummy48[sizeof (LiteralCallExpression::Ptr)];

      // LocalRule
      char dummy49[sizeof (LocalRule::Ptr)];

      // MethodCallExpression
      char dummy50[sizeof (MethodCallExpression::Ptr)];

      // Assignment
      char dummy51[sizeof (NamedExpression::Ptr)];

      // Assignments
      char dummy52[sizeof (NamedExpressions::Ptr)];

      // RangeLiteral
      char dummy53[sizeof (RangeLiteral::Ptr)];

      // RecordLiteral
      char dummy54[sizeof (RecordLiteral::Ptr)];

      // RecordType
      char dummy55[sizeof (RecordType::Ptr)];

      // ReferenceLiteral
      char dummy56[sizeof (ReferenceLiteral::Ptr)];

      // RelationType
      char dummy57[sizeof (RelationType::Ptr)];

      // Rule
      char dummy58[sizeof (Rule::Ptr)];

      // RuleDefinition
      char dummy59[sizeof (RuleDefinition::Ptr)];

      // Rules
      char dummy60[sizeof (Rules::Ptr)];

      // SequenceRule
      char dummy61[sizeof (SequenceRule::Ptr)];

      // SkipRule
      char dummy62[sizeof (SkipRule::Ptr)];

      // Specification
      char dummy63[sizeof (Specification::Ptr)];

      // TemplateType
      char dummy64[sizeof (TemplateType::Ptr)];

      // TupleLiteral
      char dummy65[sizeof (TupleLiteral::Ptr)];

      // TupleType
      char dummy66[sizeof (TupleType::Ptr)];

      // TypeCastingExpression
      char dummy67[sizeof (TypeCastingExpression::Ptr)];

      // Types
      // FunctionParameters
      // MaybeFunctionParameters
      char dummy68[sizeof (Types::Ptr)];

      // UndefinedLiteral
      char dummy69[sizeof (UndefLiteral::Ptr)];

      // UniversalQuantifierExpression
      char dummy70[sizeof (UniversalQuantifierExpression::Ptr)];

      // UpdateRule
      char dummy71[sizeof (UpdateRule::Ptr)];

      // UsingDefinition
      char dummy72[sizeof (UsingDefinition::Ptr)];

      // UsingPathDefinition
      char dummy73[sizeof (UsingPathDefinition::Ptr)];

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
      char dummy74[sizeof (ValueLiteral::Ptr)];

      // VariableBinding
      char dummy75[sizeof (VariableBinding::Ptr)];

      // VariableBindings
      char dummy76[sizeof (VariableBindings::Ptr)];

      // Variable
      // TypedVariable
      // AttributedVariable
      // TypedAttributedVariable
      char dummy77[sizeof (VariableDefinition::Ptr)];

      // Parameters
      // AttributedVariables
      // TypedVariables
      char dummy78[sizeof (VariableDefinitions::Ptr)];

      // WhileRule
      char dummy79[sizeof (WhileRule::Ptr)];

      // Type
      char dummy80[sizeof (libcasm_fe::Ast::Type::Ptr)];
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
        IMPORT = 265,
        FUNCTION = 266,
        DEFINED = 267,
        SEQ = 268,
        ENDSEQ = 269,
        PAR = 270,
        ENDPAR = 271,
        SKIP = 272,
        LET = 273,
        LOCAL = 274,
        IN = 275,
        FORALL = 276,
        CHOOSE = 277,
        ITERATE = 278,
        DO = 279,
        IF = 280,
        THEN = 281,
        ELSE = 282,
        CASE = 283,
        OF = 284,
        DEFAULT = 285,
        HOLDS = 286,
        EXISTS = 287,
        WITH = 288,
        AS = 289,
        WHILE = 290,
        UNDEF = 291,
        FALSE = 292,
        TRUE = 293,
        AND = 294,
        OR = 295,
        XOR = 296,
        IMPLIES = 297,
        NOT = 298,
        PLUS = 299,
        MINUS = 300,
        EQUAL = 301,
        LPAREN = 302,
        RPAREN = 303,
        LSQPAREN = 304,
        RSQPAREN = 305,
        LCURPAREN = 306,
        RCURPAREN = 307,
        COLON = 308,
        DOUBLECOLON = 309,
        UNDERLINE = 310,
        VERTICAL_BAR = 311,
        AT = 312,
        COMMA = 313,
        LESSER = 314,
        GREATER = 315,
        ASTERIX = 316,
        SLASH = 317,
        PERCENT = 318,
        CARET = 319,
        MARK = 320,
        DOTDOT = 321,
        DOT = 322,
        MAPS = 323,
        ARROW = 324,
        UPDATE = 325,
        NEQUAL = 326,
        LESSEQ = 327,
        GREATEREQ = 328,
        SEQ_BRACKET = 329,
        ENDSEQ_BRACKET = 330,
        BINARY = 331,
        HEXADECIMAL = 332,
        INTEGER = 333,
        RATIONAL = 334,
        DECIMAL = 335,
        STRING = 336,
        IDENTIFIER = 337,
        BASIC_TYPE = 338,
        CALL = 339,
        UPLUS = 340,
        UMINUS = 341,
        CALL_WITHOUT_ARGS = 342
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef signed char token_number_type;

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
      basic_symbol (typename Base::kind_type t, FunctionDefinitions::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const FunctionDefinitions::Ptr& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, ImportDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ImportDefinition::Ptr& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, LocalRule::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const LocalRule::Ptr& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, UsingPathDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const UsingPathDefinition::Ptr& v, const location_type& l)
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
      case 10: // "import"
      case 11: // "function"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "local"
      case 20: // "in"
      case 21: // "forall"
      case 22: // "choose"
      case 23: // "iterate"
      case 24: // "do"
      case 25: // "if"
      case 26: // "then"
      case 27: // "else"
      case 28: // "case"
      case 29: // "of"
      case 30: // "default"
      case 31: // "holds"
      case 32: // "exists"
      case 33: // "with"
      case 34: // "as"
      case 35: // "while"
      case 36: // "undef"
      case 37: // "false"
      case 38: // "true"
      case 39: // "and"
      case 40: // "or"
      case 41: // "xor"
      case 42: // "implies"
      case 43: // "not"
      case 44: // "+"
      case 45: // "-"
      case 46: // "="
      case 47: // "("
      case 48: // ")"
      case 49: // "["
      case 50: // "]"
      case 51: // "{"
      case 52: // "}"
      case 53: // ":"
      case 54: // "::"
      case 55: // "_"
      case 56: // "|"
      case 57: // "@"
      case 58: // ","
      case 59: // "<"
      case 60: // ">"
      case 61: // "*"
      case 62: // "/"
      case 63: // "%"
      case 64: // "^"
      case 65: // "'"
      case 66: // ".."
      case 67: // "."
      case 68: // "->"
      case 69: // "=>"
      case 70: // ":="
      case 71: // "!="
      case 72: // "<="
      case 73: // ">="
      case 74: // "{|"
      case 75: // "|}"
        value.template destroy< Ast::Token::Ptr > ();
        break;

      case 182: // Attribute
        value.template destroy< Attribute::Ptr > ();
        break;

      case 181: // Attributes
        value.template destroy< Attributes::Ptr > ();
        break;

      case 183: // BasicAttribute
        value.template destroy< BasicAttribute::Ptr > ();
        break;

      case 155: // BasicType
        value.template destroy< BasicType::Ptr > ();
        break;

      case 117: // BlockRule
        value.template destroy< BlockRule::Ptr > ();
        break;

      case 126: // CallExpression
        value.template destroy< CallExpression::Ptr > ();
        break;

      case 120: // CallRule
        value.template destroy< CallRule::Ptr > ();
        break;

      case 137: // CardinalityExpression
        value.template destroy< CardinalityExpression::Ptr > ();
        break;

      case 111: // CaseLabel
        value.template destroy< Case::Ptr > ();
        break;

      case 109: // CaseRule
        value.template destroy< CaseRule::Ptr > ();
        break;

      case 110: // CaseLabels
        value.template destroy< Cases::Ptr > ();
        break;

      case 134: // ChooseExpression
        value.template destroy< ChooseExpression::Ptr > ();
        break;

      case 115: // ChooseRule
        value.template destroy< ChooseRule::Ptr > ();
        break;

      case 133: // ConditionalExpression
        value.template destroy< ConditionalExpression::Ptr > ();
        break;

      case 108: // ConditionalRule
        value.template destroy< ConditionalRule::Ptr > ();
        break;

      case 164: // MaybeDefined
        value.template destroy< Defined::Ptr > ();
        break;

      case 92: // AttributedDefinition
      case 93: // Definition
        value.template destroy< Definition::Ptr > ();
        break;

      case 91: // Definitions
        value.template destroy< Definitions::Ptr > ();
        break;

      case 96: // DerivedDefinition
        value.template destroy< DerivedDefinition::Ptr > ();
        break;

      case 127: // DirectCallExpression
        value.template destroy< DirectCallExpression::Ptr > ();
        break;

      case 95: // EnumerationDefinition
        value.template destroy< EnumerationDefinition::Ptr > ();
        break;

      case 99: // EnumeratorDefinition
        value.template destroy< EnumeratorDefinition::Ptr > ();
        break;

      case 100: // Enumerators
        value.template destroy< Enumerators::Ptr > ();
        break;

      case 136: // ExistentialQuantifierExpression
        value.template destroy< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 123: // Term
      case 124: // SimpleOrClaspedTerm
      case 125: // OperatorExpression
        value.template destroy< Expression::Ptr > ();
        break;

      case 184: // ExpressionAttribute
        value.template destroy< ExpressionAttribute::Ptr > ();
        break;

      case 122: // Terms
        value.template destroy< Expressions::Ptr > ();
        break;

      case 160: // FixedSizedType
        value.template destroy< FixedSizedType::Ptr > ();
        break;

      case 114: // ForallRule
        value.template destroy< ForallRule::Ptr > ();
        break;

      case 98: // FunctionDefinition
      case 179: // AttributedLocalFunctionDefinition
      case 180: // LocalFunctionDefinition
        value.template destroy< FunctionDefinition::Ptr > ();
        break;

      case 178: // LocalFunctionDefinitions
        value.template destroy< FunctionDefinitions::Ptr > ();
        break;

      case 90: // Header
        value.template destroy< HeaderDefinition::Ptr > ();
        break;

      case 82: // "identifier"
      case 168: // Identifier
        value.template destroy< Identifier::Ptr > ();
        break;

      case 169: // IdentifierPath
        value.template destroy< IdentifierPath::Ptr > ();
        break;

      case 104: // ImportDefinition
        value.template destroy< ImportDefinition::Ptr > ();
        break;

      case 130: // IndirectCallExpression
        value.template destroy< IndirectCallExpression::Ptr > ();
        break;

      case 94: // InitDefinition
        value.template destroy< InitDefinition::Ptr > ();
        break;

      case 167: // Initializer
        value.template destroy< Initializer::Ptr > ();
        break;

      case 166: // Initializers
        value.template destroy< Initializers::Ptr > ();
        break;

      case 165: // MaybeInitially
        value.template destroy< Initially::Ptr > ();
        break;

      case 103: // InvariantDefinition
        value.template destroy< InvariantDefinition::Ptr > ();
        break;

      case 116: // IterateRule
        value.template destroy< IterateRule::Ptr > ();
        break;

      case 132: // LetExpression
        value.template destroy< LetExpression::Ptr > ();
        break;

      case 112: // LetRule
        value.template destroy< LetRule::Ptr > ();
        break;

      case 147: // ListLiteral
        value.template destroy< ListLiteral::Ptr > ();
        break;

      case 138: // Literal
        value.template destroy< Literal::Ptr > ();
        break;

      case 129: // LiteralCallExpression
        value.template destroy< LiteralCallExpression::Ptr > ();
        break;

      case 113: // LocalRule
        value.template destroy< LocalRule::Ptr > ();
        break;

      case 128: // MethodCallExpression
        value.template destroy< MethodCallExpression::Ptr > ();
        break;

      case 152: // Assignment
        value.template destroy< NamedExpression::Ptr > ();
        break;

      case 151: // Assignments
        value.template destroy< NamedExpressions::Ptr > ();
        break;

      case 148: // RangeLiteral
        value.template destroy< RangeLiteral::Ptr > ();
        break;

      case 150: // RecordLiteral
        value.template destroy< RecordLiteral::Ptr > ();
        break;

      case 157: // RecordType
        value.template destroy< RecordType::Ptr > ();
        break;

      case 146: // ReferenceLiteral
        value.template destroy< ReferenceLiteral::Ptr > ();
        break;

      case 159: // RelationType
        value.template destroy< RelationType::Ptr > ();
        break;

      case 106: // Rule
        value.template destroy< Rule::Ptr > ();
        break;

      case 97: // RuleDefinition
        value.template destroy< RuleDefinition::Ptr > ();
        break;

      case 105: // Rules
        value.template destroy< Rules::Ptr > ();
        break;

      case 118: // SequenceRule
        value.template destroy< SequenceRule::Ptr > ();
        break;

      case 107: // SkipRule
        value.template destroy< SkipRule::Ptr > ();
        break;

      case 89: // Specification
        value.template destroy< Specification::Ptr > ();
        break;

      case 158: // TemplateType
        value.template destroy< TemplateType::Ptr > ();
        break;

      case 149: // TupleLiteral
        value.template destroy< TupleLiteral::Ptr > ();
        break;

      case 156: // TupleType
        value.template destroy< TupleType::Ptr > ();
        break;

      case 131: // TypeCastingExpression
        value.template destroy< TypeCastingExpression::Ptr > ();
        break;

      case 153: // Types
      case 161: // FunctionParameters
      case 162: // MaybeFunctionParameters
        value.template destroy< Types::Ptr > ();
        break;

      case 139: // UndefinedLiteral
        value.template destroy< UndefLiteral::Ptr > ();
        break;

      case 135: // UniversalQuantifierExpression
        value.template destroy< UniversalQuantifierExpression::Ptr > ();
        break;

      case 119: // UpdateRule
        value.template destroy< UpdateRule::Ptr > ();
        break;

      case 101: // UsingDefinition
        value.template destroy< UsingDefinition::Ptr > ();
        break;

      case 102: // UsingPathDefinition
        value.template destroy< UsingPathDefinition::Ptr > ();
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 140: // BooleanLiteral
      case 141: // IntegerLiteral
      case 142: // RationalLiteral
      case 143: // DecimalLiteral
      case 144: // BinaryLiteral
      case 145: // StringLiteral
        value.template destroy< ValueLiteral::Ptr > ();
        break;

      case 177: // VariableBinding
        value.template destroy< VariableBinding::Ptr > ();
        break;

      case 176: // VariableBindings
        value.template destroy< VariableBindings::Ptr > ();
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        value.template destroy< VariableDefinition::Ptr > ();
        break;

      case 163: // Parameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        value.template destroy< VariableDefinitions::Ptr > ();
        break;

      case 121: // WhileRule
        value.template destroy< WhileRule::Ptr > ();
        break;

      case 154: // Type
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
        YY_ASSERT (tok == token::END || tok == token::BASIC_TYPE || tok == token::CALL || tok == token::UPLUS || tok == token::UMINUS || tok == token::CALL_WITHOUT_ARGS);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YY_ASSERT (tok == token::END || tok == token::BASIC_TYPE || tok == token::CALL || tok == token::UPLUS || tok == token::UMINUS || tok == token::CALL_WITHOUT_ARGS);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Ast::Token::Ptr v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::CASM || tok == token::INIT || tok == token::DERIVED || tok == token::ENUMERATION || tok == token::RULE || tok == token::USING || tok == token::INVARIANT || tok == token::IMPORT || tok == token::FUNCTION || tok == token::DEFINED || tok == token::SEQ || tok == token::ENDSEQ || tok == token::PAR || tok == token::ENDPAR || tok == token::SKIP || tok == token::LET || tok == token::LOCAL || tok == token::IN || tok == token::FORALL || tok == token::CHOOSE || tok == token::ITERATE || tok == token::DO || tok == token::IF || tok == token::THEN || tok == token::ELSE || tok == token::CASE || tok == token::OF || tok == token::DEFAULT || tok == token::HOLDS || tok == token::EXISTS || tok == token::WITH || tok == token::AS || tok == token::WHILE || tok == token::UNDEF || tok == token::FALSE || tok == token::TRUE || tok == token::AND || tok == token::OR || tok == token::XOR || tok == token::IMPLIES || tok == token::NOT || tok == token::PLUS || tok == token::MINUS || tok == token::EQUAL || tok == token::LPAREN || tok == token::RPAREN || tok == token::LSQPAREN || tok == token::RSQPAREN || tok == token::LCURPAREN || tok == token::RCURPAREN || tok == token::COLON || tok == token::DOUBLECOLON || tok == token::UNDERLINE || tok == token::VERTICAL_BAR || tok == token::AT || tok == token::COMMA || tok == token::LESSER || tok == token::GREATER || tok == token::ASTERIX || tok == token::SLASH || tok == token::PERCENT || tok == token::CARET || tok == token::MARK || tok == token::DOTDOT || tok == token::DOT || tok == token::MAPS || tok == token::ARROW || tok == token::UPDATE || tok == token::NEQUAL || tok == token::LESSEQ || tok == token::GREATEREQ || tok == token::SEQ_BRACKET || tok == token::ENDSEQ_BRACKET);
      }
#else
      symbol_type (int tok, const Ast::Token::Ptr& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::CASM || tok == token::INIT || tok == token::DERIVED || tok == token::ENUMERATION || tok == token::RULE || tok == token::USING || tok == token::INVARIANT || tok == token::IMPORT || tok == token::FUNCTION || tok == token::DEFINED || tok == token::SEQ || tok == token::ENDSEQ || tok == token::PAR || tok == token::ENDPAR || tok == token::SKIP || tok == token::LET || tok == token::LOCAL || tok == token::IN || tok == token::FORALL || tok == token::CHOOSE || tok == token::ITERATE || tok == token::DO || tok == token::IF || tok == token::THEN || tok == token::ELSE || tok == token::CASE || tok == token::OF || tok == token::DEFAULT || tok == token::HOLDS || tok == token::EXISTS || tok == token::WITH || tok == token::AS || tok == token::WHILE || tok == token::UNDEF || tok == token::FALSE || tok == token::TRUE || tok == token::AND || tok == token::OR || tok == token::XOR || tok == token::IMPLIES || tok == token::NOT || tok == token::PLUS || tok == token::MINUS || tok == token::EQUAL || tok == token::LPAREN || tok == token::RPAREN || tok == token::LSQPAREN || tok == token::RSQPAREN || tok == token::LCURPAREN || tok == token::RCURPAREN || tok == token::COLON || tok == token::DOUBLECOLON || tok == token::UNDERLINE || tok == token::VERTICAL_BAR || tok == token::AT || tok == token::COMMA || tok == token::LESSER || tok == token::GREATER || tok == token::ASTERIX || tok == token::SLASH || tok == token::PERCENT || tok == token::CARET || tok == token::MARK || tok == token::DOTDOT || tok == token::DOT || tok == token::MAPS || tok == token::ARROW || tok == token::UPDATE || tok == token::NEQUAL || tok == token::LESSEQ || tok == token::GREATEREQ || tok == token::SEQ_BRACKET || tok == token::ENDSEQ_BRACKET);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Identifier::Ptr v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::IDENTIFIER);
      }
#else
      symbol_type (int tok, const Identifier::Ptr& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::IDENTIFIER);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, ValueLiteral::Ptr v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::BINARY || tok == token::HEXADECIMAL || tok == token::INTEGER || tok == token::RATIONAL || tok == token::DECIMAL || tok == token::STRING);
      }
#else
      symbol_type (int tok, const ValueLiteral::Ptr& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::BINARY || tok == token::HEXADECIMAL || tok == token::INTEGER || tok == token::RATIONAL || tok == token::DECIMAL || tok == token::STRING);
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
      make_IMPORT (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::IMPORT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IMPORT (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::IMPORT, v, l);
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
      make_LOCAL (Ast::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LOCAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LOCAL (const Ast::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LOCAL, v, l);
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

    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const short yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    /// In theory \a t should be a token_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static token_number_type yytranslate_ (int t);

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
    static const signed char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
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
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

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

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
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
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
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
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
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
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      std::ptrdiff_t
      ssize () const YY_NOEXCEPT
      {
        return std::ptrdiff_t (size ());
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
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
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

    /// Some specific tokens.
    static const token_number_type yy_error_token_ = 1;
    static const token_number_type yy_undef_token_ = 2;

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 2685,     ///< Last index in yytable_.
      yynnts_ = 97,  ///< Number of nonterminal symbols.
      yyfinal_ = 13, ///< Termination state number.
      yyntokens_ = 88  ///< Number of tokens.
    };


    // User arguments.
    Logger& m_log;
    Lexer& m_lexer;
    Specification& m_specification;
  };

  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
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
      85,    86,    87
    };
    const int user_token_number_max_ = 342;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
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
      case 10: // "import"
      case 11: // "function"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "local"
      case 20: // "in"
      case 21: // "forall"
      case 22: // "choose"
      case 23: // "iterate"
      case 24: // "do"
      case 25: // "if"
      case 26: // "then"
      case 27: // "else"
      case 28: // "case"
      case 29: // "of"
      case 30: // "default"
      case 31: // "holds"
      case 32: // "exists"
      case 33: // "with"
      case 34: // "as"
      case 35: // "while"
      case 36: // "undef"
      case 37: // "false"
      case 38: // "true"
      case 39: // "and"
      case 40: // "or"
      case 41: // "xor"
      case 42: // "implies"
      case 43: // "not"
      case 44: // "+"
      case 45: // "-"
      case 46: // "="
      case 47: // "("
      case 48: // ")"
      case 49: // "["
      case 50: // "]"
      case 51: // "{"
      case 52: // "}"
      case 53: // ":"
      case 54: // "::"
      case 55: // "_"
      case 56: // "|"
      case 57: // "@"
      case 58: // ","
      case 59: // "<"
      case 60: // ">"
      case 61: // "*"
      case 62: // "/"
      case 63: // "%"
      case 64: // "^"
      case 65: // "'"
      case 66: // ".."
      case 67: // "."
      case 68: // "->"
      case 69: // "=>"
      case 70: // ":="
      case 71: // "!="
      case 72: // "<="
      case 73: // ">="
      case 74: // "{|"
      case 75: // "|}"
        value.move< Ast::Token::Ptr > (std::move (that.value));
        break;

      case 182: // Attribute
        value.move< Attribute::Ptr > (std::move (that.value));
        break;

      case 181: // Attributes
        value.move< Attributes::Ptr > (std::move (that.value));
        break;

      case 183: // BasicAttribute
        value.move< BasicAttribute::Ptr > (std::move (that.value));
        break;

      case 155: // BasicType
        value.move< BasicType::Ptr > (std::move (that.value));
        break;

      case 117: // BlockRule
        value.move< BlockRule::Ptr > (std::move (that.value));
        break;

      case 126: // CallExpression
        value.move< CallExpression::Ptr > (std::move (that.value));
        break;

      case 120: // CallRule
        value.move< CallRule::Ptr > (std::move (that.value));
        break;

      case 137: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (std::move (that.value));
        break;

      case 111: // CaseLabel
        value.move< Case::Ptr > (std::move (that.value));
        break;

      case 109: // CaseRule
        value.move< CaseRule::Ptr > (std::move (that.value));
        break;

      case 110: // CaseLabels
        value.move< Cases::Ptr > (std::move (that.value));
        break;

      case 134: // ChooseExpression
        value.move< ChooseExpression::Ptr > (std::move (that.value));
        break;

      case 115: // ChooseRule
        value.move< ChooseRule::Ptr > (std::move (that.value));
        break;

      case 133: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (std::move (that.value));
        break;

      case 108: // ConditionalRule
        value.move< ConditionalRule::Ptr > (std::move (that.value));
        break;

      case 164: // MaybeDefined
        value.move< Defined::Ptr > (std::move (that.value));
        break;

      case 92: // AttributedDefinition
      case 93: // Definition
        value.move< Definition::Ptr > (std::move (that.value));
        break;

      case 91: // Definitions
        value.move< Definitions::Ptr > (std::move (that.value));
        break;

      case 96: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (std::move (that.value));
        break;

      case 127: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (std::move (that.value));
        break;

      case 95: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (std::move (that.value));
        break;

      case 99: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (std::move (that.value));
        break;

      case 100: // Enumerators
        value.move< Enumerators::Ptr > (std::move (that.value));
        break;

      case 136: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (std::move (that.value));
        break;

      case 123: // Term
      case 124: // SimpleOrClaspedTerm
      case 125: // OperatorExpression
        value.move< Expression::Ptr > (std::move (that.value));
        break;

      case 184: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (std::move (that.value));
        break;

      case 122: // Terms
        value.move< Expressions::Ptr > (std::move (that.value));
        break;

      case 160: // FixedSizedType
        value.move< FixedSizedType::Ptr > (std::move (that.value));
        break;

      case 114: // ForallRule
        value.move< ForallRule::Ptr > (std::move (that.value));
        break;

      case 98: // FunctionDefinition
      case 179: // AttributedLocalFunctionDefinition
      case 180: // LocalFunctionDefinition
        value.move< FunctionDefinition::Ptr > (std::move (that.value));
        break;

      case 178: // LocalFunctionDefinitions
        value.move< FunctionDefinitions::Ptr > (std::move (that.value));
        break;

      case 90: // Header
        value.move< HeaderDefinition::Ptr > (std::move (that.value));
        break;

      case 82: // "identifier"
      case 168: // Identifier
        value.move< Identifier::Ptr > (std::move (that.value));
        break;

      case 169: // IdentifierPath
        value.move< IdentifierPath::Ptr > (std::move (that.value));
        break;

      case 104: // ImportDefinition
        value.move< ImportDefinition::Ptr > (std::move (that.value));
        break;

      case 130: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (std::move (that.value));
        break;

      case 94: // InitDefinition
        value.move< InitDefinition::Ptr > (std::move (that.value));
        break;

      case 167: // Initializer
        value.move< Initializer::Ptr > (std::move (that.value));
        break;

      case 166: // Initializers
        value.move< Initializers::Ptr > (std::move (that.value));
        break;

      case 165: // MaybeInitially
        value.move< Initially::Ptr > (std::move (that.value));
        break;

      case 103: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (std::move (that.value));
        break;

      case 116: // IterateRule
        value.move< IterateRule::Ptr > (std::move (that.value));
        break;

      case 132: // LetExpression
        value.move< LetExpression::Ptr > (std::move (that.value));
        break;

      case 112: // LetRule
        value.move< LetRule::Ptr > (std::move (that.value));
        break;

      case 147: // ListLiteral
        value.move< ListLiteral::Ptr > (std::move (that.value));
        break;

      case 138: // Literal
        value.move< Literal::Ptr > (std::move (that.value));
        break;

      case 129: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (std::move (that.value));
        break;

      case 113: // LocalRule
        value.move< LocalRule::Ptr > (std::move (that.value));
        break;

      case 128: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (std::move (that.value));
        break;

      case 152: // Assignment
        value.move< NamedExpression::Ptr > (std::move (that.value));
        break;

      case 151: // Assignments
        value.move< NamedExpressions::Ptr > (std::move (that.value));
        break;

      case 148: // RangeLiteral
        value.move< RangeLiteral::Ptr > (std::move (that.value));
        break;

      case 150: // RecordLiteral
        value.move< RecordLiteral::Ptr > (std::move (that.value));
        break;

      case 157: // RecordType
        value.move< RecordType::Ptr > (std::move (that.value));
        break;

      case 146: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (std::move (that.value));
        break;

      case 159: // RelationType
        value.move< RelationType::Ptr > (std::move (that.value));
        break;

      case 106: // Rule
        value.move< Rule::Ptr > (std::move (that.value));
        break;

      case 97: // RuleDefinition
        value.move< RuleDefinition::Ptr > (std::move (that.value));
        break;

      case 105: // Rules
        value.move< Rules::Ptr > (std::move (that.value));
        break;

      case 118: // SequenceRule
        value.move< SequenceRule::Ptr > (std::move (that.value));
        break;

      case 107: // SkipRule
        value.move< SkipRule::Ptr > (std::move (that.value));
        break;

      case 89: // Specification
        value.move< Specification::Ptr > (std::move (that.value));
        break;

      case 158: // TemplateType
        value.move< TemplateType::Ptr > (std::move (that.value));
        break;

      case 149: // TupleLiteral
        value.move< TupleLiteral::Ptr > (std::move (that.value));
        break;

      case 156: // TupleType
        value.move< TupleType::Ptr > (std::move (that.value));
        break;

      case 131: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (std::move (that.value));
        break;

      case 153: // Types
      case 161: // FunctionParameters
      case 162: // MaybeFunctionParameters
        value.move< Types::Ptr > (std::move (that.value));
        break;

      case 139: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (std::move (that.value));
        break;

      case 135: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (std::move (that.value));
        break;

      case 119: // UpdateRule
        value.move< UpdateRule::Ptr > (std::move (that.value));
        break;

      case 101: // UsingDefinition
        value.move< UsingDefinition::Ptr > (std::move (that.value));
        break;

      case 102: // UsingPathDefinition
        value.move< UsingPathDefinition::Ptr > (std::move (that.value));
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 140: // BooleanLiteral
      case 141: // IntegerLiteral
      case 142: // RationalLiteral
      case 143: // DecimalLiteral
      case 144: // BinaryLiteral
      case 145: // StringLiteral
        value.move< ValueLiteral::Ptr > (std::move (that.value));
        break;

      case 177: // VariableBinding
        value.move< VariableBinding::Ptr > (std::move (that.value));
        break;

      case 176: // VariableBindings
        value.move< VariableBindings::Ptr > (std::move (that.value));
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (std::move (that.value));
        break;

      case 163: // Parameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        value.move< VariableDefinitions::Ptr > (std::move (that.value));
        break;

      case 121: // WhileRule
        value.move< WhileRule::Ptr > (std::move (that.value));
        break;

      case 154: // Type
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
      case 10: // "import"
      case 11: // "function"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "local"
      case 20: // "in"
      case 21: // "forall"
      case 22: // "choose"
      case 23: // "iterate"
      case 24: // "do"
      case 25: // "if"
      case 26: // "then"
      case 27: // "else"
      case 28: // "case"
      case 29: // "of"
      case 30: // "default"
      case 31: // "holds"
      case 32: // "exists"
      case 33: // "with"
      case 34: // "as"
      case 35: // "while"
      case 36: // "undef"
      case 37: // "false"
      case 38: // "true"
      case 39: // "and"
      case 40: // "or"
      case 41: // "xor"
      case 42: // "implies"
      case 43: // "not"
      case 44: // "+"
      case 45: // "-"
      case 46: // "="
      case 47: // "("
      case 48: // ")"
      case 49: // "["
      case 50: // "]"
      case 51: // "{"
      case 52: // "}"
      case 53: // ":"
      case 54: // "::"
      case 55: // "_"
      case 56: // "|"
      case 57: // "@"
      case 58: // ","
      case 59: // "<"
      case 60: // ">"
      case 61: // "*"
      case 62: // "/"
      case 63: // "%"
      case 64: // "^"
      case 65: // "'"
      case 66: // ".."
      case 67: // "."
      case 68: // "->"
      case 69: // "=>"
      case 70: // ":="
      case 71: // "!="
      case 72: // "<="
      case 73: // ">="
      case 74: // "{|"
      case 75: // "|}"
        value.copy< Ast::Token::Ptr > (YY_MOVE (that.value));
        break;

      case 182: // Attribute
        value.copy< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case 181: // Attributes
        value.copy< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case 183: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 155: // BasicType
        value.copy< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case 117: // BlockRule
        value.copy< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case 126: // CallExpression
        value.copy< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 120: // CallRule
        value.copy< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 137: // CardinalityExpression
        value.copy< CardinalityExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 111: // CaseLabel
        value.copy< Case::Ptr > (YY_MOVE (that.value));
        break;

      case 109: // CaseRule
        value.copy< CaseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 110: // CaseLabels
        value.copy< Cases::Ptr > (YY_MOVE (that.value));
        break;

      case 134: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 115: // ChooseRule
        value.copy< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case 133: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 108: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 164: // MaybeDefined
        value.copy< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case 92: // AttributedDefinition
      case 93: // Definition
        value.copy< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case 91: // Definitions
        value.copy< Definitions::Ptr > (YY_MOVE (that.value));
        break;

      case 96: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 127: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 95: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 99: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 100: // Enumerators
        value.copy< Enumerators::Ptr > (YY_MOVE (that.value));
        break;

      case 136: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 123: // Term
      case 124: // SimpleOrClaspedTerm
      case 125: // OperatorExpression
        value.copy< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case 184: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case 122: // Terms
        value.copy< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case 160: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case 114: // ForallRule
        value.copy< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case 98: // FunctionDefinition
      case 179: // AttributedLocalFunctionDefinition
      case 180: // LocalFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 178: // LocalFunctionDefinitions
        value.copy< FunctionDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 90: // Header
        value.copy< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 82: // "identifier"
      case 168: // Identifier
        value.copy< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case 169: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case 104: // ImportDefinition
        value.copy< ImportDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 130: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 94: // InitDefinition
        value.copy< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 167: // Initializer
        value.copy< Initializer::Ptr > (YY_MOVE (that.value));
        break;

      case 166: // Initializers
        value.copy< Initializers::Ptr > (YY_MOVE (that.value));
        break;

      case 165: // MaybeInitially
        value.copy< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case 103: // InvariantDefinition
        value.copy< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 116: // IterateRule
        value.copy< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 132: // LetExpression
        value.copy< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 112: // LetRule
        value.copy< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case 147: // ListLiteral
        value.copy< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 138: // Literal
        value.copy< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case 129: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 113: // LocalRule
        value.copy< LocalRule::Ptr > (YY_MOVE (that.value));
        break;

      case 128: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 152: // Assignment
        value.copy< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 151: // Assignments
        value.copy< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case 148: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 150: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 157: // RecordType
        value.copy< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case 146: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 159: // RelationType
        value.copy< RelationType::Ptr > (YY_MOVE (that.value));
        break;

      case 106: // Rule
        value.copy< Rule::Ptr > (YY_MOVE (that.value));
        break;

      case 97: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 105: // Rules
        value.copy< Rules::Ptr > (YY_MOVE (that.value));
        break;

      case 118: // SequenceRule
        value.copy< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case 107: // SkipRule
        value.copy< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case 89: // Specification
        value.copy< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case 158: // TemplateType
        value.copy< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case 149: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 156: // TupleType
        value.copy< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case 131: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 153: // Types
      case 161: // FunctionParameters
      case 162: // MaybeFunctionParameters
        value.copy< Types::Ptr > (YY_MOVE (that.value));
        break;

      case 139: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 135: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case 119: // UpdateRule
        value.copy< UpdateRule::Ptr > (YY_MOVE (that.value));
        break;

      case 101: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 102: // UsingPathDefinition
        value.copy< UsingPathDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 140: // BooleanLiteral
      case 141: // IntegerLiteral
      case 142: // RationalLiteral
      case 143: // DecimalLiteral
      case 144: // BinaryLiteral
      case 145: // StringLiteral
        value.copy< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case 177: // VariableBinding
        value.copy< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case 176: // VariableBindings
        value.copy< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case 163: // Parameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case 121: // WhileRule
        value.copy< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case 154: // Type
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
      case 10: // "import"
      case 11: // "function"
      case 12: // "defined"
      case 13: // "seq"
      case 14: // "endseq"
      case 15: // "par"
      case 16: // "endpar"
      case 17: // "skip"
      case 18: // "let"
      case 19: // "local"
      case 20: // "in"
      case 21: // "forall"
      case 22: // "choose"
      case 23: // "iterate"
      case 24: // "do"
      case 25: // "if"
      case 26: // "then"
      case 27: // "else"
      case 28: // "case"
      case 29: // "of"
      case 30: // "default"
      case 31: // "holds"
      case 32: // "exists"
      case 33: // "with"
      case 34: // "as"
      case 35: // "while"
      case 36: // "undef"
      case 37: // "false"
      case 38: // "true"
      case 39: // "and"
      case 40: // "or"
      case 41: // "xor"
      case 42: // "implies"
      case 43: // "not"
      case 44: // "+"
      case 45: // "-"
      case 46: // "="
      case 47: // "("
      case 48: // ")"
      case 49: // "["
      case 50: // "]"
      case 51: // "{"
      case 52: // "}"
      case 53: // ":"
      case 54: // "::"
      case 55: // "_"
      case 56: // "|"
      case 57: // "@"
      case 58: // ","
      case 59: // "<"
      case 60: // ">"
      case 61: // "*"
      case 62: // "/"
      case 63: // "%"
      case 64: // "^"
      case 65: // "'"
      case 66: // ".."
      case 67: // "."
      case 68: // "->"
      case 69: // "=>"
      case 70: // ":="
      case 71: // "!="
      case 72: // "<="
      case 73: // ">="
      case 74: // "{|"
      case 75: // "|}"
        value.move< Ast::Token::Ptr > (YY_MOVE (s.value));
        break;

      case 182: // Attribute
        value.move< Attribute::Ptr > (YY_MOVE (s.value));
        break;

      case 181: // Attributes
        value.move< Attributes::Ptr > (YY_MOVE (s.value));
        break;

      case 183: // BasicAttribute
        value.move< BasicAttribute::Ptr > (YY_MOVE (s.value));
        break;

      case 155: // BasicType
        value.move< BasicType::Ptr > (YY_MOVE (s.value));
        break;

      case 117: // BlockRule
        value.move< BlockRule::Ptr > (YY_MOVE (s.value));
        break;

      case 126: // CallExpression
        value.move< CallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 120: // CallRule
        value.move< CallRule::Ptr > (YY_MOVE (s.value));
        break;

      case 137: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 111: // CaseLabel
        value.move< Case::Ptr > (YY_MOVE (s.value));
        break;

      case 109: // CaseRule
        value.move< CaseRule::Ptr > (YY_MOVE (s.value));
        break;

      case 110: // CaseLabels
        value.move< Cases::Ptr > (YY_MOVE (s.value));
        break;

      case 134: // ChooseExpression
        value.move< ChooseExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 115: // ChooseRule
        value.move< ChooseRule::Ptr > (YY_MOVE (s.value));
        break;

      case 133: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 108: // ConditionalRule
        value.move< ConditionalRule::Ptr > (YY_MOVE (s.value));
        break;

      case 164: // MaybeDefined
        value.move< Defined::Ptr > (YY_MOVE (s.value));
        break;

      case 92: // AttributedDefinition
      case 93: // Definition
        value.move< Definition::Ptr > (YY_MOVE (s.value));
        break;

      case 91: // Definitions
        value.move< Definitions::Ptr > (YY_MOVE (s.value));
        break;

      case 96: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 127: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 95: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 99: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 100: // Enumerators
        value.move< Enumerators::Ptr > (YY_MOVE (s.value));
        break;

      case 136: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 123: // Term
      case 124: // SimpleOrClaspedTerm
      case 125: // OperatorExpression
        value.move< Expression::Ptr > (YY_MOVE (s.value));
        break;

      case 184: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (YY_MOVE (s.value));
        break;

      case 122: // Terms
        value.move< Expressions::Ptr > (YY_MOVE (s.value));
        break;

      case 160: // FixedSizedType
        value.move< FixedSizedType::Ptr > (YY_MOVE (s.value));
        break;

      case 114: // ForallRule
        value.move< ForallRule::Ptr > (YY_MOVE (s.value));
        break;

      case 98: // FunctionDefinition
      case 179: // AttributedLocalFunctionDefinition
      case 180: // LocalFunctionDefinition
        value.move< FunctionDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 178: // LocalFunctionDefinitions
        value.move< FunctionDefinitions::Ptr > (YY_MOVE (s.value));
        break;

      case 90: // Header
        value.move< HeaderDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 82: // "identifier"
      case 168: // Identifier
        value.move< Identifier::Ptr > (YY_MOVE (s.value));
        break;

      case 169: // IdentifierPath
        value.move< IdentifierPath::Ptr > (YY_MOVE (s.value));
        break;

      case 104: // ImportDefinition
        value.move< ImportDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 130: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 94: // InitDefinition
        value.move< InitDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 167: // Initializer
        value.move< Initializer::Ptr > (YY_MOVE (s.value));
        break;

      case 166: // Initializers
        value.move< Initializers::Ptr > (YY_MOVE (s.value));
        break;

      case 165: // MaybeInitially
        value.move< Initially::Ptr > (YY_MOVE (s.value));
        break;

      case 103: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 116: // IterateRule
        value.move< IterateRule::Ptr > (YY_MOVE (s.value));
        break;

      case 132: // LetExpression
        value.move< LetExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 112: // LetRule
        value.move< LetRule::Ptr > (YY_MOVE (s.value));
        break;

      case 147: // ListLiteral
        value.move< ListLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 138: // Literal
        value.move< Literal::Ptr > (YY_MOVE (s.value));
        break;

      case 129: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 113: // LocalRule
        value.move< LocalRule::Ptr > (YY_MOVE (s.value));
        break;

      case 128: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 152: // Assignment
        value.move< NamedExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 151: // Assignments
        value.move< NamedExpressions::Ptr > (YY_MOVE (s.value));
        break;

      case 148: // RangeLiteral
        value.move< RangeLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 150: // RecordLiteral
        value.move< RecordLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 157: // RecordType
        value.move< RecordType::Ptr > (YY_MOVE (s.value));
        break;

      case 146: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 159: // RelationType
        value.move< RelationType::Ptr > (YY_MOVE (s.value));
        break;

      case 106: // Rule
        value.move< Rule::Ptr > (YY_MOVE (s.value));
        break;

      case 97: // RuleDefinition
        value.move< RuleDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 105: // Rules
        value.move< Rules::Ptr > (YY_MOVE (s.value));
        break;

      case 118: // SequenceRule
        value.move< SequenceRule::Ptr > (YY_MOVE (s.value));
        break;

      case 107: // SkipRule
        value.move< SkipRule::Ptr > (YY_MOVE (s.value));
        break;

      case 89: // Specification
        value.move< Specification::Ptr > (YY_MOVE (s.value));
        break;

      case 158: // TemplateType
        value.move< TemplateType::Ptr > (YY_MOVE (s.value));
        break;

      case 149: // TupleLiteral
        value.move< TupleLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 156: // TupleType
        value.move< TupleType::Ptr > (YY_MOVE (s.value));
        break;

      case 131: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 153: // Types
      case 161: // FunctionParameters
      case 162: // MaybeFunctionParameters
        value.move< Types::Ptr > (YY_MOVE (s.value));
        break;

      case 139: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 135: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (YY_MOVE (s.value));
        break;

      case 119: // UpdateRule
        value.move< UpdateRule::Ptr > (YY_MOVE (s.value));
        break;

      case 101: // UsingDefinition
        value.move< UsingDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 102: // UsingPathDefinition
        value.move< UsingPathDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 76: // "binary"
      case 77: // "hexadecimal"
      case 78: // "integer"
      case 79: // "rational"
      case 80: // "decimal"
      case 81: // "string"
      case 140: // BooleanLiteral
      case 141: // IntegerLiteral
      case 142: // RationalLiteral
      case 143: // DecimalLiteral
      case 144: // BinaryLiteral
      case 145: // StringLiteral
        value.move< ValueLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case 177: // VariableBinding
        value.move< VariableBinding::Ptr > (YY_MOVE (s.value));
        break;

      case 176: // VariableBindings
        value.move< VariableBindings::Ptr > (YY_MOVE (s.value));
        break;

      case 170: // Variable
      case 173: // TypedVariable
      case 174: // AttributedVariable
      case 175: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case 163: // Parameters
      case 171: // AttributedVariables
      case 172: // TypedVariables
        value.move< VariableDefinitions::Ptr > (YY_MOVE (s.value));
        break;

      case 121: // WhileRule
        value.move< WhileRule::Ptr > (YY_MOVE (s.value));
        break;

      case 154: // Type
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

#line 50 "../../obj/src/GrammarParser.y"
} // libcasm_fe
#line 5587 "GrammarParser.tab.h"





#endif // !YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
