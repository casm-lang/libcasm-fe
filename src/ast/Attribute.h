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

#ifndef _LIB_CASMFE_ATTRIBUTE_H_
#define _LIB_CASMFE_ATTRIBUTE_H_

#include "Expression.h"
#include "Node.h"

namespace libcasm_fe
{
    namespace Ast
    {
        class Attribute : public Node
        {
          public:
            using Ptr = std::shared_ptr< Attribute >;

            Attribute( Node::ID id, const Identifier::Ptr& identifier );

            Identifier::Ptr identifier( void ) const;

          private:
            Identifier::Ptr m_identifier;
        };

        using Attributes = NodeList< Attribute >;

        class BasicAttribute : public Attribute
        {
          public:
            using Ptr = std::shared_ptr< BasicAttribute >;

            BasicAttribute( const Identifier::Ptr& identifier );

            void accept( Visitor& visitor ) override final;
        };

        class ExpressionAttribute : public Attribute
        {
          public:
            using Ptr = std::shared_ptr< ExpressionAttribute >;

            ExpressionAttribute( const Identifier::Ptr& identifier,
                const Expression::Ptr& expression );

            Expression::Ptr expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Expression::Ptr m_expression;
        };
    }
}

#endif // _LIB_CASMFE_ATTRIBUTE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
