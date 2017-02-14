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

namespace libcasm_fe
{
    namespace Ast
    {
        class Definition : public Node
        {
          public:
            using Ptr = std::shared_ptr< Definition >;

            Definition(
                Node::Type type, const IdentifierNode::Ptr& identifier );

            IdentifierNode::Ptr identifier() const;

            void setRelationType(
                const libcasm_ir::RelationType::Ptr& relationType );
            libcasm_ir::RelationType::Ptr relationType() const;

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
                const IdentifierNode::Ptr& typeName );

            IdentifierNode::Ptr typeName() const;

          private:
            IdentifierNode::Ptr m_typeName;
        };

        class FunctionDefinition : public Definition
        {
          public:
            enum class Classification
            {
                In, /**< only read by an ASM, only written by its env. */
                Monitored = In,
                Controlled, /**< read and written by an ASM */
                Shared, /**< read and written by an ASM and its env. */
                Out, /**< only written by an ASM, only read by its env. */
                Static
            };

          public:
            using Ptr = std::shared_ptr< FunctionDefinition >;

            FunctionDefinition( Classification classification,
                const IdentifierNode::Ptr& identifier,
                const NodeList< IdentifierNode >::Ptr& argumentTypeNames,
                const IdentifierNode::Ptr& returnTypeName );

            Classification classification() const;
            NodeList< IdentifierNode >::Ptr argumentTypeNames() const;
            IdentifierNode::Ptr returnTypeName() const;

            void setInitializers(
                const NodeList< UpdateRule >::Ptr& initializers );
            NodeList< UpdateRule >::Ptr initializers() const;

            void setDefaultValue( const Expression::Ptr& defaultValue );
            Expression::Ptr defaultValue() const;

          private:
            Classification m_classification;
            NodeList< IdentifierNode >::Ptr m_argumentTypeNames;
            IdentifierNode::Ptr m_returnTypeName;
            NodeList< UpdateRule >::Ptr m_initializers;
            Expression::Ptr m_defaultValue;
        };

        class DerivedDefinition : public Definition
        {
          public:
            using Ptr = std::shared_ptr< DerivedDefinition >;

            DerivedDefinition( const IdentifierNode::Ptr& identifier,
                const NodeList< VariableDefinition >::Ptr& arguments,
                const IdentifierNode::Ptr& returnTypeName,
                const Expression::Ptr& expression );

            NodeList< VariableDefinition >::Ptr arguments() const;
            IdentifierNode::Ptr returnTypeName() const;
            Expression::Ptr expression() const;

          private:
            NodeList< VariableDefinition >::Ptr m_arguments;
            IdentifierNode::Ptr m_returnTypeName;
            Expression::Ptr m_expression;
        };

        class RuleDefinition : public Definition
        {
          public:
            using Ptr = std::shared_ptr< RuleDefinition >;

            RuleDefinition( const IdentifierNode::Ptr& identifier,
                const NodeList< VariableDefinition >::Ptr& arguments,
                const IdentifierNode::Ptr& returnTypeName,
                const Rule::Ptr& rule );

            NodeList< VariableDefinition >::Ptr arguments() const;
            IdentifierNode::Ptr returnTypeName() const;
            Rule::Ptr rule() const;

          private:
            NodeList< VariableDefinition >::Ptr m_arguments;
            IdentifierNode::Ptr m_returnTypeName;
            Rule::Ptr m_rule;
        };

        class EnumerationDefinition : public Definition
        {
          public:
            using Ptr = std::shared_ptr< EnumerationDefinition >;

            EnumerationDefinition( const IdentifierNode::Ptr& identifier,
                const NodeList< IdentifierNode >::Ptr& enumerators );

            NodeList< IdentifierNode >::Ptr enumerators() const;

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
