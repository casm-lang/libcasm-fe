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

#include "Expression.h"

#include "Definition.h"
#include "Type.h"

using namespace libcasm_fe;
using namespace Ast;

Expression::Expression( Node::ID id )
: TypedNode( id )
{
}

UnresolvedNamespace::UnresolvedNamespace( void )
: Expression( Node::ID::UNRESOLVED_NAMESPACE )
{
}

void UnresolvedNamespace::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

ValueAtom::ValueAtom( const libcasm_ir::Constant::Ptr& value )
: Expression( Node::ID::VALUE_ATOM )
, m_value( value )
{
    Expression::setType( value->type().ptr_type() );
}

const libcasm_ir::Constant::Ptr& ValueAtom::value( void ) const
{
    return m_value;
}

void ValueAtom::setValue( const libcasm_ir::Constant::Ptr& value )
{
    m_value = value;
    Expression::setType( m_value->type().ptr_type() );
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

const IdentifierPath::Ptr& ReferenceAtom::identifier() const
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

const TypedNode::Ptr& ReferenceAtom::reference( void ) const
{
    assert( ( m_referenceType != ReferenceType::BUILTIN )
            and ( m_referenceType != ReferenceType::UNKNOWN ) );

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
, m_targetType( TargetType::UNKNOWN )
, m_targetBuiltinId( libcasm_ir::Value::ID::_SIZE_ )
, m_targetDefinition()
, m_baseExpression()
{
}

const Expressions::Ptr& CallExpression::arguments( void ) const
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
            return "function";
        }
        case TargetType::DERIVED:
        {
            return "derived";
        }
        case TargetType::BUILTIN:
        {
            return "built-in";
        }
        case TargetType::RULE:
        {
            return "rule";
        }
        case TargetType::TYPE_DOMAIN:
        {
            return "type domain";
        }
        case TargetType::CONSTANT:
        {
            return "constant";
        }
        case TargetType::VARIABLE:
        {
            return "variable";
        }
        case TargetType::SELF:
        {
            return "self";
        }
        case TargetType::UNKNOWN:
        {
            return "unknown";
        }
    }

    assert( !" internal error! " );
    return std::string();
}

void CallExpression::setTargetBuiltinId( libcasm_ir::Value::ID builtinId )
{
    setTargetType( CallExpression::TargetType::BUILTIN );
    m_targetBuiltinId = builtinId;
}

libcasm_ir::Value::ID CallExpression::targetBuiltinId( void ) const
{
    assert( targetType() == TargetType::BUILTIN );
    return m_targetBuiltinId;
}

void CallExpression::setTargetDefinition( const TypedNode::Ptr& definition )
{
    m_targetDefinition = definition;
}

const TypedNode::Ptr& CallExpression::targetDefinition( void ) const
{
    assert( ( targetType() != TargetType::BUILTIN )
            and ( targetType() != TargetType::UNKNOWN ) );

    return m_targetDefinition;
}

void CallExpression::setBaseExpression( const Expression::Ptr& baseExpression )
{
    assert( baseExpression != nullptr );
    m_baseExpression = baseExpression;
}

const Expression::Ptr& CallExpression::baseExpression( void ) const
{
    return m_baseExpression;
}

u1 CallExpression::builtin( void ) const
{
    return m_targetBuiltinId != libcasm_ir::Value::ID::_SIZE_
           and targetType() == CallExpression::TargetType::BUILTIN;
}

u1 CallExpression::definition( void ) const
{
    return m_targetDefinition != nullptr
           and targetType() != CallExpression::TargetType::BUILTIN
           and targetType() != CallExpression::TargetType::UNKNOWN;
}

u1 CallExpression::methodCall( void ) const
{
    return m_baseExpression != nullptr
           and targetType() == CallExpression::TargetType::BUILTIN;
}

DirectCallExpression::DirectCallExpression(
    const IdentifierPath::Ptr& identifier, const Expressions::Ptr& arguments )
: DirectCallExpression(
      Node::ID::DIRECT_CALL_EXPRESSION, identifier, arguments )
{
}

DirectCallExpression::DirectCallExpression( const Node::ID id,
    const IdentifierPath::Ptr& identifier, const Expressions::Ptr& arguments )
