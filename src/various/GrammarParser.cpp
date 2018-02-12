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
            case 169:  // Attribute
                value.move< Attribute::Ptr >( that.value );
                break;

            case 168:  // Attributes
                value.move< Attributes::Ptr >( that.value );
                break;

            case 170:  // BasicAttribute
                value.move< BasicAttribute::Ptr >( that.value );
                break;

            case 143:  // BasicType
                value.move< BasicType::Ptr >( that.value );
                break;

            case 108:  // BlockRule
                value.move< BlockRule::Ptr >( that.value );
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

            case 123:  // ChooseExpression
                value.move< ChooseExpression::Ptr >( that.value );
                break;

            case 106:  // ChooseRule
                value.move< ChooseRule::Ptr >( that.value );
                break;

            case 144:  // ComposedType
            case 145:  // TupleType
            case 146:  // RecordType
                value.move< ComposedType::Ptr >( that.value );
                break;

            case 122:  // ConditionalExpression
                value.move< ConditionalExpression::Ptr >( that.value );
                break;

            case 100:  // ConditionalRule
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

            case 125:  // ExistentialQuantifierExpression
                value.move< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 113:  // Term
            case 114:  // SimpleOrClaspedTerm
            case 115:  // OperatorExpression
            case 155:  // MaybeDefined
                value.move< Expression::Ptr >( that.value );
                break;

            case 171:  // ExpressionAttribute
                value.move< ExpressionAttribute::Ptr >( that.value );
                break;

            case 112:  // Terms
            case 150:  // Arguments
                value.move< Expressions::Ptr >( that.value );
                break;

            case 149:  // FixedSizedType
                value.move< FixedSizedType::Ptr >( that.value );
                break;

            case 105:  // ForallRule
                value.move< ForallRule::Ptr >( that.value );
                break;

            case 92:  // FunctionDefinition
            case 93:  // ProgramFunctionDefinition
                value.move< FunctionDefinition::Ptr >( that.value );
                break;

            case 85:  // Header
                value.move< HeaderDefinition::Ptr >( that.value );
                break;

            case 160:  // Identifier
                value.move< Identifier::Ptr >( that.value );
                break;

            case 161:  // IdentifierPath
                value.move< IdentifierPath::Ptr >( that.value );
                break;

            case 162:  // DotSeparatedIdentifiers
                value.move< Identifiers::Ptr >( that.value );
                break;

            case 119:  // IndirectCallExpression
                value.move< IndirectCallExpression::Ptr >( that.value );
                break;

            case 107:  // IterateRule
                value.move< IterateRule::Ptr >( that.value );
                break;

            case 121:  // LetExpression
                value.move< LetExpression::Ptr >( that.value );
                break;

            case 104:  // LetRule
                value.move< LetRule::Ptr >( that.value );
                break;

            case 135:  // ListLiteral
                value.move< ListLiteral::Ptr >( that.value );
                break;

            case 126:  // Literal
                value.move< Literal::Ptr >( that.value );
                break;

            case 118:  // LiteralCallExpression
                value.move< LiteralCallExpression::Ptr >( that.value );
                break;

            case 117:  // MethodCallExpression
                value.move< MethodCallExpression::Ptr >( that.value );
                break;

            case 140:  // Assignment
                value.move< NamedExpression::Ptr >( that.value );
                break;

            case 139:  // Assignments
                value.move< NamedExpressions::Ptr >( that.value );
                break;

            case 136:  // RangeLiteral
                value.move< RangeLiteral::Ptr >( that.value );
                break;

            case 138:  // RecordLiteral
                value.move< RecordLiteral::Ptr >( that.value );
                break;

            case 134:  // ReferenceLiteral
                value.move< ReferenceLiteral::Ptr >( that.value );
                break;

            case 148:  // RelationType
                value.move< RelationType::Ptr >( that.value );
                break;

            case 97:  // Rule
                value.move< Rule::Ptr >( that.value );
                break;

            case 91:  // RuleDefinition
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

            case 84:  // Specification
                value.move< Specification::Ptr >( that.value );
                break;

            case 147:  // TemplateType
                value.move< TemplateType::Ptr >( that.value );
                break;

            case 137:  // TupleLiteral
                value.move< TupleLiteral::Ptr >( that.value );
                break;

            case 120:  // TypeCastingExpression
                value.move< TypeCastingExpression::Ptr >( that.value );
                break;

            case 141:  // Types
            case 151:  // FunctionParameters
            case 152:  // MaybeFunctionParameters
                value.move< Types::Ptr >( that.value );
                break;

            case 127:  // UndefinedLiteral
                value.move< UndefLiteral::Ptr >( that.value );
                break;

            case 124:  // UniversalQuantifierExpression
                value.move< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 110:  // UpdateRule
            case 158:  // Initializer
                value.move< UpdateRule::Ptr >( that.value );
                break;

            case 156:  // MaybeInitially
            case 157:  // Initializers
            case 159:  // MaybeInitializers
                value.move< UpdateRules::Ptr >( that.value );
                break;

            case 96:  // UsingDefinition
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

            case 163:  // Variable
            case 165:  // TypedVariable
            case 166:  // AttributedVariable
            case 167:  // TypedAttributedVariable
                value.move< VariableDefinition::Ptr >( that.value );
                break;

            case 153:  // Parameters
            case 154:  // MaybeParameters
            case 164:  // TypedVariables
                value.move< VariableDefinitions::Ptr >( that.value );
                break;

            case 142:  // Type
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
            case 169:  // Attribute
                value.copy< Attribute::Ptr >( that.value );
                break;

            case 168:  // Attributes
                value.copy< Attributes::Ptr >( that.value );
                break;

            case 170:  // BasicAttribute
                value.copy< BasicAttribute::Ptr >( that.value );
                break;

            case 143:  // BasicType
                value.copy< BasicType::Ptr >( that.value );
                break;

            case 108:  // BlockRule
                value.copy< BlockRule::Ptr >( that.value );
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

            case 123:  // ChooseExpression
                value.copy< ChooseExpression::Ptr >( that.value );
                break;

            case 106:  // ChooseRule
                value.copy< ChooseRule::Ptr >( that.value );
                break;

            case 144:  // ComposedType
            case 145:  // TupleType
            case 146:  // RecordType
                value.copy< ComposedType::Ptr >( that.value );
                break;

            case 122:  // ConditionalExpression
                value.copy< ConditionalExpression::Ptr >( that.value );
                break;

            case 100:  // ConditionalRule
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

            case 125:  // ExistentialQuantifierExpression
                value.copy< ExistentialQuantifierExpression::Ptr >( that.value );
                break;

            case 113:  // Term
            case 114:  // SimpleOrClaspedTerm
            case 115:  // OperatorExpression
            case 155:  // MaybeDefined
                value.copy< Expression::Ptr >( that.value );
                break;

            case 171:  // ExpressionAttribute
                value.copy< ExpressionAttribute::Ptr >( that.value );
                break;

            case 112:  // Terms
            case 150:  // Arguments
                value.copy< Expressions::Ptr >( that.value );
                break;

            case 149:  // FixedSizedType
                value.copy< FixedSizedType::Ptr >( that.value );
                break;

            case 105:  // ForallRule
                value.copy< ForallRule::Ptr >( that.value );
                break;

            case 92:  // FunctionDefinition
            case 93:  // ProgramFunctionDefinition
                value.copy< FunctionDefinition::Ptr >( that.value );
                break;

            case 85:  // Header
                value.copy< HeaderDefinition::Ptr >( that.value );
                break;

            case 160:  // Identifier
                value.copy< Identifier::Ptr >( that.value );
                break;

            case 161:  // IdentifierPath
                value.copy< IdentifierPath::Ptr >( that.value );
                break;

            case 162:  // DotSeparatedIdentifiers
                value.copy< Identifiers::Ptr >( that.value );
                break;

            case 119:  // IndirectCallExpression
                value.copy< IndirectCallExpression::Ptr >( that.value );
                break;

            case 107:  // IterateRule
                value.copy< IterateRule::Ptr >( that.value );
                break;

            case 121:  // LetExpression
                value.copy< LetExpression::Ptr >( that.value );
                break;

            case 104:  // LetRule
                value.copy< LetRule::Ptr >( that.value );
                break;

            case 135:  // ListLiteral
                value.copy< ListLiteral::Ptr >( that.value );
                break;

            case 126:  // Literal
                value.copy< Literal::Ptr >( that.value );
                break;

            case 118:  // LiteralCallExpression
                value.copy< LiteralCallExpression::Ptr >( that.value );
                break;

            case 117:  // MethodCallExpression
                value.copy< MethodCallExpression::Ptr >( that.value );
                break;

            case 140:  // Assignment
                value.copy< NamedExpression::Ptr >( that.value );
                break;

            case 139:  // Assignments
                value.copy< NamedExpressions::Ptr >( that.value );
                break;

            case 136:  // RangeLiteral
                value.copy< RangeLiteral::Ptr >( that.value );
                break;

            case 138:  // RecordLiteral
                value.copy< RecordLiteral::Ptr >( that.value );
                break;

            case 134:  // ReferenceLiteral
                value.copy< ReferenceLiteral::Ptr >( that.value );
                break;

            case 148:  // RelationType
                value.copy< RelationType::Ptr >( that.value );
                break;

            case 97:  // Rule
                value.copy< Rule::Ptr >( that.value );
                break;

            case 91:  // RuleDefinition
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

            case 84:  // Specification
                value.copy< Specification::Ptr >( that.value );
                break;

            case 147:  // TemplateType
                value.copy< TemplateType::Ptr >( that.value );
                break;

            case 137:  // TupleLiteral
                value.copy< TupleLiteral::Ptr >( that.value );
                break;

            case 120:  // TypeCastingExpression
                value.copy< TypeCastingExpression::Ptr >( that.value );
                break;

            case 141:  // Types
            case 151:  // FunctionParameters
            case 152:  // MaybeFunctionParameters
                value.copy< Types::Ptr >( that.value );
                break;

            case 127:  // UndefinedLiteral
                value.copy< UndefLiteral::Ptr >( that.value );
                break;

            case 124:  // UniversalQuantifierExpression
                value.copy< UniversalQuantifierExpression::Ptr >( that.value );
                break;

            case 110:  // UpdateRule
            case 158:  // Initializer
                value.copy< UpdateRule::Ptr >( that.value );
                break;

            case 156:  // MaybeInitially
            case 157:  // Initializers
            case 159:  // MaybeInitializers
                value.copy< UpdateRules::Ptr >( that.value );
                break;

            case 96:  // UsingDefinition
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

            case 163:  // Variable
            case 165:  // TypedVariable
            case 166:  // AttributedVariable
            case 167:  // TypedAttributedVariable
                value.copy< VariableDefinition::Ptr >( that.value );
                break;

            case 153:  // Parameters
            case 154:  // MaybeParameters
            case 164:  // TypedVariables
                value.copy< VariableDefinitions::Ptr >( that.value );
                break;

            case 142:  // Type
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
                    case 169:  // Attribute
                        yylhs.value.build< Attribute::Ptr >();
                        break;

                    case 168:  // Attributes
                        yylhs.value.build< Attributes::Ptr >();
                        break;

                    case 170:  // BasicAttribute
                        yylhs.value.build< BasicAttribute::Ptr >();
                        break;

                    case 143:  // BasicType
                        yylhs.value.build< BasicType::Ptr >();
                        break;

                    case 108:  // BlockRule
                        yylhs.value.build< BlockRule::Ptr >();
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

                    case 123:  // ChooseExpression
                        yylhs.value.build< ChooseExpression::Ptr >();
                        break;

                    case 106:  // ChooseRule
                        yylhs.value.build< ChooseRule::Ptr >();
                        break;

                    case 144:  // ComposedType
                    case 145:  // TupleType
                    case 146:  // RecordType
                        yylhs.value.build< ComposedType::Ptr >();
                        break;

                    case 122:  // ConditionalExpression
                        yylhs.value.build< ConditionalExpression::Ptr >();
                        break;

                    case 100:  // ConditionalRule
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

                    case 125:  // ExistentialQuantifierExpression
                        yylhs.value.build< ExistentialQuantifierExpression::Ptr >();
                        break;

                    case 113:  // Term
                    case 114:  // SimpleOrClaspedTerm
                    case 115:  // OperatorExpression
                    case 155:  // MaybeDefined
                        yylhs.value.build< Expression::Ptr >();
                        break;

                    case 171:  // ExpressionAttribute
                        yylhs.value.build< ExpressionAttribute::Ptr >();
                        break;

                    case 112:  // Terms
                    case 150:  // Arguments
                        yylhs.value.build< Expressions::Ptr >();
                        break;

                    case 149:  // FixedSizedType
                        yylhs.value.build< FixedSizedType::Ptr >();
                        break;

                    case 105:  // ForallRule
                        yylhs.value.build< ForallRule::Ptr >();
                        break;

                    case 92:  // FunctionDefinition
                    case 93:  // ProgramFunctionDefinition
                        yylhs.value.build< FunctionDefinition::Ptr >();
                        break;

                    case 85:  // Header
                        yylhs.value.build< HeaderDefinition::Ptr >();
                        break;

                    case 160:  // Identifier
                        yylhs.value.build< Identifier::Ptr >();
                        break;

                    case 161:  // IdentifierPath
                        yylhs.value.build< IdentifierPath::Ptr >();
                        break;

                    case 162:  // DotSeparatedIdentifiers
                        yylhs.value.build< Identifiers::Ptr >();
                        break;

                    case 119:  // IndirectCallExpression
                        yylhs.value.build< IndirectCallExpression::Ptr >();
                        break;

                    case 107:  // IterateRule
                        yylhs.value.build< IterateRule::Ptr >();
                        break;

                    case 121:  // LetExpression
                        yylhs.value.build< LetExpression::Ptr >();
                        break;

                    case 104:  // LetRule
                        yylhs.value.build< LetRule::Ptr >();
                        break;

                    case 135:  // ListLiteral
                        yylhs.value.build< ListLiteral::Ptr >();
                        break;

                    case 126:  // Literal
                        yylhs.value.build< Literal::Ptr >();
                        break;

                    case 118:  // LiteralCallExpression
                        yylhs.value.build< LiteralCallExpression::Ptr >();
                        break;

                    case 117:  // MethodCallExpression
                        yylhs.value.build< MethodCallExpression::Ptr >();
                        break;

                    case 140:  // Assignment
                        yylhs.value.build< NamedExpression::Ptr >();
                        break;

                    case 139:  // Assignments
                        yylhs.value.build< NamedExpressions::Ptr >();
                        break;

                    case 136:  // RangeLiteral
                        yylhs.value.build< RangeLiteral::Ptr >();
                        break;

                    case 138:  // RecordLiteral
                        yylhs.value.build< RecordLiteral::Ptr >();
                        break;

                    case 134:  // ReferenceLiteral
                        yylhs.value.build< ReferenceLiteral::Ptr >();
                        break;

                    case 148:  // RelationType
                        yylhs.value.build< RelationType::Ptr >();
                        break;

                    case 97:  // Rule
                        yylhs.value.build< Rule::Ptr >();
                        break;

                    case 91:  // RuleDefinition
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

                    case 84:  // Specification
                        yylhs.value.build< Specification::Ptr >();
                        break;

                    case 147:  // TemplateType
                        yylhs.value.build< TemplateType::Ptr >();
                        break;

                    case 137:  // TupleLiteral
                        yylhs.value.build< TupleLiteral::Ptr >();
                        break;

                    case 120:  // TypeCastingExpression
                        yylhs.value.build< TypeCastingExpression::Ptr >();
                        break;

                    case 141:  // Types
                    case 151:  // FunctionParameters
                    case 152:  // MaybeFunctionParameters
                        yylhs.value.build< Types::Ptr >();
                        break;

                    case 127:  // UndefinedLiteral
                        yylhs.value.build< UndefLiteral::Ptr >();
                        break;

                    case 124:  // UniversalQuantifierExpression
                        yylhs.value.build< UniversalQuantifierExpression::Ptr >();
                        break;

                    case 110:  // UpdateRule
                    case 158:  // Initializer
                        yylhs.value.build< UpdateRule::Ptr >();
                        break;

                    case 156:  // MaybeInitially
                    case 157:  // Initializers
                    case 159:  // MaybeInitializers
                        yylhs.value.build< UpdateRules::Ptr >();
                        break;

                    case 96:  // UsingDefinition
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

                    case 163:  // Variable
                    case 165:  // TypedVariable
                    case 166:  // AttributedVariable
                    case 167:  // TypedAttributedVariable
                        yylhs.value.build< VariableDefinition::Ptr >();
                        break;

                    case 153:  // Parameters
                    case 154:  // MaybeParameters
                    case 164:  // TypedVariables
                        yylhs.value.build< VariableDefinitions::Ptr >();
                        break;

                    case 142:  // Type
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
#line 392 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            specification.setHeader(
                                yystack_[ 1 ].value.as< HeaderDefinition::Ptr >() );
                            specification.setDefinitions(
                                yystack_[ 0 ].value.as< Definitions::Ptr >() );
                        }
