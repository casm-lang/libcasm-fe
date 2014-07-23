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