: CallExpression( id, arguments )
, m_identifier( identifier )
{
}

void DirectCallExpression::setIdentifier(
    const IdentifierPath::Ptr& identifier )
{
    m_identifier = identifier;
}

const IdentifierPath::Ptr& DirectCallExpression::identifier( void ) const
{
    return m_identifier;
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

const Expression::Ptr& IndirectCallExpression::expression( void ) const
{
    return m_expression;
}

void IndirectCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

TypeCastingExpression::TypeCastingExpression(
    const Expression::Ptr& fromExpression, const Type::Ptr& asType )
: CallExpression(
      Node::ID::TYPE_CASTING_EXPRESSION, std::make_shared< Expressions >() )
, m_fromExpression( fromExpression )
, m_asType( asType )
{
    arguments()->add( fromExpression );
}

const Expression::Ptr& TypeCastingExpression::fromExpression( void ) const
{
    return m_fromExpression;
}

const Type::Ptr& TypeCastingExpression::asType( void ) const
{
    return m_asType;
}

void TypeCastingExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

MethodCallExpression::MethodCallExpression( const Expression::Ptr& expression,
    const Identifier::Ptr& identifier,
    const Expressions::Ptr& arguments )
: DirectCallExpression( Node::ID::METHOD_CALL_EXPRESSION,
      std::make_shared< IdentifierPath >(
          identifier, IdentifierPath::Type::ABSOLUTE ),
      arguments )
, m_expression( expression )
{
    setBaseExpression( expression );
}

const Expression::Ptr& MethodCallExpression::expression( void ) const
{
    return m_expression;
}

void MethodCallExpression::accept( Visitor& visitor )
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

const Expression::Ptr& UnaryExpression::expression( void ) const
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

const Expression::Ptr& BinaryExpression::left( void ) const
{
    return m_left;
}

const Expression::Ptr& BinaryExpression::right( void ) const
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

const Expression::Ptr& RangeExpression::left( void ) const
{
    return m_left;
}

const Expression::Ptr& RangeExpression::right( void ) const
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

const Expressions::Ptr& ListExpression::expressions( void ) const
{
    return m_expressions;
}

void ListExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

LetExpression::LetExpression( const VariableDefinition::Ptr& variable,
    const Expression::Ptr& initializer, const Expression::Ptr& expression )
: Expression( Node::ID::LET_EXPRESSION )
, m_variable( variable )
, m_initializer( initializer )
, m_expression( expression )
{
}

const VariableDefinition::Ptr& LetExpression::variable( void ) const
{
    return m_variable;
}

const Expression::Ptr& LetExpression::initializer( void ) const
{
    return m_initializer;
}

const Expression::Ptr& LetExpression::expression( void ) const
{
    return m_expression;
}

void LetExpression::accept( Visitor& visitor )
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

const Expression::Ptr& ConditionalExpression::condition( void ) const
{
    return m_condition;
}

const Expression::Ptr& ConditionalExpression::thenExpression( void ) const
{
    return m_thenExpression;
}

const Expression::Ptr& ConditionalExpression::elseExpression( void ) const
{
    return m_elseExpression;
}

void ConditionalExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

ChooseExpression::ChooseExpression( const VariableDefinition::Ptr& variable,
    const Expression::Ptr& universe, const Expression::Ptr& expression )
: Expression( Node::ID::CHOOSE_EXPRESSION )
, m_variable( variable )
, m_universe( universe )
, m_expression( expression )
{
}

const VariableDefinition::Ptr& ChooseExpression::variable( void ) const
{
    return m_variable;
}

const Expression::Ptr& ChooseExpression::universe( void ) const
{
    return m_universe;
}

const Expression::Ptr& ChooseExpression::expression( void ) const
{
    return m_expression;
}

void ChooseExpression::accept( Visitor& visitor )
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

const VariableDefinition::Ptr& QuantifierExpression::predicateVariable(
    void ) const
{
    return m_predicateVariable;
}

const Expression::Ptr& QuantifierExpression::universe( void ) const
{
    return m_universe;
}

const Expression::Ptr& QuantifierExpression::proposition( void ) const
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
