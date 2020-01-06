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

#ifndef _LIBCASM_FE_NODE_H_
#define _LIBCASM_FE_NODE_H_

#include <libcasm-fe/CasmFE>
#include <libcasm-fe/ast/Visitor>
#include <libcasm-ir/Property>
#include <libcasm-ir/Type>
#include <libstdhl/List>
#include <libstdhl/SourceLocation>

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
                // definitions
                HEADER_DEFINITION,
                INIT_DEFINITION,
                INITIALLY,
                VARIABLE_DEFINITION,
                FUNCTION_DEFINITION,
                DERIVED_DEFINITION,
                RULE_DEFINITION,
                ENUMERATOR_DEFINITION,
                ENUMERATION_DEFINITION,
                USING_DEFINITION,
                USING_PATH_DEFINITION,
                INVARIANT_DEFINITION,
                IMPORT_DEFINITION,
                DOMAIN_DEFINITION,
                STRUCTURE_DEFINITION,
                BEHAVIOR_DEFINITION,
                IMPLEMENT_DEFINITION,
                BUILTIN_DEFINITION,
                DECLARATION,

                // literals
                UNDEF_LITERAL,
                VALUE_LITERAL,
                REFERENCE_LITERAL,
                LIST_LITERAL,
                RANGE_LITERAL,
                TUPLE_LITERAL,
                RECORD_LITERAL,

                // expressions
                EMBRACED_EXPRESSION,
                NAMED_EXPRESSION,
                DIRECT_CALL_EXPRESSION,
                METHOD_CALL_EXPRESSION,
                LITERAL_CALL_EXPRESSION,
                INDIRECT_CALL_EXPRESSION,
                TYPE_CASTING_EXPRESSION,
                UNARY_EXPRESSION,
                BINARY_EXPRESSION,
                LET_EXPRESSION,
                CONDITIONAL_EXPRESSION,
                CHOOSE_EXPRESSION,
                UNIVERSAL_QUANTIFIER_EXPRESSION,
                EXISTENTIAL_QUANTIFIER_EXPRESSION,
                CARDINALITY_EXPRESSION,

                // rules
                SKIP_RULE,
                CONDITIONAL_RULE,
                CASE_RULE,
                LET_RULE,
                LOCAL_RULE,
                FORALL_RULE,
                CHOOSE_RULE,
                ITERATE_RULE,
                BLOCK_RULE,
                SEQUENCE_RULE,
                UPDATE_RULE,
                CALL_RULE,
                WHILE_RULE,

                // types
                UNRESOLVED_TYPE,
                BASIC_TYPE,
                TUPLE_TYPE,
                RECORD_TYPE,
                TEMPLATE_TYPE,
                FIXED_SIZED_TYPE,
                RELATION_TYPE,

                // attributes
                BASIC_ATTRIBUTE,
                EXPRESSION_ATTRIBUTE,

                // helper
                DEFINED,
                TEMPLATE,
                INITIALIZER,

                // other
                NODE_LIST,
                IDENTIFIER,
                IDENTIFIER_PATH,
                EXPRESSION_CASE,
                DEFAULT_CASE,
                VARIABLE_BINDING,
                TOKEN,
                SPAN,
            };

          public:
            using Ptr = std::shared_ptr< Node >;

            explicit Node( ID id );
            virtual ~Node() = default;

            ID id( void ) const;

            void setSourceLocation( const libstdhl::SourceLocation& sourceLocation );
            const libstdhl::SourceLocation& sourceLocation( void ) const;

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

            template < typename T >
            typename T::Ptr duplicate( void ) const
            {
                return std::static_pointer_cast< T >( clone() );
            }

          protected:
            virtual Node::Ptr clone( void ) const = 0;

            void clone( Node& duplicate ) const;

          private:
            const ID m_id;
            libstdhl::SourceLocation m_sourceLocation;
        };

        template < typename T >
        class NodeList final
        : public Node
        , public libstdhl::List< T >
        {
          public:
            using Ptr = std::shared_ptr< NodeList >;

            explicit NodeList( void )
            : Node( Node::ID::NODE_LIST )
            {
            }

            explicit NodeList( const std::vector< typename T::Ptr >& elements )
            : Node( Node::ID::NODE_LIST )
            , libstdhl::List< T >( elements )
            {
            }

            void accept( Visitor& visitor ) override final
            {
                for( auto& node : *this )
                {
                    node->accept( visitor );
                }
            }

            Node::Ptr clone( void ) const override final
            {
                auto duplicate = std::make_shared< NodeList< T > >();
                for( const auto& element : *this )
                {
                    const auto duplicateElement = element->template duplicate< T >();
                    duplicate->add( duplicateElement );
                }
                Node::clone( *duplicate );
                return duplicate;
            }
        };

        class TypedNode : public Node
        {
          public:
            using Ptr = std::shared_ptr< TypedNode >;

            TypedNode( Node::ID id );

            void setType( const libcasm_ir::Type::Ptr& type );
            const libcasm_ir::Type::Ptr& type( void ) const;

          protected:
            void clone( TypedNode& duplicate ) const;

          private:
            libcasm_ir::Type::Ptr m_type;
        };

        class TypedPropertyNode : public TypedNode
        {
          public:
            using Ptr = std::shared_ptr< TypedPropertyNode >;

            TypedPropertyNode( Node::ID id );

            void setProperty( const libcasm_ir::Property property );
            void setProperties( const libcasm_ir::Properties& properties );
            const libcasm_ir::Properties& properties( void ) const;

          protected:
            void clone( TypedPropertyNode& duplicate ) const;

          private:
            libcasm_ir::Properties m_properties;
        };

        template < typename T, typename... Args >
        typename T::Ptr make( const libstdhl::SourceLocation& sourceLocation, Args&&... args )
        {
            auto node = std::make_shared< T >( std::forward< Args >( args )... );
            node->setSourceLocation( sourceLocation );
            return node;
        }
    }
}

#endif  // _LIBCASM_FE_NODE_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
