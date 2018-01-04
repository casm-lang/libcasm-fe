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
            case 165:  // Attribute
                value.move< Attribute::Ptr >( that.value );
                break;

            case 164:  // Attributes
                value.move< Attributes::Ptr >( that.value );
                break;

            case 166:  // BasicAttribute
                value.move< BasicAttribute::Ptr >( that.value );
                break;

            case 143:  // BasicType
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

            case 144:  // ComposedType
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
            case 152:  // MaybeDefined
                value.move< Expression::Ptr >( that.value );
                break;

            case 167:  // ExpressionAttribute
                value.move< ExpressionAttribute::Ptr >( that.value );
                break;

            case 113:  // Terms
            case 147:  // Arguments
                value.move< Expressions::Ptr >( that.value );
                break;

            case 146:  // FixedSizedType
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

            case 157:  // Identifier
                value.move< Identifier::Ptr >( that.value );
                break;

            case 158:  // IdentifierPath
                value.move< IdentifierPath::Ptr >( that.value );
                break;

            case 159:  // DotSeparatedIdentifiers
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

            case 140:  // Assignment
                value.move< NamedExpression::Ptr >( that.value );
                break;

            case 139:  // Assignments
                value.move< NamedExpressions::Ptr >( that.value );
                break;

            case 138:  // NamedTupleLiteral
                value.move< NamedTupleLiteral::Ptr >( that.value );
                break;

            case 150:  // Parameters
            case 151:  // MaybeParameters
                value.move< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 136:  // RangeLiteral
                value.move< RangeLiteral::Ptr >( that.value );
                break;

            case 134:  // ReferenceLiteral
                value.move< ReferenceLiteral::Ptr >( that.value );
                break;

            case 145:  // RelationType
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

            case 137:  // TupleLiteral
                value.move< TupleLiteral::Ptr >( that.value );
                break;

            case 120:  // TypeCastingExpression
                value.move< TypeCastingExpression::Ptr >( that.value );
                break;

            case 141:  // Types
            case 148:  // FunctionParameters
            case 149:  // MaybeFunctionParameters
                value.move< Types::Ptr >( that.value );
                break;

            case 127:  // UndefinedLiteral
                value.move< UndefLiteral::Ptr >( that.value );
                break;

            case 124:  // UniversalQuantifierExpression
                value.move< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // UpdateRule
            case 155:  // Initializer
                value.move< UpdateRule::Ptr >( that.value );
                break;

            case 153:  // MaybeInitially
            case 154:  // Initializers
            case 156:  // MaybeInitializers
                value.move< UpdateRules::Ptr >( that.value );
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

            case 160:  // Variable
            case 161:  // TypedVariable
            case 162:  // AttributedVariable
            case 163:  // TypedAttributedVariable
                value.move< VariableDefinition::Ptr >( that.value );
                break;

            case 142:  // Type
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
            case 165:  // Attribute
                value.copy< Attribute::Ptr >( that.value );
                break;

            case 164:  // Attributes
                value.copy< Attributes::Ptr >( that.value );
                break;

            case 166:  // BasicAttribute
                value.copy< BasicAttribute::Ptr >( that.value );
                break;

            case 143:  // BasicType
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

            case 144:  // ComposedType
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
            case 152:  // MaybeDefined
                value.copy< Expression::Ptr >( that.value );
                break;

            case 167:  // ExpressionAttribute
                value.copy< ExpressionAttribute::Ptr >( that.value );
                break;

            case 113:  // Terms
            case 147:  // Arguments
                value.copy< Expressions::Ptr >( that.value );
                break;

            case 146:  // FixedSizedType
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

            case 157:  // Identifier
                value.copy< Identifier::Ptr >( that.value );
                break;

            case 158:  // IdentifierPath
                value.copy< IdentifierPath::Ptr >( that.value );
                break;

            case 159:  // DotSeparatedIdentifiers
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

            case 140:  // Assignment
                value.copy< NamedExpression::Ptr >( that.value );
                break;

            case 139:  // Assignments
                value.copy< NamedExpressions::Ptr >( that.value );
                break;

            case 138:  // NamedTupleLiteral
                value.copy< NamedTupleLiteral::Ptr >( that.value );
                break;

            case 150:  // Parameters
            case 151:  // MaybeParameters
                value.copy< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 136:  // RangeLiteral
                value.copy< RangeLiteral::Ptr >( that.value );
                break;

            case 134:  // ReferenceLiteral
                value.copy< ReferenceLiteral::Ptr >( that.value );
                break;

            case 145:  // RelationType
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

            case 137:  // TupleLiteral
                value.copy< TupleLiteral::Ptr >( that.value );
                break;

            case 120:  // TypeCastingExpression
                value.copy< TypeCastingExpression::Ptr >( that.value );
                break;

            case 141:  // Types
            case 148:  // FunctionParameters
            case 149:  // MaybeFunctionParameters
                value.copy< Types::Ptr >( that.value );
                break;

            case 127:  // UndefinedLiteral
                value.copy< UndefLiteral::Ptr >( that.value );
                break;

            case 124:  // UniversalQuantifierExpression
                value.copy< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // UpdateRule
            case 155:  // Initializer
                value.copy< UpdateRule::Ptr >( that.value );
                break;

            case 153:  // MaybeInitially
            case 154:  // Initializers
            case 156:  // MaybeInitializers
                value.copy< UpdateRules::Ptr >( that.value );
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

            case 160:  // Variable
            case 161:  // TypedVariable
            case 162:  // AttributedVariable
            case 163:  // TypedAttributedVariable
                value.copy< VariableDefinition::Ptr >( that.value );
                break;

            case 142:  // Type
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
                    case 165:  // Attribute
                        yylhs.value.build< Attribute::Ptr >();
                        break;

                    case 164:  // Attributes
                        yylhs.value.build< Attributes::Ptr >();
                        break;

                    case 166:  // BasicAttribute
                        yylhs.value.build< BasicAttribute::Ptr >();
                        break;

                    case 143:  // BasicType
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

                    case 144:  // ComposedType
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
                    case 152:  // MaybeDefined
                        yylhs.value.build< Expression::Ptr >();
                        break;

                    case 167:  // ExpressionAttribute
                        yylhs.value.build< ExpressionAttribute::Ptr >();
                        break;

                    case 113:  // Terms
                    case 147:  // Arguments
                        yylhs.value.build< Expressions::Ptr >();
                        break;

                    case 146:  // FixedSizedType
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

                    case 157:  // Identifier
                        yylhs.value.build< Identifier::Ptr >();
                        break;

                    case 158:  // IdentifierPath
                        yylhs.value.build< IdentifierPath::Ptr >();
                        break;

                    case 159:  // DotSeparatedIdentifiers
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

                    case 140:  // Assignment
                        yylhs.value.build< NamedExpression::Ptr >();
                        break;

                    case 139:  // Assignments
                        yylhs.value.build< NamedExpressions::Ptr >();
                        break;

                    case 138:  // NamedTupleLiteral
                        yylhs.value.build< NamedTupleLiteral::Ptr >();
                        break;

                    case 150:  // Parameters
                    case 151:  // MaybeParameters
                        yylhs.value.build< NodeList< VariableDefinition >::Ptr >();
                        break;

                    case 136:  // RangeLiteral
                        yylhs.value.build< RangeLiteral::Ptr >();
                        break;

                    case 134:  // ReferenceLiteral
                        yylhs.value.build< ReferenceLiteral::Ptr >();
                        break;

                    case 145:  // RelationType
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

                    case 137:  // TupleLiteral
                        yylhs.value.build< TupleLiteral::Ptr >();
                        break;

                    case 120:  // TypeCastingExpression
                        yylhs.value.build< TypeCastingExpression::Ptr >();
                        break;

                    case 141:  // Types
                    case 148:  // FunctionParameters
                    case 149:  // MaybeFunctionParameters
                        yylhs.value.build< Types::Ptr >();
                        break;

                    case 127:  // UndefinedLiteral
                        yylhs.value.build< UndefLiteral::Ptr >();
                        break;

                    case 124:  // UniversalQuantifierExpression
                        yylhs.value.build< UniversalQuantifierExpression::Ptr >();
                        break;

                    case 111:  // UpdateRule
                    case 155:  // Initializer
                        yylhs.value.build< UpdateRule::Ptr >();
                        break;

                    case 153:  // MaybeInitially
                    case 154:  // Initializers
                    case 156:  // MaybeInitializers
                        yylhs.value.build< UpdateRules::Ptr >();
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

                    case 160:  // Variable
                    case 161:  // TypedVariable
                    case 162:  // AttributedVariable
                    case 163:  // TypedAttributedVariable
                        yylhs.value.build< VariableDefinition::Ptr >();
                        break;

                    case 142:  // Type
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
#line 392 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            specification.setHeader(
                                yystack_[ 1 ].value.as< HeaderDefinition::Ptr >() );
                            specification.setDefinitions(
                                yystack_[ 0 ].value.as< Definitions::Ptr >() );
                        }
