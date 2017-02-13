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

#include "../../casm-ir/src/Type.h"
#include "../../casm-ir/src/Value.h"

namespace libcasm_fe
{
    namespace Ast
    {
        class Expression : public Node
        {
          public:
            using Ptr = std::shared_ptr< Expression >;

            Expression( Node::Type type );

            void setType( const libcasm_ir::Type::Ptr& type );
            libcasm_ir::Type::Ptr type() const;

          private:
            libcasm_ir::Type::Ptr m_type;
        };

        using Expressions = NodeList< Expression >;

        class ValueAtom : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ValueAtom >;

            ValueAtom( const libcasm_ir::Value& value );

            libcasm_ir::Value value() const;

          private:
            libcasm_ir::Value m_value;
        };

        class ZeroAtom : public Expression
        {
          public:
            using Ptr = std::shared_ptr< ZeroAtom >;

            ZeroAtom();
        };

        class UndefAtom : public Expression
        {
          public:
            using Ptr = std::shared_ptr< UndefAtom >;

            UndefAtom();
        };

        class CallExpression : public Expression
        {
          public:
            enum class TargetType
            {
                Function,
                Derived,
                Builtin,
                Rule,
                Variable,
                Unknown
            };

          public:
            using Ptr = std::shared_ptr< CallExpression >;

            using Expression::Expression;

            void setTargetType( TargetType targetType );
            TargetType targetType() const;

          private:
            TargetType m_targetType = TargetType::Unknown;
        };

        class DirectCallExpression : public CallExpression
        {
          public:
            using Ptr = std::shared_ptr< DirectCallExpression >;

            DirectCallExpression( const IdentifierNode::Ptr& identifier,
                const Expressions::Ptr& arguments );

            IdentifierNode::Ptr identifier() const;
            Expressions::Ptr arguments() const;

          private:
            IdentifierNode::Ptr m_identifier;
            Expressions::Ptr m_arguments;
        };

        class IndirectCallExpression : public CallExpression
        {
          public:
            using Ptr = std::shared_ptr< IndirectCallExpression >;

            IndirectCallExpression( const Expression::Ptr& expression,
                const Expressions::Ptr& arguments );

            Expression::Ptr expression() const;
            Expressions::Ptr arguments() const;

          private:
            Expression::Ptr m_expression;
            Expressions::Ptr m_arguments;
        };

        class UnaryExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< UnaryExpression >;

            UnaryExpression(
                const Expression::Ptr& expression, libcasm_ir::Value::ID op );

            libcasm_ir::Value::ID op() const;
            Expression::Ptr expression() const;

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

            libcasm_ir::Value::ID op() const;
            Expression::Ptr left() const;
            Expression::Ptr right() const;

          private:
            libcasm_ir::Value::ID m_op;
            Expression::Ptr m_left;
            Expression::Ptr m_right;
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
