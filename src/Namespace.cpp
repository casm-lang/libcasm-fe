//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Jakob Moosbrugger
//                Florian Hahn
//                Ioan Molnar
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

#include "Namespace.h"

#include <libstdhl/Ansi>
#include <libstdhl/String>

#include "various/GrammarToken.h"

using namespace libcasm_fe;
using namespace AST;

const std::string& Namespace::delimiter( void )
{
    static const auto delimiterString = Grammar::tokenAsString( Grammar::Token::DOUBLECOLON );
    return delimiterString;
}

//
//
// Namespace
//

Namespace::Namespace( void )
: m_symbols()
, m_namespaces()
{
}

void Namespace::registerSymbol( const std::string& name, const AST::Definition::Ptr& definition )
{
    const auto result = m_symbols.emplace( name, definition );
    if( not result.second )
    {
        throw std::domain_error( "symbol '" + name + "' already defined" );
    }
}

void Namespace::registerNamespace(
    const std::string& name, const Namespace::Ptr& _namespace, const Visibility visibility )
{
    const auto result = m_namespaces.emplace( name, Linkage{ _namespace, visibility } );
    if( not result.second )
    {
        throw std::domain_error( "namespace '" + name + "' already defined" );
    }
}

Definition::Ptr Namespace::findSymbol( const std::string& name ) const
{
    const auto it = m_symbols.find( name );
    if( it == m_symbols.end() )
    {
        return nullptr;
    }

    return it->second;
}

Namespace::Symbol Namespace::findSymbol( const IdentifierPath& path ) const
{
    const auto& pathSegments = *path.identifiers();

    u1 externalImport = false;
    auto* _namespace = this;

    for( u64 i = 0; i < ( pathSegments.size() - 1 ); i++ )
    {
        const auto& name = pathSegments[ i ]->name();

        const auto it = _namespace->m_namespaces.find( name );
        if( it == _namespace->m_namespaces.end() )
        {
            return Symbol{ nullptr, false };
        }

        _namespace = it->second.first.get();
        const auto visibility = it->second.second;

        if( visibility == Visibility::External )
        {
            externalImport = true;
        }
        else if( visibility == Visibility::Internal and externalImport )
        {
            externalImport = false;
        }
    }

    const auto definition = _namespace->findSymbol( path.baseName() );

    if( not definition )
    {
        return Symbol{ nullptr, false };
    }

    return Symbol{ definition, not externalImport or definition->exported() };
}

Namespace::Ptr Namespace::findNamespace( const std::string& name ) const
{
    const auto it = m_namespaces.find( name );
    if( it == m_namespaces.end() )
    {
        return nullptr;
    }

    return it->second.first;
}

Namespace::Ptr Namespace::findNamespace( const IdentifierPath& path ) const
{
    const auto& pathSegments = *path.identifiers();
    assert( pathSegments.size() >= 1 );
    Namespace::Ptr _namespace = findNamespace( pathSegments[ 0 ]->name() );

    for( u64 i = 1; i < pathSegments.size(); i++ )
    {
        if( not _namespace )
        {
            return nullptr;
        }

        const auto& name = pathSegments[ i ]->name();
        _namespace = _namespace->findNamespace( name );
    }

    return _namespace;
}

const std::unordered_map< std::string, AST::Definition::Ptr >& Namespace::symbols( void ) const
{
    return m_symbols;
}

const std::unordered_map< std::string, Namespace::Linkage >& Namespace::namespaces( void ) const
{
    return m_namespaces;
}

#include <iostream>

void Namespace::registerTypeDefinition( TypeDefinition& node )
{
    if( not node.type() )
    {
        throw std::invalid_argument( node.description() + " has no concrete IR type" );
    }

    const auto result =
        m_typeIdToTypeDefinition.emplace( node.type()->id(), node.ptr< TypeDefinition >() );

    if( not result.second )
    {
        const auto& existingTypeID = result.first->first;
        const auto& existingNode = result.first->second;

        throw std::domain_error(
            "already registered " + node.description() + " '" + node.typeDescription() +
            "' with type ID '" + std::to_string( existingTypeID ) + "'" );
    }
}

AST::TypeDefinition::Ptr Namespace::findTypeDefinition( const libcasm_ir::Type::ID typeID ) const
{
    const auto& definitionResult = m_typeIdToTypeDefinition.find( typeID );
    if( definitionResult == m_typeIdToTypeDefinition.end() )
    {
        return nullptr;
    }

    return definitionResult->second;
}

std::string Namespace::dump( const std::string& indention ) const
{
    std::unordered_set< const Namespace* > visited;
    return dump( indention, visited );
}

std::string Namespace::dump(
    const std::string& indention, std::unordered_set< const Namespace* >& visited ) const
{
    const auto it = visited.emplace( this );
    if( not it.second )
    {
        return indention + " ...\n";
    }

    if( m_symbols.size() == 0 and m_namespaces.size() == 0 )
    {
        return indention + "\n";
    }

    std::stringstream stream;
    for( const auto& symbol : m_symbols )
    {
        const auto& name = symbol.first;
        const auto& definition = symbol.second;
        const auto& type = definition->type();

        stream << indention << name << " "
               << libstdhl::Ansi::format< libstdhl::Ansi::Color::MAGENTA >(
                      definition->description() )
               << " "
               << libstdhl::Ansi::format< libstdhl::Ansi::Color::CYAN >(
                      definition->typeDescription() )
               << " "
               << libstdhl::Ansi::format< libstdhl::Ansi::Color::BLUE >(
                      type ? type->description() : "$unresolved$" )
               << "\n";
    }

    for( const auto& _namespace : m_namespaces )
    {
        const auto& name = _namespace.first;
        const auto& space = _namespace.second.first;
        const auto visibility = libstdhl::Ansi::format< libstdhl::Ansi::Color::MAGENTA >(
            _namespace.second.second == Visibility::Internal ? "-" : "+" );
        const auto prefix = indention + name + Namespace::delimiter() + visibility;
        stream << space->dump( prefix, visited );
    }

    if( indention == "" )
    {
        std::vector< std::string > lines;
        libstdhl::String::split( stream.str(), "\n", lines );
        std::sort( lines.begin(), lines.end() );
        lines.erase( std::remove_if( lines.begin(), lines.end(), []( const std::string& str ) {
            return str.length() == 0;
        } ) );
        return libstdhl::String::join( lines, "\n" ) + "\n";
    }
    else
    {
        return stream.str();
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
