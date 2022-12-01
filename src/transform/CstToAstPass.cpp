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

#include "CstToAstPass.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/analyze/AttributionPass>
#include <libcasm-fe/ast/Declaration>
#include <libcasm-fe/ast/Expression>
#include <libcasm-fe/ast/Literal>
#include <libcasm-fe/cst/Declaration>
#include <libcasm-fe/cst/Literal>
#include <libcasm-fe/cst/Visitor>
#include <libcasm-fe/transform/SourceToCstPass>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/File>

#include <fstream>
#include <iostream>
#include <stack>

using namespace libcasm_fe;
using namespace CST;

char CstToAstPass::id = 0;

static libpass::PassRegistration< CstToAstPass > PASS(
    "CST To AST Pass", "transforms CST to AST representation", "cst2ast", 0 );

//
//
// CstToAstVisitor
//

namespace libcasm_fe
{
    namespace CST
    {
        class CstToAstVisitor final : public Visitor
        {
          public:
            CstToAstVisitor( libcasm_fe::Logger& log );

            AST::Root::Ptr transform( const Root::Ptr& node );

            void visit( Root& node ) override;

            void visit( HeaderDefinition& node ) override;
            void visit( InitDefinition& node ) override;
            void visit( VariableDefinition& node ) override;
            void visit( FunctionDefinition& node ) override;
            void visit( DerivedDefinition& node ) override;
            void visit( RuleDefinition& node ) override;
            void visit( EnumeratorDefinition& node ) override;
            void visit( EnumerationDefinition& node ) override;
            void visit( UsingDefinition& node ) override;
            void visit( UsingPathDefinition& node ) override;
            void visit( InvariantDefinition& node ) override;
            void visit( ImportDefinition& node ) override;
            void visit( DomainDefinition& node ) override;
            void visit( StructureDefinition& node ) override;
            void visit( BehaviorDefinition& node ) override;
            void visit( ImplementDefinition& node ) override;
            void visit( BuiltinDefinition& node ) override;
            void visit( Declaration& node ) override;

            void visit( ValueLiteral& node ) override;
            void visit( ReferenceLiteral& node ) override;
            void visit( UndefLiteral& node ) override;
            void visit( SetLiteral& node ) override;
            void visit( ListLiteral& node ) override;
            void visit( RangeLiteral& node ) override;
            void visit( TupleLiteral& node ) override;
            void visit( RecordLiteral& node ) override;

            void visit( AbstractExpression& node ) override;
            void visit( EmbracedExpression& node ) override;
            void visit( NamedExpression& node ) override;
            void visit( MappedExpression& node ) override;
            void visit( DirectCallExpression& node ) override;
            void visit( MethodCallExpression& node ) override;
            void visit( LiteralCallExpression& node ) override;
            void visit( IndirectCallExpression& node ) override;
            void visit( TypeCastingExpression& node ) override;
            void visit( UnaryExpression& node ) override;
            void visit( BinaryExpression& node ) override;
            void visit( LetExpression& node ) override;
            void visit( ConditionalExpression& node ) override;
            void visit( ChooseExpression& node ) override;
            void visit( UniversalQuantifierExpression& node ) override;
            void visit( ExistentialQuantifierExpression& node ) override;
            void visit( CardinalityExpression& node ) override;
            void visit( MatchExpression& node ) override;
            void visit( MatchArm& node ) override;

            void visit( SkipRule& node ) override;
            void visit( ConditionalRule& node ) override;
            void visit( CaseRule& node ) override;
            void visit( LetRule& node ) override;
            void visit( LocalRule& node ) override;
            void visit( ForallRule& node ) override;
            void visit( ChooseRule& node ) override;
            void visit( IterateRule& node ) override;
            void visit( BlockRule& node ) override;
            void visit( SequenceRule& node ) override;
            void visit( UpdateRule& node ) override;
            void visit( CallRule& node ) override;
            void visit( WhileRule& node ) override;

            void visit( UnresolvedType& node ) override;
            void visit( BasicType& node ) override;
            void visit( TupleType& node ) override;
            void visit( RecordType& node ) override;
            void visit( TemplateType& node ) override;
            void visit( FixedSizedType& node ) override;
            void visit( MappingType& node ) override;
            void visit( VaradicType& node ) override;
            void visit( RelationType& node ) override;

            void visit( Identifier& node ) override;
            void visit( IdentifierPath& node ) override;
            void visit( ExpressionCase& node ) override;
            void visit( DefaultCase& node ) override;
            void visit( VariableBinding& node ) override;

