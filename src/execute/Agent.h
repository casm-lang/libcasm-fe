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

#ifndef _LIBCASM_FE_AGENT_H
#define _LIBCASM_FE_AGENT_H

#include <libcasm-fe/Codes>
#include <libcasm-fe/Specification>
#include <libcasm-fe/ast/Definition>
#include <libcasm-fe/ast/EmptyVisitor>
#include <libcasm-fe/execute/ExecutionVisitor>
#include <libcasm-fe/execute/Frame>
#include <libcasm-fe/execute/FunctionState>
#include <libcasm-fe/execute/LocationRegistry>
#include <libcasm-fe/execute/ReferenceConstant>
#include <libcasm-fe/execute/Stack>
#include <libcasm-fe/execute/SymbolicExecutionPass>
#include <libcasm-fe/execute/UpdateSet>

#include <libstdhl/Enum>
#include <libstdhl/Hash>
#include <libstdhl/Random>

namespace libcasm_fe
{
    namespace IR = libcasm_ir;
    class Agent
    {
      public:
        Agent(
            ExecutionLocationRegistry& locationRegistry,
            Storage& globalState,
            const IR::Constant& agentId,
            const ReferenceConstant& rule,
            bool symbolic,
            libstdhl::Optional< IR::SymbolicExecutionEnvironment* > environment );

        void run( void );

        ExecutionUpdateSet* updateSet( void ) const;

        void setSymbolicEnvironment( IR::SymbolicExecutionEnvironment& environment );

        bool symbolic( void ) const;

      private:
        Storage& m_globalState;
        ExecutionLocationRegistry& m_locationRegistry;
        const IR::Constant& m_agentId;
        const ReferenceConstant& m_rule;
        UpdateSetManager< ExecutionUpdateSet > m_updateSetManager;
        const bool m_symbolic;
        libstdhl::Optional< IR::SymbolicExecutionEnvironment* > m_environment;
    };

    class DispatchStrategy
    {
      public:
        virtual ~DispatchStrategy() = default;

        virtual void dispatch( std::vector< Agent >& agents ) = 0;
    };

    class ParallelDispatchStrategy : public DispatchStrategy
    {
      public:
        void dispatch( std::vector< Agent >& agents ) override;
    };

    class SequentialDispatchStrategy : public DispatchStrategy
    {
      public:
        void dispatch( std::vector< Agent >& agents ) override;
    };

    class SelectionStrategy
    {
      public:
        virtual ~SelectionStrategy() = default;

        /**
         * Selects the agents from \a agents which should be executed, by removing
         * all agents which should not be executed.
         *
         * @param agents List of available agents
         */
        virtual void selectAgents( std::vector< Agent >& agents ) const = 0;
    };

    class AllAgentsSelectionStrategy final : public SelectionStrategy
    {
      public:
        void selectAgents( std::vector< Agent >& agents ) const override;
    };

    class SingleRandomAgentSelectionStrategy final : public SelectionStrategy
    {
      public:
        void selectAgents( std::vector< Agent >& agents ) const override;
    };

    class AgentScheduler
    {
      public:
        AgentScheduler(
            ExecutionLocationRegistry& locationRegistry, Storage& globalState, bool symbolic );

        void setDispatchStrategy( std::unique_ptr< DispatchStrategy > dispatchStrategy );
        void setAgentSelectionStrategy( std::unique_ptr< SelectionStrategy > selectionStrategy );
        void setSymbolicEnvironment( IR::SymbolicExecutionEnvironment& environment );

        u1 check( void );

        /**
         * Performs an ASM step.
         */
        void step( void );

        /**
         * @return A boolean value indicating wheter the ASM has reached an end
         *         state, meaning that no further steps need to be done.
         */
        bool done( void ) const;

        bool symbolic( void ) const;

        std::size_t numberOfSteps( void ) const;

      private:
        std::vector< Agent > collectAgents( void ) const;
        void selectAgents( std::vector< Agent >& agents );
        void dispatch( std::vector< Agent >& agents );
        void collectUpdates( const std::vector< Agent >& agents );
        void fireUpdates( void );

      private:
        std::unique_ptr< DispatchStrategy > m_dispatchStrategy;
        std::unique_ptr< SelectionStrategy > m_selectionStrategy;
        Storage& m_globalState;
        ExecutionLocationRegistry& m_locationRegistry;
        ParallelUpdateSet< UpdateSetDetails > m_collectedUpdates;
        bool m_done;
        const bool m_symbolic;
        std::size_t m_stepCounter;
        libstdhl::Optional< IR::SymbolicExecutionEnvironment* > m_environment;
    };

}

#endif  // _LIBCASM_FE_AGENT_H

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