#line 1476 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 3:
#line 401 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                            definition->setAttributes(
                                yystack_[ 1 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< HeaderDefinition::Ptr >() = definition;
                        }
#line 1486 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 4:
#line 407 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< HeaderDefinition::Ptr >() =
                                Ast::make< HeaderDefinition >( yylhs.location, yylhs.location );
                        }
#line 1494 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 5:
#line 415 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = yystack_[ 1 ].value.as< Definitions::Ptr >();
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1504 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 6:
#line 421 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definitions = Ast::make< Definitions >( yylhs.location );
                            definitions->add( yystack_[ 0 ].value.as< Definition::Ptr >() );
                            yylhs.value.as< Definitions::Ptr >() = definitions;
                        }
#line 1514 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 7:
#line 431 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto definition = yystack_[ 0 ].value.as< Definition::Ptr >();
                            definition->setAttributes(
                                yystack_[ 1 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< Definition::Ptr >() = definition;
                        }
#line 1524 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 8:
#line 437 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< Definition::Ptr >();
                        }
#line 1532 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 9:
#line 441 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() = nullptr;
                        }
#line 1540 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 10:
#line 449 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< EnumerationDefinition::Ptr >();
                        }
#line 1548 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 11:
#line 453 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< DerivedDefinition::Ptr >();
                        }
#line 1556 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 12:
#line 457 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< RuleDefinition::Ptr >();
                        }
#line 1564 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 13:
#line 461 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< FunctionDefinition::Ptr >();
                        }
#line 1572 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 14:
#line 465 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Definition::Ptr >() =
                                yystack_[ 0 ].value.as< UsingDefinition::Ptr >();
                        }
#line 1580 "GrammarParser.cpp"  // lalr1.cc:859
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
#line 1588 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 16:
#line 481 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DerivedDefinition::Ptr >() =
                                Ast::make< DerivedDefinition >(
                                    yylhs.location,
                                    yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 4 ].value.as< VariableDefinitions::Ptr >(),
                                    yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 1596 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 17:
#line 489 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Identifier::Ptr >(),
                                yystack_[ 2 ].value.as< VariableDefinitions::Ptr >(),
                                createVoidType( yylhs.location ),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1605 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 18:
#line 494 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RuleDefinition::Ptr >() = Ast::make< RuleDefinition >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< Identifier::Ptr >(),
                                yystack_[ 4 ].value.as< VariableDefinitions::Ptr >(),
                                yystack_[ 2 ].value.as< libcasm_fe::Ast::Type::Ptr >(),
                                wrapInBlockRule( yystack_[ 0 ].value.as< Rule::Ptr >() ) );
                        }
#line 1614 "GrammarParser.cpp"  // lalr1.cc:859
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
#line 1634 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 20:
#line 519 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FunctionDefinition::Ptr >() =
                                yystack_[ 0 ]
                                    .value.as< FunctionDefinition::Ptr >();  // `init` special case
                        }
#line 1642 "GrammarParser.cpp"  // lalr1.cc:859
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
#line 1669 "GrammarParser.cpp"  // lalr1.cc:859
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
#line 1687 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 23:
#line 568 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() =
                                Ast::make< EnumeratorDefinition >(
                                    yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 1695 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 24:
#line 572 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerator = Ast::make< EnumeratorDefinition >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            enumerator->setAttributes(
                                yystack_[ 1 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = enumerator;
                        }
#line 1705 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 25:
#line 578 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< EnumeratorDefinition::Ptr >() = nullptr;
                        }
#line 1713 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 26:
#line 586 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = yystack_[ 2 ].value.as< Enumerators::Ptr >();
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1723 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 27:
#line 592 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto enumerators = Ast::make< Enumerators >( yylhs.location );
                            enumerators->add(
                                yystack_[ 0 ].value.as< EnumeratorDefinition::Ptr >() );
                            yylhs.value.as< Enumerators::Ptr >() = enumerators;
                        }
#line 1733 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 28:
#line 602 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UsingDefinition::Ptr >() = Ast::make< UsingDefinition >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 1741 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 29:
#line 614 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SkipRule::Ptr >();
                        }
#line 1749 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 30:
#line 618 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalRule::Ptr >();
                        }
#line 1757 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 31:
#line 622 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CaseRule::Ptr >();
                        }
#line 1765 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 32:
#line 626 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< LetRule::Ptr >();
                        }
