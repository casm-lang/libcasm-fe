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
#include "../src/execute/SymbolicExecutionPass.h"
#include "../src/various/location.hh"

using namespace testing;

template <typename T>
static value_t make_value(TypeType type, T v)
{
    value_t value(v);
    assert(type == value.type);
    return value;
}

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
        case TypeType::SYMBOL:
            static symbol_t* sym = new symbol_t(1);
            value.value.sym = sym;
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

static value_t yields(value_t value)
{
    return value;
}

struct UnaryOpArgs {
    value_t value;
    value_t expectedResult;
    bool checkReturnValue;
};

class Symbolic_UnaryExpressionTest : public TestWithParam<std::tuple<ExpressionOperation, UnaryOpArgs>>{};

TEST_P(Symbolic_UnaryExpressionTest, testUnaryExpressionResultType)
{
    const auto row = GetParam();

    const ExpressionOperation op = std::get<0>(row);
    const auto expr = make_expression(op);

    const auto values = std::get<1>(row);
    const auto value = values.value;
    const auto expectedResult = values.expectedResult;

    const bool checkReturnValue = values.checkReturnValue;

    libcasm_fe::SymbolicExecutionPass visitor{};
    const auto result = visitor.visit_expression_single(expr.get(), value);

    EXPECT_EQ(expectedResult.type, result.type);
    if (checkReturnValue) {
        EXPECT_EQ(expectedResult, result);
    }
}

struct BinaryOpArgs {
    value_t lhs;
    value_t rhs;
    value_t expectedResult;
    bool checkReturnValue;
};

class Symbolic_BinaryExpressionTest : public TestWithParam<std::tuple<ExpressionOperation, BinaryOpArgs>>{};

TEST_P(Symbolic_BinaryExpressionTest, testBinaryExpressionResultType)
{
    const auto row = GetParam();

    const ExpressionOperation op = std::get<0>(row);
    const auto expr = make_expression(op);

    const auto values = std::get<1>(row);
    const auto lhs = values.lhs;
    const auto rhs = values.rhs;
    const auto expectedResult = values.expectedResult;

    const bool checkReturnValue = values.checkReturnValue;

    libcasm_fe::SymbolicExecutionPass visitor{};
    const auto result = visitor.visit_expression(expr.get(), lhs, rhs);

    EXPECT_EQ(expectedResult.type, result.type);
    if (checkReturnValue) {
        EXPECT_EQ(expectedResult, result);
    }
}

using BinaryOpArgss = std::vector<BinaryOpArgs>;
static BinaryOpArgss generateSymbolic_BinaryExpressionTestCases(const std::vector<TypeType> &types,
                                                                const std::function<BinaryOpArgss(TypeType)> &testTemplate)
{
    BinaryOpArgss binOpTypes;
    for (auto type : types) {
        const auto instantiatedTypes = testTemplate(type);
        binOpTypes.insert(binOpTypes.cend(), instantiatedTypes.cbegin(), instantiatedTypes.cend());
    }
    return binOpTypes;
}

INSTANTIATE_TEST_CASE_P(Symbolic_UnaryOperations, Symbolic_UnaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::NOT
        ),
        Values(
            UnaryOpArgs{make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
            UnaryOpArgs{make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            UnaryOpArgs{make_value(TypeType::BOOLEAN), yields(make_value(TypeType::BOOLEAN))}
        )
    )
);

INSTANTIATE_TEST_CASE_P(Symbolic_LogicalOperations_Xor, Symbolic_BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::XOR
        ),
        Values(
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::BOOLEAN), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::BOOLEAN), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::UNDEF), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::BOOLEAN), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::BOOLEAN), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::BOOLEAN), make_value(TypeType::BOOLEAN), yields(make_value(TypeType::BOOLEAN))}
        )
    )
);

