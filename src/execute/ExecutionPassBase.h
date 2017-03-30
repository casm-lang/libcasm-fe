//
//  Copyright (c) 2014-2017 CASM Organization
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

#ifndef _LIB_CASMFE_EXECUTION_PASS_BASE_H_
#define _LIB_CASMFE_EXECUTION_PASS_BASE_H_

#include <set>

#include "../Ast.h"
#include "../Visitor.h"
#include "../allocator/BlockAllocator.h"
#include "UpdateSet.h"

#include "ChainedHashMap.h"
#include "ProbingHashMap.h"
#include "RobinHoodHashMap.h"

/**
   @brief    TODO

   TODO
*/

namespace libcasm_fe
{
    using FunctionState = ProbingHashMap< std::vector< value_t >, value_t >;

    class ExecutionPassBase : public Visitor< value_t >
    {
      public:
        static char id;

        bool hasEmptyUpdateSet() const;
        Update* addUpdate( Function* function,
            const std::vector< value_t >& arguments, const value_t& value,
            const yy::location& location );
        void applyUpdates();

        void fork( const UpdateSet::Type updateSetType );
        void merge();

        value_t functionValue(
            Function* function, const std::vector< value_t >& arguments );

        void visit_body_elements_pre( AstListNode* node ) override;
        void visit_body_elements_post( AstListNode* node ) override;

        void visit_function_def_pre(
            FunctionDefNode* node, const value_t& defaultValue ) override;
        void visit_function_def_post( FunctionDefNode* node ) override;

        void visit_seqblock_pre( UnaryNode* seqblock ) override;
        void visit_seqblock_post( UnaryNode* seqblock ) override;

        void visit_parblock_pre( UnaryNode* parblock ) override;
        void visit_parblock_post( UnaryNode* parblock ) override;

        void visit_forall_pre( ForallNode* node ) override;
        void visit_forall_post( ForallNode* node ) override;
        void visit_forall_iteration_pre(
            ForallNode* node, const value_t& value ) override;
        void visit_forall_iteration_post( ForallNode* node ) override;

        void visit_update( UpdateNode* node,
            std::vector< value_t >& arguments,
            const value_t& value ) override;

        void visit_call_pre( CallNode* call ) override;
        void visit_call_pre( CallNode* call, const value_t& value ) override;
        void visit_call(
            CallNode* call, std::vector< value_t >& arguments ) override;
        void visit_call_post( CallNode* call ) override;

        void visit_assert( UnaryNode* node, const value_t& value ) override;
        void visit_assure( UnaryNode* node, const value_t& value ) override;
        void visit_diedie( DiedieNode* node, const value_t& msg ) override;
        void visit_impossible( AstNode* node ) override;

        void visit_let( LetNode* node, const value_t& value ) override;
        void visit_let_post( LetNode* node ) override;

        value_t visit_zero_atom( ZeroAtom* atom ) override;
        value_t visit_undef_atom( UndefAtom* atom ) override;
        value_t visit_self_atom( SelfAtom* atom ) override;
        value_t visit_int_atom( IntegerAtom* atom ) override;
        value_t visit_bit_atom( IntegerAtom* atom ) override;
        value_t visit_floating_atom( FloatingAtom* atom ) override;
        value_t visit_rational_atom( RationalAtom* atom ) override;
        value_t visit_rule_atom( RuleAtom* atom ) override;
        value_t visit_boolean_atom( BooleanAtom* atom ) override;
        value_t visit_string_atom( StringAtom* atom ) override;
        value_t visit_number_range_atom( NumberRangeAtom* atom,
            const value_t& left, const value_t& right ) override;

        value_t visit_function_atom(
            FunctionAtom* atom, std::vector< value_t >& arguments ) override;

        value_t visit_builtin_atom(
            BuiltinAtom* atom, std::vector< value_t >& arguments ) override;

        void visit_derived_function_atom_pre(
            FunctionAtom* atom, std::vector< value_t >& arguments ) override;
        value_t visit_derived_function_atom(
            FunctionAtom* atom, const value_t& value ) override;

        void visit_root( Ast* ) override{};
        void visit_specification( SpecificationNode* ) override{};
        void visit_init( InitNode* ) override{};
        void visit_derived_def_pre( DerivedDefNode* ) override{};
        void visit_derived_def( DerivedDefNode*, const value_t& ) override{};
        void visit_rule( RuleNode* ) override{};
        void visit_rule_post( RuleNode* ) override{};
        void visit_statements( AstListNode* ) override{};
        void visit_statement( AstNode* ) override{};
        void visit_ifthenelse( IfThenElseNode*, const value_t& ) override{};
        void visit_skip( AstNode* ) override{};
        void visit_iterate( UnaryNode* ) override{};
        void visit_case_pre( CaseNode*, const value_t& ) override{};
        void visit_case( CaseNode*, const value_t&,
            const std::vector< value_t >& ) override{};

      protected:
        /**
         * @throws std::domain_error if any argument is out of range
         */
        void validateArguments( const std::vector< Type* >& argumentTypes,
            const std::vector< value_t >& argumentValues ) const;

        /**
         * @throws std::domain_error if value is out of range
         */
        void validateValue( const Type* type, const value_t& value ) const;

        virtual value_t defaultFunctionValue(
            Function* function, const std::vector< value_t >& arguments );

        bool filter_enabled( const std::string& filter );

      protected:
        std::vector< value_t > main_bindings;
        std::vector< std::vector< value_t >* > rule_bindings;

        UpdateSetManager updateSetManager;

        std::vector< FunctionState > function_states;
        std::vector< const Function* > function_symbols;
        std::vector< value_t > functionDefaultValues;

        std::vector< List* > temp_lists;

      private:
        std::map< const std::string, bool > debuginfo_filters;

        BlockAllocator< 4096 > stack;
    };

    namespace builtins
    {
        const value_t cons( std::vector< List* >& tempLists, const value_t& val,
            const value_t& list );
        const value_t tail(
            std::vector< List* >& tempLists, const value_t& arg_list );
        const value_t peek( const value_t& arg_list );
    }
}

#endif // _LIB_CASMFE_EXECUTION_PASS_BASE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
