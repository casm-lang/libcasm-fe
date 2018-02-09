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

#include "Expression.h"

#include <libcasm-fe/ast/Definition>
#include <libcasm-fe/ast/Literal>
#include <libcasm-fe/ast/Type>

using namespace libcasm_fe;
using namespace Ast;

//
//
// Expression
//

Expression::Expression( Node::ID id )
: TypedPropertyNode( id )
{
}

//
//
// NamedExpression
//

NamedExpression::NamedExpression(
    const Identifier::Ptr& identifier, const Expression::Ptr& expression )
: Expression( Node::ID::NAMED_EXPRESSION )
, m_identifier( identifier )
, m_expression( expression )
{
}

const Identifier::Ptr& NamedExpression::identifier( void ) const
{
    return m_identifier;
}

const Expression::Ptr& NamedExpression::expression( void ) const
{
    return m_expression;
}

void NamedExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// CallExpression
//

CallExpression::CallExpression( Node::ID id, const Expressions::Ptr& arguments )
: Expression( id )
, m_arguments( arguments )
, m_targetType( TargetType::UNKNOWN )
, m_targetBuiltinId( libcasm_ir::Value::ID::_SIZE_ )
, m_targetDefinition()
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
    m_targetBuiltinId = builtinId;
}

libcasm_ir::Value::ID CallExpression::targetBuiltinId( void ) const
{
    assert( targetType() == TargetType::BUILTIN );
    return m_targetBuiltinId;
}

void CallExpression::setTargetDefinition( const Definition::Ptr& definition )
{
    m_targetDefinition = definition;
}

const Definition::Ptr& CallExpression::targetDefinition( void ) const
{
    assert( ( targetType() != TargetType::BUILTIN ) and ( targetType() != TargetType::UNKNOWN ) );
    return m_targetDefinition;
}

//
//
// DirectCallExpression
//

DirectCallExpression::DirectCallExpression(
    const IdentifierPath::Ptr& identifier, const Expressions::Ptr& arguments )
: CallExpression( Node::ID::DIRECT_CALL_EXPRESSION, arguments )
, m_identifier( identifier )
{
}

void DirectCallExpression::setIdentifier( const IdentifierPath::Ptr& identifier )
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

//
//
// MethodCallExpression
//

MethodCallExpression::MethodCallExpression(
    const Expression::Ptr& object,
    const Identifier::Ptr& methodName,
    const Expressions::Ptr& arguments )
: CallExpression( Node::ID::METHOD_CALL_EXPRESSION, arguments )
, m_object( object )
, m_methodName( methodName )
, m_methodType( MethodType::UNKNOWN )
, m_targetBuiltinId( libcasm_ir::Value::ID::_SIZE_ )
{
}

const Expression::Ptr& MethodCallExpression::object( void ) const
{
    return m_object;
}

const Identifier::Ptr& MethodCallExpression::methodName( void ) const
{
    return m_methodName;
}

void MethodCallExpression::setMethodType( MethodType methodType )
{
    m_methodType = methodType;
}

MethodCallExpression::MethodType MethodCallExpression::methodType( void ) const
{
    return m_methodType;
}

std::string MethodCallExpression::methodTypeName( void ) const
{
    switch( m_methodType )
    {
        case MethodType::FUNCTION:
        {
            return "function";
        }
        case MethodType::DERIVED:
        {
            return "derived";
        }
        case MethodType::BUILTIN:
        {
            return "built-in";
        }
        case MethodType::RULE:
        {
            return "rule";
        }
        case MethodType::UNKNOWN:
        {
            return "unknown";
        }
    }

    assert( !" internal error! " );
    return std::string();
}

void MethodCallExpression::setTargetBuiltinId( libcasm_ir::Value::ID builtinId )
{
    m_targetBuiltinId = builtinId;
}

libcasm_ir::Value::ID MethodCallExpression::targetBuiltinId( void ) const
{
    assert( m_methodType == MethodType::BUILTIN );

    return m_targetBuiltinId;
}

void MethodCallExpression::setTargetDefinition( const Definition::Ptr& definition )
{
    m_targetDefinition = definition;
}

const Definition::Ptr& MethodCallExpression::targetDefinition( void ) const
{
    assert( ( m_methodType != MethodType::BUILTIN ) and ( m_methodType != MethodType::UNKNOWN ) );

    return m_targetDefinition;
}

void MethodCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// LiteralCallExpression
//

