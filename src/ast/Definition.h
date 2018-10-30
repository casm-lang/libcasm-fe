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

#ifndef _LIBCASM_FE_DEFINITION_H_
#define _LIBCASM_FE_DEFINITION_H_

#include <libcasm-fe/ast/Attribute>
#include <libcasm-fe/ast/Helper>
#include <libcasm-fe/ast/Node>
#include <libcasm-fe/ast/Rule>
#include <libcasm-fe/ast/Token>
#include <libcasm-fe/ast/Type>

namespace libcasm_fe
{
    namespace Ast
    {
        class Expression;
        using Expressions = NodeList< Expression >;

        class Definition : public TypedPropertyNode
        {
          public:
            using Ptr = std::shared_ptr< Definition >;

            Definition( Node::ID id, const Identifier::Ptr& identifier );

            const Identifier::Ptr& identifier( void ) const;

            void setAttributes( const Attributes::Ptr& attributes );
            const Attributes::Ptr& attributes( void ) const;

            void setDelimiterToken( const Token::Ptr& delimiterToken );
            const Token::Ptr& delimiterToken( void ) const;

            /**
             * Sets the number of required frame local slots.
             *
             * @note Assigned by SymbolResolved and used during execution
             */
            void setMaximumNumberOfLocals( std::size_t maxNumberOfLocals );
            std::size_t maximumNumberOfLocals( void ) const;

            void setExported( const u1 exported );
            u1 exported( void ) const;

          private:
            const Identifier::Ptr m_identifier;
            Attributes::Ptr m_attributes;
            Token::Ptr m_delimiterToken;
            std::size_t m_maxNumberOfLocals;
            u1 m_exported;
        };

        using Definitions = NodeList< Definition >;

        class HeaderDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< HeaderDefinition >;

            HeaderDefinition( const Token::Ptr& headerToken );

            void accept( Visitor& visitor ) override final;

            const Token::Ptr& headerToken( void ) const;

          private:
            const Token::Ptr m_headerToken;
        };

        class VariableDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< VariableDefinition >;

            VariableDefinition(
                const Identifier::Ptr& identifier,
                const Token::Ptr& colonToken,
                const Type::Ptr& variableType );

            const Type::Ptr& variableType( void ) const;

