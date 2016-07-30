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

#include "SymbolicExecutionPass.h"

#include <iostream>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <cassert>
#include <utility>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdio>
#include <type_traits>

#include "../Driver.h"
#include "../Symbols.h"
#include "../Exceptions.h"

using namespace libcasm_fe;

extern Driver *global_driver;

char SymbolicExecutionPass::id = 0;

static libpass::PassRegistration< SymbolicExecutionPass > PASS
( "Symbolic Execution Pass"
, "execute symbolically over the AST the input specification"
, "ast-sym"
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

bool SymbolicExecutionPass::run(libpass::PassResult& pr)
{
    walker = new SymbolicExecutionWalker(*this);

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

        for (List *l : temp_lists) {
            l->bump_usage();
        }
        temp_lists.clear();

        mainLoop();
        printTrace();
    } catch (const RuntimeException& ex) {
        return false;
        std::cerr << "Abort after runtime exception: " << ex.what() << std::endl;
    } catch (const ImpossibleException& ex) {
        return false;
    } catch (char * e) {
        std::cerr << "Abort after catching a string: " << e << std::endl;
        return false;
    }

    return true;
}

namespace symbolic
{
    enum class check_status_t {
        NOT_FOUND,
        TRUE,
        FALSE
    };

    static uint32_t last_symbol_id = 1; // symbol id of 0 means 'non existing symbol'
    static uint32_t current_time = 2; // FIXME EP: why?

    const static uint32_t FINAL_TIME = 0;

    static uint32_t next_symbol_id()
    {
        return last_symbol_id++;
    }

    static void advance_timestamp()
    {
        ++current_time;
    }

    static uint32_t get_timestamp()
    {
        return current_time;
    }
}

#define CREATE_NUMERICAL_OPERATION(op, lhs, rhs)  {                             \
    if (lhs.is_symbolic() or rhs.is_symbolic()) {                               \
        return value_t(new symbol_t(symbolic::next_symbol_id()));               \
    }                                                                           \
                                                                                \
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
    if (lhs.is_undef() or rhs.is_undef()) {                                     \
        return value_t();                                                       \
    }                                                                           \
                                                                                \
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
        if (lhs.is_symbolic() or rhs.is_symbolic()) {
            return value_t(new symbol_t(symbolic::next_symbol_id()));
        }

        switch (lhs.type) {
        case TypeType::INTEGER:
            return value_t(lhs.value.integer % rhs.value.integer);
        default:
            return value_t();
        }
    }

    static const value_t rat_div(const value_t& lhs, const value_t& rhs)
    {
        if (lhs.is_symbolic() or rhs.is_symbolic()) {
            return value_t(new symbol_t(symbolic::next_symbol_id()));
        }

        switch (lhs.type) {
        case TypeType::INTEGER: {
            auto result = new rational_t;
            result->numerator = lhs.value.integer;
            result->denominator = rhs.value.integer;
            return value_t(result);
        }
        default:
            FAILURE();
        }
    }

    static const value_t lesser(const value_t& lhs, const value_t& rhs)
    {
        CREATE_COMPARE_OPERATION(<, lhs, rhs);
    }

    static const value_t greater(const value_t& lhs, const value_t& rhs)
    {
        CREATE_COMPARE_OPERATION(>, lhs, rhs);
    }

    static const value_t lessereq(const value_t& lhs, const value_t& rhs)
    {
        CREATE_COMPARE_OPERATION(<=, lhs, rhs);
    }

    static const value_t greatereq(const value_t& lhs, const value_t& rhs)
    {
        CREATE_COMPARE_OPERATION(>=, lhs, rhs);
    }
}

namespace symbolic
{
    static std::string symbol_to_string(const uint32_t sym_id)
    {
        return "sym" + std::to_string(sym_id);
    }

    static void fof(std::stringstream& ss, const std::string& name, const Function *func,
                    uint32_t num_arguments, const value_t arguments[], const value_t& val,
                    uint32_t time, const std::string &type)
    {
        ss << "fof(" << name << ",hypothesis,"
           << (func->is_static ? "cs" : "st") << func->name << "(" << time << ","
           << arguments_to_string(num_arguments, arguments) << val.to_str(true)
           << "))." << type << ": " << func->name;
        if (num_arguments > 0) {
            ss << '(' << arguments_to_string(num_arguments, arguments) << ')';
        }
        ss << std::endl;
    }

