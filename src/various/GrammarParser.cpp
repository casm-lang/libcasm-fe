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

static IdentifierPath::Ptr asIdentifierPath( const Identifier::Ptr& identifier )
{
    const auto& location = identifier->sourceLocation();
    return Ast::make< IdentifierPath >( location, identifier );
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

#line 131 "GrammarParser.cpp"  // lalr1.cc:413

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
#line 217 "GrammarParser.cpp"  // lalr1.cc:479

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
            case 157:  // Attribute
                value.move< Attribute::Ptr >( that.value );
                break;

            case 156:  // Attributes
                value.move< Attributes::Ptr >( that.value );
                break;

            case 158:  // BasicAttribute
                value.move< BasicAttribute::Ptr >( that.value );
                break;

            case 134:  // BasicType
                value.move< BasicType::Ptr >( that.value );
                break;

            case 106:  // BlockRule
                value.move< BlockRule::Ptr >( that.value );
                break;

            case 109:  // CallRule
                value.move< CallRule::Ptr >( that.value );
                break;

            case 100:  // CaseLabel
                value.move< Case::Ptr >( that.value );
                break;

            case 99:  // CaseRule
                value.move< CaseRule::Ptr >( that.value );
                break;

            case 101:  // CaseLabels
                value.move< Cases::Ptr >( that.value );
                break;

            case 118:  // ChooseExpression
                value.move< ChooseExpression::Ptr >( that.value );
                break;

            case 104:  // ChooseRule
                value.move< ChooseRule::Ptr >( that.value );
                break;

            case 135:  // ComposedType
                value.move< ComposedType::Ptr >( that.value );
                break;

            case 117:  // ConditionalExpression
                value.move< ConditionalExpression::Ptr >( that.value );
                break;

            case 98:  // ConditionalRule
                value.move< ConditionalRule::Ptr >( that.value );
                break;

            case 86:  // AttributedDefinition
            case 87:  // Definition
                value.move< Definition::Ptr >( that.value );
                break;

            case 85:  // Definitions
                value.move< Definitions::Ptr >( that.value );
                break;

            case 89:  // DerivedDefinition
                value.move< DerivedDefinition::Ptr >( that.value );
                break;

            case 114:  // DirectCallExpression
                value.move< DirectCallExpression::Ptr >( that.value );
                break;

            case 88:  // EnumerationDefinition
                value.move< EnumerationDefinition::Ptr >( that.value );
                break;

            case 93:  // EnumeratorDefinition
                value.move< EnumeratorDefinition::Ptr >( that.value );
                break;

            case 94:  // Enumerators
                value.move< Enumerators::Ptr >( that.value );
                break;

            case 120:  // ExistentialQuantifierExpression
                value.move< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // Term
            case 112:  // Expression
            case 123:  // Literal
            case 144:  // MaybeDefined
                value.move< Expression::Ptr >( that.value );
                break;

            case 159:  // ExpressionAttribute
                value.move< ExpressionAttribute::Ptr >( that.value );
                break;

            case 110:  // Terms
            case 138:  // Arguments
            case 139:  // TwoOrMoreArguments
                value.move< Expressions::Ptr >( that.value );
                break;

            case 137:  // FixedSizedType
                value.move< FixedSizedType::Ptr >( that.value );
                break;

            case 103:  // ForallRule
                value.move< ForallRule::Ptr >( that.value );
                break;

            case 91:  // FunctionDefinition
            case 92:  // ProgramFunctionDefinition
                value.move< FunctionDefinition::Ptr >( that.value );
                break;

            case 84:  // Header
                value.move< HeaderDefinition::Ptr >( that.value );
                break;

            case 149:  // Identifier
                value.move< Identifier::Ptr >( that.value );
                break;

            case 150:  // IdentifierPath
                value.move< IdentifierPath::Ptr >( that.value );
                break;

            case 151:  // DotSeparatedIdentifiers
                value.move< Identifiers::Ptr >( that.value );
                break;

            case 115:  // IndirectCallExpression
                value.move< IndirectCallExpression::Ptr >( that.value );
                break;

            case 105:  // IterateRule
                value.move< IterateRule::Ptr >( that.value );
                break;

            case 116:  // LetExpression
                value.move< LetExpression::Ptr >( that.value );
                break;

            case 102:  // LetRule
                value.move< LetRule::Ptr >( that.value );
                break;

            case 121:  // List
                value.move< ListExpression::Ptr >( that.value );
                break;

            case 145:  // MaybeInitially
            case 146:  // Initializers
            case 148:  // MaybeInitializers
                value.move< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 142:  // Parameters
            case 143:  // MaybeParameters
                value.move< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 122:  // Range
                value.move< RangeExpression::Ptr >( that.value );
                break;

            case 131:  // ReferenceLiteral
                value.move< ReferenceAtom::Ptr >( that.value );
                break;

            case 136:  // RelationType
                value.move< RelationType::Ptr >( that.value );
                break;

            case 95:  // Rule
                value.move< Rule::Ptr >( that.value );
                break;

            case 90:  // RuleDefinition
                value.move< RuleDefinition::Ptr >( that.value );
                break;

            case 96:  // Rules
                value.move< Rules::Ptr >( that.value );
                break;

            case 107:  // SequenceRule
                value.move< SequenceRule::Ptr >( that.value );
                break;

            case 97:  // SkipRule
                value.move< SkipRule::Ptr >( that.value );
                break;

            case 83:  // Specification
                value.move< Specification::Ptr >( that.value );
                break;

            case 113:  // TypeCastingExpression
                value.move< TypeCastingExpression::Ptr >( that.value );
                break;

            case 132:  // Types
            case 140:  // FunctionParameters
            case 141:  // MaybeFunctionParameters
                value.move< Types::Ptr >( that.value );
                break;

            case 124:  // UndefinedLiteral
                value.move< UndefAtom::Ptr >( that.value );
                break;

            case 119:  // UniversalQuantifierExpression
                value.move< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 108:  // UpdateRule
            case 147:  // Initializer
                value.move< UpdateRule::Ptr >( that.value );
                break;

            case 125:  // BooleanLiteral
            case 126:  // IntegerLiteral
            case 127:  // RationalLiteral
            case 128:  // DecimalLiteral
            case 129:  // BinaryLiteral
            case 130:  // StringLiteral
                value.move< ValueAtom::Ptr >( that.value );
                break;

            case 152:  // Variable
            case 153:  // TypedVariable
            case 154:  // AttributedVariable
            case 155:  // TypedAttributedVariable
                value.move< VariableDefinition::Ptr >( that.value );
                break;

            case 133:  // Type
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
            case 157:  // Attribute
                value.copy< Attribute::Ptr >( that.value );
                break;

            case 156:  // Attributes
                value.copy< Attributes::Ptr >( that.value );
                break;

            case 158:  // BasicAttribute
                value.copy< BasicAttribute::Ptr >( that.value );
                break;

            case 134:  // BasicType
                value.copy< BasicType::Ptr >( that.value );
                break;

            case 106:  // BlockRule
                value.copy< BlockRule::Ptr >( that.value );
                break;

            case 109:  // CallRule
                value.copy< CallRule::Ptr >( that.value );
                break;

            case 100:  // CaseLabel
                value.copy< Case::Ptr >( that.value );
                break;

            case 99:  // CaseRule
                value.copy< CaseRule::Ptr >( that.value );
                break;

            case 101:  // CaseLabels
                value.copy< Cases::Ptr >( that.value );
                break;

            case 118:  // ChooseExpression
                value.copy< ChooseExpression::Ptr >( that.value );
                break;

            case 104:  // ChooseRule
                value.copy< ChooseRule::Ptr >( that.value );
                break;

            case 135:  // ComposedType
                value.copy< ComposedType::Ptr >( that.value );
                break;

            case 117:  // ConditionalExpression
                value.copy< ConditionalExpression::Ptr >( that.value );
                break;

            case 98:  // ConditionalRule
                value.copy< ConditionalRule::Ptr >( that.value );
                break;

            case 86:  // AttributedDefinition
            case 87:  // Definition
                value.copy< Definition::Ptr >( that.value );
                break;

            case 85:  // Definitions
                value.copy< Definitions::Ptr >( that.value );
                break;

            case 89:  // DerivedDefinition
                value.copy< DerivedDefinition::Ptr >( that.value );
                break;

            case 114:  // DirectCallExpression
                value.copy< DirectCallExpression::Ptr >( that.value );
                break;

            case 88:  // EnumerationDefinition
                value.copy< EnumerationDefinition::Ptr >( that.value );
                break;

            case 93:  // EnumeratorDefinition
                value.copy< EnumeratorDefinition::Ptr >( that.value );
                break;

            case 94:  // Enumerators
                value.copy< Enumerators::Ptr >( that.value );
                break;

            case 120:  // ExistentialQuantifierExpression
                value.copy< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // Term
            case 112:  // Expression
            case 123:  // Literal
            case 144:  // MaybeDefined
                value.copy< Expression::Ptr >( that.value );
                break;

            case 159:  // ExpressionAttribute
                value.copy< ExpressionAttribute::Ptr >( that.value );
                break;

            case 110:  // Terms
            case 138:  // Arguments
            case 139:  // TwoOrMoreArguments
                value.copy< Expressions::Ptr >( that.value );
                break;

            case 137:  // FixedSizedType
                value.copy< FixedSizedType::Ptr >( that.value );
                break;

            case 103:  // ForallRule
                value.copy< ForallRule::Ptr >( that.value );
                break;

            case 91:  // FunctionDefinition
            case 92:  // ProgramFunctionDefinition
                value.copy< FunctionDefinition::Ptr >( that.value );
                break;

            case 84:  // Header
                value.copy< HeaderDefinition::Ptr >( that.value );
                break;

            case 149:  // Identifier
                value.copy< Identifier::Ptr >( that.value );
                break;

            case 150:  // IdentifierPath
                value.copy< IdentifierPath::Ptr >( that.value );
                break;

            case 151:  // DotSeparatedIdentifiers
                value.copy< Identifiers::Ptr >( that.value );
                break;

            case 115:  // IndirectCallExpression
                value.copy< IndirectCallExpression::Ptr >( that.value );
                break;

            case 105:  // IterateRule
                value.copy< IterateRule::Ptr >( that.value );
                break;

            case 116:  // LetExpression
                value.copy< LetExpression::Ptr >( that.value );
                break;

            case 102:  // LetRule
                value.copy< LetRule::Ptr >( that.value );
                break;

            case 121:  // List
                value.copy< ListExpression::Ptr >( that.value );
                break;

            case 145:  // MaybeInitially
            case 146:  // Initializers
            case 148:  // MaybeInitializers
                value.copy< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 142:  // Parameters
            case 143:  // MaybeParameters
                value.copy< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 122:  // Range
                value.copy< RangeExpression::Ptr >( that.value );
                break;

            case 131:  // ReferenceLiteral
                value.copy< ReferenceAtom::Ptr >( that.value );
                break;

            case 136:  // RelationType
                value.copy< RelationType::Ptr >( that.value );
                break;

            case 95:  // Rule
                value.copy< Rule::Ptr >( that.value );
                break;

            case 90:  // RuleDefinition
                value.copy< RuleDefinition::Ptr >( that.value );
                break;

            case 96:  // Rules
                value.copy< Rules::Ptr >( that.value );
                break;

            case 107:  // SequenceRule
                value.copy< SequenceRule::Ptr >( that.value );
                break;

            case 97:  // SkipRule
                value.copy< SkipRule::Ptr >( that.value );
                break;

            case 83:  // Specification
                value.copy< Specification::Ptr >( that.value );
                break;

            case 113:  // TypeCastingExpression
                value.copy< TypeCastingExpression::Ptr >( that.value );
                break;

            case 132:  // Types
            case 140:  // FunctionParameters
            case 141:  // MaybeFunctionParameters
                value.copy< Types::Ptr >( that.value );
                break;

            case 124:  // UndefinedLiteral
                value.copy< UndefAtom::Ptr >( that.value );
                break;

            case 119:  // UniversalQuantifierExpression
                value.copy< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 108:  // UpdateRule
            case 147:  // Initializer
                value.copy< UpdateRule::Ptr >( that.value );
                break;

            case 125:  // BooleanLiteral
            case 126:  // IntegerLiteral
            case 127:  // RationalLiteral
            case 128:  // DecimalLiteral
            case 129:  // BinaryLiteral
            case 130:  // StringLiteral
                value.copy< ValueAtom::Ptr >( that.value );
                break;

            case 152:  // Variable
            case 153:  // TypedVariable
            case 154:  // AttributedVariable
            case 155:  // TypedAttributedVariable
                value.copy< VariableDefinition::Ptr >( that.value );
                break;

            case 133:  // Type
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
                    case 157:  // Attribute
                        yylhs.value.build< Attribute::Ptr >();
                        break;

                    case 156:  // Attributes
                        yylhs.value.build< Attributes::Ptr >();
                        break;

                    case 158:  // BasicAttribute
                        yylhs.value.build< BasicAttribute::Ptr >();
                        break;

                    case 134:  // BasicType
                        yylhs.value.build< BasicType::Ptr >();
                        break;

                    case 106:  // BlockRule
                        yylhs.value.build< BlockRule::Ptr >();
                        break;

                    case 109:  // CallRule
                        yylhs.value.build< CallRule::Ptr >();
                        break;

                    case 100:  // CaseLabel
                        yylhs.value.build< Case::Ptr >();
                        break;

                    case 99:  // CaseRule
                        yylhs.value.build< CaseRule::Ptr >();
                        break;

                    case 101:  // CaseLabels
                        yylhs.value.build< Cases::Ptr >();
                        break;

                    case 118:  // ChooseExpression
                        yylhs.value.build< ChooseExpression::Ptr >();
                        break;

                    case 104:  // ChooseRule
                        yylhs.value.build< ChooseRule::Ptr >();
                        break;

                    case 135:  // ComposedType
                        yylhs.value.build< ComposedType::Ptr >();
                        break;

                    case 117:  // ConditionalExpression
                        yylhs.value.build< ConditionalExpression::Ptr >();
                        break;

                    case 98:  // ConditionalRule
                        yylhs.value.build< ConditionalRule::Ptr >();
                        break;

                    case 86:  // AttributedDefinition
                    case 87:  // Definition
                        yylhs.value.build< Definition::Ptr >();
                        break;

                    case 85:  // Definitions
                        yylhs.value.build< Definitions::Ptr >();
                        break;

                    case 89:  // DerivedDefinition
                        yylhs.value.build< DerivedDefinition::Ptr >();
                        break;

                    case 114:  // DirectCallExpression
                        yylhs.value.build< DirectCallExpression::Ptr >();
                        break;

                    case 88:  // EnumerationDefinition
                        yylhs.value.build< EnumerationDefinition::Ptr >();
                        break;

                    case 93:  // EnumeratorDefinition
                        yylhs.value.build< EnumeratorDefinition::Ptr >();
                        break;

                    case 94:  // Enumerators
                        yylhs.value.build< Enumerators::Ptr >();
                        break;

                    case 120:  // ExistentialQuantifierExpression
                        yylhs.value.build< ExistentialQuantifierExpression::Ptr >();
                        break;

                    case 111:  // Term
                    case 112:  // Expression
                    case 123:  // Literal
                    case 144:  // MaybeDefined
                        yylhs.value.build< Expression::Ptr >();
                        break;

                    case 159:  // ExpressionAttribute
                        yylhs.value.build< ExpressionAttribute::Ptr >();
                        break;

                    case 110:  // Terms
                    case 138:  // Arguments
                    case 139:  // TwoOrMoreArguments
                        yylhs.value.build< Expressions::Ptr >();
                        break;

                    case 137:  // FixedSizedType
                        yylhs.value.build< FixedSizedType::Ptr >();
                        break;

                    case 103:  // ForallRule
                        yylhs.value.build< ForallRule::Ptr >();
                        break;

                    case 91:  // FunctionDefinition
                    case 92:  // ProgramFunctionDefinition
                        yylhs.value.build< FunctionDefinition::Ptr >();
                        break;

                    case 84:  // Header
                        yylhs.value.build< HeaderDefinition::Ptr >();
                        break;

                    case 149:  // Identifier
                        yylhs.value.build< Identifier::Ptr >();
                        break;

                    case 150:  // IdentifierPath
                        yylhs.value.build< IdentifierPath::Ptr >();
                        break;

                    case 151:  // DotSeparatedIdentifiers
                        yylhs.value.build< Identifiers::Ptr >();
                        break;

                    case 115:  // IndirectCallExpression
                        yylhs.value.build< IndirectCallExpression::Ptr >();
                        break;

                    case 105:  // IterateRule
                        yylhs.value.build< IterateRule::Ptr >();
                        break;

                    case 116:  // LetExpression
                        yylhs.value.build< LetExpression::Ptr >();
                        break;

                    case 102:  // LetRule
                        yylhs.value.build< LetRule::Ptr >();
                        break;

                    case 121:  // List
                        yylhs.value.build< ListExpression::Ptr >();
                        break;

                    case 145:  // MaybeInitially
                    case 146:  // Initializers
                    case 148:  // MaybeInitializers
                        yylhs.value.build< NodeList< UpdateRule >::Ptr >();
                        break;

                    case 142:  // Parameters
                    case 143:  // MaybeParameters
                        yylhs.value.build< NodeList< VariableDefinition >::Ptr >();
                        break;

                    case 122:  // Range
                        yylhs.value.build< RangeExpression::Ptr >();
                        break;

                    case 131:  // ReferenceLiteral
                        yylhs.value.build< ReferenceAtom::Ptr >();
                        break;

                    case 136:  // RelationType
                        yylhs.value.build< RelationType::Ptr >();
                        break;

                    case 95:  // Rule
                        yylhs.value.build< Rule::Ptr >();
                        break;

                    case 90:  // RuleDefinition
                        yylhs.value.build< RuleDefinition::Ptr >();
                        break;

                    case 96:  // Rules
                        yylhs.value.build< Rules::Ptr >();
                        break;

                    case 107:  // SequenceRule
                        yylhs.value.build< SequenceRule::Ptr >();
                        break;

                    case 97:  // SkipRule
                        yylhs.value.build< SkipRule::Ptr >();
                        break;

                    case 83:  // Specification
                        yylhs.value.build< Specification::Ptr >();
                        break;

                    case 113:  // TypeCastingExpression
                        yylhs.value.build< TypeCastingExpression::Ptr >();
                        break;

                    case 132:  // Types
                    case 140:  // FunctionParameters
                    case 141:  // MaybeFunctionParameters
                        yylhs.value.build< Types::Ptr >();
                        break;

                    case 124:  // UndefinedLiteral
                        yylhs.value.build< UndefAtom::Ptr >();
                        break;

                    case 119:  // UniversalQuantifierExpression
                        yylhs.value.build< UniversalQuantifierExpression::Ptr >();
                        break;

                    case 108:  // UpdateRule
                    case 147:  // Initializer
                        yylhs.value.build< UpdateRule::Ptr >();
                        break;

                    case 125:  // BooleanLiteral
                    case 126:  // IntegerLiteral
                    case 127:  // RationalLiteral
                    case 128:  // DecimalLiteral
                    case 129:  // BinaryLiteral
                    case 130:  // StringLiteral
                        yylhs.value.build< ValueAtom::Ptr >();
                        break;

                    case 152:  // Variable
                    case 153:  // TypedVariable
                    case 154:  // AttributedVariable
                    case 155:  // TypedAttributedVariable
                        yylhs.value.build< VariableDefinition::Ptr >();
                        break;

                    case 133:  // Type
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
#line 380 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            specification.setHeader(
                                yystack_[ 1 ].value.as< HeaderDefinition::Ptr >() );
                            specification.setDefinitions(
                                yystack_[ 0 ].value.as< Definitions::Ptr >() );
                        }
