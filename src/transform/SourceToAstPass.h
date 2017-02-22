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

#ifndef _LIB_CASMFE_SOURCETOASTPASS_H_
#define _LIB_CASMFE_SOURCETOASTPASS_H_

#include "libpass.h"

/**
   @brief    TODO

   TODO
*/

namespace libcasm_fe
{
    class Ast;

    class SourceToAstPass final : public libpass::Pass
    {
      public:
        static char id;

        bool run( libpass::PassResult& pr ) override;

        class Data : public libpass::PassData
        {
          public:
            using Ptr = std::shared_ptr< Data >;

            Data( Ast* root )
            : m_root( root )
            {
            }

            Ast* root( void ) const
            {
                return m_root;
            }

          private:
            Ast* m_root;
        };
    };
}

#endif // _LIB_CASMFE_SOURCETOASTPASS_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
