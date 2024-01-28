//
//  Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#include "Rule.h"

#include <libcasm-fe/ast/Definition>
#include <libcasm-fe/ast/Literal>

using namespace libcasm_fe;
using namespace AST;

//
//
// Rule
//

Rule::Rule( const Node::ID id )
: Node( id )
{
}

void Rule::clone( Rule& duplicate ) const
{
    Node::clone( duplicate );
}

//
//
// SkipRule
//

SkipRule::SkipRule( void )
: Rule( Node::ID::SKIP_RULE )
{
}

void SkipRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr SkipRule::clone( void ) const
{
    auto duplicate = std::make_shared< SkipRule >();

    Rule::clone( *duplicate );
    return duplicate;
}

//
//
// ConditionalRule
//

ConditionalRule::ConditionalRule(
    const Expression::Ptr& condition, const Rule::Ptr& thenRule, const Rule::Ptr& elseRule )
: Rule( Node::ID::CONDITIONAL_RULE )
, m_condition( condition )
, m_thenRule( thenRule )
, m_elseRule( elseRule )
{
}

const Expression::Ptr& ConditionalRule::condition( void ) const
{
    return m_condition;
}

const Rule::Ptr& ConditionalRule::thenRule( void ) const
{
    return m_thenRule;
}

const Rule::Ptr& ConditionalRule::elseRule( void ) const
{
    return m_elseRule;
}

void ConditionalRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ConditionalRule::clone( void ) const
{
    auto duplicate = std::make_shared< ConditionalRule >(
        condition()->duplicate< Expression >(),
        thenRule()->duplicate< Rule >(),
        elseRule()->duplicate< Rule >() );

    Node::clone( *duplicate );
    return duplicate;
}

//
//
// Case
//

Case::Case( Node::ID id, const Rule::Ptr& rule )
: Node( id )
, m_rule( rule )
{
}

const Rule::Ptr& Case::rule( void ) const
{
    return m_rule;
}

void Case::clone( Case& duplicate ) const
{
    Node::clone( duplicate );
}

//
//
// DefaultCase
//

DefaultCase::DefaultCase( const Rule::Ptr& rule )
: Case( Node::ID::DEFAULT_CASE, rule )
{
}

void DefaultCase::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr DefaultCase::clone( void ) const
{
    auto duplicate = std::make_shared< DefaultCase >( rule()->duplicate< Rule >() );

    Case::clone( *duplicate );
    return duplicate;
}

//
//
// ExpressionCase
//

ExpressionCase::ExpressionCase( const Expression::Ptr& expression, const Rule::Ptr& rule )
: Case( Node::ID::EXPRESSION_CASE, rule )
, m_expression( expression )
{
}

const Expression::Ptr& ExpressionCase::expression( void ) const
{
    return m_expression;
}

void ExpressionCase::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ExpressionCase::clone( void ) const
{
    auto duplicate = std::make_shared< ExpressionCase >(
        expression()->duplicate< Expression >(), rule()->duplicate< Rule >() );

    Case::clone( *duplicate );
    return duplicate;
}

//
//
// CaseRule
//

CaseRule::CaseRule( const Expression::Ptr& expression, const Cases::Ptr& cases )
: Rule( Node::ID::CASE_RULE )
, m_expression( expression )
, m_cases( cases )
{
}

const Expression::Ptr& CaseRule::expression( void ) const
{
    return m_expression;
}

const Cases::Ptr& CaseRule::cases( void ) const
{
    return m_cases;
}

void CaseRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr CaseRule::clone( void ) const
{
    auto duplicate = std::make_shared< CaseRule >(
        expression()->duplicate< Expression >(), cases()->duplicate< Cases >() );

    Rule::clone( *duplicate );
    return duplicate;
}

//
//
// LetRule
//

LetRule::LetRule( const VariableBindings::Ptr& variableBindings, const Rule::Ptr& rule )
: Rule( Node::ID::LET_RULE )
, m_variableBindings( variableBindings )
, m_rule( rule )
{
}

const VariableBindings::Ptr& LetRule::variableBindings( void ) const
{
    return m_variableBindings;
}

const Rule::Ptr& LetRule::rule( void ) const
{
    return m_rule;
}

void LetRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr LetRule::clone( void ) const
{
    auto duplicate = std::make_shared< LetRule >(
        variableBindings()->duplicate< VariableBindings >(), rule()->duplicate< Rule >() );

    Rule::clone( *duplicate );
    return duplicate;
}

//
//
// LocalRule
//

LocalRule::LocalRule( const FunctionDefinitions::Ptr& localFunctions, const Rule::Ptr& rule )
: Rule( Node::ID::LOCAL_RULE )
, m_localFunctions( localFunctions )
, m_rule( rule )
{
}

const FunctionDefinitions::Ptr& LocalRule::localFunctions( void ) const
{
    return m_localFunctions;
}

const Rule::Ptr& LocalRule::rule( void ) const
{
    return m_rule;
}

void LocalRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr LocalRule::clone( void ) const
{
    auto duplicate = std::make_shared< LocalRule >(
        localFunctions()->duplicate< FunctionDefinitions >(), rule()->duplicate< Rule >() );

    Rule::clone( *duplicate );
    return duplicate;
}

//
//
// ForallRule
//

ForallRule::ForallRule(
    const VariableDefinitions::Ptr& variables,
    const Expression::Ptr& universe,
    const Expression::Ptr& condition,
    const Rule::Ptr& rule )
: Rule( Node::ID::FORALL_RULE )
, m_variables( variables )
, m_universe( universe )
, m_condition( condition )
, m_rule( rule )
{
}

const VariableDefinitions::Ptr& ForallRule::variables( void ) const
{
    return m_variables;
}

const Expression::Ptr& ForallRule::universe( void ) const
{
    return m_universe;
}

const Expression::Ptr& ForallRule::condition( void ) const
{
    return m_condition;
}

const Rule::Ptr& ForallRule::rule( void ) const
{
    return m_rule;
}

void ForallRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ForallRule::clone( void ) const
{
    auto duplicate = std::make_shared< ForallRule >(
        variables()->duplicate< VariableDefinitions >(),
        universe()->duplicate< Expression >(),
        condition()->duplicate< Expression >(),
        rule()->duplicate< Rule >() );

    Rule::clone( *duplicate );
    return duplicate;
}

//
//
// ChooseRule
//

ChooseRule::ChooseRule( const VariableSelection::Ptr& variableSelection, const Rule::Ptr& rule )
: Rule( Node::ID::CHOOSE_RULE )
, m_variableSelection( variableSelection )
, m_rule( rule )
{
}

const VariableSelection::Ptr& ChooseRule::variableSelection( void ) const
{
    return m_variableSelection;
}

const Rule::Ptr& ChooseRule::rule( void ) const
{
    return m_rule;
}

void ChooseRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr ChooseRule::clone( void ) const
{
    auto duplicate = std::make_shared< ChooseRule >(
        variableSelection()->duplicate< VariableSelection >(), rule()->duplicate< Rule >() );

    Rule::clone( *duplicate );
    return duplicate;
}

//
//
// IterateRule
//

IterateRule::IterateRule( const Rule::Ptr& rule )
: Rule( Node::ID::ITERATE_RULE )
, m_rule( rule )
{
}

const Rule::Ptr& IterateRule::rule( void ) const
{
    return m_rule;
}

void IterateRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr IterateRule::clone( void ) const
{
    auto duplicate = std::make_shared< IterateRule >( rule()->duplicate< Rule >() );

    Rule::clone( *duplicate );
    return duplicate;
}

//
//
// BlockRule
//

BlockRule::BlockRule( const Rules::Ptr& rules )
: Rule( Node::ID::BLOCK_RULE )
, m_rules( rules )
{
}

const Rules::Ptr& BlockRule::rules( void ) const
{
    return m_rules;
}

void BlockRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr BlockRule::clone( void ) const
{
    auto duplicate = std::make_shared< BlockRule >( rules()->duplicate< Rules >() );

    Rule::clone( *duplicate );
    return duplicate;
}

//
//
// SequenceRule
//

SequenceRule::SequenceRule( const Rules::Ptr& rules )
: Rule( Node::ID::SEQUENCE_RULE )
, m_rules( rules )
{
}

const Rules::Ptr& SequenceRule::rules( void ) const
{
    return m_rules;
}

void SequenceRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr SequenceRule::clone( void ) const
{
    auto duplicate = std::make_shared< SequenceRule >( rules()->duplicate< Rules >() );

    Rule::clone( *duplicate );
    return duplicate;
}

//
//
// UpdateRule
//

UpdateRule::UpdateRule( const CallExpression::Ptr& function, const Expression::Ptr& expression )
: Rule( Node::ID::UPDATE_RULE )
, m_function( function )
, m_expression( expression )
{
}

const CallExpression::Ptr& UpdateRule::function( void ) const
{
    return m_function;
}

const Expression::Ptr& UpdateRule::expression( void ) const
{
    return m_expression;
}

void UpdateRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr UpdateRule::clone( void ) const
{
    auto duplicate = std::make_shared< UpdateRule >(
        function()->duplicate< CallExpression >(), expression()->duplicate< Expression >() );

    Rule::clone( *duplicate );
    return duplicate;
}

//
//
// CallRule
//

CallRule::CallRule( const CallExpression::Ptr& call )
: Rule( Node::ID::CALL_RULE )
, m_call( call )
{
}

const CallExpression::Ptr& CallRule::call( void ) const
{
    return m_call;
}

void CallRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

Node::Ptr CallRule::clone( void ) const
{
    auto duplicate = std::make_shared< CallRule >( call()->duplicate< CallExpression >() );

    Rule::clone( *duplicate );
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
