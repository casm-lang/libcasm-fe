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

#include "NumericExecutionPass.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cassert>
#include <utility>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>

#include "../Driver.h"
#include "../Symbols.h"
#include "../Exceptions.h"

using namespace libcasm_fe;

extern Driver *global_driver;

BlockAllocator<VALUE_STACK_SIZE> NumericExecutionPass::value_stack;

char NumericExecutionPass::id = 0;

static libpass::PassRegistration< NumericExecutionPass > PASS
( "Numeric Execution Pass"
, "execute numerically over the AST the input specification"
, "ast-num"
, 0
);


static std::string arguments_to_string(uint32_t num_arguments, const value_t arguments[])
{
    std::stringstream ss;
    if (num_arguments == 0) {
        return "";
    }
    for (uint32_t i = 0; i < num_arguments; i++) {
        ss << arguments[i].to_str();
        ss << ", ";
    }
    // Strip trailing comma
    return "(" + ss.str().substr(0, ss.str().size() - 2) + ")";
}

bool NumericExecutionPass::run( libpass::PassResult& pr )
{
    Ast* root = (Ast*)pr.getResult< TypeCheckPass >();
    RuleNode* node = global_driver->rules_map_[ root->getInitRule()->identifier ];

    rule_bindings.push_back(&main_bindings);
    function_states = std::vector<std::unordered_map<ArgumentsKey, value_t>>(global_driver->function_table.size());
    function_symbols = std::vector<const Function*>(global_driver->function_table.size());
    Function *program_sym = global_driver->function_table.get_function("program");
    // TODO location is wrong here
    program_sym->intitializers_ = new std::vector<std::pair<ExpressionBase*, ExpressionBase*>>();
    RuleAtom *init_atom = new RuleAtom(node->location, std::string(node->name));
    init_atom->rule = node;
    program_sym->intitializers_->push_back(std::make_pair(new SelfAtom(node->location), init_atom));

    try {
        ExecutionWalker walker(*this);
        walker.run();
        return true;
    } catch (const RuntimeException& ex) {
        std::cerr << "Abort after runtime exception: " << ex.what() << std::endl;
    } catch (const ImpossibleException& ex) {
    } catch (char * e) {
        std::cerr << "Abort after catching a string: " << e << std::endl;
    }
	
    return false;
}

bool NumericExecutionPass::hasEmptyUpdateSet() const
{
    return updateSetManager.currentUpdateSet()->empty();
}

Update* NumericExecutionPass::addUpdate(const value_t& val, size_t sym_id,
                                        uint32_t num_arguments, value_t arguments[],
                                        uint64_t line)
{
    auto& function_map = function_states[sym_id];
    auto it = function_map.find(ArgumentsKey(arguments, num_arguments, false)); // TODO EP: use emplace only
    if (it == function_map.cend()) {
        const auto pair = function_map.emplace(ArgumentsKey(arguments, num_arguments, true), value_t());
        it = pair.first;
    }

    Update* up = reinterpret_cast<Update*>(stack.allocate(sizeof(Update))); // FIXME make it nicer!!
    up->value = val;
    up->func = sym_id;
    up->args = const_cast<value_t*>(it->first.p);
    up->num_args = num_arguments;
    up->line = line;

    try {
        const value_t& ref = it->second;
        updateSetManager.add(reinterpret_cast<uint64_t>(&ref), up);
    } catch (const UpdateSet::Conflict& e) {
        const auto conflictingUpdate = e.conflictingUpdate();
        const auto existingUpdate = e.existingUpdate();

        const auto function = function_symbols[conflictingUpdate->func];
        const auto location = function->name + arguments_to_string(conflictingUpdate->num_args,
                                                                   conflictingUpdate->args);

        const auto info = "Conflict while adding update " + location + " = " + val.to_str()
                        + " at line " + std::to_string(line) + ", conflicting with line "
                        + std::to_string(existingUpdate->line) + " with value '"
                        + existingUpdate->value.to_str() + "'";
        throw RuntimeException(info);
    }

    return up;
}

