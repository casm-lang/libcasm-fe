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

#ifndef _LIB_CASMFE_NODE_H_
#define _LIB_CASMFE_NODE_H_

#include "Visitor.h"

#include "../stdhl/cpp/List.h"
#include "../stdhl/cpp/Type.h"

#include "../SourceLocation.h"

#include "../../casm-ir/src/Type.h"

namespace libcasm_fe
{
    namespace Ast
    {
        /**
         * @extends CasmFE
         */
        class Node : public std::enable_shared_from_this< Node >
        {
          public:
            enum class ID
            {
                SPECIFICATION,

                // definitions
                VARIABLE_DEFINITION,
                FUNCTION_DEFINITION,
                DERIVED_DEFINITION,
                RULE_DEFINITION,
                ENUMERATION_DEFINITION,

                // expressions
                VALUE_ATOM,
                REFERENCE_ATOM,
                UNDEF_ATOM,
                DIRECT_CALL_EXPRESSION,
                INDIRECT_CALL_EXPRESSION,
                UNARY_EXPRESSION,
                BINARY_EXPRESSION,
                RANGE_EXPRESSION,
                LIST_EXPRESSION,
                CONDITIONAL_EXPRESSION,
                CHOOSE_EXPRESSION,
                UNIVERSAL_QUANTIFIER_EXPRESSION,
                EXISTENTIAL_QUANTIFIER_EXPRESSION,

                // rules
                SKIP_RULE,
                CONDITIONAL_RULE,
                CASE_RULE,
                LET_RULE,
                FORALL_RULE,
                CHOOSE_RULE,
                ITERATE_RULE,
                BLOCK_RULE,
                SEQUENCE_RULE,
                UPDATE_RULE,
                CALL_RULE,

                // types
                UNRESOLVED_TYPE,
                BASIC_TYPE,
                COMPOSED_TYPE,
                FIXED_SIZED_TYPE,
                RELATION_TYPE,

                // attributes
                BASIC_ATTRIBUTE,
                EXPRESSION_ATTRIBUTE,

                // other
                NODE_LIST,
                IDENTIFIER,
                IDENTIFIER_PATH,
                EXPRESSION_CASE,
                DEFAULT_CASE,
            };

          public:
            using Ptr = std::shared_ptr< Node >;

            explicit Node( ID id );
            virtual ~Node() = default;

            ID id( void ) const;

            void setSourceLocation( const SourceLocation& sourceLocation );
            const SourceLocation& sourceLocation( void ) const;

            /**
             * @return A short description about the node type.
             */
            virtual std::string description( void ) const final;

            template < typename T >
            typename T::Ptr ptr( void )
            {
                return std::static_pointer_cast< T >( shared_from_this() );
            }

            virtual void accept( Visitor& visitor ) = 0;

          private:
            const ID m_id;
            SourceLocation m_sourceLocation;
        };

        template < typename T >
        class NodeList final : public Node, public libstdhl::List< T >
        {
          public:
            using Ptr = std::shared_ptr< NodeList >;

            explicit NodeList( void )
            : Node( Node::ID::NODE_LIST )
            {
            }

            void accept( Visitor& visitor ) override final
            {
                for( auto& node : *this )
                {
                    node->accept( visitor );
                }
            }
        };

        class TypedNode : public Node
        {
          public:
            TypedNode( Node::ID id );

            void setType( const libcasm_ir::Type::Ptr& type );
            const libcasm_ir::Type::Ptr& type( void ) const;

          private:
            libcasm_ir::Type::Ptr m_type;
        };

        class Identifier final : public Node
        {
          public:
            using Ptr = std::shared_ptr< Identifier >;

            explicit Identifier( const std::string& name );

            const std::string& name( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            std::string m_name;
        };

        using Identifiers = NodeList< Identifier >;

        /**
         * @brief An identifier path is an identifier + namespaces.
         *
         * The identifier path can either be absolute or relative. The string of
         * a relative identifier path starts with a dot. All relative identifier
         * paths will later be resolved and converted into absolute paths.
         *
         * An absolute path "Color.Red" will be splitted into the namespaces
         * ["Color"] and identifier "Red". Furthermore the node will be marked
         * as NamespaceType.ABSOLUTE.
         *
         * A relative path ".Red" will be splitted into the namespaces [] and
         * identifier "Red". Furthermore the node will be marked as
         * NamespaceType.RELATIVE.
         */
        class IdentifierPath final : public Node
        {
          public:
            enum class Type
            {
                ABSOLUTE, /**< absolute namespace + identifier path */
                RELATIVE, /**< path started with a dot, needs to be resolved */
            };

          public:
            using Ptr = std::shared_ptr< IdentifierPath >;

            IdentifierPath(
                const Identifier::Ptr& identifier, Type type = Type::ABSOLUTE );

            /**
             * @param identifiers A list of identifiers (must not be empty)
             * @param type The type of the identifier path (default is ABSOLUTE)
             */
            IdentifierPath( const Identifiers::Ptr& identifiers,
                Type type = Type::ABSOLUTE );

            Identifiers::Ptr identifiers( void ) const;
            Type type( void ) const;

            const std::string& baseName( void ) const;
            std::string baseDir( void ) const;
            std::string path( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Identifiers::Ptr m_identifiers;
            const Type m_type;
        };

        template < typename T, typename... Args >
        typename T::Ptr make(
            const SourceLocation& sourceLocation, Args&&... args )
        {
            auto node
                = std::make_shared< T >( std::forward< Args >( args )... );
            node->setSourceLocation( sourceLocation );
            return node;
        }
    }
}

#endif // _LIB_CASMFE_NODE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
