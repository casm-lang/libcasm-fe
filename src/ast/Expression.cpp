//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Jakob Moosbrugger
//                Florian Hahn
//                Ioan Molnar
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

#include "../various/GrammarToken.h"

using namespace libcasm_fe;
using namespace AST;

//
//
// Expression
//

Expression::Expression( Node::ID id )
: TypedPropertyNode( id )
{
}

void Expression::clone( Expression& duplicate ) const
{
    TypedPropertyNode::clone( duplicate );
}

//
//
// AbstractExpression
//

AbstractExpression::AbstractExpression( void )
: Expression( Node::ID::ABSTRACT_EXPRESSION )
{
}

void AbstractExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr AbstractExpression::clone( void ) const
{
    auto duplicate = std::make_shared< AbstractExpression >();

    Expression::clone( *duplicate );
    return duplicate;
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

Node::Ptr NamedExpression::clone( void ) const
{
    auto duplicate = std::make_shared< NamedExpression >(
        identifier()->duplicate< Identifier >(), expression()->duplicate< Expression >() );

    Expression::clone( *duplicate );
    return duplicate;
}

//
//
// MappedExpression
//

MappedExpression::MappedExpression(
    const Expressions::Ptr& arguments, const Expression::Ptr& value )
: Expression( Node::ID::MAPPED_EXPRESSION )
, m_arguments( arguments )
, m_value( value )
{
}

const Expressions::Ptr& MappedExpression::arguments( void ) const
{
    return m_arguments;
}

const Expression::Ptr& MappedExpression::value( void ) const
{
    return m_value;
}

void MappedExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr MappedExpression::clone( void ) const
{
    auto duplicate = std::make_shared< MappedExpression >(
        arguments()->duplicate< Expressions >(), value()->duplicate< Expression >() );

    Expression::clone( *duplicate );
    return duplicate;
}

//
//
// CallExpression
//

CallExpression::CallExpression( const Node::ID id, const Expressions::Ptr& arguments )
: Expression( id )
, m_arguments( arguments )
{
}

const Expressions::Ptr& CallExpression::arguments( void ) const
{
    return m_arguments;
}

void CallExpression::clone( CallExpression& duplicate ) const
{
    Expression::clone( duplicate );
}

//
//
// TargetCallExpression
//

TargetCallExpression::TargetCallExpression(
    const Node::ID id,
    const Expressions::Ptr& arguments,
    const VariableDefinitions::Ptr& templateSymbols )
: CallExpression( id, arguments )
, m_templateSymbols( templateSymbols )
, m_targetDefinition()
, m_targetType( TargetType::UNKNOWN )
{
}

TargetCallExpression::TargetCallExpression( const Node::ID id, const Expressions::Ptr& arguments )
: TargetCallExpression( id, arguments, std::make_shared< VariableDefinitions >() )
{
}

TargetCallExpression::TargetCallExpression( const Node::ID id )
: TargetCallExpression( id, std::make_shared< Expressions >() )
{
}

const VariableDefinitions::Ptr& TargetCallExpression::templateSymbols( void ) const
{
    return m_templateSymbols;
}

void TargetCallExpression::setTargetDefinition( const Definition::Ptr& definition )
{
    m_targetDefinition = definition;
}

const Definition::Ptr& TargetCallExpression::targetDefinition( void ) const
{
    assert( m_targetDefinition != nullptr );
    return m_targetDefinition;
}

u1 TargetCallExpression::hasTargetDefinition( void ) const
{
    return m_targetDefinition != nullptr;
}

void TargetCallExpression::setTargetType( TargetType targetType )
{
    m_targetType = targetType;
}

TargetCallExpression::TargetType TargetCallExpression::targetType( void ) const
{
    return m_targetType;
}

std::string TargetCallExpression::targetTypeName( void ) const
{
    return targetTypeString( m_targetType );
}

std::string TargetCallExpression::targetTypeString( const TargetType targetType )
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
            return "builtin";
        }
        case TargetType::RULE:
        {
            return "rule";
        }
        case TargetType::DOMAIN:
        {
            return "domain";
        }
        case TargetType::CONSTANT:
        {
            return "constant";
        }
        case TargetType::VARIABLE:
        {
            return "variable";
        }
        case TargetType::UNKNOWN:
        {
            return "unknown";
        }
    }

    assert( !" internal error! " );
    return std::string();
}

