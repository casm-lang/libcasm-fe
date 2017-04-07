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

#include "Namespace.h"

#include "../stdhl/cpp/String.h"

using namespace libcasm_fe;
using namespace Ast;

static std::string key( const Identifier& node, const std::size_t arity );

Namespace::Namespace( void )
{
}

u64 Namespace::registerSymbol( Logger& log, const Identifier& node,
    const CallExpression::TargetType targetType, const std::size_t arity )
{
    const auto _key = key( node.identifier(), arity );

    auto result = m_symboltable.emplace( _key, targetType );

    if( not result.second )
    {
        log.error( { node.sourceLocation() },
            "symbol '" + result.first->first + "' already defined as '"
                + CallExpression::targetTypeString( result.first->second )
                + "'" );

        return 1;
    }

    log.debug( "registered new symbol '" + result.first->first + "' as '"
               + CallExpression::targetTypeString( result.first->second )
               + "'" );

    return 0;
}

u64 Namespace::registerSymbol( Logger& log, const FunctionDefinition& node )
{
    return registerSymbol( log, *node.identifier(),
        CallExpression::TargetType::FUNCTION, node.argumentTypes()->size() );
}

u64 Namespace::registerSymbol( Logger& log, const DerivedDefinition& node )
{
    return registerSymbol( log, *node.identifier(),
        CallExpression::TargetType::DERIVED, node.arguments()->size() );
}

u64 Namespace::registerSymbol( Logger& log, const RuleDefinition& node )
{
    return registerSymbol( log, *node.identifier(),
        CallExpression::TargetType::RULE, node.arguments()->size() );
}

u64 Namespace::registerSymbol( Logger& log, const EnumerationDefinition& node )
{
    auto err = registerSymbol(
        log, *node.identifier(), CallExpression::TargetType::ENUMERATION );

    auto enumerationNamespace = libstdhl::make< Namespace >();

    auto result = m_namespaces.emplace(
        node.identifier()->identifier(), enumerationNamespace );

    if( not result.second )
    {
        log.error( { node.sourceLocation() },
            "namespace '" + result.first->first + "' already defined" );

        return err + 1;
    }

    for( auto e : *node.enumerators() )
    {
        err += enumerationNamespace->registerSymbol(
            log, *e, CallExpression::TargetType::CONSTANT );
    }

    return err;
}

CallExpression::TargetType Namespace::find(
    const DirectCallExpression& node ) const
{
    const auto arity = node.arguments()->size();
    const auto _key = key( *node.identifier()->identifiers()->back(), arity );

    auto result = m_symboltable.find( _key );
    if( result != m_symboltable.end() )
    {
        return result->second;
    }
    else
    {
        return CallExpression::TargetType::UNKNOWN;
    }
}

std::string Namespace::dump( const std::string& indention ) const
{
    std::stringstream s;

    for( auto v : m_symboltable )
    {
        std::vector< std::string > parts;
        libstdhl::String::split( v.first, "@", parts );

        const auto& arity = parts[ 0 ];
        const auto& name = parts[ 1 ];

        s << indention << name << " : "
          << CallExpression::targetTypeString( v.second ) << "( " << arity
          << "-ary)\n";
    }

    for( auto v : m_namespaces )
    {
        const auto& name = v.first;
        const auto space = v.second;

        s << space->dump( name + "." );
    }

    return s.str();
}

static std::string key( const Identifier& node, const std::size_t arity )
{
    const auto identifier = node.identifier();
    return std::to_string( arity ) + "@" + identifier;
}
