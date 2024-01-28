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

#ifndef _LIBCASM_FE_SYMBOLIC_CONSISTENCY_VISITOR_H_
#define _LIBCASM_FE_SYMBOLIC_CONSISTENCY_VISITOR_H_

#include <libcasm-fe/Exception>
#include <libcasm-fe/Logger>
#include <libcasm-fe/Specification>
#include <libcasm-fe/lst/Literal>
#include <libcasm-fe/lst/Node>
#include <libcasm-fe/lst/Visitor>

#include <libcasm-fe/execute/ExecutionVisitor>
#include <libcasm-fe/execute/Stack>

#include <libcasm-ir/Constant>
#include <memory>
#include <stdexcept>
#include <vector>

namespace libcasm_fe
{
    namespace IR = libcasm_ir;

    class SymbolicConsistencyVisitor : public LST::EmptyVisitor
    {
      public:
        enum class FunctionType
        {
            UNKNOWN,
            NUMERIC,
            SYMBOLIC,
        };

        enum class Context
        {
            PLAIN,
            CONDITIONAL,
        };

        class BuiltinRule
        {
          public:
            BuiltinRule(
                const std::vector< IR::Value::ID > ids,
                int nargs,
                const std::function< FunctionType( const std::vector< FunctionType >& ) >
                    function );

            FunctionType evaluate( const std::vector< FunctionType >& ) const;
            bool contains( const IR::Value::ID& ) const;

          private:
            const std::vector< IR::Value::ID > m_ids;
            const int m_nargs;
            const std::function< FunctionType( const std::vector< FunctionType >& ) > m_function;
        };

        using FrameStack = Stack< FunctionType >;
        using ContextStack = Stack< Context >;

        class RuleDependency : std::enable_shared_from_this< RuleDependency >
        {
          public:
            enum class Status : int
            {
                INIT = 0,       // initial status
                STARTED = 1,    // rule evaluation has started, but was aborted
                EVALUATED = 2,  // rule was fully evaluated, unknown updates possible
                FINISHED = 3,   // rule was fully evaluated and defined, no unknown updates
            };

            using Ptr = std::shared_ptr< RuleDependency >;

            RuleDependency( const LST::RuleDefinition::Ptr& rule );

            const LST::RuleDefinition::Ptr& rule( void ) const;
            std::set< RuleDependency::Ptr >& dependsOn( void );
            std::set< RuleDependency::Ptr >& usedBy( void );
            void calls( RuleDependency::Ptr& callee );
            void isCalledBy( RuleDependency::Ptr& caller, std::vector< FunctionType >& args );
            FunctionType returns( void );
            bool fullyDefined( void ) const;
            void define( void );
            const std::vector< FunctionType >& arguments() const;
            FunctionType argumentAt( const size_t index ) const;

            Status status( void ) const;
            void setStatus( Status status );
            bool inStatus( std::vector< Status > status ) const;

            friend bool operator==( LST::RuleDefinition::Ptr&, RuleDependency::Ptr& );

          private:
            const LST::RuleDefinition::Ptr m_rule;
            std::set< RuleDependency::Ptr > m_dependsOn;
            std::set< RuleDependency::Ptr > m_usedBy;
            FunctionType m_returns;
            std::vector< FunctionType > m_arguments;
            Status m_status;
        };

        class Abort : std::logic_error
        {
          public:
            explicit Abort( void );
        };

        class Frame
        {
          public:
            using Ptr = std::shared_ptr< Frame >;
            Frame( LST::Node* callee, std::size_t numberOfLocals );
            LST::Node* callee( void ) const;

            void setLocal( std::size_t index, FunctionType function );
            FunctionType local( std::size_t index );
            std::vector< FunctionType >& locals( void );

          private:
            LST::Node* m_callee;
            std::vector< FunctionType > m_locals;
        };

      public:
        class Conflict : public Exception
        {
          public:
            enum class Cause
            {
                UPDATE,
                CALLED,
                CONDITION,
            };
            explicit Conflict(
                const LST::FunctionDefinition::Ptr& function,
                const std::vector< libstdhl::SourceLocation >& locations,
                Cause cause );

            LST::FunctionDefinition::Ptr& conflictingFunction( void );

          private:
            explicit Conflict(
                const std::string& msg,
                const LST::FunctionDefinition::Ptr& function,
                const std::vector< libstdhl::SourceLocation >& locations,
                Cause cause );

