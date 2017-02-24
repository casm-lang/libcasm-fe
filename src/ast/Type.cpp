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

Type::Type( Node::ID id, const IdentifierNode::Ptr& name )
: Node( id )
, m_name( name )
{
}

IdentifierNode::Ptr Type::name( void ) const
{
    return m_name;
}

BasicType::BasicType( const IdentifierNode::Ptr& identifier )
: Type( Node::BASIC_TYPE, identifier )
{
}

ComposedType::ComposedType(
    const IdentifierNode::Ptr& identifier, const Types::Ptr& subTypes )
: Type( Node::COMPOSED_TYPE, identifier )
, m_subTypes( subTypes )
{
}

Types::Ptr ComposedType::subTypes( void ) const
{
    return m_subTypes;
}

StaticallySizedType::StaticallySizedType(
    const IdentifierNode::Ptr& identifier, const Expression::Ptr& size )
: Type( Node::STATICALLY_SIZED_TYPE, identifier )
, m_size( size )
{
}

Expression::Ptr StaticallySizedType::size( void ) const
{
    return m_size;
}

RangedType::RangedType( const IdentifierNode::Ptr& identifier,
    const Expression::Ptr& lowerBound, const Expression::Ptr& upperBound )
: Type( Node::RANGED_TYPE, identifier )
, m_lowerBound( lowerBound )
, m_upperBound( upperBound )
{
}

Expression::Ptr RangedType::lowerBound( void ) const
{
    return m_lowerBound;
}

Expression::Ptr RangedType::upperBound( void ) const
{
    return m_upperBound;
}
