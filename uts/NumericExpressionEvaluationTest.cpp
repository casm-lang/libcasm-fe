//
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libcasm-fe
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

static value_t make_value(TypeType type)
{
    value_t value;
    value.type = type;
    switch (type) {
        case TypeType::STRING:
            static std::string str = "test";
            value.value.string = &str;
            break;
        case TypeType::LIST:
        case TypeType::TUPLE:
        case TypeType::TUPLE_OR_LIST:
            static List* list = new HeadList(nullptr, value_t());
            value.value.list = list;
            break;
        case TypeType::ENUM:
            static std::string name = "enum";
            static enum_value_t* enum_val = new enum_value_t(&name, 1);
            value.value.enum_val = enum_val;
            break;
        case TypeType::RATIONAL:
            static rational_t* rat = new rational_t(1, 1);
            value.value.rat = rat;
            break;
        default:
            break;
    }
    return value;
}

static std::unique_ptr<Expression> make_expression(ExpressionOperation op)
{
    auto location = yy::location(nullptr);
    return std::unique_ptr<Expression>(new Expression(location, nullptr, nullptr, op));
}

constexpr TypeType yields(TypeType type)
{
    return type;
}

using UnaryOpType = std::tuple<TypeType, TypeType>;
class UnaryExpressionTest : public TestWithParam<std::tuple<ExpressionOperation, UnaryOpType>>{};

TEST_P(UnaryExpressionTest, testUnaryExpressionResultType)
{
    const auto row = GetParam();

    const ExpressionOperation op = std::get<0>(row);

    const auto types = std::get<1>(row);
    const TypeType valueType = std::get<0>(types);
    const TypeType resultType = std::get<1>(types);

    libcasm_fe::NumericExecutionPass visitor{};

    const auto expr = make_expression(op);
    const auto value = make_value(valueType);

    EXPECT_EQ(resultType, visitor.visit_expression_single(expr.get(), value).type);
}

using BinaryOpType = std::tuple<TypeType, TypeType, TypeType>;
class BinaryExpressionTest : public TestWithParam<std::tuple<ExpressionOperation, BinaryOpType>>{};

TEST_P(BinaryExpressionTest, testBinaryExpressionResultType)
{
    const auto row = GetParam();

    const ExpressionOperation op = std::get<0>(row);

    const auto types = std::get<1>(row);
    const TypeType lhsType = std::get<0>(types);
    const TypeType rhsType = std::get<1>(types);
    const TypeType resultType = std::get<2>(types);

    libcasm_fe::NumericExecutionPass visitor{};

    const auto expr = make_expression(op);
    const auto lhs = make_value(lhsType);
    const auto rhs = make_value(rhsType);

    EXPECT_EQ(resultType, visitor.visit_expression(expr.get(), lhs, rhs).type);
}

using BinaryOpTypes = std::vector<BinaryOpType>;
static BinaryOpTypes generateBinaryExpressionTestCases(const std::vector<TypeType> &types,
                                                       const std::function<BinaryOpTypes(TypeType)> &testTemplate)
{
    BinaryOpTypes binOpTypes;
    for (auto type : types) {
        const auto instantiatedTypes = testTemplate(type);
        binOpTypes.insert(binOpTypes.cend(), instantiatedTypes.cbegin(), instantiatedTypes.cend());
    }
    return binOpTypes;
}

INSTANTIATE_TEST_CASE_P(NotOperation, UnaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::NOT
        ),
        Values(
            UnaryOpType{TypeType::UNDEF, yields(TypeType::UNDEF)},
            UnaryOpType{TypeType::BOOLEAN, yields(TypeType::BOOLEAN)}
        )
    )
);

INSTANTIATE_TEST_CASE_P(LogicalOperations, BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::AND,
            ExpressionOperation::OR,
            ExpressionOperation::XOR
        ),
        Values(
            BinaryOpType{TypeType::UNDEF, TypeType::UNDEF, yields(TypeType::UNDEF)},
            BinaryOpType{TypeType::UNDEF, TypeType::BOOLEAN, yields(TypeType::UNDEF)},
            BinaryOpType{TypeType::BOOLEAN, TypeType::UNDEF, yields(TypeType::UNDEF)},
            BinaryOpType{TypeType::BOOLEAN, TypeType::BOOLEAN, yields(TypeType::BOOLEAN)}
        )
    )
);

