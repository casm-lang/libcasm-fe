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
            case 168:  // Attribute
                value.move< Attribute::Ptr >( that.value );
                break;

            case 167:  // Attributes
                value.move< Attributes::Ptr >( that.value );
                break;

            case 169:  // BasicAttribute
                value.move< BasicAttribute::Ptr >( that.value );
                break;

            case 144:  // BasicType
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

            case 124:  // ChooseExpression
                value.move< ChooseExpression::Ptr >( that.value );
                break;

            case 107:  // ChooseRule
                value.move< ChooseRule::Ptr >( that.value );
                break;

            case 145:  // ComposedType
                value.move< ComposedType::Ptr >( that.value );
                break;

            case 123:  // ConditionalExpression
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

            case 126:  // ExistentialQuantifierExpression
                value.move< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 114:  // Term
            case 115:  // SimpleOrClaspedTerm
            case 116:  // OperatorExpression
            case 154:  // MaybeDefined
                value.move< Expression::Ptr >( that.value );
                break;

            case 170:  // ExpressionAttribute
                value.move< ExpressionAttribute::Ptr >( that.value );
                break;

            case 113:  // Terms
            case 149:  // Arguments
                value.move< Expressions::Ptr >( that.value );
                break;

            case 148:  // FixedSizedType
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

            case 159:  // Identifier
                value.move< Identifier::Ptr >( that.value );
                break;

            case 160:  // IdentifierPath
                value.move< IdentifierPath::Ptr >( that.value );
                break;

            case 161:  // DotSeparatedIdentifiers
                value.move< Identifiers::Ptr >( that.value );
                break;

            case 120:  // IndirectCallExpression
                value.move< IndirectCallExpression::Ptr >( that.value );
                break;

            case 108:  // IterateRule
                value.move< IterateRule::Ptr >( that.value );
                break;

            case 122:  // LetExpression
                value.move< LetExpression::Ptr >( that.value );
                break;

            case 105:  // LetRule
                value.move< LetRule::Ptr >( that.value );
                break;

            case 136:  // ListLiteral
                value.move< ListLiteral::Ptr >( that.value );
                break;

            case 127:  // Literal
                value.move< Literal::Ptr >( that.value );
                break;

            case 119:  // LiteralCallExpression
                value.move< LiteralCallExpression::Ptr >( that.value );
                break;

            case 118:  // MethodCallExpression
                value.move< MethodCallExpression::Ptr >( that.value );
                break;

            case 141:  // Assignment
                value.move< NamedExpression::Ptr >( that.value );
                break;

            case 140:  // Assignments
                value.move< NamedExpressions::Ptr >( that.value );
                break;

            case 139:  // NamedTupleLiteral
                value.move< NamedTupleLiteral::Ptr >( that.value );
                break;

            case 137:  // RangeLiteral
                value.move< RangeLiteral::Ptr >( that.value );
                break;

            case 135:  // ReferenceLiteral
                value.move< ReferenceLiteral::Ptr >( that.value );
                break;

            case 147:  // RelationType
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

            case 146:  // TemplateType
                value.move< TemplateType::Ptr >( that.value );
                break;

            case 138:  // TupleLiteral
                value.move< TupleLiteral::Ptr >( that.value );
                break;

            case 121:  // TypeCastingExpression
                value.move< TypeCastingExpression::Ptr >( that.value );
                break;

            case 142:  // Types
            case 150:  // FunctionParameters
            case 151:  // MaybeFunctionParameters
                value.move< Types::Ptr >( that.value );
                break;

            case 128:  // UndefinedLiteral
                value.move< UndefLiteral::Ptr >( that.value );
                break;

            case 125:  // UniversalQuantifierExpression
                value.move< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // UpdateRule
            case 157:  // Initializer
                value.move< UpdateRule::Ptr >( that.value );
                break;

            case 155:  // MaybeInitially
            case 156:  // Initializers
            case 158:  // MaybeInitializers
                value.move< UpdateRules::Ptr >( that.value );
                break;

            case 97:  // UsingDefinition
                value.move< UsingDefinition::Ptr >( that.value );
                break;

            case 129:  // BooleanLiteral
            case 130:  // IntegerLiteral
            case 131:  // RationalLiteral
            case 132:  // DecimalLiteral
            case 133:  // BinaryLiteral
            case 134:  // StringLiteral
                value.move< ValueLiteral::Ptr >( that.value );
                break;

            case 162:  // Variable
            case 164:  // TypedVariable
            case 165:  // AttributedVariable
            case 166:  // TypedAttributedVariable
                value.move< VariableDefinition::Ptr >( that.value );
                break;

            case 152:  // Parameters
            case 153:  // MaybeParameters
            case 163:  // TypedVariables
                value.move< VariableDefinitions::Ptr >( that.value );
                break;

            case 143:  // Type
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
            case 168:  // Attribute
                value.copy< Attribute::Ptr >( that.value );
                break;

            case 167:  // Attributes
                value.copy< Attributes::Ptr >( that.value );
                break;

            case 169:  // BasicAttribute
                value.copy< BasicAttribute::Ptr >( that.value );
                break;

            case 144:  // BasicType
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

            case 124:  // ChooseExpression
                value.copy< ChooseExpression::Ptr >( that.value );
                break;

            case 107:  // ChooseRule
                value.copy< ChooseRule::Ptr >( that.value );
                break;

            case 145:  // ComposedType
                value.copy< ComposedType::Ptr >( that.value );
                break;

            case 123:  // ConditionalExpression
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

            case 126:  // ExistentialQuantifierExpression
                value.copy< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 114:  // Term
            case 115:  // SimpleOrClaspedTerm
            case 116:  // OperatorExpression
            case 154:  // MaybeDefined
                value.copy< Expression::Ptr >( that.value );
                break;

            case 170:  // ExpressionAttribute
                value.copy< ExpressionAttribute::Ptr >( that.value );
                break;

            case 113:  // Terms
            case 149:  // Arguments
                value.copy< Expressions::Ptr >( that.value );
                break;

            case 148:  // FixedSizedType
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

            case 159:  // Identifier
                value.copy< Identifier::Ptr >( that.value );
                break;

            case 160:  // IdentifierPath
                value.copy< IdentifierPath::Ptr >( that.value );
                break;

            case 161:  // DotSeparatedIdentifiers
                value.copy< Identifiers::Ptr >( that.value );
                break;

            case 120:  // IndirectCallExpression
                value.copy< IndirectCallExpression::Ptr >( that.value );
                break;

            case 108:  // IterateRule
                value.copy< IterateRule::Ptr >( that.value );
                break;

            case 122:  // LetExpression
                value.copy< LetExpression::Ptr >( that.value );
                break;

            case 105:  // LetRule
                value.copy< LetRule::Ptr >( that.value );
                break;

            case 136:  // ListLiteral
                value.copy< ListLiteral::Ptr >( that.value );
                break;

            case 127:  // Literal
                value.copy< Literal::Ptr >( that.value );
                break;

            case 119:  // LiteralCallExpression
                value.copy< LiteralCallExpression::Ptr >( that.value );
                break;

            case 118:  // MethodCallExpression
                value.copy< MethodCallExpression::Ptr >( that.value );
                break;

            case 141:  // Assignment
                value.copy< NamedExpression::Ptr >( that.value );
                break;

            case 140:  // Assignments
                value.copy< NamedExpressions::Ptr >( that.value );
                break;

            case 139:  // NamedTupleLiteral
                value.copy< NamedTupleLiteral::Ptr >( that.value );
                break;

            case 137:  // RangeLiteral
                value.copy< RangeLiteral::Ptr >( that.value );
                break;

            case 135:  // ReferenceLiteral
                value.copy< ReferenceLiteral::Ptr >( that.value );
                break;

            case 147:  // RelationType
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

            case 146:  // TemplateType
                value.copy< TemplateType::Ptr >( that.value );
                break;

            case 138:  // TupleLiteral
                value.copy< TupleLiteral::Ptr >( that.value );
                break;

            case 121:  // TypeCastingExpression
                value.copy< TypeCastingExpression::Ptr >( that.value );
                break;

            case 142:  // Types
            case 150:  // FunctionParameters
            case 151:  // MaybeFunctionParameters
                value.copy< Types::Ptr >( that.value );
                break;

            case 128:  // UndefinedLiteral
                value.copy< UndefLiteral::Ptr >( that.value );
                break;

            case 125:  // UniversalQuantifierExpression
                value.copy< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // UpdateRule
            case 157:  // Initializer
                value.copy< UpdateRule::Ptr >( that.value );
                break;

            case 155:  // MaybeInitially
            case 156:  // Initializers
            case 158:  // MaybeInitializers
                value.copy< UpdateRules::Ptr >( that.value );
                break;

            case 97:  // UsingDefinition
                value.copy< UsingDefinition::Ptr >( that.value );
                break;

            case 129:  // BooleanLiteral
            case 130:  // IntegerLiteral
            case 131:  // RationalLiteral
            case 132:  // DecimalLiteral
            case 133:  // BinaryLiteral
            case 134:  // StringLiteral
                value.copy< ValueLiteral::Ptr >( that.value );
                break;

            case 162:  // Variable
            case 164:  // TypedVariable
            case 165:  // AttributedVariable
            case 166:  // TypedAttributedVariable
                value.copy< VariableDefinition::Ptr >( that.value );
                break;

            case 152:  // Parameters
            case 153:  // MaybeParameters
            case 163:  // TypedVariables
                value.copy< VariableDefinitions::Ptr >( that.value );
                break;

            case 143:  // Type
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
                    case 168:  // Attribute
                        yylhs.value.build< Attribute::Ptr >();
                        break;

                    case 167:  // Attributes
                        yylhs.value.build< Attributes::Ptr >();
                        break;

                    case 169:  // BasicAttribute
                        yylhs.value.build< BasicAttribute::Ptr >();
                        break;

                    case 144:  // BasicType
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

                    case 124:  // ChooseExpression
                        yylhs.value.build< ChooseExpression::Ptr >();
                        break;

                    case 107:  // ChooseRule
                        yylhs.value.build< ChooseRule::Ptr >();
                        break;

                    case 145:  // ComposedType
                        yylhs.value.build< ComposedType::Ptr >();
                        break;

                    case 123:  // ConditionalExpression
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

                    case 126:  // ExistentialQuantifierExpression
                        yylhs.value.build< ExistentialQuantifierExpression::Ptr >();
                        break;

                    case 114:  // Term
                    case 115:  // SimpleOrClaspedTerm
                    case 116:  // OperatorExpression
                    case 154:  // MaybeDefined
                        yylhs.value.build< Expression::Ptr >();
                        break;

                    case 170:  // ExpressionAttribute
                        yylhs.value.build< ExpressionAttribute::Ptr >();
                        break;

                    case 113:  // Terms
                    case 149:  // Arguments
                        yylhs.value.build< Expressions::Ptr >();
                        break;

                    case 148:  // FixedSizedType
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

                    case 159:  // Identifier
                        yylhs.value.build< Identifier::Ptr >();
                        break;

                    case 160:  // IdentifierPath
                        yylhs.value.build< IdentifierPath::Ptr >();
                        break;

                    case 161:  // DotSeparatedIdentifiers
                        yylhs.value.build< Identifiers::Ptr >();
                        break;

                    case 120:  // IndirectCallExpression
                        yylhs.value.build< IndirectCallExpression::Ptr >();
                        break;

                    case 108:  // IterateRule
                        yylhs.value.build< IterateRule::Ptr >();
                        break;

                    case 122:  // LetExpression
                        yylhs.value.build< LetExpression::Ptr >();
                        break;

                    case 105:  // LetRule
                        yylhs.value.build< LetRule::Ptr >();
                        break;

                    case 136:  // ListLiteral
                        yylhs.value.build< ListLiteral::Ptr >();
                        break;

                    case 127:  // Literal
                        yylhs.value.build< Literal::Ptr >();
                        break;

                    case 119:  // LiteralCallExpression
                        yylhs.value.build< LiteralCallExpression::Ptr >();
                        break;

                    case 118:  // MethodCallExpression
                        yylhs.value.build< MethodCallExpression::Ptr >();
                        break;

                    case 141:  // Assignment
                        yylhs.value.build< NamedExpression::Ptr >();
                        break;

                    case 140:  // Assignments
                        yylhs.value.build< NamedExpressions::Ptr >();
                        break;

                    case 139:  // NamedTupleLiteral
                        yylhs.value.build< NamedTupleLiteral::Ptr >();
                        break;

                    case 137:  // RangeLiteral
                        yylhs.value.build< RangeLiteral::Ptr >();
                        break;

                    case 135:  // ReferenceLiteral
                        yylhs.value.build< ReferenceLiteral::Ptr >();
                        break;

                    case 147:  // RelationType
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

                    case 146:  // TemplateType
                        yylhs.value.build< TemplateType::Ptr >();
                        break;

                    case 138:  // TupleLiteral
                        yylhs.value.build< TupleLiteral::Ptr >();
                        break;

                    case 121:  // TypeCastingExpression
                        yylhs.value.build< TypeCastingExpression::Ptr >();
                        break;

                    case 142:  // Types
                    case 150:  // FunctionParameters
                    case 151:  // MaybeFunctionParameters
                        yylhs.value.build< Types::Ptr >();
                        break;

                    case 128:  // UndefinedLiteral
                        yylhs.value.build< UndefLiteral::Ptr >();
                        break;

                    case 125:  // UniversalQuantifierExpression
                        yylhs.value.build< UniversalQuantifierExpression::Ptr >();
                        break;

                    case 111:  // UpdateRule
                    case 157:  // Initializer
                        yylhs.value.build< UpdateRule::Ptr >();
                        break;

                    case 155:  // MaybeInitially
                    case 156:  // Initializers
                    case 158:  // MaybeInitializers
                        yylhs.value.build< UpdateRules::Ptr >();
                        break;

                    case 97:  // UsingDefinition
                        yylhs.value.build< UsingDefinition::Ptr >();
                        break;

                    case 129:  // BooleanLiteral
                    case 130:  // IntegerLiteral
                    case 131:  // RationalLiteral
                    case 132:  // DecimalLiteral
                    case 133:  // BinaryLiteral
                    case 134:  // StringLiteral
                        yylhs.value.build< ValueLiteral::Ptr >();
                        break;

                    case 162:  // Variable
                    case 164:  // TypedVariable
                    case 165:  // AttributedVariable
                    case 166:  // TypedAttributedVariable
                        yylhs.value.build< VariableDefinition::Ptr >();
                        break;

                    case 152:  // Parameters
                    case 153:  // MaybeParameters
                    case 163:  // TypedVariables
                        yylhs.value.build< VariableDefinitions::Ptr >();
                        break;

                    case 143:  // Type
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
#line 395 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            specification.setHeader(
                                yystack_[ 1 ].value.as< HeaderDefinition::Ptr >() );
                            specification.setDefinitions(
                                yystack_[ 0 ].value.as< Definitions::Ptr >() );
                        }
