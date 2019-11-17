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

#ifndef _LIBCASM_FE_EXPRESSION_H_
#define _LIBCASM_FE_EXPRESSION_H_

#include <libcasm-fe/ast/Identifier>
#include <libcasm-fe/ast/Node>
#include <libcasm-fe/ast/Token>
#include <libcasm-ir/Constant>

namespace libcasm_fe
{
    namespace Ast
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

            void setDelimiterToken( const Token::Ptr& delimiterToken );
            const Token::Ptr& delimiterToken( void ) const;

          private:
            Token::Ptr m_delimiterToken;
        };

        using Expressions = NodeList< Expression >;

        class EmbracedExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< EmbracedExpression >;

            explicit EmbracedExpression(
                const Token::Ptr& leftBraceToken,
                const Expression::Ptr& expression,
                const Token::Ptr& rightBraceToken );

            const Expression::Ptr& expression( void ) const;

            const Token::Ptr& leftBraceToken( void ) const;

            const Token::Ptr& rightBraceToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_expression;
            const Token::Ptr m_leftBraceToken;
            const Token::Ptr m_rightBraceToken;
        };

        class NamedExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< NamedExpression >;

            explicit NamedExpression(
                const Identifier::Ptr& identifier,
                const Token::Ptr& colonToken,
                const Expression::Ptr& expression );

            const Identifier::Ptr& identifier( void ) const;

            const Expression::Ptr& expression( void ) const;

            const Token::Ptr& colonToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Identifier::Ptr m_identifier;
            const Expression::Ptr m_expression;
            const Token::Ptr m_colonToken;
        };

        using NamedExpressions = NodeList< NamedExpression >;

        class CallExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< CallExpression >;

            CallExpression( const Node::ID id, const Expressions::Ptr& arguments );

            const Expressions::Ptr& arguments( void ) const;

            void setLeftBracketToken( const Token::Ptr& leftBracketToken );
            const Token::Ptr& leftBracketToken( void ) const;

            void setRightBracketToken( const Token::Ptr& rightBracketToken );
            const Token::Ptr& rightBracketToken( void ) const;

          private:
            const Expressions::Ptr m_arguments;
            Token::Ptr m_leftBracketToken;
            Token::Ptr m_rightBracketToken;
        };

        class DirectCallExpression : public CallExpression
        {
          public:
            enum class TargetType
            {
                FUNCTION,
                DERIVED,
                BUILTIN,
                RULE,
                DOMAIN,
                CONSTANT,
                VARIABLE,
                SELF,
                THIS,
                UNKNOWN
            };

            using Ptr = std::shared_ptr< DirectCallExpression >;

            DirectCallExpression(
                const IdentifierPath::Ptr& identifier, const Expressions::Ptr& arguments );

            void setIdentifier( const IdentifierPath::Ptr& identifier );
            const IdentifierPath::Ptr& identifier( void ) const;

            void setTargetType( TargetType targetType );
            TargetType targetType( void ) const;

            std::string targetTypeName( void ) const;

            /**
               Sets the definition of this call.

               @note Assigned by SymbolResolved and used during execution
             */
            void setTargetDefinition( const std::shared_ptr< Definition >& definition );
            const std::shared_ptr< Definition >& targetDefinition( void ) const;

            void accept( Visitor& visitor ) override;

            static std::string targetTypeString( const TargetType targetType );

          private:
            IdentifierPath::Ptr m_identifier;
            TargetType m_targetType;
            std::shared_ptr< Definition > m_targetDefinition;
        };

        class MethodCallExpression final : public CallExpression
        {
          public:
            enum class MethodType
            {
                FUNCTION,
                DERIVED,
                RULE,
                UNKNOWN
            };

            using Ptr = std::shared_ptr< MethodCallExpression >;

            MethodCallExpression(
                const Expression::Ptr& object,
                const Token::Ptr& dotToken,
                const Identifier::Ptr& methodName,
                const Expressions::Ptr& arguments );

            const Expression::Ptr& object( void ) const;
            const Identifier::Ptr& methodName( void ) const;

            const Token::Ptr& dotToken( void ) const;

            void setMethodType( MethodType methodType );
            MethodType methodType( void ) const;

            std::string methodTypeName( void ) const;

            /**
             *     Sets the definition of this call.
             *
             *     @note Assigned by SymbolResolved and used during execution
             */
            void setTargetDefinition( const std::shared_ptr< Definition >& definition );
            const std::shared_ptr< Definition >& targetDefinition( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Expression::Ptr m_object;
            Identifier::Ptr m_methodName;
            const Token::Ptr m_dotToken;
            MethodType m_methodType;
            std::shared_ptr< Definition > m_targetDefinition;
        };

        class LiteralCallExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< LiteralCallExpression >;

            LiteralCallExpression(
                const Expression::Ptr& object,
                const Token::Ptr& dotToken,
                const std::shared_ptr< Literal >& literal );

            const Expression::Ptr& object( void ) const;
            const std::shared_ptr< Literal >& literal( void ) const;

            const Token::Ptr& dotToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_object;
            const std::shared_ptr< Literal > m_literal;
            const Token::Ptr m_dotToken;
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

          private:
            const Expression::Ptr m_expression;
        };

        class TypeCastingExpression final : public CallExpression
        {
          public:
            using Ptr = std::shared_ptr< TypeCastingExpression >;

            TypeCastingExpression(
                const Expression::Ptr& fromExpression,
                const Token::Ptr& asToken,
                const std::shared_ptr< Type >& asType );

            const Expression::Ptr& fromExpression( void ) const;

            const std::shared_ptr< Type >& asType( void ) const;

            const Token::Ptr& asToken( void ) const;

            void setTargetDefinition( const std::shared_ptr< Definition >& definition );

            const std::shared_ptr< Definition >& targetDefinition( void ) const;

            void accept( Visitor& visitor ) override;

          private:
            const std::shared_ptr< Type > m_asType;
            const Token::Ptr m_asToken;
            std::shared_ptr< Definition > m_targetDefinition;
        };

        class UnaryExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< UnaryExpression >;

            UnaryExpression(
                const Token::Ptr& operationToken,
                const Expression::Ptr& expression,
                libcasm_ir::Value::ID op );

            libcasm_ir::Value::ID op( void ) const;
            const Expression::Ptr& expression( void ) const;
            const Token::Ptr& operationToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const libcasm_ir::Value::ID m_op;
            const Expression::Ptr m_expression;
            const Token::Ptr m_operationToken;
        };

        class BinaryExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< BinaryExpression >;

            BinaryExpression(
                const Expression::Ptr& left,
                const Token::Ptr& operationToken,
                const Expression::Ptr& right,
                const libcasm_ir::Value::ID op );

            libcasm_ir::Value::ID op( void ) const;
            const Expression::Ptr& left( void ) const;
            const Expression::Ptr& right( void ) const;
            const Token::Ptr& operationToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const libcasm_ir::Value::ID m_op;
            const Expression::Ptr m_left;
            const Expression::Ptr m_right;
            const Token::Ptr m_operationToken;
        };

        class VariableBinding : public Node
        {
          public:
            using Ptr = std::shared_ptr< VariableBinding >;

            VariableBinding(
                const std::shared_ptr< VariableDefinition >& variable,
                const Token::Ptr& equalToken,
                const Expression::Ptr& expression );

            const std::shared_ptr< VariableDefinition >& variable( void ) const;
            const Expression::Ptr& expression( void ) const;

            const Token::Ptr& equalToken( void ) const;

            void setDelimiterToken( const Token::Ptr& delimiterToken );
            const Token::Ptr& delimiterToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< VariableDefinition > m_variable;
            const Expression::Ptr m_expression;
            const Token::Ptr m_equalToken;
            Token::Ptr m_delimiterToken;
        };

        using VariableBindings = NodeList< VariableBinding >;

        class LetExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< LetExpression >;

            LetExpression(
                const Token::Ptr& letToken,
                const VariableBindings::Ptr& variableBindings,
                const Token::Ptr& inToken,
                const Expression::Ptr& expression );

            const VariableBindings::Ptr& variableBindings( void ) const;
            const Expression::Ptr& expression( void ) const;

            const Token::Ptr& letToken( void ) const;

            const Token::Ptr& inToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const VariableBindings::Ptr m_variableBindings;
            const Expression::Ptr m_expression;
            const Token::Ptr m_letToken;
            const Token::Ptr m_inToken;
        };

        class ConditionalExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ConditionalExpression >;

            ConditionalExpression(
                const Token::Ptr& ifToken,
                const Expression::Ptr& condition,
                const Token::Ptr& thenToken,
                const Expression::Ptr& thenExpression,
                const Token::Ptr& elseToken,
                const Expression::Ptr& elseExpression );

            const Expression::Ptr& condition( void ) const;
            const Expression::Ptr& thenExpression( void ) const;
            const Expression::Ptr& elseExpression( void ) const;

            const Token::Ptr& ifToken( void ) const;

            const Token::Ptr& thenToken( void ) const;

            const Token::Ptr& elseToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_condition;
            const Expression::Ptr m_thenExpression;
            const Expression::Ptr m_elseExpression;
            const Token::Ptr m_ifToken;
            const Token::Ptr m_thenToken;
            const Token::Ptr m_elseToken;
        };

        class ChooseExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ChooseExpression >;

            ChooseExpression(
                const Token::Ptr& chooseToken,
                const std::shared_ptr< VariableDefinitions >& variables,
                const Token::Ptr& inToken,
                const Expression::Ptr& universe,
                const Token::Ptr& doToken,
                const Expression::Ptr& expression );

            const Token::Ptr& chooseToken( void ) const;

            const Token::Ptr& inToken( void ) const;

            const Token::Ptr& doToken( void ) const;

            const std::shared_ptr< VariableDefinitions >& variables( void ) const;
            const Expression::Ptr& universe( void ) const;
            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< VariableDefinitions > m_variables;
            const Expression::Ptr m_universe;
            const Expression::Ptr m_expression;
            const Token::Ptr m_chooseToken;
            const Token::Ptr m_inToken;
            const Token::Ptr m_doToken;
        };

        class QuantifierExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< QuantifierExpression >;

            QuantifierExpression(
                Node::ID id,
                const Token::Ptr& quantifierToken,
                const std::shared_ptr< VariableDefinitions >& predicateVariables,
                const Token::Ptr& inToken,
                const Expression::Ptr& universe,
                const Token::Ptr& doToken,
                const Expression::Ptr& proposition );

            const std::shared_ptr< VariableDefinitions >& predicateVariables( void ) const;
            const Expression::Ptr& universe( void ) const;
            const Expression::Ptr& proposition( void ) const;

            const Token::Ptr& quantifierToken( void ) const;

            const Token::Ptr& inToken( void ) const;

            const Token::Ptr& doToken( void ) const;

          private:
            const std::shared_ptr< VariableDefinitions > m_predicateVariables;
            const Expression::Ptr m_universe;
            const Expression::Ptr m_proposition;
            const Token::Ptr m_quantifierToken;
            const Token::Ptr m_inToken;
            const Token::Ptr m_doToken;
        };

        class UniversalQuantifierExpression final : public QuantifierExpression
        {
          public:
            using Ptr = std::shared_ptr< UniversalQuantifierExpression >;

            UniversalQuantifierExpression(
                const Token::Ptr& forallToken,
                const std::shared_ptr< VariableDefinitions >& predicateVariables,
                const Token::Ptr& inToken,
                const Expression::Ptr& universe,
                const Token::Ptr& holdsToken,
                const Expression::Ptr& proposition );

            void accept( Visitor& visitor ) override final;
        };

        class ExistentialQuantifierExpression final : public QuantifierExpression
        {
          public:
            using Ptr = std::shared_ptr< ExistentialQuantifierExpression >;

            ExistentialQuantifierExpression(
                const Token::Ptr& existsToken,
                const std::shared_ptr< VariableDefinitions >& predicateVariables,
                const Token::Ptr& inToken,
                const Expression::Ptr& universe,
                const Token::Ptr& withToken,
                const Expression::Ptr& proposition );

            void accept( Visitor& visitor ) override final;
        };

        class CardinalityExpression final : public CallExpression
        {
          public:
            using Ptr = std::shared_ptr< CardinalityExpression >;

            enum class CardinalityType
            {
                BUILTIN,
                UNKNOWN
            };

            CardinalityExpression(
                const Token::Ptr& leftVerticalBarToken,
                const Expression::Ptr& expression,
                const Token::Ptr& rightVerticalBarToken );

            const Expression::Ptr& expression( void ) const;

            const Token::Ptr& leftVerticalBarToken( void ) const;
            const Token::Ptr& rightVerticalBarToken( void ) const;

            void setCardinalityType( CardinalityType cardinalityType );
            CardinalityType cardinalityType( void ) const;
            std::string cardinalityTypeName( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_expression;
            const Token::Ptr m_leftVerticalBarToken;
            const Token::Ptr m_rightVerticalBarToken;
            CardinalityType m_cardinalityType;
        };
    }
}

#endif  // _LIBCASM_FE_EXPRESSION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