            void visit( BasicAttribute& node ) override;
            void visit( SymbolAttribute& node ) override;
            void visit( ExpressionAttribute& node ) override;

            void visit( Defined& node ) override;
            void visit( Initially& node ) override;

            void visit( Token& node ) override;
            void visit( Span& node ) override;

          private:
            template < typename T >
            typename T::Ptr fetch( const CST::Node::Ptr& node )
            {
                node->accept( *this );

                const auto search = m_ast.find( node.get() );
                if( search == m_ast.end() )
                {
                    const auto& msg = " unimplemented '" + node->description() + "'";
                    m_log.error( { node->sourceLocation() }, msg, Code::Internal );
                    return nullptr;
                }

                auto result = search->second;  // save element
                m_ast.erase( search );         // erase from buffer
                if( result )
                {
                    return result->ptr< T >();  // typed return
                }
                return nullptr;
            }

            template < typename T, typename A, typename C >
            typename T::Ptr fetch( const typename CST::NodeList< C >::Ptr& node )
            {
                const auto& list = AST::make< T >( node->sourceLocation() );
                for( const auto& nodeElement : *node )
                {
                    const auto& element = fetch< A >( nodeElement );
                    if( element )
                    {
                        list->add( element );
                    }
                }

                return list;
            }

            template < typename T, typename... Args >
            typename T::Ptr store( CST::Node& node, Args&&... args )
            {
                const auto& result =
                    AST::make< T >( node.sourceLocation(), std::forward< Args >( args )... );
                set( node, result );
                return result;
            }

            void set( CST::Node& node, const AST::Node::Ptr& result )
            {
                const auto check = m_ast.emplace( &node, result );
                if( not check.second )
                {
                    const auto& msg = " already transformed '" + node.description() + "'";
                    m_log.error( { node.sourceLocation() }, msg, Code::Internal );
                }
            }

          private:
            libcasm_fe::Logger& m_log;
            AST::Definitions::Ptr m_definitions;

            std::unordered_map< CST::Node*, AST::Node::Ptr > m_ast;
        };
    }
}

CstToAstVisitor::CstToAstVisitor( libcasm_fe::Logger& log )
: m_log( log )
, m_definitions()
{
}

AST::Root::Ptr CstToAstVisitor::transform( const Root::Ptr& node )
{
    node->accept( *this );
    return AST::make< AST::Root >( node->header()->sourceLocation(), m_definitions );
}

void CstToAstVisitor::visit( Root& node )
{
    const auto& definitions =
        fetch< AST::Definitions, AST::Definition, CST::Definition >( node.definitions() );
    m_definitions = definitions;
}

void CstToAstVisitor::visit( HeaderDefinition& node )
{
    assert( not " inconsistent state, invalid node to transform " );
}

void CstToAstVisitor::visit( InitDefinition& node )
{
    const auto& initializers =
        fetch< AST::MappedExpressions, AST::MappedExpression, CST::MappedExpression >(
            node.initializers() );

    const auto singleAgent = node.isSingleAgent();
    if( singleAgent )
    {
        const auto& location = node.sourceLocation();
        const auto& zeroLiteral = AST::make< AST::ValueLiteral >(
            location, std::make_shared< libcasm_ir::IntegerConstant >( 0 ) );
        const auto& programArguments = AST::make< AST::Expressions >( location );
        programArguments->add( zeroLiteral );

        const auto& initPath = fetch< AST::IdentifierPath >( node.initPath() );
        const auto& ruleReference = AST::make< AST::ReferenceLiteral >( location, initPath );
        const auto& initializer =
            AST::make< AST::MappedExpression >( location, programArguments, ruleReference );

        assert( initializers->size() == 0 and " inconsistent state " );
        initializers->add( initializer );
    }

    store< AST::InitDefinition >( node, initializers, singleAgent );
}

void CstToAstVisitor::visit( VariableDefinition& node )
{
    const auto& identifier = fetch< AST::Identifier >( node.identifier() );
    const auto& variableType = fetch< AST::Type >( node.variableType() );
    store< AST::VariableDefinition >( node, identifier, variableType );
}

