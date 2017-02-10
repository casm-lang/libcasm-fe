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

#include "CasmFE.h"

#include "various/location.hh"

#include "../stdhl/cpp/List.h"
#include "../stdhl/cpp/Type.h"

namespace libcasm_fe
{
    namespace Ast
    {
        class Node : public CasmFE
        {
          public:
            enum class Type
            {
                NODE_LIST,
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
                DIRECT_CALL_EXPRESSION,
                INDIRECT_CALL_EXPRESSION,
                UNARY_EXPRESSION,
                BINARY_EXPRESSION,

                // rules
                PRINT_RULE,
                ASSERT_RULE,
                ASSURE_RULE,
                SKIP_RULE,
                ABORT_RULE,
                IMPOSSIBLE_RULE,
                CONDITIONAL_RULE,
                CASE_RULE,
                LET_RULE,
                FORALL_RULE,
                ITERATE_RULE,
                BLOCK_RULE,
                SEQUENCE_RULE,
                UPDATE_RULE,

                // TODO
                INIT,
                PROVIDER,
                OPTION,
                POP_RULE,
                PUSH_RULE,
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

        template < typename T >
        class NodeList : public Node, public libstdhl::List< T >
        {
          public:
            using Ptr = std::shared_ptr< NodeList >;

            NodeList()
            : Node( Node::Type::NODE_LIST )
            {
            }
        };

        class IdentifierNode : public Node
        {
          public:
            using Ptr = std::shared_ptr< IdentifierNode >;

            IdentifierNode( const std::string& identifier );

            std::string identifier() const;

          private:
            std::string m_identifier;
        };

        template < typename T, typename... Args >
        typename T::Ptr make( const yy::location& location, Args&&... args )
        {
            auto node = libstdhl::make< T >( std::forward< Args >( args )... );
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
