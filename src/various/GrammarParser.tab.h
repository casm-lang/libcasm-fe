// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file GrammarParser.tab.h
 ** Define the libcasm_fe::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
# define YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
// //                    "%code requires" blocks.
#line 63 "../../obj/src/GrammarParser.yy" // lalr1.cc:377

    namespace libcasm_fe
    {
        class Lexer;
        class Logger;
        class SourceLocation;
    }

    #include "Specification.h"
    #include "ast/Definition.h"
    #include "ast/Expression.h"
    #include "ast/Rule.h"

    using namespace libcasm_fe;
    using namespace Ast;

    #define YY_NULLPTR nullptr

#line 63 "GrammarParser.tab.h" // lalr1.cc:377

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"

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

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:377
namespace libcasm_fe {
#line 140 "GrammarParser.tab.h" // lalr1.cc:377



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
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
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
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
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
    self_type& operator=(const self_type&);
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
      // Attribute
      char dummy1[sizeof(Attribute::Ptr)];

      // Attributes
      char dummy2[sizeof(Attributes::Ptr)];

      // BasicAttribute
      char dummy3[sizeof(BasicAttribute::Ptr)];

      // BasicType
      char dummy4[sizeof(BasicType::Ptr)];

      // BlockRule
      char dummy5[sizeof(BlockRule::Ptr)];

      // CallRule
      char dummy6[sizeof(CallRule::Ptr)];

      // CaseLabel
      char dummy7[sizeof(Case::Ptr)];

      // CaseRule
      char dummy8[sizeof(CaseRule::Ptr)];

      // CaseLabels
      char dummy9[sizeof(Cases::Ptr)];

      // ChooseExpression
      char dummy10[sizeof(ChooseExpression::Ptr)];

      // ChooseRule
      char dummy11[sizeof(ChooseRule::Ptr)];

      // ComposedType
      char dummy12[sizeof(ComposedType::Ptr)];

      // ConditionalExpression
      char dummy13[sizeof(ConditionalExpression::Ptr)];

      // ConditionalRule
      char dummy14[sizeof(ConditionalRule::Ptr)];

      // Definition
      // AttributedDefinition
      char dummy15[sizeof(Definition::Ptr)];

      // Definitions
      char dummy16[sizeof(Definitions::Ptr)];

      // DerivedDefinition
      char dummy17[sizeof(DerivedDefinition::Ptr)];

      // DirectCallExpression
      char dummy18[sizeof(DirectCallExpression::Ptr)];

      // EnumerationDefinition
      char dummy19[sizeof(EnumerationDefinition::Ptr)];

      // ExistentialQuantifierExpression
      char dummy20[sizeof(ExistentialQuantifierExpression::Ptr)];

      // Term
      // Expression
      // Literal
      // MaybeDefined
      char dummy21[sizeof(Expression::Ptr)];

      // ExpressionAttribute
      char dummy22[sizeof(ExpressionAttribute::Ptr)];

      // Terms
      // Arguments
      // TwoOrMoreArguments
      char dummy23[sizeof(Expressions::Ptr)];

      // FixedSizedType
      char dummy24[sizeof(FixedSizedType::Ptr)];

      // ForallRule
      char dummy25[sizeof(ForallRule::Ptr)];

      // FunctionDefinition
      // ProgramFunctionDefinition
      char dummy26[sizeof(FunctionDefinition::Ptr)];

      // Identifier
      char dummy27[sizeof(Identifier::Ptr)];

      // IdentifierPath
      char dummy28[sizeof(IdentifierPath::Ptr)];

      // Identifiers
      // DotSeparatedIdentifiers
      char dummy29[sizeof(Identifiers::Ptr)];

      // IndirectCallExpression
      char dummy30[sizeof(IndirectCallExpression::Ptr)];

      // IterateRule
      char dummy31[sizeof(IterateRule::Ptr)];

      // LetExpression
      char dummy32[sizeof(LetExpression::Ptr)];

      // LetRule
      char dummy33[sizeof(LetRule::Ptr)];

      // List
      char dummy34[sizeof(ListExpression::Ptr)];

      // MaybeInitially
      // Initializers
      // MaybeInitializers
      char dummy35[sizeof(NodeList< UpdateRule >::Ptr)];

      // Parameters
      // MaybeParameters
      char dummy36[sizeof(NodeList< VariableDefinition >::Ptr)];

      // Range
      char dummy37[sizeof(RangeExpression::Ptr)];

      // ReferenceLiteral
      char dummy38[sizeof(ReferenceAtom::Ptr)];

      // RelationType
      char dummy39[sizeof(RelationType::Ptr)];

      // Rule
      char dummy40[sizeof(Rule::Ptr)];

      // RuleDefinition
      char dummy41[sizeof(RuleDefinition::Ptr)];

      // Rules
      char dummy42[sizeof(Rules::Ptr)];

      // SequenceRule
      char dummy43[sizeof(SequenceRule::Ptr)];

      // SkipRule
      char dummy44[sizeof(SkipRule::Ptr)];

      // Specification
      char dummy45[sizeof(Specification::Ptr)];

      // Types
      // FunctionParameters
      // MaybeFunctionParameters
      char dummy46[sizeof(Types::Ptr)];

      // UndefinedLiteral
      char dummy47[sizeof(UndefAtom::Ptr)];

      // UniversalQuantifierExpression
      char dummy48[sizeof(UniversalQuantifierExpression::Ptr)];

      // UpdateRule
      // Initializer
      char dummy49[sizeof(UpdateRule::Ptr)];

      // BooleanLiteral
      // IntegerLiteral
      // RationalLiteral
      // FloatingLiteral
      // BitLiteral
      // StringLiteral
      char dummy50[sizeof(ValueAtom::Ptr)];

      // Variable
      // TypedVariable
      // AttributedVariable
      // TypedAttributedVariable
      char dummy51[sizeof(VariableDefinition::Ptr)];

      // Type
      char dummy52[sizeof(libcasm_fe::Ast::Type::Ptr)];