void NumericExecutionPass::applyUpdates()
{
    std::unordered_map<uint32_t, std::vector<ArgumentsKey>> updated_functions;
    if (dump_updates) {
        for (uint32_t i = 0; i < function_states.size(); i++) {
            updated_functions[i] = std::vector<ArgumentsKey>();
        }
    }

    assert(updateSetManager.size() == 1);

    auto updateSet = updateSetManager.currentUpdateSet();
    std::vector<value_t*> to_fold;
    const auto end = updateSet->cend();
    for (auto it = updateSet->cbegin(); it != end; ++it) {
        value_t* location = reinterpret_cast<value_t*>(it->first);
        Update* u = it->second;

        // TODO handle tuples
        if (u->value.type == TypeType::LIST) {
            auto& function_map = function_states[u->func];
            value_t& list = function_map[ArgumentsKey(u->args, u->num_args, false)];
            if (u->value.is_undef()) {
                // set list to undef
                if (!list.is_undef()) {
                    list.value.list->decrease_usage();
                    list.type = TypeType::UNDEF;
                }
            } else {
                if (!list.is_undef() && !list.is_symbolic()) {
                    list.value.list->decrease_usage();
                } else {
                    list.type = u->value.type;
                }
                list.value.list = u->value.value.list;
                list.value.list->bump_usage();
                to_fold.push_back(&list);
            }
        } else {
            // we could erase keys that store an undef value in concrete mode,
            // but we need to know if a key was set to undef explicitly in symbolic
            // mode
            *location = u->value;
        }

        if (dump_updates) {
            updated_functions[u->func].push_back(ArgumentsKey(u->args, u->num_args, true));
        }
    }
    updateSetManager.clear();

    if (dump_updates) {
        for (uint32_t i = 0; i < function_states.size(); i++) {
            auto& function_map = function_states[i];
            const Function* function_symbol = function_symbols[i];
            const auto& updated_keys = updated_functions[i];

            for (const auto& k : updated_keys) {
                update_dump.push_back(function_symbol->name+
                arguments_to_string(k.size, k.p)+" = "+
                function_map[k].to_str());
            }
        }

        std::stringstream ss;
        for (auto s : update_dump) {
            ss << s << ", ";
        }
        std::cout << "{ " << ss.str().substr(0, ss.str().size()-2) << " }" << std::endl;
        update_dump.clear();
    }

    // Handle lists
    // 1. convert chained lists to BottomLists
    for (value_t* v : to_fold) {
        BottomList *new_l = v->value.list->collect();
        if (new_l->check_allocated_and_set_to_false()) {
            temp_lists.push_back(new_l);
        }
        v->value.list = new_l;
    }
    to_fold.clear();
    std::vector<size_t> deleted;

    // delete all list objects, except BottomLists that are currently used
    for (size_t i=0; i < temp_lists.size(); i++) {
        if (!(temp_lists[i]->is_bottom() && reinterpret_cast<BottomList*>(temp_lists[i])->is_used())) {
            delete temp_lists[i];
            deleted.push_back(i);
        }
    }

    // remove deleted lists from temp_lists
    for (size_t del : deleted) {
        temp_lists[del] = std::move(temp_lists.back());
        temp_lists.pop_back();
    }
    // list handling done

    stack.freeAll();
}

void NumericExecutionPass::fork(const UpdateSet::Type updateSetType)
{
    updateSetManager.fork(updateSetType);
}

void NumericExecutionPass::merge()
{
    try {
        updateSetManager.merge();
    } catch (const UpdateSet::Conflict& e) {
        const auto conflictingUpdate = e.conflictingUpdate();
        const auto existingUpdate = e.existingUpdate();

        const auto function = function_symbols[conflictingUpdate->func];
        const auto location = function->name + arguments_to_string(conflictingUpdate->num_args,
                                                                   conflictingUpdate->args);

        const auto info = "Conflict while merging updateset " + location
                        + " at line " + std::to_string(conflictingUpdate->line)
                        + " with value '" + conflictingUpdate->value.to_str() + "'"
                        + " and at line " + std::to_string(existingUpdate->line)
                        + " with value '" + existingUpdate->value.to_str() + "'";
        throw RuntimeException(info);
    }
}

const value_t NumericExecutionPass::get_function_value(Function *sym,
                                                       uint32_t num_arguments,
                                                       const value_t arguments[])
{
    auto& function_map = function_states[sym->id];
    try {
        const value_t &v = function_map.at(ArgumentsKey(arguments, num_arguments, false));
        const auto update = updateSetManager.lookup(reinterpret_cast<uint64_t>(&v));
        if (update) {
            return update->value;
        } else {
            return v;
        }
    } catch (const std::out_of_range &e) {
        static value_t undef = value_t();
        return undef;
    }
}

bool NumericExecutionPass::filter_enabled(const std::string& filter)
{
    return debuginfo_filters.count("all") > 0 || debuginfo_filters.count(filter) > 0;
}

namespace builtins
{
    static const value_t pow(const value_t& base, const value_t& power)
    {
        switch (base.type) {
            case TypeType::INTEGER:
                return value_t((INTEGER_T)std::pow(base.value.integer, power.value.integer));
            case TypeType::FLOATING:
                return value_t((FLOATING_T)std::pow(base.value.float_, power.value.float_));
            default:
                FAILURE();
        }
    }

    static const value_t hex(const value_t& arg)
    {
        // TODO LEAK!
        if (arg.is_undef()) {
            return value_t(new std::string("undef"));
        }

        std::stringstream ss;
        if (arg.value.integer < 0) {
            ss << "-" << std::hex << (-1) * arg.value.integer;
        } else {
            ss << std::hex << arg.value.integer;
        }
        return value_t(new std::string(ss.str()));
    }

    static const value_t nth(const value_t& list_arg, const value_t& index)
    {
        if (list_arg.is_undef() || index.is_undef()) {
            return value_t();
        }

        List *list = list_arg.value.list;
        List::const_iterator iter = list->begin();
        INTEGER_T i = 1;

        while (iter != list->end() && i < index.value.integer) {
            i++;
            iter++;
        }
        if (i == index.value.integer && iter != list->end()) {
            return value_t(*iter);
        } else {
            return value_t();
        }
    }