#line 1773 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 33:
#line 630 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ForallRule::Ptr >();
                        }
#line 1781 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 34:
#line 634 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseRule::Ptr >();
                        }
#line 1789 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 35:
#line 638 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< IterateRule::Ptr >();
                        }
#line 1797 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 36:
#line 642 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< BlockRule::Ptr >();
                        }
#line 1805 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 37:
#line 646 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< SequenceRule::Ptr >();
                        }
#line 1813 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 38:
#line 650 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRule::Ptr >();
                        }
#line 1821 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 39:
#line 654 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Rule::Ptr >() =
                                yystack_[ 0 ].value.as< CallRule::Ptr >();
                        }
#line 1829 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 40:
#line 662 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = yystack_[ 1 ].value.as< Rules::Ptr >();
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1839 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 41:
#line 668 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto rules = Ast::make< Rules >( yylhs.location );
                            rules->add( yystack_[ 0 ].value.as< Rule::Ptr >() );
                            yylhs.value.as< Rules::Ptr >() = rules;
                        }
#line 1849 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 42:
#line 678 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SkipRule::Ptr >() =
                                Ast::make< SkipRule >( yylhs.location );
                        }
#line 1857 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 43:
#line 686 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalRule::Ptr >() = Ast::make< ConditionalRule >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1865 "GrammarParser.cpp"  // lalr1.cc:859
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
#line 1873 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 45:
#line 698 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = Ast::make< CaseRule >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Cases::Ptr >() );
                        }
#line 1881 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 46:
#line 702 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CaseRule::Ptr >() = nullptr;
                        }
#line 1889 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 47:
#line 710 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1897 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 48:
#line 714 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< DefaultCase >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1905 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 49:
#line 718 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Case::Ptr >() = Ast::make< ExpressionCase >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1913 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 50:
#line 726 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = yystack_[ 1 ].value.as< Cases::Ptr >();
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1923 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 51:
#line 732 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto cases = Ast::make< Cases >( yylhs.location );
                            cases->add( yystack_[ 0 ].value.as< Case::Ptr >() );
                            yylhs.value.as< Cases::Ptr >() = cases;
                        }
#line 1933 "GrammarParser.cpp"  // lalr1.cc:859
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
#line 1941 "GrammarParser.cpp"  // lalr1.cc:859
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
#line 1949 "GrammarParser.cpp"  // lalr1.cc:859
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
#line 1957 "GrammarParser.cpp"  // lalr1.cc:859
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
#line 1965 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 56:
#line 770 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IterateRule::Ptr >() = Ast::make< IterateRule >(
                                yylhs.location, yystack_[ 0 ].value.as< Rule::Ptr >() );
                        }
#line 1973 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 57:
#line 778 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1981 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 58:
#line 782 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = Ast::make< BlockRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 1989 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 59:
#line 786 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 1998 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 60:
#line 791 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BlockRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 2007 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 61:
#line 800 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 2015 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 62:
#line 804 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = Ast::make< SequenceRule >(
                                yylhs.location, yystack_[ 1 ].value.as< Rules::Ptr >() );
                        }
#line 2023 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 63:
#line 808 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 2032 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 64:
#line 813 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< SequenceRule::Ptr >() = nullptr;
                            yyerrok;
                        }
#line 2041 "GrammarParser.cpp"  // lalr1.cc:859
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
#line 2051 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 66:
#line 832 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >() );
                        }
#line 2059 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 67:
#line 836 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >() );
                        }
#line 2067 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 68:
#line 840 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< CallRule::Ptr >() = Ast::make< CallRule >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >() );
                        }
#line 2075 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 69:
#line 852 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto expressions = yystack_[ 2 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2085 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 70:
#line 858 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            expressions->add( yystack_[ 0 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2095 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 71:
#line 868 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2103 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 72:
#line 872 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< TypeCastingExpression::Ptr >();
                        }
#line 2111 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 73:
#line 876 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2119 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 74:
#line 880 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LetExpression::Ptr >();
                        }
#line 2127 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 75:
#line 884 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ConditionalExpression::Ptr >();
                        }
#line 2135 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 76:
#line 888 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ChooseExpression::Ptr >();
                        }
#line 2143 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 77:
#line 892 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< UniversalQuantifierExpression::Ptr >();
                        }
#line 2151 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 78:
#line 896 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< ExistentialQuantifierExpression::Ptr >();
                        }
#line 2159 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 79:
#line 904 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 2167 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 80:
#line 908 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = nullptr;
                        }
#line 2175 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 81:
#line 912 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< DirectCallExpression::Ptr >();
                        }
#line 2183 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 82:
#line 916 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< MethodCallExpression::Ptr >();
                        }
#line 2191 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 83:
#line 920 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< LiteralCallExpression::Ptr >();
                        }
#line 2199 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 84:
#line 924 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< IndirectCallExpression::Ptr >();
                        }
#line 2207 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 85:
#line 928 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Literal::Ptr >();
                        }
#line 2215 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 86:
#line 940 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 0 ].value.as< Expression::Ptr >();
                        }
#line 2223 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 87:
#line 944 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::INV_INSTRUCTION );
                        }
#line 2231 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 88:
#line 948 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::ADD_INSTRUCTION );
                        }
#line 2239 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 89:
#line 952 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::SUB_INSTRUCTION );
                        }
#line 2247 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 90:
#line 956 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MUL_INSTRUCTION );
                        }
#line 2255 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 91:
#line 960 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::DIV_INSTRUCTION );
                        }
#line 2263 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 92:
#line 964 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::MOD_INSTRUCTION );
                        }
#line 2271 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 93:
#line 968 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::POW_INSTRUCTION );
                        }
#line 2279 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 94:
#line 972 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NEQ_INSTRUCTION );
                        }
#line 2287 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 95:
#line 976 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::EQU_INSTRUCTION );
                        }
#line 2295 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 96:
#line 980 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LTH_INSTRUCTION );
                        }
#line 2303 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 97:
#line 984 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GTH_INSTRUCTION );
                        }
#line 2311 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 98:
#line 988 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::LEQ_INSTRUCTION );
                        }
#line 2319 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 99:
#line 992 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::GEQ_INSTRUCTION );
                        }
#line 2327 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 100:
#line 996 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::OR_INSTRUCTION );
                        }
#line 2335 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 101:
#line 1000 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::XOR_INSTRUCTION );
                        }
#line 2343 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 102:
#line 1004 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::AND_INSTRUCTION );
                        }
#line 2351 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 103:
#line 1008 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2359 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 104:
#line 1012 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< BinaryExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::IMP_INSTRUCTION );
                        }
#line 2367 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 105:
#line 1016 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() = Ast::make< UnaryExpression >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Expression::Ptr >(),
                                libcasm_ir::Value::NOT_INSTRUCTION );
                        }
#line 2375 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 106:
#line 1024 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< IdentifierPath::Ptr >(),
                                    arguments );
                        }
#line 2384 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 107:
#line 1029 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< DirectCallExpression::Ptr >() =
                                Ast::make< DirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< IdentifierPath::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2392 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 108:
#line 1037 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto arguments = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    arguments );
                        }
#line 2401 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 109:
#line 1042 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< MethodCallExpression::Ptr >() =
                                Ast::make< MethodCallExpression >(
                                    yylhs.location,
                                    yystack_[ 3 ].value.as< Expression::Ptr >(),
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2409 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 110:
#line 1050 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LiteralCallExpression::Ptr >() =
                                Ast::make< LiteralCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< ValueLiteral::Ptr >() );
                        }
#line 2417 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 111:
#line 1058 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IndirectCallExpression::Ptr >() =
                                Ast::make< IndirectCallExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expressions::Ptr >() );
                        }
#line 2425 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 112:
#line 1066 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TypeCastingExpression::Ptr >() =
                                Ast::make< TypeCastingExpression >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2433 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 113:
#line 1074 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< LetExpression::Ptr >() = Ast::make< LetExpression >(
                                yylhs.location,
                                yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                yystack_[ 2 ].value.as< Expression::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2441 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 114:
#line 1082 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ConditionalExpression::Ptr >() =
                                Ast::make< ConditionalExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< Expression::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2449 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 115:
#line 1090 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ChooseExpression::Ptr >() =
                                Ast::make< ChooseExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2457 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 116:
#line 1098 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UniversalQuantifierExpression::Ptr >() =
                                Ast::make< UniversalQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2465 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 117:
#line 1106 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExistentialQuantifierExpression::Ptr >() =
                                Ast::make< ExistentialQuantifierExpression >(
                                    yylhs.location,
                                    yystack_[ 4 ].value.as< VariableDefinition::Ptr >(),
                                    yystack_[ 2 ].value.as< Expression::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2473 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 118:
#line 1118 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< UndefLiteral::Ptr >();
                        }
#line 2481 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 119:
#line 1122 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2489 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 120:
#line 1126 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2497 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 121:
#line 1130 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2505 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 122:
#line 1134 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2513 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 123:
#line 1138 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2521 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 124:
#line 1142 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ValueLiteral::Ptr >();
                        }
#line 2529 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 125:
#line 1146 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ReferenceLiteral::Ptr >();
                        }
#line 2537 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 126:
#line 1150 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< ListLiteral::Ptr >();
                        }
#line 2545 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 127:
#line 1154 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< RangeLiteral::Ptr >();
                        }
#line 2553 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 128:
#line 1158 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< TupleLiteral::Ptr >();
                        }
#line 2561 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 129:
#line 1162 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Literal::Ptr >() =
                                yystack_[ 0 ].value.as< RecordLiteral::Ptr >();
                        }
#line 2569 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 130:
#line 1170 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UndefLiteral::Ptr >() =
                                Ast::make< UndefLiteral >( yylhs.location );
                        }
#line 2577 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 131:
#line 1178 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true );
                            yylhs.value.as< ValueLiteral::Ptr >() =
                                Ast::make< ValueLiteral >( yylhs.location, value );
                        }
#line 2586 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 132:
#line 1183 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto value =
                                libstdhl::Memory::get< libcasm_ir::BooleanConstant >( false );
                            yylhs.value.as< ValueLiteral::Ptr >() =
                                Ast::make< ValueLiteral >( yylhs.location, value );
                        }
#line 2595 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 133:
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
#line 2611 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 134:
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
#line 2627 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 135:
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
#line 2643 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 136:
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
#line 2659 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 137:
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
#line 2675 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 138:
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
#line 2691 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 139:
#line 1284 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ReferenceLiteral::Ptr >() =
                                Ast::make< ReferenceLiteral >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2699 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 140:
#line 1292 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< ListLiteral::Ptr >() =
                                Ast::make< ListLiteral >( yylhs.location, expressions );
                        }
