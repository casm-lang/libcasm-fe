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

#include "../Location.h"

#include "../../casm-ir/src/Type.h"

namespace libcasm_fe
{
    namespace Ast
    {
        /**
         * @extends CasmFE
         */
        class Node
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
                RULE_REFERENCE_ATOM,
                UNDEF_ATOM,
                DIRECT_CALL_EXPRESSION,
                INDIRECT_CALL_EXPRESSION,
                UNARY_EXPRESSION,
                BINARY_EXPRESSION,
                RANGE_EXPRESSION,
                LIST_EXPRESSION,
                CONDITIONAL_EXPRESSION,
                UNIVERSAL_QUANTIFIER_EXPRESSION,
                EXISTENTIAL_QUANTIFIER_EXPRESSION,

                // rules
                SKIP_RULE,
                CONDITIONAL_RULE,
                CASE_RULE,
                LET_RULE,
                FORALL_RULE,
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

            Node( ID id );
            virtual ~Node() = default;

            ID id( void ) const;

            void setSourceLocation( const Location& sourceLocation );
            Location sourceLocation( void ) const;

            std::string name( void ) const;

            virtual void accept( Visitor& visitor ) = 0;

          private:
            ID m_id;
            Location m_sourceLocation;
        };

        template < typename T >
        class NodeList : public Node, public libstdhl::List< T >
        {
          public:
            using Ptr = std::shared_ptr< NodeList >;

            NodeList( void )
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

            libcasm_ir::Type::Ptr type( void ) const;

          private:
            libcasm_ir::Type::Ptr m_type;
        };
        
        class Identifier : public Node
        {
          public:
            using Ptr = std::shared_ptr< Identifier >;

            Identifier( const std::string& identifier );

            std::string identifier( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            std::string m_identifier;
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
        class IdentifierPath : public Node
        {
          public:
            enum class Type
            {
                ABSOLUTE, /**< absolute namespace + identifier path */
                RELATIVE, /**< path started with a dot, needs to be resolved */
            };

          public:
            using Ptr = std::shared_ptr< IdentifierPath >;

            IdentifierPath( const Identifiers::Ptr& identifiers, Type type );

            Identifiers::Ptr identifiers( void ) const;
            Type type( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Identifiers::Ptr m_identifiers;
            Type m_type;
        };

        template < typename T, typename... Args >
        typename T::Ptr make( const Location& sourceLocation, Args&&... args )
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
