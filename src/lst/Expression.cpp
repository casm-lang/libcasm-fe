//
//  Copyright (C) 2014-2022 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//                <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#include <libcasm-fe/lst/Definition>
#include <libcasm-fe/lst/Literal>

using namespace libcasm_fe;
using namespace LST;

//
//
// Expression
//

Expression::Expression(
    Node::ID id, const libcasm_ir::Type::Ptr& type, const libcasm_ir::Properties& properties )
: Node( id, type, properties )
{
}

//
//
// NamedExpression
//

NamedExpression::NamedExpression(
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Identifier::Ptr& identifier,
    const Expression::Ptr& expression )
: Expression( Node::ID::NAMED_EXPRESSION, type, properties )
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

CallExpression::CallExpression(
    const Node::ID id,
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Expressions::Ptr& arguments,
    const std::shared_ptr< Definition >& targetDefinition )
: Expression( id, type, properties )
, m_arguments( arguments )
, m_targetDefinition( targetDefinition )
{
}

const Expressions::Ptr& CallExpression::arguments( void ) const
{
    return m_arguments;
}

const Definition::Ptr& CallExpression::targetDefinition( void ) const
{
    assert( m_targetDefinition != nullptr );
    return m_targetDefinition;
}

//
//
// DirectCallExpression
//

DirectCallExpression::DirectCallExpression(
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Expressions::Ptr& arguments,
    const std::shared_ptr< Definition >& targetDefinition,
    const TargetType targetType )
: CallExpression( Node::ID::DIRECT_CALL_EXPRESSION, type, properties, arguments, targetDefinition )
, m_targetType( targetType )
{
    assert( targetType != TargetType::UNKNOWN );
}

DirectCallExpression::TargetType DirectCallExpression::targetType( void ) const
{
    return m_targetType;
}

std::string DirectCallExpression::targetTypeName( void ) const
{
    return AST::DirectCallExpression::targetTypeString( m_targetType );
}

void DirectCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// IndirectCallExpression
//

IndirectCallExpression::IndirectCallExpression(
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Expressions::Ptr& arguments,
    const std::shared_ptr< Definition >& targetDefinition,
    const Expression::Ptr& expression )
: CallExpression(
      Node::ID::INDIRECT_CALL_EXPRESSION, type, properties, arguments, targetDefinition )
, m_expression( expression )
{
}

const Expression::Ptr& IndirectCallExpression::expression( void ) const
{
    return m_expression;
}

bool IndirectCallExpression::isRuleCall( void ) const
{
    return m_expression->type()->isRuleReference();
}

bool IndirectCallExpression::isFunctionCall( void ) const
{
    return m_expression->type()->isFunctionReference();
}

void IndirectCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// VariableBinding
//

VariableBinding::VariableBinding(
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const std::shared_ptr< VariableDefinition >& variable,
    const Expression::Ptr& expression )
: Node( Node::ID::VARIABLE_BINDING, type, properties )
, m_variable( variable )
, m_expression( expression )
{
}

const VariableDefinition::Ptr& VariableBinding::variable( void ) const
{
    return m_variable;
}

const Expression::Ptr& VariableBinding::expression( void ) const
{
    return m_expression;
}

void VariableBinding::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// LetExpression
//

LetExpression::LetExpression(
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const VariableBindings::Ptr& variableBindings,
    const Expression::Ptr& expression )
: Expression( Node::ID::LET_EXPRESSION, type, properties )
, m_variableBindings( variableBindings )
, m_expression( expression )
{
}

const VariableBindings::Ptr& LetExpression::variableBindings( void ) const
{
    return m_variableBindings;
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
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const Expression::Ptr& condition,
    const Expression::Ptr& thenExpression,
    const Expression::Ptr& elseExpression )
: Expression( Node::ID::CONDITIONAL_EXPRESSION, type, properties )
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
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const VariableDefinition::Ptr& variable,
    const Expression::Ptr& universe,
    const Expression::Ptr& condition,
    const Expression::Ptr& expression )
: Expression( Node::ID::CHOOSE_EXPRESSION, type, properties )
, m_variable( variable )
, m_universe( universe )
, m_condition( condition )
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

const Expression::Ptr& ChooseExpression::condition( void ) const
{
    return m_condition;
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
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const VariableDefinitions::Ptr& predicateVariables,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: Expression( id, type, properties )
, m_predicateVariables( predicateVariables )
, m_universe( universe )
, m_proposition( proposition )
{
}

const VariableDefinitions::Ptr& QuantifierExpression::predicateVariables( void ) const
{
    return m_predicateVariables;
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
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const std::shared_ptr< VariableDefinitions >& predicateVariables,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: QuantifierExpression(
      Node::ID::UNIVERSAL_QUANTIFIER_EXPRESSION,
      type,
      properties,
      predicateVariables,
      universe,
      proposition )
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
    const libcasm_ir::Type::Ptr& type,
    const libcasm_ir::Properties& properties,
    const std::shared_ptr< VariableDefinitions >& predicateVariables,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: QuantifierExpression(
      Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION,
      type,
      properties,
      predicateVariables,
      universe,
      proposition )
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