      // "binary"
      // "hexadecimal"
      // "integer"
      // "rational"
      // "floating"
      // "string"
      // "identifier"
      char dummy53[sizeof(std::string)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef SourceLocation location_type;

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
        FUNCTION = 263,
        INITIALLY = 264,
        DEFINED = 265,
        SEQ = 266,
        ENDSEQ = 267,
        PAR = 268,
        ENDPAR = 269,
        SKIP = 270,
        LET = 271,
        IN = 272,
        FORALL = 273,
        CHOOSE = 274,
        ITERATE = 275,
        DO = 276,
        CALL = 277,
        IF = 278,
        THEN = 279,
        ELSE = 280,
        CASE = 281,
        OF = 282,
        DEFAULT = 283,
        HOLDS = 284,
        EXISTS = 285,
        WITH = 286,
        UNDEF = 287,
        FALSE = 288,
        TRUE = 289,
        AND = 290,
        OR = 291,
        XOR = 292,
        IMPLIES = 293,
        NOT = 294,
        PLUS = 295,
        MINUS = 296,
        EQUAL = 297,
        LPAREN = 298,
        RPAREN = 299,
        LSQPAREN = 300,
        RSQPAREN = 301,
        LCURPAREN = 302,
        RCURPAREN = 303,
        COLON = 304,
        UNDERLINE = 305,
        AT = 306,
        COMMA = 307,
        LESSER = 308,
        GREATER = 309,
        ASTERIX = 310,
        SLASH = 311,
        PERCENT = 312,
        CARET = 313,
        MARK = 314,
        DOTDOT = 315,
        DOT = 316,
        MAPS = 317,
        ARROW = 318,
        UPDATE = 319,
        NEQUAL = 320,
        LESSEQ = 321,
        GREATEREQ = 322,
        SEQ_BRACKET = 323,
        ENDSEQ_BRACKET = 324,
        BINARY = 325,
        HEXADECIMAL = 326,
        INTEGER = 327,
        RATIONAL = 328,
        FLOATING = 329,
        STRING = 330,
        IDENTIFIER = 331,
        ABSOLUTE_PATH = 332,
        UPLUS = 333,
        UMINUS = 334,
        CALL_WITHOUT_ARGS = 335
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
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Attribute::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Attributes::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const BasicAttribute::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const BasicType::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const BlockRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const CallRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Case::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const CaseRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Cases::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ChooseExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ChooseRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ComposedType::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ConditionalExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ConditionalRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Definition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Definitions::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const DerivedDefinition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const DirectCallExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const EnumerationDefinition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ExistentialQuantifierExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Expression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ExpressionAttribute::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Expressions::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const FixedSizedType::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ForallRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const FunctionDefinition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Identifier::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const IdentifierPath::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Identifiers::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const IndirectCallExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const IterateRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const LetExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const LetRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ListExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const NodeList< UpdateRule >::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const NodeList< VariableDefinition >::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const RangeExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ReferenceAtom::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const RelationType::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Rule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const RuleDefinition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Rules::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const SequenceRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const SkipRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Specification::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const Types::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const UndefAtom::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const UniversalQuantifierExpression::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const UpdateRule::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const ValueAtom::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const VariableDefinition::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const libcasm_fe::Ast::Type::Ptr v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

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
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
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

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_CASM (const location_type& l);

    static inline
    symbol_type
    make_INIT (const location_type& l);

    static inline
    symbol_type
    make_DERIVED (const location_type& l);

    static inline
    symbol_type
    make_ENUMERATION (const location_type& l);

    static inline
    symbol_type
    make_RULE (const location_type& l);

    static inline
    symbol_type
    make_FUNCTION (const location_type& l);

    static inline
    symbol_type
    make_INITIALLY (const location_type& l);

    static inline
    symbol_type
    make_DEFINED (const location_type& l);

    static inline
    symbol_type
    make_SEQ (const location_type& l);

    static inline
    symbol_type
    make_ENDSEQ (const location_type& l);

    static inline
    symbol_type
    make_PAR (const location_type& l);

    static inline
    symbol_type
    make_ENDPAR (const location_type& l);

    static inline
    symbol_type
    make_SKIP (const location_type& l);

    static inline
    symbol_type
    make_LET (const location_type& l);

    static inline
    symbol_type
    make_IN (const location_type& l);

    static inline
    symbol_type
    make_FORALL (const location_type& l);

    static inline
    symbol_type
    make_CHOOSE (const location_type& l);

    static inline
    symbol_type
    make_ITERATE (const location_type& l);

    static inline
    symbol_type
    make_DO (const location_type& l);

    static inline
    symbol_type
    make_CALL (const location_type& l);

    static inline
    symbol_type
    make_IF (const location_type& l);

    static inline
    symbol_type
    make_THEN (const location_type& l);

    static inline
    symbol_type
    make_ELSE (const location_type& l);

    static inline
    symbol_type
    make_CASE (const location_type& l);

    static inline
    symbol_type
    make_OF (const location_type& l);

    static inline
    symbol_type
    make_DEFAULT (const location_type& l);

    static inline
    symbol_type
    make_HOLDS (const location_type& l);

    static inline
    symbol_type
    make_EXISTS (const location_type& l);

    static inline
    symbol_type
    make_WITH (const location_type& l);

    static inline
    symbol_type
    make_UNDEF (const location_type& l);

    static inline
    symbol_type
    make_FALSE (const location_type& l);

    static inline
    symbol_type
    make_TRUE (const location_type& l);

    static inline
    symbol_type
    make_AND (const location_type& l);

    static inline
    symbol_type
    make_OR (const location_type& l);

    static inline
    symbol_type
    make_XOR (const location_type& l);

    static inline
    symbol_type
    make_IMPLIES (const location_type& l);

    static inline
    symbol_type
    make_NOT (const location_type& l);

    static inline
    symbol_type
    make_PLUS (const location_type& l);

    static inline
    symbol_type
    make_MINUS (const location_type& l);

    static inline
    symbol_type
    make_EQUAL (const location_type& l);

    static inline
    symbol_type
    make_LPAREN (const location_type& l);

    static inline
    symbol_type
    make_RPAREN (const location_type& l);

    static inline
    symbol_type
    make_LSQPAREN (const location_type& l);

    static inline
    symbol_type
    make_RSQPAREN (const location_type& l);

    static inline
    symbol_type
    make_LCURPAREN (const location_type& l);

    static inline
    symbol_type
    make_RCURPAREN (const location_type& l);

    static inline
    symbol_type
    make_COLON (const location_type& l);

    static inline
    symbol_type
    make_UNDERLINE (const location_type& l);

    static inline
    symbol_type
    make_AT (const location_type& l);

    static inline
    symbol_type
    make_COMMA (const location_type& l);

    static inline
    symbol_type
    make_LESSER (const location_type& l);

    static inline
    symbol_type
    make_GREATER (const location_type& l);

    static inline
    symbol_type
    make_ASTERIX (const location_type& l);

    static inline
    symbol_type
    make_SLASH (const location_type& l);

    static inline
    symbol_type
    make_PERCENT (const location_type& l);

    static inline
    symbol_type
    make_CARET (const location_type& l);

    static inline
    symbol_type
    make_MARK (const location_type& l);

    static inline
    symbol_type
    make_DOTDOT (const location_type& l);

    static inline
    symbol_type
    make_DOT (const location_type& l);

    static inline
    symbol_type
    make_MAPS (const location_type& l);

    static inline
    symbol_type
    make_ARROW (const location_type& l);

    static inline
    symbol_type
    make_UPDATE (const location_type& l);

    static inline
    symbol_type
    make_NEQUAL (const location_type& l);

    static inline
    symbol_type
    make_LESSEQ (const location_type& l);

    static inline
    symbol_type
    make_GREATEREQ (const location_type& l);

    static inline
    symbol_type
    make_SEQ_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_ENDSEQ_BRACKET (const location_type& l);

    static inline
    symbol_type
    make_BINARY (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_HEXADECIMAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_INTEGER (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_RATIONAL (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_FLOATING (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_STRING (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_IDENTIFIER (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_ABSOLUTE_PATH (const location_type& l);

    static inline
    symbol_type
    make_UPLUS (const location_type& l);

    static inline
    symbol_type
    make_UMINUS (const location_type& l);

    static inline
    symbol_type
    make_CALL_WITHOUT_ARGS (const location_type& l);


    /// Build a parser object.
    Parser (Logger& log_yyarg, Lexer& lexer_yyarg, Specification& specification_yyarg);
    virtual ~Parser ();

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

    static const short int yypact_ninf_;
    static const short int yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const short int yycheck_[];

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
  static const unsigned short int yyrline_[];
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
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 1981,     ///< Last index in yytable_.
      yynnts_ = 75,  ///< Number of nonterminal symbols.
      yyfinal_ = 18, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 81  ///< Number of tokens.
    };


    // User arguments.
    Logger& log;
    Lexer& lexer;
    Specification& specification;
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
      75,    76,    77,    78,    79,    80
    };
    const unsigned int user_token_number_max_ = 335;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
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
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 153: // Attribute
        value.copy< Attribute::Ptr > (other.value);
        break;

      case 152: // Attributes
        value.copy< Attributes::Ptr > (other.value);
        break;

      case 154: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (other.value);
        break;

      case 129: // BasicType
        value.copy< BasicType::Ptr > (other.value);
        break;

      case 102: // BlockRule
        value.copy< BlockRule::Ptr > (other.value);
        break;

      case 105: // CallRule
        value.copy< CallRule::Ptr > (other.value);
        break;

      case 96: // CaseLabel
        value.copy< Case::Ptr > (other.value);
        break;

      case 95: // CaseRule
        value.copy< CaseRule::Ptr > (other.value);
        break;

      case 97: // CaseLabels
        value.copy< Cases::Ptr > (other.value);
        break;

      case 113: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (other.value);
        break;

      case 100: // ChooseRule
        value.copy< ChooseRule::Ptr > (other.value);
        break;

      case 130: // ComposedType
        value.copy< ComposedType::Ptr > (other.value);
        break;

      case 112: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (other.value);
        break;

      case 94: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (other.value);
        break;

      case 84: // Definition
      case 85: // AttributedDefinition
        value.copy< Definition::Ptr > (other.value);
        break;

      case 83: // Definitions
        value.copy< Definitions::Ptr > (other.value);
        break;

      case 87: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (other.value);
        break;

      case 109: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (other.value);
        break;

      case 86: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (other.value);
        break;

      case 115: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (other.value);
        break;

      case 107: // Term
      case 108: // Expression
      case 118: // Literal
      case 139: // MaybeDefined
        value.copy< Expression::Ptr > (other.value);
        break;

      case 155: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (other.value);
        break;

      case 106: // Terms
      case 133: // Arguments
      case 134: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (other.value);
        break;

      case 132: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (other.value);
        break;

      case 99: // ForallRule
        value.copy< ForallRule::Ptr > (other.value);
        break;

      case 89: // FunctionDefinition
      case 90: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (other.value);
        break;

      case 145: // Identifier
        value.copy< Identifier::Ptr > (other.value);
        break;

      case 146: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (other.value);
        break;

      case 144: // Identifiers
      case 147: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (other.value);
        break;

      case 110: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (other.value);
        break;

      case 101: // IterateRule
        value.copy< IterateRule::Ptr > (other.value);
        break;

      case 111: // LetExpression
        value.copy< LetExpression::Ptr > (other.value);
        break;

      case 98: // LetRule
        value.copy< LetRule::Ptr > (other.value);
        break;

      case 116: // List
        value.copy< ListExpression::Ptr > (other.value);
        break;

      case 140: // MaybeInitially
      case 141: // Initializers
      case 143: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (other.value);
        break;

      case 137: // Parameters
      case 138: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (other.value);
        break;

      case 117: // Range
        value.copy< RangeExpression::Ptr > (other.value);
        break;

      case 126: // ReferenceLiteral
        value.copy< ReferenceAtom::Ptr > (other.value);
        break;

      case 131: // RelationType
        value.copy< RelationType::Ptr > (other.value);
        break;

      case 91: // Rule
        value.copy< Rule::Ptr > (other.value);
        break;

      case 88: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (other.value);
        break;

      case 92: // Rules
        value.copy< Rules::Ptr > (other.value);
        break;

      case 103: // SequenceRule
        value.copy< SequenceRule::Ptr > (other.value);
        break;

      case 93: // SkipRule
        value.copy< SkipRule::Ptr > (other.value);
        break;

      case 82: // Specification
        value.copy< Specification::Ptr > (other.value);
        break;

      case 127: // Types
      case 135: // FunctionParameters
      case 136: // MaybeFunctionParameters
        value.copy< Types::Ptr > (other.value);
        break;

      case 119: // UndefinedLiteral
        value.copy< UndefAtom::Ptr > (other.value);
        break;

      case 114: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (other.value);
        break;

      case 104: // UpdateRule
      case 142: // Initializer
        value.copy< UpdateRule::Ptr > (other.value);
        break;

      case 120: // BooleanLiteral
      case 121: // IntegerLiteral
      case 122: // RationalLiteral
      case 123: // FloatingLiteral
      case 124: // BitLiteral
      case 125: // StringLiteral
        value.copy< ValueAtom::Ptr > (other.value);
        break;

      case 148: // Variable
      case 149: // TypedVariable
      case 150: // AttributedVariable
      case 151: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (other.value);
        break;

      case 128: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (other.value);
        break;

      case 70: // "binary"
      case 71: // "hexadecimal"
      case 72: // "integer"
      case 73: // "rational"
      case 74: // "floating"
      case 75: // "string"
      case 76: // "identifier"
        value.copy< std::string > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 153: // Attribute
        value.copy< Attribute::Ptr > (v);
        break;

      case 152: // Attributes
        value.copy< Attributes::Ptr > (v);
        break;

      case 154: // BasicAttribute
        value.copy< BasicAttribute::Ptr > (v);
        break;

      case 129: // BasicType
        value.copy< BasicType::Ptr > (v);
        break;

      case 102: // BlockRule
        value.copy< BlockRule::Ptr > (v);
        break;

      case 105: // CallRule
        value.copy< CallRule::Ptr > (v);
        break;

      case 96: // CaseLabel
        value.copy< Case::Ptr > (v);
        break;

      case 95: // CaseRule
        value.copy< CaseRule::Ptr > (v);
        break;

      case 97: // CaseLabels
        value.copy< Cases::Ptr > (v);
        break;

      case 113: // ChooseExpression
        value.copy< ChooseExpression::Ptr > (v);
        break;

      case 100: // ChooseRule
        value.copy< ChooseRule::Ptr > (v);
        break;

      case 130: // ComposedType
        value.copy< ComposedType::Ptr > (v);
        break;

      case 112: // ConditionalExpression
        value.copy< ConditionalExpression::Ptr > (v);
        break;

      case 94: // ConditionalRule
        value.copy< ConditionalRule::Ptr > (v);
        break;

      case 84: // Definition
      case 85: // AttributedDefinition
        value.copy< Definition::Ptr > (v);
        break;

      case 83: // Definitions
        value.copy< Definitions::Ptr > (v);
        break;

      case 87: // DerivedDefinition
        value.copy< DerivedDefinition::Ptr > (v);
        break;

      case 109: // DirectCallExpression
        value.copy< DirectCallExpression::Ptr > (v);
        break;

      case 86: // EnumerationDefinition
        value.copy< EnumerationDefinition::Ptr > (v);
        break;

      case 115: // ExistentialQuantifierExpression
        value.copy< ExistentialQuantifierExpression::Ptr > (v);
        break;

      case 107: // Term
      case 108: // Expression
      case 118: // Literal
      case 139: // MaybeDefined
        value.copy< Expression::Ptr > (v);
        break;

      case 155: // ExpressionAttribute
        value.copy< ExpressionAttribute::Ptr > (v);
        break;

      case 106: // Terms
      case 133: // Arguments
      case 134: // TwoOrMoreArguments
        value.copy< Expressions::Ptr > (v);
        break;

      case 132: // FixedSizedType
        value.copy< FixedSizedType::Ptr > (v);
        break;

      case 99: // ForallRule
        value.copy< ForallRule::Ptr > (v);
        break;

      case 89: // FunctionDefinition
      case 90: // ProgramFunctionDefinition
        value.copy< FunctionDefinition::Ptr > (v);
        break;

      case 145: // Identifier
        value.copy< Identifier::Ptr > (v);
        break;

      case 146: // IdentifierPath
        value.copy< IdentifierPath::Ptr > (v);
        break;

      case 144: // Identifiers
      case 147: // DotSeparatedIdentifiers
        value.copy< Identifiers::Ptr > (v);
        break;

      case 110: // IndirectCallExpression
        value.copy< IndirectCallExpression::Ptr > (v);
        break;

      case 101: // IterateRule
        value.copy< IterateRule::Ptr > (v);
        break;

      case 111: // LetExpression
        value.copy< LetExpression::Ptr > (v);
        break;

      case 98: // LetRule
        value.copy< LetRule::Ptr > (v);
        break;

      case 116: // List
        value.copy< ListExpression::Ptr > (v);
        break;

      case 140: // MaybeInitially
      case 141: // Initializers
      case 143: // MaybeInitializers
        value.copy< NodeList< UpdateRule >::Ptr > (v);
        break;

      case 137: // Parameters
      case 138: // MaybeParameters
        value.copy< NodeList< VariableDefinition >::Ptr > (v);
        break;

      case 117: // Range
        value.copy< RangeExpression::Ptr > (v);
        break;

      case 126: // ReferenceLiteral
        value.copy< ReferenceAtom::Ptr > (v);
        break;

      case 131: // RelationType
        value.copy< RelationType::Ptr > (v);
        break;

      case 91: // Rule
        value.copy< Rule::Ptr > (v);
        break;

      case 88: // RuleDefinition
        value.copy< RuleDefinition::Ptr > (v);
        break;

      case 92: // Rules
        value.copy< Rules::Ptr > (v);
        break;

      case 103: // SequenceRule
        value.copy< SequenceRule::Ptr > (v);
        break;

      case 93: // SkipRule
        value.copy< SkipRule::Ptr > (v);
        break;

      case 82: // Specification
        value.copy< Specification::Ptr > (v);
        break;

      case 127: // Types
      case 135: // FunctionParameters
      case 136: // MaybeFunctionParameters
        value.copy< Types::Ptr > (v);
        break;

      case 119: // UndefinedLiteral
        value.copy< UndefAtom::Ptr > (v);
        break;

      case 114: // UniversalQuantifierExpression
        value.copy< UniversalQuantifierExpression::Ptr > (v);
        break;

      case 104: // UpdateRule
      case 142: // Initializer
        value.copy< UpdateRule::Ptr > (v);
        break;

      case 120: // BooleanLiteral
      case 121: // IntegerLiteral
      case 122: // RationalLiteral
      case 123: // FloatingLiteral
      case 124: // BitLiteral
      case 125: // StringLiteral
        value.copy< ValueAtom::Ptr > (v);
        break;

      case 148: // Variable
      case 149: // TypedVariable
      case 150: // AttributedVariable
      case 151: // TypedAttributedVariable
        value.copy< VariableDefinition::Ptr > (v);
        break;

      case 128: // Type
        value.copy< libcasm_fe::Ast::Type::Ptr > (v);
        break;

      case 70: // "binary"
      case 71: // "hexadecimal"
      case 72: // "integer"
      case 73: // "rational"
      case 74: // "floating"
      case 75: // "string"
      case 76: // "identifier"
        value.copy< std::string > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Attribute::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Attributes::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const BasicAttribute::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const BasicType::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const BlockRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const CallRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Case::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const CaseRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Cases::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ChooseExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ChooseRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ComposedType::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ConditionalExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ConditionalRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Definition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Definitions::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const DerivedDefinition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const DirectCallExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const EnumerationDefinition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ExistentialQuantifierExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Expression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ExpressionAttribute::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Expressions::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const FixedSizedType::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ForallRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const FunctionDefinition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Identifier::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const IdentifierPath::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Identifiers::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const IndirectCallExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const IterateRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const LetExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const LetRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ListExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const NodeList< UpdateRule >::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const NodeList< VariableDefinition >::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const RangeExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ReferenceAtom::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const RelationType::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Rule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const RuleDefinition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Rules::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SequenceRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const SkipRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Specification::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const Types::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const UndefAtom::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const UniversalQuantifierExpression::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const UpdateRule::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const ValueAtom::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const VariableDefinition::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const libcasm_fe::Ast::Type::Ptr v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
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
      case 153: // Attribute
        value.template destroy< Attribute::Ptr > ();
        break;

      case 152: // Attributes
        value.template destroy< Attributes::Ptr > ();
        break;

      case 154: // BasicAttribute
        value.template destroy< BasicAttribute::Ptr > ();
        break;

      case 129: // BasicType
        value.template destroy< BasicType::Ptr > ();
        break;

      case 102: // BlockRule
        value.template destroy< BlockRule::Ptr > ();
        break;

      case 105: // CallRule
        value.template destroy< CallRule::Ptr > ();
        break;

      case 96: // CaseLabel
        value.template destroy< Case::Ptr > ();
        break;

      case 95: // CaseRule
        value.template destroy< CaseRule::Ptr > ();
        break;

      case 97: // CaseLabels
        value.template destroy< Cases::Ptr > ();
        break;

      case 113: // ChooseExpression
        value.template destroy< ChooseExpression::Ptr > ();
        break;

      case 100: // ChooseRule
        value.template destroy< ChooseRule::Ptr > ();
        break;

      case 130: // ComposedType
        value.template destroy< ComposedType::Ptr > ();
        break;

      case 112: // ConditionalExpression
        value.template destroy< ConditionalExpression::Ptr > ();
        break;

      case 94: // ConditionalRule
        value.template destroy< ConditionalRule::Ptr > ();
        break;

      case 84: // Definition
      case 85: // AttributedDefinition
        value.template destroy< Definition::Ptr > ();
        break;

      case 83: // Definitions
        value.template destroy< Definitions::Ptr > ();
        break;

      case 87: // DerivedDefinition
        value.template destroy< DerivedDefinition::Ptr > ();
        break;

      case 109: // DirectCallExpression
        value.template destroy< DirectCallExpression::Ptr > ();
        break;

      case 86: // EnumerationDefinition
        value.template destroy< EnumerationDefinition::Ptr > ();
        break;

      case 115: // ExistentialQuantifierExpression
        value.template destroy< ExistentialQuantifierExpression::Ptr > ();
        break;

      case 107: // Term
      case 108: // Expression
      case 118: // Literal
      case 139: // MaybeDefined
        value.template destroy< Expression::Ptr > ();
        break;

      case 155: // ExpressionAttribute
        value.template destroy< ExpressionAttribute::Ptr > ();
        break;

      case 106: // Terms
      case 133: // Arguments
      case 134: // TwoOrMoreArguments
        value.template destroy< Expressions::Ptr > ();
        break;

      case 132: // FixedSizedType
        value.template destroy< FixedSizedType::Ptr > ();
        break;

      case 99: // ForallRule
        value.template destroy< ForallRule::Ptr > ();
        break;

      case 89: // FunctionDefinition
      case 90: // ProgramFunctionDefinition
        value.template destroy< FunctionDefinition::Ptr > ();
        break;

      case 145: // Identifier
        value.template destroy< Identifier::Ptr > ();
        break;

      case 146: // IdentifierPath
        value.template destroy< IdentifierPath::Ptr > ();
        break;

      case 144: // Identifiers
      case 147: // DotSeparatedIdentifiers
        value.template destroy< Identifiers::Ptr > ();
        break;

      case 110: // IndirectCallExpression
        value.template destroy< IndirectCallExpression::Ptr > ();
        break;

      case 101: // IterateRule
        value.template destroy< IterateRule::Ptr > ();
        break;

      case 111: // LetExpression
        value.template destroy< LetExpression::Ptr > ();
        break;

      case 98: // LetRule
        value.template destroy< LetRule::Ptr > ();
        break;

      case 116: // List
        value.template destroy< ListExpression::Ptr > ();
        break;

      case 140: // MaybeInitially
      case 141: // Initializers
      case 143: // MaybeInitializers
        value.template destroy< NodeList< UpdateRule >::Ptr > ();
        break;

      case 137: // Parameters
      case 138: // MaybeParameters
        value.template destroy< NodeList< VariableDefinition >::Ptr > ();
        break;

      case 117: // Range
        value.template destroy< RangeExpression::Ptr > ();
        break;

      case 126: // ReferenceLiteral
        value.template destroy< ReferenceAtom::Ptr > ();
        break;

      case 131: // RelationType
        value.template destroy< RelationType::Ptr > ();
        break;

      case 91: // Rule
        value.template destroy< Rule::Ptr > ();
        break;

      case 88: // RuleDefinition
        value.template destroy< RuleDefinition::Ptr > ();
        break;

      case 92: // Rules
        value.template destroy< Rules::Ptr > ();
        break;

      case 103: // SequenceRule
        value.template destroy< SequenceRule::Ptr > ();
        break;

      case 93: // SkipRule
        value.template destroy< SkipRule::Ptr > ();
        break;

      case 82: // Specification
        value.template destroy< Specification::Ptr > ();
        break;

      case 127: // Types
      case 135: // FunctionParameters
      case 136: // MaybeFunctionParameters
        value.template destroy< Types::Ptr > ();
        break;

      case 119: // UndefinedLiteral
        value.template destroy< UndefAtom::Ptr > ();
        break;

      case 114: // UniversalQuantifierExpression
        value.template destroy< UniversalQuantifierExpression::Ptr > ();
        break;

      case 104: // UpdateRule
      case 142: // Initializer
        value.template destroy< UpdateRule::Ptr > ();
        break;

      case 120: // BooleanLiteral
      case 121: // IntegerLiteral
      case 122: // RationalLiteral
      case 123: // FloatingLiteral
      case 124: // BitLiteral
      case 125: // StringLiteral
        value.template destroy< ValueAtom::Ptr > ();
        break;

      case 148: // Variable
      case 149: // TypedVariable
      case 150: // AttributedVariable
      case 151: // TypedAttributedVariable
        value.template destroy< VariableDefinition::Ptr > ();
        break;

      case 128: // Type
        value.template destroy< libcasm_fe::Ast::Type::Ptr > ();
        break;

      case 70: // "binary"
      case 71: // "hexadecimal"
      case 72: // "integer"
      case 73: // "rational"
      case 74: // "floating"
      case 75: // "string"
      case 76: // "identifier"
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 153: // Attribute
        value.move< Attribute::Ptr > (s.value);
        break;

      case 152: // Attributes
        value.move< Attributes::Ptr > (s.value);
        break;

      case 154: // BasicAttribute
        value.move< BasicAttribute::Ptr > (s.value);
        break;

      case 129: // BasicType
        value.move< BasicType::Ptr > (s.value);
        break;

      case 102: // BlockRule
        value.move< BlockRule::Ptr > (s.value);
        break;

      case 105: // CallRule
        value.move< CallRule::Ptr > (s.value);
        break;

      case 96: // CaseLabel
        value.move< Case::Ptr > (s.value);
        break;

      case 95: // CaseRule
        value.move< CaseRule::Ptr > (s.value);
        break;

      case 97: // CaseLabels
        value.move< Cases::Ptr > (s.value);
        break;

      case 113: // ChooseExpression
        value.move< ChooseExpression::Ptr > (s.value);
        break;

      case 100: // ChooseRule
        value.move< ChooseRule::Ptr > (s.value);
        break;

      case 130: // ComposedType
        value.move< ComposedType::Ptr > (s.value);
        break;

      case 112: // ConditionalExpression
        value.move< ConditionalExpression::Ptr > (s.value);
        break;

      case 94: // ConditionalRule
        value.move< ConditionalRule::Ptr > (s.value);
        break;

      case 84: // Definition
      case 85: // AttributedDefinition
        value.move< Definition::Ptr > (s.value);
        break;

      case 83: // Definitions
        value.move< Definitions::Ptr > (s.value);
        break;

      case 87: // DerivedDefinition
        value.move< DerivedDefinition::Ptr > (s.value);
        break;

      case 109: // DirectCallExpression
        value.move< DirectCallExpression::Ptr > (s.value);
        break;

      case 86: // EnumerationDefinition
        value.move< EnumerationDefinition::Ptr > (s.value);
        break;

      case 115: // ExistentialQuantifierExpression
        value.move< ExistentialQuantifierExpression::Ptr > (s.value);
        break;

      case 107: // Term
      case 108: // Expression
      case 118: // Literal
      case 139: // MaybeDefined
        value.move< Expression::Ptr > (s.value);
        break;

      case 155: // ExpressionAttribute
        value.move< ExpressionAttribute::Ptr > (s.value);
        break;

      case 106: // Terms
      case 133: // Arguments
      case 134: // TwoOrMoreArguments
        value.move< Expressions::Ptr > (s.value);
        break;

      case 132: // FixedSizedType
        value.move< FixedSizedType::Ptr > (s.value);
        break;

      case 99: // ForallRule
        value.move< ForallRule::Ptr > (s.value);
        break;

      case 89: // FunctionDefinition
      case 90: // ProgramFunctionDefinition
        value.move< FunctionDefinition::Ptr > (s.value);
        break;

      case 145: // Identifier
        value.move< Identifier::Ptr > (s.value);
        break;

      case 146: // IdentifierPath
        value.move< IdentifierPath::Ptr > (s.value);
        break;

      case 144: // Identifiers
      case 147: // DotSeparatedIdentifiers
        value.move< Identifiers::Ptr > (s.value);
        break;

      case 110: // IndirectCallExpression
        value.move< IndirectCallExpression::Ptr > (s.value);
        break;

      case 101: // IterateRule
        value.move< IterateRule::Ptr > (s.value);
        break;

      case 111: // LetExpression
        value.move< LetExpression::Ptr > (s.value);
        break;

      case 98: // LetRule
        value.move< LetRule::Ptr > (s.value);
        break;

      case 116: // List
        value.move< ListExpression::Ptr > (s.value);
        break;

      case 140: // MaybeInitially
      case 141: // Initializers
      case 143: // MaybeInitializers
        value.move< NodeList< UpdateRule >::Ptr > (s.value);
        break;

      case 137: // Parameters
      case 138: // MaybeParameters
        value.move< NodeList< VariableDefinition >::Ptr > (s.value);
        break;

      case 117: // Range
        value.move< RangeExpression::Ptr > (s.value);
        break;

      case 126: // ReferenceLiteral
        value.move< ReferenceAtom::Ptr > (s.value);
        break;

      case 131: // RelationType
        value.move< RelationType::Ptr > (s.value);
        break;

      case 91: // Rule
        value.move< Rule::Ptr > (s.value);
        break;

      case 88: // RuleDefinition
        value.move< RuleDefinition::Ptr > (s.value);
        break;

      case 92: // Rules
        value.move< Rules::Ptr > (s.value);
        break;

      case 103: // SequenceRule
        value.move< SequenceRule::Ptr > (s.value);
        break;

      case 93: // SkipRule
        value.move< SkipRule::Ptr > (s.value);
        break;

      case 82: // Specification
        value.move< Specification::Ptr > (s.value);
        break;

      case 127: // Types
      case 135: // FunctionParameters
      case 136: // MaybeFunctionParameters
        value.move< Types::Ptr > (s.value);
        break;

      case 119: // UndefinedLiteral
        value.move< UndefAtom::Ptr > (s.value);
        break;

      case 114: // UniversalQuantifierExpression
        value.move< UniversalQuantifierExpression::Ptr > (s.value);
        break;

      case 104: // UpdateRule
      case 142: // Initializer
        value.move< UpdateRule::Ptr > (s.value);
        break;

      case 120: // BooleanLiteral
      case 121: // IntegerLiteral
      case 122: // RationalLiteral
      case 123: // FloatingLiteral
      case 124: // BitLiteral
      case 125: // StringLiteral
        value.move< ValueAtom::Ptr > (s.value);
        break;

      case 148: // Variable
      case 149: // TypedVariable
      case 150: // AttributedVariable
      case 151: // TypedAttributedVariable
        value.move< VariableDefinition::Ptr > (s.value);
        break;

      case 128: // Type
        value.move< libcasm_fe::Ast::Type::Ptr > (s.value);
        break;

      case 70: // "binary"
      case 71: // "hexadecimal"
      case 72: // "integer"
      case 73: // "rational"
      case 74: // "floating"
      case 75: // "string"
      case 76: // "identifier"
        value.move< std::string > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
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
    const unsigned short int
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
     335
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  Parser::symbol_type
  Parser::make_END (const location_type& l)
  {
    return symbol_type (token::END, l);
  }

  Parser::symbol_type
  Parser::make_CASM (const location_type& l)
  {
    return symbol_type (token::CASM, l);
  }

  Parser::symbol_type
  Parser::make_INIT (const location_type& l)
  {
    return symbol_type (token::INIT, l);
  }

  Parser::symbol_type
  Parser::make_DERIVED (const location_type& l)
  {
    return symbol_type (token::DERIVED, l);
  }

  Parser::symbol_type
  Parser::make_ENUMERATION (const location_type& l)
  {
    return symbol_type (token::ENUMERATION, l);
  }

  Parser::symbol_type
  Parser::make_RULE (const location_type& l)
  {
    return symbol_type (token::RULE, l);
  }

  Parser::symbol_type
  Parser::make_FUNCTION (const location_type& l)
  {
    return symbol_type (token::FUNCTION, l);
  }

  Parser::symbol_type
  Parser::make_INITIALLY (const location_type& l)
  {
    return symbol_type (token::INITIALLY, l);
  }

  Parser::symbol_type
  Parser::make_DEFINED (const location_type& l)
  {
    return symbol_type (token::DEFINED, l);
  }

  Parser::symbol_type
  Parser::make_SEQ (const location_type& l)
  {
    return symbol_type (token::SEQ, l);
  }

  Parser::symbol_type
  Parser::make_ENDSEQ (const location_type& l)
  {
    return symbol_type (token::ENDSEQ, l);
  }

  Parser::symbol_type
  Parser::make_PAR (const location_type& l)
  {
    return symbol_type (token::PAR, l);
  }

  Parser::symbol_type
  Parser::make_ENDPAR (const location_type& l)
  {
    return symbol_type (token::ENDPAR, l);
  }

  Parser::symbol_type
  Parser::make_SKIP (const location_type& l)
  {
    return symbol_type (token::SKIP, l);
  }

  Parser::symbol_type
  Parser::make_LET (const location_type& l)
  {
    return symbol_type (token::LET, l);
  }

  Parser::symbol_type
  Parser::make_IN (const location_type& l)
  {
    return symbol_type (token::IN, l);
  }

  Parser::symbol_type
  Parser::make_FORALL (const location_type& l)
  {
    return symbol_type (token::FORALL, l);
  }

  Parser::symbol_type
  Parser::make_CHOOSE (const location_type& l)
  {
    return symbol_type (token::CHOOSE, l);
  }

  Parser::symbol_type
  Parser::make_ITERATE (const location_type& l)
  {
    return symbol_type (token::ITERATE, l);
  }

  Parser::symbol_type
  Parser::make_DO (const location_type& l)
  {
    return symbol_type (token::DO, l);
  }

  Parser::symbol_type
  Parser::make_CALL (const location_type& l)
  {
    return symbol_type (token::CALL, l);
  }

  Parser::symbol_type
  Parser::make_IF (const location_type& l)
  {
    return symbol_type (token::IF, l);
  }

  Parser::symbol_type
  Parser::make_THEN (const location_type& l)
  {
    return symbol_type (token::THEN, l);
  }

  Parser::symbol_type
  Parser::make_ELSE (const location_type& l)
  {
    return symbol_type (token::ELSE, l);
  }

  Parser::symbol_type
  Parser::make_CASE (const location_type& l)
  {
    return symbol_type (token::CASE, l);
  }

  Parser::symbol_type
  Parser::make_OF (const location_type& l)
  {
    return symbol_type (token::OF, l);
  }

  Parser::symbol_type
  Parser::make_DEFAULT (const location_type& l)
  {
    return symbol_type (token::DEFAULT, l);
  }

  Parser::symbol_type
  Parser::make_HOLDS (const location_type& l)
  {
    return symbol_type (token::HOLDS, l);
  }

  Parser::symbol_type
  Parser::make_EXISTS (const location_type& l)
  {
    return symbol_type (token::EXISTS, l);
  }

  Parser::symbol_type
  Parser::make_WITH (const location_type& l)
  {
    return symbol_type (token::WITH, l);
  }

  Parser::symbol_type
  Parser::make_UNDEF (const location_type& l)
  {
    return symbol_type (token::UNDEF, l);
  }

  Parser::symbol_type
  Parser::make_FALSE (const location_type& l)
  {
    return symbol_type (token::FALSE, l);
  }

  Parser::symbol_type
  Parser::make_TRUE (const location_type& l)
  {
    return symbol_type (token::TRUE, l);
  }

  Parser::symbol_type
  Parser::make_AND (const location_type& l)
  {
    return symbol_type (token::AND, l);
  }

  Parser::symbol_type
  Parser::make_OR (const location_type& l)
  {
    return symbol_type (token::OR, l);
  }

  Parser::symbol_type
  Parser::make_XOR (const location_type& l)
  {
    return symbol_type (token::XOR, l);
  }

  Parser::symbol_type
  Parser::make_IMPLIES (const location_type& l)
  {
    return symbol_type (token::IMPLIES, l);
  }

  Parser::symbol_type
  Parser::make_NOT (const location_type& l)
  {
    return symbol_type (token::NOT, l);
  }

  Parser::symbol_type
  Parser::make_PLUS (const location_type& l)
  {
    return symbol_type (token::PLUS, l);
  }

  Parser::symbol_type
  Parser::make_MINUS (const location_type& l)
  {
    return symbol_type (token::MINUS, l);
  }

  Parser::symbol_type
  Parser::make_EQUAL (const location_type& l)
  {
    return symbol_type (token::EQUAL, l);
  }

  Parser::symbol_type
  Parser::make_LPAREN (const location_type& l)
  {
    return symbol_type (token::LPAREN, l);
  }

  Parser::symbol_type
  Parser::make_RPAREN (const location_type& l)
  {
    return symbol_type (token::RPAREN, l);
  }

  Parser::symbol_type
  Parser::make_LSQPAREN (const location_type& l)
  {
    return symbol_type (token::LSQPAREN, l);
  }

  Parser::symbol_type
  Parser::make_RSQPAREN (const location_type& l)
  {
    return symbol_type (token::RSQPAREN, l);
  }

  Parser::symbol_type
  Parser::make_LCURPAREN (const location_type& l)
  {
    return symbol_type (token::LCURPAREN, l);
  }

  Parser::symbol_type
  Parser::make_RCURPAREN (const location_type& l)
  {
    return symbol_type (token::RCURPAREN, l);
  }

  Parser::symbol_type
  Parser::make_COLON (const location_type& l)
  {
    return symbol_type (token::COLON, l);
  }

  Parser::symbol_type
  Parser::make_UNDERLINE (const location_type& l)
  {
    return symbol_type (token::UNDERLINE, l);
  }

  Parser::symbol_type
  Parser::make_AT (const location_type& l)
  {
    return symbol_type (token::AT, l);
  }

  Parser::symbol_type
  Parser::make_COMMA (const location_type& l)
  {
    return symbol_type (token::COMMA, l);
  }

  Parser::symbol_type
  Parser::make_LESSER (const location_type& l)
  {
    return symbol_type (token::LESSER, l);
  }

  Parser::symbol_type
  Parser::make_GREATER (const location_type& l)
  {
    return symbol_type (token::GREATER, l);
  }

  Parser::symbol_type
  Parser::make_ASTERIX (const location_type& l)
  {
    return symbol_type (token::ASTERIX, l);
  }

  Parser::symbol_type
  Parser::make_SLASH (const location_type& l)
  {
    return symbol_type (token::SLASH, l);
  }

  Parser::symbol_type
  Parser::make_PERCENT (const location_type& l)
  {
    return symbol_type (token::PERCENT, l);
  }

  Parser::symbol_type
  Parser::make_CARET (const location_type& l)
  {
    return symbol_type (token::CARET, l);
  }

  Parser::symbol_type
  Parser::make_MARK (const location_type& l)
  {
    return symbol_type (token::MARK, l);
  }

  Parser::symbol_type
  Parser::make_DOTDOT (const location_type& l)
  {
    return symbol_type (token::DOTDOT, l);
  }

  Parser::symbol_type
  Parser::make_DOT (const location_type& l)
  {
    return symbol_type (token::DOT, l);
  }

  Parser::symbol_type
  Parser::make_MAPS (const location_type& l)
  {
    return symbol_type (token::MAPS, l);
  }

  Parser::symbol_type
  Parser::make_ARROW (const location_type& l)
  {
    return symbol_type (token::ARROW, l);
  }

  Parser::symbol_type
  Parser::make_UPDATE (const location_type& l)
  {
    return symbol_type (token::UPDATE, l);
  }

  Parser::symbol_type
  Parser::make_NEQUAL (const location_type& l)
  {
    return symbol_type (token::NEQUAL, l);
  }

  Parser::symbol_type
  Parser::make_LESSEQ (const location_type& l)
  {
    return symbol_type (token::LESSEQ, l);
  }

  Parser::symbol_type
  Parser::make_GREATEREQ (const location_type& l)
  {
    return symbol_type (token::GREATEREQ, l);
  }

  Parser::symbol_type
  Parser::make_SEQ_BRACKET (const location_type& l)
  {
    return symbol_type (token::SEQ_BRACKET, l);
  }

  Parser::symbol_type
  Parser::make_ENDSEQ_BRACKET (const location_type& l)
  {
    return symbol_type (token::ENDSEQ_BRACKET, l);
  }

  Parser::symbol_type
  Parser::make_BINARY (const std::string& v, const location_type& l)
  {
    return symbol_type (token::BINARY, v, l);
  }

  Parser::symbol_type
  Parser::make_HEXADECIMAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::HEXADECIMAL, v, l);
  }

  Parser::symbol_type
  Parser::make_INTEGER (const std::string& v, const location_type& l)
  {
    return symbol_type (token::INTEGER, v, l);
  }

  Parser::symbol_type
  Parser::make_RATIONAL (const std::string& v, const location_type& l)
  {
    return symbol_type (token::RATIONAL, v, l);
  }

  Parser::symbol_type
  Parser::make_FLOATING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::FLOATING, v, l);
  }

  Parser::symbol_type
  Parser::make_STRING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::STRING, v, l);
  }

  Parser::symbol_type
  Parser::make_IDENTIFIER (const std::string& v, const location_type& l)
  {
    return symbol_type (token::IDENTIFIER, v, l);
  }

  Parser::symbol_type
  Parser::make_ABSOLUTE_PATH (const location_type& l)
  {
    return symbol_type (token::ABSOLUTE_PATH, l);
  }

  Parser::symbol_type
  Parser::make_UPLUS (const location_type& l)
  {
    return symbol_type (token::UPLUS, l);
  }

  Parser::symbol_type
  Parser::make_UMINUS (const location_type& l)
  {
    return symbol_type (token::UMINUS, l);
  }

  Parser::symbol_type
  Parser::make_CALL_WITHOUT_ARGS (const location_type& l)
  {
    return symbol_type (token::CALL_WITHOUT_ARGS, l);
  }


#line 49 "../../obj/src/GrammarParser.yy" // lalr1.cc:377
} // libcasm_fe
#line 3374 "GrammarParser.tab.h" // lalr1.cc:377




#endif // !YY_YY_GRAMMARPARSER_TAB_H_INCLUDED
