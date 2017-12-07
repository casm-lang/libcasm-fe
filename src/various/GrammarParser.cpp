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
            case 160:  // Attribute
                value.move< Attribute::Ptr >( that.value );
                break;

            case 159:  // Attributes
                value.move< Attributes::Ptr >( that.value );
                break;

            case 161:  // BasicAttribute
                value.move< BasicAttribute::Ptr >( that.value );
                break;

            case 137:  // BasicType
                value.move< BasicType::Ptr >( that.value );
                break;

            case 107:  // BlockRule
                value.move< BlockRule::Ptr >( that.value );
                break;

            case 110:  // CallRule
                value.move< CallRule::Ptr >( that.value );
                break;

            case 101:  // CaseLabel
                value.move< Case::Ptr >( that.value );
                break;

            case 100:  // CaseRule
                value.move< CaseRule::Ptr >( that.value );
                break;

            case 102:  // CaseLabels
                value.move< Cases::Ptr >( that.value );
                break;

            case 121:  // ChooseExpression
                value.move< ChooseExpression::Ptr >( that.value );
                break;

            case 105:  // ChooseRule
                value.move< ChooseRule::Ptr >( that.value );
                break;

            case 138:  // ComposedType
                value.move< ComposedType::Ptr >( that.value );
                break;

            case 120:  // ConditionalExpression
                value.move< ConditionalExpression::Ptr >( that.value );
                break;

            case 99:  // ConditionalRule
                value.move< ConditionalRule::Ptr >( that.value );
                break;

            case 87:  // AttributedDefinition
            case 88:  // Definition
                value.move< Definition::Ptr >( that.value );
                break;

            case 86:  // Definitions
                value.move< Definitions::Ptr >( that.value );
                break;

            case 90:  // DerivedDefinition
                value.move< DerivedDefinition::Ptr >( that.value );
                break;

            case 116:  // DirectCallExpression
                value.move< DirectCallExpression::Ptr >( that.value );
                break;

            case 89:  // EnumerationDefinition
                value.move< EnumerationDefinition::Ptr >( that.value );
                break;

            case 94:  // EnumeratorDefinition
                value.move< EnumeratorDefinition::Ptr >( that.value );
                break;

            case 95:  // Enumerators
                value.move< Enumerators::Ptr >( that.value );
                break;

            case 123:  // ExistentialQuantifierExpression
                value.move< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 112:  // Term
            case 113:  // SimpleOrClaspedTerm
            case 114:  // Expression
            case 126:  // Literal
            case 147:  // MaybeDefined
                value.move< Expression::Ptr >( that.value );
                break;

            case 162:  // ExpressionAttribute
                value.move< ExpressionAttribute::Ptr >( that.value );
                break;

            case 111:  // Terms
            case 141:  // Arguments
            case 142:  // TwoOrMoreArguments
                value.move< Expressions::Ptr >( that.value );
                break;

            case 140:  // FixedSizedType
                value.move< FixedSizedType::Ptr >( that.value );
                break;

            case 104:  // ForallRule
                value.move< ForallRule::Ptr >( that.value );
                break;

            case 92:  // FunctionDefinition
            case 93:  // ProgramFunctionDefinition
                value.move< FunctionDefinition::Ptr >( that.value );
                break;

            case 85:  // Header
                value.move< HeaderDefinition::Ptr >( that.value );
                break;

            case 152:  // Identifier
                value.move< Identifier::Ptr >( that.value );
                break;

            case 153:  // IdentifierPath
                value.move< IdentifierPath::Ptr >( that.value );
                break;

            case 154:  // DotSeparatedIdentifiers
                value.move< Identifiers::Ptr >( that.value );
                break;

            case 118:  // IndirectCallExpression
                value.move< IndirectCallExpression::Ptr >( that.value );
                break;

            case 106:  // IterateRule
                value.move< IterateRule::Ptr >( that.value );
                break;

            case 119:  // LetExpression
                value.move< LetExpression::Ptr >( that.value );
                break;

            case 103:  // LetRule
                value.move< LetRule::Ptr >( that.value );
                break;

            case 124:  // List
                value.move< ListExpression::Ptr >( that.value );
                break;

            case 117:  // MethodCallExpression
                value.move< MethodCallExpression::Ptr >( that.value );
                break;

            case 148:  // MaybeInitially
            case 149:  // Initializers
            case 151:  // MaybeInitializers
                value.move< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 145:  // Parameters
            case 146:  // MaybeParameters
                value.move< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 125:  // Range
                value.move< RangeExpression::Ptr >( that.value );
                break;

            case 134:  // ReferenceLiteral
                value.move< ReferenceAtom::Ptr >( that.value );
                break;

            case 139:  // RelationType
                value.move< RelationType::Ptr >( that.value );
                break;

            case 96:  // Rule
                value.move< Rule::Ptr >( that.value );
                break;

            case 91:  // RuleDefinition
                value.move< RuleDefinition::Ptr >( that.value );
                break;

            case 97:  // Rules
                value.move< Rules::Ptr >( that.value );
                break;

            case 108:  // SequenceRule
                value.move< SequenceRule::Ptr >( that.value );
                break;

            case 98:  // SkipRule
                value.move< SkipRule::Ptr >( that.value );
                break;

            case 84:  // Specification
                value.move< Specification::Ptr >( that.value );
                break;

            case 115:  // TypeCastingExpression
                value.move< TypeCastingExpression::Ptr >( that.value );
                break;

            case 135:  // Types
            case 143:  // FunctionParameters
            case 144:  // MaybeFunctionParameters
                value.move< Types::Ptr >( that.value );
                break;

            case 127:  // UndefinedLiteral
                value.move< UndefAtom::Ptr >( that.value );
                break;

            case 122:  // UniversalQuantifierExpression
                value.move< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 109:  // UpdateRule
            case 150:  // Initializer
                value.move< UpdateRule::Ptr >( that.value );
                break;

            case 128:  // BooleanLiteral
            case 129:  // IntegerLiteral
            case 130:  // RationalLiteral
            case 131:  // DecimalLiteral
            case 132:  // BinaryLiteral
            case 133:  // StringLiteral
                value.move< ValueAtom::Ptr >( that.value );
                break;

            case 155:  // Variable
            case 156:  // TypedVariable
            case 157:  // AttributedVariable
            case 158:  // TypedAttributedVariable
                value.move< VariableDefinition::Ptr >( that.value );
                break;

            case 136:  // Type
                value.move< libcasm_fe::Ast::Type::Ptr >( that.value );
                break;

            case 72:  // "binary"
            case 73:  // "hexadecimal"
            case 74:  // "integer"
            case 75:  // "rational"
            case 76:  // "decimal"
            case 77:  // "string"
            case 78:  // "identifier"
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
            case 160:  // Attribute
                value.copy< Attribute::Ptr >( that.value );
                break;

            case 159:  // Attributes
                value.copy< Attributes::Ptr >( that.value );
                break;

            case 161:  // BasicAttribute
                value.copy< BasicAttribute::Ptr >( that.value );
                break;

            case 137:  // BasicType
                value.copy< BasicType::Ptr >( that.value );
                break;

            case 107:  // BlockRule
                value.copy< BlockRule::Ptr >( that.value );
                break;

            case 110:  // CallRule
                value.copy< CallRule::Ptr >( that.value );
                break;

            case 101:  // CaseLabel
                value.copy< Case::Ptr >( that.value );
                break;

            case 100:  // CaseRule
                value.copy< CaseRule::Ptr >( that.value );
                break;

            case 102:  // CaseLabels
                value.copy< Cases::Ptr >( that.value );
                break;

            case 121:  // ChooseExpression
                value.copy< ChooseExpression::Ptr >( that.value );
                break;

            case 105:  // ChooseRule
                value.copy< ChooseRule::Ptr >( that.value );
                break;

            case 138:  // ComposedType
                value.copy< ComposedType::Ptr >( that.value );
                break;

            case 120:  // ConditionalExpression
                value.copy< ConditionalExpression::Ptr >( that.value );
                break;

            case 99:  // ConditionalRule
                value.copy< ConditionalRule::Ptr >( that.value );
                break;

            case 87:  // AttributedDefinition
            case 88:  // Definition
                value.copy< Definition::Ptr >( that.value );
                break;

            case 86:  // Definitions
                value.copy< Definitions::Ptr >( that.value );
                break;

            case 90:  // DerivedDefinition
                value.copy< DerivedDefinition::Ptr >( that.value );
                break;

            case 116:  // DirectCallExpression
                value.copy< DirectCallExpression::Ptr >( that.value );
                break;

            case 89:  // EnumerationDefinition
                value.copy< EnumerationDefinition::Ptr >( that.value );
                break;

            case 94:  // EnumeratorDefinition
                value.copy< EnumeratorDefinition::Ptr >( that.value );
                break;

            case 95:  // Enumerators
                value.copy< Enumerators::Ptr >( that.value );
                break;

            case 123:  // ExistentialQuantifierExpression
                value.copy< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 112:  // Term
            case 113:  // SimpleOrClaspedTerm
            case 114:  // Expression
            case 126:  // Literal
            case 147:  // MaybeDefined
                value.copy< Expression::Ptr >( that.value );
                break;

            case 162:  // ExpressionAttribute
                value.copy< ExpressionAttribute::Ptr >( that.value );
                break;

            case 111:  // Terms
            case 141:  // Arguments
            case 142:  // TwoOrMoreArguments
                value.copy< Expressions::Ptr >( that.value );
                break;

            case 140:  // FixedSizedType
                value.copy< FixedSizedType::Ptr >( that.value );
                break;

            case 104:  // ForallRule
                value.copy< ForallRule::Ptr >( that.value );
                break;

            case 92:  // FunctionDefinition
            case 93:  // ProgramFunctionDefinition
                value.copy< FunctionDefinition::Ptr >( that.value );
                break;

            case 85:  // Header
                value.copy< HeaderDefinition::Ptr >( that.value );
                break;

            case 152:  // Identifier
                value.copy< Identifier::Ptr >( that.value );
                break;

            case 153:  // IdentifierPath
                value.copy< IdentifierPath::Ptr >( that.value );
                break;

            case 154:  // DotSeparatedIdentifiers
                value.copy< Identifiers::Ptr >( that.value );
                break;

            case 118:  // IndirectCallExpression
                value.copy< IndirectCallExpression::Ptr >( that.value );
                break;

            case 106:  // IterateRule
                value.copy< IterateRule::Ptr >( that.value );
                break;

            case 119:  // LetExpression
                value.copy< LetExpression::Ptr >( that.value );
                break;

            case 103:  // LetRule
                value.copy< LetRule::Ptr >( that.value );
                break;

            case 124:  // List
                value.copy< ListExpression::Ptr >( that.value );
                break;

            case 117:  // MethodCallExpression
                value.copy< MethodCallExpression::Ptr >( that.value );
                break;

            case 148:  // MaybeInitially
            case 149:  // Initializers
            case 151:  // MaybeInitializers
                value.copy< NodeList< UpdateRule >::Ptr >( that.value );
                break;

            case 145:  // Parameters
            case 146:  // MaybeParameters
                value.copy< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 125:  // Range
                value.copy< RangeExpression::Ptr >( that.value );
                break;

            case 134:  // ReferenceLiteral
                value.copy< ReferenceAtom::Ptr >( that.value );
                break;

            case 139:  // RelationType
                value.copy< RelationType::Ptr >( that.value );
                break;

            case 96:  // Rule
                value.copy< Rule::Ptr >( that.value );
                break;

            case 91:  // RuleDefinition
                value.copy< RuleDefinition::Ptr >( that.value );
                break;

            case 97:  // Rules
                value.copy< Rules::Ptr >( that.value );
                break;

            case 108:  // SequenceRule
                value.copy< SequenceRule::Ptr >( that.value );
                break;

            case 98:  // SkipRule
                value.copy< SkipRule::Ptr >( that.value );
                break;

            case 84:  // Specification
                value.copy< Specification::Ptr >( that.value );
                break;

            case 115:  // TypeCastingExpression
                value.copy< TypeCastingExpression::Ptr >( that.value );
                break;

            case 135:  // Types
            case 143:  // FunctionParameters
            case 144:  // MaybeFunctionParameters
                value.copy< Types::Ptr >( that.value );
                break;

            case 127:  // UndefinedLiteral
                value.copy< UndefAtom::Ptr >( that.value );
                break;

            case 122:  // UniversalQuantifierExpression
                value.copy< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 109:  // UpdateRule
            case 150:  // Initializer
                value.copy< UpdateRule::Ptr >( that.value );
                break;

            case 128:  // BooleanLiteral
            case 129:  // IntegerLiteral
            case 130:  // RationalLiteral
            case 131:  // DecimalLiteral
            case 132:  // BinaryLiteral
            case 133:  // StringLiteral
                value.copy< ValueAtom::Ptr >( that.value );
                break;

            case 155:  // Variable
            case 156:  // TypedVariable
            case 157:  // AttributedVariable
            case 158:  // TypedAttributedVariable
                value.copy< VariableDefinition::Ptr >( that.value );
                break;

            case 136:  // Type
                value.copy< libcasm_fe::Ast::Type::Ptr >( that.value );
                break;

            case 72:  // "binary"
            case 73:  // "hexadecimal"
            case 74:  // "integer"
            case 75:  // "rational"
            case 76:  // "decimal"
            case 77:  // "string"
            case 78:  // "identifier"
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
                    case 160:  // Attribute
                        yylhs.value.build< Attribute::Ptr >();
                        break;

                    case 159:  // Attributes
                        yylhs.value.build< Attributes::Ptr >();
                        break;

                    case 161:  // BasicAttribute
                        yylhs.value.build< BasicAttribute::Ptr >();
                        break;

                    case 137:  // BasicType
                        yylhs.value.build< BasicType::Ptr >();
                        break;

                    case 107:  // BlockRule
                        yylhs.value.build< BlockRule::Ptr >();
                        break;

                    case 110:  // CallRule
                        yylhs.value.build< CallRule::Ptr >();
                        break;

                    case 101:  // CaseLabel
                        yylhs.value.build< Case::Ptr >();
                        break;

                    case 100:  // CaseRule
                        yylhs.value.build< CaseRule::Ptr >();
                        break;

                    case 102:  // CaseLabels
                        yylhs.value.build< Cases::Ptr >();
                        break;

                    case 121:  // ChooseExpression
                        yylhs.value.build< ChooseExpression::Ptr >();
                        break;

                    case 105:  // ChooseRule
                        yylhs.value.build< ChooseRule::Ptr >();
                        break;

                    case 138:  // ComposedType
                        yylhs.value.build< ComposedType::Ptr >();
                        break;

                    case 120:  // ConditionalExpression
                        yylhs.value.build< ConditionalExpression::Ptr >();
                        break;

                    case 99:  // ConditionalRule
                        yylhs.value.build< ConditionalRule::Ptr >();
                        break;

                    case 87:  // AttributedDefinition
                    case 88:  // Definition
                        yylhs.value.build< Definition::Ptr >();
                        break;

                    case 86:  // Definitions
                        yylhs.value.build< Definitions::Ptr >();
                        break;

                    case 90:  // DerivedDefinition
                        yylhs.value.build< DerivedDefinition::Ptr >();
                        break;

                    case 116:  // DirectCallExpression
                        yylhs.value.build< DirectCallExpression::Ptr >();
                        break;

                    case 89:  // EnumerationDefinition
                        yylhs.value.build< EnumerationDefinition::Ptr >();
                        break;

                    case 94:  // EnumeratorDefinition
                        yylhs.value.build< EnumeratorDefinition::Ptr >();
                        break;

                    case 95:  // Enumerators
                        yylhs.value.build< Enumerators::Ptr >();
                        break;

                    case 123:  // ExistentialQuantifierExpression
                        yylhs.value.build< ExistentialQuantifierExpression::Ptr >();
                        break;

                    case 112:  // Term
                    case 113:  // SimpleOrClaspedTerm
                    case 114:  // Expression
                    case 126:  // Literal
                    case 147:  // MaybeDefined
                        yylhs.value.build< Expression::Ptr >();
                        break;

                    case 162:  // ExpressionAttribute
                        yylhs.value.build< ExpressionAttribute::Ptr >();
                        break;

                    case 111:  // Terms
                    case 141:  // Arguments
                    case 142:  // TwoOrMoreArguments
                        yylhs.value.build< Expressions::Ptr >();
                        break;

                    case 140:  // FixedSizedType
                        yylhs.value.build< FixedSizedType::Ptr >();
                        break;

                    case 104:  // ForallRule
                        yylhs.value.build< ForallRule::Ptr >();
                        break;

                    case 92:  // FunctionDefinition
                    case 93:  // ProgramFunctionDefinition
                        yylhs.value.build< FunctionDefinition::Ptr >();
                        break;

                    case 85:  // Header
                        yylhs.value.build< HeaderDefinition::Ptr >();
                        break;

                    case 152:  // Identifier
                        yylhs.value.build< Identifier::Ptr >();
                        break;

                    case 153:  // IdentifierPath
                        yylhs.value.build< IdentifierPath::Ptr >();
                        break;

                    case 154:  // DotSeparatedIdentifiers
                        yylhs.value.build< Identifiers::Ptr >();
                        break;

                    case 118:  // IndirectCallExpression
                        yylhs.value.build< IndirectCallExpression::Ptr >();
                        break;

                    case 106:  // IterateRule
                        yylhs.value.build< IterateRule::Ptr >();
                        break;

                    case 119:  // LetExpression
                        yylhs.value.build< LetExpression::Ptr >();
                        break;

                    case 103:  // LetRule
                        yylhs.value.build< LetRule::Ptr >();
                        break;

                    case 124:  // List
                        yylhs.value.build< ListExpression::Ptr >();
                        break;

                    case 117:  // MethodCallExpression
                        yylhs.value.build< MethodCallExpression::Ptr >();
                        break;

                    case 148:  // MaybeInitially
                    case 149:  // Initializers
                    case 151:  // MaybeInitializers
                        yylhs.value.build< NodeList< UpdateRule >::Ptr >();
                        break;

                    case 145:  // Parameters
                    case 146:  // MaybeParameters
                        yylhs.value.build< NodeList< VariableDefinition >::Ptr >();
                        break;

                    case 125:  // Range
                        yylhs.value.build< RangeExpression::Ptr >();
                        break;

                    case 134:  // ReferenceLiteral
                        yylhs.value.build< ReferenceAtom::Ptr >();
                        break;

                    case 139:  // RelationType
                        yylhs.value.build< RelationType::Ptr >();
                        break;

                    case 96:  // Rule
                        yylhs.value.build< Rule::Ptr >();
                        break;

                    case 91:  // RuleDefinition
                        yylhs.value.build< RuleDefinition::Ptr >();
                        break;

                    case 97:  // Rules
                        yylhs.value.build< Rules::Ptr >();
                        break;

                    case 108:  // SequenceRule
                        yylhs.value.build< SequenceRule::Ptr >();
                        break;

                    case 98:  // SkipRule
                        yylhs.value.build< SkipRule::Ptr >();
                        break;

                    case 84:  // Specification
                        yylhs.value.build< Specification::Ptr >();
                        break;

                    case 115:  // TypeCastingExpression
                        yylhs.value.build< TypeCastingExpression::Ptr >();
                        break;

                    case 135:  // Types
                    case 143:  // FunctionParameters
                    case 144:  // MaybeFunctionParameters
                        yylhs.value.build< Types::Ptr >();
                        break;

                    case 127:  // UndefinedLiteral
                        yylhs.value.build< UndefAtom::Ptr >();
                        break;

                    case 122:  // UniversalQuantifierExpression
                        yylhs.value.build< UniversalQuantifierExpression::Ptr >();
                        break;

                    case 109:  // UpdateRule
                    case 150:  // Initializer
                        yylhs.value.build< UpdateRule::Ptr >();
                        break;

                    case 128:  // BooleanLiteral
                    case 129:  // IntegerLiteral
                    case 130:  // RationalLiteral
                    case 131:  // DecimalLiteral
                    case 132:  // BinaryLiteral
                    case 133:  // StringLiteral
                        yylhs.value.build< ValueAtom::Ptr >();
                        break;

                    case 155:  // Variable
                    case 156:  // TypedVariable
                    case 157:  // AttributedVariable
                    case 158:  // TypedAttributedVariable
                        yylhs.value.build< VariableDefinition::Ptr >();
                        break;

                    case 136:  // Type
                        yylhs.value.build< libcasm_fe::Ast::Type::Ptr >();
                        break;

                    case 72:  // "binary"
                    case 73:  // "hexadecimal"
                    case 74:  // "integer"
                    case 75:  // "rational"
                    case 76:  // "decimal"
                    case 77:  // "string"
                    case 78:  // "identifier"
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
#line 374 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            specification.setHeader(
                                yystack_[ 1 ].value.as< HeaderDefinition::Ptr >() );
                            specification.setDefinitions(
                                yystack_[ 0 ].value.as< Definitions::Ptr >() );
                        }
