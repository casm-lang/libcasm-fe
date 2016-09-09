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

#ifndef _LIB_CASMFE_EXECUTIONPASSBASE_H_
#define _LIB_CASMFE_EXECUTIONPASSBASE_H_

#include <set>

#include "UpdateSet.h"
#include "../allocator/BlockAllocator.h"
#include "../Visitor.h"
#include "../Ast.h"

#define TEMP_STACK_SIZE 32768

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
    class ExecutionPassBase : public BaseVisitor<value_t>
    {
    public:
        static char id;

        bool hasEmptyUpdateSet() const;
        Update* addUpdate(Function *sym, const value_t& val, uint32_t num_arguments,
                          value_t arguments[], const yy::location& location);

        void fork(const UpdateSet::Type updateSetType);
        void merge();
        void applyUpdates();

        virtual const value_t get_function_value(Function *sym, const std::vector<value_t>& arguments);

        bool filter_enabled(const std::string& filter);

        void visit_assert(UnaryNode* assert, const value_t& val);
        void visit_update(UpdateNode *update, const value_t& expr_v);

        void visit_update_dumps(UpdateNode *update, const value_t& expr_v);
        void visit_call_pre(CallNode *call);
        void visit_call_pre(CallNode *call, const value_t& expr);
        void visit_call(CallNode *call, std::vector<value_t> &arguments);
        void visit_call_post(CallNode *call);
        void visit_diedie(DiedieNode *node, const value_t& msg);
        void visit_impossible(AstNode *node);

        void visit_let(LetNode *node, const value_t& v);
        void visit_let_post(LetNode *node);

        const value_t visit_int_atom(IntegerAtom *atom) { return value_t(atom->val_); }
        const value_t visit_bit_atom(IntegerAtom *atom) { return value_t(atom->val_); }
        const value_t visit_floating_atom(FloatingAtom *atom) { return value_t(atom->val_); }
        const value_t visit_rational_atom(RationalAtom *atom) { return value_t(&atom->val_); }
        const value_t visit_undef_atom(UndefAtom *atom) { UNUSED(atom); return value_t(); }
        const value_t visit_function_atom(FunctionAtom *atom, std::vector<value_t> &arguments);

        const value_t visit_builtin_atom(BuiltinAtom *atom, std::vector<value_t> &arguments);
        void visit_derived_function_atom_pre(FunctionAtom *atom, std::vector<value_t> &arguments);
        const value_t visit_derived_function_atom(FunctionAtom *atom, const value_t& expr);
        const value_t visit_self_atom(SelfAtom *atom) { UNUSED(atom); return value_t(); }
        const value_t visit_rule_atom(RuleAtom *atom) { return value_t(atom->rule); }
        const value_t visit_boolean_atom(BooleanAtom *atom) { return value_t(atom->value); }
        const value_t visit_string_atom(StringAtom *atom) { return value_t(&atom->string); }
        const value_t visit_number_range_atom(NumberRangeAtom *atom,
                                              const value_t& left,
                                              const value_t& right);

    private:
        /**
         * @ throws std::domain_error if any argument is out of range                    *
         */
        void validateArguments(const std::vector<Type*>& argumentTypes,
                               const std::vector<value_t>& argumentValues) const;

    protected:
        std::vector<value_t> main_bindings;
        UpdateSetManager updateSetManager;

        BlockAllocator<TEMP_STACK_SIZE> stack;
        std::map<const std::string, bool> debuginfo_filters;

        std::set<std::string> initialized;

    public:
        std::vector<value_t> value_list;
        std::vector<std::vector<value_t> *> rule_bindings;

        value_t arguments[10];
        uint32_t num_arguments;

        std::vector<std::unordered_map<ArgumentsKey, value_t>> function_states;
        std::vector<const Function*> function_symbols;

        std::vector<List*> temp_lists;
    };
}

namespace builtins
{
    const value_t cons(std::vector<List*>& tempLists, const value_t& val, const value_t& list);
    const value_t tail(std::vector<List*>& tempLists, const value_t& arg_list);
    const value_t peek(const value_t& arg_list);
}

#endif /* _LIB_CASMFE_EXECUTIONPASSBASE_H_ */


//  
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
