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

#include "Agent.h"

#include <libcasm-fe/Exception>
#include <libcasm-fe/Logger>
#include <libcasm-fe/analyze/FrameSizeDeterminationPass>
#include <libcasm-fe/ast/Expression>
#include <libcasm-fe/ast/RecursiveVisitor>
#include <libcasm-fe/ast/Rule>
#include <libcasm-fe/transform/SourceToAstPass>
#include <libcasm-fe/execute/UpdateException>

#include <libcasm-ir/Exception>
#include <libcasm-ir/Operation>

#include <mutex>
#include <stdexcept>
#include <thread>

using namespace libcasm_fe;
using namespace Ast;

namespace IR = libcasm_ir;

Agent::Agent(
    ExecutionLocationRegistry& locationRegistry,
    const Storage& globalState,
    const IR::Constant& agentId,
    const ReferenceConstant& rule,
    bool symbolic,
    libstdhl::Optional< IR::SymbolicExecutionEnvironment* > environment )
: m_globalState( globalState )
, m_locationRegistry( locationRegistry )
, m_agentId( agentId )
, m_rule( rule )
, m_updateSetManager()
, m_symbolic( symbolic )
, m_environment( environment )
{
}

void Agent::run( void )
{
    Transaction transaction( &m_updateSetManager, Semantics::Parallel, 100 );
    if( symbolic() )
    {
        if( not m_environment )
        {
            throw Exception( "Symbolic Agent has no environment." );
        }
        SymbolicExecutionVisitor executionVisitor(
            m_locationRegistry, m_globalState, m_updateSetManager, m_agentId, **m_environment );
        executionVisitor.execute( m_rule );
    }
    else
    {
        ExecutionVisitor executionVisitor(
            m_locationRegistry, m_globalState, m_updateSetManager, m_agentId );
        executionVisitor.execute( m_rule );
    }
    transaction.merge();
}

ExecutionUpdateSet* Agent::updateSet( void ) const
{
    return m_updateSetManager.currentUpdateSet();
}

void Agent::setSymbolicEnvironment( IR::SymbolicExecutionEnvironment& environment )
{
    m_environment = &environment;
}

bool Agent::symbolic( void ) const
{
    return m_symbolic;
}

void ParallelDispatchStrategy::dispatch( std::vector< Agent >& agents )
{
    if( agents.size() == 1 )
    {
        agents.at( 0 ).run();
    }
    else
    {
        std::vector< std::thread > threads;
        threads.reserve( agents.size() );
        for( auto& agent : agents )
        {
            threads.emplace_back( [&] { agent.run(); } );
        }
        for( auto& thread : threads )
        {
            thread.join();
        }
    }
}

void SequentialDispatchStrategy::dispatch( std::vector< Agent >& agents )
{
    for( auto& agent : agents )
    {
        agent.run();
    }
}

void AllAgentsSelectionStrategy::selectAgents( std::vector< Agent >& agents ) const
{
}

void SingleRandomAgentSelectionStrategy::selectAgents( std::vector< Agent >& agents ) const
{
    if( agents.size() < 2 )
    {
        return;
    }

    const auto randomIndex = libstdhl::Random::uniform< std::size_t >( 0, agents.size() - 1 );
    auto selectedAgent = std::move( agents[ randomIndex ] );
    agents.clear();
    agents.push_back( std::move( selectedAgent ) );
}

AgentScheduler::AgentScheduler(
    ExecutionLocationRegistry& locationRegistry, Storage& globalState, bool symbolic )
: m_dispatchStrategy( libstdhl::Memory::make_unique< SequentialDispatchStrategy >() )
, m_selectionStrategy( nullptr )
, m_globalState( globalState )
, m_locationRegistry( locationRegistry )
, m_collectedUpdates()
, m_done( false )
, m_symbolic( symbolic )
, m_stepCounter( 0 )
, m_environment()
{
}

void AgentScheduler::setDispatchStrategy( std::unique_ptr< DispatchStrategy > dispatchStrategy )
{
    m_dispatchStrategy = std::move( dispatchStrategy );
}

