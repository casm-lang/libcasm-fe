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

#ifndef _LIB_CASMFE_SPECIFICATION_H_
#define _LIB_CASMFE_SPECIFICATION_H_

#include <memory>

#include "ast/Definition.h"

namespace libcasm_fe
{
    class Specification
    {
      public:
        using Ptr = std::shared_ptr< Specification >;

        explicit Specification( void );

        void setName( const std::string& name );
        const std::string& name( void ) const;

        void setDefinitions( const Ast::Definitions::Ptr& definitions );
        const Ast::Definitions::Ptr& definitions( void ) const;

      private:
        std::string m_name;
        Ast::Definitions::Ptr m_definitions;
    };
}

#endif // _LIB_CASMFE_SPECIFICATION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
