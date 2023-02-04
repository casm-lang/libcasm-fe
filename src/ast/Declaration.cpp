//
//  Copyright (C) 2014-2023 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#include "Declaration.h"

#include <cassert>

using namespace libcasm_fe;
using namespace AST;

//
//
// Declaration
//

Declaration::Declaration(
    const Identifier::Ptr& identifier,
    const Types::Ptr& argumentTypes,
    const Type::Ptr& returnType,
    const Kind kind )
: Definition( Node::ID::DECLARATION, identifier )
, m_argumentTypes( argumentTypes )
, m_returnType( returnType )
, m_kind( kind )
{
    if( m_kind == Kind::DERIVED )
    {
        setProperty( libcasm_ir::Property::SIDE_EFFECT_FREE );
    }
}

const Types::Ptr& Declaration::argumentTypes( void ) const
{
    return m_argumentTypes;
}

const Type::Ptr& Declaration::returnType( void ) const
{
    return m_returnType;
}

Declaration::Kind Declaration::kind( void ) const
{
    return m_kind;
}

std::string Declaration::kindName( void ) const
{
    switch( kind() )
    {
        case Declaration::Kind::DERIVED:
        {
            return "derived";
        }
        case Declaration::Kind::RULE:
        {
            return "rule";
        }
    }

    assert( !" internal error! " );
    return std::string();
}

std::string Declaration::typeDescription( void ) const
{
    std::stringstream stream;
    stream << kindName() << " : ";

    const auto& innerTypes = argumentTypes();
    for( const auto& innerType : *innerTypes )
    {
        stream << innerType->signature() << " * ";
    }

    if( innerTypes->size() > 0 )
    {
        stream.seekp( -2, stream.cur );
    }

    stream << "-> ";
    stream << returnType()->signature() << " ";

    return stream.str();
}

void Declaration::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr Declaration::clone( void ) const
{
    auto duplicate = std::make_shared< Declaration >(
        identifier()->duplicate< Identifier >(),
        argumentTypes()->duplicate< Types >(),
        returnType()->duplicate< Type >(),
        kind() );

    Definition::clone( *duplicate );
    return duplicate;
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
