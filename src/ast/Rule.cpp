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

#include "Rule.h"

#include "Definition.h"

using namespace libcasm_fe;
using namespace Ast;

SkipRule::SkipRule( void )
: Rule( Node::ID::SKIP_RULE )
{
}

ConditionalRule::ConditionalRule( const Expression::Ptr& condition,
    const Rule::Ptr& thenRule, const Rule::Ptr& elseRule )
: Rule( Node::ID::CONDITIONAL_RULE )
, m_condition( condition )
, m_thenRule( thenRule )
, m_elseRule( elseRule )
{
}

ConditionalRule::ConditionalRule(
    const Expression::Ptr& condition, const Rule::Ptr& thenRule )
: ConditionalRule( condition, thenRule, nullptr )
{
}

Expression::Ptr ConditionalRule::condition( void ) const
{
    return m_condition;
}

Rule::Ptr ConditionalRule::thenRule( void ) const
{
    return m_thenRule;
}

Rule::Ptr ConditionalRule::elseRule( void ) const
{
    return m_elseRule;
}

CaseRule::CaseRule(
    const Expression::Ptr& expression, const std::vector< Case >& cases )
: Rule( Node::ID::CASE_RULE )
, m_expression( expression )
, m_cases( cases )
{
}

Expression::Ptr CaseRule::expression( void ) const
{
    return m_expression;
}

std::vector< CaseRule::Case > CaseRule::cases( void ) const
{
    return m_cases;
}

LetRule::LetRule( const VariableDefinition::Ptr& variable,
    const Expression::Ptr& expression, const Rule::Ptr& rule )
: Rule( Node::ID::LET_RULE )
, m_variable( variable )
, m_expression( expression )
, m_rule( rule )
{
}

VariableDefinition::Ptr LetRule::variable( void ) const
{
    return m_variable;
}

Expression::Ptr LetRule::expression( void ) const
{
    return m_expression;
}

Rule::Ptr LetRule::rule( void ) const
{
    return m_rule;
}

ForallRule::ForallRule( const VariableDefinition::Ptr& variable,
    const Expression::Ptr& expression, const Rule::Ptr& rule )
: Rule( Node::ID::FORALL_RULE )
, m_variable( variable )
, m_expression( expression )
, m_rule( rule )
{
}

VariableDefinition::Ptr ForallRule::variable( void ) const
{
    return m_variable;
}

Expression::Ptr ForallRule::expression( void ) const
{
    return m_expression;
}

Rule::Ptr ForallRule::rule( void ) const
{
    return m_rule;
}

IterateRule::IterateRule( const Rule::Ptr& rule )
: Rule( Node::ID::ITERATE_RULE )
, m_rule( rule )
{
}

Rule::Ptr IterateRule::rule( void ) const
{
    return m_rule;
}

BlockRule::BlockRule( const Rules::Ptr& rules )
: Rule( Node::ID::BLOCK_RULE )
, m_rules( rules )
{
}

Rules::Ptr BlockRule::rules( void ) const
{
    return m_rules;
}

SequenceRule::SequenceRule( const Rules::Ptr& rules )
: Rule( Node::ID::SEQUENCE_RULE )
, m_rules( rules )
{
}

Rules::Ptr SequenceRule::rules( void ) const
{
    return m_rules;
}

UpdateRule::UpdateRule( const DirectCallExpression::Ptr& function,
    const Expression::Ptr& expression )
: Rule( Node::ID::UPDATE_RULE )
, m_function( function )
, m_expression( expression )
{
}

DirectCallExpression::Ptr UpdateRule::function( void ) const
{
    return m_function;
}

Expression::Ptr UpdateRule::expression( void ) const
{
    return m_expression;
}

CallRule::CallRule( const CallExpression::Ptr& call,
    const std::set< CallExpression::TargetType >& allowedCallTargetTypes )
: Rule( Node::ID::CALL_RULE )
, m_call( call )
, m_allowedCallTargetTypes( allowedCallTargetTypes )
{
}

CallExpression::Ptr CallRule::call( void ) const
{
    return m_call;
}

std::set< CallExpression::TargetType > CallRule::allowedCallTargetTypes(
    void ) const
{
    return m_allowedCallTargetTypes;
}