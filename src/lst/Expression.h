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

#ifndef _LIBCASM_FE_LST_EXPRESSION_H_
#define _LIBCASM_FE_LST_EXPRESSION_H_

#include <libcasm-fe/lst/Identifier>
#include <libcasm-fe/lst/Node>

#include <libcasm-fe/ast/Expression>

namespace libcasm_fe
{
    namespace LST
    {
        class Type;
        class Literal;
        class Definition;
        class VariableDefinition;
        using VariableDefinitions = NodeList< VariableDefinition >;

        class Expression : public Node
        {
          public:
            using Ptr = std::shared_ptr< Expression >;

            explicit Expression(
                const Node::ID id,
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties );
        };

        using Expressions = NodeList< Expression >;

        class NamedExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< NamedExpression >;

            explicit NamedExpression(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Identifier::Ptr& identifier,
                const Expression::Ptr& expression );

            const Identifier::Ptr& identifier( void ) const;

            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Identifier::Ptr m_identifier;
            const Expression::Ptr m_expression;
        };

        using NamedExpressions = NodeList< NamedExpression >;

        class CallExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< CallExpression >;

            CallExpression(
                const Node::ID id,
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Expressions::Ptr& arguments,
                const std::shared_ptr< Definition >& targetDefinition );

            const Expressions::Ptr& arguments( void ) const;

            const std::shared_ptr< Definition >& targetDefinition( void ) const;

          private:
            const Expressions::Ptr m_arguments;
            const std::shared_ptr< Definition > m_targetDefinition;
        };

        class DirectCallExpression final : public CallExpression
        {
          public:
            using TargetType = AST::DirectCallExpression::TargetType;

            using Ptr = std::shared_ptr< DirectCallExpression >;

            DirectCallExpression(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Expressions::Ptr& arguments,
                const std::shared_ptr< Definition >& targetDefinition,
                const TargetType targetType );

            TargetType targetType( void ) const;

            std::string targetTypeName( void ) const;

            void accept( Visitor& visitor ) override;

          private:
            const TargetType m_targetType;
        };

        class IndirectCallExpression final : public CallExpression
        {
          public:
            using Ptr = std::shared_ptr< IndirectCallExpression >;

            IndirectCallExpression(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Expressions::Ptr& arguments,
                const std::shared_ptr< Definition >& targetDefinition,
                const Expression::Ptr& expression );

            const Expression::Ptr& expression( void ) const;

            bool isRuleCall( void ) const;

            bool isFunctionCall( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_expression;
        };

        class VariableBinding final : public Node
        {
          public:
            using Ptr = std::shared_ptr< VariableBinding >;

            VariableBinding(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const std::shared_ptr< VariableDefinition >& variable,
                const Expression::Ptr& expression );

            const std::shared_ptr< VariableDefinition >& variable( void ) const;

            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< VariableDefinition > m_variable;
            const Expression::Ptr m_expression;
        };

        using VariableBindings = NodeList< VariableBinding >;

        class LetExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< LetExpression >;

            LetExpression(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const VariableBindings::Ptr& variableBindings,
                const Expression::Ptr& expression );

            const VariableBindings::Ptr& variableBindings( void ) const;

            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const VariableBindings::Ptr m_variableBindings;
            const Expression::Ptr m_expression;
        };

        class ConditionalExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ConditionalExpression >;

            ConditionalExpression(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Expression::Ptr& condition,
                const Expression::Ptr& thenExpression,
                const Expression::Ptr& elseExpression );

            const Expression::Ptr& condition( void ) const;

            const Expression::Ptr& thenExpression( void ) const;

            const Expression::Ptr& elseExpression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_condition;
            const Expression::Ptr m_thenExpression;
            const Expression::Ptr m_elseExpression;
        };

        class ChooseExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ChooseExpression >;

            ChooseExpression(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const std::shared_ptr< VariableDefinitions >& variables,
                const Expression::Ptr& universe,
                const Expression::Ptr& expression );

            const std::shared_ptr< VariableDefinitions >& variables( void ) const;

            const Expression::Ptr& universe( void ) const;

            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< VariableDefinitions > m_variables;
            const Expression::Ptr m_universe;
            const Expression::Ptr m_expression;
        };

        class QuantifierExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< QuantifierExpression >;

            QuantifierExpression(
                const Node::ID id,
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const std::shared_ptr< VariableDefinitions >& predicateVariables,
                const Expression::Ptr& universe,
                const Expression::Ptr& proposition );

            const std::shared_ptr< VariableDefinitions >& predicateVariables( void ) const;

            const Expression::Ptr& universe( void ) const;

            const Expression::Ptr& proposition( void ) const;

          private:
            const std::shared_ptr< VariableDefinitions > m_predicateVariables;
            const Expression::Ptr m_universe;
            const Expression::Ptr m_proposition;
        };

        class UniversalQuantifierExpression final : public QuantifierExpression
        {
          public:
            using Ptr = std::shared_ptr< UniversalQuantifierExpression >;

            UniversalQuantifierExpression(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const std::shared_ptr< VariableDefinitions >& predicateVariables,
                const Expression::Ptr& universe,
                const Expression::Ptr& proposition );

            void accept( Visitor& visitor ) override final;
        };

        class ExistentialQuantifierExpression final : public QuantifierExpression
        {
          public:
            using Ptr = std::shared_ptr< ExistentialQuantifierExpression >;

            ExistentialQuantifierExpression(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const std::shared_ptr< VariableDefinitions >& predicateVariables,
                const Expression::Ptr& universe,
                const Expression::Ptr& proposition );

            void accept( Visitor& visitor ) override final;
        };
    }
}

#endif  // _LIBCASM_FE_LST_EXPRESSION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