#line 1371 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 3:
#line 383 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< HeaderDefinition::Ptr >() = definition;
                        }
#line 1381 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 4:
#line 389 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< HeaderDefinition::Ptr >() =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                        }
#line 1389 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 5:
#line 397 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = yystack_[ 1 ].value.as< Definitions::Ptr >();
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1399 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 6:
#line 403 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = Ast::make< Definitions >( yylhs.location );
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1409 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 7:
#line 413 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition = yystack_[ 0 ].value.as< Definition::Ptr >();
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< Definition::Ptr >() = definition;
                        }
#line 1419 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 8:
#line 419 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< Definition::Ptr >();
                        }
#line 1427 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 9:
#line 423 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() = nullptr;
                        }
#line 1435 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 10:
#line 431 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< EnumerationDefinition::Ptr >();
                        }
#line 1443 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 11:
#line 435 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< DerivedDefinition::Ptr >();
                        }
#line 1451 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 12:
#line 439 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< RuleDefinition::Ptr >();
                        }
#line 1459 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 13:
#line 443 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< FunctionDefinition::Ptr >();
                        }
#line 1467 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 14:
#line 451 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumerationDefinition::Ptr >() =
                                Ast::make< EnumerationDefinition >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 1 ].value.as< Enumerators::Ptr >() );
                        }
