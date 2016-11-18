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

#ifndef _LIB_CASMFE_NUMERICEXECUTIONPASS_H_
#define _LIB_CASMFE_NUMERICEXECUTIONPASS_H_

#include "libcasm-fe.all.h"
#include "libpass.h"

#include "ExecutionPassBase.h"

/**
   @brief    TODO

   TODO
*/

namespace libcasm_fe
{
    class NumericExecutionPass final : public ExecutionPassBase,
                                       public libpass::Pass
    {
      public:
        static char id;

        bool run( libpass::PassResult& pr ) override;

        void visit_assure( UnaryNode* assure, const value_t& val );

        void visit_print( PrintNode* node, const value_t& argument );

        void visit_push(
            PushNode* node, const value_t& expr, const value_t& atom );
        void visit_pop( PopNode* node, const value_t& val );

        const value_t visit_expression( BinaryExpression* expr,
            const value_t& left_val, const value_t& right_val );
        const value_t visit_expression_single(
            UnaryExpression* expr, const value_t& val );

        const value_t visit_list_atom(
            ListAtom* atom, const std::vector< value_t >& vals );

      private:
        bool init_function(
            const std::string& name, std::set< std::string >& visited );

        void dumpUpdates() const;

      private:
        AstWalker< libcasm_fe::NumericExecutionPass, value_t >* walker;
    };
}

using NumericExecutionWalker
    = AstWalker< libcasm_fe::NumericExecutionPass, value_t >;

template <>
value_t NumericExecutionWalker::walk_list_atom( ListAtom* atom );

template <>
void NumericExecutionWalker::walk_ifthenelse( IfThenElseNode* node );

template <>
void NumericExecutionWalker::walk_seqblock( UnaryNode* seqblock );

template <>
void NumericExecutionWalker::walk_parblock( UnaryNode* parblock );

template <>
void NumericExecutionWalker::walk_pop( PopNode* node );

template <>
void NumericExecutionWalker::walk_push( PushNode* node );

template <>
void NumericExecutionWalker::walk_case( CaseNode* node );

template <>
void NumericExecutionWalker::walk_forall( ForallNode* node );

template <>
void NumericExecutionWalker::walk_iterate( UnaryNode* node );

template <>
void NumericExecutionWalker::walk_update( UpdateNode* node );

template <>
void NumericExecutionWalker::walk_update_dumps( UpdateNode* node );

#endif /* _LIB_CASMFE_NUMERICEXECUTIONPASS_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
