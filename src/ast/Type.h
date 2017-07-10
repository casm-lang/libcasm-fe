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
        class Type : public TypedNode
        {
          public:
            using Ptr = std::shared_ptr< Type >;

            Type( Node::ID id, const IdentifierPath::Ptr& name );

            IdentifierPath::Ptr name( void ) const;

          private:
            const IdentifierPath::Ptr m_name;
        };

        using Types = NodeList< Type >;

        class UnresolvedType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< UnresolvedType >;

            explicit UnresolvedType( void );

            void accept( Visitor& visitor ) override final;
        };

        class BasicType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< BasicType >;

            explicit BasicType( const IdentifierPath::Ptr& identifier );

            void accept( Visitor& visitor ) override final;
        };

        class ComposedType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< ComposedType >;

            ComposedType( const IdentifierPath::Ptr& identifier,
                const Types::Ptr& subTypes );

            Types::Ptr subTypes( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Types::Ptr m_subTypes;
        };

        class FixedSizedType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< FixedSizedType >;

            FixedSizedType( const IdentifierPath::Ptr& identifier,
                const Expression::Ptr& size );

            Expression::Ptr size( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_size;
        };

        class RelationType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< RelationType >;

            RelationType( const IdentifierPath::Ptr& identifier,
                const Types::Ptr& argumentTypes,
                const Type::Ptr& returnType );

            Types::Ptr argumentTypes( void ) const;
            Type::Ptr returnType( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Types::Ptr m_argumentTypes;
            const Type::Ptr m_returnType;
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
