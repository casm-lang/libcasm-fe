//
//  Copyright (C) 2014-2021 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Jakob Moosbrugger
//                Florian Hahn
//                Ioan Molnar
//                <https://github.com/casm-lang/libcasm-fe>
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

#ifndef _LIBCASM_FE_HELPER_H_
#define _LIBCASM_FE_HELPER_H_

#include <libcasm-fe/ast/Expression>
#include <libcasm-fe/ast/Node>
#include <libcasm-fe/ast/Rule>
#include <libcasm-fe/ast/Token>

namespace libcasm_fe
{
    namespace Ast
    {
        class FunctionDefinition;

        class Helper : public Node
        {
          public:
            Helper(
                const Node::ID id,
                const Token::Ptr& leftBraceToken,
                const Token::Ptr& rightBraceToken );

            const Token::Ptr& leftBraceToken( void ) const;

            const Token::Ptr& rightBraceToken( void ) const;

            void setDelimiterToken( const Token::Ptr& delimiterToken );
            const Token::Ptr& delimiterToken( void ) const;

          protected:
            void clone( Helper& duplicate ) const;

          private:
            const Token::Ptr m_leftBraceToken;
            const Token::Ptr m_rightBraceToken;
            Token::Ptr m_delimiterToken;
        };

        class Defined final : public Helper
        {
          public:
            using Ptr = std::shared_ptr< Defined >;

            Defined(
                const Token::Ptr& definedToken,
                const Token::Ptr& leftBraceToken,
                const Expression::Ptr& expression,
                const Token::Ptr& rightBraceToken );

            const Expression::Ptr& expression( void ) const;

            const Token::Ptr& definedToken( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Expression::Ptr m_expression;
            const Token::Ptr m_definedToken;
        };

        class Initializer final : public Helper
        {
          public:
            using Ptr = std::shared_ptr< Initializer >;

            Initializer(
                const Token::Ptr& leftBraceToken,
                const Expressions::Ptr& arguments,
                const Token::Ptr& rightBraceToken,
                const Token::Ptr& mapsToken,
                const Expression::Ptr& value );

            const Expressions::Ptr& arguments( void ) const;

            const Expression::Ptr& value( void ) const;

            const Token::Ptr& mapsToken( void ) const;

            const UpdateRule::Ptr& updateRule( void ) const;

            void setObjectType( const libcasm_ir::Type::Ptr& objectType );

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Expressions::Ptr m_arguments;
            const Expression::Ptr m_value;
            const Token::Ptr m_mapsToken;
            UpdateRule::Ptr m_updateRule;
        };

        using Initializers = NodeList< Initializer >;

        class Initially final : public Helper
        {
          public:
            using Ptr = std::shared_ptr< Initially >;

            Initially(
                const Token::Ptr& initiallyToken,
                const Token::Ptr& leftBraceToken,
                const Initializers::Ptr& initializers,
                const Token::Ptr& rightBraceToken );

            const Initializers::Ptr& initializers( void ) const;

            const Token::Ptr& initiallyToken( void ) const;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Initializers::Ptr m_initializers;
            const Token::Ptr m_initiallyToken;
        };
    }
}

#endif  // _LIBCASM_FE_HELPER_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
