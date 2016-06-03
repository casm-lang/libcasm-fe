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

#include "Operators.h"

#include <cassert>
#include <utility>
#include <sstream>

#include "Symbolic.h"
#include "ExecutionContext.h"
#include "../Value.h"
#include "../Ast.h"

#define HANDLE_SYMBOLIC_OR_UNDEF(lhs, rhs)                                  \
  if (lhs.is_undef() || rhs.is_undef()) {                                   \
    return value_t();                                                       \
  } else if (lhs.is_symbolic() || rhs.is_symbolic()) {                      \
    /* TODO cleanup symbols */                                              \
    return value_t(new symbol_t(symbolic::next_symbol_id()));               \
  }                                                                         \

#define CREATE_NUMERICAL_OPERATION(op, lhs, rhs)  {                         \
  HANDLE_SYMBOLIC_OR_UNDEF(lhs, rhs)                                        \
  switch (lhs.type) {                                                       \
    case TypeType::INTEGER:                                                 \
      return value_t(lhs.value.integer op rhs.value.integer);               \
    case TypeType::FLOATING:                                                \
      return value_t(lhs.value.float_ op rhs.value.float_);                 \
    case TypeType::RATIONAL:                                                \
      return value_t(&(*lhs.value.rat op *rhs.value.rat));                  \
    default: FAILURE();                                                     \
  }                                                                         \
}

#define CREATE_NUMERICAL_CMP_OPERATION(op, lhs, rhs)  {                     \
  HANDLE_SYMBOLIC_OR_UNDEF(lhs, rhs)                                        \
                                                                            \
  switch (lhs.type) {                                                       \
    case TypeType::INTEGER:                                                 \
      return value_t(lhs.value.integer op rhs.value.integer);               \
    case TypeType::FLOATING:                                                \
      return value_t(lhs.value.float_ op rhs.value.float_);                 \
    default: FAILURE();                                                     \
  }                                                                         \
}

#define CHECK_SYMBOLIC_CMP_OPERATION(op, lhs, rhs) {                        \
 if (lhs.is_symbolic() && !rhs.is_undef()) {                                \
    return value_t(new symbol_t(symbolic::next_symbol_id(),                 \
                              new symbolic_condition_t(new value_t(lhs),    \
                                                     new value_t(rhs),      \
                                                      op)));                \
 }                                                                          \
 if (rhs.is_symbolic() && !lhs.is_undef()) {                                \
    return value_t(new symbol_t(symbolic::next_symbol_id(),                 \
                              new symbolic_condition_t(new value_t(lhs),    \
                                                     new value_t(rhs),      \
                                                      op)));                \
  }                                                                         \
}

const value_t operators::dispatch(ExpressionOperation op, const value_t& lhs, const value_t& rhs) {
  switch (op) {
    case ExpressionOperation::ADD:
      return operators::add(lhs, rhs);

    case ExpressionOperation::SUB:
      return operators::sub(lhs, rhs);

    case ExpressionOperation::MUL:
      return operators::mul(lhs, rhs);

    case ExpressionOperation::DIV:
      return operators::div(lhs, rhs);

    case ExpressionOperation::MOD:
      return operators::mod(lhs, rhs);

    case ExpressionOperation::RAT_DIV:
      return operators::rat_div(lhs, rhs);

    case ExpressionOperation::EQ:
      if (lhs.is_symbolic() && rhs.is_symbolic()) {
        return operators::eq(lhs, rhs);
      } else {
        CHECK_SYMBOLIC_CMP_OPERATION(op, lhs, rhs);
        return operators::eq(lhs, rhs);
      }

    case ExpressionOperation::NEQ:
      if (lhs.is_symbolic() && rhs.is_symbolic()) {
        return operators::neq(lhs, rhs);
      } else {
        CHECK_SYMBOLIC_CMP_OPERATION(op, lhs, rhs);
        return operators::neq(lhs, rhs);
      }

    case ExpressionOperation::AND:
      return operators::and_(lhs, rhs);

    case ExpressionOperation::OR:
      return operators::or_(lhs, rhs);

    case ExpressionOperation::XOR:
      return operators::xor_(lhs, rhs);

    case ExpressionOperation::NOT:
      return operators::not_(lhs);

    case ExpressionOperation::LESSER:
      if (lhs.is_symbolic() && rhs.is_symbolic() && lhs == rhs) {
        return value_t(false);
      }

      CHECK_SYMBOLIC_CMP_OPERATION(op, lhs, rhs);
      return operators::lesser(lhs, rhs);

    case ExpressionOperation::GREATER:
      if (lhs.is_symbolic() && rhs.is_symbolic() && lhs == rhs) {
        return value_t(false);
      }

      CHECK_SYMBOLIC_CMP_OPERATION(op, lhs, rhs);
      return operators::greater(lhs, rhs);

    case ExpressionOperation::LESSEREQ:
      if (lhs.is_symbolic() && rhs.is_symbolic() && lhs == rhs) {
        return value_t(true);
      }

      CHECK_SYMBOLIC_CMP_OPERATION(op, lhs, rhs);
      return operators::lessereq(lhs, rhs);

    case ExpressionOperation::GREATEREQ:
      if (lhs.is_symbolic() && rhs.is_symbolic() && lhs == rhs) {
        return value_t(true);
      }

      CHECK_SYMBOLIC_CMP_OPERATION(op, lhs, rhs);
      return operators::greatereq(lhs, rhs);

    default: FAILURE();
  }
}