    static void dump_type(std::stringstream& ss, const value_t& v)
    {
        if (v.is_symbolic() and not v.value.sym->type_dumped) {
            ss << "tff(symbolNext, type, " << v.to_str() << ": $int)." << std::endl;
            v.value.sym->type_dumped = true;
        }
    }

    static void dump_catchup(std::vector<std::string>& trace, const Function *func,
                             uint32_t num_arguments, const value_t arguments[],
                             const value_t& v)
    {
        for (uint32_t i = 1; i < symbolic::get_timestamp() - 1; i++) {
            std::stringstream ss;
            fof(ss, "id%u", func, num_arguments, arguments, v, i, "%%CATCHUP");
            trace.push_back(ss.str());
        }
    }

    static void dump_create(std::vector<std::string>& trace, const Function *func,
                            uint32_t num_arguments, const value_t arguments[],
                            const value_t& v)
    {
        std::stringstream ss;
        dump_type(ss, v);
        fof(ss, "id%u", func, num_arguments, arguments, v, symbolic::get_timestamp() - 1,
            "%%CREATE");
        trace.push_back(ss.str());

        if (symbolic::get_timestamp() > 2) {
            dump_catchup(trace, func, num_arguments, arguments, v);
        }
    }

    static void dump_symbolic(std::vector<std::string>& trace, const Function *func,
                              uint32_t num_arguments, const value_t arguments[],
                              const value_t& v)
    {
        std::stringstream ss;
        fof(ss, "id%u", func, num_arguments, arguments, v, symbolic::get_timestamp(),
            "%%SYMBOLIC");
        trace.push_back(ss.str());
    }

    static void dump_update(std::vector<std::string>& trace, const Function *func,
                            uint32_t num_arguments, const value_t arguments[],
                            const value_t& v)
    {
        std::stringstream ss;
        dump_type(ss, v);
        fof(ss, "id%u", func, num_arguments, arguments, v, symbolic::get_timestamp(),
            "%%UPDATE");
        trace.push_back(ss.str());
    }

    static void dump_pathcond_match(std::vector<std::string>& trace,
                                    const std::string &filename, size_t lineno,
                                    const symbolic_condition_t *cond, bool status)
    {
        std::stringstream ss;
        ss << "% " << filename << ":" << lineno << " PC-LOOKUP (" << cond->to_str()
           << ") = " << status
           << std::endl;
        trace.push_back(ss.str());
    }

    static void dump_if(std::vector<std::string>& trace,
                        const std::string &filename, size_t lineno,
                        const symbolic_condition_t *cond)
    {
        std::stringstream ss;
        ss << "fof('id" << filename <<  ":" << lineno << "',hypothesis,"
           << cond->to_str() << ")."
           << std::endl;
        trace.push_back(ss.str());
    }

    static void dump_final(std::vector<std::string>& trace,
                           const std::vector<const Function*>& symbols,
                           const std::vector<std::unordered_map<ArgumentsKey, value_t>>& states)
    {
        std::stringstream ss;
        uint32_t i = 0;
        for (uint32_t j = 0; j < symbols.size(); j++) {
            if (not symbols[j]->is_symbolic) {
                continue;
            }
            for (auto& value_pair : states[j]) {
                const auto arguments = value_pair.first;
                const auto value = value_pair.second;

                fof(ss, "final", symbols[j], arguments.size, arguments.p, value,
                    FINAL_TIME, "%FINAL");
                i += 1;
            }
        }
        trace.push_back(ss.str());
    }

    constexpr inline uint16_t operator ,(const ExpressionOperation lhs,
                                         const ExpressionOperation rhs) noexcept
    {
        static_assert(sizeof(ExpressionOperation) == 1,
                      "uint8_t | (uint8_t << 8) == uint16_t");
        return (static_cast<uint16_t>(lhs) << 8) | static_cast<uint16_t>(rhs);
    }

