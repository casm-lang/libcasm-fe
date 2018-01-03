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
            case 162:  // Attribute
                value.move< Attribute::Ptr >( that.value );
                break;

            case 161:  // Attributes
                value.move< Attributes::Ptr >( that.value );
                break;

            case 163:  // BasicAttribute
                value.move< BasicAttribute::Ptr >( that.value );
                break;

            case 139:  // BasicType
                value.move< BasicType::Ptr >( that.value );
                break;

            case 109:  // BlockRule
                value.move< BlockRule::Ptr >( that.value );
                break;

            case 112:  // CallRule
                value.move< CallRule::Ptr >( that.value );
                break;

            case 103:  // CaseLabel
                value.move< Case::Ptr >( that.value );
                break;

            case 102:  // CaseRule
                value.move< CaseRule::Ptr >( that.value );
                break;

            case 104:  // CaseLabels
                value.move< Cases::Ptr >( that.value );
                break;

            case 123:  // ChooseExpression
                value.move< ChooseExpression::Ptr >( that.value );
                break;

            case 107:  // ChooseRule
                value.move< ChooseRule::Ptr >( that.value );
                break;

            case 140:  // ComposedType
                value.move< ComposedType::Ptr >( that.value );
                break;

            case 122:  // ConditionalExpression
                value.move< ConditionalExpression::Ptr >( that.value );
                break;

            case 101:  // ConditionalRule
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

            case 125:  // ExistentialQuantifierExpression
                value.move< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 114:  // Term
            case 115:  // SimpleOrClaspedTerm
            case 116:  // OperatorExpression
            case 126:  // Literal
            case 149:  // MaybeDefined
                value.move< Expression::Ptr >( that.value );
                break;

            case 164:  // ExpressionAttribute
                value.move< ExpressionAttribute::Ptr >( that.value );
                break;

            case 113:  // Terms
            case 143:  // Arguments
            case 144:  // TwoOrMoreArguments
                value.move< Expressions::Ptr >( that.value );
                break;

            case 142:  // FixedSizedType
                value.move< FixedSizedType::Ptr >( that.value );
                break;

            case 106:  // ForallRule
                value.move< ForallRule::Ptr >( that.value );
                break;

            case 93:  // FunctionDefinition
            case 94:  // ProgramFunctionDefinition
                value.move< FunctionDefinition::Ptr >( that.value );
                break;

            case 86:  // Header
                value.move< HeaderDefinition::Ptr >( that.value );
                break;

            case 154:  // Identifier
                value.move< Identifier::Ptr >( that.value );
                break;

            case 155:  // IdentifierPath
                value.move< IdentifierPath::Ptr >( that.value );
                break;

            case 156:  // DotSeparatedIdentifiers
                value.move< Identifiers::Ptr >( that.value );
                break;

            case 119:  // IndirectCallExpression
                value.move< IndirectCallExpression::Ptr >( that.value );
                break;

            case 108:  // IterateRule
                value.move< IterateRule::Ptr >( that.value );
                break;

            case 121:  // LetExpression
                value.move< LetExpression::Ptr >( that.value );
                break;

            case 105:  // LetRule
                value.move< LetRule::Ptr >( that.value );
                break;

            case 135:  // ListLiteral
                value.move< ListLiteral::Ptr >( that.value );
                break;

            case 118:  // MethodCallExpression
                value.move< MethodCallExpression::Ptr >( that.value );
                break;

            case 150:  // MaybeInitially
            case 151:  // Initializers
            case 153:  // MaybeInitializers
                value.move< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 147:  // Parameters
            case 148:  // MaybeParameters
                value.move< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 136:  // RangeLiteral
                value.move< RangeLiteral::Ptr >( that.value );
                break;

            case 134:  // ReferenceLiteral
                value.move< ReferenceLiteral::Ptr >( that.value );
                break;

            case 141:  // RelationType
                value.move< RelationType::Ptr >( that.value );
                break;

            case 98:  // Rule
                value.move< Rule::Ptr >( that.value );
                break;

            case 92:  // RuleDefinition
                value.move< RuleDefinition::Ptr >( that.value );
                break;

            case 99:  // Rules
                value.move< Rules::Ptr >( that.value );
                break;

            case 110:  // SequenceRule
                value.move< SequenceRule::Ptr >( that.value );
                break;

            case 100:  // SkipRule
                value.move< SkipRule::Ptr >( that.value );
                break;

            case 85:  // Specification
                value.move< Specification::Ptr >( that.value );
                break;

            case 120:  // TypeCastingExpression
                value.move< TypeCastingExpression::Ptr >( that.value );
                break;

            case 137:  // Types
            case 145:  // FunctionParameters
            case 146:  // MaybeFunctionParameters
                value.move< Types::Ptr >( that.value );
                break;

            case 127:  // UndefinedLiteral
                value.move< UndefLiteral::Ptr >( that.value );
                break;

            case 124:  // UniversalQuantifierExpression
                value.move< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // UpdateRule
            case 152:  // Initializer
                value.move< UpdateRule::Ptr >( that.value );
                break;

            case 97:  // UsingDefinition
                value.move< UsingDefinition::Ptr >( that.value );
                break;

            case 128:  // BooleanLiteral
            case 129:  // IntegerLiteral
            case 130:  // RationalLiteral
            case 131:  // DecimalLiteral
            case 132:  // BinaryLiteral
            case 133:  // StringLiteral
                value.move< ValueLiteral::Ptr >( that.value );
                break;

            case 157:  // Variable
            case 158:  // TypedVariable
            case 159:  // AttributedVariable
            case 160:  // TypedAttributedVariable
                value.move< VariableDefinition::Ptr >( that.value );
                break;

            case 138:  // Type
                value.move< libcasm_fe::Ast::Type::Ptr >( that.value );
                break;

            case 73:  // "binary"
            case 74:  // "hexadecimal"
            case 75:  // "integer"
            case 76:  // "rational"
            case 77:  // "decimal"
            case 78:  // "string"
            case 79:  // "identifier"
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
            case 162:  // Attribute
                value.copy< Attribute::Ptr >( that.value );
                break;

            case 161:  // Attributes
                value.copy< Attributes::Ptr >( that.value );
                break;

            case 163:  // BasicAttribute
                value.copy< BasicAttribute::Ptr >( that.value );
                break;

            case 139:  // BasicType
                value.copy< BasicType::Ptr >( that.value );
                break;

            case 109:  // BlockRule
                value.copy< BlockRule::Ptr >( that.value );
                break;

            case 112:  // CallRule
                value.copy< CallRule::Ptr >( that.value );
                break;

            case 103:  // CaseLabel
                value.copy< Case::Ptr >( that.value );
                break;

            case 102:  // CaseRule
                value.copy< CaseRule::Ptr >( that.value );
                break;

            case 104:  // CaseLabels
                value.copy< Cases::Ptr >( that.value );
                break;

            case 123:  // ChooseExpression
                value.copy< ChooseExpression::Ptr >( that.value );
                break;

            case 107:  // ChooseRule
                value.copy< ChooseRule::Ptr >( that.value );
                break;

            case 140:  // ComposedType
                value.copy< ComposedType::Ptr >( that.value );
                break;

            case 122:  // ConditionalExpression
                value.copy< ConditionalExpression::Ptr >( that.value );
                break;

            case 101:  // ConditionalRule
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

            case 125:  // ExistentialQuantifierExpression
                value.copy< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 114:  // Term
            case 115:  // SimpleOrClaspedTerm
            case 116:  // OperatorExpression
            case 126:  // Literal
            case 149:  // MaybeDefined
                value.copy< Expression::Ptr >( that.value );
                break;

            case 164:  // ExpressionAttribute
                value.copy< ExpressionAttribute::Ptr >( that.value );
                break;

            case 113:  // Terms
            case 143:  // Arguments
            case 144:  // TwoOrMoreArguments
                value.copy< Expressions::Ptr >( that.value );
                break;

            case 142:  // FixedSizedType
                value.copy< FixedSizedType::Ptr >( that.value );
                break;

            case 106:  // ForallRule
                value.copy< ForallRule::Ptr >( that.value );
                break;

            case 93:  // FunctionDefinition
            case 94:  // ProgramFunctionDefinition
                value.copy< FunctionDefinition::Ptr >( that.value );
                break;

            case 86:  // Header
                value.copy< HeaderDefinition::Ptr >( that.value );
                break;

            case 154:  // Identifier
                value.copy< Identifier::Ptr >( that.value );
                break;

            case 155:  // IdentifierPath
                value.copy< IdentifierPath::Ptr >( that.value );
                break;

            case 156:  // DotSeparatedIdentifiers
                value.copy< Identifiers::Ptr >( that.value );
                break;

            case 119:  // IndirectCallExpression
                value.copy< IndirectCallExpression::Ptr >( that.value );
                break;

            case 108:  // IterateRule
                value.copy< IterateRule::Ptr >( that.value );
                break;

            case 121:  // LetExpression
                value.copy< LetExpression::Ptr >( that.value );
                break;

            case 105:  // LetRule
                value.copy< LetRule::Ptr >( that.value );
                break;

            case 135:  // ListLiteral
                value.copy< ListLiteral::Ptr >( that.value );
                break;

            case 118:  // MethodCallExpression
                value.copy< MethodCallExpression::Ptr >( that.value );
                break;

            case 150:  // MaybeInitially
            case 151:  // Initializers
            case 153:  // MaybeInitializers
                value.copy< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 147:  // Parameters
            case 148:  // MaybeParameters
                value.copy< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 136:  // RangeLiteral
                value.copy< RangeLiteral::Ptr >( that.value );
                break;

            case 134:  // ReferenceLiteral
                value.copy< ReferenceLiteral::Ptr >( that.value );
                break;

            case 141:  // RelationType
                value.copy< RelationType::Ptr >( that.value );
                break;

            case 98:  // Rule
                value.copy< Rule::Ptr >( that.value );
                break;

            case 92:  // RuleDefinition
                value.copy< RuleDefinition::Ptr >( that.value );
                break;

            case 99:  // Rules
                value.copy< Rules::Ptr >( that.value );
                break;

            case 110:  // SequenceRule
                value.copy< SequenceRule::Ptr >( that.value );
                break;

            case 100:  // SkipRule
                value.copy< SkipRule::Ptr >( that.value );
                break;

            case 85:  // Specification
                value.copy< Specification::Ptr >( that.value );
                break;

            case 120:  // TypeCastingExpression
                value.copy< TypeCastingExpression::Ptr >( that.value );
                break;

            case 137:  // Types
            case 145:  // FunctionParameters
            case 146:  // MaybeFunctionParameters
                value.copy< Types::Ptr >( that.value );
                break;

            case 127:  // UndefinedLiteral
                value.copy< UndefLiteral::Ptr >( that.value );
                break;

            case 124:  // UniversalQuantifierExpression
                value.copy< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // UpdateRule
            case 152:  // Initializer
                value.copy< UpdateRule::Ptr >( that.value );
                break;

            case 97:  // UsingDefinition
                value.copy< UsingDefinition::Ptr >( that.value );
                break;

            case 128:  // BooleanLiteral
            case 129:  // IntegerLiteral
            case 130:  // RationalLiteral
            case 131:  // DecimalLiteral
            case 132:  // BinaryLiteral
            case 133:  // StringLiteral
                value.copy< ValueLiteral::Ptr >( that.value );
                break;

            case 157:  // Variable
            case 158:  // TypedVariable
            case 159:  // AttributedVariable
            case 160:  // TypedAttributedVariable
                value.copy< VariableDefinition::Ptr >( that.value );
                break;

            case 138:  // Type
                value.copy< libcasm_fe::Ast::Type::Ptr >( that.value );
                break;

            case 73:  // "binary"
            case 74:  // "hexadecimal"
            case 75:  // "integer"
            case 76:  // "rational"
            case 77:  // "decimal"
            case 78:  // "string"
            case 79:  // "identifier"
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
                    case 162:  // Attribute
                        yylhs.value.build< Attribute::Ptr >();
                        break;

                    case 161:  // Attributes
                        yylhs.value.build< Attributes::Ptr >();
                        break;

                    case 163:  // BasicAttribute
                        yylhs.value.build< BasicAttribute::Ptr >();
                        break;

                    case 139:  // BasicType
                        yylhs.value.build< BasicType::Ptr >();
                        break;

                    case 109:  // BlockRule
                        yylhs.value.build< BlockRule::Ptr >();
                        break;

                    case 112:  // CallRule
                        yylhs.value.build< CallRule::Ptr >();
                        break;

                    case 103:  // CaseLabel
                        yylhs.value.build< Case::Ptr >();
                        break;

                    case 102:  // CaseRule
                        yylhs.value.build< CaseRule::Ptr >();
                        break;

                    case 104:  // CaseLabels
                        yylhs.value.build< Cases::Ptr >();
                        break;

                    case 123:  // ChooseExpression
                        yylhs.value.build< ChooseExpression::Ptr >();
                        break;

                    case 107:  // ChooseRule
                        yylhs.value.build< ChooseRule::Ptr >();
                        break;

                    case 140:  // ComposedType
                        yylhs.value.build< ComposedType::Ptr >();
                        break;

                    case 122:  // ConditionalExpression
                        yylhs.value.build< ConditionalExpression::Ptr >();
                        break;

                    case 101:  // ConditionalRule
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

                    case 125:  // ExistentialQuantifierExpression
                        yylhs.value.build< ExistentialQuantifierExpression::Ptr >();
                        break;

                    case 114:  // Term
                    case 115:  // SimpleOrClaspedTerm
                    case 116:  // OperatorExpression
                    case 126:  // Literal
                    case 149:  // MaybeDefined
                        yylhs.value.build< Expression::Ptr >();
                        break;

                    case 164:  // ExpressionAttribute
                        yylhs.value.build< ExpressionAttribute::Ptr >();
                        break;

                    case 113:  // Terms
                    case 143:  // Arguments
                    case 144:  // TwoOrMoreArguments
                        yylhs.value.build< Expressions::Ptr >();
                        break;

                    case 142:  // FixedSizedType
                        yylhs.value.build< FixedSizedType::Ptr >();
                        break;

                    case 106:  // ForallRule
                        yylhs.value.build< ForallRule::Ptr >();
                        break;

                    case 93:  // FunctionDefinition
                    case 94:  // ProgramFunctionDefinition
                        yylhs.value.build< FunctionDefinition::Ptr >();
                        break;

                    case 86:  // Header
                        yylhs.value.build< HeaderDefinition::Ptr >();
                        break;

                    case 154:  // Identifier
                        yylhs.value.build< Identifier::Ptr >();
                        break;

                    case 155:  // IdentifierPath
                        yylhs.value.build< IdentifierPath::Ptr >();
                        break;

                    case 156:  // DotSeparatedIdentifiers
                        yylhs.value.build< Identifiers::Ptr >();
                        break;

                    case 119:  // IndirectCallExpression
                        yylhs.value.build< IndirectCallExpression::Ptr >();
                        break;

                    case 108:  // IterateRule
                        yylhs.value.build< IterateRule::Ptr >();
                        break;

                    case 121:  // LetExpression
                        yylhs.value.build< LetExpression::Ptr >();
                        break;

                    case 105:  // LetRule
                        yylhs.value.build< LetRule::Ptr >();
                        break;

                    case 135:  // ListLiteral
                        yylhs.value.build< ListLiteral::Ptr >();
                        break;

                    case 118:  // MethodCallExpression
                        yylhs.value.build< MethodCallExpression::Ptr >();
                        break;

                    case 150:  // MaybeInitially
                    case 151:  // Initializers
                    case 153:  // MaybeInitializers
                        yylhs.value.build< NodeList< UpdateRule >::Ptr >();
                        break;

                    case 147:  // Parameters
                    case 148:  // MaybeParameters
                        yylhs.value.build< NodeList< VariableDefinition >::Ptr >();
                        break;

                    case 136:  // RangeLiteral
                        yylhs.value.build< RangeLiteral::Ptr >();
                        break;

                    case 134:  // ReferenceLiteral
                        yylhs.value.build< ReferenceLiteral::Ptr >();
                        break;

                    case 141:  // RelationType
                        yylhs.value.build< RelationType::Ptr >();
                        break;

                    case 98:  // Rule
                        yylhs.value.build< Rule::Ptr >();
                        break;

                    case 92:  // RuleDefinition
                        yylhs.value.build< RuleDefinition::Ptr >();
                        break;

                    case 99:  // Rules
                        yylhs.value.build< Rules::Ptr >();
                        break;

                    case 110:  // SequenceRule
                        yylhs.value.build< SequenceRule::Ptr >();
                        break;

                    case 100:  // SkipRule
                        yylhs.value.build< SkipRule::Ptr >();
                        break;

                    case 85:  // Specification
                        yylhs.value.build< Specification::Ptr >();
                        break;

                    case 120:  // TypeCastingExpression
                        yylhs.value.build< TypeCastingExpression::Ptr >();
                        break;

                    case 137:  // Types
                    case 145:  // FunctionParameters
                    case 146:  // MaybeFunctionParameters
                        yylhs.value.build< Types::Ptr >();
                        break;

                    case 127:  // UndefinedLiteral
                        yylhs.value.build< UndefLiteral::Ptr >();
                        break;

                    case 124:  // UniversalQuantifierExpression
                        yylhs.value.build< UniversalQuantifierExpression::Ptr >();
                        break;

                    case 111:  // UpdateRule
                    case 152:  // Initializer
                        yylhs.value.build< UpdateRule::Ptr >();
                        break;

                    case 97:  // UsingDefinition
                        yylhs.value.build< UsingDefinition::Ptr >();
                        break;

                    case 128:  // BooleanLiteral
                    case 129:  // IntegerLiteral
                    case 130:  // RationalLiteral
                    case 131:  // DecimalLiteral
                    case 132:  // BinaryLiteral
                    case 133:  // StringLiteral
                        yylhs.value.build< ValueLiteral::Ptr >();
                        break;

                    case 157:  // Variable
                    case 158:  // TypedVariable
                    case 159:  // AttributedVariable
                    case 160:  // TypedAttributedVariable
                        yylhs.value.build< VariableDefinition::Ptr >();
                        break;

                    case 138:  // Type
                        yylhs.value.build< libcasm_fe::Ast::Type::Ptr >();
                        break;

                    case 73:  // "binary"
                    case 74:  // "hexadecimal"
                    case 75:  // "integer"
                    case 76:  // "rational"
                    case 77:  // "decimal"
                    case 78:  // "string"
                    case 79:  // "identifier"
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
#line 386 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            specification.setHeader(
                                yystack_[ 1 ].value.as< HeaderDefinition::Ptr >() );
                            specification.setDefinitions(
                                yystack_[ 0 ].value.as< Definitions::Ptr >() );
                        }
