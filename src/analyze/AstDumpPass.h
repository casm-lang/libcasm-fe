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

#ifndef _LIB_CASMFE_ASTDUMPPASS_H_
#define _LIB_CASMFE_ASTDUMPPASS_H_

#include "libpass.h"

#include "../Visitor.h"

/**
   @brief    TODO

   TODO
*/

namespace libcasm_fe
{
    class AstDumpPass : public libpass::Pass, public Visitor< bool, bool >
    {
      private:
        std::stringstream dump_stream_;

        void dump_node( uint64_t key, const std::string& name );
        void dump_node( AstNode* n, const std::string& name );
        void dump_link( uint64_t from, uint64_t to );
        void dump_link( AstNode* from, AstNode* to );

      public:
        static char id;

        bool run( libpass::PassResult& pr ) override final;

        std::string get_dump();

        LIB_CASMFE_VISITOR_INTERFACE( bool, bool );
    };
}

#endif /* _LIB_CASMFE_ASTDUMPPASS_H_ */

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