INSTANTIATE_TEST_CASE_P(Symbolic_LogicalOperations_And, Symbolic_BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::AND
        ),
        Values(
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::BOOLEAN, false), yields(make_value(TypeType::BOOLEAN, false)), true},
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::BOOLEAN, true), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::BOOLEAN, false), make_value(TypeType::UNDEF), yields(make_value(TypeType::BOOLEAN, false)), true},
            BinaryOpArgs{make_value(TypeType::BOOLEAN, true), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::UNDEF), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::BOOLEAN, false), yields(make_value(TypeType::BOOLEAN, false)), true},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::BOOLEAN, true), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::BOOLEAN, false), make_value(TypeType::SYMBOL), yields(make_value(TypeType::BOOLEAN, false)), true},
            BinaryOpArgs{make_value(TypeType::BOOLEAN, true), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::BOOLEAN), make_value(TypeType::BOOLEAN), yields(make_value(TypeType::BOOLEAN))}
        )
    )
);

INSTANTIATE_TEST_CASE_P(Symbolic_LogicalOperations_Or, Symbolic_BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::OR
        ),
        Values(
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::BOOLEAN, false), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::BOOLEAN, true), yields(make_value(TypeType::BOOLEAN, true)), true},
            BinaryOpArgs{make_value(TypeType::BOOLEAN, false), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::BOOLEAN, true), make_value(TypeType::UNDEF), yields(make_value(TypeType::BOOLEAN, true)), true},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::UNDEF), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::BOOLEAN, false), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::BOOLEAN, true), yields(make_value(TypeType::BOOLEAN, true)), true},
            BinaryOpArgs{make_value(TypeType::BOOLEAN, false), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::BOOLEAN, true), make_value(TypeType::SYMBOL), yields(make_value(TypeType::BOOLEAN, true)), true},
            BinaryOpArgs{make_value(TypeType::BOOLEAN), make_value(TypeType::BOOLEAN), yields(make_value(TypeType::BOOLEAN))}
        )
    )
);

INSTANTIATE_TEST_CASE_P(Symbolic_CompareOperations_LesserGreater, Symbolic_BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::LESSER,
            ExpressionOperation::GREATER
        ),
        ValuesIn(generateSymbolic_BinaryExpressionTestCases(
            {
                TypeType::INTEGER,
                TypeType::FLOATING,
                //TypeType::RATIONAL, TODO EP not implemented yet
            },
            [](TypeType number) -> BinaryOpArgss {
                return {
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(number), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(number), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::SYMBOL), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL, new symbol_t(1)), make_value(TypeType::SYMBOL, new symbol_t(1)), yields(make_value(TypeType::BOOLEAN, false)), true}, // same symbols -> false
                    BinaryOpArgs{make_value(TypeType::SYMBOL, new symbol_t(1)), make_value(TypeType::SYMBOL, new symbol_t(2)), yields(make_value(TypeType::SYMBOL))}, // different symbols -> new symbol
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(number), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(number), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(number), make_value(number), yields(make_value(TypeType::BOOLEAN))}
                };
            }
        ))
    )
);

INSTANTIATE_TEST_CASE_P(Symbolic_CompareOperations_LesserEqGreaterEq, Symbolic_BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::LESSEREQ,
            ExpressionOperation::GREATEREQ
        ),
        ValuesIn(generateSymbolic_BinaryExpressionTestCases(
            {
                TypeType::INTEGER,
                TypeType::FLOATING,
                //TypeType::RATIONAL, TODO EP not implemented yet
            },
            [](TypeType number) -> BinaryOpArgss {
                return {
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::UNDEF), yields(make_value(TypeType::BOOLEAN, true)), true},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(number), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(number), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::UNDEF), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL, new symbol_t(1)), make_value(TypeType::SYMBOL, new symbol_t(1)), yields(make_value(TypeType::BOOLEAN, true)), true}, // same symbols -> true
                    BinaryOpArgs{make_value(TypeType::SYMBOL, new symbol_t(1)), make_value(TypeType::SYMBOL, new symbol_t(2)), yields(make_value(TypeType::SYMBOL))}, // different symbols -> new symbol
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(number), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(number), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(number), make_value(number), yields(make_value(TypeType::BOOLEAN))}
                };
            }
        ))
    )
);