#line 1470 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 3:
#line 404 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< HeaderDefinition::Ptr >() = definition;
                        }
#line 1480 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 4:
#line 410 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< HeaderDefinition::Ptr >() =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                        }
#line 1488 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 5:
#line 418 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = yystack_[ 1 ].value.as< Definitions::Ptr >();
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1498 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 6:
#line 424 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = Ast::make< Definitions >( yylhs.location );
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1508 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 7:
#line 434 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition = yystack_[ 0 ].value.as< Definition::Ptr >();
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< Definition::Ptr >() = definition;
                        }
#line 1518 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 8:
#line 440 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< Definition::Ptr >();
                        }
#line 1526 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 9:
#line 444 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() = nullptr;
                        }
#line 1534 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 10:
#line 452 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< EnumerationDefinition::Ptr >();
                        }
#line 1542 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 11:
#line 456 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< DerivedDefinition::Ptr >();
                        }
#line 1550 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 12:
#line 460 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< RuleDefinition::Ptr >();
                        }
#line 1558 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 13:
#line 464 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< FunctionDefinition::Ptr >();
                        }
#line 1566 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 14:
#line 468 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< UsingDefinition::Ptr >();
                        }
#line 1574 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 15:
#line 476 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumerationDefinition::Ptr >() =
                                Ast::make< EnumerationDefinition >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 1 ].value.as< Enumerators::Ptr >() );
                        }
#line 1582 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 16:
#line 484 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DerivedDefinition::Ptr >() =
                                Ast::make< DerivedDefinition >(
                                    yylhs.location,
                                    yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 4 ].value.as< VariableDefinitions::Ptr >(),
                                    yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1590 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 17:
#line 492 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Identifier::Ptr >(),
                                yystack_[ 2 ].value.as< VariableDefinitions::Ptr >(),
                                createVoidType( yylhs.location ),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1599 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 18:
#line 497 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                yystack_[ 4 ].value.as< VariableDefinitions::Ptr >(),
                                yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1608 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 19:
#line 506 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1628 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 20:
#line 522 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FunctionDefinition::Ptr >() =
                                yystack_[ 0 ]
                                    .value.as< FunctionDefinition::Ptr >();  // `init` special case
                        }
#line 1636 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 21:
#line 530 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1663 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 22:
#line 553 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1681 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 23:
#line 571 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() =
                                Ast::make< EnumeratorDefinition >(
                                    yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 1689 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 24:
#line 575 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerator = Ast::make< EnumeratorDefinition >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            enumerator->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = enumerator;
                        }
#line 1699 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 25:
#line 581 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = nullptr;
                        }
#line 1707 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 26:
#line 589 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = yystack_[ 2 ].value.as< Enumerators::Ptr >();
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1717 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 27:
#line 595 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = Ast::make< Enumerators >( yylhs.location );
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1727 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 28:
#line 605 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UsingDefinition::Ptr >() = Ast::make< UsingDefinition >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 1735 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 29:
#line 617 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SkipRule::Ptr >();
                        }
#line 1743 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 30:
#line 621 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalRule::Ptr >();
                        }
#line 1751 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 31:
#line 625 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CaseRule::Ptr >();
                        }
#line 1759 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 32:
#line 629 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< LetRule::Ptr >();
                        }
#line 1767 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 33:
#line 633 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ForallRule::Ptr >();
                        }
#line 1775 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 34:
#line 637 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseRule::Ptr >();
                        }
#line 1783 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 35:
#line 641 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< IterateRule::Ptr >();
                        }
#line 1791 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 36:
#line 645 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< BlockRule::Ptr >();
                        }
#line 1799 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 37:
#line 649 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SequenceRule::Ptr >();
                        }
#line 1807 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 38:
#line 653 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRule::Ptr >();
                        }
#line 1815 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 39:
#line 657 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CallRule::Ptr >();
                        }
