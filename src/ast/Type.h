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

#ifndef _LIB_CASMFE_TYPE_H_
#define _LIB_CASMFE_TYPE_H_

#include "Expression.h"

namespace libcasm_fe
{
    namespace Ast
    {
        class Type : public Node
        {
          public:
            using Ptr = std::shared_ptr< Type >;

            Type( Node::ID id, const IdentifierNode::Ptr& name );

            IdentifierNode::Ptr name( void ) const;

            void setType( const libcasm_ir::Type::Ptr& type );
            libcasm_ir::Type::Ptr type( void ) const;

          private:
            IdentifierNode::Ptr m_name;
            libcasm_ir::Type::Ptr m_type;
        };

        using Types = NodeList< Type >;

        class UnresolvedType : public Type
        {
          public:
            using Ptr = std::shared_ptr< UnresolvedType >;

            UnresolvedType( void );

            void accept( Visitor& visitor ) override final;
        };

        class BasicType : public Type
        {
          public:
            using Ptr = std::shared_ptr< BasicType >;

            BasicType( const IdentifierNode::Ptr& identifier );

            void accept( Visitor& visitor ) override final;
        };

        class ComposedType : public Type
        {
          public:
            using Ptr = std::shared_ptr< ComposedType >;

            ComposedType( const IdentifierNode::Ptr& identifier,
                const Types::Ptr& subTypes );

            Types::Ptr subTypes( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Types::Ptr m_subTypes;
        };

        class FixedSizedType : public Type
        {
          public:
            using Ptr = std::shared_ptr< FixedSizedType >;

            FixedSizedType( const IdentifierNode::Ptr& identifier,
                const Expression::Ptr& size );

            Expression::Ptr size( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Expression::Ptr m_size;
        };
    }
}

#endif // _LIB_CASMFE_TYPE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
