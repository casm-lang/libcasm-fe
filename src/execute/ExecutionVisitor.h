//
//  Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#ifndef _LIBCASM_FE_EXECUTION_VISITOR_H_
#define _LIBCASM_FE_EXECUTION_VISITOR_H_

#include <libcasm-fe/Codes>
#include <libcasm-fe/Specification>
#include <libcasm-fe/execute/Frame>
#include <libcasm-fe/execute/FunctionState>
#include <libcasm-fe/execute/LocationRegistry>
#include <libcasm-fe/execute/ReferenceConstant>
#include <libcasm-fe/execute/Stack>
#include <libcasm-fe/execute/UpdateException>
#include <libcasm-fe/execute/UpdateSet>
#include <libcasm-fe/lst/Definition>
#include <libcasm-fe/lst/Visitor>

#include <libstdhl/Enum>
#include <libstdhl/Hash>
#include <libstdhl/Random>

namespace libcasm_fe
{
    namespace IR = libcasm_ir;

    class ConstantStack : public Stack< IR::Constant >
    {
      public:
        using Stack::Stack;

        using Stack::pop;

        template < typename T >
        T pop( void )
        {
            const auto value = Stack::pop();
            assert( IR::isa< T >( value ) );
            return static_cast< const T& >( value );
        }
    };

    struct ConstantsHash
    {
        inline std::size_t operator()( const std::vector< IR::Constant >& constants ) const
        {
            return libstdhl::Hash::value( constants );
        }
    };

    /**
     * @brief Represents an update
     */
    struct Update
    {
        IR::Constant value;  /**< The value of the update */
        LST::Node* producer; /**< The update producer */
        IR::Constant agent;  /**< The contributing agent */
                             // TODO maybe a list of agents (multi-agent case)?
    };

    struct UpdateEquals : public std::binary_function< const Update&, const Update&, bool >
    {
        bool operator()( const Update& lhs, const Update& rhs ) const
        {
            return lhs.value == rhs.value;
        }
    };

    struct LocationRegistryDetails
    {
        using Function = LST::FunctionDefinition*;
        using FunctionHash = std::hash< Function >;
        using FunctionEquals = std::equal_to< Function >;
        using Arguments = std::vector< IR::Constant >;
        using ArgumentsHash = ConstantsHash;
        using ArgumentsEquals = std::equal_to< Arguments >;
    };

    using ExecutionLocationRegistry = LocationRegistry< LocationRegistryDetails >;

    struct UpdateSetDetails
    {
        using Location = ExecutionLocationRegistry::Location;
        using Value = Update;
        using LocationHash = ExecutionLocationRegistry::LocationHash;
        using LocationEquals = ExecutionLocationRegistry::LocationEquals;
        using ValueEquals = UpdateEquals;
    };

    using ExecutionUpdateSet = UpdateSet< UpdateSetDetails >;
    using Transaction = UpdateSetTransaction< ExecutionUpdateSet >;
    using Semantics = ExecutionUpdateSet::Semantics;

    class Storage
    {
        using Location = ExecutionLocationRegistry::Location;
        using Value = IR::Constant;

        struct FunctionStateDetails
        {
            using Location = Storage::Location;
            using Value = Storage::Value;
            using LocationHash = ExecutionLocationRegistry::LocationHash;
            using LocationEquals = ExecutionLocationRegistry::LocationEquals;
        };

        using ExecutionFunctionState = FunctionState< FunctionStateDetails >;

      public:
        Storage( void );

        void fireUpdateSet( ExecutionUpdateSet* updateSet );

        void set( const Location& location, const Value& value );
        void remove( const Location& location );
        libstdhl::Optional< Value > get( const Location& location ) const;

        const ExecutionFunctionState& programState( void ) const;

      private:
        /**
         * Program function state is stored separately to allow efficient iteration
         * over all program locations (e.g. when determining the set of runnable
         * agents).
         */
        ExecutionFunctionState m_programState;
        ExecutionFunctionState m_functionState;
    };

    class ExecutionVisitor : public LST::Visitor
    {
      public:
        ExecutionVisitor(
            ExecutionLocationRegistry& locationRegistry,
            Storage& globalState,
            UpdateSetManager< ExecutionUpdateSet >& updateSetManager,
            const IR::Constant& agentId );