#line 1362 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 3:
#line 389 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< HeaderDefinition::Ptr >() = definition;
                        }
#line 1372 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 4:
#line 395 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< HeaderDefinition::Ptr >() =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                        }
#line 1380 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 5:
#line 403 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = yystack_[ 1 ].value.as< Definitions::Ptr >();
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1390 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 6:
#line 409 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = Ast::make< Definitions >( yylhs.location );
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1400 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 7:
#line 419 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition = yystack_[ 0 ].value.as< Definition::Ptr >();
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< Definition::Ptr >() = definition;
                        }
#line 1410 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 8:
#line 425 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< Definition::Ptr >();
                        }
#line 1418 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 9:
#line 429 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() = nullptr;
                        }
#line 1426 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 10:
#line 437 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< EnumerationDefinition::Ptr >();
                        }
#line 1434 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 11:
#line 441 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< DerivedDefinition::Ptr >();
                        }
#line 1442 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 12:
#line 445 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< RuleDefinition::Ptr >();
                        }
#line 1450 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 13:
#line 449 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< FunctionDefinition::Ptr >();
                        }
#line 1458 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 14:
#line 457 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumerationDefinition::Ptr >() =
                                Ast::make< EnumerationDefinition >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 1 ].value.as< Enumerators::Ptr >() );
                        }
