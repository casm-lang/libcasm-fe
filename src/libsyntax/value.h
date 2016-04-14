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
