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

//
// Symbol
//

Namespace::Symbol::Symbol( const Ast::Identifier& identifier,
    Ast::TypedNode& definition,
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

Ast::TypedNode& Namespace::Symbol::definition( void )
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

void Namespace::registerSymbol( const DirectCallExpression& node )
{
    const auto path = node.identifier()->identifiers();
    assert( path->size() == 1 );

    registerSymbol( *path->back(), node, CallExpression::TargetType::BUILTIN,
        node.arguments()->size() );
}

void Namespace::registerSymbol( const FunctionDefinition& node )
{
    registerSymbol( *node.identifier(), node,
        CallExpression::TargetType::FUNCTION, node.argumentTypes()->size() );
}

void Namespace::registerSymbol( const DerivedDefinition& node )
{
    registerSymbol( *node.identifier(), node,
        CallExpression::TargetType::DERIVED, node.arguments()->size() );
}

void Namespace::registerSymbol( const RuleDefinition& node )
{
    registerSymbol( *node.identifier(), node, CallExpression::TargetType::RULE,
        node.arguments()->size() );
}

void Namespace::registerSymbol( const EnumerationDefinition& node )
{
    registerSymbol(
        *node.identifier(), node, CallExpression::TargetType::ENUMERATION );

    auto enumerationNamespace = libstdhl::make< Namespace >();

    auto result = m_namespaces.emplace(
        node.identifier()->name(), enumerationNamespace );

    if( not result.second )
    {
        throw std::domain_error(
            "namespace '" + result.first->first + "' already defined" );
    }

    for( auto e : *node.enumerators() )
    {
        enumerationNamespace->registerSymbol(
            *e, node, CallExpression::TargetType::CONSTANT );
    }
}

Namespace::Symbol Namespace::find( const DirectCallExpression& node ) const
{
    return find( *node.identifier(), node.arguments()->size() );
}

Namespace::Symbol Namespace::find( const FunctionDefinition& node ) const
{
    return find( node.identifier()->name(), node.argumentTypes()->size() );
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
    auto result = m_symboltable.find( name );
    if( result == m_symboltable.end() )
    {
        throw std::domain_error(
            "unable to find " + std::to_string( arity ) + "-ary symbol '" + name
            + "'" );
    }

    return result->second.front();
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
        const auto& name = v.first;

        s << indention << name << " : "
          << CallExpression::targetTypeString( v.second.front().targetType() )
          << "( " << v.second.front().arity() << "-ary)\n";
    }

    for( auto v : m_namespaces )
    {
        const auto& name = v.first;
        const auto space = v.second;

        s << space->dump( name + "." );
    }

    return s.str();
}

void Namespace::registerSymbol( const Identifier& node,
    const TypedNode& definition, const CallExpression::TargetType targetType,
    const std::size_t arity )
{
    const auto name = node.name();

    auto& symtbl = m_symboltable[ name ];

    for( const auto& symbol : symtbl )
    {
        if( symbol.arity() == arity )
        {
            throw std::domain_error(
                "symbol '" + name + "' already defined as "
                + std::to_string( arity )
                + "-ary '"
                + CallExpression::targetTypeString( symbol.targetType() )
                + "'" );
        }
    }

    symtbl.emplace_back( Symbol{
        node, const_cast< TypedNode& >( definition ), targetType, arity } );
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

        const auto& name = path[ index ]->name();

        auto result = m_symboltable.find( name );
        if( result == m_symboltable.end() )
        {
            throw std::domain_error(
                "unable to find symbol '" + node.path() + "'" );
        }

        if( result->second.size() > 1 )
        {
            for( const auto& symbol : result->second )
            {
                if( symbol.arity() == arity )
                {
                    return symbol;
                }
            }

            throw std::domain_error( "unable to find " + std::to_string( arity )
                                     + "-ary symbol '"
                                     + node.path()
                                     + "'" );
        }

        return result->second.front();
    }
}
