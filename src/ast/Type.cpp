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

#include "Type.h"

using namespace libcasm_fe;
using namespace Ast;

Type::Type( Node::ID id, const Identifier::Ptr& name )
: TypedNode( id )
, m_name( name )
{
}

Identifier::Ptr Type::name( void ) const
{
    return m_name;
}

static Identifier::Ptr createUnresolvedIdentifier()
{
    return std::make_shared< Identifier >( "$unresolved$" );
}

UnresolvedType::UnresolvedType( void )
: Type( Node::ID::UNRESOLVED_TYPE, createUnresolvedIdentifier() )
{
}

void UnresolvedType::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

BasicType::BasicType( const Identifier::Ptr& identifier )
: Type( Node::ID::BASIC_TYPE, identifier )
{
}

void BasicType::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

ComposedType::ComposedType(
    const Identifier::Ptr& identifier, const Types::Ptr& subTypes )
: Type( Node::ID::COMPOSED_TYPE, identifier )
, m_subTypes( subTypes )
{
}

Types::Ptr ComposedType::subTypes( void ) const
{
    return m_subTypes;
}

void ComposedType::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

FixedSizedType::FixedSizedType(
    const Identifier::Ptr& identifier, const Expression::Ptr& size )
: Type( Node::ID::FIXED_SIZED_TYPE, identifier )
, m_size( size )
{
}

Expression::Ptr FixedSizedType::size( void ) const
{
    return m_size;
}

void FixedSizedType::accept( Visitor& visitor )
{
    visitor.visit( *this );
}