    static const value_t app(std::vector<List*>& tempLists, const value_t& list, const value_t& val)
    {
        // TODO LEAK
        if (list.is_undef()) {
            return value_t();
        }

        List *current = list.value.list;

        while (true) {
            if (current->list_type == List::ListType::HEAD) {
                current = reinterpret_cast<HeadList*>(current)->right;
            }
            if (current->list_type == List::ListType::SKIP) {
                current = reinterpret_cast<SkipList*>(current)->bottom;
            }
            if (current->list_type == List::ListType::BOTTOM) {
                BottomList *bottom = reinterpret_cast<BottomList*>(current);
                if (bottom->tail) {
                    current = bottom->tail;
                } else {
                    break;
                }
            }
            if (current->list_type == List::ListType::TAIL) {
                TailList *tail = reinterpret_cast<TailList*>(current);
                if (tail->right) {
                    current = tail->right;
                } else {
                    break;
                }
            }
        }


        TailList *tail = new TailList(nullptr, val);
        tempLists.push_back(tail);

        if (current->list_type == List::ListType::TAIL) {
            reinterpret_cast<TailList*>(current)->right = tail;
        } else if (current->list_type == List::ListType::BOTTOM) {
            reinterpret_cast<BottomList*>(current)->tail = tail;
        } else {
            FAILURE();
        }
        return value_t(list.type, list.value.list);
    }

    static const value_t cons(std::vector<List*>& tempLists, const value_t& val, const value_t& list)
    {
        // TODO LEAK
        if (list.is_undef()) {
            return value_t();
        }

        HeadList *consed_list = new HeadList(list.value.list, val);
        tempLists.push_back(consed_list);
        return value_t(list.type, consed_list);
    }

    static const value_t tail(std::vector<List*>& tempLists, const value_t& arg_list)
    {
        if (arg_list.is_undef()) {
            return value_t();
        }

        List *list = arg_list.value.list;

        if (list->is_head()) {
            return value_t(arg_list.type, reinterpret_cast<HeadList*>(list)->right);
        } else if (list->is_bottom()) {
            BottomList *btm = reinterpret_cast<BottomList*>(list);
            SkipList *skip = new SkipList(1, btm);
            tempLists.push_back(skip);
            return value_t(arg_list.type, skip);
        } else {
            SkipList *old_skip = reinterpret_cast<SkipList*>(list);
            SkipList *skip = new SkipList(old_skip->skip+1, old_skip->bottom);
            tempLists.push_back(skip);
            return value_t(arg_list.type, skip);
        }
    }

    static const value_t len(const value_t& list_arg)
    {
        // TODO len is really slow right now, it itertes over complete list
        if (list_arg.is_undef()) {
            return value_t();
        }

        List *list = list_arg.value.list;
        List::const_iterator iter = list->begin();

        size_t count = 0;

        while (iter != list->end()) {
            count++;
            iter++;
        }
        return value_t((INTEGER_T) count);
    }

    static const value_t peek(const value_t& arg_list)
    {
        if (arg_list.is_undef()) {
            return value_t();
        }

        List *list = arg_list.value.list;

        if (list->begin() != list->end()) {
            return value_t(*(list->begin()));
        } else {
            return value_t();
        }
    }

    static const value_t asboolean(const value_t& arg)
    {
        if (arg.is_undef()) {
            return std::move(arg);
        }

        return value_t((bool)arg.value.integer);
    }

    static const value_t asinteger(const value_t& arg)
    {
        switch (arg.type) {
            case TypeType::INTEGER:
                return value_t(arg.value.integer);
            case TypeType::FLOATING:
                return value_t((INTEGER_T)arg.value.float_);
            case TypeType::RATIONAL:
                return value_t((INTEGER_T)(arg.value.rat->numerator / arg.value.rat->denominator));
            case TypeType::ENUM:
                return value_t((INTEGER_T)arg.value.enum_val->id);
            case TypeType::UNDEF:
                return arg;
            default:
                FAILURE();
        }
    }

    static const value_t asfloating(const value_t& arg)
    {
        switch (arg.type) {
            case TypeType::INTEGER:
                return value_t((FLOATING_T) arg.value.integer);
            case TypeType::FLOATING:
                return value_t(arg.value.float_);
            case TypeType::RATIONAL:
                return value_t(((FLOATING_T)arg.value.rat->numerator) / arg.value.rat->denominator);
            case TypeType::UNDEF:
                return arg;
            default:
                FAILURE();
        }
    }

    static void get_numerator_denominator(double x, int64_t *num, int64_t *denom)
    {
        // thanks to
        // http://stackoverflow.com/a/96035/781502
        uint64_t m[2][2];
        double startx = x;
        uint64_t maxden = 10000000000;
        int64_t ai;

        /* initialize matrix */
        m[0][0] = m[1][1] = 1;
        m[0][1] = m[1][0] = 0;

        /* loop finding terms until denom gets too big */
        while (m[1][0] *  ( ai = (int64_t)x ) + m[1][1] <= maxden) {
            long t;
            t = m[0][0] * ai + m[0][1];
            m[0][1] = m[0][0];
            m[0][0] = t;
            t = m[1][0] * ai + m[1][1];
            m[1][1] = m[1][0];
            m[1][0] = t;
            if(x==(double)ai) break;     // AF: division by zero
            x = 1/(x - (double) ai);
            if(x>(double)0x7FFFFFFF) break;  // AF: representation failure
        }

        /* now remaining x is between 0 and 1/ai */
        /* approx as either 0 or 1/m where m is max that will fit in maxden */
        /* first try zero */

        double error1 = startx - ((double) m[0][0] / (double) m[1][0]);

        *num = m[0][0];
        *denom =  m[1][0];

        /* now try other possibility */
        ai = (maxden - m[1][1]) / m[1][0];
        m[0][0] = m[0][0] * ai + m[0][1];
        m[1][0] = m[1][0] * ai + m[1][1];
        double error2 = startx - ((double) m[0][0] / (double) m[1][0]);

        if (fabs(error1) > fabs(error2)) {
            *num = m[0][0];
            *denom =  m[1][0];
        }
    }

