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

#line 37 "GrammarParser.cpp"  // lalr1.cc:404

#ifndef YY_NULLPTR
#if defined __cplusplus && 201103L <= __cplusplus
#define YY_NULLPTR nullptr
#else
#define YY_NULLPTR 0
#endif
#endif

#include "GrammarParser.tab.h"

// User implementation prologue.

#line 51 "GrammarParser.cpp"  // lalr1.cc:412
// Unqualified %code blocks.
#line 87 "../../obj/src/GrammarParser.yy"  // lalr1.cc:413

#include "Exception.h"
#include "Lexer.h"
#include "Logger.h"
#include "SourceLocation.h"

#include <libstdhl/Type>

#undef yylex
#define yylex lexer.nextToken

static BasicType::Ptr createVoidType( SourceLocation& sourceLocation )
{
    const auto type = libstdhl::Memory::get< libcasm_ir::VoidType >();
    const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
    const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
    const auto node = Ast::make< BasicType >( sourceLocation, path );
    node->setType( type );
    return node;
}

static BasicType::Ptr createRuleRefType( SourceLocation& sourceLocation )
{
    const auto type = libstdhl::Memory::get< libcasm_ir::RuleReferenceType >();
    const auto name = Ast::make< Identifier >( sourceLocation, type->description() );
    const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
    const auto node = Ast::make< BasicType >( sourceLocation, path );
    node->setType( type );
    return node;
}

static BasicType::Ptr createAgentType( SourceLocation& sourceLocation )
{
    const auto name = Ast::make< Identifier >( sourceLocation, "Agent" );
    const auto path = Ast::make< IdentifierPath >( sourceLocation, name );
    const auto node = Ast::make< BasicType >( sourceLocation, path );
    return node;
}

static FunctionDefinition::Ptr createProgramFunction( SourceLocation& sourceLocation )
{
    const auto agentType = createAgentType( sourceLocation );
    const auto ruleRefType = createRuleRefType( sourceLocation );

    const auto argTypes = Ast::make< Types >( sourceLocation );
    argTypes->add( agentType );

    const auto program = Ast::make< Identifier >( sourceLocation, "program" );
    return Ast::make< FunctionDefinition >( sourceLocation, program, argTypes, ruleRefType );
}

static Rule::Ptr wrapInBlockRule( const Rule::Ptr& rule )
{
    if( rule == nullptr )
    {
        // this can happen while recovering from a syntax error
        return nullptr;
    }

    if( ( rule->id() == Node::ID::BLOCK_RULE ) or ( rule->id() == Node::ID::SEQUENCE_RULE ) )
    {
        return rule;  // no need to wrap it
    }

    const auto& sourceLocation = rule->sourceLocation();
    const auto rules = Ast::make< Rules >( sourceLocation );
    rules->add( rule );
    return Ast::make< BlockRule >( sourceLocation, rules );
}

#line 125 "GrammarParser.cpp"  // lalr1.cc:413

#ifndef YY_
#if defined YYENABLE_NLS && YYENABLE_NLS
#if ENABLE_NLS
#include <libintl.h>  // FIXME: INFRINGES ON USER NAME SPACE.
#define YY_( msgid ) dgettext( "bison-runtime", msgid )
#endif
#endif
#ifndef YY_
#define YY_( msgid ) msgid
#endif
#endif

#define YYRHSLOC( Rhs, K ) ( ( Rhs )[ K ].location )
    /* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
       If N is 0, then set CURRENT to the empty location which ends
       the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
#define YYLLOC_DEFAULT( Current, Rhs, N )                                 \
    do                                                                    \
        if( N )                                                           \
        {                                                                 \
            ( Current ).begin = YYRHSLOC( Rhs, 1 ).begin;                 \
            ( Current ).end = YYRHSLOC( Rhs, N ).end;                     \
        }                                                                 \
        else                                                              \
        {                                                                 \
            ( Current ).begin = ( Current ).end = YYRHSLOC( Rhs, 0 ).end; \
        }                                                                 \
    while( /*CONSTCOND*/ false )
#endif

// Suppress unused-variable warnings by "using" E.
#define YYUSE( E ) ( (void)( E ) )

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
#define YYCDEBUG   \
    if( yydebug_ ) \
    ( *yycdebug_ )

#define YY_SYMBOL_PRINT( Title, Symbol )     \
    do                                       \
    {                                        \
        if( yydebug_ )                       \
        {                                    \
            *yycdebug_ << Title << ' ';      \
            yy_print_( *yycdebug_, Symbol ); \
            *yycdebug_ << std::endl;         \
        }                                    \
    } while( false )

#define YY_REDUCE_PRINT( Rule )       \
    do                                \
    {                                 \
        if( yydebug_ )                \
            yy_reduce_print_( Rule ); \
    } while( false )

#define YY_STACK_PRINT()      \
    do                        \
    {                         \
        if( yydebug_ )        \
            yystack_print_(); \
    } while( false )

#else  // !YYDEBUG

#define YYCDEBUG \
    if( false )  \
    std::cerr
#define YY_SYMBOL_PRINT( Title, Symbol ) YYUSE( Symbol )
#define YY_REDUCE_PRINT( Rule ) static_cast< void >( 0 )
#define YY_STACK_PRINT() static_cast< void >( 0 )

#endif  // !YYDEBUG

#define yyerrok ( yyerrstatus_ = 0 )
#define yyclearin ( yyla.clear() )

#define YYACCEPT goto yyacceptlab
#define YYABORT goto yyabortlab
#define YYERROR goto yyerrorlab
#define YYRECOVERING() ( !!yyerrstatus_ )

#line 49 "../../obj/src/GrammarParser.yy"  // lalr1.cc:479
namespace libcasm_fe
{
#line 211 "GrammarParser.cpp"  // lalr1.cc:479

    /* Return YYSTR after stripping away unnecessary quotes and
       backslashes, so that it's suitable for yyerror.  The heuristic is
       that double-quoting is unnecessary unless the string contains an
       apostrophe, a comma, or backslash (other than backslash-backslash).
       YYSTR is taken from yytname.  */
    std::string Parser::yytnamerr_( const char* yystr )
    {
        if( *yystr == '"' )
        {
            std::string yyr = "";
            char const* yyp = yystr;

            for( ;; )
                switch( *++yyp )
                {
                    case '\'':
                    case ',':
                        goto do_not_strip_quotes;

                    case '\\':
                        if( *++yyp != '\\' )
                            goto do_not_strip_quotes;
                        // Fall through.
                    default:
                        yyr += *yyp;
                        break;

                    case '"':
                        return yyr;
                }
        do_not_strip_quotes:;
        }

        return yystr;
    }

    /// Build a parser object.
    Parser::Parser( Logger& log_yyarg, Lexer& lexer_yyarg, Specification& specification_yyarg )
    :
#if YYDEBUG
        yydebug_( false )
    , yycdebug_( &std::cerr )
    ,
#endif
        log( log_yyarg )
    , lexer( lexer_yyarg )
    , specification( specification_yyarg )
    {
    }

    Parser::~Parser()
    {
    }

    /*---------------.
    | Symbol types.  |
    `---------------*/

    // by_state.
    inline Parser::by_state::by_state()
    : state( empty_state )
    {
    }

    inline Parser::by_state::by_state( const by_state& other )
    : state( other.state )
    {
    }

    inline void Parser::by_state::clear()
    {
        state = empty_state;
    }

    inline void Parser::by_state::move( by_state& that )
    {
        state = that.state;
        that.clear();
    }

    inline Parser::by_state::by_state( state_type s )
    : state( s )
    {
    }

    inline Parser::symbol_number_type Parser::by_state::type_get() const
    {
        if( state == empty_state )
            return empty_symbol;
        else
            return yystos_[ state ];
    }

    inline Parser::stack_symbol_type::stack_symbol_type()
    {
    }

    inline Parser::stack_symbol_type::stack_symbol_type( state_type s, symbol_type& that )
    : super_type( s, that.location )
    {
        switch( that.type_get() )
        {
            case 161:  // Attribute
                value.move< Attribute::Ptr >( that.value );
                break;

            case 160:  // Attributes
                value.move< Attributes::Ptr >( that.value );
                break;

            case 162:  // BasicAttribute
                value.move< BasicAttribute::Ptr >( that.value );
                break;

            case 138:  // BasicType
                value.move< BasicType::Ptr >( that.value );
                break;

            case 108:  // BlockRule
                value.move< BlockRule::Ptr >( that.value );
                break;

            case 116:  // CallExpression
                value.move< CallExpression::Ptr >( that.value );
                break;

            case 111:  // CallRule
                value.move< CallRule::Ptr >( that.value );
                break;

            case 102:  // CaseLabel
                value.move< Case::Ptr >( that.value );
                break;

            case 101:  // CaseRule
                value.move< CaseRule::Ptr >( that.value );
                break;

            case 103:  // CaseLabels
                value.move< Cases::Ptr >( that.value );
                break;

            case 122:  // ChooseExpression
                value.move< ChooseExpression::Ptr >( that.value );
                break;

            case 106:  // ChooseRule
                value.move< ChooseRule::Ptr >( that.value );
                break;

            case 139:  // ComposedType
                value.move< ComposedType::Ptr >( that.value );
                break;

            case 121:  // ConditionalExpression
                value.move< ConditionalExpression::Ptr >( that.value );
                break;

            case 100:  // ConditionalRule
                value.move< ConditionalRule::Ptr >( that.value );
                break;

            case 88:  // AttributedDefinition
            case 89:  // Definition
                value.move< Definition::Ptr >( that.value );
                break;

            case 87:  // Definitions
                value.move< Definitions::Ptr >( that.value );
                break;

            case 91:  // DerivedDefinition
                value.move< DerivedDefinition::Ptr >( that.value );
                break;

            case 117:  // DirectCallExpression
                value.move< DirectCallExpression::Ptr >( that.value );
                break;

            case 90:  // EnumerationDefinition
                value.move< EnumerationDefinition::Ptr >( that.value );
                break;

            case 95:  // EnumeratorDefinition
                value.move< EnumeratorDefinition::Ptr >( that.value );
                break;

            case 96:  // Enumerators
                value.move< Enumerators::Ptr >( that.value );
                break;

            case 124:  // ExistentialQuantifierExpression
                value.move< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 113:  // Term
            case 114:  // Expression
            case 127:  // Literal
            case 148:  // MaybeDefined
                value.move< Expression::Ptr >( that.value );
                break;

            case 163:  // ExpressionAttribute
                value.move< ExpressionAttribute::Ptr >( that.value );
                break;

            case 112:  // Terms
            case 142:  // Arguments
            case 143:  // TwoOrMoreArguments
                value.move< Expressions::Ptr >( that.value );
                break;

            case 141:  // FixedSizedType
                value.move< FixedSizedType::Ptr >( that.value );
                break;

            case 105:  // ForallRule
                value.move< ForallRule::Ptr >( that.value );
                break;

            case 93:  // FunctionDefinition
            case 94:  // ProgramFunctionDefinition
                value.move< FunctionDefinition::Ptr >( that.value );
                break;

            case 86:  // Header
                value.move< HeaderDefinition::Ptr >( that.value );
                break;

            case 153:  // Identifier
                value.move< Identifier::Ptr >( that.value );
                break;

            case 154:  // IdentifierPath
                value.move< IdentifierPath::Ptr >( that.value );
                break;

            case 155:  // DotSeparatedIdentifiers
                value.move< Identifiers::Ptr >( that.value );
                break;

            case 118:  // IndirectCallExpression
                value.move< IndirectCallExpression::Ptr >( that.value );
                break;

            case 107:  // IterateRule
                value.move< IterateRule::Ptr >( that.value );
                break;

            case 120:  // LetExpression
                value.move< LetExpression::Ptr >( that.value );
                break;

            case 104:  // LetRule
                value.move< LetRule::Ptr >( that.value );
                break;

            case 125:  // List
                value.move< ListExpression::Ptr >( that.value );
                break;

            case 119:  // MethodCallExpression
                value.move< MethodCallExpression::Ptr >( that.value );
                break;

            case 149:  // MaybeInitially
            case 150:  // Initializers
            case 152:  // MaybeInitializers
                value.move< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 146:  // Parameters
            case 147:  // MaybeParameters
                value.move< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 126:  // Range
                value.move< RangeExpression::Ptr >( that.value );
                break;

            case 135:  // ReferenceLiteral
                value.move< ReferenceAtom::Ptr >( that.value );
                break;

            case 140:  // RelationType
                value.move< RelationType::Ptr >( that.value );
                break;

            case 97:  // Rule
                value.move< Rule::Ptr >( that.value );
                break;

            case 92:  // RuleDefinition
                value.move< RuleDefinition::Ptr >( that.value );
                break;

            case 98:  // Rules
                value.move< Rules::Ptr >( that.value );
                break;

            case 109:  // SequenceRule
                value.move< SequenceRule::Ptr >( that.value );
                break;

            case 99:  // SkipRule
                value.move< SkipRule::Ptr >( that.value );
                break;

            case 85:  // Specification
                value.move< Specification::Ptr >( that.value );
                break;

            case 115:  // TypeCastingExpression
                value.move< TypeCastingExpression::Ptr >( that.value );
                break;

            case 136:  // Types
            case 144:  // FunctionParameters
            case 145:  // MaybeFunctionParameters
                value.move< Types::Ptr >( that.value );
                break;

            case 128:  // UndefinedLiteral
                value.move< UndefAtom::Ptr >( that.value );
                break;

            case 123:  // UniversalQuantifierExpression
                value.move< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 110:  // UpdateRule
            case 151:  // Initializer
                value.move< UpdateRule::Ptr >( that.value );
                break;

            case 129:  // BooleanLiteral
            case 130:  // IntegerLiteral
            case 131:  // RationalLiteral
            case 132:  // DecimalLiteral
            case 133:  // BinaryLiteral
            case 134:  // StringLiteral
                value.move< ValueAtom::Ptr >( that.value );
                break;

            case 156:  // Variable
            case 157:  // TypedVariable
            case 158:  // AttributedVariable
            case 159:  // TypedAttributedVariable
                value.move< VariableDefinition::Ptr >( that.value );
                break;

            case 137:  // Type
                value.move< libcasm_fe::Ast::Type::Ptr >( that.value );
                break;

            case 71:  // "binary"
            case 72:  // "hexadecimal"
            case 73:  // "integer"
            case 74:  // "rational"
            case 75:  // "decimal"
            case 76:  // "string"
            case 77:  // "identifier"
                value.move< std::string >( that.value );
                break;

            default:
                break;
        }

        // that is emptied.
        that.type = empty_symbol;
    }

