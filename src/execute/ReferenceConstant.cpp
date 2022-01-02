//
//  Copyright (C) 2014-2022 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//                <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#include "ReferenceConstant.h"

#include <libcasm-fe/lst/Node>

using namespace libcasm_fe;

static const auto VOID = libstdhl::Memory::get< libcasm_ir::VoidType >();

//
//
// ReferenceConstant
//

ReferenceConstant::ReferenceConstant( const LST::ReferenceLiteral* literal )
: libcasm_ir::ReferenceConstant< LST::ReferenceLiteral >( VOID, literal, classid() )
{
}

ReferenceConstant::ReferenceConstant( void )
: libcasm_ir::ReferenceConstant< LST::ReferenceLiteral >( VOID, classid() )
{
}

std::string ReferenceConstant::toString( void ) const
{
    if( defined() )
    {
        return "@" + value()->identifier()->path();
    }
    else
    {
        return "undef";
    }
}

std::size_t ReferenceConstant::hash( void ) const
{
    if( defined() )
    {
        return std::hash< LST::Node* >()( value()->reference().get() );
    }
    else
    {
        return -1;
    }
}

u1 ReferenceConstant::operator==( const Value& rhs ) const
{
    if( this == &rhs )
    {
        return true;
    }

    if( not libcasm_ir::Value::operator==( rhs ) )
    {
        return false;
    }

    const auto& other = static_cast< const ReferenceConstant& >( rhs );
    return this->hash() == other.hash();
}

u1 ReferenceConstant::classof( Value const* obj )
{
    return obj->id() == classid() or libcasm_ir::RuleReferenceConstant::classof( obj )
        // or libcasm_ir::FunctionReferenceConstant::classof( obj )
        // TODO: enable if FuncRef constant and type is ready
        ;
}

//
//
// ConstantHandler
//

u1 ConstantHandler::name( const libcasm_ir::Constant& constant, std::string& result ) const
{
    if( libcasm_ir::isa< ReferenceConstant >( constant ) )
    {
        const auto referenceConstant = static_cast< const ReferenceConstant& >( constant );
        result = referenceConstant.toString();
        return true;
    }
    else
    {
        return false;
    }
}

u1 ConstantHandler::foreach(
    const libcasm_ir::Constant& constant,
    const std::function< void( const libcasm_ir::Constant& constant ) >& callback ) const
{
    if( libcasm_ir::isa< ReferenceConstant >( constant ) )
    {
        callback( constant );
        return true;
    }
    else
    {
        return false;
    }
}

u1 ConstantHandler::choose(
    const libcasm_ir::Constant& constant, libcasm_ir::Constant& result ) const
{
    if( libcasm_ir::isa< ReferenceConstant >( constant ) )
    {
        result = constant;
        return true;
    }
    else
    {
        return false;
    }
}

u1 ConstantHandler::hash( const libcasm_ir::Constant& constant, std::size_t& result ) const
{
    if( libcasm_ir::isa< ReferenceConstant >( constant ) )
    {
        const auto referenceConstant = static_cast< const ReferenceConstant& >( constant );
        result = referenceConstant.hash();
        return true;
    }
    else
    {
        return false;
    }
}

u1 ConstantHandler::compare(
    const libcasm_ir::Constant& constant, const libcasm_ir::Value& value, u1& result ) const
{
    if( libcasm_ir::isa< ReferenceConstant >( constant ) )
    {
        const auto referenceConstant = static_cast< const ReferenceConstant& >( constant );
        result = referenceConstant.operator==( value );
        return true;
    }
    else
    {
        return false;
    }
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