void AgentScheduler::setAgentSelectionStrategy(
    std::unique_ptr< SelectionStrategy > selectionStrategy )
{
    m_selectionStrategy = std::move( selectionStrategy );
}

void AgentScheduler::setSymbolicEnvironment( IR::SymbolicExecutionEnvironment& environment )
{
    m_environment = &environment;
}

void AgentScheduler::step( void )
{
    auto agents = collectAgents();
    selectAgents( agents );

    if( agents.empty() )
    {
        m_done = true;
        return;
    }

    dispatch( agents );

    collectUpdates( agents );
    m_done = m_collectedUpdates.empty();
    fireUpdates();

    ++m_stepCounter;
}

bool AgentScheduler::done( void ) const
{
    return m_done;
}

bool AgentScheduler::symbolic( void ) const
{
    return m_symbolic;
}

std::size_t AgentScheduler::numberOfSteps( void ) const
{
    return m_stepCounter;
}

u1 AgentScheduler::check( void )
{
    u1 foundAtLeastOneDefinedAgent = false;

    const auto& programs = m_globalState.programState();
    const auto end = programs.end();
    for( auto it = programs.begin(); it != end; ++it )
    {
        const auto& location = it.key();
        const auto& value = it.value();

        const auto& agentId = location.arguments().at( 0 );

        if( value.defined() )
        {
            foundAtLeastOneDefinedAgent = true;
        }
    }

    if( not foundAtLeastOneDefinedAgent )
    {
        m_done = true;
    }

    return foundAtLeastOneDefinedAgent;
}

std::vector< Agent > AgentScheduler::collectAgents( void ) const
{
    std::vector< Agent > agents;

    const auto& programs = m_globalState.programState();
    const auto end = programs.end();
    for( auto it = programs.begin(); it != end; ++it )
    {
        const auto& location = it.key();
        const auto& value = it.value();

        const auto& agentId = location.arguments().at( 0 );

        assert( IR::isa< ReferenceConstant >( value ) );
        const auto& rule = static_cast< const ReferenceConstant& >( value );

        if( rule.defined() )
        {
            agents.emplace_back(
                m_locationRegistry, m_globalState, agentId, rule, symbolic(), m_environment );
        }
    }

    return agents;
}

void AgentScheduler::selectAgents( std::vector< Agent >& agents )
{
    assert( m_selectionStrategy && "agent selection strategy must be set" );
    m_selectionStrategy->selectAgents( agents );
}

void AgentScheduler::dispatch( std::vector< Agent >& agents )
{
    assert( m_dispatchStrategy );
    m_dispatchStrategy->dispatch( agents );
}

void AgentScheduler::collectUpdates( const std::vector< Agent >& agents )
{
    for( const auto& agent : agents )
    {
        try
        {
            agent.updateSet()->mergeInto( &m_collectedUpdates );
        }
        catch( const ExecutionUpdateSet::Conflict& conflict )
        {
            // existing
            const auto& updateA = conflict.existingUpdate();
            const auto updateStrA = ExecutionVisitor::updateAsString( updateA );
            const auto agentStrA = updateA.value.agent.name();
            const auto& sourceLocationA = updateA.value.producer->sourceLocation();

            // conflicting
            const auto& updateB = conflict.conflictingUpdate();
            const auto updateStrB = ExecutionVisitor::updateAsString( updateB );
            const auto agentStrB = updateB.value.agent.name();
            const auto& sourceLocationB = updateB.value.producer->sourceLocation();

            throw UpdateException(
                {},
                "Conflict while collection updates from agents. Update '" + updateStrA +
                    "' produced by agent " + agentStrA + " clashed with update '" + updateStrB +
                    "' produced by agent " + agentStrB,
                {},
                { ExecutionVisitor::updateAsUpdateInfo( updateA ), ExecutionVisitor::updateAsUpdateInfo( updateB ) },
                libcasm_fe::Code::UpdateSetMergeConflict );
        }
    }
}

void AgentScheduler::fireUpdates( void )
{
    m_globalState.fireUpdateSet( &m_collectedUpdates );
    m_collectedUpdates.clear();
}

