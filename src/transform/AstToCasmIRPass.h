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
    class AstToCasmIRPass : public libpass::Pass, public Visitor< bool, bool >
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

        LIB_CASMFE_VISITOR_INTERFACE( bool, bool );

        // void visit_init( InitNode* node ) override;
        // void visit_specification( SpecificationNode* node ) override;
        // void visit_body_elements( AstListNode* node ) override;
        // void visit_function_def( FunctionDefNode* node,
        //     const std::vector< std::pair< bool, bool > >& inits ) override;
        // void visit_derived_function_atom_pre(
        //     FunctionAtom* node, std::vector< bool >& args ) override;
        // void visit_derived_def_pre( FunctionDefNode* node ) override;
        // void visit_derived_def( FunctionDefNode* node, bool expr ) override;
        // void visit_rule( RuleNode* node ) override;
        // void visit_rule_post( RuleNode* node ) override;
        // void visit_skip( AstNode* node ) override;
        // void visit_statements( AstListNode* node ) override;
        // void visit_parblock_pre( UnaryNode* node ) override;
        // void visit_seqblock_pre( UnaryNode* node ) override;
        // void visit_forall_pre( ForallNode* node ) override;
        // void visit_forall_post( ForallNode* node ) override;
        // void visit_iterate( UnaryNode* node ) override;
        // void visit_update( UpdateNode* node,
        //     const std::vector< bool >& args,
        //     bool expr ) override;
        // void visit_call_pre( CallNode* node ) override;
        // void visit_call_pre( CallNode* node, bool expr ) override;
        // void visit_call( CallNode* node, std::vector< bool >& args )
        // override;
        // void visit_call_post( CallNode* node ) override;
        // void visit_print( PrintNode* node, bool expr ) override;
        // void visit_diedie( DiedieNode* node, bool msg ) override;
        // void visit_impossible( AstNode* node ) override;
        // void visit_assert( UnaryNode* node, bool expr ) override;
        // void visit_assure( UnaryNode* node, bool expr ) override;
        // void visit_let( LetNode* node, bool var ) override;
        // void visit_let_post( LetNode* node ) override;
        // void visit_push( PushNode* node, bool expr, bool atom ) override;
        // void visit_pop( PopNode* node, bool atom ) override;
        // void visit_ifthenelse( IfThenElseNode* node, bool cond ) override;
        // void visit_case_pre( CaseNode* node, bool val ) override;
        // void visit_case( CaseNode* node,
        //     bool val,
        //     const std::vector< bool >& case_labels ) override;
        // bool visit_expression(
        //     BinaryExpression* node, bool lhs, bool rhs ) override;
        // bool visit_expression_single(
        //     UnaryExpression* node, bool val ) override;
        // bool visit_function_atom(
        //     FunctionAtom* node, std::vector< bool >& args ) override;
        // bool visit_derived_function_atom(
        //     FunctionAtom* node, bool expr ) override;
        // bool visit_zero_atom( ZeroAtom* node ) override
        // {
        //     assert( !"internal error!" );
        //     return false;
        // };
        // bool visit_int_atom( IntegerAtom* node ) override;
        // bool visit_bit_atom( IntegerAtom* node ) override;
        // bool visit_floating_atom( FloatingAtom* node ) override;
        // bool visit_rational_atom( RationalAtom* node ) override;
        // bool visit_undef_atom( UndefAtom* node ) override;
        // bool visit_self_atom( SelfAtom* node ) override;
        // bool visit_rule_atom( RuleAtom* node ) override;
        // bool visit_boolean_atom( BooleanAtom* node ) override;
        // bool visit_string_atom( StringAtom* node ) override;
        // bool visit_list_atom(
        //     ListAtom* node, const std::vector< bool >& args ) override;
        // bool visit_number_range_atom(
        //     NumberRangeAtom* node, bool start, bool end ) override;
        // bool visit_builtin_atom(
        //     BuiltinAtom* node, std::vector< bool >& args ) override;

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