    static check_status_t check_inclusion(const symbolic_condition_t& known,
                                          const symbolic_condition_t& check)
    {
        switch (check.op, known.op) {
        case (ExpressionOperation::EQ, ExpressionOperation::EQ):
            return (*known.rhs == *check.rhs) ? check_status_t::TRUE
                                              : check_status_t::FALSE;
        case (ExpressionOperation::EQ, ExpressionOperation::NEQ):
            return (*known.rhs == *check.rhs) ? check_status_t::FALSE
                                              : check_status_t::NOT_FOUND;
        case (ExpressionOperation::NEQ, ExpressionOperation::NEQ):
            return (*known.rhs == *check.rhs) ? check_status_t::TRUE
                                              : check_status_t::NOT_FOUND;
        case (ExpressionOperation::NEQ, ExpressionOperation::EQ):
            return (*known.rhs == *check.rhs) ? check_status_t::FALSE
                                              : check_status_t::TRUE;
        case (ExpressionOperation::LESSEREQ, ExpressionOperation::EQ): {
            const value_t res = operators::lessereq(*known.rhs, *check.rhs);
            return res.value.boolean ? check_status_t::TRUE
                                     : check_status_t::FALSE;
        }
        case (ExpressionOperation::LESSEREQ, ExpressionOperation::LESSEREQ): {
            const value_t res = operators::lessereq(*check.rhs, *known.rhs);
            return res.value.boolean ? check_status_t::TRUE
                                     : check_status_t::NOT_FOUND;
        }
        case (ExpressionOperation::LESSEREQ, ExpressionOperation::GREATER): {
            const value_t res = operators::lessereq(*check.rhs, *known.rhs);
            return res.value.boolean ? check_status_t::FALSE
                                     : check_status_t::NOT_FOUND;
        }
        case (ExpressionOperation::GREATER, ExpressionOperation::EQ): {
            const value_t res = operators::greater(*known.rhs, *check.rhs);
            return res.value.boolean ? check_status_t::TRUE
                                     : check_status_t::FALSE;
        }
        case (ExpressionOperation::GREATER, ExpressionOperation::LESSEREQ): {
            const value_t res = operators::greater(*check.rhs, *known.rhs);
            return res.value.boolean ? check_status_t::FALSE
                                     : check_status_t::NOT_FOUND;
        }
        case (ExpressionOperation::GREATER, ExpressionOperation::GREATER): {
            const value_t res = operators::greater(*check.rhs, *known.rhs);
            return res.value.boolean ? check_status_t::TRUE
                                     : check_status_t::NOT_FOUND;
        }
        default:
            return check_status_t::NOT_FOUND;
        }
    }

    static check_status_t check_condition(const std::vector<symbolic_condition_t*>& known_conditions,
                                          const symbolic_condition_t *check)
    {
        symbolic_condition_t cond(check->lhs, check->rhs, check->op);

        if (check->lhs->type != TypeType::SYMBOL) {
            if (check->rhs->type == TypeType::SYMBOL) {
                cond = symbolic_condition_t(check->rhs, check->lhs, check->op);
            } else {
                throw RuntimeException("Invalid condition passed");
            }
        }

        for (auto known_cond : known_conditions) {
            check_status_t s = check_status_t::NOT_FOUND;
            if (*(known_cond->lhs) == *(cond.lhs)) {
                s = check_inclusion(*known_cond, cond);
            } else if (*(known_cond->rhs) == *(cond.lhs)) {
                s = check_inclusion(symbolic_condition_t(known_cond->rhs,
                                                         known_cond->lhs,
                                                         known_cond->op), cond);
            }
            if (s != check_status_t::NOT_FOUND) {
                return s;
            }
        }

        return check_status_t::NOT_FOUND;
    }

    static uint32_t dump_listconst(std::vector<std::string>& trace, List *l)
    {
        uint32_t sym_id = 0;

        const auto end = l->end();
        for (auto it = l->begin(); it != end; ++it) {
            const uint32_t prev_sym_id = sym_id;
            sym_id = symbolic::next_symbol_id();

            std::stringstream ss;
            ss << "tff(symbolNext,type," << symbol_to_string(sym_id) << ": $int)."
               << std::endl
               << "fof(id%u,hypothesis,fcons("
               << ((prev_sym_id > 0) ? symbol_to_string(sym_id) : "eEmptyList")
               << "," << (*it).to_str(true) << "," << symbol_to_string(sym_id) << "))."
               << std::endl;
            trace.push_back(ss.str());
        }

        return sym_id;
    }

