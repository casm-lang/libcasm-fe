//
//  Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
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

#include "Identifier.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/Namespace>
#include <libcasm-fe/cst/Token>

#include <cassert>

using namespace libcasm_fe;
using namespace CST;

//
//
// Identifier
//

Identifier::Identifier( void )
: Identifier( std::string() )
{
}

Identifier::Identifier( const std::string& name )
: Node( Node::ID::IDENTIFIER )
, m_name( name )
, m_doubleColon( Token::unresolved() )
, m_spans( std::make_shared< Spans >() )
{
}

const std::string& Identifier::name( void ) const
{
    return m_name;
}

void Identifier::setName( const std::string& name )
{
    m_name = name;
}

bool Identifier::empty( void ) const
{
    return m_name.empty();
}

void Identifier::setDoubleColon( const Token::Ptr& doubleColon )
{
    assert( m_doubleColon->token() == Grammar::Token::UNRESOLVED );
    m_doubleColon = doubleColon;
}

const Token::Ptr& Identifier::doubleColon( void ) const
{
    return m_doubleColon;
}

void Identifier::setSpans( const Spans::Ptr& spans )
{
    m_spans = spans;
}

const Spans::Ptr& Identifier::spans( void ) const
{
    return m_spans;
}

void Identifier::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr Identifier::clone( void ) const
{
    auto duplicate = std::make_shared< Identifier >( std::string( name() ) );

    Node::clone( *duplicate );
    duplicate->setDoubleColon( doubleColon() );
    duplicate->setSpans( spans() );
    return duplicate;
}

//
//
// IdentifierPath
//

IdentifierPath::IdentifierPath( const Identifier::Ptr& identifier, Type type )
: Node( Node::ID::IDENTIFIER_PATH )
, m_identifiers( CST::make< Identifiers >( identifier->sourceLocation() ) )
, m_type( type )
{
    m_identifiers->add( identifier );
}

IdentifierPath::IdentifierPath( const Identifiers::Ptr& identifiers, Type type )
: Node( Node::ID::IDENTIFIER_PATH )
, m_identifiers( identifiers )
, m_type( type )
{
    assert( not identifiers->empty() && "identifiers must not be empty" );
}

void IdentifierPath::addIdentifier( const Identifier::Ptr& identifier )
{
    m_identifiers->add( identifier );
}

Identifiers::Ptr IdentifierPath::identifiers( void ) const
{
    return m_identifiers;
}

IdentifierPath::Type IdentifierPath::type( void ) const
{
    return m_type;
}

const std::string& IdentifierPath::baseName( void ) const
{
    assert( not m_identifiers->empty() );  // see ctor precondition
    return m_identifiers->back()->name();
}

std::string IdentifierPath::baseDir( void ) const
{
    const auto& p = path();
    const size_t lastDotPos = p.find_last_of( Namespace::delimiter() );
    if( lastDotPos != std::string::npos )
    {
        return p.substr( 0, lastDotPos - Namespace::delimiter().size() + 1 );
    }
    else
    {
        return std::string();
    }
}

std::string IdentifierPath::path( void ) const
{
    std::string path;

    if( m_type == Type::RELATIVE )
    {
        path += Namespace::delimiter();
    }

    bool isFirstElement = true;
    for( const auto& identifier : *m_identifiers )
    {
        if( not isFirstElement )
        {
            path += Namespace::delimiter();
        }
        path += identifier->name();
        isFirstElement = false;
    }

    return path;
}

void IdentifierPath::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr IdentifierPath::clone( void ) const
{
    auto duplicate =
        std::make_shared< IdentifierPath >( identifiers()->duplicate< Identifiers >(), type() );

    Node::clone( *duplicate );
    return duplicate;
}

IdentifierPath::Ptr IdentifierPath::fromIdentifier( const Identifier::Ptr& identifier )
{
    const auto& location = identifier->sourceLocation();
    return CST::make< IdentifierPath >( location, identifier );
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
