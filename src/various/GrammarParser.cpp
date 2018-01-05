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
            case 166:  // Attribute
                value.move< Attribute::Ptr >( that.value );
                break;

            case 165:  // Attributes
                value.move< Attributes::Ptr >( that.value );
                break;

            case 167:  // BasicAttribute
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
            case 153:  // MaybeDefined
                value.move< Expression::Ptr >( that.value );
                break;

            case 168:  // ExpressionAttribute
                value.move< ExpressionAttribute::Ptr >( that.value );
                break;

            case 113:  // Terms
            case 148:  // Arguments
                value.move< Expressions::Ptr >( that.value );
                break;

            case 147:  // FixedSizedType
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

            case 158:  // Identifier
                value.move< Identifier::Ptr >( that.value );
                break;

            case 159:  // IdentifierPath
                value.move< IdentifierPath::Ptr >( that.value );
                break;

            case 160:  // DotSeparatedIdentifiers
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

            case 151:  // Parameters
            case 152:  // MaybeParameters
                value.move< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 136:  // RangeLiteral
                value.move< RangeLiteral::Ptr >( that.value );
                break;

            case 134:  // ReferenceLiteral
                value.move< ReferenceLiteral::Ptr >( that.value );
                break;

            case 146:  // RelationType
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

            case 145:  // TemplateType
                value.move< TemplateType::Ptr >( that.value );
                break;

            case 137:  // TupleLiteral
                value.move< TupleLiteral::Ptr >( that.value );
                break;

            case 120:  // TypeCastingExpression
                value.move< TypeCastingExpression::Ptr >( that.value );
                break;

            case 141:  // Types
            case 149:  // FunctionParameters
            case 150:  // MaybeFunctionParameters
                value.move< Types::Ptr >( that.value );
                break;

            case 127:  // UndefinedLiteral
                value.move< UndefLiteral::Ptr >( that.value );
                break;

            case 124:  // UniversalQuantifierExpression
                value.move< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // UpdateRule
            case 156:  // Initializer
                value.move< UpdateRule::Ptr >( that.value );
                break;

            case 154:  // MaybeInitially
            case 155:  // Initializers
            case 157:  // MaybeInitializers
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

            case 161:  // Variable
            case 162:  // TypedVariable
            case 163:  // AttributedVariable
            case 164:  // TypedAttributedVariable
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
            case 166:  // Attribute
                value.copy< Attribute::Ptr >( that.value );
                break;

            case 165:  // Attributes
                value.copy< Attributes::Ptr >( that.value );
                break;

            case 167:  // BasicAttribute
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
            case 153:  // MaybeDefined
                value.copy< Expression::Ptr >( that.value );
                break;

            case 168:  // ExpressionAttribute
                value.copy< ExpressionAttribute::Ptr >( that.value );
                break;

            case 113:  // Terms
            case 148:  // Arguments
                value.copy< Expressions::Ptr >( that.value );
                break;

            case 147:  // FixedSizedType
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

            case 158:  // Identifier
                value.copy< Identifier::Ptr >( that.value );
                break;

            case 159:  // IdentifierPath
                value.copy< IdentifierPath::Ptr >( that.value );
                break;

            case 160:  // DotSeparatedIdentifiers
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

            case 151:  // Parameters
            case 152:  // MaybeParameters
                value.copy< NodeList< VariableDefinition >::Ptr >( that.value );
                break;

            case 136:  // RangeLiteral
                value.copy< RangeLiteral::Ptr >( that.value );
                break;

            case 134:  // ReferenceLiteral
                value.copy< ReferenceLiteral::Ptr >( that.value );
                break;

            case 146:  // RelationType
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

            case 145:  // TemplateType
                value.copy< TemplateType::Ptr >( that.value );
                break;

            case 137:  // TupleLiteral
                value.copy< TupleLiteral::Ptr >( that.value );
                break;

            case 120:  // TypeCastingExpression
                value.copy< TypeCastingExpression::Ptr >( that.value );
                break;

            case 141:  // Types
            case 149:  // FunctionParameters
            case 150:  // MaybeFunctionParameters
                value.copy< Types::Ptr >( that.value );
                break;

            case 127:  // UndefinedLiteral
                value.copy< UndefLiteral::Ptr >( that.value );
                break;

            case 124:  // UniversalQuantifierExpression
                value.copy< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 111:  // UpdateRule
            case 156:  // Initializer
                value.copy< UpdateRule::Ptr >( that.value );
                break;

            case 154:  // MaybeInitially
            case 155:  // Initializers
            case 157:  // MaybeInitializers
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

            case 161:  // Variable
            case 162:  // TypedVariable
            case 163:  // AttributedVariable
            case 164:  // TypedAttributedVariable
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
                    case 166:  // Attribute
                        yylhs.value.build< Attribute::Ptr >();
                        break;

                    case 165:  // Attributes
                        yylhs.value.build< Attributes::Ptr >();
                        break;

                    case 167:  // BasicAttribute
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
                    case 153:  // MaybeDefined
                        yylhs.value.build< Expression::Ptr >();
                        break;

                    case 168:  // ExpressionAttribute
                        yylhs.value.build< ExpressionAttribute::Ptr >();
                        break;

                    case 113:  // Terms
                    case 148:  // Arguments
                        yylhs.value.build< Expressions::Ptr >();
                        break;

                    case 147:  // FixedSizedType
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

                    case 158:  // Identifier
                        yylhs.value.build< Identifier::Ptr >();
                        break;

                    case 159:  // IdentifierPath
                        yylhs.value.build< IdentifierPath::Ptr >();
                        break;

                    case 160:  // DotSeparatedIdentifiers
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

                    case 151:  // Parameters
                    case 152:  // MaybeParameters
                        yylhs.value.build< NodeList< VariableDefinition >::Ptr >();
                        break;

                    case 136:  // RangeLiteral
                        yylhs.value.build< RangeLiteral::Ptr >();
                        break;

                    case 134:  // ReferenceLiteral
                        yylhs.value.build< ReferenceLiteral::Ptr >();
                        break;

                    case 146:  // RelationType
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

                    case 145:  // TemplateType
                        yylhs.value.build< TemplateType::Ptr >();
                        break;

                    case 137:  // TupleLiteral
                        yylhs.value.build< TupleLiteral::Ptr >();
                        break;

                    case 120:  // TypeCastingExpression
                        yylhs.value.build< TypeCastingExpression::Ptr >();
                        break;

                    case 141:  // Types
                    case 149:  // FunctionParameters
                    case 150:  // MaybeFunctionParameters
                        yylhs.value.build< Types::Ptr >();
                        break;

                    case 127:  // UndefinedLiteral
                        yylhs.value.build< UndefLiteral::Ptr >();
                        break;

                    case 124:  // UniversalQuantifierExpression
                        yylhs.value.build< UniversalQuantifierExpression::Ptr >();
                        break;

                    case 111:  // UpdateRule
                    case 156:  // Initializer
                        yylhs.value.build< UpdateRule::Ptr >();
                        break;

                    case 154:  // MaybeInitially
                    case 155:  // Initializers
                    case 157:  // MaybeInitializers
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

                    case 161:  // Variable
                    case 162:  // TypedVariable
                    case 163:  // AttributedVariable
                    case 164:  // TypedAttributedVariable
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
#line 393 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            specification.setHeader(
                                yystack_[ 1 ].value.as< HeaderDefinition::Ptr >() );
                            specification.setDefinitions(
                                yystack_[ 0 ].value.as< Definitions::Ptr >() );
                        }
#line 1446 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 3:
#line 402 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< HeaderDefinition::Ptr >() = definition;
                        }
