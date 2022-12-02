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

#include "TemplatingPass.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/analyze/SymbolRegistrationPass>
#include <libcasm-fe/analyze/SymbolResolverPass>
#include <libcasm-fe/ast/Declaration>
#include <libcasm-fe/ast/Literal>
#include <libcasm-fe/ast/Visitor>
#include <libcasm-fe/import/SpecificationMergerPass>
#include <libcasm-fe/transform/CstToAstPass>
#include <libcasm-fe/transform/SourceToCstPass>

#include <libpass/PassManager>
#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

using namespace libcasm_fe;
using namespace AST;

char TemplatingPass::id = 0;

static libpass::PassRegistration< TemplatingPass > PASS(
    "Templating Pass", "type check of all types in the AST representation", "ast-type-chk", 0 );

//
//
// TemplatingVisitor
//

namespace libcasm_fe
{
    namespace AST
    {
        class TemplatingVisitor final : public Visitor
        {
          public:
            TemplatingVisitor(
                libcasm_fe::Logger& log,
                const Type::Ptr& templateType,
                const Type::Ptr& fromType = nullptr,
                const Type::Ptr& toType = nullptr );

            void visit( Root& node ) override;

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

            void visit( UnresolvedType& node ) override;
            void visit( BasicType& node ) override;
            void visit( TupleType& node ) override;
            void visit( RecordType& node ) override;
            void visit( TemplateType& node ) override;
            void visit( FixedSizedType& node ) override;
            void visit( RelationType& node ) override;

            void visit( Identifier& node ) override;
            void visit( IdentifierPath& node ) override;
            void visit( ExpressionCase& node ) override;
            void visit( DefaultCase& node ) override;
            void visit( VariableBinding& node ) override;
            void visit( VariableSelection& node ) override;

            const Definitions::Ptr& definitions( void ) const;

          private:
            template < typename T >
            typename T::Ptr fetch( const Node::Ptr& node )
            {
                node->accept( *this );

                const auto search = m_lst.find( node.get() );
                if( search == m_lst.end() )
                {
                    const auto& msg = " unimplemented '" + node->description() + "'";
                    m_log.error( { node->sourceLocation() }, msg, Code::Internal );
                    return nullptr;
                }

                auto result = search->second;  // save element
                m_lst.erase( search );         // erase from buffer
                return result->ptr< T >();     // typed return
            }

            template < typename T, typename E >
            typename T::Ptr fetch( const typename NodeList< E >::Ptr& node )
            {
                const auto& list = make< T >( node->sourceLocation() );
                for( const auto& nodeElement : *node )
                {
                    const auto& element = fetch< E >( nodeElement );
                    list->add( element );
                }

                return list;
            }

            template < typename T, typename... Args >
            typename T::Ptr store( Node& node, Args&&... args )
            {
                const auto& result =
                    AST::make< T >( node.sourceLocation(), std::forward< Args >( args )... );
                set( node, result );
                return result;
            }

            void set( Node& node, const Node::Ptr& result )
            {
                const auto check = m_lst.emplace( &node, result );
                if( not check.second )
                {
                    const auto& msg = " already transformed '" + node.description() + "'";
                    m_log.error( { node.sourceLocation() }, msg, Code::Internal );
                }
            }

          private:
            libcasm_fe::Logger& m_log;
            const Type::Ptr m_templateType;
            const Type::Ptr m_fromType;
            const Type::Ptr m_toType;
            Definitions::Ptr m_definitions;
            TypeDefinition::Ptr m_objectDefinition;

            std::unordered_map< Node*, Node::Ptr > m_lst;
        };
    }
}

TemplatingVisitor::TemplatingVisitor(
    libcasm_fe::Logger& log,
    const Type::Ptr& templateType,
    const Type::Ptr& fromType,
    const Type::Ptr& toType )
: m_log( log )
, m_templateType( templateType )
, m_fromType( fromType )
, m_toType( toType )
, m_definitions( std::make_shared< Definitions >() )
, m_objectDefinition()
{
}

void TemplatingVisitor::visit( Root& node )
{
}

void TemplatingVisitor::visit( InitDefinition& node )
{
}

