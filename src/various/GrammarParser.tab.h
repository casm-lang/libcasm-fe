// A Bison parser, made by GNU Bison 3.7.6.

// Skeleton interface for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

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

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
# define YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
// "%code requires" blocks.
#line 64 "../../obj/src/GrammarParser.y"

    namespace libcasm_fe
    {
        class Lexer;
        class Logger;
    }

    #include <libcasm-fe/Specification>
    #include <libcasm-fe/cst/Definition>
    #include <libcasm-fe/cst/Declaration>
    #include <libcasm-fe/cst/Literal>
    #include <libcasm-fe/Exception>
    #include <libcasm-fe/TypeInfo>
    #include <libcasm-fe/Logger>

    #include <libstdhl/SourceLocation>

    using namespace libcasm_fe;
    using namespace CST;

    #define YY_NULLPTR nullptr

#line 72 "GrammarParser.tab.h"

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
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

#line 51 "../../obj/src/GrammarParser.y"
namespace libcasm_fe {
#line 207 "GrammarParser.tab.h"




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

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    semantic_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

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
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    semantic_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

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
      // Attribute
      char dummy1[sizeof (Attribute::Ptr)];

      // Attributes
      char dummy2[sizeof (Attributes::Ptr)];

      // BasicAttribute
      char dummy3[sizeof (BasicAttribute::Ptr)];

      // BasicType
      char dummy4[sizeof (BasicType::Ptr)];

      // BehaviorDefinition
      char dummy5[sizeof (BehaviorDefinition::Ptr)];

      // BlockRule
      char dummy6[sizeof (BlockRule::Ptr)];

      // BuiltinDefinition
      char dummy7[sizeof (BuiltinDefinition::Ptr)];

      // "CASM"
      // "init"
      // "derived"
      // "enumeration"
      // "rule"
      // "using"
      // "invariant"
      // "import"
      // "structure"
      // "behavior"
      // "implement"
      // "for"
      // "self"
      // "this"
      // "domain"
      // "builtin"
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
      // "->"
      // "=>"
      // ":="
      // "!="
      // "<="
      // ">="
      // "{|"
      // "|}"
      // "."
      // ".."
      // "..."
      char dummy8[sizeof (CST::Token::Ptr)];

      // CallExpression
      char dummy9[sizeof (CallExpression::Ptr)];

      // CallRule
      char dummy10[sizeof (CallRule::Ptr)];

      // CardinalityExpression
      char dummy11[sizeof (CardinalityExpression::Ptr)];

      // CaseLabel
      char dummy12[sizeof (Case::Ptr)];

      // CaseRule
      char dummy13[sizeof (CaseRule::Ptr)];

      // CaseLabels
      char dummy14[sizeof (Cases::Ptr)];

      // ChooseExpression
      char dummy15[sizeof (ChooseExpression::Ptr)];

      // ChooseRule
      char dummy16[sizeof (ChooseRule::Ptr)];

      // ConditionalExpression
      char dummy17[sizeof (ConditionalExpression::Ptr)];

      // ConditionalRule
      char dummy18[sizeof (ConditionalRule::Ptr)];

      // Declaration
      char dummy19[sizeof (Declaration::Ptr)];

      // MaybeDefined
      char dummy20[sizeof (Defined::Ptr)];

      // AttributedDefinition
      // Definition
      // BehaviorDefinitionElement
      // ImplementDefinitionElement
      // ImplementDefinitionAttributedElement
      char dummy21[sizeof (Definition::Ptr)];

      // Definitions
      // BehaviorDefinitionList
      // ImplementDefinitionList
      char dummy22[sizeof (Definitions::Ptr)];

      // DerivedDefinition
      char dummy23[sizeof (DerivedDefinition::Ptr)];

      // DirectCallExpression
      char dummy24[sizeof (DirectCallExpression::Ptr)];

      // DomainDefinition
      char dummy25[sizeof (DomainDefinition::Ptr)];

      // EnumerationDefinition
      char dummy26[sizeof (EnumerationDefinition::Ptr)];

      // EnumeratorDefinition
      char dummy27[sizeof (EnumeratorDefinition::Ptr)];

      // Enumerators
      char dummy28[sizeof (Enumerators::Ptr)];

      // ExistentialQuantifierExpression
      char dummy29[sizeof (ExistentialQuantifierExpression::Ptr)];

      // Term
      // Expression
      // OperatorExpression
      char dummy30[sizeof (Expression::Ptr)];

      // ExpressionAttribute
      char dummy31[sizeof (ExpressionAttribute::Ptr)];

      // Terms
      char dummy32[sizeof (Expressions::Ptr)];

      // FixedSizedType
      char dummy33[sizeof (FixedSizedType::Ptr)];

      // ForallRule
      char dummy34[sizeof (ForallRule::Ptr)];

      // FunctionDefinition
      // StructureDefinitionElement
      // AttributedLocalFunctionDefinition
      // LocalFunctionDefinition
      char dummy35[sizeof (FunctionDefinition::Ptr)];

      // StructureDefinitionList
      // LocalFunctionDefinitions
      char dummy36[sizeof (FunctionDefinitions::Ptr)];

      // Header
      char dummy37[sizeof (HeaderDefinition::Ptr)];

      // "identifier"
      // Identifier
      char dummy38[sizeof (Identifier::Ptr)];

      // IdentifierPath
      char dummy39[sizeof (IdentifierPath::Ptr)];

      // ImplementDefinition
      char dummy40[sizeof (ImplementDefinition::Ptr)];

      // ImportDefinition
      char dummy41[sizeof (ImportDefinition::Ptr)];

      // IndirectCallExpression
      char dummy42[sizeof (IndirectCallExpression::Ptr)];

      // InitDefinition
      char dummy43[sizeof (InitDefinition::Ptr)];

      // MaybeInitially
      char dummy44[sizeof (Initially::Ptr)];

      // InvariantDefinition
      char dummy45[sizeof (InvariantDefinition::Ptr)];

      // IterateRule
      char dummy46[sizeof (IterateRule::Ptr)];

      // LetExpression
      char dummy47[sizeof (LetExpression::Ptr)];

      // LetRule
      char dummy48[sizeof (LetRule::Ptr)];

      // ListLiteral
      char dummy49[sizeof (ListLiteral::Ptr)];

      // Literal
      char dummy50[sizeof (Literal::Ptr)];

      // LiteralCallExpression
      char dummy51[sizeof (LiteralCallExpression::Ptr)];

      // LocalRule
      char dummy52[sizeof (LocalRule::Ptr)];

      // MappedExpression
      char dummy53[sizeof (MappedExpression::Ptr)];

      // MappedExpressions
      char dummy54[sizeof (MappedExpressions::Ptr)];

      // MappingType
      char dummy55[sizeof (MappingType::Ptr)];

      // MethodCallExpression
      char dummy56[sizeof (MethodCallExpression::Ptr)];

      // Assignment
      char dummy57[sizeof (NamedExpression::Ptr)];

      // Assignments
      char dummy58[sizeof (NamedExpressions::Ptr)];

      // RangeLiteral
      char dummy59[sizeof (RangeLiteral::Ptr)];

      // RecordLiteral
      char dummy60[sizeof (RecordLiteral::Ptr)];

      // RecordType
      char dummy61[sizeof (RecordType::Ptr)];

      // ReferenceLiteral
      char dummy62[sizeof (ReferenceLiteral::Ptr)];

      // RelationType
      char dummy63[sizeof (RelationType::Ptr)];

      // Rule
      char dummy64[sizeof (Rule::Ptr)];

      // RuleDefinition
      char dummy65[sizeof (RuleDefinition::Ptr)];

      // Rules
      char dummy66[sizeof (Rules::Ptr)];

      // SequenceRule
      char dummy67[sizeof (SequenceRule::Ptr)];

      // SkipRule
      char dummy68[sizeof (SkipRule::Ptr)];

      // Specification
      char dummy69[sizeof (Specification::Ptr)];

      // StructureDefinition
      char dummy70[sizeof (StructureDefinition::Ptr)];

      // SymbolAttribute
      char dummy71[sizeof (SymbolAttribute::Ptr)];

      // TemplateType
      char dummy72[sizeof (TemplateType::Ptr)];

      // TupleLiteral
      char dummy73[sizeof (TupleLiteral::Ptr)];

      // TupleType
      char dummy74[sizeof (TupleType::Ptr)];

      // TypeCastingExpression
      char dummy75[sizeof (TypeCastingExpression::Ptr)];

      // Types
      // FunctionParameters
      // MaybeFunctionParameters
      char dummy76[sizeof (Types::Ptr)];

      // UndefinedLiteral
      char dummy77[sizeof (UndefLiteral::Ptr)];

      // UniversalQuantifierExpression
      char dummy78[sizeof (UniversalQuantifierExpression::Ptr)];

      // UpdateRule
      char dummy79[sizeof (UpdateRule::Ptr)];

      // UsingDefinition
      char dummy80[sizeof (UsingDefinition::Ptr)];

      // UsingPathDefinition
      char dummy81[sizeof (UsingPathDefinition::Ptr)];

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
      char dummy82[sizeof (ValueLiteral::Ptr)];

      // VaradicType
      char dummy83[sizeof (VaradicType::Ptr)];

      // VariableBinding
      char dummy84[sizeof (VariableBinding::Ptr)];

      // VariableBindings
      char dummy85[sizeof (VariableBindings::Ptr)];

      // Variable
      // TypedVariable
      // AttributedVariable
      // TypedAttributedVariable
      char dummy86[sizeof (VariableDefinition::Ptr)];

      // MethodParameters
      // Parameters
      // AttributedVariables
      // TypedVariables
      char dummy87[sizeof (VariableDefinitions::Ptr)];

      // WhileRule
      char dummy88[sizeof (WhileRule::Ptr)];

