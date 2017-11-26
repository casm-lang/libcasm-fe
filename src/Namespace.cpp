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

#include "Namespace.h"

#include <libstdhl/String>

using namespace libcasm_fe;
using namespace Ast;

Namespace::Namespace( void )
: m_symbols()
, m_namespaces()
{
}

void Namespace::registerSymbol( const std::string& name, const Ast::Definition::Ptr& definition )
{
    const auto result = m_symbols.emplace( name, definition );
    if( not result.second )
    {
        const auto& existingDefinition = result.first->second;
        throw std::domain_error(
            "symbol '" + name + "' already defined as " + existingDefinition->description() + "'" );
    }
}

void Namespace::registerNamespace( const std::string& name, const Namespace::Ptr& _namespace )
{
    const auto result = m_namespaces.emplace( name, _namespace );
    if( not result.second )
    {
        throw std::domain_error( "namespace '" + name + "' already defined" );
    }
}

void Namespace::addNamespace(
    const Ast::IdentifierPath::Ptr& path, const Namespace::Ptr& _namespace )
{
    const auto identifiers = path->identifiers();
    assert( not identifiers->empty() );

    // Get the deepest nested namespace to register the given namespace.
    // The last identifier of the path will be used for the namespace name.
    Namespace* ns = this;
    const auto end = std::prev( identifiers->cend() );
    for( auto it = identifiers->cbegin(); it != end; ++it )
    {
        ns = &ns->nestedNamespace( *it );
    }
    ns->addNamespace( identifiers->back(), _namespace );
}

void Namespace::addNamespace(
    const Ast::Identifier::Ptr& identifier, const Namespace::Ptr& _namespace )
{
    const auto result = m_namespaces.emplace( identifier->name(), _namespace );
    if( not result.second )
    {
        throw std::domain_error(
            "namespace '" + identifier->name() + "' already defined" );
    }
}

Namespace& Namespace::findNestedNamespace(
    const Ast::Identifier::Ptr& identifier ) const
{
    const auto it = m_namespaces.find( identifier->name() );
    if( it == m_namespaces.cend() )
    {
        throw std::domain_error(
            "namespace '" + identifier->name() + "' not found" );
    }

    return *it->second;
}

Ast::Definition::Ptr Namespace::find( const std::string& name ) const
{
    const auto it = m_symbols.find( name );
    if( it == m_symbols.end() )
    {
        throw std::domain_error( "unable to find symbol '" + name + "'" );
    }

    return it->second;
}

Ast::Definition::Ptr Namespace::find( const std::vector< std::string >& path ) const
{
    assert( path.size() > 0 );

    auto* _namespace = this;
    u64 pos = 0;

    while( ( pos + 1 ) != path.size() )
    {
        const auto& name = path[ pos ];

        const auto it = m_namespaces.find( name );
        if( it == m_namespaces.end() )
        {
            throw std::domain_error(
                "unable to find namespace '" + name + "' in symbol path '" +
                libstdhl::String::join( path, "." ) + "'" );
        }

        _namespace = it->second.get();
        pos++;
    }

    try
    {
        return _namespace->find( path[ pos ] );
    }
    catch( const std::domain_error& e )
    {
        throw std::domain_error(
            "unable to find symbol '" + libstdhl::String::join( path, "." ) + "'" );
    }
}

std::string Namespace::dump( const std::string& indention ) const
{
    std::stringstream s;

    for( const auto& symbol : m_symbols )
    {
        const auto& name = symbol.first;
        const auto& definition = symbol.second;

        const auto& type = definition->type();

        s << indention << name << " : " << definition->description() << " "
          << ( type ? type->description() : "$unresolved$" ) << "\n";
    }

    for( const auto& _namespace : m_namespaces )
    {
        const auto& name = _namespace.first;
        const auto& space = _namespace.second;

        s << space->dump( name + "." );
    }

    return s.str();
}

Namespace& Namespace::nestedNamespace( const Ast::Identifier::Ptr& identifier )
{
    try
    {
        return findNestedNamespace( identifier );
    }
    catch( const std::domain_error& e )
    {
        const auto _namespace = std::make_shared< Namespace >();
        this->addNamespace( identifier, _namespace );
        return *_namespace;
    }

    assert( !"internal error!" );
    return *this;
}

Ast::Definition::Ptr Namespace::find( const IdentifierPath& node, const std::size_t index ) const
{
    const auto& path = *node.identifiers();

    assert( path.size() > 0 );
    assert( path.size() > index );

    if( ( index + 1 ) < path.size() )
    {
        // search in sub-namespaces

        const auto& name = path[ index ]->name();

        const auto it = m_namespaces.find( name );
        if( it == m_namespaces.end() )
        {
            throw std::domain_error(
                "unable to find namespace '" + name + "' in symbol path '" + node.path() + "'" );
        }

        return it->second->find( node, index + 1 );
    }
    else
    {
        // search for identifier/symbol in this namespace

        const auto& name = path[ index ]->name();

        const auto it = m_symbols.find( name );
        if( it == m_symbols.end() )
        {
            throw std::domain_error( "unable to find symbol '" + node.path() + "'" );
        }

        return it->second;
    }
}