        /**
         * Executes the rule reference stored in \a value.
         *
         * @note It only support rules without arguments.
         *
         * @param value Rule reference (must be defined and the literal reference type
         *        must be RULE)
         */
        void execute( const ReferenceConstant& value );

        void execute( const LST::Definition::Ptr& definition );

        void visit( LST::Root& node ) override;

        void visit( LST::VariableDefinition& node ) override;
        void visit( LST::FunctionDefinition& node ) override;
        void visit( LST::DerivedDefinition& node ) override;
        void visit( LST::RuleDefinition& node ) override;
        void visit( LST::EnumeratorDefinition& node ) override;
        void visit( LST::EnumerationDefinition& node ) override;
        void visit( LST::InvariantDefinition& node ) override;
        void visit( LST::DomainDefinition& node ) override;
        void visit( LST::BuiltinDefinition& node ) override;

        void visit( LST::ValueLiteral& node ) override;
        void visit( LST::ReferenceLiteral& node ) override;
        void visit( LST::SetLiteral& node ) override;
        void visit( LST::ListLiteral& node ) override;
        void visit( LST::RangeLiteral& node ) override;
        void visit( LST::TupleLiteral& node ) override;
        void visit( LST::RecordLiteral& node ) override;

        void visit( LST::NamedExpression& node ) override;
        void visit( LST::DirectCallExpression& node ) override;
        void visit( LST::IndirectCallExpression& node ) override;
        void visit( LST::LetExpression& node ) override;
        void visit( LST::ConditionalExpression& node ) override;
        void visit( LST::ChooseExpression& node ) override;
        void visit( LST::UniversalQuantifierExpression& node ) override;
        void visit( LST::ExistentialQuantifierExpression& node ) override;

        void visit( LST::SkipRule& node ) override;
        void visit( LST::ConditionalRule& node ) override;
        void visit( LST::CaseRule& node ) override;
        void visit( LST::LetRule& node ) override;
        void visit( LST::LocalRule& node ) override;
        void visit( LST::ForallRule& node ) override;
        void visit( LST::ChooseRule& node ) override;
        void visit( LST::IterateRule& node ) override;
        void visit( LST::BlockRule& node ) override;
        void visit( LST::SequenceRule& node ) override;
        void visit( LST::UpdateRule& node ) override;
        void visit( LST::CallRule& node ) override;

        void visit( LST::VariableBinding& node ) override;
        void visit( LST::ExpressionCase& node ) override;
        void visit( LST::DefaultCase& node ) override;
        void visit( LST::Identifier& node ) override;
        void visit( LST::IdentifierPath& node ) override;

        static std::string updateAsString( const ExecutionUpdateSet::Update& update );
        static UpdateException::UpdateInfo updateAsUpdateInfo(
            const ExecutionUpdateSet::Update& update );

      protected:
        u1 hasEmptyUpdateSet( void ) const;

        std::unique_ptr< Frame > makeFrame(
            LST::CallExpression* call, LST::Node* callee, std::size_t numberOfLocals );

        std::unique_ptr< Frame > makeObjectFrame(
            const IR::Constant& object,
            LST::CallExpression* call,
            LST::Node* callee,
            std::size_t numberOfLocals );

        enum class ValidationFlag
        {
            ValueMustBeDefined,
        };
        using ValidationFlags = libstdhl::Enum::Flags< ValidationFlag >;

        /**
         * Checks if the \a value is correct, i.e. if it complies to the \a type
         * specification.
         *
         * @param value The value whose correcteness should be checked
         * @param type The specified type
         * @param flags Disables or enables various validation properties
         *
         * @throws libcasm_IR::ValidationException in case of an invalid value
         */
        void validateValue(
            const IR::Constant& value, const IR::Type& type, ValidationFlags flags = {} ) const;

        /**
         * Validates the arguments, i.e. if the values comply to the argument types
         * \a argumentTypes.
         *
         * It uses the locals of the current frame as argument values.
         *
         * @param node The LST node in whose context the validation is performed
         *             (used for the error location and stack trace generation)
         * @param argumentTypes A list of arguments types used for the validation
         * @param flags Disables or enables various validation properties
         * @param errorCode Defines the error code which should be applied to the
         *                  exception in case of a validation error
         *
         * @throws RuntimeException in case of an invalid argument value with proper
         *                          error and location information
         */
        void validateArguments(
            const LST::Node& node,
            const IR::Types& argumentTypes,
            ValidationFlags flags,
            Code errorCode ) const;