#line 1434 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 3:
#line 401 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< HeaderDefinition::Ptr >() = definition;
                        }
#line 1444 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 4:
#line 407 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< HeaderDefinition::Ptr >() =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                        }
#line 1452 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 5:
#line 415 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = yystack_[ 1 ].value.as< Definitions::Ptr >();
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1462 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 6:
#line 421 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = Ast::make< Definitions >( yylhs.location );
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1472 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 7:
#line 431 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition = yystack_[ 0 ].value.as< Definition::Ptr >();
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< Definition::Ptr >() = definition;
                        }
#line 1482 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 8:
#line 437 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< Definition::Ptr >();
                        }
#line 1490 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 9:
#line 441 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() = nullptr;
                        }
#line 1498 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 10:
#line 449 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< EnumerationDefinition::Ptr >();
                        }
#line 1506 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 11:
#line 453 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< DerivedDefinition::Ptr >();
                        }
#line 1514 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 12:
#line 457 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< RuleDefinition::Ptr >();
                        }
#line 1522 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 13:
#line 461 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< FunctionDefinition::Ptr >();
                        }
#line 1530 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 14:
#line 465 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< UsingDefinition::Ptr >();
                        }
#line 1538 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 15:
#line 473 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumerationDefinition::Ptr >() =
                                Ast::make< EnumerationDefinition >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 1 ].value.as< Enumerators::Ptr >() );
                        }
#line 1546 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 16:
#line 481 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DerivedDefinition::Ptr >() =
                                Ast::make< DerivedDefinition >(
                                    yylhs.location,
                                    yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                    yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1554 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 17:
#line 489 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Identifier::Ptr >(),
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                createVoidType( yylhs.location ),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1563 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 18:
#line 494 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1572 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 19:
#line 503 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
                            auto initializers = yystack_[ 0 ].value.as< UpdateRules::Ptr >();
                            for( auto& initializer : *initializers )
                            {
                                initializer->function()->setIdentifier(
                                    asIdentifierPath( identifier ) );
                            }
                            function->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = function;
                        }
#line 1592 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 20:
#line 519 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FunctionDefinition::Ptr >() =
                                yystack_[ 0 ]
                                    .value.as< FunctionDefinition::Ptr >();  // `init` special case
                        }
#line 1600 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 21:
#line 527 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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

                            auto initializers = Ast::make< UpdateRules >( yylhs.location );
                            initializers->add(
                                Ast::make< UpdateRule >( yylhs.location, program, ruleReference ) );
                            programDefinition->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = programDefinition;
                        }
#line 1627 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 22:
#line 550 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto programDefinition = createProgramFunction( yylhs.location );

                            // apply the name of the program declaration to the initializer
                            // functions
                            auto initializers = yystack_[ 1 ].value.as< UpdateRules::Ptr >();
                            for( auto& initializer : *initializers )
                            {
                                initializer->function()->setIdentifier(
                                    asIdentifierPath( programDefinition->identifier() ) );
                            }
                            programDefinition->setInitializers( initializers );

                            yylhs.value.as< FunctionDefinition::Ptr >() = programDefinition;
                        }
#line 1645 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 23:
#line 568 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() =
                                Ast::make< EnumeratorDefinition >(
                                    yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 1653 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 24:
#line 572 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerator = Ast::make< EnumeratorDefinition >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            enumerator->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = enumerator;
                        }
#line 1663 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 25:
#line 578 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = nullptr;
                        }
#line 1671 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 26:
#line 586 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = yystack_[ 2 ].value.as< Enumerators::Ptr >();
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1681 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 27:
#line 592 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = Ast::make< Enumerators >( yylhs.location );
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1691 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 28:
#line 602 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UsingDefinition::Ptr >() = Ast::make< UsingDefinition >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 1699 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 29:
#line 614 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SkipRule::Ptr >();
                        }
#line 1707 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 30:
#line 618 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalRule::Ptr >();
                        }
#line 1715 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 31:
#line 622 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CaseRule::Ptr >();
                        }
#line 1723 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 32:
#line 626 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< LetRule::Ptr >();
                        }
#line 1731 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 33:
#line 630 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ForallRule::Ptr >();
                        }
#line 1739 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 34:
#line 634 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseRule::Ptr >();
                        }
#line 1747 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 35:
#line 638 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< IterateRule::Ptr >();
                        }
#line 1755 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 36:
#line 642 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< BlockRule::Ptr >();
                        }
#line 1763 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 37:
#line 646 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SequenceRule::Ptr >();
                        }
#line 1771 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 38:
#line 650 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRule::Ptr >();
                        }
#line 1779 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 39:
#line 654 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CallRule::Ptr >();
                        }
#line 1787 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 40:
#line 662 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = yystack_[ 1 ].value.as< Rules::Ptr >();
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1797 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 41:
#line 668 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = Ast::make< Rules >( yylhs.location );
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1807 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 42:
#line 678 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SkipRule::Ptr >() =
                                Ast::make< SkipRule >( yylhs.location );
                        }
#line 1815 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 43:
#line 686 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1823 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 44:
#line 690 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Rule::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1831 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 45:
#line 698 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = Ast::make< CaseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Cases::Ptr >() );
                        }
#line 1839 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 46:
#line 702 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = nullptr;
                        }
#line 1847 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 47:
#line 710 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1855 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 48:
#line 714 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1863 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 49:
#line 718 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< ExpressionCase >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1871 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 50:
#line 726 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = yystack_[ 1 ].value.as< Cases::Ptr >();
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1881 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 51:
#line 732 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = Ast::make< Cases >( yylhs.location );
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1891 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 52:
#line 742 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetRule::Ptr >() = Ast::make< LetRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1899 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 53:
#line 750 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1907 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 54:
#line 754 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 6 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1915 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 55:
#line 762 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseRule::Ptr >() = Ast::make< ChooseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1923 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 56:
#line 770 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IterateRule::Ptr >() = Ast::make< IterateRule >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1931 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 57:
#line 778 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1939 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 58:
#line 782 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1947 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 59:
#line 786 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1956 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 60:
#line 791 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1965 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 61:
#line 800 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1973 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 62:
#line 804 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1981 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 63:
#line 808 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1990 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 64:
#line 813 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1999 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 65:
#line 822 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto function =
                                yystack_[ 2 ].value.as< DirectCallExpression::Ptr >();
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2009 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 66:
#line 832 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 2017 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 67:
#line 836 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 2025 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 68:
#line 840 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 2033 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 69:
#line 844 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 2041 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 70:
#line 848 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 2049 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 71:
#line 852 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 2057 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 72:
#line 864 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto expressions = yystack_[ 2 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2067 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 73:
#line 870 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2077 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 74:
#line 880 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2085 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 75:
#line 884 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TypeCastingExpression::Ptr >();
                        }
#line 2093 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 76:
#line 888 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2101 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 77:
#line 892 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LetExpression::Ptr >();
                        }
#line 2109 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 78:
#line 896 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalExpression::Ptr >();
                        }
#line 2117 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 79:
#line 900 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseExpression::Ptr >();
                        }
#line 2125 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 80:
#line 904 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UniversalQuantifierExpression::Ptr >();
                        }
#line 2133 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 81:
#line 908 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ExistentialQuantifierExpression::Ptr >();
                        }
#line 2141 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 82:
#line 916 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2149 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 83:
#line 920 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = nullptr;
                        }
#line 2157 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 84:
#line 924 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >();
                        }
#line 2165 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 85:
#line 928 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >();
                        }
#line 2173 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 86:
#line 932 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >();
                        }
#line 2181 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 87:
#line 936 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2189 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 88:
#line 948 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2197 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 89:
#line 952 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::INV_INSTRUCTION );
                        }
#line 2205 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 90:
#line 956 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::ADD_INSTRUCTION );
                        }
