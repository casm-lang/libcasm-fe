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

#ifndef _LIBCASM_FE_AST_TYPE_H_
#define _LIBCASM_FE_AST_TYPE_H_

#include <libcasm-fe/ast/Expression>

namespace libcasm_fe
{
    namespace AST
    {
        class TypeDefinition;
        class VariableDefinition;
        using VariableDefinitions = NodeList< VariableDefinition >;

        class Type : public TypedNode
        {
          public:
            using Ptr = std::shared_ptr< Type >;

            Type( const Node::ID id, const IdentifierPath::Ptr& name );

            const IdentifierPath::Ptr& name( void ) const;

            void setTypeDefinition( const std::shared_ptr< TypeDefinition >& typeDefinition );

            const std::shared_ptr< TypeDefinition >& typeDefinition( void ) const;

            virtual std::string signature( void ) const = 0;

            IdentifierPath::Ptr signaturePath( void ) const;

          protected:
            void clone( Type& duplicate ) const;

          private:
            const IdentifierPath::Ptr m_name;
            std::shared_ptr< TypeDefinition > m_typeDefinition;
        };

        using Types = NodeList< Type >;

        class UnresolvedType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< UnresolvedType >;

            explicit UnresolvedType( void );

            std::string signature( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;
        };

        class BasicType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< BasicType >;

            explicit BasicType( const IdentifierPath::Ptr& identifier );

            std::string signature( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;
        };

        class TupleType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< TupleType >;

            TupleType( const Types::Ptr& subTypes );

            const Types::Ptr& subTypes( void ) const;

            std::string signature( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Types::Ptr m_subTypes;
        };

        class RecordType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< RecordType >;

            RecordType( const std::shared_ptr< VariableDefinitions >& namedSubTypes );

            const std::shared_ptr< VariableDefinitions >& namedSubTypes( void ) const;

            std::string signature( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const std::shared_ptr< VariableDefinitions > m_namedSubTypes;
        };

        class TemplateType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< TemplateType >;

            TemplateType( const IdentifierPath::Ptr& identifier, const Types::Ptr& subTypes );

            const Types::Ptr& subTypes( void ) const;

            void setSubTypes( const Types::Ptr& subTypes );

            u1 varadic( void ) const;

            std::string signature( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            Types::Ptr m_subTypes;
        };

        class RelationType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< RelationType >;

            RelationType(
                const IdentifierPath::Ptr& identifier,
                const Types::Ptr& argumentTypes,
                const Type::Ptr& returnType );

            const Types::Ptr& argumentTypes( void ) const;

            const Type::Ptr& returnType( void ) const;

            u1 mapping( void ) const;

            std::string signature( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Types::Ptr m_argumentTypes;
            const Type::Ptr m_returnType;
        };

        class FixedSizedType final : public Type
        {
          public:
            using Ptr = std::shared_ptr< FixedSizedType >;

            FixedSizedType( const IdentifierPath::Ptr& identifier, const Expression::Ptr& size );

            const Expression::Ptr& size( void ) const;

            std::string signature( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Expression::Ptr m_size;
        };
    }
}

#endif  // _LIBCASM_FE_AST_TYPE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
