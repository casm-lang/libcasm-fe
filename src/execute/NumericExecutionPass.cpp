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

#include "NumericExecutionPass.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/execute/RuntimeException>
#include <libcasm-fe/execute/UpdateException>

#include <libcasm-fe/execute/Agent>
#include <libcasm-fe/execute/ExecutionVisitor>

#include <libcasm-fe/analyze/FrameSizeDeterminationPass>
#include <libcasm-fe/import/SpecificationMergerPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/String>

#include <mutex>

using namespace libcasm_fe;
using namespace Ast;

char NumericExecutionPass::id = 0;

static libpass::PassRegistration< NumericExecutionPass > PASS(
    "NumericExecutionPass", "execute numerically over the AST input specification", "ast-exec", 0 );

void NumericExecutionPass::usage( libpass::PassUsage& pu )
{
    pu.require< SpecificationMergerPass >();
    pu.scheduleAfter< FrameSizeDeterminationPass >();
}

static std::string updateInfoToString( const UpdateException::UpdateInfo& updateInfo )
{
    auto locationStr = updateInfo.function->identifier()->name();

    if( not updateInfo.arguments.empty() )
    {
        locationStr += "(";
        bool isFirst = true;
        for( const auto& arg : updateInfo.arguments )
        {
            if( not isFirst )
            {
                locationStr += ", ";
            }
            locationStr += arg.name();
            isFirst = false;
        }
        locationStr += ")";
    }

    return locationStr + " := " + updateInfo.value.name();
}

u1 NumericExecutionPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SpecificationMergerPass >();
    const auto specification = data->specification();

    static u1 constantHandlerFlag = false;
    static std::mutex constantHandlerLock;
    static auto constantHandlerInitialization = []() {
        std::lock_guard< std::mutex > guard( constantHandlerLock );
        if( not constantHandlerFlag )
        {
            auto constantHandler = std::make_unique< ConstantHandler >();
            IR::ConstantHandlerManager::instance().registerConstantHandler(
                std::move( constantHandler ) );
            constantHandlerFlag = true;
        }
    };
    constantHandlerInitialization();

    ExecutionLocationRegistry locationRegistry;
    Storage globalState;

    AgentScheduler scheduler( locationRegistry, globalState, false );
    /*scheduler.setDispatchStrategy(
        libstdhl::Memory::make_unique< ParallelDispatchStrategy >() );*/

    switch( specification->asmType() )
    {
        case Specification::AsmType::SYNCHRONOUS:
        {
            scheduler.setAgentSelectionStrategy(
                libstdhl::Memory::make_unique< AllAgentsSelectionStrategy >() );
            break;
        }
        case Specification::AsmType::ASYNCHRONOUS:
        {
            scheduler.setAgentSelectionStrategy(
                libstdhl::Memory::make_unique< SingleRandomAgentSelectionStrategy >() );
            break;
        }
    }

    try
    {
        StateInitializationVisitor stateInitializationVisitor( locationRegistry, globalState );
        stateInitializationVisitor.visit( *specification );

        InvariantChecker invariantChecker( locationRegistry, globalState );
        invariantChecker.check( *specification );

        if( not scheduler.check() )
        {
            log.warning(
                { specification->header()->sourceLocation() },
                "no init definition found in this specification" );
        }

        while( not scheduler.done() )
        {
            scheduler.step();
            invariantChecker.check( *specification );
        }

        if( scheduler.numberOfSteps() == 0 )
        {
            log.warning(
                { specification->header()->sourceLocation() },
                "Could not perform a single step because no agent was initially available. This "
                "may happen when no valid initial rule has been specified (see InitRule)." );
        }

        log.info(
            "Finished execution after " + std::to_string( scheduler.numberOfSteps() ) + " steps" );
    }
    catch( const UpdateException& e )
    {
        log.error( e );
        log.info( "Backtrace:\n" + libstdhl::String::join( e.backtrace(), "\n" ) );
        for( const auto& update : e.updateInfos() )
        {
            log.info(
                { update.producer->sourceLocation() },
                "Produced update '" + updateInfoToString( update ) + "'" );
        }
        return false;
    }
    catch( const RuntimeException& e )
    {
        log.error( e );
        log.info( "Backtrace:\n" + libstdhl::String::join( e.backtrace(), "\n" ) );
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
