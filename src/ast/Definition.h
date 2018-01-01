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

#ifndef _LIBCASM_FE_DEFINITION_H_
#define _LIBCASM_FE_DEFINITION_H_

#include <libcasm-fe/ast/Attribute>
#include <libcasm-fe/ast/Node>
#include <libcasm-fe/ast/Rule>
#include <libcasm-fe/ast/Type>

namespace libcasm_fe
{
    namespace Ast
    {
        class Definition : public TypedNode
        {
          public:
            using Ptr = std::shared_ptr< Definition >;

            Definition( Node::ID id, const Identifier::Ptr& identifier );

            const Identifier::Ptr& identifier( void ) const;

            void setAttributes( const Attributes::Ptr& attributes );
            const Attributes::Ptr& attributes( void ) const;

            /**
             * Sets the number of required frame local slots.
             *
             * @note Assigned by SymbolResolved and used during execution
             */
            void setMaximumNumberOfLocals( std::size_t maxNumberOfLocals );
            std::size_t maximumNumberOfLocals( void ) const;

          private:
            const Identifier::Ptr m_identifier;
            Attributes::Ptr m_attributes;
            std::size_t m_maxNumberOfLocals;
        };

        using Definitions = NodeList< Definition >;

        class HeaderDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< HeaderDefinition >;

            HeaderDefinition( const SourceLocation& sourceLocation );

            void accept( Visitor& visitor ) override final;
        };

        class VariableDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< VariableDefinition >;

            VariableDefinition( const Identifier::Ptr& identifier, const Type::Ptr& variableType );

            const Type::Ptr& variableType( void ) const;

            /**
             * Sets the frame local index of the variable.
             *
             * @note Assigned by SymbolResolved and used during execution
             */
            void setLocalIndex( std::size_t localIndex );
            std::size_t localIndex( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Type::Ptr m_variableType;
            std::size_t m_localIndex;
        };

        class FunctionDefinition final : public Definition
        {
          public:
            enum class Classification
            {
                UNKNOWN,
                IN,         /**< only read by an ASM, only written by its env. */
                CONTROLLED, /**< read and written by an ASM */
                SHARED,     /**< read and written by an ASM and its env. */
                OUT,        /**< only written by an ASM, only read by its env. */
                STATIC
            };

            enum class UID
            {
                SELF = 1,
                PROGRAM = 2,
                RESULT = 3,
                OTHER
            };

            static std::string toString( const Classification classification );

          public:
            using Ptr = std::shared_ptr< FunctionDefinition >;

            FunctionDefinition(
                const Identifier::Ptr& identifier,
                const Types::Ptr& argumentTypes,
                const Type::Ptr& returnType );

            UID uid() const;

            const Types::Ptr& argumentTypes( void ) const;
            const Type::Ptr& returnType( void ) const;

            void setClassification( Classification classification );
            Classification classification( void ) const;
            std::string classificationName( void ) const;

            void setSymbolic( u1 symbolic );
            u1 symbolic( void ) const;

            void setInitializers( const NodeList< UpdateRule >::Ptr& initializers );
            const NodeList< UpdateRule >::Ptr& initializers( void ) const;

            void setDefaultValue( const Expression::Ptr& defaultValue );
            const Expression::Ptr& defaultValue( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Classification m_classification;
            const Types::Ptr m_argumentTypes;
            const Type::Ptr m_returnType;
            u1 m_symbolic;
            NodeList< UpdateRule >::Ptr m_initializers;
            Expression::Ptr m_defaultValue;
            UID m_uid;
        };

        class DerivedDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< DerivedDefinition >;

            DerivedDefinition(
                const Identifier::Ptr& identifier,
                const NodeList< VariableDefinition >::Ptr& arguments,
                const Type::Ptr& returnType,
                const Expression::Ptr& expression );

            const NodeList< VariableDefinition >::Ptr& arguments( void ) const;

            const Type::Ptr& returnType( void ) const;
            const Expression::Ptr& expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const NodeList< VariableDefinition >::Ptr m_arguments;
            const Type::Ptr m_returnType;
            const Expression::Ptr m_expression;
        };

        class RuleDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< RuleDefinition >;

            RuleDefinition(
                const Identifier::Ptr& identifier,
                const NodeList< VariableDefinition >::Ptr& arguments,
                const Type::Ptr& returnType,
                const Rule::Ptr& rule );

            const NodeList< VariableDefinition >::Ptr& arguments( void ) const;

            const Type::Ptr& returnType( void ) const;
            const Rule::Ptr& rule( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const NodeList< VariableDefinition >::Ptr m_arguments;
            const Type::Ptr m_returnType;
            const Rule::Ptr m_rule;
        };

        class EnumeratorDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< EnumeratorDefinition >;

            EnumeratorDefinition( const Identifier::Ptr& identifier );

            void accept( Visitor& visitor ) override final;
        };

        using Enumerators = NodeList< EnumeratorDefinition >;

        class EnumerationDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< EnumerationDefinition >;

            EnumerationDefinition(
                const Identifier::Ptr& identifier, const Enumerators::Ptr& enumerators );

            const Enumerators::Ptr& enumerators( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Enumerators::Ptr m_enumerators;
        };

        class UsingDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< UsingDefinition >;

            UsingDefinition( const Identifier::Ptr& identifier, const Type::Ptr& type );

            const Type::Ptr& type( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Type::Ptr m_type;
        };
    }
}

namespace std
{
    template <>
    struct hash< libcasm_fe::Ast::FunctionDefinition::UID >
    {
        std::size_t operator()( libcasm_fe::Ast::FunctionDefinition::UID uid ) const
        {
            return static_cast< std::size_t >( uid );
        }
    };
}

#endif  // _LIBCASM_FE_DEFINITION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
