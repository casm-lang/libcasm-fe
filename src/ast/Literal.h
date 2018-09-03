//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#ifndef _LIBCASM_FE_LITERAL_H_
#define _LIBCASM_FE_LITERAL_H_

#include <libcasm-fe/ast/Expression>
#include <libcasm-fe/ast/Token>

#include <libcasm-ir/Constant>

namespace libcasm_fe
{
    namespace Ast
    {
        class Literal : public Expression
        {
          public:
            using Ptr = std::shared_ptr< Literal >;

            explicit Literal( Node::ID id );

            void setLeftBracket( const Token::Ptr& leftBracket );
            const Token::Ptr& leftBracket( void ) const;

            void setRightBracket( const Token::Ptr& rightBracket );
            const Token::Ptr& rightBracket( void ) const;

          private:
            Token::Ptr m_leftBracket;
            Token::Ptr m_rightBracket;
        };

        using Literals = NodeList< Literal >;

        class UndefLiteral final : public Literal
        {
          public:
            using Ptr = std::shared_ptr< UndefLiteral >;

            explicit UndefLiteral( void );

            void accept( Visitor& visitor ) override final;
        };

        class ValueLiteral final : public Literal
        {
          public:
            using Ptr = std::shared_ptr< ValueLiteral >;

            explicit ValueLiteral( const libcasm_ir::Constant::Ptr& value );

            const libcasm_ir::Constant::Ptr& value( void ) const;

            void setValue( const libcasm_ir::Constant::Ptr& value );

            void accept( Visitor& visitor ) override final;

          private:
            libcasm_ir::Constant::Ptr m_value;
        };

        class ReferenceLiteral final : public Literal
        {
          public:
            enum class ReferenceType
            {
                FUNCTION,
                DERIVED,
                BUILTIN,
                RULE,
                UNKNOWN
            };

            using Ptr = std::shared_ptr< ReferenceLiteral >;

            explicit ReferenceLiteral( const Token::Ptr& at, const IdentifierPath::Ptr& identifier );

            const IdentifierPath::Ptr& identifier( void ) const;

            const Token::Ptr& at( void ) const;

            void setReferenceType( ReferenceType referenceType );
            ReferenceType referenceType( void ) const;

            void setReference( const TypedNode::Ptr& reference );
            const TypedNode::Ptr& reference( void ) const;

            void setBuiltinId( libcasm_ir::Value::ID builtinId );
            libcasm_ir::Value::ID builtinId( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const IdentifierPath::Ptr m_identifier;
            const Token::Ptr m_at;
            ReferenceType m_referenceType;
            TypedNode::Ptr m_reference;
            libcasm_ir::Value::ID m_builtinId;
        };

        class ListLiteral final : public Literal
        {
          public:
            using Ptr = std::shared_ptr< ListLiteral >;

            explicit ListLiteral( const Expressions::Ptr& expressions );

            const Expressions::Ptr& expressions( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expressions::Ptr m_expressions;
        };

        class RangeLiteral final : public Literal
        {
          public:
            using Ptr = std::shared_ptr< RangeLiteral >;

            RangeLiteral(
                const Expression::Ptr& left,
                const Token::Ptr& dotdot,
                const Expression::Ptr& right );

            const Expression::Ptr& left( void ) const;
            const Expression::Ptr& right( void ) const;
            const Token::Ptr& dotdot( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_left;
            const Expression::Ptr m_right;
            const Token::Ptr m_dotdot;
        };

        class TupleLiteral final : public Literal
        {
          public:
            using Ptr = std::shared_ptr< TupleLiteral >;

            TupleLiteral( const Expressions::Ptr& expressions );

            const Expressions::Ptr& expressions( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expressions::Ptr m_expressions;
        };

        class RecordLiteral final : public Literal
        {
          public:
            using Ptr = std::shared_ptr< RecordLiteral >;

            RecordLiteral( const NamedExpressions::Ptr& namedExpressions );

            const NamedExpressions::Ptr& namedExpressions( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const NamedExpressions::Ptr m_namedExpressions;
        };
    }
}

#endif  // _LIBCASM_FE_LITERAL_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