void TemplatingVisitor::visit( VariableDefinition& node )
{
    const auto& identifier = fetch< Identifier >( node.identifier() );

    Type::Ptr variableType = nullptr;
    if( m_fromType and m_toType and ( identifier->name() == "this" ) )
    {
        variableType = fetch< Type >( m_toType );
    }
    else if(
        m_fromType and m_toType and
        ( m_fromType->signature() == node.variableType()->signature() ) )
    {
        variableType = fetch< Type >( m_toType );
    }
    else
    {
        variableType = fetch< Type >( node.variableType() );
    }

    store< VariableDefinition >( node, identifier, variableType );
}

void TemplatingVisitor::visit( FunctionDefinition& node )
{
}

void TemplatingVisitor::visit( DerivedDefinition& node )
{
    const auto& identifier = fetch< Identifier >( node.identifier() );
    const auto& arguments = fetch< VariableDefinitions, VariableDefinition >( node.arguments() );
    const auto& returnType = fetch< Type >( node.returnType() );
    const auto& expression = fetch< Expression >( node.expression() );
    const auto& astNode =
        store< DerivedDefinition >( node, identifier, arguments, returnType, expression );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );

    m_definitions->add( astNode );
}

void TemplatingVisitor::visit( RuleDefinition& node )
{
    const auto& identifier = fetch< Identifier >( node.identifier() );
    const auto& arguments = fetch< VariableDefinitions, VariableDefinition >( node.arguments() );
    const auto& returnType = fetch< Type >( node.returnType() );
    const auto& rule = fetch< Rule >( node.rule() );
    const auto& astNode = store< RuleDefinition >( node, identifier, arguments, returnType, rule );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );

    m_definitions->add( astNode );
}

void TemplatingVisitor::visit( EnumeratorDefinition& node )
{
}

void TemplatingVisitor::visit( EnumerationDefinition& node )
{
}

void TemplatingVisitor::visit( UsingDefinition& node )
{
}

void TemplatingVisitor::visit( UsingPathDefinition& node )
{
}

void TemplatingVisitor::visit( InvariantDefinition& node )
{
}

void TemplatingVisitor::visit( ImportDefinition& node )
{
}

void TemplatingVisitor::visit( DomainDefinition& node )
{
    const auto& domainType = fetch< Type >( node.domainType() );
    // const auto& templateSymbols =
    //     fetch< VariableDefinitions, VariableDefinition >( node.templateSymbols() );

    const auto& astNode = store< DomainDefinition >( node, domainType );
    // astNode->setTemplateSymbols( templateSymbols );
    astNode->setAbstract( node.abstract() );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );

    m_definitions->add( astNode );

    m_objectDefinition = astNode;
    domainType->setTypeDefinition( astNode );

    if( node.basicBehavior() )
    {
        const auto& basicBehavior = fetch< ImplementDefinition >( node.basicBehavior() );
        m_definitions->add( basicBehavior );
    }

    for( const auto& element : node.extendedBehaviors() )
    {
        const auto& extendedBehavior = fetch< ImplementDefinition >( element.second );
        m_definitions->add( extendedBehavior );
    }
}

void TemplatingVisitor::visit( StructureDefinition& node )
{
}

void TemplatingVisitor::visit( BehaviorDefinition& node )
{
    const auto& domainType = fetch< Type >( node.domainType() );
    const auto& definitions = fetch< Definitions, Definition >( node.definitions() );
    // const auto& templateSymbols =
    //     fetch< VariableDefinitions, VariableDefinition >(
    //         node.templateSymbols() );

    const auto& astNode = store< BehaviorDefinition >( node, domainType, definitions );
    // astNode->setTemplateSymbols( templateSymbols );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );

    for( const auto& definition : *node.definitions() )
    {
        if( definition->id() == Node::ID::DECLARATION )
        {
            continue;
        }

        m_definitions->add( definition );
    }
}

void TemplatingVisitor::visit( ImplementDefinition& node )
{
    Type::Ptr domainType = fetch< Type >( node.domainType() );
    if( m_fromType and m_toType and ( m_fromType->signature() == node.domainType()->signature() ) )
    {
        domainType = fetch< Type >( m_toType );
    }

    const auto& definitions = fetch< Definitions, Definition >( node.definitions() );
    // const auto& templateSymbols =
    //     fetch< VariableDefinitions, VariableDefinition >( node.templateSymbols() );

    Type::Ptr behaviorType = nullptr;
    if( node.forBehaviorType() )
    {
        behaviorType = fetch< Type >( node.behaviorType() );
    }
    else
    {
        behaviorType = domainType;
    }

    const auto& astNode =
        store< ImplementDefinition >( node, behaviorType, domainType, definitions );
    // astNode->setTemplateSymbols( templateSymbols );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );

    m_definitions->add( astNode );
}