    static void dump_builtin(std::vector<std::string>& trace, const std::string& name,
                             const value_t arguments[], uint16_t num_arguments,
                             const value_t& ret)
    {
        std::stringstream ss;

        for (uint16_t i = 0; i < num_arguments; i++) {
            dump_type(ss, arguments[i]);
        }
        dump_type(ss, ret);

        ss << "fof(id%u,hypothesis,f" << name << '('
           << arguments_to_string(num_arguments, arguments) << "))."
           << std::endl;

        trace.push_back(ss.str());
    }
}

void SymbolicExecutionPass::visit_assure(UnaryNode* assure, const value_t& val)
{
    if (val.is_symbolic() && val.value.sym->condition) {
        path_conditions.push_back(val.value.sym->condition);
    } else {
        visit_assert(assure, val);
    }
}

void SymbolicExecutionPass::visit_print(PrintNode *node, const std::vector<value_t> &arguments)
{
    std::stringstream ss;
    if (node->filter.size() > 0 ) {
        if (filter_enabled(node->filter)) {
            ss << node->filter << ": ";
        } else {
            return;
        }
    }

    for (const value_t& v: arguments) {
        ss << v.to_str();
    }
    ss << std::endl;

    trace.push_back(ss.str());
}

void SymbolicExecutionPass::visit_push(PushNode *node, const value_t& expr, const value_t& atom)
{
    num_arguments = 0; // TODO at the moment, functions with arguments are not supported

    const value_t to_res(new symbol_t(symbolic::next_symbol_id()));
    if (atom.value.sym->list) {
        to_res.value.sym->list = builtins::cons(temp_lists, expr,
                                                value_t(TypeType::LIST, atom.value.sym->list)).value.list;
    } else {
        to_res.value.sym->list = builtins::cons(temp_lists, expr,
                                                value_t(TypeType::LIST, new BottomList())).value.list;
    }

    addUpdate(to_res, node->to->symbol->id, num_arguments, arguments, node->location.begin.line);

    value_t args[] = {atom, expr};
    symbolic::dump_builtin(trace, "push", args, 2, to_res);
}

void SymbolicExecutionPass::visit_pop(PopNode *node, const value_t& val)
{
    num_arguments = 0; // TODO at the moment, functions with arguments are not supported

    const value_t to_res = (val.value.sym->list) ? builtins::peek(value_t(TypeType::LIST, val.value.sym->list))
                                                 : value_t(new symbol_t(symbolic::next_symbol_id()));

    Update *up = nullptr;
    if (node->to->symbol_type == FunctionAtom::SymbolType::FUNCTION) {
        up = addUpdate(to_res, node->to->symbol->id, num_arguments, arguments, node->location.begin.line);
    } else {
        rule_bindings.back()->push_back(to_res);
    }

    const value_t from_res(new symbol_t(symbolic::next_symbol_id()));
    if (val.value.sym->list) {
        from_res.value.sym->list = builtins::tail(temp_lists,
                                                  value_t(TypeType::LIST, val.value.sym->list)).value.list;
    }

    value_t args[] = {val, to_res};
    symbolic::dump_builtin(trace, "pop", args, 2, from_res);

    addUpdate(from_res, node->from->symbol->id, num_arguments, arguments, node->location.begin.line);
}