#line 1823 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 40:
#line 665 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = yystack_[ 1 ].value.as< Rules::Ptr >();
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1833 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 41:
#line 671 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = Ast::make< Rules >( yylhs.location );
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1843 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 42:
#line 681 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SkipRule::Ptr >() =
                                Ast::make< SkipRule >( yylhs.location );
                        }
#line 1851 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 43:
#line 689 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1859 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 44:
#line 693 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Rule::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1867 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 45:
#line 701 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = Ast::make< CaseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Cases::Ptr >() );
                        }
#line 1875 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 46:
#line 705 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = nullptr;
                        }
#line 1883 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 47:
#line 713 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1891 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 48:
#line 717 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1899 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 49:
#line 721 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< ExpressionCase >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1907 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 50:
#line 729 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = yystack_[ 1 ].value.as< Cases::Ptr >();
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1917 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 51:
#line 735 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = Ast::make< Cases >( yylhs.location );
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1927 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 52:
#line 745 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetRule::Ptr >() = Ast::make< LetRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1935 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 53:
#line 753 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1943 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 54:
#line 757 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 6 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1951 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 55:
#line 765 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseRule::Ptr >() = Ast::make< ChooseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1959 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 56:
#line 773 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IterateRule::Ptr >() = Ast::make< IterateRule >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1967 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 57:
#line 781 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1975 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 58:
#line 785 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1983 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 59:
#line 789 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1992 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 60:
#line 794 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 2001 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 61:
#line 803 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 2009 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 62:
#line 807 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 2017 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 63:
#line 811 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 2026 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 64:
#line 816 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 2035 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 65:
#line 825 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto function =
                                yystack_[ 2 ].value.as< DirectCallExpression::Ptr >();
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2045 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 66:
#line 835 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 2053 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 67:
#line 839 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 2061 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 68:
#line 843 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 2069 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 69:
#line 847 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 2077 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 70:
#line 851 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 2085 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 71:
#line 855 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 2093 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 72:
#line 867 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto expressions = yystack_[ 2 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2103 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 73:
#line 873 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2113 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 74:
#line 883 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2121 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 75:
#line 887 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TypeCastingExpression::Ptr >();
                        }
#line 2129 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 76:
#line 891 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2137 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 77:
#line 895 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LetExpression::Ptr >();
                        }
#line 2145 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 78:
#line 899 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalExpression::Ptr >();
                        }
#line 2153 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 79:
#line 903 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseExpression::Ptr >();
                        }
#line 2161 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 80:
#line 907 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UniversalQuantifierExpression::Ptr >();
                        }
#line 2169 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 81:
#line 911 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ExistentialQuantifierExpression::Ptr >();
                        }
#line 2177 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 82:
#line 919 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2185 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 83:
#line 923 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = nullptr;
                        }
#line 2193 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 84:
#line 927 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >();
                        }
#line 2201 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 85:
#line 931 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >();
                        }
#line 2209 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 86:
#line 935 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LiteralCallExpression::Ptr >();
                        }
#line 2217 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 87:
#line 939 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >();
                        }
#line 2225 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 88:
#line 943 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Literal::Ptr >();
                        }
#line 2233 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 89:
#line 955 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2241 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 90:
#line 959 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::INV_INSTRUCTION );
                        }
#line 2249 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 91:
#line 963 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::ADD_INSTRUCTION );
                        }
#line 2257 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 92:
#line 967 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::SUB_INSTRUCTION );
                        }
#line 2265 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 93:
#line 971 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MUL_INSTRUCTION );
                        }
#line 2273 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 94:
#line 975 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::DIV_INSTRUCTION );
                        }
#line 2281 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 95:
#line 979 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MOD_INSTRUCTION );
                        }
#line 2289 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 96:
#line 983 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::POW_INSTRUCTION );
                        }
#line 2297 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 97:
#line 987 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NEQ_INSTRUCTION );
                        }
#line 2305 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 98:
#line 991 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::EQU_INSTRUCTION );
                        }
#line 2313 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 99:
#line 995 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LTH_INSTRUCTION );
                        }
#line 2321 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 100:
#line 999 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GTH_INSTRUCTION );
                        }
#line 2329 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 101:
#line 1003 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LEQ_INSTRUCTION );
                        }
#line 2337 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 102:
#line 1007 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GEQ_INSTRUCTION );
                        }
#line 2345 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 103:
#line 1011 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::OR_INSTRUCTION );
                        }
#line 2353 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 104:
#line 1015 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::XOR_INSTRUCTION );
                        }
#line 2361 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 105:
#line 1019 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::AND_INSTRUCTION );
                        }
#line 2369 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 106:
#line 1023 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2377 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 107:
#line 1027 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2385 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 108:
#line 1031 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NOT_INSTRUCTION );
                        }
#line 2393 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 109:
#line 1039 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< IdentifierPath::Ptr >(),
                                    arguments );
                        }
#line 2402 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 110:
#line 1044 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< IdentifierPath::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2410 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 111:
#line 1052 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2419 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 112:
#line 1057 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 3 ].value.as< Expression::Ptr >(),
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2427 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 113:
#line 1065 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LiteralCallExpression::Ptr >() =
                                Ast::make< LiteralCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< ValueLiteral::Ptr >() );
                        }
#line 2435 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 114:
#line 1073 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IndirectCallExpression::Ptr >() =
                                Ast::make< IndirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2443 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 115:
#line 1081 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TypeCastingExpression::Ptr >() =
                                Ast::make< TypeCastingExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2451 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 116:
#line 1089 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetExpression::Ptr >() = Ast::make< LetExpression >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2459 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 117:
#line 1097 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalExpression::Ptr >() =
                                Ast::make< ConditionalExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Expression::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2467 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 118:
#line 1105 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseExpression::Ptr >() =
                                Ast::make< ChooseExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2475 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 119:
#line 1113 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UniversalQuantifierExpression::Ptr >() =
                                Ast::make< UniversalQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2483 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 120:
#line 1121 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExistentialQuantifierExpression::Ptr >() =
                                Ast::make< ExistentialQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2491 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 121:
#line 1133 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< UndefLiteral::Ptr >();
                        }
#line 2499 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 122:
#line 1137 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2507 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 123:
#line 1141 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2515 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 124:
#line 1145 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2523 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 125:
#line 1149 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2531 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 126:
#line 1153 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2539 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 127:
#line 1157 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2547 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 128:
#line 1161 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ReferenceLiteral::Ptr >();
                        }
#line 2555 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 129:
#line 1165 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ListLiteral::Ptr >();
                        }
#line 2563 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 130:
#line 1169 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< RangeLiteral::Ptr >();
                        }
#line 2571 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 131:
#line 1173 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< TupleLiteral::Ptr >();
                        }
#line 2579 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 132:
#line 1177 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< NamedTupleLiteral::Ptr >();
                        }
#line 2587 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 133:
#line 1185 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UndefLiteral::Ptr >() =
                                Ast::make< UndefLiteral >( yylhs.location );
                        }
#line 2595 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 134:
#line 1193 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
                            yylhs.value.as< ValueLiteral::Ptr >() =
                                Ast::make< ValueLiteral >( yylhs.location, value );
                        }
#line 2604 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 135:
#line 1198 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
                            yylhs.value.as< ValueLiteral::Ptr >() =
                                Ast::make< ValueLiteral >( yylhs.location, value );
                        }
#line 2613 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 136:
#line 1207 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2629 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 137:
#line 1223 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2645 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 138:
#line 1239 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2661 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 139:
#line 1255 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2677 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 140:
#line 1267 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2693 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 141:
#line 1283 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2709 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 142:
#line 1299 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ReferenceLiteral::Ptr >() =
                                Ast::make< ReferenceLiteral >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2717 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 143:
#line 1307 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< ListLiteral::Ptr >() =
                                Ast::make< ListLiteral >( yylhs.location, expressions );
                        }
#line 2726 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 144:
#line 1312 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListLiteral::Ptr >() = Ast::make< ListLiteral >(
                                yylhs.location, yystack_[ 1 ].value.as< Expressions::Ptr >() );
                        }
#line 2734 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 145:
#line 1316 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListLiteral::Ptr >() = nullptr;
                        }
#line 2742 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 146:
#line 1324 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RangeLiteral::Ptr >() = Ast::make< RangeLiteral >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Expression::Ptr >() );
                        }
#line 2750 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 147:
#line 1331 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = yystack_[ 3 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 1 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< TupleLiteral::Ptr >() =
                                Ast::make< TupleLiteral >( yylhs.location, expressions );
                        }
#line 2760 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 148:
#line 1339 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NamedTupleLiteral::Ptr >() =
                                Ast::make< NamedTupleLiteral >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< NamedExpressions::Ptr >() );
                        }
#line 2768 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 149:
#line 1346 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto assignments = yystack_[ 2 ].value.as< NamedExpressions::Ptr >();
                            assignments->add( yystack_[ 0 ].value.as< NamedExpression::Ptr >() );
                            yylhs.value.as< NamedExpressions::Ptr >() = assignments;
                        }
#line 2778 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 150:
#line 1352 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto assignments = Ast::make< NamedExpressions >( yylhs.location );
                            assignments->add( yystack_[ 0 ].value.as< NamedExpression::Ptr >() );
                            yylhs.value.as< NamedExpressions::Ptr >() = assignments;
                        }
#line 2788 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 151:
#line 1361 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NamedExpression::Ptr >() = Ast::make< NamedExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2796 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 152:
#line 1373 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2806 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 153:
#line 1379 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2816 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 154:
#line 1389 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< BasicType::Ptr >();
                        }