#line 1389 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 3:
#line 395 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< HeaderDefinition::Ptr >() = definition;
                        }
#line 1399 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 4:
#line 401 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< HeaderDefinition::Ptr >() =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                        }
#line 1407 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 5:
#line 409 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = yystack_[ 1 ].value.as< Definitions::Ptr >();
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1417 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 6:
#line 415 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = Ast::make< Definitions >( yylhs.location );
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1427 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 7:
#line 425 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition = yystack_[ 0 ].value.as< Definition::Ptr >();
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< Definition::Ptr >() = definition;
                        }
#line 1437 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 8:
#line 431 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< Definition::Ptr >();
                        }
#line 1445 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 9:
#line 435 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() = nullptr;
                        }
#line 1453 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 10:
#line 443 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< EnumerationDefinition::Ptr >();
                        }
#line 1461 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 11:
#line 447 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< DerivedDefinition::Ptr >();
                        }
#line 1469 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 12:
#line 451 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< RuleDefinition::Ptr >();
                        }
#line 1477 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 13:
#line 455 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< FunctionDefinition::Ptr >();
                        }
#line 1485 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 14:
#line 459 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< UsingDefinition::Ptr >();
                        }
#line 1493 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 15:
#line 467 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumerationDefinition::Ptr >() =
                                Ast::make< EnumerationDefinition >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 1 ].value.as< Enumerators::Ptr >() );
                        }