    inline Parser::stack_symbol_type& Parser::stack_symbol_type::operator=(
        const stack_symbol_type& that )
    {
        state = that.state;
        switch( that.type_get() )
        {
            case 161:  // Attribute
                value.copy< Attribute::Ptr >( that.value );
                break;

            case 160:  // Attributes
                value.copy< Attributes::Ptr >( that.value );
                break;

            case 162:  // BasicAttribute
                value.copy< BasicAttribute::Ptr >( that.value );
                break;

            case 138:  // BasicType
                value.copy< BasicType::Ptr >( that.value );
                break;

            case 108:  // BlockRule
                value.copy< BlockRule::Ptr >( that.value );
                break;

            case 116:  // CallExpression
                value.copy< CallExpression::Ptr >( that.value );
                break;

            case 111:  // CallRule
                value.copy< CallRule::Ptr >( that.value );
                break;

            case 102:  // CaseLabel
                value.copy< Case::Ptr >( that.value );
                break;

            case 101:  // CaseRule
                value.copy< CaseRule::Ptr >( that.value );
                break;

            case 103:  // CaseLabels
                value.copy< Cases::Ptr >( that.value );
                break;

            case 122:  // ChooseExpression
                value.copy< ChooseExpression::Ptr >( that.value );
                break;

            case 106:  // ChooseRule
                value.copy< ChooseRule::Ptr >( that.value );
                break;

            case 139:  // ComposedType
                value.copy< ComposedType::Ptr >( that.value );
                break;

            case 121:  // ConditionalExpression
                value.copy< ConditionalExpression::Ptr >( that.value );
                break;

            case 100:  // ConditionalRule
                value.copy< ConditionalRule::Ptr >( that.value );
                break;

            case 88:  // AttributedDefinition
            case 89:  // Definition
                value.copy< Definition::Ptr >( that.value );
                break;

            case 87:  // Definitions
                value.copy< Definitions::Ptr >( that.value );
                break;

            case 91:  // DerivedDefinition
                value.copy< DerivedDefinition::Ptr >( that.value );
                break;

            case 117:  // DirectCallExpression
                value.copy< DirectCallExpression::Ptr >( that.value );
                break;

            case 90:  // EnumerationDefinition
                value.copy< EnumerationDefinition::Ptr >( that.value );
                break;

            case 95:  // EnumeratorDefinition
                value.copy< EnumeratorDefinition::Ptr >( that.value );
                break;

            case 96:  // Enumerators
                value.copy< Enumerators::Ptr >( that.value );
                break;

            case 124:  // ExistentialQuantifierExpression
                value.copy< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 113:  // Term
            case 114:  // Expression
            case 127:  // Literal
            case 148:  // MaybeDefined
                value.copy< Expression::Ptr >( that.value );
                break;

            case 163:  // ExpressionAttribute
                value.copy< ExpressionAttribute::Ptr >( that.value );
                break;

            case 112:  // Terms
            case 142:  // Arguments
            case 143:  // TwoOrMoreArguments
                value.copy< Expressions::Ptr >( that.value );
                break;

            case 141:  // FixedSizedType
                value.copy< FixedSizedType::Ptr >( that.value );
                break;

            case 105:  // ForallRule
                value.copy< ForallRule::Ptr >( that.value );
                break;

            case 93:  // FunctionDefinition
            case 94:  // ProgramFunctionDefinition
                value.copy< FunctionDefinition::Ptr >( that.value );
                break;

            case 86:  // Header
                value.copy< HeaderDefinition::Ptr >( that.value );
                break;

            case 153:  // Identifier
                value.copy< Identifier::Ptr >( that.value );
                break;

            case 154:  // IdentifierPath
                value.copy< IdentifierPath::Ptr >( that.value );
                break;

            case 155:  // DotSeparatedIdentifiers
                value.copy< Identifiers::Ptr >( that.value );
                break;

            case 118:  // IndirectCallExpression
                value.copy< IndirectCallExpression::Ptr >( that.value );
                break;

            case 107:  // IterateRule
                value.copy< IterateRule::Ptr >( that.value );
                break;

            case 120:  // LetExpression
                value.copy< LetExpression::Ptr >( that.value );
                break;

            case 104:  // LetRule
                value.copy< LetRule::Ptr >( that.value );
                break;

            case 125:  // List
                value.copy< ListExpression::Ptr >( that.value );
                break;

            case 119:  // MethodCallExpression
                value.copy< MethodCallExpression::Ptr >( that.value );
                break;

            case 149:  // MaybeInitially
            case 150:  // Initializers
            case 152:  // MaybeInitializers
                value.copy< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 146:  // Parameters
            case 147:  // MaybeParameters
                value.copy< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 126:  // Range
                value.copy< RangeExpression::Ptr >( that.value );
                break;

            case 135:  // ReferenceLiteral
                value.copy< ReferenceAtom::Ptr >( that.value );
                break;

            case 140:  // RelationType
                value.copy< RelationType::Ptr >( that.value );
                break;

            case 97:  // Rule
                value.copy< Rule::Ptr >( that.value );
                break;

            case 92:  // RuleDefinition
                value.copy< RuleDefinition::Ptr >( that.value );
                break;

            case 98:  // Rules
                value.copy< Rules::Ptr >( that.value );
                break;

            case 109:  // SequenceRule
                value.copy< SequenceRule::Ptr >( that.value );
                break;

            case 99:  // SkipRule
                value.copy< SkipRule::Ptr >( that.value );
                break;

            case 85:  // Specification
                value.copy< Specification::Ptr >( that.value );
                break;

            case 115:  // TypeCastingExpression
                value.copy< TypeCastingExpression::Ptr >( that.value );
                break;

            case 136:  // Types
            case 144:  // FunctionParameters
            case 145:  // MaybeFunctionParameters
                value.copy< Types::Ptr >( that.value );
                break;

            case 128:  // UndefinedLiteral
                value.copy< UndefAtom::Ptr >( that.value );
                break;

            case 123:  // UniversalQuantifierExpression
                value.copy< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 110:  // UpdateRule
            case 151:  // Initializer
                value.copy< UpdateRule::Ptr >( that.value );
                break;

            case 129:  // BooleanLiteral
            case 130:  // IntegerLiteral
            case 131:  // RationalLiteral
            case 132:  // DecimalLiteral
            case 133:  // BinaryLiteral
            case 134:  // StringLiteral
                value.copy< ValueAtom::Ptr >( that.value );
                break;

            case 156:  // Variable
            case 157:  // TypedVariable
            case 158:  // AttributedVariable
            case 159:  // TypedAttributedVariable
                value.copy< VariableDefinition::Ptr >( that.value );
                break;

            case 137:  // Type
                value.copy< libcasm_fe::Ast::Type::Ptr >( that.value );
                break;

            case 71:  // "binary"
            case 72:  // "hexadecimal"
            case 73:  // "integer"
            case 74:  // "rational"
            case 75:  // "decimal"
            case 76:  // "string"
            case 77:  // "identifier"
                value.copy< std::string >( that.value );
                break;

            default:
                break;
        }

        location = that.location;
        return *this;
    }

    template < typename Base >
    inline void Parser::yy_destroy_( const char* yymsg, basic_symbol< Base >& yysym ) const
    {
        if( yymsg )
            YY_SYMBOL_PRINT( yymsg, yysym );
    }

#if YYDEBUG
    template < typename Base >
    void Parser::yy_print_( std::ostream& yyo, const basic_symbol< Base >& yysym ) const
    {
        std::ostream& yyoutput = yyo;
        YYUSE( yyoutput );
        symbol_number_type yytype = yysym.type_get();
        // Avoid a (spurious) G++ 4.8 warning about "array subscript is
        // below array bounds".
        if( yysym.empty() )
            std::abort();
        yyo << ( yytype < yyntokens_ ? "token" : "nterm" ) << ' ' << yytname_[ yytype ] << " ("
            << yysym.location << ": ";
        YYUSE( yytype );
        yyo << ')';
    }
#endif

    inline void Parser::yypush_( const char* m, state_type s, symbol_type& sym )
    {
        stack_symbol_type t( s, sym );
        yypush_( m, t );
    }

    inline void Parser::yypush_( const char* m, stack_symbol_type& s )
    {
        if( m )
            YY_SYMBOL_PRINT( m, s );
        yystack_.push( s );
    }

    inline void Parser::yypop_( unsigned int n )
    {
        yystack_.pop( n );
    }

#if YYDEBUG
    std::ostream& Parser::debug_stream() const
    {
        return *yycdebug_;
    }

    void Parser::set_debug_stream( std::ostream& o )
    {
        yycdebug_ = &o;
    }

    Parser::debug_level_type Parser::debug_level() const
    {
        return yydebug_;
    }

    void Parser::set_debug_level( debug_level_type l )
    {
        yydebug_ = l;
    }
#endif  // YYDEBUG

    inline Parser::state_type Parser::yy_lr_goto_state_( state_type yystate, int yysym )
    {
        int yyr = yypgoto_[ yysym - yyntokens_ ] + yystate;
        if( 0 <= yyr && yyr <= yylast_ && yycheck_[ yyr ] == yystate )
            return yytable_[ yyr ];
        else
            return yydefgoto_[ yysym - yyntokens_ ];
    }

    inline bool Parser::yy_pact_value_is_default_( int yyvalue )
    {
        return yyvalue == yypact_ninf_;
    }

    inline bool Parser::yy_table_value_is_error_( int yyvalue )
    {
        return yyvalue == yytable_ninf_;
    }

    int Parser::parse()
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
        stack_symbol_type yyerror_range[ 3 ];

        /// The return value of parse ().
        int yyresult;