INSTANTIATE_TEST_CASE_P(Symbolic_CompareOperations_Eq, Symbolic_BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::EQ
        ),
        ValuesIn(generateSymbolic_BinaryExpressionTestCases(
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
            [](TypeType literal) -> BinaryOpArgss {
                return {
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::UNDEF), yields(make_value(TypeType::BOOLEAN, true)), true},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(literal), yields(make_value(TypeType::BOOLEAN, false)), true},
                    BinaryOpArgs{make_value(literal), make_value(TypeType::UNDEF), yields(make_value(TypeType::BOOLEAN, false)), true},
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::UNDEF), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL, new symbol_t(1)), make_value(TypeType::SYMBOL, new symbol_t(1)), yields(make_value(TypeType::BOOLEAN, true)), true}, // same symbols -> true
                    BinaryOpArgs{make_value(TypeType::SYMBOL, new symbol_t(1)), make_value(TypeType::SYMBOL, new symbol_t(2)), yields(make_value(TypeType::SYMBOL))}, // different symbols -> new symbol
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(literal), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(literal), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(literal), make_value(literal), yields(make_value(TypeType::BOOLEAN))}
                };
            }
        ))
    )
);

INSTANTIATE_TEST_CASE_P(Symbolic_CompareOperations_Neq, Symbolic_BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::NEQ
        ),
        ValuesIn(generateSymbolic_BinaryExpressionTestCases(
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
            [](TypeType literal) -> BinaryOpArgss {
                return {
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::UNDEF), yields(make_value(TypeType::BOOLEAN, false)), true},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(literal), yields(make_value(TypeType::BOOLEAN, true)), true},
                    BinaryOpArgs{make_value(literal), make_value(TypeType::UNDEF), yields(make_value(TypeType::BOOLEAN, true)), true},
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::UNDEF), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL, new symbol_t(1)), make_value(TypeType::SYMBOL, new symbol_t(1)), yields(make_value(TypeType::BOOLEAN, false)), true}, // same symbols -> false
                    BinaryOpArgs{make_value(TypeType::SYMBOL, new symbol_t(1)), make_value(TypeType::SYMBOL, new symbol_t(2)), yields(make_value(TypeType::SYMBOL))}, // different symbols -> new symbol
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(literal), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(literal), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(literal), make_value(literal), yields(make_value(TypeType::BOOLEAN))}
                };
            }
        ))
    )
);

INSTANTIATE_TEST_CASE_P(Symbolic_ArithmeticOperations_AddSubMulDiv, Symbolic_BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::ADD,
            ExpressionOperation::SUB,
            ExpressionOperation::MUL,
            ExpressionOperation::DIV
        ),
        ValuesIn(generateSymbolic_BinaryExpressionTestCases(
            {
                TypeType::INTEGER,
                TypeType::FLOATING,
                TypeType::RATIONAL,
            },
            [](TypeType number) -> BinaryOpArgss {
                return {
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(number), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(number), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::SYMBOL), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(number), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(number), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(number), make_value(number), yields(make_value(number))}
                };
            }
        ))
    )
);

INSTANTIATE_TEST_CASE_P(Symbolic_ArithmeticOperations_Mod, Symbolic_BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::MOD
        ),
        ValuesIn(generateSymbolic_BinaryExpressionTestCases(
            {
                TypeType::INTEGER,
                TypeType::FLOATING,
            },
            [](TypeType number) -> BinaryOpArgss {
                return {
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(number), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(number), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::SYMBOL), yields(make_value(TypeType::UNDEF))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(number), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(number), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
                    BinaryOpArgs{make_value(number), make_value(number), yields(make_value(number))}
                };
            }
        ))
    )
);


INSTANTIATE_TEST_CASE_P(Symbolic_ArithmeticOperations_RatDiv, Symbolic_BinaryExpressionTest,
    Combine(
        Values(
            ExpressionOperation::RAT_DIV
        ),
        Values(
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::INTEGER), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::INTEGER), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::UNDEF), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::UNDEF), make_value(TypeType::SYMBOL), yields(make_value(TypeType::UNDEF))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::SYMBOL), make_value(TypeType::INTEGER), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::INTEGER), make_value(TypeType::SYMBOL), yields(make_value(TypeType::SYMBOL))},
            BinaryOpArgs{make_value(TypeType::INTEGER), make_value(TypeType::INTEGER), yields(make_value(TypeType::RATIONAL))}
        )
    )
);
