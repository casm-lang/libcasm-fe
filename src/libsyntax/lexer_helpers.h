//  
//  Copyright (c) 2014-2016, Florian Hahn, Philipp Paulweber
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                https://github.com/ppaulweber/libcasm-fe
//  
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see <http://www.gnu.org/licenses/>.
//  

#ifndef CASMI_LIBPARSE_LEXER_HELPERS_H
#define CASMI_LIBPARSE_LEXER_HELPERS_H

#include <cstdint>
#include <iostream>

#include "libsyntax/types.h"
#include "libsyntax/driver.h"
#include "libsyntax/parser.tab.h"

INTEGER_T convert_to_long(const char* val, int base, Driver &driver, yy::location loc);
FLOAT_T convert_to_float(const char* val, Driver &driver, yy::location loc);
rational_t convert_to_rational(char* val, Driver &driver, yy::location loc);

#endif