#line 1456 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 4:
#line 408 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< HeaderDefinition::Ptr >() =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                        }
#line 1464 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 5:
#line 416 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = yystack_[ 1 ].value.as< Definitions::Ptr >();
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1474 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 6:
#line 422 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = Ast::make< Definitions >( yylhs.location );
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1484 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 7:
#line 432 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition = yystack_[ 0 ].value.as< Definition::Ptr >();
                            definition->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< Definition::Ptr >() = definition;
                        }
#line 1494 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 8:
#line 438 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< Definition::Ptr >();
                        }
#line 1502 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 9:
#line 442 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() = nullptr;
                        }
#line 1510 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 10:
#line 450 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< EnumerationDefinition::Ptr >();
                        }
#line 1518 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 11:
#line 454 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< DerivedDefinition::Ptr >();
                        }
#line 1526 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 12:
#line 458 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< RuleDefinition::Ptr >();
                        }
#line 1534 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 13:
#line 462 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< FunctionDefinition::Ptr >();
                        }
#line 1542 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 14:
#line 466 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< UsingDefinition::Ptr >();
                        }
#line 1550 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 15:
#line 474 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumerationDefinition::Ptr >() =
                                Ast::make< EnumerationDefinition >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 1 ].value.as< Enumerators::Ptr >() );
                        }
#line 1558 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 16:
#line 482 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DerivedDefinition::Ptr >() =
                                Ast::make< DerivedDefinition >(
                                    yylhs.location,
                                    yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                    yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1566 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 17:
#line 490 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Identifier::Ptr >(),
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                createVoidType( yylhs.location ),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1575 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 18:
#line 495 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                yystack_[ 4 ].value.as< NodeList< VariableDefinition >::Ptr >(),
                                yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1584 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 19:
#line 504 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1604 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 20:
#line 520 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FunctionDefinition::Ptr >() =
                                yystack_[ 0 ]
                                    .value.as< FunctionDefinition::Ptr >();  // `init` special case
                        }
#line 1612 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 21:
#line 528 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1639 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 22:
#line 551 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 1657 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 23:
#line 569 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() =
                                Ast::make< EnumeratorDefinition >(
                                    yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 1665 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 24:
#line 573 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerator = Ast::make< EnumeratorDefinition >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            enumerator->setAttributes(
                                yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = enumerator;
                        }
#line 1675 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 25:
#line 579 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = nullptr;
                        }
#line 1683 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 26:
#line 587 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = yystack_[ 2 ].value.as< Enumerators::Ptr >();
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1693 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 27:
#line 593 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = Ast::make< Enumerators >( yylhs.location );
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1703 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 28:
#line 603 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UsingDefinition::Ptr >() = Ast::make< UsingDefinition >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 1711 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 29:
#line 615 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SkipRule::Ptr >();
                        }
#line 1719 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 30:
#line 619 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalRule::Ptr >();
                        }
#line 1727 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 31:
#line 623 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CaseRule::Ptr >();
                        }
#line 1735 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 32:
#line 627 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< LetRule::Ptr >();
                        }
#line 1743 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 33:
#line 631 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ForallRule::Ptr >();
                        }
#line 1751 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 34:
#line 635 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseRule::Ptr >();
                        }
#line 1759 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 35:
#line 639 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< IterateRule::Ptr >();
                        }
#line 1767 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 36:
#line 643 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< BlockRule::Ptr >();
                        }
#line 1775 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 37:
#line 647 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SequenceRule::Ptr >();
                        }
#line 1783 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 38:
#line 651 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRule::Ptr >();
                        }
#line 1791 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 39:
#line 655 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CallRule::Ptr >();
                        }
#line 1799 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 40:
#line 663 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = yystack_[ 1 ].value.as< Rules::Ptr >();
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1809 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 41:
#line 669 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = Ast::make< Rules >( yylhs.location );
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1819 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 42:
#line 679 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SkipRule::Ptr >() =
                                Ast::make< SkipRule >( yylhs.location );
                        }
#line 1827 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 43:
#line 687 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1835 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 44:
#line 691 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Rule::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1843 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 45:
#line 699 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = Ast::make< CaseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Cases::Ptr >() );
                        }
#line 1851 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 46:
#line 703 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = nullptr;
                        }
#line 1859 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 47:
#line 711 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1867 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 48:
#line 715 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1875 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 49:
#line 719 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< ExpressionCase >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1883 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 50:
#line 727 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = yystack_[ 1 ].value.as< Cases::Ptr >();
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1893 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 51:
#line 733 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = Ast::make< Cases >( yylhs.location );
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1903 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 52:
#line 743 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetRule::Ptr >() = Ast::make< LetRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1911 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 53:
#line 751 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1919 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 54:
#line 755 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ForallRule::Ptr >() = Ast::make< ForallRule >(
                                yylhs.location,
                                yystack_[ 6 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1927 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 55:
#line 763 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseRule::Ptr >() = Ast::make< ChooseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1935 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 56:
#line 771 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IterateRule::Ptr >() = Ast::make< IterateRule >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1943 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 57:
#line 779 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1951 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 58:
#line 783 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1959 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 59:
#line 787 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1968 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 60:
#line 792 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1977 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 61:
#line 801 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1985 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 62:
#line 805 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1993 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 63:
#line 809 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 2002 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 64:
#line 814 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 2011 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 65:
#line 823 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto function =
                                yystack_[ 2 ].value.as< DirectCallExpression::Ptr >();
                            function->setTargetType( CallExpression::TargetType::FUNCTION );
                            yylhs.value.as< UpdateRule::Ptr >() = Ast::make< UpdateRule >(
                                yylhs.location,
                                function,
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2021 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 66:
#line 833 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 2029 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 67:
#line 837 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 2037 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 68:
#line 841 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 2045 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 69:
#line 845 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 2053 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 70:
#line 849 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::RULE_CALL );
                        }
#line 2061 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 71:
#line 853 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >(),
                                CallRule::Type::FUNCTION_CALL );
                        }
#line 2069 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 72:
#line 865 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto expressions = yystack_[ 2 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2079 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 73:
#line 871 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2089 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 74:
#line 881 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2097 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 75:
#line 885 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TypeCastingExpression::Ptr >();
                        }
#line 2105 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 76:
#line 889 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2113 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 77:
#line 893 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LetExpression::Ptr >();
                        }
#line 2121 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 78:
#line 897 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalExpression::Ptr >();
                        }
#line 2129 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 79:
#line 901 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseExpression::Ptr >();
                        }
#line 2137 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 80:
#line 905 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UniversalQuantifierExpression::Ptr >();
                        }
#line 2145 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 81:
#line 909 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ExistentialQuantifierExpression::Ptr >();
                        }
#line 2153 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 82:
#line 917 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2161 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 83:
#line 921 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = nullptr;
                        }
#line 2169 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 84:
#line 925 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >();
                        }
#line 2177 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 85:
#line 929 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >();
                        }
#line 2185 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 86:
#line 933 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >();
                        }
#line 2193 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 87:
#line 937 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2201 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 88:
#line 949 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2209 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 89:
#line 953 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::INV_INSTRUCTION );
                        }
#line 2217 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 90:
#line 957 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::ADD_INSTRUCTION );
                        }
#line 2225 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 91:
#line 961 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::SUB_INSTRUCTION );
                        }
#line 2233 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 92:
#line 965 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MUL_INSTRUCTION );
                        }
#line 2241 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 93:
#line 969 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::DIV_INSTRUCTION );
                        }
#line 2249 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 94:
#line 973 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MOD_INSTRUCTION );
                        }
#line 2257 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 95:
#line 977 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::POW_INSTRUCTION );
                        }
#line 2265 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 96:
#line 981 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NEQ_INSTRUCTION );
                        }
#line 2273 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 97:
#line 985 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::EQU_INSTRUCTION );
                        }
#line 2281 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 98:
#line 989 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LTH_INSTRUCTION );
                        }
