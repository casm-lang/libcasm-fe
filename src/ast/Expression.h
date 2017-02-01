//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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

namespace libcasm_fe
{
    namespace Ast
    {
        class Expression : public Node
        {
          public:
            using Ptr = std::shared_ptr< Expression >;

            Expression( Node::Type type );

            void setType( libcasm_ir::Type* type );
            libcasm_ir::Type* type() const;

          private:
            libcasm_ir::Type* m_type;
        };

        using Expressions = NodeList< Expression >;

        class Atom : public Expression
        {
          public:
            using Ptr = std::shared_ptr< Atom >;

            Atom( const libcasm_ir::Value& value );

            libcasm_ir::Value value() const;

          private:
            libcasm_ir::Value m_value;
        };

        // TODO port FunctionAtom, RuleAtom, BuiltinAtom

        class UnaryExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< UnaryExpression >;

            UnaryExpression(
                const Expression::Ptr& expression, libcasm_ir::Value::ID id );

            libcasm_ir::Value::ID id() const;
            Expression::Ptr expression() const;

          private:
            libcasm_ir::Value::ID m_id;
            Expression::Ptr m_expression;
        };

        class BinaryExpression : public Expression
        {
          public:
            using Ptr = std::shared_ptr< BinaryExpression >;

            BinaryExpression( const Expression::Ptr& left,
                const Expression::Ptr& right, libcasm_ir::Value::ID id );

            libcasm_ir::Value::ID id() const;
            Expression::Ptr left() const;
            Expression::Ptr right() const;

          private:
            libcasm_ir::Value::ID m_id;
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
