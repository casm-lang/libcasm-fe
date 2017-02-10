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

DirectCallExpression::DirectCallExpression(
    const std::string& identifier, const Expressions::Ptr& arguments )
: Expression( Node::Type::DIRECT_CALL_EXPRESSION )
, m_identifier( identifier )
, m_arguments( arguments )
, m_targetType( TargetType::Unknown )
{
}

std::string DirectCallExpression::identifier() const
{
    return m_identifier;
}

Expressions::Ptr DirectCallExpression::arguments() const
{
    return m_arguments;
}

void DirectCallExpression::setTargetType(
    DirectCallExpression::TargetType targetType )
{
    m_targetType = targetType;
}

DirectCallExpression::TargetType DirectCallExpression::targetType() const
{
    return m_targetType;
}

IndirectCallExpression::IndirectCallExpression(
    const Expression::Ptr& expression, const Expressions::Ptr& arguments )
: Expression( Node::Type::INDIRECT_CALL_EXPRESSION )
, m_expression( expression )
, m_arguments( arguments )
, m_targetType( TargetType::Unknown )
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

void IndirectCallExpression::setTargetType(
    IndirectCallExpression::TargetType targetType )
{
    m_targetType = targetType;
}

IndirectCallExpression::TargetType IndirectCallExpression::targetType() const
{
    return m_targetType;
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
