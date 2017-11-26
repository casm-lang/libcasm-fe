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
            case 159:  // Attribute
                value.move< Attribute::Ptr >( that.value );
                break;

            case 158:  // Attributes
                value.move< Attributes::Ptr >( that.value );
                break;

            case 160:  // BasicAttribute
                value.move< BasicAttribute::Ptr >( that.value );
                break;

            case 136:  // BasicType
                value.move< BasicType::Ptr >( that.value );
                break;

            case 106:  // BlockRule
                value.move< BlockRule::Ptr >( that.value );
                break;

            case 114:  // CallExpression
                value.move< CallExpression::Ptr >( that.value );
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

            case 120:  // ChooseExpression
                value.move< ChooseExpression::Ptr >( that.value );
                break;

            case 104:  // ChooseRule
                value.move< ChooseRule::Ptr >( that.value );
                break;

            case 137:  // ComposedType
                value.move< ComposedType::Ptr >( that.value );
                break;

            case 119:  // ConditionalExpression
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

            case 115:  // DirectCallExpression
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

            case 122:  // ExistentialQuantifierExpression
                value.move< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // Term
            case 112:  // Expression
            case 125:  // Literal
            case 146:  // MaybeDefined
                value.move< Expression::Ptr >( that.value );
                break;

            case 161:  // ExpressionAttribute
                value.move< ExpressionAttribute::Ptr >( that.value );
                break;

            case 110:  // Terms
            case 140:  // Arguments
            case 141:  // TwoOrMoreArguments
                value.move< Expressions::Ptr >( that.value );
                break;

            case 139:  // FixedSizedType
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

            case 151:  // Identifier
                value.move< Identifier::Ptr >( that.value );
                break;

            case 152:  // IdentifierPath
                value.move< IdentifierPath::Ptr >( that.value );
                break;

            case 153:  // DotSeparatedIdentifiers
                value.move< Identifiers::Ptr >( that.value );
                break;

            case 116:  // IndirectCallExpression
                value.move< IndirectCallExpression::Ptr >( that.value );
                break;

            case 105:  // IterateRule
                value.move< IterateRule::Ptr >( that.value );
                break;

            case 118:  // LetExpression
                value.move< LetExpression::Ptr >( that.value );
                break;

            case 102:  // LetRule
                value.move< LetRule::Ptr >( that.value );
                break;

            case 123:  // List
                value.move< ListExpression::Ptr >( that.value );
                break;

            case 117:  // MethodCallExpression
                value.move< MethodCallExpression::Ptr >( that.value );
                break;

            case 147:  // MaybeInitially
            case 148:  // Initializers
            case 150:  // MaybeInitializers
                value.move< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 144:  // Parameters
            case 145:  // MaybeParameters
                value.move< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 124:  // Range
                value.move< RangeExpression::Ptr >( that.value );
                break;

            case 133:  // ReferenceLiteral
                value.move< ReferenceAtom::Ptr >( that.value );
                break;

            case 138:  // RelationType
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

            case 134:  // Types
            case 142:  // FunctionParameters
            case 143:  // MaybeFunctionParameters
                value.move< Types::Ptr >( that.value );
                break;

            case 126:  // UndefinedLiteral
                value.move< UndefAtom::Ptr >( that.value );
                break;

            case 121:  // UniversalQuantifierExpression
                value.move< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 108:  // UpdateRule
            case 149:  // Initializer
                value.move< UpdateRule::Ptr >( that.value );
                break;

            case 127:  // BooleanLiteral
            case 128:  // IntegerLiteral
            case 129:  // RationalLiteral
            case 130:  // DecimalLiteral
            case 131:  // BitLiteral
            case 132:  // StringLiteral
                value.move< ValueAtom::Ptr >( that.value );
                break;

            case 154:  // Variable
            case 155:  // TypedVariable
            case 156:  // AttributedVariable
            case 157:  // TypedAttributedVariable
                value.move< VariableDefinition::Ptr >( that.value );
                break;

            case 135:  // Type
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
            case 159:  // Attribute
                value.copy< Attribute::Ptr >( that.value );
                break;

            case 158:  // Attributes
                value.copy< Attributes::Ptr >( that.value );
                break;

            case 160:  // BasicAttribute
                value.copy< BasicAttribute::Ptr >( that.value );
                break;

            case 136:  // BasicType
                value.copy< BasicType::Ptr >( that.value );
                break;

            case 106:  // BlockRule
                value.copy< BlockRule::Ptr >( that.value );
                break;

            case 114:  // CallExpression
                value.copy< CallExpression::Ptr >( that.value );
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

            case 120:  // ChooseExpression
                value.copy< ChooseExpression::Ptr >( that.value );
                break;

            case 104:  // ChooseRule
                value.copy< ChooseRule::Ptr >( that.value );
                break;

            case 137:  // ComposedType
                value.copy< ComposedType::Ptr >( that.value );
                break;

            case 119:  // ConditionalExpression
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

            case 115:  // DirectCallExpression
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

            case 122:  // ExistentialQuantifierExpression
                value.copy< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // Term
            case 112:  // Expression
            case 125:  // Literal
            case 146:  // MaybeDefined
                value.copy< Expression::Ptr >( that.value );
                break;

            case 161:  // ExpressionAttribute
                value.copy< ExpressionAttribute::Ptr >( that.value );
                break;

            case 110:  // Terms
            case 140:  // Arguments
            case 141:  // TwoOrMoreArguments
                value.copy< Expressions::Ptr >( that.value );
                break;

            case 139:  // FixedSizedType
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

            case 151:  // Identifier
                value.copy< Identifier::Ptr >( that.value );
                break;

            case 152:  // IdentifierPath
                value.copy< IdentifierPath::Ptr >( that.value );
                break;

            case 153:  // DotSeparatedIdentifiers
                value.copy< Identifiers::Ptr >( that.value );
                break;

            case 116:  // IndirectCallExpression
                value.copy< IndirectCallExpression::Ptr >( that.value );
                break;

            case 105:  // IterateRule
                value.copy< IterateRule::Ptr >( that.value );
                break;

            case 118:  // LetExpression
                value.copy< LetExpression::Ptr >( that.value );
                break;

            case 102:  // LetRule
                value.copy< LetRule::Ptr >( that.value );
                break;

            case 123:  // List
                value.copy< ListExpression::Ptr >( that.value );
                break;

            case 117:  // MethodCallExpression
                value.copy< MethodCallExpression::Ptr >( that.value );
                break;

            case 147:  // MaybeInitially
            case 148:  // Initializers
            case 150:  // MaybeInitializers
                value.copy< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 144:  // Parameters
            case 145:  // MaybeParameters
                value.copy< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 124:  // Range
                value.copy< RangeExpression::Ptr >( that.value );
                break;

            case 133:  // ReferenceLiteral
                value.copy< ReferenceAtom::Ptr >( that.value );
                break;

            case 138:  // RelationType
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

            case 134:  // Types
            case 142:  // FunctionParameters
            case 143:  // MaybeFunctionParameters
                value.copy< Types::Ptr >( that.value );
                break;

            case 126:  // UndefinedLiteral
                value.copy< UndefAtom::Ptr >( that.value );
                break;

            case 121:  // UniversalQuantifierExpression
                value.copy< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 108:  // UpdateRule
            case 149:  // Initializer
                value.copy< UpdateRule::Ptr >( that.value );
                break;

            case 127:  // BooleanLiteral
            case 128:  // IntegerLiteral
            case 129:  // RationalLiteral
            case 130:  // DecimalLiteral
            case 131:  // BitLiteral
            case 132:  // StringLiteral
                value.copy< ValueAtom::Ptr >( that.value );
                break;

            case 154:  // Variable
            case 155:  // TypedVariable
            case 156:  // AttributedVariable
            case 157:  // TypedAttributedVariable
                value.copy< VariableDefinition::Ptr >( that.value );
                break;

            case 135:  // Type
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
                    case 159:  // Attribute
                        yylhs.value.build< Attribute::Ptr >();
                        break;

                    case 158:  // Attributes
                        yylhs.value.build< Attributes::Ptr >();
                        break;

                    case 160:  // BasicAttribute
                        yylhs.value.build< BasicAttribute::Ptr >();
                        break;

                    case 136:  // BasicType
                        yylhs.value.build< BasicType::Ptr >();
                        break;

                    case 106:  // BlockRule
                        yylhs.value.build< BlockRule::Ptr >();
                        break;

                    case 114:  // CallExpression
                        yylhs.value.build< CallExpression::Ptr >();
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

                    case 120:  // ChooseExpression
                        yylhs.value.build< ChooseExpression::Ptr >();
                        break;

                    case 104:  // ChooseRule
                        yylhs.value.build< ChooseRule::Ptr >();
                        break;

                    case 137:  // ComposedType
                        yylhs.value.build< ComposedType::Ptr >();
                        break;

                    case 119:  // ConditionalExpression
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

                    case 115:  // DirectCallExpression
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

                    case 122:  // ExistentialQuantifierExpression
                        yylhs.value.build< ExistentialQuantifierExpression::Ptr >();
                        break;

                    case 111:  // Term
                    case 112:  // Expression
                    case 125:  // Literal
                    case 146:  // MaybeDefined
                        yylhs.value.build< Expression::Ptr >();
                        break;

                    case 161:  // ExpressionAttribute
                        yylhs.value.build< ExpressionAttribute::Ptr >();
                        break;

                    case 110:  // Terms
                    case 140:  // Arguments
                    case 141:  // TwoOrMoreArguments
                        yylhs.value.build< Expressions::Ptr >();
                        break;

                    case 139:  // FixedSizedType
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

                    case 151:  // Identifier
                        yylhs.value.build< Identifier::Ptr >();
                        break;

                    case 152:  // IdentifierPath
                        yylhs.value.build< IdentifierPath::Ptr >();
                        break;

                    case 153:  // DotSeparatedIdentifiers
                        yylhs.value.build< Identifiers::Ptr >();
                        break;

                    case 116:  // IndirectCallExpression
                        yylhs.value.build< IndirectCallExpression::Ptr >();
                        break;

                    case 105:  // IterateRule
                        yylhs.value.build< IterateRule::Ptr >();
                        break;

                    case 118:  // LetExpression
                        yylhs.value.build< LetExpression::Ptr >();
                        break;

                    case 102:  // LetRule
                        yylhs.value.build< LetRule::Ptr >();
                        break;

                    case 123:  // List
                        yylhs.value.build< ListExpression::Ptr >();
                        break;

                    case 117:  // MethodCallExpression
                        yylhs.value.build< MethodCallExpression::Ptr >();
                        break;

                    case 147:  // MaybeInitially
                    case 148:  // Initializers
                    case 150:  // MaybeInitializers
                        yylhs.value.build< NodeList< UpdateRule >::Ptr >();
                        break;

                    case 144:  // Parameters
                    case 145:  // MaybeParameters
                        yylhs.value.build< NodeList< VariableDefinition >::Ptr >();
                        break;

                    case 124:  // Range
                        yylhs.value.build< RangeExpression::Ptr >();
                        break;

                    case 133:  // ReferenceLiteral
                        yylhs.value.build< ReferenceAtom::Ptr >();
                        break;

                    case 138:  // RelationType
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

                    case 134:  // Types
                    case 142:  // FunctionParameters
                    case 143:  // MaybeFunctionParameters
                        yylhs.value.build< Types::Ptr >();
                        break;

                    case 126:  // UndefinedLiteral
                        yylhs.value.build< UndefAtom::Ptr >();
                        break;

                    case 121:  // UniversalQuantifierExpression
                        yylhs.value.build< UniversalQuantifierExpression::Ptr >();
                        break;

                    case 108:  // UpdateRule
                    case 149:  // Initializer
                        yylhs.value.build< UpdateRule::Ptr >();
                        break;

                    case 127:  // BooleanLiteral
                    case 128:  // IntegerLiteral
                    case 129:  // RationalLiteral
                    case 130:  // DecimalLiteral
                    case 131:  // BitLiteral
                    case 132:  // StringLiteral
                        yylhs.value.build< ValueAtom::Ptr >();
                        break;

                    case 154:  // Variable
                    case 155:  // TypedVariable
                    case 156:  // AttributedVariable
                    case 157:  // TypedAttributedVariable
                        yylhs.value.build< VariableDefinition::Ptr >();
                        break;

                    case 135:  // Type
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
#line 377 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            specification.setHeader(
                                yystack_[ 1 ].value.as< HeaderDefinition::Ptr >() );
                            specification.setDefinitions(
                                yystack_[ 0 ].value.as< Definitions::Ptr >() );
                        }
