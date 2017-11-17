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

//
// Symbol
//

Namespace::Symbol::Symbol( const Ast::TypedNode::Ptr& definition,
    const Ast::CallExpression::TargetType targetType,
    const std::size_t arity )
: m_definition( definition )
, m_targetType( targetType )
, m_arity( arity )
{
}

const Ast::TypedNode::Ptr& Namespace::Symbol::definition( void ) const
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

void Namespace::registerSymbol( const DirectCallExpression::Ptr& node,
    const CallExpression::TargetType targetType )
{
    registerSymbol( node->identifier()->baseName(), node, targetType,
        node->arguments()->size() );
}

void Namespace::registerSymbol( const std::string& identifier,
    const TypedNode::Ptr& definition,
    const CallExpression::TargetType targetType )
{
    registerSymbol( identifier, definition, targetType, 0 );
}

void Namespace::registerSymbol( const FunctionDefinition::Ptr& node )
{
    registerSymbol( node->identifier()->name(), node,
        CallExpression::TargetType::FUNCTION, node->argumentTypes()->size() );
}

void Namespace::registerSymbol( const DerivedDefinition::Ptr& node )
{
    registerSymbol( node->identifier()->name(), node,
        CallExpression::TargetType::DERIVED, node->arguments()->size() );
}

void Namespace::registerSymbol( const RuleDefinition::Ptr& node )
{
    registerSymbol( node->identifier()->name(), node,
        CallExpression::TargetType::RULE, node->arguments()->size() );
}

void Namespace::registerSymbol( const EnumerationDefinition::Ptr& node )
{
    registerSymbol( node->identifier()->name(), node,
        CallExpression::TargetType::TYPE_DOMAIN );

    auto enumerationNamespace = libstdhl::Memory::make< Namespace >();

    auto result = m_namespaces.emplace(
        node->identifier()->name(), enumerationNamespace );

    if( not result.second )
    {
        throw std::domain_error(
            "namespace '" + result.first->first + "' already defined" );
    }

    for( auto e : *node->enumerators() )
    {
        enumerationNamespace->registerSymbol(
            e->name(), node, CallExpression::TargetType::CONSTANT );
    }
}

void Namespace::registerSymbol( const BasicType::Ptr& node )
{
    registerSymbol( node->name()->baseName(), node,
        CallExpression::TargetType::TYPE_DOMAIN );
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

    for( const auto& v : m_symboltable )
    {
        const auto& name = v.first;
        const auto& symbol = v.second.front();

        const auto& type = symbol.definition()->type();

        s << indention << name << " : "
          << CallExpression::targetTypeString( symbol.targetType() ) << " ("
          << symbol.arity() << "-ary)"
          << " " << ( type ? type->description() : "$unresolved$" ) << "\n";
    }

    for( const auto& v : m_namespaces )
    {
        const auto& name = v.first;
        const auto& space = v.second;

        s << space->dump( name + "." );
    }

    return s.str();
}

void Namespace::registerSymbol( const std::string& name,
    const TypedNode::Ptr& definition,
    const CallExpression::TargetType targetType, const std::size_t arity )
{
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

    symtbl.emplace_back( definition, targetType, arity );
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