#line 2708 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 141:
#line 1297 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListLiteral::Ptr >() = Ast::make< ListLiteral >(
                                yylhs.location, yystack_[ 1 ].value.as< Expressions::Ptr >() );
                        }
#line 2716 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 142:
#line 1301 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ListLiteral::Ptr >() = nullptr;
                        }
#line 2724 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 143:
#line 1309 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RangeLiteral::Ptr >() = Ast::make< RangeLiteral >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< Expression::Ptr >(),
                                yystack_[ 1 ].value.as< Expression::Ptr >() );
                        }
#line 2732 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 144:
#line 1316 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = yystack_[ 3 ].value.as< Expressions::Ptr >();
                            expressions->add( yystack_[ 1 ].value.as< Expression::Ptr >() );
                            yylhs.value.as< TupleLiteral::Ptr >() =
                                Ast::make< TupleLiteral >( yylhs.location, expressions );
                        }
#line 2742 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 145:
#line 1324 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RecordLiteral::Ptr >() = Ast::make< RecordLiteral >(
                                yylhs.location, yystack_[ 1 ].value.as< NamedExpressions::Ptr >() );
                        }
#line 2750 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 146:
#line 1331 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto assignments = yystack_[ 2 ].value.as< NamedExpressions::Ptr >();
                            assignments->add( yystack_[ 0 ].value.as< NamedExpression::Ptr >() );
                            yylhs.value.as< NamedExpressions::Ptr >() = assignments;
                        }
#line 2760 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 147:
#line 1337 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto assignments = Ast::make< NamedExpressions >( yylhs.location );
                            assignments->add( yystack_[ 0 ].value.as< NamedExpression::Ptr >() );
                            yylhs.value.as< NamedExpressions::Ptr >() = assignments;
                        }
#line 2770 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 148:
#line 1346 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< NamedExpression::Ptr >() = Ast::make< NamedExpression >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2778 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 149:
#line 1358 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2788 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 150:
#line 1364 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2798 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 151:
#line 1374 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< BasicType::Ptr >();
                        }
#line 2806 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 152:
#line 1378 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2814 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 153:
#line 1382 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< TemplateType::Ptr >();
                        }
#line 2822 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 154:
#line 1386 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< RelationType::Ptr >();
                        }
#line 2830 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 155:
#line 1390 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< libcasm_fe::Ast::Type::Ptr >() =
                                yystack_[ 0 ].value.as< FixedSizedType::Ptr >();
                        }
#line 2838 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 156:
#line 1398 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicType::Ptr >() = Ast::make< BasicType >(
                                yylhs.location, yystack_[ 0 ].value.as< IdentifierPath::Ptr >() );
                        }
#line 2846 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 157:
#line 1406 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ComposedType::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2854 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 158:
#line 1410 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ComposedType::Ptr >() =
                                yystack_[ 0 ].value.as< ComposedType::Ptr >();
                        }
#line 2862 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 159:
#line 1417 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto identifier =
                                Ast::make< Identifier >( yylhs.location, "Tuple" );
                            auto subTypes = yystack_[ 3 ].value.as< Types::Ptr >();
                            subTypes->add( yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< ComposedType::Ptr >() = Ast::make< ComposedType >(
                                yylhs.location, asIdentifierPath( identifier ), subTypes );
                        }
#line 2873 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 160:
#line 1427 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto identifier =
                                Ast::make< Identifier >( yylhs.location, "Record" );
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
#line 2893 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 161:
#line 1447 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< TemplateType::Ptr >() = Ast::make< TemplateType >(
                                yylhs.location,
                                yystack_[ 3 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 1 ].value.as< Types::Ptr >() );
                        }
#line 2901 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 162:
#line 1455 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< RelationType::Ptr >() = Ast::make< RelationType >(
                                yylhs.location,
                                yystack_[ 5 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 3 ].value.as< Types::Ptr >(),
                                yystack_[ 1 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 2909 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 163:
#line 1463 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< FixedSizedType::Ptr >() = Ast::make< FixedSizedType >(
                                yylhs.location,
                                yystack_[ 2 ].value.as< IdentifierPath::Ptr >(),
                                yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 2917 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 164:
#line 1475 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() =
                                yystack_[ 1 ].value.as< Expressions::Ptr >();
                        }
#line 2925 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 165:
#line 1479 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expressions::Ptr >() = nullptr;
                        }
#line 2933 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 166:
#line 1483 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto expressions = Ast::make< Expressions >( yylhs.location );
                            yylhs.value.as< Expressions::Ptr >() = expressions;
                        }
#line 2942 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 167:
#line 1497 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = yystack_[ 2 ].value.as< Types::Ptr >();
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2952 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 168:
#line 1503 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto types = Ast::make< Types >( yylhs.location );
                            types->add( yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                            yylhs.value.as< Types::Ptr >() = types;
                        }
#line 2962 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 169:
#line 1513 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = yystack_[ 0 ].value.as< Types::Ptr >();
                        }
#line 2970 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 170:
#line 1517 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Types::Ptr >() = Ast::make< Types >( yylhs.location );
                        }
#line 2978 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 171:
#line 1525 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters = yystack_[ 2 ].value.as< VariableDefinitions::Ptr >();
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< VariableDefinitions::Ptr >() = parameters;
                        }
#line 2988 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 172:
#line 1531 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto parameters =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                            parameters->add( yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< VariableDefinitions::Ptr >() = parameters;
                        }
#line 2998 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 173:
#line 1541 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinitions::Ptr >() =
                                yystack_[ 1 ].value.as< VariableDefinitions::Ptr >();
                        }
#line 3006 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 174:
#line 1545 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinitions::Ptr >() = nullptr;
                        }
#line 3014 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 175:
#line 1549 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinitions::Ptr >() =
                                Ast::make< NodeList< VariableDefinition > >( yylhs.location );
                        }
#line 3022 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 176:
#line 1561 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                yystack_[ 1 ].value.as< Expression::Ptr >();
                        }
#line 3030 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 177:
#line 1565 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Expression::Ptr >() =
                                Ast::make< UndefLiteral >( yylhs.location );
                        }
#line 3038 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 178:
#line 1573 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                yystack_[ 1 ].value.as< UpdateRules::Ptr >();
                        }
#line 3046 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 179:
#line 1577 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                Ast::make< UpdateRules >( yylhs.location );
                        }
#line 3054 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 180:
#line 1585 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers = yystack_[ 2 ].value.as< UpdateRules::Ptr >();
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< UpdateRules::Ptr >() = initializers;
                        }
#line 3064 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 181:
#line 1591 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto initializers = Ast::make< UpdateRules >( yylhs.location );
                            initializers->add( yystack_[ 0 ].value.as< UpdateRule::Ptr >() );
                            yylhs.value.as< UpdateRules::Ptr >() = initializers;
                        }
#line 3074 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 182:
#line 1601 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 3086 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 183:
#line 1609 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto arguments = Ast::make< Expressions >( yylhs.location );
                            arguments->add( yystack_[ 3 ].value.as< Expression::Ptr >() );

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
#line 3100 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 184:
#line 1619 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
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
#line 3111 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 185:
#line 1630 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                yystack_[ 0 ].value.as< UpdateRules::Ptr >();
                        }
#line 3119 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 186:
#line 1634 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< UpdateRules::Ptr >() =
                                Ast::make< UpdateRules >( yylhs.location );
                        }
#line 3127 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 187:
#line 1646 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() = Ast::make< Identifier >(
                                yylhs.location, yystack_[ 0 ].value.as< std::string >() );
                        }
#line 3135 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 188:
#line 1650 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Identifier::Ptr >() =
                                Ast::make< Identifier >( yylhs.location, "in" );
                        }
#line 3143 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 189:
#line 1658 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location,
                                yystack_[ 0 ].value.as< Identifiers::Ptr >(),
                                IdentifierPath::Type::ABSOLUTE );
                        }
#line 3151 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 190:
#line 1662 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< IdentifierPath::Ptr >() = Ast::make< IdentifierPath >(
                                yylhs.location, identifiers, IdentifierPath::Type::RELATIVE );
                        }
#line 3161 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 191:
#line 1672 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = yystack_[ 2 ].value.as< Identifiers::Ptr >();
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 3171 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 192:
#line 1678 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto identifiers = Ast::make< Identifiers >( yylhs.location );
                            identifiers->add( yystack_[ 0 ].value.as< Identifier::Ptr >() );
                            yylhs.value.as< Identifiers::Ptr >() = identifiers;
                        }
#line 3181 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 193:
#line 1692 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3189 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 194:
#line 1696 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            const auto unresolvedType =
                                Ast::make< UnresolvedType >( yylhs.location );
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 0 ].value.as< Identifier::Ptr >(),
                                    unresolvedType );
                        }
#line 3198 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 195:
#line 1705 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto typedVariables =
                                yystack_[ 2 ].value.as< VariableDefinitions::Ptr >();
                            typedVariables->add(
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< VariableDefinitions::Ptr >() = typedVariables;
                        }
#line 3208 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 196:
#line 1711 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto typedVariables =
                                Ast::make< VariableDefinitions >( yylhs.location );
                            typedVariables->add(
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >() );
                            yylhs.value.as< VariableDefinitions::Ptr >() = typedVariables;
                        }
#line 3218 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 197:
#line 1721 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                Ast::make< VariableDefinition >(
                                    yylhs.location,
                                    yystack_[ 2 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< libcasm_fe::Ast::Type::Ptr >() );
                        }
#line 3226 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 198:
#line 1729 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 1 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3236 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 199:
#line 1735 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3244 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 200:
#line 1743 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto variable = yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                            variable->setAttributes( yystack_[ 1 ].value.as< Attributes::Ptr >() );
                            yylhs.value.as< VariableDefinition::Ptr >() = variable;
                        }
#line 3254 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 201:
#line 1749 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< VariableDefinition::Ptr >() =
                                yystack_[ 0 ].value.as< VariableDefinition::Ptr >();
                        }
#line 3262 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 202:
#line 1760 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = yystack_[ 1 ].value.as< Attributes::Ptr >();
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3272 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 203:
#line 1766 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            auto attributes = Ast::make< Attributes >( yylhs.location );
                            attributes->add( yystack_[ 0 ].value.as< Attribute::Ptr >() );
                            yylhs.value.as< Attributes::Ptr >() = attributes;
                        }
#line 3282 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 204:
#line 1776 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 1 ].value.as< BasicAttribute::Ptr >();
                        }
#line 3290 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 205:
#line 1780 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() =
                                yystack_[ 1 ].value.as< ExpressionAttribute::Ptr >();
                        }
#line 3298 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 206:
#line 1784 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< Attribute::Ptr >() = nullptr;
                        }
#line 3306 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 207:
#line 1792 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< BasicAttribute::Ptr >() = Ast::make< BasicAttribute >(
                                yylhs.location, yystack_[ 0 ].value.as< Identifier::Ptr >() );
                        }