#line 1380 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 3:
#line 386 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 392 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< HeaderDefinition::Ptr >() =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                        }
#line 1398 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 5:
#line 400 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = yystack_[ 1 ].value.as< Definitions::Ptr >();
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1408 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 6:
#line 406 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = Ast::make< Definitions >( yylhs.location );
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1418 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 7:
#line 416 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition = yystack_[ 0 ].value.as< Definition::Ptr >();
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< Definition::Ptr >() = definition;
                        }
#line 1428 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 8:
#line 422 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< Definition::Ptr >();
                        }
#line 1436 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 9:
#line 426 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() = nullptr;
                        }
#line 1444 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 10:
#line 434 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< EnumerationDefinition::Ptr >();
                        }
#line 1452 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 11:
#line 438 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< DerivedDefinition::Ptr >();
                        }
#line 1460 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 12:
#line 442 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< RuleDefinition::Ptr >();
                        }
#line 1468 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 13:
#line 446 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< FunctionDefinition::Ptr >();
                        }
#line 1476 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 14:
#line 454 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 462 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 470 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 475 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 484 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 500 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FunctionDefinition::Ptr >() =
                                yystack_[ 0 ]
                                    .value.as< FunctionDefinition::Ptr >();  // `init` special case
                        }
#line 1538 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 20:
#line 508 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 531 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 548 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() =
                                Ast::make< EnumeratorDefinition >(
                                    yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 1590 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 23:
#line 552 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 558 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = nullptr;
                        }
#line 1608 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 25:
#line 566 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = yystack_[ 2 ].value.as< Enumerators::Ptr >();
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1618 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 26:
#line 572 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = Ast::make< Enumerators >( yylhs.location );
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1628 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 27:
#line 586 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SkipRule::Ptr >();
                        }
#line 1636 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 28:
#line 590 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalRule::Ptr >();
                        }
#line 1644 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 29:
#line 594 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CaseRule::Ptr >();
                        }
#line 1652 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 30:
#line 598 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< LetRule::Ptr >();
                        }
#line 1660 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 31:
#line 602 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ForallRule::Ptr >();
                        }
#line 1668 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 32:
#line 606 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseRule::Ptr >();
                        }
#line 1676 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 33:
#line 610 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< IterateRule::Ptr >();
                        }
#line 1684 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 34:
#line 614 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< BlockRule::Ptr >();
                        }
#line 1692 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 35:
#line 618 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SequenceRule::Ptr >();
                        }
#line 1700 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 36:
#line 622 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRule::Ptr >();
                        }
#line 1708 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 37:
#line 626 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CallRule::Ptr >();
                        }
#line 1716 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 38:
#line 634 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = yystack_[ 1 ].value.as< Rules::Ptr >();
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1726 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 39:
#line 640 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = Ast::make< Rules >( yylhs.location );
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1736 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 40:
#line 650 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SkipRule::Ptr >() =
                                Ast::make< SkipRule >( yylhs.location );
                        }
#line 1744 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 41:
#line 658 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1752 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 42:
#line 662 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 670 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = Ast::make< CaseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Cases::Ptr >() );
                        }
#line 1768 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 44:
#line 674 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = nullptr;
                        }
