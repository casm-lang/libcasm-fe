//
//  Copyright (C) 2014-2020 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
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

#include <libcasm-fe/cst/Definition>
#include <libcasm-fe/cst/Literal>
#include <libcasm-fe/cst/Token>
#include <libcasm-fe/cst/Type>

#include "../various/GrammarToken.h"

using namespace libcasm_fe;
using namespace CST;

//
//
// Expression
//

Expression::Expression( Node::ID id )
: TypedPropertyNode( id )
, m_delimiterToken( Token::unresolved() )
{
}

void Expression::setDelimiterToken( const Token::Ptr& delimiterToken )
{
    assert( m_delimiterToken->token() == Grammar::Token::UNRESOLVED );
    m_delimiterToken = delimiterToken;
}

const Token::Ptr& Expression::delimiterToken( void ) const
{
    return m_delimiterToken;
}

void Expression::clone( Expression& duplicate ) const
{
    TypedPropertyNode::clone( duplicate );
    duplicate.setDelimiterToken( delimiterToken() );
}

//
//
// AbstractExpression
//

AbstractExpression::AbstractExpression( const Token::Ptr& abstractToken )
: Expression( Node::ID::ABSTRACT_EXPRESSION )
, m_abstractToken( abstractToken )
{
}

const Token::Ptr& AbstractExpression::abstractToken( void ) const
{
    return m_abstractToken;
}

void AbstractExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr AbstractExpression::clone( void ) const
{
    auto duplicate = std::make_shared< AbstractExpression >( abstractToken() );

    Expression::clone( *duplicate );
    return duplicate;
}

//
//
// EmbracedExpression
//

EmbracedExpression::EmbracedExpression(
    const Token::Ptr& leftBraceToken,
    const Expression::Ptr& expression,
    const Token::Ptr& rightBraceToken )
: Expression( Node::ID::EMBRACED_EXPRESSION )
, m_expression( expression )
, m_leftBraceToken( leftBraceToken )
, m_rightBraceToken( rightBraceToken )
{
}

const Expression::Ptr& EmbracedExpression::expression( void ) const
{
    return m_expression;
}

const Token::Ptr& EmbracedExpression::leftBraceToken( void ) const
{
    return m_leftBraceToken;
}

const Token::Ptr& EmbracedExpression::rightBraceToken( void ) const
{
    return m_rightBraceToken;
}

void EmbracedExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr EmbracedExpression::clone( void ) const
{
    auto duplicate = std::make_shared< EmbracedExpression >(
        leftBraceToken(), expression()->duplicate< Expression >(), rightBraceToken() );

    Expression::clone( *duplicate );
    return duplicate;
}

//
//
// NamedExpression
//

NamedExpression::NamedExpression(
    const Identifier::Ptr& identifier,
    const Token::Ptr& colonToken,
    const Expression::Ptr& expression )
: Expression( Node::ID::NAMED_EXPRESSION )
, m_identifier( identifier )
, m_expression( expression )
, m_colonToken( colonToken )
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

const Token::Ptr& NamedExpression::colonToken( void ) const
{
    return m_colonToken;
}

void NamedExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr NamedExpression::clone( void ) const
{
    auto duplicate = std::make_shared< NamedExpression >(
        identifier()->duplicate< Identifier >(),
        colonToken(),
        expression()->duplicate< Expression >() );

    Expression::clone( *duplicate );
    return duplicate;
}

//
//
// MappedExpression
//

MappedExpression::MappedExpression(
    const Token::Ptr& leftBracketToken,
    const Expressions::Ptr& arguments,
    const Token::Ptr& rightBracketToken,
    const Token::Ptr& mapsToken,
    const Expression::Ptr& value )
: Expression( Node::ID::MAPPED_EXPRESSION )
, m_arguments( arguments )
, m_value( value )
, m_leftBracketToken( leftBracketToken )
, m_rightBracketToken( rightBracketToken )
, m_mapsToken( mapsToken )
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