#line 1475 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 15:
#line 459 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DerivedDefinition::Ptr >() =
                                Ast::make< DerivedDefinition >(
                                    yylhs.location,
                                    yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                    yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1483 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 16:
#line 467 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Identifier::Ptr >(),
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                createVoidType( yylhs.location ),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1492 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 17:
#line 472 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1501 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 18:
#line 481 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1521 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 19:
#line 497 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FunctionDefinition::Ptr >() =
                                yystack_[ 0 ]
                                    .value.as< FunctionDefinition::Ptr >();  // `init` special case
                        }
#line 1529 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 20:
#line 505 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1556 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 21:
#line 528 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1573 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 22:
#line 545 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() =
                                Ast::make< EnumeratorDefinition >(
                                    yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 1581 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 23:
#line 549 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerator = Ast::make< EnumeratorDefinition >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            enumerator->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = enumerator;
                        }
#line 1591 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 24:
#line 555 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = nullptr;
                        }
#line 1599 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 25:
#line 563 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = yystack_[ 2 ].value.as< Enumerators::Ptr >();
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1609 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 26:
#line 569 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = Ast::make< Enumerators >( yylhs.location );
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1619 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 27:
#line 583 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SkipRule::Ptr >();
                        }
#line 1627 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 28:
#line 587 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalRule::Ptr >();
                        }
#line 1635 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 29:
#line 591 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CaseRule::Ptr >();
                        }
#line 1643 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 30:
#line 595 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< LetRule::Ptr >();
                        }
#line 1651 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 31:
#line 599 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ForallRule::Ptr >();
                        }
#line 1659 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 32:
#line 603 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseRule::Ptr >();
                        }
#line 1667 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 33:
#line 607 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< IterateRule::Ptr >();
                        }
#line 1675 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 34:
#line 611 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< BlockRule::Ptr >();
                        }
#line 1683 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 35:
#line 615 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SequenceRule::Ptr >();
                        }
#line 1691 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 36:
#line 619 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRule::Ptr >();
                        }
#line 1699 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 37:
#line 623 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CallRule::Ptr >();
                        }
#line 1707 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 38:
#line 631 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = yystack_[ 1 ].value.as< Rules::Ptr >();
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1717 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 39:
#line 637 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = Ast::make< Rules >( yylhs.location );
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1727 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 40:
#line 647 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SkipRule::Ptr >() =
                                Ast::make< SkipRule >( yylhs.location );
                        }
#line 1735 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 41:
#line 655 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1743 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 42:
#line 659 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Rule::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1751 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 43:
#line 667 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = Ast::make< CaseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Cases::Ptr >() );
                        }
#line 1759 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 44:
#line 671 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = nullptr;
                        }
#line 1767 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 45:
#line 679 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1775 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 46:
#line 683 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1783 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 47:
#line 687 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< ExpressionCase >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1791 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 48:
#line 695 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = yystack_[ 1 ].value.as< Cases::Ptr >();
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1801 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 49:
#line 701 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = Ast::make< Cases >( yylhs.location );
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1811 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 50:
#line 711 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetRule::Ptr >() = Ast::make< LetRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1819 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 51:
#line 719 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1827 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 52:
#line 723 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 6 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1835 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 53:
#line 731 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseRule::Ptr >() = Ast::make< ChooseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1843 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 54:
#line 739 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IterateRule::Ptr >() = Ast::make< IterateRule >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1851 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 55:
#line 747 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1859 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 56:
#line 751 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1867 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 57:
#line 755 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1876 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 58:
#line 760 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1885 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 59:
#line 769 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1893 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 60:
#line 773 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1901 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 61:
#line 777 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1910 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 62:
#line 782 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1919 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 63:
#line 791 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto function =
                                yystack_[ 2 ].value.as< DirectCallExpression::Ptr >();
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1929 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 64:
#line 801 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 1937 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 65:
#line 805 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 1945 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 66:
#line 809 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 1953 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 67:
#line 813 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 1961 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 68:
#line 817 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 1969 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 69:
#line 821 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 1977 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 70:
#line 833 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto expressions = yystack_[ 2 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 1987 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 71:
#line 839 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 1997 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 72:
#line 849 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2005 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 73:
#line 853 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2013 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 74:
#line 857 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LetExpression::Ptr >();
                        }
#line 2021 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 75:
#line 861 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalExpression::Ptr >();
                        }
#line 2029 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 76:
#line 865 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseExpression::Ptr >();
                        }
#line 2037 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 77:
#line 869 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UniversalQuantifierExpression::Ptr >();
                        }
#line 2045 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 78:
#line 873 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ExistentialQuantifierExpression::Ptr >();
                        }
#line 2053 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 79:
#line 877 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TypeCastingExpression::Ptr >();
                        }
#line 2061 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 80:
#line 885 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2069 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 81:
#line 889 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = nullptr;
                        }
#line 2077 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 82:
#line 893 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >();
                        }
#line 2085 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 83:
#line 897 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >();
                        }
#line 2093 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 84:
#line 901 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >();
                        }
#line 2101 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 85:
#line 905 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ListExpression::Ptr >();
                        }
#line 2109 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 86:
#line 909 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< RangeExpression::Ptr >();
                        }
#line 2117 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 87:
#line 913 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2125 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 88:
#line 925 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2133 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 89:
#line 929 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::INV_INSTRUCTION );
                        }
#line 2141 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 90:
#line 933 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::ADD_INSTRUCTION );
                        }
#line 2149 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 91:
#line 937 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::SUB_INSTRUCTION );
                        }
#line 2157 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 92:
#line 941 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MUL_INSTRUCTION );
                        }
#line 2165 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 93:
#line 945 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::DIV_INSTRUCTION );
                        }
#line 2173 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 94:
#line 949 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MOD_INSTRUCTION );
                        }
#line 2181 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 95:
#line 953 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::POW_INSTRUCTION );
                        }
#line 2189 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 96:
#line 957 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NEQ_INSTRUCTION );
                        }
#line 2197 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 97:
#line 961 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::EQU_INSTRUCTION );
                        }
#line 2205 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 98:
#line 965 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LTH_INSTRUCTION );
                        }
#line 2213 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 99:
#line 969 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GTH_INSTRUCTION );
                        }
#line 2221 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 100:
#line 973 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LEQ_INSTRUCTION );
                        }
#line 2229 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 101:
#line 977 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GEQ_INSTRUCTION );
                        }
#line 2237 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 102:
#line 981 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::OR_INSTRUCTION );
                        }
#line 2245 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 103:
#line 985 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::XOR_INSTRUCTION );
                        }
#line 2253 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 104:
#line 989 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::AND_INSTRUCTION );
                        }