const value_t operators::add(const value_t& lhs, const value_t& rhs) {
  CREATE_NUMERICAL_OPERATION(+, lhs, rhs);
}

const value_t operators::sub(const value_t& lhs, const value_t& rhs) {
  CREATE_NUMERICAL_OPERATION(-, lhs, rhs);
}

const value_t operators::mul(const value_t& lhs, const value_t& rhs) {
  CREATE_NUMERICAL_OPERATION(*, lhs, rhs);
}

const value_t operators::div(const value_t& lhs, const value_t& rhs) {
  CREATE_NUMERICAL_OPERATION(/, lhs, rhs);
}

const value_t operators::mod(const value_t& lhs, const value_t& rhs) {
  HANDLE_SYMBOLIC_OR_UNDEF(lhs, rhs)
  if (lhs.type == TypeType::INTEGER) {
    return value_t(lhs.value.integer % rhs.value.integer);
  }
  return value_t();
}

const value_t operators::rat_div(const value_t& lhs, const value_t& rhs) {
  HANDLE_SYMBOLIC_OR_UNDEF(lhs, rhs)

  switch (lhs.type) {
    case TypeType::INTEGER: {
      auto result = reinterpret_cast<rational_t*>(ExecutionContext::value_stack.allocate(sizeof(rational_t)));
      result->numerator = lhs.value.integer;
      result->denominator = rhs.value.integer;
      return value_t(result);
    }
    default: FAILURE();
  }
}

const value_t operators::eq(const value_t& lhs, const value_t& rhs) {
  return value_t(lhs == rhs);
}

const value_t operators::and_(const value_t& lhs, const value_t& rhs) {
  if (lhs.is_undef() || rhs.is_undef()) {
    return value_t();
  }
  return value_t(lhs.value.boolean && rhs.value.boolean);
}

const value_t operators::or_(const value_t& lhs, const value_t& rhs) {
  if (lhs.is_undef() || rhs.is_undef()) {
    return value_t();
  }
  return value_t(lhs.value.boolean || rhs.value.boolean);
}

const value_t operators::xor_(const value_t& lhs, const value_t& rhs) {
  if (lhs.is_undef() || rhs.is_undef()) {
    return value_t();
  }
  return value_t((bool)(lhs.value.boolean ^ rhs.value.boolean));
}

const value_t operators::not_(const value_t& lhs) {
  if (lhs.is_undef()) {
    return value_t();
  }
  return value_t(!lhs.value.boolean);
}

const value_t operators::neq(const value_t& lhs, const value_t& rhs) {
  return value_t(lhs != rhs);
}

const value_t operators::lesser(const value_t& lhs, const value_t& rhs) {
  CREATE_NUMERICAL_CMP_OPERATION(<, lhs, rhs);
}

const value_t operators::greater(const value_t& lhs, const value_t& rhs) {
  CREATE_NUMERICAL_CMP_OPERATION(>, lhs, rhs);
}

const value_t operators::lessereq(const value_t& lhs, const value_t& rhs) {
  CREATE_NUMERICAL_CMP_OPERATION(<=, lhs, rhs);
}

const value_t operators::greatereq(const value_t& lhs, const value_t& rhs) {
  CREATE_NUMERICAL_CMP_OPERATION(>=, lhs, rhs);
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
