//
//  Copyright (C) 2014-2023 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "gtest/gtest.h"

#include <memory>

#include "../src/AST.h"
#include "../src/Symbolic.h"
#include "../src/execute/SymbolicExecutionPass.h"
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
        case TypeType::SYMBOL:
            static symbol_t* sym = new symbol_t( 1 );
            value.value.sym = sym;
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

static std::unique_ptr< UnaryExpression > make_unary_expression( libcasm_ir::Value::ID op )
{
    auto location = yy::location( nullptr );
    return std::unique_ptr< UnaryExpression >( new UnaryExpression( location, nullptr, op ) );
}

static std::unique_ptr< BinaryExpression > make_binary_expression( libcasm_ir::Value::ID op )
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

class symbolic_una_expr_test
: public TestWithParam< std::tuple< libcasm_ir::Value::ID, UnaryOpArgs > >
{
};

TEST_P( symbolic_una_expr_test, testUnaryExpressionResultType )
{
    const auto row = GetParam();

    const libcasm_ir::Value::ID op = std::get< 0 >( row );
    const auto expr = make_unary_expression( op );

    const auto values = std::get< 1 >( row );
    const auto value = values.value;
    const auto expectedResult = values.expectedResult;

    const bool checkReturnValue = values.checkReturnValue;

    libcasm_fe::SymbolicExecutionPass visitor{};
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

class symbolic_bin_expr_test
: public TestWithParam< std::tuple< libcasm_ir::Value::ID, BinaryOpArgs > >
{
};

TEST_P( symbolic_bin_expr_test, result_type )
{
    const auto row = GetParam();

    const libcasm_ir::Value::ID op = std::get< 0 >( row );
    const auto expr = make_binary_expression( op );

    const auto values = std::get< 1 >( row );
    const auto lhs = values.lhs;
    const auto rhs = values.rhs;
    const auto expectedResult = values.expectedResult;

    const bool checkReturnValue = values.checkReturnValue;

    libcasm_fe::SymbolicExecutionPass visitor{};
    const auto result = visitor.visit_expression( expr.get(), lhs, rhs );

    EXPECT_EQ( expectedResult.type, result.type );
    if( checkReturnValue )
    {
        EXPECT_EQ( expectedResult, result );
    }
}

using BinaryOpArgss = std::vector< BinaryOpArgs >;
static BinaryOpArgss generateSymbolic_BinaryExpressionTestCases(
    const std::vector< TypeType >& types,
    const std::function< BinaryOpArgss( TypeType ) >& testTemplate )
{
    BinaryOpArgss binOpTypes;
    for( auto type : types )
    {
        const auto instantiatedTypes = testTemplate( type );
        binOpTypes.insert(
            binOpTypes.cend(), instantiatedTypes.cbegin(), instantiatedTypes.cend() );
    }
    return binOpTypes;
}

INSTANTIATE_TEST_CASE_P(
    libcasm_fe__symbolic_una_op,
    symbolic_una_expr_test,
    Combine(
        Values( libcasm_ir::Value::NOT_INSTRUCTION ),
        Values(
            UnaryOpArgs{ make_value( TypeType::UNDEF ), yields( make_value( TypeType::UNDEF ) ) },
            UnaryOpArgs{ make_value( TypeType::SYMBOL ), yields( make_value( TypeType::SYMBOL ) ) },
            UnaryOpArgs{ make_value( TypeType::BOOLEAN ),
                         yields( make_value( TypeType::BOOLEAN ) ) } ) ) );

INSTANTIATE_TEST_CASE_P(
    libcasm_fe__symbolic_log_op_xor,
    symbolic_bin_expr_test,
    Combine(
        Values( libcasm_ir::Value::XOR_INSTRUCTION ),
        Values(
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                          make_value( TypeType::UNDEF ),
                          yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                          make_value( TypeType::BOOLEAN ),
                          yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN ),
                          make_value( TypeType::UNDEF ),
                          yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                          make_value( TypeType::UNDEF ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                          make_value( TypeType::SYMBOL ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                          make_value( TypeType::SYMBOL ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                          make_value( TypeType::BOOLEAN ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN ),
                          make_value( TypeType::SYMBOL ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN ),
                          make_value( TypeType::BOOLEAN ),
                          yields( make_value( TypeType::BOOLEAN ) ) } ) ) );

INSTANTIATE_TEST_CASE_P(
    libcasm_fe__symbolic_log_op_and,
    symbolic_bin_expr_test,
    Combine(
        Values( libcasm_ir::Value::AND_INSTRUCTION ),
        Values(
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                          make_value( TypeType::UNDEF ),
                          yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                          make_value( TypeType::BOOLEAN, false ),
                          yields( make_value( TypeType::BOOLEAN, false ) ),
                          true },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                          make_value( TypeType::BOOLEAN, true ),
                          yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, false ),
                          make_value( TypeType::UNDEF ),
                          yields( make_value( TypeType::BOOLEAN, false ) ),
                          true },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, true ),
                          make_value( TypeType::UNDEF ),
                          yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                          make_value( TypeType::UNDEF ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                          make_value( TypeType::SYMBOL ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                          make_value( TypeType::SYMBOL ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                          make_value( TypeType::BOOLEAN, false ),
                          yields( make_value( TypeType::BOOLEAN, false ) ),
                          true },
            BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                          make_value( TypeType::BOOLEAN, true ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, false ),
                          make_value( TypeType::SYMBOL ),
                          yields( make_value( TypeType::BOOLEAN, false ) ),
                          true },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, true ),
                          make_value( TypeType::SYMBOL ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN ),
                          make_value( TypeType::BOOLEAN ),
                          yields( make_value( TypeType::BOOLEAN ) ) } ) ) );

