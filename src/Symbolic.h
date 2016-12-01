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

#ifndef CASMI_LIBINTERPRETER_SYMBOLIC_H
#define CASMI_LIBINTERPRETER_SYMBOLIC_H

#include "Ast.h"
#include "Value.h"

struct symbol_t
{
    const uint32_t id;
    symbolic_condition_t* condition;
    bool type_dumped;
    bool update_dumped;
    List* list; // used for symbolic lists
    // The distinction between concrete lists and symbolic lists can be fuzzy,
    // because fcons formulas are generated for all list constants by the legacy
    // interpreter

    symbol_t( uint32_t id );
    symbol_t( uint32_t id, symbolic_condition_t* cond );
};

struct symbolic_condition_t
{
    value_t* lhs;
    value_t* rhs;
    BinaryExpression::Operation op;

    symbolic_condition_t(
        value_t* lhs, value_t* rhs, BinaryExpression::Operation op );
    std::string to_str() const;
};

#endif
