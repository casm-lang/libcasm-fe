#ifndef CASMI_LIBINTERPRETER_VALUE_H
#define CASMI_LIBINTERPRETER_VALUE_H

#include "macros.h"


struct enum_value_t;
struct rational_t;


struct rational_t {
  int64_t numerator;
  int64_t denominator;

  rational_t();
  rational_t(int64_t num, int64_t denom);
  rational_t(const rational_t& other);

  bool operator==(const rational_t& other) const;
  const rational_t& operator+(const rational_t& other) const;
  const rational_t& operator-(const rational_t& other) const;
  const rational_t& operator*(const rational_t& other) const;
  const rational_t& operator/(const rational_t& other) const;
  const rational_t& operator%(const rational_t& other) const;

  const std::string to_str() const;
};

#endif