#line 2289 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 99:
#line 993 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GTH_INSTRUCTION );
                        }
#line 2297 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 100:
#line 997 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LEQ_INSTRUCTION );
                        }
#line 2305 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 101:
#line 1001 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GEQ_INSTRUCTION );
                        }
#line 2313 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 102:
#line 1005 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::OR_INSTRUCTION );
                        }
#line 2321 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 103:
#line 1009 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::XOR_INSTRUCTION );
                        }
#line 2329 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 104:
#line 1013 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::AND_INSTRUCTION );
                        }
#line 2337 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 105:
#line 1017 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2345 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 106:
#line 1021 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2353 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 107:
#line 1025 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NOT_INSTRUCTION );
                        }
#line 2361 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 108:
#line 1033 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< IdentifierPath::Ptr >(),
                                    arguments );
                        }
#line 2370 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 109:
#line 1038 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< IdentifierPath::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2378 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 110:
#line 1046 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2387 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 111:
#line 1051 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 3 ].value.as< Expression::Ptr >(),
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2395 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 112:
#line 1059 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IndirectCallExpression::Ptr >() =
                                Ast::make< IndirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2403 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 113:
#line 1067 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TypeCastingExpression::Ptr >() =
                                Ast::make< TypeCastingExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2411 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 114:
#line 1075 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetExpression::Ptr >() = Ast::make< LetExpression >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2419 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 115:
#line 1083 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalExpression::Ptr >() =
                                Ast::make< ConditionalExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Expression::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2427 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 116:
#line 1091 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseExpression::Ptr >() =
                                Ast::make< ChooseExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2435 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 117:
#line 1099 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UniversalQuantifierExpression::Ptr >() =
                                Ast::make< UniversalQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2443 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 118:
#line 1107 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExistentialQuantifierExpression::Ptr >() =
                                Ast::make< ExistentialQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2451 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 119:
#line 1119 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UndefLiteral::Ptr >();
                        }
#line 2459 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 120:
#line 1123 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2467 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 121:
#line 1127 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2475 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 122:
#line 1131 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2483 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 123:
#line 1135 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2491 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 124:
#line 1139 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2499 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 125:
#line 1143 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2507 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 126:
#line 1147 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ReferenceLiteral::Ptr >();
                        }
#line 2515 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 127:
#line 1151 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ListLiteral::Ptr >();
                        }
#line 2523 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 128:
#line 1155 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< RangeLiteral::Ptr >();
                        }
#line 2531 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 129:
#line 1159 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TupleLiteral::Ptr >();
                        }
#line 2539 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 130:
#line 1163 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< NamedTupleLiteral::Ptr >();
                        }
#line 2547 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 131:
#line 1171 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UndefLiteral::Ptr >() =
                                Ast::make< UndefLiteral >( yylhs.location );
                        }
#line 2555 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 132:
#line 1179 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
                            yylhs.value.as< ValueLiteral::Ptr >() =
                                Ast::make< ValueLiteral >( yylhs.location, value );
                        }
#line 2564 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 133:
#line 1184 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
                            yylhs.value.as< ValueLiteral::Ptr >() =
                                Ast::make< ValueLiteral >( yylhs.location, value );
                        }
#line 2573 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 134:
#line 1193 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2589 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 135:
#line 1209 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2605 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 136:
#line 1225 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2621 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 137:
#line 1241 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2637 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 138:
#line 1253 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2653 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 139:
#line 1269 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 2669 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 140:
#line 1285 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ReferenceLiteral::Ptr >() =
                                Ast::make< ReferenceLiteral >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2677 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 141:
#line 1293 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< ListLiteral::Ptr >() =
                                Ast::make< ListLiteral >( yylhs.location, expressions );
                        }
#line 2686 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 142:
#line 1298 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListLiteral::Ptr >() = Ast::make< ListLiteral >(
                                yylhs.location, yystack_[ 1 ].value.as< Expressions::Ptr >() );
                        }
#line 2694 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 143:
#line 1302 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListLiteral::Ptr >() = nullptr;
                        }
#line 2702 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 144:
#line 1310 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RangeLiteral::Ptr >() = Ast::make< RangeLiteral >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Expression::Ptr >() );
                        }
#line 2710 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 145:
#line 1317 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = yystack_[ 3 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 1 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< TupleLiteral::Ptr >() =
                                Ast::make< TupleLiteral >( yylhs.location, expressions );
                        }
#line 2720 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 146:
#line 1325 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NamedTupleLiteral::Ptr >() =
                                Ast::make< NamedTupleLiteral >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< NamedExpressions::Ptr >() );
                        }
#line 2728 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 147:
#line 1332 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto assignments = yystack_[ 2 ].value.as< NamedExpressions::Ptr >();
                            assignments->add( yystack_[ 0 ].value.as< NamedExpression::Ptr >() );
                            yylhs.value.as< NamedExpressions::Ptr >() = assignments;
                        }
#line 2738 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 148:
#line 1338 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto assignments = Ast::make< NamedExpressions >( yylhs.location );
                            assignments->add( yystack_[ 0 ].value.as< NamedExpression::Ptr >() );
                            yylhs.value.as< NamedExpressions::Ptr >() = assignments;
                        }
#line 2748 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 149:
#line 1347 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NamedExpression::Ptr >() = Ast::make< NamedExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2756 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 150:
#line 1359 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2766 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 151:
#line 1365 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2776 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 152:
#line 1375 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< BasicType::Ptr >();
                        }
#line 2784 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 153:
#line 1379 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2792 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 154:
#line 1383 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< TemplateType::Ptr >();
                        }
#line 2800 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 155:
#line 1387 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< RelationType::Ptr >();
                        }
#line 2808 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 156:
#line 1391 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< FixedSizedType::Ptr >();
                        }
#line 2816 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 157:
#line 1399 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicType::Ptr >() = Ast::make< BasicType >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2824 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 158:
#line 1407 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto identifier =
                                Ast::make< Identifier >( yylhs.location, "Tuple" );
                            auto types = yystack_[ 3 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< ComposedType::Ptr >() = Ast::make< ComposedType >(
                                yylhs.location, asIdentifierPath( identifier ), types );
                        }
#line 2835 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 159:
#line 1418 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TemplateType::Ptr >() = Ast::make< TemplateType >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 1 ].value.as< Types::Ptr >() );
                        }
#line 2843 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 160:
#line 1426 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RelationType::Ptr >() = Ast::make< RelationType >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 3 ].value.as< Types::Ptr >(),
                                yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2851 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 161:
#line 1434 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FixedSizedType::Ptr >() = Ast::make< FixedSizedType >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2859 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 162:
#line 1446 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() =
                                yystack_[ 1 ].value.as< Expressions::Ptr >();
                        }
#line 2867 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 163:
#line 1450 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() = nullptr;
                        }
#line 2875 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 164:
#line 1454 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2884 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 165:
#line 1468 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2894 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 166:
#line 1474 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2904 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 167:
#line 1484 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = yystack_[ 0 ].value.as< Types::Ptr >();
                        }
#line 2912 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 168:
#line 1488 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = Ast::make< Types >( yylhs.location );
                        }
#line 2920 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 169:
#line 1496 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                yystack_[ 2 ].value.as< NodeList< VariableDefinition >::Ptr >();
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2930 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 170:
#line 1502 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = parameters;
                        }
#line 2940 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 171:
#line 1512 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                yystack_[ 1 ].value.as< NodeList< VariableDefinition >::Ptr >();
                        }
#line 2948 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 172:
#line 1516 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() = nullptr;
                        }
#line 2956 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 173:
#line 1520 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NodeList< VariableDefinition >::Ptr >() =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                        }
#line 2964 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 174:
#line 1532 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2972 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 175:
#line 1536 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                Ast::make< UndefLiteral >( yylhs.location );
                        }
