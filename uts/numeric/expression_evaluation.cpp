//
//  Copyright (c) 2014-2017 CASM Organization
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
using namespace libcasm_fe;

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
            value.value.string = new std::string( "test" );
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
            value.value.rat = new rational_t( 1, 1 );
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
    libcasm_ir::Value::ID op )
{
    auto location = yy::location( nullptr );
    return std::unique_ptr< UnaryExpression >(
        new UnaryExpression( location, nullptr, op ) );
}

static std::unique_ptr< BinaryExpression > make_binary_expression(
    libcasm_ir::Value::ID op )
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

class numeric_una_expr_test
    : public TestWithParam< std::tuple< libcasm_ir::Value::ID, UnaryOpArgs > >
{
};

TEST_P( numeric_una_expr_test, result_type )
{
    const auto row = GetParam();

    const libcasm_ir::Value::ID op = std::get< 0 >( row );
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

class numeric_bin_expr_test
    : public TestWithParam< std::tuple< libcasm_ir::Value::ID, BinaryOpArgs > >
{
};

TEST_P( numeric_bin_expr_test, result_type )
{
    const auto row = GetParam();

    const libcasm_ir::Value::ID op = std::get< 0 >( row );
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

INSTANTIATE_TEST_CASE_P( libcasm_fe__numeric_una_op, numeric_una_expr_test,
    Combine( Values( libcasm_ir::Value::NOT_INSTRUCTION ),
        Values( UnaryOpArgs{ make_value( TypeType::UNDEF ),
                    yields( make_value( TypeType::UNDEF ) ) },
            UnaryOpArgs{ make_value( TypeType::BOOLEAN ),
                yields( make_value( TypeType::BOOLEAN ) ) } ) ) );

INSTANTIATE_TEST_CASE_P( libcasm_fe__numeric_log_op_xor,
    numeric_bin_expr_test,
    Combine( Values( libcasm_ir::Value::XOR_INSTRUCTION ),
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

INSTANTIATE_TEST_CASE_P( libcasm_fe__numeric_log_op_and,
    numeric_bin_expr_test,
    Combine( Values( libcasm_ir::Value::AND_INSTRUCTION ),
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

INSTANTIATE_TEST_CASE_P( libcasm_fe__numeric_log_op_or,
    numeric_bin_expr_test,
    Combine( Values( libcasm_ir::Value::OR_INSTRUCTION ),
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

INSTANTIATE_TEST_CASE_P( libcasm_fe__numeric_cmp_op_lth_gth,
    numeric_bin_expr_test,
    Combine( Values( libcasm_ir::Value::LTH_INSTRUCTION,
                 libcasm_ir::Value::GTH_INSTRUCTION ),
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

INSTANTIATE_TEST_CASE_P( libcasm_fe__numeric_cmp_op_leq_geq,
    numeric_bin_expr_test,
    Combine( Values( libcasm_ir::Value::LEQ_INSTRUCTION,
                 libcasm_ir::Value::GEQ_INSTRUCTION ),
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

INSTANTIATE_TEST_CASE_P( libcasm_fe__numeric_cmp_op_equ,
    numeric_bin_expr_test,
    Combine( Values( libcasm_ir::Value::EQU_INSTRUCTION ),
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

INSTANTIATE_TEST_CASE_P( libcasm_fe__numeric_cmp_op_neq,
    numeric_bin_expr_test,
    Combine( Values( libcasm_ir::Value::NEQ_INSTRUCTION ),
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

INSTANTIATE_TEST_CASE_P( libcasm_fe__numeric_arith_op_add,
    numeric_bin_expr_test,
    Combine( Values( libcasm_ir::Value::ADD_INSTRUCTION ),
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

INSTANTIATE_TEST_CASE_P( libcasm_fe__numeric_arith_op_sub_mul_div,
    numeric_bin_expr_test,
    Combine( Values( libcasm_ir::Value::SUB_INSTRUCTION,
                 libcasm_ir::Value::MUL_INSTRUCTION,
                 libcasm_ir::Value::DIV_INSTRUCTION ),
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

INSTANTIATE_TEST_CASE_P( libcasm_fe__numeric_arith_op_mod,
    numeric_bin_expr_test,
    Combine( Values( libcasm_ir::Value::MOD_INSTRUCTION ),
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
