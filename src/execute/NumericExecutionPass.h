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

#ifndef _LIB_CASMFE_NUMERICEXECUTIONPASS_H_
#define _LIB_CASMFE_NUMERICEXECUTIONPASS_H_

#include "libpass.h"
#include "libcasm-fe.all.h"

#include "UpdateSet.h"
#include "../allocator/BlockAllocator.h"
#include "../Visitor.h"
#include "../Ast.h"

#define TEMP_STACK_SIZE 32768
#define VALUE_STACK_SIZE 32768

/**
   @brief    TODO
   
   TODO
*/

struct ArgumentsKey {
    const value_t* p;
    uint32_t size;
    bool dynamic;

    // size must be equal to the size specified in the function type
    ArgumentsKey(const value_t args[], uint32_t size, bool dyn);
    ArgumentsKey(const ArgumentsKey& other);
    ArgumentsKey(ArgumentsKey&& other) noexcept;
    ~ArgumentsKey();
};



namespace std {

    template <> struct hash<ArgumentsKey> {
        size_t operator()(const ArgumentsKey &key) const {
            size_t h = 0;
            for (uint32_t i = 0; i < key.size; i++) {
                assert(not key.p[i].is_symbolic());
                static std::hash<value_t> value_hasher;
                h ^= value_hasher(key.p[i]);
            }
            return h;
        }
    };

    template <> struct equal_to<ArgumentsKey> {
        bool operator()(const ArgumentsKey &lhs, const ArgumentsKey &rhs) const {
            for (uint32_t i = 0; i < lhs.size; i++) {
                if (lhs.p[i] != rhs.p[i]) {
                    return false;
                }
            }
            return true;
        }
    };
}

namespace libcasm_fe
{
    class NumericExecutionPass : public libpass::Pass, public BaseVisitor<value_t>
    {
    public:
        static char id;

        virtual bool run( libpass::PassResult& pr );

        bool hasEmptyUpdateSet() const;
        Update* addUpdate(const value_t& val, size_t sym_id, uint32_t num_arguments, value_t arguments[], uint64_t line);
        void applyUpdates();

        void fork(const UpdateSet::Type updateSetType);
        void merge();

        const value_t get_function_value(Function *sym, uint32_t num_arguments, const value_t arguments[]);

        bool filter_enabled(const std::string& filter);

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

    private:
        std::vector<value_t> main_bindings;
        UpdateSetManager updateSetManager;

        const bool dump_updates = false;
        std::vector<std::string> update_dump;

        BlockAllocator<TEMP_STACK_SIZE> stack;
        std::map<const std::string, bool> debuginfo_filters;

    public:
        std::vector<value_t> value_list;
        std::vector<std::vector<value_t> *> rule_bindings;

        value_t arguments[10];
        uint32_t num_arguments;

        std::vector<std::unordered_map<ArgumentsKey, value_t>> function_states;
        std::vector<const Function*> function_symbols;

        std::vector<List*> temp_lists;

        static BlockAllocator<VALUE_STACK_SIZE> value_stack;
    };
}

template <>
value_t AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_list_atom(ListAtom *atom);

// Specialize if-then-else for NumericExecutionPass
template <>
void AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_ifthenelse(IfThenElseNode* node);

template <>
void AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_seqblock(UnaryNode* seqblock);

template <>
void AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_parblock(UnaryNode* parblock);

template <>
void AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_pop(PopNode* node);

template <>
void AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_push(PushNode* node);

template <>
void AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_case(CaseNode *node);

template <>
void AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_forall(ForallNode *node);

template <>
void AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_iterate(UnaryNode *node);

template <>
void AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_update(UpdateNode *node);

template <>
void AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_update_subrange(UpdateNode *node);

template <>
void AstWalker<libcasm_fe::NumericExecutionPass, value_t>::walk_update_dumps(UpdateNode *node);

class ExecutionWalker : public AstWalker<libcasm_fe::NumericExecutionPass, value_t> {
private:
    std::set<std::string> initialized;

    bool init_function(const std::string& name, std::set<std::string>& visited);

public:
    ExecutionWalker(libcasm_fe::NumericExecutionPass& v);
    void run();
};

#endif /* _LIB_CASMFE_NUMERICEXECUTIONPASS_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: t
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