#line 2213 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 91:
#line 960 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::SUB_INSTRUCTION );
                        }
#line 2221 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 92:
#line 964 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MUL_INSTRUCTION );
                        }
#line 2229 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 93:
#line 968 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::DIV_INSTRUCTION );
                        }
#line 2237 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 94:
#line 972 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MOD_INSTRUCTION );
                        }
#line 2245 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 95:
#line 976 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::POW_INSTRUCTION );
                        }
#line 2253 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 96:
#line 980 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NEQ_INSTRUCTION );
                        }
#line 2261 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 97:
#line 984 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::EQU_INSTRUCTION );
                        }
#line 2269 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 98:
#line 988 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LTH_INSTRUCTION );
                        }
#line 2277 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 99:
#line 992 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GTH_INSTRUCTION );
                        }
#line 2285 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 100:
#line 996 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LEQ_INSTRUCTION );
                        }
#line 2293 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 101:
#line 1000 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GEQ_INSTRUCTION );
                        }
#line 2301 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 102:
#line 1004 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::OR_INSTRUCTION );
                        }
#line 2309 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 103:
#line 1008 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::XOR_INSTRUCTION );
                        }
#line 2317 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 104:
#line 1012 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::AND_INSTRUCTION );
                        }
#line 2325 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 105:
#line 1016 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2333 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 106:
#line 1020 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2341 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 107:
#line 1024 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NOT_INSTRUCTION );
                        }
#line 2349 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 108:
#line 1032 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< IdentifierPath::Ptr >(),
                                    arguments );
                        }
#line 2358 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 109:
#line 1037 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< IdentifierPath::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2366 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 110:
#line 1045 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2375 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 111:
#line 1050 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 3 ].value.as< Expression::Ptr >(),
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2383 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 112:
#line 1058 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IndirectCallExpression::Ptr >() =
                                Ast::make< IndirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2391 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 113:
#line 1066 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TypeCastingExpression::Ptr >() =
                                Ast::make< TypeCastingExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2399 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 114:
#line 1074 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetExpression::Ptr >() = Ast::make< LetExpression >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2407 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 115:
#line 1082 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalExpression::Ptr >() =
                                Ast::make< ConditionalExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Expression::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2415 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 116:
#line 1090 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseExpression::Ptr >() =
                                Ast::make< ChooseExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2423 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 117:
#line 1098 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UniversalQuantifierExpression::Ptr >() =
                                Ast::make< UniversalQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2431 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 118:
#line 1106 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExistentialQuantifierExpression::Ptr >() =
                                Ast::make< ExistentialQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2439 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 119:
#line 1118 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UndefLiteral::Ptr >();
                        }
#line 2447 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 120:
#line 1122 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2455 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 121:
#line 1126 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2463 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 122:
#line 1130 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2471 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 123:
#line 1134 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2479 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 124:
#line 1138 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2487 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 125:
#line 1142 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2495 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 126:
#line 1146 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ReferenceLiteral::Ptr >();
                        }
#line 2503 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 127:
#line 1150 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ListLiteral::Ptr >();
                        }
#line 2511 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 128:
#line 1154 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< RangeLiteral::Ptr >();
                        }
#line 2519 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 129:
#line 1158 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TupleLiteral::Ptr >();
                        }
#line 2527 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 130:
#line 1162 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< NamedTupleLiteral::Ptr >();
                        }
#line 2535 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 131:
#line 1170 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UndefLiteral::Ptr >() =
                                Ast::make< UndefLiteral >( yylhs.location );
                        }
#line 2543 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 132:
#line 1178 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
                            yylhs.value.as< ValueLiteral::Ptr >() =
                                Ast::make< ValueLiteral >( yylhs.location, value );
                        }
#line 2552 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 133:
#line 1183 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
                            yylhs.value.as< ValueLiteral::Ptr >() =
                                Ast::make< ValueLiteral >( yylhs.location, value );
                        }
#line 2561 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 134:
#line 1192 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2577 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 135:
#line 1208 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2593 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 136:
#line 1224 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2609 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 137:
#line 1240 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2625 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 138:
#line 1252 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2641 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 139:
#line 1268 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2657 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 140:
#line 1284 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ReferenceLiteral::Ptr >() =
                                Ast::make< ReferenceLiteral >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2665 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 141:
#line 1292 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< ListLiteral::Ptr >() =
                                Ast::make< ListLiteral >( yylhs.location, expressions );
                        }
#line 2674 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 142:
#line 1297 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListLiteral::Ptr >() = Ast::make< ListLiteral >(
                                yylhs.location, yystack_[ 1 ].value.as< Expressions::Ptr >() );
                        }
#line 2682 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 143:
#line 1301 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListLiteral::Ptr >() = nullptr;
                        }
#line 2690 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 144:
#line 1309 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RangeLiteral::Ptr >() = Ast::make< RangeLiteral >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Expression::Ptr >() );
                        }
#line 2698 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 145:
#line 1316 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = yystack_[ 3 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 1 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< TupleLiteral::Ptr >() =
                                Ast::make< TupleLiteral >( yylhs.location, expressions );
                        }
#line 2708 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 146:
#line 1324 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NamedTupleLiteral::Ptr >() =
                                Ast::make< NamedTupleLiteral >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< NamedExpressions::Ptr >() );
                        }
#line 2716 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 147:
#line 1331 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto assignments = yystack_[ 2 ].value.as< NamedExpressions::Ptr >();
                            assignments->add( yystack_[ 0 ].value.as< NamedExpression::Ptr >() );
                            yylhs.value.as< NamedExpressions::Ptr >() = assignments;
                        }
#line 2726 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 148:
#line 1337 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto assignments = Ast::make< NamedExpressions >( yylhs.location );
                            assignments->add( yystack_[ 0 ].value.as< NamedExpression::Ptr >() );
                            yylhs.value.as< NamedExpressions::Ptr >() = assignments;
                        }
#line 2736 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 149:
#line 1346 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NamedExpression::Ptr >() = Ast::make< NamedExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2744 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 150:
#line 1358 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2754 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 151:
#line 1364 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2764 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 152:
#line 1374 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< BasicType::Ptr >();
                        }
#line 2772 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 153:
#line 1378 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2780 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 154:
#line 1382 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< RelationType::Ptr >();
                        }
#line 2788 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 155:
#line 1386 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< FixedSizedType::Ptr >();
                        }
#line 2796 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 156:
#line 1394 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicType::Ptr >() = Ast::make< BasicType >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2804 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 157:
#line 1402 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ComposedType::Ptr >() = Ast::make< ComposedType >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 1 ].value.as< Types::Ptr >() );
                        }
#line 2812 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 158:
#line 1410 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RelationType::Ptr >() = Ast::make< RelationType >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 3 ].value.as< Types::Ptr >(),
                                yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2820 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 159:
#line 1418 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FixedSizedType::Ptr >() = Ast::make< FixedSizedType >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2828 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 160:
#line 1430 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() =
                                yystack_[ 1 ].value.as< Expressions::Ptr >();
                        }
#line 2836 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 161:
#line 1434 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() = nullptr;
                        }
#line 2844 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 162:
#line 1438 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2853 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 163:
#line 1452 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2863 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 164:
#line 1458 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2873 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 165:
#line 1468 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = yystack_[ 0 ].value.as< Types::Ptr >();
                        }
#line 2881 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 166:
#line 1472 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = Ast::make< Types >( yylhs.location );
                        }
#line 2889 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 167:
#line 1480 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >();
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2899 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 168:
#line 1486 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2909 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 169:
#line 1496 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< VariableDefinition >::Ptr >();
                        }
#line 2917 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 170:
#line 1500 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = nullptr;
                        }
#line 2925 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 171:
#line 1504 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                        }
#line 2933 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 172:
#line 1516 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2941 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 173:
#line 1520 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                Ast::make< UndefLiteral >( yylhs.location );
                        }
#line 2949 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 174:
#line 1528 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                yystack_[ 1 ].value.as< UpdateRules::Ptr >();
                        }
#line 2957 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 175:
#line 1532 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                Ast::make< UpdateRules >( yylhs.location );
                        }
#line 2965 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 176:
#line 1540 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers = yystack_[ 2 ].value.as< UpdateRules::Ptr >();
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< UpdateRules::Ptr >() = initializers;
                        }