const value_t SymbolicExecutionPass::visit_expression(Expression *expr,
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
        if (left_val.is_symbolic() and right_val.is_symbolic() and left_val == right_val) {
            return value_t(false);
        }
        if (left_val.is_symbolic() or right_val.is_symbolic()) {
            auto symCond = new symbolic_condition_t(new value_t(left_val),
                                                    new value_t(right_val),
                                                    expr->op);
            return value_t(new symbol_t(symbolic::next_symbol_id(), symCond));
        }
        operators::lesser(left_val, right_val);
    case ExpressionOperation::GREATER:
        if (left_val.is_symbolic() and right_val.is_symbolic() and left_val == right_val) {
            return value_t(false);
        }
        if (left_val.is_symbolic() or right_val.is_symbolic()) {
            auto symCond = new symbolic_condition_t(new value_t(left_val),
                                                    new value_t(right_val),
                                                    expr->op);
            return value_t(new symbol_t(symbolic::next_symbol_id(), symCond));
        }
        operators::greater(left_val, right_val);
    case ExpressionOperation::LESSEREQ:
        if (left_val.is_symbolic() and right_val.is_symbolic() and left_val == right_val) {
            return value_t(true);
        }
        if (left_val.is_symbolic() or right_val.is_symbolic()) {
            auto symCond = new symbolic_condition_t(new value_t(left_val),
                                                    new value_t(right_val),
                                                    expr->op);
            return value_t(new symbol_t(symbolic::next_symbol_id(), symCond));
        }
        operators::lessereq(left_val, right_val);
    case ExpressionOperation::GREATEREQ:
        if (left_val.is_symbolic() and right_val.is_symbolic() and left_val == right_val) {
            return value_t(true);
        }
        if (left_val.is_symbolic() or right_val.is_symbolic()) {
            auto symCond = new symbolic_condition_t(new value_t(left_val),
                                                    new value_t(right_val),
                                                    expr->op);
            return value_t(new symbol_t(symbolic::next_symbol_id(), symCond));
        }
        operators::greatereq(left_val, right_val);
    default:
        FAILURE();
    }
}

const value_t SymbolicExecutionPass::visit_expression_single(Expression *expr,
                                                             const value_t &val)
{
    if (val.is_undef()) {
        return value_t();
    } else if (val.is_symbolic()) {
        return value_t(new symbol_t(symbolic::next_symbol_id()));
    }

    switch (expr->op) {
    case ExpressionOperation::NOT:
        return value_t(not val.value.boolean);
    default:
        FAILURE();
    }
}

const value_t SymbolicExecutionPass::visit_list_atom(ListAtom *atom,
                                                    const std::vector<value_t> &vals)
{
    BottomList *list = new BottomList(vals);
    //context_.temp_lists.push_back(list);

    const uint32_t sym_id = symbolic::dump_listconst(trace_creates, list);
    if (sym_id > 0) {
        // TODO cleanup symbols
        symbol_t *sym = new symbol_t(sym_id);
        sym->type_dumped = true;
        sym->list = list;
        return value_t(sym);
    } else {
        return value_t(atom->type_, list);
    }
}

bool SymbolicExecutionPass::init_function(const std::string& name, std::set<std::string>& visited)
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

    function_states[func->id] = std::unordered_map<ArgumentsKey, value_t>(0);
    function_symbols[func->id] = func;

    auto& function_map = function_states[func->id];

    if (func->intitializers_ != nullptr) {
        for (std::pair<ExpressionBase*, ExpressionBase*> init : *func->intitializers_) {
            uint32_t num_arguments = 0;
            value_t *args = new value_t[10];
            if (init.first != nullptr) {
                const value_t argument_v = walker->walk_expression_base(init.first);
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

            if (func->is_symbolic) {
                const value_t v = walker->walk_expression_base(init.second);
                symbolic::dump_create(trace_creates, func, num_arguments, args, v);
                function_map.emplace(std::pair<ArgumentsKey, value_t>(ArgumentsKey(args, num_arguments, true), v));
            } else {
                value_t v = walker->walk_expression_base(init.second);
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
            }

            initializer_args.push_back(args);
        }
    }

    initialized.insert(name);
    return true;
}

void SymbolicExecutionPass::mainLoop()
{
    Function *program_sym = global_driver->function_table.get_function("program");
    const auto& function_map = function_states[program_sym->id];
    const value_t& program_val = function_map.at(ArgumentsKey(nullptr, 0, false));

    while (program_val.type != TypeType::UNDEF) {
        walker->walk_rule(program_val.value.rule);
        applyUpdates();
        symbolic::advance_timestamp();
    }

    symbolic::dump_final(trace, function_symbols, function_states);
}