#line 1776 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 45:
#line 682 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1784 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 46:
#line 686 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1792 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 47:
#line 690 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< ExpressionCase >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1800 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 48:
#line 698 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = yystack_[ 1 ].value.as< Cases::Ptr >();
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1810 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 49:
#line 704 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = Ast::make< Cases >( yylhs.location );
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1820 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 50:
#line 714 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 722 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 726 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 734 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 742 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IterateRule::Ptr >() = Ast::make< IterateRule >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1860 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 55:
#line 750 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1868 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 56:
#line 754 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1876 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 57:
#line 758 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1885 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 58:
#line 763 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1894 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 59:
#line 772 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1902 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 60:
#line 776 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1910 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 61:
#line 780 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1919 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 62:
#line 785 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1928 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 63:
#line 794 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 804 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 1946 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 65:
#line 808 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 1954 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 66:
#line 812 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 1962 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 67:
#line 816 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 1970 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 68:
#line 828 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto expressions = yystack_[ 2 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 1980 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 69:
#line 834 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 1990 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 70:
#line 844 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 1998 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 71:
#line 848 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TypeCastingExpression::Ptr >();
                        }
#line 2006 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 72:
#line 852 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< CallExpression::Ptr >();
                        }
#line 2014 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 73:
#line 856 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LetExpression::Ptr >();
                        }
#line 2022 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 74:
#line 860 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalExpression::Ptr >();
                        }
#line 2030 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 75:
#line 864 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseExpression::Ptr >();
                        }
#line 2038 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 76:
#line 868 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UniversalQuantifierExpression::Ptr >();
                        }
#line 2046 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 77:
#line 872 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ExistentialQuantifierExpression::Ptr >();
                        }
#line 2054 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 78:
#line 876 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ListExpression::Ptr >();
                        }
#line 2062 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 79:
#line 880 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< RangeExpression::Ptr >();
                        }
#line 2070 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 80:
#line 884 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2078 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 81:
#line 896 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2086 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 82:
#line 900 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = nullptr;
                        }
#line 2094 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 83:
#line 904 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2102 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 84:
#line 908 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::INV_INSTRUCTION );
                        }
#line 2110 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 85:
#line 912 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::ADD_INSTRUCTION );
                        }
#line 2118 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 86:
#line 916 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::SUB_INSTRUCTION );
                        }
#line 2126 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 87:
#line 920 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MUL_INSTRUCTION );
                        }
#line 2134 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 88:
#line 924 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::DIV_INSTRUCTION );
                        }
#line 2142 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 89:
#line 928 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MOD_INSTRUCTION );
                        }
#line 2150 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 90:
#line 932 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::POW_INSTRUCTION );
                        }
#line 2158 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 91:
#line 936 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NEQ_INSTRUCTION );
                        }
#line 2166 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 92:
#line 940 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::EQU_INSTRUCTION );
                        }
#line 2174 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 93:
#line 944 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LTH_INSTRUCTION );
                        }
#line 2182 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 94:
#line 948 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GTH_INSTRUCTION );
                        }
#line 2190 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 95:
#line 952 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LEQ_INSTRUCTION );
                        }
#line 2198 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 96:
#line 956 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GEQ_INSTRUCTION );
                        }
#line 2206 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 97:
#line 960 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::OR_INSTRUCTION );
                        }
#line 2214 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 98:
#line 964 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::XOR_INSTRUCTION );
                        }
#line 2222 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 99:
#line 968 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::AND_INSTRUCTION );
                        }
#line 2230 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 100:
#line 972 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2238 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 101:
#line 976 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2246 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 102:
#line 980 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NOT_INSTRUCTION );
                        }
#line 2254 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 103:
#line 988 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TypeCastingExpression::Ptr >() =
                                Ast::make< TypeCastingExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2262 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 104:
#line 996 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallExpression::Ptr >() =
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >();
                        }
#line 2270 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 105:
#line 1000 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallExpression::Ptr >() =
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >();
                        }
#line 2278 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 106:
#line 1004 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallExpression::Ptr >() =
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >();
                        }
#line 2286 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 107:
#line 1012 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2295 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 108:
#line 1017 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2303 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 109:
#line 1025 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IndirectCallExpression::Ptr >() =
                                Ast::make< IndirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2311 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 110:
#line 1033 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2320 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 111:
#line 1038 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 3 ].value.as< Expression::Ptr >(),
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2329 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 112:
#line 1043 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1053 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1061 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1069 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1077 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1085 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1093 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< ListExpression::Ptr >() =
                                Ast::make< ListExpression >( yylhs.location, expressions );
                        }
#line 2388 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 119:
#line 1098 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListExpression::Ptr >() = Ast::make< ListExpression >(
                                yylhs.location, yystack_[ 1 ].value.as< Expressions::Ptr >() );
                        }
#line 2396 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 120:
#line 1102 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListExpression::Ptr >() = nullptr;
                        }
#line 2404 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 121:
#line 1110 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RangeExpression::Ptr >() = Ast::make< RangeExpression >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Expression::Ptr >() );
                        }
#line 2412 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 122:
#line 1122 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UndefAtom::Ptr >();
                        }
#line 2420 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 123:
#line 1126 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2428 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 124:
#line 1130 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2436 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 125:
#line 1134 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2444 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 126:
#line 1138 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2452 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 127:
#line 1142 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2460 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 128:
#line 1146 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2468 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 129:
#line 1150 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ReferenceAtom::Ptr >();
                        }
#line 2476 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 130:
#line 1158 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UndefAtom::Ptr >() =
                                Ast::make< UndefAtom >( yylhs.location );
                        }
#line 2484 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 131:
#line 1166 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
                            yylhs.value.as< ValueAtom::Ptr >() =
                                Ast::make< ValueAtom >( yylhs.location, value );
                        }
#line 2493 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 132:
#line 1171 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
                            yylhs.value.as< ValueAtom::Ptr >() =
                                Ast::make< ValueAtom >( yylhs.location, value );
                        }
#line 2502 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 133:
#line 1180 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1196 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1212 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1228 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value = libstdhl::Memory::get< libcasm_ir::BitConstant >(
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
#line 1240 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            try
                            {
                                const auto value = libstdhl::Memory::get< libcasm_ir::BitConstant >(
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
#line 1256 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1272 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ReferenceAtom::Ptr >() = Ast::make< ReferenceAtom >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2606 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 140:
#line 1284 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2616 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 141:
#line 1290 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2626 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 142:
#line 1300 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< BasicType::Ptr >();
                        }
#line 2634 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 143:
#line 1304 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2642 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 144:
#line 1308 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< RelationType::Ptr >();
                        }
#line 2650 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 145:
#line 1312 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< FixedSizedType::Ptr >();
                        }
#line 2658 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 146:
#line 1320 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicType::Ptr >() = Ast::make< BasicType >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2666 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 147:
#line 1328 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ComposedType::Ptr >() = Ast::make< ComposedType >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 1 ].value.as< Types::Ptr >() );
                        }
#line 2674 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 148:
#line 1336 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1344 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FixedSizedType::Ptr >() = Ast::make< FixedSizedType >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2690 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 150:
#line 1356 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() =
                                yystack_[ 1 ].value.as< Expressions::Ptr >();
                        }
#line 2698 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 151:
#line 1360 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() = nullptr;
                        }
#line 2706 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 152:
#line 1364 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2715 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 153:
#line 1373 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = yystack_[ 3 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 1 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2725 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 154:
#line 1387 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2735 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 155:
#line 1393 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2745 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 156:
#line 1403 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = yystack_[ 0 ].value.as< Types::Ptr >();
                        }
#line 2753 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 157:
#line 1407 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = Ast::make< Types >( yylhs.location );
                        }
#line 2761 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 158:
#line 1415 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >();
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2771 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 159:
#line 1421 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2781 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 160:
#line 1431 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< VariableDefinition >::Ptr >();
                        }