#line 1466 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 15:
#line 465 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DerivedDefinition::Ptr >() =
                                Ast::make< DerivedDefinition >(
                                    yylhs.location,
                                    yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                    yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1474 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 16:
#line 473 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Identifier::Ptr >(),
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                createVoidType( yylhs.location ),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1483 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 17:
#line 478 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1492 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 18:
#line 487 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
                                initializer->function()->setIdentifier(
                                    asIdentifierPath( identifier ) );
                            }
                            function->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = function;
                        }
#line 1512 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 19:
#line 503 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FunctionDefinition::Ptr >() =
                                yystack_[ 0 ]
                                    .value.as< FunctionDefinition::Ptr >();  // `init` special case
                        }
#line 1520 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 20:
#line 511 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto singleAgentIdentifier =
                                Ast::make< Identifier >( yylhs.location, "$" );
                            auto singleAgentArguments =
                                libcasm_fe::Ast::make< Expressions >( yylhs.location );
                            const auto singleAgent = libcasm_fe::Ast::make< DirectCallExpression >(
                                yylhs.location,
                                asIdentifierPath( singleAgentIdentifier ),
                                singleAgentArguments );
                            singleAgent->setTargetType( CallExpression::TargetType::CONSTANT );

                            auto programDefinition = createProgramFunction( yylhs.location );
                            auto programArguments =
                                libcasm_fe::Ast::make< Expressions >( yylhs.location );
                            programArguments->add( singleAgent );
                            const auto program = libcasm_fe::Ast::make< DirectCallExpression >(
                                yylhs.location,
                                asIdentifierPath( programDefinition->identifier() ),
                                programArguments );
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
#line 1547 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 21:
#line 534 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto programDefinition = createProgramFunction( yylhs.location );

                            // apply the name of the program declaration to the initializer
                            // functions
                            auto initializers =
                                yystack_[ 1 ].value.as< NodeList< UpdateRule >::Ptr >();
                            for( auto& initializer : *initializers )
                            {
                                initializer->function()->setIdentifier(
                                    asIdentifierPath( programDefinition->identifier() ) );
                            }
                            programDefinition->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = programDefinition;
                        }
#line 1565 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 22:
#line 552 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() =
                                Ast::make< EnumeratorDefinition >(
                                    yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 1573 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 23:
#line 556 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerator = Ast::make< EnumeratorDefinition >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            enumerator->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = enumerator;
                        }
#line 1583 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 24:
#line 562 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = nullptr;
                        }
#line 1591 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 25:
#line 570 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = yystack_[ 2 ].value.as< Enumerators::Ptr >();
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1601 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 26:
#line 576 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = Ast::make< Enumerators >( yylhs.location );
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1611 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 27:
#line 590 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SkipRule::Ptr >();
                        }
#line 1619 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 28:
#line 594 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalRule::Ptr >();
                        }
#line 1627 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 29:
#line 598 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CaseRule::Ptr >();
                        }
#line 1635 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 30:
#line 602 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< LetRule::Ptr >();
                        }
#line 1643 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 31:
#line 606 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ForallRule::Ptr >();
                        }
#line 1651 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 32:
#line 610 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseRule::Ptr >();
                        }
#line 1659 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 33:
#line 614 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< IterateRule::Ptr >();
                        }
#line 1667 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 34:
#line 618 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< BlockRule::Ptr >();
                        }
#line 1675 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 35:
#line 622 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SequenceRule::Ptr >();
                        }
#line 1683 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 36:
#line 626 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRule::Ptr >();
                        }
#line 1691 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 37:
#line 630 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CallRule::Ptr >();
                        }
#line 1699 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 38:
#line 638 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = yystack_[ 1 ].value.as< Rules::Ptr >();
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1709 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 39:
#line 644 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = Ast::make< Rules >( yylhs.location );
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1719 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 40:
#line 654 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SkipRule::Ptr >() =
                                Ast::make< SkipRule >( yylhs.location );
                        }
#line 1727 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 41:
#line 662 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1735 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 42:
#line 666 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Rule::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1743 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 43:
#line 674 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = Ast::make< CaseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Cases::Ptr >() );
                        }
#line 1751 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 44:
#line 678 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = nullptr;
                        }
#line 1759 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 45:
#line 686 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1767 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 46:
#line 690 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1775 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 47:
#line 694 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< ExpressionCase >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1783 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 48:
#line 702 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = yystack_[ 1 ].value.as< Cases::Ptr >();
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1793 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 49:
#line 708 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = Ast::make< Cases >( yylhs.location );
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1803 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 50:
#line 718 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetRule::Ptr >() = Ast::make< LetRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1811 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 51:
#line 726 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1819 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 52:
#line 730 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 6 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1827 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 53:
#line 738 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseRule::Ptr >() = Ast::make< ChooseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1835 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 54:
#line 746 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IterateRule::Ptr >() = Ast::make< IterateRule >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1843 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 55:
#line 754 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1851 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 56:
#line 758 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1859 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 57:
#line 762 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1868 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 58:
#line 767 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1877 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 59:
#line 776 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1885 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 60:
#line 780 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1893 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 61:
#line 784 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1902 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 62:
#line 789 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1911 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 63:
#line 798 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto function =
                                yystack_[ 2 ].value.as< DirectCallExpression::Ptr >();
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1921 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 64:
#line 808 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 1929 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 65:
#line 812 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 1937 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 66:
#line 816 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 1945 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 67:
#line 820 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 1953 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 68:
#line 832 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto expressions = yystack_[ 2 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 1963 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 69:
#line 838 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 1973 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 70:
#line 848 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 1981 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 71:
#line 852 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TypeCastingExpression::Ptr >();
                        }
#line 1989 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 72:
#line 856 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >();
                        }
#line 1997 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 73:
#line 860 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >();
                        }
#line 2005 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 74:
#line 864 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LetExpression::Ptr >();
                        }
#line 2013 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 75:
#line 868 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalExpression::Ptr >();
                        }
#line 2021 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 76:
#line 872 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseExpression::Ptr >();
                        }
#line 2029 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 77:
#line 876 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UniversalQuantifierExpression::Ptr >();
                        }