#line 2824 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 155:
#line 1393 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2832 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 156:
#line 1397 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< TemplateType::Ptr >();
                        }
#line 2840 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 157:
#line 1401 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< RelationType::Ptr >();
                        }
#line 2848 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 158:
#line 1405 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< FixedSizedType::Ptr >();
                        }
#line 2856 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 159:
#line 1413 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicType::Ptr >() = Ast::make< BasicType >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2864 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 160:
#line 1421 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto identifier =
                                Ast::make< Identifier >( yylhs.location, "Tuple" );
                            auto subTypes = yystack_[ 3 ].value.as< Types::Ptr >();
                            subTypes->add( yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< ComposedType::Ptr >() = Ast::make< ComposedType >(
                                yylhs.location, asIdentifierPath( identifier ), subTypes );
                        }
#line 2875 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 161:
#line 1428 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto identifier =
                                Ast::make< Identifier >( yylhs.location, "Tuple" );
                            auto namedSubTypes =
                                yystack_[ 3 ].value.as< VariableDefinitions::Ptr >();
                            namedSubTypes->add(
                                yystack_[ 1 ].value.as< VariableDefinition::Ptr >() );

                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            auto subTypes = Ast::make< Types >( yylhs.location );
                            for( const auto& namedSubType : *namedSubTypes )
                            {
                                identifiers->add( namedSubType->identifier() );
                                subTypes->add( namedSubType->variableType() );
                            }

                            yylhs.value.as< ComposedType::Ptr >() = Ast::make< ComposedType >(
                                yylhs.location,
                                asIdentifierPath( identifier ),
                                subTypes,
                                identifiers );
                        }
#line 2895 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 162:
#line 1448 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TemplateType::Ptr >() = Ast::make< TemplateType >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 1 ].value.as< Types::Ptr >() );
                        }
#line 2903 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 163:
#line 1456 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RelationType::Ptr >() = Ast::make< RelationType >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 3 ].value.as< Types::Ptr >(),
                                yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2911 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 164:
#line 1464 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FixedSizedType::Ptr >() = Ast::make< FixedSizedType >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2919 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 165:
#line 1476 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() =
                                yystack_[ 1 ].value.as< Expressions::Ptr >();
                        }
#line 2927 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 166:
#line 1480 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() = nullptr;
                        }
#line 2935 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 167:
#line 1484 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2944 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 168:
#line 1498 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2954 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 169:
#line 1504 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2964 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 170:
#line 1514 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = yystack_[ 0 ].value.as< Types::Ptr >();
                        }
#line 2972 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 171:
#line 1518 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = Ast::make< Types >( yylhs.location );
                        }
#line 2980 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 172:
#line 1526 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters = yystack_[ 2 ].value.as< VariableDefinitions::Ptr >();
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< VariableDefinitions::Ptr >() = parameters;
                        }
#line 2990 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 173:
#line 1532 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< VariableDefinitions::Ptr >() = parameters;
                        }
#line 3000 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 174:
#line 1542 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinitions::Ptr >() =
                                yystack_[ 1 ].value.as< VariableDefinitions::Ptr >();
                        }
#line 3008 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 175:
#line 1546 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinitions::Ptr >() = nullptr;
                        }
#line 3016 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 176:
#line 1550 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinitions::Ptr >() =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                        }
#line 3024 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 177:
#line 1562 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 3032 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 178:
#line 1566 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                Ast::make< UndefLiteral >( yylhs.location );
                        }
#line 3040 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 179:
#line 1574 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                yystack_[ 1 ].value.as< UpdateRules::Ptr >();
                        }
#line 3048 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 180:
#line 1578 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                Ast::make< UpdateRules >( yylhs.location );
                        }
#line 3056 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 181:
#line 1586 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers = yystack_[ 2 ].value.as< UpdateRules::Ptr >();
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< UpdateRules::Ptr >() = initializers;
                        }
#line 3066 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 182:
#line 1592 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers = Ast::make< UpdateRules >( yylhs.location );
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< UpdateRules::Ptr >() = initializers;
                        }
#line 3076 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 183:
#line 1602 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 3088 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 184:
#line 1610 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 3102 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 185:
#line 1620 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 3113 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 186:
#line 1631 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRules::Ptr >();
                        }
#line 3121 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 187:
#line 1635 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                Ast::make< UpdateRules >( yylhs.location );
                        }
#line 3129 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 188:
#line 1647 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() = Ast::make< Identifier >(
                                yylhs.location, yystack_[ 0 ].value.as< std::string >() );
                        }
#line 3137 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 189:
#line 1651 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() =
                                Ast::make< Identifier >( yylhs.location, "in" );
                        }
#line 3145 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 190:
#line 1659 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Identifiers::Ptr >(),
                                IdentifierPath::Type::ABSOLUTE );
                        }
#line 3153 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 191:
#line 1663 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
                        }
#line 3163 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 192:
#line 1673 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = yystack_[ 2 ].value.as< Identifiers::Ptr >();
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 3173 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 193:
#line 1679 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 3183 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 194:
#line 1693 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3191 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 195:
#line 1697 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto unresolvedType =
                                Ast::make< UnresolvedType >( yylhs.location );
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    unresolvedType );
                        }
#line 3200 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 196:
#line 1706 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto typedVariables =
                                yystack_[ 2 ].value.as< VariableDefinitions::Ptr >();
                            typedVariables->add(
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< VariableDefinitions::Ptr >() = typedVariables;
                        }
#line 3210 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 197:
#line 1712 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto typedVariables =
                                Ast::make< VariableDefinitions >( yylhs.location );
                            typedVariables->add(
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< VariableDefinitions::Ptr >() = typedVariables;
                        }
#line 3220 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 198:
#line 1722 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 3228 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 199:
#line 1730 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3238 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 200:
#line 1736 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3246 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 201:
#line 1744 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3256 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 202:
#line 1750 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3264 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 203:
#line 1761 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = yystack_[ 2 ].value.as< Attributes::Ptr >();
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3274 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 204:
#line 1767 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = Ast::make< Attributes >( yylhs.location );
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3284 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 205:
#line 1776 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< BasicAttribute::Ptr >();
                        }
#line 3292 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 206:
#line 1780 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< ExpressionAttribute::Ptr >();
                        }
#line 3300 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 207:
#line 1788 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicAttribute::Ptr >() = Ast::make< BasicAttribute >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 3308 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 208:
#line 1796 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExpressionAttribute::Ptr >() =
                                Ast::make< ExpressionAttribute >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 3316 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

