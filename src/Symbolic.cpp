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

#include "Symbolic.h"

symbol_t::symbol_t( uint32_t id )
: symbol_t( id, nullptr )
{
}

symbol_t::symbol_t( uint32_t id, symbolic_condition_t* cond )
: id( id )
, condition( cond )
, type_dumped( false )
, update_dumped( false )
, list( nullptr )
{
}

symbolic_condition_t::symbolic_condition_t(
    value_t* lhs, value_t* rhs, BinaryExpression::Operation op )
: lhs( lhs )
, rhs( rhs )
, op( op )
{
}

std::string symbolic_condition_t::to_str() const
{
    using Operation = BinaryExpression::Operation;

    switch( op )
    {
        case Operation::EQ:
            return lhs->to_str() + "=" + rhs->to_str();
        case Operation::NEQ:
            return lhs->to_str() + "!=" + rhs->to_str();
        case Operation::LESSEREQ:
            return "$lesseq(" + lhs->to_str() + ", " + rhs->to_str() + ")";
        case Operation::LESSER:
            return "$less(" + lhs->to_str() + ", " + rhs->to_str() + ")";
        case Operation::GREATER:
            return "$greater(" + lhs->to_str() + ", " + rhs->to_str() + ")";
        case Operation::GREATEREQ:
            return "$greatereq(" + lhs->to_str() + ", " + rhs->to_str() + ")";
        default:
            FAILURE();
    }
}