#line 2789 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 161:
#line 1435 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = nullptr;
                        }
#line 2797 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 162:
#line 1439 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                        }
#line 2805 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 163:
#line 1451 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2813 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 164:
#line 1455 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                Ast::make< UndefAtom >( yylhs.location );
                        }
#line 2821 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 165:
#line 1463 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2829 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 166:
#line 1467 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2837 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 167:
#line 1475 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                yystack_[ 2 ].value.as< NodeList< UpdateRule >::Ptr >();
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2847 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 168:
#line 1481 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2857 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 169:
#line 1491 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1499 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1509 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1520 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 0 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2902 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 173:
#line 1524 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2910 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 174:
#line 1536 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() = Ast::make< Identifier >(
                                yylhs.location, yystack_[ 0 ].value.as< std::string >() );
                        }
#line 2918 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 175:
#line 1540 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() =
                                Ast::make< Identifier >( yylhs.location, "in" );
                        }
#line 2926 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 176:
#line 1548 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Identifiers::Ptr >(),
                                IdentifierPath::Type::ABSOLUTE );
                        }
#line 2934 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 177:
#line 1552 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
                        }
#line 2944 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 178:
#line 1562 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = yystack_[ 2 ].value.as< Identifiers::Ptr >();
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2954 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 179:
#line 1568 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2964 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 180:
#line 1582 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 2972 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 181:
#line 1586 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1595 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1603 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 2999 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 184:
#line 1609 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3007 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 185:
#line 1617 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3017 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 186:
#line 1623 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3025 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 187:
#line 1635 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = yystack_[ 2 ].value.as< Attributes::Ptr >();
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3035 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 188:
#line 1641 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = Ast::make< Attributes >( yylhs.location );
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3045 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 189:
#line 1650 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< BasicAttribute::Ptr >();
                        }
#line 3053 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 190:
#line 1654 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< ExpressionAttribute::Ptr >();
                        }
