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

#ifndef _LIB_CASMFE_REFERENCE_CONSTANT_H_
#define _LIB_CASMFE_REFERENCE_CONSTANT_H_

#include "../ast/Expression.h"
#include "../ast/Node.h"

#include "../casm-ir/src/Constant.h"

namespace libcasm_fe
{
    class EmptyValue : public libcasm_ir::Value
    {
      public:
        EmptyValue( void )
        : libcasm_ir::Value(
              "", libstdhl::get< libcasm_ir::VoidType >(), Value::ID::VALUE )
        {
        }
    };

    class ReferenceConstant final
        : public libcasm_ir::ReferenceConstant< EmptyValue >
    {
      public:
        ReferenceConstant( const Ast::ReferenceAtom::Ptr& atom )
        : libcasm_ir::ReferenceConstant< EmptyValue >( "",
              libstdhl::get< libcasm_ir::VoidType >(), nullptr, false, false,
              Value::ID::VALUE )
        {
        }

        Ast::ReferenceAtom::Ptr atom( void ) const
        {
            return m_atom;
        }

      private:
        Ast::ReferenceAtom::Ptr m_atom;
    };
}

#endif // _LIB_CASMFE_REFERENCE_CONSTANT_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