#line 2037 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 78:
#line 880 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ExistentialQuantifierExpression::Ptr >();
                        }
#line 2045 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 79:
#line 884 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ListExpression::Ptr >();
                        }
#line 2053 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 80:
#line 888 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< RangeExpression::Ptr >();
                        }
#line 2061 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 81:
#line 892 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2069 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 82:
#line 904 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2077 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 83:
#line 908 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = nullptr;
                        }
#line 2085 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 84:
#line 912 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2093 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 85:
#line 916 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::INV_INSTRUCTION );
                        }
#line 2101 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 86:
#line 920 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::ADD_INSTRUCTION );
                        }
#line 2109 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 87:
#line 924 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::SUB_INSTRUCTION );
                        }
#line 2117 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 88:
#line 928 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MUL_INSTRUCTION );
                        }
#line 2125 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 89:
#line 932 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::DIV_INSTRUCTION );
                        }
#line 2133 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 90:
#line 936 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MOD_INSTRUCTION );
                        }
#line 2141 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 91:
#line 940 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::POW_INSTRUCTION );
                        }
#line 2149 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 92:
#line 944 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NEQ_INSTRUCTION );
                        }
#line 2157 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 93:
#line 948 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::EQU_INSTRUCTION );
                        }
#line 2165 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 94:
#line 952 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LTH_INSTRUCTION );
                        }
#line 2173 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 95:
#line 956 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GTH_INSTRUCTION );
                        }
#line 2181 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 96:
#line 960 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LEQ_INSTRUCTION );
                        }
#line 2189 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 97:
#line 964 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GEQ_INSTRUCTION );
                        }
#line 2197 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 98:
#line 968 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::OR_INSTRUCTION );
                        }
#line 2205 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 99:
#line 972 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::XOR_INSTRUCTION );
                        }
#line 2213 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 100:
#line 976 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::AND_INSTRUCTION );
                        }
#line 2221 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 101:
#line 980 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2229 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 102:
#line 984 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2237 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 103:
#line 988 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NOT_INSTRUCTION );
                        }
#line 2245 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 104:
#line 996 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TypeCastingExpression::Ptr >() =
                                Ast::make< TypeCastingExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2253 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 105:
#line 1004 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< IdentifierPath::Ptr >(),
                                    arguments );
                        }
#line 2262 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 106:
#line 1009 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< IdentifierPath::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2270 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 107:
#line 1017 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IndirectCallExpression::Ptr >() =
                                Ast::make< IndirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2278 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 108:
#line 1025 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetExpression::Ptr >() = Ast::make< LetExpression >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2286 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 109:
#line 1033 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalExpression::Ptr >() =
                                Ast::make< ConditionalExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Expression::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2294 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 110:
#line 1041 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseExpression::Ptr >() =
                                Ast::make< ChooseExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2302 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 111:
#line 1049 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UniversalQuantifierExpression::Ptr >() =
                                Ast::make< UniversalQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2310 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 112:
#line 1057 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExistentialQuantifierExpression::Ptr >() =
                                Ast::make< ExistentialQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2318 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 113:
#line 1065 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< ListExpression::Ptr >() =
                                Ast::make< ListExpression >( yylhs.location, expressions );
                        }
#line 2327 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 114:
#line 1070 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListExpression::Ptr >() = Ast::make< ListExpression >(
                                yylhs.location, yystack_[ 1 ].value.as< Expressions::Ptr >() );
                        }
#line 2335 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 115:
#line 1074 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListExpression::Ptr >() = nullptr;
                        }
#line 2343 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 116:
#line 1082 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RangeExpression::Ptr >() = Ast::make< RangeExpression >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Expression::Ptr >() );
                        }
#line 2351 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 117:
#line 1094 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UndefAtom::Ptr >();
                        }
#line 2359 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 118:
#line 1098 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2367 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 119:
#line 1102 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2375 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 120:
#line 1106 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2383 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 121:
#line 1110 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2391 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 122:
#line 1114 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2399 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 123:
#line 1118 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2407 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 124:
#line 1122 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ReferenceAtom::Ptr >();
                        }
#line 2415 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 125:
#line 1130 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UndefAtom::Ptr >() =
                                Ast::make< UndefAtom >( yylhs.location );
                        }
#line 2423 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 126:
#line 1138 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
                            yylhs.value.as< ValueAtom::Ptr >() =
                                Ast::make< ValueAtom >( yylhs.location, value );
                        }
#line 2432 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 127:
#line 1143 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
                            yylhs.value.as< ValueAtom::Ptr >() =
                                Ast::make< ValueAtom >( yylhs.location, value );
                        }
#line 2441 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 128:
#line 1152 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2457 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 129:
#line 1168 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2473 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 130:
#line 1184 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2489 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 131:
#line 1200 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2505 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 132:
#line 1212 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2521 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 133:
#line 1228 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2537 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 134:
#line 1244 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ReferenceAtom::Ptr >() = Ast::make< ReferenceAtom >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2545 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 135:
#line 1256 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2555 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 136:
#line 1262 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2565 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 137:
#line 1272 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< BasicType::Ptr >();
                        }
#line 2573 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 138:
#line 1276 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2581 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 139:
#line 1280 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< RelationType::Ptr >();
                        }
#line 2589 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 140:
#line 1284 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< FixedSizedType::Ptr >();
                        }
#line 2597 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 141:
#line 1292 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicType::Ptr >() = Ast::make< BasicType >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2605 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 142:
#line 1300 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ComposedType::Ptr >() = Ast::make< ComposedType >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 1 ].value.as< Types::Ptr >() );
                        }
#line 2613 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 143:
#line 1308 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RelationType::Ptr >() = Ast::make< RelationType >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 3 ].value.as< Types::Ptr >(),
                                yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2621 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 144:
#line 1316 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FixedSizedType::Ptr >() = Ast::make< FixedSizedType >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2629 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 145:
#line 1328 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() =
                                yystack_[ 1 ].value.as< Expressions::Ptr >();
                        }
#line 2637 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 146:
#line 1332 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() = nullptr;
                        }
#line 2645 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 147:
#line 1336 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2654 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 148:
#line 1345 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = yystack_[ 3 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 1 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2664 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 149:
#line 1359 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2674 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 150:
#line 1365 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2684 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 151:
#line 1375 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = yystack_[ 0 ].value.as< Types::Ptr >();
                        }
#line 2692 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 152:
#line 1379 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = Ast::make< Types >( yylhs.location );
                        }
#line 2700 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 153:
#line 1387 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >();
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2710 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 154:
#line 1393 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2720 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 155:
#line 1403 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< VariableDefinition >::Ptr >();
                        }
#line 2728 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 156:
#line 1407 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = nullptr;
                        }
#line 2736 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 157:
#line 1411 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                        }
#line 2744 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 158:
#line 1423 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2752 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 159:
#line 1427 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                Ast::make< UndefAtom >( yylhs.location );
                        }
#line 2760 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 160:
#line 1435 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2768 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 161:
#line 1439 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2776 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 162:
#line 1447 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                yystack_[ 2 ].value.as< NodeList< UpdateRule >::Ptr >();
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2786 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 163:
#line 1453 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2796 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 164:
#line 1463 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2808 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 165:
#line 1471 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2822 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 166:
#line 1481 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2833 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 167:
#line 1492 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 0 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2841 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 168:
#line 1496 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2849 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 169:
#line 1508 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() = Ast::make< Identifier >(
                                yylhs.location, yystack_[ 0 ].value.as< std::string >() );
                        }
#line 2857 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 170:
#line 1512 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() =
                                Ast::make< Identifier >( yylhs.location, "in" );
                        }
#line 2865 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 171:
#line 1520 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Identifiers::Ptr >(),
                                IdentifierPath::Type::ABSOLUTE );
                        }
#line 2873 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 172:
#line 1524 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
                        }
#line 2883 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 173:
#line 1534 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = yystack_[ 2 ].value.as< Identifiers::Ptr >();
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2893 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 174:
#line 1540 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2903 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 175:
#line 1554 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 2911 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 176:
#line 1558 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto unresolvedType =
                                Ast::make< UnresolvedType >( yylhs.location );
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    unresolvedType );
                        }
#line 2920 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 177:
#line 1567 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2928 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 178:
#line 1575 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 2938 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 179:
#line 1581 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 2946 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 180:
#line 1589 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 2956 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 181:
#line 1595 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 2964 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 182:
#line 1607 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = yystack_[ 2 ].value.as< Attributes::Ptr >();
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 2974 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 183:
#line 1613 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = Ast::make< Attributes >( yylhs.location );
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 2984 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 184:
#line 1622 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< BasicAttribute::Ptr >();
                        }
#line 2992 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 185:
#line 1626 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< ExpressionAttribute::Ptr >();
                        }
#line 3000 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 186:
#line 1634 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicAttribute::Ptr >() = Ast::make< BasicAttribute >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 3008 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 187:
#line 1642 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExpressionAttribute::Ptr >() =
                                Ast::make< ExpressionAttribute >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 3016 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

