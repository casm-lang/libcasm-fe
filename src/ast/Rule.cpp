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

#include "Rule.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/ast/Definition>
#include <libcasm-fe/ast/Literal>
#include <libcasm-fe/ast/Token>

using namespace libcasm_fe;
using namespace Ast;

//
//
// SkipRule
//

SkipRule::SkipRule( const Token::Ptr& skipToken )
: Rule( Node::ID::SKIP_RULE )
, m_skipToken( skipToken )
{
}

SkipRule::SkipRule( void )
: SkipRule( Token::unresolved() )
{
}

const Token::Ptr& SkipRule::skipToken( void ) const
{
    return m_skipToken;
}

void SkipRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// ConditionalRule
//

ConditionalRule::ConditionalRule(
    const Token::Ptr& ifToken,
    const Expression::Ptr& condition,
    const Token::Ptr& thenToken,
    const Rule::Ptr& thenRule,
    const Token::Ptr& elseToken,
    const Rule::Ptr& elseRule )
: Rule( Node::ID::CONDITIONAL_RULE )
, m_condition( condition )
, m_thenRule( thenRule )
, m_elseRule( elseRule )
, m_ifToken( ifToken )
, m_thenToken( thenToken )
, m_elseToken( elseToken )
{
}

ConditionalRule::ConditionalRule(
    const Token::Ptr& ifToken,
    const Expression::Ptr& condition,
    const Token::Ptr& thenToken,
    const Rule::Ptr& thenRule )
: ConditionalRule(
      ifToken, condition, thenToken, thenRule, Token::unresolved(), std::make_shared< SkipRule >() )
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

const Token::Ptr& ConditionalRule::ifToken( void ) const
{
    return m_ifToken;
}

const Token::Ptr& ConditionalRule::thenToken( void ) const
{
    return m_thenToken;
}

const Token::Ptr& ConditionalRule::elseToken( void ) const
{
    return m_elseToken;
}

void ConditionalRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// Case
//

Case::Case( Node::ID id, const Token::Ptr& colonToken, const Rule::Ptr& rule )
: Node( id )
, m_rule( rule )
, m_colonToken( colonToken )
{
}

const Rule::Ptr& Case::rule( void ) const
{
    return m_rule;
}

const Token::Ptr& Case::colonToken( void ) const
{
    return m_colonToken;
}

//
//
// DefaultCase
//

DefaultCase::DefaultCase(
    const Token::Ptr& labelToken, const Token::Ptr& colonToken, const Rule::Ptr& rule )
: Case( Node::ID::DEFAULT_CASE, colonToken, rule )
, m_labelToken( labelToken )
{
}

const Token::Ptr& DefaultCase::labelToken( void ) const
{
    return m_labelToken;
}

void DefaultCase::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// ExpressionCase
//

ExpressionCase::ExpressionCase(
    const Expression::Ptr& expression, const Token::Ptr& colonToken, const Rule::Ptr& rule )
: Case( Node::ID::EXPRESSION_CASE, colonToken, rule )
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

//
//
// CaseRule
//

CaseRule::CaseRule(
    const Token::Ptr& caseToken,
    const Expression::Ptr& expression,
    const Token::Ptr& ofToken,
    const Token::Ptr& leftBraceToken,
    const Cases::Ptr& cases,
    const Token::Ptr& rightBraceToken )
: Rule( Node::ID::CASE_RULE )
, m_expression( expression )
, m_cases( cases )
, m_caseToken( caseToken )
, m_ofToken( ofToken )
, m_leftBraceToken( leftBraceToken )
, m_rightBraceToken( rightBraceToken )
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

const Token::Ptr& CaseRule::caseToken( void ) const
{
    return m_caseToken;
}

const Token::Ptr& CaseRule::ofToken( void ) const
{
    return m_ofToken;
}

const Token::Ptr& CaseRule::leftBraceToken( void ) const
{
    return m_leftBraceToken;
}

const Token::Ptr& CaseRule::rightBraceToken( void ) const
{
    return m_rightBraceToken;
}

void CaseRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// LetRule
//

LetRule::LetRule(
    const Token::Ptr& letToken,
    const VariableBindings::Ptr& variableBindings,
    const Token::Ptr& inToken,
    const Rule::Ptr& rule )
: Rule( Node::ID::LET_RULE )
, m_variableBindings( variableBindings )
, m_rule( rule )
, m_letToken( letToken )
, m_inToken( inToken )
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

const Token::Ptr& LetRule::letToken( void ) const
{
    return m_letToken;
}

const Token::Ptr& LetRule::inToken( void ) const
{
    return m_inToken;
}

void LetRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// LocalRule
//

LocalRule::LocalRule(
    const Token::Ptr& localToken,
    const FunctionDefinitions::Ptr& localFunctions,
    const Token::Ptr& inToken,
    const Rule::Ptr& rule )
: Rule( Node::ID::LOCAL_RULE )
, m_localFunctions( localFunctions )
, m_rule( rule )
, m_localToken( localToken )
, m_inToken( inToken )
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

const Token::Ptr& LocalRule::localToken( void ) const
{
    return m_localToken;
}

const Token::Ptr& LocalRule::inToken( void ) const
{
    return m_inToken;
}

void LocalRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// ForallRule
//

ForallRule::ForallRule(
    const Token::Ptr& forallToken,
    const VariableDefinitions::Ptr& variables,
    const Token::Ptr& inToken,
    const Expression::Ptr& universe,
    const Token::Ptr& doToken,
    const Rule::Ptr& rule )
: ForallRule(
      forallToken,
      variables,
      inToken,
      universe,
      Token::unresolved(),
      std::make_shared< ValueLiteral >(
          libstdhl::Memory::get< libcasm_ir::BooleanConstant >( true ) ),
      doToken,
      rule )
{
}