    static const value_t asrational(const value_t& arg)
    {
        auto result = reinterpret_cast<rational_t*>(NumericExecutionPass::value_stack.allocate(sizeof(rational_t)));
        switch (arg.type) {
            case TypeType::INTEGER:
                result->numerator = arg.value.integer;
                result->denominator = 1;
                return value_t(result);
            case TypeType::FLOATING:
                get_numerator_denominator(arg.value.float_, &result->numerator, &result->denominator);
                return value_t(result);
            case TypeType::RATIONAL:
                return value_t(arg.value.rat);
            case TypeType::UNDEF:
                return arg;
            default:
                FAILURE();
        }
    }

    static const value_t symbolic(const value_t& arg)
    {
        if (arg.is_symbolic() && !arg.value.sym->list) {
            return value_t(true);
        } else {
            return value_t(false);
        }
    }
}

void NumericExecutionPass::visit_assert(UnaryNode* assert, const value_t& val)
{
    if (!val.value.boolean) {
        throw RuntimeException(assert->location, "Assertion failed");
    }
}

void NumericExecutionPass::visit_assure(UnaryNode* assure, const value_t& val)
{
    visit_assert(assure, val);
}

void NumericExecutionPass::visit_update_dumps(UpdateNode *update, const value_t& expr_v)
{
    const std::string& filter = global_driver->function_trace_map[update->func->symbol->id];
    if (filter_enabled(filter)) {
        std::cout << filter << ": "
                  << update->func->symbol->name << arguments_to_string(num_arguments, arguments)
                  << " = " << expr_v.to_str() << std::endl;
    }

    visit_update(update, expr_v);
}

void NumericExecutionPass::visit_update(UpdateNode *update, const value_t& expr_v)
{
    addUpdate(expr_v, update->func->symbol->id, num_arguments, arguments, update->location.begin.line);
}

void NumericExecutionPass::visit_update_subrange(UpdateNode *update, const value_t& expr_v)
{
    const INTEGER_T v = expr_v.value.integer;
    const Type *t = update->func->symbol->return_type_;
    if ((t->subrange_start < t->subrange_end) && (v < t->subrange_start || v > t->subrange_end)) {
        throw RuntimeException(update->location,
                               std::to_string(v) + " does violate the subrange " +
                               std::to_string(t->subrange_start) +
                               ".." + std::to_string(t->subrange_end) +
                               " of `" + update->func->name + "`");
    }

    visit_update(update, expr_v);
}

void NumericExecutionPass::visit_call_pre(CallNode *call)
{
    UNUSED(call);
}

void NumericExecutionPass::visit_call_pre(CallNode *call, const value_t& expr)
{
    if (expr.type != TypeType::UNDEF) {
        call->rule = expr.value.rule;
    } else {
        throw RuntimeException(call->location, "Cannot call UNDEF");
    }
}

void NumericExecutionPass::visit_call(CallNode *call, std::vector<value_t> &argument_results)
{
    UNUSED(call);

    if (call->ruleref) {
        size_t args_defined = call->rule->arguments.size();
        size_t args_provided = argument_results.size();
        if (args_defined != args_provided) {
            throw RuntimeException(call->location, "indirectly called rule `" + call->rule->name +
                                   "` expects " + std::to_string(args_defined) + " arguments but " +
                                   std::to_string(args_provided) + " where provided");
        } else {
            for (size_t i=0; i < args_defined; i++) {
                Type arg_t(argument_results[i].type);
                if (call->rule->arguments[i]->t == TypeType::LIST) {
                    // TODO
                    assert(0);
                } else if (!call->rule->arguments[i]->unify(&arg_t) && !(argument_results[i].is_undef() && argument_results[i].type == TypeType::UNDEF)) {
                    throw RuntimeException(call->arguments->at(i)->location,
                                           "argument "+std::to_string(i+1)+" of indirectly called rule `"+
                                           call->rule->name+"` must be `"+
                                           call->rule->arguments[i]->to_str()+"` but was `"+
                                           Type(argument_results[i].type).to_str()+"`");
                }
            }
        }
    }

    rule_bindings.push_back(&argument_results);
}

void NumericExecutionPass::visit_call_post(CallNode *call)
{
    UNUSED(call);
    rule_bindings.pop_back();
}

void NumericExecutionPass::visit_print(PrintNode *node, const std::vector<value_t> &arguments)
{
    if (node->filter.size() > 0 ) {
        if (filter_enabled(node->filter)) {
            std::cout << node->filter << ": ";
        } else {
            return;
        }
    }

    for (const value_t& v: arguments) {
        std::cout << v.to_str();
    }
    std::cout << std::endl;
}

void NumericExecutionPass::visit_diedie(DiedieNode *node, const value_t& msg)
{
    if (node->msg) {
        throw RuntimeException(node->location, *msg.value.string);
    } else {
        throw RuntimeException(node->location, "`diedie` executed");
    }
}

