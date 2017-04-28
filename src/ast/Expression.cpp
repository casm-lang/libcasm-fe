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
: TypedNode( id )
{
}

ValueAtom::ValueAtom( const libcasm_ir::Constant::Ptr& value )
: Expression( Node::ID::VALUE_ATOM )
, m_value( value )
{
    Expression::setType( value->ptr_type() );
}

libcasm_ir::Constant::Ptr ValueAtom::value( void ) const
{
    return m_value;
}

void ValueAtom::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

ReferenceAtom::ReferenceAtom( const IdentifierPath::Ptr& identifier )
: Expression( Node::ID::REFERENCE_ATOM )
, m_identifier( identifier )
, m_referenceType( ReferenceType::UNKNOWN )
, m_reference( nullptr )
, m_builtinId( libcasm_ir::Value::ID::_SIZE_ )
{
}

IdentifierPath::Ptr ReferenceAtom::identifier() const
{
    return m_identifier;
}

void ReferenceAtom::setReferenceType( ReferenceType referenceType )
{
    m_referenceType = referenceType;
}

ReferenceAtom::ReferenceType ReferenceAtom::referenceType( void ) const
{
    return m_referenceType;
}

void ReferenceAtom::setReference( const TypedNode::Ptr& reference )
{
    m_reference = reference;
}

TypedNode::Ptr ReferenceAtom::reference( void ) const
{
    assert( ( m_referenceType != ReferenceType::BUILTIN ) and
            ( m_referenceType != ReferenceType::UNKNOWN ) );

    return m_reference;
}

void ReferenceAtom::setBuiltinId( libcasm_ir::Value::ID builtinId )
{
    m_builtinId = builtinId;
}

libcasm_ir::Value::ID ReferenceAtom::builtinId( void ) const
{
    assert( m_referenceType == ReferenceType::BUILTIN );

    return m_builtinId;
}

void ReferenceAtom::accept( Visitor& visitor )
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

CallExpression::CallExpression( Node::ID id, const Expressions::Ptr& arguments )
: Expression( id )
, m_arguments( arguments )
{
}

Expressions::Ptr CallExpression::arguments( void ) const
{
    return m_arguments;
}

void CallExpression::setTargetType( CallExpression::TargetType targetType )
{
    m_targetType = targetType;
}

CallExpression::TargetType CallExpression::targetType( void ) const
{
    return m_targetType;
}

std::string CallExpression::targetTypeName( void ) const
{
    return targetTypeString( m_targetType );
}

std::string CallExpression::targetTypeString( const TargetType targetType )
{
    switch( targetType )
    {
        case TargetType::FUNCTION:
        {
            return "Function";
        }
        case TargetType::DERIVED:
        {
            return "Derived";
        }
        case TargetType::BUILTIN:
        {
            return "Builtin";
        }
        case TargetType::RULE:
        {
            return "Rule";
        }
        case TargetType::ENUMERATION:
        {
            return "Enumeration";
        }
        case TargetType::CONSTANT:
        {
            return "Constant";
        }
        case TargetType::VARIABLE:
        {
            return "Variable";
        }
        case TargetType::UNKNOWN:
        {
            return "Unknown";
        }
    }
}

DirectCallExpression::DirectCallExpression(
    const IdentifierPath::Ptr& identifier, const Expressions::Ptr& arguments )
: CallExpression( Node::ID::DIRECT_CALL_EXPRESSION, arguments )
, m_identifier( identifier )
, m_targetId( 0 )
{
}

void DirectCallExpression::setIdentifier(
    const IdentifierPath::Ptr& identifier )
{
    m_identifier = identifier;
}

IdentifierPath::Ptr DirectCallExpression::identifier( void ) const
{
    return m_identifier;
}

void DirectCallExpression::setTargetId( std::size_t targetId )
{
    m_targetId = targetId;
}

std::size_t DirectCallExpression::targetId( void ) const
{
    return m_targetId;
}

void DirectCallExpression::setTargetDefinition(
    const TypedNode::Ptr& definition )
{
    m_targetDefinition = definition;
}

TypedNode::Ptr DirectCallExpression::targetDefinition( void ) const
{
    return m_targetDefinition;
}

void DirectCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

IndirectCallExpression::IndirectCallExpression(
    const Expression::Ptr& expression, const Expressions::Ptr& arguments )
: CallExpression( Node::ID::INDIRECT_CALL_EXPRESSION, arguments )
, m_expression( expression )
{
}

Expression::Ptr IndirectCallExpression::expression( void ) const
{
    return m_expression;
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