#line 3061 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 191:
#line 1662 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicAttribute::Ptr >() = Ast::make< BasicAttribute >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 3069 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 192:
#line 1670 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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

    const short int Parser::yypact_ninf_ = -162;

    const short int Parser::yytable_ninf_ = -156;

    const short int Parser::yypact_[] = {
        -1,   -162, 4,    23,   158,  -162, -162, 993,  44,   -162, -162, -162, -162, -162, -6,
        4,    4,    4,    4,    4,    125,  -162, -162, -162, -162, -162, -162, -162, -5,   -5,
        -5,   993,  -5,   -162, -162, -162, 993,  993,  993,  520,  582,  -3,   4,    -162, -162,
        -162, -162, -162, -162, 1810, -162, -162, -162, -162, -162, -162, -162, -162, -162, -162,
        -162, -162, -162, -162, -162, -162, -162, -162, -162, -162, -162, -162, 5,    36,   4,
        1055, 4,    -162, -162, -11,  8,    17,   8,    19,   74,   -162, 4,    20,   -162, -162,
        41,   70,   71,   1327, 79,   66,   66,   66,   53,   993,  1546, 88,   -162, 114,  1579,
        -162, -162, -3,   993,  993,  993,  993,  993,  993,  993,  993,  993,  993,  993,  993,
        993,  4,    993,  993,  993,  993,  644,  -162, -162, -162, 520,  1612, 75,   115,  -162,
        121,  -162, 4,    2,    117,  131,  -26,  -3,   194,  130,  -3,   993,  993,  993,  993,
        993,  -162, 1645, -162, -162, -162, 993,  993,  -162, -162, -162, -162, -162, 60,   1926,
        1876, 1904, 1843, 116,  116,  1945, 95,   95,   -54,  -54,  -54,  66,   5,    1843, 1945,
        95,   95,   143,  -162, -10,  1810, 134,  1546, 993,  993,  1055, -162, -162, 147,  4,
        1,    20,   -162, -162, -3,   9,    909,  -3,   -162, 149,  140,  -162, 4,    -162, 1101,
        1475, 1212, 1402, 1513, 5,    1810, 1678, -3,   993,  -162, -162, -162, 993,  1810, 1810,
        -162, -162, 142,  -162, -2,   165,  -162, 4,    -162, -31,  -162, 682,  721,  -162, -5,
        -5,   -5,   909,  -4,   993,  993,  156,  755,  791,  -162, -162, -162, -162, -162, -162,
        -162, -162, -162, -162, -162, -162, 148,  -162, 176,  -3,   -3,   -162, 993,  993,  993,
        993,  993,  -162, -162, -17,  -29,  157,  -162, 1711, 4,    -162, 993,  144,  -162, 9,
        209,  -162, 360,  208,  827,  180,  207,  210,  -162, -162, -162, 1364, 1435, 179,  861,
        160,  875,  993,  909,  -162, 221,  1810, 1810, 1810, 1810, 1810, -3,   -162, -3,   -162,
        -162, 1810, 4,    -162, -162, -162, -162, -162, -162, 993,  993,  993,  909,  185,  -162,
        -162, -162, -162, 1810, -162, 186,  226,  -162, 181,  -162, 1134, 1173, 1251, 214,  458,
        993,  192,  -162, -162, 909,  909,  993,  909,  909,  195,  191,  193,  -162, 931,  1744,
        1777, 1055, -162, -162, 1290, -162, -162, -162, 909,  909,  -162, -162, 909,  -162, 196,
        909,  -162, -162, -162, -162, -162
    };

    const unsigned char Parser::yydefact_[] = {
        0,   4,   0,   0,   0,   175, 174, 191, 0,   188, 189, 190, 1,   9,   0,   0,   0,   0,
        0,   0,   0,   6,   8,   10,  11,  12,  13,  19,  0,   0,   0,   0,   0,   130, 132, 131,
        0,   0,   0,   0,   0,   0,   0,   136, 137, 133, 134, 135, 138, 192, 70,  71,  72,  104,
        105, 106, 73,  74,  75,  76,  77,  78,  79,  80,  122, 123, 124, 125, 126, 127, 128, 129,
        107, 0,   0,   173, 0,   179, 20,  176, 162, 0,   162, 0,   0,   5,   0,   181, 184, 180,
        0,   0,   0,   0,   0,   102, 83,  84,  0,   0,   0,   0,   118, 0,   69,  139, 112, 0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   108, 3,   187, 0,   169, 0,   172, 168, 0,   177, 0,   0,   0,   0,   0,   157, 0,
        0,   0,   0,   0,   0,   0,   0,   82,  0,   81,  120, 119, 0,   0,   103, 142, 143, 144,
        145, 146, 99,  97,  98,  101, 85,  86,  92,  93,  94,  87,  88,  89,  90,  110, 100, 91,
        95,  96,  0,   152, 0,   69,  0,   69,  0,   0,   0,   21,  178, 0,   0,   0,   0,   186,
        159, 0,   0,   0,   0,   155, 156, 0,   7,   0,   182, 0,   0,   0,   0,   0,   0,   68,
        0,   157, 0,   111, 151, 150, 0,   170, 171, 167, 161, 0,   160, 0,   0,   24,  0,   26,
        0,   22,  0,   0,   40,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   16,  27,  28,
        29,  30,  31,  32,  33,  34,  35,  36,  37,  66,  67,  0,   0,   0,   183, 0,   0,   0,
        0,   0,   109, 121, 0,   141, 0,   149, 68,  0,   158, 0,   0,   14,  0,   0,   39,  0,
        0,   0,   0,   0,   0,   54,  64,  65,  0,   0,   0,   0,   0,   0,   0,   0,   154, 164,
        113, 116, 115, 114, 117, 0,   147, 0,   153, 185, 15,  0,   25,  62,  60,  38,  58,  56,
        0,   0,   0,   0,   0,   57,  55,  61,  59,  63,  17,  0,   166, 140, 0,   23,  0,   0,
        0,   41,  0,   0,   0,   18,  148, 0,   0,   0,   0,   0,   0,   0,   0,   49,  0,   0,
        0,   173, 50,  51,  0,   53,  42,  44,  0,   0,   43,  48,  0,   163, 0,   0,   45,  46,
        47,  165, 52
    };

    const short int Parser::yypgoto_[] = {
        -162, -162, -162, -162, 229,  103,  -162, -162, -162, -162, -162, -33,  -162, -143,
        -154, -162, -162, -162, -106, -162, -162, -162, -162, -162, -162, -162, -162, -162,
        -69,  -7,   -162, -162, -162, 67,   98,   -162, -162, -162, -162, -162, -162, -162,
        -162, -162, -162, -162, -162, -162, -162, -162, -162, -162, -162, -117, -162, -162,
        -162, -162, -161, -162, -162, 37,   -162, 171,  -162, -162, -162, 68,   -105, 48,
        6,    -162, 50,   -134, -23,  30,   -18,  197,  -162, -162
    };

    const short int Parser::yydefgoto_[] = {
        -1,  3,   4,   20,  21,  22,  23,  24,  25,  26,  27,  233, 234, 286, 287, 250,
        251, 252, 357, 358, 253, 254, 255, 256, 257, 258, 259, 260, 103, 131, 50,  51,
        52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,
        68,  69,  70,  71,  274, 158, 159, 160, 161, 162, 127, 132, 204, 205, 195, 139,
        336, 347, 133, 134, 135, 72,  163, 79,  88,  89,  90,  198, 8,   9,   10,  11
    };

    const short int Parser::yytable_[] = {
        49,  84,  1,   193, 197, 120, 91,  92,  121, 94,   231, 5,   5,   5,   5,   5,   219,  201,
        283, 5,   78,  5,   284, 12,  93,  203, 5,   -155, 208, 95,  96,  97,  100, 104, -155, 221,
        311, 202, 312, 128, 246, 86,  75,  156, 194, 2,    228, 105, 194, 126, 7,   137, 138,  272,
        229, 232, 76,  184, 249, 76,  140, 186, 77,  80,   81,  82,  83,  7,   144, 142, 145,  6,
        6,   6,   6,   6,   87,  87,  87,  6,   87,  6,    230, 289, 146, 263, 6,   147, 148,  77,
        106, 73,  152, 299, 301, 197, 150, 74,  151, 293,  275, 164, 165, 166, 167, 168, 169,  170,
        171, 172, 173, 174, 175, 176, 217, 178, 179, 180,  181, 185, 218, 143, 7,   187, 136,  -2,
        13,  74,  121, 14,  15,  16,  17,  18,  7,   154,  112, 113, 189, 209, 210, 211, 212,  213,
        321, 315, 321, 304, 305, 215, 216, 117, 118, 119,  120, 77,  321, 121, 321, 13,  334,  155,
        14,  15,  16,  17,  18,  156, 190, 177, 191, 19,   117, 118, 119, 120, 227, 207, 121,  200,
        199, 223, 224, 74,  343, 192, 196, 222, 220, 279,  77,  317, 226, 77,  337, 74,  338,  74,
        14,  15,  16,  17,  18,  265, 19,  264, 362, 363,  281, 365, 366, 277, 99,  302, 282,  278,
        290, 291, 292, 303, 313, 319, 322, 324, 325, 376,  377, 326, 329, 378, 331, 335, 380,  344,
        345, 346, 348, 296, 297, 353, 361, 368, 7,   369,  367, 379, 206, 77,  235, 85,  77,   318,
        371, 141, 276, 87,  374, 266, 225, 280, 306, 307,  308, 309, 310, 77,  0,   0,   261,  0,
        0,   129, 0,   0,   316, 0,   0,   196, 0,   0,    7,   0,   0,   0,   0,   0,   0,    87,
        87,  87,  0,   0,   0,   0,   0,   333, 0,   0,    0,   262, 0,   0,   0,   261, 261,  0,
        0,   0,   0,   261, 294, 0,   77,  77,  261, 261,  0,   340, 341, 342, 0,   0,   0,    0,
        0,   0,   0,   196, 0,   0,   0,   0,   235, 0,    262, 262, 0,   359, 360, 0,   262,  295,
        0,   0,   364, 262, 262, 0,   0,   0,   0,   359,  0,   0,   261, 0,   261, 0,   0,    77,
        0,   77,  0,   0,   0,   339, 261, 0,   261, 0,    261, 236, 320, 237, 0,   238, 239,  5,
        240, 241, 242, 0,   243, 244, 0,   262, 245, 262,  0,   0,   0,   0,   0,   0,   261,  0,
        0,   262, 0,   262, 0,   262, 0,   0,   246, 0,    0,   0,   247, 0,   0,   0,   0,    0,
        0,   0,   261, 261, 0,   261, 261, 0,   0,   0,    0,   262, 0,   0,   0,   248, 0,    0,
        0,   0,   0,   261, 261, 6,   0,   261, 0,   0,    261, 0,   0,   0,   0,   262, 262,  0,
        262, 262, 0,   0,   0,   0,   0,   0,   0,   354,  0,   0,   0,   0,   0,   0,   262,  262,
        0,   0,   262, 0,   0,   262, 28,  5,   29,  30,   0,   0,   0,   31,  0,   0,   0,    0,
        355, 0,   32,  0,   0,   33,  34,  35,  0,   0,    0,   0,   36,  37,  38,  0,   39,   0,
        40,  0,   0,   0,   0,   356, 41,  0,   0,   0,    0,   0,   0,   0,   0,   0,   42,   98,
        0,   0,   0,   0,   0,   0,   0,   43,  44,  45,   46,  47,  48,  6,   28,  5,   29,   30,
        0,   0,   0,   31,  0,   0,   0,   0,   0,   0,    32,  0,   0,   33,  34,  35,  0,    0,
        0,   0,   36,  37,  38,  0,   39,  0,   40,  0,    0,   0,   0,   0,   41,  0,   0,    0,
        99,  0,   0,   0,   0,   0,   42,  101, 0,   0,    0,   0,   0,   0,   0,   43,  44,   45,
        46,  47,  48,  6,   28,  5,   29,  30,  0,   0,    0,   31,  0,   0,   0,   0,   0,    0,
        32,  0,   0,   33,  34,  35,  0,   0,   0,   0,    36,  37,  38,  0,   39,  0,   40,   102,
        0,   0,   0,   0,   41,  0,   0,   0,   0,   0,    0,   0,   0,   0,   42,  182, 0,    0,
        0,   0,   0,   0,   0,   43,  44,  45,  46,  47,   48,  6,   28,  5,   29,  30,  0,    0,
        0,   31,  0,   0,   0,   0,   0,   0,   32,  0,    0,   33,  34,  35,  0,   0,   0,    285,
        36,  37,  38,  0,   39,  183, 40,  0,   0,   236,  0,   237, 41,  238, 239, 5,   240,  241,
        242, 0,   243, 244, 42,  0,   245, 0,   0,   0,    0,   0,   0,   43,  44,  45,  46,   47,
        48,  6,   288, 0,   0,   0,   246, 0,   0,   0,    247, 0,   236, 0,   237, 0,   238,  239,
        5,   240, 241, 242, 0,   243, 244, 0,   0,   245,  0,   0,   0,   248, 0,   0,   0,    0,
        298, 0,   0,   6,   0,   0,   0,   0,   0,   246,  236, 0,   237, 247, 238, 239, 5,    240,
        241, 242, 0,   243, 244, 0,   0,   245, 0,   0,    0,   0,   0,   0,   0,   0,   248,  0,
        300, 0,   0,   0,   0,   0,   6,   246, 0,   0,    236, 247, 237, 0,   238, 239, 5,    240,
        241, 242, 0,   243, 244, 0,   0,   245, 0,   0,    0,   0,   0,   0,   248, 0,   0,    0,
        0,   0,   0,   0,   6,   0,   0,   246, 0,   0,    236, 247, 237, 323, 238, 239, 5,    240,
        241, 242, 0,   243, 244, 0,   0,   245, 0,   0,    0,   0,   0,   0,   248, 0,   0,    0,
        0,   0,   0,   0,   6,   0,   0,   246, 236, 0,    237, 247, 238, 239, 5,   240, 241,  242,
        0,   243, 244, 0,   236, 245, 237, 0,   238, 239,  5,   240, 241, 242, 248, 243, 244,  0,
        0,   245, 0,   0,   6,   246, 0,   0,   0,   247,  330, 0,   0,   0,   0,   0,   0,    0,
        0,   246, 236, 0,   237, 247, 238, 239, 5,   240,  241, 242, 248, 243, 244, 0,   0,    245,
        0,   0,   6,   0,   0,   0,   0,   0,   248, 332,  0,   28,  5,   29,  30,  0,   6,    246,
        31,  0,   0,   247, 0,   355, 0,   32,  0,   0,    33,  34,  35,  0,   0,   0,   0,    36,
        37,  38,  0,   39,  0,   40,  248, 0,   370, 0,    356, 41,  0,   0,   6,   0,   0,    0,
        0,   0,   0,   42,  0,   0,   0,   0,   0,   0,    0,   0,   43,  44,  45,  46,  47,   48,
        6,   28,  5,   29,  30,  0,   0,   0,   31,  0,    0,   0,   0,   0,   0,   32,  0,    0,
        33,  34,  35,  0,   0,   0,   0,   36,  37,  38,   0,   39,  0,   40,  0,   0,   0,    0,
        0,   41,  0,   0,   0,   0,   0,   0,   0,   0,    0,   42,  0,   0,   0,   0,   0,    0,
        0,   0,   43,  44,  45,  46,  47,  48,  6,   28,   5,   29,  30,  0,   0,   0,   31,   0,
        0,   0,   0,   0,   0,   32,  0,   0,   33,  34,   35,  0,   0,   0,   0,   36,  37,   38,
        0,   130, 0,   40,  0,   0,   0,   0,   0,   41,   0,   0,   0,   0,   0,   0,   0,    0,
        0,   42,  267, 0,   0,   0,   0,   0,   0,   0,    43,  44,  45,  46,  47,  48,  6,    107,
        0,   0,   0,   108, 109, 110, 111, 0,   112, 113,  114, 0,   0,   0,   0,   0,   0,    349,
        0,   0,   0,   115, 116, 117, 118, 119, 120, 0,    0,   121, 0,   122, 107, 123, 124,  125,
        108, 109, 110, 111, 0,   112, 113, 114, 0,   0,    0,   0,   0,   0,   0,   0,   0,    0,
        115, 116, 117, 118, 119, 120, 350, 0,   121, 0,    122, 0,   123, 124, 125, 0,   351,  107,
        0,   0,   0,   108, 109, 110, 111, 0,   112, 113,  114, 0,   0,   0,   0,   0,   0,    0,
        0,   0,   0,   115, 116, 117, 118, 119, 120, 269,  0,   121, 0,   122, 0,   123, 124,  125,
        0,   0,   107, 0,   0,   0,   108, 109, 110, 111,  0,   112, 113, 114, 0,   0,   0,    0,
        0,   0,   0,   0,   0,   0,   115, 116, 117, 118,  119, 120, 352, 0,   121, 0,   122,  0,
        123, 124, 125, 0,   0,   107, 0,   0,   0,   108,  109, 110, 111, 0,   112, 113, 114,  0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   115,  116, 117, 118, 119, 120, 375, 0,    121,
        0,   122, 0,   123, 124, 125, 0,   0,   107, 0,    0,   0,   108, 109, 110, 111, 0,    112,
        113, 114, 0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   115, 116, 117, 118, 119,  120,
        0,   149, 121, 0,   122, 0,   123, 124, 125, 107,  0,   0,   0,   108, 109, 110, 111,  0,
        112, 113, 114, 0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   115, 116, 117, 118,  119,
        120, 0,   327, 121, 0,   122, 0,   123, 124, 125,  107, 0,   0,   0,   108, 109, 110,  111,
        0,   112, 113, 114, 0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   115, 116, 117,  118,
        119, 120, 0,   0,   121, 270, 122, 0,   123, 124,  125, 0,   107, 0,   0,   0,   108,  109,
        110, 111, 0,   112, 113, 114, 0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   115,  116,
        117, 118, 119, 120, 328, 0,   121, 0,   122, 107,  123, 124, 125, 108, 109, 110, 111,  0,
        112, 113, 114, 0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   115, 116, 117, 118,  119,
        120, 0,   0,   121, 0,   122, 0,   123, 124, 125,  268, 0,   0,   107, 0,   0,   0,    108,
        109, 110, 111, 0,   112, 113, 114, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,    115,
        116, 117, 118, 119, 120, 0,   0,   121, 0,   122,  0,   123, 124, 125, 271, 107, 0,    0,
        0,   108, 109, 110, 111, 0,   112, 113, 114, 0,    0,   0,   0,   0,   0,   0,   0,    0,
        0,   115, 116, 117, 118, 119, 120, 0,   0,   121,  0,   122, 107, 123, 124, 125, 108,  109,
        110, 111, 0,   112, 113, 114, 0,   153, 0,   0,    0,   0,   0,   0,   0,   0,   115,  116,
        117, 118, 119, 120, 0,   0,   121, 0,   122, 107,  123, 124, 125, 108, 109, 110, 111,  0,
        112, 113, 114, 0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   115, 116, 117, 118,  119,
        120, 0,   157, 121, 0,   122, 107, 123, 124, 125,  108, 109, 110, 111, 0,   112, 113,  114,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    115, 116, 117, 118, 119, 120, 0,    0,
        121, 188, 122, 107, 123, 124, 125, 108, 109, 110,  111, 0,   112, 113, 114, 0,   214,  0,
        0,   0,   0,   0,   0,   0,   0,   115, 116, 117,  118, 119, 120, 0,   0,   121, 0,    122,
        107, 123, 124, 125, 108, 109, 110, 111, 0,   112,  113, 114, 0,   0,   0,   273, 0,    0,
        0,   0,   0,   0,   115, 116, 117, 118, 119, 120,  0,   0,   121, 0,   122, 107, 123,  124,
        125, 108, 109, 110, 111, 0,   112, 113, 114, 0,    314, 0,   0,   0,   0,   0,   0,    0,
        0,   115, 116, 117, 118, 119, 120, 0,   0,   121,  0,   122, 107, 123, 124, 125, 108,  109,
        110, 111, 0,   112, 113, 114, 0,   0,   0,   0,    0,   0,   372, 0,   0,   0,   115,  116,
        117, 118, 119, 120, 0,   0,   121, 0,   122, 107,  123, 124, 125, 108, 109, 110, 111,  0,
        112, 113, 114, 0,   0,   0,   0,   0,   373, 0,    0,   0,   0,   115, 116, 117, 118,  119,
        120, 0,   0,   121, 0,   122, 107, 123, 124, 125,  108, 109, 110, 111, 0,   112, 113,  114,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    115, 116, 117, 118, 119, 120, 0,    0,
        121, 0,   122, 0,   123, 124, 125, 108, 109, 110,  0,   0,   112, 113, 114, 0,   0,    0,
        0,   0,   0,   0,   0,   0,   0,   115, 116, 117,  118, 119, 120, 0,   0,   121, 0,    0,
        0,   123, 124, 125, 108, 0,   110, 0,   0,   112,  113, 114, 0,   0,   0,   0,   0,    0,
        0,   0,   0,   0,   115, 116, 117, 118, 119, 120,  0,   0,   121, 0,   108, 0,   123,  124,
        125, 112, 113, 114, 0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   115, 116, 117,  118,
        119, 120, 0,   0,   121, 112, 113, 114, 123, 124,  125, 0,   0,   0,   0,   0,   0,    0,
        115, 116, 117, 118, 119, 120, 112, 113, 121, 0,    0,   0,   123, 124, 125, 0,   0,    0,
        0,   115, 116, 117, 118, 119, 120, 0,   0,   121,  0,   0,   0,   0,   124, 125
    };

    const short int Parser::yycheck_[] = {
        7,   19,  3,   1,   138, 59,  29,  30,  62,  32,  1,   17,  17,  17,  17,  17,  177, 43,
        49,  17,  14,  17,  53,  0,   31,  142, 17,  56,  145, 36,  37,  38,  39,  40,  63,  45,
        53,  63,  55,  3,   44,  46,  48,  53,  46,  46,  45,  41,  46,  44,  2,   62,  44,  214,
        53,  46,  62,  126, 201, 62,  43,  130, 14,  15,  16,  17,  18,  19,  86,  50,  50,  77,
        77,  77,  77,  77,  28,  29,  30,  77,  32,  77,  199, 237, 43,  202, 77,  17,  17,  41,
        42,  47,  99,  247, 248, 229, 17,  53,  45,  242, 217, 108, 109, 110, 111, 112, 113, 114,
        115, 116, 117, 118, 119, 120, 54,  122, 123, 124, 125, 126, 60,  47,  74,  130, 76,  0,
        1,   53,  62,  4,   5,   6,   7,   8,   86,  47,  41,  42,  63,  146, 147, 148, 149, 150,
        287, 279, 289, 264, 265, 156, 157, 56,  57,  58,  59,  107, 299, 62,  301, 1,   303, 47,
        4,   5,   6,   7,   8,   53,  53,  121, 49,  46,  56,  57,  58,  59,  194, 47,  62,  48,
        63,  188, 189, 53,  327, 137, 138, 53,  45,  47,  142, 47,  45,  145, 311, 53,  313, 53,
        4,   5,   6,   7,   8,   63,  46,  56,  349, 350, 43,  352, 353, 218, 56,  65,  232, 222,
        239, 240, 241, 43,  63,  12,  14,  43,  17,  368, 369, 17,  49,  372, 70,  10,  375, 48,
        48,  9,   55,  244, 245, 25,  48,  50,  194, 50,  49,  49,  143, 199, 200, 20,  202, 284,
        358, 82,  217, 207, 361, 207, 190, 229, 267, 268, 269, 270, 271, 217, -1,  -1,  201, -1,
        -1,  74,  -1,  -1,  281, -1,  -1,  229, -1,  -1,  232, -1,  -1,  -1,  -1,  -1,  -1,  239,
        240, 241, -1,  -1,  -1,  -1,  -1,  302, -1,  -1,  -1,  201, -1,  -1,  -1,  236, 237, -1,
        -1,  -1,  -1,  242, 243, -1,  264, 265, 247, 248, -1,  324, 325, 326, -1,  -1,  -1,  -1,
        -1,  -1,  -1,  279, -1,  -1,  -1,  -1,  284, -1,  236, 237, -1,  344, 345, -1,  242, 243,
        -1,  -1,  351, 247, 248, -1,  -1,  -1,  -1,  358, -1,  -1,  287, -1,  289, -1,  -1,  311,
        -1,  313, -1,  -1,  -1,  317, 299, -1,  301, -1,  303, 11,  12,  13,  -1,  15,  16,  17,
        18,  19,  20,  -1,  22,  23,  -1,  287, 26,  289, -1,  -1,  -1,  -1,  -1,  -1,  327, -1,
        -1,  299, -1,  301, -1,  303, -1,  -1,  44,  -1,  -1,  -1,  48,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  349, 350, -1,  352, 353, -1,  -1,  -1,  -1,  327, -1,  -1,  -1,  69,  -1,  -1,
        -1,  -1,  -1,  368, 369, 77,  -1,  372, -1,  -1,  375, -1,  -1,  -1,  -1,  349, 350, -1,
        352, 353, -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,  -1,  -1,  -1,  368, 369,
        -1,  -1,  372, -1,  -1,  375, 16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,
        28,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,
        46,  -1,  -1,  -1,  -1,  51,  52,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  62,  1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,  77,  16,  17,  18,  19,
        -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,
        -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  52,  -1,  -1,  -1,
        56,  -1,  -1,  -1,  -1,  -1,  62,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,
        74,  75,  76,  77,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,
        30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  47,
        -1,  -1,  -1,  -1,  52,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  62,  1,   -1,  -1,
        -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,  77,  16,  17,  18,  19,  -1,  -1,
        -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  1,
        40,  41,  42,  -1,  44,  45,  46,  -1,  -1,  11,  -1,  13,  52,  15,  16,  17,  18,  19,
        20,  -1,  22,  23,  62,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,
        76,  77,  1,   -1,  -1,  -1,  44,  -1,  -1,  -1,  48,  -1,  11,  -1,  13,  -1,  15,  16,
        17,  18,  19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  -1,  -1,  69,  -1,  -1,  -1,  -1,
        1,   -1,  -1,  77,  -1,  -1,  -1,  -1,  -1,  44,  11,  -1,  13,  48,  15,  16,  17,  18,
        19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  69,  -1,
        1,   -1,  -1,  -1,  -1,  -1,  77,  44,  -1,  -1,  11,  48,  13,  -1,  15,  16,  17,  18,
        19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  69,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  77,  -1,  -1,  44,  -1,  -1,  11,  48,  13,  14,  15,  16,  17,  18,
        19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  69,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  77,  -1,  -1,  44,  11,  -1,  13,  48,  15,  16,  17,  18,  19,  20,
        -1,  22,  23,  -1,  11,  26,  13,  -1,  15,  16,  17,  18,  19,  20,  69,  22,  23,  -1,
        -1,  26,  -1,  -1,  77,  44,  -1,  -1,  -1,  48,  49,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  44,  11,  -1,  13,  48,  15,  16,  17,  18,  19,  20,  69,  22,  23,  -1,  -1,  26,
        -1,  -1,  77,  -1,  -1,  -1,  -1,  -1,  69,  70,  -1,  16,  17,  18,  19,  -1,  77,  44,
        23,  -1,  -1,  48,  -1,  28,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,
        41,  42,  -1,  44,  -1,  46,  69,  -1,  49,  -1,  51,  52,  -1,  -1,  77,  -1,  -1,  -1,
        -1,  -1,  -1,  62,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,
        77,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,
        33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,
        -1,  52,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  62,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  71,  72,  73,  74,  75,  76,  77,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,
        -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,
        -1,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  52,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  62,  17,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,  77,  32,
        -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  17,
        -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  62,  -1,  64,  32,  66,  67,  68,
        36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        54,  55,  56,  57,  58,  59,  21,  -1,  62,  -1,  64,  -1,  66,  67,  68,  -1,  31,  32,
        -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  21,  -1,  62,  -1,  64,  -1,  66,  67,  68,
        -1,  -1,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  21,  -1,  62,  -1,  64,  -1,
        66,  67,  68,  -1,  -1,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  21,  -1,  62,
        -1,  64,  -1,  66,  67,  68,  -1,  -1,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,
        42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,
        -1,  24,  62,  -1,  64,  -1,  66,  67,  68,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,
        41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,
        59,  -1,  24,  62,  -1,  64,  -1,  66,  67,  68,  32,  -1,  -1,  -1,  36,  37,  38,  39,
        -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,
        58,  59,  -1,  -1,  62,  25,  64,  -1,  66,  67,  68,  -1,  32,  -1,  -1,  -1,  36,  37,
        38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,
        56,  57,  58,  59,  27,  -1,  62,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,
        41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,
        59,  -1,  -1,  62,  -1,  64,  -1,  66,  67,  68,  29,  -1,  -1,  32,  -1,  -1,  -1,  36,
        37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,
        55,  56,  57,  58,  59,  -1,  -1,  62,  -1,  64,  -1,  66,  67,  68,  31,  32,  -1,  -1,
        -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  62,  -1,  64,  32,  66,  67,  68,  36,  37,
        38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,
        56,  57,  58,  59,  -1,  -1,  62,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,
        41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,
        59,  -1,  61,  62,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,
        62,  63,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  62,  -1,  64,
        32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  47,  -1,  -1,
        -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  62,  -1,  64,  32,  66,  67,
        68,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  62,  -1,  64,  32,  66,  67,  68,  36,  37,
        38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  50,  -1,  -1,  -1,  54,  55,
        56,  57,  58,  59,  -1,  -1,  62,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,
        41,  42,  43,  -1,  -1,  -1,  -1,  -1,  49,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,
        59,  -1,  -1,  62,  -1,  64,  32,  66,  67,  68,  36,  37,  38,  39,  -1,  41,  42,  43,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,
        62,  -1,  64,  -1,  66,  67,  68,  36,  37,  38,  -1,  -1,  41,  42,  43,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  62,  -1,  -1,
        -1,  66,  67,  68,  36,  -1,  38,  -1,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  62,  -1,  36,  -1,  66,  67,
        68,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  54,  55,  56,  57,
        58,  59,  -1,  -1,  62,  41,  42,  43,  66,  67,  68,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        54,  55,  56,  57,  58,  59,  41,  42,  62,  -1,  -1,  -1,  66,  67,  68,  -1,  -1,  -1,
        -1,  54,  55,  56,  57,  58,  59,  -1,  -1,  62,  -1,  -1,  -1,  -1,  67,  68
    };

    const unsigned char Parser::yystos_[] = {
        0,   3,   46,  83,  84,  17,  77,  151, 158, 159, 160, 161, 0,   1,   4,   5,   6,   7,
        8,   46,  85,  86,  87,  88,  89,  90,  91,  92,  16,  18,  19,  23,  30,  33,  34,  35,
        40,  41,  42,  44,  46,  52,  62,  71,  72,  73,  74,  75,  76,  111, 112, 113, 114, 115,
        116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133,
        151, 47,  53,  48,  62,  151, 152, 153, 151, 151, 151, 151, 158, 86,  46,  151, 154, 155,
        156, 156, 156, 111, 156, 111, 111, 111, 1,   56,  111, 1,   47,  110, 111, 152, 151, 32,
        36,  37,  38,  39,  41,  42,  43,  54,  55,  56,  57,  58,  59,  62,  64,  66,  67,  68,
        44,  140, 3,   159, 44,  111, 141, 148, 149, 150, 151, 62,  44,  145, 43,  145, 50,  47,
        158, 50,  43,  17,  17,  24,  17,  45,  111, 45,  47,  47,  53,  61,  135, 136, 137, 138,
        139, 152, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 151, 111, 111,
        111, 111, 1,   45,  110, 111, 110, 111, 63,  63,  53,  49,  151, 1,   46,  144, 151, 155,
        157, 63,  48,  43,  63,  135, 142, 143, 87,  47,  135, 111, 111, 111, 111, 111, 45,  111,
        111, 54,  60,  140, 45,  45,  53,  111, 111, 149, 45,  158, 45,  53,  135, 1,   46,  93,
        94,  151, 11,  13,  15,  16,  18,  19,  20,  22,  23,  26,  44,  48,  69,  95,  97,  98,
        99,  102, 103, 104, 105, 106, 107, 108, 109, 115, 116, 135, 56,  63,  154, 17,  29,  21,
        25,  31,  140, 47,  134, 135, 143, 111, 111, 47,  157, 43,  158, 49,  53,  1,   95,  96,
        1,   96,  156, 156, 156, 95,  115, 116, 111, 111, 1,   96,  1,   96,  65,  43,  135, 135,
        111, 111, 111, 111, 111, 53,  55,  63,  45,  155, 111, 47,  93,  12,  12,  95,  14,  14,
        43,  17,  17,  24,  27,  49,  49,  70,  70,  111, 95,  10,  146, 135, 135, 151, 111, 111,
        111, 95,  48,  48,  9,   147, 55,  17,  21,  31,  21,  25,  1,   28,  51,  100, 101, 111,
        111, 48,  95,  95,  111, 95,  95,  49,  50,  50,  49,  100, 50,  49,  150, 21,  95,  95,
        95,  49,  95
    };

    const unsigned char Parser::yyr1_[] = {
        0,   82,  83,  84,  84,  85,  85,  86,  86,  86,  87,  87,  87,  87,  88,  89,  90,  90,
        91,  91,  92,  92,  93,  93,  93,  94,  94,  95,  95,  95,  95,  95,  95,  95,  95,  95,
        95,  95,  96,  96,  97,  98,  98,  99,  99,  100, 100, 100, 101, 101, 102, 103, 103, 104,
        105, 106, 106, 106, 106, 107, 107, 107, 107, 108, 109, 109, 109, 109, 110, 110, 111, 111,
        111, 111, 111, 111, 111, 111, 111, 111, 111, 112, 112, 112, 112, 112, 112, 112, 112, 112,
        112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 113, 114, 114, 114, 115,
        115, 116, 117, 117, 117, 118, 119, 120, 121, 122, 123, 123, 123, 124, 125, 125, 125, 125,
        125, 125, 125, 125, 126, 127, 127, 128, 129, 130, 131, 131, 132, 133, 134, 134, 135, 135,
        135, 135, 136, 137, 138, 139, 140, 140, 140, 141, 142, 142, 143, 143, 144, 144, 145, 145,
        145, 146, 146, 147, 147, 148, 148, 149, 149, 149, 150, 150, 151, 151, 152, 152, 153, 153,
        154, 154, 155, 156, 156, 157, 157, 158, 158, 159, 159, 160, 161
    };

    const unsigned char Parser::yyr2_[] = {
        0, 2, 2, 4, 1, 2, 1, 4, 1, 1, 1, 1, 1, 1, 6, 7, 5, 7, 8, 1, 2, 4, 1, 4, 1, 3, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 4, 6, 6, 6, 3, 3, 3, 2, 1, 6, 6, 8, 6, 2, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 2,
        2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 1, 1, 1, 1, 2, 5, 3, 4,
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
                                             "BitLiteral",
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
        0,    376,  376,  385,  391,  399,  405,  415,  421,  425,  433,  437,  441,  445,  453,
        461,  469,  474,  483,  499,  507,  530,  547,  551,  557,  565,  571,  585,  589,  593,
        597,  601,  605,  609,  613,  617,  621,  625,  633,  639,  649,  657,  661,  669,  673,
        681,  685,  689,  697,  703,  713,  721,  725,  733,  741,  749,  753,  757,  762,  771,
        775,  779,  784,  793,  803,  807,  811,  815,  827,  833,  843,  847,  851,  855,  859,
        863,  867,  871,  875,  879,  883,  895,  899,  903,  907,  911,  915,  919,  923,  927,
        931,  935,  939,  943,  947,  951,  955,  959,  963,  967,  971,  975,  979,  987,  995,
        999,  1003, 1011, 1016, 1024, 1032, 1037, 1042, 1052, 1060, 1068, 1076, 1084, 1092, 1097,
        1101, 1109, 1121, 1125, 1129, 1133, 1137, 1141, 1145, 1149, 1157, 1165, 1170, 1179, 1195,
        1211, 1227, 1239, 1255, 1271, 1283, 1289, 1299, 1303, 1307, 1311, 1319, 1327, 1335, 1343,
        1355, 1359, 1363, 1372, 1386, 1392, 1402, 1406, 1414, 1420, 1430, 1434, 1438, 1450, 1454,
        1462, 1466, 1474, 1480, 1490, 1498, 1508, 1519, 1523, 1535, 1539, 1547, 1551, 1561, 1567,
        1581, 1585, 1594, 1602, 1608, 1616, 1622, 1634, 1640, 1649, 1653, 1661, 1669
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
#line 4064 "GrammarParser.cpp"               // lalr1.cc:1167
#line 1675 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1168

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