      // Type
      char dummy89[sizeof (libcasm_fe::CST::Type::Ptr)];
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

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    END = 0,                       // "end of file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    CASM = 258,                    // "CASM"
    INIT = 259,                    // "init"
    DERIVED = 260,                 // "derived"
    ENUMERATION = 261,             // "enumeration"
    RULE = 262,                    // "rule"
    USING = 263,                   // "using"
    INVARIANT = 264,               // "invariant"
    IMPORT = 265,                  // "import"
    STRUCTURE = 266,               // "structure"
    BEHAVIOR = 267,                // "behavior"
    IMPLEMENT = 268,               // "implement"
    FOR = 269,                     // "for"
    SELF = 270,                    // "self"
    THIS = 271,                    // "this"
    DOMAIN = 272,                  // "domain"
    BUILTIN = 273,                 // "builtin"
    FUNCTION = 274,                // "function"
    DEFINED = 275,                 // "defined"
    SEQ = 276,                     // "seq"
    ENDSEQ = 277,                  // "endseq"
    PAR = 278,                     // "par"
    ENDPAR = 279,                  // "endpar"
    SKIP = 280,                    // "skip"
    LET = 281,                     // "let"
    LOCAL = 282,                   // "local"
    IN = 283,                      // "in"
    FORALL = 284,                  // "forall"
    CHOOSE = 285,                  // "choose"
    ITERATE = 286,                 // "iterate"
    DO = 287,                      // "do"
    IF = 288,                      // "if"
    THEN = 289,                    // "then"
    ELSE = 290,                    // "else"
    CASE = 291,                    // "case"
    OF = 292,                      // "of"
    DEFAULT = 293,                 // "default"
    HOLDS = 294,                   // "holds"
    EXISTS = 295,                  // "exists"
    WITH = 296,                    // "with"
    AS = 297,                      // "as"
    WHILE = 298,                   // "while"
    UNDEF = 299,                   // "undef"
    FALSE = 300,                   // "false"
    TRUE = 301,                    // "true"
    AND = 302,                     // "and"
    OR = 303,                      // "or"
    XOR = 304,                     // "xor"
    IMPLIES = 305,                 // "implies"
    NOT = 306,                     // "not"
    PLUS = 307,                    // "+"
    MINUS = 308,                   // "-"
    EQUAL = 309,                   // "="
    LPAREN = 310,                  // "("
    RPAREN = 311,                  // ")"
    LSQPAREN = 312,                // "["
    RSQPAREN = 313,                // "]"
    LCURPAREN = 314,               // "{"
    RCURPAREN = 315,               // "}"
    COLON = 316,                   // ":"
    DOUBLECOLON = 317,             // "::"
    UNDERLINE = 318,               // "_"
    VERTICAL_BAR = 319,            // "|"
    AT = 320,                      // "@"
    COMMA = 321,                   // ","
    LESSER = 322,                  // "<"
    GREATER = 323,                 // ">"
    ASTERIX = 324,                 // "*"
    SLASH = 325,                   // "/"
    PERCENT = 326,                 // "%"
    CARET = 327,                   // "^"
    MARK = 328,                    // "'"
    MAPS = 329,                    // "->"
    ARROW = 330,                   // "=>"
    UPDATE = 331,                  // ":="
    NEQUAL = 332,                  // "!="
    LESSEQ = 333,                  // "<="
    GREATEREQ = 334,               // ">="
    SEQ_BRACKET = 335,             // "{|"
    ENDSEQ_BRACKET = 336,          // "|}"
    DOT = 337,                     // "."
    DOTDOT = 338,                  // ".."
    DOTDOTDOT = 339,               // "..."
    BINARY = 340,                  // "binary"
    HEXADECIMAL = 341,             // "hexadecimal"
    INTEGER = 342,                 // "integer"
    RATIONAL = 343,                // "rational"
    DECIMAL = 344,                 // "decimal"
    STRING = 345,                  // "string"
    IDENTIFIER = 346,              // "identifier"
    BASIC_TYPE = 347,              // BASIC_TYPE
    CALL = 348,                    // CALL
    UPLUS = 349,                   // UPLUS
    UMINUS = 350,                  // UMINUS
    CALL_WITHOUT_ARGS = 351        // CALL_WITHOUT_ARGS
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::yytokentype token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 97, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end of file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_CASM = 3,                              // "CASM"
        S_INIT = 4,                              // "init"
        S_DERIVED = 5,                           // "derived"
        S_ENUMERATION = 6,                       // "enumeration"
        S_RULE = 7,                              // "rule"
        S_USING = 8,                             // "using"
        S_INVARIANT = 9,                         // "invariant"
        S_IMPORT = 10,                           // "import"
        S_STRUCTURE = 11,                        // "structure"
        S_BEHAVIOR = 12,                         // "behavior"
        S_IMPLEMENT = 13,                        // "implement"
        S_FOR = 14,                              // "for"
        S_SELF = 15,                             // "self"
        S_THIS = 16,                             // "this"
        S_DOMAIN = 17,                           // "domain"
        S_BUILTIN = 18,                          // "builtin"
        S_FUNCTION = 19,                         // "function"
        S_DEFINED = 20,                          // "defined"
        S_SEQ = 21,                              // "seq"
        S_ENDSEQ = 22,                           // "endseq"
        S_PAR = 23,                              // "par"
        S_ENDPAR = 24,                           // "endpar"
        S_SKIP = 25,                             // "skip"
        S_LET = 26,                              // "let"
        S_LOCAL = 27,                            // "local"
        S_IN = 28,                               // "in"
        S_FORALL = 29,                           // "forall"
        S_CHOOSE = 30,                           // "choose"
        S_ITERATE = 31,                          // "iterate"
        S_DO = 32,                               // "do"
        S_IF = 33,                               // "if"
        S_THEN = 34,                             // "then"
        S_ELSE = 35,                             // "else"
        S_CASE = 36,                             // "case"
        S_OF = 37,                               // "of"
        S_DEFAULT = 38,                          // "default"
        S_HOLDS = 39,                            // "holds"
        S_EXISTS = 40,                           // "exists"
        S_WITH = 41,                             // "with"
        S_AS = 42,                               // "as"
        S_WHILE = 43,                            // "while"
        S_UNDEF = 44,                            // "undef"
        S_FALSE = 45,                            // "false"
        S_TRUE = 46,                             // "true"
        S_AND = 47,                              // "and"
        S_OR = 48,                               // "or"
        S_XOR = 49,                              // "xor"
        S_IMPLIES = 50,                          // "implies"
        S_NOT = 51,                              // "not"
        S_PLUS = 52,                             // "+"
        S_MINUS = 53,                            // "-"
        S_EQUAL = 54,                            // "="
        S_LPAREN = 55,                           // "("
        S_RPAREN = 56,                           // ")"
        S_LSQPAREN = 57,                         // "["
        S_RSQPAREN = 58,                         // "]"
        S_LCURPAREN = 59,                        // "{"
        S_RCURPAREN = 60,                        // "}"
        S_COLON = 61,                            // ":"
        S_DOUBLECOLON = 62,                      // "::"
        S_UNDERLINE = 63,                        // "_"
        S_VERTICAL_BAR = 64,                     // "|"
        S_AT = 65,                               // "@"
        S_COMMA = 66,                            // ","
        S_LESSER = 67,                           // "<"
        S_GREATER = 68,                          // ">"
        S_ASTERIX = 69,                          // "*"
        S_SLASH = 70,                            // "/"
        S_PERCENT = 71,                          // "%"
        S_CARET = 72,                            // "^"
        S_MARK = 73,                             // "'"
        S_MAPS = 74,                             // "->"
        S_ARROW = 75,                            // "=>"
        S_UPDATE = 76,                           // ":="
        S_NEQUAL = 77,                           // "!="
        S_LESSEQ = 78,                           // "<="
        S_GREATEREQ = 79,                        // ">="
        S_SEQ_BRACKET = 80,                      // "{|"
        S_ENDSEQ_BRACKET = 81,                   // "|}"
        S_DOT = 82,                              // "."
        S_DOTDOT = 83,                           // ".."
        S_DOTDOTDOT = 84,                        // "..."
        S_BINARY = 85,                           // "binary"
        S_HEXADECIMAL = 86,                      // "hexadecimal"
        S_INTEGER = 87,                          // "integer"
        S_RATIONAL = 88,                         // "rational"
        S_DECIMAL = 89,                          // "decimal"
        S_STRING = 90,                           // "string"
        S_IDENTIFIER = 91,                       // "identifier"
        S_BASIC_TYPE = 92,                       // BASIC_TYPE
        S_CALL = 93,                             // CALL
        S_UPLUS = 94,                            // UPLUS
        S_UMINUS = 95,                           // UMINUS
        S_CALL_WITHOUT_ARGS = 96,                // CALL_WITHOUT_ARGS
        S_YYACCEPT = 97,                         // $accept
        S_Specification = 98,                    // Specification
        S_Header = 99,                           // Header
        S_Definitions = 100,                     // Definitions
        S_AttributedDefinition = 101,            // AttributedDefinition
        S_Definition = 102,                      // Definition
        S_InitDefinition = 103,                  // InitDefinition
        S_EnumerationDefinition = 104,           // EnumerationDefinition
        S_DerivedDefinition = 105,               // DerivedDefinition
        S_RuleDefinition = 106,                  // RuleDefinition
        S_FunctionDefinition = 107,              // FunctionDefinition
        S_EnumeratorDefinition = 108,            // EnumeratorDefinition
        S_Enumerators = 109,                     // Enumerators
        S_UsingDefinition = 110,                 // UsingDefinition
        S_UsingPathDefinition = 111,             // UsingPathDefinition
        S_InvariantDefinition = 112,             // InvariantDefinition
        S_ImportDefinition = 113,                // ImportDefinition
        S_StructureDefinition = 114,             // StructureDefinition
        S_StructureDefinitionList = 115,         // StructureDefinitionList
        S_StructureDefinitionElement = 116,      // StructureDefinitionElement
        S_BehaviorDefinition = 117,              // BehaviorDefinition
        S_BehaviorDefinitionElement = 118,       // BehaviorDefinitionElement
        S_BehaviorDefinitionList = 119,          // BehaviorDefinitionList
        S_ImplementDefinition = 120,             // ImplementDefinition
        S_ImplementDefinitionList = 121,         // ImplementDefinitionList
        S_ImplementDefinitionElement = 122,      // ImplementDefinitionElement
        S_ImplementDefinitionAttributedElement = 123, // ImplementDefinitionAttributedElement
        S_DomainDefinition = 124,                // DomainDefinition
        S_BuiltinDefinition = 125,               // BuiltinDefinition
        S_Declaration = 126,                     // Declaration
        S_Rules = 127,                           // Rules
        S_Rule = 128,                            // Rule
        S_SkipRule = 129,                        // SkipRule
        S_ConditionalRule = 130,                 // ConditionalRule
        S_CaseRule = 131,                        // CaseRule
        S_CaseLabels = 132,                      // CaseLabels
        S_CaseLabel = 133,                       // CaseLabel
        S_LetRule = 134,                         // LetRule
        S_LocalRule = 135,                       // LocalRule
        S_ForallRule = 136,                      // ForallRule
        S_ChooseRule = 137,                      // ChooseRule
        S_IterateRule = 138,                     // IterateRule
        S_BlockRule = 139,                       // BlockRule
        S_SequenceRule = 140,                    // SequenceRule
        S_UpdateRule = 141,                      // UpdateRule
        S_CallRule = 142,                        // CallRule
        S_WhileRule = 143,                       // WhileRule
        S_Terms = 144,                           // Terms
        S_Term = 145,                            // Term
        S_Expression = 146,                      // Expression
        S_OperatorExpression = 147,              // OperatorExpression
        S_CallExpression = 148,                  // CallExpression
        S_DirectCallExpression = 149,            // DirectCallExpression
        S_MethodCallExpression = 150,            // MethodCallExpression
        S_LiteralCallExpression = 151,           // LiteralCallExpression
        S_IndirectCallExpression = 152,          // IndirectCallExpression
        S_TypeCastingExpression = 153,           // TypeCastingExpression
        S_LetExpression = 154,                   // LetExpression
        S_ConditionalExpression = 155,           // ConditionalExpression
        S_ChooseExpression = 156,                // ChooseExpression
        S_UniversalQuantifierExpression = 157,   // UniversalQuantifierExpression
        S_ExistentialQuantifierExpression = 158, // ExistentialQuantifierExpression
        S_CardinalityExpression = 159,           // CardinalityExpression
        S_Literal = 160,                         // Literal
        S_UndefinedLiteral = 161,                // UndefinedLiteral
        S_BooleanLiteral = 162,                  // BooleanLiteral
        S_IntegerLiteral = 163,                  // IntegerLiteral
        S_RationalLiteral = 164,                 // RationalLiteral
        S_DecimalLiteral = 165,                  // DecimalLiteral
        S_BinaryLiteral = 166,                   // BinaryLiteral
        S_StringLiteral = 167,                   // StringLiteral
        S_ReferenceLiteral = 168,                // ReferenceLiteral
        S_ListLiteral = 169,                     // ListLiteral
        S_RangeLiteral = 170,                    // RangeLiteral
        S_TupleLiteral = 171,                    // TupleLiteral
        S_RecordLiteral = 172,                   // RecordLiteral
        S_Assignments = 173,                     // Assignments
        S_Assignment = 174,                      // Assignment
        S_MappedExpressions = 175,               // MappedExpressions
        S_MappedExpression = 176,                // MappedExpression
        S_Types = 177,                           // Types
        S_Type = 178,                            // Type
        S_BasicType = 179,                       // BasicType
        S_TupleType = 180,                       // TupleType
        S_RecordType = 181,                      // RecordType
        S_TemplateType = 182,                    // TemplateType
        S_RelationType = 183,                    // RelationType
        S_FixedSizedType = 184,                  // FixedSizedType
        S_MappingType = 185,                     // MappingType
        S_VaradicType = 186,                     // VaradicType
        S_FunctionParameters = 187,              // FunctionParameters
        S_MaybeFunctionParameters = 188,         // MaybeFunctionParameters
        S_MethodParameters = 189,                // MethodParameters
        S_Parameters = 190,                      // Parameters
        S_MaybeDefined = 191,                    // MaybeDefined
        S_MaybeInitially = 192,                  // MaybeInitially
        S_Identifier = 193,                      // Identifier
        S_IdentifierPath = 194,                  // IdentifierPath
        S_Variable = 195,                        // Variable
        S_AttributedVariables = 196,             // AttributedVariables
        S_TypedVariables = 197,                  // TypedVariables
        S_TypedVariable = 198,                   // TypedVariable
        S_AttributedVariable = 199,              // AttributedVariable
        S_TypedAttributedVariable = 200,         // TypedAttributedVariable
        S_VariableBindings = 201,                // VariableBindings
        S_VariableBinding = 202,                 // VariableBinding
        S_LocalFunctionDefinitions = 203,        // LocalFunctionDefinitions
        S_AttributedLocalFunctionDefinition = 204, // AttributedLocalFunctionDefinition
        S_LocalFunctionDefinition = 205,         // LocalFunctionDefinition
        S_Attributes = 206,                      // Attributes
        S_Attribute = 207,                       // Attribute
        S_BasicAttribute = 208,                  // BasicAttribute
        S_SymbolAttribute = 209,                 // SymbolAttribute
        S_ExpressionAttribute = 210              // ExpressionAttribute
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
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
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
        , location (std::move (that.location))
      {
        switch (this->kind ())
    {
      case symbol_kind::S_Attribute: // Attribute
        value.move< Attribute::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Attributes: // Attributes
        value.move< Attributes::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_BasicAttribute: // BasicAttribute
        value.move< BasicAttribute::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_BasicType: // BasicType
        value.move< BasicType::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.move< BehaviorDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.move< BlockRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.move< BuiltinDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_BEHAVIOR: // "behavior"
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAIN: // "domain"
      case symbol_kind::S_BUILTIN: // "builtin"
      case symbol_kind::S_FUNCTION: // "function"
      case symbol_kind::S_DEFINED: // "defined"
      case symbol_kind::S_SEQ: // "seq"
      case symbol_kind::S_ENDSEQ: // "endseq"
      case symbol_kind::S_PAR: // "par"
      case symbol_kind::S_ENDPAR: // "endpar"
      case symbol_kind::S_SKIP: // "skip"
      case symbol_kind::S_LET: // "let"
      case symbol_kind::S_LOCAL: // "local"
      case symbol_kind::S_IN: // "in"
      case symbol_kind::S_FORALL: // "forall"
      case symbol_kind::S_CHOOSE: // "choose"
      case symbol_kind::S_ITERATE: // "iterate"
      case symbol_kind::S_DO: // "do"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_THEN: // "then"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_CASE: // "case"
      case symbol_kind::S_OF: // "of"
      case symbol_kind::S_DEFAULT: // "default"
      case symbol_kind::S_HOLDS: // "holds"
      case symbol_kind::S_EXISTS: // "exists"
      case symbol_kind::S_WITH: // "with"
      case symbol_kind::S_AS: // "as"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_UNDEF: // "undef"
      case symbol_kind::S_FALSE: // "false"
      case symbol_kind::S_TRUE: // "true"
      case symbol_kind::S_AND: // "and"
      case symbol_kind::S_OR: // "or"
      case symbol_kind::S_XOR: // "xor"
      case symbol_kind::S_IMPLIES: // "implies"
      case symbol_kind::S_NOT: // "not"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_EQUAL: // "="
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LSQPAREN: // "["
      case symbol_kind::S_RSQPAREN: // "]"
      case symbol_kind::S_LCURPAREN: // "{"
      case symbol_kind::S_RCURPAREN: // "}"
      case symbol_kind::S_COLON: // ":"
      case symbol_kind::S_DOUBLECOLON: // "::"
      case symbol_kind::S_UNDERLINE: // "_"
      case symbol_kind::S_VERTICAL_BAR: // "|"
      case symbol_kind::S_AT: // "@"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_LESSER: // "<"
      case symbol_kind::S_GREATER: // ">"
      case symbol_kind::S_ASTERIX: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_CARET: // "^"
      case symbol_kind::S_MARK: // "'"
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOTDOTDOT: // "..."
        value.move< CST::Token::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_CallExpression: // CallExpression
        value.move< CallExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_CallRule: // CallRule
        value.move< CallRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_CardinalityExpression: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_CaseLabel: // CaseLabel
        value.move< Case::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_CaseRule: // CaseRule
        value.move< CaseRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_CaseLabels: // CaseLabels
        value.move< Cases::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_ChooseExpression: // ChooseExpression
        value.move< ChooseExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_ChooseRule: // ChooseRule
        value.move< ChooseRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_ConditionalExpression: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_ConditionalRule: // ConditionalRule
        value.move< ConditionalRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Declaration: // Declaration
        value.move< Declaration::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.move< Defined::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_BehaviorDefinitionElement: // BehaviorDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
      case symbol_kind::S_ImplementDefinitionAttributedElement: // ImplementDefinitionAttributedElement
        value.move< Definition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_BehaviorDefinitionList: // BehaviorDefinitionList
      case symbol_kind::S_ImplementDefinitionList: // ImplementDefinitionList
        value.move< Definitions::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_DomainDefinition: // DomainDefinition
        value.move< DomainDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_EnumerationDefinition: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_EnumeratorDefinition: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Enumerators: // Enumerators
        value.move< Enumerators::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_ExistentialQuantifierExpression: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Term: // Term
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.move< Expression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Terms: // Terms
        value.move< Expressions::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_FixedSizedType: // FixedSizedType
        value.move< FixedSizedType::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_ForallRule: // ForallRule
        value.move< ForallRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_FunctionDefinition: // FunctionDefinition
      case symbol_kind::S_StructureDefinitionElement: // StructureDefinitionElement
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.move< FunctionDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_StructureDefinitionList: // StructureDefinitionList
      case symbol_kind::S_LocalFunctionDefinitions: // LocalFunctionDefinitions
        value.move< FunctionDefinitions::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Header: // Header
        value.move< HeaderDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_Identifier: // Identifier
        value.move< Identifier::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_IdentifierPath: // IdentifierPath
        value.move< IdentifierPath::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_ImplementDefinition: // ImplementDefinition
        value.move< ImplementDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_ImportDefinition: // ImportDefinition
        value.move< ImportDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_IndirectCallExpression: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_InitDefinition: // InitDefinition
        value.move< InitDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_MaybeInitially: // MaybeInitially
        value.move< Initially::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_InvariantDefinition: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_IterateRule: // IterateRule
        value.move< IterateRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_LetExpression: // LetExpression
        value.move< LetExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_LetRule: // LetRule
        value.move< LetRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_ListLiteral: // ListLiteral
        value.move< ListLiteral::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Literal: // Literal
        value.move< Literal::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_LiteralCallExpression: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_LocalRule: // LocalRule
        value.move< LocalRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_MappedExpression: // MappedExpression
        value.move< MappedExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_MappedExpressions: // MappedExpressions
        value.move< MappedExpressions::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_MappingType: // MappingType
        value.move< MappingType::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_MethodCallExpression: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Assignment: // Assignment
        value.move< NamedExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Assignments: // Assignments
        value.move< NamedExpressions::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_RangeLiteral: // RangeLiteral
        value.move< RangeLiteral::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_RecordLiteral: // RecordLiteral
        value.move< RecordLiteral::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_RecordType: // RecordType
        value.move< RecordType::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_ReferenceLiteral: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_RelationType: // RelationType
        value.move< RelationType::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Rule: // Rule
        value.move< Rule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_RuleDefinition: // RuleDefinition
        value.move< RuleDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Rules: // Rules
        value.move< Rules::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_SequenceRule: // SequenceRule
        value.move< SequenceRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_SkipRule: // SkipRule
        value.move< SkipRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Specification: // Specification
        value.move< Specification::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_StructureDefinition: // StructureDefinition
        value.move< StructureDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_SymbolAttribute: // SymbolAttribute
        value.move< SymbolAttribute::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_TemplateType: // TemplateType
        value.move< TemplateType::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_TupleLiteral: // TupleLiteral
        value.move< TupleLiteral::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_TupleType: // TupleType
        value.move< TupleType::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_TypeCastingExpression: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Types: // Types
      case symbol_kind::S_FunctionParameters: // FunctionParameters
      case symbol_kind::S_MaybeFunctionParameters: // MaybeFunctionParameters
        value.move< Types::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_UndefinedLiteral: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_UniversalQuantifierExpression: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_UpdateRule: // UpdateRule
        value.move< UpdateRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_UsingDefinition: // UsingDefinition
        value.move< UsingDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_UsingPathDefinition: // UsingPathDefinition
        value.move< UsingPathDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_BINARY: // "binary"
      case symbol_kind::S_HEXADECIMAL: // "hexadecimal"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_RATIONAL: // "rational"
      case symbol_kind::S_DECIMAL: // "decimal"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_BooleanLiteral: // BooleanLiteral
      case symbol_kind::S_IntegerLiteral: // IntegerLiteral
      case symbol_kind::S_RationalLiteral: // RationalLiteral
      case symbol_kind::S_DecimalLiteral: // DecimalLiteral
      case symbol_kind::S_BinaryLiteral: // BinaryLiteral
      case symbol_kind::S_StringLiteral: // StringLiteral
        value.move< ValueLiteral::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_VaradicType: // VaradicType
        value.move< VaradicType::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_VariableBinding: // VariableBinding
        value.move< VariableBinding::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_VariableBindings: // VariableBindings
        value.move< VariableBindings::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Variable: // Variable
      case symbol_kind::S_TypedVariable: // TypedVariable
      case symbol_kind::S_AttributedVariable: // AttributedVariable
      case symbol_kind::S_TypedAttributedVariable: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.move< VariableDefinitions::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.move< WhileRule::Ptr > (std::move (that.value));
        break;

      case symbol_kind::S_Type: // Type
        value.move< libcasm_fe::CST::Type::Ptr > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
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
      basic_symbol (typename Base::kind_type t, BehaviorDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const BehaviorDefinition::Ptr& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, BuiltinDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const BuiltinDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, CST::Token::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const CST::Token::Ptr& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, Declaration::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const Declaration::Ptr& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, DomainDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const DomainDefinition::Ptr& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, ImplementDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const ImplementDefinition::Ptr& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, MappedExpression::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const MappedExpression::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, MappedExpressions::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const MappedExpressions::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, MappingType::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const MappingType::Ptr& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, StructureDefinition::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const StructureDefinition::Ptr& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, SymbolAttribute::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const SymbolAttribute::Ptr& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, VaradicType::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const VaradicType::Ptr& v, const location_type& l)
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
      basic_symbol (typename Base::kind_type t, libcasm_fe::CST::Type::Ptr&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const libcasm_fe::CST::Type::Ptr& v, const location_type& l)
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
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_Attribute: // Attribute
        value.template destroy< Attribute::Ptr > ();
        break;

      case symbol_kind::S_Attributes: // Attributes
        value.template destroy< Attributes::Ptr > ();
        break;

      case symbol_kind::S_BasicAttribute: // BasicAttribute
        value.template destroy< BasicAttribute::Ptr > ();
        break;

      case symbol_kind::S_BasicType: // BasicType
        value.template destroy< BasicType::Ptr > ();
        break;

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.template destroy< BehaviorDefinition::Ptr > ();
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.template destroy< BlockRule::Ptr > ();
        break;

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.template destroy< BuiltinDefinition::Ptr > ();
        break;

      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_BEHAVIOR: // "behavior"
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAIN: // "domain"
      case symbol_kind::S_BUILTIN: // "builtin"
      case symbol_kind::S_FUNCTION: // "function"
      case symbol_kind::S_DEFINED: // "defined"
      case symbol_kind::S_SEQ: // "seq"
      case symbol_kind::S_ENDSEQ: // "endseq"
      case symbol_kind::S_PAR: // "par"
      case symbol_kind::S_ENDPAR: // "endpar"
      case symbol_kind::S_SKIP: // "skip"
      case symbol_kind::S_LET: // "let"
      case symbol_kind::S_LOCAL: // "local"
      case symbol_kind::S_IN: // "in"
      case symbol_kind::S_FORALL: // "forall"
      case symbol_kind::S_CHOOSE: // "choose"
      case symbol_kind::S_ITERATE: // "iterate"
      case symbol_kind::S_DO: // "do"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_THEN: // "then"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_CASE: // "case"
      case symbol_kind::S_OF: // "of"
      case symbol_kind::S_DEFAULT: // "default"
      case symbol_kind::S_HOLDS: // "holds"
      case symbol_kind::S_EXISTS: // "exists"
      case symbol_kind::S_WITH: // "with"
      case symbol_kind::S_AS: // "as"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_UNDEF: // "undef"
      case symbol_kind::S_FALSE: // "false"
      case symbol_kind::S_TRUE: // "true"
      case symbol_kind::S_AND: // "and"
      case symbol_kind::S_OR: // "or"
      case symbol_kind::S_XOR: // "xor"
      case symbol_kind::S_IMPLIES: // "implies"
      case symbol_kind::S_NOT: // "not"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_EQUAL: // "="
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LSQPAREN: // "["
      case symbol_kind::S_RSQPAREN: // "]"
      case symbol_kind::S_LCURPAREN: // "{"
      case symbol_kind::S_RCURPAREN: // "}"
      case symbol_kind::S_COLON: // ":"
      case symbol_kind::S_DOUBLECOLON: // "::"
      case symbol_kind::S_UNDERLINE: // "_"
      case symbol_kind::S_VERTICAL_BAR: // "|"
      case symbol_kind::S_AT: // "@"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_LESSER: // "<"
      case symbol_kind::S_GREATER: // ">"
      case symbol_kind::S_ASTERIX: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_CARET: // "^"
      case symbol_kind::S_MARK: // "'"
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOTDOTDOT: // "..."
        value.template destroy< CST::Token::Ptr > ();
        break;

      case symbol_kind::S_CallExpression: // CallExpression
        value.template destroy< CallExpression::Ptr > ();
        break;

      case symbol_kind::S_CallRule: // CallRule
        value.template destroy< CallRule::Ptr > ();
        break;

      case symbol_kind::S_CardinalityExpression: // CardinalityExpression
        value.template destroy< CardinalityExpression::Ptr > ();
        break;

      case symbol_kind::S_CaseLabel: // CaseLabel
        value.template destroy< Case::Ptr > ();
        break;

      case symbol_kind::S_CaseRule: // CaseRule
        value.template destroy< CaseRule::Ptr > ();
        break;

      case symbol_kind::S_CaseLabels: // CaseLabels
        value.template destroy< Cases::Ptr > ();
        break;

      case symbol_kind::S_ChooseExpression: // ChooseExpression
        value.template destroy< ChooseExpression::Ptr > ();
        break;

      case symbol_kind::S_ChooseRule: // ChooseRule
        value.template destroy< ChooseRule::Ptr > ();
        break;

      case symbol_kind::S_ConditionalExpression: // ConditionalExpression
        value.template destroy< ConditionalExpression::Ptr > ();
        break;

      case symbol_kind::S_ConditionalRule: // ConditionalRule
        value.template destroy< ConditionalRule::Ptr > ();
        break;

      case symbol_kind::S_Declaration: // Declaration
        value.template destroy< Declaration::Ptr > ();
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.template destroy< Defined::Ptr > ();
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_BehaviorDefinitionElement: // BehaviorDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
      case symbol_kind::S_ImplementDefinitionAttributedElement: // ImplementDefinitionAttributedElement
        value.template destroy< Definition::Ptr > ();
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_BehaviorDefinitionList: // BehaviorDefinitionList
      case symbol_kind::S_ImplementDefinitionList: // ImplementDefinitionList
        value.template destroy< Definitions::Ptr > ();
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.template destroy< DerivedDefinition::Ptr > ();
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.template destroy< DirectCallExpression::Ptr > ();
        break;

      case symbol_kind::S_DomainDefinition: // DomainDefinition
        value.template destroy< DomainDefinition::Ptr > ();
        break;

      case symbol_kind::S_EnumerationDefinition: // EnumerationDefinition
        value.template destroy< EnumerationDefinition::Ptr > ();
        break;

      case symbol_kind::S_EnumeratorDefinition: // EnumeratorDefinition
        value.template destroy< EnumeratorDefinition::Ptr > ();
        break;

      case symbol_kind::S_Enumerators: // Enumerators
        value.template destroy< Enumerators::Ptr > ();
        break;

      case symbol_kind::S_ExistentialQuantifierExpression: // ExistentialQuantifierExpression
        value.template destroy< ExistentialQuantifierExpression::Ptr > ();
        break;

      case symbol_kind::S_Term: // Term
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.template destroy< Expression::Ptr > ();
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.template destroy< ExpressionAttribute::Ptr > ();
        break;

      case symbol_kind::S_Terms: // Terms
        value.template destroy< Expressions::Ptr > ();
        break;

      case symbol_kind::S_FixedSizedType: // FixedSizedType
        value.template destroy< FixedSizedType::Ptr > ();
        break;

      case symbol_kind::S_ForallRule: // ForallRule
        value.template destroy< ForallRule::Ptr > ();
        break;

      case symbol_kind::S_FunctionDefinition: // FunctionDefinition
      case symbol_kind::S_StructureDefinitionElement: // StructureDefinitionElement
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.template destroy< FunctionDefinition::Ptr > ();
        break;

      case symbol_kind::S_StructureDefinitionList: // StructureDefinitionList
      case symbol_kind::S_LocalFunctionDefinitions: // LocalFunctionDefinitions
        value.template destroy< FunctionDefinitions::Ptr > ();
        break;

      case symbol_kind::S_Header: // Header
        value.template destroy< HeaderDefinition::Ptr > ();
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_Identifier: // Identifier
        value.template destroy< Identifier::Ptr > ();
        break;

      case symbol_kind::S_IdentifierPath: // IdentifierPath
        value.template destroy< IdentifierPath::Ptr > ();
        break;

      case symbol_kind::S_ImplementDefinition: // ImplementDefinition
        value.template destroy< ImplementDefinition::Ptr > ();
        break;

      case symbol_kind::S_ImportDefinition: // ImportDefinition
        value.template destroy< ImportDefinition::Ptr > ();
        break;

      case symbol_kind::S_IndirectCallExpression: // IndirectCallExpression
        value.template destroy< IndirectCallExpression::Ptr > ();
        break;

      case symbol_kind::S_InitDefinition: // InitDefinition
        value.template destroy< InitDefinition::Ptr > ();
        break;

      case symbol_kind::S_MaybeInitially: // MaybeInitially
        value.template destroy< Initially::Ptr > ();
        break;

      case symbol_kind::S_InvariantDefinition: // InvariantDefinition
        value.template destroy< InvariantDefinition::Ptr > ();
        break;

      case symbol_kind::S_IterateRule: // IterateRule
        value.template destroy< IterateRule::Ptr > ();
        break;

      case symbol_kind::S_LetExpression: // LetExpression
        value.template destroy< LetExpression::Ptr > ();
        break;

      case symbol_kind::S_LetRule: // LetRule
        value.template destroy< LetRule::Ptr > ();
        break;

      case symbol_kind::S_ListLiteral: // ListLiteral
        value.template destroy< ListLiteral::Ptr > ();
        break;

      case symbol_kind::S_Literal: // Literal
        value.template destroy< Literal::Ptr > ();
        break;

      case symbol_kind::S_LiteralCallExpression: // LiteralCallExpression
        value.template destroy< LiteralCallExpression::Ptr > ();
        break;

      case symbol_kind::S_LocalRule: // LocalRule
        value.template destroy< LocalRule::Ptr > ();
        break;

      case symbol_kind::S_MappedExpression: // MappedExpression
        value.template destroy< MappedExpression::Ptr > ();
        break;

      case symbol_kind::S_MappedExpressions: // MappedExpressions
        value.template destroy< MappedExpressions::Ptr > ();
        break;

      case symbol_kind::S_MappingType: // MappingType
        value.template destroy< MappingType::Ptr > ();
        break;

      case symbol_kind::S_MethodCallExpression: // MethodCallExpression
        value.template destroy< MethodCallExpression::Ptr > ();
        break;

      case symbol_kind::S_Assignment: // Assignment
        value.template destroy< NamedExpression::Ptr > ();
        break;

      case symbol_kind::S_Assignments: // Assignments
        value.template destroy< NamedExpressions::Ptr > ();
        break;

      case symbol_kind::S_RangeLiteral: // RangeLiteral
        value.template destroy< RangeLiteral::Ptr > ();
        break;

      case symbol_kind::S_RecordLiteral: // RecordLiteral
        value.template destroy< RecordLiteral::Ptr > ();
        break;

      case symbol_kind::S_RecordType: // RecordType
        value.template destroy< RecordType::Ptr > ();
        break;

      case symbol_kind::S_ReferenceLiteral: // ReferenceLiteral
        value.template destroy< ReferenceLiteral::Ptr > ();
        break;

      case symbol_kind::S_RelationType: // RelationType
        value.template destroy< RelationType::Ptr > ();
        break;

      case symbol_kind::S_Rule: // Rule
        value.template destroy< Rule::Ptr > ();
        break;

      case symbol_kind::S_RuleDefinition: // RuleDefinition
        value.template destroy< RuleDefinition::Ptr > ();
        break;

      case symbol_kind::S_Rules: // Rules
        value.template destroy< Rules::Ptr > ();
        break;

      case symbol_kind::S_SequenceRule: // SequenceRule
        value.template destroy< SequenceRule::Ptr > ();
        break;

      case symbol_kind::S_SkipRule: // SkipRule
        value.template destroy< SkipRule::Ptr > ();
        break;

      case symbol_kind::S_Specification: // Specification
        value.template destroy< Specification::Ptr > ();
        break;

      case symbol_kind::S_StructureDefinition: // StructureDefinition
        value.template destroy< StructureDefinition::Ptr > ();
        break;

      case symbol_kind::S_SymbolAttribute: // SymbolAttribute
        value.template destroy< SymbolAttribute::Ptr > ();
        break;

      case symbol_kind::S_TemplateType: // TemplateType
        value.template destroy< TemplateType::Ptr > ();
        break;

      case symbol_kind::S_TupleLiteral: // TupleLiteral
        value.template destroy< TupleLiteral::Ptr > ();
        break;

      case symbol_kind::S_TupleType: // TupleType
        value.template destroy< TupleType::Ptr > ();
        break;

      case symbol_kind::S_TypeCastingExpression: // TypeCastingExpression
        value.template destroy< TypeCastingExpression::Ptr > ();
        break;

      case symbol_kind::S_Types: // Types
      case symbol_kind::S_FunctionParameters: // FunctionParameters
      case symbol_kind::S_MaybeFunctionParameters: // MaybeFunctionParameters
        value.template destroy< Types::Ptr > ();
        break;

      case symbol_kind::S_UndefinedLiteral: // UndefinedLiteral
        value.template destroy< UndefLiteral::Ptr > ();
        break;

      case symbol_kind::S_UniversalQuantifierExpression: // UniversalQuantifierExpression
        value.template destroy< UniversalQuantifierExpression::Ptr > ();
        break;

      case symbol_kind::S_UpdateRule: // UpdateRule
        value.template destroy< UpdateRule::Ptr > ();
        break;

      case symbol_kind::S_UsingDefinition: // UsingDefinition
        value.template destroy< UsingDefinition::Ptr > ();
        break;

      case symbol_kind::S_UsingPathDefinition: // UsingPathDefinition
        value.template destroy< UsingPathDefinition::Ptr > ();
        break;

      case symbol_kind::S_BINARY: // "binary"
      case symbol_kind::S_HEXADECIMAL: // "hexadecimal"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_RATIONAL: // "rational"
      case symbol_kind::S_DECIMAL: // "decimal"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_BooleanLiteral: // BooleanLiteral
      case symbol_kind::S_IntegerLiteral: // IntegerLiteral
      case symbol_kind::S_RationalLiteral: // RationalLiteral
      case symbol_kind::S_DecimalLiteral: // DecimalLiteral
      case symbol_kind::S_BinaryLiteral: // BinaryLiteral
      case symbol_kind::S_StringLiteral: // StringLiteral
        value.template destroy< ValueLiteral::Ptr > ();
        break;

      case symbol_kind::S_VaradicType: // VaradicType
        value.template destroy< VaradicType::Ptr > ();
        break;

      case symbol_kind::S_VariableBinding: // VariableBinding
        value.template destroy< VariableBinding::Ptr > ();
        break;

      case symbol_kind::S_VariableBindings: // VariableBindings
        value.template destroy< VariableBindings::Ptr > ();
        break;

      case symbol_kind::S_Variable: // Variable
      case symbol_kind::S_TypedVariable: // TypedVariable
      case symbol_kind::S_AttributedVariable: // AttributedVariable
      case symbol_kind::S_TypedAttributedVariable: // TypedAttributedVariable
        value.template destroy< VariableDefinition::Ptr > ();
        break;

      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.template destroy< VariableDefinitions::Ptr > ();
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.template destroy< WhileRule::Ptr > ();
        break;

      case symbol_kind::S_Type: // Type
        value.template destroy< libcasm_fe::CST::Type::Ptr > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

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
    struct by_kind
    {
      /// Default constructor.
      by_kind ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that);
#endif

      /// Copy constructor.
      by_kind (const by_kind& that);

      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t);

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
#endif
      {
        YY_ASSERT (tok == token::END
                   || (token::YYerror <= tok && tok <= token::YYUNDEF)
                   || (token::BASIC_TYPE <= tok && tok <= token::CALL_WITHOUT_ARGS));
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, CST::Token::Ptr v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const CST::Token::Ptr& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT ((token::CASM <= tok && tok <= token::DOTDOTDOT));
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, Identifier::Ptr v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const Identifier::Ptr& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT (tok == token::IDENTIFIER);
      }
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, ValueLiteral::Ptr v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
#else
      symbol_type (int tok, const ValueLiteral::Ptr& v, const location_type& l)
        : super_type(token_type (tok), v, l)
#endif
      {
        YY_ASSERT ((token::BINARY <= tok && tok <= token::STRING));
      }
    };

