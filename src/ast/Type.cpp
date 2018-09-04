//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                <https://github.com/casm-lang/libcasm-fe>
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

#include "Type.h"

#include "../various/GrammarToken.h"

using namespace libcasm_fe;
using namespace Ast;

static IdentifierPath::Ptr createUnresolvedIdentifierPath( void )
{
    return std::make_shared< IdentifierPath >( std::make_shared< Identifier >( "$unresolved$" ) );
}

//
//
// Type
//

Type::Type( Node::ID id, const IdentifierPath::Ptr& name )
: TypedNode( id )
, m_name( name )
, m_delimiterToken( std::make_shared< Ast::Token >( Grammar::Token::UNRESOLVED ) )
{
}

const IdentifierPath::Ptr& Type::name( void ) const
{
    return m_name;
}

void Type::setDelimiterToken( const Token::Ptr& delimiterToken )
{
    assert( m_delimiterToken->token() == Grammar::Token::UNRESOLVED );
    m_delimiterToken = delimiterToken;
}

const Token::Ptr& Type::delimiterToken( void ) const
{
    return m_delimiterToken;
}

//
//
// UnresolvedType
//

UnresolvedType::UnresolvedType( void )
: Type( Node::ID::UNRESOLVED_TYPE, createUnresolvedIdentifierPath() )
{
}

void UnresolvedType::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// BasicType
//

BasicType::BasicType( const IdentifierPath::Ptr& identifier )
: Type( Node::ID::BASIC_TYPE, identifier )
{
}

void BasicType::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// ComposedType
//

ComposedType::ComposedType(
    const IdentifierPath::Ptr& identifier,
    const Token::Ptr& leftBrace,
    const Types::Ptr& subTypes,
    const Token::Ptr& rightBrace )
: ComposedType( identifier, leftBrace, subTypes, nullptr, rightBrace )
{
}

ComposedType::ComposedType(
    const IdentifierPath::Ptr& identifier,
    const Token::Ptr& leftBrace,
    const Types::Ptr& subTypes,
    const Identifiers::Ptr& subTypeIdentifiers,
    const Token::Ptr& rightBrace )
: Type( Node::ID::COMPOSED_TYPE, identifier )
, m_subTypes( subTypes )
, m_subTypeIdentifiers( subTypeIdentifiers )
, m_leftBrace( leftBrace )
, m_rightBrace( rightBrace )
{
    assert( subTypes );
    assert( not subTypeIdentifiers or subTypes->size() == subTypeIdentifiers->size() );
}

const Types::Ptr& ComposedType::subTypes( void ) const
{
    return m_subTypes;
}

const Identifiers::Ptr& ComposedType::subTypeIdentifiers( void ) const
{
    return m_subTypeIdentifiers;
}

const Token::Ptr& ComposedType::leftBrace( void ) const
{
    return m_leftBrace;
}

const Token::Ptr& ComposedType::rightBrace( void ) const
{
    return m_rightBrace;
}

u1 ComposedType::isNamed( void ) const
{
    return m_subTypeIdentifiers != nullptr;
}

void ComposedType::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// TemplateType
//

TemplateType::TemplateType(
    const IdentifierPath::Ptr& identifier,
    const Token::Ptr& leftBrace,
    const Types::Ptr& subTypes,
    const Token::Ptr& rightBrace )
: Type( Node::ID::TEMPLATE_TYPE, identifier )
, m_subTypes( subTypes )
, m_leftBrace( leftBrace )
, m_rightBrace( rightBrace )
{
}

const Types::Ptr& TemplateType::subTypes( void ) const
{
    return m_subTypes;
}

const Token::Ptr& TemplateType::leftBrace( void ) const
{
    return m_leftBrace;
}

const Token::Ptr& TemplateType::rightBrace( void ) const
{
    return m_rightBrace;
}

void TemplateType::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// RelationType
//

RelationType::RelationType(
    const IdentifierPath::Ptr& identifier,
    const Token::Ptr& leftBrace,
    const Types::Ptr& argumentTypes,
    const Token::Ptr& maps,
    const Type::Ptr& returnType,
    const Token::Ptr& rightBrace )
: Type( Node::ID::RELATION_TYPE, identifier )
, m_argumentTypes( argumentTypes )
, m_returnType( returnType )
, m_leftBrace( leftBrace )
, m_rightBrace( rightBrace )
, m_maps( maps )
{
}

const Types::Ptr& RelationType::argumentTypes( void ) const
{
    return m_argumentTypes;
}

const Type::Ptr& RelationType::returnType( void ) const
{
    return m_returnType;
}

const Token::Ptr& RelationType::leftBrace( void ) const
{
    return m_leftBrace;
}

const Token::Ptr& RelationType::rightBrace( void ) const
{
    return m_rightBrace;
}

const Token::Ptr& RelationType::maps( void ) const
{
    return m_maps;
}

void RelationType::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// FixedSizeType
//

FixedSizedType::FixedSizedType(
    const IdentifierPath::Ptr& identifier, const Token::Ptr& mark, const Expression::Ptr& size )
: Type( Node::ID::FIXED_SIZED_TYPE, identifier )
, m_size( size )
, m_mark( mark )
{
}

const Expression::Ptr& FixedSizedType::size( void ) const
{
    return m_size;
}

const Token::Ptr& FixedSizedType::mark( void ) const
{
    return m_mark;
}

void FixedSizedType::accept( Visitor& visitor )
{
    visitor.visit( *this );
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