            const Token::Ptr& colonToken( void ) const;

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
            const Token::Ptr m_colonToken;
            std::size_t m_localIndex;
        };

        using VariableDefinitions = NodeList< VariableDefinition >;

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
                STATIC,
                LOCAL
            };

            static std::string toString( const Classification classification );

          public:
            using Ptr = std::shared_ptr< FunctionDefinition >;

            FunctionDefinition(
                const Token::Ptr& functionToken,
                const Identifier::Ptr& identifier,
                const Token::Ptr& colonToken,
                const Types::Ptr& argumentTypes,
                const Token::Ptr& mapsToken,
                const Type::Ptr& returnType,
                const Defined::Ptr& defined,
                const Initially::Ptr& initially );

            bool isProgram( void ) const;
            bool isLocal( void ) const;

            const Types::Ptr& argumentTypes( void ) const;

            const Type::Ptr& returnType( void ) const;

            const Token::Ptr& functionToken( void ) const;

            const Token::Ptr& colonToken( void ) const;

            const Token::Ptr& mapsToken( void ) const;

            const Defined::Ptr& defined( void ) const;

            const Initially::Ptr& initially( void ) const;

            void setClassification( Classification classification );
            Classification classification( void ) const;
            std::string classificationName( void ) const;

            void setSymbolic( u1 symbolic );
            u1 symbolic( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Types::Ptr m_argumentTypes;
            const Type::Ptr m_returnType;
            const Defined::Ptr m_defined;
            const Token::Ptr m_functionToken;
            const Token::Ptr m_colonToken;
            const Token::Ptr m_mapsToken;
            Classification m_classification;
            u1 m_symbolic;
            Initially::Ptr m_initially;
            const bool m_isProgram;
        };

        using FunctionDefinitions = NodeList< FunctionDefinition >;

        class DerivedDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< DerivedDefinition >;

            DerivedDefinition(
                const Token::Ptr& derivedToken,
                const Identifier::Ptr& identifier,
                const NodeList< VariableDefinition >::Ptr& arguments,
                const Token::Ptr& mapsToken,
                const Type::Ptr& returnType,
                const Token::Ptr& assignmentToken,
                const Expression::Ptr& expression );

            const NodeList< VariableDefinition >::Ptr& arguments( void ) const;

            const Type::Ptr& returnType( void ) const;
            const Expression::Ptr& expression( void ) const;

            const Token::Ptr& derivedToken( void ) const;

            const Token::Ptr& mapsToken( void ) const;

            const Token::Ptr& assignmentToken( void ) const;

            void setLeftBracketToken( const Token::Ptr& leftBracketToken );
            const Token::Ptr& leftBracketToken( void ) const;

            void setRightBracketToken( const Token::Ptr& rightBracketToken );
            const Token::Ptr& rightBracketToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const NodeList< VariableDefinition >::Ptr m_arguments;
            const Type::Ptr m_returnType;
            const Expression::Ptr m_expression;
            const Token::Ptr m_derivedToken;
            const Token::Ptr m_mapsToken;
            const Token::Ptr m_assignmentToken;
            Token::Ptr m_leftBracketToken;
            Token::Ptr m_rightBracketToken;
        };

        class RuleDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< RuleDefinition >;

            RuleDefinition(
                const Token::Ptr& ruleToken,
                const Identifier::Ptr& identifier,
                const NodeList< VariableDefinition >::Ptr& arguments,
                const Token::Ptr& mapsToken,
                const Type::Ptr& returnType,
                const Token::Ptr& assignmentToken,
                const Rule::Ptr& rule );

            const NodeList< VariableDefinition >::Ptr& arguments( void ) const;

            const Type::Ptr& returnType( void ) const;
            const Rule::Ptr& rule( void ) const;

            const Token::Ptr& ruleToken( void ) const;

            const Token::Ptr& mapsToken( void ) const;

            const Token::Ptr& assignmentToken( void ) const;

            void setLeftBracketToken( const Token::Ptr& leftBracketToken );
            const Token::Ptr& leftBracketToken( void ) const;

            void setRightBracketToken( const Token::Ptr& rightBracketToken );
            const Token::Ptr& rightBracketToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const NodeList< VariableDefinition >::Ptr m_arguments;
            const Type::Ptr m_returnType;
            const Rule::Ptr m_rule;
            const Token::Ptr m_ruleToken;
            const Token::Ptr m_mapsToken;
            const Token::Ptr m_assignmentToken;
            Token::Ptr m_leftBracketToken;
            Token::Ptr m_rightBracketToken;
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
                const Token::Ptr& enumerationToken,
                const Identifier::Ptr& identifier,
                const Token::Ptr& assignmentToken,
                const Token::Ptr& leftBraceToken,
                const Enumerators::Ptr& enumerators,
                const Token::Ptr& rightBraceToken );

            const Enumerators::Ptr& enumerators( void ) const;

            const Token::Ptr& enumerationToken( void ) const;

            const Token::Ptr& assignmentToken( void ) const;

            const Token::Ptr& leftBraceToken( void ) const;

            const Token::Ptr& rightBraceToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Enumerators::Ptr m_enumerators;
            const Token::Ptr m_enumerationToken;
            const Token::Ptr m_assignmentToken;
            const Token::Ptr m_leftBraceToken;
            const Token::Ptr m_rightBraceToken;
        };

        class UsingDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< UsingDefinition >;

            UsingDefinition(
                const Token::Ptr& usingToken,
                const Identifier::Ptr& identifier,
                const Token::Ptr& assignmentToken,
                const Type::Ptr& type );

            const Type::Ptr& type( void ) const;

            const Token::Ptr& usingToken( void ) const;

            const Token::Ptr& assignmentToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Type::Ptr m_type;
            const Token::Ptr m_usingToken;
            const Token::Ptr m_assignmentToken;
        };

        class UsingPathDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< UsingPathDefinition >;

            UsingPathDefinition(
                const Token::Ptr& usingToken,
                const IdentifierPath::Ptr& path,
                const Token::Ptr& doubleColonToken,
                const Token::Ptr& asterixToken );

            UsingPathDefinition( const Token::Ptr& usingToken, const IdentifierPath::Ptr& path );

            const IdentifierPath::Ptr& path( void ) const;

            u1 explicitSymbol( void ) const;

            const Token::Ptr& usingToken( void ) const;

            const Token::Ptr& doubleColonToken( void ) const;

            const Token::Ptr& asterixToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const IdentifierPath::Ptr m_path;
            const Token::Ptr m_usingToken;
            const Token::Ptr m_doubleColonToken;
            const Token::Ptr m_asterixToken;
        };

        class InvariantDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< InvariantDefinition >;

            InvariantDefinition(
                const Token::Ptr& invariantToken,
                const Identifier::Ptr& identifier,
                const Token::Ptr& assignmentToken,
                const Expression::Ptr& expression );

            const Expression::Ptr& expression( void ) const;

            const Token::Ptr& invariantToken( void ) const;

            const Token::Ptr& assignmentToken( void ) const;

            void accept( Visitor& visitor ) override;

          private:
            const Expression::Ptr m_expression;
            const Token::Ptr m_invariantToken;
            const Token::Ptr m_assignmentToken;
        };

        class StructureDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< StructureDefinition >;

            StructureDefinition(
                const Token::Ptr structureToken,
                const Identifier::Ptr& identifier,
                const Token::Ptr assignmentToken,
                const Token::Ptr leftBraceToken,
                const FunctionDefinitions::Ptr& functions,
                const Token::Ptr rightBraceToken );

            const FunctionDefinitions::Ptr& functions( void ) const;

            const Token::Ptr structureToken( void ) const;

            const Token::Ptr assignmentToken( void ) const;

            const Token::Ptr leftBraceToken( void ) const;

            const Token::Ptr rightBraceToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const FunctionDefinitions::Ptr m_functions;
            const Token::Ptr m_structureToken;
            const Token::Ptr m_assignmentToken;
            const Token::Ptr m_leftBraceToken;
            const Token::Ptr m_rightBraceToken;
        };

        class FeatureDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< FeatureDefinition >;

            FeatureDefinition(
                const Token::Ptr featureToken,
                const Identifier::Ptr& identifier,
                const Token::Ptr assignmentToken,
                const Token::Ptr leftBraceToken,
                const Definitions::Ptr& definitions,
                const Token::Ptr rightBraceToken );

            const Definitions::Ptr& definitions( void ) const;

            const Token::Ptr featureToken( void ) const;

            const Token::Ptr assignmentToken( void ) const;

            const Token::Ptr leftBraceToken( void ) const;

            const Token::Ptr rightBraceToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Definitions::Ptr m_definitions;
            const Token::Ptr m_featureToken;
            const Token::Ptr m_assignmentToken;
            const Token::Ptr m_leftBraceToken;
            const Token::Ptr m_rightBraceToken;
        };

        class ImplementDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< ImplementDefinition >;

            ImplementDefinition(
                const IdentifierPath::Ptr& feature,
                const Identifier::Ptr& identifier,
                const Definitions::Ptr& definitions );

            const IdentifierPath::Ptr& feature( void ) const;

            const Definitions::Ptr& definitions( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const IdentifierPath::Ptr m_feature;
            const Definitions::Ptr m_definitions;
        };

        class DeclarationDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< DeclarationDefinition >;

            enum class Kind
            {
                DERIVED,
                RULE
            };

            DeclarationDefinition(
                const Identifier::Ptr& identifier,
                const Types::Ptr& argumentTypes,
                const Type::Ptr& returnType,
                const Kind kind );

            const Types::Ptr& argumentTypes( void ) const;

            const Type::Ptr& returnType( void ) const;

            Kind kind( void ) const;

            std::string kindName( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const Types::Ptr m_argumentTypes;
            const Type::Ptr m_returnType;
            const Kind m_kind;
        };

        using DeclarationDefinitions = NodeList< DeclarationDefinition >;

        class InitDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< InitDefinition >;

            InitDefinition( const Token::Ptr& initToken, const IdentifierPath::Ptr& initPath );

            InitDefinition(
                const Token::Ptr& initToken,
                const Token::Ptr& leftBraceToken,
                const Initializers::Ptr& initializers,
                const Token::Ptr& rightBraceToken );

            const IdentifierPath::Ptr& initPath( void ) const;

            const Initializers::Ptr& initializers( void ) const;

            const Token::Ptr& initToken( void ) const;

            const Token::Ptr& leftBraceToken( void ) const;

            const Token::Ptr& rightBraceToken( void ) const;

            void setProgramFunction( const FunctionDefinition::Ptr& programFunction );
            const FunctionDefinition::Ptr& programFunction( void ) const;

            u1 isSingleAgent( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const IdentifierPath::Ptr m_initPath;
            const Initializers::Ptr m_initializers;
            const Token::Ptr m_initToken;
            const Token::Ptr m_leftBraceToken;
            const Token::Ptr m_rightBraceToken;
            FunctionDefinition::Ptr m_programFunction;
        };

        class ImportDefinition final : public Definition
        {
          public:
            using Ptr = std::shared_ptr< ImportDefinition >;

            ImportDefinition( const Token::Ptr& importToken, const IdentifierPath::Ptr& path );

            ImportDefinition(
                const Token::Ptr& importToken,
                const IdentifierPath::Ptr& path,
                const Token::Ptr& asToken,
                const Identifier::Ptr& identifier );

            const IdentifierPath::Ptr& path( void ) const;

            const Token::Ptr& importToken( void ) const;
            const Token::Ptr& asToken( void ) const;

            void accept( Visitor& visitor ) override final;

          private:
            const IdentifierPath::Ptr m_path;
            const Token::Ptr m_importToken;
            const Token::Ptr m_asToken;
        };
    }
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
