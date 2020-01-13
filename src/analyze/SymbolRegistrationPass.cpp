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
#include <libcasm-fe/ast/Declaration>
#include <libcasm-fe/ast/Definition>
#include <libcasm-fe/transform/CstToAstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace AST;

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

namespace libcasm_fe
{
    namespace AST
    {
        class SymbolRegistrationVisitor final : public RecursiveVisitor
        {
          public:
            SymbolRegistrationVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

            void visit( InitDefinition& node ) override;
            void visit( FunctionDefinition& node ) override;
            void visit( DerivedDefinition& node ) override;
            void visit( RuleDefinition& node ) override;
            void visit( EnumeratorDefinition& node ) override;
            void visit( EnumerationDefinition& node ) override;
            void visit( UsingDefinition& node ) override;
            void visit( DomainDefinition& node ) override;
            void visit( StructureDefinition& node ) override;
            void visit( BehaviorDefinition& node ) override;
            void visit( ImplementDefinition& node ) override;
            void visit( BuiltinDefinition& node ) override;
            void visit( Declaration& node ) override;

          private:
            void registerSymbol( Definition& node );

          private:
            libcasm_fe::Logger& m_log;
            Namespace& m_symboltable;
        };
    }
}

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

    SymbolRegistrationVisitor enumeratorVisitor( m_log, *node.symboltable() );
    node.enumerators()->accept( enumeratorVisitor );
}

void SymbolRegistrationVisitor::visit( UsingDefinition& node )
{
    registerSymbol( node );
}

void SymbolRegistrationVisitor::visit( DomainDefinition& node )
{
    registerSymbol( node );
}

void SymbolRegistrationVisitor::visit( StructureDefinition& node )
{
    SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, *node.symboltable() );
    node.functions()->accept( symbolRegistrationVisitor );

    registerSymbol( node );
}

void SymbolRegistrationVisitor::visit( BehaviorDefinition& node )
{
    SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, *node.symboltable() );
    node.definitions()->accept( symbolRegistrationVisitor );

    registerSymbol( node );
}

void SymbolRegistrationVisitor::visit( ImplementDefinition& node )
{
    // symbol registration is done during symbol resolving

    SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, *node.symboltable() );
    node.definitions()->accept( symbolRegistrationVisitor );
}

void SymbolRegistrationVisitor::visit( BuiltinDefinition& node )
{
    registerSymbol( node );
}

void SymbolRegistrationVisitor::visit( Declaration& node )
{
    registerSymbol( node );
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

        if( symbol->abstract() and not node.abstract() )
        {
            symbol->symboltable()->replaceSymbol( name, node.ptr< Definition >() );
            return;
        }
        else
        {
            m_log.error( { node.sourceLocation() }, e.what(), Code::IdentifierIsAlreadyUsed );
            m_log.info( { symbol->sourceLocation() }, e.what() );
            return;
        }
    }

    if( ( node.id() == Node::ID::DOMAIN_DEFINITION ) or
        ( node.id() == Node::ID::ENUMERATION_DEFINITION ) or
        ( node.id() == Node::ID::STRUCTURE_DEFINITION ) )
    {
        const auto& typeDefinition = static_cast< TypeDefinition& >( node );
        const auto& typeName = typeDefinition.domainType()->signature();

        try
        {
            node.symboltable()->registerNamespace( name, std::make_shared< Namespace >() );
        }
        catch( const std::domain_error& e )
        {
            m_log.error( { node.sourceLocation() }, e.what(), Code::IdentifierIsAlreadyUsed );
        }

        try
        {
            node.symboltable()->registerSymbol( name, node.ptr< Definition >() );
        }
        catch( const std::domain_error& e )
        {
            const auto& symbol = node.symboltable()->findSymbol( typeName );

            if( symbol->abstract() and not node.abstract() )
            {
                m_symboltable.replaceSymbol( name, node.ptr< Definition >() );
                return;
            }

            m_log.error( { node.sourceLocation() }, e.what(), Code::IdentifierIsAlreadyUsed );
            m_log.info( { symbol->sourceLocation() }, e.what() );
        }

        return;
    }
}

//
//
// SymbolRegistrationPass
//

void SymbolRegistrationPass::usage( libpass::PassUsage& pu )
{
    pu.require< CstToAstPass >();
}

u1 SymbolRegistrationPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto& data = pr.output< CstToAstPass >();
    const auto& specification = data->specification();

    SymbolRegistrationVisitor visitor( log, *specification->symboltable() );
    specification->ast()->accept( visitor );

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
