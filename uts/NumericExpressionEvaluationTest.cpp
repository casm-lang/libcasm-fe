//
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/casm-lang/libcasm-fe
//
//  This file is part of libcasm-fe.
//
//  libcasm-fe is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libcasm-fe is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libcasm-fe. If not, see <http://www.gnu.org/licenses/>.
//

#include "gtest/gtest.h"

#include <memory>

#include "../src/Ast.h"
#include "../src/execute/NumericExecutionPass.h"
#include "../src/various/location.hh"

using namespace testing;

template < typename T >
static value_t make_value( TypeType type, T v )
{
    value_t value( v );
    assert( type == value.type );
    return value;
}

static value_t make_value( TypeType type )
{
    value_t value;
    value.type = type;
    switch( type )
    {
        case TypeType::STRING:
            static std::string str = "test";
            value.value.string = &str;
            break;
        case TypeType::LIST:
        case TypeType::TUPLE:
        case TypeType::TUPLE_OR_LIST:
            static List* list = new HeadList( nullptr, value_t() );
            value.value.list = list;
            break;
        case TypeType::ENUM:
            static std::string name = "enum";
            static enum_value_t* enum_val = new enum_value_t( &name, 1 );
            value.value.enum_val = enum_val;
            break;
        case TypeType::RATIONAL:
            static rational_t* rat = new rational_t( 1, 1 );
            value.value.rat = rat;
            break;
        case TypeType::FLOATING:
            value.value.float_ = 1.0f;
            break;
        case TypeType::INTEGER:
            value.value.integer = 1;
            break;
        default:
            break;
    }
    return value;
}

static std::unique_ptr< UnaryExpression > make_unary_expression(
    UnaryExpression::Operation op )
{
    auto location = yy::location( nullptr );
    return std::unique_ptr< UnaryExpression >(
        new UnaryExpression( location, nullptr, op ) );
}

static std::unique_ptr< BinaryExpression > make_binary_expression(
    BinaryExpression::Operation op )
{
    auto location = yy::location( nullptr );
    return std::unique_ptr< BinaryExpression >(
        new BinaryExpression( location, nullptr, nullptr, op ) );
}

static value_t yields( value_t value )
{
    return value;
}

struct UnaryOpArgs
{
    value_t value;
    value_t expectedResult;
    bool checkReturnValue;
};

class Numeric_UnaryExpressionTest
    : public TestWithParam< std::tuple< UnaryExpression::Operation,
          UnaryOpArgs > >
{
};

TEST_P( Numeric_UnaryExpressionTest, testUnaryExpressionResultTypeType )
{
    const auto row = GetParam();

    const UnaryExpression::Operation op = std::get< 0 >( row );
    const auto expr = make_unary_expression( op );

    const auto values = std::get< 1 >( row );
    const auto value = values.value;
    const auto expectedResult = values.expectedResult;

    const bool checkReturnValue = values.checkReturnValue;

    libcasm_fe::NumericExecutionPass visitor{};
    const auto result = visitor.visit_expression_single( expr.get(), value );

    EXPECT_EQ( expectedResult.type, result.type );
    if( checkReturnValue )
    {
        EXPECT_EQ( expectedResult, result );
    }
}

struct BinaryOpArgs
{
    value_t lhs;
    value_t rhs;
    value_t expectedResult;
    bool checkReturnValue;
};

class Numeric_BinaryExpressionTest
    : public TestWithParam< std::tuple< BinaryExpression::Operation,
          BinaryOpArgs > >
{
};

TEST_P( Numeric_BinaryExpressionTest, testBinaryExpressionResultTypeType )
{
    const auto row = GetParam();

    const BinaryExpression::Operation op = std::get< 0 >( row );
    const auto expr = make_binary_expression( op );

    const auto values = std::get< 1 >( row );
    const auto lhs = values.lhs;
    const auto rhs = values.rhs;
    const auto expectedResult = values.expectedResult;

    const bool checkReturnValue = values.checkReturnValue;

    libcasm_fe::NumericExecutionPass visitor{};
    const auto result = visitor.visit_expression( expr.get(), lhs, rhs );

    EXPECT_EQ( expectedResult.type, result.type );
    if( checkReturnValue )
    {
        EXPECT_EQ( expectedResult, result );
    }
}

using BinaryOpArgss = std::vector< BinaryOpArgs >;
static BinaryOpArgss generateNumeric_BinaryExpressionTestCases(
    const std::vector< TypeType >& types,
    const std::function< BinaryOpArgss( TypeType ) >& testTemplate )
{
    BinaryOpArgss binOpTypeTypes;
    for( auto type : types )
    {
        const auto instantiatedTypeTypes = testTemplate( type );
        binOpTypeTypes.insert( binOpTypeTypes.cend(),
            instantiatedTypeTypes.cbegin(), instantiatedTypeTypes.cend() );
    }
    return binOpTypeTypes;
}

