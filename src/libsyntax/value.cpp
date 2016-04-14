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
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//  

#include <assert.h>
#include <utility>
#include <sstream>

#include "libsyntax/ast.h"

#include "libsyntax/value.h"

rational_t::rational_t() {}

rational_t::rational_t(int64_t num, int64_t denom) {
  numerator = num;
  denominator = denom;
}

rational_t::rational_t(const rational_t& other) : numerator(other.numerator),
    denominator(other.denominator) {}

bool rational_t::operator==(const rational_t& other) const {
  return (numerator * other.denominator) == (other.numerator * denominator);
}

/*
const rational_t& rational_t::operator+(const rational_t& other) const {
  rational_t *result = (rational_t*) pp_mem_alloc(
      &(ExecutionContext::value_stack), sizeof(rational_t)
  );

  result->numerator = (numerator * other.denominator) + (other.numerator * denominator);
  result->denominator = denominator * other.denominator;
  return *result;
}

const rational_t& rational_t::operator-(const rational_t& other) const {
  rational_t *result = (rational_t*) pp_mem_alloc(
      &(ExecutionContext::value_stack), sizeof(rational_t)
  );

  result->numerator = (numerator * other.denominator) - (other.numerator * denominator);
  result->denominator = denominator * other.denominator;
  return *result;
}

const rational_t& rational_t::operator*(const rational_t& other) const {
  rational_t *result = (rational_t*) pp_mem_alloc(
      &(ExecutionContext::value_stack), sizeof(rational_t)
  );

  result->numerator = numerator * other.numerator;
  result->denominator = denominator * other.denominator;
  return *result;
}

const rational_t& rational_t::operator/(const rational_t& other) const {
  rational_t *result = (rational_t*) pp_mem_alloc(
      &(ExecutionContext::value_stack), sizeof(rational_t)
  );

  result->numerator = numerator * other.denominator;
  result->denominator = denominator * other.numerator;
  return *result;
}
*/
const rational_t& rational_t::operator%(const rational_t&) const {
  // rational modulo is not supported by CASM
  return *this;
}

int64_t gcd(int64_t a, int64_t b) {
  int64_t tmp;

  while (b != 0) {
    tmp = b;
    b = a % b;
    a = tmp;
  }
  return a;
}

const std::string rational_t::to_str() const {
  if (numerator == 0) {
    return "0";
  }
  int64_t divisor = gcd(numerator, denominator);
  int64_t num = numerator / divisor;
  int64_t denom = denominator / divisor;
  if (denom == 1) {
    return std::to_string(num);
  } else {
    return std::to_string(num) + "/" + std::to_string(denom);
  }
  return "";
}
