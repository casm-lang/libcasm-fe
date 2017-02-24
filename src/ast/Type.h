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

          private:
            IdentifierNode::Ptr m_name;
        };

        using Types = NodeList< Type >;

        class BasicType : public Type
        {
          public:
            using Ptr = std::shared_ptr< BasicType >;

            BasicType( const IdentifierNode::Ptr& identifier );
        };

        class ComposedType : public Type
        {
          public:
            using Ptr = std::shared_ptr< ComposedType >;

            ComposedType( const IdentifierNode::Ptr& identifier,
                const Types::Ptr& subTypes );

            Types::Ptr subTypes( void ) const;

          private:
            Types::Ptr m_subTypes;
        };

        class StaticallySizedType : public Type
        {
          public:
            using Ptr = std::shared_ptr< StaticallySizedType >;

            StaticallySizedType( const IdentifierNode::Ptr& identifier,
                const Expression::Ptr& size );

            Expression::Ptr size( void ) const;

          private:
            Expression::Ptr m_size;
        };

        class RangedType : public Type
        {
          public:
            using Ptr = std::shared_ptr< RangedType >;

            RangedType( const IdentifierNode::Ptr& identifier,
                const Expression::Ptr& lowerBound,
                const Expression::Ptr& upperBound );

            Expression::Ptr lowerBound( void ) const;

            Expression::Ptr upperBound( void ) const;

          private:
            Expression::Ptr m_lowerBound;

            Expression::Ptr m_upperBound;
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