void TargetCallExpression::clone( TargetCallExpression& duplicate ) const
{
    CallExpression::clone( duplicate );
    duplicate.setTargetDefinition( m_targetDefinition );
    duplicate.setTargetType( targetType() );
}

//
//
// DirectCallExpression
//

DirectCallExpression::DirectCallExpression(
    const VariableDefinitions::Ptr& templateSymbols,
    const IdentifierPath::Ptr& identifier,
    const Expressions::Ptr& arguments )
: TargetCallExpression( Node::ID::DIRECT_CALL_EXPRESSION, arguments, templateSymbols )
, m_identifier( identifier )
{
}

DirectCallExpression::DirectCallExpression(
    const IdentifierPath::Ptr& identifier, const Expressions::Ptr& arguments )
: TargetCallExpression( Node::ID::DIRECT_CALL_EXPRESSION, arguments )
, m_identifier( identifier )
{
}

DirectCallExpression::DirectCallExpression( const IdentifierPath::Ptr& identifier )
: TargetCallExpression( Node::ID::DIRECT_CALL_EXPRESSION )
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

Node::Ptr DirectCallExpression::clone( void ) const
{
    auto duplicate = std::make_shared< DirectCallExpression >(
        templateSymbols()->duplicate< VariableDefinitions >(),
        identifier()->duplicate< IdentifierPath >(),
        arguments()->duplicate< Expressions >() );

    TargetCallExpression::clone( *duplicate );
    return duplicate;
}

//
//
// MethodCallExpression
//

MethodCallExpression::MethodCallExpression(
    const Expression::Ptr& object,
    const Identifier::Ptr& methodName,
    const Expressions::Ptr& arguments )
: TargetCallExpression( Node::ID::METHOD_CALL_EXPRESSION, std::make_shared< Expressions >() )
, m_methodName( methodName )
{
    this->arguments()->add( object );
    for( const auto& argument : *arguments )
    {
        this->arguments()->add( argument );
    }
}

const Expression::Ptr& MethodCallExpression::object( void ) const
{
    assert( arguments()->size() >= 1 );
    return arguments()->front();
}

const Identifier::Ptr& MethodCallExpression::methodName( void ) const
{
    return m_methodName;
}

void MethodCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr MethodCallExpression::clone( void ) const
{
    auto duplicate = std::make_shared< MethodCallExpression >(
        object()->duplicate< Expression >(),
        methodName()->duplicate< Identifier >(),
        arguments()->duplicate< Expressions >() );

    TargetCallExpression::clone( *duplicate );
    return duplicate;
}

//
//
// LiteralCallExpression
//

LiteralCallExpression::LiteralCallExpression(
    const Expression::Ptr& object, const std::shared_ptr< Literal >& literal )
: TargetCallExpression( Node::ID::LITERAL_CALL_EXPRESSION, std::make_shared< Expressions >() )
, m_literal( literal )
{
    arguments()->add( object );
    arguments()->add( m_literal );
}

const Expression::Ptr& LiteralCallExpression::object( void ) const
{
    assert( arguments()->size() == 2 );
    return arguments()->front();
}

const std::shared_ptr< Literal >& LiteralCallExpression::literal( void ) const
{
    assert( arguments()->size() == 2 and arguments()->back() == m_literal );
    return m_literal;
}

void LiteralCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr LiteralCallExpression::clone( void ) const
{
    auto duplicate = std::make_shared< LiteralCallExpression >(
        object()->duplicate< Expression >(), literal()->duplicate< Literal >() );

    TargetCallExpression::clone( *duplicate );
    return duplicate;
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

Node::Ptr IndirectCallExpression::clone( void ) const
{
    auto duplicate = std::make_shared< IndirectCallExpression >(
        expression()->duplicate< Expression >(), arguments()->duplicate< Expressions >() );

    CallExpression::clone( *duplicate );
    return duplicate;
}

//
//
// TypeCastingExpression
//

TypeCastingExpression::TypeCastingExpression(
    const Expression::Ptr& fromExpression, const Type::Ptr& asType )
: TargetCallExpression( Node::ID::TYPE_CASTING_EXPRESSION, std::make_shared< Expressions >() )
, m_asType( asType )
{
    arguments()->add( fromExpression );
}

const Expression::Ptr& TypeCastingExpression::fromExpression( void ) const
{
    assert( arguments()->size() == 1 );
    return arguments()->front();
}

const Type::Ptr& TypeCastingExpression::asType( void ) const
{
    return m_asType;
}

void TypeCastingExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr TypeCastingExpression::clone( void ) const
{
    auto duplicate = std::make_shared< TypeCastingExpression >(
        fromExpression()->duplicate< Expression >(), asType()->duplicate< Type >() );

    TargetCallExpression::clone( *duplicate );
    return duplicate;
}

//
//
// UnaryExpression
//

UnaryExpression::UnaryExpression(
    const Grammar::Token operationToken, const Expression::Ptr& expression )
: TargetCallExpression( Node::ID::UNARY_EXPRESSION, std::make_shared< Expressions >() )
, m_operationToken( operationToken )
{
    arguments()->add( expression );
}

const Expression::Ptr& UnaryExpression::expression( void ) const
{
    assert( arguments()->size() == 1 );
    return arguments()->front();
}

const Grammar::Token UnaryExpression::operationToken( void ) const
{
    return m_operationToken;
}

const std::string UnaryExpression::operationTokenString( void ) const
{
    return Grammar::tokenAsString( operationToken() );
}

void UnaryExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr UnaryExpression::clone( void ) const
{
    auto duplicate = std::make_shared< UnaryExpression >(
        operationToken(), expression()->duplicate< Expression >() );

    TargetCallExpression::clone( *duplicate );
    return duplicate;
}

//
//
// BinaryExpression
//

BinaryExpression::BinaryExpression(
    const Expression::Ptr& left, const Grammar::Token operationToken, const Expression::Ptr& right )
: TargetCallExpression( Node::ID::BINARY_EXPRESSION, std::make_shared< Expressions >() )
, m_operationToken( operationToken )
{
    arguments()->add( left );
    arguments()->add( right );
}

const Expression::Ptr& BinaryExpression::left( void ) const
{
    assert( arguments()->size() == 2 );
    return arguments()->front();
}

const Expression::Ptr& BinaryExpression::right( void ) const
{
    assert( arguments()->size() == 2 );
    return arguments()->back();
}

const Grammar::Token BinaryExpression::operationToken( void ) const
{
    return m_operationToken;
}

const std::string BinaryExpression::operationTokenString( void ) const
{
    return Grammar::tokenAsString( operationToken() );
}

void BinaryExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr BinaryExpression::clone( void ) const
{
    auto duplicate = std::make_shared< BinaryExpression >(
        left()->duplicate< Expression >(), operationToken(), right()->duplicate< Expression >() );

    TargetCallExpression::clone( *duplicate );
    return duplicate;
}

//
//
// VariableBinding
//

VariableBinding::VariableBinding(
    const VariableDefinition::Ptr& variable, const Expression::Ptr& expression )
: TypedNode( Node::ID::VARIABLE_BINDING )
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

Node::Ptr VariableBinding::clone( void ) const
{
    auto duplicate = std::make_shared< VariableBinding >(
        variable()->duplicate< VariableDefinition >(), expression()->duplicate< Expression >() );

    TypedNode::clone( *duplicate );
    return duplicate;
}

//
//
// LetExpression
//

LetExpression::LetExpression(
    const VariableBindings::Ptr& variableBindings, const Expression::Ptr& expression )
: Expression( Node::ID::LET_EXPRESSION )
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

Node::Ptr LetExpression::clone( void ) const
{
    auto duplicate = std::make_shared< LetExpression >(
        variableBindings()->duplicate< VariableBindings >(),
        expression()->duplicate< Expression >() );

    Expression::clone( *duplicate );
    return duplicate;
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

Node::Ptr ConditionalExpression::clone( void ) const
{
    auto duplicate = std::make_shared< ConditionalExpression >(
        condition()->duplicate< Expression >(),
        thenExpression()->duplicate< Expression >(),
        elseExpression()->duplicate< Expression >() );

    Expression::clone( *duplicate );
    return duplicate;
}

//
//
// ChooseExpression
//

ChooseExpression::ChooseExpression(
    const VariableDefinitions::Ptr& variables,
    const Expression::Ptr& universe,
    const Expression::Ptr& expression )
: Expression( Node::ID::CHOOSE_EXPRESSION )
, m_variables( variables )
, m_universe( universe )
, m_expression( expression )
{
}

const VariableDefinitions::Ptr& ChooseExpression::variables( void ) const
{
    return m_variables;
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

Node::Ptr ChooseExpression::clone( void ) const
{
    auto duplicate = std::make_shared< ChooseExpression >(
        variables()->duplicate< VariableDefinitions >(),
        universe()->duplicate< Expression >(),
        expression()->duplicate< Expression >() );

    Expression::clone( *duplicate );
    return duplicate;
}

//
//
// QuantifierExpression
//

QuantifierExpression::QuantifierExpression(
    Node::ID id,
    const VariableDefinitions::Ptr& predicateVariables,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: Expression( id )
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

void QuantifierExpression::clone( QuantifierExpression& duplicate ) const
{
    Expression::clone( duplicate );
}

//
//
// UniversalQuantifierExpression
//

UniversalQuantifierExpression::UniversalQuantifierExpression(
    const std::shared_ptr< VariableDefinitions >& predicateVariables,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: QuantifierExpression(
      Node::ID::UNIVERSAL_QUANTIFIER_EXPRESSION, predicateVariables, universe, proposition )
{
}

void UniversalQuantifierExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr UniversalQuantifierExpression::clone( void ) const
{
    auto duplicate = std::make_shared< UniversalQuantifierExpression >(
        predicateVariables()->duplicate< VariableDefinitions >(),
        universe()->duplicate< Expression >(),
        proposition()->duplicate< Expression >() );

    QuantifierExpression::clone( *duplicate );
    return duplicate;
}

//
//
// ExistentialQuantifierExpression
//

ExistentialQuantifierExpression::ExistentialQuantifierExpression(
    const std::shared_ptr< VariableDefinitions >& predicateVariables,
    const Expression::Ptr& universe,
    const Expression::Ptr& proposition )
: QuantifierExpression(
      Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION, predicateVariables, universe, proposition )
{
}

void ExistentialQuantifierExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ExistentialQuantifierExpression::clone( void ) const
{
    auto duplicate = std::make_shared< ExistentialQuantifierExpression >(
        predicateVariables()->duplicate< VariableDefinitions >(),
        universe()->duplicate< Expression >(),
        proposition()->duplicate< Expression >() );

    QuantifierExpression::clone( *duplicate );
    return duplicate;
}

//
//
// CardinalityExpression
//

CardinalityExpression::CardinalityExpression( const Expression::Ptr& expression )
: TargetCallExpression( Node::ID::CARDINALITY_EXPRESSION, std::make_shared< Expressions >() )
{
    arguments()->add( expression );
}

const Expression::Ptr& CardinalityExpression::expression( void ) const
{
    assert( arguments()->size() == 1 );
    return arguments()->front();
}

void CardinalityExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr CardinalityExpression::clone( void ) const
{
    auto duplicate =
        std::make_shared< CardinalityExpression >( expression()->duplicate< Expression >() );

    TargetCallExpression::clone( *duplicate );
    return duplicate;
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