#line 3314 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

                        case 208:
#line 1800 "../../obj/src/GrammarParser.yy"  // lalr1.cc:859
                        {
                            yylhs.value.as< ExpressionAttribute::Ptr >() =
                                Ast::make< ExpressionAttribute >(
                                    yylhs.location,
                                    yystack_[ 1 ].value.as< Identifier::Ptr >(),
                                    yystack_[ 0 ].value.as< Expression::Ptr >() );
                        }
#line 3322 "GrammarParser.cpp"  // lalr1.cc:859
                        break;

#line 3326 "GrammarParser.cpp"  // lalr1.cc:859
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

    const short int Parser::yypact_ninf_ = -213;

    const short int Parser::yytable_ninf_ = -169;

    const short int Parser::yypact_[] = {
        7,    -213, 13,   39,   162,  20,   -213, 21,   -213, -213, 1496, 27,   40,   -213, -213,
        -6,   28,   28,   28,   28,   28,   130,  -213, -213, -213, -213, -213, -213, -213, -213,
        231,  -213, -213, -213, -2,   -2,   -2,   1496, -2,   -213, -213, -213, 1496, 1496, 1496,
        913,  975,  28,   -1,   -213, -213, -213, -213, -213, -213, 2294, -11,  -213, -213, -213,
        -213, -213, -213, -213, -213, -213, -213, -213, -213, -213, -213, -213, -213, -213, -213,
        -213, -213, -213, -213, -213, -213, -213, 23,   53,   -213, -213, 1558, -213, 61,   66,
        61,   84,   92,   -213, -213, 102,  -213, -213, 115,  -2,   138,  147,  1812, 156,  -213,
        -213, -213, 26,   1496, 105,  2022, 6,    -213, 125,  134,  -213, 48,   2056, -213, -213,
        1496, 1496, 1496, 1496, 1496, 1496, 1496, 1496, 1496, 1496, 1496, 1496, 1496, 1496, 1496,
        1496, 1496, -3,   19,   1037, -213, 28,   913,  2294, 118,  140,  -213, 135,  8,    121,
        144,  -5,   -3,   -3,   -3,   1496, -213, 1496, 1496, 1496, 1496, -213, 2090, 1496, -213,
        -213, 28,   1496, -213, -213, 1496, 1496, 788,  2328, 2357, 500,  141,  141,  425,  131,
        131,  136,  136,  136,  -213, 500,  425,  131,  131,  -3,   -213, -213, -213, -213, -213,
        -213, -213, -213, 85,   -213, 23,   150,  -213, 24,   2294, -213, 2124, 1496, 1558, -213,
        158,  49,   102,  -213, -213, -2,   -3,   10,   1372, -3,   -213, -213, 148,  142,  -213,
        1583, 1953, 1697, 1885, 1988, 23,   2158, -213, 125,  2294, 2294, 2192, 153,  -213, 102,
        155,  -213, -3,   1496, -213, -213, -213, 146,  2294, -213, -213, -213, -2,   -213, 169,
        -213, -213, 35,   -213, -2,   588,  655,  -213, -2,   -2,   -2,   1372, 1496, 1496, 722,
        789,  -213, -213, -213, -213, -213, -213, -213, -213, -213, -213, -213, -213, 154,  -41,
        160,  161,  170,  -3,   -3,   1496, 1496, 1496, 1496, 1496, -213, -213, -213, -3,   28,
        87,   43,   152,  -213, 1496, -213, 1496, -213, 10,   -213, 205,  -213, 1104, 204,  1171,
        178,  207,  208,  -213, 1849, 1919, 179,  1238, 171,  1305, 1496, 1372, -213, 216,  2294,
        2294, 2294, 2294, 2294, 187,  198,  -3,   -213, -3,   2294, 2294, -213, -213, -213, -213,
        -213, -213, 1496, 1496, 1496, 1372, 197,  -213, -213, -213, -213, 2294, -213, 199,  236,
        -213, -213, -213, 192,  1619, 1658, 1736, 224,  851,  1496, 203,  -213, -213, 1372, 1372,
        1496, 1372, 1372, 201,  206,  211,  -213, 1434, 2226, 2260, 1558, -213, -213, 1775, -213,
        -213, -213, 1372, 1372, -213, -213, 1372, -213, 214,  1372, -213, -213, -213, -213, -213
    };

    const unsigned char Parser::yydefact_[] = {
        0,   4,   0,   0,   0,   0,   203, 0,   188, 187, 207, 0,   0,   1,   9,   0,   0,   0,
        0,   0,   0,   0,   6,   8,   10,  11,  12,  13,  20,  14,  0,   3,   202, 206, 0,   0,
        0,   0,   0,   130, 132, 131, 0,   0,   0,   0,   0,   0,   0,   136, 137, 133, 134, 135,
        138, 208, 71,  73,  81,  82,  83,  84,  72,  74,  75,  76,  77,  78,  85,  118, 119, 120,
        121, 122, 123, 124, 125, 126, 127, 128, 129, 192, 106, 189, 204, 205, 186, 21,  175, 0,
        175, 0,   0,   5,   7,   194, 199, 193, 0,   0,   0,   0,   0,   0,   105, 86,  87,  0,
        0,   0,   70,  0,   147, 192, 0,   140, 0,   70,  190, 139, 0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   107, 0,   0,   182,
        128, 185, 181, 0,   0,   0,   0,   0,   0,   170, 0,   0,   198, 0,   0,   0,   0,   80,
        0,   0,   79,  145, 0,   0,   142, 141, 0,   0,   102, 100, 101, 104, 88,  89,  95,  96,
        97,  90,  91,  92,  93,  103, 94,  98,  99,  0,   112, 151, 152, 157, 158, 153, 154, 155,
        156, 110, 108, 0,   166, 0,   70,  191, 70,  0,   0,   22,  0,   0,   0,   201, 172, 0,
        0,   0,   0,   0,   28,  168, 169, 0,   197, 0,   0,   0,   0,   0,   0,   69,  146, 0,
        148, 69,  0,   0,   150, 192, 0,   196, 170, 0,   109, 165, 164, 79,  184, 180, 174, 173,
        0,   200, 0,   25,  27,  0,   23,  0,   0,   0,   42,  0,   0,   0,   0,   0,   0,   0,
        0,   17,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  0,   66,  67,  68,  0,
        0,   0,   0,   0,   0,   0,   0,   111, 144, 143, 0,   0,   0,   150, 0,   163, 0,   171,
        0,   15,  0,   24,  0,   41,  0,   0,   0,   0,   0,   0,   56,  0,   0,   0,   0,   0,
        0,   0,   0,   167, 177, 113, 116, 115, 114, 117, 149, 195, 0,   161, 0,   183, 16,  26,
        64,  62,  40,  60,  58,  0,   0,   0,   0,   0,   59,  57,  63,  61,  65,  18,  0,   179,
        159, 160, 149, 0,   0,   0,   0,   43,  0,   0,   0,   19,  162, 0,   0,   0,   0,   0,
        0,   0,   0,   51,  0,   0,   0,   186, 52,  53,  0,   55,  44,  46,  0,   0,   45,  50,
        0,   176, 0,   0,   47,  48,  49,  178, 54
    };

    const short int Parser::yypgoto_[] = {
        -213, -213, -213, -213, 232,  222,  -213, -213, -213, -213, -213, -54,  -213, -213, 202,
        -212, -213, -213, -213, -116, -213, -213, -213, -213, -213, -213, -213, -213, -213, -38,
        -10,  4,    -213, 80,   113,  -213, 189,  -213, -213, -213, -213, -213, -213, -213, -213,
        -213, 133,  -213, -213, -213, -213, -213, -213, -213, -80,  -213, -213, 103,  30,   -134,
        -213, -213, -213, -213, -213, -213, -213, -187, -213, 33,   -213, 186,  -213, -213, -213,
        60,   -107, 45,   25,   -213, 180,  -213, -119, -34,  34,   3,    0,    -213, -213
    };

    const short int Parser::yydefgoto_[] = {
        -1,  3,   4,   21,  22,  23,  24,  25,  26,  27,  28,  256, 257, 29,  311, 312, 272, 273,
        274, 381, 382, 275, 276, 277, 278, 279, 280, 281, 282, 109, 143, 56,  57,  58,  59,  60,
        61,  62,  63,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,
        79,  80,  111, 112, 237, 190, 191, 192, 193, 194, 195, 196, 197, 140, 222, 223, 211, 149,
        359, 371, 145, 146, 147, 81,  82,  83,  96,  240, 97,  98,  214, 99,  6,   11,  12
    };

    const short int Parser::yytable_[] = {
        55,  100, 101, 5,   103, 32,  144, 30,  116, 210, 1,    255, 8,   244, 7,   8,   8,   8,
        220, 221, 224, 137, -81, 31,  30,  325, 8,   102, 8,    213, 32,  8,   104, 105, 106, 110,
        117, 8,   218, 13,  87,  189, 86,  295, 2,   47,  8,    10,  47,  314, 47,  165, 138, 2,
        2,   238, 2,   322, 324, 219, 166, 88,  89,  90,  91,   92,  2,   139, 33,  246, 241, 161,
        9,   119, 84,  9,   9,   9,   170, 95,  95,  95,  254,  95,  307, 287, 9,   85,  9,   308,
        113, 9,   118, 51,  251, 169, 253, 9,   162, 32,  -168, 203, 170, 252, 141, 148, 9,   -168,
        301, 150, 172, 173, 174, 175, 176, 177, 178, 179, 180,  181, 182, 183, 184, 185, 186, 187,
        188, 152, 144, 204, -2,  14,  206, 213, 15,  16,  17,   18,  19,  20,  242, 336, 153, 337,
        95,  225, 243, 226, 227, 228, 229, 215, 154, 231, 327,  328, 157, 234, 155, 163, 235, 236,
        198, 14,  334, 158, 15,  16,  17,  18,  19,  20,  124,  125, 160, 167, 2,   198, 198, 198,
        335, 168, 207, 200, 209, 216, 205, 113, 129, 130, 131,  132, 217, 212, 208, 245, 132, 248,
        129, 130, 131, 132, 362, 250, 363, 288, 289, 298, 2,    299, 304, 233, 306, 326, 198, 32,
        338, 138, 342, 345, 259, 347, 283, -82, -84, 348, 349,  358, 352, 315, 316, 317, 360, 303,
        239, 15,  16,  17,  18,  19,  20,  198, 354, 361, 198,  368, 370, 369, 372, 377, 391, 385,
        94,  93,  341, 215, 392, 319, 320, 32,  212, 393, 258,  403, 283, 283, 395, 198, 249, 232,
        283, 199, 300, 283, 283, 302, 151, 2,   398, 156, 329,  330, 331, 332, 333, 0,   305, 0,
        0,   0,   0,   0,   0,   0,   339, 0,   340, 212, 284,  0,   0,   0,   0,   0,   309, 144,
        0,   0,   95,  95,  95,  259, 0,   198, 198, 356, 283,  0,   283, 0,   0,   0,   0,   198,
        0,   0,   283, 0,   283, 0,   283, 285, 0,   0,   0,    0,   0,   364, 365, 366, 284, 284,
        0,   0,   212, 0,   284, 0,   0,   284, 284, 0,   0,    258, 283, 0,   0,   0,   383, 384,
        0,   198, 0,   198, 0,   388, 0,   0,   0,   0,   0,    0,   383, 285, 285, 0,   0,   283,
        283, 285, 283, 283, 285, 285, 0,   0,   0,   0,   0,    0,   0,   0,   284, 0,   284, 0,
        283, 283, 0,   0,   283, 0,   284, 283, 284, 0,   284,  286, 0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   271, 0,   0,   0,   0,    285, 0,   285, 0,   0,   284, 0,
        0,   0,   0,   285, 0,   285, 0,   285, 0,   0,   0,    0,   0,   0,   0,   0,   0,   286,
        286, 0,   0,   284, 284, 286, 284, 284, 286, 286, 0,    0,   0,   285, 0,   0,   124, 125,
        318, 0,   0,   0,   284, 284, 0,   0,   284, 0,   0,    284, 127, 128, 129, 130, 131, 132,
        285, 285, 0,   285, 285, 0,   0,   135, 136, 0,   0,    0,   0,   0,   0,   286, 0,   286,
        0,   285, 285, 0,   0,   285, 0,   286, 285, 286, 344,  286, 344, 0,   0,   0,   0,   0,
        0,   0,   344, 0,   344, 0,   357, 0,   0,   0,   0,    0,   0,   0,   120, 121, 122, 286,
        0,   124, 125, 126, 0,   0,   0,   0,   0,   0,   0,    0,   367, 0,   0,   127, 128, 129,
        130, 131, 132, 0,   286, 286, 0,   286, 286, 134, 135,  136, 0,   0,   0,   0,   0,   386,
        387, 0,   389, 390, 0,   286, 286, 0,   0,   286, 0,    0,   286, 310, 0,   0,   0,   0,
        400, 401, 0,   0,   402, 0,   260, 404, 261, 0,   262,  263, 8,   264, 265, 266, 0,   267,
        0,   0,   268, 0,   0,   0,   0,   0,   0,   39,  40,   41,  0,   0,   0,   0,   0,   0,
        0,   0,   45,  0,   46,  0,   269, 0,   0,   47,  0,    48,  0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   313, 0,   270,  0,   49,  50,  51,  52,  53,  54,
        9,   260, 0,   261, 0,   262, 263, 8,   264, 265, 266,  0,   267, 0,   0,   268, 0,   0,
        0,   0,   0,   0,   39,  40,  41,  0,   0,   0,   0,    0,   0,   0,   0,   45,  0,   46,
        0,   269, 0,   0,   47,  0,   48,  0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   321, 0,   270, 0,   49,  50,  51,  52,   53,  54,  9,   260, 0,   261, 0,
        262, 263, 8,   264, 265, 266, 0,   267, 0,   0,   268,  0,   0,   0,   0,   0,   0,   39,
        40,  41,  0,   0,   0,   0,   0,   0,   0,   0,   45,   0,   46,  0,   269, 0,   0,   47,
        0,   48,  0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   323, 0,
        270, 0,   49,  50,  51,  52,  53,  54,  9,   260, 0,    261, 0,   262, 263, 8,   264, 265,
        266, 0,   267, 0,   0,   268, 0,   0,   0,   0,   0,    0,   39,  40,  41,  0,   0,   0,
        0,   124, 125, 126, 0,   45,  0,   46,  0,   269, 0,    0,   47,  0,   48,  127, 128, 129,
        130, 131, 132, 0,   0,   0,   378, 0,   0,   134, 135,  136, 0,   270, 0,   49,  50,  51,
        52,  53,  54,  9,   34,  8,   35,  36,  0,   0,   37,   0,   0,   0,   0,   379, 0,   38,
        0,   0,   39,  40,  41,  0,   0,   0,   0,   42,  43,   44,  0,   45,  0,   46,  0,   0,
        0,   0,   47,  380, 48,  0,   0,   0,   0,   0,   0,    0,   0,   0,   107, 0,   0,   0,
        0,   0,   0,   0,   0,   49,  50,  51,  52,  53,  54,   9,   34,  8,   35,  36,  0,   0,
        37,  0,   0,   0,   0,   0,   0,   38,  0,   0,   39,   40,  41,  0,   0,   0,   0,   42,
        43,  44,  0,   45,  0,   46,  0,   0,   0,   0,   47,   0,   48,  0,   0,   0,   108, 0,
        0,   0,   0,   0,   114, 0,   0,   0,   0,   0,   0,    0,   0,   49,  50,  51,  52,  53,
        54,  9,   34,  8,   35,  36,  0,   0,   37,  0,   0,    0,   0,   0,   0,   38,  0,   0,
        39,  40,  41,  0,   0,   0,   0,   42,  43,  44,  0,    45,  0,   46,  115, 0,   0,   0,
        47,  0,   48,  0,   0,   0,   0,   0,   0,   0,   0,    0,   201, 0,   0,   0,   0,   0,
        0,   0,   0,   49,  50,  51,  52,  53,  54,  9,   34,   8,   35,  36,  0,   0,   37,  0,
        0,   0,   0,   0,   0,   38,  0,   0,   39,  40,  41,   0,   0,   0,   0,   42,  43,  44,
        0,   45,  202, 46,  0,   0,   0,   0,   47,  0,   48,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    49,  50,  51,  52,  53,  54,  9,
        260, 343, 261, 0,   262, 263, 8,   264, 265, 266, 0,    267, 0,   0,   268, 0,   0,   0,
        0,   0,   0,   39,  40,  41,  0,   0,   0,   0,   0,    0,   0,   0,   45,  0,   46,  0,
        269, 0,   0,   47,  0,   48,  0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   270, 0,   49,  50,  51,  52,  53,   54,  9,   260, 0,   261, 346, 262,
        263, 8,   264, 265, 266, 0,   267, 0,   0,   268, 0,    0,   0,   0,   0,   0,   39,  40,
        41,  0,   0,   0,   0,   0,   0,   0,   0,   45,  0,    46,  0,   269, 0,   0,   47,  0,
        48,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   270,
        0,   49,  50,  51,  52,  53,  54,  9,   260, 0,   261,  0,   262, 263, 8,   264, 265, 266,
        0,   267, 0,   0,   268, 0,   0,   0,   0,   0,   0,    39,  40,  41,  0,   0,   0,   0,
        0,   0,   0,   0,   45,  0,   46,  0,   269, 353, 0,    47,  0,   48,  0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   270, 0,   49,  50,  51,  52,
        53,  54,  9,   260, 0,   261, 0,   262, 263, 8,   264,  265, 266, 0,   267, 0,   0,   268,
        0,   0,   0,   0,   0,   0,   39,  40,  41,  0,   0,    0,   0,   0,   0,   0,   0,   45,
        0,   46,  0,   269, 0,   0,   47,  0,   48,  0,   0,    0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   270, 355, 49,  50,   51,  52,  53,  54,  9,   260, 0,
        261, 0,   262, 263, 8,   264, 265, 266, 0,   267, 0,    0,   268, 0,   0,   0,   0,   0,
        0,   39,  40,  41,  0,   0,   0,   0,   0,   0,   0,    0,   45,  0,   46,  0,   269, 0,
        0,   47,  0,   48,  0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,
        0,   0,   270, 0,   49,  50,  51,  52,  53,  54,  9,    34,  8,   35,  36,  0,   0,   37,
        0,   0,   0,   0,   379, 0,   38,  0,   0,   39,  40,   41,  0,   0,   0,   0,   42,  43,
        44,  0,   45,  0,   46,  0,   0,   394, 0,   47,  380,  48,  0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   49,  50,  51,  52,  53,  54,
        9,   34,  8,   35,  36,  0,   0,   37,  0,   0,   0,    0,   0,   0,   38,  0,   0,   39,
        40,  41,  0,   0,   0,   0,   42,  43,  44,  0,   45,   0,   46,  0,   0,   0,   0,   47,
        0,   48,  0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,
        0,   0,   49,  50,  51,  52,  53,  54,  9,   34,  8,    35,  36,  0,   0,   37,  0,   0,
        0,   0,   0,   0,   38,  0,   0,   39,  40,  41,  0,    0,   0,   0,   42,  43,  44,  290,
        142, 0,   46,  0,   0,   0,   0,   47,  0,   48,  0,    0,   0,   0,   0,   0,   0,   120,
        121, 122, 123, 0,   124, 125, 126, 0,   0,   0,   49,   50,  51,  52,  53,  54,  9,   373,
        127, 128, 129, 130, 131, 132, 0,   0,   0,   0,   133,  0,   134, 135, 136, 0,   0,   120,
        121, 122, 123, 0,   124, 125, 126, 0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,
        127, 128, 129, 130, 131, 132, 374, 0,   0,   0,   133,  0,   134, 135, 136, 375, 0,   0,
        0,   0,   120, 121, 122, 123, 0,   124, 125, 126, 0,    0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   127, 128, 129, 130, 131, 132, 292, 0,    0,   0,   133, 0,   134, 135, 136,
        0,   0,   0,   0,   0,   120, 121, 122, 123, 0,   124,  125, 126, 0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   127, 128, 129, 130, 131,  132, 376, 0,   0,   0,   133, 0,
        134, 135, 136, 0,   0,   0,   0,   0,   120, 121, 122,  123, 0,   124, 125, 126, 0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   127, 128,  129, 130, 131, 132, 399, 0,   0,
        0,   133, 0,   134, 135, 136, 0,   0,   0,   0,   0,    120, 121, 122, 123, 0,   124, 125,
        126, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   127, 128, 129, 130, 131, 132,
        159, 0,   0,   0,   133, 0,   134, 135, 136, 0,   0,    0,   120, 121, 122, 123, 0,   124,
        125, 126, 0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   127, 128, 129, 130, 131,
        132, 350, 0,   0,   0,   133, 0,   134, 135, 136, 0,    0,   0,   120, 121, 122, 123, 0,
        124, 125, 126, 0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   127, 128, 129, 130,
        131, 132, 293, 0,   0,   0,   133, 0,   134, 135, 136,  0,   0,   120, 121, 122, 123, 0,
        124, 125, 126, 0,   0,   0,   0,   0,   0,   0,   0,    0,   0,   0,   127, 128, 129, 130,
        131, 132, 351, 0,   0,   0,   133, 0,   134, 135, 136,  120, 121, 122, 123, 0,   124, 125,
        126, 0,   0,   0,   0,   0,   0,   0,   0,   0,   0,    0,   127, 128, 129, 130, 131, 132,
        0,   0,   291, 0,   133, 0,   134, 135, 136, 120, 121,  122, 123, 0,   124, 125, 126, 0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   127,  128, 129, 130, 131, 132, 0,   0,
        0,   0,   133, 294, 134, 135, 136, 0,   120, 121, 122,  123, 0,   124, 125, 126, 0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   127, 128,  129, 130, 131, 132, 0,   0,   0,
        0,   133, 0,   134, 135, 136, 120, 121, 122, 123, 0,    124, 125, 126, 0,   164, 0,   0,
        0,   0,   0,   0,   0,   0,   0,   127, 128, 129, 130,  131, 132, 0,   0,   0,   0,   133,
        0,   134, 135, 136, 120, 121, 122, 123, 0,   124, 125,  126, 0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   127, 128, 129, 130, 131, 132,  0,   171, 0,   0,   133, 0,   134,
        135, 136, 120, 121, 122, 123, 0,   124, 125, 126, 0,    230, 0,   0,   0,   0,   0,   0,
        0,   0,   0,   127, 128, 129, 130, 131, 132, 0,   0,    0,   0,   133, 0,   134, 135, 136,
        120, 121, 122, 123, 0,   124, 125, 126, 0,   247, 0,    0,   0,   0,   0,   0,   0,   0,
        0,   127, 128, 129, 130, 131, 132, 0,   0,   0,   0,    133, 0,   134, 135, 136, 120, 121,
        122, 123, 0,   124, 125, 126, 0,   296, 0,   0,   0,    0,   0,   0,   0,   0,   0,   127,
        128, 129, 130, 131, 132, 0,   0,   0,   0,   133, 0,    134, 135, 136, 120, 121, 122, 123,
        0,   124, 125, 126, 0,   0,   0,   297, 0,   0,   0,    0,   0,   0,   0,   127, 128, 129,
        130, 131, 132, 0,   0,   0,   0,   133, 0,   134, 135,  136, 120, 121, 122, 123, 0,   124,
        125, 126, 0,   0,   0,   0,   0,   0,   396, 0,   0,    0,   0,   127, 128, 129, 130, 131,
        132, 0,   0,   0,   0,   133, 0,   134, 135, 136, 120,  121, 122, 123, 0,   124, 125, 126,
        0,   0,   0,   0,   0,   397, 0,   0,   0,   0,   0,    127, 128, 129, 130, 131, 132, 0,
        0,   0,   0,   133, 0,   134, 135, 136, 120, 121, 122,  123, 0,   124, 125, 126, 0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   127, 128,  129, 130, 131, 132, 0,   0,   0,
        0,   133, 0,   134, 135, 136, 120, 0,   122, 0,   0,    124, 125, 126, 0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   127, 128, 129, 130,  131, 132, 0,   0,   0,   0,   120,
        0,   134, 135, 136, 124, 125, 126, 0,   0,   0,   0,    0,   0,   0,   0,   0,   0,   0,
        127, 128, 129, 130, 131, 132, 0,   0,   0,   0,   0,    0,   134, 135, 136
    };

    const short int Parser::yycheck_[] = {
        10,  35,  36,  0,   38,  5,   86,  4,   46,  1,   3,   1,   18,  200, 1,   18,  18,  18,
        152, 153, 154, 32,  63,  3,   21,  66,  18,  37,  18,  148, 30,  18,  42,  43,  44,  45,
        46,  18,  43,  0,   15,  44,  48,  230, 46,  51,  18,  2,   51,  261, 51,  45,  63,  46,
        46,  189, 46,  269, 270, 64,  54,  16,  17,  18,  19,  20,  46,  44,  47,  45,  189, 45,
        78,  48,  47,  78,  78,  78,  54,  34,  35,  36,  216, 38,  49,  219, 78,  47,  78,  54,
        45,  78,  47,  74,  45,  47,  215, 78,  108, 99,  57,  139, 54,  54,  51,  44,  78,  64,
        242, 43,  120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135,
        136, 43,  208, 139, 0,   1,   142, 252, 4,   5,   6,   7,   8,   9,   55,  54,  50,  56,
        99,  155, 61,  157, 158, 159, 160, 148, 50,  163, 288, 289, 18,  167, 43,  54,  170, 171,
        137, 1,   298, 18,  4,   5,   6,   7,   8,   9,   41,  42,  18,  50,  46,  152, 153, 154,
        299, 47,  64,  138, 49,  64,  141, 142, 57,  58,  59,  60,  48,  148, 54,  45,  60,  207,
        57,  58,  59,  60,  336, 45,  338, 57,  64,  54,  46,  54,  64,  166, 43,  43,  189, 215,
        64,  63,  13,  15,  217, 43,  218, 63,  63,  18,  18,  11,  49,  263, 264, 265, 45,  243,
        189, 4,   5,   6,   7,   8,   9,   216, 71,  45,  219, 48,  10,  48,  56,  25,  49,  48,
        30,  21,  308, 252, 50,  267, 268, 259, 215, 50,  217, 49,  260, 261, 382, 242, 208, 166,
        266, 138, 242, 269, 270, 242, 90,  46,  385, 99,  290, 291, 292, 293, 294, -1,  252, -1,
        -1,  -1,  -1,  -1,  -1,  -1,  304, -1,  306, 252, 218, -1,  -1,  -1,  -1,  -1,  259, 385,
        -1,  -1,  263, 264, 265, 308, -1,  288, 289, 325, 312, -1,  314, -1,  -1,  -1,  -1,  298,
        -1,  -1,  322, -1,  324, -1,  326, 218, -1,  -1,  -1,  -1,  -1,  347, 348, 349, 260, 261,
        -1,  -1,  299, -1,  266, -1,  -1,  269, 270, -1,  -1,  308, 350, -1,  -1,  -1,  368, 369,
        -1,  336, -1,  338, -1,  375, -1,  -1,  -1,  -1,  -1,  -1,  382, 260, 261, -1,  -1,  373,
        374, 266, 376, 377, 269, 270, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  312, -1,  314, -1,
        392, 393, -1,  -1,  396, -1,  322, 399, 324, -1,  326, 218, -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  218, -1,  -1,  -1,  -1,  312, -1,  314, -1,  -1,  350, -1,
        -1,  -1,  -1,  322, -1,  324, -1,  326, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  260,
        261, -1,  -1,  373, 374, 266, 376, 377, 269, 270, -1,  -1,  -1,  350, -1,  -1,  41,  42,
        266, -1,  -1,  -1,  392, 393, -1,  -1,  396, -1,  -1,  399, 55,  56,  57,  58,  59,  60,
        373, 374, -1,  376, 377, -1,  -1,  68,  69,  -1,  -1,  -1,  -1,  -1,  -1,  312, -1,  314,
        -1,  392, 393, -1,  -1,  396, -1,  322, 399, 324, 312, 326, 314, -1,  -1,  -1,  -1,  -1,
        -1,  -1,  322, -1,  324, -1,  326, -1,  -1,  -1,  -1,  -1,  -1,  -1,  36,  37,  38,  350,
        -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  350, -1,  -1,  55,  56,  57,
        58,  59,  60,  -1,  373, 374, -1,  376, 377, 67,  68,  69,  -1,  -1,  -1,  -1,  -1,  373,
        374, -1,  376, 377, -1,  392, 393, -1,  -1,  396, -1,  -1,  399, 1,   -1,  -1,  -1,  -1,
        392, 393, -1,  -1,  396, -1,  12,  399, 14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,
        -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  44,  -1,  46,  -1,  48,  -1,  -1,  51,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  70,  -1,  72,  73,  74,  75,  76,  77,
        78,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  -1,  -1,  26,  -1,  -1,
        -1,  -1,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,  -1,  46,
        -1,  48,  -1,  -1,  51,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  1,   -1,  70,  -1,  72,  73,  74,  75,  76,  77,  78,  12,  -1,  14,  -1,
        16,  17,  18,  19,  20,  21,  -1,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  33,
        34,  35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,  -1,  46,  -1,  48,  -1,  -1,  51,
        -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,
        70,  -1,  72,  73,  74,  75,  76,  77,  78,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,
        21,  -1,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,
        -1,  41,  42,  43,  -1,  44,  -1,  46,  -1,  48,  -1,  -1,  51,  -1,  53,  55,  56,  57,
        58,  59,  60,  -1,  -1,  -1,  1,   -1,  -1,  67,  68,  69,  -1,  70,  -1,  72,  73,  74,
        75,  76,  77,  78,  17,  18,  19,  20,  -1,  -1,  23,  -1,  -1,  -1,  -1,  28,  -1,  30,
        -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,
        -1,  -1,  51,  52,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,  77,  78,  17,  18,  19,  20,  -1,  -1,
        23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,
        41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,  51,  -1,  53,  -1,  -1,  -1,  57,  -1,
        -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,
        77,  78,  17,  18,  19,  20,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,
        33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  47,  -1,  -1,  -1,
        51,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  1,   -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  72,  73,  74,  75,  76,  77,  78,  17,  18,  19,  20,  -1,  -1,  23,  -1,
        -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,
        -1,  44,  45,  46,  -1,  -1,  -1,  -1,  51,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,  77,  78,
        12,  13,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  -1,  -1,  26,  -1,  -1,  -1,
        -1,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,  -1,  46,  -1,
        48,  -1,  -1,  51,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  70,  -1,  72,  73,  74,  75,  76,  77,  78,  12,  -1,  14,  15,  16,
        17,  18,  19,  20,  21,  -1,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  33,  34,
        35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,  -1,  46,  -1,  48,  -1,  -1,  51,  -1,
        53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  70,
        -1,  72,  73,  74,  75,  76,  77,  78,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,
        -1,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  44,  -1,  46,  -1,  48,  49,  -1,  51,  -1,  53,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  70,  -1,  72,  73,  74,  75,
        76,  77,  78,  12,  -1,  14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  -1,  -1,  26,
        -1,  -1,  -1,  -1,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,
        -1,  46,  -1,  48,  -1,  -1,  51,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  70,  71,  72,  73,  74,  75,  76,  77,  78,  12,  -1,
        14,  -1,  16,  17,  18,  19,  20,  21,  -1,  23,  -1,  -1,  26,  -1,  -1,  -1,  -1,  -1,
        -1,  33,  34,  35,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  44,  -1,  46,  -1,  48,  -1,
        -1,  51,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  70,  -1,  72,  73,  74,  75,  76,  77,  78,  17,  18,  19,  20,  -1,  -1,  23,
        -1,  -1,  -1,  -1,  28,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,
        42,  -1,  44,  -1,  46,  -1,  -1,  49,  -1,  51,  52,  53,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  72,  73,  74,  75,  76,  77,
        78,  17,  18,  19,  20,  -1,  -1,  23,  -1,  -1,  -1,  -1,  -1,  -1,  30,  -1,  -1,  33,
        34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  -1,  44,  -1,  46,  -1,  -1,  -1,  -1,  51,
        -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  72,  73,  74,  75,  76,  77,  78,  17,  18,  19,  20,  -1,  -1,  23,  -1,  -1,
        -1,  -1,  -1,  -1,  30,  -1,  -1,  33,  34,  35,  -1,  -1,  -1,  -1,  40,  41,  42,  18,
        44,  -1,  46,  -1,  -1,  -1,  -1,  51,  -1,  53,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  36,
        37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  72,  73,  74,  75,  76,  77,  78,  18,
        55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  -1,  -1,  36,
        37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        55,  56,  57,  58,  59,  60,  22,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  31,  -1,  -1,
        -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  22,  -1,  -1,  -1,  65,  -1,  67,  68,  69,
        -1,  -1,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  22,  -1,  -1,  -1,  65,  -1,
        67,  68,  69,  -1,  -1,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  22,  -1,  -1,
        -1,  65,  -1,  67,  68,  69,  -1,  -1,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,  42,
        43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,
        24,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  -1,  -1,  -1,  36,  37,  38,  39,  -1,  41,
        42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,
        60,  24,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  -1,  -1,  -1,  36,  37,  38,  39,  -1,
        41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,
        59,  60,  25,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  -1,  -1,  36,  37,  38,  39,  -1,
        41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,
        59,  60,  27,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,
        43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,
        -1,  -1,  29,  -1,  65,  -1,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,
        -1,  -1,  65,  31,  67,  68,  69,  -1,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,
        -1,  65,  -1,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,
        -1,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  62,  -1,  -1,  65,  -1,  67,
        68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  -1,  67,  68,  69,
        36,  37,  38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  36,  37,
        38,  39,  -1,  41,  42,  43,  -1,  45,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,
        56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  36,  37,  38,  39,
        -1,  41,  42,  43,  -1,  -1,  -1,  47,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,
        58,  59,  60,  -1,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  36,  37,  38,  39,  -1,  41,
        42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  50,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,
        60,  -1,  -1,  -1,  -1,  65,  -1,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,
        -1,  -1,  -1,  -1,  -1,  49,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,
        -1,  -1,  -1,  65,  -1,  67,  68,  69,  36,  37,  38,  39,  -1,  41,  42,  43,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,
        -1,  65,  -1,  67,  68,  69,  36,  -1,  38,  -1,  -1,  41,  42,  43,  -1,  -1,  -1,  -1,
        -1,  -1,  -1,  -1,  -1,  -1,  -1,  55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  36,
        -1,  67,  68,  69,  41,  42,  43,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1,
        55,  56,  57,  58,  59,  60,  -1,  -1,  -1,  -1,  -1,  -1,  67,  68,  69
    };

    const unsigned char Parser::yystos_[] = {
        0,   3,   46,  84,  85,  168, 169, 1,   18,  78,  160, 170, 171, 0,   1,   4,   5,   6,
        7,   8,   9,   86,  87,  88,  89,  90,  91,  92,  93,  96,  168, 3,   169, 47,  17,  19,
        20,  23,  30,  33,  34,  35,  40,  41,  42,  44,  46,  51,  53,  72,  73,  74,  75,  76,
        77,  113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
        130, 131, 132, 133, 134, 135, 136, 137, 138, 160, 161, 162, 47,  47,  48,  161, 160, 160,
        160, 160, 160, 87,  88,  160, 163, 165, 166, 168, 166, 166, 113, 166, 113, 113, 113, 1,
        57,  112, 113, 139, 140, 160, 1,   47,  112, 113, 160, 161, 36,  37,  38,  39,  41,  42,
        43,  55,  56,  57,  58,  59,  60,  65,  67,  68,  69,  32,  63,  44,  150, 51,  44,  113,
        137, 157, 158, 159, 44,  154, 43,  154, 43,  50,  50,  43,  163, 18,  18,  24,  18,  45,
        113, 54,  45,  45,  54,  50,  47,  47,  54,  62,  113, 113, 113, 113, 113, 113, 113, 113,
        113, 113, 113, 113, 113, 113, 113, 113, 113, 44,  142, 143, 144, 145, 146, 147, 148, 149,
        161, 129, 160, 1,   45,  112, 113, 160, 113, 64,  54,  49,  1,   153, 160, 165, 167, 168,
        64,  48,  43,  64,  142, 142, 151, 152, 142, 113, 113, 113, 113, 113, 45,  113, 140, 160,
        113, 113, 113, 141, 142, 160, 164, 165, 55,  61,  150, 45,  45,  45,  113, 158, 45,  45,
        54,  165, 142, 1,   94,  95,  160, 168, 12,  14,  16,  17,  19,  20,  21,  23,  26,  48,
        70,  97,  99,  100, 101, 104, 105, 106, 107, 108, 109, 110, 111, 114, 116, 117, 119, 142,
        57,  64,  18,  29,  22,  25,  31,  150, 45,  47,  54,  54,  141, 142, 152, 113, 64,  167,
        43,  49,  54,  160, 1,   97,  98,  1,   98,  166, 166, 166, 97,  113, 113, 1,   98,  1,
        98,  66,  43,  142, 142, 113, 113, 113, 113, 113, 142, 165, 54,  56,  64,  113, 113, 94,
        13,  13,  97,  15,  15,  43,  18,  18,  24,  27,  49,  49,  71,  71,  113, 97,  11,  155,
        45,  45,  142, 142, 113, 113, 113, 97,  48,  48,  10,  156, 56,  18,  22,  31,  22,  25,
        1,   28,  52,  102, 103, 113, 113, 48,  97,  97,  113, 97,  97,  49,  50,  50,  49,  102,
        50,  49,  159, 22,  97,  97,  97,  49,  97
    };

    const unsigned char Parser::yyr1_[] = {
        0,   83,  84,  85,  85,  86,  86,  87,  87,  87,  88,  88,  88,  88,  88,  89,  90,  91,
        91,  92,  92,  93,  93,  94,  94,  94,  95,  95,  96,  97,  97,  97,  97,  97,  97,  97,
        97,  97,  97,  97,  98,  98,  99,  100, 100, 101, 101, 102, 102, 102, 103, 103, 104, 105,
        105, 106, 107, 108, 108, 108, 108, 109, 109, 109, 109, 110, 111, 111, 111, 112, 112, 113,
        113, 113, 113, 113, 113, 113, 113, 114, 114, 114, 114, 114, 114, 114, 115, 115, 115, 115,
        115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 116, 116,
        117, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 126, 126, 126, 126, 126, 126, 126,
        126, 126, 126, 126, 127, 128, 128, 129, 130, 131, 132, 132, 133, 134, 135, 135, 135, 136,
        137, 138, 139, 139, 140, 141, 141, 142, 142, 142, 142, 142, 143, 144, 144, 145, 146, 147,
        148, 149, 150, 150, 150, 151, 151, 152, 152, 153, 153, 154, 154, 154, 155, 155, 156, 156,
        157, 157, 158, 158, 158, 159, 159, 160, 160, 161, 161, 162, 162, 163, 163, 164, 164, 165,
        166, 166, 167, 167, 168, 168, 169, 169, 169, 170, 171
    };

    const unsigned char Parser::yyr2_[] = {
        0, 2, 2, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 6, 7, 5, 7, 8, 1, 2, 4, 1, 2, 1, 3, 1, 4, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 4, 6, 6, 6, 3, 3, 3, 2, 1, 6, 6, 8, 6, 2, 3, 3, 3,
        3, 3, 3, 3, 3, 3, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 1, 2, 2, 3, 3,
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 2, 3, 4, 3, 5, 3, 6, 6, 6, 6, 6, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 3, 3, 5, 5, 3, 3, 1, 3, 3,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 4, 6, 3, 3, 3, 2, 3, 1, 1, 0, 3, 1, 3, 3, 0, 4, 0, 4, 0,
        3, 1, 1, 5, 3, 1, 0, 1, 1, 1, 2, 3, 1, 1, 1, 3, 1, 3, 2, 1, 2, 1, 2, 1, 3, 3, 3, 1, 2
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
                                             "RecordLiteral",
                                             "Assignments",
                                             "Assignment",
                                             "Types",
                                             "Type",
                                             "BasicType",
                                             "ComposedType",
                                             "TupleType",
                                             "RecordType",
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
        0,    391,  391,  400,  406,  414,  420,  430,  436,  440,  448,  452,  456,  460,  464,
        472,  480,  488,  493,  502,  518,  526,  549,  567,  571,  577,  585,  591,  601,  613,
        617,  621,  625,  629,  633,  637,  641,  645,  649,  653,  661,  667,  677,  685,  689,
        697,  701,  709,  713,  717,  725,  731,  741,  749,  753,  761,  769,  777,  781,  785,
        790,  799,  803,  807,  812,  821,  831,  835,  839,  851,  857,  867,  871,  875,  879,
        883,  887,  891,  895,  903,  907,  911,  915,  919,  923,  927,  939,  943,  947,  951,
        955,  959,  963,  967,  971,  975,  979,  983,  987,  991,  995,  999,  1003, 1007, 1011,
        1015, 1023, 1028, 1036, 1041, 1049, 1057, 1065, 1073, 1081, 1089, 1097, 1105, 1117, 1121,
        1125, 1129, 1133, 1137, 1141, 1145, 1149, 1153, 1157, 1161, 1169, 1177, 1182, 1191, 1207,
        1223, 1239, 1251, 1267, 1283, 1291, 1296, 1300, 1308, 1315, 1323, 1330, 1336, 1345, 1357,
        1363, 1373, 1377, 1381, 1385, 1389, 1397, 1405, 1409, 1416, 1426, 1446, 1454, 1462, 1474,
        1478, 1482, 1496, 1502, 1512, 1516, 1524, 1530, 1540, 1544, 1548, 1560, 1564, 1572, 1576,
        1584, 1590, 1600, 1608, 1618, 1629, 1633, 1645, 1649, 1657, 1661, 1671, 1677, 1691, 1695,
        1704, 1710, 1720, 1728, 1734, 1742, 1748, 1759, 1765, 1775, 1779, 1783, 1791, 1799
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
#line 4405 "GrammarParser.cpp"               // lalr1.cc:1167
#line 1805 "../../obj/src/GrammarParser.yy"  // lalr1.cc:1168

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