const Token::Ptr& MappedExpression::leftBracketToken( void ) const
{
    return m_leftBracketToken;
}

const Token::Ptr& MappedExpression::rightBracketToken( void ) const
{
    return m_rightBracketToken;
}

const Token::Ptr& MappedExpression::mapsToken( void ) const
{
    return m_mapsToken;
}

void MappedExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr MappedExpression::clone( void ) const
{
    auto duplicate = std::make_shared< MappedExpression >(
        leftBracketToken(),
        arguments()->duplicate< Expressions >(),
        rightBracketToken(),
        mapsToken(),
        value()->duplicate< Expression >() );

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
, m_leftBracketToken( Token::unresolved() )
, m_rightBracketToken( Token::unresolved() )
{
}

const Expressions::Ptr& CallExpression::arguments( void ) const
{
    return m_arguments;
}

void CallExpression::setLeftBracketToken( const Token::Ptr& leftBracketToken )
{
    m_leftBracketToken = leftBracketToken;
}

const Token::Ptr& CallExpression::leftBracketToken( void ) const
{
    return m_leftBracketToken;
}

void CallExpression::setRightBracketToken( const Token::Ptr& rightBracketToken )
{
    m_rightBracketToken = rightBracketToken;
}

const Token::Ptr& CallExpression::rightBracketToken( void ) const
{
    return m_rightBracketToken;
}

void CallExpression::clone( CallExpression& duplicate ) const
{
    Expression::clone( duplicate );
    duplicate.setLeftBracketToken( leftBracketToken() );
    duplicate.setRightBracketToken( rightBracketToken() );
}

//
//
// TargetCallExpression
//

TargetCallExpression::TargetCallExpression( const Node::ID id, const Expressions::Ptr& arguments )
: CallExpression( id, arguments )
, m_targetDefinition()
{
}

TargetCallExpression::TargetCallExpression( const Node::ID id )
: TargetCallExpression( id, std::make_shared< Expressions >() )
{
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

void TargetCallExpression::clone( TargetCallExpression& duplicate ) const
{
    CallExpression::clone( duplicate );
    duplicate.setTargetDefinition( m_targetDefinition );
}

//
//
// DirectCallExpression
//

DirectCallExpression::DirectCallExpression(
    const IdentifierPath::Ptr& identifier,
    const Token::Ptr& leftBracketToken,
    const Expressions::Ptr& arguments,
    const Token::Ptr& rightBracketToken )
: TargetCallExpression( Node::ID::DIRECT_CALL_EXPRESSION, arguments )
, m_identifier( identifier )
, m_targetType( TargetType::UNKNOWN )
{
    setLeftBracketToken( leftBracketToken );
    setRightBracketToken( rightBracketToken );
}

DirectCallExpression::DirectCallExpression( const IdentifierPath::Ptr& identifier )
: DirectCallExpression(
      identifier, Token::unresolved(), std::make_shared< Expressions >(), Token::unresolved() )
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

void DirectCallExpression::setTargetType( TargetType targetType )
{
    m_targetType = targetType;
}

DirectCallExpression::TargetType DirectCallExpression::targetType( void ) const
{
    return m_targetType;
}

std::string DirectCallExpression::targetTypeName( void ) const
{
    return targetTypeString( m_targetType );
}

std::string DirectCallExpression::targetTypeString( const TargetType targetType )
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
        case TargetType::THIS:
        {
            return "this";
        }
        case TargetType::UNKNOWN:
        {
            return "unknown";
        }
    }

    assert( !" internal error! " );
    return std::string();
}

void DirectCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr DirectCallExpression::clone( void ) const
{
    auto duplicate = std::make_shared< DirectCallExpression >(
        identifier()->duplicate< IdentifierPath >(),
        leftBracketToken(),
        arguments()->duplicate< Expressions >(),
        leftBracketToken() );

    TargetCallExpression::clone( *duplicate );
    duplicate->setTargetType( targetType() );
    return duplicate;
}