#line 3020 "GrammarParser.cpp"  // lalr1.cc:859
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

    const short int Parser::yypact_ninf_ = -204;

    const short int Parser::yytable_ninf_ = -151;

    const short int Parser::yypact_[] = {
        -1,   -204, 4,    20,   146,  -204, -204, 969,  -30,  -204, -204, -204, -204, -204, -5,
        4,    4,    4,    4,    4,    219,  -204, -204, -204, -204, -204, -204, -204, -2,   -2,
        -2,   969,  -2,   -204, -204, -204, 969,  969,  969,  489,  551,  -3,   4,    -204, -204,
        -204, -204, -204, -204, 1778, -204, -204, -204, -204, -204, -204, -204, -204, -204, -204,
        -204, -204, -204, -204, -204, -204, -204, -204, -204, -204, -204, -39,  -20,  46,   4,
        1031, -204, 26,   17,   26,   34,   -12,  -204, 4,    42,   -204, -204, 52,   35,   80,
        1303, 100,  -204, -204, -204, 81,   969,  1514, 71,   -204, 0,    1547, -204, -204, -3,
        969,  969,  969,  969,  969,  969,  969,  969,  969,  969,  969,  969,  969,  969,  969,
        969,  969,  613,  -204, 4,    -204, -204, 489,  1580, 62,   75,   -204, 83,   2,    66,
        82,   -27,  -3,   270,  9,    -3,   969,  969,  969,  969,  969,  -204, 1613, -204, -204,
        -204, 969,  969,  -204, -204, -204, -204, -204, 1,    1878, 1844, 1872, 1811, 138,  138,
        777,  128,  128,  74,   74,   74,   -204, 1811, 777,  128,  128,  95,   -204, -35,  1778,
        -204, 88,   1514, 969,  969,  1031, -204, 98,   4,    -19,  42,   -204, -204, -3,   5,
        869,  -3,   -204, 92,   86,   -204, 4,    -204, 1077, 1443, 1188, 1377, 1481, -39,  1778,
        1646, -3,   969,  -204, -204, 969,  1778, 1778, -204, -204, 40,   -204, 8,    112,  -204,
        4,    -204, 70,   -204, 355,  651,  -204, -2,   -2,   -2,   869,  -4,   969,  969,  110,
        692,  726,  -204, -204, -204, -204, -204, -204, -204, -204, -204, -204, -204, -204, 109,
        -204, 132,  -3,   -3,   -204, 969,  969,  969,  969,  969,  -204, -204, 16,   -17,  115,
        -204, 1679, 4,    -204, 969,  41,   -204, 5,    167,  -204, 760,  168,  145,  147,  171,
        174,  -204, -204, -204, 1340, 1410, 150,  794,  130,  835,  969,  869,  -204, 191,  1778,
        1778, 1778, 1778, 1778, -3,   -204, -3,   -204, -204, 1778, 4,    -204, -204, -204, -204,
        -204, -204, 969,  969,  969,  869,  154,  -204, -204, -204, -204, 1778, -204, 158,  200,
        -204, 160,  -204, 1110, 1149, 1227, 192,  427,  969,  170,  -204, -204, 869,  869,  969,
        869,  869,  172,  166,  178,  -204, 907,  1712, 1745, 1031, -204, -204, 1266, -204, -204,
        -204, 869,  869,  -204, -204, 869,  -204, 180,  869,  -204, -204, -204, -204, -204
    };

    const unsigned char Parser::yydefact_[] = {
        0,   4,   0,   0,   0,   170, 169, 186, 0,   183, 184, 185, 1,   9,   0,   0,   0,   0,
        0,   0,   0,   6,   8,   10,  11,  12,  13,  19,  0,   0,   0,   0,   0,   125, 127, 126,
        0,   0,   0,   0,   0,   0,   0,   131, 132, 128, 129, 130, 133, 187, 70,  71,  72,  73,
        74,  75,  76,  77,  78,  79,  80,  81,  117, 118, 119, 120, 121, 122, 123, 124, 174, 105,
        171, 0,   0,   168, 20,  157, 0,   157, 0,   0,   5,   0,   176, 179, 175, 0,   0,   0,
        0,   0,   103, 84,  85,  0,   0,   0,   0,   113, 0,   69,  134, 172, 0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   106, 0,   3,
        182, 0,   164, 0,   167, 163, 0,   0,   0,   0,   0,   152, 0,   0,   0,   0,   0,   0,
        0,   0,   83,  0,   82,  115, 114, 0,   0,   104, 137, 138, 139, 140, 141, 100, 98,  99,
        102, 86,  87,  93,  94,  95,  88,  89,  90,  91,  101, 92,  96,  97,  0,   147, 0,   69,
        173, 0,   69,  0,   0,   0,   21,  0,   0,   0,   0,   181, 154, 0,   0,   0,   0,   150,
        151, 0,   7,   0,   177, 0,   0,   0,   0,   0,   0,   68,  0,   152, 0,   146, 145, 0,
        165, 166, 162, 156, 0,   155, 0,   0,   24,  0,   26,  0,   22,  0,   0,   40,  0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   16,  27,  28,  29,  30,  31,  32,  33,  34,  35,
        36,  37,  65,  67,  0,   0,   0,   178, 0,   0,   0,   0,   0,   107, 116, 0,   136, 0,
        144, 68,  0,   153, 0,   0,   14,  0,   0,   39,  0,   0,   0,   0,   0,   0,   54,  64,
        66,  0,   0,   0,   0,   0,   0,   0,   0,   149, 159, 108, 111, 110, 109, 112, 0,   142,
        0,   148, 180, 15,  0,   25,  62,  60,  38,  58,  56,  0,   0,   0,   0,   0,   57,  55,
        61,  59,  63,  17,  0,   161, 135, 0,   23,  0,   0,   0,   41,  0,   0,   0,   18,  143,
        0,   0,   0,   0,   0,   0,   0,   0,   49,  0,   0,   0,   168, 50,  51,  0,   53,  42,
        44,  0,   0,   43,  48,  0,   158, 0,   0,   45,  46,  47,  160, 52
    };

    const short int Parser::yypgoto_[] = {
        -204, -204, -204, -204, 212,  96,   -204, -204, -204, -204, -204, -44,  -204,
        44,   -203, -204, -204, -204, -116, -204, -204, -204, -204, -204, -204, -204,
        -204, -204, -6,   -7,   -204, -204, 65,   73,   -204, -204, -204, -204, -204,
        -204, -204, -204, -204, -204, -204, -204, -204, -204, -204, -204, -204, -54,
        -204, -204, -204, -204, 29,   -204, -204, 27,   -204, 161,  -204, -204, -204,
        56,   -111, 48,   -13,  -204, 45,   -126, -21,  25,   -15,  177,  -204, -204
    };

    const short int Parser::yydefgoto_[] = {
        -1,  3,   4,   20,  21,  22,  23,  24,  25,  26,  27,  226, 227, 279, 280, 243,
        244, 245, 350, 351, 246, 247, 248, 249, 250, 251, 252, 253, 100, 128, 50,  51,
        52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,
        68,  69,  267, 153, 154, 155, 156, 157, 123, 129, 198, 199, 189, 134, 329, 340,
        130, 131, 132, 70,  71,  72,  85,  86,  87,  192, 8,   9,   10,  11
    };

    const short int Parser::yytable_[] = {
        49,  76,  1,   187,  81,  122, 224, 191, 88,  89,  214,  91,  5,   5,   5,   5,   195, 73,
        151, 5,   12,  5,    5,   74,  90,  5,   221, 282, 102,  92,  93,  94,  97,  101, 222, 138,
        196, 292, 294, -150, 239, 74,  124, 75,  83,  2,   -150, 150, 188, 125, 7,   225, 142, 151,
        188, 211, 201, 42,   42,  42,  135, 212, 74,  77,  78,   79,  80,  7,   139, 304, 133, 305,
        6,   6,   6,   6,    84,  84,  84,  6,   84,  6,   6,    197, 137, 6,   202, 272, 310, 147,
        103, 158, 140, 74,   74,  141, 191, 143, 159, 160, 161,  162, 163, 164, 165, 166, 167, 168,
        169, 170, 171, 172,  173, 174, 175, 179, 178, 145, 149,  276, 182, 181, 7,   277, 158, 184,
        146, 158, 185, 193,  194, 7,   186, 117, 203, 204, 205,  206, 207, 223, 213, 215, 256, 219,
        209, 210, 308, 13,   257, 258, 14,  15,  16,  17,  18,   274, 229, 268, 230, 316, 231, 232,
        5,   233, 234, 235,  96,  236, 237, 109, 110, 238, 180,  220, 295, 296, 216, 217, 306, 312,
        158, 190, 315, 158,  114, 115, 116, 117, 318, 239, 317,  319, 19,  240, 114, 115, 116, 117,
        158, 322, 324, 328,  337, 297, 298, 270, 338, 42,  271,  339, 275, 283, 284, 285, 241, 341,
        361, 346, 354, -2,   13,  360, 6,   14,  15,  16,  17,   18,  362, 372, 289, 290, 82,  311,
        200, 364, 7,   265,  269, 242, 136, 218, 228, 367, 158,  158, 259, 273, 0,   84,  330, 126,
        331, 299, 300, 301,  302, 303, 0,   0,   254, 0,   0,    0,   0,   19,  0,   309, 255, 0,
        190, 0,   0,   7,    14,  15,  16,  17,  18,  286, 84,   84,  84,  0,   0,   0,   0,   0,
        326, 0,   0,   158,  0,   158, 254, 254, 0,   0,   0,    0,   254, 287, 255, 255, 0,   254,
        254, 0,   255, 288,  333, 334, 335, 255, 255, 0,   0,    0,   0,   0,   190, 0,   0,   0,
        314, 228, 314, 0,    0,   0,   352, 353, 0,   0,   0,    0,   314, 357, 314, 0,   327, 0,
        0,   0,   352, 254,  0,   254, 0,   0,   0,   0,   0,    255, 0,   255, 278, 254, 332, 254,
        0,   254, 0,   0,    336, 255, 229, 255, 230, 255, 231,  232, 5,   233, 234, 235, 0,   236,
        237, 0,   0,   238,  0,   0,   0,   254, 355, 356, 0,    358, 359, 0,   0,   255, 0,   0,
        0,   0,   0,   239,  0,   0,   0,   240, 0,   369, 370,  254, 254, 371, 254, 254, 373, 0,
        0,   255, 255, 42,   255, 255, 0,   0,   0,   0,   241,  0,   254, 254, 347, 0,   254, 0,
        6,   254, 255, 255,  0,   0,   255, 0,   0,   255, 0,    28,  5,   29,  30,  0,   0,   0,
        31,  0,   0,   0,    0,   348, 0,   32,  0,   0,   33,   34,  35,  0,   0,   0,   0,   36,
        37,  38,  0,   39,   0,   40,  0,   0,   0,   0,   349,  41,  0,   0,   0,   0,   0,   0,
        0,   0,   0,   42,   95,  0,   0,   0,   0,   0,   0,    0,   43,  44,  45,  46,  47,  48,
        6,   28,  5,   29,   30,  0,   0,   0,   31,  0,   0,    0,   0,   0,   0,   32,  0,   0,
        33,  34,  35,  0,    0,   0,   0,   36,  37,  38,  0,    39,  0,   40,  0,   0,   0,   0,
        0,   41,  0,   0,    0,   96,  0,   0,   0,   0,   0,    42,  98,  0,   0,   0,   0,   0,
        0,   0,   43,  44,   45,  46,  47,  48,  6,   28,  5,    29,  30,  0,   0,   0,   31,  0,
        0,   0,   0,   0,    0,   32,  0,   0,   33,  34,  35,   0,   0,   0,   0,   36,  37,  38,
        0,   39,  0,   40,   99,  0,   0,   0,   0,   41,  0,    0,   0,   0,   0,   0,   0,   0,
        0,   42,  176, 0,    0,   0,   0,   0,   0,   0,   43,   44,  45,  46,  47,  48,  6,   28,
        5,   29,  30,  0,    0,   0,   31,  0,   0,   0,   0,    0,   0,   32,  0,   0,   33,  34,
        35,  0,   0,   0,    281, 36,  37,  38,  0,   39,  177,  40,  0,   0,   229, 0,   230, 41,
        231, 232, 5,   233,  234, 235, 0,   236, 237, 42,  0,    238, 0,   0,   0,   0,   0,   0,
        43,  44,  45,  46,   47,  48,  6,   0,   0,   291, 0,    239, 0,   0,   0,   240, 0,   0,
        0,   229, 0,   230,  0,   231, 232, 5,   233, 234, 235,  42,  236, 237, 0,   0,   238, 0,
        241, 0,   0,   0,    0,   0,   0,   293, 6,   0,   0,    0,   0,   0,   0,   0,   239, 229,
        0,   230, 240, 231,  232, 5,   233, 234, 235, 0,   236,  237, 0,   0,   238, 0,   42,  0,
        0,   0,   0,   0,    0,   241, 0,   0,   0,   0,   0,    0,   0,   6,   239, 229, 313, 230,
        240, 231, 232, 5,    233, 234, 235, 0,   236, 237, 0,    0,   238, 0,   42,  0,   0,   0,
        0,   0,   0,   241,  0,   0,   0,   0,   0,   0,   0,    6,   239, 229, 0,   230, 240, 231,
        232, 5,   233, 234,  235, 0,   236, 237, 109, 110, 238,  0,   42,  0,   0,   0,   0,   0,
        0,   241, 0,   112,  113, 114, 115, 116, 117, 6,   239,  0,   0,   0,   240, 323, 120, 121,
        229, 0,   230, 0,    231, 232, 5,   233, 234, 235, 42,   236, 237, 0,   0,   238, 0,   241,
        0,   0,   0,   0,    0,   0,   0,   6,   0,   0,   0,    0,   0,   0,   0,   239, 229, 0,
        230, 240, 231, 232,  5,   233, 234, 235, 0,   236, 237,  0,   0,   238, 0,   42,  0,   0,
        0,   0,   0,   0,    241, 325, 0,   0,   0,   0,   0,    0,   6,   239, 0,   0,   0,   240,
        0,   0,   0,   0,    0,   28,  5,   29,  30,  0,   0,    0,   31,  42,  0,   0,   0,   348,
        0,   32,  241, 0,    33,  34,  35,  0,   0,   0,   6,    36,  37,  38,  0,   39,  0,   40,
        0,   0,   363, 0,    349, 41,  0,   0,   0,   0,   0,    0,   0,   0,   0,   42,  0,   0,
        0,   0,   0,   0,    0,   0,   43,  44,  45,  46,  47,   48,  6,   28,  5,   29,  30,  0,
        0,   0,   31,  0,    0,   0,   0,   0,   0,   32,  0,    0,   33,  34,  35,  0,   0,   0,
        0,   36,  37,  38,   0,   39,  0,   40,  0,   0,   0,    0,   0,   41,  0,   0,   0,   0,
        0,   0,   0,   0,    0,   42,  0,   0,   0,   0,   0,    0,   0,   0,   43,  44,  45,  46,
        47,  48,  6,   28,   5,   29,  30,  0,   0,   0,   31,   0,   0,   0,   0,   0,   0,   32,
        0,   0,   33,  34,   35,  0,   0,   0,   0,   36,  37,   38,  0,   127, 0,   40,  0,   0,
        0,   0,   0,   41,   0,   0,   0,   0,   0,   0,   0,    0,   0,   42,  260, 0,   0,   0,
        0,   0,   0,   0,    43,  44,  45,  46,  47,  48,  6,    104, 0,   0,   0,   105, 106, 107,
        108, 0,   109, 110,  111, 0,   0,   0,   0,   0,   0,    342, 0,   0,   0,   112, 113, 114,
        115, 116, 117, 0,    0,   0,   0,   118, 104, 119, 120,  121, 105, 106, 107, 108, 0,   109,
        110, 111, 0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   112, 113, 114, 115, 116, 117,
        343, 0,   0,   0,    118, 0,   119, 120, 121, 0,   344,  104, 0,   0,   0,   105, 106, 107,
        108, 0,   109, 110,  111, 0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   112, 113, 114,
        115, 116, 117, 262,  0,   0,   0,   118, 0,   119, 120,  121, 0,   0,   104, 0,   0,   0,
        105, 106, 107, 108,  0,   109, 110, 111, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,
        112, 113, 114, 115,  116, 117, 345, 0,   0,   0,   118,  0,   119, 120, 121, 0,   0,   104,
        0,   0,   0,   105,  106, 107, 108, 0,   109, 110, 111,  0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   112,  113, 114, 115, 116, 117, 368, 0,    0,   0,   118, 0,   119, 120, 121,
        0,   0,   104, 0,    0,   0,   105, 106, 107, 108, 0,    109, 110, 111, 0,   0,   0,   0,
        0,   0,   0,   0,    0,   0,   112, 113, 114, 115, 116,  117, 0,   144, 0,   0,   118, 0,
        119, 120, 121, 104,  0,   0,   0,   105, 106, 107, 108,  0,   109, 110, 111, 0,   0,   0,
        0,   0,   0,   0,    0,   0,   0,   112, 113, 114, 115,  116, 117, 0,   320, 0,   0,   118,
        0,   119, 120, 121,  104, 0,   0,   0,   105, 106, 107,  108, 0,   109, 110, 111, 0,   0,
        0,   0,   0,   0,    0,   0,   0,   0,   112, 113, 114,  115, 116, 117, 0,   0,   263, 0,
        118, 0,   119, 120,  121, 104, 0,   0,   0,   105, 106,  107, 108, 0,   109, 110, 111, 0,
        0,   0,   0,   0,    0,   0,   0,   0,   0,   112, 113,  114, 115, 116, 117, 321, 0,   0,
        0,   118, 104, 119,  120, 121, 105, 106, 107, 108, 0,    109, 110, 111, 0,   0,   0,   0,
        0,   0,   0,   0,    0,   0,   112, 113, 114, 115, 116,  117, 0,   0,   261, 0,   118, 104,
        119, 120, 121, 105,  106, 107, 108, 0,   109, 110, 111,  0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   112,  113, 114, 115, 116, 117, 0,   0,    0,   0,   118, 0,   119, 120, 121,
        264, 104, 0,   0,    0,   105, 106, 107, 108, 0,   109,  110, 111, 0,   0,   0,   0,   0,
        0,   0,   0,   0,    0,   112, 113, 114, 115, 116, 117,  0,   0,   0,   0,   118, 104, 119,
        120, 121, 105, 106,  107, 108, 0,   109, 110, 111, 0,    148, 0,   0,   0,   0,   0,   0,
        0,   0,   112, 113,  114, 115, 116, 117, 0,   0,   0,    0,   118, 104, 119, 120, 121, 105,
        106, 107, 108, 0,    109, 110, 111, 0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   112,
        113, 114, 115, 116,  117, 0,   152, 0,   0,   118, 104,  119, 120, 121, 105, 106, 107, 108,
        0,   109, 110, 111,  0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   112, 113, 114, 115,
        116, 117, 0,   0,    0,   183, 118, 104, 119, 120, 121,  105, 106, 107, 108, 0,   109, 110,
        111, 0,   208, 0,    0,   0,   0,   0,   0,   0,   0,    112, 113, 114, 115, 116, 117, 0,
        0,   0,   0,   118,  104, 119, 120, 121, 105, 106, 107,  108, 0,   109, 110, 111, 0,   0,
        0,   266, 0,   0,    0,   0,   0,   0,   112, 113, 114,  115, 116, 117, 0,   0,   0,   0,
        118, 104, 119, 120,  121, 105, 106, 107, 108, 0,   109,  110, 111, 0,   307, 0,   0,   0,
        0,   0,   0,   0,    0,   112, 113, 114, 115, 116, 117,  0,   0,   0,   0,   118, 104, 119,
        120, 121, 105, 106,  107, 108, 0,   109, 110, 111, 0,    0,   0,   0,   0,   0,   365, 0,
        0,   0,   112, 113,  114, 115, 116, 117, 0,   0,   0,    0,   118, 104, 119, 120, 121, 105,
        106, 107, 108, 0,    109, 110, 111, 0,   0,   0,   0,    0,   366, 0,   0,   0,   0,   112,
        113, 114, 115, 116,  117, 0,   0,   0,   0,   118, 104,  119, 120, 121, 105, 106, 107, 108,
        0,   109, 110, 111,  0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   112, 113, 114, 115,
        116, 117, 0,   0,    0,   0,   118, 0,   119, 120, 121,  105, 106, 107, 0,   0,   109, 110,
        111, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,    112, 113, 114, 115, 116, 117, 0,
        0,   0,   0,   0,    0,   119, 120, 121, 105, 0,   107,  0,   0,   109, 110, 111, 0,   0,
        0,   0,   0,   0,    0,   0,   0,   0,   112, 113, 114,  115, 116, 117, 0,   0,   0,   0,
        105, 0,   119, 120,  121, 109, 110, 111, 0,   0,   0,    109, 110, 111, 0,   0,   0,   0,
        112, 113, 114, 115,  116, 117, 112, 113, 114, 115, 116,  117, 119, 120, 121, 0,   0,   0,
        119, 120, 121
    };

    const short int Parser::yycheck_[] = {
        7,   14,  3,   1,   19,  44,  1,   133, 29,  30,  45,  32,  17,  17,  17,  17,  43,  47,
        53,  17,  0,   17,  17,  53,  31,  17,  45,  230, 41,  36,  37,  38,  39,  40,  53,  47,
        63,  240, 241, 56,  44,  53,  62,  48,  46,  46,  63,  47,  46,  3,   2,   46,  17,  53,
        46,  54,  47,  62,  62,  62,  43,  60,  53,  15,  16,  17,  18,  19,  83,  53,  44,  55,
        77,  77,  77,  77,  28,  29,  30,  77,  32,  77,  77,  137, 50,  77,  140, 47,  47,  96,
        42,  104, 50,  53,  53,  43,  222, 17,  105, 106, 107, 108, 109, 110, 111, 112, 113, 114,
        115, 116, 117, 118, 119, 120, 121, 122, 122, 17,  47,  49,  127, 127, 74,  53,  137, 63,
        45,  140, 53,  63,  48,  83,  49,  59,  141, 142, 143, 144, 145, 193, 45,  53,  196, 45,
        151, 152, 272, 1,   56,  63,  4,   5,   6,   7,   8,   43,  11,  211, 13,  14,  15,  16,
        17,  18,  19,  20,  56,  22,  23,  41,  42,  26,  124, 188, 65,  43,  183, 184, 63,  12,
        193, 133, 14,  196, 56,  57,  58,  59,  17,  44,  43,  17,  46,  48,  56,  57,  58,  59,
        211, 49,  70,  10,  48,  257, 258, 212, 48,  62,  215, 9,   225, 232, 233, 234, 69,  55,
        50,  25,  48,  0,   1,   49,  77,  4,   5,   6,   7,   8,   50,  49,  237, 238, 20,  277,
        138, 351, 188, 208, 211, 195, 79,  185, 194, 354, 257, 258, 201, 222, -1,  201, 304, 74,
        306, 260, 261, 262, 263, 264, -1,  -1,  195, -1,  -1,  -1,  -1,  46,  -1,  274, 195, -1,
        222, -1,  -1,  225, 4,   5,   6,   7,   8,   235, 232, 233, 234, -1,  -1,  -1,  -1,  -1,
        295, -1,  -1,  304, -1,  306, 229, 230, -1,  -1,  -1,  -1,  235, 236, 229, 230, -1,  240,
        241, -1,  235, 236, 317, 318, 319, 240, 241, -1,  -1,  -1,  -1,  -1,  272, -1,  -1,  -1,
        280, 277, 282, -1,  -1,  -1,  337, 338, -1,  -1,  -1,  -1,  292, 344, 294, -1,  296, -1,
        -1,  -1,  351, 280, -1,  282, -1,  -1,  -1,  -1,  -1,  280, -1,  282, 1,   292, 310, 294,
        -1,  296, -1,  -1,  320, 292, 11,  294, 13,  296, 15,  16,  17,  18,  19,  20,  -1,  22,
        23,  -1,  -1,  26,  -1,  -1,  -1,  320, 342, 343, -1,  345, 346, -1,  -1,  320, -1,  -1,
        -1,  -1,  -1,  44,  -1,  -1,  -1,  48,  -1,  361, 362, 342, 343, 365, 345, 346, 368, -1,
        -1,  342, 343, 62,  345, 346, -1,  -1,  -1,  -1,  69,  -1,  361, 362, 1,   -1,  365, -1,
        77,  368, 361, 362, -1,  -1,  365, -1,  -1,  368, -1,  16,  17,  18,  19,  -1,  -1,  -1,
        23,  -1,  -1,  -1,  -1,  28,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,
        41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,  51,  52,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  62,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,
        77,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,
        33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,
        -1,  52,  -1,  -1,  -1,  56,  -1,  -1,  -1,  -1,  -1,  62,  1,   -1,  -1,  -1,  -1,  -1,
        -1,  -1,  71,  72,  73,  74,  75,  76,  77,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,
        -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,
        -1,  44,  -1,  46,  47,  -1,  -1,  -1,  -1,  52,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  62,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,  77,  16,
        17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,
        35,  -1,  -1,  -1,  1,   40,  41,  42,  -1,  44,  45,  46,  -1,  -1,  11,  -1,  13,  52,
        15,  16,  17,  18,  19,  20,  -1,  22,  23,  62,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,
        71,  72,  73,  74,  75,  76,  77,  -1,  -1,  1,   -1,  44,  -1,  -1,  -1,  48,  -1,  -1,
        -1,  11,  -1,  13,  -1,  15,  16,  17,  18,  19,  20,  62,  22,  23,  -1,  -1,  26,  -1,
        69,  -1,  -1,  -1,  -1,  -1,  -1,  1,   77,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,  11,
        -1,  13,  48,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  62,  -1,
        -1,  -1,  -1,  -1,  -1,  69,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  77,  44,  11,  12,  13,
        48,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  62,  -1,  -1,  -1,
        -1,  -1,  -1,  69,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  77,  44,  11,  -1,  13,  48,  15,
        16,  17,  18,  19,  20,  -1,  22,  23,  41,  42,  26,  -1,  62,  -1,  -1,  -1,  -1,  -1,
        -1,  69,  -1,  54,  55,  56,  57,  58,  59,  77,  44,  -1,  -1,  -1,  48,  49,  67,  68,
        11,  -1,  13,  -1,  15,  16,  17,  18,  19,  20,  62,  22,  23,  -1,  -1,  26,  -1,  69,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  77,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,  11,  -1,
        13,  48,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  62,  -1,  -1,
        -1,  -1,  -1,  -1,  69,  70,  -1,  -1,  -1,  -1,  -1,  -1,  77,  44,  -1,  -1,  -1,  48,
        -1,  -1,  -1,  -1,  -1,  16,  17,  18,  19,  -1,  -1,  -1,  23,  62,  -1,  -1,  -1,  28,
        -1,  30,  69,  -1,  33,  34,  35,  -1,  -1,  -1,  77,  40,  41,  42,  -1,  44,  -1,  46,
        -1,  -1,  49,  -1,  51,  52,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  62,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,  77,  16,  17,  18,  19,  -1,
        -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,
        -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  52,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  62,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,
        75,  76,  77,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,
        -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,
        -1,  -1,  -1,  52,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  62,  17,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,  77,  32,  -1,  -1,  -1,  36,  37,  38,
        39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  17,  -1,  -1,  -1,  54,  55,  56,
        57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,
        42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,
        21,  -1,  -1,  -1,  64,  -1,  66,  67,  68,  -1,  31,  32,  -1,  -1,  -1,  36,  37,  38,
        39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,
        57,  58,  59,  21,  -1,  -1,  -1,  64,  -1,  66,  67,  68,  -1,  -1,  32,  -1,  -1,  -1,
        36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        54,  55,  56,  57,  58,  59,  21,  -1,  -1,  -1,  64,  -1,  66,  67,  68,  -1,  -1,  32,
        -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  21,  -1,  -1,  -1,  64,  -1,  66,  67,  68,
        -1,  -1,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  24,  -1,  -1,  64,  -1,
        66,  67,  68,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  24,  -1,  -1,  64,
        -1,  66,  67,  68,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  25,  -1,
        64,  -1,  66,  67,  68,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  27,  -1,  -1,
        -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  29,  -1,  64,  32,
        66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  -1,  66,  67,  68,
        31,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,  66,
        67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,  66,  67,  68,  36,
        37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,
        55,  56,  57,  58,  59,  -1,  61,  -1,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,
        -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,
        58,  59,  -1,  -1,  -1,  63,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,
        43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,
        -1,  -1,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,
        -1,  47,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,
        64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,  66,
        67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  50,  -1,
        -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,  66,  67,  68,  36,
        37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  49,  -1,  -1,  -1,  -1,  54,
        55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,
        -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,
        58,  59,  -1,  -1,  -1,  -1,  64,  -1,  66,  67,  68,  36,  37,  38,  -1,  -1,  41,  42,
        43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,
        -1,  -1,  -1,  -1,  -1,  66,  67,  68,  36,  -1,  38,  -1,  -1,  41,  42,  43,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  -1,  -1,
        36,  -1,  66,  67,  68,  41,  42,  43,  -1,  -1,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,
        54,  55,  56,  57,  58,  59,  54,  55,  56,  57,  58,  59,  66,  67,  68,  -1,  -1,  -1,
        66,  67,  68
    };

    const unsigned char Parser::yystos_[] = {
        0,   3,   46,  83,  84,  17,  77,  149, 156, 157, 158, 159, 0,   1,   4,   5,   6,   7,
        8,   46,  85,  86,  87,  88,  89,  90,  91,  92,  16,  18,  19,  23,  30,  33,  34,  35,
        40,  41,  42,  44,  46,  52,  62,  71,  72,  73,  74,  75,  76,  111, 112, 113, 114, 115,
        116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 149, 150,
        151, 47,  53,  48,  150, 149, 149, 149, 149, 156, 86,  46,  149, 152, 153, 154, 154, 154,
        111, 154, 111, 111, 111, 1,   56,  111, 1,   47,  110, 111, 150, 149, 32,  36,  37,  38,
        39,  41,  42,  43,  54,  55,  56,  57,  58,  59,  64,  66,  67,  68,  44,  138, 62,  3,
        157, 44,  111, 139, 146, 147, 148, 44,  143, 43,  143, 50,  47,  156, 50,  43,  17,  17,
        24,  17,  45,  111, 45,  47,  47,  53,  61,  133, 134, 135, 136, 137, 150, 111, 111, 111,
        111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 1,   45,  110, 111,
        149, 110, 111, 63,  63,  53,  49,  1,   46,  142, 149, 153, 155, 63,  48,  43,  63,  133,
        140, 141, 87,  47,  133, 111, 111, 111, 111, 111, 45,  111, 111, 54,  60,  45,  45,  53,
        111, 111, 147, 45,  156, 45,  53,  133, 1,   46,  93,  94,  149, 11,  13,  15,  16,  18,
        19,  20,  22,  23,  26,  44,  48,  69,  95,  97,  98,  99,  102, 103, 104, 105, 106, 107,
        108, 109, 114, 115, 133, 56,  63,  152, 17,  29,  21,  25,  31,  138, 47,  132, 133, 141,
        111, 111, 47,  155, 43,  156, 49,  53,  1,   95,  96,  1,   96,  154, 154, 154, 95,  114,
        115, 111, 111, 1,   96,  1,   96,  65,  43,  133, 133, 111, 111, 111, 111, 111, 53,  55,
        63,  45,  153, 111, 47,  93,  12,  12,  95,  14,  14,  43,  17,  17,  24,  27,  49,  49,
        70,  70,  111, 95,  10,  144, 133, 133, 149, 111, 111, 111, 95,  48,  48,  9,   145, 55,
        17,  21,  31,  21,  25,  1,   28,  51,  100, 101, 111, 111, 48,  95,  95,  111, 95,  95,
        49,  50,  50,  49,  100, 50,  49,  148, 21,  95,  95,  95,  49,  95
    };

    const unsigned char Parser::yyr1_[] = {
        0,   82,  83,  84,  84,  85,  85,  86,  86,  86,  87,  87,  87,  87,  88,  89,  90,  90,
        91,  91,  92,  92,  93,  93,  93,  94,  94,  95,  95,  95,  95,  95,  95,  95,  95,  95,
        95,  95,  96,  96,  97,  98,  98,  99,  99,  100, 100, 100, 101, 101, 102, 103, 103, 104,
        105, 106, 106, 106, 106, 107, 107, 107, 107, 108, 109, 109, 109, 109, 110, 110, 111, 111,
        111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 112, 112, 112, 112, 112, 112, 112, 112,
        112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 113, 114, 114, 115,
        116, 117, 118, 119, 120, 121, 121, 121, 122, 123, 123, 123, 123, 123, 123, 123, 123, 124,
        125, 125, 126, 127, 128, 129, 129, 130, 131, 132, 132, 133, 133, 133, 133, 134, 135, 136,
        137, 138, 138, 138, 139, 140, 140, 141, 141, 142, 142, 143, 143, 143, 144, 144, 145, 145,
        146, 146, 147, 147, 147, 148, 148, 149, 149, 150, 150, 151, 151, 152, 152, 153, 154, 154,
        155, 155, 156, 156, 157, 157, 158, 159
    };

    const unsigned char Parser::yyr2_[] = {
        0, 2, 2, 4, 1, 2, 1, 4, 1, 1, 1, 1, 1, 1, 6, 7, 5, 7, 8, 1, 2, 4, 1, 4, 1, 3, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 4, 6, 6, 6, 3, 3, 3, 2, 1, 6, 6, 8, 6,
        2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 3, 3, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 1, 2, 5,
        6, 6, 6, 6, 6, 2, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        3, 1, 1, 1, 1, 1, 1, 4, 6, 3, 3, 3, 2, 5, 3, 1, 1, 0, 3, 1, 3, 3, 0, 4, 0, 4, 0,
        3, 1, 1, 3, 3, 1, 0, 1, 1, 1, 2, 3, 1, 1, 1, 3, 4, 1, 4, 1, 3, 1, 1, 1, 1, 2
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
                                             "DirectCallExpression",
                                             "IndirectCallExpression",
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
        0,    379,  379,  388,  394,  402,  408,  418,  424,  428,  436,  440,  444,  448,  456,
        464,  472,  477,  486,  502,  510,  533,  551,  555,  561,  569,  575,  589,  593,  597,
        601,  605,  609,  613,  617,  621,  625,  629,  637,  643,  653,  661,  665,  673,  677,
        685,  689,  693,  701,  707,  717,  725,  729,  737,  745,  753,  757,  761,  766,  775,
        779,  783,  788,  797,  807,  811,  815,  819,  831,  837,  847,  851,  855,  859,  863,
        867,  871,  875,  879,  883,  887,  891,  903,  907,  911,  915,  919,  923,  927,  931,
        935,  939,  943,  947,  951,  955,  959,  963,  967,  971,  975,  979,  983,  987,  995,
        1003, 1008, 1016, 1024, 1032, 1040, 1048, 1056, 1064, 1069, 1073, 1081, 1093, 1097, 1101,
        1105, 1109, 1113, 1117, 1121, 1129, 1137, 1142, 1151, 1167, 1183, 1199, 1211, 1227, 1243,
        1255, 1261, 1271, 1275, 1279, 1283, 1291, 1299, 1307, 1315, 1327, 1331, 1335, 1344, 1358,
        1364, 1374, 1378, 1386, 1392, 1402, 1406, 1410, 1422, 1426, 1434, 1438, 1446, 1452, 1462,
        1470, 1480, 1491, 1495, 1507, 1511, 1519, 1523, 1533, 1539, 1553, 1557, 1566, 1574, 1580,
        1588, 1594, 1606, 1612, 1621, 1625, 1633, 1641
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
#line 3983 "GrammarParser.cpp"               // lalr1.cc:1167
#line 1647 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1168

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