void CstToAstVisitor::visit( FunctionDefinition& node )
{
    const auto& initially = node.initially()->expression();
    const auto& initiallyLocation = initially->sourceLocation();
    const auto& mappedExpressions = AST::make< AST::MappedExpressions >( initiallyLocation );

    if( initially->id() == CST::Node::ID::EMBRACED_EXPRESSION )
    {
        const auto& embracedExpression = initially->ptr< CST::EmbracedExpression >();
        const auto& value = fetch< AST::Expression >( embracedExpression->expression() );
        const auto& arguments = AST::make< AST::Expressions >( initiallyLocation );
        const auto& mappedExpression =
            AST::make< AST::MappedExpression >( initiallyLocation, arguments, value );
        mappedExpressions->add( mappedExpression );
    }
    else if( initially->id() == CST::Node::ID::SET_LITERAL )
    {
        const auto& setLiteral = initially->ptr< CST::SetLiteral >();
        const auto& setExpressions = setLiteral->expressions();
        for( auto const& setExpression : *setExpressions )
        {
            const auto& fetchExpression = fetch< AST::Expression >( setExpression );
            assert(
                fetchExpression->id() == AST::Node::ID::MAPPED_EXPRESSION and
                " inconsistent state @ GrammarParser " );
            const auto& mappedExpression = fetchExpression->template ptr< AST::MappedExpression >();
            mappedExpressions->add( mappedExpression );
        }
    }
    else if( initially->id() == CST::Node::ID::ABSTRACT_EXPRESSION )
    {
        const auto& value = fetch< AST::Expression >( initially );
        const auto& arguments = AST::make< AST::Expressions >( initiallyLocation );
        for( const auto& argumentType : *node.argumentTypes() )
        {
            arguments->add( value );
        }

        const auto& mappedExpression =
            AST::make< AST::MappedExpression >( initiallyLocation, arguments, value );
        mappedExpressions->add( mappedExpression );
    }
    else
    {
        assert( not " inconsistent state @ GrammarParser " );
    }

    const auto& identifier = fetch< AST::Identifier >( node.identifier() );
    const auto& argumentTypes = fetch< AST::Types, AST::Type, CST::Type >( node.argumentTypes() );
    const auto& returnType = fetch< AST::Type >( node.returnType() );
    const auto& defined = fetch< AST::Expression >( node.defined()->expression() );

    const auto& astNode = store< AST::FunctionDefinition >(
        node,
        identifier,
        argumentTypes,
        returnType,
        defined,
        mappedExpressions,
        node.classification(),
        node.symbolic() );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( DerivedDefinition& node )
{
    const auto& identifier = fetch< AST::Identifier >( node.identifier() );
    const auto& arguments =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.arguments() );
    const auto& returnType = fetch< AST::Type >( node.returnType() );
    const auto& expression = fetch< AST::Expression >( node.expression() );
    const auto& astNode =
        store< AST::DerivedDefinition >( node, identifier, arguments, returnType, expression );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( RuleDefinition& node )
{
    const auto& identifier = fetch< AST::Identifier >( node.identifier() );
    const auto& arguments =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.arguments() );
    const auto& returnType = fetch< AST::Type >( node.returnType() );
    const auto& rule = fetch< AST::Rule >( node.rule() );
    const auto& astNode =
        store< AST::RuleDefinition >( node, identifier, arguments, returnType, rule );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( EnumeratorDefinition& node )
{
    const auto& identifier = fetch< AST::Identifier >( node.identifier() );
    const auto& astNode = store< AST::EnumeratorDefinition >( node, identifier );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( EnumerationDefinition& node )
{
    const auto& identifier = fetch< AST::Identifier >( node.identifier() );
    const auto& enumerators =
        fetch< AST::Enumerators, AST::EnumeratorDefinition, CST::EnumeratorDefinition >(
            node.enumerators() );

    const auto& astNode = store< AST::EnumerationDefinition >( node, identifier, enumerators );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( UsingDefinition& node )
{
    const auto& identifier = fetch< AST::Identifier >( node.identifier() );
    const auto& aliasType = fetch< AST::Type >( node.aliasType() );
    const auto& astNode = store< AST::UsingDefinition >( node, identifier, aliasType );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( UsingPathDefinition& node )
{
    const auto& path = fetch< AST::IdentifierPath >( node.path() );
    const auto explicitSymbol = node.explicitSymbol();
    const auto& astNode = store< AST::UsingPathDefinition >( node, path, explicitSymbol );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( InvariantDefinition& node )
{
    const auto& identifier = fetch< AST::Identifier >( node.identifier() );
    const auto& expression = fetch< AST::Expression >( node.expression() );
    const auto& astNode = store< AST::InvariantDefinition >( node, identifier, expression );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( ImportDefinition& node )
{
    const auto& path = fetch< AST::IdentifierPath >( node.path() );
    AST::Identifier::Ptr identifier = nullptr;

    if( node.identifier() )
    {
        // use "as" identifier as definition symbol
        identifier = fetch< AST::Identifier >( node.identifier() );
    }
    else
    {
        // use the last identifier of the import path as definition symbol
        identifier = path->identifiers()->back();
    }

    const auto& astNode = store< AST::ImportDefinition >( node, path, identifier );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( DomainDefinition& node )
{
    const auto& templateSymbols =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.templateSymbols() );
    const auto& domainType = fetch< AST::Type >( node.domainType() );
    const auto& astNode = store< AST::DomainDefinition >( node, domainType );
    astNode->setTemplateSymbols( templateSymbols );
    astNode->setAbstract( node.abstract() );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( StructureDefinition& node )
{
    const auto& identifier = fetch< AST::Identifier >( node.identifier() );
    const auto& functions =
        fetch< AST::FunctionDefinitions, AST::FunctionDefinition, CST::FunctionDefinition >(
            node.functions() );
    const auto& templateSymbols =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.templateSymbols() );

    // create new domain type for structure identifier
    const auto& domainType = AST::make< AST::BasicType >(
        identifier->sourceLocation(), AST::IdentifierPath::fromIdentifier( identifier ) );

    // extend relation type of functions by adding the structure domainType as first argument
    for( const auto& function : *functions )
    {
        const auto& functionArgumentTypes = function->argumentTypes();
        functionArgumentTypes->add( functionArgumentTypes->begin(), domainType );
    }

    const auto& astNode = store< AST::StructureDefinition >( node, domainType, functions );
    astNode->setTemplateSymbols( templateSymbols );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( BehaviorDefinition& node )
{
    const auto& domainType = fetch< AST::Type >( node.domainType() );
    const auto& definitions =
        fetch< AST::Definitions, AST::Definition, CST::Definition >( node.definitions() );
    const auto& templateSymbols =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.templateSymbols() );

    const auto& astNode = store< AST::BehaviorDefinition >( node, domainType, definitions );
    astNode->setTemplateSymbols( templateSymbols );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( ImplementDefinition& node )
{
    const auto& domainType = fetch< AST::Type >( node.domainType() );
    const auto& definitions =
        fetch< AST::Definitions, AST::Definition, CST::Definition >( node.definitions() );
    const auto& templateSymbols =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.templateSymbols() );

    AST::Type::Ptr behaviorType = nullptr;
    if( node.hasBehavior() )
    {
        behaviorType = fetch< AST::Type >( node.behaviorType() );
    }
    else
    {
        behaviorType = domainType;
    }

    const auto& astNode =
        store< AST::ImplementDefinition >( node, behaviorType, domainType, definitions );
    astNode->setTemplateSymbols( templateSymbols );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( BuiltinDefinition& node )
{
    const auto& relationType = fetch< AST::RelationType >( node.domainType() );
    const auto& templateSymbols =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.templateSymbols() );

    const auto& identifier =
        AST::make< AST::Identifier >( node.sourceLocation(), relationType->name()->path() );
    const auto& argumentTypes = relationType->argumentTypes();
    const auto& returnType = relationType->returnType();

    const auto& astNode =
        store< AST::BuiltinDefinition >( node, identifier, argumentTypes, returnType );
    astNode->setTemplateSymbols( templateSymbols );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( Declaration& node )
{
    const auto& identifier = fetch< AST::Identifier >( node.identifier() );
    const auto& argumentTypes = fetch< AST::Types, AST::Type, CST::Type >( node.argumentTypes() );
    const auto& returnType = fetch< AST::Type >( node.returnType() );
    const auto kind = node.kind();
    const auto& astNode =
        store< AST::Declaration >( node, identifier, argumentTypes, returnType, kind );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void CstToAstVisitor::visit( UndefLiteral& node )
{
    store< AST::UndefLiteral >( node );
}

void CstToAstVisitor::visit( ValueLiteral& node )
{
    store< AST::ValueLiteral >( node, node.value() );
}

void CstToAstVisitor::visit( ReferenceLiteral& node )
{
    const auto& identifier = fetch< AST::IdentifierPath >( node.identifier() );
    store< AST::ReferenceLiteral >( node, identifier );
}

void CstToAstVisitor::visit( SetLiteral& node )
{
    const auto& expressions =
        fetch< AST::Expressions, AST::Expression, CST::Expression >( node.expressions() );
    store< AST::SetLiteral >( node, expressions );
}

void CstToAstVisitor::visit( ListLiteral& node )
{
    const auto& expressions =
        fetch< AST::Expressions, AST::Expression, CST::Expression >( node.expressions() );
    store< AST::ListLiteral >( node, expressions );
}

void CstToAstVisitor::visit( RangeLiteral& node )
{
    const auto& left = fetch< AST::Expression >( node.left() );
    const auto& right = fetch< AST::Expression >( node.right() );
    store< AST::RangeLiteral >( node, left, right );
}

void CstToAstVisitor::visit( TupleLiteral& node )
{
    const auto& expressions =
        fetch< AST::Expressions, AST::Expression, CST::Expression >( node.expressions() );
    store< AST::TupleLiteral >( node, expressions );
}

void CstToAstVisitor::visit( RecordLiteral& node )
{
    const auto& namedExpressions =
        fetch< AST::NamedExpressions, AST::NamedExpression, CST::NamedExpression >(
            node.namedExpressions() );
    store< AST::RecordLiteral >( node, namedExpressions );
}

void CstToAstVisitor::visit( AbstractExpression& node )
{
    store< AST::AbstractExpression >( node );
}

void CstToAstVisitor::visit( EmbracedExpression& node )
{
    const auto& expression = fetch< AST::Expression >( node.expression() );
    set( node, expression );
}

void CstToAstVisitor::visit( NamedExpression& node )
{
    const auto& identifier = fetch< AST::Identifier >( node.identifier() );
    const auto& expression = fetch< AST::Expression >( node.expression() );
    store< AST::NamedExpression >( node, identifier, expression );
}

void CstToAstVisitor::visit( MappedExpression& node )
{
    const auto& arguments =
        fetch< AST::Expressions, AST::Expression, CST::Expression >( node.arguments() );
    const auto& value = fetch< AST::Expression >( node.value() );
    store< AST::MappedExpression >( node, arguments, value );
}

void CstToAstVisitor::visit( DirectCallExpression& node )
{
    const auto& identifier = fetch< AST::IdentifierPath >( node.identifier() );
    const auto& arguments =
        fetch< AST::Expressions, AST::Expression, CST::Expression >( node.arguments() );
    store< AST::DirectCallExpression >( node, identifier, arguments );
}

void CstToAstVisitor::visit( MethodCallExpression& node )
{
    const auto& object = fetch< AST::Expression >( node.object() );
    const auto& methodName = fetch< AST::Identifier >( node.methodName() );
    const auto& arguments =
        fetch< AST::Expressions, AST::Expression, CST::Expression >( node.arguments() );
    store< AST::MethodCallExpression >( node, object, methodName, arguments );
}

void CstToAstVisitor::visit( LiteralCallExpression& node )
{
    const auto& object = fetch< AST::Expression >( node.object() );
    const auto& literal = fetch< AST::Literal >( node.literal() );
    store< AST::LiteralCallExpression >( node, object, literal );
}

void CstToAstVisitor::visit( CardinalityExpression& node )
{
    const auto& expression = fetch< AST::Expression >( node.expression() );
    store< AST::CardinalityExpression >( node, expression );
}

void CstToAstVisitor::visit( MatchExpression& node )
{
    // match scrutinee with
    // { pattern0 => expression0
    // , pattern1 => expression1
    // , ...
    // }
    // <=>
    // let s = scrutinee in
    // if  s = pattern0 then expression0 else
    // if  s = pattern1 then expression1 else
    // if  s = ... else
    // undef

    const auto& sourceLocation = node.sourceLocation();
    const auto& scrutinee = fetch< AST::Expression >( node.scrutinee() );

    const void* identifierAddress = static_cast< const void* >( &node );
    std::stringstream identifierStream;
    identifierStream << identifierAddress;
    std::string identifierName = "." + identifierStream.str();
    const auto& identifier = AST::make< AST::Identifier >( sourceLocation, identifierName );
    const auto& unresolvedType = AST::make< AST::UnresolvedType >( sourceLocation );

    const auto& variable =
        AST::make< AST::VariableDefinition >( sourceLocation, identifier, unresolvedType );
    const auto& variableBinding =
        AST::make< AST::VariableBinding >( sourceLocation, variable, scrutinee );
    const auto& variableBindings = AST::make< AST::VariableBindings >( sourceLocation );
    variableBindings->add( variableBinding );

    const auto& s = AST::make< AST::DirectCallExpression >(
        sourceLocation,
        AST::make< AST::IdentifierPath >( sourceLocation, identifier ),
        AST::make< AST::Expressions >( sourceLocation ) );

    AST::Expression::Ptr expression = AST::make< AST::UndefLiteral >( sourceLocation );

    const auto& begin = node.matchArms()->crbegin();
    const auto& end = node.matchArms()->crend();
    for( auto iterator = begin; iterator != end; iterator++ )
    {
        const auto& matchArm = *iterator;
        const auto& pattern = fetch< AST::Expression >( matchArm->pattern() );
        const auto& matchArmExpression = fetch< AST::Expression >( matchArm->expression() );

        const auto& condition =
            AST::make< AST::BinaryExpression >( sourceLocation, s, Grammar::Token::EQUAL, pattern );
        const auto& thenExpression = matchArmExpression;
        const auto& elseExpression = expression;

        expression = AST::make< AST::ConditionalExpression >(
            sourceLocation, condition, thenExpression, elseExpression );
    }

    store< AST::LetExpression >( node, variableBindings, expression );
}

void CstToAstVisitor::visit( MatchArm& node )
{
    assert( not " inconsistent state, invalid node to transform " );
}

void CstToAstVisitor::visit( IndirectCallExpression& node )
{
    const auto& expression = fetch< AST::Expression >( node.expression() );
    const auto& arguments =
        fetch< AST::Expressions, AST::Expression, CST::Expression >( node.arguments() );
    store< AST::IndirectCallExpression >( node, expression, arguments );
}

void CstToAstVisitor::visit( TypeCastingExpression& node )
{
    const auto& fromExpression = fetch< AST::Expression >( node.fromExpression() );
    const auto& asType = fetch< AST::Type >( node.asType() );
    store< AST::TypeCastingExpression >( node, fromExpression, asType );
}

void CstToAstVisitor::visit( UnaryExpression& node )
{
    const auto& expression = fetch< AST::Expression >( node.expression() );
    store< AST::UnaryExpression >( node, node.operationToken()->token(), expression );
}

void CstToAstVisitor::visit( BinaryExpression& node )
{
    const auto& left = fetch< AST::Expression >( node.left() );
    const auto& right = fetch< AST::Expression >( node.right() );
    store< AST::BinaryExpression >( node, left, node.operationToken()->token(), right );
}

void CstToAstVisitor::visit( LetExpression& node )
{
    const auto& expression = fetch< AST::Expression >( node.expression() );
    const auto& variableBindings =
        fetch< AST::VariableBindings, AST::VariableBinding, CST::VariableBinding >(
            node.variableBindings() );
    store< AST::LetExpression >( node, variableBindings, expression );
}

void CstToAstVisitor::visit( ConditionalExpression& node )
{
    const auto& condition = fetch< AST::Expression >( node.condition() );
    const auto& thenExpression = fetch< AST::Expression >( node.thenExpression() );
    const auto& elseExpression = fetch< AST::Expression >( node.elseExpression() );
    store< AST::ConditionalExpression >( node, condition, thenExpression, elseExpression );
}

void CstToAstVisitor::visit( ChooseExpression& node )
{
    const auto& variables =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.variables() );
    const auto& universe = fetch< AST::Expression >( node.universe() );
    const auto& expression = fetch< AST::Expression >( node.expression() );
    store< AST::ChooseExpression >( node, variables, universe, expression );
}

void CstToAstVisitor::visit( UniversalQuantifierExpression& node )
{
    const auto& predicateVariables =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.predicateVariables() );
    const auto& universe = fetch< AST::Expression >( node.universe() );
    const auto& proposition = fetch< AST::Expression >( node.proposition() );
    store< AST::UniversalQuantifierExpression >( node, predicateVariables, universe, proposition );
}

void CstToAstVisitor::visit( ExistentialQuantifierExpression& node )
{
    const auto& predicateVariables =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.predicateVariables() );
    const auto& universe = fetch< AST::Expression >( node.universe() );
    const auto& proposition = fetch< AST::Expression >( node.proposition() );
    store< AST::ExistentialQuantifierExpression >(
        node, predicateVariables, universe, proposition );
}

void CstToAstVisitor::visit( SkipRule& node )
{
    store< AST::SkipRule >( node );
}

void CstToAstVisitor::visit( ConditionalRule& node )
{
    const auto& condition = fetch< AST::Expression >( node.condition() );
    const auto& thenRule = fetch< AST::Rule >( node.thenRule() );
    const auto& elseRule = fetch< AST::Rule >( node.elseRule() );
    store< AST::ConditionalRule >( node, condition, thenRule, elseRule );
    if( node.elseToken()->token() == Grammar::Token::UNRESOLVED )
    {
        assert( elseRule->id() == AST::Node::ID::SKIP_RULE );
    }
}

void CstToAstVisitor::visit( CaseRule& node )
{
    const auto& expression = fetch< AST::Expression >( node.expression() );
    const auto& cases = fetch< AST::Cases, AST::Case, CST::Case >( node.cases() );
    store< AST::CaseRule >( node, expression, cases );
}

void CstToAstVisitor::visit( LetRule& node )
{
    const auto& variableBindings =
        fetch< AST::VariableBindings, AST::VariableBinding, CST::VariableBinding >(
            node.variableBindings() );
    const auto& rule = fetch< AST::Rule >( node.rule() );
    store< AST::LetRule >( node, variableBindings, rule );
}

void CstToAstVisitor::visit( LocalRule& node )
{
    const auto& localFunctions =
        fetch< AST::FunctionDefinitions, AST::FunctionDefinition, CST::FunctionDefinition >(
            node.localFunctions() );
    const auto& rule = fetch< AST::Rule >( node.rule() );
    store< AST::LocalRule >( node, localFunctions, rule );
}

void CstToAstVisitor::visit( ForallRule& node )
{
    const auto& variables =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.variables() );
    const auto& universe = fetch< AST::Expression >( node.universe() );
    const auto& condition = fetch< AST::Expression >( node.condition() );
    const auto& rule = fetch< AST::Rule >( node.rule() );
    store< AST::ForallRule >( node, variables, universe, condition, rule );
}

void CstToAstVisitor::visit( ChooseRule& node )
{
    const auto& variables =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.variables() );
    const auto& universe = fetch< AST::Expression >( node.universe() );
    const auto& rule = fetch< AST::Rule >( node.rule() );
    store< AST::ChooseRule >( node, variables, universe, rule );
}

void CstToAstVisitor::visit( IterateRule& node )
{
    const auto& rule = fetch< AST::Rule >( node.rule() );
    store< AST::IterateRule >( node, rule );
}

void CstToAstVisitor::visit( BlockRule& node )
{
    const auto& rules = fetch< AST::Rules, AST::Rule, CST::Rule >( node.rules() );
    store< AST::BlockRule >( node, rules );
}

void CstToAstVisitor::visit( SequenceRule& node )
{
    const auto& rules = fetch< AST::Rules, AST::Rule, CST::Rule >( node.rules() );
    store< AST::SequenceRule >( node, rules );
}

void CstToAstVisitor::visit( UpdateRule& node )
{
    const auto& function = fetch< AST::CallExpression >( node.function() );
    const auto& expression = fetch< AST::Expression >( node.expression() );
    store< AST::UpdateRule >( node, function, expression );
}

void CstToAstVisitor::visit( CallRule& node )
{
    const auto& call = fetch< AST::CallExpression >( node.call() );
    store< AST::CallRule >( node, call );
}

void CstToAstVisitor::visit( WhileRule& node )
{
    // while <Term> do <Rule>
    // <=>
    // iterate
    //   if not <Term> then
    //     skip
    //   else
    //     <Rule>
    //

    const auto& term = fetch< AST::Expression >( node.condition() );
    const auto& rule = fetch< AST::Rule >( node.rule() );

    const auto& location = node.sourceLocation();
    const auto& notTerm = AST::make< AST::UnaryExpression >( location, Grammar::Token::NOT, term );
    const auto& skipRule = AST::make< AST::SkipRule >( location );
    const auto& conditionalRule =
        AST::make< AST::ConditionalRule >( location, notTerm, skipRule, rule );
    store< AST::IterateRule >( node, conditionalRule );
}

void CstToAstVisitor::visit( UnresolvedType& node )
{
    store< AST::UnresolvedType >( node );
}

void CstToAstVisitor::visit( BasicType& node )
{
    const auto& name = fetch< AST::IdentifierPath >( node.name() );
    store< AST::BasicType >( node, name );
}

void CstToAstVisitor::visit( TupleType& node )
{
    const auto& subTypes = fetch< AST::Types, AST::Type, CST::Type >( node.subTypes() );
    store< AST::TupleType >( node, subTypes );
}

void CstToAstVisitor::visit( RecordType& node )
{
    const auto& namedSubTypes =
        fetch< AST::VariableDefinitions, AST::VariableDefinition, CST::VariableDefinition >(
            node.namedSubTypes() );
    store< AST::RecordType >( node, namedSubTypes );
}

void CstToAstVisitor::visit( TemplateType& node )
{
    const auto& identifier = fetch< AST::IdentifierPath >( node.name() );
    const auto& subTypes = fetch< AST::Types, AST::Type, CST::Type >( node.subTypes() );
    store< AST::TemplateType >( node, identifier, subTypes );
}

void CstToAstVisitor::visit( FixedSizedType& node )
{
    const auto& identifier = fetch< AST::IdentifierPath >( node.name() );
    const auto& size = fetch< AST::Expression >( node.size() );
    store< AST::FixedSizedType >( node, identifier, size );
}

void CstToAstVisitor::visit( MappingType& node )
{
    const auto& identifier = fetch< AST::IdentifierPath >( node.name() );
    const auto& argumentTypes = fetch< AST::Types, AST::Type, CST::Type >( node.argumentTypes() );
    const auto& returnType = fetch< AST::Type >( node.returnType() );
    store< AST::RelationType >( node, identifier, argumentTypes, returnType );
}

void CstToAstVisitor::visit( RelationType& node )
{
    const auto& identifier = fetch< AST::IdentifierPath >( node.name() );
    const auto& argumentTypes = fetch< AST::Types, AST::Type, CST::Type >( node.argumentTypes() );
    const auto& returnType = fetch< AST::Type >( node.returnType() );
    store< AST::RelationType >( node, identifier, argumentTypes, returnType );
}

void CstToAstVisitor::visit( VaradicType& node )
{
    // varadic type maps to template type of 0 arguments, because the are resolved later
    const auto& identifier = fetch< AST::IdentifierPath >( node.name() );
    const auto& subTypes = AST::make< AST::Types >( node.sourceLocation() );
    store< AST::TemplateType >( node, identifier, subTypes );
}

void CstToAstVisitor::visit( Identifier& node )
{
    store< AST::Identifier >( node, node.name() );
}

void CstToAstVisitor::visit( IdentifierPath& node )
{
    const auto& identifiers =
        fetch< AST::Identifiers, AST::Identifier, CST::Identifier >( node.identifiers() );
    store< AST::IdentifierPath >( node, identifiers );
}

void CstToAstVisitor::visit( ExpressionCase& node )
{
    const auto& expression = fetch< AST::Expression >( node.expression() );
    const auto& rule = fetch< AST::Rule >( node.rule() );
    store< AST::ExpressionCase >( node, expression, rule );
}

void CstToAstVisitor::visit( DefaultCase& node )
{
    const auto& rule = fetch< AST::Rule >( node.rule() );
    store< AST::DefaultCase >( node, rule );
}

void CstToAstVisitor::visit( VariableBinding& node )
{
    const auto& variable = fetch< AST::VariableDefinition >( node.variable() );
    const auto& expression = fetch< AST::Expression >( node.expression() );
    store< AST::VariableBinding >( node, variable, expression );
}

void CstToAstVisitor::visit( BasicAttribute& node )
{
    assert( not " inconsistent state, invalid node to transform " );
}

void CstToAstVisitor::visit( SymbolAttribute& node )
{
    assert( not " inconsistent state, invalid node to transform " );
}

void CstToAstVisitor::visit( ExpressionAttribute& node )
{
    assert( not " inconsistent state, invalid node to transform " );
}

void CstToAstVisitor::visit( Defined& node )
{
    assert( not " inconsistent state, invalid node to transform " );
}

void CstToAstVisitor::visit( Initially& node )
{
    assert( not " inconsistent state, invalid node to transform " );
}

void CstToAstVisitor::visit( Token& node )
{
    assert( not " inconsistent state, invalid node to transform " );
}

void CstToAstVisitor::visit( Span& node )
{
    assert( not " inconsistent state, invalid node to transform " );
}

//
//
// CstToAstPass
//

void CstToAstPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToCstPass >();
    pu.scheduleAfter< AttributionPass >();
}

u1 CstToAstPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto& data = pr.output< SourceToCstPass >();
    const auto& specification = data->specification();

    CstToAstVisitor visitor{ log };
    const auto& ast = visitor.transform( specification->cst() );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "symbol table =\n" + specification->symboltable()->dump() );
        log.debug( "found %lu error(s) during transformation", errors );
        return false;
    }

    const auto& transformedSpecification = std::make_shared< Specification >();
    transformedSpecification->setAsmType( specification->asmType() );
    transformedSpecification->setLocation( specification->location() );
    transformedSpecification->setSymboltable( specification->symboltable() );
    transformedSpecification->setAst( ast );

    pr.setOutput< CstToAstPass >( transformedSpecification );
    return true;
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
