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

#include <memory>
#include <vector>

#include "../various/location.hh"

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
                NODE_LIST = 0,

                SPECIFICATION,
                IDENTIFIER,

                // definitions
                VARIABLE_DEFINITION,
                FUNCTION_DEFINITION,
                DERIVED_DEFINITION,
                RULE_DEFINITION,
                ENUMERATION_DEFINITION,

                // expressions
                VALUE_ATOM,
                RULE_REFERENCE_ATOM,
                ZERO_ATOM,
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
                VOID_TYPE,
                UNRESOLVED_TYPE,
                BASIC_TYPE,
                COMPOSED_TYPE,
                FIXED_SIZED_TYPE,
                RANGED_TYPE,

                // TODO
                INIT,
                PROVIDER,
                OPTION,
            };

          public:
            using Ptr = std::shared_ptr< Node >;

            Node( ID id );
            virtual ~Node() = default;

            ID id( void ) const;

            void setSourceLocation( const location& sourceLocation );

            location sourceLocation( void ) const;

            virtual void accept( Visitor& visitor ) = 0;

          private:
            ID m_id;

            location m_sourceLocation;
        };

        template < typename T >
        class NodeList : public Node
        {
          public:
            using Ptr = std::shared_ptr< NodeList >;
            using iterator = typename std::vector< typename T::Ptr >::iterator;
            using const_iterator =
                typename std::vector< typename T::Ptr >::const_iterator;

            NodeList( void )
            : Node( Node::ID::NODE_LIST )
            {
            }

            void add( const typename T::Ptr& node )
            {
                m_elements.emplace_back( node );
            }

            iterator begin( void )
            {
                return m_elements.begin();
            }

            const_iterator begin( void ) const
            {
                return m_elements.begin();
            }

            const_iterator cbegin( void ) const
            {
                return m_elements.cbegin();
            }

            iterator end( void )
            {
                return m_elements.end();
            }

            const_iterator end( void ) const
            {
                return m_elements.end();
            }

            const_iterator cend( void ) const
            {
                return m_elements.cend();
            }

            void accept( Visitor& visitor ) override final
            {
                for( auto& node : *this )
                {
                    node->accept( visitor );
                }
            }

          private:
            std::vector< typename T::Ptr > m_elements;
        };

        class IdentifierNode : public Node
        {
          public:
            using Ptr = std::shared_ptr< IdentifierNode >;

            IdentifierNode( const std::string& identifier );

            std::string identifier( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            std::string m_identifier;
        };

        template < typename T, typename... Args >
        typename T::Ptr make( const location& location, Args&&... args )
        {
            auto node
                = std::make_shared< T >( std::forward< Args >( args )... );
            node->setSourceLocation( location );
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