void NumericExecutionPass::visit_impossible(AstNode *node)
{
    throw RuntimeException(node->location, "`impossible` executed");
}

void NumericExecutionPass::visit_let(LetNode*, const value_t& v)
{
    rule_bindings.back()->push_back(v);
}

void NumericExecutionPass::visit_let_post(LetNode*)
{
    rule_bindings.back()->pop_back();
}

void NumericExecutionPass::visit_push(PushNode *node, const value_t& expr, const value_t& atom)
{
    num_arguments = 0; // TODO at the moment, functions with arguments are not supported

    const value_t to_res = builtins::cons(temp_lists, expr, atom);
    addUpdate(to_res, node->to->symbol->id, num_arguments, arguments, node->location.begin.line);
}

void NumericExecutionPass::visit_pop(PopNode *node, const value_t& val)
{
    num_arguments = 0; // TODO at the moment, functions with arguments are not supported

    const value_t to_res = builtins::peek(val);

    if (node->to->symbol_type == FunctionAtom::SymbolType::FUNCTION) {
        addUpdate(to_res, node->to->symbol->id, num_arguments, arguments, node->location.begin.line);
    } else {
        rule_bindings.back()->push_back(to_res);
    }

    const value_t from_res = builtins::tail(temp_lists, val);
    addUpdate(from_res, node->from->symbol->id, num_arguments, arguments, node->location.begin.line);
}

#define CREATE_NUMERICAL_OPERATION(op, lhs, rhs)  {                             \
    switch (lhs.type) {                                                         \
    case TypeType::INTEGER:                                                     \
        return value_t(lhs.value.integer op rhs.value.integer);                 \
    case TypeType::FLOATING:                                                    \
        return value_t(lhs.value.float_ op rhs.value.float_);                   \
    case TypeType::RATIONAL:                                                    \
        return value_t(&(*lhs.value.rat op *rhs.value.rat));                    \
    default:                                                                    \
        FAILURE();                                                              \
    }                                                                           \
}

#define CREATE_BOOLEAN_OPERATION(op, lhs, rhs)  {                               \
    return value_t((bool)(lhs.value.boolean op rhs.value.boolean));             \
}

#define CREATE_COMPARE_OPERATION(op, lhs, rhs)  {                               \
    switch (lhs.type) {                                                         \
    case TypeType::INTEGER:                                                     \
        return value_t(lhs.value.integer op rhs.value.integer);                 \
    case TypeType::FLOATING:                                                    \
        return value_t(lhs.value.float_ op rhs.value.float_);                   \
    default:                                                                    \
        FAILURE();                                                              \
    }                                                                           \
}

namespace operators
{
    static const value_t mod(const value_t& lhs, const value_t& rhs)
    {
        if (lhs.type == TypeType::INTEGER) {
            return value_t(lhs.value.integer % rhs.value.integer);
        } else {
            return value_t();
        }
    }

    static const value_t rat_div(const value_t& lhs, const value_t& rhs)
    {
        switch (lhs.type) {
        case TypeType::INTEGER: {
            auto result = reinterpret_cast<rational_t*>(NumericExecutionPass::value_stack.allocate(sizeof(rational_t)));
            result->numerator = lhs.value.integer;
            result->denominator = rhs.value.integer;
            return value_t(result);
        }
        default:
            FAILURE();
        }
    }
}

const value_t NumericExecutionPass::visit_expression(Expression *expr,
                                                     const value_t &left_val,
                                                     const value_t &right_val)
{
    if (left_val.is_undef() or right_val.is_undef()) {
        return value_t();
    }

    switch (expr->op) {
    case ExpressionOperation::ADD:
        CREATE_NUMERICAL_OPERATION(+, left_val, right_val);
    case ExpressionOperation::SUB:
        CREATE_NUMERICAL_OPERATION(-, left_val, right_val);
    case ExpressionOperation::MUL:
        CREATE_NUMERICAL_OPERATION(*, left_val, right_val);
    case ExpressionOperation::DIV:
        CREATE_NUMERICAL_OPERATION(/, left_val, right_val);
    case ExpressionOperation::MOD:
        return operators::mod(left_val, right_val);
    case ExpressionOperation::RAT_DIV:
        return operators::rat_div(left_val, right_val);
    case ExpressionOperation::EQ:
        CREATE_COMPARE_OPERATION(==, left_val, right_val);
    case ExpressionOperation::NEQ:
        CREATE_COMPARE_OPERATION(!=, left_val, right_val);
    case ExpressionOperation::AND:
        CREATE_BOOLEAN_OPERATION(and, left_val, right_val);
    case ExpressionOperation::OR:
        CREATE_BOOLEAN_OPERATION(or, left_val, right_val);
    case ExpressionOperation::XOR:
        CREATE_BOOLEAN_OPERATION(^, left_val, right_val);
    case ExpressionOperation::LESSER:
        CREATE_COMPARE_OPERATION(<, left_val, right_val);
    case ExpressionOperation::GREATER:
        CREATE_COMPARE_OPERATION(>, left_val, right_val);
    case ExpressionOperation::LESSEREQ:
        CREATE_COMPARE_OPERATION(<=, left_val, right_val);
    case ExpressionOperation::GREATEREQ:
        CREATE_COMPARE_OPERATION(>=, left_val, right_val);
    default:
        FAILURE();
    }
}

