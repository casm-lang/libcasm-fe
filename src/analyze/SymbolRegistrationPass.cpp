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

#include "SymbolRegistrationPass.h"

#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/analyze/AttributionPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace Ast;

char SymbolRegistrationPass::id = 0;

static libpass::PassRegistration< SymbolRegistrationPass > PASS(
    "Symbol Registration Pass",
    "registers defined and declared symbols in the namespace symbol table",
    "ast-sym-reg",
    0 );

//
//
// SymbolRegistrationVisitor
//

SymbolRegistrationVisitor::SymbolRegistrationVisitor(
    libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

void SymbolRegistrationVisitor::visit( InitDefinition& node )
{
    const auto& name = node.identifier()->name();

    try
    {
        m_symboltable.registerSymbol( name, node.ptr< Definition >() );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = m_symboltable.findSymbol( name );
        m_log.error(
            { node.sourceLocation() },
            "multiple definitions of 'init' rule",
            Code::AgentInitRuleMultipleDefinitions );
        m_log.info( { symbol->sourceLocation() }, "first definition found here" );
        return;
    }
}

void SymbolRegistrationVisitor::visit( FunctionDefinition& node )
{
    registerSymbol( node );
}

void SymbolRegistrationVisitor::visit( DerivedDefinition& node )
{
    registerSymbol( node );
}

void SymbolRegistrationVisitor::visit( RuleDefinition& node )
{
    registerSymbol( node );
}

void SymbolRegistrationVisitor::visit( EnumeratorDefinition& node )
{
    registerSymbol( node );
}

void SymbolRegistrationVisitor::visit( EnumerationDefinition& node )
{
    registerSymbol( node );

    const auto symbolNamespace = std::make_shared< Namespace >();

    registerSymbolNamespace( node, symbolNamespace );

    const auto& domainName = node.identifier()->name();
    auto domainNamespace = m_symboltable.findNamespace( domainName );
    assert( domainNamespace and " inconsistent state @ registerSymbolNamespace " );

    SymbolRegistrationVisitor enumeratorVisitor( m_log, *domainNamespace );
    node.enumerators()->accept( enumeratorVisitor );
}

void SymbolRegistrationVisitor::visit( UsingDefinition& node )
{
    registerSymbol( node );

    const auto symbolNamespace = std::make_shared< Namespace >();

    registerSymbolNamespace( node, node.identifier()->name(), symbolNamespace );
}

void SymbolRegistrationVisitor::visit( DomainDefinition& node )
{
    registerSymbol( node );

    const auto symbolNamespace = std::make_shared< Namespace >();

    registerSymbolNamespace( node, symbolNamespace );
}

void SymbolRegistrationVisitor::visit( StructureDefinition& node )
{
    registerSymbol( node );

    const auto symbolNamespace = std::make_shared< Namespace >();
    SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, *symbolNamespace );
    node.functions()->accept( symbolRegistrationVisitor );

    registerSymbolNamespace( node, symbolNamespace );
}

void SymbolRegistrationVisitor::visit( FeatureDefinition& node )
{
    registerSymbol( node );

    const auto symbolNamespace = std::make_shared< Namespace >();
    SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, *symbolNamespace );
    node.definitions()->accept( symbolRegistrationVisitor );

    registerSymbolNamespace( node, symbolNamespace );
}

void SymbolRegistrationVisitor::visit( ImplementDefinition& node )
{
    const auto& domainType = node.domainType();
    const auto& domainTypeName = domainType->signature();
    const auto& domainTypePath = domainType->signaturePath();

    // Domain::Type::
    const auto domainTypeNamespace = m_symboltable.findNamespace( *domainTypePath );
    if( not domainTypeNamespace )
    {
        // domain type not found, delay to SymbolResolverPass
        return;
    }

    // Domain::Type::Domain::
    const auto implementDomainNamespace = std::make_shared< Namespace >();
    auto implementDomainDefinition = node.ptr< TypeDefinition >();
    auto implementDomainName = implementDomainDefinition->identifier()->name();
    auto implementTypeName = implementDomainDefinition->domainType()->signature();

    if( node.hasFeature() )
    {
        const auto& featureType = node.featureType();
        const auto& featureTypeName = featureType->signature();
        const auto& featureTypePath = featureType->signaturePath();
        const auto& featureTypeSymbolResult = m_symboltable.findSymbol( *featureTypePath );
        const auto& featureTypeSymbol = featureTypeSymbolResult.first;
        if( not featureTypeSymbol )
        {
            // feature type not found, delay to SymbolResolverPass
            return;
        }

        implementDomainDefinition = featureTypeSymbol->ptr< TypeDefinition >();
        implementDomainName = featureType->signature();
        implementTypeName = featureType->signature();
    }

    try
    {
        // Domain::Type::Symbol
        domainTypeNamespace->registerSymbol( implementDomainName, implementDomainDefinition );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = m_symboltable.findSymbol( implementDomainName );
        m_log.error( { node.sourceLocation() }, e.what(), Code::IdentifierIsAlreadyUsed );
        m_log.info( { symbol->sourceLocation() }, e.what() );
    }

    try
    {
        // Domain::Type::Domain::
        domainTypeNamespace->registerNamespace( implementDomainName, implementDomainNamespace );
    }
    catch( const std::domain_error& e )
    {
        m_log.error( { node.sourceLocation() }, e.what() );
    }

    try
    {
        // Domain::Type::Domain::Symbol
        implementDomainNamespace->registerSymbol( implementTypeName, node.ptr< TypeDefinition >() );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = m_symboltable.findSymbol( implementDomainName );
        m_log.error( { node.sourceLocation() }, e.what(), Code::IdentifierIsAlreadyUsed );
        m_log.info( { symbol->sourceLocation() }, e.what() );
    }

    // Domain::Type::Domain::Type::*
    const auto implementTypeNamespace = std::make_shared< Namespace >();
    SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, *implementTypeNamespace );
    node.definitions()->accept( symbolRegistrationVisitor );

    try
    {
        // Domain::Type::Domain::Type::
        implementDomainNamespace->registerNamespace( implementTypeName, implementTypeNamespace );
    }
    catch( const std::domain_error& e )
    {
        m_log.error( { node.sourceLocation() }, e.what() );
    }
}