#line 1501 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 16:
#line 475 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DerivedDefinition::Ptr >() =
                                Ast::make< DerivedDefinition >(
                                    yylhs.location,
                                    yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                    yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1509 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 17:
#line 483 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Identifier::Ptr >(),
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                createVoidType( yylhs.location ),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1518 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 18:
#line 488 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1527 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 19:
#line 497 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1547 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 20:
#line 513 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FunctionDefinition::Ptr >() =
                                yystack_[ 0 ]
                                    .value.as< FunctionDefinition::Ptr >();  // `init` special case
                        }
#line 1555 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 21:
#line 521 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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

                            const auto ruleReference = Ast::make< ReferenceLiteral >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );

                            auto initializers =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                            initializers->add(
                                Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
                            programDefinition->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = programDefinition;
                        }
#line 1582 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 22:
#line 544 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1600 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 23:
#line 562 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() =
                                Ast::make< EnumeratorDefinition >(
                                    yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 1608 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 24:
#line 566 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerator = Ast::make< EnumeratorDefinition >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            enumerator->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = enumerator;
                        }
#line 1618 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 25:
#line 572 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = nullptr;
                        }
#line 1626 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 26:
#line 580 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = yystack_[ 2 ].value.as< Enumerators::Ptr >();
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1636 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 27:
#line 586 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = Ast::make< Enumerators >( yylhs.location );
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1646 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 28:
#line 596 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UsingDefinition::Ptr >() = Ast::make< UsingDefinition >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 1654 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 29:
#line 608 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SkipRule::Ptr >();
                        }
#line 1662 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 30:
#line 612 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalRule::Ptr >();
                        }
#line 1670 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 31:
#line 616 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CaseRule::Ptr >();
                        }
#line 1678 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 32:
#line 620 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< LetRule::Ptr >();
                        }
#line 1686 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 33:
#line 624 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ForallRule::Ptr >();
                        }
#line 1694 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 34:
#line 628 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseRule::Ptr >();
                        }
#line 1702 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 35:
#line 632 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< IterateRule::Ptr >();
                        }
#line 1710 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 36:
#line 636 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< BlockRule::Ptr >();
                        }
#line 1718 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 37:
#line 640 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SequenceRule::Ptr >();
                        }
#line 1726 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 38:
#line 644 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRule::Ptr >();
                        }
#line 1734 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 39:
#line 648 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CallRule::Ptr >();
                        }
#line 1742 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 40:
#line 656 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = yystack_[ 1 ].value.as< Rules::Ptr >();
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1752 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 41:
#line 662 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = Ast::make< Rules >( yylhs.location );
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1762 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 42:
#line 672 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SkipRule::Ptr >() =
                                Ast::make< SkipRule >( yylhs.location );
                        }
#line 1770 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 43:
#line 680 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1778 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 44:
#line 684 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Rule::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1786 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 45:
#line 692 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = Ast::make< CaseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Cases::Ptr >() );
                        }
#line 1794 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 46:
#line 696 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = nullptr;
                        }
#line 1802 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 47:
#line 704 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1810 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 48:
#line 708 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1818 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 49:
#line 712 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< ExpressionCase >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1826 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 50:
#line 720 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = yystack_[ 1 ].value.as< Cases::Ptr >();
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1836 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 51:
#line 726 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = Ast::make< Cases >( yylhs.location );
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1846 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 52:
#line 736 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetRule::Ptr >() = Ast::make< LetRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1854 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 53:
#line 744 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1862 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 54:
#line 748 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 6 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1870 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 55:
#line 756 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseRule::Ptr >() = Ast::make< ChooseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1878 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 56:
#line 764 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IterateRule::Ptr >() = Ast::make< IterateRule >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1886 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 57:
#line 772 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1894 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 58:
#line 776 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1902 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 59:
#line 780 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1911 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 60:
#line 785 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1920 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 61:
#line 794 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1928 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 62:
#line 798 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1936 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 63:
#line 802 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1945 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 64:
#line 807 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1954 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 65:
#line 816 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto function =
                                yystack_[ 2 ].value.as< DirectCallExpression::Ptr >();
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1964 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 66:
#line 826 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 1972 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 67:
#line 830 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 1980 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 68:
#line 834 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 1988 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 69:
#line 838 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 1996 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 70:
#line 842 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 2004 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 71:
#line 846 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 2012 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 72:
#line 858 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto expressions = yystack_[ 2 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2022 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 73:
#line 864 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2032 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 74:
#line 874 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2040 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 75:
#line 878 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TypeCastingExpression::Ptr >();
                        }
#line 2048 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 76:
#line 882 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2056 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 77:
#line 886 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LetExpression::Ptr >();
                        }
#line 2064 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 78:
#line 890 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalExpression::Ptr >();
                        }
#line 2072 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 79:
#line 894 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseExpression::Ptr >();
                        }
#line 2080 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 80:
#line 898 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UniversalQuantifierExpression::Ptr >();
                        }
#line 2088 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 81:
#line 902 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ExistentialQuantifierExpression::Ptr >();
                        }
#line 2096 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 82:
#line 910 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2104 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 83:
#line 914 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = nullptr;
                        }
#line 2112 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 84:
#line 918 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >();
                        }
#line 2120 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 85:
#line 922 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >();
                        }
#line 2128 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 86:
#line 926 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >();
                        }
#line 2136 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 87:
#line 930 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2144 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 88:
#line 942 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2152 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 89:
#line 946 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::INV_INSTRUCTION );
                        }
#line 2160 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 90:
#line 950 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::ADD_INSTRUCTION );
                        }
#line 2168 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 91:
#line 954 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::SUB_INSTRUCTION );
                        }
#line 2176 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 92:
#line 958 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MUL_INSTRUCTION );
                        }
#line 2184 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 93:
#line 962 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::DIV_INSTRUCTION );
                        }
#line 2192 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 94:
#line 966 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MOD_INSTRUCTION );
                        }
#line 2200 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 95:
#line 970 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::POW_INSTRUCTION );
                        }
#line 2208 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 96:
#line 974 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NEQ_INSTRUCTION );
                        }
#line 2216 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 97:
#line 978 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::EQU_INSTRUCTION );
                        }
#line 2224 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 98:
#line 982 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LTH_INSTRUCTION );
                        }
#line 2232 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 99:
#line 986 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GTH_INSTRUCTION );
                        }
#line 2240 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 100:
#line 990 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LEQ_INSTRUCTION );
                        }
#line 2248 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 101:
#line 994 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GEQ_INSTRUCTION );
                        }
#line 2256 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 102:
#line 998 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::OR_INSTRUCTION );
                        }
#line 2264 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 103:
#line 1002 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::XOR_INSTRUCTION );
                        }
#line 2272 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 104:
#line 1006 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::AND_INSTRUCTION );
                        }
#line 2280 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 105:
#line 1010 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2288 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 106:
#line 1014 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2296 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 107:
#line 1018 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NOT_INSTRUCTION );
                        }
#line 2304 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 108:
#line 1026 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< IdentifierPath::Ptr >(),
                                    arguments );
                        }
#line 2313 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 109:
#line 1031 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< IdentifierPath::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2321 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 110:
#line 1039 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2330 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 111:
#line 1044 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 3 ].value.as< Expression::Ptr >(),
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2338 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 112:
#line 1052 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IndirectCallExpression::Ptr >() =
                                Ast::make< IndirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2346 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 113:
#line 1060 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TypeCastingExpression::Ptr >() =
                                Ast::make< TypeCastingExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2354 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 114:
#line 1068 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetExpression::Ptr >() = Ast::make< LetExpression >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2362 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 115:
#line 1076 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalExpression::Ptr >() =
                                Ast::make< ConditionalExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Expression::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2370 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 116:
#line 1084 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseExpression::Ptr >() =
                                Ast::make< ChooseExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2378 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 117:
#line 1092 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UniversalQuantifierExpression::Ptr >() =
                                Ast::make< UniversalQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2386 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 118:
#line 1100 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExistentialQuantifierExpression::Ptr >() =
                                Ast::make< ExistentialQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2394 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 119:
#line 1112 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UndefLiteral::Ptr >();
                        }