const value_t NumericExecutionPass::visit_expression_single(Expression *expr,
                                                            const value_t &val)
{
    if (val.is_undef()) {
        return value_t();
    }

    switch (expr->op) {
    case ExpressionOperation::NOT:
        return value_t(not val.value.boolean);
    default:
        FAILURE();
    }
}

const value_t NumericExecutionPass::visit_function_atom(FunctionAtom *atom,
                                                        const value_t arguments[],
                                                        uint16_t num_arguments)
{
    switch (atom->symbol_type) {
    case FunctionAtom::SymbolType::PARAMETER:
        return value_t(rule_bindings.back()->at(atom->offset));
    case FunctionAtom::SymbolType::FUNCTION:
        return get_function_value(atom->symbol, num_arguments, arguments);
    case FunctionAtom::SymbolType::ENUM: {
        enum_value_t *val = atom->enum_->mapping[atom->name];
        value_t v = value_t(val);
        v.type = TypeType::ENUM;
        return v;
    }
    default:
        FAILURE();
    }
}

const value_t NumericExecutionPass::visit_function_atom_subrange(FunctionAtom *atom,
                                                                 const value_t arguments[],
                                                                 uint16_t num_arguments)
{
    for (uint32_t i = 0; i < atom->symbol->subrange_arguments.size(); i++) {
        uint32_t j = atom->symbol->subrange_arguments[i];
        value_t v = arguments[j];
        Type *t = atom->symbol->arguments_[j];
        if (v.value.integer < t->subrange_start || v.value.integer > t->subrange_end) {
            throw RuntimeException(atom->location,
                                   std::to_string(v.value.integer) + " does violate the subrange " +
                                   std::to_string(t->subrange_start) + ".." + std::to_string(t->subrange_end) +
                                   " of " + std::to_string(i + 1) + ". function argument");
        }
    }

    return visit_function_atom(atom, arguments, num_arguments);
}

const value_t NumericExecutionPass::visit_builtin_atom(BuiltinAtom *atom,
                                                       const value_t arguments[],
                                                       uint16_t num_arguments)
{
    // TODO Int2Enum is a special builtin, it needs the complete type information
    // for the enum, values only store TypeType and passing the type to all
    // builtins seems ugly.
    // Maybe store Type* in value_t?
    if (atom->id == Builtin::Id::AS_ENUM) {
        Enum *enum_ = global_driver->function_table.get_enum(atom->type_.enum_name);
        for (auto pair : enum_->mapping) {
            // TODO check why the enum mapping contains an extra entry with the name
            // of the enum
            if (pair.first != enum_->name && pair.second->id == arguments[0].value.integer) {
                return value_t(pair.second);
            }
        }
        return value_t();
    }

    switch (atom->id) {
    case Builtin::Id::POW:
        return builtins::pow(arguments[0], arguments[1]);
    case Builtin::Id::NTH:
        return builtins::nth(arguments[0], arguments[1]);
    case Builtin::Id::APP:
        return builtins::app(temp_lists, arguments[0], arguments[1]);
    case Builtin::Id::CONS:
        return builtins::cons(temp_lists, arguments[0], arguments[1]);
    case Builtin::Id::HEX:
        return builtins::hex(arguments[0]);
    case Builtin::Id::TAIL:
        return builtins::tail(temp_lists, arguments[0]);
    case Builtin::Id::LEN:
        return builtins::len(arguments[0]);
    case Builtin::Id::PEEK:
        return builtins::peek(arguments[0]);
    case Builtin::Id::AS_BOOLEAN:
        return builtins::asboolean(arguments[0]);
    case Builtin::Id::AS_INTEGER:
        return builtins::asinteger(arguments[0]);
    case Builtin::Id::AS_FLOATING:
        return builtins::asfloating(arguments[0]);
    case Builtin::Id::AS_RATIONAL:
        return builtins::asrational(arguments[0]);
    case Builtin::Id::SYMBOLIC:
        return builtins::symbolic(arguments[0]);
    default:
        FAILURE();
    }
}

void NumericExecutionPass::visit_derived_function_atom_pre(FunctionAtom*,
                                                           const value_t arguments[],
                                                           uint16_t num_arguments)
{
    // TODO change, cleanup!
    std::vector<value_t> *tmp = new std::vector<value_t>();
    for (uint32_t i = 0; i < num_arguments; i++) {
        tmp->push_back(arguments[i]);
    }

    rule_bindings.push_back(tmp);
}

const value_t NumericExecutionPass::visit_derived_function_atom(FunctionAtom*,
                                                                const value_t& expr)
{
    rule_bindings.pop_back();
    return expr;
}

const value_t NumericExecutionPass::visit_list_atom(ListAtom *atom,
                                                    const std::vector<value_t> &vals)
{
    BottomList *list = new BottomList(vals);
    //context_.temp_lists.push_back(list);
    return value_t(atom->type_, list);
}

const value_t NumericExecutionPass::visit_number_range_atom(NumberRangeAtom *atom)
{
    return value_t(atom->type_, atom->list);
}

