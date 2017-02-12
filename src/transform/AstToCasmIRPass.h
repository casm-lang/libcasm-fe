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

#include "libpass.h"

#include "../Visitor.h"

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
        libcasm_ir::ExecutionSemanticsBlock* initially_scope;
        libcasm_ir::ExecutionSemanticsBlock* initially_update_scope;
        u1 is_initially;

      public:
        libcasm_ir::Specification* getSpecification( void ) const;

        LIB_CASMFE_VISITOR_INTERFACE( bool, bool );

        libcasm_ir::Type* getType( Type* type );
        libcasm_ir::Value* constant(
            const value_t& value, libcasm_ir::Type& hint );
        value_t value_t_value( const libcasm_ir::Value& value );

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