//
//
// MethodCallExpression
//

MethodCallExpression::MethodCallExpression(
    const Expression::Ptr& object,
    const Token::Ptr& dotToken,
    const Identifier::Ptr& methodName,
    const Expressions::Ptr& arguments )
: TargetCallExpression( Node::ID::METHOD_CALL_EXPRESSION, arguments )
, m_object( object )
, m_methodName( methodName )
, m_dotToken( dotToken )
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

const Token::Ptr& MethodCallExpression::dotToken( void ) const
{
    return m_dotToken;
}

void MethodCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr MethodCallExpression::clone( void ) const
{
    auto duplicate = std::make_shared< MethodCallExpression >(
        object()->duplicate< Expression >(),
        dotToken(),
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
    const Expression::Ptr& object,
    const Token::Ptr& dotToken,
    const std::shared_ptr< Literal >& literal )
: TargetCallExpression( Node::ID::LITERAL_CALL_EXPRESSION, std::make_shared< Expressions >() )
, m_literal( literal )
, m_dotToken( dotToken )
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

const Token::Ptr& LiteralCallExpression::dotToken( void ) const
{
    return m_dotToken;
}

void LiteralCallExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr LiteralCallExpression::clone( void ) const
{
    auto duplicate = std::make_shared< LiteralCallExpression >(
        object()->duplicate< Expression >(), dotToken(), literal()->duplicate< Literal >() );

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
    const Expression::Ptr& fromExpression, const Token::Ptr& asToken, const Type::Ptr& asType )
: TargetCallExpression( Node::ID::TYPE_CASTING_EXPRESSION, std::make_shared< Expressions >() )
, m_fromExpression( fromExpression )
, m_asType( asType )
, m_asToken( asToken )
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

const Token::Ptr& TypeCastingExpression::asToken( void ) const
{
    return m_asToken;
}

void TypeCastingExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr TypeCastingExpression::clone( void ) const
{
    auto duplicate = std::make_shared< TypeCastingExpression >(
        fromExpression()->duplicate< Expression >(), asToken(), asType()->duplicate< Type >() );

    TargetCallExpression::clone( *duplicate );
    return duplicate;
}

//
//
// UnaryExpression
//

UnaryExpression::UnaryExpression(
    const Token::Ptr& operationToken, const Expression::Ptr& expression )
: TargetCallExpression( Node::ID::UNARY_EXPRESSION, std::make_shared< Expressions >() )
, m_expression( expression )
, m_operationToken( operationToken )
{
}

const Expression::Ptr& UnaryExpression::expression( void ) const
{
    return m_expression;
}

const Token::Ptr& UnaryExpression::operationToken( void ) const
{
    return m_operationToken;
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
    const Expression::Ptr& left, const Token::Ptr& operationToken, const Expression::Ptr& right )
: TargetCallExpression( Node::ID::BINARY_EXPRESSION, std::make_shared< Expressions >() )
, m_left( left )
, m_right( right )
, m_operationToken( operationToken )
{
}

const Expression::Ptr& BinaryExpression::left( void ) const
{
    return m_left;
}

const Expression::Ptr& BinaryExpression::right( void ) const
{
    return m_right;
}

const Token::Ptr& BinaryExpression::operationToken( void ) const
{
    return m_operationToken;
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
    const VariableDefinition::Ptr& variable,
    const Token::Ptr& equalToken,
    const Expression::Ptr& expression )
: TypedNode( Node::ID::VARIABLE_BINDING )
, m_variable( variable )
, m_expression( expression )
, m_equalToken( equalToken )
, m_delimiterToken( Token::unresolved() )
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

const Token::Ptr& VariableBinding::equalToken( void ) const
{
    return m_equalToken;
}

void VariableBinding::setDelimiterToken( const Token::Ptr& delimiterToken )
{
    assert( m_delimiterToken->token() == Grammar::Token::UNRESOLVED );
    m_delimiterToken = delimiterToken;
}

const Token::Ptr& VariableBinding::delimiterToken( void ) const
{
    return m_delimiterToken;
}

void VariableBinding::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr VariableBinding::clone( void ) const
{
    auto duplicate = std::make_shared< VariableBinding >(
        variable()->duplicate< VariableDefinition >(),
        equalToken(),
        expression()->duplicate< Expression >() );

    TypedNode::clone( *duplicate );
    duplicate->setDelimiterToken( delimiterToken() );
    return duplicate;
}

//
//
// LetExpression
//

LetExpression::LetExpression(
    const Token::Ptr& letToken,
    const VariableBindings::Ptr& variableBindings,
    const Token::Ptr& inToken,
    const Expression::Ptr& expression )
: Expression( Node::ID::LET_EXPRESSION )
, m_variableBindings( variableBindings )
, m_expression( expression )
, m_letToken( letToken )
, m_inToken( inToken )
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

const Token::Ptr& LetExpression::letToken( void ) const
{
    return m_letToken;
}

const Token::Ptr& LetExpression::inToken( void ) const
{
    return m_inToken;
}

void LetExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr LetExpression::clone( void ) const
{
    auto duplicate = std::make_shared< LetExpression >(
        letToken(),
        variableBindings()->duplicate< VariableBindings >(),
        inToken(),
        expression()->duplicate< Expression >() );

    Expression::clone( *duplicate );
    return duplicate;
}

//
//
// ConditionalExpression
//

ConditionalExpression::ConditionalExpression(
    const Token::Ptr& ifToken,
    const Expression::Ptr& condition,
    const Token::Ptr& thenToken,
    const Expression::Ptr& thenExpression,
    const Token::Ptr& elseToken,
    const Expression::Ptr& elseExpression )
: Expression( Node::ID::CONDITIONAL_EXPRESSION )
, m_condition( condition )
, m_thenExpression( thenExpression )
, m_elseExpression( elseExpression )
, m_ifToken( ifToken )
, m_thenToken( thenToken )
, m_elseToken( elseToken )
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

const Token::Ptr& ConditionalExpression::ifToken( void ) const
{
    return m_ifToken;
}

const Token::Ptr& ConditionalExpression::thenToken( void ) const
{
    return m_thenToken;
}

const Token::Ptr& ConditionalExpression::elseToken( void ) const
{
    return m_elseToken;
}

void ConditionalExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ConditionalExpression::clone( void ) const
{
    auto duplicate = std::make_shared< ConditionalExpression >(
        ifToken(),
        condition()->duplicate< Expression >(),
        thenToken(),
        thenExpression()->duplicate< Expression >(),
        elseToken(),
        elseExpression()->duplicate< Expression >() );

    Expression::clone( *duplicate );
    return duplicate;
}

//
//
// ChooseExpression
//

ChooseExpression::ChooseExpression(
    const Token::Ptr& chooseToken,
    const VariableDefinitions::Ptr& variables,
    const Token::Ptr& inToken,
    const Expression::Ptr& universe,
    const Token::Ptr& doToken,
    const Expression::Ptr& expression )
: Expression( Node::ID::CHOOSE_EXPRESSION )
, m_variables( variables )
, m_universe( universe )
, m_expression( expression )
, m_chooseToken( chooseToken )
, m_inToken( inToken )
, m_doToken( doToken )
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

const Token::Ptr& ChooseExpression::chooseToken( void ) const
{
    return m_chooseToken;
}

const Token::Ptr& ChooseExpression::inToken( void ) const
{
    return m_inToken;
}

const Token::Ptr& ChooseExpression::doToken( void ) const
{
    return m_doToken;
}

void ChooseExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ChooseExpression::clone( void ) const
{
    auto duplicate = std::make_shared< ChooseExpression >(
        chooseToken(),
        variables()->duplicate< VariableDefinitions >(),
        inToken(),
        universe()->duplicate< Expression >(),
        doToken(),
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
    const Token::Ptr& quantifierToken,
    const VariableDefinitions::Ptr& predicateVariables,
    const Token::Ptr& inToken,
    const Expression::Ptr& universe,
    const Token::Ptr& doToken,
    const Expression::Ptr& proposition )
: Expression( id )
, m_predicateVariables( predicateVariables )
, m_universe( universe )
, m_proposition( proposition )
, m_quantifierToken( quantifierToken )
, m_inToken( inToken )
, m_doToken( doToken )
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

const Token::Ptr& QuantifierExpression::quantifierToken( void ) const
{
    return m_quantifierToken;
}

const Token::Ptr& QuantifierExpression::inToken( void ) const
{
    return m_inToken;
}

const Token::Ptr& QuantifierExpression::doToken( void ) const
{
    return m_doToken;
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
    const Token::Ptr& forallToken,
    const std::shared_ptr< VariableDefinitions >& predicateVariables,
    const Token::Ptr& inToken,
    const Expression::Ptr& universe,
    const Token::Ptr& holdsToken,
    const Expression::Ptr& proposition )
: QuantifierExpression(
      Node::ID::UNIVERSAL_QUANTIFIER_EXPRESSION,
      forallToken,
      predicateVariables,
      inToken,
      universe,
      holdsToken,
      proposition )
{
}

void UniversalQuantifierExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr UniversalQuantifierExpression::clone( void ) const
{
    auto duplicate = std::make_shared< UniversalQuantifierExpression >(
        quantifierToken(),
        predicateVariables()->duplicate< VariableDefinitions >(),
        inToken(),
        universe()->duplicate< Expression >(),
        doToken(),
        proposition()->duplicate< Expression >() );

    QuantifierExpression::clone( *duplicate );
    return duplicate;
}

//
//
// ExistentialQuantifierExpression
//

ExistentialQuantifierExpression::ExistentialQuantifierExpression(
    const Token::Ptr& existsToken,
    const std::shared_ptr< VariableDefinitions >& predicateVariables,
    const Token::Ptr& inToken,
    const Expression::Ptr& universe,
    const Token::Ptr& withToken,
    const Expression::Ptr& proposition )
: QuantifierExpression(
      Node::ID::EXISTENTIAL_QUANTIFIER_EXPRESSION,
      existsToken,
      predicateVariables,
      inToken,
      universe,
      withToken,
      proposition )
{
}

void ExistentialQuantifierExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ExistentialQuantifierExpression::clone( void ) const
{
    auto duplicate = std::make_shared< ExistentialQuantifierExpression >(
        quantifierToken(),
        predicateVariables()->duplicate< VariableDefinitions >(),
        inToken(),
        universe()->duplicate< Expression >(),
        doToken(),
        proposition()->duplicate< Expression >() );

    QuantifierExpression::clone( *duplicate );
    return duplicate;
}

//
//
// CardinalityExpression
//

CardinalityExpression::CardinalityExpression(
    const Token::Ptr& leftVerticalBarToken,
    const Expression::Ptr& expression,
    const Token::Ptr& rightVerticalBarToken )
: TargetCallExpression( Node::ID::CARDINALITY_EXPRESSION, std::make_shared< Expressions >() )
, m_leftVerticalBarToken( leftVerticalBarToken )
, m_rightVerticalBarToken( rightVerticalBarToken )
{
    arguments()->add( expression );
}

const Expression::Ptr& CardinalityExpression::expression( void ) const
{
    assert( arguments()->size() == 1 );
    return arguments()->front();
}

const Token::Ptr& CardinalityExpression::leftVerticalBarToken( void ) const
{
    return m_leftVerticalBarToken;
}

const Token::Ptr& CardinalityExpression::rightVerticalBarToken( void ) const
{
    return m_rightVerticalBarToken;
}

void CardinalityExpression::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr CardinalityExpression::clone( void ) const
{
    auto duplicate = std::make_shared< CardinalityExpression >(
        leftVerticalBarToken(), expression()->duplicate< Expression >(), leftVerticalBarToken() );

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
