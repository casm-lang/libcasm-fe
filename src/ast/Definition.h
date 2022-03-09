//
//  Copyright (C) 2014-2022 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber et al.
//                <https://github.com/casm-lang/libcasm-fe/graphs/contributors>
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

#ifndef _LIBCASM_FE_AST_DEFINITION_H_
#define _LIBCASM_FE_AST_DEFINITION_H_

#include <libcasm-fe/ast/Node>
#include <libcasm-fe/ast/Rule>
#include <libcasm-fe/ast/Type>
#include <libcasm-fe/cst/Definition>

#include <libcasm-ir/Value>

namespace libcasm_fe
{
    class Namespace;

    namespace AST
    {
        class Expression;
        using Expressions = NodeList< Expression >;
        class VariableDefinition;
        using VariableDefinitions = NodeList< VariableDefinition >;
        class ImplementDefinition;
        class TypeDefinition;

        class Definition : public TypedPropertyNode
        {
          public:
            using Ptr = std::shared_ptr< Definition >;

            Definition( const Node::ID id, const Identifier::Ptr& identifier );

            const Identifier::Ptr& identifier( void ) const;

            const std::shared_ptr< Namespace >& symboltable( void ) const;

            void setTemplateSymbols(
                const std::shared_ptr< VariableDefinitions >& templateSymbols );

            const std::shared_ptr< VariableDefinitions >& templateSymbols( void ) const;

            u1 isTemplate( void ) const;

            void setAbstract( const u1 abstract );

            u1 abstract( void ) const;

            void setExported( const u1 exported );

            u1 exported( void ) const;

            void setMaximumNumberOfLocals( std::size_t maxNumberOfLocals );

            std::size_t maximumNumberOfLocals( void ) const;

            virtual std::string typeDescription( void ) const = 0;

          protected:
            void clone( Definition& duplicate ) const;

          private:
            const Identifier::Ptr m_identifier;
            const std::shared_ptr< Namespace > m_symboltable;
            std::shared_ptr< VariableDefinitions > m_templateSymbols;
            u1 m_abstract;
            u1 m_exported;
            std::size_t m_maxNumberOfLocals;
        };

        using Definitions = NodeList< Definition >;

        class VariableDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< VariableDefinition >;

            VariableDefinition( const Identifier::Ptr& identifier, const Type::Ptr& variableType );

            const Type::Ptr& variableType( void ) const;
            void setVariableType( const Type::Ptr& variableType );

            /**
             Sets the frame local index of the variable.
             */
            void setLocalIndex( std::size_t localIndex );
            std::size_t localIndex( void ) const;

            // used in SymbolResolver to point to the correct Behavior/Implement Definition
            void setObjectDefinition( const std::shared_ptr< TypeDefinition >& objectDefinition );
            const std::shared_ptr< TypeDefinition >& objectDefinition( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            Type::Ptr m_variableType;
            std::size_t m_localIndex;
            std::shared_ptr< TypeDefinition > m_objectDefinition;
        };

        using VariableDefinitions = NodeList< VariableDefinition >;

        class TypeDefinition : public Definition
        {
          public:
            using Ptr = std::shared_ptr< TypeDefinition >;

            TypeDefinition( const Node::ID id, const Type::Ptr& domainType );

            const Type::Ptr& domainType( void ) const;

            void setBasicBehavior( const std::shared_ptr< ImplementDefinition >& basicBehavior );

            const std::shared_ptr< ImplementDefinition >& basicBehavior( void ) const;

            void addExtendedBehavior(
                const std::shared_ptr< ImplementDefinition >& extendedBehavior );

            const std::unordered_map< std::string, std::shared_ptr< ImplementDefinition > >&
            extendedBehaviors( void ) const;

          protected:
            void clone( TypeDefinition& duplicate ) const;

          private:
            const Type::Ptr m_domainType;
            std::shared_ptr< ImplementDefinition > m_basicBehavior;
            std::unordered_map< std::string, std::shared_ptr< ImplementDefinition > >
                m_extendedBehaviors;
        };

        using TypeDefinitions = NodeList< TypeDefinition >;

        class FunctionDefinition final : public Definition
        {
          public:
            using Classification = CST::FunctionDefinition::Classification;

          public:
            using Ptr = std::shared_ptr< FunctionDefinition >;

            FunctionDefinition(
                const Identifier::Ptr& identifier,
                const Types::Ptr& argumentTypes,
                const Type::Ptr& returnType,
                const Expression::Ptr& defined,
                const MappedExpressions::Ptr& initially,
                const Classification classification,
                const u1 symbolic );

            const Types::Ptr& argumentTypes( void ) const;

            const Type::Ptr& returnType( void ) const;

            const Expression::Ptr& defined( void ) const;

            const MappedExpressions::Ptr& initially( void ) const;

            Classification classification( void ) const;

            std::string classificationName( void ) const;

            u1 symbolic( void ) const;

            u1 program( void ) const;

            u1 local( void ) const;

            void setInitiallyRule( const Rule::Ptr& initiallyRule );

            const Rule::Ptr& initiallyRule( void ) const;

            const SequenceRule::Ptr& prologRule( void ) const;

            const SequenceRule::Ptr& epilogRule( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Types::Ptr m_argumentTypes;
            const Type::Ptr m_returnType;
            const Expression::Ptr m_defined;
            const MappedExpressions::Ptr m_initially;
            const Classification m_classification;
            const u1 m_symbolic;
            const u1 m_program;
            Rule::Ptr m_initiallyRule;
            SequenceRule::Ptr m_prologRule;
            SequenceRule::Ptr m_epilogRule;
        };