void SymbolRegistrationVisitor::visit( BuiltinDefinition& node )
{
    registerSymbol( node );

    node.relationType().argumentTypes()->accept( *this );
    node.relationType().returnType()->accept( *this );

    const auto symbolNamespace = std::make_shared< Namespace >();
    registerSymbolNamespace( node, symbolNamespace );
}

void SymbolRegistrationVisitor::visit( Declaration& node )
{
    registerSymbol( node );
    RecursiveVisitor::visit( node );
}

void SymbolRegistrationVisitor::registerSymbol( Definition& node )
{
    const auto& name = node.identifier()->name();

    try
    {
        m_symboltable.registerSymbol( name, node.ptr< Definition >() );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = m_symboltable.findSymbol( name );

        if( ( node.id() == Node::ID::DOMAIN_DEFINITION and
              symbol->id() == Node::ID::DOMAIN_DEFINITION ) or
            ( node.id() == Node::ID::BUILTIN_DEFINITION and
              symbol->id() == Node::ID::BUILTIN_DEFINITION ) or
            ( node.id() == Node::ID::FEATURE_DEFINITION and
              symbol->id() == Node::ID::FEATURE_DEFINITION ) or
            ( node.id() == Node::ID::STRUCTURE_DEFINITION and
              symbol->id() == Node::ID::STRUCTURE_DEFINITION ) )
        {
            const auto& nodeTTD = static_cast< const TypeDefinition& >( node );
            const auto& symbolTTD = static_cast< const TypeDefinition& >( *symbol );

            if( nodeTTD.templateSymbols()->size() == 0 and
                symbolTTD.templateSymbols()->size() != 0 )
            {
                // already registered domain template of domain instance
                return;
            }
        }

        m_log.error(
            { node.sourceLocation() },
            "registerSymbol@Symbol: " + std::string( e.what() ),
            Code::IdentifierIsAlreadyUsed );
        m_log.info( { symbol->sourceLocation() }, e.what() );
    }
}

void SymbolRegistrationVisitor::registerSymbolNamespace(
    TypeDefinition& node, const Namespace::Ptr& symbolNamespace )
{
    const auto& typeName = node.domainType()->signature();
    registerSymbolNamespace( node, typeName, symbolNamespace );
}

void SymbolRegistrationVisitor::registerSymbolNamespace(
    Definition& node, const std::string& typeName, const Namespace::Ptr& symbolNamespace )
{
    const auto& domainName = node.identifier()->name();
    auto domainNamespace = m_symboltable.findNamespace( domainName );
    if( not domainNamespace )
    {
        domainNamespace = std::make_shared< Namespace >();
        try
        {
            m_symboltable.registerNamespace( domainName, domainNamespace );
        }
        catch( const std::domain_error& e )
        {
            m_log.error(
                { node.sourceLocation() },
                "registerSymbolNamespace@Namespace:" + std::string( e.what() ) );
        }
    }

    try
    {
        domainNamespace->registerSymbol( typeName, node.ptr< Definition >() );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = domainNamespace->findSymbol( typeName );
        m_log.error(
            { node.sourceLocation() },
            "registerSymbolNamespace@Symbol:" + std::string( e.what() ),
            Code::IdentifierIsAlreadyUsed );
        m_log.info( { symbol->sourceLocation() }, e.what() );
    }

    try
    {
        domainNamespace->registerNamespace( typeName, symbolNamespace );
    }
    catch( const std::domain_error& e )
    {
        m_log.debug( { node.sourceLocation() }, e.what() );
    }
}

//
//
// SymbolRegistrationPass
//

void SymbolRegistrationPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< AttributionPass >();
}

u1 SymbolRegistrationPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();

    SymbolRegistrationVisitor visitor( log, *specification->symboltable() );
    specification->definitions()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "symbol table =\n" + specification->symboltable()->dump() );
        log.debug( "found %lu error(s) during symbol registration", errors );
        return false;
    }

    return true;
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
