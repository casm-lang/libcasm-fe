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

#include "ReferenceConstant.h"

using namespace libcasm_fe;

static const auto VOID = libstdhl::get< libcasm_ir::VoidType >();

ReferenceConstant::ReferenceConstant( const Ast::ReferenceAtom* atom )
: libcasm_ir::ReferenceConstant< Ast::ReferenceAtom >( VOID, atom, classid() )
{
}

ReferenceConstant::ReferenceConstant( void )
: libcasm_ir::ReferenceConstant< Ast::ReferenceAtom >( VOID, classid() )
{
}

Ast::ReferenceAtom* ReferenceConstant::atom( void ) const
{
    return value();
}

std::string ReferenceConstant::name( void ) const
{
    if( defined() )
    {
        return "@" + atom()->identifier()->path();
    }
    else
    {
        return "undef";
    }
}

u1 ReferenceConstant::classof( Value const* obj )
{
    return obj->id() == classid()
           or libcasm_ir::RuleReferenceConstant::classof( obj )
        // or libcasm_ir::FunctionReferenceConstant::classof( obj )
        // TODO: enable if FuncRef constant and type is ready
        ;
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