INSTANTIATE_TEST_CASE_P(
    libcasm_fe__symbolic_log_op_or,
    symbolic_bin_expr_test,
    Combine(
        Values( libcasm_ir::Value::OR_INSTRUCTION ),
        Values(
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                          make_value( TypeType::UNDEF ),
                          yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                          make_value( TypeType::BOOLEAN, false ),
                          yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                          make_value( TypeType::BOOLEAN, true ),
                          yields( make_value( TypeType::BOOLEAN, true ) ),
                          true },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, false ),
                          make_value( TypeType::UNDEF ),
                          yields( make_value( TypeType::UNDEF ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, true ),
                          make_value( TypeType::UNDEF ),
                          yields( make_value( TypeType::BOOLEAN, true ) ),
                          true },
            BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                          make_value( TypeType::UNDEF ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::UNDEF ),
                          make_value( TypeType::SYMBOL ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                          make_value( TypeType::SYMBOL ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                          make_value( TypeType::BOOLEAN, false ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                          make_value( TypeType::BOOLEAN, true ),
                          yields( make_value( TypeType::BOOLEAN, true ) ),
                          true },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, false ),
                          make_value( TypeType::SYMBOL ),
                          yields( make_value( TypeType::SYMBOL ) ) },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN, true ),
                          make_value( TypeType::SYMBOL ),
                          yields( make_value( TypeType::BOOLEAN, true ) ),
                          true },
            BinaryOpArgs{ make_value( TypeType::BOOLEAN ),
                          make_value( TypeType::BOOLEAN ),
                          yields( make_value( TypeType::BOOLEAN ) ) } ) ) );