INSTANTIATE_TEST_CASE_P( Numeric_UnaryOperations, Numeric_UnaryExpressionTest,
    Combine( Values( UnaryExpression::Operation::NOT ),
        Values( UnaryOpArgs{ make_value( TypeType::UNDEF ),
                    yields( make_value( TypeType::UNDEF ) ) },
            UnaryOpArgs{ make_value( TypeType::BOOLEAN ),
                yields( make_value( TypeType::BOOLEAN ) ) } ) ) );

INSTANTIATE_TEST_CASE_P( Numeric_LogicalOperations_Xor,
    Numeric_BinaryExpressionTest,
    Combine( Values( BinaryExpression::Operation::XOR ),
        Values( BinaryOpArgs{ make_value( TypeType::UNDEF ),
                    make_value( TypeType::UNDEF ),
                    yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                make_value( TypeType::BOOLEAN ),
                yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN ),
                make_value( TypeType::UNDEF ),
                yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN ),
                make_value( TypeType::BOOLEAN ),
                yields( make_value( TypeType::BOOLEAN ) ) } ) ) );

INSTANTIATE_TEST_CASE_P( Numeric_LogicalOperations_And,
    Numeric_BinaryExpressionTest,
    Combine( Values( BinaryExpression::Operation::AND ),
        Values( BinaryOpArgs{ make_value( TypeType::UNDEF ),
                    make_value( TypeType::UNDEF ),
                    yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                make_value( TypeType::BOOLEAN, false ),
                yields( make_value( TypeType::BOOLEAN, false ) ), true },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                make_value( TypeType::BOOLEAN, true ),
                yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, false ),
                make_value( TypeType::UNDEF ),
                yields( make_value( TypeType::BOOLEAN, false ) ), true },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, true ),
                make_value( TypeType::UNDEF ),
                yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN ),
                make_value( TypeType::BOOLEAN ),
                yields( make_value( TypeType::BOOLEAN ) ) } ) ) );

INSTANTIATE_TEST_CASE_P( Numeric_LogicalOperations_Or,
    Numeric_BinaryExpressionTest,
    Combine( Values( BinaryExpression::Operation::OR ),
        Values( BinaryOpArgs{ make_value( TypeType::UNDEF ),
                    make_value( TypeType::UNDEF ),
                    yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                make_value( TypeType::BOOLEAN, false ),
                yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                make_value( TypeType::BOOLEAN, true ),
                yields( make_value( TypeType::BOOLEAN, true ) ), true },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, false ),
                make_value( TypeType::UNDEF ),
                yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, true ),
                make_value( TypeType::UNDEF ),
                yields( make_value( TypeType::BOOLEAN, true ) ), true },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN ),
                make_value( TypeType::BOOLEAN ),
                yields( make_value( TypeType::BOOLEAN ) ) } ) ) );

