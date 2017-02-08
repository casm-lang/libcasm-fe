//
//  Copyright (c) 2014-2017 CASM Organization
//  All rights reserved.
//
//  Developed by: Florian Hahn
//                Philipp Paulweber
//                Emmanuel Pescosta
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

#include <memory>
#include <vector>

#include "../various/location.hh"

namespace libcasm_fe
{
    namespace Ast
    {
        class Node
        {
          public:
            enum class Type
            {
                NODE_LIST,
                SPECIFICATION,

                // definitions
                FUNCTION_DEFINITION,
                DERIVED_DEFINITION,
                RULE_DEFINITION,
                ENUMERATION_DEFINITION,

                // expressions
                ATOM,
                UNARY_EXPRESSION,
                BINARY_EXPRESSION,

                // rules
                PRINT_RULE,
                ASSERT_RULE,
                ASSURE_RULE,
                SKIP_RULE,
                DIEDIE_RULE,
                IMPOSSIBLE_RULE,
                CONDITIONAL_RULE,
                LET_RULE,
                FORALL_RULE,
                ITERATE_RULE,
                BLOCK_RULE,
                SEQUENCE_RULE,

                // TODO
                INIT,
                PROVIDER,
                OPTION,
                CALL_RULE,
                UPDATE_RULE,
                POP_RULE,
                PUSH_RULE,
                CASE_RULE,
            };

          public:
            using Ptr = std::shared_ptr< Node >;

            Node( Type type );

            Type type() const;

            void setLocation( const yy::location& location );
            yy::location location() const;

          private:
            Type m_type;
            yy::location m_location;
        };

        template < typename NodeType >
        class NodeList : public Node
        {
          public:
            using Ptr = std::shared_ptr< NodeList >;
            using iterator =
                typename std::vector< typename NodeType::Ptr >::iterator;
            using const_iterator =
                typename std::vector< typename NodeType::Ptr >::const_iterator;

            NodeList()
            : Node( Node::Type::NODE_LIST )
            {
            }

            std::size_t size() const
            {
                return m_nodes.size();
            }

            void add( const typename NodeType::Ptr& node )
            {
                m_nodes.push_back( node );
            }

            iterator begin()
            {
                return m_nodes.begin();
            }

            iterator end()
            {
                return m_nodes.end();
            }

            const_iterator cbegin() const
            {
                return m_nodes.cbegin();
            }

            const_iterator cend() const
            {
                return m_nodes.cend();
            }

          private:
            std::vector< typename NodeType::Ptr > m_nodes;
        };

        template < typename NodeType, typename... Args >
        typename NodeType::Ptr make_node( Args&&... args )
        {
            return std::make_shared< NodeType >(
                std::forward< Args >( args )... );
        }

        template < typename NodeType, typename... Args >
        typename NodeType::Ptr make_node(
            const yy::location& location, Args&&... args )
        {
            auto node = std::make_shared< NodeType >(
                std::forward< Args >( args )... );
            node->setLocation( location );
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