#line 3320 "GrammarParser.cpp"  // lalr1.cc:859
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

    const short int Parser::yypact_ninf_ = -241;

    const short int Parser::yytable_ninf_ = -170;

    const short int Parser::yypact_[] = {
        15,   -241, -3,   11,   244,  -241, -241, 1490, 1,    -241, -241, -241, -241, -241, -8,
        -3,   -3,   -3,   -3,   -3,   -3,   200,  -241, -241, -241, -241, -241, -241, -241, -241,
        -2,   -2,   -2,   1490, -2,   -241, -241, -241, 1490, 1490, 1490, 898,  961,  -3,   -4,
        -241, -241, -241, -241, -241, -241, 2203, -52,  -241, -241, -241, -241, -241, -241, -241,
        -241, -241, -241, -241, -241, -241, -241, -241, -241, -241, -241, -241, -241, -241, -241,
        -241, -241, -241, -23,  -29,  33,   -3,   1490, -241, 12,   17,   12,   26,   -14,  5,
        -241, -3,   40,   -241, -241, 63,   90,   115,  1714, 124,  -241, -241, -241, 97,   1490,
        89,   1931, 39,   -241, 95,   107,  -241, 45,   1965, -241, -241, -5,   1490, 1490, 1490,
        1490, 1490, 1490, 1490, 1490, 1490, 1490, 1490, 1490, 1490, 1490, 1490, 1490, 1490, 9,
        1024, -241, -3,   -241, -241, 1999, 91,   102,  -241, 109,  3,    108,  111,  -41,  -5,
        -5,   267,  51,   -5,   1490, 1490, 1490, 1490, 1490, -241, 2033, 1490, -241, -241, -3,
        1490, -241, -241, 1490, 1490, -5,   -241, -241, -241, -241, -241, -241, 79,   771,  2271,
        2300, 2237, 105,  105,  1091, 110,  110,  113,  113,  113,  -241, 2237, 1091, 110,  110,
        -241, -23,  126,  -241, 41,   2203, -241, 1490, 1490, 1490, -241, 129,  -3,   43,   40,
        -241, -241, -5,   7,    1364, -5,   -241, -241, 122,  116,  -241, -3,   -241, 437,  1858,
        1596, 1790, 1897, -23,  2067, -241, 95,   2203, 2203, 2101, 130,  -241, 40,   135,  -241,
        -5,   1490, -241, -241, -241, 2203, 2203, -241, -241, 54,   -241, -1,   147,  -241, -3,
        -241, 8,    -241, 568,  636,  -241, -2,   -2,   -2,   1364, 347,  1490, 1490, 704,  772,
        -241, -241, -241, -241, -241, -241, -241, -241, -241, -241, -241, -241, -52,  70,   128,
        133,  149,  -5,   -5,   -241, 1490, 1490, 1490, 1490, 1490, -241, -241, -241, -5,   -3,
        48,   73,   137,  -241, -3,   -241, 1490, 84,   -241, 7,    185,  -241, 1092, 188,  1160,
        166,  197,  198,  -241, 150,  128,  133,  1752, 1824, 170,  1228, 151,  1296, 1490, 1364,
        -241, 213,  2203, 2203, 2203, 2203, 2203, 179,  180,  -5,   -241, -5,   -241, 2203, -3,
        -241, -241, -241, -241, -241, -241, 1490, 1490, 1490, 1364, 178,  -241, -241, -241, -241,
        2203, -241, 182,  219,  -241, -241, -241, 176,  -241, 1516, 1556, 1636, 206,  835,  1490,
        190,  -241, -241, 1364, 1364, 1490, 1364, 1364, 192,  189,  195,  -241, 1427, 2135, 2169,
        1490, -241, -241, 1676, -241, -241, -241, 1364, 1364, -241, -241, 1364, -241, 193,  1364,
        -241, -241, -241, -241, -241
    };

    const unsigned char Parser::yydefact_[] = {
        0,   4,   0,   0,   0,   189, 188, 207, 0,   204, 205, 206, 1,   9,   0,   0,   0,   0,
        0,   0,   0,   0,   6,   8,   10,  11,  12,  13,  20,  14,  0,   0,   0,   0,   0,   133,
        135, 134, 0,   0,   0,   0,   0,   0,   0,   139, 140, 136, 137, 138, 141, 208, 74,  76,
        84,  85,  86,  87,  75,  77,  78,  79,  80,  81,  88,  121, 122, 123, 124, 125, 126, 127,
        128, 129, 130, 131, 132, 193, 109, 190, 0,   0,   187, 21,  176, 0,   176, 0,   0,   0,
        5,   0,   195, 200, 194, 0,   0,   0,   0,   0,   108, 89,  90,  0,   0,   0,   73,  0,
        150, 193, 0,   143, 0,   73,  191, 142, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   110, 0,   3,   203, 183, 131, 186, 182,
        0,   0,   0,   0,   0,   0,   171, 0,   0,   0,   0,   0,   0,   0,   0,   83,  0,   0,
        82,  148, 0,   0,   145, 144, 0,   0,   0,   115, 154, 155, 156, 157, 158, 159, 105, 103,
        104, 107, 91,  92,  98,  99,  100, 93,  94,  95,  96,  106, 97,  101, 102, 113, 111, 0,
        167, 0,   73,  192, 0,   0,   0,   22,  0,   0,   0,   0,   202, 173, 0,   0,   0,   0,
        28,  169, 170, 0,   7,   0,   198, 0,   0,   0,   0,   0,   0,   72,  149, 0,   151, 72,
        0,   0,   153, 193, 0,   197, 171, 0,   112, 166, 165, 184, 185, 181, 175, 0,   174, 0,
        0,   25,  0,   27,  0,   23,  0,   0,   42,  0,   0,   0,   0,   0,   0,   0,   0,   0,
        17,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  0,   67,  69,  71,  0,   0,
        0,   199, 0,   0,   0,   0,   0,   114, 147, 146, 0,   0,   0,   153, 0,   164, 0,   172,
        0,   0,   15,  0,   0,   41,  0,   0,   0,   0,   0,   0,   56,  66,  68,  70,  0,   0,
        0,   0,   0,   0,   0,   0,   168, 178, 116, 119, 118, 117, 120, 152, 196, 0,   162, 0,
        201, 16,  0,   26,  64,  62,  40,  60,  58,  0,   0,   0,   0,   0,   59,  57,  63,  61,
        65,  18,  0,   180, 160, 161, 152, 0,   24,  0,   0,   0,   43,  0,   0,   0,   19,  163,
        0,   0,   0,   0,   0,   0,   0,   0,   51,  0,   0,   0,   187, 52,  53,  0,   55,  44,
        46,  0,   0,   45,  50,  0,   177, 0,   0,   47,  48,  49,  179, 54
    };

    const short int Parser::yypgoto_[] = {
        -241, -241, -241, -241, 233,  104,  -241, -241, -241, -241, -241, -51,  -241, -241, 196,
        -240, -241, -241, -241, -130, -241, -241, -241, -241, -241, -241, -241, -241, -241, -40,
        -7,   -47,  -241, 50,   138,  -241, 175,  -241, -241, -241, -241, -241, -241, -241, -241,
        -241, 127,  -241, -241, -241, -241, -241, -241, -241, -77,  -241, -241, 99,   28,   -111,
        -241, -241, -241, -241, -241, -176, -241, 37,   -241, 202,  -241, -241, -241, 62,   -109,
        49,   29,   -241, 58,   -241, -115, -25,  38,   -19,  209,  -241, -241
    };

    const short int Parser::yydefgoto_[] = {
        -1,  3,   4,   21,  22,  23,  24,  25,  26,  27,  28,  255, 256, 29,  311, 312, 271, 272,
        273, 386, 387, 274, 275, 276, 277, 278, 279, 280, 281, 105, 140, 52,  53,  54,  55,  56,
        57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,
        75,  76,  107, 108, 235, 171, 172, 173, 174, 175, 176, 136, 218, 219, 208, 146, 363, 376,
        142, 143, 144, 77,  78,  79,  93,  238, 94,  95,  211, 8,   9,   10,  11
    };

    const short int Parser::yytable_[] = {
        51,  89,  112, 214, 206, 141,  96,  97,  253, 99,  5,   12,  134,  5,   5,   5,   5,   5,
        1,   314, 242, 5,   135, 137,  215, 5,   98,  5,   325, 327, 210,  100, 101, 102, 106, 113,
        138, 150, 216, 217, 170, 82,   222, 83,  43,  91,  207, 43,  43,   80,  207, 7,   295, 151,
        254, 239, 81,  145, 308, 236,  81,  147, 2,   309, 84,  85,  86,   87,  88,  7,   149, 6,
        152, 115, 6,   6,   6,   6,    6,   92,  92,  92,  6,   92,  47,   163, 6,   244, 6,   250,
        109, 153, 114, 167, 164, 199,  168, 160, 251, 221, 168, 252, 304,  339, 286, 340, 81,  154,
        155, 81,  178, 179, 180, 181,  182, 183, 184, 185, 186, 187, 188,  189, 190, 191, 192, 193,
        194, 141, 200, 301, 7,   -169, 344, 156, -84, 240, 210, 328, -169, 81,  7,   241, 158, 159,
        161, 177, 165, 223, 224, 225,  226, 227, 121, 122, 229, 166, 203,  204, 232, 205, 213, 233,
        234, 126, 127, 128, 129, 282,  126, 127, 128, 129, 243, 212, 129,  248, 330, 331, 177, 177,
        287, 288, 177, 196, 338, 298,  201, 337, 249, 342, 299, 306, -85,  329, 209, 245, 246, -87,
        346, 177, -2,  13,  341, 349,  14,  15,  16,  17,  18,  19,  351,  282, 282, 231, -84, 352,
        353, 282, 282, 237, 356, 282,  282, 358, 362, 364, 365, 373, 366,  375, 367, 374, 382, 377,
        303, 307, 315, 316, 317, 390,  397, 177, 396, 408, 177, 13,  398,  20,  14,  15,  16,  17,
        18,  19,  90,  220, 7,   400,  345, 322, 323, 195, 257, 230, 283,  282, 247, 282, 300, 177,
        92,  14,  15,  16,  17,  18,   19,  302, 282, 289, 282, 403, 282,  332, 333, 334, 335, 336,
        148, 305, 139, 20,  0,   0,    0,   0,   0,   0,   0,   343, 209,  0,   0,   7,   0,   0,
        0,   282, 283, 283, 92,  92,   92,  141, 283, 319, 177, 177, 283,  283, 0,   360, 0,   0,
        0,   0,   0,   177, 0,   0,    0,   282, 282, 0,   282, 282, 0,    0,   0,   0,   0,   0,
        0,   0,   369, 370, 371, 0,    209, 0,   282, 282, 284, 209, 282,  0,   0,   282, 257, 0,
        0,   0,   283, 0,   283, 5,    388, 389, 177, 0,   177, 0,   0,    393, 0,   283, 0,   283,
        0,   283, 388, 35,  36,  37,   0,   0,   0,   0,   0,   285, 0,    0,   41,  368, 42,  0,
        284, 284, 0,   43,  0,   44,   284, 320, 283, 0,   284, 284, 0,    0,   270, 0,   0,   0,
        0,   0,   0,   0,   0,   0,    45,  46,  47,  48,  49,  50,  6,    0,   283, 283, 0,   283,
        283, 285, 285, 0,   0,   0,    0,   285, 321, 0,   0,   285, 285,  0,   0,   283, 283, 0,
        284, 283, 284, 0,   283, 290,  0,   0,   0,   0,   318, 0,   0,    284, 0,   284, 0,   284,
        0,   0,   116, 0,   0,   0,    117, 118, 119, 120, 0,   121, 122,  123, 0,   0,   0,   0,
        0,   285, 0,   285, 0,   0,    284, 124, 125, 126, 127, 128, 129,  0,   285, 0,   285, 130,
        285, 131, 132, 133, 348, 0,    348, 0,   0,   0,   0,   0,   284,  284, 0,   284, 284, 348,
        0,   348, 0,   361, 0,   0,    0,   285, 0,   0,   0,   0,   0,    284, 284, 0,   0,   284,
        0,   0,   284, 0,   0,   0,    0,   0,   0,   0,   372, 0,   0,    285, 285, 0,   285, 285,
        0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   310, 0,    0,   285, 285, 391, 392,
        285, 394, 395, 285, 258, 0,    259, 0,   260, 261, 5,   262, 263,  264, 0,   265, 266, 405,
        406, 267, 0,   407, 0,   0,    409, 0,   35,  36,  37,  0,   0,    0,   0,   0,   0,   0,
        0,   41,  0,   42,  0,   268,  0,   0,   43,  0,   44,  0,   0,    0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,    0,   313, 0,   269, 0,   45,  46,   47,  48,  49,  50,  6,
        258, 0,   259, 0,   260, 261,  5,   262, 263, 264, 0,   265, 266,  0,   0,   267, 0,   0,
        0,   0,   0,   0,   35,  36,   37,  0,   0,   0,   0,   0,   0,    0,   0,   41,  0,   42,
        0,   268, 0,   0,   43,  0,    44,  0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,
        0,   0,   0,   324, 0,   269,  0,   45,  46,  47,  48,  49,  50,   6,   258, 0,   259, 0,
        260, 261, 5,   262, 263, 264,  0,   265, 266, 0,   0,   267, 0,    0,   0,   0,   0,   0,
        35,  36,  37,  0,   0,   0,    0,   0,   0,   0,   0,   41,  0,    42,  0,   268, 0,   0,
        43,  0,   44,  0,   0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   326,
        0,   269, 0,   45,  46,  47,   48,  49,  50,  6,   258, 0,   259,  0,   260, 261, 5,   262,
        263, 264, 0,   265, 266, 0,    0,   267, 0,   0,   0,   0,   0,    0,   35,  36,  37,  0,
        0,   0,   0,   121, 122, 123,  0,   41,  0,   42,  0,   268, 0,    0,   43,  0,   44,  124,
        125, 126, 127, 128, 129, 0,    0,   0,   383, 0,   0,   131, 132,  133, 0,   269, 0,   45,
        46,  47,  48,  49,  50,  6,    30,  5,   31,  32,  0,   0,   0,    33,  0,   0,   0,   0,
        384, 0,   34,  0,   0,   35,   36,  37,  0,   0,   0,   0,   38,   39,  40,  0,   41,  0,
        42,  0,   0,   0,   0,   43,   385, 44,  0,   0,   0,   0,   0,    0,   0,   0,   0,   103,
        0,   0,   0,   0,   0,   0,    0,   0,   45,  46,  47,  48,  49,   50,  6,   30,  5,   31,
        32,  0,   0,   0,   33,  0,    0,   0,   0,   0,   0,   34,  0,    0,   35,  36,  37,  0,
        0,   0,   0,   38,  39,  40,   0,   41,  0,   42,  0,   0,   0,    0,   43,  0,   44,  0,
        0,   0,   104, 0,   0,   0,    0,   0,   110, 0,   0,   0,   0,    0,   0,   0,   0,   45,
        46,  47,  48,  49,  50,  6,    30,  5,   31,  32,  0,   0,   0,    33,  0,   0,   0,   0,
        0,   0,   34,  0,   0,   35,   36,  37,  0,   0,   0,   0,   38,   39,  40,  0,   41,  0,
        42,  111, 0,   0,   0,   43,   0,   44,  0,   0,   0,   0,   0,    0,   0,   0,   0,   197,
        0,   0,   0,   0,   0,   0,    0,   0,   45,  46,  47,  48,  49,   50,  6,   30,  5,   31,
        32,  0,   0,   0,   33,  0,    0,   0,   0,   0,   0,   34,  0,    0,   35,  36,  37,  0,
        0,   0,   0,   38,  39,  40,   0,   41,  198, 42,  0,   0,   0,    0,   43,  0,   44,  0,
        0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   45,
        46,  47,  48,  49,  50,  6,    258, 347, 259, 0,   260, 261, 5,    262, 263, 264, 0,   265,
        266, 0,   0,   267, 0,   0,    0,   0,   0,   0,   35,  36,  37,   0,   0,   0,   0,   121,
        122, 0,   0,   41,  0,   42,   0,   268, 0,   0,   43,  0,   44,   124, 125, 126, 127, 128,
        129, 0,   0,   0,   0,   0,    0,   0,   132, 133, 0,   269, 0,    45,  46,  47,  48,  49,
        50,  6,   258, 0,   259, 350,  260, 261, 5,   262, 263, 264, 0,    265, 266, 0,   0,   267,
        0,   0,   0,   0,   0,   0,    35,  36,  37,  0,   0,   0,   0,    0,   0,   0,   0,   41,
        0,   42,  0,   268, 0,   0,    43,  0,   44,  0,   0,   0,   0,    0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,    0,   269, 0,   45,  46,  47,  48,   49,  50,  6,   258, 0,
        259, 0,   260, 261, 5,   262,  263, 264, 0,   265, 266, 0,   0,    267, 0,   0,   0,   0,
        0,   0,   35,  36,  37,  0,    0,   0,   0,   0,   0,   0,   0,    41,  0,   42,  0,   268,
        357, 0,   43,  0,   44,  0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,
        0,   0,   0,   269, 0,   45,   46,  47,  48,  49,  50,  6,   258,  0,   259, 0,   260, 261,
        5,   262, 263, 264, 0,   265,  266, 0,   0,   267, 0,   0,   0,    0,   0,   0,   35,  36,
        37,  0,   0,   0,   0,   0,    0,   0,   0,   41,  0,   42,  0,    268, 0,   0,   43,  0,
        44,  0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   269,
        359, 45,  46,  47,  48,  49,   50,  6,   258, 0,   259, 0,   260,  261, 5,   262, 263, 264,
        0,   265, 266, 0,   0,   267,  0,   0,   0,   0,   0,   0,   35,   36,  37,  0,   0,   0,
        0,   0,   0,   0,   0,   41,   0,   42,  0,   268, 0,   0,   43,   0,   44,  0,   0,   0,
        0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,    269, 0,   45,  46,  47,
        48,  49,  50,  6,   30,  5,    31,  32,  0,   0,   0,   33,  0,    0,   0,   0,   384, 0,
        34,  0,   0,   35,  36,  37,   0,   0,   0,   0,   38,  39,  40,   0,   41,  0,   42,  0,
        0,   399, 0,   43,  385, 44,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,    45,  46,  47,  48,  49,  50,  6,    30,  5,   31,  32,  0,
        0,   0,   33,  0,   0,   0,    0,   0,   0,   34,  0,   0,   35,   36,  37,  0,   0,   0,
        0,   38,  39,  40,  378, 41,   0,   42,  0,   0,   0,   0,   43,   0,   44,  0,   0,   0,
        0,   116, 0,   0,   0,   117,  118, 119, 120, 0,   121, 122, 123,  0,   0,   45,  46,  47,
        48,  49,  50,  6,   0,   0,    124, 125, 126, 127, 128, 129, 379,  0,   0,   0,   130, 0,
        131, 132, 133, 0,   380, 116,  0,   0,   0,   117, 118, 119, 120,  0,   121, 122, 123, 0,
        0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   124, 125, 126,  127, 128, 129, 292, 0,
        0,   0,   130, 0,   131, 132,  133, 0,   0,   116, 0,   0,   0,    117, 118, 119, 120, 0,
        121, 122, 123, 0,   0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   124, 125, 126, 127,
        128, 129, 381, 0,   0,   0,    130, 0,   131, 132, 133, 0,   0,    116, 0,   0,   0,   117,
        118, 119, 120, 0,   121, 122,  123, 0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,
        124, 125, 126, 127, 128, 129,  404, 0,   0,   0,   130, 0,   131,  132, 133, 0,   0,   116,
        0,   0,   0,   117, 118, 119,  120, 0,   121, 122, 123, 0,   0,    0,   0,   0,   0,   0,
        0,   0,   0,   0,   124, 125,  126, 127, 128, 129, 0,   157, 0,    0,   130, 0,   131, 132,
        133, 116, 0,   0,   0,   117,  118, 119, 120, 0,   121, 122, 123,  0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,    124, 125, 126, 127, 128, 129, 0,    354, 0,   0,   130, 0,
        131, 132, 133, 116, 0,   0,    0,   117, 118, 119, 120, 0,   121,  122, 123, 0,   0,   0,
        0,   0,   0,   0,   0,   0,    0,   0,   124, 125, 126, 127, 128,  129, 0,   0,   293, 0,
        130, 0,   131, 132, 133, 116,  0,   0,   0,   117, 118, 119, 120,  0,   121, 122, 123, 0,
        0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   124, 125, 126,  127, 128, 129, 355, 0,
        0,   0,   130, 116, 131, 132,  133, 117, 118, 119, 120, 0,   121,  122, 123, 0,   0,   0,
        0,   0,   0,   0,   0,   0,    0,   0,   124, 125, 126, 127, 128,  129, 0,   0,   291, 0,
        130, 116, 131, 132, 133, 117,  118, 119, 120, 0,   121, 122, 123,  0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,    124, 125, 126, 127, 128, 129, 0,    0,   0,   0,   130, 0,
        131, 132, 133, 294, 116, 0,    0,   0,   117, 118, 119, 120, 0,    121, 122, 123, 0,   0,
        0,   0,   0,   0,   0,   0,    0,   0,   0,   124, 125, 126, 127,  128, 129, 0,   0,   0,
        0,   130, 116, 131, 132, 133,  117, 118, 119, 120, 0,   121, 122,  123, 0,   162, 0,   0,
        0,   0,   0,   0,   0,   0,    0,   124, 125, 126, 127, 128, 129,  0,   0,   0,   0,   130,
        116, 131, 132, 133, 117, 118,  119, 120, 0,   121, 122, 123, 0,    0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   124,  125, 126, 127, 128, 129, 0,   169,  0,   0,   130, 116, 131,
        132, 133, 117, 118, 119, 120,  0,   121, 122, 123, 0,   0,   0,    0,   0,   0,   0,   0,
        0,   0,   0,   124, 125, 126,  127, 128, 129, 0,   0,   0,   202,  130, 116, 131, 132, 133,
        117, 118, 119, 120, 0,   121,  122, 123, 0,   228, 0,   0,   0,    0,   0,   0,   0,   0,
        0,   124, 125, 126, 127, 128,  129, 0,   0,   0,   0,   130, 116,  131, 132, 133, 117, 118,
        119, 120, 0,   121, 122, 123,  0,   296, 0,   0,   0,   0,   0,    0,   0,   0,   0,   124,
        125, 126, 127, 128, 129, 0,    0,   0,   0,   130, 116, 131, 132,  133, 117, 118, 119, 120,
        0,   121, 122, 123, 0,   0,    0,   297, 0,   0,   0,   0,   0,    0,   0,   124, 125, 126,
        127, 128, 129, 0,   0,   0,    0,   130, 116, 131, 132, 133, 117,  118, 119, 120, 0,   121,
        122, 123, 0,   0,   0,   0,    0,   0,   401, 0,   0,   0,   0,    124, 125, 126, 127, 128,
        129, 0,   0,   0,   0,   130,  116, 131, 132, 133, 117, 118, 119,  120, 0,   121, 122, 123,
        0,   0,   0,   0,   0,   402,  0,   0,   0,   0,   0,   124, 125,  126, 127, 128, 129, 0,
        0,   0,   0,   130, 116, 131,  132, 133, 117, 118, 119, 120, 0,    121, 122, 123, 0,   0,
        0,   0,   0,   0,   0,   0,    0,   0,   0,   124, 125, 126, 127,  128, 129, 0,   0,   0,
        0,   130, 0,   131, 132, 133,  117, 118, 119, 0,   0,   121, 122,  123, 0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,    0,   124, 125, 126, 127, 128, 129,  0,   0,   0,   0,   0,
        0,   131, 132, 133, 117, 0,    119, 0,   0,   121, 122, 123, 0,    0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   124,  125, 126, 127, 128, 129, 0,   0,    0,   0,   117, 0,   131,
        132, 133, 121, 122, 123, 0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   124, 125,
        126, 127, 128, 129, 0,   0,    0,   0,   0,   0,   131, 132, 133
    };

    const short int Parser::yycheck_[] = {
        7,   20,  42,  44,  1,   82,  31,  32,  1,   34,  18,  0,   64,  18,  18,  18,  18,  18,
        3,   259, 196, 18,  45,  52,  65,  18,  33,  18,  268, 269, 145, 38,  39,  40,  41,  42,
        3,   51,  149, 150, 45,  49,  153, 14,  52,  47,  47,  52,  52,  48,  47,  2,   228, 48,
        47,  170, 55,  45,  50,  170, 55,  44,  47,  55,  15,  16,  17,  18,  19,  20,  44,  79,
        91,  44,  79,  79,  79,  79,  79,  30,  31,  32,  79,  34,  75,  46,  79,  46,  79,  46,
        41,  51,  43,  48,  55,  135, 55,  104, 55,  48,  55,  212, 48,  55,  215, 57,  55,  44,
        18,  55,  117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132,
        133, 204, 135, 240, 81,  58,  48,  18,  64,  56,  251, 67,  65,  55,  91,  62,  18,  46,
        55,  116, 51,  154, 155, 156, 157, 158, 42,  43,  161, 48,  65,  55,  165, 50,  49,  168,
        169, 58,  59,  60,  61,  214, 58,  59,  60,  61,  46,  65,  61,  46,  287, 288, 149, 150,
        58,  65,  153, 134, 299, 55,  137, 298, 207, 304, 55,  44,  64,  44,  145, 202, 203, 64,
        13,  170, 0,   1,   65,  15,  4,   5,   6,   7,   8,   9,   44,  258, 259, 164, 64,  18,
        18,  264, 265, 170, 50,  268, 269, 72,  11,  46,  46,  49,  339, 10,  341, 49,  26,  57,
        241, 254, 261, 262, 263, 49,  51,  212, 50,  50,  215, 1,   51,  47,  4,   5,   6,   7,
        8,   9,   21,  151, 207, 387, 309, 266, 267, 134, 213, 164, 214, 312, 204, 314, 240, 240,
        221, 4,   5,   6,   7,   8,   9,   240, 325, 221, 327, 390, 329, 290, 291, 292, 293, 294,
        86,  251, 81,  47,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  306, 251, -1,  -1,  254, -1,  -1,
        -1,  354, 258, 259, 261, 262, 263, 390, 264, 265, 287, 288, 268, 269, -1,  328, -1,  -1,
        -1,  -1,  -1,  298, -1,  -1,  -1,  378, 379, -1,  381, 382, -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  351, 352, 353, -1,  299, -1,  397, 398, 214, 304, 401, -1,  -1,  404, 309, -1,
        -1,  -1,  312, -1,  314, 18,  373, 374, 339, -1,  341, -1,  -1,  380, -1,  325, -1,  327,
        -1,  329, 387, 34,  35,  36,  -1,  -1,  -1,  -1,  -1,  214, -1,  -1,  45,  344, 47,  -1,
        258, 259, -1,  52,  -1,  54,  264, 265, 354, -1,  268, 269, -1,  -1,  214, -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,  76,  77,  78,  79,  -1,  378, 379, -1,  381,
        382, 258, 259, -1,  -1,  -1,  -1,  264, 265, -1,  -1,  268, 269, -1,  -1,  397, 398, -1,
        312, 401, 314, -1,  404, 18,  -1,  -1,  -1,  -1,  264, -1,  -1,  325, -1,  327, -1,  329,
        -1,  -1,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,
        -1,  312, -1,  314, -1,  -1,  354, 56,  57,  58,  59,  60,  61,  -1,  325, -1,  327, 66,
        329, 68,  69,  70,  312, -1,  314, -1,  -1,  -1,  -1,  -1,  378, 379, -1,  381, 382, 325,
        -1,  327, -1,  329, -1,  -1,  -1,  354, -1,  -1,  -1,  -1,  -1,  397, 398, -1,  -1,  401,
        -1,  -1,  404, -1,  -1,  -1,  -1,  -1,  -1,  -1,  354, -1,  -1,  378, 379, -1,  381, 382,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  397, 398, 378, 379,
        401, 381, 382, 404, 12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  397,
        398, 27,  -1,  401, -1,  -1,  404, -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,
        12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,
        -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,
        -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  1,   -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  12,  -1,  14,  -1,
        16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,
        34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,
        52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,
        -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  12,  -1,  14,  -1,  16,  17,  18,  19,
        20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,
        -1,  -1,  -1,  42,  43,  44,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  56,
        57,  58,  59,  60,  61,  -1,  -1,  -1,  1,   -1,  -1,  68,  69,  70,  -1,  71,  -1,  73,
        74,  75,  76,  77,  78,  79,  17,  18,  19,  20,  -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,
        29,  -1,  31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  41,  42,  43,  -1,  45,  -1,
        47,  -1,  -1,  -1,  -1,  52,  53,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,  76,  77,  78,  79,  17,  18,  19,
        20,  -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,  -1,  -1,  31,  -1,  -1,  34,  35,  36,  -1,
        -1,  -1,  -1,  41,  42,  43,  -1,  45,  -1,  47,  -1,  -1,  -1,  -1,  52,  -1,  54,  -1,
        -1,  -1,  58,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  73,
        74,  75,  76,  77,  78,  79,  17,  18,  19,  20,  -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,
        -1,  -1,  31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  41,  42,  43,  -1,  45,  -1,
        47,  48,  -1,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,  76,  77,  78,  79,  17,  18,  19,
        20,  -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,  -1,  -1,  31,  -1,  -1,  34,  35,  36,  -1,
        -1,  -1,  -1,  41,  42,  43,  -1,  45,  46,  47,  -1,  -1,  -1,  -1,  52,  -1,  54,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  73,
        74,  75,  76,  77,  78,  79,  12,  13,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,
        24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  42,
        43,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  56,  57,  58,  59,  60,
        61,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  69,  70,  -1,  71,  -1,  73,  74,  75,  76,  77,
        78,  79,  12,  -1,  14,  15,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,
        -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,
        -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  12,  -1,
        14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,
        -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,
        50,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  12,  -1,  14,  -1,  16,  17,
        18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,
        36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,
        54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,
        72,  73,  74,  75,  76,  77,  78,  79,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,
        -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  71,  -1,  73,  74,  75,
        76,  77,  78,  79,  17,  18,  19,  20,  -1,  -1,  -1,  24,  -1,  -1,  -1,  -1,  29,  -1,
        31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  41,  42,  43,  -1,  45,  -1,  47,  -1,
        -1,  50,  -1,  52,  53,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  73,  74,  75,  76,  77,  78,  79,  17,  18,  19,  20,  -1,
        -1,  -1,  24,  -1,  -1,  -1,  -1,  -1,  -1,  31,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,
        -1,  41,  42,  43,  18,  45,  -1,  47,  -1,  -1,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,
        -1,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  73,  74,  75,
        76,  77,  78,  79,  -1,  -1,  56,  57,  58,  59,  60,  61,  22,  -1,  -1,  -1,  66,  -1,
        68,  69,  70,  -1,  32,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  22,  -1,
        -1,  -1,  66,  -1,  68,  69,  70,  -1,  -1,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,
        42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,
        60,  61,  22,  -1,  -1,  -1,  66,  -1,  68,  69,  70,  -1,  -1,  33,  -1,  -1,  -1,  37,
        38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        56,  57,  58,  59,  60,  61,  22,  -1,  -1,  -1,  66,  -1,  68,  69,  70,  -1,  -1,  33,
        -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  25,  -1,  -1,  66,  -1,  68,  69,
        70,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  25,  -1,  -1,  66,  -1,
        68,  69,  70,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  26,  -1,
        66,  -1,  68,  69,  70,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  28,  -1,
        -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  30,  -1,
        66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  -1,
        68,  69,  70,  32,  33,  -1,  -1,  -1,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,
        -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  46,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,
        33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  63,  -1,  -1,  66,  33,  68,
        69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  65,  66,  33,  68,  69,  70,
        37,  38,  39,  40,  -1,  42,  43,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,
        39,  40,  -1,  42,  43,  44,  -1,  46,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,
        57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,
        -1,  42,  43,  44,  -1,  -1,  -1,  48,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,
        59,  60,  61,  -1,  -1,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,
        43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  51,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,
        61,  -1,  -1,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,
        -1,  -1,  -1,  -1,  -1,  50,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,
        -1,  -1,  -1,  66,  33,  68,  69,  70,  37,  38,  39,  40,  -1,  42,  43,  44,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,
        -1,  66,  -1,  68,  69,  70,  37,  38,  39,  -1,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  -1,
        -1,  68,  69,  70,  37,  -1,  39,  -1,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  37,  -1,  68,
        69,  70,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  56,  57,
        58,  59,  60,  61,  -1,  -1,  -1,  -1,  -1,  -1,  68,  69,  70
    };

    const unsigned char Parser::yystos_[] = {
        0,   3,   47,  85,  86,  18,  79,  159, 167, 168, 169, 170, 0,   1,   4,   5,   6,   7,
        8,   9,   47,  87,  88,  89,  90,  91,  92,  93,  94,  97,  17,  19,  20,  24,  31,  34,
        35,  36,  41,  42,  43,  45,  47,  52,  54,  73,  74,  75,  76,  77,  78,  114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
        135, 136, 137, 138, 139, 159, 160, 161, 48,  55,  49,  160, 159, 159, 159, 159, 159, 167,
        88,  47,  159, 162, 164, 165, 165, 165, 114, 165, 114, 114, 114, 1,   58,  113, 114, 140,
        141, 159, 1,   48,  113, 114, 159, 160, 33,  37,  38,  39,  40,  42,  43,  44,  56,  57,
        58,  59,  60,  61,  66,  68,  69,  70,  64,  45,  149, 52,  3,   168, 114, 138, 156, 157,
        158, 45,  153, 44,  153, 44,  51,  48,  167, 51,  44,  18,  18,  25,  18,  46,  114, 55,
        46,  46,  55,  51,  48,  48,  55,  63,  45,  143, 144, 145, 146, 147, 148, 160, 114, 114,
        114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 130, 159, 1,
        46,  113, 114, 159, 65,  65,  55,  50,  1,   47,  152, 159, 164, 166, 65,  49,  44,  65,
        143, 143, 150, 151, 89,  48,  143, 114, 114, 114, 114, 114, 46,  114, 141, 159, 114, 114,
        114, 142, 143, 159, 163, 164, 56,  62,  149, 46,  46,  114, 114, 157, 46,  167, 46,  55,
        143, 1,   47,  95,  96,  159, 12,  14,  16,  17,  19,  20,  21,  23,  24,  27,  49,  71,
        98,  100, 101, 102, 105, 106, 107, 108, 109, 110, 111, 112, 115, 117, 118, 120, 143, 58,
        65,  162, 18,  30,  22,  26,  32,  149, 46,  48,  55,  55,  142, 143, 151, 114, 48,  166,
        44,  167, 50,  55,  1,   98,  99,  1,   99,  165, 165, 165, 98,  117, 118, 120, 114, 114,
        1,   99,  1,   99,  67,  44,  143, 143, 114, 114, 114, 114, 114, 143, 164, 55,  57,  65,
        164, 114, 48,  95,  13,  13,  98,  15,  15,  44,  18,  18,  25,  28,  50,  50,  72,  72,
        114, 98,  11,  154, 46,  46,  143, 143, 159, 114, 114, 114, 98,  49,  49,  10,  155, 57,
        18,  22,  32,  22,  26,  1,   29,  53,  103, 104, 114, 114, 49,  98,  98,  114, 98,  98,
        50,  51,  51,  50,  103, 51,  50,  158, 22,  98,  98,  98,  50,  98
    };

    const unsigned char Parser::yyr1_[] = {
        0,   84,  85,  86,  86,  87,  87,  88,  88,  88,  89,  89,  89,  89,  89,  90,  91,  92,
        92,  93,  93,  94,  94,  95,  95,  95,  96,  96,  97,  98,  98,  98,  98,  98,  98,  98,
        98,  98,  98,  98,  99,  99,  100, 101, 101, 102, 102, 103, 103, 103, 104, 104, 105, 106,
        106, 107, 108, 109, 109, 109, 109, 110, 110, 110, 110, 111, 112, 112, 112, 112, 112, 112,
        113, 113, 114, 114, 114, 114, 114, 114, 114, 114, 115, 115, 115, 115, 115, 115, 115, 116,
        116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116,
        116, 117, 117, 118, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 127, 127, 127, 127,
        127, 127, 127, 127, 127, 127, 127, 128, 129, 129, 130, 131, 132, 133, 133, 134, 135, 136,
        136, 136, 137, 138, 139, 140, 140, 141, 142, 142, 143, 143, 143, 143, 143, 144, 145, 145,
        146, 147, 148, 149, 149, 149, 150, 150, 151, 151, 152, 152, 153, 153, 153, 154, 154, 155,
        155, 156, 156, 157, 157, 157, 158, 158, 159, 159, 160, 160, 161, 161, 162, 162, 163, 163,
        164, 165, 165, 166, 166, 167, 167, 168, 168, 169, 170
    };

    const unsigned char Parser::yyr2_[] = {
        0, 2, 2, 4, 1, 2, 1, 4, 1, 1, 1, 1, 1, 1, 1, 6, 7, 5, 7, 8, 1, 2, 4, 1, 4, 1, 3, 1, 4, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 4, 6, 6, 6, 3, 3, 3, 2, 1, 6, 6, 8, 6, 2, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 2,
        2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 2, 3, 4, 3, 5, 3, 6, 6, 6, 6,
        6, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 5, 5, 3, 3,
        1, 3, 3, 1, 1, 1, 1, 1, 1, 1, 5, 5, 4, 6, 3, 3, 3, 2, 3, 1, 1, 0, 3, 1, 3, 3, 0, 4, 0, 4,
        0, 3, 1, 1, 3, 3, 1, 0, 1, 1, 1, 2, 3, 1, 1, 1, 3, 1, 3, 4, 1, 4, 1, 3, 1, 1, 1, 1, 2
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
                                             "LiteralCallExpression",
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
                                             "TemplateType",
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
                                             "TypedVariables",
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
        0,    394,  394,  403,  409,  417,  423,  433,  439,  443,  451,  455,  459,  463,  467,
        475,  483,  491,  496,  505,  521,  529,  552,  570,  574,  580,  588,  594,  604,  616,
        620,  624,  628,  632,  636,  640,  644,  648,  652,  656,  664,  670,  680,  688,  692,
        700,  704,  712,  716,  720,  728,  734,  744,  752,  756,  764,  772,  780,  784,  788,
        793,  802,  806,  810,  815,  824,  834,  838,  842,  846,  850,  854,  866,  872,  882,
        886,  890,  894,  898,  902,  906,  910,  918,  922,  926,  930,  934,  938,  942,  954,
        958,  962,  966,  970,  974,  978,  982,  986,  990,  994,  998,  1002, 1006, 1010, 1014,
        1018, 1022, 1026, 1030, 1038, 1043, 1051, 1056, 1064, 1072, 1080, 1088, 1096, 1104, 1112,
        1120, 1132, 1136, 1140, 1144, 1148, 1152, 1156, 1160, 1164, 1168, 1172, 1176, 1184, 1192,
        1197, 1206, 1222, 1238, 1254, 1266, 1282, 1298, 1306, 1311, 1315, 1323, 1330, 1338, 1345,
        1351, 1360, 1372, 1378, 1388, 1392, 1396, 1400, 1404, 1412, 1420, 1427, 1447, 1455, 1463,
        1475, 1479, 1483, 1497, 1503, 1513, 1517, 1525, 1531, 1541, 1545, 1549, 1561, 1565, 1573,
        1577, 1585, 1591, 1601, 1609, 1619, 1630, 1634, 1646, 1650, 1658, 1662, 1672, 1678, 1692,
        1696, 1705, 1711, 1721, 1729, 1735, 1743, 1749, 1760, 1766, 1775, 1779, 1787, 1795
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
#line 4390 "GrammarParser.cpp"               // lalr1.cc:1167
#line 1801 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1168

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