#line 2261 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 105:
#line 993 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2269 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 106:
#line 997 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2277 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 107:
#line 1001 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NOT_INSTRUCTION );
                        }
#line 2285 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 108:
#line 1009 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TypeCastingExpression::Ptr >() =
                                Ast::make< TypeCastingExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2293 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 109:
#line 1017 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2302 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 110:
#line 1022 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2310 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 111:
#line 1030 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2319 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 112:
#line 1035 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 3 ].value.as< Expression::Ptr >(),
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2327 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 113:
#line 1043 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IndirectCallExpression::Ptr >() =
                                Ast::make< IndirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2335 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 114:
#line 1051 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetExpression::Ptr >() = Ast::make< LetExpression >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2343 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 115:
#line 1059 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalExpression::Ptr >() =
                                Ast::make< ConditionalExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Expression::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2351 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 116:
#line 1067 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseExpression::Ptr >() =
                                Ast::make< ChooseExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2359 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 117:
#line 1075 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UniversalQuantifierExpression::Ptr >() =
                                Ast::make< UniversalQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2367 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 118:
#line 1083 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExistentialQuantifierExpression::Ptr >() =
                                Ast::make< ExistentialQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2375 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 119:
#line 1091 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< ListExpression::Ptr >() =
                                Ast::make< ListExpression >( yylhs.location, expressions );
                        }
#line 2384 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 120:
#line 1096 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListExpression::Ptr >() = Ast::make< ListExpression >(
                                yylhs.location, yystack_[ 1 ].value.as< Expressions::Ptr >() );
                        }
#line 2392 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 121:
#line 1100 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListExpression::Ptr >() = nullptr;
                        }
#line 2400 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 122:
#line 1108 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RangeExpression::Ptr >() = Ast::make< RangeExpression >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Expression::Ptr >() );
                        }
#line 2408 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 123:
#line 1120 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UndefAtom::Ptr >();
                        }
#line 2416 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 124:
#line 1124 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2424 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 125:
#line 1128 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2432 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 126:
#line 1132 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2440 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 127:
#line 1136 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2448 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 128:
#line 1140 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2456 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 129:
#line 1144 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueAtom::Ptr >();
                        }
#line 2464 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 130:
#line 1148 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ReferenceAtom::Ptr >();
                        }
#line 2472 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 131:
#line 1156 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UndefAtom::Ptr >() =
                                Ast::make< UndefAtom >( yylhs.location );
                        }
#line 2480 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 132:
#line 1164 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
                            yylhs.value.as< ValueAtom::Ptr >() =
                                Ast::make< ValueAtom >( yylhs.location, value );
                        }
#line 2489 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 133:
#line 1169 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
                            yylhs.value.as< ValueAtom::Ptr >() =
                                Ast::make< ValueAtom >( yylhs.location, value );
                        }
#line 2498 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 134:
#line 1178 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2514 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 135:
#line 1194 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2530 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 136:
#line 1210 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2546 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 137:
#line 1226 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2562 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 138:
#line 1238 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2578 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 139:
#line 1254 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2594 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 140:
#line 1270 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ReferenceAtom::Ptr >() = Ast::make< ReferenceAtom >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2602 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 141:
#line 1282 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2612 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 142:
#line 1288 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2622 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 143:
#line 1298 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< BasicType::Ptr >();
                        }
#line 2630 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 144:
#line 1302 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2638 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 145:
#line 1306 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< RelationType::Ptr >();
                        }
#line 2646 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 146:
#line 1310 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< FixedSizedType::Ptr >();
                        }
#line 2654 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 147:
#line 1318 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicType::Ptr >() = Ast::make< BasicType >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2662 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 148:
#line 1326 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ComposedType::Ptr >() = Ast::make< ComposedType >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 1 ].value.as< Types::Ptr >() );
                        }
#line 2670 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 149:
#line 1334 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RelationType::Ptr >() = Ast::make< RelationType >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 3 ].value.as< Types::Ptr >(),
                                yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2678 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 150:
#line 1342 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FixedSizedType::Ptr >() = Ast::make< FixedSizedType >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2686 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 151:
#line 1354 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() =
                                yystack_[ 1 ].value.as< Expressions::Ptr >();
                        }
#line 2694 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 152:
#line 1358 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() = nullptr;
                        }
#line 2702 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 153:
#line 1362 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2711 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 154:
#line 1371 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = yystack_[ 3 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 1 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2721 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 155:
#line 1385 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2731 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 156:
#line 1391 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2741 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 157:
#line 1401 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = yystack_[ 0 ].value.as< Types::Ptr >();
                        }
#line 2749 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 158:
#line 1405 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = Ast::make< Types >( yylhs.location );
                        }
#line 2757 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 159:
#line 1413 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >();
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2767 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 160:
#line 1419 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2777 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 161:
#line 1429 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< VariableDefinition >::Ptr >();
                        }
#line 2785 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 162:
#line 1433 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = nullptr;
                        }
#line 2793 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 163:
#line 1437 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                        }
#line 2801 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 164:
#line 1449 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2809 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 165:
#line 1453 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                Ast::make< UndefAtom >( yylhs.location );
                        }
#line 2817 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 166:
#line 1461 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2825 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 167:
#line 1465 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2833 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 168:
#line 1473 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                yystack_[ 2 ].value.as< NodeList< UpdateRule >::Ptr >();
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2843 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 169:
#line 1479 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() = initializers;
                        }
#line 2853 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 170:
#line 1489 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2865 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 171:
#line 1497 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2879 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 172:
#line 1507 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2890 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 173:
#line 1518 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                yystack_[ 0 ].value.as< NodeList< UpdateRule >::Ptr >();
                        }
#line 2898 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 174:
#line 1522 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< UpdateRule >::Ptr >() =
                                Ast::make< NodeList< UpdateRule > >( yylhs.location );
                        }
#line 2906 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 175:
#line 1534 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() = Ast::make< Identifier >(
                                yylhs.location, yystack_[ 0 ].value.as< std::string >() );
                        }
#line 2914 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 176:
#line 1538 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() =
                                Ast::make< Identifier >( yylhs.location, "in" );
                        }
#line 2922 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 177:
#line 1546 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Identifiers::Ptr >(),
                                IdentifierPath::Type::ABSOLUTE );
                        }
#line 2930 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 178:
#line 1550 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
                        }
#line 2940 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 179:
#line 1560 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = yystack_[ 2 ].value.as< Identifiers::Ptr >();
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2950 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 180:
#line 1566 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 2960 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 181:
#line 1580 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 2968 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 182:
#line 1584 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto unresolvedType =
                                Ast::make< UnresolvedType >( yylhs.location );
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    unresolvedType );
                        }
#line 2977 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 183:
#line 1593 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2985 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 184:
#line 1601 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 2995 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 185:
#line 1607 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3003 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 186:
#line 1615 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3013 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 187:
#line 1621 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3021 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 188:
#line 1633 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = yystack_[ 2 ].value.as< Attributes::Ptr >();
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3031 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 189:
#line 1639 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = Ast::make< Attributes >( yylhs.location );
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3041 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 190:
#line 1648 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< BasicAttribute::Ptr >();
                        }
#line 3049 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 191:
#line 1652 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< ExpressionAttribute::Ptr >();
                        }
#line 3057 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 192:
#line 1660 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicAttribute::Ptr >() = Ast::make< BasicAttribute >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 3065 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 193:
#line 1668 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExpressionAttribute::Ptr >() =
                                Ast::make< ExpressionAttribute >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 3073 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