        using FunctionDefinitions = NodeList< FunctionDefinition >;

        class DerivedDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< DerivedDefinition >;

            DerivedDefinition(
                const Identifier::Ptr& identifier,
                const VariableDefinitions::Ptr& arguments,
                const Type::Ptr& returnType,
                const Expression::Ptr& expression );

            const VariableDefinitions::Ptr& arguments( void ) const;

            const Type::Ptr& returnType( void ) const;

            void setReturnType( const Type::Ptr& returnType );

            const Expression::Ptr& expression( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const VariableDefinitions::Ptr m_arguments;
            Type::Ptr m_returnType;
            const Expression::Ptr m_expression;
        };

        class RuleDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< RuleDefinition >;

            RuleDefinition(
                const Identifier::Ptr& identifier,
                const VariableDefinitions::Ptr& arguments,
                const Type::Ptr& returnType,
                const Rule::Ptr& rule );

            const NodeList< VariableDefinition >::Ptr& arguments( void ) const;

            const Type::Ptr& returnType( void ) const;

            void setReturnType( const Type::Ptr& returnType );

            const Rule::Ptr& rule( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const VariableDefinitions::Ptr m_arguments;
            Type::Ptr m_returnType;
            const Rule::Ptr m_rule;
        };

        class EnumeratorDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< EnumeratorDefinition >;

            EnumeratorDefinition( const Identifier::Ptr& identifier );

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;
        };

        using Enumerators = NodeList< EnumeratorDefinition >;

        class EnumerationDefinition final : public TypeDefinition
        {
          public:
            using Ptr = std::shared_ptr< EnumerationDefinition >;

            EnumerationDefinition(
                const Identifier::Ptr& identifier, const Enumerators::Ptr& enumerators );

            const Enumerators::Ptr& enumerators( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Enumerators::Ptr m_enumerators;
        };

        class UsingDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< UsingDefinition >;

            UsingDefinition( const Identifier::Ptr& identifier, const Type::Ptr& aliasType );

            const Type::Ptr& aliasType( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Type::Ptr m_aliasType;
        };

        class UsingPathDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< UsingPathDefinition >;

            UsingPathDefinition( const IdentifierPath::Ptr& path, const u1 explicitSymbol );

            const IdentifierPath::Ptr& path( void ) const;

            u1 explicitSymbol( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const IdentifierPath::Ptr m_path;
            const u1 m_explicitSymbol;
        };

        class InvariantDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< InvariantDefinition >;

            InvariantDefinition(
                const Identifier::Ptr& identifier, const Expression::Ptr& expression );

            const Expression::Ptr& expression( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override;

            Node::Ptr clone( void ) const override final;

          private:
            const Expression::Ptr m_expression;
        };

        class DomainDefinition final : public TypeDefinition
        {
          public:
            using Ptr = std::shared_ptr< DomainDefinition >;

            DomainDefinition( const Type::Ptr& domainType );

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;
        };

        class StructureDefinition final : public TypeDefinition
        {
          public:
            using Ptr = std::shared_ptr< StructureDefinition >;

            StructureDefinition(
                const Type::Ptr& domainType, const FunctionDefinitions::Ptr& functions );

            const FunctionDefinitions::Ptr& functions( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const FunctionDefinitions::Ptr m_functions;
        };

        class BehaviorDefinition final : public TypeDefinition
        {
          public:
            using Ptr = std::shared_ptr< BehaviorDefinition >;

            BehaviorDefinition( const Type::Ptr& domainType, const Definitions::Ptr& definitions );

            const Definitions::Ptr& definitions( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Definitions::Ptr m_definitions;
        };

        class ImplementDefinition final : public TypeDefinition
        {
          public:
            using Ptr = std::shared_ptr< ImplementDefinition >;

            ImplementDefinition(
                const Type::Ptr& behaviorType,
                const Type::Ptr& domainType,
                const Definitions::Ptr& definitions );

            const Type::Ptr& behaviorType( void ) const;

            const Definitions::Ptr& definitions( void ) const;

            u1 forBehaviorType( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Type::Ptr m_behaviorType;
            const Definitions::Ptr m_definitions;
        };

        class BuiltinDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< BuiltinDefinition >;

            BuiltinDefinition(
                const Identifier::Ptr& identifier,
                const Types::Ptr& argumentTypes,
                const Type::Ptr& returnType );

            const Types::Ptr& argumentTypes( void ) const;

            const Type::Ptr& returnType( void ) const;

            void setTargetId( const libcasm_ir::Value::ID targetId );

            libcasm_ir::Value::ID targetId( void ) const;

            u1 hasTargetId( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const Identifier::Ptr m_identifier;
            const Types::Ptr m_argumentTypes;
            const Type::Ptr m_returnType;
            libcasm_ir::Value::ID m_targetId;
        };

        class InitDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< InitDefinition >;

            InitDefinition( const MappedExpressions::Ptr& initializers, const u1 singleAgent );

            const MappedExpressions::Ptr& initializers( void ) const;

            u1 singleAgent( void ) const;

            void setExternal( void );

            u1 external( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const MappedExpressions::Ptr m_initializers;
            const u1 m_singleAgent;
            u1 m_external;
        };

        class ImportDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< ImportDefinition >;

            ImportDefinition( const IdentifierPath::Ptr& path, const Identifier::Ptr& identifier );

            const IdentifierPath::Ptr& path( void ) const;

            std::string typeDescription( void ) const override;

            void accept( Visitor& visitor ) override final;

            Node::Ptr clone( void ) const override final;

          private:
            const IdentifierPath::Ptr m_path;
        };
    }
}

#endif  // _LIBCASM_FE_AST_DEFINITION_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
