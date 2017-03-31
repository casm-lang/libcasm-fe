//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#ifndef _LIB_CASMFE_AST_TO_CASM_IR_PASS_H_
#define _LIB_CASMFE_AST_TO_CASM_IR_PASS_H_

#include "../analyze/TypeCheckPass.h"
#include "../casm-ir/src/analyze/ConsistencyCheckPass.h"

/**
   @brief    TODO

   TODO
*/

namespace libcasm_ir
{
    class Value;
    class Specification;
    class ExecutionSemanticsBlock;
}

namespace libcasm_fe
{
    class AstToCasmIRPass final : public libpass::Pass
    {
      public:
        static char id;

        void usage( libpass::PassUsage& pu ) override;

        bool run( libpass::PassResult& pr ) override;
    };

    //     std::shared_ptr< libcasm_ir::Specification > getSpecification(
    //         void ) const;

    //     LIB_CASMFE_VISITOR_INTERFACE( u1, u1 );

    //     libcasm_ir::Type::Ptr getType( Type* type );

    //     libcasm_ir::Value::Ptr constant(
    //         const value_t& value, const Type& type, libcasm_ir::Type& hint );
    //     value_t value_t_value( const libcasm_ir::Value::Ptr& value );

    //   private:
    //     template < typename C >
    //     typename C::Ptr lookupParent( AstNode* node );

    //     template < typename C >
    //     typename C::Ptr lookup( AstNode* node );

    //     std::unordered_map< AstNode*, std::shared_ptr< libcasm_ir::Value > >
    //         ast2casmir;
    //     std::unordered_map< AstNode*, AstNode* > ast2parent;

    //     std::vector< libcasm_ir::Value::Ptr > current_scope;

    //     std::shared_ptr< libcasm_ir::Specification > m_specification;
    //     std::shared_ptr< libcasm_ir::Agent > m_agent;

    //     std::shared_ptr< libcasm_ir::ExecutionSemanticsBlock >
    //     initially_scope;
    //     std::shared_ptr< libcasm_ir::ExecutionSemanticsBlock >
    //         initially_update_scope;

    //     u1 is_initially;
    // };
}

#endif // _LIB_CASMFE_AST_TO_CASM_IR_PASS_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