        // FIXME: This shoud be completely indented.  It is not yet to
        // avoid gratuitous conflicts when merging into the master branch.
        try
        {
            YYCDEBUG << "Starting parse" << std::endl;

            /* Initialize the stack.  The initial state will be set in
               yynewstate, since the latter expects the semantical and the
               location values to have been already stored, initialize these
               stacks with a primary value.  */
            yystack_.clear();
            yypush_( YY_NULLPTR, 0, yyla );

            // A new symbol was pushed on the stack.
        yynewstate:
            YYCDEBUG << "Entering state " << yystack_[ 0 ].state << std::endl;

            // Accept?
            if( yystack_[ 0 ].state == yyfinal_ )
                goto yyacceptlab;

            goto yybackup;

            // Backup.
        yybackup:

            // Try to take a decision without lookahead.
            yyn = yypact_[ yystack_[ 0 ].state ];
            if( yy_pact_value_is_default_( yyn ) )
                goto yydefault;

            // Read a lookahead token.
            if( yyla.empty() )
            {
                YYCDEBUG << "Reading a token: ";
                try
                {
                    symbol_type yylookahead( yylex() );
                    yyla.move( yylookahead );
                }
                catch( const syntax_error& yyexc )
                {
                    error( yyexc );
                    goto yyerrlab1;
                }
            }
            YY_SYMBOL_PRINT( "Next token is", yyla );

            /* If the proper action on seeing token YYLA.TYPE is to reduce or
               to detect an error, take that action.  */
            yyn += yyla.type_get();
            if( yyn < 0 || yylast_ < yyn || yycheck_[ yyn ] != yyla.type_get() )
                goto yydefault;

            // Reduce or error.
            yyn = yytable_[ yyn ];
            if( yyn <= 0 )
            {
                if( yy_table_value_is_error_( yyn ) )
                    goto yyerrlab;
                yyn = -yyn;
                goto yyreduce;
            }

            // Count tokens shifted since error; after three, turn off error status.
            if( yyerrstatus_ )
                --yyerrstatus_;

            // Shift the lookahead token.
            yypush_( "Shifting", yyn, yyla );
            goto yynewstate;

        /*-----------------------------------------------------------.
        | yydefault -- do the default action for the current state.  |
        `-----------------------------------------------------------*/
        yydefault:
            yyn = yydefact_[ yystack_[ 0 ].state ];
            if( yyn == 0 )
                goto yyerrlab;
            goto yyreduce;

        /*-----------------------------.
        | yyreduce -- Do a reduction.  |
        `-----------------------------*/
        yyreduce:
            yylen = yyr2_[ yyn ];
            {
                stack_symbol_type yylhs;
                yylhs.state = yy_lr_goto_state_( yystack_[ yylen ].state, yyr1_[ yyn ] );
                /* Variants are always initialized to an empty instance of the
                   correct type. The default '$$ = $1' action is NOT applied
                   when using variants.  */
                switch( yyr1_[ yyn ] )
                {
                    case 161:  // Attribute
                        yylhs.value.build< Attribute::Ptr >();
                        break;

                    case 160:  // Attributes
                        yylhs.value.build< Attributes::Ptr >();
                        break;

                    case 162:  // BasicAttribute
                        yylhs.value.build< BasicAttribute::Ptr >();
                        break;

                    case 138:  // BasicType
                        yylhs.value.build< BasicType::Ptr >();
                        break;

                    case 108:  // BlockRule
                        yylhs.value.build< BlockRule::Ptr >();
                        break;

                    case 116:  // CallExpression
                        yylhs.value.build< CallExpression::Ptr >();
                        break;

                    case 111:  // CallRule
                        yylhs.value.build< CallRule::Ptr >();
                        break;

                    case 102:  // CaseLabel
                        yylhs.value.build< Case::Ptr >();
                        break;

                    case 101:  // CaseRule
                        yylhs.value.build< CaseRule::Ptr >();
                        break;

                    case 103:  // CaseLabels
                        yylhs.value.build< Cases::Ptr >();
                        break;

                    case 122:  // ChooseExpression
                        yylhs.value.build< ChooseExpression::Ptr >();
                        break;

                    case 106:  // ChooseRule
                        yylhs.value.build< ChooseRule::Ptr >();
                        break;

                    case 139:  // ComposedType
                        yylhs.value.build< ComposedType::Ptr >();
                        break;

                    case 121:  // ConditionalExpression
                        yylhs.value.build< ConditionalExpression::Ptr >();
                        break;

                    case 100:  // ConditionalRule
                        yylhs.value.build< ConditionalRule::Ptr >();
                        break;

                    case 88:  // AttributedDefinition
                    case 89:  // Definition
                        yylhs.value.build< Definition::Ptr >();
                        break;

                    case 87:  // Definitions
                        yylhs.value.build< Definitions::Ptr >();
                        break;

                    case 91:  // DerivedDefinition
                        yylhs.value.build< DerivedDefinition::Ptr >();
                        break;

                    case 117:  // DirectCallExpression
                        yylhs.value.build< DirectCallExpression::Ptr >();
                        break;

                    case 90:  // EnumerationDefinition
                        yylhs.value.build< EnumerationDefinition::Ptr >();
                        break;

                    case 95:  // EnumeratorDefinition
                        yylhs.value.build< EnumeratorDefinition::Ptr >();
                        break;

                    case 96:  // Enumerators
                        yylhs.value.build< Enumerators::Ptr >();
                        break;

                    case 124:  // ExistentialQuantifierExpression
                        yylhs.value.build< ExistentialQuantifierExpression::Ptr >();
                        break;

                    case 113:  // Term
                    case 114:  // Expression
                    case 127:  // Literal
                    case 148:  // MaybeDefined
                        yylhs.value.build< Expression::Ptr >();
                        break;

                    case 163:  // ExpressionAttribute
                        yylhs.value.build< ExpressionAttribute::Ptr >();
                        break;

                    case 112:  // Terms
                    case 142:  // Arguments
                    case 143:  // TwoOrMoreArguments
                        yylhs.value.build< Expressions::Ptr >();
                        break;

                    case 141:  // FixedSizedType
                        yylhs.value.build< FixedSizedType::Ptr >();
                        break;

                    case 105:  // ForallRule
                        yylhs.value.build< ForallRule::Ptr >();
                        break;

                    case 93:  // FunctionDefinition
                    case 94:  // ProgramFunctionDefinition
                        yylhs.value.build< FunctionDefinition::Ptr >();
                        break;

                    case 86:  // Header
                        yylhs.value.build< HeaderDefinition::Ptr >();
                        break;

                    case 153:  // Identifier
                        yylhs.value.build< Identifier::Ptr >();
                        break;

                    case 154:  // IdentifierPath
                        yylhs.value.build< IdentifierPath::Ptr >();
                        break;

                    case 155:  // DotSeparatedIdentifiers
                        yylhs.value.build< Identifiers::Ptr >();
                        break;

                    case 118:  // IndirectCallExpression
                        yylhs.value.build< IndirectCallExpression::Ptr >();
                        break;

                    case 107:  // IterateRule
                        yylhs.value.build< IterateRule::Ptr >();
                        break;

                    case 120:  // LetExpression
                        yylhs.value.build< LetExpression::Ptr >();
                        break;

                    case 104:  // LetRule
                        yylhs.value.build< LetRule::Ptr >();
                        break;

                    case 125:  // List
                        yylhs.value.build< ListExpression::Ptr >();
                        break;

                    case 119:  // MethodCallExpression
                        yylhs.value.build< MethodCallExpression::Ptr >();
                        break;

                    case 149:  // MaybeInitially
                    case 150:  // Initializers
                    case 152:  // MaybeInitializers
                        yylhs.value.build< NodeList< UpdateRule >::Ptr >();
                        break;

                    case 146:  // Parameters
                    case 147:  // MaybeParameters
                        yylhs.value.build< NodeList< VariableDefinition >::Ptr >();
                        break;

                    case 126:  // Range
                        yylhs.value.build< RangeExpression::Ptr >();
                        break;

                    case 135:  // ReferenceLiteral
                        yylhs.value.build< ReferenceAtom::Ptr >();
                        break;

                    case 140:  // RelationType
                        yylhs.value.build< RelationType::Ptr >();
                        break;

                    case 97:  // Rule
                        yylhs.value.build< Rule::Ptr >();
                        break;

                    case 92:  // RuleDefinition
                        yylhs.value.build< RuleDefinition::Ptr >();
                        break;

                    case 98:  // Rules
                        yylhs.value.build< Rules::Ptr >();
                        break;

                    case 109:  // SequenceRule
                        yylhs.value.build< SequenceRule::Ptr >();
                        break;

                    case 99:  // SkipRule
                        yylhs.value.build< SkipRule::Ptr >();
                        break;

                    case 85:  // Specification
                        yylhs.value.build< Specification::Ptr >();
                        break;

                    case 115:  // TypeCastingExpression
                        yylhs.value.build< TypeCastingExpression::Ptr >();
                        break;

                    case 136:  // Types
                    case 144:  // FunctionParameters
                    case 145:  // MaybeFunctionParameters
                        yylhs.value.build< Types::Ptr >();
                        break;

                    case 128:  // UndefinedLiteral
                        yylhs.value.build< UndefAtom::Ptr >();
                        break;

                    case 123:  // UniversalQuantifierExpression
                        yylhs.value.build< UniversalQuantifierExpression::Ptr >();
                        break;

                    case 110:  // UpdateRule
                    case 151:  // Initializer
                        yylhs.value.build< UpdateRule::Ptr >();
                        break;

                    case 129:  // BooleanLiteral
                    case 130:  // IntegerLiteral
                    case 131:  // RationalLiteral
                    case 132:  // DecimalLiteral
                    case 133:  // BinaryLiteral
                    case 134:  // StringLiteral
                        yylhs.value.build< ValueAtom::Ptr >();
                        break;

                    case 156:  // Variable
                    case 157:  // TypedVariable
                    case 158:  // AttributedVariable
                    case 159:  // TypedAttributedVariable
                        yylhs.value.build< VariableDefinition::Ptr >();
                        break;

                    case 137:  // Type
                        yylhs.value.build< libcasm_fe::Ast::Type::Ptr >();
                        break;

                    case 71:  // "binary"
                    case 72:  // "hexadecimal"
                    case 73:  // "integer"
                    case 74:  // "rational"
                    case 75:  // "decimal"
                    case 76:  // "string"
                    case 77:  // "identifier"
                        yylhs.value.build< std::string >();
                        break;

                    default:
                        break;
                }

                // Compute the default @$.
                {
                    slice< stack_symbol_type, stack_type > slice( yystack_, yylen );
                    YYLLOC_DEFAULT( yylhs.location, slice, yylen );
                }

                // Perform the reduction.
                YY_REDUCE_PRINT( yyn );
                try
                {
                    switch( yyn )
                    {
                        case 2:
#line 379 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            specification.setHeader(
                                yystack_[ 1 ].value.as< HeaderDefinition::Ptr >() );
                            specification.setDefinitions(
                                yystack_[ 0 ].value.as< Definitions::Ptr >() );
                        }
#line 1380 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 3:
#line 388 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< HeaderDefinition::Ptr >() = definition;
                        }
#line 1390 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 4:
#line 394 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< HeaderDefinition::Ptr >() =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                        }
#line 1398 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 5:
#line 402 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = yystack_[ 1 ].value.as< Definitions::Ptr >();
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1408 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 6:
#line 408 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = Ast::make< Definitions >( yylhs.location );
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1418 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 7:
#line 418 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition = yystack_[ 0 ].value.as< Definition::Ptr >();
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< Definition::Ptr >() = definition;
                        }
#line 1428 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 8:
#line 424 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< Definition::Ptr >();
                        }
#line 1436 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 9:
#line 428 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() = nullptr;
                        }
#line 1444 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 10:
#line 436 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< EnumerationDefinition::Ptr >();
                        }
#line 1452 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 11:
#line 440 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< DerivedDefinition::Ptr >();
                        }
#line 1460 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 12:
#line 444 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< RuleDefinition::Ptr >();
                        }
#line 1468 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 13:
#line 448 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< FunctionDefinition::Ptr >();
                        }
#line 1476 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 14:
#line 456 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumerationDefinition::Ptr >() =
                                Ast::make< EnumerationDefinition >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 1 ].value.as< Enumerators::Ptr >() );
                        }
#line 1484 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 15:
#line 464 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DerivedDefinition::Ptr >() =
                                Ast::make< DerivedDefinition >(
                                    yylhs.location,
                                    yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                    yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1492 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 16:
#line 472 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Identifier::Ptr >(),
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                createVoidType( yylhs.location ),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1501 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 17:
#line 477 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1510 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 18:
#line 486 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto identifier = yystack_[ 6 ].value.as< Identifier::Ptr >();

                            auto function = Ast::make< FunctionDefinition >(
                                yylhs.location,
                                identifier,
                                yystack_[ 4 ].value.as< Types::Ptr >(),
                                yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            function->setDefaultValue(
                                yystack_[ 1 ].value.as< Expression::Ptr >() );

                            // apply the name of the function declaration to the initializer
                            // functions
                            auto initializers =
                                yystack_[ 0 ].value.as< NodeList< UpdateRule >::Ptr >();
                            for( auto& initializer : *initializers )
                            {
                                initializer->function()->setIdentifier( identifier );
                            }
                            function->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = function;
                        }
#line 1530 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 19:
#line 502 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FunctionDefinition::Ptr >() =
                                yystack_[ 0 ]
                                    .value.as< FunctionDefinition::Ptr >();  // `init` special case
                        }
#line 1538 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 20:
#line 510 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto singleAgentIdentifier =
                                Ast::make< Identifier >( yylhs.location, "$" );
                            auto singleAgentArguments =
                                libcasm_fe::Ast::make< Expressions >( yylhs.location );
                            const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
                                yylhs.location, singleAgentIdentifier, singleAgentArguments );
                            singleAgent->setTargetType( CallExpression::TargetType::CONSTANT );

                            auto programDefinition = createProgramFunction( yylhs.location );
                            auto programArguments =
                                libcasm_fe::Ast::make< Expressions >( yylhs.location );
                            programArguments->add( singleAgent );
                            const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
                                yylhs.location, programDefinition->identifier(), programArguments );
                            program->setTargetType( CallExpression::TargetType::FUNCTION );

                            const auto ruleReference = Ast::make< ReferenceAtom >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );

                            auto initializers =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                            initializers->add(
                                Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
                            programDefinition->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = programDefinition;
                        }
#line 1565 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 21:
#line 533 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto programDefinition = createProgramFunction( yylhs.location );

                            // apply the name of the program declaration to the initializer
                            // functions
                            auto initializers =
                                yystack_[ 1 ].value.as< NodeList< UpdateRule >::Ptr >();
                            for( auto& initializer : *initializers )
                            {
                                initializer->function()->setIdentifier(
                                    programDefinition->identifier() );
                            }
                            programDefinition->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = programDefinition;
                        }
#line 1582 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 22:
#line 550 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() =
                                Ast::make< EnumeratorDefinition >(
                                    yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 1590 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 23:
#line 554 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerator = Ast::make< EnumeratorDefinition >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            enumerator->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = enumerator;
                        }
