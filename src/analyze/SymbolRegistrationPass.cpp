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

#include "SymbolRegistrationPass.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "Logger.h"
#include "ast/RecursiveVisitor.h"

using namespace libcasm_fe;
using namespace Ast;

char SymbolRegistrationPass::id = 0;

static libpass::PassRegistration< SymbolRegistrationPass > PASS(
    "ASTSymbolRegistrationPass",
    "registers declared symbols in the symbol table", "ast-sym-reg",
    0 );

class SymbolRegistrationVisitor final : public RecursiveVisitor
{
  public:
    SymbolRegistrationVisitor( Logger& log, Namespace& symboltable );

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

  private:
    Logger& m_log;
    Namespace& m_symboltable;
};

SymbolRegistrationVisitor::SymbolRegistrationVisitor(
    Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

void SymbolRegistrationVisitor::visit( FunctionDefinition& node )
{
    try
    {
        m_symboltable.registerSymbol( node.ptr< FunctionDefinition >() );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = m_symboltable.find( node );

        if( node.uid() == FunctionDefinition::UID::PROGRAM )
        {
            m_log.error( { node.sourceLocation(),
                             symbol.definition()->sourceLocation() },
                "init already defined",
                Code::AgentInitRuleMultipleDefinitions );
        }
        else
        {
            m_log.error( { node.sourceLocation(),
                             symbol.definition()->sourceLocation() },
                e.what(),
                Code::FunctionDefinitionAlreadyUsed );
        }
    }

    RecursiveVisitor::visit( node );
}

void SymbolRegistrationVisitor::visit( DerivedDefinition& node )
{
    try
    {
        m_symboltable.registerSymbol( node.ptr< DerivedDefinition >() );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = m_symboltable.find( node );

        m_log.error(
            { node.sourceLocation(), symbol.definition()->sourceLocation() },
            e.what(), Code::DerivedDefinitionAlreadyUsed );
    }

    RecursiveVisitor::visit( node );
}

void SymbolRegistrationVisitor::visit( RuleDefinition& node )
{
    try
    {
        m_symboltable.registerSymbol( node.ptr< RuleDefinition >() );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = m_symboltable.find( node );

        m_log.error(
            { node.sourceLocation(), symbol.definition()->sourceLocation() },
            e.what(), Code::RuleDefinitionAlreadyUsed );
    }

    RecursiveVisitor::visit( node );
}

void SymbolRegistrationVisitor::visit( EnumerationDefinition& node )
{
    try
    {
        m_symboltable.registerSymbol( node.ptr< EnumerationDefinition >() );

        const auto& name = node.identifier()->name();

        m_log.debug( "creating IR enumeration type '" + name + "'" );
        const auto kind = libstdhl::make< libcasm_ir::Enumeration >( name );
        for( const auto& enumerator : *node.enumerators() )
        {
            kind->add( enumerator->name() );
        }

        const auto type = libstdhl::make< libcasm_ir::EnumerationType >( kind );
        node.setType( type );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = m_symboltable.find( node );

        m_log.error(
            { node.sourceLocation(), symbol.definition()->sourceLocation() },
            e.what() );
    }

    RecursiveVisitor::visit( node );
}

void SymbolRegistrationPass::usage( libpass::PassUsage& pu )
{
    pu.require< AttributionPass >();
}

u1 SymbolRegistrationPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< AttributionPass >();
    const auto specification = data->specification();

    SymbolRegistrationVisitor visitor( log, *specification->symboltable() );
    specification->definitions()->accept( visitor );

#ifndef NDEBUG
    log.debug( "symbol table = \n" + specification->symboltable()->dump() );
#endif

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "found %lu error(s) during symbol table creation", errors );
        return false;
    }

    pr.setResult< SymbolRegistrationPass >( data );

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