INSTANTIATE_TEST_CASE_P(
    libcasm_fe__symbolic_cmp_op_lth_gth,
    symbolic_bin_expr_test,
    Combine(
        Values( libcasm_ir::Value::LTH_INSTRUCTION, libcasm_ir::Value::GTH_INSTRUCTION ),
        ValuesIn( generateSymbolic_BinaryExpressionTestCases(
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
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( TypeType::UNDEF ),
                                       yields( make_value( TypeType::UNDEF ) ) },
                         BinaryOpArgs{ make_value( TypeType::UNDEF ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::UNDEF ) ) },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       yields( make_value( TypeType::BOOLEAN, false ) ),
                                       true },  // same symbols -> false
                         BinaryOpArgs{ make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       make_value( TypeType::SYMBOL, new symbol_t( 2 ) ),
                                       yields( make_value( TypeType::SYMBOL ) ) },  // different
                                                                                    // symbols
                                                                                    // -> new
                                                                                    // symbol
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( number ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( number ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( number ),
                                       make_value( number ),
                                       yields( make_value( TypeType::BOOLEAN ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P(
    libcasm_fe__symbolic_cmp_op_leq_geq,
    symbolic_bin_expr_test,
    Combine(
        Values( libcasm_ir::Value::LEQ_INSTRUCTION, libcasm_ir::Value::GEQ_INSTRUCTION ),
        ValuesIn( generateSymbolic_BinaryExpressionTestCases(
            {
                TypeType::INTEGER, TypeType::FLOATING,
                // TypeType::RATIONAL, TODO EP not implemented yet
            },
            []( TypeType number ) -> BinaryOpArgss {
                return { BinaryOpArgs{ make_value( TypeType::UNDEF ),
                                       make_value( TypeType::UNDEF ),
                                       yields( make_value( TypeType::BOOLEAN, true ) ),
                                       true },
                         BinaryOpArgs{ make_value( TypeType::UNDEF ),
                                       make_value( number ),
                                       yields( make_value( TypeType::UNDEF ) ) },
                         BinaryOpArgs{ make_value( number ),
                                       make_value( TypeType::UNDEF ),
                                       yields( make_value( TypeType::UNDEF ) ) },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( TypeType::UNDEF ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( TypeType::UNDEF ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       yields( make_value( TypeType::BOOLEAN, true ) ),
                                       true },  // same symbols -> true
                         BinaryOpArgs{ make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       make_value( TypeType::SYMBOL, new symbol_t( 2 ) ),
                                       yields( make_value( TypeType::SYMBOL ) ) },  // different
                                                                                    // symbols
                                                                                    // -> new
                                                                                    // symbol
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( number ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( number ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( number ),
                                       make_value( number ),
                                       yields( make_value( TypeType::BOOLEAN ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P(
    libcasm_fe__symbolic_cmp_op_equ,
    symbolic_bin_expr_test,
    Combine(
        Values( libcasm_ir::Value::EQU_INSTRUCTION ),
        ValuesIn( generateSymbolic_BinaryExpressionTestCases(
            {
                TypeType::STRING,
                TypeType::INTEGER,
                TypeType::FLOATING,
                TypeType::BOOLEAN,
                TypeType::LIST,
                TypeType::TUPLE,
                TypeType::TUPLE_OR_LIST,
                TypeType::ENUM,
                TypeType::RATIONAL,
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
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( TypeType::UNDEF ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( TypeType::UNDEF ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       yields( make_value( TypeType::BOOLEAN, true ) ),
                                       true },  // same symbols -> true
                         BinaryOpArgs{ make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       make_value( TypeType::SYMBOL, new symbol_t( 2 ) ),
                                       yields( make_value( TypeType::SYMBOL ) ) },  // different
                                                                                    // symbols
                                                                                    // -> new
                                                                                    // symbol
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( literal ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( literal ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( literal ),
                                       make_value( literal ),
                                       yields( make_value( TypeType::BOOLEAN ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P(
    libcasm_fe__symbolic_cmp_op_neq,
    symbolic_bin_expr_test,
    Combine(
        Values( libcasm_ir::Value::NEQ_INSTRUCTION ),
        ValuesIn( generateSymbolic_BinaryExpressionTestCases(
            {
                TypeType::STRING,
                TypeType::INTEGER,
                TypeType::FLOATING,
                TypeType::BOOLEAN,
                TypeType::LIST,
                TypeType::TUPLE,
                TypeType::TUPLE_OR_LIST,
                TypeType::ENUM,
                TypeType::RATIONAL,
            },
            []( TypeType literal ) -> BinaryOpArgss {
                return { BinaryOpArgs{ make_value( TypeType::UNDEF ),
                                       make_value( TypeType::UNDEF ),
                                       yields( make_value( TypeType::BOOLEAN, false ) ),
                                       true },
                         BinaryOpArgs{ make_value( TypeType::UNDEF ),
                                       make_value( literal ),
                                       yields( make_value( TypeType::BOOLEAN, true ) ),
                                       true },
                         BinaryOpArgs{ make_value( literal ),
                                       make_value( TypeType::UNDEF ),
                                       yields( make_value( TypeType::BOOLEAN, true ) ),
                                       true },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( TypeType::UNDEF ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( TypeType::UNDEF ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       yields( make_value( TypeType::BOOLEAN, false ) ),
                                       true },  // same symbols -> false
                         BinaryOpArgs{ make_value( TypeType::SYMBOL, new symbol_t( 1 ) ),
                                       make_value( TypeType::SYMBOL, new symbol_t( 2 ) ),
                                       yields( make_value( TypeType::SYMBOL ) ) },  // different
                                                                                    // symbols
                                                                                    // -> new
                                                                                    // symbol
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( literal ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( literal ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( literal ),
                                       make_value( literal ),
                                       yields( make_value( TypeType::BOOLEAN ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P(
    libcasm_fe__symbolic_arith_op_add,
    symbolic_bin_expr_test,
    Combine(
        Values( libcasm_ir::Value::ADD_INSTRUCTION ),
        ValuesIn( generateSymbolic_BinaryExpressionTestCases(
            {
                TypeType::INTEGER,
                TypeType::FLOATING,
                TypeType::RATIONAL,
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
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( TypeType::UNDEF ),
                                       yields( make_value( TypeType::UNDEF ) ) },
                         BinaryOpArgs{ make_value( TypeType::UNDEF ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::UNDEF ) ) },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( number ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( number ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( number ),
                                       make_value( number ),
                                       yields( make_value( number ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P(
    libcasm_fe__symbolic_arith_op_sub_mul_div,
    symbolic_bin_expr_test,
    Combine(
        Values(
            libcasm_ir::Value::SUB_INSTRUCTION,
            libcasm_ir::Value::MUL_INSTRUCTION,
            libcasm_ir::Value::DIV_INSTRUCTION ),
        ValuesIn( generateSymbolic_BinaryExpressionTestCases(
            {
                TypeType::INTEGER,
                TypeType::FLOATING,
                TypeType::RATIONAL,
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
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( TypeType::UNDEF ),
                                       yields( make_value( TypeType::UNDEF ) ) },
                         BinaryOpArgs{ make_value( TypeType::UNDEF ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::UNDEF ) ) },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( number ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( number ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( number ),
                                       make_value( number ),
                                       yields( make_value( number ) ) } };
            } ) ) ) );

INSTANTIATE_TEST_CASE_P(
    libcasm_fe__symbolic_arith_op_mod,
    symbolic_bin_expr_test,
    Combine(
        Values( libcasm_ir::Value::MOD_INSTRUCTION ),
        ValuesIn( generateSymbolic_BinaryExpressionTestCases(
            {
                TypeType::INTEGER,
                TypeType::FLOATING,
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
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( TypeType::UNDEF ),
                                       yields( make_value( TypeType::UNDEF ) ) },
                         BinaryOpArgs{ make_value( TypeType::UNDEF ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::UNDEF ) ) },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( TypeType::SYMBOL ),
                                       make_value( number ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( number ),
                                       make_value( TypeType::SYMBOL ),
                                       yields( make_value( TypeType::SYMBOL ) ) },
                         BinaryOpArgs{ make_value( number ),
                                       make_value( number ),
                                       yields( make_value( number ) ) } };
            } ) ) ) );
