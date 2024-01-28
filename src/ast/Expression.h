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

#ifndef _LIBCASM_FE_AST_EXPRESSION_H_
#define _LIBCASM_FE_AST_EXPRESSION_H_

#include <libcasm-fe/ast/Identifier>
#include <libcasm-fe/ast/Node>
#include <libcasm-fe/cst/Token>

namespace libcasm_fe
{
    namespace AST
    {
        class Type;
        class Literal;
        class Definition;
        class VariableDefinition;
        using VariableDefinitions = NodeList< VariableDefinition >;

        class Expression : public TypedPropertyNode
        {
          public:
            using Ptr = std::shared_ptr< Expression >;

            explicit Expression( Node::ID id );

          protected:
            void clone( Expression& duplicate ) const;
        };

        using Expressions = NodeList< Expression >;

        class AbstractExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< AbstractExpression >;

            explicit AbstractExpression( void );

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;
        };

        class NamedExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< NamedExpression >;

            explicit NamedExpression(
                const Identifier::Ptr& identifier, const Expression::Ptr& expression );

            const Identifier::Ptr& identifier( void ) const;

            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Identifier::Ptr m_identifier;
            const Expression::Ptr m_expression;
        };

        using NamedExpressions = NodeList< NamedExpression >;

        class MappedExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< MappedExpression >;

            MappedExpression( const Expressions::Ptr& arguments, const Expression::Ptr& value );

            const Expressions::Ptr& arguments( void ) const;

            const Expression::Ptr& value( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Expressions::Ptr m_arguments;
            const Expression::Ptr m_value;
        };

        using MappedExpressions = NodeList< MappedExpression >;

        class CallExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< CallExpression >;

            CallExpression( const Node::ID id, const Expressions::Ptr& arguments );

            const Expressions::Ptr& arguments( void ) const;

          protected:
            void clone( CallExpression& duplicate ) const;

          private:
            const Expressions::Ptr m_arguments;
        };

        class TargetCallExpression : public CallExpression
        {
          public:
            enum class TargetType
            {
                FUNCTION,
                DERIVED,
                BUILTIN,
                RULE,
                DOMAINTYPE,
                CONSTANT,
                VARIABLE,
                UNKNOWN
            };

            using Ptr = std::shared_ptr< TargetCallExpression >;

            TargetCallExpression(
                const Node::ID id,
                const Expressions::Ptr& arguments,
                const std::shared_ptr< VariableDefinitions >& templateSymbols );

            TargetCallExpression( const Node::ID id, const Expressions::Ptr& arguments );

            TargetCallExpression( const Node::ID id );

            const std::shared_ptr< VariableDefinitions >& templateSymbols( void ) const;

            void setTargetDefinition( const std::shared_ptr< Definition >& definition );

            const std::shared_ptr< Definition >& targetDefinition( void ) const;

            u1 hasTargetDefinition( void ) const;

            void setTargetType( TargetType targetType );

            TargetType targetType( void ) const;

            std::string targetTypeName( void ) const;
            static std::string targetTypeString( const TargetType targetType );

          protected:
            void clone( TargetCallExpression& duplicate ) const;

          private:
            const std::shared_ptr< VariableDefinitions > m_templateSymbols;
            std::shared_ptr< Definition > m_targetDefinition;
            TargetType m_targetType;
        };

        class DirectCallExpression final : public TargetCallExpression
        {
          public:
            using Ptr = std::shared_ptr< DirectCallExpression >;

            DirectCallExpression(
                const std::shared_ptr< VariableDefinitions >& templateSymbols,
                const IdentifierPath::Ptr& identifier,
                const Expressions::Ptr& arguments );

            DirectCallExpression(
                const IdentifierPath::Ptr& identifier, const Expressions::Ptr& arguments );

            DirectCallExpression( const IdentifierPath::Ptr& identifier );

            void setIdentifier( const IdentifierPath::Ptr& identifier );

            const IdentifierPath::Ptr& identifier( void ) const;

            void accept( Visitor& visitor ) override;

            Node::Ptr clone( void ) const override final;

          private:
            IdentifierPath::Ptr m_identifier;
        };

        class MethodCallExpression final : public TargetCallExpression
        {
          public:
            using Ptr = std::shared_ptr< MethodCallExpression >;

            MethodCallExpression(
                const Expression::Ptr& object,
                const Identifier::Ptr& methodName,
                const Expressions::Ptr& methodArguments );

            const Expression::Ptr& object( void ) const;

            const Identifier::Ptr& methodName( void ) const;

            const Expressions::Ptr& methodArguments( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Expression::Ptr m_object;
            const Identifier::Ptr m_methodName;
            const Expressions::Ptr m_methodArguments;
        };

        class LiteralCallExpression final : public TargetCallExpression
        {
          public:
            using Ptr = std::shared_ptr< LiteralCallExpression >;

            LiteralCallExpression(
                const Expression::Ptr& object, const std::shared_ptr< Literal >& literal );

            const Expression::Ptr& object( void ) const;

            const std::shared_ptr< Literal >& literal( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const std::shared_ptr< Literal > m_literal;
        };

        class IndirectCallExpression final : public CallExpression
        {
          public:
            using Ptr = std::shared_ptr< IndirectCallExpression >;

            IndirectCallExpression(
                const Expression::Ptr& expression, const Expressions::Ptr& arguments );

            const Expression::Ptr& expression( void ) const;

            bool isRuleCall( void ) const;

            bool isFunctionCall( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Expression::Ptr m_expression;
        };

        class TypeCastingExpression final : public TargetCallExpression
        {
          public:
            using Ptr = std::shared_ptr< TypeCastingExpression >;

            TypeCastingExpression(
                const Expression::Ptr& fromExpression, const std::shared_ptr< Type >& asType );

            const Expression::Ptr& fromExpression( void ) const;

            const std::shared_ptr< Type >& asType( void ) const;

            void accept( Visitor& visitor ) override;

            Node::Ptr clone( void ) const override final;

          private:
            const std::shared_ptr< Type > m_asType;
        };

        class UnaryExpression final : public TargetCallExpression
        {
          public:
            using Ptr = std::shared_ptr< UnaryExpression >;

            UnaryExpression(
                const Grammar::Token operationToken, const Expression::Ptr& expression );

            const Expression::Ptr& expression( void ) const;

            const Grammar::Token operationToken( void ) const;

            const std::string operationTokenString( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Grammar::Token m_operationToken;
        };

        class BinaryExpression final : public TargetCallExpression
        {
          public:
            using Ptr = std::shared_ptr< BinaryExpression >;

            BinaryExpression(
                const Expression::Ptr& left,
                const Grammar::Token operationToken,
                const Expression::Ptr& right );

            const Expression::Ptr& left( void ) const;

            const Expression::Ptr& right( void ) const;

            const Grammar::Token operationToken( void ) const;

            const std::string operationTokenString( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Grammar::Token m_operationToken;
        };

        class VariableBinding final : public TypedNode
        {
          public:
            using Ptr = std::shared_ptr< VariableBinding >;

            VariableBinding(
                const std::shared_ptr< VariableDefinition >& variable,
                const Expression::Ptr& expression );

            const std::shared_ptr< VariableDefinition >& variable( void ) const;
            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

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
                const VariableBindings::Ptr& variableBindings, const Expression::Ptr& expression );

            const VariableBindings::Ptr& variableBindings( void ) const;
            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const VariableBindings::Ptr m_variableBindings;
            const Expression::Ptr m_expression;
        };

        class ConditionalExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ConditionalExpression >;

            ConditionalExpression(
                const Expression::Ptr& condition,
                const Expression::Ptr& thenExpression,
                const Expression::Ptr& elseExpression );

            const Expression::Ptr& condition( void ) const;
            const Expression::Ptr& thenExpression( void ) const;
            const Expression::Ptr& elseExpression( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Expression::Ptr m_condition;
            const Expression::Ptr m_thenExpression;
            const Expression::Ptr m_elseExpression;
        };

        class VariableSelection final : public TypedNode
        {
          public:
            using Ptr = std::shared_ptr< VariableSelection >;

            VariableSelection(
                const std::shared_ptr< VariableDefinition >& variable,
                const Expression::Ptr& universe,
                const Expression::Ptr& condition );

            const std::shared_ptr< VariableDefinition >& variable( void ) const;
            const Expression::Ptr& universe( void ) const;
            const Expression::Ptr& condition( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const std::shared_ptr< VariableDefinition > m_variable;
            const Expression::Ptr m_universe;
            const Expression::Ptr m_condition;
        };

        using VariableSelections = NodeList< VariableSelection >;

        class ChooseExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ChooseExpression >;

            ChooseExpression(
                const VariableSelection::Ptr& variableSelection,
                const Expression::Ptr& expression );

            const VariableSelection::Ptr& variableSelection( void ) const;
            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const VariableSelection::Ptr m_variableSelection;
            const Expression::Ptr m_expression;
        };

        class QuantifierExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< QuantifierExpression >;

            QuantifierExpression(
                Node::ID id,
                const std::shared_ptr< VariableDefinitions >& predicateVariables,
                const Expression::Ptr& universe,
                const Expression::Ptr& proposition );

            const std::shared_ptr< VariableDefinitions >& predicateVariables( void ) const;
            const Expression::Ptr& universe( void ) const;
            const Expression::Ptr& proposition( void ) const;

          protected:
            void clone( QuantifierExpression& duplicate ) const;

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
                const std::shared_ptr< VariableDefinitions >& predicateVariables,
                const Expression::Ptr& universe,
                const Expression::Ptr& proposition );

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;
        };

        class ExistentialQuantifierExpression final : public QuantifierExpression
        {
          public:
            using Ptr = std::shared_ptr< ExistentialQuantifierExpression >;

            ExistentialQuantifierExpression(
                const std::shared_ptr< VariableDefinitions >& predicateVariables,
                const Expression::Ptr& universe,
                const Expression::Ptr& proposition );

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;
        };

        class CardinalityExpression final : public TargetCallExpression
        {
          public:
            using Ptr = std::shared_ptr< CardinalityExpression >;

            CardinalityExpression( const Expression::Ptr& expression );

            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;
        };
    }
}

#endif  // _LIBCASM_FE_AST_EXPRESSION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