INSTANTIATE_TEST_CASE_P(CompareOperationsLesserGreater, BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::LESSER,
            ExpressionOperation::GREATER
        ),
        ValuesIn(generateBinaryExpressionTestCases(
            {
                TypeType::INTEGER,
                TypeType::FLOATING,
                //TypeType::RATIONAL, TODO EP not implemented yet
            },
            [](TypeType number) -> BinaryOpTypes {
                return {
                    BinaryOpType{TypeType::UNDEF, TypeType::UNDEF, yields(TypeType::UNDEF)},
                    BinaryOpType{TypeType::UNDEF, number, yields(TypeType::UNDEF)},
                    BinaryOpType{number, TypeType::UNDEF, yields(TypeType::UNDEF)},
                    BinaryOpType{number, number, yields(TypeType::BOOLEAN)}
                };
            }
        ))
    )
);

INSTANTIATE_TEST_CASE_P(CompareOperationsLesserEqGreaterEq, BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::LESSEREQ,
            ExpressionOperation::GREATEREQ
        ),
        ValuesIn(generateBinaryExpressionTestCases(
            {
                TypeType::INTEGER,
                TypeType::FLOATING,
                //TypeType::RATIONAL, TODO EP not implemented yet
            },
            [](TypeType number) -> BinaryOpTypes {
                return {
                    BinaryOpType{TypeType::UNDEF, TypeType::UNDEF, yields(TypeType::BOOLEAN)},
                    BinaryOpType{TypeType::UNDEF, number, yields(TypeType::UNDEF)},
                    BinaryOpType{number, TypeType::UNDEF, yields(TypeType::UNDEF)},
                    BinaryOpType{number, number, yields(TypeType::BOOLEAN)}
                };
            }
        ))
    )
);

INSTANTIATE_TEST_CASE_P(CompareOperationsEqNeq, BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::EQ,
            ExpressionOperation::NEQ
        ),
        ValuesIn(generateBinaryExpressionTestCases(
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
            [](TypeType literal) -> BinaryOpTypes {
                return {
                    BinaryOpType{TypeType::UNDEF, TypeType::UNDEF, yields(TypeType::BOOLEAN)},
                    BinaryOpType{TypeType::UNDEF, literal, yields(TypeType::BOOLEAN)},
                    BinaryOpType{literal, TypeType::UNDEF, yields(TypeType::BOOLEAN)},
                    BinaryOpType{literal, literal, yields(TypeType::BOOLEAN)}
                };
            }
        ))
    )
);

INSTANTIATE_TEST_CASE_P(ArithmeticOperationsAddSubMulDiv, BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::ADD,
            ExpressionOperation::SUB,
            ExpressionOperation::MUL,
            ExpressionOperation::DIV
        ),
        ValuesIn(generateBinaryExpressionTestCases(
            {
                TypeType::INTEGER,
                TypeType::FLOATING,
                TypeType::RATIONAL,
            },
            [](TypeType number) -> BinaryOpTypes {
                return {
                    BinaryOpType{TypeType::UNDEF, TypeType::UNDEF, yields(TypeType::UNDEF)},
                    BinaryOpType{TypeType::UNDEF, number, yields(TypeType::UNDEF)},
                    BinaryOpType{number, TypeType::UNDEF, yields(TypeType::UNDEF)},
                    BinaryOpType{number, number, yields(number)}
                };
            }
        ))
    )
);

INSTANTIATE_TEST_CASE_P(ArithmeticOperationsMod, BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::MOD
        ),
        ValuesIn(generateBinaryExpressionTestCases(
            {
                TypeType::INTEGER,
                TypeType::FLOATING,
            },
            [](TypeType number) -> BinaryOpTypes {
                return {
                    BinaryOpType{TypeType::UNDEF, TypeType::UNDEF, yields(TypeType::UNDEF)},
                    BinaryOpType{TypeType::UNDEF, number, yields(TypeType::UNDEF)},
                    BinaryOpType{number, TypeType::UNDEF, yields(TypeType::UNDEF)},
                    BinaryOpType{number, number, yields(number)}
                };
            }
        ))
    )
);


INSTANTIATE_TEST_CASE_P(ArithmeticOperationsRatDiv, BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::RAT_DIV
        ),
        Values(
            BinaryOpType{TypeType::UNDEF, TypeType::UNDEF, yields(TypeType::UNDEF)},
            BinaryOpType{TypeType::UNDEF, TypeType::INTEGER, yields(TypeType::UNDEF)},
            BinaryOpType{TypeType::INTEGER, TypeType::UNDEF, yields(TypeType::UNDEF)},
            BinaryOpType{TypeType::INTEGER, TypeType::INTEGER, yields(TypeType::RATIONAL)}
        )
    )
);