void TemplatingVisitor::visit( BuiltinDefinition& node )
{
}

void TemplatingVisitor::visit( Declaration& node )
{
    const auto& identifier = fetch< Identifier >( node.identifier() );
    const auto& argumentTypes = fetch< Types, Type >( node.argumentTypes() );
    const auto& returnType = fetch< Type >( node.returnType() );
    const auto& kind = node.kind();
    const auto& astNode = store< Declaration >( node, identifier, argumentTypes, returnType, kind );
    astNode->setExported( node.exported() );
    astNode->setProperties( node.properties() );
}

void TemplatingVisitor::visit( UndefLiteral& node )
{
}

void TemplatingVisitor::visit( ValueLiteral& node )
{
}

void TemplatingVisitor::visit( ReferenceLiteral& node )
{
}

void TemplatingVisitor::visit( SetLiteral& node )
{
}

void TemplatingVisitor::visit( ListLiteral& node )
{
}

void TemplatingVisitor::visit( RangeLiteral& node )
{
}

void TemplatingVisitor::visit( TupleLiteral& node )
{
}

void TemplatingVisitor::visit( RecordLiteral& node )
{
}

void TemplatingVisitor::visit( AbstractExpression& node )
{
}

void TemplatingVisitor::visit( NamedExpression& node )
{
}

void TemplatingVisitor::visit( MappedExpression& node )
{
}

void TemplatingVisitor::visit( DirectCallExpression& node )
{
    const auto& identifier = fetch< IdentifierPath >( node.identifier() );
    const auto& arguments = fetch< Expressions, Expression >( node.arguments() );
    store< DirectCallExpression >( node, identifier, arguments );
}

void TemplatingVisitor::visit( MethodCallExpression& node )
{
    const auto& object = fetch< Expression >( node.object() );
    const auto& methodName = fetch< Identifier >( node.methodName() );
    const auto& methodArguments = fetch< Expressions, Expression >( node.methodArguments() );
    store< MethodCallExpression >( node, object, methodName, methodArguments );
}

void TemplatingVisitor::visit( LiteralCallExpression& node )
{
}

void TemplatingVisitor::visit( IndirectCallExpression& node )
{
}

void TemplatingVisitor::visit( TypeCastingExpression& node )
{
}

void TemplatingVisitor::visit( UnaryExpression& node )
{
    const auto& expression = fetch< Expression >( node.expression() );
    store< UnaryExpression >( node, node.operationToken(), expression );
}

void TemplatingVisitor::visit( BinaryExpression& node )
{
    const auto& left = fetch< Expression >( node.left() );
    const auto& right = fetch< Expression >( node.right() );
    store< BinaryExpression >( node, left, node.operationToken(), right );
}

void TemplatingVisitor::visit( LetExpression& node )
{
}

void TemplatingVisitor::visit( ConditionalExpression& node )
{
}

void TemplatingVisitor::visit( ChooseExpression& node )
{
}

void TemplatingVisitor::visit( UniversalQuantifierExpression& node )
{
}

void TemplatingVisitor::visit( ExistentialQuantifierExpression& node )
{
}

void TemplatingVisitor::visit( CardinalityExpression& node )
{
}

void TemplatingVisitor::visit( SkipRule& node )
{
    store< SkipRule >( node );
}

void TemplatingVisitor::visit( ConditionalRule& node )
{
}

void TemplatingVisitor::visit( CaseRule& node )
{
}

void TemplatingVisitor::visit( LetRule& node )
{
}

void TemplatingVisitor::visit( LocalRule& node )
{
}

void TemplatingVisitor::visit( ForallRule& node )
{
}

void TemplatingVisitor::visit( ChooseRule& node )
{
}

void TemplatingVisitor::visit( IterateRule& node )
{
}

void TemplatingVisitor::visit( BlockRule& node )
{
}

void TemplatingVisitor::visit( SequenceRule& node )
{
    // const auto& rules = fetch< Rules, Rule, AST::Rule >( node.rules() );
    // store< SequenceRule >( node, rules );
}

void TemplatingVisitor::visit( UpdateRule& node )
{
    // const auto& function = fetch< CallExpression >( node.function() );
    // const auto& expression = fetch< Expression >( node.expression() );
    // store< UpdateRule >( node, function, expression );
}

void TemplatingVisitor::visit( CallRule& node )
{
    // const auto& call = fetch< CallExpression >( node.call() );
    // store< CallRule >( node, call );
}

