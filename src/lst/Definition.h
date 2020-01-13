//
//  Copyright (C) 2014-2020 CASM Organization <https://casm-lang.org>
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

#ifndef _LIBCASM_FE_LST_DEFINITION_H_
#define _LIBCASM_FE_LST_DEFINITION_H_

#include <libcasm-fe/lst/Node>
#include <libcasm-fe/lst/Rule>

#include <libcasm-fe/cst/Definition>

#include <libcasm-ir/Value>

namespace libcasm_fe
{
    namespace LST
    {
        class Expression;
        using Expressions = NodeList< Expression >;

        class Definition : public Node
        {
          public:
            using Ptr = std::shared_ptr< Definition >;

            Definition(
                const Node::ID id,
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Identifier::Ptr& identifier,
                const std::size_t maxNumberOfLocals );

            const Identifier::Ptr& identifier( void ) const;

            std::size_t maximumNumberOfLocals( void ) const;

          private:
            const Identifier::Ptr m_identifier;
            const std::size_t m_maxNumberOfLocals;
        };

        using Definitions = NodeList< Definition >;

        class VariableDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< VariableDefinition >;

            VariableDefinition(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Identifier::Ptr& identifier,
                const std::size_t maxNumberOfLocals,
                const std::size_t localIndex );

            std::size_t localIndex( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::size_t m_localIndex;
        };

        using VariableDefinitions = NodeList< VariableDefinition >;

        class FunctionDefinition final : public Definition
        {
          public:
            using Classification = CST::FunctionDefinition::Classification;

          public:
            using Ptr = std::shared_ptr< FunctionDefinition >;

            FunctionDefinition(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Identifier::Ptr& identifier,
                const std::size_t maxNumberOfLocals,
                const Expression::Ptr& defined,
                const SequenceRule::Ptr& initially,
                const u1 symbolic,
                const u1 program,
                const u1 local );

            const Expression::Ptr& defined( void ) const;

            const SequenceRule::Ptr& initially( void ) const;

            u1 symbolic( void ) const;

            u1 program( void ) const;

            u1 local( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_defined;
            const SequenceRule::Ptr m_initially;
            const u1 m_symbolic;
            const u1 m_program;
            const u1 m_local;
        };

        using FunctionDefinitions = NodeList< FunctionDefinition >;

        class DerivedDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< DerivedDefinition >;

            DerivedDefinition(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Identifier::Ptr& identifier,
                const std::size_t maxNumberOfLocals,
                const VariableDefinitions::Ptr& arguments,
                const Expression::Ptr& expression );

            const VariableDefinitions::Ptr& arguments( void ) const;

            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const VariableDefinitions::Ptr m_arguments;
            const Expression::Ptr m_expression;
        };

        class RuleDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< RuleDefinition >;

            RuleDefinition(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Identifier::Ptr& identifier,
                const std::size_t maxNumberOfLocals,
                const VariableDefinitions::Ptr& arguments,
                const Rule::Ptr& rule );

            const NodeList< VariableDefinition >::Ptr& arguments( void ) const;

            const Rule::Ptr& rule( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const VariableDefinitions::Ptr m_arguments;
            const Rule::Ptr m_rule;
        };

        class EnumeratorDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< EnumeratorDefinition >;

            EnumeratorDefinition(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Identifier::Ptr& identifier,
                const std::size_t maxNumberOfLocals );

            void accept( Visitor& visitor ) override final;
        };

        using Enumerators = NodeList< EnumeratorDefinition >;

        class EnumerationDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< EnumerationDefinition >;

            EnumerationDefinition(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Identifier::Ptr& identifier,
                const std::size_t maxNumberOfLocals,
                const Enumerators::Ptr& enumerators );

            const Enumerators::Ptr& enumerators( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Enumerators::Ptr m_enumerators;
        };

        class InvariantDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< InvariantDefinition >;

            InvariantDefinition(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Identifier::Ptr& identifier,
                const std::size_t maxNumberOfLocals,
                const Expression::Ptr& expression );

            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override;

          private:
            const Expression::Ptr m_expression;
        };

        class DomainDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< DomainDefinition >;

            DomainDefinition(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Identifier::Ptr& identifier,
                const std::size_t maxNumberOfLocals );

            void accept( Visitor& visitor ) override final;
        };

        class BuiltinDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< BuiltinDefinition >;

            BuiltinDefinition(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Identifier::Ptr& identifier,
                const std::size_t maxNumberOfLocals,
                const libcasm_ir::Value::ID targetId );

            libcasm_ir::Value::ID targetId( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const libcasm_ir::Value::ID m_targetId;
        };
    }
}

#endif  // _LIBCASM_FE_LST_DEFINITION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
