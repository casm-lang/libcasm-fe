//
//  Copyright (C) 2014-2024 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//  <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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
//  Additional permission under GNU GPL version 3 section 7
//
//  libcasm-fe is distributed under the terms of the GNU General Public License
//  with the following clarification and special exception: Linking libcasm-fe
//  statically or dynamically with other modules is making a combined work
//  based on libcasm-fe. Thus, the terms and conditions of the GNU General
//  Public License cover the whole combination. As a special exception,
//  the copyright holders of libcasm-fe give you permission to link libcasm-fe
//  with independent modules to produce an executable, regardless of the
//  license terms of these independent modules, and to copy and distribute
//  the resulting executable under terms of your choice, provided that you
//  also meet, for each linked independent module, the terms and conditions
//  of the license of that module. An independent module is a module which
//  is not derived from or based on libcasm-fe. If you modify libcasm-fe, you
//  may extend this exception to your version of the library, but you are
//  not obliged to do so. If you do not wish to do so, delete this exception
//  statement from your version.
//

#ifndef _LIBCASM_FE_CST_DECLARATION_H_
#define _LIBCASM_FE_CST_DECLARATION_H_

#include <libcasm-fe/cst/Definition>
#include <libcasm-fe/cst/Token>
#include <libcasm-fe/cst/Type>

namespace libcasm_fe
{
    namespace CST
    {
        class Declaration final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< Declaration >;

            enum class Kind
            {
                DERIVED,
                RULE
            };

            Declaration(
                const Token::Ptr& kindToken,
                const Identifier::Ptr& identifier,
                const Token::Ptr& colonToken,
                const Types::Ptr& argumentTypes,
                const Token::Ptr& mapsToken,
                const Type::Ptr& returnType );

            const Types::Ptr& argumentTypes( void ) const;

            void setArgumentTypes( const Types::Ptr& argumentTypes );

            const Type::Ptr& returnType( void ) const;

            void setReturnType( const Type::Ptr& returnType );

            const Token::Ptr& kindToken( void ) const;

            const Token::Ptr& colonToken( void ) const;

            const Token::Ptr& mapsToken( void ) const;

            Kind kind( void ) const;

            std::string kindName( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            Types::Ptr m_argumentTypes;
            Type::Ptr m_returnType;
            const Token::Ptr m_kindToken;
            const Token::Ptr m_colonToken;
            const Token::Ptr m_mapsToken;
            const Kind m_kind;
        };

        using Declarations = NodeList< Declaration >;
    }
}

#endif  // _LIBCASM_FE_CST_DECLARATION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
