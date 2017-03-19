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

#ifndef _LIB_CASMFE_DEFINITION_H_
#define _LIB_CASMFE_DEFINITION_H_

#include "Node.h"

#include "Rule.h"
#include "Type.h"

namespace libcasm_fe
{
    namespace Ast
    {
        class Definition : public Node
        {
          public:
            using Ptr = std::shared_ptr< Definition >;

            Definition( Node::ID id, const IdentifierNode::Ptr& identifier );

            IdentifierNode::Ptr identifier( void ) const;

            void setRelationType(
                const libcasm_ir::RelationType::Ptr& relationType );
            libcasm_ir::RelationType::Ptr relationType( void ) const;

          private:
            IdentifierNode::Ptr m_identifier;
            libcasm_ir::RelationType::Ptr m_relationType;
        };

        using Definitions = NodeList< Definition >;

        class VariableDefinition : public Definition
        {
          public:
            using Ptr = std::shared_ptr< VariableDefinition >;

            VariableDefinition( const IdentifierNode::Ptr& identifier,
                const Type::Ptr& variableType );

            Type::Ptr variableType( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Type::Ptr m_variableType;
        };

        class FunctionDefinition : public Definition
        {
          public:
            enum class Classification
            {
                IN, /**< only read by an ASM, only written by its env. */
                CONTROLLED, /**< read and written by an ASM */
                SHARED,     /**< read and written by an ASM and its env. */
                OUT, /**< only written by an ASM, only read by its env. */
                STATIC
            };

          public:
            using Ptr = std::shared_ptr< FunctionDefinition >;

            FunctionDefinition( const IdentifierNode::Ptr& identifier,
                const Types::Ptr& argumentTypes,
                const Type::Ptr& returnType );

            Types::Ptr argumentTypes( void ) const;
            Type::Ptr returnType( void ) const;

            void setClassification( Classification classification );
            Classification classification( void ) const;

            void setSymbolic( bool symbolic );
            bool symbolic( void ) const;

            void setInitializers(
                const NodeList< UpdateRule >::Ptr& initializers );
            NodeList< UpdateRule >::Ptr initializers( void ) const;

            void setDefaultValue( const Expression::Ptr& defaultValue );
            Expression::Ptr defaultValue( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            Classification m_classification;
            Types::Ptr m_argumentTypes;
            Type::Ptr m_returnType;
            bool m_symbolic;
            NodeList< UpdateRule >::Ptr m_initializers;
            Expression::Ptr m_defaultValue;
        };

        class DerivedDefinition : public Definition
        {
          public:
            using Ptr = std::shared_ptr< DerivedDefinition >;

            DerivedDefinition( const IdentifierNode::Ptr& identifier,
                const NodeList< VariableDefinition >::Ptr& arguments,
                const Type::Ptr& returnType,
                const Expression::Ptr& expression );

            NodeList< VariableDefinition >::Ptr arguments( void ) const;

            Type::Ptr returnType( void ) const;
            Expression::Ptr expression( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            NodeList< VariableDefinition >::Ptr m_arguments;
            Type::Ptr m_returnType;
            Expression::Ptr m_expression;
        };

        class RuleDefinition : public Definition
        {
          public:
            using Ptr = std::shared_ptr< RuleDefinition >;

            RuleDefinition( const IdentifierNode::Ptr& identifier,
                const NodeList< VariableDefinition >::Ptr& arguments,
                const Type::Ptr& returnType,
                const Rule::Ptr& rule );

            NodeList< VariableDefinition >::Ptr arguments( void ) const;

            Type::Ptr returnType( void ) const;
            Rule::Ptr rule( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            NodeList< VariableDefinition >::Ptr m_arguments;
            Type::Ptr m_returnType;
            Rule::Ptr m_rule;
        };

        class EnumerationDefinition : public Definition
        {
          public:
            using Ptr = std::shared_ptr< EnumerationDefinition >;

            EnumerationDefinition( const IdentifierNode::Ptr& identifier,
                const NodeList< IdentifierNode >::Ptr& enumerators );

            NodeList< IdentifierNode >::Ptr enumerators( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            NodeList< IdentifierNode >::Ptr m_enumerators;
        };
    }
}

#endif // _LIB_CASMFE_DEFINITION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
