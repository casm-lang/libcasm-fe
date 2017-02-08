//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#ifndef CASMI_LIBPARSE_LEXER_HELPERS_H
#define CASMI_LIBPARSE_LEXER_HELPERS_H

#include <cstdint>
#include <iostream>

#include "Driver.h"
#include "Types.h"

#include "various/GrammarParser.tab.h"

INTEGER_T convert_to_long(
    const char* val, int base, Driver& driver, yy::location loc );
FLOATING_T convert_to_float(
    const char* val, Driver& driver, yy::location loc );
rational_t convert_to_rational( char* val, Driver& driver, yy::location loc );

#endif