ExpressionOperation invert(ExpressionOperation op)
{
    switch (op) {
    case ExpressionOperation::EQ:
        return ExpressionOperation::NEQ;
    case ExpressionOperation::NEQ:
        return ExpressionOperation::EQ;
    case ExpressionOperation::LESSEREQ:
        return ExpressionOperation::GREATER;
    case ExpressionOperation::LESSER:
        return ExpressionOperation::GREATEREQ;
    case ExpressionOperation::GREATER:
        return ExpressionOperation::LESSEREQ;
    case ExpressionOperation::GREATEREQ:
        return ExpressionOperation::LESSER;
    default:
        throw RuntimeException("Invert not implemented for operation");
    }
}

template <>
value_t NumericExecutionWalker::walk_list_atom(ListAtom *atom)
{
    std::vector<value_t> expr_results;
    if (atom->expr_list) {
        for (auto iter = atom->expr_list->rbegin(); iter != atom->expr_list->rend(); iter++) {
            expr_results.push_back(walk_expression_base(*iter));
        }
    }
    return visitor.visit_list_atom(atom, expr_results);
}

template <>
void NumericExecutionWalker::walk_ifthenelse(IfThenElseNode* node)
{
    const value_t cond = walk_expression_base(node->condition_);

    if (cond.is_undef()) {
        throw RuntimeException(node->condition_->location,
                               "condition must be true or false but was undef");
    } else if (cond.value.boolean) {
        walk_statement(node->then_);
    } else if (node->else_) {
        walk_statement(node->else_);
    }
}

template <>
void NumericExecutionWalker::walk_seqblock(UnaryNode* seqblock)
{
    visitor.fork(UpdateSet::Type::Sequential);
    visitor.visit_seqblock(seqblock);
    walk_statements(reinterpret_cast<AstListNode*>(seqblock->child_));
    visitor.merge();
}

template <>
void NumericExecutionWalker::walk_parblock(UnaryNode* parblock)
{
    visitor.fork(UpdateSet::Type::Parallel);
    visitor.visit_parblock(parblock);
    walk_statements(reinterpret_cast<AstListNode*>(parblock->child_));
    visitor.merge();
}

template <>
void NumericExecutionWalker::walk_pop(PopNode* node)
{
    const value_t from = walk_function_atom(node->from);
    visitor.visit_pop(node, from);
}

template <>
void NumericExecutionWalker::walk_push(PushNode *node)
{
    const value_t expr = walk_expression_base(node->expr);
    const value_t atom = walk_function_atom(node->to);
    visitor.visit_push(node, expr, atom);
}

template <>
void NumericExecutionWalker::walk_case(CaseNode *node)
{
    const value_t cond = walk_expression_base(node->expr);

    std::pair<AtomNode*, AstNode*> *default_pair = nullptr;
    for (auto& pair : node->case_list) {
        // pair.first == nullptr for default:
        if (pair.first) {
            if (walk_atom(pair.first) == cond) {
                walk_statement(pair.second);
                return;
            }
        } else {
            default_pair = &pair;
        }
    }
    if (default_pair) {
        walk_statement(default_pair->second);
    }
}

template <>
void NumericExecutionWalker::walk_forall(ForallNode *node)
{
    const value_t in_list = walk_expression_base(node->in_expr);

    visitor.fork(UpdateSet::Type::Parallel);

    switch (node->in_expr->type_.t) {
    case TypeType::LIST: {
        List *l =  in_list.value.list;
        for (auto iter = l->begin(); iter != l->end(); iter++) {
            visitor.rule_bindings.back()->push_back(*iter);
            walk_statement(node->statement);
            visitor.rule_bindings.back()->pop_back();
        }
    }   break;
    case TypeType::INTEGER: {
        INTEGER_T end =  in_list.value.integer;
        if (end > 0) {
            for (INTEGER_T i = 0; i < end; i++) {
                visitor.rule_bindings.back()->push_back(value_t(i));
                walk_statement(node->statement);
                visitor.rule_bindings.back()->pop_back();
            }
        } else {
            for (INTEGER_T i = 0; end < i; i--) {
                visitor.rule_bindings.back()->push_back(value_t(i));
                walk_statement(node->statement);
                visitor.rule_bindings.back()->pop_back();
            }
        }
    }   break;
    case TypeType::ENUM: {
        FunctionAtom *func = reinterpret_cast<FunctionAtom*>(node->in_expr);
        if (func->name == func->enum_->name) {
            for (auto pair : func->enum_->mapping) {
                // why is an element with the name of the enum in the map??
                if (func->name == pair.first) {
                    continue;
                }
                value_t v = value_t(pair.second);
                v.type = TypeType::ENUM;
                visitor.rule_bindings.back()->push_back(std::move(v));
                walk_statement(node->statement);
                visitor.rule_bindings.back()->pop_back();
            }
        } else {
            assert(0);
        }
    }   break;
    default:
        assert(0);
    }

    visitor.merge();
}

template <>
void NumericExecutionWalker::walk_iterate(UnaryNode *node)
{
    visitor.fork(UpdateSet::Type::Sequential);

    while (true) {
        visitor.fork(UpdateSet::Type::Parallel);
        walk_statement(node->child_);
        if (visitor.hasEmptyUpdateSet()) {
            visitor.merge(); // to remove the update set from the stack
            break;
        }
        visitor.merge();
    }

    visitor.merge();
}

static void walk_function_arguments(NumericExecutionWalker* walker, std::vector<ExpressionBase*>* arguments)
{
    if (arguments) {
        for (uint16_t i = 0; i < arguments->size(); i++) {
            walker->visitor.arguments[i] = walker->walk_expression_base(arguments->at(i));
        }
        walker->visitor.num_arguments = arguments->size();
    } else {
        walker->visitor.num_arguments = 0;
    }
}