LiteralCallExpression::LiteralCallExpression(
    const Expression::Ptr& object, const std::shared_ptr< Literal >& literal )
: Expression( Node::ID::LITERAL_CALL_EXPRESSION )
, m_object( object )
, m_literal( literal )
{
}

const Expression::Ptr& LiteralCallExpression::object( void ) const
{
    return m_object;
}

const std::shared_ptr< Literal >& LiteralCallExpression::literal( void ) const
{
    return m_literal;
}

void LiteralCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// IndirectCallExpression
//

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

//
//
// TypeCastingExpression
//

TypeCastingExpression::TypeCastingExpression(
    const Expression::Ptr& fromExpression, const Type::Ptr& asType )
: CallExpression( Node::ID::TYPE_CASTING_EXPRESSION, std::make_shared< Expressions >() )
, m_fromExpression( fromExpression )
, m_asType( asType )
, m_castingType( CastingType::UNKNOWN )
, m_targetBuiltinId( libcasm_ir::Value::ID::_SIZE_ )
{
}

const Expression::Ptr& TypeCastingExpression::fromExpression( void ) const
{
    return m_fromExpression;
}

const Type::Ptr& TypeCastingExpression::asType( void ) const
{
    return m_asType;
}

void TypeCastingExpression::setCastingType( CastingType castingType )
{
    m_castingType = castingType;
}

TypeCastingExpression::CastingType TypeCastingExpression::castingType( void ) const
{
    return m_castingType;
}

std::string TypeCastingExpression::castingTypeName( void ) const
{
    switch( m_castingType )
    {
        case CastingType::BUILTIN:
        {
            return "built-in";
        }
        case CastingType::UNKNOWN:
        {
            return "unknown";
        }
    }

    assert( !" internal error! " );
    return std::string();
}

void TypeCastingExpression::setTargetBuiltinId( libcasm_ir::Value::ID builtinId )
{
    m_targetBuiltinId = builtinId;
}

libcasm_ir::Value::ID TypeCastingExpression::targetBuiltinId( void ) const
{
    assert( m_castingType == CastingType::BUILTIN );
    return m_targetBuiltinId;
}

void TypeCastingExpression::setTargetDefinition( const Definition::Ptr& definition )
{
    m_targetDefinition = definition;
}

const Definition::Ptr& TypeCastingExpression::targetDefinition( void ) const
{
    assert(
        ( m_castingType != CastingType::BUILTIN ) and ( m_castingType != CastingType::UNKNOWN ) );
    return m_targetDefinition;
}

void TypeCastingExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// UnaryExpression
//

UnaryExpression::UnaryExpression( const Expression::Ptr& expression, libcasm_ir::Value::ID op )
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

//
//
// BinaryExpression
//

BinaryExpression::BinaryExpression(
    const Expression::Ptr& left, const Expression::Ptr& right, libcasm_ir::Value::ID op )
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

//
//
// LetExpression
//

LetExpression::LetExpression(
    const VariableDefinition::Ptr& variable,
    const Expression::Ptr& initializer,
    const Expression::Ptr& expression )
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

//
//
// ConditionalExpression
//

ConditionalExpression::ConditionalExpression(
    const Expression::Ptr& condition,
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

//
//
// ChooseExpression
//

ChooseExpression::ChooseExpression(
    const VariableDefinition::Ptr& variable,
    const Expression::Ptr& universe,
    const Expression::Ptr& expression )
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

//
//
// QuantifierExpression
//

QuantifierExpression::QuantifierExpression(
    Node::ID id,
    const VariableDefinition::Ptr& predicateVariable,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: Expression( id )
, m_predicateVariable( predicateVariable )
, m_universe( universe )
, m_proposition( proposition )
{
}

const VariableDefinition::Ptr& QuantifierExpression::predicateVariable( void ) const
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

//
//
// UniversalQuantifierExpression
//

UniversalQuantifierExpression::UniversalQuantifierExpression(
    const std::shared_ptr< VariableDefinition >& predicateVariable,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: QuantifierExpression(
      Node::ID::UNIVERSAL_QUANTIFIER_EXPRESSION, predicateVariable, universe, proposition )
{
}

void UniversalQuantifierExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// ExistentialQuantifierExpression
//

ExistentialQuantifierExpression::ExistentialQuantifierExpression(
    const std::shared_ptr< VariableDefinition >& predicateVariable,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: QuantifierExpression(
      Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION, predicateVariable, universe, proposition )
{
}

void ExistentialQuantifierExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
