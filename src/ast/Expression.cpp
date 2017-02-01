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

#include "Expression.h"

#include "../../casm-ir/src/Type.h"

using namespace libcasm_fe;
using namespace Ast;

Expression::Expression( Node::Type type )
: Node( type )
, m_type( nullptr )
{
}

void Expression::setType( libcasm_ir::Type* type )
{
    m_type = type;
}

libcasm_ir::Type* Expression::type() const
{
    return m_type;
}

Atom::Atom( const libcasm_ir::Value& value )
: Expression( Node::Type::ATOM )
, m_value( value )
{
    Expression::setType( &value.type() );
}

libcasm_ir::Value Atom::value() const
{
    return m_value;
}

UnaryExpression::UnaryExpression(
    const Expression::Ptr& expression, libcasm_ir::Value::ID id )
: Expression( Node::Type::UNARY_EXPRESSION )
, m_expression( expression )
{
}

libcasm_ir::Value::ID UnaryExpression::id() const
{
    return m_id;
}

Expression::Ptr UnaryExpression::expression() const
{
    return m_expression;
}

BinaryExpression::BinaryExpression( const Expression::Ptr& left,
    const Expression::Ptr& right, libcasm_ir::Value::ID id )
: Expression( Node::Type::BINARY_EXPRESSION )
, m_id( id )
, m_left( left )
, m_right( right )
{
}

libcasm_ir::Value::ID BinaryExpression::id() const
{
    return m_id;
}

Expression::Ptr BinaryExpression::left() const
{
    return m_left;
}

Expression::Ptr BinaryExpression::right() const
{
    return m_right;
}