#line 3077 "GrammarParser.cpp"  // lalr1.cc:859
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

    const short int Parser::yypact_ninf_ = -208;

    const short int Parser::yytable_ninf_ = -157;

    const short int Parser::yypact_[] = {
        1,    -208, 2,    20,   219,  -208, -208, 1487, -31,  -208, -208, -208, -208, -208, -6,
        2,    2,    2,    2,    2,    52,   -208, -208, -208, -208, -208, -208, -208, -5,   -5,
        -5,   1487, -5,   -208, -208, -208, 1487, 1487, 1487, 895,  958,  -3,   -208, -208, -208,
        -208, -208, -208, 2307, -27,  -208, -208, -208, -208, -208, -208, -208, -208, -208, -208,
        -208, -208, -208, -208, -208, -208, -208, -208, -208, -208, -208, 5,    59,   2,    1550,
        2,    -208, -208, 19,   53,   50,   53,   34,   -8,   -208, 2,    80,   -208, -208, 76,
        103,  116,  1818, 118,  -208, -208, -208, 91,   1487, 2035, 97,   -208, 41,   2069, -208,
        -3,   1487, 1487, 1487, 1487, 1487, 1487, 1487, 1487, 1487, 1487, 1487, 1487, 1487, 1487,
        1487, 1487, 1487, 2,    1021, -208, -208, -208, 895,  2103, 81,   98,   -208, 102,  -208,
        2,    4,    89,   107,  -37,  -3,   224,  42,   -3,   1487, 1487, 1487, 1487, 1487, -208,
        2137, -208, -208, -208, 1487, 1487, -208, -208, -208, -208, -208, 0,    564,  2341, 2370,
        414,  104,  104,  265,  108,  108,  96,   96,   96,   -208, 414,  265,  108,  108,  5,
        112,  -208, -28,  2307, 119,  2035, 1487, 1487, 1550, -208, -208, 129,  2,    -11,  80,
        -208, -208, -3,   8,    1361, -3,   -208, 113,  111,  -208, 2,    -208, 1576, 1962, 1700,
        1894, 2001, 5,    2307, 2171, -3,   1487, -208, -208, -208, 1487, 2307, 2307, -208, -208,
        69,   -208, -2,   134,  -208, 2,    -208, 78,   -208, 565,  633,  -208, -5,   -5,   -5,
        1361, 125,  1487, 1487, 701,  769,  -208, -208, -208, -208, -208, -208, -208, -208, -208,
        -208, -208, -208, -27,  63,   120,  123,  138,  -3,   -3,   -208, 1487, 1487, 1487, 1487,
        1487, -208, -208, 29,   30,   124,  -208, 2205, 2,    -208, 1487, 71,   -208, 8,    170,
        -208, 1089, 173,  1157, 147,  174,  176,  -208, 133,  120,  123,  1856, 1928, 155,  1225,
        135,  1293, 1487, 1361, -208, 195,  2307, 2307, 2307, 2307, 2307, -3,   -208, -3,   -208,
        -208, 2307, 2,    -208, -208, -208, -208, -208, -208, 1487, 1487, 1487, 1361, 159,  -208,
        -208, -208, -208, 2307, -208, 162,  199,  -208, 156,  -208, 1620, 1660, 1740, 186,  832,
        1487, 171,  -208, -208, 1361, 1361, 1487, 1361, 1361, 169,  172,  183,  -208, 1424, 2239,
        2273, 1550, -208, -208, 1780, -208, -208, -208, 1361, 1361, -208, -208, 1361, -208, 185,
        1361, -208, -208, -208, -208, -208
    };

    const unsigned char Parser::yydefact_[] = {
        0,   4,   0,   0,   0,   176, 175, 192, 0,   189, 190, 191, 1,   9,   0,   0,   0,   0,
        0,   0,   0,   6,   8,   10,  11,  12,  13,  19,  0,   0,   0,   0,   0,   131, 133, 132,
        0,   0,   0,   0,   0,   0,   137, 138, 134, 135, 136, 139, 193, 72,  73,  79,  82,  83,
        84,  74,  75,  76,  77,  78,  85,  86,  87,  123, 124, 125, 126, 127, 128, 129, 130, 109,
        0,   0,   174, 0,   180, 20,  177, 163, 0,   163, 0,   0,   5,   0,   182, 185, 181, 0,
        0,   0,   0,   0,   107, 88,  89,  0,   0,   0,   0,   119, 0,   71,  140, 0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   110,
        3,   188, 0,   170, 0,   173, 169, 0,   178, 0,   0,   0,   0,   0,   158, 0,   0,   0,
        0,   0,   0,   0,   0,   81,  0,   80,  121, 120, 0,   0,   108, 143, 144, 145, 146, 147,
        104, 102, 103, 106, 90,  91,  97,  98,  99,  92,  93,  94,  95,  105, 96,  100, 101, 111,
        0,   153, 0,   71,  0,   71,  0,   0,   0,   21,  179, 0,   0,   0,   0,   187, 160, 0,
        0,   0,   0,   156, 157, 0,   7,   0,   183, 0,   0,   0,   0,   0,   0,   70,  0,   158,
        0,   112, 152, 151, 0,   171, 172, 168, 162, 0,   161, 0,   0,   24,  0,   26,  0,   22,
        0,   0,   40,  0,   0,   0,   0,   0,   0,   0,   0,   0,   16,  27,  28,  29,  30,  31,
        32,  33,  34,  35,  36,  37,  0,   65,  67,  69,  0,   0,   0,   184, 0,   0,   0,   0,
        0,   113, 122, 0,   142, 0,   150, 70,  0,   159, 0,   0,   14,  0,   0,   39,  0,   0,
        0,   0,   0,   0,   54,  64,  66,  68,  0,   0,   0,   0,   0,   0,   0,   0,   155, 165,
        114, 117, 116, 115, 118, 0,   148, 0,   154, 186, 15,  0,   25,  62,  60,  38,  58,  56,
        0,   0,   0,   0,   0,   57,  55,  61,  59,  63,  17,  0,   167, 141, 0,   23,  0,   0,
        0,   41,  0,   0,   0,   18,  149, 0,   0,   0,   0,   0,   0,   0,   0,   49,  0,   0,
        0,   174, 50,  51,  0,   53,  42,  44,  0,   0,   43,  48,  0,   164, 0,   0,   45,  46,
        47,  166, 52
    };

    const short int Parser::yypgoto_[] = {
        -208, -208, -208, -208, 201,  99,   -208, -208, -208, -208, -208, -46,  -208, 200,
        -207, -208, -208, -208, -120, -208, -208, -208, -208, -208, -208, -208, -208, -208,
        -106, -7,   40,   -208, -208, 70,   160,  192,  -208, -208, -208, -208, -208, -208,
        -208, -208, -208, -208, -208, -208, -208, -208, -208, -208, -208, -69,  -208, -208,
        -208, -208, -177, -208, -208, 28,   -208, 164,  -208, -208, -208, 60,   -111, 49,
        -1,   -208, 46,   -135, -22,  25,   -16,  180,  -208, -208
    };

    const short int Parser::yydefgoto_[] = {
        -1,  3,   4,   20,  21,  22,  23,  24,  25,  26,  27,  231, 232, 285, 286, 247,
        248, 249, 357, 358, 250, 251, 252, 253, 254, 255, 256, 257, 102, 129, 49,  50,
        51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,
        67,  68,  69,  70,  273, 156, 157, 158, 159, 160, 125, 130, 202, 203, 193, 137,
        336, 347, 131, 132, 133, 71,  161, 78,  87,  88,  89,  196, 8,   9,   10,  11
    };

    const short int Parser::yytable_[] = {
        48,  195, 217, 83,  1,    191, 199, 90,  91,  229, 93,  5,   5,   77,  5,   5,    72,  219,
        182, 5,   12,  5,   184,  73,  92,  5,   154, 200, 288, 94,  95,  96,  99,  103,  226, 271,
        123, 299, 301, 141, 104,  85,  74,  227, 192, 75,  73,  2,   75,  124, 192, 7,    -2,  13,
        230, 215, 14,  15,  16,   17,  18,  216, 126, 76,  79,  80,  81,  82,  7,   142,  135, 201,
        6,   6,   206, 6,   6,    86,  86,  86,  6,   86,  6,   311, 140, 312, 6,   -156, 153, 205,
        76,  150, 195, 138, -156, 154, 73,  136, 19,  162, 163, 164, 165, 166, 167, 168,  169, 170,
        171, 172, 173, 174, 175,  176, 177, 178, 278, 183, 317, 144, 145, 185, 7,   73,   134, 73,
        -82, 282, 228, 302, 143,  262, 283, 146, 7,   148, 149, 207, 208, 209, 210, 211,  5,   315,
        152, 187, 274, 213, 214,  110, 111, 189, 188, 197, 76,  198, 118, 218, 33,  34,   35,  115,
        116, 117, 118, 115, 116,  117, 118, 39,  263, 40,  179, 220, 224, 264, 225, 280,  41,  221,
        222, 303, 319, -83, 190,  194, -84, 322, 313, 76,  324, 325, 76,  326, 304, 305,  -82, 42,
        43,  44,  45,  46,  47,   6,   329, 335, 331, 344, 346, 276, 345, 353, 348, 277,  281, 289,
        290, 291, 367, 361, 13,   84,  368, 14,  15,  16,  17,  18,  14,  15,  16,  17,   18,  369,
        379, 296, 297, 318, 371,  258, 204, 7,   337, 275, 338, 139, 76,  233, 223, 76,   374, 265,
        279, 127, 86,  0,   0,    0,   0,   306, 307, 308, 309, 310, 76,  19,  0,   0,    0,   259,
        0,   0,   0,   316, 258,  258, 194, 0,   0,   7,   258, 258, 0,   0,   258, 258,  86,  86,
        86,  0,   0,   0,   0,    0,   0,   333, 0,   0,   0,   0,   0,   0,   0,   0,    259, 259,
        110, 111, 0,   0,   259,  293, 76,  76,  259, 259, 0,   340, 341, 342, 113, 114,  115, 116,
        117, 118, 258, 194, 258,  0,   0,   0,   233, 121, 122, 0,   0,   359, 360, 258,  0,   258,
        0,   258, 364, 0,   0,    0,   0,   0,   0,   359, 0,   0,   0,   0,   259, 0,    259, 260,
        76,  0,   76,  0,   0,    0,   339, 258, 0,   259, 0,   259, 0,   259, 0,   0,    0,   0,
        0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   258, 258, 261, 258, 258,  260, 260,
        0,   259, 0,   246, 260,  294, 0,   0,   260, 260, 0,   0,   258, 258, 0,   0,    258, 0,
        0,   258, 0,   0,   0,    259, 259, 0,   259, 259, 0,   0,   261, 261, 0,   0,    0,   0,
        261, 295, 0,   0,   261,  261, 259, 259, 292, 0,   259, 0,   0,   259, 260, 0,    260, 0,
        106, 107, 108, 0,   0,    110, 111, 112, 0,   260, 0,   260, 0,   260, 0,   0,    0,   0,
        0,   113, 114, 115, 116,  117, 118, 0,   0,   0,   261, 0,   261, 120, 121, 122,  0,   0,
        321, 260, 321, 0,   0,    261, 0,   261, 0,   261, 0,   0,   0,   321, 0,   321,  0,   334,
        0,   0,   0,   0,   0,    260, 260, 0,   260, 260, 0,   0,   0,   0,   0,   261,  0,   0,
        0,   0,   0,   0,   0,    343, 260, 260, 0,   0,   260, 0,   0,   260, 0,   0,    0,   0,
        0,   261, 261, 0,   261,  261, 0,   0,   0,   362, 363, 0,   365, 366, 0,   0,    0,   0,
        0,   0,   261, 261, 0,    0,   261, 0,   284, 261, 376, 377, 0,   0,   378, 0,    0,   380,
        234, 0,   235, 0,   236,  237, 5,   238, 239, 240, 0,   241, 242, 0,   0,   243,  0,   0,
        0,   0,   0,   0,   33,   34,  35,  0,   0,   0,   0,   110, 111, 112, 0,   39,   0,   40,
        0,   244, 0,   0,   0,    0,   41,  113, 114, 115, 116, 117, 118, 0,   0,   0,    0,   0,
        0,   120, 121, 122, 287,  245, 0,   42,  43,  44,  45,  46,  47,  6,   234, 0,    235, 0,
        236, 237, 5,   238, 239,  240, 0,   241, 242, 0,   0,   243, 0,   0,   0,   0,    0,   0,
        33,  34,  35,  0,   0,    0,   0,   0,   0,   0,   0,   39,  0,   40,  0,   244,  0,   0,
        0,   0,   41,  0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
        298, 245, 0,   42,  43,   44,  45,  46,  47,  6,   234, 0,   235, 0,   236, 237,  5,   238,
        239, 240, 0,   241, 242,  0,   0,   243, 0,   0,   0,   0,   0,   0,   33,  34,   35,  0,
        0,   0,   0,   0,   0,    0,   0,   39,  0,   40,  0,   244, 0,   0,   0,   0,    41,  0,
        0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   300, 245,  0,   42,
        43,  44,  45,  46,  47,   6,   234, 0,   235, 0,   236, 237, 5,   238, 239, 240,  0,   241,
        242, 0,   0,   243, 0,    0,   0,   0,   0,   0,   33,  34,  35,  0,   0,   0,    0,   0,
        0,   0,   0,   39,  0,    40,  0,   244, 0,   0,   0,   0,   41,  0,   0,   0,    0,   0,
        0,   0,   0,   0,   0,    354, 0,   0,   0,   0,   0,   245, 0,   42,  43,  44,   45,  46,
        47,  6,   28,  5,   29,   30,  0,   0,   0,   31,  0,   0,   0,   0,   355, 0,    32,  0,
        0,   33,  34,  35,  0,    0,   0,   0,   36,  37,  38,  0,   39,  0,   40,  0,    0,   0,
        0,   0,   356, 41,  0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   97,  0,    0,   0,
        0,   0,   0,   0,   42,   43,  44,  45,  46,  47,  6,   28,  5,   29,  30,  0,    0,   0,
        31,  0,   0,   0,   0,    0,   0,   32,  0,   0,   33,  34,  35,  0,   0,   0,    0,   36,
        37,  38,  0,   39,  0,    40,  0,   0,   0,   0,   0,   0,   41,  0,   0,   0,    98,  0,
        0,   0,   0,   0,   0,    100, 0,   0,   0,   0,   0,   0,   0,   42,  43,  44,   45,  46,
        47,  6,   28,  5,   29,   30,  0,   0,   0,   31,  0,   0,   0,   0,   0,   0,    32,  0,
        0,   33,  34,  35,  0,    0,   0,   0,   36,  37,  38,  0,   39,  0,   40,  101,  0,   0,
        0,   0,   0,   41,  0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   180, 0,    0,   0,
        0,   0,   0,   0,   42,   43,  44,  45,  46,  47,  6,   28,  5,   29,  30,  0,    0,   0,
        31,  0,   0,   0,   0,    0,   0,   32,  0,   0,   33,  34,  35,  0,   0,   0,    0,   36,
        37,  38,  0,   39,  181,  40,  0,   0,   0,   0,   0,   0,   41,  0,   0,   0,    0,   0,
        0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   42,  43,  44,   45,  46,
        47,  6,   234, 320, 235,  0,   236, 237, 5,   238, 239, 240, 0,   241, 242, 0,    0,   243,
        0,   0,   0,   0,   0,    0,   33,  34,  35,  0,   0,   0,   0,   0,   0,   0,    0,   39,
        0,   40,  0,   244, 0,    0,   0,   0,   41,  0,   0,   0,   0,   0,   0,   0,    0,   0,
        0,   0,   0,   0,   0,    0,   0,   245, 0,   42,  43,  44,  45,  46,  47,  6,    234, 0,
        235, 323, 236, 237, 5,    238, 239, 240, 0,   241, 242, 0,   0,   243, 0,   0,    0,   0,
        0,   0,   33,  34,  35,   0,   0,   0,   0,   0,   0,   0,   0,   39,  0,   40,   0,   244,
        0,   0,   0,   0,   41,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
        0,   0,   0,   245, 0,    42,  43,  44,  45,  46,  47,  6,   234, 0,   235, 0,    236, 237,
        5,   238, 239, 240, 0,    241, 242, 0,   0,   243, 0,   0,   0,   0,   0,   0,    33,  34,
        35,  0,   0,   0,   0,    0,   0,   0,   0,   39,  0,   40,  0,   244, 330, 0,    0,   0,
        41,  0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   245,
        0,   42,  43,  44,  45,   46,  47,  6,   234, 0,   235, 0,   236, 237, 5,   238,  239, 240,
        0,   241, 242, 0,   0,    243, 0,   0,   0,   0,   0,   0,   33,  34,  35,  0,    0,   0,
        0,   0,   0,   0,   0,    39,  0,   40,  0,   244, 0,   0,   0,   0,   41,  0,    0,   0,
        0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   245, 332, 42,   43,  44,
        45,  46,  47,  6,   234,  0,   235, 0,   236, 237, 5,   238, 239, 240, 0,   241,  242, 0,
        0,   243, 0,   0,   0,    0,   0,   0,   33,  34,  35,  0,   0,   0,   0,   0,    0,   0,
        0,   39,  0,   40,  0,    244, 0,   0,   0,   0,   41,  0,   0,   0,   0,   0,    0,   0,
        0,   0,   0,   0,   0,    0,   0,   0,   0,   245, 0,   42,  43,  44,  45,  46,   47,  6,
        28,  5,   29,  30,  0,    0,   0,   31,  0,   0,   0,   0,   355, 0,   32,  0,    0,   33,
        34,  35,  0,   0,   0,    0,   36,  37,  38,  0,   39,  0,   40,  0,   0,   370,  0,   0,
        356, 41,  0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
        0,   0,   42,  43,  44,   45,  46,  47,  6,   28,  5,   29,  30,  0,   0,   0,    31,  0,
        0,   0,   0,   0,   0,    32,  0,   0,   33,  34,  35,  0,   0,   0,   0,   36,   37,  38,
        0,   39,  0,   40,  0,    0,   0,   0,   0,   0,   41,  0,   0,   0,   0,   0,    0,   0,
        0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   42,  43,  44,  45,  46,   47,  6,
        28,  5,   29,  30,  0,    0,   0,   31,  0,   0,   0,   0,   0,   0,   32,  0,    0,   33,
        34,  35,  0,   0,   0,    0,   36,  37,  38,  266, 128, 0,   40,  0,   0,   0,    0,   0,
        0,   41,  0,   0,   0,    0,   105, 0,   0,   0,   106, 107, 108, 109, 0,   110,  111, 112,
        0,   0,   42,  43,  44,   45,  46,  47,  6,   0,   0,   113, 114, 115, 116, 117,  118, 349,
        0,   0,   0,   119, 0,    120, 121, 122, 0,   0,   0,   0,   0,   0,   105, 0,    0,   0,
        106, 107, 108, 109, 0,    110, 111, 112, 0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
        0,   113, 114, 115, 116,  117, 118, 350, 0,   0,   0,   119, 0,   120, 121, 122,  0,   351,
        105, 0,   0,   0,   106,  107, 108, 109, 0,   110, 111, 112, 0,   0,   0,   0,    0,   0,
        0,   0,   0,   0,   0,    113, 114, 115, 116, 117, 118, 268, 0,   0,   0,   119,  0,   120,
        121, 122, 0,   0,   105,  0,   0,   0,   106, 107, 108, 109, 0,   110, 111, 112,  0,   0,
        0,   0,   0,   0,   0,    0,   0,   0,   0,   113, 114, 115, 116, 117, 118, 352,  0,   0,
        0,   119, 0,   120, 121,  122, 0,   0,   105, 0,   0,   0,   106, 107, 108, 109,  0,   110,
        111, 112, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   113, 114, 115,  116, 117,
        118, 375, 0,   0,   0,    119, 0,   120, 121, 122, 0,   0,   105, 0,   0,   0,    106, 107,
        108, 109, 0,   110, 111,  112, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   113,
        114, 115, 116, 117, 118,  0,   147, 0,   0,   119, 0,   120, 121, 122, 105, 0,    0,   0,
        106, 107, 108, 109, 0,    110, 111, 112, 0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
        0,   113, 114, 115, 116,  117, 118, 0,   327, 0,   0,   119, 0,   120, 121, 122,  105, 0,
        0,   0,   106, 107, 108,  109, 0,   110, 111, 112, 0,   0,   0,   0,   0,   0,    0,   0,
        0,   0,   0,   113, 114,  115, 116, 117, 118, 0,   0,   269, 0,   119, 0,   120,  121, 122,
        105, 0,   0,   0,   106,  107, 108, 109, 0,   110, 111, 112, 0,   0,   0,   0,    0,   0,
        0,   0,   0,   0,   0,    113, 114, 115, 116, 117, 118, 328, 0,   0,   0,   119,  105, 120,
        121, 122, 106, 107, 108,  109, 0,   110, 111, 112, 0,   0,   0,   0,   0,   0,    0,   0,
        0,   0,   0,   113, 114,  115, 116, 117, 118, 0,   0,   267, 0,   119, 105, 120,  121, 122,
        106, 107, 108, 109, 0,    110, 111, 112, 0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
        0,   113, 114, 115, 116,  117, 118, 0,   0,   0,   0,   119, 0,   120, 121, 122,  270, 105,
        0,   0,   0,   106, 107,  108, 109, 0,   110, 111, 112, 0,   0,   0,   0,   0,    0,   0,
        0,   0,   0,   0,   113,  114, 115, 116, 117, 118, 0,   0,   0,   0,   119, 105,  120, 121,
        122, 106, 107, 108, 109,  0,   110, 111, 112, 0,   151, 0,   0,   0,   0,   0,    0,   0,
        0,   0,   113, 114, 115,  116, 117, 118, 0,   0,   0,   0,   119, 105, 120, 121,  122, 106,
        107, 108, 109, 0,   110,  111, 112, 0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,
        113, 114, 115, 116, 117,  118, 0,   155, 0,   0,   119, 105, 120, 121, 122, 106,  107, 108,
        109, 0,   110, 111, 112,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    113, 114,
        115, 116, 117, 118, 0,    0,   0,   186, 119, 105, 120, 121, 122, 106, 107, 108,  109, 0,
        110, 111, 112, 0,   212,  0,   0,   0,   0,   0,   0,   0,   0,   0,   113, 114,  115, 116,
        117, 118, 0,   0,   0,    0,   119, 105, 120, 121, 122, 106, 107, 108, 109, 0,    110, 111,
        112, 0,   0,   0,   272,  0,   0,   0,   0,   0,   0,   0,   113, 114, 115, 116,  117, 118,
        0,   0,   0,   0,   119,  105, 120, 121, 122, 106, 107, 108, 109, 0,   110, 111,  112, 0,
        314, 0,   0,   0,   0,    0,   0,   0,   0,   0,   113, 114, 115, 116, 117, 118,  0,   0,
        0,   0,   119, 105, 120,  121, 122, 106, 107, 108, 109, 0,   110, 111, 112, 0,    0,   0,
        0,   0,   0,   372, 0,    0,   0,   0,   113, 114, 115, 116, 117, 118, 0,   0,    0,   0,
        119, 105, 120, 121, 122,  106, 107, 108, 109, 0,   110, 111, 112, 0,   0,   0,    0,   0,
        373, 0,   0,   0,   0,    0,   113, 114, 115, 116, 117, 118, 0,   0,   0,   0,    119, 105,
        120, 121, 122, 106, 107,  108, 109, 0,   110, 111, 112, 0,   0,   0,   0,   0,    0,   0,
        0,   0,   0,   0,   113,  114, 115, 116, 117, 118, 0,   0,   0,   0,   119, 0,    120, 121,
        122, 106, 0,   108, 0,    0,   110, 111, 112, 0,   0,   0,   0,   0,   0,   0,    0,   0,
        0,   0,   113, 114, 115,  116, 117, 118, 0,   0,   0,   0,   106, 0,   120, 121,  122, 110,
        111, 112, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   113, 114, 115,  116, 117,
        118, 0,   0,   0,   0,    0,   0,   120, 121, 122
    };

    const short int Parser::yycheck_[] = {
        7,   136, 179, 19,  3,   1,   43,  29,  30,  1,   32,  17,  17,  14,  17,  17,  47,  45,
        124, 17,  0,   17,  128, 54,  31,  17,  54,  64,  235, 36,  37,  38,  39,  40,  45,  212,
        63,  244, 245, 47,  41,  46,  48,  54,  46,  51,  54,  46,  51,  44,  46,  2,   0,   1,
        46,  55,  4,   5,   6,   7,   8,   61,  3,   14,  15,  16,  17,  18,  19,  85,  51,  140,
        78,  78,  143, 78,  78,  28,  29,  30,  78,  32,  78,  54,  50,  56,  78,  57,  47,  47,
        41,  98,  227, 43,  64,  54,  54,  44,  46,  106, 107, 108, 109, 110, 111, 112, 113, 114,
        115, 116, 117, 118, 119, 120, 121, 122, 47,  124, 47,  43,  17,  128, 73,  54,  75,  54,
        63,  49,  197, 66,  50,  200, 54,  17,  85,  17,  45,  144, 145, 146, 147, 148, 17,  278,
        47,  64,  215, 154, 155, 41,  42,  49,  54,  64,  105, 48,  60,  45,  33,  34,  35,  57,
        58,  59,  60,  57,  58,  59,  60,  44,  57,  46,  123, 54,  45,  64,  192, 43,  53,  186,
        187, 43,  12,  63,  135, 136, 63,  14,  64,  140, 43,  17,  143, 17,  263, 264, 63,  72,
        73,  74,  75,  76,  77,  78,  49,  10,  71,  48,  9,   216, 48,  25,  56,  220, 230, 237,
        238, 239, 49,  48,  1,   20,  50,  4,   5,   6,   7,   8,   4,   5,   6,   7,   8,   50,
        49,  242, 243, 283, 358, 199, 141, 192, 311, 215, 313, 81,  197, 198, 188, 200, 361, 205,
        227, 73,  205, -1,  -1,  -1,  -1,  266, 267, 268, 269, 270, 215, 46,  -1,  -1,  -1,  199,
        -1,  -1,  -1,  280, 234, 235, 227, -1,  -1,  230, 240, 241, -1,  -1,  244, 245, 237, 238,
        239, -1,  -1,  -1,  -1,  -1,  -1,  302, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  234, 235,
        41,  42,  -1,  -1,  240, 241, 263, 264, 244, 245, -1,  324, 325, 326, 55,  56,  57,  58,
        59,  60,  286, 278, 288, -1,  -1,  -1,  283, 68,  69,  -1,  -1,  344, 345, 299, -1,  301,
        -1,  303, 351, -1,  -1,  -1,  -1,  -1,  -1,  358, -1,  -1,  -1,  -1,  286, -1,  288, 199,
        311, -1,  313, -1,  -1,  -1,  317, 327, -1,  299, -1,  301, -1,  303, -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  349, 350, 199, 352, 353, 234, 235,
        -1,  327, -1,  199, 240, 241, -1,  -1,  244, 245, -1,  -1,  368, 369, -1,  -1,  372, -1,
        -1,  375, -1,  -1,  -1,  349, 350, -1,  352, 353, -1,  -1,  234, 235, -1,  -1,  -1,  -1,
        240, 241, -1,  -1,  244, 245, 368, 369, 240, -1,  372, -1,  -1,  375, 286, -1,  288, -1,
        36,  37,  38,  -1,  -1,  41,  42,  43,  -1,  299, -1,  301, -1,  303, -1,  -1,  -1,  -1,
        -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  286, -1,  288, 67,  68,  69,  -1,  -1,
        286, 327, 288, -1,  -1,  299, -1,  301, -1,  303, -1,  -1,  -1,  299, -1,  301, -1,  303,
        -1,  -1,  -1,  -1,  -1,  349, 350, -1,  352, 353, -1,  -1,  -1,  -1,  -1,  327, -1,  -1,
        -1,  -1,  -1,  -1,  -1,  327, 368, 369, -1,  -1,  372, -1,  -1,  375, -1,  -1,  -1,  -1,
        -1,  349, 350, -1,  352, 353, -1,  -1,  -1,  349, 350, -1,  352, 353, -1,  -1,  -1,  -1,
        -1,  -1,  368, 369, -1,  -1,  372, -1,  1,   375, 368, 369, -1,  -1,  372, -1,  -1,  375,
        11,  -1,  13,  -1,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  -1,
        -1,  -1,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  41,  42,  43,  -1,  44,  -1,  46,
        -1,  48,  -1,  -1,  -1,  -1,  53,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  -1,
        -1,  67,  68,  69,  1,   70,  -1,  72,  73,  74,  75,  76,  77,  78,  11,  -1,  13,  -1,
        15,  16,  17,  18,  19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,
        33,  34,  35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,  -1,  46,  -1,  48,  -1,  -1,
        -1,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        1,   70,  -1,  72,  73,  74,  75,  76,  77,  78,  11,  -1,  13,  -1,  15,  16,  17,  18,
        19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  33,  34,  35,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,  -1,  46,  -1,  48,  -1,  -1,  -1,  -1,  53,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   70,  -1,  72,
        73,  74,  75,  76,  77,  78,  11,  -1,  13,  -1,  15,  16,  17,  18,  19,  20,  -1,  22,
        23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  44,  -1,  46,  -1,  48,  -1,  -1,  -1,  -1,  53,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,  -1,  -1,  70,  -1,  72,  73,  74,  75,  76,
        77,  78,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  28,  -1,  30,  -1,
        -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,
        -1,  -1,  52,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,
        -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,  77,  78,  16,  17,  18,  19,  -1,  -1,  -1,
        23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,
        41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  -1,  53,  -1,  -1,  -1,  57,  -1,
        -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,
        77,  78,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,
        -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  47,  -1,  -1,
        -1,  -1,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,
        -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,  77,  78,  16,  17,  18,  19,  -1,  -1,  -1,
        23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,
        41,  42,  -1,  44,  45,  46,  -1,  -1,  -1,  -1,  -1,  -1,  53,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,
        77,  78,  11,  12,  13,  -1,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  -1,  -1,  26,
        -1,  -1,  -1,  -1,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,
        -1,  46,  -1,  48,  -1,  -1,  -1,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  70,  -1,  72,  73,  74,  75,  76,  77,  78,  11,  -1,
        13,  14,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,
        -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,  -1,  46,  -1,  48,
        -1,  -1,  -1,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  70,  -1,  72,  73,  74,  75,  76,  77,  78,  11,  -1,  13,  -1,  15,  16,
        17,  18,  19,  20,  -1,  22,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  33,  34,
        35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,  -1,  46,  -1,  48,  49,  -1,  -1,  -1,
        53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  70,
        -1,  72,  73,  74,  75,  76,  77,  78,  11,  -1,  13,  -1,  15,  16,  17,  18,  19,  20,
        -1,  22,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  44,  -1,  46,  -1,  48,  -1,  -1,  -1,  -1,  53,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  70,  71,  72,  73,  74,
        75,  76,  77,  78,  11,  -1,  13,  -1,  15,  16,  17,  18,  19,  20,  -1,  22,  23,  -1,
        -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  44,  -1,  46,  -1,  48,  -1,  -1,  -1,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  70,  -1,  72,  73,  74,  75,  76,  77,  78,
        16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  28,  -1,  30,  -1,  -1,  33,
        34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,  49,  -1,  -1,
        52,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  72,  73,  74,  75,  76,  77,  78,  16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,
        -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,
        -1,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,  77,  78,
        16,  17,  18,  19,  -1,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,
        34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  17,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,
        -1,  53,  -1,  -1,  -1,  -1,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,
        -1,  -1,  72,  73,  74,  75,  76,  77,  78,  -1,  -1,  55,  56,  57,  58,  59,  60,  17,
        -1,  -1,  -1,  65,  -1,  67,  68,  69,  -1,  -1,  -1,  -1,  -1,  -1,  32,  -1,  -1,  -1,
        36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  55,  56,  57,  58,  59,  60,  21,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  -1,  31,
        32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  21,  -1,  -1,  -1,  65,  -1,  67,
        68,  69,  -1,  -1,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  21,  -1,  -1,
        -1,  65,  -1,  67,  68,  69,  -1,  -1,  32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,
        42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,
        60,  21,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  -1,  -1,  32,  -1,  -1,  -1,  36,  37,
        38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,
        56,  57,  58,  59,  60,  -1,  24,  -1,  -1,  65,  -1,  67,  68,  69,  32,  -1,  -1,  -1,
        36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  55,  56,  57,  58,  59,  60,  -1,  24,  -1,  -1,  65,  -1,  67,  68,  69,  32,  -1,
        -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  25,  -1,  65,  -1,  67,  68,  69,
        32,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  27,  -1,  -1,  -1,  65,  32,  67,
        68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  29,  -1,  65,  32,  67,  68,  69,
        36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  31,  32,
        -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  32,  67,  68,
        69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  32,  67,  68,  69,  36,
        37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        55,  56,  57,  58,  59,  60,  -1,  62,  -1,  -1,  65,  32,  67,  68,  69,  36,  37,  38,
        39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,
        57,  58,  59,  60,  -1,  -1,  -1,  64,  65,  32,  67,  68,  69,  36,  37,  38,  39,  -1,
        41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,
        59,  60,  -1,  -1,  -1,  -1,  65,  32,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,
        43,  -1,  -1,  -1,  47,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,
        -1,  -1,  -1,  -1,  65,  32,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,
        45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,
        -1,  -1,  65,  32,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,
        -1,  -1,  -1,  50,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,
        65,  32,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,
        49,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  32,
        67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  -1,  67,  68,
        69,  36,  -1,  38,  -1,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  36,  -1,  67,  68,  69,  41,
        42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,
        60,  -1,  -1,  -1,  -1,  -1,  -1,  67,  68,  69
    };

    const unsigned char Parser::yystos_[] = {
        0,   3,   46,  84,  85,  17,  78,  152, 159, 160, 161, 162, 0,   1,   4,   5,   6,   7,
        8,   46,  86,  87,  88,  89,  90,  91,  92,  93,  16,  18,  19,  23,  30,  33,  34,  35,
        40,  41,  42,  44,  46,  53,  72,  73,  74,  75,  76,  77,  112, 113, 114, 115, 116, 117,
        118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 152,
        47,  54,  48,  51,  152, 153, 154, 152, 152, 152, 152, 159, 87,  46,  152, 155, 156, 157,
        157, 157, 112, 157, 112, 112, 112, 1,   57,  112, 1,   47,  111, 112, 153, 32,  36,  37,
        38,  39,  41,  42,  43,  55,  56,  57,  58,  59,  60,  65,  67,  68,  69,  63,  44,  141,
        3,   160, 44,  112, 142, 149, 150, 151, 152, 51,  44,  146, 43,  146, 50,  47,  159, 50,
        43,  17,  17,  24,  17,  45,  112, 45,  47,  47,  54,  62,  136, 137, 138, 139, 140, 153,
        112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 152,
        1,   45,  111, 112, 111, 112, 64,  64,  54,  49,  152, 1,   46,  145, 152, 156, 158, 64,
        48,  43,  64,  136, 143, 144, 88,  47,  136, 112, 112, 112, 112, 112, 45,  112, 112, 55,
        61,  141, 45,  45,  54,  112, 112, 150, 45,  159, 45,  54,  136, 1,   46,  94,  95,  152,
        11,  13,  15,  16,  18,  19,  20,  22,  23,  26,  48,  70,  96,  98,  99,  100, 103, 104,
        105, 106, 107, 108, 109, 110, 113, 116, 117, 118, 136, 57,  64,  155, 17,  29,  21,  25,
        31,  141, 47,  135, 136, 144, 112, 112, 47,  158, 43,  159, 49,  54,  1,   96,  97,  1,
        97,  157, 157, 157, 96,  116, 117, 118, 112, 112, 1,   97,  1,   97,  66,  43,  136, 136,
        112, 112, 112, 112, 112, 54,  56,  64,  45,  156, 112, 47,  94,  12,  12,  96,  14,  14,
        43,  17,  17,  24,  27,  49,  49,  71,  71,  112, 96,  10,  147, 136, 136, 152, 112, 112,
        112, 96,  48,  48,  9,   148, 56,  17,  21,  31,  21,  25,  1,   28,  52,  101, 102, 112,
        112, 48,  96,  96,  112, 96,  96,  49,  50,  50,  49,  101, 50,  49,  151, 21,  96,  96,
        96,  49,  96
    };

    const unsigned char Parser::yyr1_[] = {
        0,   83,  84,  85,  85,  86,  86,  87,  87,  87,  88,  88,  88,  88,  89,  90,  91,  91,
        92,  92,  93,  93,  94,  94,  94,  95,  95,  96,  96,  96,  96,  96,  96,  96,  96,  96,
        96,  96,  97,  97,  98,  99,  99,  100, 100, 101, 101, 101, 102, 102, 103, 104, 104, 105,
        106, 107, 107, 107, 107, 108, 108, 108, 108, 109, 110, 110, 110, 110, 110, 110, 111, 111,
        112, 112, 112, 112, 112, 112, 112, 112, 113, 113, 113, 113, 113, 113, 113, 113, 114, 114,
        114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114,
        115, 116, 116, 117, 117, 118, 119, 120, 121, 122, 123, 124, 124, 124, 125, 126, 126, 126,
        126, 126, 126, 126, 126, 127, 128, 128, 129, 130, 131, 132, 132, 133, 134, 135, 135, 136,
        136, 136, 136, 137, 138, 139, 140, 141, 141, 141, 142, 143, 143, 144, 144, 145, 145, 146,
        146, 146, 147, 147, 148, 148, 149, 149, 150, 150, 150, 151, 151, 152, 152, 153, 153, 154,
        154, 155, 155, 156, 157, 157, 158, 158, 159, 159, 160, 160, 161, 162
    };

    const unsigned char Parser::yyr2_[] = {
        0, 2, 2, 4, 1, 2, 1, 4, 1, 1, 1, 1, 1, 1, 6, 7, 5, 7, 8, 1, 2, 4, 1, 4, 1, 3, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 4, 6, 6, 6, 3, 3, 3, 2, 1, 6, 6, 8, 6, 2, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1,
        1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 3, 1, 2, 3,
        4, 5, 6, 6, 6, 6, 6, 2, 3, 3, 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        2, 3, 1, 1, 1, 1, 1, 1, 4, 6, 3, 3, 3, 2, 5, 3, 1, 1, 0, 3, 1, 3, 3, 0, 4, 0, 4, 0,
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
                                             "Expression",
                                             "TypeCastingExpression",
                                             "DirectCallExpression",
                                             "MethodCallExpression",
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
        0,    373,  373,  382,  388,  396,  402,  412,  418,  422,  430,  434,  438,  442,  450,
        458,  466,  471,  480,  496,  504,  527,  544,  548,  554,  562,  568,  582,  586,  590,
        594,  598,  602,  606,  610,  614,  618,  622,  630,  636,  646,  654,  658,  666,  670,
        678,  682,  686,  694,  700,  710,  718,  722,  730,  738,  746,  750,  754,  759,  768,
        772,  776,  781,  790,  800,  804,  808,  812,  816,  820,  832,  838,  848,  852,  856,
        860,  864,  868,  872,  876,  884,  888,  892,  896,  900,  904,  908,  912,  924,  928,
        932,  936,  940,  944,  948,  952,  956,  960,  964,  968,  972,  976,  980,  984,  988,
        992,  996,  1000, 1008, 1016, 1021, 1029, 1034, 1042, 1050, 1058, 1066, 1074, 1082, 1090,
        1095, 1099, 1107, 1119, 1123, 1127, 1131, 1135, 1139, 1143, 1147, 1155, 1163, 1168, 1177,
        1193, 1209, 1225, 1237, 1253, 1269, 1281, 1287, 1297, 1301, 1305, 1309, 1317, 1325, 1333,
        1341, 1353, 1357, 1361, 1370, 1384, 1390, 1400, 1404, 1412, 1418, 1428, 1432, 1436, 1448,
        1452, 1460, 1464, 1472, 1478, 1488, 1496, 1506, 1517, 1521, 1533, 1537, 1545, 1549, 1559,
        1565, 1579, 1583, 1592, 1600, 1606, 1614, 1620, 1632, 1638, 1647, 1651, 1659, 1667
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
#line 4145 "GrammarParser.cpp"               // lalr1.cc:1167
#line 1673 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1168

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
