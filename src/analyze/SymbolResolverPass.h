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

#ifndef _LIB_CASMFE_SYMBOL_RESOLVER_PASS_H_
#define _LIB_CASMFE_SYMBOL_RESOLVER_PASS_H_

#include "../analyze/AttributionPass.h"

#include "../Namespace.h"
#include "../ast/Specification.h"

namespace libcasm_fe
{
    /**
     * @brief Symbol resolver pass of AST identifiers
     */
    class SymbolResolverPass final : public libpass::Pass
    {
      public:
        static char id;

        void usage( libpass::PassUsage& pu ) override;

        bool run( libpass::PassResult& pr ) override;

        class Data : public AttributionPass::Data
        {
          public:
            using Ptr = std::shared_ptr< Data >;

            Data( const Ast::Specification::Ptr& specification,
                const Namespace::Ptr& symboltable )
            : AttributionPass::Data( specification )
            , m_symboltable( symboltable )
            {
            }

            Namespace::Ptr symboltable( void ) const
            {
                return m_symboltable;
            }

          private:
            Namespace::Ptr m_symboltable;
        };
    };
}

#endif // _LIB_CASMFE_SYMBOL_RESOLVER_PASS_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