template <>
void NumericExecutionWalker::walk_update(UpdateNode *node)
{
    const value_t expr = walk_expression_base(node->expr_);
    walk_function_arguments(this, node->func->arguments);
    visitor.visit_update(node, expr);
}

template <>
void NumericExecutionWalker::walk_update_subrange(UpdateNode *node)
{
    const value_t expr = walk_expression_base(node->expr_);
    if (node->func->symbol->subrange_arguments.size() > 0) {
        walk_expression_base(node->func);
    }
    walk_function_arguments(this, node->func->arguments);
    visitor.visit_update_subrange(node, expr);
}

template <>
void NumericExecutionWalker::walk_update_dumps(UpdateNode *node)
{
    const value_t expr = walk_expression_base(node->expr_);
    walk_function_arguments(this, node->func->arguments);
    visitor.visit_update_dumps(node, expr);
}

ExecutionWalker::ExecutionWalker(NumericExecutionPass& v) :
    NumericExecutionWalker(v),
    initialized()
{

}

bool ExecutionWalker::init_function(const std::string& name,
                                    std::set<std::string>& visited)
{
    if (global_driver->init_dependencies.count(name) != 0) {
        visited.insert(name);
        const std::set<std::string>& deps = global_driver->init_dependencies[name];
        for (const std::string& dep : deps) {
            if (visited.count(dep) > 0) {
                return false;
            } else {
                if (!init_function(dep, visited)) {
                    return false;
                }
            }
        }
    }

    std::vector<value_t> initializer_args;

    Function *func = global_driver->function_table.get_function(name);
    if (!func) {
        return true;
    }

    visitor.function_states[func->id] = std::unordered_map<ArgumentsKey, value_t>(0);
    visitor.function_symbols[func->id] = func;

    auto& function_map = visitor.function_states[func->id];

    if (func->intitializers_ != nullptr) {
        for (std::pair<ExpressionBase*, ExpressionBase*> init : *func->intitializers_) {
            uint32_t num_arguments = 0;
            value_t *args = new value_t[10];
            if (init.first != nullptr) {
                const value_t argument_v = walk_expression_base(init.first);
                if (func->arguments_.size() > 1) {
                    List *list = argument_v.value.list;
                    for (auto iter = list->begin(); iter != list->end(); iter++) {
                        args[num_arguments] = *iter;
                        num_arguments += 1;
                    }
                } else {
                    args[num_arguments] = argument_v;
                    num_arguments += 1;
                }
            }

            if (function_map.count(ArgumentsKey(args, num_arguments, false)) != 0) {
                yy::location loc = init.first ? init.first->location+init.second->location
                                              : init.second->location;
                throw RuntimeException(loc, "function `" + func->name +
                                            arguments_to_string(num_arguments, args) +
                                            "` already initialized");
            }

            value_t v = walk_expression_base(init.second);
            if (func->subrange_return) {
                if (v.value.integer < func->return_type_->subrange_start ||
                    v.value.integer > func->return_type_->subrange_end) {
                    yy::location loc = init.first ? init.first->location+init.second->location
                                                    : init.second->location;
                    throw RuntimeException(loc, std::to_string(v.value.integer) +
                                                " does violate the subrange "
                                                + std::to_string(func->return_type_->subrange_start)
                                                + ".." + std::to_string(func->return_type_->subrange_end)
                                                + " of `" + func->name + "`");
                }
            }
            function_map.emplace(std::make_pair(ArgumentsKey(args, num_arguments, true), v));

            initializer_args.push_back(args);
        }
    }

    initialized.insert(name);
    return true;
}

void ExecutionWalker::run()
{
    for (auto pair : global_driver->init_dependencies) {
        std::set<std::string> visited;
        if (initialized.count(pair.first) > 0) {
            continue;;
        }
        if (!init_function(pair.first, visited)) {
            Function *func = global_driver->function_table.get_function(pair.first);
            std::string cycle = pair.first;
            for (const std::string& dep : visited) {
                cycle = cycle + " => " + dep;
            }
            throw RuntimeException(func->intitializers_->at(0).second->location,
                                   "initializer dependency cycle detected: " + cycle);
        }
    }


    for (auto pair: global_driver->function_table.table_) {
        if (pair.second->type != Symbol::SymbolType::FUNCTION || initialized.count(pair.first) > 0) {
            continue;
        }

        std::set<std::string> visited;
        init_function(pair.first, visited);
    }

    for (List *l : visitor.temp_lists) {
        l->bump_usage();
    }

    visitor.temp_lists.clear();

    uint64_t stepCounter = 0;

    Function *program_sym = global_driver->function_table.get_function("program");
    const auto& function_map = visitor.function_states[program_sym->id];
    const value_t& program_val = function_map.at(ArgumentsKey(nullptr, 0, false));

    while (program_val.type != TypeType::UNDEF) {
        walk_rule(program_val.value.rule);
        visitor.applyUpdates();
        ++stepCounter;
    }

    std::cout << (stepCounter - 2);
    if ((stepCounter - 2) > 1) {
        std::cout << " steps later..." << std::endl;
    } else {
        std::cout << " step later..." << std::endl;
    }
}

//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//  