INSTANTIATE_TEST_CASE_P( Numeric_CompareOperations_LesserGreater,
    Numeric_BinaryExpressionTest,
    Combine( Values( BinaryExpression::Operation::LESSER,
                 BinaryExpression::Operation::GREATER ),
        ValuesIn( generateNumeric_BinaryExpressionTestCases(
            {
                TypeType::INTEGER, TypeType::FLOATING,
                // TypeType::RATIONAL, TODO EP not implemented yet
            },
            []( TypeType number ) -> BinaryOpArgss {
                return { BinaryOpArgs{ make_value( TypeType::UNDEF ),
                             make_value( TypeType::UNDEF ),
                             yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( TypeType::UNDEF ),
                        make_value( number ),
                        yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( number ),
                        make_value( TypeType::UNDEF ),
                        yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( number ), make_value( number ),
                        yields( make_value( TypeType::BOOLEAN ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P( Numeric_CompareOperations_LesserEqGreaterEq,
    Numeric_BinaryExpressionTest,
    Combine( Values( BinaryExpression::Operation::LESSEREQ,
                 BinaryExpression::Operation::GREATEREQ ),
        ValuesIn( generateNumeric_BinaryExpressionTestCases(
            {
                TypeType::INTEGER, TypeType::FLOATING,
                // TypeType::RATIONAL, TODO EP not implemented yet
            },
            []( TypeType number ) -> BinaryOpArgss {
                return { BinaryOpArgs{ make_value( TypeType::UNDEF ),
                             make_value( TypeType::UNDEF ),
                             yields( make_value( TypeType::BOOLEAN ) ) },
                    BinaryOpArgs{ make_value( TypeType::UNDEF ),
                        make_value( number ),
                        yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( number ),
                        make_value( TypeType::UNDEF ),
                        yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( number ), make_value( number ),
                        yields( make_value( TypeType::BOOLEAN ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P( Numeric_CompareOperations_Eq,
    Numeric_BinaryExpressionTest,
    Combine( Values( BinaryExpression::Operation::EQ ),
        ValuesIn( generateNumeric_BinaryExpressionTestCases(
            {
                TypeType::STRING, TypeType::INTEGER, TypeType::FLOATING,
                TypeType::BOOLEAN, TypeType::LIST, TypeType::TUPLE,
                TypeType::TUPLE_OR_LIST, TypeType::ENUM, TypeType::RATIONAL,
            },
            []( TypeType literal ) -> BinaryOpArgss {
                return { BinaryOpArgs{ make_value( TypeType::UNDEF ),
                             make_value( TypeType::UNDEF ),
                             yields( make_value( TypeType::BOOLEAN, true ) ),
                             true },
                    BinaryOpArgs{ make_value( TypeType::UNDEF ),
                        make_value( literal ),
                        yields( make_value( TypeType::BOOLEAN, false ) ),
                        true },
                    BinaryOpArgs{ make_value( literal ),
                        make_value( TypeType::UNDEF ),
                        yields( make_value( TypeType::BOOLEAN, false ) ),
                        true },
                    BinaryOpArgs{ make_value( literal ), make_value( literal ),
                        yields( make_value( TypeType::BOOLEAN ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P( Numeric_CompareOperations_Neq,
    Numeric_BinaryExpressionTest,
    Combine( Values( BinaryExpression::Operation::NEQ ),
        ValuesIn( generateNumeric_BinaryExpressionTestCases(
            {
                TypeType::STRING, TypeType::INTEGER, TypeType::FLOATING,
                TypeType::BOOLEAN, TypeType::LIST, TypeType::TUPLE,
                TypeType::TUPLE_OR_LIST, TypeType::ENUM, TypeType::RATIONAL,
            },
            []( TypeType literal ) -> BinaryOpArgss {
                return { BinaryOpArgs{ make_value( TypeType::UNDEF ),
                             make_value( TypeType::UNDEF ),
                             yields( make_value( TypeType::BOOLEAN, false ) ),
                             true },
                    BinaryOpArgs{ make_value( TypeType::UNDEF ),
                        make_value( literal ),
                        yields( make_value( TypeType::BOOLEAN, true ) ), true },
                    BinaryOpArgs{ make_value( literal ),
                        make_value( TypeType::UNDEF ),
                        yields( make_value( TypeType::BOOLEAN, true ) ), true },
                    BinaryOpArgs{ make_value( literal ), make_value( literal ),
                        yields( make_value( TypeType::BOOLEAN ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P( Numeric_ArithmeticOperations_Add,
    Numeric_BinaryExpressionTest,
    Combine( Values( BinaryExpression::Operation::ADD ),
        ValuesIn( generateNumeric_BinaryExpressionTestCases(
            {
                TypeType::INTEGER, TypeType::FLOATING, TypeType::RATIONAL,
                TypeType::STRING,
            },
            []( TypeType number ) -> BinaryOpArgss {
                return { BinaryOpArgs{ make_value( TypeType::UNDEF ),
                             make_value( TypeType::UNDEF ),
                             yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( TypeType::UNDEF ),
                        make_value( number ),
                        yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( number ),
                        make_value( TypeType::UNDEF ),
                        yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( number ), make_value( number ),
                        yields( make_value( number ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P( Numeric_ArithmeticOperations_SubMulDiv,
    Numeric_BinaryExpressionTest,
    Combine( Values( BinaryExpression::Operation::SUB,
                 BinaryExpression::Operation::MUL,
                 BinaryExpression::Operation::DIV ),
        ValuesIn( generateNumeric_BinaryExpressionTestCases(
            {
                TypeType::INTEGER, TypeType::FLOATING, TypeType::RATIONAL,
            },
            []( TypeType number ) -> BinaryOpArgss {
                return { BinaryOpArgs{ make_value( TypeType::UNDEF ),
                             make_value( TypeType::UNDEF ),
                             yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( TypeType::UNDEF ),
                        make_value( number ),
                        yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( number ),
                        make_value( TypeType::UNDEF ),
                        yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( number ), make_value( number ),
                        yields( make_value( number ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P( Numeric_ArithmeticOperations_Mod,
    Numeric_BinaryExpressionTest,
    Combine( Values( BinaryExpression::Operation::MOD ),
        ValuesIn( generateNumeric_BinaryExpressionTestCases(
            {
                TypeType::INTEGER, TypeType::FLOATING,
            },
            []( TypeType number ) -> BinaryOpArgss {
                return { BinaryOpArgs{ make_value( TypeType::UNDEF ),
                             make_value( TypeType::UNDEF ),
                             yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( TypeType::UNDEF ),
                        make_value( number ),
                        yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( number ),
                        make_value( TypeType::UNDEF ),
                        yields( make_value( TypeType::UNDEF ) ) },
                    BinaryOpArgs{ make_value( number ), make_value( number ),
                        yields( make_value( number ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P( Numeric_ArithmeticOperations_RatDiv,
    Numeric_BinaryExpressionTest,
    Combine( Values( BinaryExpression::Operation::RAT_DIV ),
        Values( BinaryOpArgs{ make_value( TypeType::UNDEF ),
                    make_value( TypeType::UNDEF ),
                    yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                make_value( TypeType::INTEGER ),
                yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::INTEGER ),
                make_value( TypeType::UNDEF ),
                yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::INTEGER ),
                make_value( TypeType::INTEGER ),
                yields( make_value( TypeType::RATIONAL ) ) } ) ) );
