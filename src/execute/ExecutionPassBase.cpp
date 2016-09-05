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

#include "ExecutionPassBase.h"

#include <cstring>
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

ArgumentsKey::ArgumentsKey(const value_t args[], uint32_t size, bool dyn) :
    size(size),
    dynamic(dyn)
{
    if (dynamic) {
        auto argsDup = new value_t[size];
        memcpy(argsDup, args, sizeof(value_t) * size);
        p = argsDup;
    } else {
        p = args;
    }
}

ArgumentsKey::ArgumentsKey(const ArgumentsKey& other) :
    p(other.p),
    size(other.size),
    dynamic(other.dynamic)
{

}

ArgumentsKey::ArgumentsKey(ArgumentsKey&& other) noexcept
{
    p = other.p;
    dynamic = other.dynamic;
    size = other.size;
    other.dynamic = false;
}

ArgumentsKey::~ArgumentsKey()
{
    if (dynamic) {
        delete[] p;
    }
}

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

bool ExecutionPassBase::hasEmptyUpdateSet() const
{
    return updateSetManager.currentUpdateSet()->empty();
}

Update* ExecutionPassBase::addUpdate(Function *sym, const value_t& val,
                                     uint32_t num_arguments, value_t arguments[],
                                     const yy::location& location)
{
    try
    {
        sym->validateArguments(num_arguments, arguments);
    }
    catch( const std::domain_error& e )
    {
        throw RuntimeException
        ( location
        , e.what()
        , libcasm_fe::Codes::FunctionArgumentsInvalidRangeAtUpdate
        );
    }
    
    try
    {
        sym->validateValue(val);
    }
    catch( const std::domain_error& e )
    {
        throw RuntimeException
        ( location
        , e.what()
        , libcasm_fe::Codes::FunctionValueInvalidRangeAtUpdate
        );
    }
    
    
    auto& function_map = function_states[sym->id];
    auto it = function_map.find(ArgumentsKey(arguments, num_arguments, false)); // TODO EP: use emplace only
    if (it == function_map.cend()) {
        const auto pair = function_map.emplace(ArgumentsKey(arguments, num_arguments, true), value_t());
        it = pair.first;
    }

    Update* up = reinterpret_cast<Update*>(stack.allocate(sizeof(Update))); // FIXME make it nicer!!
    up->value = val;
    up->func = sym->id;
    up->args = const_cast<value_t*>(it->first.p);
    up->num_args = num_arguments;
    up->line = location.begin.line;

    try {
        const value_t& ref = it->second;
        updateSetManager.add(reinterpret_cast<uint64_t>(&ref), up);
    } catch (const UpdateSet::Conflict& e) {
        const auto conflictingUpdate = e.conflictingUpdate();
        const auto existingUpdate = e.existingUpdate();

        const auto info = "Conflict while adding update " + sym->name
                        + arguments_to_string(conflictingUpdate->num_args, conflictingUpdate->args)
                        + " = " + val.to_str() + " at line " + std::to_string(up->line)
                        + ", conflicting with line " + std::to_string(existingUpdate->line)
                        + " with value '" + existingUpdate->value.to_str() + "'";
        throw RuntimeException(location, info);
    }

    return up;
}

void ExecutionPassBase::fork(const UpdateSet::Type updateSetType)
{
    updateSetManager.fork(updateSetType);
}

void ExecutionPassBase::merge()
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

void ExecutionPassBase::applyUpdates()
{
    assert(updateSetManager.size() == 1);

    std::vector<value_t*> to_fold;

    auto updateSet = updateSetManager.currentUpdateSet();
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
    }
    updateSetManager.clear();

    // Handle lists
    // 1. convert chained lists to BottomLists
    for (value_t* v : to_fold) {
        BottomList *new_l = v->value.list->collect();
        if (new_l->check_allocated_and_set_to_false()) {
            temp_lists.push_back(new_l);
        }
        v->value.list = new_l;
    }

    // delete all list objects, except BottomLists that are currently used
    std::vector<size_t> deleted;
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