#line 2980 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 176:
#line 1544 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                yystack_[ 1 ].value.as< UpdateRules::Ptr >();
                        }
#line 2988 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 177:
#line 1548 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                Ast::make< UpdateRules >( yylhs.location );
                        }
#line 2996 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 178:
#line 1556 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers = yystack_[ 2 ].value.as< UpdateRules::Ptr >();
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< UpdateRules::Ptr >() = initializers;
                        }
#line 3006 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 179:
#line 1562 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers = Ast::make< UpdateRules >( yylhs.location );
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< UpdateRules::Ptr >() = initializers;
                        }
#line 3016 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 180:
#line 1572 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 3028 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 181:
#line 1580 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 3042 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 182:
#line 1590 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 3053 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 183:
#line 1601 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRules::Ptr >();
                        }
#line 3061 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 184:
#line 1605 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                Ast::make< UpdateRules >( yylhs.location );
                        }
#line 3069 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 185:
#line 1617 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() = Ast::make< Identifier >(
                                yylhs.location, yystack_[ 0 ].value.as< std::string >() );
                        }
#line 3077 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 186:
#line 1621 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() =
                                Ast::make< Identifier >( yylhs.location, "in" );
                        }
#line 3085 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 187:
#line 1629 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Identifiers::Ptr >(),
                                IdentifierPath::Type::ABSOLUTE );
                        }
#line 3093 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 188:
#line 1633 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
                        }
#line 3103 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 189:
#line 1643 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = yystack_[ 2 ].value.as< Identifiers::Ptr >();
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 3113 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 190:
#line 1649 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 3123 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 191:
#line 1663 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3131 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 192:
#line 1667 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto unresolvedType =
                                Ast::make< UnresolvedType >( yylhs.location );
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    unresolvedType );
                        }
#line 3140 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 193:
#line 1676 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 3148 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 194:
#line 1684 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3158 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 195:
#line 1690 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3166 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 196:
#line 1698 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 2 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3176 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 197:
#line 1704 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3184 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 198:
#line 1715 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = yystack_[ 2 ].value.as< Attributes::Ptr >();
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3194 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 199:
#line 1721 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = Ast::make< Attributes >( yylhs.location );
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3204 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 200:
#line 1730 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< BasicAttribute::Ptr >();
                        }
#line 3212 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 201:
#line 1734 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 0 ].value.as< ExpressionAttribute::Ptr >();
                        }
#line 3220 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 202:
#line 1742 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicAttribute::Ptr >() = Ast::make< BasicAttribute >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 3228 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 203:
#line 1750 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExpressionAttribute::Ptr >() =
                                Ast::make< ExpressionAttribute >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 3236 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

