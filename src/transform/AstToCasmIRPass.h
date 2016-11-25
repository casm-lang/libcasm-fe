//
//  Copyright (c) 2015-2016 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                https://github.com/casm-lang/libcasm-ir
//
//  This file is part of libcasm-ir.
//
//  libcasm-ir is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libcasm-ir is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libcasm-ir. If not, see <http://www.gnu.org/licenses/>.
//

#ifndef _LIB_CASMFE_ASTTOCASMIRPASS_H_
#define _LIB_CASMFE_ASTTOCASMIRPASS_H_

#include "libcasm-fe.all.h"
#include "libcasm-ir.all.h"
#include "libpass.h"

/**
   @brief    TODO

   TODO
*/

namespace libcasm_fe
{
    class AstToCasmIRPass : public libpass::Pass, public BaseVisitor< bool >
    {
      public:
        static char id;

        bool run( libpass::PassResult& pr ) override final;

      private:
        std::unordered_map< AstNode*, libcasm_ir::Value* > ast2casmir;
        std::unordered_map< AstNode*, AstNode* > ast2parent;

        std::vector< libcasm_ir::Value* > current_scope;

        libcasm_ir::Specification* specification;

      public:
        libcasm_ir::Specification* getSpecification( void ) const;

        void visit_init( InitNode* node );
        void visit_specification( SpecificationNode* node );
        void visit_body_elements( AstNode* node );
        void visit_function_def( FunctionDefNode* node,
            const std::vector< std::pair< bool, bool > >& inits );
        void visit_derived_function_atom_pre(
            FunctionAtom* node, std::vector< bool >& args );
        void visit_derived_def_pre( FunctionDefNode* node );
        void visit_derived_def( FunctionDefNode* node, bool expr );
        void visit_rule( RuleNode* node );
        void visit_rule_post( RuleNode* node );
        void visit_skip( AstNode* node );
        void visit_statements( AstListNode* node );
        void visit_parblock_pre( UnaryNode* node );
        void visit_seqblock_pre( UnaryNode* node );
        void visit_forall_pre( AstNode* node );
        void visit_forall_post( AstNode* node );
        void visit_iterate( AstNode* node );
        void visit_update( UpdateNode* node, bool func, bool expr );
        void visit_update_dumps( UpdateNode* node, bool func, bool expr );
        void visit_update_subrange( UpdateNode* node, bool func, bool expr );
        void visit_call_pre( CallNode* node );
        void visit_call_pre( CallNode* node, bool expr );
        void visit_call( CallNode* node, std::vector< bool >& args );
        void visit_call_post( CallNode* node );
        void visit_print( PrintNode* node, bool expr );
        void visit_diedie( DiedieNode* node, bool msg );
        void visit_impossible( AstNode* node );
        void visit_assert( UnaryNode* node, bool expr );
        void visit_assure( UnaryNode* node, bool expr );
        void visit_let( LetNode* node, bool var );
        void visit_let_post( LetNode* node );
        void visit_push( PushNode* node, bool expr, bool atom );
        void visit_pop( PopNode* node );
        void visit_ifthenelse( IfThenElseNode* node, bool cond );
        void visit_case_pre( CaseNode* node, bool val );
        void visit_case(
            CaseNode* node, bool val, const std::vector< bool >& case_labels );
        bool visit_expression( BinaryExpression* node, bool lhs, bool rhs );
        bool visit_expression_single( UnaryExpression* node, bool val );
        bool visit_function_atom(
            FunctionAtom* node, std::vector< bool >& args );
        bool visit_function_atom_subrange(
            FunctionAtom* node, bool args[], uint16_t argc );
        bool visit_derived_function_atom( FunctionAtom* node, bool expr );
        bool visit_zero_atom( ZeroAtom* node )
        {
            assert( !"internal error!" );
        };
        bool visit_int_atom( IntegerAtom* node );
        bool visit_bit_atom( IntegerAtom* node );
        bool visit_floating_atom( FloatingAtom* node );
        bool visit_rational_atom( RationalAtom* node );
        bool visit_undef_atom( UndefAtom* node );
        bool visit_self_atom( SelfAtom* node );
        bool visit_rule_atom( RuleAtom* node );
        bool visit_boolean_atom( BooleanAtom* node );
        bool visit_string_atom( StringAtom* node );
        bool visit_list_atom( ListAtom* node, std::vector< bool >& args );
        bool visit_number_range_atom(
            NumberRangeAtom* node, bool start, bool end );
        bool visit_builtin_atom( BuiltinAtom* node, std::vector< bool >& args );

      private:
        template < class C >
        C* lookupParent( AstNode* node );

        template < class C >
        C* lookup( AstNode* node );
    };
}

#endif /* _LIB_CASMFE_PASSASTTOCASMIR_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
