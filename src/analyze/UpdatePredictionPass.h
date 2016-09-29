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

#ifndef _LIB_CASMFE_UPDATEPREDICTIONPASS_H_
#define _LIB_CASMFE_UPDATEPREDICTIONPASS_H_

#include <cstddef>
#include <vector>
#include <unordered_set>

#include "libpass.h"
#include "libcasm-fe.all.h"

/**
   @brief    TODO

   TODO
*/

namespace libcasm_fe
{
    class UpdatePredictionPass : public libpass::Pass, public BaseVisitor<bool>
    {
    public:
        static char id;

        UpdatePredictionPass();

        bool run(libpass::PassResult& pr) override;

        void visit_rule_post(RuleNode* node);
        void visit_statements_post(AstListNode* stmts);
        void visit_ifthenelse_post(IfThenElseNode* node, bool);
        void visit_case(CaseNode* node, const bool, const std::vector<bool>&);
        void visit_call_post(CallNode* node);
        void visit_let_post(LetNode* node);
        void visit_iterate_post(UnaryNode* node);
        void visit_forall_post(ForallNode* node);
        void visit_seqblock_post(UnaryNode* node);
        void visit_parblock_post(UnaryNode* node);

        bool visit_update(UpdateNode* update, bool, bool);
        bool visit_update_dumps(UpdateNode* update, bool, bool);
        void visit_push(PushNode* node, bool, bool);
        void visit_pop(PopNode* node);

    private:
        void evaluateRule(RuleNode* rule);
        bool isRuleEvaluated(RuleNode* rule) const;

    private:
        std::unordered_set<RuleNode*> m_evaluatedRules;
    };
}

#endif /* _LIB_CASMFE_UPDATEPREDICTIONPASS_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