#line 3240 "GrammarParser.cpp"  // lalr1.cc:859
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

    const short int Parser::yypact_ninf_ = -226;

    const short int Parser::yytable_ninf_ = -167;

    const short int Parser::yypact_[] = {
        12,   -226, -4,   30,   166,  -226, -226, 1461, 2,    -226, -226, -226, -226, -226, -6,
        -4,   -4,   -4,   -4,   -4,   -4,   133,  -226, -226, -226, -226, -226, -226, -226, -226,
        7,    7,    7,    1461, 7,    -226, -226, -226, 1461, 1461, 1461, 869,  932,  -4,   18,
        -226, -226, -226, -226, -226, -226, 2218, -60,  -226, -226, -226, -226, -226, -226, -226,
        -226, -226, -226, -226, -226, -226, -226, -226, -226, -226, -226, -226, -226, -226, -226,
        -226, -226, -27,  -3,   42,   -4,   1461, -226, 10,   16,   10,   23,   17,   43,   -226,
        -4,   28,   -226, -226, 25,   74,   76,   1729, 85,   -226, -226, -226, 60,   1461, 77,
        1946, -2,   -226, 92,   83,   -226, 45,   1980, -226, -226, -5,   1461, 1461, 1461, 1461,
        1461, 1461, 1461, 1461, 1461, 1461, 1461, 1461, 1461, 1461, 1461, 1461, 1461, -4,   995,
        -226, -4,   -226, -226, 2014, 94,   113,  -226, 127,  4,    122,  129,  -28,  -5,   -5,
        239,  53,   -5,   1461, 1461, 1461, 1461, 1461, -226, 2048, 1461, -226, -226, -4,   1461,
        -226, -226, 1461, 1461, -5,   -226, -226, -226, -226, -226, -226, 102,  527,  2286, 365,
        2252, 215,  215,  263,  142,  142,  128,  128,  128,  -226, 2252, 263,  142,  142,  -27,
        145,  -226, 26,   2218, -226, 1461, 1461, 1461, -226, 146,  -4,   44,   28,   -226, -226,
        -5,   5,    1335, -5,   -226, -226, 130,  140,  -226, -4,   -226, 1487, 1873, 1611, 1805,
        1912, -27,  2082, -226, 92,   2218, 2218, 2116, 152,  -226, -5,   1461, -226, -226, -226,
        2218, 2218, -226, -226, 96,   -226, 9,    151,  -226, -4,   -226, 80,   -226, 528,  607,
        -226, 7,    7,    7,    1335, 163,  1461, 1461, 675,  743,  -226, -226, -226, -226, -226,
        -226, -226, -226, -226, -226, -226, -226, -60,  38,   132,  147,  168,  -5,   -5,   -226,
        1461, 1461, 1461, 1461, 1461, -226, -226, -226, -5,   -38,  87,   149,  -226, -4,   -226,
        1461, 121,  -226, 5,    203,  -226, 1063, 204,  1131, 174,  205,  207,  -226, 157,  132,
        147,  1767, 1839, 172,  1199, 154,  1267, 1461, 1335, -226, 217,  2218, 2218, 2218, 2218,
        2218, 185,  -5,   -226, -5,   -226, 2218, -4,   -226, -226, -226, -226, -226, -226, 1461,
        1461, 1461, 1335, 183,  -226, -226, -226, -226, 2218, -226, 201,  242,  -226, -226, 196,
        -226, 1531, 1571, 1651, 230,  806,  1461, 209,  -226, -226, 1335, 1335, 1461, 1335, 1335,
        210,  208,  212,  -226, 1398, 2150, 2184, 1461, -226, -226, 1691, -226, -226, -226, 1335,
        1335, -226, -226, 1335, -226, 214,  1335, -226, -226, -226, -226, -226
    };

    const unsigned char Parser::yydefact_[] = {
        0,   4,   0,   0,   0,   186, 185, 202, 0,   199, 200, 201, 1,   9,   0,   0,   0,   0,
        0,   0,   0,   0,   6,   8,   10,  11,  12,  13,  20,  14,  0,   0,   0,   0,   0,   131,
        133, 132, 0,   0,   0,   0,   0,   0,   0,   137, 138, 134, 135, 136, 139, 203, 74,  76,
        84,  85,  86,  75,  77,  78,  79,  80,  81,  87,  119, 120, 121, 122, 123, 124, 125, 126,
        127, 128, 129, 130, 190, 108, 187, 0,   0,   184, 21,  173, 0,   173, 0,   0,   0,   5,
        0,   192, 195, 191, 0,   0,   0,   0,   0,   107, 88,  89,  0,   0,   0,   73,  0,   148,
        190, 0,   141, 0,   73,  188, 140, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   109, 0,   3,   198, 180, 129, 183, 179, 0,
        0,   0,   0,   0,   0,   168, 0,   0,   0,   0,   0,   0,   0,   0,   83,  0,   0,   82,
        146, 0,   0,   143, 142, 0,   0,   0,   113, 152, 153, 154, 155, 156, 157, 104, 102, 103,
        106, 90,  91,  97,  98,  99,  92,  93,  94,  95,  105, 96,  100, 101, 110, 0,   164, 0,
        73,  189, 0,   0,   0,   22,  0,   0,   0,   0,   197, 170, 0,   0,   0,   0,   28,  166,
        167, 0,   7,   0,   193, 0,   0,   0,   0,   0,   0,   72,  147, 0,   149, 72,  0,   0,
        151, 168, 0,   111, 163, 162, 181, 182, 178, 172, 0,   171, 0,   0,   25,  0,   27,  0,
        23,  0,   0,   42,  0,   0,   0,   0,   0,   0,   0,   0,   0,   17,  29,  30,  31,  32,
        33,  34,  35,  36,  37,  38,  39,  0,   67,  69,  71,  0,   0,   0,   194, 0,   0,   0,
        0,   0,   112, 145, 144, 0,   0,   151, 0,   161, 0,   169, 0,   0,   15,  0,   0,   41,
        0,   0,   0,   0,   0,   0,   56,  66,  68,  70,  0,   0,   0,   0,   0,   0,   0,   0,
        165, 175, 114, 117, 116, 115, 118, 150, 0,   159, 0,   196, 16,  0,   26,  64,  62,  40,
        60,  58,  0,   0,   0,   0,   0,   59,  57,  63,  61,  65,  18,  0,   177, 158, 150, 0,
        24,  0,   0,   0,   43,  0,   0,   0,   19,  160, 0,   0,   0,   0,   0,   0,   0,   0,
        51,  0,   0,   0,   184, 52,  53,  0,   55,  44,  46,  0,   0,   45,  50,  0,   174, 0,
        0,   47,  48,  49,  176, 54
    };

    const short int Parser::yypgoto_[] = {
        -226, -226, -226, -226, 245,  119,  -226, -226, -226, -226, -226, -33,  -226, -226, 141,
        -225, -226, -226, -226, -102, -226, -226, -226, -226, -226, -226, -226, -226, -226, -39,
        -7,   8,    -226, 97,   131,  220,  -226, -226, -226, -226, -226, -226, -226, -226, -226,
        -226, -226, -226, -226, -226, -226, -226, -226, -74,  -226, -226, 120,  49,   -128, -226,
        -226, -226, -226, -226, -184, -226, 50,   -226, 202,  -226, -226, -226, 84,   -94,  46,
        14,   -226, 70,   -142, -23,  48,   -19,  211,  -226, -226
    };

    const short int Parser::yydefgoto_[] = {
        -1,  3,   4,   21,  22,  23,  24,  25,  26,  27,  28,  250, 251, 29,  305, 306, 266,
        267, 268, 378, 379, 269, 270, 271, 272, 273, 274, 275, 276, 104, 139, 52,  53,  54,
        55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,
        72,  73,  74,  75,  106, 107, 233, 170, 171, 172, 173, 174, 175, 135, 216, 217, 206,
        145, 356, 368, 141, 142, 143, 76,  77,  78,  92,  93,  94,  209, 8,   9,   10,  11
    };

    const short int Parser::yytable_[] = {
        51,  88,   208, 111, 133, 204, 248, 140, 95,   96,  237, 98,  5,   5,   5,   1,   212, 332,
        134, 333,  214, 215, 5,   5,   220, 5,   97,   5,   82,  308, 12,  99,  100, 101, 105, 112,
        5,   213,  319, 321, 169, 234, 290, 81,  162,  137, 43,  43,  7,   136, 79,  205, 249, 163,
        90,  144,  205, 80,  114, 2,   146, 83,  84,   85,  86,  87,  7,   148, 149, 153, 43,  151,
        239, 6,    6,   6,   91,  91,  91,  152, 91,   167, 247, 6,   6,   281, 6,   108, 6,   113,
        245, 150,  154, 166, 155, 197, 159, 6,   80,   246, 167, 219, -84, 157, 208, 322, 158, 295,
        80,  177,  178, 179, 180, 181, 182, 183, 184,  185, 186, 187, 188, 189, 190, 191, 192, 193,
        7,   198,  140, 176, 302, 165, 160, -2,  13,   303, 7,   14,  15,  16,  17,  18,  19,  164,
        298, -166, 221, 222, 223, 224, 225, 80,  -166, 227, 324, 325, 335, 230, 235, 201, 231, 232,
        176, 176,  236, 331, 176, 13,  202, 337, 14,   15,  16,  17,  18,  19,  80,  203, 211, 194,
        20,  5,    199, 176, 120, 121, 244, 210, 282,  128, 207, 238, 243, 240, 241, 300, -85, 35,
        36,  37,   125, 126, 127, 128, 358, 283, 359,  293, 41,  229, 42,  -86, 323, 20,  334, 43,
        339, 44,   344, 342, 277, -84, 349, 345, 176,  346, 351, 176, 355, 297, 301, 357, 365, 309,
        310, 311,  45,  46,  47,  48,  49,  50,  6,    14,  15,  16,  17,  18,  19,  176, 366, 7,
        367, 369,  316, 317, 374, 252, 382, 389, 388,  277, 277, 390, 400, 91,  89,  277, 277, 218,
        338, 277,  277, 125, 126, 127, 128, 392, 326,  327, 328, 329, 330, 228, 294, 296, 242, 147,
        395, 284,  0,   138, 207, 336, 299, 7,   176,  176, 0,   0,   0,   0,   91,  91,  91,  120,
        121, 176,  140, 278, 0,   0,   0,   0,   277,  353, 277, 0,   0,   123, 124, 125, 126, 127,
        128, 0,    0,   277, 0,   277, 0,   277, 131,  132, 0,   0,   0,   361, 362, 363, 0,   0,
        0,   279,  207, 0,   176, 0,   176, 252, 278,  278, 0,   265, 0,   277, 278, 313, 380, 381,
        278, 278,  0,   0,   0,   385, 0,   0,   0,    0,   0,   0,   380, 0,   0,   0,   0,   0,
        277, 277,  0,   277, 277, 360, 279, 279, 0,    0,   0,   0,   279, 314, 0,   0,   279, 279,
        0,   277,  277, 0,   312, 277, 116, 278, 277,  278, 0,   120, 121, 122, 0,   0,   0,   0,
        0,   0,    278, 0,   278, 0,   278, 123, 124,  125, 126, 127, 128, 0,   0,   0,   0,   0,
        280, 130,  131, 132, 0,   279, 0,   279, 0,    0,   0,   0,   278, 0,   0,   341, 0,   341,
        279, 0,    279, 0,   279, 0,   0,   0,   0,    0,   341, 0,   341, 0,   354, 0,   0,   278,
        278, 0,    278, 278, 0,   280, 280, 0,   0,    0,   279, 280, 315, 0,   0,   280, 280, 0,
        278, 278,  364, 0,   278, 0,   0,   278, 0,    0,   0,   0,   0,   0,   0,   279, 279, 0,
        279, 279,  0,   0,   0,   0,   0,   383, 384,  0,   386, 387, 0,   0,   0,   0,   279, 279,
        0,   0,    279, 0,   280, 279, 280, 304, 397,  398, 0,   0,   399, 0,   0,   401, 0,   280,
        253, 280,  254, 280, 255, 256, 5,   257, 258,  259, 0,   260, 261, 0,   0,   262, 0,   0,
        0,   0,    0,   0,   35,  36,  37,  0,   0,    280, 0,   120, 121, 122, 0,   41,  0,   42,
        0,   263,  0,   0,   43,  0,   44,  123, 124,  125, 126, 127, 128, 0,   280, 280, 0,   280,
        280, 130,  131, 132, 0,   264, 0,   45,  46,   47,  48,  49,  50,  6,   307, 280, 280, 0,
        0,   280,  0,   0,   280, 0,   0,   253, 0,    254, 0,   255, 256, 5,   257, 258, 259, 0,
        260, 261,  0,   0,   262, 0,   0,   0,   0,    0,   0,   35,  36,  37,  0,   0,   0,   0,
        0,   0,    0,   0,   41,  0,   42,  0,   263,  0,   0,   43,  0,   44,  0,   0,   0,   0,
        0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   318, 0,   264, 0,   45,  46,  47,  48,
        49,  50,   6,   253, 0,   254, 0,   255, 256,  5,   257, 258, 259, 0,   260, 261, 0,   0,
        262, 0,    0,   0,   0,   0,   0,   35,  36,   37,  0,   0,   0,   0,   0,   0,   0,   0,
        41,  0,    42,  0,   263, 0,   0,   43,  0,    44,  0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,    0,   0,   0,   0,   320, 0,   264,  0,   45,  46,  47,  48,  49,  50,  6,   253,
        0,   254,  0,   255, 256, 5,   257, 258, 259,  0,   260, 261, 0,   0,   262, 0,   0,   0,
        0,   0,    0,   35,  36,  37,  0,   0,   0,    0,   0,   0,   0,   0,   41,  0,   42,  0,
        263, 0,    0,   43,  0,   44,  0,   0,   0,    0,   0,   0,   0,   0,   0,   375, 0,   0,
        0,   0,    0,   0,   264, 0,   45,  46,  47,   48,  49,  50,  6,   30,  5,   31,  32,  0,
        0,   0,    33,  0,   0,   0,   0,   376, 0,    34,  0,   0,   35,  36,  37,  0,   0,   0,
        0,   38,   39,  40,  0,   41,  0,   42,  0,    0,   0,   0,   43,  377, 44,  0,   0,   0,
        0,   0,    0,   0,   0,   0,   102, 0,   0,    0,   0,   0,   0,   0,   0,   45,  46,  47,
        48,  49,   50,  6,   30,  5,   31,  32,  0,    0,   0,   33,  0,   0,   0,   0,   0,   0,
        34,  0,    0,   35,  36,  37,  0,   0,   0,    0,   38,  39,  40,  0,   41,  0,   42,  0,
        0,   0,    0,   43,  0,   44,  0,   0,   0,    103, 0,   0,   0,   0,   0,   109, 0,   0,
        0,   0,    0,   0,   0,   0,   45,  46,  47,   48,  49,  50,  6,   30,  5,   31,  32,  0,
        0,   0,    33,  0,   0,   0,   0,   0,   0,    34,  0,   0,   35,  36,  37,  0,   0,   0,
        0,   38,   39,  40,  0,   41,  0,   42,  110,  0,   0,   0,   43,  0,   44,  0,   0,   0,
        0,   0,    0,   0,   0,   0,   195, 0,   0,    0,   0,   0,   0,   0,   0,   45,  46,  47,
        48,  49,   50,  6,   30,  5,   31,  32,  0,    0,   0,   33,  0,   0,   0,   0,   0,   0,
        34,  0,    0,   35,  36,  37,  0,   0,   0,    0,   38,  39,  40,  0,   41,  196, 42,  0,
        0,   0,    0,   43,  0,   44,  0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,    0,   0,   0,   0,   45,  46,  47,   48,  49,  50,  6,   253, 340, 254, 0,   255,
        256, 5,    257, 258, 259, 0,   260, 261, 0,    0,   262, 0,   0,   0,   0,   0,   0,   35,
        36,  37,   0,   0,   0,   0,   0,   0,   0,    0,   41,  0,   42,  0,   263, 0,   0,   43,
        0,   44,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,
        264, 0,    45,  46,  47,  48,  49,  50,  6,    253, 0,   254, 343, 255, 256, 5,   257, 258,
        259, 0,    260, 261, 0,   0,   262, 0,   0,    0,   0,   0,   0,   35,  36,  37,  0,   0,
        0,   0,    0,   0,   0,   0,   41,  0,   42,   0,   263, 0,   0,   43,  0,   44,  0,   0,
        0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   264, 0,   45,  46,
        47,  48,   49,  50,  6,   253, 0,   254, 0,    255, 256, 5,   257, 258, 259, 0,   260, 261,
        0,   0,    262, 0,   0,   0,   0,   0,   0,    35,  36,  37,  0,   0,   0,   0,   0,   0,
        0,   0,    41,  0,   42,  0,   263, 350, 0,    43,  0,   44,  0,   0,   0,   0,   0,   0,
        0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   264, 0,   45,  46,  47,  48,  49,  50,
        6,   253,  0,   254, 0,   255, 256, 5,   257,  258, 259, 0,   260, 261, 0,   0,   262, 0,
        0,   0,    0,   0,   0,   35,  36,  37,  0,    0,   0,   0,   0,   0,   0,   0,   41,  0,
        42,  0,    263, 0,   0,   43,  0,   44,  0,    0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,    0,   0,   0,   0,   264, 352, 45,   46,  47,  48,  49,  50,  6,   253, 0,   254,
        0,   255,  256, 5,   257, 258, 259, 0,   260,  261, 0,   0,   262, 0,   0,   0,   0,   0,
        0,   35,   36,  37,  0,   0,   0,   0,   0,    0,   0,   0,   41,  0,   42,  0,   263, 0,
        0,   43,   0,   44,  0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,    264, 0,   45,  46,  47,  48,  49,   50,  6,   30,  5,   31,  32,  0,   0,   0,
        33,  0,    0,   0,   0,   376, 0,   34,  0,    0,   35,  36,  37,  0,   0,   0,   0,   38,
        39,  40,   0,   41,  0,   42,  0,   0,   391,  0,   43,  377, 44,  0,   0,   0,   0,   0,
        0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   45,  46,  47,  48,  49,
        50,  6,    30,  5,   31,  32,  0,   0,   0,    33,  0,   0,   0,   0,   0,   0,   34,  0,
        0,   35,   36,  37,  0,   0,   0,   0,   38,   39,  40,  285, 41,  0,   42,  0,   0,   0,
        0,   43,   0,   44,  0,   0,   0,   0,   115,  0,   0,   0,   116, 117, 118, 119, 0,   120,
        121, 122,  0,   0,   45,  46,  47,  48,  49,   50,  6,   0,   0,   123, 124, 125, 126, 127,
        128, 370,  0,   0,   0,   129, 0,   130, 131,  132, 0,   0,   0,   0,   0,   0,   115, 0,
        0,   0,    116, 117, 118, 119, 0,   120, 121,  122, 0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,    0,   123, 124, 125, 126, 127, 128,  371, 0,   0,   0,   129, 0,   130, 131, 132,
        0,   372,  115, 0,   0,   0,   116, 117, 118,  119, 0,   120, 121, 122, 0,   0,   0,   0,
        0,   0,    0,   0,   0,   0,   0,   123, 124,  125, 126, 127, 128, 287, 0,   0,   0,   129,
        0,   130,  131, 132, 0,   0,   115, 0,   0,    0,   116, 117, 118, 119, 0,   120, 121, 122,
        0,   0,    0,   0,   0,   0,   0,   0,   0,    0,   0,   123, 124, 125, 126, 127, 128, 373,
        0,   0,    0,   129, 0,   130, 131, 132, 0,    0,   115, 0,   0,   0,   116, 117, 118, 119,
        0,   120,  121, 122, 0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   123, 124, 125,
        126, 127,  128, 396, 0,   0,   0,   129, 0,    130, 131, 132, 0,   0,   115, 0,   0,   0,
        116, 117,  118, 119, 0,   120, 121, 122, 0,    0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   123,  124, 125, 126, 127, 128, 0,   156,  0,   0,   129, 0,   130, 131, 132, 115, 0,
        0,   0,    116, 117, 118, 119, 0,   120, 121,  122, 0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,    0,   123, 124, 125, 126, 127, 128,  0,   347, 0,   0,   129, 0,   130, 131, 132,
        115, 0,    0,   0,   116, 117, 118, 119, 0,    120, 121, 122, 0,   0,   0,   0,   0,   0,
        0,   0,    0,   0,   0,   123, 124, 125, 126,  127, 128, 0,   0,   288, 0,   129, 0,   130,
        131, 132,  115, 0,   0,   0,   116, 117, 118,  119, 0,   120, 121, 122, 0,   0,   0,   0,
        0,   0,    0,   0,   0,   0,   0,   123, 124,  125, 126, 127, 128, 348, 0,   0,   0,   129,
        115, 130,  131, 132, 116, 117, 118, 119, 0,    120, 121, 122, 0,   0,   0,   0,   0,   0,
        0,   0,    0,   0,   0,   123, 124, 125, 126,  127, 128, 0,   0,   286, 0,   129, 115, 130,
        131, 132,  116, 117, 118, 119, 0,   120, 121,  122, 0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,    0,   123, 124, 125, 126, 127, 128,  0,   0,   0,   0,   129, 0,   130, 131, 132,
        289, 115,  0,   0,   0,   116, 117, 118, 119,  0,   120, 121, 122, 0,   0,   0,   0,   0,
        0,   0,    0,   0,   0,   0,   123, 124, 125,  126, 127, 128, 0,   0,   0,   0,   129, 115,
        130, 131,  132, 116, 117, 118, 119, 0,   120,  121, 122, 0,   161, 0,   0,   0,   0,   0,
        0,   0,    0,   0,   123, 124, 125, 126, 127,  128, 0,   0,   0,   0,   129, 115, 130, 131,
        132, 116,  117, 118, 119, 0,   120, 121, 122,  0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,    123, 124, 125, 126, 127, 128, 0,    168, 0,   0,   129, 115, 130, 131, 132, 116,
        117, 118,  119, 0,   120, 121, 122, 0,   0,    0,   0,   0,   0,   0,   0,   0,   0,   0,
        123, 124,  125, 126, 127, 128, 0,   0,   0,    200, 129, 115, 130, 131, 132, 116, 117, 118,
        119, 0,    120, 121, 122, 0,   226, 0,   0,    0,   0,   0,   0,   0,   0,   0,   123, 124,
        125, 126,  127, 128, 0,   0,   0,   0,   129,  115, 130, 131, 132, 116, 117, 118, 119, 0,
        120, 121,  122, 0,   291, 0,   0,   0,   0,    0,   0,   0,   0,   0,   123, 124, 125, 126,
        127, 128,  0,   0,   0,   0,   129, 115, 130,  131, 132, 116, 117, 118, 119, 0,   120, 121,
        122, 0,    0,   0,   292, 0,   0,   0,   0,    0,   0,   0,   123, 124, 125, 126, 127, 128,
        0,   0,    0,   0,   129, 115, 130, 131, 132,  116, 117, 118, 119, 0,   120, 121, 122, 0,
        0,   0,    0,   0,   0,   393, 0,   0,   0,    0,   123, 124, 125, 126, 127, 128, 0,   0,
        0,   0,    129, 115, 130, 131, 132, 116, 117,  118, 119, 0,   120, 121, 122, 0,   0,   0,
        0,   0,    394, 0,   0,   0,   0,   0,   123,  124, 125, 126, 127, 128, 0,   0,   0,   0,
        129, 115,  130, 131, 132, 116, 117, 118, 119,  0,   120, 121, 122, 0,   0,   0,   0,   0,
        0,   0,    0,   0,   0,   0,   123, 124, 125,  126, 127, 128, 0,   0,   0,   0,   129, 0,
        130, 131,  132, 116, 117, 118, 0,   0,   120,  121, 122, 0,   0,   0,   0,   0,   0,   0,
        0,   0,    0,   0,   123, 124, 125, 126, 127,  128, 0,   0,   0,   0,   0,   0,   130, 131,
        132, 116,  0,   118, 0,   0,   120, 121, 122,  0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,    123, 124, 125, 126, 127, 128, 0,    0,   0,   0,   0,   0,   130, 131, 132
    };

    const short int Parser::yycheck_[] = {
        7,   20,  144, 42,  64,  1,   1,   81,  31,  32,  194, 34,  18,  18,  18,  3,   44,  55,
        45,  57,  148, 149, 18,  18,  152, 18,  33,  18,  14,  254, 0,   38,  39,  40,  41,  42,
        18,  65,  263, 264, 45,  169, 226, 49,  46,  3,   52,  52,  2,   52,  48,  47,  47,  55,
        47,  45,  47,  55,  44,  47,  44,  15,  16,  17,  18,  19,  20,  44,  51,  44,  52,  90,
        46,  79,  79,  79,  30,  31,  32,  51,  34,  55,  210, 79,  79,  213, 79,  41,  79,  43,
        46,  48,  18,  48,  18,  134, 103, 79,  55,  55,  55,  48,  64,  18,  246, 67,  46,  235,
        55,  116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132,
        80,  134, 202, 115, 50,  48,  55,  0,   1,   55,  90,  4,   5,   6,   7,   8,   9,   51,
        48,  58,  153, 154, 155, 156, 157, 55,  65,  160, 282, 283, 298, 164, 56,  65,  167, 168,
        148, 149, 62,  293, 152, 1,   55,  48,  4,   5,   6,   7,   8,   9,   55,  50,  49,  133,
        47,  18,  136, 169, 42,  43,  205, 65,  58,  61,  144, 46,  46,  200, 201, 44,  64,  34,
        35,  36,  58,  59,  60,  61,  332, 65,  334, 55,  45,  163, 47,  64,  44,  47,  65,  52,
        13,  54,  44,  15,  212, 64,  50,  18,  210, 18,  72,  213, 11,  236, 249, 46,  49,  256,
        257, 258, 73,  74,  75,  76,  77,  78,  79,  4,   5,   6,   7,   8,   9,   235, 49,  205,
        10,  57,  261, 262, 26,  211, 49,  51,  50,  253, 254, 51,  50,  219, 21,  259, 260, 150,
        303, 263, 264, 58,  59,  60,  61,  379, 285, 286, 287, 288, 289, 163, 235, 235, 202, 85,
        382, 219, -1,  80,  246, 300, 246, 249, 282, 283, -1,  -1,  -1,  -1,  256, 257, 258, 42,
        43,  293, 382, 212, -1,  -1,  -1,  -1,  306, 322, 308, -1,  -1,  56,  57,  58,  59,  60,
        61,  -1,  -1,  319, -1,  321, -1,  323, 69,  70,  -1,  -1,  -1,  344, 345, 346, -1,  -1,
        -1,  212, 298, -1,  332, -1,  334, 303, 253, 254, -1,  212, -1,  347, 259, 260, 365, 366,
        263, 264, -1,  -1,  -1,  372, -1,  -1,  -1,  -1,  -1,  -1,  379, -1,  -1,  -1,  -1,  -1,
        370, 371, -1,  373, 374, 337, 253, 254, -1,  -1,  -1,  -1,  259, 260, -1,  -1,  263, 264,
        -1,  389, 390, -1,  259, 393, 37,  306, 396, 308, -1,  42,  43,  44,  -1,  -1,  -1,  -1,
        -1,  -1,  319, -1,  321, -1,  323, 56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  -1,
        212, 68,  69,  70,  -1,  306, -1,  308, -1,  -1,  -1,  -1,  347, -1,  -1,  306, -1,  308,
        319, -1,  321, -1,  323, -1,  -1,  -1,  -1,  -1,  319, -1,  321, -1,  323, -1,  -1,  370,
        371, -1,  373, 374, -1,  253, 254, -1,  -1,  -1,  347, 259, 260, -1,  -1,  263, 264, -1,
        389, 390, 347, -1,  393, -1,  -1,  396, -1,  -1,  -1,  -1,  -1,  -1,  -1,  370, 371, -1,
        373, 374, -1,  -1,  -1,  -1,  -1,  370, 371, -1,  373, 374, -1,  -1,  -1,  -1,  389, 390,
        -1,  -1,  393, -1,  306, 396, 308, 1,   389, 390, -1,  -1,  393, -1,  -1,  396, -1,  319,
        12,  321, 14,  323, 16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,
        -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  347, -1,  42,  43,  44,  -1,  45,  -1,  47,
        -1,  49,  -1,  -1,  52,  -1,  54,  56,  57,  58,  59,  60,  61,  -1,  370, 371, -1,  373,
        374, 68,  69,  70,  -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  1,   389, 390, -1,
        -1,  393, -1,  -1,  396, -1,  -1,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,
        23,  24,  -1,  -1,  27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  71,  -1,  73,  74,  75,  76,
        77,  78,  79,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,
        27,  -1,  -1,  -1,  -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        45,  -1,  47,  -1,  49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  12,
        -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  24,  -1,  -1,  27,  -1,  -1,  -1,
        -1,  -1,  -1,  34,  35,  36,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  45,  -1,  47,  -1,
        49,  -1,  -1,  52,  -1,  54,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,
        -1,  -1,  -1,  -1,  71,  -1,  73,  74,  75,  76,  77,  78,  79,  17,  18,  19,  20,  -1,
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
        70,  37,  -1,  39,  -1,  -1,  42,  43,  44,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  56,  57,  58,  59,  60,  61,  -1,  -1,  -1,  -1,  -1,  -1,  68,  69,  70
    };

    const unsigned char Parser::yystos_[] = {
        0,   3,   47,  85,  86,  18,  79,  158, 165, 166, 167, 168, 0,   1,   4,   5,   6,   7,
        8,   9,   47,  87,  88,  89,  90,  91,  92,  93,  94,  97,  17,  19,  20,  24,  31,  34,
        35,  36,  41,  42,  43,  45,  47,  52,  54,  73,  74,  75,  76,  77,  78,  114, 115, 116,
        117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
        135, 136, 137, 138, 158, 159, 160, 48,  55,  49,  159, 158, 158, 158, 158, 158, 165, 88,
        47,  158, 161, 162, 163, 163, 163, 114, 163, 114, 114, 114, 1,   58,  113, 114, 139, 140,
        158, 1,   48,  113, 114, 158, 159, 33,  37,  38,  39,  40,  42,  43,  44,  56,  57,  58,
        59,  60,  61,  66,  68,  69,  70,  64,  45,  148, 52,  3,   166, 114, 137, 155, 156, 157,
        45,  152, 44,  152, 44,  51,  48,  165, 51,  44,  18,  18,  25,  18,  46,  114, 55,  46,
        46,  55,  51,  48,  48,  55,  63,  45,  142, 143, 144, 145, 146, 147, 159, 114, 114, 114,
        114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 158, 1,   46,  113,
        114, 158, 65,  65,  55,  50,  1,   47,  151, 158, 162, 164, 65,  49,  44,  65,  142, 142,
        149, 150, 89,  48,  142, 114, 114, 114, 114, 114, 46,  114, 140, 158, 114, 114, 114, 141,
        142, 56,  62,  148, 46,  46,  114, 114, 156, 46,  165, 46,  55,  142, 1,   47,  95,  96,
        158, 12,  14,  16,  17,  19,  20,  21,  23,  24,  27,  49,  71,  98,  100, 101, 102, 105,
        106, 107, 108, 109, 110, 111, 112, 115, 117, 118, 119, 142, 58,  65,  161, 18,  30,  22,
        26,  32,  148, 46,  48,  55,  141, 142, 150, 114, 48,  164, 44,  165, 50,  55,  1,   98,
        99,  1,   99,  163, 163, 163, 98,  117, 118, 119, 114, 114, 1,   99,  1,   99,  67,  44,
        142, 142, 114, 114, 114, 114, 114, 142, 55,  57,  65,  162, 114, 48,  95,  13,  13,  98,
        15,  15,  44,  18,  18,  25,  28,  50,  50,  72,  72,  114, 98,  11,  153, 46,  142, 142,
        158, 114, 114, 114, 98,  49,  49,  10,  154, 57,  18,  22,  32,  22,  26,  1,   29,  53,
        103, 104, 114, 114, 49,  98,  98,  114, 98,  98,  50,  51,  51,  50,  103, 51,  50,  157,
        22,  98,  98,  98,  50,  98
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
        142, 142, 142, 142, 143, 144, 145, 146, 147, 148, 148, 148, 149, 149, 150, 150, 151,
        151, 152, 152, 152, 153, 153, 154, 154, 155, 155, 156, 156, 156, 157, 157, 158, 158,
        159, 159, 160, 160, 161, 161, 162, 163, 163, 164, 164, 165, 165, 166, 166, 167, 168
    };

    const unsigned char Parser::yyr2_[] = {
        0, 2, 2, 4, 1, 2, 1, 4, 1, 1, 1, 1, 1, 1, 1, 6, 7, 5, 7, 8, 1, 2, 4, 1, 4, 1, 3, 1, 4, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 4, 6, 6, 6, 3, 3, 3, 2, 1, 6, 6, 8, 6, 2, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 2, 1, 2, 1, 2, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 2, 2,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 2, 3, 4, 5, 3, 6, 6, 6, 6, 6, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 5, 5, 3, 3, 1, 3,
        3, 1, 1, 1, 1, 1, 1, 1, 5, 4, 6, 3, 3, 3, 2, 3, 1, 1, 0, 3, 1, 3, 3, 0, 4, 0, 4, 0, 3, 1,
        1, 3, 3, 1, 0, 1, 1, 1, 2, 3, 1, 1, 1, 3, 4, 1, 4, 1, 3, 1, 1, 1, 1, 2
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
        0,    392,  392,  401,  407,  415,  421,  431,  437,  441,  449,  453,  457,  461,  465,
        473,  481,  489,  494,  503,  519,  527,  550,  568,  572,  578,  586,  592,  602,  614,
        618,  622,  626,  630,  634,  638,  642,  646,  650,  654,  662,  668,  678,  686,  690,
        698,  702,  710,  714,  718,  726,  732,  742,  750,  754,  762,  770,  778,  782,  786,
        791,  800,  804,  808,  813,  822,  832,  836,  840,  844,  848,  852,  864,  870,  880,
        884,  888,  892,  896,  900,  904,  908,  916,  920,  924,  928,  932,  936,  948,  952,
        956,  960,  964,  968,  972,  976,  980,  984,  988,  992,  996,  1000, 1004, 1008, 1012,
        1016, 1020, 1024, 1032, 1037, 1045, 1050, 1058, 1066, 1074, 1082, 1090, 1098, 1106, 1118,
        1122, 1126, 1130, 1134, 1138, 1142, 1146, 1150, 1154, 1158, 1162, 1170, 1178, 1183, 1192,
        1208, 1224, 1240, 1252, 1268, 1284, 1292, 1297, 1301, 1309, 1316, 1324, 1331, 1337, 1346,
        1358, 1364, 1374, 1378, 1382, 1386, 1390, 1398, 1406, 1417, 1425, 1433, 1445, 1449, 1453,
        1467, 1473, 1483, 1487, 1495, 1501, 1511, 1515, 1519, 1531, 1535, 1543, 1547, 1555, 1561,
        1571, 1579, 1589, 1600, 1604, 1616, 1620, 1628, 1632, 1642, 1648, 1662, 1666, 1675, 1683,
        1689, 1697, 1703, 1714, 1720, 1729, 1733, 1741, 1749
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
#line 4305 "GrammarParser.cpp"               // lalr1.cc:1167
#line 1755 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1168

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
