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

#include "Symbolic.h"

using namespace libcasm_fe;

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
    value_t* lhs, value_t* rhs, libcasm_ir::Value::ID op )
: lhs( lhs )
, rhs( rhs )
, op( op )
{
}

std::string symbolic_condition_t::to_str() const
{
    using Opcode = libcasm_ir::Value::ID;

    switch( op )
    {
        case Opcode::EQU_INSTRUCTION:
            return lhs->to_str() + "=" + rhs->to_str();
        case Opcode::NEQ_INSTRUCTION:
            return lhs->to_str() + "!=" + rhs->to_str();
        case Opcode::LEQ_INSTRUCTION:
            return "$lesseq(" + lhs->to_str() + ", " + rhs->to_str() + ")";
        case Opcode::LTH_INSTRUCTION:
            return "$less(" + lhs->to_str() + ", " + rhs->to_str() + ")";
        case Opcode::GTH_INSTRUCTION:
            return "$greater(" + lhs->to_str() + ", " + rhs->to_str() + ")";
        case Opcode::GEQ_INSTRUCTION:
            return "$greatereq(" + lhs->to_str() + ", " + rhs->to_str() + ")";
        default:
            FAILURE();
    }
}