#line 2402 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 120:
#line 1116 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2410 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 121:
#line 1120 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2418 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 122:
#line 1124 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2426 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 123:
#line 1128 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2434 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 124:
#line 1132 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2442 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 125:
#line 1136 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2450 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 126:
#line 1140 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ReferenceLiteral::Ptr >();
                        }
#line 2458 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 127:
#line 1144 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ListLiteral::Ptr >();
                        }
#line 2466 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 128:
#line 1148 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< RangeLiteral::Ptr >();
                        }
#line 2474 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 129:
#line 1156 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UndefLiteral::Ptr >() =
                                Ast::make< UndefLiteral >( yylhs.location );
                        }
#line 2482 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 130:
#line 1164 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
                            yylhs.value.as< ValueLiteral::Ptr >() =
                                Ast::make< ValueLiteral >( yylhs.location, value );
                        }
#line 2491 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 131:
#line 1169 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
                            yylhs.value.as< ValueLiteral::Ptr >() =
                                Ast::make< ValueLiteral >( yylhs.location, value );
                        }
#line 2500 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 132:
#line 1178 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::IntegerConstant >(
                                        yystack_[ 0 ].value.as< std::string >(),
                                        libstdhl::Type::DECIMAL );
                                yylhs.value.as< ValueLiteral::Ptr >() =
                                    Ast::make< ValueLiteral >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2516 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 133:
#line 1194 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::RationalConstant >(
                                        yystack_[ 0 ].value.as< std::string >() );
                                yylhs.value.as< ValueLiteral::Ptr >() =
                                    Ast::make< ValueLiteral >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2532 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 134:
#line 1210 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::DecimalConstant >(
                                        yystack_[ 0 ].value.as< std::string >() );
                                yylhs.value.as< ValueLiteral::Ptr >() =
                                    Ast::make< ValueLiteral >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2548 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 135:
#line 1226 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::BinaryConstant >(
                                        yystack_[ 0 ].value.as< std::string >(),
                                        libstdhl::Type::BINARY );
                                yylhs.value.as< ValueLiteral::Ptr >() =
                                    Ast::make< ValueLiteral >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2564 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 136:
#line 1238 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::BinaryConstant >(
                                        yystack_[ 0 ].value.as< std::string >(),
                                        libstdhl::Type::HEXADECIMAL );
                                yylhs.value.as< ValueLiteral::Ptr >() =
                                    Ast::make< ValueLiteral >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2580 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 137:
#line 1254 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value =
                                    libstdhl::Memory::get< libcasm_ir::StringConstant >(
                                        yystack_[ 0 ].value.as< std::string >() );
                                yylhs.value.as< ValueLiteral::Ptr >() =
                                    Ast::make< ValueLiteral >( yylhs.location, value );
                            }
                            catch( const std::domain_error& e )
                            {
                                throw syntax_error( yylhs.location, e.what() );
                            }
                        }
#line 2596 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 138:
#line 1270 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ReferenceLiteral::Ptr >() =
                                Ast::make< ReferenceLiteral >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2604 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 139:
#line 1278 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< ListLiteral::Ptr >() =
                                Ast::make< ListLiteral >( yylhs.location, expressions );
                        }
#line 2613 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 140:
#line 1283 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListLiteral::Ptr >() = Ast::make< ListLiteral >(
                                yylhs.location, yystack_[ 1 ].value.as< Expressions::Ptr >() );
                        }
#line 2621 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 141:
#line 1287 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListLiteral::Ptr >() = nullptr;
                        }
#line 2629 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 142:
#line 1295 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RangeLiteral::Ptr >() = Ast::make< RangeLiteral >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Expression::Ptr >() );
                        }
#line 2637 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 143:
#line 1307 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2647 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 144:
#line 1313 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2657 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 145:
#line 1323 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< BasicType::Ptr >();
                        }
#line 2665 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 146:
#line 1327 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2673 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 147:
#line 1331 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< RelationType::Ptr >();
                        }
#line 2681 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 148:
#line 1335 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< FixedSizedType::Ptr >();
                        }
#line 2689 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 149:
#line 1343 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicType::Ptr >() = Ast::make< BasicType >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2697 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 150:
#line 1351 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ComposedType::Ptr >() = Ast::make< ComposedType >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 1 ].value.as< Types::Ptr >() );
                        }
#line 2705 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 151:
#line 1359 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RelationType::Ptr >() = Ast::make< RelationType >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 3 ].value.as< Types::Ptr >(),
                                yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2713 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 152:
#line 1367 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FixedSizedType::Ptr >() = Ast::make< FixedSizedType >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2721 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 153:
#line 1379 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() =
                                yystack_[ 1 ].value.as< Expressions::Ptr >();
                        }
#line 2729 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 154:
#line 1383 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() = nullptr;
                        }
#line 2737 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 155:
#line 1387 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2746 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 156:
#line 1396 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = yystack_[ 3 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 1 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2756 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 157:
#line 1410 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2766 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 158:
#line 1416 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2776 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 159:
#line 1426 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = yystack_[ 0 ].value.as< Types::Ptr >();
                        }
#line 2784 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 160:
#line 1430 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = Ast::make< Types >( yylhs.location );
                        }
#line 2792 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 161:
#line 1438 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >();
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2802 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 162:
#line 1444 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2812 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 163:
#line 1454 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< VariableDefinition >::Ptr >();
                        }
#line 2820 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 164:
#line 1458 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = nullptr;
                        }
#line 2828 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 165:
#line 1462 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                        }
#line 2836 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 166:
#line 1474 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2844 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 167:
#line 1478 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                Ast::make< UndefLiteral >( yylhs.location );
                        }
#line 2852 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 168:
#line 1486 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2860 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 169:
#line 1490 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2868 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 170:
#line 1498 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                yystack_[ 2 ].value.as< NodeList< UpdateRule >::Ptr >();
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2878 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 171:
#line 1504 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2888 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 172:
#line 1514 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2900 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 173:
#line 1522 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2914 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 174:
#line 1532 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2925 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 175:
#line 1543 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 0 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2933 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 176:
#line 1547 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2941 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 177:
#line 1559 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() = Ast::make< Identifier >(
                                yylhs.location, yystack_[ 0 ].value.as< std::string >() );
                        }
#line 2949 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 178:
#line 1563 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() =
                                Ast::make< Identifier >( yylhs.location, "in" );
                        }
#line 2957 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 179:
#line 1571 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Identifiers::Ptr >(),
                                IdentifierPath::Type::ABSOLUTE );
                        }
#line 2965 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 180:
#line 1575 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
                        }
#line 2975 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 181:
#line 1585 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = yystack_[ 2 ].value.as< Identifiers::Ptr >();
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2985 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 182:
#line 1591 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2995 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 183:
#line 1605 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3003 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 184:
#line 1609 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto unresolvedType =
                                Ast::make< UnresolvedType >( yylhs.location );
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    unresolvedType );
                        }
#line 3012 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 185:
#line 1618 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 3020 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 186:
#line 1626 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3030 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 187:
#line 1632 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3038 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 188:
#line 1640 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3048 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 189:
#line 1646 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3056 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 190:
#line 1658 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = yystack_[ 2 ].value.as< Attributes::Ptr >();
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3066 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 191:
#line 1664 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = Ast::make< Attributes >( yylhs.location );
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3076 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 192:
#line 1673 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< BasicAttribute::Ptr >();
                        }
#line 3084 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 193:
#line 1677 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< ExpressionAttribute::Ptr >();
                        }
#line 3092 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 194:
#line 1685 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicAttribute::Ptr >() = Ast::make< BasicAttribute >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 3100 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 195:
#line 1693 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExpressionAttribute::Ptr >() =
                                Ast::make< ExpressionAttribute >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 3108 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