#line 2975 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 177:
#line 1546 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers = Ast::make< UpdateRules >( yylhs.location );
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< UpdateRules::Ptr >() = initializers;
                        }
#line 2985 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 178:
#line 1556 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2997 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 179:
#line 1564 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 3011 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 180:
#line 1574 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            // the unknown function identifier will be replaced in
                            // FunctionDefinition
                            const auto function = Ast::make< DirectCallExpression >(
                                yylhs.location,
                                nullptr,
                                yystack_[ 2 ].value.as< TupleLiteral::Ptr >()->expressions() );
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 3022 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 181:
#line 1585 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRules::Ptr >();
                        }
#line 3030 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 182:
#line 1589 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                Ast::make< UpdateRules >( yylhs.location );
                        }
#line 3038 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 183:
#line 1601 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() = Ast::make< Identifier >(
                                yylhs.location, yystack_[ 0 ].value.as< std::string >() );
                        }
#line 3046 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 184:
#line 1605 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() =
                                Ast::make< Identifier >( yylhs.location, "in" );
                        }
#line 3054 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 185:
#line 1613 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Identifiers::Ptr >(),
                                IdentifierPath::Type::ABSOLUTE );
                        }
#line 3062 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 186:
#line 1617 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
                        }
#line 3072 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 187:
#line 1627 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = yystack_[ 2 ].value.as< Identifiers::Ptr >();
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 3082 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 188:
#line 1633 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 3092 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 189:
#line 1647 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3100 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 190:
#line 1651 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto unresolvedType =
                                Ast::make< UnresolvedType >( yylhs.location );
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    unresolvedType );
                        }
#line 3109 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 191:
#line 1660 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 3117 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 192:
#line 1668 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3127 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 193:
#line 1674 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3135 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 194:
#line 1682 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3145 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 195:
#line 1688 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3153 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 196:
#line 1699 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = yystack_[ 2 ].value.as< Attributes::Ptr >();
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3163 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 197:
#line 1705 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = Ast::make< Attributes >( yylhs.location );
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3173 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 198:
#line 1714 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< BasicAttribute::Ptr >();
                        }
#line 3181 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 199:
#line 1718 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< ExpressionAttribute::Ptr >();
                        }
#line 3189 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 200:
#line 1726 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicAttribute::Ptr >() = Ast::make< BasicAttribute >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 3197 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 201:
#line 1734 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExpressionAttribute::Ptr >() =
                                Ast::make< ExpressionAttribute >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 3205 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