ForallRule::ForallRule(
    const Token::Ptr& forallToken,
    const VariableDefinitions::Ptr& variables,
    const Token::Ptr& inToken,
    const Expression::Ptr& universe,
    const Token::Ptr& withToken,
    const Expression::Ptr& condition,
    const Token::Ptr& doToken,
    const Rule::Ptr& rule )
: Rule( Node::ID::FORALL_RULE )
, m_variables( variables )
, m_universe( universe )
, m_condition( condition )
, m_rule( rule )
, m_forallToken( forallToken )
, m_inToken( inToken )
, m_withToken( withToken )
, m_doToken( doToken )
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

const Token::Ptr& ForallRule::forallToken( void ) const
{
    return m_forallToken;
}

const Token::Ptr& ForallRule::inToken( void ) const
{
    return m_inToken;
}

const Token::Ptr& ForallRule::withToken( void ) const
{
    return m_withToken;
}

const Token::Ptr& ForallRule::doToken( void ) const
{
    return m_doToken;
}

void ForallRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// ChooseRule
//

ChooseRule::ChooseRule(
    const Token::Ptr& chooseToken,
    const VariableDefinitions::Ptr& variables,
    const Token::Ptr& inToken,
    const Expression::Ptr& universe,
    const Token::Ptr& doToken,
    const Rule::Ptr& rule )
: Rule( Node::ID::CHOOSE_RULE )
, m_variables( variables )
, m_universe( universe )
, m_rule( rule )
, m_chooseToken( chooseToken )
, m_inToken( inToken )
, m_doToken( doToken )
{
}

const VariableDefinitions::Ptr& ChooseRule::variables( void ) const
{
    return m_variables;
}

const Expression::Ptr& ChooseRule::universe( void ) const
{
    return m_universe;
}

const Rule::Ptr& ChooseRule::rule( void ) const
{
    return m_rule;
}

const Token::Ptr& ChooseRule::chooseToken( void ) const
{
    return m_chooseToken;
}

const Token::Ptr& ChooseRule::inToken( void ) const
{
    return m_inToken;
}

const Token::Ptr& ChooseRule::doToken( void ) const
{
    return m_doToken;
}

void ChooseRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// IterateRule
//

IterateRule::IterateRule( const Token::Ptr& iterateToken, const Rule::Ptr& rule )
: Rule( Node::ID::ITERATE_RULE )
, m_rule( rule )
, m_iterateToken( iterateToken )
{
}

const Rule::Ptr& IterateRule::rule( void ) const
{
    return m_rule;
}

const Token::Ptr& IterateRule::iterateToken( void ) const
{
    return m_iterateToken;
}

void IterateRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// BlockRule
//

BlockRule::BlockRule(
    const Token::Ptr& leftBraceToken, const Rules::Ptr& rules, const Token::Ptr& rightBraceToken )
: Rule( Node::ID::BLOCK_RULE )
, m_rules( rules )
, m_leftBraceToken( leftBraceToken )
, m_rightBraceToken( rightBraceToken )
{
}

const Rules::Ptr& BlockRule::rules( void ) const
{
    return m_rules;
}

const Token::Ptr& BlockRule::leftBraceToken( void ) const
{
    return m_leftBraceToken;
}

const Token::Ptr& BlockRule::rightBraceToken( void ) const
{
    return m_rightBraceToken;
}

void BlockRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// SequenceRule
//

SequenceRule::SequenceRule(
    const Token::Ptr& leftBraceToken, const Rules::Ptr& rules, const Token::Ptr& rightBraceToken )
: Rule( Node::ID::SEQUENCE_RULE )
, m_rules( rules )
, m_leftBraceToken( leftBraceToken )
, m_rightBraceToken( rightBraceToken )
{
}

const Rules::Ptr& SequenceRule::rules( void ) const
{
    return m_rules;
}

const Token::Ptr& SequenceRule::leftBraceToken( void ) const
{
    return m_leftBraceToken;
}

const Token::Ptr& SequenceRule::rightBraceToken( void ) const
{
    return m_rightBraceToken;
}

void SequenceRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
}

//
//
// UpdateRule
//

UpdateRule::UpdateRule(
    const DirectCallExpression::Ptr& function,
    const Token::Ptr& updateToken,
    const Expression::Ptr& expression )
: Rule( Node::ID::UPDATE_RULE )
, m_function( function )
, m_expression( expression )
, m_updateToken( updateToken )
{
}

UpdateRule::UpdateRule(
    const DirectCallExpression::Ptr& function, const Expression::Ptr& expression )
: UpdateRule( function, Token::unresolved(), expression )
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

const Token::Ptr& UpdateRule::updateToken( void ) const
{
    return m_updateToken;
}

void UpdateRule::accept( Visitor& visitor )
{
    visitor.visit( *this );
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

//
//
// WhileRule
//

WhileRule::WhileRule(
    const Token::Ptr& whileToken,
    const Expression::Ptr& condition,
    const Token::Ptr& doToken,
    const Rule::Ptr& rule )
: Rule( Node::ID::WHILE_RULE )
, m_condition( condition )
, m_rule( rule )
, m_whileToken( whileToken )
, m_doToken( doToken )
{
}

const Expression::Ptr& WhileRule::condition( void ) const
{
    return m_condition;
}

const Rule::Ptr& WhileRule::rule( void ) const
{
    return m_rule;
}

const Token::Ptr& WhileRule::whileToken( void ) const
{
    return m_whileToken;
}

const Token::Ptr& WhileRule::doToken( void ) const
{
    return m_doToken;
}

void WhileRule::accept( Visitor& visitor )
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
