//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#include <libcasm-fe/ast/Node>

#include <libcasm-ir/Constant>

namespace libcasm_fe
{
    namespace Ast
    {
        class Type;
        class Literal;
        class Definition;
        class VariableDefinition;

        class Expression : public TypedPropertyNode
        {
          public:
            using Ptr = std::shared_ptr< Expression >;

            explicit Expression( Node::ID id );
        };

        using Expressions = NodeList< Expression >;

        class NamedExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< NamedExpression >;

            explicit NamedExpression(
                const Identifier::Ptr& identifier, const Expression::Ptr& expression );

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

            CallExpression( Node::ID id, const Expressions::Ptr& arguments );

            const Expressions::Ptr& arguments( void ) const;

          private:
            const Expressions::Ptr m_arguments;
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
                TYPE_DOMAIN,
                CONSTANT,
                VARIABLE,
                SELF,
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
             * Sets the builtin id of this call.
             *
             * @note Assigned by SymbolResolved and used during execution
             */
            void setTargetBuiltinId( libcasm_ir::Value::ID builtinId );
            libcasm_ir::Value::ID targetBuiltinId( void ) const;

            /**
             * Sets the definition of this call.
             *
             * @note Assigned by SymbolResolved and used during execution
             */
            void setTargetDefinition( const std::shared_ptr< Definition >& definition );
            const std::shared_ptr< Definition >& targetDefinition( void ) const;

            void accept( Visitor& visitor ) override;

            static std::string targetTypeString( const TargetType targetType );

          private:
            IdentifierPath::Ptr m_identifier;
            TargetType m_targetType;
            libcasm_ir::Value::ID m_targetBuiltinId;
            std::shared_ptr< Definition > m_targetDefinition;
        };

        class MethodCallExpression final : public CallExpression
        {
          public:
            enum class MethodType
            {
                FUNCTION,
                DERIVED,
                BUILTIN,
                RULE,
                UNKNOWN
            };

            using Ptr = std::shared_ptr< MethodCallExpression >;

            MethodCallExpression(
                const Expression::Ptr& object,
                const Identifier::Ptr& methodName,
                const Expressions::Ptr& arguments );

            const Expression::Ptr& object( void ) const;
            const Identifier::Ptr& methodName( void ) const;

            void setMethodType( MethodType methodType );
            MethodType methodType( void ) const;

            std::string methodTypeName( void ) const;

            /**
             * Sets the builtin id of this call.
             *
             * @note Assigned by SymbolResolved and used during execution
             */
            void setTargetBuiltinId( libcasm_ir::Value::ID builtinId );
            libcasm_ir::Value::ID targetBuiltinId( void ) const;

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
            MethodType m_methodType;
            libcasm_ir::Value::ID m_targetBuiltinId;
            std::shared_ptr< Definition > m_targetDefinition;
        };

        class LiteralCallExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< LiteralCallExpression >;

            LiteralCallExpression(
                const Expression::Ptr& object, const std::shared_ptr< Literal >& literal );

            const Expression::Ptr& object( void ) const;
            const std::shared_ptr< Literal >& literal( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_object;
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

          private:
            const Expression::Ptr m_expression;
        };

        class TypeCastingExpression final : public CallExpression
        {
          public:
            enum class CastingType
            {
                BUILTIN,
                UNKNOWN
            };

            using Ptr = std::shared_ptr< TypeCastingExpression >;

            TypeCastingExpression(
                const Expression::Ptr& fromExpression, const std::shared_ptr< Type >& asType );

            const Expression::Ptr& fromExpression( void ) const;

            const std::shared_ptr< Type >& asType( void ) const;

            void setCastingType( CastingType castingType );
            CastingType castingType( void ) const;
            std::string castingTypeName( void ) const;

            /**
             * Sets the builtin id of this call.
             *
             * @note Assigned by SymbolResolved and used during execution
             */
            void setTargetBuiltinId( libcasm_ir::Value::ID builtinId );
            libcasm_ir::Value::ID targetBuiltinId( void ) const;

            /**
             *     Sets the definition of this call.
             *
             *     @note Assigned by SymbolResolved and used during execution
             */
            void setTargetDefinition( const std::shared_ptr< Definition >& definition );
            const std::shared_ptr< Definition >& targetDefinition( void ) const;

            void accept( Visitor& visitor ) override;

          private:
            const Expression::Ptr m_fromExpression;
            const std::shared_ptr< Type > m_asType;
            CastingType m_castingType;
            libcasm_ir::Value::ID m_targetBuiltinId;
            std::shared_ptr< Definition > m_targetDefinition;
        };

        class UnaryExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< UnaryExpression >;

            UnaryExpression( const Expression::Ptr& expression, libcasm_ir::Value::ID op );

            libcasm_ir::Value::ID op( void ) const;
            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const libcasm_ir::Value::ID m_op;
            const Expression::Ptr m_expression;
        };

        class BinaryExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< BinaryExpression >;

            BinaryExpression(
                const Expression::Ptr& left,
                const Expression::Ptr& right,
                libcasm_ir::Value::ID op );

            libcasm_ir::Value::ID op( void ) const;
            const Expression::Ptr& left( void ) const;
            const Expression::Ptr& right( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const libcasm_ir::Value::ID m_op;
            const Expression::Ptr m_left;
            const Expression::Ptr m_right;
        };

        class LetExpression final : public Expression
        {
          public:
            using Ptr = std::shared_ptr< LetExpression >;

            LetExpression(
                const std::shared_ptr< VariableDefinition >& variable,
                const Expression::Ptr& initializer,
                const Expression::Ptr& expression );

            const std::shared_ptr< VariableDefinition >& variable( void ) const;
            const Expression::Ptr& initializer( void ) const;
            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< VariableDefinition > m_variable;
            const Expression::Ptr m_initializer;
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
                const std::shared_ptr< VariableDefinition >& variable,
                const Expression::Ptr& universe,
                const Expression::Ptr& expression );

            const std::shared_ptr< VariableDefinition >& variable( void ) const;
            const Expression::Ptr& universe( void ) const;
            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const std::shared_ptr< VariableDefinition > m_variable;
            const Expression::Ptr m_universe;
            const Expression::Ptr m_expression;
        };

        class QuantifierExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< QuantifierExpression >;

            QuantifierExpression(
                Node::ID id,
                const std::shared_ptr< VariableDefinition >& predicateVariable,
                const Expression::Ptr& universe,
                const Expression::Ptr& proposition );

            const std::shared_ptr< VariableDefinition >& predicateVariable( void ) const;
            const Expression::Ptr& universe( void ) const;
            const Expression::Ptr& proposition( void ) const;

          private:
            const std::shared_ptr< VariableDefinition > m_predicateVariable;
            const Expression::Ptr m_universe;
            const Expression::Ptr m_proposition;
        };

        class UniversalQuantifierExpression final : public QuantifierExpression
        {
          public:
            using Ptr = std::shared_ptr< UniversalQuantifierExpression >;

            UniversalQuantifierExpression(
                const std::shared_ptr< VariableDefinition >& predicateVariable,
                const Expression::Ptr& universe,
                const Expression::Ptr& proposition );

            void accept( Visitor& visitor ) override final;
        };

        class ExistentialQuantifierExpression final : public QuantifierExpression
        {
          public:
            using Ptr = std::shared_ptr< ExistentialQuantifierExpression >;

            ExistentialQuantifierExpression(
                const std::shared_ptr< VariableDefinition >& predicateVariable,
                const Expression::Ptr& universe,
                const Expression::Ptr& proposition );

            void accept( Visitor& visitor ) override final;
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