void SymbolicExecutionPass::printTrace() const
{
    FILE *out;
    /*if (fileout) { TODO EP
        const std::string& filename = global_driver->get_filename().substr(
            0, global_driver->get_filename().rfind("."));

        out = fopen((filename + "_"  + path_name + ".trace").c_str(), "wt");
    } else {*/
        out = stdout;
    //}
    fprintf(out, "forklog:%s\n", path_name.c_str());
    uint32_t fof_id = 0;
    for (const std::string& s :trace_creates) {
        if (s.find("id%u") != std::string::npos) {
            fprintf(out, s.c_str(), fof_id);
            fof_id += 1;
        } else {
            fprintf(out, "%s", s.c_str());
        }
    }
    for (const std::string& s : trace) {
        if (s.find("id%u") != std::string::npos) {
            fprintf(out, s.c_str(), fof_id);
            fof_id += 1;
        } else {
            fprintf(out, "%s", s.c_str());
        }
    }
    fprintf(out, "\n");
}

static ExpressionOperation invert(ExpressionOperation op)
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
value_t SymbolicExecutionWalker::walk_list_atom(ListAtom *atom)
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
void SymbolicExecutionWalker::walk_ifthenelse(IfThenElseNode* node)
{
    const value_t cond = walk_expression_base(node->condition_);

    if (cond.is_symbolic()) {
        symbolic_condition_t *sym_cond;
        if (cond.value.sym->condition) {
            sym_cond = cond.value.sym->condition;
        } else {
            sym_cond = new symbolic_condition_t(new value_t(cond),
                                                new value_t((INTEGER_T)1),
                                                ExpressionOperation::EQ);
        }

        switch (symbolic::check_condition(visitor.path_conditions, sym_cond)) {
        case symbolic::check_status_t::NOT_FOUND:
            break;
        case symbolic::check_status_t::TRUE:
            symbolic::dump_pathcond_match(visitor.trace, global_driver->get_filename(),
                                          node->condition_->location.begin.line,
                                          sym_cond, true);
            walk_statement(node->then_);
            return;
        case symbolic::check_status_t::FALSE:
            symbolic::dump_pathcond_match(visitor.trace, global_driver->get_filename(),
                                          node->condition_->location.begin.line,
                                          sym_cond, false);

            if (node->else_) {
                walk_statement(node->else_);
            }
            return;
        }

        pid_t pid = fork();
        switch (pid) {
        case -1:
            throw RuntimeException("Could not fork");
        case 0:
            visitor.path_name += "I";
            symbolic::dump_if(visitor.trace, global_driver->get_filename(),
                              node->condition_->location.begin.line, sym_cond);
            visitor.path_conditions.push_back(sym_cond);
            walk_statement(node->then_);
            break;
        default: {
            // at the moment this limits parallelism, but ensures a deterministic
            // trace output on stdout
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                throw RuntimeException("error waiting for child process");
            }
            if (WEXITSTATUS(status) != 0) {
                throw RuntimeException("error in child process");
            }

            if (cond.value.sym->condition) {
                sym_cond->op = invert(sym_cond->op);
            } else {
                // needed to generate correct output for boolean functions as conditions
                delete sym_cond;
                sym_cond = new symbolic_condition_t(new value_t(cond),
                                                    new value_t((INTEGER_T)0), ExpressionOperation::EQ);
            }
            visitor.path_name += "E";
            symbolic::dump_if(visitor.trace, global_driver->get_filename(),
                              node->condition_->location.begin.line, sym_cond);
            visitor.path_conditions.push_back(sym_cond);
            if (node->else_) {
                walk_statement(node->else_);
            }
        }
        }
    } else if (cond.is_undef()) {
        throw RuntimeException(node->condition_->location,
                               "condition must be true or false but was undef");
    } else if (cond.value.boolean) {
        walk_statement(node->then_);
    } else if (node->else_) {
        walk_statement(node->else_);
    }
}

template <>
void SymbolicExecutionWalker::walk_seqblock(UnaryNode* seqblock)
{
    visitor.fork(UpdateSet::Type::Sequential);
    visitor.visit_seqblock(seqblock);
    walk_statements(reinterpret_cast<AstListNode*>(seqblock->child_));
    visitor.merge();
}