#line 1600 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 24:
#line 560 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = nullptr;
                        }
#line 1608 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 25:
#line 568 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = yystack_[ 2 ].value.as< Enumerators::Ptr >();
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1618 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 26:
#line 574 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = Ast::make< Enumerators >( yylhs.location );
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1628 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 27:
#line 588 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SkipRule::Ptr >();
                        }
#line 1636 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 28:
#line 592 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalRule::Ptr >();
                        }
#line 1644 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 29:
#line 596 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CaseRule::Ptr >();
                        }
#line 1652 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 30:
#line 600 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< LetRule::Ptr >();
                        }
#line 1660 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 31:
#line 604 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ForallRule::Ptr >();
                        }
#line 1668 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 32:
#line 608 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseRule::Ptr >();
                        }
#line 1676 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 33:
#line 612 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< IterateRule::Ptr >();
                        }
#line 1684 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 34:
#line 616 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< BlockRule::Ptr >();
                        }
#line 1692 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 35:
#line 620 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SequenceRule::Ptr >();
                        }
#line 1700 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 36:
#line 624 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRule::Ptr >();
                        }
#line 1708 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 37:
#line 628 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CallRule::Ptr >();
                        }
#line 1716 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 38:
#line 636 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = yystack_[ 1 ].value.as< Rules::Ptr >();
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1726 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 39:
#line 642 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = Ast::make< Rules >( yylhs.location );
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1736 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 40:
#line 652 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SkipRule::Ptr >() =
                                Ast::make< SkipRule >( yylhs.location );
                        }
#line 1744 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 41:
#line 660 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1752 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 42:
#line 664 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Rule::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1760 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 43:
#line 672 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = Ast::make< CaseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Cases::Ptr >() );
                        }
#line 1768 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 44:
#line 676 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = nullptr;
                        }
#line 1776 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 45:
#line 684 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1784 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 46:
#line 688 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1792 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 47:
#line 692 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< ExpressionCase >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1800 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 48:
#line 700 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = yystack_[ 1 ].value.as< Cases::Ptr >();
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1810 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 49:
#line 706 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = Ast::make< Cases >( yylhs.location );
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1820 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 50:
#line 716 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetRule::Ptr >() = Ast::make< LetRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1828 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 51:
#line 724 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1836 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 52:
#line 728 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 6 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1844 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 53:
#line 736 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseRule::Ptr >() = Ast::make< ChooseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1852 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 54:
#line 744 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IterateRule::Ptr >() = Ast::make< IterateRule >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1860 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 55:
#line 752 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1868 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 56:
#line 756 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1876 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 57:
#line 760 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1885 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 58:
#line 765 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1894 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 59:
#line 774 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1902 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 60:
#line 778 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1910 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 61:
#line 782 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1919 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 62:
#line 787 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1928 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 63:
#line 796 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto function =
                                yystack_[ 2 ].value.as< DirectCallExpression::Ptr >();
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1938 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 64:
#line 806 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< CallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 1946 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 65:
#line 810 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< CallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 1954 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 66:
#line 822 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto expressions = yystack_[ 2 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 1964 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 67:
#line 828 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 1974 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 68:
#line 838 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 1982 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 69:
#line 842 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TypeCastingExpression::Ptr >();
                        }
#line 1990 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 70:
#line 846 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< CallExpression::Ptr >();
                        }
#line 1998 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 71:
#line 850 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LetExpression::Ptr >();
                        }
#line 2006 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 72:
#line 854 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalExpression::Ptr >();
                        }
#line 2014 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 73:
#line 858 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseExpression::Ptr >();
                        }
#line 2022 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 74:
#line 862 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UniversalQuantifierExpression::Ptr >();
                        }
#line 2030 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 75:
#line 866 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ExistentialQuantifierExpression::Ptr >();
                        }
#line 2038 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 76:
#line 870 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ListExpression::Ptr >();
                        }
#line 2046 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 77:
#line 874 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< RangeExpression::Ptr >();
                        }
#line 2054 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 78:
#line 878 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2062 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 79:
#line 890 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2070 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 80:
#line 894 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = nullptr;
                        }
#line 2078 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 81:
#line 898 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2086 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 82:
#line 902 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::INV_INSTRUCTION );
                        }
#line 2094 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 83:
#line 906 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::ADD_INSTRUCTION );
                        }
#line 2102 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 84:
#line 910 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::SUB_INSTRUCTION );
                        }
#line 2110 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 85:
#line 914 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MUL_INSTRUCTION );
                        }
#line 2118 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 86:
#line 918 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::DIV_INSTRUCTION );
                        }
#line 2126 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 87:
#line 922 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MOD_INSTRUCTION );
                        }
#line 2134 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 88:
#line 926 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::POW_INSTRUCTION );
                        }
#line 2142 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 89:
#line 930 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NEQ_INSTRUCTION );
                        }
#line 2150 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 90:
#line 934 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::EQU_INSTRUCTION );
                        }
#line 2158 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 91:
#line 938 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LTH_INSTRUCTION );
                        }
#line 2166 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 92:
#line 942 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GTH_INSTRUCTION );
                        }
#line 2174 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 93:
#line 946 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LEQ_INSTRUCTION );
                        }
#line 2182 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 94:
#line 950 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GEQ_INSTRUCTION );
                        }
#line 2190 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 95:
#line 954 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::OR_INSTRUCTION );
                        }
#line 2198 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 96:
#line 958 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::XOR_INSTRUCTION );
                        }
#line 2206 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 97:
#line 962 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::AND_INSTRUCTION );
                        }
#line 2214 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 98:
#line 966 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2222 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 99:
#line 970 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2230 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 100:
#line 974 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NOT_INSTRUCTION );
                        }
#line 2238 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 101:
#line 982 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TypeCastingExpression::Ptr >() =
                                Ast::make< TypeCastingExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2246 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 102:
#line 990 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallExpression::Ptr >() =
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >();
                        }
#line 2254 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 103:
#line 994 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallExpression::Ptr >() =
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >();
                        }
#line 2262 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 104:
#line 998 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallExpression::Ptr >() =
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >();
                        }
#line 2270 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 105:
#line 1006 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2279 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 106:
#line 1011 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2287 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 107:
#line 1019 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IndirectCallExpression::Ptr >() =
                                Ast::make< IndirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2295 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 108:
#line 1027 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 3 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2304 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 109:
#line 1032 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Expression::Ptr >(),
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2312 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 110:
#line 1036 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< CallExpression::Ptr >(),
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2321 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 111:
#line 1041 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 3 ].value.as< CallExpression::Ptr >(),
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2329 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 112:
#line 1045 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto unresolvedNamespace =
                                Ast::make< UnresolvedNamespace >( yylhs.location );
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    unresolvedNamespace,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2339 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 113:
#line 1055 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetExpression::Ptr >() = Ast::make< LetExpression >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2347 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 114:
#line 1063 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalExpression::Ptr >() =
                                Ast::make< ConditionalExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Expression::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2355 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 115:
#line 1071 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseExpression::Ptr >() =
                                Ast::make< ChooseExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2363 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 116:
#line 1079 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UniversalQuantifierExpression::Ptr >() =
                                Ast::make< UniversalQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2371 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 117:
#line 1087 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExistentialQuantifierExpression::Ptr >() =
                                Ast::make< ExistentialQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2379 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 118:
#line 1095 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< ListExpression::Ptr >() =
                                Ast::make< ListExpression >( yylhs.location, expressions );
                        }
#line 2388 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 119:
#line 1100 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListExpression::Ptr >() = Ast::make< ListExpression >(
                                yylhs.location, yystack_[ 1 ].value.as< Expressions::Ptr >() );
                        }
#line 2396 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 120:
#line 1104 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListExpression::Ptr >() = nullptr;
                        }
#line 2404 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 121:
#line 1112 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RangeExpression::Ptr >() = Ast::make< RangeExpression >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Expression::Ptr >() );
                        }
#line 2412 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 122:
#line 1124 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UndefAtom::Ptr >();
                        }
#line 2420 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 123:
#line 1128 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2428 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 124:
#line 1132 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2436 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 125:
#line 1136 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2444 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 126:
#line 1140 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2452 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 127:
#line 1144 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2460 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 128:
#line 1148 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2468 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 129:
#line 1152 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ReferenceAtom::Ptr >();
                        }
#line 2476 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 130:
#line 1160 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UndefAtom::Ptr >() =
                                Ast::make< UndefAtom >( yylhs.location );
                        }
#line 2484 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 131:
#line 1168 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
                            yylhs.value.as< ValueAtom::Ptr >() =
                                Ast::make< ValueAtom >( yylhs.location, value );
                        }
#line 2493 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 132:
#line 1173 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
                            yylhs.value.as< ValueAtom::Ptr >() =
                                Ast::make< ValueAtom >( yylhs.location, value );
                        }
#line 2502 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 133:
#line 1182 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::IntegerConstant >(
                                        yystack_[ 0 ].value.as< std::string >(),
                                        libstdhl::Type::DECIMAL );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2518 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 134:
#line 1198 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::RationalConstant >(
                                        yystack_[ 0 ].value.as< std::string >() );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2534 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 135:
#line 1214 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::DecimalConstant >(
                                        yystack_[ 0 ].value.as< std::string >() );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2550 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 136:
#line 1230 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::BinaryConstant >(
                                        yystack_[ 0 ].value.as< std::string >(),
                                        libstdhl::Type::BINARY );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2566 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 137:
#line 1242 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::BinaryConstant >(
                                        yystack_[ 0 ].value.as< std::string >(),
                                        libstdhl::Type::HEXADECIMAL );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2582 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 138:
#line 1258 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::StringConstant >(
                                        yystack_[ 0 ].value.as< std::string >() );
                                yylhs.value.as< ValueAtom::Ptr >() =
                                    Ast::make< ValueAtom >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2598 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 139:
#line 1274 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ReferenceAtom::Ptr >() = Ast::make< ReferenceAtom >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2606 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 140:
#line 1286 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2616 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 141:
#line 1292 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2626 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 142:
#line 1302 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< BasicType::Ptr >();
                        }
#line 2634 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 143:
#line 1306 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2642 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 144:
#line 1310 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< RelationType::Ptr >();
                        }
#line 2650 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 145:
#line 1314 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< FixedSizedType::Ptr >();
                        }
#line 2658 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 146:
#line 1322 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicType::Ptr >() = Ast::make< BasicType >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2666 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 147:
#line 1330 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ComposedType::Ptr >() = Ast::make< ComposedType >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 1 ].value.as< Types::Ptr >() );
                        }
#line 2674 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 148:
#line 1338 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RelationType::Ptr >() = Ast::make< RelationType >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 3 ].value.as< Types::Ptr >(),
                                yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2682 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 149:
#line 1346 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FixedSizedType::Ptr >() = Ast::make< FixedSizedType >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2690 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 150:
#line 1358 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() =
                                yystack_[ 1 ].value.as< Expressions::Ptr >();
                        }
#line 2698 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 151:
#line 1362 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() = nullptr;
                        }
#line 2706 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 152:
#line 1366 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2715 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 153:
#line 1375 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = yystack_[ 3 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 1 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2725 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 154:
#line 1389 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2735 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 155:
#line 1395 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2745 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 156:
#line 1405 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = yystack_[ 0 ].value.as< Types::Ptr >();
                        }
#line 2753 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 157:
#line 1409 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = Ast::make< Types >( yylhs.location );
                        }
#line 2761 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 158:
#line 1417 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >();
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2771 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 159:
#line 1423 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2781 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 160:
#line 1433 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< VariableDefinition >::Ptr >();
                        }
#line 2789 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 161:
#line 1437 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = nullptr;
                        }
#line 2797 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 162:
#line 1441 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                        }
#line 2805 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 163:
#line 1453 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2813 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 164:
#line 1457 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                Ast::make< UndefAtom >( yylhs.location );
                        }
#line 2821 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 165:
#line 1465 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2829 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 166:
#line 1469 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2837 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 167:
#line 1477 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                yystack_[ 2 ].value.as< NodeList< UpdateRule >::Ptr >();
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2847 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 168:
#line 1483 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2857 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 169:
#line 1493 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            // the unknown function identifier will be replaced in
                            // FunctionDefinition
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            const auto function = Ast::make< DirectCallExpression >(
                                yylhs.location, nullptr, arguments );
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2869 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 170:
#line 1501 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto arguments = Ast::make< Expressions >( yylhs.location );
                            arguments->add( yystack_[ 2 ].value.as< Expression::Ptr >() );

                            // the unknown function identifier will be replaced in
                            // FunctionDefinition
                            const auto function = Ast::make< DirectCallExpression >(
                                yylhs.location, nullptr, arguments );
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2883 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 171:
#line 1511 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            // the unknown function identifier will be replaced in
                            // FunctionDefinition
                            const auto function = Ast::make< DirectCallExpression >(
                                yylhs.location,
                                nullptr,
                                yystack_[ 2 ].value.as< Expressions::Ptr >() );
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2894 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 172:
#line 1522 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 0 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2902 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 173:
#line 1526 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2910 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 174:
#line 1538 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() = Ast::make< Identifier >(
                                yylhs.location, yystack_[ 0 ].value.as< std::string >() );
                        }
