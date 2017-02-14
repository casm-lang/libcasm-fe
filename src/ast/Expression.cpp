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

using namespace libcasm_fe;
using namespace Ast;

Expression::Expression( Node::Type type )
: Node( type )
, m_type( nullptr )
{
}

void Expression::setType( const libcasm_ir::Type::Ptr& type )
{
    m_type = type;
}

libcasm_ir::Type::Ptr Expression::type() const
{
    return m_type;
}

ValueAtom::ValueAtom( const libcasm_ir::Value& value )
: Expression( Node::Type::VALUE_ATOM )
, m_value( value )
{
    // Expression::setType( value.type() ); FIXME enable this when ir uses
    // Type::Ptr!!
}

libcasm_ir::Value ValueAtom::value() const
{
    return m_value;
}

ZeroAtom::ZeroAtom()
: Expression( Node::Type::ZERO_ATOM )
{
}

UndefAtom::UndefAtom()
: Expression( Node::Type::UNDEF_ATOM )
{
}

void CallExpression::setTargetType( CallExpression::TargetType targetType )
{
    m_targetType = targetType;
}

CallExpression::TargetType CallExpression::targetType() const
{
    return m_targetType;
}

DirectCallExpression::DirectCallExpression(
    const IdentifierNode::Ptr& identifier, const Expressions::Ptr& arguments )
: CallExpression( Node::Type::DIRECT_CALL_EXPRESSION )
, m_identifier( identifier )
, m_arguments( arguments )
{
}

IdentifierNode::Ptr DirectCallExpression::identifier() const
{
    return m_identifier;
}

Expressions::Ptr DirectCallExpression::arguments() const
{
    return m_arguments;
}

IndirectCallExpression::IndirectCallExpression(
    const Expression::Ptr& expression, const Expressions::Ptr& arguments )
: CallExpression( Node::Type::INDIRECT_CALL_EXPRESSION )
, m_expression( expression )
, m_arguments( arguments )
{
}

Expression::Ptr IndirectCallExpression::expression() const
{
    return m_expression;
}

Expressions::Ptr IndirectCallExpression::arguments() const
{
    return m_arguments;
}

UnaryExpression::UnaryExpression(
    const Expression::Ptr& expression, libcasm_ir::Value::ID op )
: Expression( Node::Type::UNARY_EXPRESSION )
, m_op( op )
, m_expression( expression )
{
}

libcasm_ir::Value::ID UnaryExpression::op() const
{
    return m_op;
}

Expression::Ptr UnaryExpression::expression() const
{
    return m_expression;
}

BinaryExpression::BinaryExpression( const Expression::Ptr& left,
    const Expression::Ptr& right, libcasm_ir::Value::ID op )
: Expression( Node::Type::BINARY_EXPRESSION )
, m_op( op )
, m_left( left )
, m_right( right )
{
}

libcasm_ir::Value::ID BinaryExpression::op() const
{
    return m_op;
}

Expression::Ptr BinaryExpression::left() const
{
    return m_left;
}

Expression::Ptr BinaryExpression::right() const
{
    return m_right;
}

RangeExpression::RangeExpression(
    const Expression::Ptr& left, const Expression::Ptr& right )
: Expression( Node::Type::RANGE_EXPRESSION )
, m_left( left )
, m_right( right )
{
}

Expression::Ptr RangeExpression::left() const
{
    return m_left;
}

Expression::Ptr RangeExpression::right() const
{
    return m_right;
}

ListExpression::ListExpression( const Expressions::Ptr& expressions )
: Expression( Node::Type::LIST_EXPRESSION )
, m_expressions( expressions )
{
}

Expressions::Ptr ListExpression::expressions() const
{
    return m_expressions;
}