template <>
void SymbolicExecutionWalker::walk_parblock(UnaryNode* parblock)
{
    visitor.fork(UpdateSet::Type::Parallel);
    visitor.visit_parblock(parblock);
    walk_statements(reinterpret_cast<AstListNode*>(parblock->child_));
    visitor.merge();
}

template <>
void SymbolicExecutionWalker::walk_pop(PopNode* node)
{
    const value_t from = walk_function_atom(node->from);
    if (node->to->symbol_type == FunctionAtom::SymbolType::FUNCTION and
            node->to->symbol->is_symbolic) {
        walk_function_atom(node->to);
    }
    visitor.visit_pop(node, from);
}

template <>
void SymbolicExecutionWalker::walk_push(PushNode *node)
{
    const value_t expr = walk_expression_base(node->expr);
    const value_t atom = walk_function_atom(node->to);
    visitor.visit_push(node, expr, atom);
}

template <>
void SymbolicExecutionWalker::walk_case(CaseNode *node)
{
    const value_t cond = walk_expression_base(node->expr);

    for (uint32_t i = 0; i < node->case_list.size(); i++) {
        auto pair = node->case_list[i];
        // pair.first == nullptr for default:
        symbolic_condition_t *sym_cond;
        if (pair.first) {
            const value_t c = walk_atom(pair.first);
            sym_cond = new symbolic_condition_t(new value_t(cond), new value_t(c),
                                                ExpressionOperation::EQ);

            switch (symbolic::check_condition(visitor.path_conditions, sym_cond)) {
            case symbolic::check_status_t::NOT_FOUND:
                break;
            case symbolic::check_status_t::TRUE:
                symbolic::dump_pathcond_match(visitor.trace, global_driver->get_filename(),
                                              pair.first->location.begin.line,
                                              sym_cond, true);
                walk_statement(pair.second);
                return;
            default:
                break;
            }
        }

        pid_t pid = fork();
        switch (pid) {
        case -1:
            throw RuntimeException("Could not fork");
        case 0: {
            if (pair.first) {
                visitor.path_name += std::to_string(i);
                visitor.path_conditions.push_back(sym_cond);
                symbolic::dump_if(visitor.trace, global_driver->get_filename(),
                                  pair.first->location.begin.line, sym_cond);
            } else {
                visitor.path_name += "D";
            }
            walk_statement(pair.second);
        }   return;
        default: {
            // at the moment this limits parallelism, but ensures a deterministic
            // trace output on stdout
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                throw RuntimeException("error waiting for child process");
            }
            if (WEXITSTATUS(status) != 0) {
                throw RuntimeException("error in child process");
            }
        }
        }
    }
    exit(0); // FIXME EP: ask Florian if this is indended
}

template <>
void SymbolicExecutionWalker::walk_forall(ForallNode *node)
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
void SymbolicExecutionWalker::walk_iterate(UnaryNode *node)
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

static void walk_function_arguments(SymbolicExecutionWalker* walker, std::vector<ExpressionBase*>* arguments)
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
void SymbolicExecutionWalker::walk_update(UpdateNode *node)
{
    const value_t expr = walk_expression_base(node->expr_);
    if (node->func->symbol->is_symbolic) {
        walk_expression_base(node->func);
    }
    walk_function_arguments(this, node->func->arguments);
    visitor.visit_update(node, expr);
}

template <>
void SymbolicExecutionWalker::walk_update_subrange(UpdateNode *node)
{
    const value_t expr = walk_expression_base(node->expr_);
    if (node->func->symbol->is_symbolic or
            (node->func->symbol->subrange_arguments.size() > 0)) {
        walk_expression_base(node->func);
    }
    walk_function_arguments(this, node->func->arguments);
    visitor.visit_update_subrange(node, expr);
}

template <>
void SymbolicExecutionWalker::walk_update_dumps(UpdateNode *node)
{
    const value_t expr = walk_expression_base(node->expr_);
    walk_function_arguments(this, node->func->arguments);
    visitor.visit_update_dumps(node, expr);
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
