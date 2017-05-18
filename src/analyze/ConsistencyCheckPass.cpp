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

#include "ConsistencyCheckPass.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../Exceptions.h"
#include "../Logger.h"
#include "../Namespace.h"
#include "../analyze/TypeInferencePass.h"
#include "../ast/RecursiveVisitor.h"

#include "../casm-ir/src/Builtin.h"

using namespace libcasm_fe;
using namespace Ast;

char ConsistencyCheckPass::id = 0;

static libpass::PassRegistration< ConsistencyCheckPass > PASS(
    "ASTConsistencyCheckPass",
    "checks the consistency of the AST representation", "ast-check", 0 );

static const std::string PROGRAM = "program";

//
// ConsistencyCheckVisitor
//

class ConsistencyCheckVisitor final : public RecursiveVisitor
{
  public:
    ConsistencyCheckVisitor( Logger& m_log, const Namespace& symboltable );

    void visit( Specification& node ) override;

    void visit( FunctionDefinition& node ) override;

    void visit( ReferenceAtom& node ) override;
    void visit( ValueAtom& node ) override;
    void visit( UndefAtom& node ) override;

    void verify( const TypedNode& node ) const;

  private:
    Logger& m_log;
    const Namespace& m_symboltable;
    u1 m_functionInitially;
};

ConsistencyCheckVisitor::ConsistencyCheckVisitor(
    Logger& log, const Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
, m_functionInitially( false )
{
}

void ConsistencyCheckVisitor::visit( Specification& node )
{
    try
    {
        m_symboltable.find( PROGRAM );
    }
    catch( const std::domain_error& e )
    {
        m_log.error( { node.sourceLocation() },
            "no init definition found in the specification",
            Code::AgentInitRuleNotDefined );
    }

    RecursiveVisitor::visit( node );
}

void ConsistencyCheckVisitor::visit( FunctionDefinition& node )
{
    m_functionInitially = true;

    try
    {
        node.initializers()->accept( *this );
    }
    catch( const CompiletimeException& e )
    {
        const auto name = node.identifier()->name();

        if( name.compare( PROGRAM ) == 0 )
        {
            m_log.error( { node.sourceLocation(), *e.locations().begin() },
                "unknown init rule reference '" + std::string( e.what() ) + "'",
                Code::AgentInitRuleDoesNotExist );
        }
        else
        {
            m_log.error( e );
        }
    }

    m_functionInitially = false;

    node.identifier()->accept( *this );
    node.argumentTypes()->accept( *this );
    node.returnType()->accept( *this );
    node.defaultValue()->accept( *this );
    node.attributes()->accept( *this );
}

void ConsistencyCheckVisitor::visit( ReferenceAtom& node )
{
    RecursiveVisitor::visit( node );

    if( m_functionInitially and not node.type() )
    {
        throw CompiletimeException( node.identifier()->sourceLocation(),
            node.identifier()->path(), Code::Unspecified );
    }

    verify( node );
}

void ConsistencyCheckVisitor::visit( ValueAtom& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::visit( UndefAtom& node )
{
    RecursiveVisitor::visit( node );
    verify( node );
}

void ConsistencyCheckVisitor::verify( const TypedNode& node ) const
{
    if( not node.type() )
    {
        m_log.error( { node.sourceLocation() }, "found node without a type",
            Code::Unspecified );
    }
}

//
// ConsistencyCheckPass
//

void ConsistencyCheckPass::usage( libpass::PassUsage& pu )
{
    pu.require< TypeInferencePass >();
}

u1 ConsistencyCheckPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< TypeInferencePass >();
    const auto specification = data->specification();
    const auto& symboltable = *data->symboltable();

    ConsistencyCheckVisitor visitor( log, symboltable );
    specification->accept( visitor );

    const auto errors = log.errors();
    if( errors )
    {
        log.debug( "found %lu error(s) during consistency checking", errors );
        return false;
    }

    pr.setResult< ConsistencyCheckPass >(
        libstdhl::make< Data >( specification ) );

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