void TemplatingVisitor::visit( UnresolvedType& node )
{
}

void TemplatingVisitor::visit( BasicType& node )
{
    const auto& name = fetch< IdentifierPath >( node.name() );
    store< BasicType >( node, name );
}

void TemplatingVisitor::visit( TupleType& node )
{
    // const auto& subTypes = fetch< Types, Type, AST::Type >( node.subTypes() );
    // store< TupleType >( node, subTypes );
}

void TemplatingVisitor::visit( RecordType& node )
{
    // const auto& namedSubTypes =
    //     fetch< VariableDefinitions, VariableDefinition, AST::VariableDefinition >(
    //         node.namedSubTypes() );
    // store< RecordType >( node, namedSubTypes );
}

void TemplatingVisitor::visit( TemplateType& node )
{
    if( m_templateType and node.name()->baseName() == m_templateType->name()->baseName() and
        node.signature() != m_templateType->signature() )
    {
        if( m_templateType->id() != Node::ID::RELATION_TYPE )
        {
            m_log.error(
                { node.sourceLocation() },
                "unsupported " + node.description() + " '" + node.signature() + "' ==> " +
                    m_templateType->description() + " '" + m_templateType->signature() + "'",
                Code::Unspecified );
            return;
        }
        const auto& templateType = static_cast< RelationType& >( *m_templateType );
        const auto& identifier = fetch< IdentifierPath >( templateType.name() );
        const auto& argumentTypes = fetch< Types, Type >( templateType.argumentTypes() );
        const auto& returnType = fetch< Type >( templateType.returnType() );
        const auto& astNode = AST::make< RelationType >(
            templateType.sourceLocation(), identifier, argumentTypes, returnType );
        if( m_objectDefinition )
        {
            astNode->setTypeDefinition( m_objectDefinition );
        }
        set( node, astNode );
    }
    else
    {
        const auto& identifier = fetch< IdentifierPath >( node.name() );
        const auto& subTypes = fetch< Types, Type >( node.subTypes() );
        store< TemplateType >( node, identifier, subTypes );
    }
}

void TemplatingVisitor::visit( FixedSizedType& node )
{
    // const auto& identifier = fetch< IdentifierPath >( node.name() );
    // const auto& size = fetch< Expression >( node.size() );
    // store< FixedSizedType >( node, identifier, size );
}

void TemplatingVisitor::visit( RelationType& node )
{
    const auto& identifier = fetch< IdentifierPath >( node.name() );
    const auto& argumentTypes = fetch< Types, Type >( node.argumentTypes() );
    const auto& returnType = fetch< Type >( node.returnType() );
    store< RelationType >( node, identifier, argumentTypes, returnType );
}

void TemplatingVisitor::visit( Identifier& node )
{
    store< Identifier >( node, node.name() );
}

void TemplatingVisitor::visit( IdentifierPath& node )
{
    const auto& identifiers = fetch< Identifiers, Identifier >( node.identifiers() );
    store< IdentifierPath >( node, identifiers );
}

void TemplatingVisitor::visit( ExpressionCase& node )
{
}

void TemplatingVisitor::visit( DefaultCase& node )
{
}

void TemplatingVisitor::visit( VariableBinding& node )
{
}

void TemplatingVisitor::visit( VariableSelection& node )
{
}

const Definitions::Ptr& TemplatingVisitor::definitions( void ) const
{
    return m_definitions;
}

//
//
// TemplatingPass
//

void TemplatingPass::usage( libpass::PassUsage& pu )
{
    pu.require< CstToAstPass >();
    pu.scheduleAfter< SymbolResolverPass >();
}

