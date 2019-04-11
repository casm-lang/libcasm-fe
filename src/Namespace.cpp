//
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
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

#include <libstdhl/String>

#include "various/GrammarToken.h"

using namespace libcasm_fe;
using namespace Ast;

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

Ast::Definition::Ptr Namespace::findSymbol( const std::string& name ) const
{
    const auto it = m_symbols.find( name );
    if( it == m_symbols.end() )
    {
        return nullptr;
    }

    return it->second;
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

        s << space->dump( name + Namespace::delimiter() );
    }

    return s.str();
}

Ast::Definition::Ptr Namespace::findSymbol( const IdentifierPath& path ) const
{
    const auto& pathSegments = *path.identifiers();

    auto* _namespace = this;
    for( u64 i = 0; i < ( pathSegments.size() - 1 ); i++ )
    {
        const auto& name = pathSegments[ i ]->name();

        const auto subNamespace = findNamespace( name );
        if( not subNamespace )
        {
            return nullptr;
        }
        _namespace = subNamespace.get();
    }

    return _namespace->findSymbol( path.baseName() );
}

Namespace::Ptr Namespace::findNamespace( const std::string& name ) const
{
    const auto it = m_namespaces.find( name );
    if( it == m_namespaces.end() )
    {
        return nullptr;
    }

    return it->second;
}