#line 2918 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 175:
#line 1542 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() =
                                Ast::make< Identifier >( yylhs.location, "in" );
                        }
#line 2926 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 176:
#line 1550 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Identifiers::Ptr >(),
                                IdentifierPath::Type::ABSOLUTE );
                        }
#line 2934 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 177:
#line 1554 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
                        }
#line 2944 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 178:
#line 1564 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = yystack_[ 2 ].value.as< Identifiers::Ptr >();
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2954 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 179:
#line 1570 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2964 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 180:
#line 1584 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 2972 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 181:
#line 1588 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto unresolvedType =
                                Ast::make< UnresolvedType >( yylhs.location );
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    unresolvedType );
                        }
#line 2981 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 182:
#line 1597 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2989 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 183:
#line 1605 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 2999 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 184:
#line 1611 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3007 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 185:
#line 1619 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3017 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 186:
#line 1625 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3025 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 187:
#line 1637 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = yystack_[ 2 ].value.as< Attributes::Ptr >();
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3035 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 188:
#line 1643 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = Ast::make< Attributes >( yylhs.location );
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3045 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 189:
#line 1652 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< BasicAttribute::Ptr >();
                        }
#line 3053 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 190:
#line 1656 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< ExpressionAttribute::Ptr >();
                        }
#line 3061 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 191:
#line 1664 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicAttribute::Ptr >() = Ast::make< BasicAttribute >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 3069 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 192:
#line 1672 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExpressionAttribute::Ptr >() =
                                Ast::make< ExpressionAttribute >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 3077 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

