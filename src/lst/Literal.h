//
//  Copyright (C) 2014-2020 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
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

#ifndef _LIBCASM_FE_LST_LITERAL_H_
#define _LIBCASM_FE_LST_LITERAL_H_

#include <libcasm-fe/lst/Definition>
#include <libcasm-fe/lst/Expression>

#include <libcasm-ir/Constant>

namespace libcasm_fe
{
    namespace LST
    {
        class Literal : public Expression
        {
          public:
            using Ptr = std::shared_ptr< Literal >;

            explicit Literal(
                const Node::ID id,
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties );
        };

        using Literals = NodeList< Literal >;

        class ValueLiteral final : public Literal
        {
          public:
            using Ptr = std::shared_ptr< ValueLiteral >;

            explicit ValueLiteral(
                const libcasm_ir::Properties& properties, const libcasm_ir::Constant::Ptr& value );

            const libcasm_ir::Constant::Ptr& value( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const libcasm_ir::Constant::Ptr m_value;
        };

        class ReferenceLiteral final : public Literal
        {
          public:
            enum class ReferenceType
            {
                FUNCTION,
                DERIVED,
                RULE,
                UNKNOWN
            };

            using Ptr = std::shared_ptr< ReferenceLiteral >;

            explicit ReferenceLiteral(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const IdentifierPath::Ptr& identifier,
                const Definition::Ptr& reference );

            const IdentifierPath::Ptr& identifier( void ) const;

            const Definition::Ptr& reference( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const IdentifierPath::Ptr m_identifier;
            const Definition::Ptr m_reference;
        };

        class SetLiteral final : public Literal
        {
          public:
            using Ptr = std::shared_ptr< SetLiteral >;

            explicit SetLiteral(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Expressions::Ptr& expressions );

            const Expressions::Ptr& expressions( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expressions::Ptr m_expressions;
        };

        class ListLiteral final : public Literal
        {
          public:
            using Ptr = std::shared_ptr< ListLiteral >;

            explicit ListLiteral(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Expressions::Ptr& expressions );

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
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Expression::Ptr& left,
                const Expression::Ptr& right );

            const Expression::Ptr& left( void ) const;

            const Expression::Ptr& right( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expression::Ptr m_left;
            const Expression::Ptr m_right;
        };

        class TupleLiteral final : public Literal
        {
          public:
            using Ptr = std::shared_ptr< TupleLiteral >;

            TupleLiteral(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const Expressions::Ptr& expressions );

            const Expressions::Ptr& expressions( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Expressions::Ptr m_expressions;
        };

        class RecordLiteral final : public Literal
        {
          public:
            using Ptr = std::shared_ptr< RecordLiteral >;

            RecordLiteral(
                const libcasm_ir::Type::Ptr& type,
                const libcasm_ir::Properties& properties,
                const NamedExpressions::Ptr& namedExpressions );

            const NamedExpressions::Ptr& namedExpressions( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const NamedExpressions::Ptr m_namedExpressions;
        };
    }
}

#endif  // _LIBCASM_FE_LST_LITERAL_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