            static std::string description(
                const LST::FunctionDefinition::Ptr& function, Cause cause );
            static std::string causeDescription( Cause cause );

          private:
            LST::FunctionDefinition::Ptr m_function;
            Cause m_cause;
        };

        SymbolicConsistencyVisitor( Logger& logger );

        void visit( Specification& specification );

        // void visit( LST::Initially& node ) override;

        // void visit( LST::Initializer& node ) override;
        void visit( LST::VariableDefinition& node ) override;
        void visit( LST::FunctionDefinition& node ) override;
        void visit( LST::DerivedDefinition& node ) override;
        void visit( LST::RuleDefinition& node ) override;
        void visit( LST::EnumeratorDefinition& node ) override;
        void visit( LST::InvariantDefinition& node ) override;

        // void visit( LST::UndefLiteral& node ) override;
        void visit( LST::ValueLiteral& node ) override;
        void visit( LST::ReferenceLiteral& node ) override;
        void visit( LST::ListLiteral& node ) override;
        void visit( LST::RangeLiteral& node ) override;
        void visit( LST::TupleLiteral& node ) override;
        void visit( LST::RecordLiteral& node ) override;

        // void visit( LST::BasicType& node ) override;

        // void visit( LST::EmbracedExpression& node ) override;
        void visit( LST::NamedExpression& node ) override;
        void visit( LST::DirectCallExpression& node ) override;
        // void visit( LST::MethodCallExpression& node ) override;
        // void visit( LST::LiteralCallExpression& node ) override;
        void visit( LST::IndirectCallExpression& node ) override;
        // void visit( LST::TypeCastingExpression& node ) override;
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
        void visit( LST::LetRule& node ) override;
        void visit( LST::LocalRule& node ) override;
        void visit( LST::ForallRule& node ) override;
        void visit( LST::ChooseRule& node ) override;
        void visit( LST::IterateRule& node ) override;
        void visit( LST::BlockRule& node ) override;
        void visit( LST::SequenceRule& node ) override;
        void visit( LST::UpdateRule& node ) override;
        void visit( LST::CallRule& node ) override;
        // void visit( LST::WhileRule& node ) override;

        void visit( LST::VariableBinding& node ) override;

        friend FunctionType operator&&( const FunctionType, const FunctionType );

      private:
        /**
         * creates either a conditional or plain context, depending on the type of the conditon
         * - if it is called in a conditional context, a conditional context is created, no matter
         * the condition
         * - if the condition is unknown, execution is aborted
         * - if condition is unknown and creation is forced due to enabling assumption, a
         * conditional context is created and false is returned
         *
         * @param condition type of the condition
         * @returns false if creation is forced and type is unknown, true otherwise
         * @throws Abort if condition is unknown and cration is not forced
         */
        bool createContext( const FunctionType condition );
        FunctionType callRule(
            const LST::RuleDefinition::Ptr& rule, std::vector< FunctionType > args );
        RuleDependency::Ptr findOrInsert( const LST::RuleDefinition::Ptr& rule );
        template < class T >
        FunctionType typeOfList( const T& list );
        template < class T >
        std::vector< FunctionType > toTypeList( const T& list );
        bool done( void ) const;
        RuleDependency::Ptr nextRule( void );

      private:
        Logger& m_logger;
        std::set< RuleDependency::Ptr > m_dependencies;
        FrameStack m_stack;
        ContextStack m_context;
        bool m_forceContextCreation;
        bool m_unknownUpdate;
        bool m_evaluateUpdateLocation;
        LST::FunctionDefinition::Ptr m_updateLocation;
        LST::RuleDefinition::Ptr m_currentRule;
        Frame::Ptr m_frame;
        std::vector< BuiltinRule > m_builtins;

      public:
    };

    class SCStateInitializationVisitor final : public LST::EmptyVisitor
    {
      public:
        SCStateInitializationVisitor(
            ExecutionLocationRegistry& locationRegistry, Storage& globalState, Logger& logger );

        void visit( Specification& node );
        // void visit( LST::InitDefinition& node ) override;
        void visit( LST::FunctionDefinition& node ) override;

      private:
        Storage& m_globalState;
        ExecutionLocationRegistry& m_locationRegistry;
        UpdateSetManager< ExecutionUpdateSet > m_updateSetManager;
        Logger& m_logger;
    };
}

#endif  // _LIBCASM_FE_SYMBOLIC_CONSISTENCY_VISITOR_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
