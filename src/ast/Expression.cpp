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

#include "Definition.h"

using namespace libcasm_fe;
using namespace Ast;

Expression::Expression( Node::ID id )
: Node( id )
, m_type( nullptr )
{
}

void Expression::setType( const libcasm_ir::Type::Ptr& type )
{
    m_type = type;
}

libcasm_ir::Type::Ptr Expression::type( void ) const
{
    return m_type;
}

ValueAtom::ValueAtom( const libcasm_ir::Value::Ptr& value )
: Expression( Node::ID::VALUE_ATOM )
, m_value( value )
{
    Expression::setType( value->ptr_type() );
}

libcasm_ir::Value::Ptr ValueAtom::value( void ) const
{
    return m_value;
}

void ValueAtom::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

RuleReferenceAtom::RuleReferenceAtom( const IdentifierNode::Ptr& identifier )
: Expression( Node::ID::RULE_REFERENCE_ATOM )
, m_identifier( identifier )
, m_ruleReference( nullptr )
{
    Expression::setType( libstdhl::get< libcasm_ir::RuleReferenceType >() );
}

IdentifierNode::Ptr RuleReferenceAtom::identifier() const
{
    return m_identifier;
}

void RuleReferenceAtom::setRuleReference(
    const libcasm_ir::RuleReferenceConstant::Ptr& ruleReference )
{
    m_ruleReference = ruleReference;
}

libcasm_ir::RuleReferenceConstant::Ptr RuleReferenceAtom::ruleReference(
    void ) const
{
    return m_ruleReference;
}

void RuleReferenceAtom::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

ZeroAtom::ZeroAtom( void )
: Expression( Node::ID::ZERO_ATOM )
{
}

void ZeroAtom::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

UndefAtom::UndefAtom( void )
: Expression( Node::ID::UNDEF_ATOM )
{
}

void UndefAtom::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

void CallExpression::setTargetType( CallExpression::TargetType targetType )
{
    m_targetType = targetType;
}

CallExpression::TargetType CallExpression::targetType( void ) const
{
    return m_targetType;
}

DirectCallExpression::DirectCallExpression(
    const IdentifierNode::Ptr& identifier, const Expressions::Ptr& arguments )
: CallExpression( Node::ID::DIRECT_CALL_EXPRESSION )
, m_identifier( identifier )
, m_arguments( arguments )
{
}

void DirectCallExpression::setIdentifier(
    const IdentifierNode::Ptr& identifier )
{
    m_identifier = identifier;
}

IdentifierNode::Ptr DirectCallExpression::identifier( void ) const
{
    return m_identifier;
}

Expressions::Ptr DirectCallExpression::arguments( void ) const
{
    return m_arguments;
}

void DirectCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

IndirectCallExpression::IndirectCallExpression(
    const Expression::Ptr& expression, const Expressions::Ptr& arguments )
: CallExpression( Node::ID::INDIRECT_CALL_EXPRESSION )
, m_expression( expression )
, m_arguments( arguments )
{
}

Expression::Ptr IndirectCallExpression::expression( void ) const
{
    return m_expression;
}

Expressions::Ptr IndirectCallExpression::arguments( void ) const
{
    return m_arguments;
}

void IndirectCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

UnaryExpression::UnaryExpression(
    const Expression::Ptr& expression, libcasm_ir::Value::ID op )
: Expression( Node::ID::UNARY_EXPRESSION )
, m_op( op )
, m_expression( expression )
{
}

libcasm_ir::Value::ID UnaryExpression::op( void ) const
{
    return m_op;
}

Expression::Ptr UnaryExpression::expression( void ) const
{
    return m_expression;
}

void UnaryExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

BinaryExpression::BinaryExpression( const Expression::Ptr& left,
    const Expression::Ptr& right, libcasm_ir::Value::ID op )
: Expression( Node::ID::BINARY_EXPRESSION )
, m_op( op )
, m_left( left )
, m_right( right )
{
}

libcasm_ir::Value::ID BinaryExpression::op( void ) const
{
    return m_op;
}

Expression::Ptr BinaryExpression::left( void ) const
{
    return m_left;
}

Expression::Ptr BinaryExpression::right( void ) const
{
    return m_right;
}

void BinaryExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

RangeExpression::RangeExpression(
    const Expression::Ptr& left, const Expression::Ptr& right )
: Expression( Node::ID::RANGE_EXPRESSION )
, m_left( left )
, m_right( right )
{
}

Expression::Ptr RangeExpression::left( void ) const
{
    return m_left;
}

Expression::Ptr RangeExpression::right( void ) const
{
    return m_right;
}

void RangeExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

ListExpression::ListExpression( const Expressions::Ptr& expressions )
: Expression( Node::ID::LIST_EXPRESSION )
, m_expressions( expressions )
{
}

Expressions::Ptr ListExpression::expressions( void ) const
{
    return m_expressions;
}

void ListExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

ConditionalExpression::ConditionalExpression( const Expression::Ptr& condition,
    const Expression::Ptr& thenExpression,
    const Expression::Ptr& elseExpression )
: Expression( Node::ID::CONDITIONAL_EXPRESSION )
, m_condition( condition )
, m_thenExpression( thenExpression )
, m_elseExpression( elseExpression )
{
}

Expression::Ptr ConditionalExpression::condition( void ) const
{
    return m_condition;
}

Expression::Ptr ConditionalExpression::thenExpression( void ) const
{
    return m_thenExpression;
}

Expression::Ptr ConditionalExpression::elseExpression( void ) const
{
    return m_elseExpression;
}

void ConditionalExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

QuantifierExpression::QuantifierExpression( Node::ID id,
    const VariableDefinition::Ptr& predicateVariable,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: Expression( id )
, m_predicateVariable( predicateVariable )
, m_universe( universe )
, m_proposition( proposition )
{
}

VariableDefinition::Ptr QuantifierExpression::predicateVariable( void ) const
{
    return m_predicateVariable;
}

Expression::Ptr QuantifierExpression::universe( void ) const
{
    return m_universe;
}

Expression::Ptr QuantifierExpression::proposition( void ) const
{
    return m_proposition;
}

UniversalQuantifierExpression::UniversalQuantifierExpression(
    const std::shared_ptr< VariableDefinition >& predicateVariable,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: QuantifierExpression( Node::ID::UNIVERSAL_QUANTIFIER_EXPRESSION,
      predicateVariable, universe, proposition )
{
}

void UniversalQuantifierExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

ExistentialQuantifierExpression::ExistentialQuantifierExpression(
    const std::shared_ptr< VariableDefinition >& predicateVariable,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: QuantifierExpression( Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION,
      predicateVariable, universe, proposition )
{
}

void ExistentialQuantifierExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}