    /// Build a parser object.
    Parser (Logger& m_log_yyarg, Lexer& m_lexer_yyarg, Specification& m_specification_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

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

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

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
      make_YYerror (location_type l)
      {
        return symbol_type (token::YYerror, std::move (l));
      }
#else
      static
      symbol_type
      make_YYerror (const location_type& l)
      {
        return symbol_type (token::YYerror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF (location_type l)
      {
        return symbol_type (token::YYUNDEF, std::move (l));
      }
#else
      static
      symbol_type
      make_YYUNDEF (const location_type& l)
      {
        return symbol_type (token::YYUNDEF, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASM (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::CASM, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CASM (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::CASM, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INIT (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::INIT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INIT (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::INIT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DERIVED (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DERIVED, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DERIVED (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DERIVED, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENUMERATION (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ENUMERATION, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ENUMERATION (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ENUMERATION, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RULE (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::RULE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RULE (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::RULE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_USING (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::USING, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_USING (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::USING, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INVARIANT (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::INVARIANT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_INVARIANT (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::INVARIANT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IMPORT (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::IMPORT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IMPORT (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::IMPORT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRUCTURE (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::STRUCTURE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_STRUCTURE (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::STRUCTURE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BEHAVIOR (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::BEHAVIOR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BEHAVIOR (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::BEHAVIOR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IMPLEMENT (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::IMPLEMENT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IMPLEMENT (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::IMPLEMENT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FOR (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::FOR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FOR (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::FOR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SELF (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::SELF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SELF (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::SELF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THIS (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::THIS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_THIS (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::THIS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOMAIN (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DOMAIN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DOMAIN (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DOMAIN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BUILTIN (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::BUILTIN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_BUILTIN (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::BUILTIN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FUNCTION (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::FUNCTION, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FUNCTION (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::FUNCTION, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEFINED (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DEFINED, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DEFINED (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DEFINED, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEQ (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::SEQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SEQ (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::SEQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENDSEQ (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ENDSEQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ENDSEQ (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ENDSEQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PAR (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::PAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PAR (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::PAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENDPAR (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ENDPAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ENDPAR (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ENDPAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SKIP (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::SKIP, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SKIP (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::SKIP, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LET (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LET, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LET (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LET, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LOCAL (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LOCAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LOCAL (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LOCAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IN (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::IN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IN (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::IN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FORALL (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::FORALL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FORALL (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::FORALL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CHOOSE (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::CHOOSE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CHOOSE (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::CHOOSE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ITERATE (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ITERATE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ITERATE (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ITERATE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DO (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DO, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DO (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DO, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::IF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IF (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::IF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_THEN (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::THEN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_THEN (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::THEN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ELSE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ELSE (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ELSE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CASE (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::CASE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CASE (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::CASE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OF (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::OF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OF (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::OF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DEFAULT (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DEFAULT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DEFAULT (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DEFAULT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_HOLDS (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::HOLDS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_HOLDS (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::HOLDS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EXISTS (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::EXISTS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EXISTS (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::EXISTS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WITH (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::WITH, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WITH (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::WITH, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AS (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::AS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AS (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::AS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::WHILE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_WHILE (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::WHILE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNDEF (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::UNDEF, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNDEF (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::UNDEF, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FALSE (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::FALSE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_FALSE (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::FALSE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRUE (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::TRUE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_TRUE (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::TRUE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::AND, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AND (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::AND, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::OR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_OR (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::OR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_XOR (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::XOR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_XOR (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::XOR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IMPLIES (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::IMPLIES, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_IMPLIES (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::IMPLIES, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::NOT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NOT (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::NOT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PLUS (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::PLUS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PLUS (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::PLUS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MINUS (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::MINUS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MINUS (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::MINUS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUAL (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::EQUAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_EQUAL (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::EQUAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LPAREN (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::RPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RPAREN (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::RPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LSQPAREN (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LSQPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LSQPAREN (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LSQPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RSQPAREN (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::RSQPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RSQPAREN (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::RSQPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LCURPAREN (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LCURPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LCURPAREN (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LCURPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RCURPAREN (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::RCURPAREN, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_RCURPAREN (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::RCURPAREN, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::COLON, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_COLON (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::COLON, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOUBLECOLON (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DOUBLECOLON, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DOUBLECOLON (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DOUBLECOLON, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UNDERLINE (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::UNDERLINE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UNDERLINE (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::UNDERLINE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VERTICAL_BAR (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::VERTICAL_BAR, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_VERTICAL_BAR (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::VERTICAL_BAR, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AT (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::AT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_AT (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::AT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::COMMA, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_COMMA (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::COMMA, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESSER (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LESSER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LESSER (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LESSER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATER (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::GREATER, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_GREATER (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::GREATER, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASTERIX (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ASTERIX, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ASTERIX (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ASTERIX, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SLASH (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::SLASH, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SLASH (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::SLASH, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_PERCENT (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::PERCENT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_PERCENT (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::PERCENT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CARET (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::CARET, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_CARET (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::CARET, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MARK (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::MARK, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MARK (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::MARK, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MAPS (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::MAPS, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_MAPS (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::MAPS, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARROW (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ARROW, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ARROW (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ARROW, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_UPDATE (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::UPDATE, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_UPDATE (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::UPDATE, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NEQUAL (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::NEQUAL, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_NEQUAL (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::NEQUAL, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESSEQ (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::LESSEQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_LESSEQ (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::LESSEQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATEREQ (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::GREATEREQ, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_GREATEREQ (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::GREATEREQ, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEQ_BRACKET (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::SEQ_BRACKET, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_SEQ_BRACKET (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::SEQ_BRACKET, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ENDSEQ_BRACKET (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::ENDSEQ_BRACKET, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_ENDSEQ_BRACKET (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::ENDSEQ_BRACKET, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOT (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DOT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DOT (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DOT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOTDOT (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DOTDOT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DOTDOT (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DOTDOT, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DOTDOTDOT (CST::Token::Ptr v, location_type l)
      {
        return symbol_type (token::DOTDOTDOT, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_DOTDOTDOT (const CST::Token::Ptr& v, const location_type& l)
      {
        return symbol_type (token::DOTDOTDOT, v, l);
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


    class context
    {
    public:
      context (const Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      const location_type& location () const YY_NOEXCEPT { return yyla_.location; }

      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
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

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static symbol_kind_type yytranslate_ (int t);

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const short yydefact_[];

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


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
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

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

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
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

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

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
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
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
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
      yylast_ = 3268,     ///< Last index in yytable_.
      yynnts_ = 114,  ///< Number of nonterminal symbols.
      yyfinal_ = 18 ///< Termination state number.
    };


    // User arguments.
    Logger& m_log;
    Lexer& m_lexer;
    Specification& m_specification;

  };

  inline
  Parser::symbol_kind_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
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
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96
    };
    // Last valid token kind.
    const int code_max = 351;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return YY_CAST (symbol_kind_type, translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->kind ())
    {
      case symbol_kind::S_Attribute: // Attribute
        value.copy< Attribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Attributes: // Attributes
        value.copy< Attributes::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BasicAttribute: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BasicType: // BasicType
        value.copy< BasicType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.copy< BehaviorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.copy< BlockRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.copy< BuiltinDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_BEHAVIOR: // "behavior"
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAIN: // "domain"
      case symbol_kind::S_BUILTIN: // "builtin"
      case symbol_kind::S_FUNCTION: // "function"
      case symbol_kind::S_DEFINED: // "defined"
      case symbol_kind::S_SEQ: // "seq"
      case symbol_kind::S_ENDSEQ: // "endseq"
      case symbol_kind::S_PAR: // "par"
      case symbol_kind::S_ENDPAR: // "endpar"
      case symbol_kind::S_SKIP: // "skip"
      case symbol_kind::S_LET: // "let"
      case symbol_kind::S_LOCAL: // "local"
      case symbol_kind::S_IN: // "in"
      case symbol_kind::S_FORALL: // "forall"
      case symbol_kind::S_CHOOSE: // "choose"
      case symbol_kind::S_ITERATE: // "iterate"
      case symbol_kind::S_DO: // "do"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_THEN: // "then"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_CASE: // "case"
      case symbol_kind::S_OF: // "of"
      case symbol_kind::S_DEFAULT: // "default"
      case symbol_kind::S_HOLDS: // "holds"
      case symbol_kind::S_EXISTS: // "exists"
      case symbol_kind::S_WITH: // "with"
      case symbol_kind::S_AS: // "as"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_UNDEF: // "undef"
      case symbol_kind::S_FALSE: // "false"
      case symbol_kind::S_TRUE: // "true"
      case symbol_kind::S_AND: // "and"
      case symbol_kind::S_OR: // "or"
      case symbol_kind::S_XOR: // "xor"
      case symbol_kind::S_IMPLIES: // "implies"
      case symbol_kind::S_NOT: // "not"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_EQUAL: // "="
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LSQPAREN: // "["
      case symbol_kind::S_RSQPAREN: // "]"
      case symbol_kind::S_LCURPAREN: // "{"
      case symbol_kind::S_RCURPAREN: // "}"
      case symbol_kind::S_COLON: // ":"
      case symbol_kind::S_DOUBLECOLON: // "::"
      case symbol_kind::S_UNDERLINE: // "_"
      case symbol_kind::S_VERTICAL_BAR: // "|"
      case symbol_kind::S_AT: // "@"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_LESSER: // "<"
      case symbol_kind::S_GREATER: // ">"
      case symbol_kind::S_ASTERIX: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_CARET: // "^"
      case symbol_kind::S_MARK: // "'"
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOTDOTDOT: // "..."
        value.copy< CST::Token::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CallExpression: // CallExpression
        value.copy< CallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CallRule: // CallRule
        value.copy< CallRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CardinalityExpression: // CardinalityExpression
        value.copy< CardinalityExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CaseLabel: // CaseLabel
        value.copy< Case::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CaseRule: // CaseRule
        value.copy< CaseRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_CaseLabels: // CaseLabels
        value.copy< Cases::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ChooseExpression: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ChooseRule: // ChooseRule
        value.copy< ChooseRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConditionalExpression: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ConditionalRule: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Declaration: // Declaration
        value.copy< Declaration::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.copy< Defined::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_BehaviorDefinitionElement: // BehaviorDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
      case symbol_kind::S_ImplementDefinitionAttributedElement: // ImplementDefinitionAttributedElement
        value.copy< Definition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_BehaviorDefinitionList: // BehaviorDefinitionList
      case symbol_kind::S_ImplementDefinitionList: // ImplementDefinitionList
        value.copy< Definitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_DomainDefinition: // DomainDefinition
        value.copy< DomainDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_EnumerationDefinition: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_EnumeratorDefinition: // EnumeratorDefinition
        value.copy< EnumeratorDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Enumerators: // Enumerators
        value.copy< Enumerators::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ExistentialQuantifierExpression: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Term: // Term
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.copy< Expression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Terms: // Terms
        value.copy< Expressions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FixedSizedType: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ForallRule: // ForallRule
        value.copy< ForallRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FunctionDefinition: // FunctionDefinition
      case symbol_kind::S_StructureDefinitionElement: // StructureDefinitionElement
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_StructureDefinitionList: // StructureDefinitionList
      case symbol_kind::S_LocalFunctionDefinitions: // LocalFunctionDefinitions
        value.copy< FunctionDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Header: // Header
        value.copy< HeaderDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_Identifier: // Identifier
        value.copy< Identifier::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IdentifierPath: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ImplementDefinition: // ImplementDefinition
        value.copy< ImplementDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ImportDefinition: // ImportDefinition
        value.copy< ImportDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IndirectCallExpression: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InitDefinition: // InitDefinition
        value.copy< InitDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MaybeInitially: // MaybeInitially
        value.copy< Initially::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_InvariantDefinition: // InvariantDefinition
        value.copy< InvariantDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_IterateRule: // IterateRule
        value.copy< IterateRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LetExpression: // LetExpression
        value.copy< LetExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LetRule: // LetRule
        value.copy< LetRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ListLiteral: // ListLiteral
        value.copy< ListLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Literal: // Literal
        value.copy< Literal::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LiteralCallExpression: // LiteralCallExpression
        value.copy< LiteralCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_LocalRule: // LocalRule
        value.copy< LocalRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MappedExpression: // MappedExpression
        value.copy< MappedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MappedExpressions: // MappedExpressions
        value.copy< MappedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MappingType: // MappingType
        value.copy< MappingType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MethodCallExpression: // MethodCallExpression
        value.copy< MethodCallExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Assignment: // Assignment
        value.copy< NamedExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Assignments: // Assignments
        value.copy< NamedExpressions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RangeLiteral: // RangeLiteral
        value.copy< RangeLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RecordLiteral: // RecordLiteral
        value.copy< RecordLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RecordType: // RecordType
        value.copy< RecordType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ReferenceLiteral: // ReferenceLiteral
        value.copy< ReferenceLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RelationType: // RelationType
        value.copy< RelationType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Rule: // Rule
        value.copy< Rule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_RuleDefinition: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Rules: // Rules
        value.copy< Rules::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SequenceRule: // SequenceRule
        value.copy< SequenceRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SkipRule: // SkipRule
        value.copy< SkipRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Specification: // Specification
        value.copy< Specification::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_StructureDefinition: // StructureDefinition
        value.copy< StructureDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_SymbolAttribute: // SymbolAttribute
        value.copy< SymbolAttribute::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TemplateType: // TemplateType
        value.copy< TemplateType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TupleLiteral: // TupleLiteral
        value.copy< TupleLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TupleType: // TupleType
        value.copy< TupleType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_TypeCastingExpression: // TypeCastingExpression
        value.copy< TypeCastingExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Types: // Types
      case symbol_kind::S_FunctionParameters: // FunctionParameters
      case symbol_kind::S_MaybeFunctionParameters: // MaybeFunctionParameters
        value.copy< Types::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UndefinedLiteral: // UndefinedLiteral
        value.copy< UndefLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UniversalQuantifierExpression: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UpdateRule: // UpdateRule
        value.copy< UpdateRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UsingDefinition: // UsingDefinition
        value.copy< UsingDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_UsingPathDefinition: // UsingPathDefinition
        value.copy< UsingPathDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BINARY: // "binary"
      case symbol_kind::S_HEXADECIMAL: // "hexadecimal"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_RATIONAL: // "rational"
      case symbol_kind::S_DECIMAL: // "decimal"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_BooleanLiteral: // BooleanLiteral
      case symbol_kind::S_IntegerLiteral: // IntegerLiteral
      case symbol_kind::S_RationalLiteral: // RationalLiteral
      case symbol_kind::S_DecimalLiteral: // DecimalLiteral
      case symbol_kind::S_BinaryLiteral: // BinaryLiteral
      case symbol_kind::S_StringLiteral: // StringLiteral
        value.copy< ValueLiteral::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VaradicType: // VaradicType
        value.copy< VaradicType::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VariableBinding: // VariableBinding
        value.copy< VariableBinding::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_VariableBindings: // VariableBindings
        value.copy< VariableBindings::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Variable: // Variable
      case symbol_kind::S_TypedVariable: // TypedVariable
      case symbol_kind::S_AttributedVariable: // AttributedVariable
      case symbol_kind::S_TypedAttributedVariable: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.copy< VariableDefinitions::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.copy< WhileRule::Ptr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_Type: // Type
        value.copy< libcasm_fe::CST::Type::Ptr > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_Attribute: // Attribute
        value.move< Attribute::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Attributes: // Attributes
        value.move< Attributes::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BasicAttribute: // BasicAttribute
        value.move< BasicAttribute::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BasicType: // BasicType
        value.move< BasicType::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BehaviorDefinition: // BehaviorDefinition
        value.move< BehaviorDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BlockRule: // BlockRule
        value.move< BlockRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BuiltinDefinition: // BuiltinDefinition
        value.move< BuiltinDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CASM: // "CASM"
      case symbol_kind::S_INIT: // "init"
      case symbol_kind::S_DERIVED: // "derived"
      case symbol_kind::S_ENUMERATION: // "enumeration"
      case symbol_kind::S_RULE: // "rule"
      case symbol_kind::S_USING: // "using"
      case symbol_kind::S_INVARIANT: // "invariant"
      case symbol_kind::S_IMPORT: // "import"
      case symbol_kind::S_STRUCTURE: // "structure"
      case symbol_kind::S_BEHAVIOR: // "behavior"
      case symbol_kind::S_IMPLEMENT: // "implement"
      case symbol_kind::S_FOR: // "for"
      case symbol_kind::S_SELF: // "self"
      case symbol_kind::S_THIS: // "this"
      case symbol_kind::S_DOMAIN: // "domain"
      case symbol_kind::S_BUILTIN: // "builtin"
      case symbol_kind::S_FUNCTION: // "function"
      case symbol_kind::S_DEFINED: // "defined"
      case symbol_kind::S_SEQ: // "seq"
      case symbol_kind::S_ENDSEQ: // "endseq"
      case symbol_kind::S_PAR: // "par"
      case symbol_kind::S_ENDPAR: // "endpar"
      case symbol_kind::S_SKIP: // "skip"
      case symbol_kind::S_LET: // "let"
      case symbol_kind::S_LOCAL: // "local"
      case symbol_kind::S_IN: // "in"
      case symbol_kind::S_FORALL: // "forall"
      case symbol_kind::S_CHOOSE: // "choose"
      case symbol_kind::S_ITERATE: // "iterate"
      case symbol_kind::S_DO: // "do"
      case symbol_kind::S_IF: // "if"
      case symbol_kind::S_THEN: // "then"
      case symbol_kind::S_ELSE: // "else"
      case symbol_kind::S_CASE: // "case"
      case symbol_kind::S_OF: // "of"
      case symbol_kind::S_DEFAULT: // "default"
      case symbol_kind::S_HOLDS: // "holds"
      case symbol_kind::S_EXISTS: // "exists"
      case symbol_kind::S_WITH: // "with"
      case symbol_kind::S_AS: // "as"
      case symbol_kind::S_WHILE: // "while"
      case symbol_kind::S_UNDEF: // "undef"
      case symbol_kind::S_FALSE: // "false"
      case symbol_kind::S_TRUE: // "true"
      case symbol_kind::S_AND: // "and"
      case symbol_kind::S_OR: // "or"
      case symbol_kind::S_XOR: // "xor"
      case symbol_kind::S_IMPLIES: // "implies"
      case symbol_kind::S_NOT: // "not"
      case symbol_kind::S_PLUS: // "+"
      case symbol_kind::S_MINUS: // "-"
      case symbol_kind::S_EQUAL: // "="
      case symbol_kind::S_LPAREN: // "("
      case symbol_kind::S_RPAREN: // ")"
      case symbol_kind::S_LSQPAREN: // "["
      case symbol_kind::S_RSQPAREN: // "]"
      case symbol_kind::S_LCURPAREN: // "{"
      case symbol_kind::S_RCURPAREN: // "}"
      case symbol_kind::S_COLON: // ":"
      case symbol_kind::S_DOUBLECOLON: // "::"
      case symbol_kind::S_UNDERLINE: // "_"
      case symbol_kind::S_VERTICAL_BAR: // "|"
      case symbol_kind::S_AT: // "@"
      case symbol_kind::S_COMMA: // ","
      case symbol_kind::S_LESSER: // "<"
      case symbol_kind::S_GREATER: // ">"
      case symbol_kind::S_ASTERIX: // "*"
      case symbol_kind::S_SLASH: // "/"
      case symbol_kind::S_PERCENT: // "%"
      case symbol_kind::S_CARET: // "^"
      case symbol_kind::S_MARK: // "'"
      case symbol_kind::S_MAPS: // "->"
      case symbol_kind::S_ARROW: // "=>"
      case symbol_kind::S_UPDATE: // ":="
      case symbol_kind::S_NEQUAL: // "!="
      case symbol_kind::S_LESSEQ: // "<="
      case symbol_kind::S_GREATEREQ: // ">="
      case symbol_kind::S_SEQ_BRACKET: // "{|"
      case symbol_kind::S_ENDSEQ_BRACKET: // "|}"
      case symbol_kind::S_DOT: // "."
      case symbol_kind::S_DOTDOT: // ".."
      case symbol_kind::S_DOTDOTDOT: // "..."
        value.move< CST::Token::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CallExpression: // CallExpression
        value.move< CallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CallRule: // CallRule
        value.move< CallRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CardinalityExpression: // CardinalityExpression
        value.move< CardinalityExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CaseLabel: // CaseLabel
        value.move< Case::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CaseRule: // CaseRule
        value.move< CaseRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_CaseLabels: // CaseLabels
        value.move< Cases::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ChooseExpression: // ChooseExpression
        value.move< ChooseExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ChooseRule: // ChooseRule
        value.move< ChooseRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ConditionalExpression: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ConditionalRule: // ConditionalRule
        value.move< ConditionalRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Declaration: // Declaration
        value.move< Declaration::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_MaybeDefined: // MaybeDefined
        value.move< Defined::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_AttributedDefinition: // AttributedDefinition
      case symbol_kind::S_Definition: // Definition
      case symbol_kind::S_BehaviorDefinitionElement: // BehaviorDefinitionElement
      case symbol_kind::S_ImplementDefinitionElement: // ImplementDefinitionElement
      case symbol_kind::S_ImplementDefinitionAttributedElement: // ImplementDefinitionAttributedElement
        value.move< Definition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Definitions: // Definitions
      case symbol_kind::S_BehaviorDefinitionList: // BehaviorDefinitionList
      case symbol_kind::S_ImplementDefinitionList: // ImplementDefinitionList
        value.move< Definitions::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_DerivedDefinition: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_DirectCallExpression: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_DomainDefinition: // DomainDefinition
        value.move< DomainDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_EnumerationDefinition: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_EnumeratorDefinition: // EnumeratorDefinition
        value.move< EnumeratorDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Enumerators: // Enumerators
        value.move< Enumerators::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ExistentialQuantifierExpression: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Term: // Term
      case symbol_kind::S_Expression: // Expression
      case symbol_kind::S_OperatorExpression: // OperatorExpression
        value.move< Expression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ExpressionAttribute: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Terms: // Terms
        value.move< Expressions::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FixedSizedType: // FixedSizedType
        value.move< FixedSizedType::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ForallRule: // ForallRule
        value.move< ForallRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_FunctionDefinition: // FunctionDefinition
      case symbol_kind::S_StructureDefinitionElement: // StructureDefinitionElement
      case symbol_kind::S_AttributedLocalFunctionDefinition: // AttributedLocalFunctionDefinition
      case symbol_kind::S_LocalFunctionDefinition: // LocalFunctionDefinition
        value.move< FunctionDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_StructureDefinitionList: // StructureDefinitionList
      case symbol_kind::S_LocalFunctionDefinitions: // LocalFunctionDefinitions
        value.move< FunctionDefinitions::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Header: // Header
        value.move< HeaderDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IDENTIFIER: // "identifier"
      case symbol_kind::S_Identifier: // Identifier
        value.move< Identifier::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IdentifierPath: // IdentifierPath
        value.move< IdentifierPath::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ImplementDefinition: // ImplementDefinition
        value.move< ImplementDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ImportDefinition: // ImportDefinition
        value.move< ImportDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IndirectCallExpression: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_InitDefinition: // InitDefinition
        value.move< InitDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_MaybeInitially: // MaybeInitially
        value.move< Initially::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_InvariantDefinition: // InvariantDefinition
        value.move< InvariantDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_IterateRule: // IterateRule
        value.move< IterateRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_LetExpression: // LetExpression
        value.move< LetExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_LetRule: // LetRule
        value.move< LetRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ListLiteral: // ListLiteral
        value.move< ListLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Literal: // Literal
        value.move< Literal::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_LiteralCallExpression: // LiteralCallExpression
        value.move< LiteralCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_LocalRule: // LocalRule
        value.move< LocalRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_MappedExpression: // MappedExpression
        value.move< MappedExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_MappedExpressions: // MappedExpressions
        value.move< MappedExpressions::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_MappingType: // MappingType
        value.move< MappingType::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_MethodCallExpression: // MethodCallExpression
        value.move< MethodCallExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Assignment: // Assignment
        value.move< NamedExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Assignments: // Assignments
        value.move< NamedExpressions::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_RangeLiteral: // RangeLiteral
        value.move< RangeLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_RecordLiteral: // RecordLiteral
        value.move< RecordLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_RecordType: // RecordType
        value.move< RecordType::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ReferenceLiteral: // ReferenceLiteral
        value.move< ReferenceLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_RelationType: // RelationType
        value.move< RelationType::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Rule: // Rule
        value.move< Rule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_RuleDefinition: // RuleDefinition
        value.move< RuleDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Rules: // Rules
        value.move< Rules::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_SequenceRule: // SequenceRule
        value.move< SequenceRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_SkipRule: // SkipRule
        value.move< SkipRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Specification: // Specification
        value.move< Specification::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_StructureDefinition: // StructureDefinition
        value.move< StructureDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_SymbolAttribute: // SymbolAttribute
        value.move< SymbolAttribute::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TemplateType: // TemplateType
        value.move< TemplateType::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TupleLiteral: // TupleLiteral
        value.move< TupleLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TupleType: // TupleType
        value.move< TupleType::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_TypeCastingExpression: // TypeCastingExpression
        value.move< TypeCastingExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Types: // Types
      case symbol_kind::S_FunctionParameters: // FunctionParameters
      case symbol_kind::S_MaybeFunctionParameters: // MaybeFunctionParameters
        value.move< Types::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_UndefinedLiteral: // UndefinedLiteral
        value.move< UndefLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_UniversalQuantifierExpression: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_UpdateRule: // UpdateRule
        value.move< UpdateRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_UsingDefinition: // UsingDefinition
        value.move< UsingDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_UsingPathDefinition: // UsingPathDefinition
        value.move< UsingPathDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_BINARY: // "binary"
      case symbol_kind::S_HEXADECIMAL: // "hexadecimal"
      case symbol_kind::S_INTEGER: // "integer"
      case symbol_kind::S_RATIONAL: // "rational"
      case symbol_kind::S_DECIMAL: // "decimal"
      case symbol_kind::S_STRING: // "string"
      case symbol_kind::S_BooleanLiteral: // BooleanLiteral
      case symbol_kind::S_IntegerLiteral: // IntegerLiteral
      case symbol_kind::S_RationalLiteral: // RationalLiteral
      case symbol_kind::S_DecimalLiteral: // DecimalLiteral
      case symbol_kind::S_BinaryLiteral: // BinaryLiteral
      case symbol_kind::S_StringLiteral: // StringLiteral
        value.move< ValueLiteral::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_VaradicType: // VaradicType
        value.move< VaradicType::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_VariableBinding: // VariableBinding
        value.move< VariableBinding::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_VariableBindings: // VariableBindings
        value.move< VariableBindings::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Variable: // Variable
      case symbol_kind::S_TypedVariable: // TypedVariable
      case symbol_kind::S_AttributedVariable: // AttributedVariable
      case symbol_kind::S_TypedAttributedVariable: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_MethodParameters: // MethodParameters
      case symbol_kind::S_Parameters: // Parameters
      case symbol_kind::S_AttributedVariables: // AttributedVariables
      case symbol_kind::S_TypedVariables: // TypedVariables
        value.move< VariableDefinitions::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_WhileRule: // WhileRule
        value.move< WhileRule::Ptr > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_Type: // Type
        value.move< libcasm_fe::CST::Type::Ptr > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_kind.
  inline
  Parser::by_kind::by_kind ()
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Parser::by_kind::by_kind (by_kind&& that)
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  inline
  Parser::by_kind::by_kind (const by_kind& that)
    : kind_ (that.kind_)
  {}

  inline
  Parser::by_kind::by_kind (token_kind_type t)
    : kind_ (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  inline
  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }

  inline
  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }

#line 51 "../../obj/src/GrammarParser.y"
} // libcasm_fe
#line 6510 "GrammarParser.tab.h"




#endif // !YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
