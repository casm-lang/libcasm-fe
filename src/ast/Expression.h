//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
//                https://github.com/casm-lang/libcasm-fe
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

#ifndef _LIB_CASMFE_EXPRESSION_H_
#define _LIB_CASMFE_EXPRESSION_H_

#include "Node.h"

#include "../../casm-ir/src/Constant.h"

namespace libcasm_fe
{
    namespace Ast
    {
        class VariableDefinition;

        class Expression : public TypedNode
        {
          public:
            using Ptr = std::shared_ptr< Expression >;

            explicit Expression( Node::ID id );
        };

        using Expressions = NodeList< Expression >;

        class ValueAtom : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ValueAtom >;

            explicit ValueAtom( const libcasm_ir::Constant::Ptr& value );

            libcasm_ir::Constant::Ptr value( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            libcasm_ir::Constant::Ptr m_value;
        };

        class ReferenceAtom : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ReferenceAtom >;

            explicit ReferenceAtom( const IdentifierPath::Ptr& identifier );

            IdentifierPath::Ptr identifier( void ) const;

            void setReference( const TypedNode::Ptr& reference );
            TypedNode::Ptr reference( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            IdentifierPath::Ptr m_identifier;
            TypedNode::Ptr m_reference;
        };

        class UndefAtom : public Expression
        {
          public:
            using Ptr = std::shared_ptr< UndefAtom >;

            explicit UndefAtom( void );

            void accept( Visitor& visitor ) override final;
        };

        class CallExpression : public Expression
        {
          public:
            enum class TargetType
            {
                FUNCTION,
                DERIVED,
                BUILTIN,
                RULE,
                ENUMERATION,
                CONSTANT,
                VARIABLE,
                UNKNOWN
            };

            using Ptr = std::shared_ptr< CallExpression >;

            CallExpression( Node::ID id, const Expressions::Ptr& arguments );

            Expressions::Ptr arguments( void ) const;

            void setTargetType( TargetType targetType );
            TargetType targetType( void ) const;

            std::string targetTypeName( void ) const;

          private:
            Expressions::Ptr m_arguments;
            TargetType m_targetType = TargetType::UNKNOWN;

          public:
            static std::string targetTypeString( const TargetType targetType );
        };

        class DirectCallExpression : public CallExpression
        {
          public:
            using Ptr = std::shared_ptr< DirectCallExpression >;

            DirectCallExpression( const IdentifierPath::Ptr& identifier,
                const Expressions::Ptr& arguments );

            void setIdentifier( const IdentifierPath::Ptr& identifier );
            IdentifierPath::Ptr identifier( void ) const;

            /**
             * Sets the id of the target.
             *
             * Functions, deriveds, builtins, rules, ... may be stored in a
             * flat list, thus the target id may correspond to the list index.
             *
             * Variables may be stored in frames, thus the target id may
             * correspond to the local index.
             *
             * @note Assigned by SymbolResolved and used during execution
             */
            void setTargetId( std::size_t targetId );
            std::size_t targetId( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            IdentifierPath::Ptr m_identifier;
            std::size_t m_targetId;
        };

        class IndirectCallExpression : public CallExpression
        {
          public:
            using Ptr = std::shared_ptr< IndirectCallExpression >;

            IndirectCallExpression( const Expression::Ptr& expression,
                const Expressions::Ptr& arguments );

            Expression::Ptr expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Expression::Ptr m_expression;
        };

        class UnaryExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< UnaryExpression >;

            UnaryExpression(
                const Expression::Ptr& expression, libcasm_ir::Value::ID op );

            libcasm_ir::Value::ID op( void ) const;
            Expression::Ptr expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            libcasm_ir::Value::ID m_op;
            Expression::Ptr m_expression;
        };

        class BinaryExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< BinaryExpression >;

            BinaryExpression( const Expression::Ptr& left,
                const Expression::Ptr& right, libcasm_ir::Value::ID op );

            libcasm_ir::Value::ID op( void ) const;
            Expression::Ptr left( void ) const;
            Expression::Ptr right( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            libcasm_ir::Value::ID m_op;
            Expression::Ptr m_left;
            Expression::Ptr m_right;
        };

        class RangeExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< RangeExpression >;

            RangeExpression(
                const Expression::Ptr& left, const Expression::Ptr& right );

            Expression::Ptr left( void ) const;
            Expression::Ptr right( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Expression::Ptr m_left;
            Expression::Ptr m_right;
        };

        class ListExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ListExpression >;

            explicit ListExpression( const Expressions::Ptr& expressions );

            Expressions::Ptr expressions( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Expressions::Ptr m_expressions;
        };

        class ConditionalExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ConditionalExpression >;

            ConditionalExpression( const Expression::Ptr& condition,
                const Expression::Ptr& thenExpression,
                const Expression::Ptr& elseExpression );

            Expression::Ptr condition( void ) const;
            Expression::Ptr thenExpression( void ) const;
            Expression::Ptr elseExpression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Expression::Ptr m_condition;
            Expression::Ptr m_thenExpression;
            Expression::Ptr m_elseExpression;
        };

        class QuantifierExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< QuantifierExpression >;

            QuantifierExpression( Node::ID id,
                const std::shared_ptr< VariableDefinition >& predicateVariable,
                const Expression::Ptr& universe,
                const Expression::Ptr& proposition );

            std::shared_ptr< VariableDefinition > predicateVariable(
                void ) const;
            Expression::Ptr universe( void ) const;
            Expression::Ptr proposition( void ) const;

          private:
            std::shared_ptr< VariableDefinition > m_predicateVariable;
            Expression::Ptr m_universe;
            Expression::Ptr m_proposition;
        };

        class UniversalQuantifierExpression : public QuantifierExpression
        {
          public:
            using Ptr = std::shared_ptr< UniversalQuantifierExpression >;

            UniversalQuantifierExpression(
                const std::shared_ptr< VariableDefinition >& predicateVariable,
                const Expression::Ptr& universe,
                const Expression::Ptr& proposition );

            void accept( Visitor& visitor ) override final;
        };

        class ExistentialQuantifierExpression : public QuantifierExpression
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

#endif // _LIB_CASMFE_EXPRESSION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
