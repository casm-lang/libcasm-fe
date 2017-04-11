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

//
// Symbol
//

Namespace::Symbol::Symbol( const Ast::Identifier& identifier,
    Ast::Node& definition,
    const Ast::CallExpression::TargetType targetType,
    const std::size_t arity )
: m_identifier( identifier )
, m_definition( definition )
, m_targetType( targetType )
, m_arity( arity )
{
}

const Ast::Identifier& Namespace::Symbol::identifier( void ) const
{
    return m_identifier;
}

Ast::Node& Namespace::Symbol::definition( void )
{
    return m_definition;
}

Ast::CallExpression::TargetType Namespace::Symbol::targetType( void ) const
{
    return m_targetType;
}

std::size_t Namespace::Symbol::arity( void ) const
{
    return m_arity;
}

//
// Namespace
//

Namespace::Namespace( void )
{
}

u64 Namespace::registerSymbol( Logger& log, const DirectCallExpression& node )
{
    const auto path = node.identifier()->identifiers();
    assert( path->size() == 1 );

    return registerSymbol( log, *path->back(), node,
        CallExpression::TargetType::BUILTIN, node.arguments()->size() );
}

u64 Namespace::registerSymbol( Logger& log, const FunctionDefinition& node )
{
    return registerSymbol( log, *node.identifier(), node,
        CallExpression::TargetType::FUNCTION, node.argumentTypes()->size() );
}

u64 Namespace::registerSymbol( Logger& log, const DerivedDefinition& node )
{
    return registerSymbol( log, *node.identifier(), node,
        CallExpression::TargetType::DERIVED, node.arguments()->size() );
}

u64 Namespace::registerSymbol( Logger& log, const RuleDefinition& node )
{
    return registerSymbol( log, *node.identifier(), node,
        CallExpression::TargetType::RULE, node.arguments()->size() );
}

u64 Namespace::registerSymbol( Logger& log, const EnumerationDefinition& node )
{
    auto err = registerSymbol( log, *node.identifier(), node,
        CallExpression::TargetType::ENUMERATION );

    auto enumerationNamespace = libstdhl::make< Namespace >();

    auto result = m_namespaces.emplace(
        node.identifier()->name(), enumerationNamespace );

    if( not result.second )
    {
        log.error( { node.sourceLocation() },
            "namespace '" + result.first->first + "' already defined" );

        return err + 1;
    }

    for( auto e : *node.enumerators() )
    {
        err += enumerationNamespace->registerSymbol(
            log, *e, node, CallExpression::TargetType::CONSTANT );
    }

    return err;
}

Namespace::Symbol Namespace::find( const DirectCallExpression& node ) const
{
    return find( *node.identifier(), node.arguments()->size() );
}

Namespace::Symbol Namespace::find( const BasicType& node ) const
{
    return find( *node.name(), 0 );
}

Namespace::Symbol Namespace::find( const IdentifierPath& node ) const
{
    return find( node, 0 );
}

Namespace::Symbol Namespace::find(
    const std::string& name, const std::size_t arity ) const
{
    Identifier ident( name );
    const auto _key = key( ident, arity );

    auto result = m_symboltable.find( _key );
    if( result == m_symboltable.end() )
    {
        throw std::domain_error(
            "unable to find " + std::to_string( arity ) + "-ary symbol '" + name
            + "'" );
    }

    return result->second;
}

Namespace::Symbol Namespace::find(
    const std::vector< std::string >& path, const std::size_t arity ) const
{
    assert( path.size() > 0 );

    Namespace* n = const_cast< Namespace* >( this );
    u64 pos = 0;

    while( ( pos + 1 ) != path.size() )
    {
        const auto& name = path[ pos ];

        auto result = m_namespaces.find( name );
        if( result == m_namespaces.end() )
        {
            throw std::domain_error( "unable to find namespace '" + name
                                     + "' in symbol path '"
                                     + libstdhl::String::join( path, "." )
                                     + "'" );
        }

        n = result->second.get();
        pos++;
    }

    try
    {
        const auto symbol = n->find( path[ pos ], arity );
        return symbol;
    }
    catch( const std::domain_error& e )
    {
        throw std::domain_error( "unable to find " + std::to_string( arity )
                                 + "-ary symbol '"
                                 + libstdhl::String::join( path, "." )
                                 + "'" );
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
          << CallExpression::targetTypeString( v.second.targetType() ) << "( "
          << arity << "-ary)\n";
    }

    for( auto v : m_namespaces )
    {
        const auto& name = v.first;
        const auto space = v.second;

        s << space->dump( name + "." );
    }

    return s.str();
}

u64 Namespace::registerSymbol( Logger& log, const Identifier& node,
    const Node& definition, const CallExpression::TargetType targetType,
    const std::size_t arity )
{
    const auto _key = key( node, arity );

    auto result = m_symboltable.emplace( _key,
        Symbol{ node, const_cast< Node& >( definition ), targetType, arity } );

    if( not result.second )
    {
        log.error( { node.sourceLocation() },
            "symbol '" + result.first->first + "' already defined as '"
                + CallExpression::targetTypeString(
                      result.first->second.targetType() )
                + "'" );

        return 1;
    }

    log.debug(
        "registered new symbol '" + result.first->first + "' as '"
        + CallExpression::targetTypeString( result.first->second.targetType() )
        + "'" );

    return 0;
}

Namespace::Symbol Namespace::find( const IdentifierPath& node,
    const std::size_t arity, const std::size_t index ) const
{
    const auto& path = *node.identifiers();

    assert( path.size() > 0 );
    assert( path.size() > index );

    if( ( index + 1 ) < path.size() )
    {
        // search in sub-namespaces

        const auto& name = path[ index ]->name();

        auto result = m_namespaces.find( name );
        if( result == m_namespaces.end() )
        {
            throw std::domain_error( "unable to find namespace '" + name
                                     + "' in symbol path '"
                                     + node.path()
                                     + "'" );
        }

        return result->second->find( node, arity, index + 1 );
    }
    else
    {
        // search for identifier/symbol in this namespace

        const auto& name = *path[ index ];
        const auto _key = key( name, arity );

        auto result = m_symboltable.find( _key );
        if( result == m_symboltable.end() )
        {
            throw std::domain_error(
                "unable to find symbol '" + node.path() + "'" );
        }

        return result->second;
    }
}

static std::string key( const Identifier& node, const std::size_t arity )
{
    const auto identifier = node.name();
    return std::to_string( arity ) + "@" + identifier;
}