#line 3209 "GrammarParser.cpp"  // lalr1.cc:859
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

    const short int Parser::yypact_ninf_ = -233;

    const short int Parser::yytable_ninf_ = -165;

    const short int Parser::yypact_[] = {
        2,    -233, -2,   23,   200,  -233, -233, 1497, -26,  -233, -233, -233, -233, -233, -9,
        -2,   -2,   -2,   -2,   -2,   -2,   169,  -233, -233, -233, -233, -233, -233, -233, -233,
        -6,   -6,   -6,   1497, -6,   -233, -233, -233, 1497, 1497, 1497, 905,  968,  -2,   -4,
        -233, -233, -233, -233, -233, -233, 2254, -40,  -233, -233, -233, -233, -233, -233, -233,
        -233, -233, -233, -233, -233, -233, -233, -233, -233, -233, -233, -233, -233, -233, -233,
        -233, -233, 13,   10,   36,   -2,   1497, -233, 27,   40,   27,   44,   46,   30,   -233,
        -2,   52,   -233, -233, 45,   56,   84,   1765, 110,  -233, -233, -233, 11,   1497, 77,
        1982, -1,   -233, 80,   90,   -233, 38,   2016, -233, -233, -4,   1497, 1497, 1497, 1497,
        1497, 1497, 1497, 1497, 1497, 1497, 1497, 1497, 1497, 1497, 1497, 1497, 1497, -2,   1031,
        -233, -2,   -233, -233, 2050, 87,   88,   -233, 92,   3,    91,   96,   -27,  -4,   -4,
        213,  39,   -4,   1497, 1497, 1497, 1497, 1497, -233, 2084, 1497, -233, -233, -2,   1497,
        -233, -233, 1497, 1497, -233, -233, -233, -233, -233, -37,  778,  426,  389,  2288, 76,
        76,   255,  137,  137,  93,   93,   93,   -233, 2288, 255,  137,  137,  13,   109,  -233,
        0,    2254, -233, 1497, 1497, 1497, -233, 112,  -2,   1,    52,   -233, -233, -4,   12,
        1371, -4,   -233, -233, 101,  97,   -233, -2,   -233, 1523, 1909, 1647, 1841, 1948, 13,
        2118, -233, 80,   2254, 2254, 2152, -4,   1497, -233, -233, -233, 2254, 2254, -233, -233,
        51,   -233, -3,   119,  -233, -2,   -233, -13,  -233, 575,  643,  -233, -6,   -6,   -6,
        1371, 488,  1497, 1497, 711,  779,  -233, -233, -233, -233, -233, -233, -233, -233, -233,
        -233, -233, -233, -40,  34,   102,  104,  121,  -4,   -4,   -233, 1497, 1497, 1497, 1497,
        1497, -233, -233, -233, 6,    -5,   106,  -233, -2,   -233, 1497, 78,   -233, 12,   159,
        -233, 1099, 166,  1167, 139,  168,  170,  -233, 125,  102,  104,  1803, 1875, 140,  1235,
        122,  1303, 1497, 1371, -233, 188,  2254, 2254, 2254, 2254, 2254, -4,   -233, -4,   -233,
        2254, -2,   -233, -233, -233, -233, -233, -233, 1497, 1497, 1497, 1371, 153,  -233, -233,
        -233, -233, 2254, -233, 161,  201,  -233, 156,  -233, 1567, 1607, 1687, 198,  842,  1497,
        165,  -233, -233, 1371, 1371, 1497, 1371, 1371, 177,  180,  181,  -233, 1434, 2186, 2220,
        1497, -233, -233, 1727, -233, -233, -233, 1371, 1371, -233, -233, 1371, -233, 183,  1371,
        -233, -233, -233, -233, -233
    };

    const unsigned char Parser::yydefact_[] = {
        0,   4,   0,   0,   0,   184, 183, 200, 0,   197, 198, 199, 1,   9,   0,   0,   0,   0,
        0,   0,   0,   0,   6,   8,   10,  11,  12,  13,  20,  14,  0,   0,   0,   0,   0,   131,
        133, 132, 0,   0,   0,   0,   0,   0,   0,   137, 138, 134, 135, 136, 139, 201, 74,  76,
        84,  85,  86,  75,  77,  78,  79,  80,  81,  87,  119, 120, 121, 122, 123, 124, 125, 126,
        127, 128, 129, 130, 188, 108, 185, 0,   0,   182, 21,  171, 0,   171, 0,   0,   0,   5,
        0,   190, 193, 189, 0,   0,   0,   0,   0,   107, 88,  89,  0,   0,   0,   73,  0,   148,
        188, 0,   141, 0,   73,  186, 140, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   109, 0,   3,   196, 178, 129, 181, 177, 0,
        0,   0,   0,   0,   0,   166, 0,   0,   0,   0,   0,   0,   0,   0,   83,  0,   0,   82,
        146, 0,   0,   143, 142, 0,   0,   113, 152, 153, 154, 155, 156, 104, 102, 103, 106, 90,
        91,  97,  98,  99,  92,  93,  94,  95,  105, 96,  100, 101, 110, 0,   162, 0,   73,  187,
        0,   0,   0,   22,  0,   0,   0,   0,   195, 168, 0,   0,   0,   0,   28,  164, 165, 0,
        7,   0,   191, 0,   0,   0,   0,   0,   0,   72,  147, 0,   149, 72,  0,   166, 0,   111,
        161, 160, 179, 180, 176, 170, 0,   169, 0,   0,   25,  0,   27,  0,   23,  0,   0,   42,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   17,  29,  30,  31,  32,  33,  34,  35,  36,
        37,  38,  39,  0,   67,  69,  71,  0,   0,   0,   192, 0,   0,   0,   0,   0,   112, 145,
        144, 0,   151, 0,   159, 0,   167, 0,   0,   15,  0,   0,   41,  0,   0,   0,   0,   0,
        0,   56,  66,  68,  70,  0,   0,   0,   0,   0,   0,   0,   0,   163, 173, 114, 117, 116,
        115, 118, 0,   157, 0,   194, 16,  0,   26,  64,  62,  40,  60,  58,  0,   0,   0,   0,
        0,   59,  57,  63,  61,  65,  18,  0,   175, 150, 0,   24,  0,   0,   0,   43,  0,   0,
        0,   19,  158, 0,   0,   0,   0,   0,   0,   0,   0,   51,  0,   0,   0,   182, 52,  53,
        0,   55,  44,  46,  0,   0,   45,  50,  0,   172, 0,   0,   47,  48,  49,  174, 54
    };

    const short int Parser::yypgoto_[] = {
        -233, -233, -233, -233, 215,  94,   -233, -233, -233, -233, -233, -61,  -233, -233,
        218,  -232, -233, -233, -233, -134, -233, -233, -233, -233, -233, -233, -233, -233,
        -233, -39,  -7,   5,    -233, 89,   126,  163,  -233, -233, -233, -233, -233, -233,
        -233, -233, -233, -233, -233, -233, -233, -233, -233, -233, -233, -70,  -233, -233,
        79,   -233, -44,  -233, -233, -233, -233, -172, -233, 8,    -233, 155,  -233, -233,
        -233, 41,   -132, 49,   -8,   -233, 28,   -142, -24,  4,    -19,  173,  -233, -233
    };

    const short int Parser::yydefgoto_[] = {
        -1,  3,   4,   21,  22,  23,  24,  25,  26,  27,  28,  246, 247, 29,  300, 301, 262,
        263, 264, 371, 372, 265, 266, 267, 268, 269, 270, 271, 272, 104, 139, 52,  53,  54,
        55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,
        72,  73,  74,  75,  106, 107, 289, 169, 170, 171, 172, 173, 135, 214, 215, 204, 145,
        350, 361, 141, 142, 143, 76,  77,  78,  92,  93,  94,  207, 8,   9,   10,  11
    };

    const short int Parser::yytable_[] = {
        51,  88,  206, 111, 202, 1,   82,   95,  96,  5,   98,  140, 5,   244, 5,   5,   5,   210,
        303, 231, 233, 5,   79,  12,  133,  232, 97,  314, 316, 80,  5,   99,  100, 101, 105, 112,
        114, 297, 211, 137, 81,  90,  298,  43,  203, 162, 235, 241, 43,  2,   203, 7,   286, -164,
        163, 167, 242, 158, 134, 245, -164, 326, 136, 327, 83,  84,  85,  86,  87,  7,   6,   151,
        144, 6,   154, 6,   6,   6,   150,  91,  91,  91,  6,   91,  146, 80,  166, 217, 148, 153,
        108, 6,   113, 167, 80,  195, 159,  149, -84, 293, 206, 317, 155, 152, 212, 213, 80,  174,
        218, 175, 176, 177, 178, 179, 180,  181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
        331, 196, 157, 7,   140, 164, 160,  80,  125, 126, 127, 128, 165, 7,   174, 174, 201, 200,
        174, 209, 219, 220, 221, 222, 223,  329, 199, 225, 128, 234, 208, 228, 239, 278, 229, 230,
        279, 295, 243, 318, -85, 277, -86,  -2,  13,  328, 333, 14,  15,  16,  17,  18,  19,  120,
        121, 336, 192, 338, 240, 197, 339,  290, 340, -84, 343, 236, 237, 205, 345, 125, 126, 127,
        128, 349, 174, 13,  358, 174, 14,   15,  16,  17,  18,  19,  359, 360, 227, 362, 375, 273,
        20,  14,  15,  16,  17,  18,  19,   174, 367, 292, 296, 381, 304, 305, 306, 382, 383, 393,
        319, 320, 89,  332, 385, 291, 147,  238, 226, 388, 216, 280, 294, 20,  0,   0,   311, 312,
        7,   138, 273, 273, 0,   0,   248,  0,   273, 273, 0,   0,   273, 273, 91,  0,   0,   0,
        174, 174, 0,   0,   321, 322, 323,  324, 325, 0,   0,   0,   351, 0,   352, 0,   0,   0,
        330, 0,   0,   205, 0,   0,   7,    0,   0,   120, 121, 274, 0,   91,  91,  91,  0,   140,
        273, 0,   273, 0,   347, 123, 124,  125, 126, 127, 128, 0,   174, 273, 174, 273, 0,   273,
        131, 132, 0,   0,   0,   0,   0,    354, 355, 356, 0,   0,   275, 0,   274, 274, 0,   0,
        205, 0,   274, 308, 273, 248, 274,  274, 0,   373, 374, 0,   0,   0,   0,   0,   378, 0,
        0,   0,   0,   0,   0,   373, 0,    0,   273, 273, 0,   273, 273, 276, 0,   275, 275, 0,
        0,   0,   353, 275, 309, 0,   0,    275, 275, 273, 273, 0,   274, 273, 274, 0,   273, 0,
        0,   0,   0,   0,   0,   0,   0,    274, 0,   274, 0,   274, 0,   0,   0,   0,   276, 276,
        0,   0,   0,   0,   276, 310, 0,    0,   276, 276, 0,   0,   116, 275, 261, 275, 274, 120,
        121, 122, 0,   0,   0,   0,   0,    0,   275, 0,   275, 0,   275, 123, 124, 125, 126, 127,
        128, 0,   274, 274, 0,   274, 274,  130, 131, 132, 0,   0,   0,   116, 276, 118, 276, 275,
        120, 121, 122, 274, 274, 307, 0,    274, 0,   276, 274, 276, 0,   276, 123, 124, 125, 126,
        127, 128, 0,   275, 275, 0,   275,  275, 130, 131, 132, 0,   0,   0,   0,   0,   0,   0,
        276, 0,   5,   0,   275, 275, 0,    0,   275, 0,   0,   275, 0,   0,   0,   335, 0,   335,
        35,  36,  37,  0,   276, 276, 0,    276, 276, 0,   335, 41,  335, 42,  348, 0,   0,   0,
        43,  0,   44,  0,   0,   276, 276,  0,   0,   276, 0,   0,   276, 0,   0,   0,   0,   0,
        0,   357, 0,   45,  46,  47,  48,   49,  50,  6,   0,   0,   0,   0,   0,   0,   0,   0,
        299, 0,   0,   0,   0,   376, 377,  0,   379, 380, 0,   249, 0,   250, 0,   251, 252, 5,
        253, 254, 255, 0,   256, 257, 390,  391, 258, 0,   392, 0,   0,   394, 0,   35,  36,  37,
        0,   0,   0,   0,   0,   0,   0,    0,   41,  0,   42,  0,   259, 0,   0,   43,  0,   44,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   302, 0,   260, 0,
        45,  46,  47,  48,  49,  50,  6,    249, 0,   250, 0,   251, 252, 5,   253, 254, 255, 0,
        256, 257, 0,   0,   258, 0,   0,    0,   0,   0,   0,   35,  36,  37,  0,   0,   0,   0,
        0,   0,   0,   0,   41,  0,   42,   0,   259, 0,   0,   43,  0,   44,  0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   313, 0,   260, 0,   45,  46,  47,  48,
        49,  50,  6,   249, 0,   250, 0,    251, 252, 5,   253, 254, 255, 0,   256, 257, 0,   0,
        258, 0,   0,   0,   0,   0,   0,    35,  36,  37,  0,   0,   0,   0,   0,   0,   0,   0,
        41,  0,   42,  0,   259, 0,   0,    43,  0,   44,  0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   315,  0,   260, 0,   45,  46,  47,  48,  49,  50,  6,   249,
        0,   250, 0,   251, 252, 5,   253,  254, 255, 0,   256, 257, 0,   0,   258, 0,   0,   0,
        0,   0,   0,   35,  36,  37,  0,    0,   0,   0,   120, 121, 122, 0,   41,  0,   42,  0,
        259, 0,   0,   43,  0,   44,  123,  124, 125, 126, 127, 128, 0,   0,   0,   368, 0,   0,
        130, 131, 132, 0,   260, 0,   45,   46,  47,  48,  49,  50,  6,   30,  5,   31,  32,  0,
        0,   0,   33,  0,   0,   0,   0,    369, 0,   34,  0,   0,   35,  36,  37,  0,   0,   0,
        0,   38,  39,  40,  0,   41,  0,    42,  0,   0,   0,   0,   43,  370, 44,  0,   0,   0,
        0,   0,   0,   0,   0,   0,   102,  0,   0,   0,   0,   0,   0,   0,   0,   45,  46,  47,
        48,  49,  50,  6,   30,  5,   31,   32,  0,   0,   0,   33,  0,   0,   0,   0,   0,   0,
        34,  0,   0,   35,  36,  37,  0,    0,   0,   0,   38,  39,  40,  0,   41,  0,   42,  0,
        0,   0,   0,   43,  0,   44,  0,    0,   0,   103, 0,   0,   0,   0,   0,   109, 0,   0,
        0,   0,   0,   0,   0,   0,   45,   46,  47,  48,  49,  50,  6,   30,  5,   31,  32,  0,
        0,   0,   33,  0,   0,   0,   0,    0,   0,   34,  0,   0,   35,  36,  37,  0,   0,   0,
        0,   38,  39,  40,  0,   41,  0,    42,  110, 0,   0,   0,   43,  0,   44,  0,   0,   0,
        0,   0,   0,   0,   0,   0,   193,  0,   0,   0,   0,   0,   0,   0,   0,   45,  46,  47,
        48,  49,  50,  6,   30,  5,   31,   32,  0,   0,   0,   33,  0,   0,   0,   0,   0,   0,
        34,  0,   0,   35,  36,  37,  0,    0,   0,   0,   38,  39,  40,  0,   41,  194, 42,  0,
        0,   0,   0,   43,  0,   44,  0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   45,   46,  47,  48,  49,  50,  6,   249, 334, 250, 0,   251,
        252, 5,   253, 254, 255, 0,   256,  257, 0,   0,   258, 0,   0,   0,   0,   0,   0,   35,
        36,  37,  0,   0,   0,   0,   0,    0,   0,   0,   41,  0,   42,  0,   259, 0,   0,   43,
        0,   44,  0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        260, 0,   45,  46,  47,  48,  49,   50,  6,   249, 0,   250, 337, 251, 252, 5,   253, 254,
        255, 0,   256, 257, 0,   0,   258,  0,   0,   0,   0,   0,   0,   35,  36,  37,  0,   0,
        0,   0,   0,   0,   0,   0,   41,   0,   42,  0,   259, 0,   0,   43,  0,   44,  0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   260, 0,   45,  46,
        47,  48,  49,  50,  6,   249, 0,    250, 0,   251, 252, 5,   253, 254, 255, 0,   256, 257,
        0,   0,   258, 0,   0,   0,   0,    0,   0,   35,  36,  37,  0,   0,   0,   0,   0,   0,
        0,   0,   41,  0,   42,  0,   259,  344, 0,   43,  0,   44,  0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   260, 0,   45,  46,  47,  48,  49,  50,
        6,   249, 0,   250, 0,   251, 252,  5,   253, 254, 255, 0,   256, 257, 0,   0,   258, 0,
        0,   0,   0,   0,   0,   35,  36,   37,  0,   0,   0,   0,   0,   0,   0,   0,   41,  0,
        42,  0,   259, 0,   0,   43,  0,    44,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   260,  346, 45,  46,  47,  48,  49,  50,  6,   249, 0,   250,
        0,   251, 252, 5,   253, 254, 255,  0,   256, 257, 0,   0,   258, 0,   0,   0,   0,   0,
        0,   35,  36,  37,  0,   0,   0,    0,   0,   0,   0,   0,   41,  0,   42,  0,   259, 0,
        0,   43,  0,   44,  0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   260, 0,   45,  46,  47,   48,  49,  50,  6,   30,  5,   31,  32,  0,   0,   0,
        33,  0,   0,   0,   0,   369, 0,    34,  0,   0,   35,  36,  37,  0,   0,   0,   0,   38,
        39,  40,  0,   41,  0,   42,  0,    0,   384, 0,   43,  370, 44,  0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   45,  46,  47,  48,  49,
        50,  6,   30,  5,   31,  32,  0,    0,   0,   33,  0,   0,   0,   0,   0,   0,   34,  0,
        0,   35,  36,  37,  0,   0,   0,    0,   38,  39,  40,  281, 41,  0,   42,  0,   0,   0,
        0,   43,  0,   44,  0,   0,   0,    0,   115, 0,   0,   0,   116, 117, 118, 119, 0,   120,
        121, 122, 0,   0,   45,  46,  47,   48,  49,  50,  6,   0,   0,   123, 124, 125, 126, 127,
        128, 363, 0,   0,   0,   129, 0,    130, 131, 132, 0,   0,   0,   0,   0,   0,   115, 0,
        0,   0,   116, 117, 118, 119, 0,    120, 121, 122, 0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   123, 124, 125, 126,  127, 128, 364, 0,   0,   0,   129, 0,   130, 131, 132,
        0,   365, 115, 0,   0,   0,   116,  117, 118, 119, 0,   120, 121, 122, 0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,    123, 124, 125, 126, 127, 128, 283, 0,   0,   0,   129,
        0,   130, 131, 132, 0,   0,   115,  0,   0,   0,   116, 117, 118, 119, 0,   120, 121, 122,
        0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   123, 124, 125, 126, 127, 128, 366,
        0,   0,   0,   129, 0,   130, 131,  132, 0,   0,   115, 0,   0,   0,   116, 117, 118, 119,
        0,   120, 121, 122, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   123, 124, 125,
        126, 127, 128, 389, 0,   0,   0,    129, 0,   130, 131, 132, 0,   0,   115, 0,   0,   0,
        116, 117, 118, 119, 0,   120, 121,  122, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   123, 124, 125, 126, 127, 128,  0,   156, 0,   0,   129, 0,   130, 131, 132, 115, 0,
        0,   0,   116, 117, 118, 119, 0,    120, 121, 122, 0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   123, 124, 125, 126,  127, 128, 0,   341, 0,   0,   129, 0,   130, 131, 132,
        115, 0,   0,   0,   116, 117, 118,  119, 0,   120, 121, 122, 0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   123, 124,  125, 126, 127, 128, 0,   0,   284, 0,   129, 0,   130,
        131, 132, 115, 0,   0,   0,   116,  117, 118, 119, 0,   120, 121, 122, 0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,    123, 124, 125, 126, 127, 128, 342, 0,   0,   0,   129,
        115, 130, 131, 132, 116, 117, 118,  119, 0,   120, 121, 122, 0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   123, 124,  125, 126, 127, 128, 0,   0,   282, 0,   129, 115, 130,
        131, 132, 116, 117, 118, 119, 0,    120, 121, 122, 0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   123, 124, 125, 126,  127, 128, 0,   0,   0,   0,   129, 0,   130, 131, 132,
        285, 115, 0,   0,   0,   116, 117,  118, 119, 0,   120, 121, 122, 0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   123,  124, 125, 126, 127, 128, 0,   0,   0,   0,   129, 115,
        130, 131, 132, 116, 117, 118, 119,  0,   120, 121, 122, 0,   161, 0,   0,   0,   0,   0,
        0,   0,   0,   0,   123, 124, 125,  126, 127, 128, 0,   0,   0,   0,   129, 115, 130, 131,
        132, 116, 117, 118, 119, 0,   120,  121, 122, 0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   123, 124, 125, 126, 127,  128, 0,   168, 0,   0,   129, 115, 130, 131, 132, 116,
        117, 118, 119, 0,   120, 121, 122,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        123, 124, 125, 126, 127, 128, 0,    0,   0,   198, 129, 115, 130, 131, 132, 116, 117, 118,
        119, 0,   120, 121, 122, 0,   224,  0,   0,   0,   0,   0,   0,   0,   0,   0,   123, 124,
        125, 126, 127, 128, 0,   0,   0,    0,   129, 115, 130, 131, 132, 116, 117, 118, 119, 0,
        120, 121, 122, 0,   287, 0,   0,    0,   0,   0,   0,   0,   0,   0,   123, 124, 125, 126,
        127, 128, 0,   0,   0,   0,   129,  115, 130, 131, 132, 116, 117, 118, 119, 0,   120, 121,
        122, 0,   0,   0,   288, 0,   0,    0,   0,   0,   0,   0,   123, 124, 125, 126, 127, 128,
        0,   0,   0,   0,   129, 115, 130,  131, 132, 116, 117, 118, 119, 0,   120, 121, 122, 0,
        0,   0,   0,   0,   0,   386, 0,    0,   0,   0,   123, 124, 125, 126, 127, 128, 0,   0,
        0,   0,   129, 115, 130, 131, 132,  116, 117, 118, 119, 0,   120, 121, 122, 0,   0,   0,
        0,   0,   387, 0,   0,   0,   0,    0,   123, 124, 125, 126, 127, 128, 0,   0,   0,   0,
        129, 115, 130, 131, 132, 116, 117,  118, 119, 0,   120, 121, 122, 0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   123,  124, 125, 126, 127, 128, 0,   0,   0,   0,   129, 0,
        130, 131, 132, 116, 117, 118, 0,    0,   120, 121, 122, 0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   123, 124, 125,  126, 127, 128, 0,   0,   0,   0,   0,   0,   130, 131,
        132
    };

    const short int Parser::yycheck_[] = {
        7,   20,  144, 42,  1,   3,   14,  31,  32,  18,  34,  81,  18,  1,   18,  18,  18,  44,
        250, 56,  192, 18,  48,  0,   64,  62,  33,  259, 260, 55,  18,  38,  39,  40,  41,  42,
        44,  50,  65,  3,   49,  47,  55,  52,  47,  46,  46,  46,  52,  47,  47,  2,   224, 58,
        55,  55,  55,  46,  45,  47,  65,  55,  52,  57,  15,  16,  17,  18,  19,  20,  79,  90,
        45,  79,  18,  79,  79,  79,  48,  30,  31,  32,  79,  34,  44,  55,  48,  48,  44,  44,
        41,  79,  43,  55,  55,  134, 103, 51,  64,  48,  242, 67,  18,  51,  148, 149, 55,  115,
        152, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132,
        48,  134, 18,  80,  200, 51,  55,  55,  58,  59,  60,  61,  48,  90,  148, 149, 50,  55,
        152, 49,  153, 154, 155, 156, 157, 293, 65,  160, 61,  46,  65,  164, 46,  58,  167, 168,
        65,  44,  208, 44,  64,  211, 64,  0,   1,   65,  13,  4,   5,   6,   7,   8,   9,   42,
        43,  15,  133, 44,  203, 136, 18,  231, 18,  64,  50,  198, 199, 144, 72,  58,  59,  60,
        61,  11,  208, 1,   49,  211, 4,   5,   6,   7,   8,   9,   49,  10,  163, 57,  49,  210,
        47,  4,   5,   6,   7,   8,   9,   231, 26,  232, 245, 50,  252, 253, 254, 51,  51,  50,
        278, 279, 21,  298, 372, 231, 85,  200, 163, 375, 150, 217, 242, 47,  -1,  -1,  257, 258,
        203, 80,  249, 250, -1,  -1,  209, -1,  255, 256, -1,  -1,  259, 260, 217, -1,  -1,  -1,
        278, 279, -1,  -1,  281, 282, 283, 284, 285, -1,  -1,  -1,  326, -1,  328, -1,  -1,  -1,
        295, -1,  -1,  242, -1,  -1,  245, -1,  -1,  42,  43,  210, -1,  252, 253, 254, -1,  375,
        301, -1,  303, -1,  317, 56,  57,  58,  59,  60,  61,  -1,  326, 314, 328, 316, -1,  318,
        69,  70,  -1,  -1,  -1,  -1,  -1,  338, 339, 340, -1,  -1,  210, -1,  249, 250, -1,  -1,
        293, -1,  255, 256, 341, 298, 259, 260, -1,  358, 359, -1,  -1,  -1,  -1,  -1,  365, -1,
        -1,  -1,  -1,  -1,  -1,  372, -1,  -1,  363, 364, -1,  366, 367, 210, -1,  249, 250, -1,
        -1,  -1,  331, 255, 256, -1,  -1,  259, 260, 382, 383, -1,  301, 386, 303, -1,  389, -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  314, -1,  316, -1,  318, -1,  -1,  -1,  -1,  249, 250,
        -1,  -1,  -1,  -1,  255, 256, -1,  -1,  259, 260, -1,  -1,  37,  301, 210, 303, 341, 42,
        43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  314, -1,  316, -1,  318, 56,  57,  58,  59,  60,
        61,  -1,  363, 364, -1,  366, 367, 68,  69,  70,  -1,  -1,  -1,  37,  301, 39,  303, 341,
        42,  43,  44,  382, 383, 255, -1,  386, -1,  314, 389, 316, -1,  318, 56,  57,  58,  59,
        60,  61,  -1,  363, 364, -1,  366, 367, 68,  69,  70,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        341, -1,  18,  -1,  382, 383, -1,  -1,  386, -1,  -1,  389, -1,  -1,  -1,  301, -1,  303,
        34,  35,  36,  -1,  363, 364, -1,  366, 367, -1,  314, 45,  316, 47,  318, -1,  -1,  -1,
        52,  -1,  54,  -1,  -1,  382, 383, -1,  -1,  386, -1,  -1,  389, -1,  -1,  -1,  -1,  -1,
        -1,  341, -1,  73,  74,  75,  76,  77,  78,  79,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        1,   -1,  -1,  -1,  -1,  363, 364, -1,  366, 367, -1,  12,  -1,  14,  -1,  16,  17,  18,
        19,  20,  21,  -1,  23,  24,  382, 383, 27,  -1,  386, -1,  -1,  389, -1,  34,  35,  36,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  71,  -1,
        73,  74,  75,  76,  77,  78,  79,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,
        23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  71,  -1,  73,  74,  75,  76,
        77,  78,  79,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,
        27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  12,
        -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,
        -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  42,  43,  44,  -1,  45,  -1,  47,  -1,
        49,  -1,  -1,  52,  -1,  54,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  1,   -1,  -1,
        68,  69,  70,  -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  17,  18,  19,  20,  -1,
        -1,  -1,  24,  -1,  -1,  -1,  -1,  29,  -1,  31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,
        -1,  41,  42,  43,  -1,  45,  -1,  47,  -1,  -1,  -1,  -1,  52,  53,  54,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,
        76,  77,  78,  79,  17,  18,  19,  20,  -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,  -1,  -1,
        31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  41,  42,  43,  -1,  45,  -1,  47,  -1,
        -1,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  58,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,  76,  77,  78,  79,  17,  18,  19,  20,  -1,
        -1,  -1,  24,  -1,  -1,  -1,  -1,  -1,  -1,  31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,
        -1,  41,  42,  43,  -1,  45,  -1,  47,  48,  -1,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,
        76,  77,  78,  79,  17,  18,  19,  20,  -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,  -1,  -1,
        31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  41,  42,  43,  -1,  45,  46,  47,  -1,
        -1,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,  76,  77,  78,  79,  12,  13,  14,  -1,  16,
        17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,
        35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,
        -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        71,  -1,  73,  74,  75,  76,  77,  78,  79,  12,  -1,  14,  15,  16,  17,  18,  19,  20,
        21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  -1,  73,  74,
        75,  76,  77,  78,  79,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,
        -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  45,  -1,  47,  -1,  49,  50,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  -1,  73,  74,  75,  76,  77,  78,
        79,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,
        -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,
        47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  71,  72,  73,  74,  75,  76,  77,  78,  79,  12,  -1,  14,
        -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,
        -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,
        -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  17,  18,  19,  20,  -1,  -1,  -1,
        24,  -1,  -1,  -1,  -1,  29,  -1,  31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  41,
        42,  43,  -1,  45,  -1,  47,  -1,  -1,  50,  -1,  52,  53,  54,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,  76,  77,
        78,  79,  17,  18,  19,  20,  -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,  -1,  -1,  31,  -1,
        -1,  34,  35,  36,  -1,  -1,  -1,  -1,  41,  42,  43,  18,  45,  -1,  47,  -1,  -1,  -1,
        -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,
        43,  44,  -1,  -1,  73,  74,  75,  76,  77,  78,  79,  -1,  -1,  56,  57,  58,  59,  60,
        61,  18,  -1,  -1,  -1,  66,  -1,  68,  69,  70,  -1,  -1,  -1,  -1,  -1,  -1,  33,  -1,
        -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  22,  -1,  -1,  -1,  66,  -1,  68,  69,  70,
        -1,  32,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  22,  -1,  -1,  -1,  66,
        -1,  68,  69,  70,  -1,  -1,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  22,
        -1,  -1,  -1,  66,  -1,  68,  69,  70,  -1,  -1,  33,  -1,  -1,  -1,  37,  38,  39,  40,
        -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,
        59,  60,  61,  22,  -1,  -1,  -1,  66,  -1,  68,  69,  70,  -1,  -1,  33,  -1,  -1,  -1,
        37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  56,  57,  58,  59,  60,  61,  -1,  25,  -1,  -1,  66,  -1,  68,  69,  70,  33,  -1,
        -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  25,  -1,  -1,  66,  -1,  68,  69,  70,
        33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  26,  -1,  66,  -1,  68,
        69,  70,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  28,  -1,  -1,  -1,  66,
        33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  30,  -1,  66,  33,  68,
        69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  -1,  68,  69,  70,
        32,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  33,
        68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  33,  68,  69,
        70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  63,  -1,  -1,  66,  33,  68,  69,  70,  37,
        38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  65,  66,  33,  68,  69,  70,  37,  38,  39,
        40,  -1,  42,  43,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,
        58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,
        42,  43,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,
        60,  61,  -1,  -1,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,
        44,  -1,  -1,  -1,  48,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,
        -1,  -1,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,
        -1,  -1,  -1,  -1,  -1,  51,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,
        -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,
        -1,  -1,  50,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,
        66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  -1,
        68,  69,  70,  37,  38,  39,  -1,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  -1,  -1,  68,  69,
        70
    };

    const unsigned char Parser::yystos_[] = {
        0,   3,   47,  85,  86,  18,  79,  157, 164, 165, 166, 167, 0,   1,   4,   5,   6,   7,
        8,   9,   47,  87,  88,  89,  90,  91,  92,  93,  94,  97,  17,  19,  20,  24,  31,  34,
        35,  36,  41,  42,  43,  45,  47,  52,  54,  73,  74,  75,  76,  77,  78,  114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
        135, 136, 137, 138, 157, 158, 159, 48,  55,  49,  158, 157, 157, 157, 157, 157, 164, 88,
        47,  157, 160, 161, 162, 162, 162, 114, 162, 114, 114, 114, 1,   58,  113, 114, 139, 140,
        157, 1,   48,  113, 114, 157, 158, 33,  37,  38,  39,  40,  42,  43,  44,  56,  57,  58,
        59,  60,  61,  66,  68,  69,  70,  64,  45,  147, 52,  3,   165, 114, 137, 154, 155, 156,
        45,  151, 44,  151, 44,  51,  48,  164, 51,  44,  18,  18,  25,  18,  46,  114, 55,  46,
        46,  55,  51,  48,  48,  55,  63,  142, 143, 144, 145, 146, 158, 114, 114, 114, 114, 114,
        114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 157, 1,   46,  113, 114, 157,
        65,  65,  55,  50,  1,   47,  150, 157, 161, 163, 65,  49,  44,  65,  142, 142, 148, 149,
        89,  48,  142, 114, 114, 114, 114, 114, 46,  114, 140, 157, 114, 114, 114, 56,  62,  147,
        46,  46,  114, 114, 155, 46,  164, 46,  55,  142, 1,   47,  95,  96,  157, 12,  14,  16,
        17,  19,  20,  21,  23,  24,  27,  49,  71,  98,  100, 101, 102, 105, 106, 107, 108, 109,
        110, 111, 112, 115, 117, 118, 119, 142, 58,  65,  160, 18,  30,  22,  26,  32,  147, 46,
        48,  141, 142, 149, 114, 48,  163, 44,  164, 50,  55,  1,   98,  99,  1,   99,  162, 162,
        162, 98,  117, 118, 119, 114, 114, 1,   99,  1,   99,  67,  44,  142, 142, 114, 114, 114,
        114, 114, 55,  57,  65,  161, 114, 48,  95,  13,  13,  98,  15,  15,  44,  18,  18,  25,
        28,  50,  50,  72,  72,  114, 98,  11,  152, 142, 142, 157, 114, 114, 114, 98,  49,  49,
        10,  153, 57,  18,  22,  32,  22,  26,  1,   29,  53,  103, 104, 114, 114, 49,  98,  98,
        114, 98,  98,  50,  51,  51,  50,  103, 51,  50,  156, 22,  98,  98,  98,  50,  98
    };

    const unsigned char Parser::yyr1_[] = {
        0,   84,  85,  86,  86,  87,  87,  88,  88,  88,  89,  89,  89,  89,  89,  90,  91,
        92,  92,  93,  93,  94,  94,  95,  95,  95,  96,  96,  97,  98,  98,  98,  98,  98,
        98,  98,  98,  98,  98,  98,  99,  99,  100, 101, 101, 102, 102, 103, 103, 103, 104,
        104, 105, 106, 106, 107, 108, 109, 109, 109, 109, 110, 110, 110, 110, 111, 112, 112,
        112, 112, 112, 112, 113, 113, 114, 114, 114, 114, 114, 114, 114, 114, 115, 115, 115,
        115, 115, 115, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116,
        116, 116, 116, 116, 116, 116, 117, 117, 118, 118, 119, 120, 121, 122, 123, 124, 125,
        126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 127, 128, 128, 129, 130,
        131, 132, 132, 133, 134, 135, 135, 135, 136, 137, 138, 139, 139, 140, 141, 141, 142,
        142, 142, 142, 143, 144, 145, 146, 147, 147, 147, 148, 148, 149, 149, 150, 150, 151,
        151, 151, 152, 152, 153, 153, 154, 154, 155, 155, 155, 156, 156, 157, 157, 158, 158,
        159, 159, 160, 160, 161, 162, 162, 163, 163, 164, 164, 165, 165, 166, 167
    };

    const unsigned char Parser::yyr2_[] = {
        0, 2, 2, 4, 1, 2, 1, 4, 1, 1, 1, 1, 1, 1, 1, 6, 7, 5, 7, 8, 1, 2, 4, 1, 4, 1, 3, 1, 4,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 4, 6, 6, 6, 3, 3, 3, 2, 1, 6, 6, 8, 6, 2, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1,
        1, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 2, 3, 4, 5, 3, 6, 6,
        6, 6, 6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 5,
        5, 3, 3, 1, 3, 3, 1, 1, 1, 1, 1, 1, 4, 6, 3, 3, 3, 2, 3, 1, 1, 0, 3, 1, 3, 3, 0, 4, 0,
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
                                             "TupleLiteral",
                                             "NamedTupleLiteral",
                                             "Assignments",
                                             "Assignment",
                                             "Types",
                                             "Type",
                                             "BasicType",
                                             "ComposedType",
                                             "RelationType",
                                             "FixedSizedType",
                                             "Arguments",
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
        0,    391,  391,  400,  406,  414,  420,  430,  436,  440,  448,  452,  456,  460,  464,
        472,  480,  488,  493,  502,  518,  526,  549,  567,  571,  577,  585,  591,  601,  613,
        617,  621,  625,  629,  633,  637,  641,  645,  649,  653,  661,  667,  677,  685,  689,
        697,  701,  709,  713,  717,  725,  731,  741,  749,  753,  761,  769,  777,  781,  785,
        790,  799,  803,  807,  812,  821,  831,  835,  839,  843,  847,  851,  863,  869,  879,
        883,  887,  891,  895,  899,  903,  907,  915,  919,  923,  927,  931,  935,  947,  951,
        955,  959,  963,  967,  971,  975,  979,  983,  987,  991,  995,  999,  1003, 1007, 1011,
        1015, 1019, 1023, 1031, 1036, 1044, 1049, 1057, 1065, 1073, 1081, 1089, 1097, 1105, 1117,
        1121, 1125, 1129, 1133, 1137, 1141, 1145, 1149, 1153, 1157, 1161, 1169, 1177, 1182, 1191,
        1207, 1223, 1239, 1251, 1267, 1283, 1291, 1296, 1300, 1308, 1315, 1323, 1330, 1336, 1345,
        1357, 1363, 1373, 1377, 1381, 1385, 1393, 1401, 1409, 1417, 1429, 1433, 1437, 1451, 1457,
        1467, 1471, 1479, 1485, 1495, 1499, 1503, 1515, 1519, 1527, 1531, 1539, 1545, 1555, 1563,
        1573, 1584, 1588, 1600, 1604, 1612, 1616, 1626, 1632, 1646, 1650, 1659, 1667, 1673, 1681,
        1687, 1698, 1704, 1713, 1717, 1725, 1733
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
#line 4271 "GrammarParser.cpp"               // lalr1.cc:1167
#line 1739 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1168

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