u1 TemplatingPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto& data = pr.output< CstToAstPass >();
    const auto& specification = data->specification();
    auto& symboltable = *specification->symboltable();

    const auto& symbolData = pr.output< SymbolResolverPass >();
    const auto& templateTypes = symbolData->templateTypes();
    const auto& templateDefinitions = symbolData->templateDefinitions();

    const auto& definitions = std::make_shared< Definitions >();
    for( const auto& templateType : *templateTypes )
    {
        TemplatingVisitor visitor( log, templateType );
        templateType->typeDefinition()->accept( visitor );

        for( const auto& definition : *visitor.definitions() )
        {
            if( not definition )
            {
                log.error(
                    { templateType->sourceLocation() },
                    "unable to resolve " + templateType->description() + " '" +
                        templateType->signature() + "'",
                    Code::Unspecified );
                continue;
            }

            definitions->add( definition );
        }
    }

    const auto& enumerationSymbol = symboltable.findSymbol( TypeInfo::TYPE_NAME_ENUMERATION );
    assert( enumerationSymbol and " inconsistent state " );
    assert( enumerationSymbol->id() == Node::ID::DOMAIN_DEFINITION );
    const auto& enumerationDefinition = enumerationSymbol->ptr< DomainDefinition >();

    for( const auto& templateDefinition : *templateDefinitions )
    {
        assert( templateDefinition->id() == Node::ID::ENUMERATION_DEFINITION );
        const auto templateEnumerationDefinition =
            templateDefinition->ptr< EnumerationDefinition >();

        for( const auto it : enumerationDefinition->extendedBehaviors() )
        {
            const auto& definition = it.second;
            assert( definition->id() == Node::ID::IMPLEMENT_DEFINITION );
            const auto& implementDefinition = definition->ptr< ImplementDefinition >();

            const auto& definitionInstance = TemplatingPass::duplicate(
                log,
                implementDefinition,
                implementDefinition->domainType(),
                templateEnumerationDefinition->domainType() );

            definitions->add( definitionInstance );
        }
    }

    const auto& initSymbol = symboltable.findSymbol( "init" );
    if( initSymbol )
    {
        assert( initSymbol->id() == Node::ID::INIT_DEFINITION );
        const auto& initDefinition = initSymbol->ptr< InitDefinition >();

        const auto& agentDomainSymbol = symboltable.findSymbol( TypeInfo::TYPE_NAME_AGENT );
        assert( agentDomainSymbol and " inconsistent state @ SymbolResolverPass " );

        if( initDefinition->singleAgent() )
        {
            const auto& agentLocation = agentDomainSymbol->sourceLocation();
            const auto& agentIdentifier =
                AST::make< Identifier >( agentLocation, TypeInfo::TYPE_NAME_AGENT );
            const auto& agentDomainType = AST::make< BasicType >(
                agentLocation,
                IdentifierPath::fromIdentifier(
                    AST::make< Identifier >( agentLocation, TypeInfo::TYPE_NAME_INTEGER ) ) );
            const auto& agentUsingDefinition = AST::make< UsingDefinition >(
                initDefinition->sourceLocation(), agentIdentifier, agentDomainType );
            definitions->add( agentUsingDefinition );
        }
    }

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "symbol table =\n" + symboltable.dump() );
        log.debug( "found %lu error(s) during visiting templates", errors );
        return false;
    }

    const auto& templateSpecification = std::make_shared< Specification >();
    templateSpecification->setAsmType( specification->asmType() );
    templateSpecification->setLocation( specification->location() );
    templateSpecification->setSymboltable( specification->symboltable() );

    const auto& templateAst = std::make_shared< AST::Root >( definitions );
    templateSpecification->setAst( templateAst );

    libpass::PassResult passResult;
    passResult.setOutput< CstToAstPass >( templateSpecification );

    SymbolRegistrationPass symbolRegistrationPass;
    if( not symbolRegistrationPass.run( passResult ) )
    {
        log.debug( "found %lu error(s) during templating symbol registration", log.errors() );
        return false;
    }

    const auto& astDefinitions = specification->ast()->definitions();

    for( const auto& definition : *definitions )
    {
        astDefinitions->add( definition );
    }

    SymbolResolverPass symbolResolverPass;
    if( not symbolResolverPass.run( passResult ) )
    {
        log.debug( "found %lu error(s) during templating symbol resolving", log.errors() );
        return false;
    }

    assert( passResult.hasOutput< SymbolResolverPass >() );
    const auto& passData = passResult.output< SymbolResolverPass >();
    const auto& passTemplateTypes = passData->templateTypes();
    log.debug( "remaining templates type size %lu", passTemplateTypes->size() );
    return true;
}

AST::Definition::Ptr TemplatingPass::duplicate(
    libcasm_fe::Logger& log,
    const AST::Definition::Ptr& node,
    const AST::Type::Ptr& from,
    const AST::Type::Ptr& to )
{
    TemplatingVisitor visitor( log, nullptr, from, to );
    node->accept( visitor );

    if( visitor.definitions()->size() < 1 )
    {
        log.error(
            { node->sourceLocation() },
            "unable to duplicate " + node->description(),
            Code::Unspecified );
        return nullptr;
    }

    return visitor.definitions()->back();
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
