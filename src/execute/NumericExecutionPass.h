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

#ifndef _LIB_CASMFE_NUMERIC_EXECUTION_PASS_H_
#define _LIB_CASMFE_NUMERIC_EXECUTION_PASS_H_

#include "../analyze/TypeCheckPass.h"
//#include "../transform/AstToCasmIRPass.h"

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

        ~NumericExecutionPass() override;

        void usage( libpass::PassUsage& pu ) override;

        bool run( libpass::PassResult& pr ) override;

        void visit_print( PrintNode* node, const value_t& argument ) override;

        void visit_push(
            PushNode* node, const value_t& expr, const value_t& atom ) override;
        void visit_pop( PopNode* node, const value_t& val ) override;

        value_t visit_expression( BinaryExpression* expr,
            const value_t& left_val, const value_t& right_val ) override;
        value_t visit_expression_single(
            UnaryExpression* expr, const value_t& val ) override;

        value_t visit_list_atom(
            ListAtom* atom, const std::vector< value_t >& vals ) override;

        void setDumpUpdates( u1 enabled )
        {
            m_dump_updates = enabled;
        }

      private:
        void dumpUpdates() const;

        AstWalker< libcasm_fe::NumericExecutionPass, value_t >* walker;

        bool m_dump_updates;
    };

    using NumericExecutionWalker
        = AstWalker< libcasm_fe::NumericExecutionPass, value_t >;

    template <>
    void NumericExecutionWalker::walk_ifthenelse( IfThenElseNode* node );

    template <>
    void NumericExecutionWalker::walk_case( CaseNode* node );

    template <>
    void NumericExecutionWalker::walk_iterate( UnaryNode* node );
}

#endif // _LIB_CASMFE_NUMERIC_EXECUTION_PASS_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
