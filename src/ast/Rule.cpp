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

#include "Rule.h"

#include "Definition.h"

using namespace libcasm_fe;
using namespace Ast;

SkipRule::SkipRule( void )
: Rule( Node::ID::SKIP_RULE )
{
}

void SkipRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

ConditionalRule::ConditionalRule(
    const Expression::Ptr& condition, const Rule::Ptr& thenRule, const Rule::Ptr& elseRule )
: Rule( Node::ID::CONDITIONAL_RULE )
, m_condition( condition )
, m_thenRule( thenRule )
, m_elseRule( elseRule )
{
}

ConditionalRule::ConditionalRule( const Expression::Ptr& condition, const Rule::Ptr& thenRule )
: ConditionalRule( condition, thenRule, std::make_shared< SkipRule >() )
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

Case::Case( Node::ID id, const Rule::Ptr& rule )
: Node( id )
, m_rule( rule )
{
}

const Rule::Ptr& Case::rule() const
{
    return m_rule;
}

ExpressionCase::ExpressionCase( const Expression::Ptr& expression, const Rule::Ptr& rule )
: Case( Node::ID::EXPRESSION_CASE, rule )
, m_expression( expression )
{
}

const Expression::Ptr& ExpressionCase::expression() const
{
    return m_expression;
}

void ExpressionCase::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

DefaultCase::DefaultCase( const Rule::Ptr& rule )
: Case( Node::ID::DEFAULT_CASE, rule )
{
}

void DefaultCase::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

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

LetRule::LetRule(
    const VariableDefinition::Ptr& variable,
    const Expression::Ptr& expression,
    const Rule::Ptr& rule )
: Rule( Node::ID::LET_RULE )
, m_variable( variable )
, m_expression( expression )
, m_rule( rule )
{
}

const VariableDefinition::Ptr& LetRule::variable( void ) const
{
    return m_variable;
}

const Expression::Ptr& LetRule::expression( void ) const
{
    return m_expression;
}

const Rule::Ptr& LetRule::rule( void ) const
{
    return m_rule;
}

void LetRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

ForallRule::ForallRule(
    const VariableDefinition::Ptr& variable,
    const Expression::Ptr& universe,
    const Rule::Ptr& rule )
: ForallRule(
      variable,
      universe,
      std::make_shared< ValueLiteral >(
          libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true ) ),
      rule )
{
}

ForallRule::ForallRule(
    const VariableDefinition::Ptr& variable,
    const Expression::Ptr& universe,
    const Expression::Ptr& condition,
    const Rule::Ptr& rule )
: Rule( Node::ID::FORALL_RULE )
, m_variable( variable )
, m_universe( universe )
, m_condition( condition )
, m_rule( rule )
{
}

const VariableDefinition::Ptr& ForallRule::variable( void ) const
{
    return m_variable;
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

ChooseRule::ChooseRule(
    const VariableDefinition::Ptr& variable,
    const Expression::Ptr& universe,
    const Rule::Ptr& rule )
: Rule( Node::ID::CHOOSE_RULE )
, m_variable( variable )
, m_universe( universe )
, m_rule( rule )
{
}

const VariableDefinition::Ptr& ChooseRule::variable( void ) const
{
    return m_variable;
}

const Expression::Ptr& ChooseRule::universe( void ) const
{
    return m_universe;
}

const Rule::Ptr& ChooseRule::rule( void ) const
{
    return m_rule;
}

void ChooseRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

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

UpdateRule::UpdateRule(
    const DirectCallExpression::Ptr& function, const Expression::Ptr& expression )
: Rule( Node::ID::UPDATE_RULE )
, m_function( function )
, m_expression( expression )
{
}

const DirectCallExpression::Ptr& UpdateRule::function( void ) const
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

CallRule::CallRule( const CallExpression::Ptr& call, Type type )
: Rule( Node::ID::CALL_RULE )
, m_call( call )
, m_type( type )
{
}

const CallExpression::Ptr& CallRule::call( void ) const
{
    return m_call;
}

CallRule::Type CallRule::type( void ) const
{
    return m_type;
}

void CallRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}