#line 3112 "GrammarParser.cpp"  // lalr1.cc:859
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

    const short int Parser::yytable_ninf_ = -159;

    const short int Parser::yypact_[] = {
        7,    -228, -1,   29,   82,   -228, -228, 1446, -18,  -228, -228, -228, -228, -228, -11,
        -1,   -1,   -1,   -1,   -1,   -1,   198,  -228, -228, -228, -228, -228, -228, -228, -228,
        -4,   -4,   -4,   1446, -4,   -228, -228, -228, 1446, 1446, 1446, 854,  917,  -1,   -13,
        -228, -228, -228, -228, -228, -228, 2266, -22,  -228, -228, -228, -228, -228, -228, -228,
        -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -228,
        6,    28,   49,   -1,   1509, -228, 22,   48,   22,   52,   46,   0,    -228, -1,   71,
        -228, -228, 80,   105,  110,  1777, 115,  -228, -228, -228, 91,   1446, 1994, 102,  -228,
        8,    2028, -228, -228, -13,  1446, 1446, 1446, 1446, 1446, 1446, 1446, 1446, 1446, 1446,
        1446, 1446, 1446, 1446, 1446, 1446, 1446, -1,   980,  -228, -1,   -228, -228, 854,  2062,
        89,   98,   -228, 107,  2,    90,   117,  -25,  -13,  -13,  225,  16,   -13,  1446, 1446,
        1446, 1446, 1446, -228, 2096, -228, -228, -228, 1446, 1446, -228, -228, -228, -228, -228,
        -9,   510,  2300, 2329, 380,  103,  103,  237,  167,  167,  109,  109,  109,  -228, 380,
        237,  167,  167,  6,    122,  -228, -31,  2266, -228, 116,  1994, 1446, 1446, 1509, -228,
        127,  -1,   -28,  71,   -228, -228, -13,  3,    1320, -13,  -228, -228, 118,  114,  -228,
        -1,   -228, 1535, 1921, 1659, 1853, 1960, 6,    2266, 2130, -13,  1446, -228, -228, -228,
        1446, 2266, 2266, -228, -228, 45,   -228, -2,   130,  -228, -1,   -228, 15,   -228, 511,
        592,  -228, -4,   -4,   -4,   1320, 113,  1446, 1446, 660,  728,  -228, -228, -228, -228,
        -228, -228, -228, -228, -228, -228, -228, -228, -22,  -39,  119,  131,  134,  -13,  -13,
        -228, 1446, 1446, 1446, 1446, 1446, -228, -228, 83,   67,   129,  -228, 2164, -1,   -228,
        1446, 79,   -228, 3,    169,  -228, 1048, 165,  1116, 153,  183,  190,  -228, 147,  119,
        131,  1815, 1887, 172,  1184, 141,  1252, 1446, 1320, -228, 204,  2266, 2266, 2266, 2266,
        2266, -13,  -228, -13,  -228, -228, 2266, -1,   -228, -228, -228, -228, -228, -228, 1446,
        1446, 1446, 1320, 168,  -228, -228, -228, -228, 2266, -228, 186,  229,  -228, 191,  -228,
        1579, 1619, 1699, 223,  791,  1446, 201,  -228, -228, 1320, 1320, 1446, 1320, 1320, 203,
        200,  205,  -228, 1383, 2198, 2232, 1509, -228, -228, 1739, -228, -228, -228, 1320, 1320,
        -228, -228, 1320, -228, 207,  1320, -228, -228, -228, -228, -228
    };

    const unsigned char Parser::yydefact_[] = {
        0,   4,   0,   0,   0,   178, 177, 194, 0,   191, 192, 193, 1,   9,   0,   0,   0,   0,
        0,   0,   0,   0,   6,   8,   10,  11,  12,  13,  20,  14,  0,   0,   0,   0,   0,   129,
        131, 130, 0,   0,   0,   0,   0,   0,   0,   135, 136, 132, 133, 134, 137, 195, 74,  76,
        84,  85,  86,  75,  77,  78,  79,  80,  81,  87,  119, 120, 121, 122, 123, 124, 125, 126,
        127, 128, 182, 108, 179, 0,   0,   176, 21,  165, 0,   165, 0,   0,   0,   5,   0,   184,
        187, 183, 0,   0,   0,   0,   0,   107, 88,  89,  0,   0,   0,   0,   139, 0,   73,  180,
        138, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   109, 0,   3,   190, 0,   172, 0,   175, 171, 0,   0,   0,   0,   0,   0,
        160, 0,   0,   0,   0,   0,   0,   0,   0,   83,  0,   82,  141, 140, 0,   0,   113, 145,
        146, 147, 148, 149, 104, 102, 103, 106, 90,  91,  97,  98,  99,  92,  93,  94,  95,  105,
        96,  100, 101, 110, 0,   155, 0,   73,  181, 0,   73,  0,   0,   0,   22,  0,   0,   0,
        0,   189, 162, 0,   0,   0,   0,   28,  158, 159, 0,   7,   0,   185, 0,   0,   0,   0,
        0,   0,   72,  0,   160, 0,   111, 154, 153, 0,   173, 174, 170, 164, 0,   163, 0,   0,
        25,  0,   27,  0,   23,  0,   0,   42,  0,   0,   0,   0,   0,   0,   0,   0,   0,   17,
        29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  0,   67,  69,  71,  0,   0,   0,
        186, 0,   0,   0,   0,   0,   112, 142, 0,   144, 0,   152, 72,  0,   161, 0,   0,   15,
        0,   0,   41,  0,   0,   0,   0,   0,   0,   56,  66,  68,  70,  0,   0,   0,   0,   0,
        0,   0,   0,   157, 167, 114, 117, 116, 115, 118, 0,   150, 0,   156, 188, 16,  0,   26,
        64,  62,  40,  60,  58,  0,   0,   0,   0,   0,   59,  57,  63,  61,  65,  18,  0,   169,
        143, 0,   24,  0,   0,   0,   43,  0,   0,   0,   19,  151, 0,   0,   0,   0,   0,   0,
        0,   0,   51,  0,   0,   0,   176, 52,  53,  0,   55,  44,  46,  0,   0,   45,  50,  0,
        166, 0,   0,   47,  48,  49,  168, 54
    };

    const short int Parser::yypgoto_[] = {
        -228, -228, -228, -228, 233,  124,  -228, -228, -228, -228, -228, -33,  -228, -228,
        218,  -227, -228, -228, -228, -105, -228, -228, -228, -228, -228, -228, -228, -228,
        -228, -49,  -7,   -3,   -228, 88,   123,  163,  -228, -228, -228, -228, -228, -228,
        -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -228, -45,  -228,
        -228, -228, -228, -171, -228, -228, 39,   -228, 179,  -228, -228, -228, 70,   -96,
        42,   -8,   -228, 62,   -137, -23,  43,   -19,  209,  -228, -228
    };

    const short int Parser::yydefgoto_[] = {
        -1,  3,   4,   21,  22,  23,  24,  25,  26,  27,  28,  236, 237, 29,  290, 291, 252,
        253, 254, 362, 363, 255, 256, 257, 258, 259, 260, 261, 262, 105, 134, 52,  53,  54,
        55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,
        72,  73,  278, 160, 161, 162, 163, 164, 129, 135, 207, 208, 197, 140, 341, 352, 136,
        137, 138, 74,  75,  76,  90,  91,  92,  200, 8,   9,   10,  11
    };

    const short int Parser::yytable_[] = {
        51,  86,  199, 195, 234, 5,   80,   5,   93,  94,  1,   96,  222, 293, 5,   224, 5,   5,
        231, 203, 5,   5,   304, 306, 158,  -84, 95,  232, 307, 12,  77,  97,  98,  99,  102, 106,
        108, 78,  79,  43,  204, 43,  127,  88,  7,   196, 276, 220, 145, 196, 235, 128, 131, 221,
        2,   78,  157, 81,  82,  83,  84,   85,  7,   158, 210, 287, 6,   139, 6,   146, 288, 78,
        89,  89,  89,  6,   89,  6,   6,    186, 130, 6,   6,   13,  189, 107, 14,  15,  16,  17,
        18,  19,  141, 283, 154, 199, 143,  144, 205, 206, 78,  165, 211, 166, 167, 168, 169, 170,
        171, 172, 173, 174, 175, 176, 177,  178, 179, 180, 181, 182, 7,   187, 147, 149, 148, -158,
        190, 322, 150, 20,  7,   5,   -158, 152, 78,  165, 165, 153, 316, 165, 317, 212, 213, 214,
        215, 216, 320, 35,  36,  37,  156,  218, 219, 193, 192, 201, 233, 194, 41,  267, 42,  119,
        120, 121, 122, 43,  202, 44,  223,  183, 122, 225, 188, 229, 285, 279, 268, 230, 308, 269,
        327, 198, 324, -85, 226, 227, 45,   46,  47,  48,  49,  50,  6,   165, 318, -86, 165, 329,
        -2,  13,  263, 330, 14,  15,  16,   17,  18,  19,  331, 114, 115, -84, 165, 336, 281, 340,
        286, 349, 282, 294, 295, 296, 334,  309, 310, 119, 120, 121, 122, 14,  15,  16,  17,  18,
        19,  350, 263, 263, 7,   351, 301,  302, 263, 263, 238, 20,  263, 263, 353, 358, 366, 373,
        89,  372, 87,  323, 374, 384, 376,  280, 165, 165, 142, 228, 311, 312, 313, 314, 315, 209,
        379, 342, 270, 343, 198, 284, 0,    7,   321, 114, 115, 0,   0,   0,   89,  89,  89,  132,
        263, 0,   263, 264, 0,   117, 118,  119, 120, 121, 122, 0,   338, 263, 0,   263, 0,   263,
        125, 126, 165, 0,   165, 0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   345, 346,
        347, 198, 265, 264, 264, 263, 238,  0,   0,   264, 298, 0,   0,   264, 264, 0,   0,   0,
        364, 365, 0,   0,   0,   0,   0,    369, 0,   263, 263, 0,   263, 263, 364, 0,   0,   0,
        0,   0,   265, 265, 344, 0,   266,  0,   265, 299, 263, 263, 265, 265, 263, 0,   0,   263,
        0,   264, 0,   264, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   264, 0,   264, 0,
        264, 0,   0,   0,   0,   0,   266,  266, 0,   0,   0,   0,   266, 300, 0,   0,   266, 266,
        265, 0,   265, 110, 111, 112, 264,  251, 114, 115, 116, 0,   0,   265, 0,   265, 0,   265,
        0,   0,   0,   0,   117, 118, 119,  120, 121, 122, 264, 264, 0,   264, 264, 0,   124, 125,
        126, 0,   0,   0,   266, 265, 266,  0,   0,   0,   0,   264, 264, 297, 0,   264, 0,   266,
        264, 266, 0,   266, 0,   0,   0,    0,   0,   265, 265, 0,   265, 265, 0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   266, 265, 265, 0,   0,   265, 0,   0,   265,
        0,   0,   0,   0,   0,   326, 0,    326, 289, 0,   0,   0,   0,   266, 266, 0,   266, 266,
        326, 239, 326, 240, 339, 241, 242,  5,   243, 244, 245, 0,   246, 247, 266, 266, 248, 0,
        266, 0,   0,   266, 0,   35,  36,   37,  0,   0,   348, 0,   114, 115, 116, 0,   41,  0,
        42,  0,   249, 0,   0,   43,  0,    44,  117, 118, 119, 120, 121, 122, 367, 368, 0,   370,
        371, 0,   124, 125, 126, 0,   250,  0,   45,  46,  47,  48,  49,  50,  6,   381, 382, 292,
        0,   383, 0,   0,   385, 0,   0,    0,   0,   0,   239, 0,   240, 0,   241, 242, 5,   243,
        244, 245, 0,   246, 247, 0,   0,    248, 0,   0,   0,   0,   0,   0,   35,  36,  37,  0,
        0,   0,   0,   0,   0,   0,   0,    41,  0,   42,  0,   249, 0,   0,   43,  0,   44,  0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   303, 0,   250, 0,   45,
        46,  47,  48,  49,  50,  6,   239,  0,   240, 0,   241, 242, 5,   243, 244, 245, 0,   246,
        247, 0,   0,   248, 0,   0,   0,    0,   0,   0,   35,  36,  37,  0,   0,   0,   0,   0,
        0,   0,   0,   41,  0,   42,  0,    249, 0,   0,   43,  0,   44,  0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   305, 0,   250, 0,   45,  46,  47,  48,  49,
        50,  6,   239, 0,   240, 0,   241,  242, 5,   243, 244, 245, 0,   246, 247, 0,   0,   248,
        0,   0,   0,   0,   0,   0,   35,   36,  37,  0,   0,   0,   0,   0,   0,   0,   0,   41,
        0,   42,  0,   249, 0,   0,   43,   0,   44,  0,   0,   0,   0,   0,   0,   0,   0,   0,
        359, 0,   0,   0,   0,   0,   0,    250, 0,   45,  46,  47,  48,  49,  50,  6,   30,  5,
        31,  32,  0,   0,   0,   33,  0,    0,   0,   0,   360, 0,   34,  0,   0,   35,  36,  37,
        0,   0,   0,   0,   38,  39,  40,   0,   41,  0,   42,  0,   0,   0,   0,   43,  361, 44,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   100, 0,   0,   0,   0,   0,   0,   0,   0,
        45,  46,  47,  48,  49,  50,  6,    30,  5,   31,  32,  0,   0,   0,   33,  0,   0,   0,
        0,   0,   0,   34,  0,   0,   35,   36,  37,  0,   0,   0,   0,   38,  39,  40,  0,   41,
        0,   42,  0,   0,   0,   0,   43,   0,   44,  0,   0,   0,   101, 0,   0,   0,   0,   0,
        103, 0,   0,   0,   0,   0,   0,    0,   0,   45,  46,  47,  48,  49,  50,  6,   30,  5,
        31,  32,  0,   0,   0,   33,  0,    0,   0,   0,   0,   0,   34,  0,   0,   35,  36,  37,
        0,   0,   0,   0,   38,  39,  40,   0,   41,  0,   42,  104, 0,   0,   0,   43,  0,   44,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   184, 0,   0,   0,   0,   0,   0,   0,   0,
        45,  46,  47,  48,  49,  50,  6,    30,  5,   31,  32,  0,   0,   0,   33,  0,   0,   0,
        0,   0,   0,   34,  0,   0,   35,   36,  37,  0,   0,   0,   0,   38,  39,  40,  0,   41,
        185, 42,  0,   0,   0,   0,   43,   0,   44,  0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   45,  46,  47,  48,  49,  50,  6,   239, 325,
        240, 0,   241, 242, 5,   243, 244,  245, 0,   246, 247, 0,   0,   248, 0,   0,   0,   0,
        0,   0,   35,  36,  37,  0,   0,    0,   0,   0,   0,   0,   0,   41,  0,   42,  0,   249,
        0,   0,   43,  0,   44,  0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   250, 0,   45,  46,   47,  48,  49,  50,  6,   239, 0,   240, 328, 241, 242,
        5,   243, 244, 245, 0,   246, 247,  0,   0,   248, 0,   0,   0,   0,   0,   0,   35,  36,
        37,  0,   0,   0,   0,   0,   0,    0,   0,   41,  0,   42,  0,   249, 0,   0,   43,  0,
        44,  0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   250,
        0,   45,  46,  47,  48,  49,  50,   6,   239, 0,   240, 0,   241, 242, 5,   243, 244, 245,
        0,   246, 247, 0,   0,   248, 0,    0,   0,   0,   0,   0,   35,  36,  37,  0,   0,   0,
        0,   0,   0,   0,   0,   41,  0,    42,  0,   249, 335, 0,   43,  0,   44,  0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   250, 0,   45,  46,  47,
        48,  49,  50,  6,   239, 0,   240,  0,   241, 242, 5,   243, 244, 245, 0,   246, 247, 0,
        0,   248, 0,   0,   0,   0,   0,    0,   35,  36,  37,  0,   0,   0,   0,   0,   0,   0,
        0,   41,  0,   42,  0,   249, 0,    0,   43,  0,   44,  0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   250, 337, 45,  46,  47,  48,  49,  50,  6,
        239, 0,   240, 0,   241, 242, 5,    243, 244, 245, 0,   246, 247, 0,   0,   248, 0,   0,
        0,   0,   0,   0,   35,  36,  37,   0,   0,   0,   0,   0,   0,   0,   0,   41,  0,   42,
        0,   249, 0,   0,   43,  0,   44,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   250, 0,    45,  46,  47,  48,  49,  50,  6,   30,  5,   31,  32,
        0,   0,   0,   33,  0,   0,   0,    0,   360, 0,   34,  0,   0,   35,  36,  37,  0,   0,
        0,   0,   38,  39,  40,  0,   41,   0,   42,  0,   0,   375, 0,   43,  361, 44,  0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   45,  46,
        47,  48,  49,  50,  6,   30,  5,    31,  32,  0,   0,   0,   33,  0,   0,   0,   0,   0,
        0,   34,  0,   0,   35,  36,  37,   0,   0,   0,   0,   38,  39,  40,  0,   41,  0,   42,
        0,   0,   0,   0,   43,  0,   44,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,    45,  46,  47,  48,  49,  50,  6,   30,  5,   31,  32,
        0,   0,   0,   33,  0,   0,   0,    0,   0,   0,   34,  0,   0,   35,  36,  37,  0,   0,
        0,   0,   38,  39,  40,  271, 133,  0,   42,  0,   0,   0,   0,   43,  0,   44,  0,   0,
        0,   0,   109, 0,   0,   0,   110,  111, 112, 113, 0,   114, 115, 116, 0,   0,   45,  46,
        47,  48,  49,  50,  6,   0,   0,    117, 118, 119, 120, 121, 122, 354, 0,   0,   0,   123,
        0,   124, 125, 126, 0,   0,   0,    0,   0,   0,   109, 0,   0,   0,   110, 111, 112, 113,
        0,   114, 115, 116, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   117, 118, 119,
        120, 121, 122, 355, 0,   0,   0,    123, 0,   124, 125, 126, 0,   356, 109, 0,   0,   0,
        110, 111, 112, 113, 0,   114, 115,  116, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   117, 118, 119, 120, 121, 122,  273, 0,   0,   0,   123, 0,   124, 125, 126, 0,   0,
        109, 0,   0,   0,   110, 111, 112,  113, 0,   114, 115, 116, 0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   117, 118,  119, 120, 121, 122, 357, 0,   0,   0,   123, 0,   124,
        125, 126, 0,   0,   109, 0,   0,    0,   110, 111, 112, 113, 0,   114, 115, 116, 0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   117, 118, 119, 120, 121, 122, 380, 0,   0,
        0,   123, 0,   124, 125, 126, 0,    0,   109, 0,   0,   0,   110, 111, 112, 113, 0,   114,
        115, 116, 0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   117, 118, 119, 120, 121,
        122, 0,   151, 0,   0,   123, 0,    124, 125, 126, 109, 0,   0,   0,   110, 111, 112, 113,
        0,   114, 115, 116, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   117, 118, 119,
        120, 121, 122, 0,   332, 0,   0,    123, 0,   124, 125, 126, 109, 0,   0,   0,   110, 111,
        112, 113, 0,   114, 115, 116, 0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   117,
        118, 119, 120, 121, 122, 0,   0,    274, 0,   123, 0,   124, 125, 126, 109, 0,   0,   0,
        110, 111, 112, 113, 0,   114, 115,  116, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   117, 118, 119, 120, 121, 122,  333, 0,   0,   0,   123, 109, 124, 125, 126, 110, 111,
        112, 113, 0,   114, 115, 116, 0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   117,
        118, 119, 120, 121, 122, 0,   0,    272, 0,   123, 109, 124, 125, 126, 110, 111, 112, 113,
        0,   114, 115, 116, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   117, 118, 119,
        120, 121, 122, 0,   0,   0,   0,    123, 0,   124, 125, 126, 275, 109, 0,   0,   0,   110,
        111, 112, 113, 0,   114, 115, 116,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        117, 118, 119, 120, 121, 122, 0,    0,   0,   0,   123, 109, 124, 125, 126, 110, 111, 112,
        113, 0,   114, 115, 116, 0,   155,  0,   0,   0,   0,   0,   0,   0,   0,   0,   117, 118,
        119, 120, 121, 122, 0,   0,   0,    0,   123, 109, 124, 125, 126, 110, 111, 112, 113, 0,
        114, 115, 116, 0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   117, 118, 119, 120,
        121, 122, 0,   159, 0,   0,   123,  109, 124, 125, 126, 110, 111, 112, 113, 0,   114, 115,
        116, 0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   117, 118, 119, 120, 121, 122,
        0,   0,   0,   191, 123, 109, 124,  125, 126, 110, 111, 112, 113, 0,   114, 115, 116, 0,
        217, 0,   0,   0,   0,   0,   0,    0,   0,   0,   117, 118, 119, 120, 121, 122, 0,   0,
        0,   0,   123, 109, 124, 125, 126,  110, 111, 112, 113, 0,   114, 115, 116, 0,   0,   0,
        277, 0,   0,   0,   0,   0,   0,    0,   117, 118, 119, 120, 121, 122, 0,   0,   0,   0,
        123, 109, 124, 125, 126, 110, 111,  112, 113, 0,   114, 115, 116, 0,   319, 0,   0,   0,
        0,   0,   0,   0,   0,   0,   117,  118, 119, 120, 121, 122, 0,   0,   0,   0,   123, 109,
        124, 125, 126, 110, 111, 112, 113,  0,   114, 115, 116, 0,   0,   0,   0,   0,   0,   377,
        0,   0,   0,   0,   117, 118, 119,  120, 121, 122, 0,   0,   0,   0,   123, 109, 124, 125,
        126, 110, 111, 112, 113, 0,   114,  115, 116, 0,   0,   0,   0,   0,   378, 0,   0,   0,
        0,   0,   117, 118, 119, 120, 121,  122, 0,   0,   0,   0,   123, 109, 124, 125, 126, 110,
        111, 112, 113, 0,   114, 115, 116,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        117, 118, 119, 120, 121, 122, 0,    0,   0,   0,   123, 0,   124, 125, 126, 110, 0,   112,
        0,   0,   114, 115, 116, 0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   117, 118,
        119, 120, 121, 122, 0,   0,   0,    0,   110, 0,   124, 125, 126, 114, 115, 116, 0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   117, 118, 119, 120, 121, 122, 0,   0,   0,
        0,   0,   0,   124, 125, 126
    };

    const short int Parser::yycheck_[] = {
        7,   20,  139, 1,   1,   18,  14,  18,  31,  32,  3,   34,  183, 240, 18,  46,  18,  18,
        46,  44,  18,  18,  249, 250, 55,  64,  33,  55,  67,  0,   48,  38,  39,  40,  41,  42,
        44,  55,  49,  52,  65,  52,  64,  47,  2,   47,  217, 56,  48,  47,  47,  45,  3,   62,
        47,  55,  48,  15,  16,  17,  18,  19,  20,  55,  48,  50,  79,  45,  79,  88,  55,  55,
        30,  31,  32,  79,  34,  79,  79,  128, 52,  79,  79,  1,   133, 43,  4,   5,   6,   7,
        8,   9,   44,  48,  101, 232, 44,  51,  143, 144, 55,  109, 147, 110, 111, 112, 113, 114,
        115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 78,  128, 51,  18,  44,  58,
        133, 48,  18,  47,  88,  18,  65,  18,  55,  143, 144, 46,  55,  147, 57,  148, 149, 150,
        151, 152, 283, 34,  35,  36,  48,  158, 159, 55,  65,  65,  201, 50,  45,  204, 47,  58,
        59,  60,  61,  52,  49,  54,  46,  127, 61,  55,  130, 46,  44,  220, 58,  196, 44,  65,
        15,  139, 13,  64,  191, 192, 73,  74,  75,  76,  77,  78,  79,  201, 65,  64,  204, 44,
        0,   1,   203, 18,  4,   5,   6,   7,   8,   9,   18,  42,  43,  64,  220, 72,  221, 11,
        235, 49,  225, 242, 243, 244, 50,  268, 269, 58,  59,  60,  61,  4,   5,   6,   7,   8,
        9,   49,  239, 240, 196, 10,  247, 248, 245, 246, 202, 47,  249, 250, 57,  26,  49,  51,
        210, 50,  21,  288, 51,  50,  363, 220, 268, 269, 83,  193, 271, 272, 273, 274, 275, 145,
        366, 316, 210, 318, 232, 232, -1,  235, 285, 42,  43,  -1,  -1,  -1,  242, 243, 244, 78,
        291, -1,  293, 203, -1,  56,  57,  58,  59,  60,  61,  -1,  307, 304, -1,  306, -1,  308,
        69,  70,  316, -1,  318, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  329, 330,
        331, 283, 203, 239, 240, 332, 288, -1,  -1,  245, 246, -1,  -1,  249, 250, -1,  -1,  -1,
        349, 350, -1,  -1,  -1,  -1,  -1,  356, -1,  354, 355, -1,  357, 358, 363, -1,  -1,  -1,
        -1,  -1,  239, 240, 322, -1,  203, -1,  245, 246, 373, 374, 249, 250, 377, -1,  -1,  380,
        -1,  291, -1,  293, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  304, -1,  306, -1,
        308, -1,  -1,  -1,  -1,  -1,  239, 240, -1,  -1,  -1,  -1,  245, 246, -1,  -1,  249, 250,
        291, -1,  293, 37,  38,  39,  332, 203, 42,  43,  44,  -1,  -1,  304, -1,  306, -1,  308,
        -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  354, 355, -1,  357, 358, -1,  68,  69,
        70,  -1,  -1,  -1,  291, 332, 293, -1,  -1,  -1,  -1,  373, 374, 245, -1,  377, -1,  304,
        380, 306, -1,  308, -1,  -1,  -1,  -1,  -1,  354, 355, -1,  357, 358, -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  332, 373, 374, -1,  -1,  377, -1,  -1,  380,
        -1,  -1,  -1,  -1,  -1,  291, -1,  293, 1,   -1,  -1,  -1,  -1,  354, 355, -1,  357, 358,
        304, 12,  306, 14,  308, 16,  17,  18,  19,  20,  21,  -1,  23,  24,  373, 374, 27,  -1,
        377, -1,  -1,  380, -1,  34,  35,  36,  -1,  -1,  332, -1,  42,  43,  44,  -1,  45,  -1,
        47,  -1,  49,  -1,  -1,  52,  -1,  54,  56,  57,  58,  59,  60,  61,  354, 355, -1,  357,
        358, -1,  68,  69,  70,  -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  373, 374, 1,
        -1,  377, -1,  -1,  380, -1,  -1,  -1,  -1,  -1,  12,  -1,  14,  -1,  16,  17,  18,  19,
        20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  71,  -1,  73,
        74,  75,  76,  77,  78,  79,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,
        24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  71,  -1,  73,  74,  75,  76,  77,
        78,  79,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,
        -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,
        -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        1,   -1,  -1,  -1,  -1,  -1,  -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  17,  18,
        19,  20,  -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,  29,  -1,  31,  -1,  -1,  34,  35,  36,
        -1,  -1,  -1,  -1,  41,  42,  43,  -1,  45,  -1,  47,  -1,  -1,  -1,  -1,  52,  53,  54,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        73,  74,  75,  76,  77,  78,  79,  17,  18,  19,  20,  -1,  -1,  -1,  24,  -1,  -1,  -1,
        -1,  -1,  -1,  31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  41,  42,  43,  -1,  45,
        -1,  47,  -1,  -1,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  58,  -1,  -1,  -1,  -1,  -1,
        1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,  76,  77,  78,  79,  17,  18,
        19,  20,  -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,  -1,  -1,  31,  -1,  -1,  34,  35,  36,
        -1,  -1,  -1,  -1,  41,  42,  43,  -1,  45,  -1,  47,  48,  -1,  -1,  -1,  52,  -1,  54,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        73,  74,  75,  76,  77,  78,  79,  17,  18,  19,  20,  -1,  -1,  -1,  24,  -1,  -1,  -1,
        -1,  -1,  -1,  31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  41,  42,  43,  -1,  45,
        46,  47,  -1,  -1,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,  76,  77,  78,  79,  12,  13,
        14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,
        -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,
        -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  12,  -1,  14,  15,  16,  17,
        18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,
        36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,
        54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,
        -1,  73,  74,  75,  76,  77,  78,  79,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,
        -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  50,  -1,  52,  -1,  54,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  -1,  73,  74,  75,
        76,  77,  78,  79,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,
        -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,  77,  78,  79,
        12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,
        -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,
        -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  17,  18,  19,  20,
        -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,  29,  -1,  31,  -1,  -1,  34,  35,  36,  -1,  -1,
        -1,  -1,  41,  42,  43,  -1,  45,  -1,  47,  -1,  -1,  50,  -1,  52,  53,  54,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  73,  74,
        75,  76,  77,  78,  79,  17,  18,  19,  20,  -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,  -1,
        -1,  31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  41,  42,  43,  -1,  45,  -1,  47,
        -1,  -1,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,  76,  77,  78,  79,  17,  18,  19,  20,
        -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,  -1,  -1,  31,  -1,  -1,  34,  35,  36,  -1,  -1,
        -1,  -1,  41,  42,  43,  18,  45,  -1,  47,  -1,  -1,  -1,  -1,  52,  -1,  54,  -1,  -1,
        -1,  -1,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  73,  74,
        75,  76,  77,  78,  79,  -1,  -1,  56,  57,  58,  59,  60,  61,  18,  -1,  -1,  -1,  66,
        -1,  68,  69,  70,  -1,  -1,  -1,  -1,  -1,  -1,  33,  -1,  -1,  -1,  37,  38,  39,  40,
        -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,
        59,  60,  61,  22,  -1,  -1,  -1,  66,  -1,  68,  69,  70,  -1,  32,  33,  -1,  -1,  -1,
        37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  56,  57,  58,  59,  60,  61,  22,  -1,  -1,  -1,  66,  -1,  68,  69,  70,  -1,  -1,
        33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  22,  -1,  -1,  -1,  66,  -1,  68,
        69,  70,  -1,  -1,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  22,  -1,  -1,
        -1,  66,  -1,  68,  69,  70,  -1,  -1,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,
        43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,
        61,  -1,  25,  -1,  -1,  66,  -1,  68,  69,  70,  33,  -1,  -1,  -1,  37,  38,  39,  40,
        -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,
        59,  60,  61,  -1,  25,  -1,  -1,  66,  -1,  68,  69,  70,  33,  -1,  -1,  -1,  37,  38,
        39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,
        57,  58,  59,  60,  61,  -1,  -1,  26,  -1,  66,  -1,  68,  69,  70,  33,  -1,  -1,  -1,
        37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  56,  57,  58,  59,  60,  61,  28,  -1,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,
        39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,
        57,  58,  59,  60,  61,  -1,  -1,  30,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,
        -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,
        59,  60,  61,  -1,  -1,  -1,  -1,  66,  -1,  68,  69,  70,  32,  33,  -1,  -1,  -1,  37,
        38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,
        40,  -1,  42,  43,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,
        58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,
        42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,
        60,  61,  -1,  63,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,
        44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,
        -1,  -1,  -1,  65,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,
        46,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,
        -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,
        48,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,
        66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  46,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  33,
        68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  51,
        -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  33,  68,  69,
        70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  50,  -1,  -1,  -1,
        -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  33,  68,  69,  70,  37,
        38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  -1,  68,  69,  70,  37,  -1,  39,
        -1,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,
        58,  59,  60,  61,  -1,  -1,  -1,  -1,  37,  -1,  68,  69,  70,  42,  43,  44,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,
        -1,  -1,  -1,  68,  69,  70
    };

    const unsigned char Parser::yystos_[] = {
        0,   3,   47,  85,  86,  18,  79,  154, 161, 162, 163, 164, 0,   1,   4,   5,   6,   7,
        8,   9,   47,  87,  88,  89,  90,  91,  92,  93,  94,  97,  17,  19,  20,  24,  31,  34,
        35,  36,  41,  42,  43,  45,  47,  52,  54,  73,  74,  75,  76,  77,  78,  114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
        135, 136, 154, 155, 156, 48,  55,  49,  155, 154, 154, 154, 154, 154, 161, 88,  47,  154,
        157, 158, 159, 159, 159, 114, 159, 114, 114, 114, 1,   58,  114, 1,   48,  113, 114, 154,
        155, 33,  37,  38,  39,  40,  42,  43,  44,  56,  57,  58,  59,  60,  61,  66,  68,  69,
        70,  64,  45,  143, 52,  3,   162, 45,  114, 144, 151, 152, 153, 45,  148, 44,  148, 44,
        51,  48,  161, 51,  44,  18,  18,  25,  18,  46,  114, 46,  48,  48,  55,  63,  138, 139,
        140, 141, 142, 155, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114,
        114, 114, 114, 154, 1,   46,  113, 114, 154, 113, 114, 65,  65,  55,  50,  1,   47,  147,
        154, 158, 160, 65,  49,  44,  65,  138, 138, 145, 146, 89,  48,  138, 114, 114, 114, 114,
        114, 46,  114, 114, 56,  62,  143, 46,  46,  55,  114, 114, 152, 46,  161, 46,  55,  138,
        1,   47,  95,  96,  154, 12,  14,  16,  17,  19,  20,  21,  23,  24,  27,  49,  71,  98,
        100, 101, 102, 105, 106, 107, 108, 109, 110, 111, 112, 115, 117, 118, 119, 138, 58,  65,
        157, 18,  30,  22,  26,  32,  143, 48,  137, 138, 146, 114, 114, 48,  160, 44,  161, 50,
        55,  1,   98,  99,  1,   99,  159, 159, 159, 98,  117, 118, 119, 114, 114, 1,   99,  1,
        99,  67,  44,  138, 138, 114, 114, 114, 114, 114, 55,  57,  65,  46,  158, 114, 48,  95,
        13,  13,  98,  15,  15,  44,  18,  18,  25,  28,  50,  50,  72,  72,  114, 98,  11,  149,
        138, 138, 154, 114, 114, 114, 98,  49,  49,  10,  150, 57,  18,  22,  32,  22,  26,  1,
        29,  53,  103, 104, 114, 114, 49,  98,  98,  114, 98,  98,  50,  51,  51,  50,  103, 51,
        50,  153, 22,  98,  98,  98,  50,  98
    };

    const unsigned char Parser::yyr1_[] = {
        0,   84,  85,  86,  86,  87,  87,  88,  88,  88,  89,  89,  89,  89,  89,  90,  91,  92,
        92,  93,  93,  94,  94,  95,  95,  95,  96,  96,  97,  98,  98,  98,  98,  98,  98,  98,
        98,  98,  98,  98,  99,  99,  100, 101, 101, 102, 102, 103, 103, 103, 104, 104, 105, 106,
        106, 107, 108, 109, 109, 109, 109, 110, 110, 110, 110, 111, 112, 112, 112, 112, 112, 112,
        113, 113, 114, 114, 114, 114, 114, 114, 114, 114, 115, 115, 115, 115, 115, 115, 116, 116,
        116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116,
        117, 117, 118, 118, 119, 120, 121, 122, 123, 124, 125, 126, 126, 126, 126, 126, 126, 126,
        126, 126, 126, 127, 128, 128, 129, 130, 131, 132, 132, 133, 134, 135, 135, 135, 136, 137,
        137, 138, 138, 138, 138, 139, 140, 141, 142, 143, 143, 143, 144, 145, 145, 146, 146, 147,
        147, 148, 148, 148, 149, 149, 150, 150, 151, 151, 152, 152, 152, 153, 153, 154, 154, 155,
        155, 156, 156, 157, 157, 158, 159, 159, 160, 160, 161, 161, 162, 162, 163, 164
    };

    const unsigned char Parser::yyr2_[] = {
        0, 2, 2, 4, 1, 2, 1, 4, 1, 1, 1, 1, 1, 1, 1, 6, 7, 5, 7, 8, 1, 2, 4, 1, 4, 1, 3, 1,
        4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 4, 6, 6, 6, 3, 3, 3, 2, 1, 6, 6, 8, 6,
        2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3,
        1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 2, 3, 4,
        5, 3, 6, 6, 6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,
        3, 3, 5, 3, 1, 1, 1, 1, 1, 1, 4, 6, 3, 3, 3, 2, 5, 3, 1, 1, 0, 3, 1, 3, 3, 0, 4, 0,
        4, 0, 3, 1, 1, 3, 3, 1, 0, 1, 1, 1, 2, 3, 1, 1, 1, 3, 4, 1, 4, 1, 3, 1, 1, 1, 1, 2
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
                                             "\"using\"",
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
                                             "\"::\"",
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
                                             "UsingDefinition",
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
                                             "SimpleOrClaspedTerm",
                                             "OperatorExpression",
                                             "DirectCallExpression",
                                             "MethodCallExpression",
                                             "IndirectCallExpression",
                                             "TypeCastingExpression",
                                             "LetExpression",
                                             "ConditionalExpression",
                                             "ChooseExpression",
                                             "UniversalQuantifierExpression",
                                             "ExistentialQuantifierExpression",
                                             "Literal",
                                             "UndefinedLiteral",
                                             "BooleanLiteral",
                                             "IntegerLiteral",
                                             "RationalLiteral",
                                             "DecimalLiteral",
                                             "BinaryLiteral",
                                             "StringLiteral",
                                             "ReferenceLiteral",
                                             "ListLiteral",
                                             "RangeLiteral",
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
        0,    385,  385,  394,  400,  408,  414,  424,  430,  434,  442,  446,  450,  454,
        458,  466,  474,  482,  487,  496,  512,  520,  543,  561,  565,  571,  579,  585,
        595,  607,  611,  615,  619,  623,  627,  631,  635,  639,  643,  647,  655,  661,
        671,  679,  683,  691,  695,  703,  707,  711,  719,  725,  735,  743,  747,  755,
        763,  771,  775,  779,  784,  793,  797,  801,  806,  815,  825,  829,  833,  837,
        841,  845,  857,  863,  873,  877,  881,  885,  889,  893,  897,  901,  909,  913,
        917,  921,  925,  929,  941,  945,  949,  953,  957,  961,  965,  969,  973,  977,
        981,  985,  989,  993,  997,  1001, 1005, 1009, 1013, 1017, 1025, 1030, 1038, 1043,
        1051, 1059, 1067, 1075, 1083, 1091, 1099, 1111, 1115, 1119, 1123, 1127, 1131, 1135,
        1139, 1143, 1147, 1155, 1163, 1168, 1177, 1193, 1209, 1225, 1237, 1253, 1269, 1277,
        1282, 1286, 1294, 1306, 1312, 1322, 1326, 1330, 1334, 1342, 1350, 1358, 1366, 1378,
        1382, 1386, 1395, 1409, 1415, 1425, 1429, 1437, 1443, 1453, 1457, 1461, 1473, 1477,
        1485, 1489, 1497, 1503, 1513, 1521, 1531, 1542, 1546, 1558, 1562, 1570, 1574, 1584,
        1590, 1604, 1608, 1617, 1625, 1631, 1639, 1645, 1657, 1663, 1672, 1676, 1684, 1692
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
#line 4175 "GrammarParser.cpp"               // lalr1.cc:1167
#line 1698 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1168

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
