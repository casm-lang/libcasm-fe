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

PrintRule::PrintRule( const Expression::Ptr& expression )
: Rule( Node::Type::PRINT_RULE )
, m_expression( expression )
, m_filter()
{
}

Expression::Ptr PrintRule::expression() const
{
    return m_expression;
}

void PrintRule::setFilter( const std::string& filter )
{
    m_filter = filter;
}

std::string PrintRule::filter() const
{
    return m_filter;
}

AssertRule::AssertRule( const Expression::Ptr& expression )
: Rule( Node::Type::ASSERT_RULE )
, m_expression( expression )
{
}

Expression::Ptr AssertRule::expression() const
{
    return m_expression;
}

AssureRule::AssureRule( const Expression::Ptr& expression )
: Rule( Node::Type::ASSURE_RULE )
, m_expression( expression )
{
}

Expression::Ptr AssureRule::expression() const
{
    return m_expression;
}

SkipRule::SkipRule()
: Rule( Node::Type::SKIP_RULE )
{
}

DieDieRule::DieDieRule( const Expression::Ptr& expression )
: Rule( Node::Type::DIEDIE_RULE )
, m_expression( expression )
{
}

ImpossibleRule::ImpossibleRule()
: Rule( Node::Type::IMPOSSIBLE_RULE )
{
}

Expression::Ptr DieDieRule::expression() const
{
    return m_expression;
}

ConditionalRule::ConditionalRule( const Expression::Ptr& condition,
    const Rule::Ptr& thenRule, const Rule::Ptr& elseRule )
: Rule( Node::Type::CONDITIONAL_RULE )
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

Expression::Ptr ConditionalRule::condition() const
{
    return m_condition;
}

Rule::Ptr ConditionalRule::thenRule() const
{
    return m_thenRule;
}

Rule::Ptr ConditionalRule::elseRule() const
{
    return m_elseRule;
}

CaseRule::CaseRule(
    const Expression::Ptr& expression, const std::vector< Case >& cases )
: Rule( Node::Type::CASE_RULE )
, m_expression( expression )
, m_cases( cases )
{
}

Expression::Ptr CaseRule::expression() const
{
    return m_expression;
}

std::vector< CaseRule::Case > CaseRule::cases() const
{
    return m_cases;
}

LetRule::LetRule( const VariableDefinition::Ptr& variable,
    const Expression::Ptr& expression, const Rule::Ptr& rule )
: Rule( Node::Type::LET_RULE )
, m_variable( variable )
, m_expression( expression )
, m_rule( rule )
{
}

VariableDefinition::Ptr LetRule::variable() const
{
    return m_variable;
}

Expression::Ptr LetRule::expression() const
{
    return m_expression;
}

Rule::Ptr LetRule::rule() const
{
    return m_rule;
}

ForallRule::ForallRule( const VariableDefinition::Ptr& variable,
    const Expression::Ptr& expression, const Rule::Ptr& rule )
: Rule( Node::Type::FORALL_RULE )
, m_variable( variable )
, m_expression( expression )
, m_rule( rule )
{
}

VariableDefinition::Ptr ForallRule::variable() const
{
    return m_variable;
}

Expression::Ptr ForallRule::expression() const
{
    return m_expression;
}

Rule::Ptr ForallRule::rule() const
{
    return m_rule;
}

IterateRule::IterateRule( const Rule::Ptr& rule )
: Rule( Node::Type::ITERATE_RULE )
, m_rule( rule )
{
}

Rule::Ptr IterateRule::rule() const
{
    return m_rule;
}

BlockRule::BlockRule( const Rules::Ptr& rules )
: Rule( Node::Type::BLOCK_RULE )
, m_rules( rules )
{
}

Rules::Ptr BlockRule::rules() const
{
    return m_rules;
}

SequenceRule::SequenceRule( const Rules::Ptr& rules )
: Rule( Node::Type::SEQUENCE_RULE )
, m_rules( rules )
{
}

Rules::Ptr SequenceRule::rules() const
{
    return m_rules;
}

UpdateRule::UpdateRule( const DirectCallExpression::Ptr& function,
    const Expression::Ptr& expression )
: Rule( Node::Type::UPDATE_RULE )
, m_function( function )
, m_expression( expression )
{
}

DirectCallExpression::Ptr UpdateRule::function() const
{
    return m_function;
}

Expression::Ptr UpdateRule::expression() const
{
    return m_expression;
}
