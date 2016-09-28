//  
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//  
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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

#include "UpdatePass.h"

#include <utility>

#include "../Driver.h"

using namespace libcasm_fe;

extern Driver* global_driver;

char UpdatePass::id = 0;

static libpass::PassRegistration<UpdatePass> PASS
( "Update Pass"
, "determines the update set size"
, "update"
, 0
);

UpdatePass::UpdatePass() :
    m_evaluatedRules()
{

}

bool UpdatePass::run(libpass::PassResult& pr)
{
    const auto& rules = global_driver->rules_map_;
    m_evaluatedRules.reserve(rules.size());
    for (const auto& pair : rules) {
        const auto rule = pair.second;
        if (not isRuleEvaluated(rule)) { // visit_call_post may have evaluated it already
            evaluateRule(rule);
        }
    }

    return true;
}

void UpdatePass::visit_rule_post(RuleNode* node)
{
    node->updates = node->child_->updates;
}

void UpdatePass::visit_statements_post(AstListNode* stmts)
{
    std::size_t updates = 0;
    for (auto stmt: stmts->nodes) {
        updates += stmt->updates;
    }
    stmts->updates = updates;
}

void UpdatePass::visit_ifthenelse_post(IfThenElseNode* node, bool)
{
    if (node->else_) {
        node->updates = std::max(node->then_->updates, node->else_->updates);
    } else {
        node->updates = node->then_->updates;
    }
}

void UpdatePass::visit_case(CaseNode* node, const bool, const std::vector<bool>&)
{
    // find the case with the biggest amount of updates
    std::size_t updates = 0;
    for (const auto& pair : node->case_list) {
        const auto stmt = pair.second;
        updates = std::max(updates, stmt->updates);
    }
    node->updates = updates;
}

void UpdatePass::visit_call_post(CallNode* node)
{
    // make sure that the target rule is evaluated before we make use of it
    auto rule = node->rule;
    if (not isRuleEvaluated(rule)) {
        evaluateRule(rule);
    }

    node->updates = rule->updates;
}

void UpdatePass::visit_let_post(LetNode* node)
{
    node->updates = node->stmt->updates;
}

void UpdatePass::visit_iterate_post(UnaryNode* node)
{
    node->updates = node->child_->updates; // in theorie this should be infinity
}

/**
 * Checks if the expression \a expr is bounded/finite.
 *
 * @return <true, span> if \a expr is bounded/finite, <false, _> otherwise.
 */
static std::pair<bool, std::size_t> expressionBound(ExpressionBase* expr) // TODO use std::optional
{
    switch (expr->node_type_) {
        case NodeType::INTEGER_ATOM:
            return std::make_pair(true, std::abs(reinterpret_cast<IntegerAtom*>(expr)->val_) - 1);
        case NodeType::NUMBER_RANGE_ATOM: {
            const auto numberRange = reinterpret_cast<NumberRangeAtom*>(expr);
            if ((numberRange->left->node_type_ == NodeType::INTEGER_ATOM) and
                (numberRange->right->node_type_ == NodeType::INTEGER_ATOM)) {
                const auto left = reinterpret_cast<IntegerAtom*>(numberRange->left);
                const auto right = reinterpret_cast<IntegerAtom*>(numberRange->right);
                return std::make_pair(true, std::abs(left->val_ - right->val_));
            } else {
                return std::make_pair(false, 0);
            }
        }
        case NodeType::FUNCTION_ATOM: {
            const auto function = reinterpret_cast<FunctionAtom*>(expr);
            assert(function->name == function->enum_->name);
            return std::make_pair(true, function->enum_->mapping.size());
        }
        default:
            return std::make_pair(false, 0);
    }
}

void UpdatePass::visit_forall_post(ForallNode* node)
{
    const auto bound = expressionBound(node->in_expr);
    if (bound.first) { // is bounded
        node->updates = node->statement->updates * bound.second;
    } else {
        node->updates = node->statement->updates; // in theorie this should be infinity
    }
}

void UpdatePass::visit_seqblock_post(UnaryNode* node)
{
    node->updates = node->child_->updates;
}

void UpdatePass::visit_parblock_post(UnaryNode* node)
{
    node->updates = node->child_->updates;
}

bool UpdatePass::visit_update(UpdateNode* update, bool, bool)
{
    update->updates = 1;
    return true;
}

bool UpdatePass::visit_update_dumps(UpdateNode* update, bool, bool)
{
    update->updates = 1;
    return true;
}

void UpdatePass::visit_push(PushNode* node, bool, bool)
{
    node->updates = 1;
}

void UpdatePass::visit_pop(PopNode* node)
{
    if (node->to->symbol_type == FunctionAtom::SymbolType::FUNCTION) { // pop into
        node->updates = 2;
    } else {
        node->updates = 1;
    }
}

void UpdatePass::evaluateRule(RuleNode* rule)
{
    m_evaluatedRules.emplace(rule);
    AstWalker<libcasm_fe::UpdatePass, bool> walker{*this};
    walker.suppress_calls = true;
    walker.walk_rule(rule);
}

bool UpdatePass::isRuleEvaluated(RuleNode* rule) const
{
    return m_evaluatedRules.count(rule) != 0;
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