#line 3081 "GrammarParser.cpp"  // lalr1.cc:859
                        default:
                            break;
                    }
                }
                catch( const syntax_error& yyexc )
                {
                    error( yyexc );
                    YYERROR;
                }
                YY_SYMBOL_PRINT( "-> $$ =", yylhs );
                yypop_( yylen );
                yylen = 0;
                YY_STACK_PRINT();

                // Shift the result of the reduction.
                yypush_( YY_NULLPTR, yylhs );
            }
            goto yynewstate;

        /*--------------------------------------.
        | yyerrlab -- here on detecting error.  |
        `--------------------------------------*/
        yyerrlab:
            // If not already recovering from an error, report this error.
            if( !yyerrstatus_ )
            {
                ++yynerrs_;
                error( yyla.location, yysyntax_error_( yystack_[ 0 ].state, yyla ) );
            }

            yyerror_range[ 1 ].location = yyla.location;
            if( yyerrstatus_ == 3 )
            {
                /* If just tried and failed to reuse lookahead token after an
                   error, discard it.  */

                // Return failure if at end of input.
                if( yyla.type_get() == yyeof_ )
                    YYABORT;
                else if( !yyla.empty() )
                {
                    yy_destroy_( "Error: discarding", yyla );
                    yyla.clear();
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
            if( false )
                goto yyerrorlab;
            yyerror_range[ 1 ].location = yystack_[ yylen - 1 ].location;
            /* Do not reclaim the symbols of the rule whose action triggered
               this YYERROR.  */
            yypop_( yylen );
            yylen = 0;
            goto yyerrlab1;

        /*-------------------------------------------------------------.
        | yyerrlab1 -- common code for both syntax error and YYERROR.  |
        `-------------------------------------------------------------*/
        yyerrlab1:
            yyerrstatus_ = 3;  // Each real token shifted decrements this.
            {
                stack_symbol_type error_token;
                for( ;; )
                {
                    yyn = yypact_[ yystack_[ 0 ].state ];
                    if( !yy_pact_value_is_default_( yyn ) )
                    {
                        yyn += yyterror_;
                        if( 0 <= yyn && yyn <= yylast_ && yycheck_[ yyn ] == yyterror_ )
                        {
                            yyn = yytable_[ yyn ];
                            if( 0 < yyn )
                                break;
                        }
                    }

                    // Pop the current state because it cannot handle the error token.
                    if( yystack_.size() == 1 )
                        YYABORT;

                    yyerror_range[ 1 ].location = yystack_[ 0 ].location;
                    yy_destroy_( "Error: popping", yystack_[ 0 ] );
                    yypop_();
                    YY_STACK_PRINT();
                }

                yyerror_range[ 2 ].location = yyla.location;
                YYLLOC_DEFAULT( error_token.location, yyerror_range, 2 );

                // Shift the error token.
                error_token.state = yyn;
                yypush_( "Shifting", error_token );
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
            if( !yyla.empty() )
                yy_destroy_( "Cleanup: discarding lookahead", yyla );

            /* Do not reclaim the symbols of the rule whose action triggered
               this YYABORT or YYACCEPT.  */
            yypop_( yylen );
            while( 1 < yystack_.size() )
            {
                yy_destroy_( "Cleanup: popping", yystack_[ 0 ] );
                yypop_();
            }

            return yyresult;
        }
        catch( ... )
        {
            YYCDEBUG << "Exception caught: cleaning lookahead and stack" << std::endl;
            // Do not try to display the values of the reclaimed symbols,
            // as their printer might throw an exception.
            if( !yyla.empty() )
                yy_destroy_( YY_NULLPTR, yyla );

            while( 1 < yystack_.size() )
            {
                yy_destroy_( YY_NULLPTR, yystack_[ 0 ] );
                yypop_();
            }
            throw;
        }
    }

    void Parser::error( const syntax_error& yyexc )
    {
        error( yyexc.location, yyexc.what() );
    }

    // Generate an error message.
    std::string Parser::yysyntax_error_( state_type yystate, const symbol_type& yyla ) const
    {
        // Number of reported tokens (one for the "unexpected", one per
        // "expected").
        size_t yycount = 0;
        // Its maximum.
        enum
        {
            YYERROR_VERBOSE_ARGS_MAXIMUM = 5
        };
        // Arguments of yyformat.
        char const* yyarg[ YYERROR_VERBOSE_ARGS_MAXIMUM ];

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
        if( !yyla.empty() )
        {
            int yytoken = yyla.type_get();
            yyarg[ yycount++ ] = yytname_[ yytoken ];
            int yyn = yypact_[ yystate ];
            if( !yy_pact_value_is_default_( yyn ) )
            {
                /* Start YYX at -YYN if negative to avoid negative indexes in
                   YYCHECK.  In other words, skip the first -YYN actions for
                   this state because they are default actions.  */
                int yyxbegin = yyn < 0 ? -yyn : 0;
                // Stay within bounds of both yycheck and yytname.
                int yychecklim = yylast_ - yyn + 1;
                int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
                for( int yyx = yyxbegin; yyx < yyxend; ++yyx )
                    if( yycheck_[ yyx + yyn ] == yyx && yyx != yyterror_ &&
                        !yy_table_value_is_error_( yytable_[ yyx + yyn ] ) )
                    {
                        if( yycount == YYERROR_VERBOSE_ARGS_MAXIMUM )
                        {
                            yycount = 1;
                            break;
                        }
                        else
                            yyarg[ yycount++ ] = yytname_[ yyx ];
                    }
            }
        }

        char const* yyformat = YY_NULLPTR;
        switch( yycount )
        {
#define YYCASE_( N, S ) \
    case N:             \
        yyformat = S;   \
        break
            YYCASE_( 0, YY_( "syntax error" ) );
            YYCASE_( 1, YY_( "syntax error, unexpected %s" ) );
            YYCASE_( 2, YY_( "syntax error, unexpected %s, expecting %s" ) );
            YYCASE_( 3, YY_( "syntax error, unexpected %s, expecting %s or %s" ) );
            YYCASE_( 4, YY_( "syntax error, unexpected %s, expecting %s or %s or %s" ) );
            YYCASE_( 5, YY_( "syntax error, unexpected %s, expecting %s or %s or %s or %s" ) );
#undef YYCASE_
        }

        std::string yyres;
        // Argument number.
        size_t yyi = 0;
        for( char const* yyp = yyformat; *yyp; ++yyp )
            if( yyp[ 0 ] == '%' && yyp[ 1 ] == 's' && yyi < yycount )
            {
                yyres += yytnamerr_( yyarg[ yyi++ ] );
                ++yyp;
            }
            else
                yyres += *yyp;
        return yyres;
    }

    const short int Parser::yypact_ninf_ = -228;

    const short int Parser::yytable_ninf_ = -156;

    const short int Parser::yypact_[] = {
        3,    -228, 8,    18,   267,  -228, -228, 1075, 4,    -228, -228, -228, -228, -228, -3,
        8,    8,    8,    8,    8,    163,  -228, -228, -228, -228, -228, -228, -228, -4,   -4,
        -4,   1075, -4,   -228, -228, -228, 1075, 1075, 1075, 495,  557,  21,   8,    -228, -228,
        -228, -228, -228, -228, 1917, -228, -228, -54,  -228, -228, -228, -228, -228, -228, -228,
        -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, 19,   37,   8,
        1137, 8,    -228, -228, -9,   55,   22,   55,   12,   44,   -228, 8,    70,   -228, -228,
        79,   112,  116,  1409, 117,  -228, -228, -228, 92,   1075, 1620, 97,   -228, 71,   1653,
        -228, -228, 21,   1075, 1075, 1075, 1075, 1075, 1075, 1075, 1075, 1075, 1075, 1075, 1075,
        1075, 1075, 1075, 1075, 1075, 8,    619,  -228, -228, -228, 495,  1686, 82,   104,  -228,
        123,  -228, 8,    0,    98,   118,  -36,  21,   148,  74,   21,   1075, 1075, 1075, 1075,
        1075, -228, 1719, 103,  -228, -228, 1075, 1075, -228, -228, -228, -228, -228, -10,  1984,
        248,  1978, 1950, 31,   31,   340,  144,  144,  114,  114,  114,  -228, 1950, 340,  144,
        144,  19,   129,  -228, -30,  1917, 122,  1620, 1075, 1075, 1137, -228, -228, 131,  8,
        -17,  70,   -228, -228, 21,   2,    913,  21,   -228, 127,  115,  -228, 8,    -228, 1183,
        1549, 1294, 1483, 1587, 19,   8,    1917, 1752, 21,   1075, -228, -228, -228, 1075, 1917,
        1917, -228, -228, 78,   -228, 9,    136,  -228, 8,    -228, 11,   -228, 409,  657,  -228,
        -4,   -4,   -4,   913,  -1,   1075, 1075, 1013, 698,  732,  -228, -228, -228, -228, -228,
        -228, -228, -228, -228, -228, -228, -228, -54,  119,  145,  21,   21,   -228, 1075, 1075,
        1075, 1075, 1075, -228, 19,   -228, -16,  -22,  128,  -228, 1785, 8,    -228, 1075, 83,
        -228, 2,    180,  -228, 766,  179,  804,  152,  187,  188,  -228, -54,  1446, 1516, 1818,
        147,  838,  137,  879,  1075, 913,  -228, 196,  1917, 1917, 1917, 1917, 1917, -228, 21,
        -228, 21,   -228, -228, 1917, 8,    -228, -228, -228, -228, -228, -228, 1075, 1075, 1075,
        913,  167,  103,  -228, -228, -228, -228, 1917, -228, 169,  209,  -228, 168,  -228, 1216,
        1255, 1333, 199,  433,  1075, 177,  -228, -228, 913,  913,  1075, 913,  913,  178,  176,
        181,  -228, 951,  1851, 1884, 1137, -228, -228, 1372, -228, -228, -228, 913,  913,  -228,
        -228, 913,  -228, 183,  913,  -228, -228, -228, -228, -228
    };

    const unsigned char Parser::yydefact_[] = {
        0,   4,   0,   0,   0,   175, 174, 191, 0,   188, 189, 190, 1,   9,   0,   0,   0,   0,
        0,   0,   0,   6,   8,   10,  11,  12,  13,  19,  0,   0,   0,   0,   0,   130, 132, 131,
        0,   0,   0,   0,   0,   0,   0,   136, 137, 133, 134, 135, 138, 192, 68,  69,  70,  102,
        103, 104, 71,  72,  73,  74,  75,  76,  77,  78,  122, 123, 124, 125, 126, 127, 128, 129,
        105, 0,   0,   173, 0,   179, 20,  176, 162, 0,   162, 0,   0,   5,   0,   181, 184, 180,
        0,   0,   0,   0,   0,   100, 81,  82,  0,   0,   0,   0,   118, 0,   67,  139, 112, 0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   106, 3,   187, 0,   169, 0,   172, 168, 0,   177, 0,   0,   0,   0,   0,   157, 0,
        0,   0,   0,   0,   0,   0,   0,   80,  0,   79,  120, 119, 0,   0,   101, 142, 143, 144,
        145, 146, 97,  95,  96,  99,  83,  84,  90,  91,  92,  85,  86,  87,  88,  98,  89,  93,
        94,  110, 0,   152, 0,   67,  0,   67,  0,   0,   0,   21,  178, 0,   0,   0,   0,   186,
        159, 0,   0,   0,   0,   155, 156, 0,   7,   0,   182, 0,   0,   0,   0,   0,   0,   0,
        66,  0,   157, 0,   111, 151, 150, 0,   170, 171, 167, 161, 0,   160, 0,   0,   24,  0,
        26,  0,   22,  0,   0,   40,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   16,  27,
        28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  65,  102, 0,   0,   0,   183, 0,   0,
        0,   0,   0,   107, 108, 121, 0,   141, 0,   149, 66,  0,   158, 0,   0,   14,  0,   0,
        39,  0,   0,   0,   0,   0,   0,   54,  64,  0,   0,   0,   0,   0,   0,   0,   0,   0,
        154, 164, 113, 116, 115, 114, 117, 109, 0,   147, 0,   153, 185, 15,  0,   25,  62,  60,
        38,  58,  56,  0,   0,   0,   0,   0,   0,   57,  55,  61,  59,  63,  17,  0,   166, 140,
        0,   23,  0,   0,   0,   41,  0,   0,   0,   18,  148, 0,   0,   0,   0,   0,   0,   0,
        0,   49,  0,   0,   0,   173, 50,  51,  0,   53,  42,  44,  0,   0,   43,  48,  0,   163,
        0,   0,   45,  46,  47,  165, 52
    };

    const short int Parser::yypgoto_[] = {
        -228, -228, -228, -228, 208,  91,   -228, -228, -228, -228, -228, -51,  -228, -143,
        -227, -228, -228, -228, -125, -228, -228, -228, -228, -228, -228, -228, -228, -228,
        -74,  -7,   -228, -228, 86,   7,    -228, -228, -228, -228, -228, -228, -228, -228,
        -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -67,  -228, -228,
        -228, -228, -179, -228, -228, 23,   -228, 160,  -228, -228, -228, 53,   -117, 52,
        6,    -228, 46,   -134, -20,  27,   -14,  184,  -228, -228
    };

    const short int Parser::yydefgoto_[] = {
        -1,  3,   4,   20,  21,  22,  23,  24,  25,  26,  27,  234, 235, 288, 289, 251,
        252, 253, 361, 362, 254, 255, 256, 257, 258, 259, 260, 261, 103, 131, 50,  51,
        52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,
        68,  69,  70,  71,  276, 158, 159, 160, 161, 162, 127, 132, 204, 205, 195, 139,
        340, 351, 133, 134, 135, 72,  163, 79,  88,  89,  90,  198, 8,   9,   10,  11
    };

    const short int Parser::yytable_[] = {
        49,  193, 220, 232, 197, 84,   1,   201, 125, 91,  92,  291, 94,  5,   5,   222, 5,    5,
        12,  5,   78,  301, 303, 156,  93,  5,   5,   202, 229, 95,  96,  97,  100, 104, -155, 273,
        230, 314, 5,   315, 128, -155, 86,  247, 218, 75,  194, 105, 233, 2,   219, 73,  184,  137,
        7,   194, 186, 74,  250, 76,   285, 42,  142, 126, 286, 140, 77,  80,  81,  82,  83,   7,
        144, 6,   6,   203, 6,   6,    208, 6,   87,  87,  87,  76,  87,  6,   6,   117, 118,  119,
        120, 143, 152, 77,  106, 313,  197, 74,  6,   138, 295, 164, 165, 166, 167, 168, 169,  170,
        171, 172, 173, 174, 175, 176,  177, 178, 179, 180, 155, 185, 145, 207, 146, 187, 156,  281,
        7,   74,  136, 147, 320, 74,   231, 148, 150, 264, 74,  151, 7,   209, 210, 211, 212,  213,
        154, 189, 324, 318, 324, 216,  217, 277, 14,  15,  16,  17,  18,  190, 324, 77,  324,  199,
        338, -2,  13,  215, 200, 14,   15,  16,  17,  18,  191, 120, 221, 223, 227, 181, 266,  283,
        228, 224, 225, 265, 304, 112,  113, 347, 305, 192, 196, 316, 322, 325, 77,  327, 333,  77,
        306, 307, 117, 118, 119, 120,  328, 329, 339, 335, 263, 19,  366, 367, 279, 369, 370,  348,
        280, 349, 350, 284, 292, 293,  294, 352, 357, 365, 372, 371, 85,  380, 381, 373, 383,  382,
        206, 321, 384, 375, 297, 298,  299, 278, 141, 226, 263, 263, 7,   341, 378, 342, 263,  77,
        236, 267, 77,  263, 263, 282,  129, 87,  0,   308, 309, 310, 311, 312, 0,   274, 13,   0,
        77,  14,  15,  16,  17,  18,   319, 0,   0,   0,   0,   0,   196, 0,   108, 7,   110,  262,
        0,   112, 113, 114, 87,  87,   87,  0,   263, 337, 263, 0,   0,   0,   115, 116, 117,  118,
        119, 120, 263, 0,   263, 0,    263, 19,  122, 123, 124, 77,  77,  0,   344, 345, 346,  262,
        262, 0,   0,   0,   0,   262,  296, 0,   0,   196, 262, 262, 0,   263, 236, 0,   0,    363,
        364, 0,   0,   0,   0,   0,    368, 0,   0,   0,   0,   0,   0,   363, 0,   0,   0,    0,
        263, 263, 0,   263, 263, 0,    77,  0,   77,  0,   0,   0,   343, 0,   0,   262, 0,    262,
        0,   263, 263, 112, 113, 263,  0,   0,   263, 262, 0,   262, 0,   262, 0,   0,   115,  116,
        117, 118, 119, 120, 0,   0,    0,   0,   0,   0,   0,   123, 124, 0,   287, 0,   0,    0,
        0,   0,   262, 0,   0,   0,    237, 0,   238, 0,   239, 240, 5,   241, 242, 243, 0,    244,
        245, 0,   358, 246, 0,   0,    0,   262, 262, 0,   262, 262, 0,   0,   0,   0,   0,    28,
        5,   29,  30,  247, 0,   0,    31,  248, 262, 262, 0,   359, 262, 32,  0,   262, 33,   34,
        35,  0,   0,   42,  0,   36,   37,  38,  0,   39,  249, 40,  0,   0,   0,   0,   360,  41,
        6,   0,   0,   0,   0,   0,    0,   0,   0,   42,  98,  0,   0,   0,   0,   0,   0,    0,
        43,  44,  45,  46,  47,  48,   6,   28,  5,   29,  30,  0,   0,   0,   31,  0,   0,    0,
        0,   0,   0,   32,  0,   0,    33,  34,  35,  0,   0,   0,   0,   36,  37,  38,  0,    39,
        0,   40,  0,   0,   0,   0,    0,   41,  0,   0,   0,   99,  0,   0,   0,   0,   0,    42,
        101, 0,   0,   0,   0,   0,    0,   0,   43,  44,  45,  46,  47,  48,  6,   28,  5,    29,
        30,  0,   0,   0,   31,  0,    0,   0,   0,   0,   0,   32,  0,   0,   33,  34,  35,   0,
        0,   0,   0,   36,  37,  38,   0,   39,  0,   40,  102, 0,   0,   0,   0,   41,  0,    0,
        0,   0,   0,   0,   0,   0,    0,   42,  182, 0,   0,   0,   0,   0,   0,   0,   43,   44,
        45,  46,  47,  48,  6,   28,   5,   29,  30,  0,   0,   0,   31,  0,   0,   0,   0,    0,
        0,   32,  0,   0,   33,  34,   35,  0,   0,   0,   290, 36,  37,  38,  0,   39,  183,  40,
        0,   0,   237, 0,   238, 41,   239, 240, 5,   241, 242, 243, 0,   244, 245, 42,  0,    246,
        0,   0,   0,   0,   0,   0,    43,  44,  45,  46,  47,  48,  6,   0,   0,   300, 0,    247,
        0,   0,   0,   248, 0,   0,    0,   237, 0,   238, 0,   239, 240, 5,   241, 242, 243,  42,
        244, 245, 0,   0,   246, 0,    249, 0,   0,   0,   0,   0,   0,   302, 6,   0,   0,    0,
        0,   0,   0,   0,   247, 237,  0,   238, 248, 239, 240, 5,   241, 242, 243, 0,   244,  245,
        0,   0,   246, 0,   42,  0,    0,   0,   0,   0,   0,   249, 0,   0,   0,   0,   0,    0,
        0,   6,   247, 237, 323, 238,  248, 239, 240, 5,   241, 242, 243, 0,   244, 245, 0,    0,
        246, 0,   42,  0,   0,   0,    0,   0,   0,   249, 0,   0,   0,   0,   0,   0,   0,    6,
        247, 0,   0,   0,   248, 237,  0,   238, 326, 239, 240, 5,   241, 242, 243, 0,   244,  245,
        42,  0,   246, 0,   0,   0,    0,   249, 0,   0,   0,   0,   0,   0,   0,   6,   0,    0,
        0,   0,   247, 237, 0,   238,  248, 239, 240, 5,   241, 242, 243, 0,   244, 245, 0,    0,
        246, 0,   42,  0,   0,   0,    0,   0,   0,   249, 0,   0,   0,   0,   0,   0,   0,    6,
        247, 0,   0,   0,   248, 334,  0,   0,   237, 0,   238, 0,   239, 240, 5,   241, 242,  243,
        42,  244, 245, 0,   0,   246,  0,   249, 0,   0,   0,   0,   0,   0,   0,   6,   0,    0,
        0,   0,   0,   0,   0,   247,  237, 0,   238, 248, 239, 240, 5,   241, 242, 243, 0,    244,
        245, 0,   0,   246, 0,   42,   0,   0,   0,   0,   0,   0,   249, 336, 0,   0,   0,    0,
        0,   0,   6,   247, 0,   0,    0,   248, 0,   0,   0,   0,   0,   28,  5,   29,  30,   0,
        0,   0,   31,  42,  0,   0,    0,   359, 0,   32,  249, 0,   33,  34,  35,  0,   0,    0,
        6,   36,  37,  38,  0,   39,   0,   40,  0,   0,   374, 0,   360, 41,  0,   0,   0,    0,
        0,   0,   0,   0,   0,   42,   0,   0,   0,   0,   0,   0,   0,   0,   43,  44,  45,   46,
        47,  48,  6,   28,  5,   29,   30,  0,   0,   0,   31,  0,   0,   0,   0,   0,   0,    32,
        0,   0,   33,  34,  35,  0,    0,   0,   0,   36,  37,  38,  0,   39,  0,   40,  0,    0,
        0,   0,   0,   41,  0,   0,    0,   99,  0,   0,   0,   0,   0,   42,  0,   0,   0,    0,
        0,   0,   0,   0,   43,  44,   45,  46,  47,  48,  6,   28,  5,   29,  30,  0,   0,    0,
        31,  0,   0,   0,   0,   0,    0,   32,  0,   0,   33,  34,  35,  0,   0,   0,   0,    36,
        37,  38,  0,   39,  0,   40,   0,   0,   0,   0,   0,   41,  0,   0,   0,   0,   0,    0,
        0,   0,   0,   42,  0,   0,    0,   0,   0,   0,   0,   0,   43,  44,  45,  46,  47,   48,
        6,   28,  5,   29,  30,  0,    0,   0,   31,  0,   0,   0,   0,   0,   0,   32,  0,    0,
        33,  34,  35,  0,   0,   0,    0,   36,  37,  38,  0,   130, 0,   40,  0,   0,   0,    0,
        0,   41,  0,   0,   0,   0,    0,   0,   0,   0,   0,   42,  268, 0,   0,   0,   0,    0,
        0,   0,   43,  44,  45,  46,   47,  48,  6,   107, 0,   0,   0,   108, 109, 110, 111,  0,
        112, 113, 114, 0,   0,   0,    0,   0,   0,   353, 0,   0,   0,   115, 116, 117, 118,  119,
        120, 0,   0,   0,   0,   121,  107, 122, 123, 124, 108, 109, 110, 111, 0,   112, 113,  114,
        0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   115, 116, 117, 118, 119, 120, 354,  0,
        0,   0,   121, 0,   122, 123,  124, 0,   355, 107, 0,   0,   0,   108, 109, 110, 111,  0,
        112, 113, 114, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   115, 116, 117, 118,  119,
        120, 270, 0,   0,   0,   121,  0,   122, 123, 124, 0,   0,   107, 0,   0,   0,   108,  109,
        110, 111, 0,   112, 113, 114,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   115,  116,
        117, 118, 119, 120, 356, 0,    0,   0,   121, 0,   122, 123, 124, 0,   0,   107, 0,    0,
        0,   108, 109, 110, 111, 0,    112, 113, 114, 0,   0,   0,   0,   0,   0,   0,   0,    0,
        0,   115, 116, 117, 118, 119,  120, 379, 0,   0,   0,   121, 0,   122, 123, 124, 0,    0,
        107, 0,   0,   0,   108, 109,  110, 111, 0,   112, 113, 114, 0,   0,   0,   0,   0,    0,
        0,   0,   0,   0,   115, 116,  117, 118, 119, 120, 0,   149, 0,   0,   121, 0,   122,  123,
        124, 107, 0,   0,   0,   108,  109, 110, 111, 0,   112, 113, 114, 0,   0,   0,   0,    0,
        0,   0,   0,   0,   0,   115,  116, 117, 118, 119, 120, 0,   330, 0,   0,   121, 0,    122,
        123, 124, 107, 0,   0,   0,    108, 109, 110, 111, 0,   112, 113, 114, 0,   0,   0,    0,
        0,   0,   0,   0,   0,   0,    115, 116, 117, 118, 119, 120, 0,   0,   271, 0,   121,  0,
        122, 123, 124, 107, 0,   0,    0,   108, 109, 110, 111, 0,   112, 113, 114, 0,   0,    0,
        0,   0,   0,   0,   0,   0,    0,   115, 116, 117, 118, 119, 120, 331, 0,   0,   0,    121,
        107, 122, 123, 124, 108, 109,  110, 111, 0,   112, 113, 114, 0,   0,   0,   0,   0,    0,
        0,   0,   0,   0,   115, 116,  117, 118, 119, 120, 0,   0,   269, 0,   121, 107, 122,  123,
        124, 108, 109, 110, 111, 0,    112, 113, 114, 0,   0,   0,   0,   0,   0,   0,   0,    0,
        0,   115, 116, 117, 118, 119,  120, 0,   0,   0,   0,   121, 0,   122, 123, 124, 272,  107,
        0,   0,   0,   108, 109, 110,  111, 0,   112, 113, 114, 0,   0,   0,   0,   0,   0,    0,
        0,   0,   0,   115, 116, 117,  118, 119, 120, 0,   0,   0,   0,   121, 107, 122, 123,  124,
        108, 109, 110, 111, 0,   112,  113, 114, 0,   153, 0,   0,   0,   0,   0,   0,   0,    0,
        115, 116, 117, 118, 119, 120,  0,   0,   0,   0,   121, 107, 122, 123, 124, 108, 109,  110,
        111, 0,   112, 113, 114, 0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   115, 116,  117,
        118, 119, 120, 0,   157, 0,    0,   121, 107, 122, 123, 124, 108, 109, 110, 111, 0,    112,
        113, 114, 0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   115, 116, 117, 118, 119,  120,
        0,   0,   0,   188, 121, 107,  122, 123, 124, 108, 109, 110, 111, 0,   112, 113, 114,  0,
        214, 0,   0,   0,   0,   0,    0,   0,   0,   115, 116, 117, 118, 119, 120, 0,   0,    0,
        0,   121, 107, 122, 123, 124,  108, 109, 110, 111, 0,   112, 113, 114, 0,   0,   0,    275,
        0,   0,   0,   0,   0,   0,    115, 116, 117, 118, 119, 120, 0,   0,   0,   0,   121,  107,
        122, 123, 124, 108, 109, 110,  111, 0,   112, 113, 114, 0,   317, 0,   0,   0,   0,    0,
        0,   0,   0,   115, 116, 117,  118, 119, 120, 0,   0,   0,   0,   121, 107, 122, 123,  124,
        108, 109, 110, 111, 0,   112,  113, 114, 0,   332, 0,   0,   0,   0,   0,   0,   0,    0,
        115, 116, 117, 118, 119, 120,  0,   0,   0,   0,   121, 107, 122, 123, 124, 108, 109,  110,
        111, 0,   112, 113, 114, 0,    0,   0,   0,   0,   0,   376, 0,   0,   0,   115, 116,  117,
        118, 119, 120, 0,   0,   0,    0,   121, 107, 122, 123, 124, 108, 109, 110, 111, 0,    112,
        113, 114, 0,   0,   0,   0,    0,   377, 0,   0,   0,   0,   115, 116, 117, 118, 119,  120,
        0,   0,   0,   0,   121, 107,  122, 123, 124, 108, 109, 110, 111, 0,   112, 113, 114,  0,
        0,   0,   0,   0,   0,   0,    0,   0,   0,   115, 116, 117, 118, 119, 120, 0,   0,    0,
        0,   121, 0,   122, 123, 124,  108, 109, 110, 0,   0,   112, 113, 114, 0,   0,   0,    0,
        0,   0,   0,   0,   0,   0,    115, 116, 117, 118, 119, 120, 0,   0,   0,   0,   108,  0,
        122, 123, 124, 112, 113, 114,  0,   0,   0,   112, 113, 114, 0,   0,   0,   0,   115,  116,
        117, 118, 119, 120, 115, 116,  117, 118, 119, 120, 122, 123, 124, 0,   0,   0,   122,  123,
        124
    };

    const short int Parser::yycheck_[] = {
        7,   1,   181, 1,   138, 19,  3,   43,  62,  29,  30,  238, 32,  17,  17,  45,  17,  17,
        0,   17,  14,  248, 249, 53,  31,  17,  17,  63,  45,  36,  37,  38,  39,  40,  56,  214,
        53,  53,  17,  55,  3,   63,  46,  44,  54,  48,  46,  41,  46,  46,  60,  47,  126, 62,
        2,   46,  130, 53,  201, 62,  49,  62,  50,  44,  53,  43,  14,  15,  16,  17,  18,  19,
        86,  77,  77,  142, 77,  77,  145, 77,  28,  29,  30,  62,  32,  77,  77,  56,  57,  58,
        59,  47,  99,  41,  42,  274, 230, 53,  77,  44,  243, 108, 109, 110, 111, 112, 113, 114,
        115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 47,  126, 50,  47,  43,  130, 53,  47,
        74,  53,  76,  17,  47,  53,  199, 17,  17,  202, 53,  45,  86,  146, 147, 148, 149, 150,
        47,  63,  289, 281, 291, 156, 157, 218, 4,   5,   6,   7,   8,   53,  301, 107, 303, 63,
        305, 0,   1,   62,  48,  4,   5,   6,   7,   8,   49,  59,  45,  53,  45,  125, 63,  43,
        194, 188, 189, 56,  65,  41,  42,  330, 43,  137, 138, 63,  12,  14,  142, 43,  49,  145,
        265, 266, 56,  57,  58,  59,  17,  17,  10,  70,  201, 46,  353, 354, 219, 356, 357, 48,
        223, 48,  9,   233, 240, 241, 242, 55,  25,  48,  50,  49,  20,  372, 373, 50,  49,  376,
        143, 286, 379, 362, 245, 246, 247, 218, 82,  190, 237, 238, 194, 314, 365, 316, 243, 199,
        200, 207, 202, 248, 249, 230, 74,  207, -1,  268, 269, 270, 271, 272, -1,  215, 1,   -1,
        218, 4,   5,   6,   7,   8,   283, -1,  -1,  -1,  -1,  -1,  230, -1,  36,  233, 38,  201,
        -1,  41,  42,  43,  240, 241, 242, -1,  289, 304, 291, -1,  -1,  -1,  54,  55,  56,  57,
        58,  59,  301, -1,  303, -1,  305, 46,  66,  67,  68,  265, 266, -1,  327, 328, 329, 237,
        238, -1,  -1,  -1,  -1,  243, 244, -1,  -1,  281, 248, 249, -1,  330, 286, -1,  -1,  348,
        349, -1,  -1,  -1,  -1,  -1,  355, -1,  -1,  -1,  -1,  -1,  -1,  362, -1,  -1,  -1,  -1,
        353, 354, -1,  356, 357, -1,  314, -1,  316, -1,  -1,  -1,  320, -1,  -1,  289, -1,  291,
        -1,  372, 373, 41,  42,  376, -1,  -1,  379, 301, -1,  303, -1,  305, -1,  -1,  54,  55,
        56,  57,  58,  59,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  67,  68,  -1,  1,   -1,  -1,  -1,
        -1,  -1,  330, -1,  -1,  -1,  11,  -1,  13,  -1,  15,  16,  17,  18,  19,  20,  -1,  22,
        23,  -1,  1,   26,  -1,  -1,  -1,  353, 354, -1,  356, 357, -1,  -1,  -1,  -1,  -1,  16,
        17,  18,  19,  44,  -1,  -1,  23,  48,  372, 373, -1,  28,  376, 30,  -1,  379, 33,  34,
        35,  -1,  -1,  62,  -1,  40,  41,  42,  -1,  44,  69,  46,  -1,  -1,  -1,  -1,  51,  52,
        77,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  62,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,
        71,  72,  73,  74,  75,  76,  77,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,
        -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,
        -1,  46,  -1,  -1,  -1,  -1,  -1,  52,  -1,  -1,  -1,  56,  -1,  -1,  -1,  -1,  -1,  62,
        1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,  77,  16,  17,  18,
        19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,
        -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  47,  -1,  -1,  -1,  -1,  52,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  62,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,
        73,  74,  75,  76,  77,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,
        -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  1,   40,  41,  42,  -1,  44,  45,  46,
        -1,  -1,  11,  -1,  13,  52,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  62,  -1,  26,
        -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,  77,  -1,  -1,  1,   -1,  44,
        -1,  -1,  -1,  48,  -1,  -1,  -1,  11,  -1,  13,  -1,  15,  16,  17,  18,  19,  20,  62,
        22,  23,  -1,  -1,  26,  -1,  69,  -1,  -1,  -1,  -1,  -1,  -1,  1,   77,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  44,  11,  -1,  13,  48,  15,  16,  17,  18,  19,  20,  -1,  22,  23,
        -1,  -1,  26,  -1,  62,  -1,  -1,  -1,  -1,  -1,  -1,  69,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  77,  44,  11,  12,  13,  48,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  -1,  -1,
        26,  -1,  62,  -1,  -1,  -1,  -1,  -1,  -1,  69,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  77,
        44,  -1,  -1,  -1,  48,  11,  -1,  13,  14,  15,  16,  17,  18,  19,  20,  -1,  22,  23,
        62,  -1,  26,  -1,  -1,  -1,  -1,  69,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  77,  -1,  -1,
        -1,  -1,  44,  11,  -1,  13,  48,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  -1,  -1,
        26,  -1,  62,  -1,  -1,  -1,  -1,  -1,  -1,  69,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  77,
        44,  -1,  -1,  -1,  48,  49,  -1,  -1,  11,  -1,  13,  -1,  15,  16,  17,  18,  19,  20,
        62,  22,  23,  -1,  -1,  26,  -1,  69,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  77,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  44,  11,  -1,  13,  48,  15,  16,  17,  18,  19,  20,  -1,  22,
        23,  -1,  -1,  26,  -1,  62,  -1,  -1,  -1,  -1,  -1,  -1,  69,  70,  -1,  -1,  -1,  -1,
        -1,  -1,  77,  44,  -1,  -1,  -1,  48,  -1,  -1,  -1,  -1,  -1,  16,  17,  18,  19,  -1,
        -1,  -1,  23,  62,  -1,  -1,  -1,  28,  -1,  30,  69,  -1,  33,  34,  35,  -1,  -1,  -1,
        77,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,  49,  -1,  51,  52,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  62,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,
        75,  76,  77,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,
        -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,
        -1,  -1,  -1,  52,  -1,  -1,  -1,  56,  -1,  -1,  -1,  -1,  -1,  62,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,  77,  16,  17,  18,  19,  -1,  -1,  -1,
        23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,
        41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  52,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  62,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,
        77,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,
        33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,
        -1,  52,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  62,  17,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  71,  72,  73,  74,  75,  76,  77,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,
        41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  17,  -1,  -1,  -1,  54,  55,  56,  57,  58,
        59,  -1,  -1,  -1,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  21,  -1,
        -1,  -1,  64,  -1,  66,  67,  68,  -1,  31,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,
        41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,
        59,  21,  -1,  -1,  -1,  64,  -1,  66,  67,  68,  -1,  -1,  32,  -1,  -1,  -1,  36,  37,
        38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,
        56,  57,  58,  59,  21,  -1,  -1,  -1,  64,  -1,  66,  67,  68,  -1,  -1,  32,  -1,  -1,
        -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  54,  55,  56,  57,  58,  59,  21,  -1,  -1,  -1,  64,  -1,  66,  67,  68,  -1,  -1,
        32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  24,  -1,  -1,  64,  -1,  66,  67,
        68,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  24,  -1,  -1,  64,  -1,  66,
        67,  68,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  25,  -1,  64,  -1,
        66,  67,  68,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  27,  -1,  -1,  -1,  64,
        32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  29,  -1,  64,  32,  66,  67,
        68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  -1,  66,  67,  68,  31,  32,
        -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,  66,  67,  68,
        36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,  66,  67,  68,  36,  37,  38,
        39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,
        57,  58,  59,  -1,  61,  -1,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,
        42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,
        -1,  -1,  -1,  63,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,
        45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,
        -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  47,
        -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,
        66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,  66,  67,  68,
        36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,  66,  67,  68,  36,  37,  38,
        39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  50,  -1,  -1,  -1,  54,  55,  56,
        57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,
        42,  43,  -1,  -1,  -1,  -1,  -1,  49,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,
        -1,  -1,  -1,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,
        -1,  64,  -1,  66,  67,  68,  36,  37,  38,  -1,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  36,  -1,
        66,  67,  68,  41,  42,  43,  -1,  -1,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  54,  55,
        56,  57,  58,  59,  54,  55,  56,  57,  58,  59,  66,  67,  68,  -1,  -1,  -1,  66,  67,
        68
    };

    const unsigned char Parser::yystos_[] = {
        0,   3,   46,  85,  86,  17,  77,  153, 160, 161, 162, 163, 0,   1,   4,   5,   6,   7,
        8,   46,  87,  88,  89,  90,  91,  92,  93,  94,  16,  18,  19,  23,  30,  33,  34,  35,
        40,  41,  42,  44,  46,  52,  62,  71,  72,  73,  74,  75,  76,  113, 114, 115, 116, 117,
        118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,
        153, 47,  53,  48,  62,  153, 154, 155, 153, 153, 153, 153, 160, 88,  46,  153, 156, 157,
        158, 158, 158, 113, 158, 113, 113, 113, 1,   56,  113, 1,   47,  112, 113, 154, 153, 32,
        36,  37,  38,  39,  41,  42,  43,  54,  55,  56,  57,  58,  59,  64,  66,  67,  68,  62,
        44,  142, 3,   161, 44,  113, 143, 150, 151, 152, 153, 62,  44,  147, 43,  147, 50,  47,
        160, 50,  43,  17,  17,  24,  17,  45,  113, 45,  47,  47,  53,  61,  137, 138, 139, 140,
        141, 154, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113,
        113, 153, 1,   45,  112, 113, 112, 113, 63,  63,  53,  49,  153, 1,   46,  146, 153, 157,
        159, 63,  48,  43,  63,  137, 144, 145, 89,  47,  137, 113, 113, 113, 113, 113, 45,  62,
        113, 113, 54,  60,  142, 45,  45,  53,  113, 113, 151, 45,  160, 45,  53,  137, 1,   46,
        95,  96,  153, 11,  13,  15,  16,  18,  19,  20,  22,  23,  26,  44,  48,  69,  97,  99,
        100, 101, 104, 105, 106, 107, 108, 109, 110, 111, 116, 117, 137, 56,  63,  156, 17,  29,
        21,  25,  31,  142, 153, 47,  136, 137, 145, 113, 113, 47,  159, 43,  160, 49,  53,  1,
        97,  98,  1,   98,  158, 158, 158, 97,  116, 113, 113, 113, 1,   98,  1,   98,  65,  43,
        137, 137, 113, 113, 113, 113, 113, 142, 53,  55,  63,  45,  157, 113, 47,  95,  12,  12,
        97,  14,  14,  43,  17,  17,  24,  27,  45,  49,  49,  70,  70,  113, 97,  10,  148, 137,
        137, 153, 113, 113, 113, 97,  48,  48,  9,   149, 55,  17,  21,  31,  21,  25,  1,   28,
        51,  102, 103, 113, 113, 48,  97,  97,  113, 97,  97,  49,  50,  50,  49,  102, 50,  49,
        152, 21,  97,  97,  97,  49,  97
    };

    const unsigned char Parser::yyr1_[] = {
        0,   84,  85,  86,  86,  87,  87,  88,  88,  88,  89,  89,  89,  89,  90,  91,  92,  92,
        93,  93,  94,  94,  95,  95,  95,  96,  96,  97,  97,  97,  97,  97,  97,  97,  97,  97,
        97,  97,  98,  98,  99,  100, 100, 101, 101, 102, 102, 102, 103, 103, 104, 105, 105, 106,
        107, 108, 108, 108, 108, 109, 109, 109, 109, 110, 111, 111, 112, 112, 113, 113, 113, 113,
        113, 113, 113, 113, 113, 113, 113, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114,
        114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 115, 116, 116, 116, 117, 117, 118,
        119, 119, 119, 119, 119, 120, 121, 122, 123, 124, 125, 125, 125, 126, 127, 127, 127, 127,
        127, 127, 127, 127, 128, 129, 129, 130, 131, 132, 133, 133, 134, 135, 136, 136, 137, 137,
        137, 137, 138, 139, 140, 141, 142, 142, 142, 143, 144, 144, 145, 145, 146, 146, 147, 147,
        147, 148, 148, 149, 149, 150, 150, 151, 151, 151, 152, 152, 153, 153, 154, 154, 155, 155,
        156, 156, 157, 158, 158, 159, 159, 160, 160, 161, 161, 162, 163
    };

    const unsigned char Parser::yyr2_[] = {
        0, 2, 2, 4, 1, 2, 1, 4, 1, 1, 1, 1, 1, 1, 6, 7, 5, 7, 8, 1, 2, 4, 1, 4, 1, 3, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 4, 6, 6, 6, 3, 3, 3, 2, 1, 6, 6, 8, 6, 2, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2, 2, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 1, 1, 1, 1, 2, 5, 5, 6, 3, 4,
        2, 6, 6, 6, 6, 6, 2, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        3, 1, 1, 1, 1, 1, 1, 4, 6, 3, 3, 3, 2, 5, 3, 1, 1, 0, 3, 1, 3, 3, 0, 4, 0, 4, 0, 3,
        1, 1, 3, 3, 1, 0, 1, 1, 1, 2, 3, 1, 1, 1, 3, 4, 1, 4, 1, 3, 1, 1, 1, 1, 2
    };

    // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
    // First, the terminals, then, starting at \a yyntokens_, nonterminals.
    const char* const Parser::yytname_[] = { "\"end of file\"",
                                             "error",
                                             "$undefined",
                                             "\"CASM\"",
                                             "\"init\"",
                                             "\"derived\"",
                                             "\"enumeration\"",
                                             "\"rule\"",
                                             "\"function\"",
                                             "\"initially\"",
                                             "\"defined\"",
                                             "\"seq\"",
                                             "\"endseq\"",
                                             "\"par\"",
                                             "\"endpar\"",
                                             "\"skip\"",
                                             "\"let\"",
                                             "\"in\"",
                                             "\"forall\"",
                                             "\"choose\"",
                                             "\"iterate\"",
                                             "\"do\"",
                                             "\"call\"",
                                             "\"if\"",
                                             "\"then\"",
                                             "\"else\"",
                                             "\"case\"",
                                             "\"of\"",
                                             "\"default\"",
                                             "\"holds\"",
                                             "\"exists\"",
                                             "\"with\"",
                                             "\"as\"",
                                             "\"undef\"",
                                             "\"false\"",
                                             "\"true\"",
                                             "\"and\"",
                                             "\"or\"",
                                             "\"xor\"",
                                             "\"implies\"",
                                             "\"not\"",
                                             "\"+\"",
                                             "\"-\"",
                                             "\"=\"",
                                             "\"(\"",
                                             "\")\"",
                                             "\"[\"",
                                             "\"]\"",
                                             "\"{\"",
                                             "\"}\"",
                                             "\":\"",
                                             "\"_\"",
                                             "\"@\"",
                                             "\",\"",
                                             "\"<\"",
                                             "\">\"",
                                             "\"*\"",
                                             "\"/\"",
                                             "\"%\"",
                                             "\"^\"",
                                             "\"'\"",
                                             "\"..\"",
                                             "\".\"",
                                             "\"->\"",
                                             "\"=>\"",
                                             "\":=\"",
                                             "\"!=\"",
                                             "\"<=\"",
                                             "\">=\"",
                                             "\"{|\"",
                                             "\"|}\"",
                                             "\"binary\"",
                                             "\"hexadecimal\"",
                                             "\"integer\"",
                                             "\"rational\"",
                                             "\"decimal\"",
                                             "\"string\"",
                                             "\"identifier\"",
                                             "ABSOLUTE_PATH",
                                             "CALL_EXPRESSION",
                                             "PAREN_TERM",
                                             "UPLUS",
                                             "UMINUS",
                                             "CALL_WITHOUT_ARGS",
                                             "$accept",
                                             "Specification",
                                             "Header",
                                             "Definitions",
                                             "AttributedDefinition",
                                             "Definition",
                                             "EnumerationDefinition",
                                             "DerivedDefinition",
                                             "RuleDefinition",
                                             "FunctionDefinition",
                                             "ProgramFunctionDefinition",
                                             "EnumeratorDefinition",
                                             "Enumerators",
                                             "Rule",
                                             "Rules",
                                             "SkipRule",
                                             "ConditionalRule",
                                             "CaseRule",
                                             "CaseLabel",
                                             "CaseLabels",
                                             "LetRule",
                                             "ForallRule",
                                             "ChooseRule",
                                             "IterateRule",
                                             "BlockRule",
                                             "SequenceRule",
                                             "UpdateRule",
                                             "CallRule",
                                             "Terms",
                                             "Term",
                                             "Expression",
                                             "TypeCastingExpression",
                                             "CallExpression",
                                             "DirectCallExpression",
                                             "IndirectCallExpression",
                                             "MethodCallExpression",
                                             "LetExpression",
                                             "ConditionalExpression",
                                             "ChooseExpression",
                                             "UniversalQuantifierExpression",
                                             "ExistentialQuantifierExpression",
                                             "List",
                                             "Range",
                                             "Literal",
                                             "UndefinedLiteral",
                                             "BooleanLiteral",
                                             "IntegerLiteral",
                                             "RationalLiteral",
                                             "DecimalLiteral",
                                             "BinaryLiteral",
                                             "StringLiteral",
                                             "ReferenceLiteral",
                                             "Types",
                                             "Type",
                                             "BasicType",
                                             "ComposedType",
                                             "RelationType",
                                             "FixedSizedType",
                                             "Arguments",
                                             "TwoOrMoreArguments",
                                             "FunctionParameters",
                                             "MaybeFunctionParameters",
                                             "Parameters",
                                             "MaybeParameters",
                                             "MaybeDefined",
                                             "MaybeInitially",
                                             "Initializers",
                                             "Initializer",
                                             "MaybeInitializers",
                                             "Identifier",
                                             "IdentifierPath",
                                             "DotSeparatedIdentifiers",
                                             "Variable",
                                             "TypedVariable",
                                             "AttributedVariable",
                                             "TypedAttributedVariable",
                                             "Attributes",
                                             "Attribute",
                                             "BasicAttribute",
                                             "ExpressionAttribute",
                                             YY_NULLPTR };

#if YYDEBUG
    const unsigned short int Parser::yyrline_[] = {
        0,    378,  378,  387,  393,  401,  407,  417,  423,  427,  435,  439,  443,  447,  455,
        463,  471,  476,  485,  501,  509,  532,  549,  553,  559,  567,  573,  587,  591,  595,
        599,  603,  607,  611,  615,  619,  623,  627,  635,  641,  651,  659,  663,  671,  675,
        683,  687,  691,  699,  705,  715,  723,  727,  735,  743,  751,  755,  759,  764,  773,
        777,  781,  786,  795,  805,  809,  821,  827,  837,  841,  845,  849,  853,  857,  861,
        865,  869,  873,  877,  889,  893,  897,  901,  905,  909,  913,  917,  921,  925,  929,
        933,  937,  941,  945,  949,  953,  957,  961,  965,  969,  973,  981,  989,  993,  997,
        1005, 1010, 1018, 1026, 1031, 1035, 1040, 1044, 1054, 1062, 1070, 1078, 1086, 1094, 1099,
        1103, 1111, 1123, 1127, 1131, 1135, 1139, 1143, 1147, 1151, 1159, 1167, 1172, 1181, 1197,
        1213, 1229, 1241, 1257, 1273, 1285, 1291, 1301, 1305, 1309, 1313, 1321, 1329, 1337, 1345,
        1357, 1361, 1365, 1374, 1388, 1394, 1404, 1408, 1416, 1422, 1432, 1436, 1440, 1452, 1456,
        1464, 1468, 1476, 1482, 1492, 1500, 1510, 1521, 1525, 1537, 1541, 1549, 1553, 1563, 1569,
        1583, 1587, 1596, 1604, 1610, 1618, 1624, 1636, 1642, 1651, 1655, 1663, 1671
    };

    // Print the state stack on the debug stream.
    void Parser::yystack_print_()
    {
        *yycdebug_ << "Stack now";
        for( stack_type::const_iterator i = yystack_.begin(), i_end = yystack_.end(); i != i_end;
             ++i )
            *yycdebug_ << ' ' << i->state;
        *yycdebug_ << std::endl;
    }

    // Report on the debug stream that the rule \a yyrule is going to be reduced.
    void Parser::yy_reduce_print_( int yyrule )
    {
        unsigned int yylno = yyrline_[ yyrule ];
        int yynrhs = yyr2_[ yyrule ];
        // Print the symbols being reduced, and their result.
        *yycdebug_ << "Reducing stack by rule " << yyrule - 1 << " (line " << yylno
                   << "):" << std::endl;
        // The symbols being reduced.
        for( int yyi = 0; yyi < yynrhs; yyi++ )
            YY_SYMBOL_PRINT( "   $" << yyi + 1 << " =", yystack_[ ( yynrhs ) - ( yyi + 1 ) ] );
    }
#endif  // YYDEBUG

#line 49 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1167
}  // libcasm_fe
#line 4073 "GrammarParser.cpp"               // lalr1.cc:1167
#line 1677 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1168

void Parser::error( const SourceLocation& location, const std::string& message )
{
    log.error( { location }, message, Code::SyntaxError );
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
