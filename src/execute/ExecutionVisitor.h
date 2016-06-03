//
//  Copyright (c) 2014-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libcasm-fe
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

#ifndef _LIB_CASMFE_EXECUTIONVISITOR_H_
#define _LIB_CASMFE_EXECUTIONVISITOR_H_

class value_t;
class Driver;
class ExecutionContext;

#include <vector>
#include <set>

#include "UpdateSet.h"
#include "../Visitor.h"
#include "../Ast.h"

class ExecutionVisitor : public BaseVisitor<value_t> {
  private:
    std::vector<value_t> main_bindings;
    Update *add_update(const value_t& val, size_t sym_id);

  public:
    std::vector<value_t> value_list;
    Driver& driver_;
    ExecutionContext& context_;
    std::vector<std::vector<value_t> *> rule_bindings;

    value_t arguments[10];
    uint32_t num_arguments;

    ExecutionVisitor(ExecutionContext& context, Driver& driver);

    void visit_assert(UnaryNode* assert, const value_t& val);
    void visit_assure(UnaryNode* assure, const value_t& val);
    void visit_update(UpdateNode *update, const value_t& expr_v);
    void visit_update_subrange(UpdateNode *update, const value_t& expr_v);

    void visit_update_dumps(UpdateNode *update, const value_t& expr_v);
    void visit_call_pre(CallNode *call);
    void visit_call_pre(CallNode *call, const value_t& expr);
    void visit_call(CallNode *call, std::vector<value_t> &arguments);
    void visit_call_post(CallNode *call);
    void visit_print(PrintNode *node, const std::vector<value_t> &arguments);
    void visit_diedie(DiedieNode *node, const value_t& msg);
    void visit_impossible(AstNode *node);

    void visit_let(LetNode *node, const value_t& v);
    void visit_let_post(LetNode *node);
    void visit_push(PushNode *node, const value_t& expr, const value_t& atom);
    void visit_pop(PopNode *node, const value_t& val);

    const value_t visit_expression(Expression *expr, const value_t& left_val,
                                 const value_t& right_val);
    const value_t visit_expression_single(Expression *expr, const value_t& val);
    const value_t visit_int_atom(IntegerAtom *atom) { return value_t(atom->val_); }
    const value_t visit_bit_atom(IntegerAtom *atom) { return value_t(atom->val_); }
    const value_t visit_floating_atom(FloatingAtom *atom) { return value_t(atom->val_); }
    const value_t visit_rational_atom(RationalAtom *atom) { return value_t(&atom->val_); }
    const value_t visit_undef_atom(UndefAtom *atom) { UNUSED(atom); return value_t(); }
    const value_t visit_function_atom(FunctionAtom *atom,
                                      const value_t arguments[], uint16_t num_arguments);
    const value_t visit_function_atom_subrange(FunctionAtom *atom,
                                               const value_t arguments[],
                                               uint16_t num_arguments);


    const value_t visit_builtin_atom(BuiltinAtom *atom, const value_t arguments[],
                                     uint16_t num_arguments);
    void visit_derived_function_atom_pre(FunctionAtom *atom,
                                         const value_t arguments[],
                                         uint16_t num_arguments);
    const value_t visit_derived_function_atom(FunctionAtom *atom, const value_t& expr);
    const value_t visit_self_atom(SelfAtom *atom) { UNUSED(atom); return value_t(); }
    const value_t visit_rule_atom(RuleAtom *atom) { return value_t(atom->rule); }
    const value_t visit_boolean_atom(BooleanAtom *atom) { return value_t(atom->value); }
    const value_t visit_string_atom(StringAtom *atom) { return value_t(&atom->string); }
    const value_t visit_list_atom(ListAtom *atom, const std::vector<value_t> &vals);
    const value_t visit_number_range_atom(NumberRangeAtom *atom);
};

template <>
value_t AstWalker<ExecutionVisitor, value_t>::walk_list_atom(ListAtom *atom);

// Specialize if-then-else for ExecutionVisitor
template <>
void AstWalker<ExecutionVisitor, value_t>::walk_ifthenelse(IfThenElseNode* node);

template <>
void AstWalker<ExecutionVisitor, value_t>::walk_seqblock(UnaryNode* seqblock);

template <>
void AstWalker<ExecutionVisitor, value_t>::walk_parblock(UnaryNode* parblock);

template <>
void AstWalker<ExecutionVisitor, value_t>::walk_pop(PopNode* node);

template <>
void AstWalker<ExecutionVisitor, value_t>::walk_push(PushNode* node);

template <>
void AstWalker<ExecutionVisitor, value_t>::walk_case(CaseNode *node);

template <>
void AstWalker<ExecutionVisitor, value_t>::walk_forall(ForallNode *node);

template <>
void AstWalker<ExecutionVisitor, value_t>::walk_iterate(UnaryNode *node);

template <>
void AstWalker<ExecutionVisitor, value_t>::walk_update(UpdateNode *node);

template <>
void AstWalker<ExecutionVisitor, value_t>::walk_update_subrange(UpdateNode *node);

template <>
void AstWalker<ExecutionVisitor, value_t>::walk_update_dumps(UpdateNode *node);

class ExecutionWalker : public AstWalker<ExecutionVisitor, value_t> {
  private:
    std::set<std::string> initialized;

    bool init_function(const std::string& name, std::set<std::string>& visited);

  public:
    ExecutionWalker(ExecutionVisitor& v);
    void run();
};

#endif // _LIB_CASMFE_EXECUTIONVISITOR_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