const value_t ExecutionPassBase::get_function_value
( Function *sym
, uint32_t num_arguments
, const value_t arguments[]
)
{
    try
    {
        sym->validateArguments(num_arguments, arguments);
    }
    catch( const std::domain_error& e )
    {
        throw RuntimeException
        ( sym->location
        , e.what()
        , libcasm_fe::Codes::FunctionArgumentsInvalidRangeAtLookup
        );
    }
    
    const auto &function_map = function_states[sym->id];
    const value_t &v = function_map.at(ArgumentsKey(arguments, num_arguments, false));
    const auto update = updateSetManager.lookup( reinterpret_cast< uint64_t >( &v ) );
    
    if( update )
    {
        return update->value;
    }
    else
    {
        return v;
    }
}

bool ExecutionPassBase::filter_enabled(const std::string& filter)
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

    static const value_t dec(const value_t& arg)
    {
        // TODO LEAK!
        if (arg.is_undef()) {
            return value_t(new std::string("undef"));
        }

        std::stringstream ss;
        if (arg.value.integer < 0) {
            ss << "-" << std::dec << (-1) * arg.value.integer;
        } else {
            ss << std::dec << arg.value.integer;
        }
        return value_t(new std::string(ss.str()));
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

    const value_t cons(std::vector<List*>& tempLists, const value_t& val, const value_t& list)
    {
        // TODO LEAK
        if (list.is_undef()) {
            return value_t();
        }

        HeadList *consed_list = new HeadList(list.value.list, val);
        tempLists.push_back(consed_list);
        return value_t(list.type, consed_list);
    }

    const value_t tail(std::vector<List*>& tempLists, const value_t& arg_list)
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

    const value_t peek(const value_t& arg_list)
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

    static const value_t asbit(const value_t& arg, const value_t& bitsize)
    {
        return asinteger(arg); // TODO EP: fix this once we have a proper bit implementation
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
        auto result = new rational_t;
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

    static const value_t issymbolic(const value_t& arg)
    {
        if (arg.is_symbolic() && !arg.value.sym->list) {
            return value_t(true);
        } else {
            return value_t(false);
        }
    }
}


void ExecutionPassBase::visit_assert( UnaryNode* assert, const value_t& val )
{
    if( not val.value.boolean )
    {
        throw RuntimeException
        ( assert->location
        , "assertion failed"
        , libcasm_fe::Codes::AssertInvalidExpression
        );
    }
}


void ExecutionPassBase::visit_update_dumps(UpdateNode *update, const value_t& expr_v)
{
    const std::string& filter = global_driver->function_trace_map[update->func->symbol->id];
    if (filter_enabled(filter)) {
        std::cout << filter << ": "
                  << update->func->symbol->name << arguments_to_string(num_arguments, arguments)
                  << " = " << expr_v.to_str() << std::endl;
    }

    visit_update(update, expr_v);
}

void ExecutionPassBase::visit_update(UpdateNode *update, const value_t& expr_v)
{
    addUpdate(update->func->symbol, expr_v, num_arguments, arguments, update->location);
}

void ExecutionPassBase::visit_call_pre(CallNode *call)
{
    UNUSED(call);
}

void ExecutionPassBase::visit_call_pre(CallNode *call, const value_t& expr)
{
    if (expr.type != TypeType::UNDEF) {
        call->rule = expr.value.rule;
    } else {
        throw RuntimeException(call->location, "Cannot call UNDEF");
    }
}

void ExecutionPassBase::visit_call( CallNode *call, std::vector< value_t > &argument_results )
{
    if( call->ruleref )
    {
        // only relevant for indirect calls
        const size_t args_defined = call->rule->arguments.size();
        const size_t args_provided = argument_results.size();

        if( args_defined != args_provided )
        {
            throw RuntimeException
            ( call->location
            , "indirectly called rule '"
              + call->rule->name
              + "' expects "
              + std::to_string( args_defined )
              + " arguments but "
              + std::to_string( args_provided )
              + " were provided"
            , libcasm_fe::Codes::RuleArgumentsSizeInvalidAtIndirectCall
            );
        }
        else
        {
            for( size_t i = 0; i < args_defined; i++ )
            {
                const auto arg = argument_results.at( i );
                
                Type argType( arg.type );
                
                Type ruleArgType = call->rule->arguments.at( i );
                
                if( not (ruleArgType.unify( &argType ) or arg.is_undef()) )
                {
                    throw RuntimeException
                    ( call->arguments->at( i )->location
                    , "argument "
                      + std::to_string( i + 1 )
                      + " of indirectly called rule `"
                      + call->rule->name
                      + "` must be `"
                      + ruleArgType.to_str()
                      + "` but was `"
                      + argType.to_str()
                      + "`"
                    , libcasm_fe::Codes::RuleArgumentsTypeInvalidAtIndirectCall
                    );
                }
            }
        }
    }
    
    // arguments validation
    for( size_t i = 0; i < argument_results.size(); i++ )
    {
        const auto arg = argument_results.at( i );

        Type ruleArgType = call->rule->arguments.at( i );

        switch( ruleArgType.t )
        {
            case TypeType::INTEGER:
            {
                const INTEGER_T integer = arg.value.integer;
                
                if( ruleArgType.has_range_restriction()
                and (  integer < ruleArgType.subrange_start
                    or integer > ruleArgType.subrange_end
                    )
                )
                {
                    throw RuntimeException
                    ( call->arguments->at( i )->location
                    , std::to_string( integer )
                      + " does violate the subrange "
                      + std::to_string( ruleArgType.subrange_start )
                      + ".."
                      + std::to_string( ruleArgType.subrange_end )
                      + " at argument #"
                      + std::to_string( i + 1 )
                      + " of rule '"
                      + ( call->ruleref ? call->rule->name : call->rule_name )
                      + "'"
                    , libcasm_fe::Codes::RuleArgumentsInvalidRangeAtCall
                    );
                }
                break;
            }
            default:
            {
                break;
            }
        }
    }
    
    rule_bindings.push_back( &argument_results );
}

void ExecutionPassBase::visit_call_post(CallNode *call)
{
    UNUSED(call);
    rule_bindings.pop_back();
}

void ExecutionPassBase::visit_diedie(DiedieNode *node, const value_t& msg)
{
    if (node->msg) {
        throw RuntimeException(node->location, *msg.value.string);
    } else {
        throw RuntimeException(node->location, "`diedie` executed");
    }
}

void ExecutionPassBase::visit_impossible(AstNode *node)
{
    throw RuntimeException(node->location, "`impossible` executed");
}

void ExecutionPassBase::visit_let(LetNode*, const value_t& v)
{
    rule_bindings.back()->push_back(v);
}

void ExecutionPassBase::visit_let_post(LetNode*)
{
    rule_bindings.back()->pop_back();
}

const value_t ExecutionPassBase::visit_function_atom(FunctionAtom *atom,
                                                     const value_t arguments[],
                                                     uint16_t num_arguments)
{
    switch (atom->symbol_type) {
    case FunctionAtom::SymbolType::PARAMETER:
        return value_t(rule_bindings.back()->at(atom->offset));
    case FunctionAtom::SymbolType::FUNCTION:
        try {
            return get_function_value(atom->symbol, num_arguments, arguments);
        } catch (const RuntimeException& e) {
            throw RuntimeException(atom->location, e.what(), e.getErrorCode());
        }
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

const value_t ExecutionPassBase::visit_builtin_atom(BuiltinAtom *atom,
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
    case Builtin::Id::DEC:
        return builtins::dec(arguments[0]);
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
    case Builtin::Id::AS_BIT:
        return builtins::asbit(arguments[0], arguments[1]);
    case Builtin::Id::IS_SYMBOLIC:
        return builtins::issymbolic(arguments[0]);
    default:
        global_driver->error(atom->location, "unknown builtin `" + atom->to_str() + "`");
        return value_t();
    }
}

void ExecutionPassBase::visit_derived_function_atom_pre(FunctionAtom *function,
                                                        const value_t arguments[],
                                                        uint16_t num_arguments)
{
    try
    {
        function->symbol->validateArguments( num_arguments, arguments );
    }
    catch( const std::domain_error& e )
    {
        std::string msg = std::string( e.what() ) + " of derived '" + function->symbol->name + "'";
        
        throw RuntimeException
        ( function->location
        , msg.c_str()
        , libcasm_fe::Codes::DerivedArgumentsInvalidRangeAtLookup
        );
    }
    
    // TODO change, cleanup!
    std::vector<value_t> *tmp = new std::vector<value_t>();
    for( uint32_t i = 0; i < num_arguments; i++ )
    {
        tmp->push_back( arguments[ i ] );
    }
    
    rule_bindings.push_back( tmp );
}

const value_t ExecutionPassBase::visit_derived_function_atom(FunctionAtom*,
                                                             const value_t& expr)
{
    rule_bindings.pop_back();
    return expr;
}

const value_t ExecutionPassBase::visit_number_range_atom(NumberRangeAtom *atom)
{
    return value_t(atom->type_, atom->list);
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