        void handleMergeConflict(
            const LST::Node& node, const ExecutionUpdateSet::Conflict& conflict ) const;

        void foreachInUniverse(
            const LST::VariableDefinitions& variables,
            const IR::Constant& universe,
            const std::function< void() >& subRule ) const;

      protected:
        Storage& m_globalState;
        ExecutionLocationRegistry& m_locationRegistry;
        UpdateSetManager< ExecutionUpdateSet >& m_updateSetManager;
        const IR::Constant& m_agentId;

        ConstantStack m_evaluationStack;
        FrameStack m_frameStack;

        bool m_evaluateUpdateLocation; /**< Controls if FunctionDefinition visit should evaluate the
                                          update location or perform a normal function call */
        ExecutionLocationRegistry::Location m_updateLocation;
    };

    class StateInitializationVisitor final : public LST::EmptyVisitor
    {
      public:
        StateInitializationVisitor(
            ExecutionLocationRegistry& locationRegistry, Storage& globalState );

        void visit( Specification& node );
        void visit( LST::FunctionDefinition& node ) override;

      private:
        Storage& m_globalState;
        ExecutionLocationRegistry& m_locationRegistry;
        UpdateSetManager< ExecutionUpdateSet > m_updateSetManager;
    };

    class InvariantChecker
    {
      public:
        InvariantChecker( ExecutionLocationRegistry& locationRegistry, Storage& globalState );

        void check( const Specification& specification );

      private:
        Storage& m_globalState;
        ExecutionLocationRegistry& m_locationRegistry;
    };
    class SymbolicExecutionVisitor final : public ExecutionVisitor
    {
      private:
        Stack< libtptp::Node::Ptr > m_stack;

      public:
        SymbolicExecutionVisitor(
            ExecutionLocationRegistry& locationRegistry,
            Storage& globalState,
            UpdateSetManager< ExecutionUpdateSet >& updateSetManager,
            const IR::Constant& agentId,
            IR::SymbolicExecutionEnvironment& environment );

        void visit( LST::FunctionDefinition& node ) override;

        void visit( LST::DirectCallExpression& node ) override;
        // void visit( LST::MethodCallExpression& node ) override;
        // void visit( LST::LiteralCallExpression& node ) override;
        void visit( LST::IndirectCallExpression& node ) override;
        // void visit( LST::UnaryExpression& node ) override;
        // void visit( LST::BinaryExpression& node ) override;
        void visit( LST::LetExpression& node ) override;
        void visit( LST::ConditionalExpression& node ) override;
        void visit( LST::ChooseExpression& node ) override;
        void visit( LST::UniversalQuantifierExpression& node ) override;
        void visit( LST::ExistentialQuantifierExpression& node ) override;
        // void visit( LST::CardinalityExpression& node ) override;

        void visit( LST::ConditionalRule& node ) override;
        void visit( LST::CaseRule& node ) override;
        void visit( LST::ForallRule& node ) override;
        void visit( LST::ChooseRule& node ) override;
        void visit( LST::IterateRule& node ) override;
        void visit( LST::BlockRule& node ) override;
        void visit( LST::SequenceRule& node ) override;
        void visit( LST::UpdateRule& node ) override;
        // void visit( LST::WhileRule& node ) override;

      private:
        IR::SymbolicExecutionEnvironment& m_environment;

        IR::SymbolicExecutionEnvironment& environment();
    };

    class SymbolicStateInitializationVisitor final : public LST::EmptyVisitor
    {
      public:
        SymbolicStateInitializationVisitor(
            ExecutionLocationRegistry& locationRegistry,
            Storage& globalState,
            IR::SymbolicExecutionEnvironment& environment );

        void visit( Specification& node );
        // void visit( LST::InitDefinition& node ) override;
        void visit( LST::FunctionDefinition& node ) override;

      private:
        Storage& m_globalState;
        ExecutionLocationRegistry& m_locationRegistry;
        IR::SymbolicExecutionEnvironment& m_environment;
        UpdateSetManager< ExecutionUpdateSet > m_updateSetManager;
    };

}

#endif  // _LIBCASM_FE_EXECUTION_VISITOR_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
