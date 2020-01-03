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

#include "SymbolResolverPass.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/analyze/SymbolRegistrationPass>
#include <libcasm-fe/import/LibraryLoaderPass>
#include <libcasm-fe/import/SpecificationMergerPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libcasm-ir/Builtin>
#include <libcasm-ir/Instruction>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <unordered_map>

using namespace libcasm_fe;
using namespace Ast;

char SymbolResolverPass::id = 0;

static libpass::PassRegistration< SymbolResolverPass > PASS(
    "ASTSymbolResolverPass",
    "resolves AST identifiers of type-, call-, ... nodes",
    "ast-sym-resolve",
    0 );

//
//
// NamespaceResolveVisitor
//

class NamespaceResolveVisitor final : public RecursiveVisitor
{
  public:
    NamespaceResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

    void visit( UsingPathDefinition& node ) override;

  private:
    void registerSymbolWithPath(
        UsingPathDefinition& node, const IdentifierPath& path, const u1 useAll = false );

  private:
    libcasm_fe::Logger& m_log;
    Namespace& m_symboltable;
};

NamespaceResolveVisitor::NamespaceResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

void NamespaceResolveVisitor::visit( UsingPathDefinition& node )
{
    const auto& location = node.sourceLocation();
    const auto& path = *node.path();
    const auto& name = path.baseName();
    const auto& pathName = path.path();

    if( node.explicitSymbol() )
    {
        registerSymbolWithPath( node, path );
    }
    else
    {
        const auto usingNamespace = m_symboltable.findNamespace( path );
        if( not usingNamespace )
        {
            m_log.error(
                { node.sourceLocation() },
                "unable to resolve namespace '" + pathName + "'",
                Code::SymbolIsUnknown );
            return;
        }

        for( const auto& namespaceSymbol : usingNamespace->symbols() )
        {
            const auto& name = namespaceSymbol.first;
            const auto symbolName =
                Ast::make< Identifiers >( location, path.identifiers()->data() );
            symbolName->add( Ast::make< Identifier >( location, name ) );
            const IdentifierPath symbolPath( symbolName );

            registerSymbolWithPath( node, symbolPath, true );
        }
    }
}

void NamespaceResolveVisitor::registerSymbolWithPath(
    UsingPathDefinition& node, const IdentifierPath& path, const u1 useAll )
{
    const auto& name = path.baseName();
    const auto& pathName = path.path();

    const auto& symbol = m_symboltable.findSymbol( path );
    const auto definition = symbol.first;
    const auto accessible = symbol.second;

    if( not definition )
    {
        m_log.error( { node.sourceLocation() }, "unable to resolve symbol '" + pathName + "'" );
        return;
    }

    if( definition->id() == Node::ID::ENUMERATOR_DEFINITION )
    {
        m_log.error(
            { path.sourceLocation() },
            "enumerator '" + pathName +
                "' cannot be used in 'using' definition, access it with enumeration namespace",
            Code::SymbolIsInaccessible );
        return;
    }

    if( not useAll and not accessible )
    {
        m_log.error(
            { path.sourceLocation() },
            "'" + pathName + "' is not accessible",
            Code::SymbolIsInaccessible );
        m_log.warning(
            { definition->sourceLocation() },
            "'" + definition->identifier()->name() + "' has not been exported" );
        return;
    }

    if( useAll )
    {
        if( not definition->exported() )
        {
            return;
        }

        if( definition->id() == Node::ID::BEHAVIOR_DEFINITION or
            definition->id() == Node::ID::BUILTIN_DEFINITION )
        {
            return;
        }
    }

    try
    {
        m_symboltable.registerSymbol( name, definition );
    }
    catch( const std::domain_error& e )
    {
        const auto& otherSymbol = m_symboltable.findSymbol( name );

        if( definition.get() != otherSymbol.get() )
        {
            if( node.usingToken()->token() == Grammar::Token::UNRESOLVED )
            {
                // using CASM::* ... report issues from current specification
                m_log.error(
                    { otherSymbol->sourceLocation() }, e.what(), Code::IdentifierIsAlreadyUsed );
                m_log.info( { definition->sourceLocation() }, e.what() );
            }
            else
            {
                // using ...::* ... report issues of using path definition itself
                m_log.error( { node.sourceLocation() }, e.what(), Code::IdentifierIsAlreadyUsed );
                m_log.info( { definition->sourceLocation() }, e.what() );
                m_log.info( { otherSymbol->sourceLocation() }, e.what() );
            }
            return;
        }
    }

    if( definition->id() == Node::ID::ENUMERATION_DEFINITION or
        definition->id() == Node::ID::STRUCTURE_DEFINITION or
        definition->id() == Node::ID::BEHAVIOR_DEFINITION or
        definition->id() == Node::ID::DOMAIN_DEFINITION )
    {
        const auto innerNamespace = m_symboltable.findNamespace( path );
        assert( innerNamespace != nullptr );

        try
        {
            m_symboltable.registerNamespace(
                name, innerNamespace, Namespace::Visibility::Internal );
        }
        catch( const std::domain_error& e )
        {
            m_log.debug( { node.sourceLocation() }, std::string( e.what() ) );
        }
    }
}

//
//
// ReplaceIdentifierNameVisitor
//

class ReplaceIdentifierNameVisitor final : public RecursiveVisitor
{
  public:
    ReplaceIdentifierNameVisitor( const Identifier& from, const Identifier& to );

    void visit( Identifier& node ) override;

  private:
    const Identifier& m_from;
    const Identifier& m_to;
};

ReplaceIdentifierNameVisitor::ReplaceIdentifierNameVisitor(
    const Identifier& from, const Identifier& to )
: m_from( from )
, m_to( to )
{
}

void ReplaceIdentifierNameVisitor::visit( Identifier& node )
{
    if( node.name() == m_from.name() )
    {
        node.setName( m_to.name() );
    }
}

//
//
// ReplaceRelationTypeVisitor
//

ReplaceTypeVisitor::ReplaceTypeVisitor(
    libcasm_fe::Logger& log, const Ast::Type::Ptr& from, const Ast::Type::Ptr& to )
: m_log( log )
, m_from( from )
, m_to( to )
{
}

void ReplaceTypeVisitor::visit( DomainDefinition& node )
{
    if( node.domainType()->signature() == m_from->signature() )
    {
        node.setDomainType( m_to );
    }
}

void ReplaceTypeVisitor::visit( RuleDefinition& node )
{
    node.arguments()->accept( *this );

    const auto& returnType = node.returnType();
    auto replaceReturnType = returnType;
    if( returnType->signature() == m_from->signature() )
    {
        replaceReturnType = m_to;
    }

    node.setReturnType( replaceReturnType );
}

void ReplaceTypeVisitor::visit( DerivedDefinition& node )
{
    node.arguments()->accept( *this );

    const auto& returnType = node.returnType();
    auto replaceReturnType = returnType;
    if( returnType->signature() == m_from->signature() )
    {
        replaceReturnType = m_to;
    }

    node.setReturnType( replaceReturnType );
}

void ReplaceTypeVisitor::visit( Declaration& node )
{
    const auto& replaceArgumentTypes = std::make_shared< Types >();
    for( const auto& argumentType : *node.argumentTypes() )
    {
        if( argumentType->signature() == m_from->signature() )
        {
            replaceArgumentTypes->add( m_to );
        }
        else
        {
            replaceArgumentTypes->add( argumentType );
        }
    }

    node.setArgumentTypes( replaceArgumentTypes );

    const auto& returnType = node.returnType();
    auto replaceReturnType = returnType;
    if( returnType->signature() == m_from->signature() )
    {
        replaceReturnType = m_to;
    }

    node.setReturnType( replaceReturnType );
}

void ReplaceTypeVisitor::visit( BuiltinDefinition& node )
{
    const auto& domainType = node.relationType();
    const auto& argumentTypes = domainType.argumentTypes();
    const auto& returnType = domainType.returnType();

    const auto& replaceArgumentTypes = std::make_shared< Types >();
    for( const auto& argumentType : *argumentTypes )
    {
        if( argumentType->signature() == m_from->signature() )
        {
            replaceArgumentTypes->add( m_to );
        }
        else
        {
            replaceArgumentTypes->add( argumentType );
        }
    }

    auto replaceReturnType = returnType;
    if( returnType->signature() == m_from->signature() )
    {
        replaceReturnType = m_to;
    }

    const auto& replaceDomainType = Ast::make< RelationType >(
        domainType.sourceLocation(),
        domainType.name()->duplicate< IdentifierPath >(),
        domainType.leftBraceToken(),
        replaceArgumentTypes,
        domainType.mapsToken(),
        replaceReturnType,
        domainType.rightBraceToken() );

    node.setDomainType( replaceDomainType );
}

void ReplaceTypeVisitor::visit( ImplementDefinition& node )
{
    if( node.domainType()->signature() == m_from->signature() )
    {
        node.setDomainType( m_to );
    }

    RecursiveVisitor::visit( node );
}

void ReplaceTypeVisitor::visit( VariableDefinition& node )
{
    if( node.variableType()->signature() == m_from->signature() )
    {
        node.setVariableType( m_to );
    }
}

void ReplaceTypeVisitor::visit( TemplateType& node )
{
    const auto& replaceArgumentTypes = std::make_shared< Types >();
    for( const auto& argumentType : *node.subTypes() )
    {
        if( argumentType->signature() == m_from->signature() )
        {
            replaceArgumentTypes->add( m_to );
        }
        else
        {
            replaceArgumentTypes->add( argumentType );
        }
    }

    node.setSubTypes( replaceArgumentTypes );
}

//
//
// SymbolResolveVisitor
//

SymbolResolveVisitor::SymbolResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
, m_scopeSymbols()
, m_objectDefinition( nullptr )
, m_behaviorDefinition( nullptr )
, m_agentDomainDefinition( nullptr )
{
}

void SymbolResolveVisitor::visit( InitDefinition& node )
{
    if( node.external() )
    {
        m_log.debug(
            { node.sourceLocation() }, "omit symbol resolving for external init definition" );
        return;
    }

    const auto temporaryAgentDomainDefinition = m_agentDomainDefinition;

    const auto& programSymbol = m_symboltable.findSymbol( "program" );
    assert( programSymbol and " inconsistent state @ CASM prelude specification " );
    assert( programSymbol->id() == Node::ID::FUNCTION_DEFINITION );
    const auto& programFunction = programSymbol->ptr< FunctionDefinition >();

    const auto& location = node.sourceLocation();
    const auto& initializers = Ast::make< Initializers >( location );
    if( node.isSingleAgent() )
    {
        const auto& agentDomainName = TypeInfo::TYPE_NAME_AGENT;
        const auto& agentDomainSymbol = m_symboltable.findSymbol( agentDomainName );
        assert( agentDomainSymbol and " inconsistent state @ CASM prelude specification " );
        assert( agentDomainSymbol->id() == Node::ID::DOMAIN_DEFINITION and " inconsistent state " );
        const auto& agentDomainDefinition = agentDomainSymbol->ptr< DomainDefinition >();

        const auto& agentDomainType = Ast::make< BasicType >(
            location,
            IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( location, TypeInfo::TYPE_NAME_INTEGER ) ) );
        agentDomainDefinition->setDomainType( agentDomainType );
        agentDomainDefinition->accept( *this );
        m_agentDomainDefinition = agentDomainDefinition;

        const auto& zeroLiteral = Ast::make< ValueLiteral >(
            location, std::make_shared< libcasm_ir::IntegerConstant >( 0 ) );

        const auto& programArguments = Ast::make< Expressions >( location );
        programArguments->add( zeroLiteral );

        const auto& ruleReference =
            Ast::make< ReferenceLiteral >( location, Token::unresolved(), node.initPath() );

        const auto& initializer = Ast::make< Initializer >(
            location,
            Token::unresolved(),
            programArguments,
            Token::unresolved(),
            Token::unresolved(),
            ruleReference );

        initializers->add( initializer );
    }
    else
    {
        for( const auto& initializer : *node.initializers() )
        {
            initializers->add( initializer );
        }
    }

    if( m_agentDomainDefinition )
    {
        programFunction->initially()->setInitializers( initializers );
        programFunction->accept( *this );
    }

    m_agentDomainDefinition = temporaryAgentDomainDefinition;
}

void SymbolResolveVisitor::visit( FunctionDefinition& node )
{
    // apply the name of the function declaration to the initializer functions
    for( const auto& initializer : *node.initially()->initializers() )
    {
        const auto& updateRuleFunction = initializer->updateRule()->function();
        assert( updateRuleFunction->id() == Node::ID::DIRECT_CALL_EXPRESSION );
        const auto& directCallExpression = updateRuleFunction->ptr< DirectCallExpression >();
        directCallExpression->setIdentifier( IdentifierPath::fromIdentifier( node.identifier() ) );
    }

    RecursiveVisitor::visit( node );
}

void SymbolResolveVisitor::visit( DerivedDefinition& node )
{
    pushSymbols< VariableDefinition >( node.arguments() );
    node.expression()->accept( *this );
    popSymbols< VariableDefinition >( node.arguments() );
}

void SymbolResolveVisitor::visit( RuleDefinition& node )
{
    pushSymbols< VariableDefinition >( node.arguments() );
    node.rule()->accept( *this );
    popSymbols< VariableDefinition >( node.arguments() );
}

void SymbolResolveVisitor::visit( EnumerationDefinition& node )
{
    const auto& objectSymbol = node.ptr< TypeDefinition >();
    const auto temporaryObjectDefinition = m_objectDefinition;
    m_objectDefinition = objectSymbol;
    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.domainType()->accept( *this );

    popSymbols< VariableDefinition >( node.templateSymbols() );
    m_objectDefinition = temporaryObjectDefinition;

    // Domain::Type::
    const auto& domainTypeName = node.domainType()->signature();
    const auto& domainTypePath = node.domainType()->signaturePath();
    const auto& domainTypeNamespace = m_symboltable.findNamespace( *domainTypePath );
    assert( domainTypeNamespace and " inconsistent state, checked during symbol registration " );

    // CASM::enumeration::enumeration::
    const auto& sourceLocation = node.sourceLocation();
    // const auto& casmIdentifier = Ast::make< Identifier >( sourceLocation, "CASM" );
    const auto& enumerationIdentifier =
        Ast::make< Identifier >( sourceLocation, TypeInfo::TYPE_NAME_ENUMERATION );
    // const auto& enumerationName = Ast::make< IdentifierPath >( sourceLocation, casmIdentifier );
    const auto& enumerationName =
        Ast::make< IdentifierPath >( sourceLocation, enumerationIdentifier );
    enumerationName->addIdentifier( enumerationIdentifier );
    // enumerationName->addIdentifier( enumerationIdentifier );

    const auto& enumerationSymbolResult = m_symboltable.findSymbol( *enumerationName );
    const auto& enumerationSymbol = enumerationSymbolResult.first;
    assert( enumerationSymbol and " inconsistent state @ SymbolRegistrationPass " );
    assert( enumerationSymbol->id() == Node::ID::DOMAIN_DEFINITION and " inconsistent state " );
    const auto& domainDefinition = enumerationSymbol->ptr< DomainDefinition >();

    const auto enumerationNamespace = m_symboltable.findNamespace( *enumerationName );
    assert( enumerationNamespace and " inconsistent state, checked during symbol registration " );

    ReplaceIdentifierNameVisitor replaceIdentifierNameVisitor(
        *enumerationIdentifier, *node.identifier() );

    for( const auto& inner : enumerationNamespace->symbols() )
    {
        const auto& innerName = inner.first;
        const auto& innerSymbol = inner.second;
        const auto& innerNamespace = enumerationNamespace->findNamespace( innerName );
        assert( innerSymbol and " inconsistent state, inside enumerationNamespace " );
        assert( innerNamespace and " inconsistent state, inside enumerationNamespace " );

        if( innerSymbol->id() != Node::ID::BEHAVIOR_DEFINITION )
        {
            continue;
        }

        const auto& behaviorDefinition = innerSymbol->ptr< BehaviorDefinition >();
        const auto& behaviorName = behaviorDefinition->domainType()->signature();
        const auto behaviorNamespace = std::make_shared< Namespace >();

        // Domain::Type::BehaviorDefinition
        try
        {
            domainTypeNamespace->registerSymbol( behaviorName, behaviorDefinition );
        }
        catch( const std::domain_error& e )
        {
            m_log.error( { node.sourceLocation() }, std::string( e.what() ) );
        }

        // Domain::Type::Behavior::
        try
        {
            domainTypeNamespace->registerNamespace( behaviorName, behaviorNamespace );
        }
        catch( const std::domain_error& e )
        {
            m_log.error( { node.sourceLocation() }, std::string( e.what() ) );
        }

        const auto& enumerationBehaviorNamespace =
            enumerationNamespace->findNamespace( behaviorDefinition->domainType()->signature() );
        assert( enumerationBehaviorNamespace and " inconsistent state @ SymbolRegistrationPass " );

        const auto& implementSymbol = enumerationBehaviorNamespace->findSymbol(
            behaviorDefinition->domainType()->signature() );
        assert( implementSymbol and " inconsistent state, inside enumerationNamespace " );

        const auto& implementDefinition = implementSymbol->ptr< ImplementDefinition >();
        const auto duplicateImplementDefinition =
            implementDefinition->duplicate< ImplementDefinition >();
        duplicateImplementDefinition->templateInstances()->clear();

        const auto& fromBasicType = Ast::make< BasicType >(
            enumerationIdentifier->sourceLocation(),
            IdentifierPath::fromIdentifier( enumerationIdentifier ) );

        const auto& duplicateDomainType = node.domainType()->duplicate< Ast::Type >();

        ReplaceTypeVisitor replaceTypeVisitor( m_log, fromBasicType, duplicateDomainType );
        duplicateImplementDefinition->accept( replaceTypeVisitor );

        const auto& implementName = behaviorDefinition->domainType()->signature();
        const auto implementNamespace = std::make_shared< Namespace >();

        // Domain::Type::Behavior::ImplementDefinition
        try
        {
            behaviorNamespace->registerSymbol( implementName, implementDefinition );
        }
        catch( const std::domain_error& e )
        {
            m_log.error( { node.sourceLocation() }, std::string( e.what() ) );
        }

        // Domain::Type::Behavior::Implement::
        try
        {
            behaviorNamespace->registerNamespace( implementName, implementNamespace );
        }
        catch( const std::domain_error& e )
        {
            m_log.error( { node.sourceLocation() }, std::string( e.what() ) );
        }

        SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, *implementNamespace );
        duplicateImplementDefinition->definitions()->accept( symbolRegistrationVisitor );

        m_objectDefinition = duplicateImplementDefinition;
        m_behaviorDefinition = behaviorDefinition;

        duplicateImplementDefinition->domainType()->accept( *this );
        duplicateImplementDefinition->behaviorType()->accept( *this );
        duplicateImplementDefinition->definitions()->accept( *this );

        m_behaviorDefinition = nullptr;
        m_objectDefinition = nullptr;

        // adding instance to implement definition
        implementDefinition->addTemplateInstance( duplicateImplementDefinition );
    }
}

void SymbolResolveVisitor::visit( StructureDefinition& node )
{
    const auto& objectSymbol = node.ptr< TypeDefinition >();

    const auto temporaryObjectDefinition = m_objectDefinition;
    m_objectDefinition = objectSymbol;

    const auto temporaryBehaviorDefinition = m_behaviorDefinition;
    m_behaviorDefinition = nullptr;

    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.domainType()->accept( *this );
    node.functions()->accept( *this );

    popSymbols< VariableDefinition >( node.templateSymbols() );

    m_behaviorDefinition = temporaryBehaviorDefinition;
    m_objectDefinition = temporaryObjectDefinition;
}

void SymbolResolveVisitor::visit( BehaviorDefinition& node )
{
    const auto& objectSymbol = node.ptr< TypeDefinition >();

    const auto temporaryObjectDefinition = m_objectDefinition;
    m_objectDefinition = objectSymbol;

    const auto temporaryBehaviorDefinition = m_behaviorDefinition;
    m_behaviorDefinition = nullptr;

    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.domainType()->accept( *this );
    node.definitions()->accept( *this );

    popSymbols< VariableDefinition >( node.templateSymbols() );

    m_behaviorDefinition = temporaryBehaviorDefinition;
    m_objectDefinition = temporaryObjectDefinition;
}

void SymbolResolveVisitor::visit( ImplementDefinition& node )
{
    const auto& objectSymbol = node.ptr< TypeDefinition >();

    const auto temporaryObjectDefinition = m_objectDefinition;
    m_objectDefinition = objectSymbol;

    const auto temporaryBehaviorDefinition = m_behaviorDefinition;
    if( node.hasBehavior() )
    {
        const auto& behaviorType = node.behaviorType();
        const auto& behaviorPath = behaviorType->signaturePath();

        resolveBehaviorInstance( *behaviorType );

        auto behaviorSymbolResult = m_symboltable.findSymbol( *behaviorPath );
        auto behaviorSymbol = behaviorSymbolResult.first;
        if( not behaviorSymbol )
        {
            const auto& casmBehaviorPath = IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( behaviorType->sourceLocation(), "CASM" ) );
            for( const auto& behaviorPathIdentifier : *behaviorPath->identifiers() )
            {
                casmBehaviorPath->addIdentifier( behaviorPathIdentifier );
            }

            behaviorSymbolResult = m_symboltable.findSymbol( *casmBehaviorPath );
            // relax if symbol is behavior definition inside the CASM namespace
            behaviorSymbol = behaviorSymbolResult.first;
            assert( behaviorSymbol and " inconsistent state @ SymbolRegistrationPass " );
        }

        const auto behaviorDefinition = behaviorSymbol->ptr< TypeDefinition >();
        m_behaviorDefinition = behaviorDefinition;
    }
    else
    {
        const auto& domainTypeName = node.domainType()->signature();
        const auto& domainTypePath = node.domainType()->signaturePath();
        auto domainTypeSymbolResult = m_symboltable.findSymbol( *domainTypePath );
        auto domainTypeSymbol = domainTypeSymbolResult.first;
        if( not domainTypeSymbol )
        {
            const auto& casmDomainTypePath = IdentifierPath::fromIdentifier(
                Ast::make< Identifier >( node.domainType()->sourceLocation(), "CASM" ) );
            casmDomainTypePath->addIdentifier( node.identifier() );

            domainTypeSymbolResult = m_symboltable.findSymbol( *casmDomainTypePath );
            domainTypeSymbol = domainTypeSymbolResult.first;

            if( domainTypeSymbol )
            {
                const std::string msg =
                    node.description() + " symbol '" + domainTypeName + "' already used";
                m_log.error( { node.sourceLocation() }, msg, Code::IdentifierIsAlreadyUsed );
                m_log.info( { domainTypeSymbol->sourceLocation() }, msg );
                return;
            }

            m_log.error(
                { node.sourceLocation() },
                "unknown " + node.description() + " symbol '" + domainTypeName + "' found",
                Code::SymbolIsUnknown );
            return;
        }

        m_behaviorDefinition = objectSymbol;
    }

    const auto& domainName = m_objectDefinition->domainType()->signaturePath();
    const auto& domainNamespace = m_symboltable.findNamespace( *domainName );
    assert( domainNamespace and " inconsistent state @ SymbolRegistrationPass " );

    const auto& behaviorName = m_behaviorDefinition->domainType()->signature();
    const auto& behaviorNamespace = domainNamespace->findNamespace( behaviorName );
    if( not behaviorNamespace )
    {
        SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, m_symboltable );
        node.accept( symbolRegistrationVisitor );
    }

    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.behaviorType()->accept( *this );
    node.domainType()->accept( *this );
    node.definitions()->accept( *this );

    // resolve only symbols of built-in instances used inside the implement definition
    for( const auto& templateInstance : *node.templateInstances() )
    {
        if( templateInstance->id() == Node::ID::BUILTIN_DEFINITION )
        {
            const auto& templateDefinition = templateInstance->ptr< BuiltinDefinition >();
            templateDefinition->accept( *this );
        }
        else
        {
            assert( templateInstance->id() == Node::ID::IMPLEMENT_DEFINITION );
        }
    }

    m_behaviorDefinition = temporaryBehaviorDefinition;
    m_objectDefinition = temporaryObjectDefinition;

    popSymbols< VariableDefinition >( node.templateSymbols() );
}

void SymbolResolveVisitor::visit( DomainDefinition& node )
{
    const auto& objectSymbol = node.ptr< TypeDefinition >();

    const auto temporaryObjectDefinition = m_objectDefinition;
    m_objectDefinition = objectSymbol;
    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.domainType()->accept( *this );

    popSymbols< VariableDefinition >( node.templateSymbols() );
    m_objectDefinition = temporaryObjectDefinition;
}

void SymbolResolveVisitor::visit( UsingDefinition& node )
{
    const auto& symbolName = node.identifier()->name();
    const auto& symbol = m_symboltable.findSymbol( symbolName );
    assert( symbol and " inconsistent state @ SymbolRegistrationPass " );

    const auto& usingSymbolName = node.aliasType()->signature();
    const auto& usingSymbolPath = node.aliasType()->name();
    auto usingSymbol = tryResolveSymbol( *usingSymbolPath );
    if( not usingSymbol )
    {
        m_log.error(
            { node.sourceLocation() },
            "unknown symbol '" + usingSymbolName + "' found",
            Code::SymbolIsUnknown );
        return;
    }

    node.aliasType()->accept( *this );

    auto aliasSymbol = resolveIfAlias( usingSymbol );
    m_log.info( { node.sourceLocation() }, aliasSymbol->typeDescription() );

    if( symbol->id() == Node::ID::DOMAIN_DEFINITION and symbolName == TypeInfo::TYPE_NAME_AGENT )
    {
        const auto& agentDomainDefinition = symbol->ptr< DomainDefinition >();
        agentDomainDefinition->setDomainType( node.aliasType() );
        agentDomainDefinition->accept( *this );

        const auto& initSymbol = m_symboltable.findSymbol( "init" );
        if( initSymbol )
        {
            assert( initSymbol->id() == Node::ID::INIT_DEFINITION );
            const auto temporaryAgentDomainDefinition = m_agentDomainDefinition;
            m_agentDomainDefinition = agentDomainDefinition;

            initSymbol->accept( *this );

            m_agentDomainDefinition = temporaryAgentDomainDefinition;
        }
    }
    else
    {
        const auto& aliasNamespace =
            m_symboltable.findNamespace( aliasSymbol->identifier()->name() );
        m_symboltable.registerNamespace( symbolName, aliasNamespace );
    }
}

void SymbolResolveVisitor::visit( BuiltinDefinition& node )
{
    const auto& name = node.domainType()->name()->path();
    auto symbol = m_symboltable.findSymbol( name );
    assert( symbol and " inconsistent state, checked during symbol registration " );

    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.relationType().argumentTypes()->accept( *this );
    node.relationType().returnType()->accept( *this );

    popSymbols< VariableDefinition >( node.templateSymbols() );

    if( node.hasTargetId() )
    {
        return;
    }

    static const std::unordered_map< std::string, libcasm_ir::Value::ID > builtinToTargetId = {
        { "SelfInstruction", libcasm_ir::SelfInstruction::classid() },
        { "AbortInstruction", libcasm_ir::AbortBuiltin::classid() },
        { "AssertInstruction", libcasm_ir::AssertBuiltin::classid() },
        { "AssureInstruction", libcasm_ir::AssureBuiltin::classid() },
        { "PrintInstruction", libcasm_ir::PrintBuiltin::classid() },
        { "NotInstruction", libcasm_ir::NotInstruction::classid() },
        { "OrInstruction", libcasm_ir::OrInstruction::classid() },
        { "ConcatInstruction", libcasm_ir::AddInstruction::classid() },
        { "AddInstruction", libcasm_ir::AddInstruction::classid() },
        { "SubInstruction", libcasm_ir::SubInstruction::classid() },
        { "MulInstruction", libcasm_ir::MulInstruction::classid() },
        { "DivInstruction", libcasm_ir::DivInstruction::classid() },
        { "ModInstruction", libcasm_ir::ModInstruction::classid() },
        { "PowInstruction", libcasm_ir::PowInstruction::classid() },
        { "SizeInstruction", libcasm_ir::SizeBuiltin::classid() },
        { "SymInstruction", libcasm_ir::IsSymbolicBuiltin::classid() },
        { "EquInstruction", libcasm_ir::EquInstruction::classid() },
        { "LthInstruction", libcasm_ir::LthInstruction::classid() },
        { "GthInstruction", libcasm_ir::GthInstruction::classid() },
        { "NthInstruction", libcasm_ir::AtBuiltin::classid() },
        { "StrInstruction", libcasm_ir::AsStringBuiltin::classid() },
        { "BinInstruction", libcasm_ir::BinBuiltin::classid() },
        { "OctInstruction", libcasm_ir::OctBuiltin::classid() },
        { "HexInstruction", libcasm_ir::HexBuiltin::classid() },
    };

    const auto& builtin = builtinToTargetId.find( name );
    if( builtin == builtinToTargetId.end() )
    {
        m_log.error(
            { node.sourceLocation() },
            " " + node.description() + " '" + name + "'",
            Code::SymbolIsUnknown );
        return;
    }

    const auto builtinTargetId = builtin->second;
    node.setTargetId( builtinTargetId );
}

void SymbolResolveVisitor::visit( Declaration& node )
{
    RecursiveVisitor::visit( node );
}

void SymbolResolveVisitor::visit( ReferenceLiteral& node )
{
    RecursiveVisitor::visit( node );

    const auto& symbolPath = node.identifier();
    const auto& symbolName = symbolPath->path();
    const auto& symbol = tryResolveSymbol( *symbolPath );
    if( not symbol )
    {
        m_log.error(
            { node.sourceLocation() },
            "unknown " + node.description() + " symbol '" + symbolName + "' found",
            Code::SymbolIsUnknown );
        return;
    }

    switch( symbol->id() )
    {
        case Node::ID::FUNCTION_DEFINITION:
        {
            node.setReferenceType( ReferenceLiteral::ReferenceType::FUNCTION );
            node.setReference( symbol );
            break;
        }
        case Node::ID::DERIVED_DEFINITION:
        {
            node.setReferenceType( ReferenceLiteral::ReferenceType::DERIVED );
            node.setReference( symbol );
            break;
        }
        case Node::ID::RULE_DEFINITION:
        {
            node.setReferenceType( ReferenceLiteral::ReferenceType::RULE );
            node.setReference( symbol );
            break;
        }
        default:
        {
            m_log.error(
                { symbol->sourceLocation() },
                "cannot reference " + symbol->description() + " '" + symbolName + "'" );
        }
    }
}

void SymbolResolveVisitor::visit( DirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    const auto& sourceLocation = node.sourceLocation();
    const auto& symbolPath = node.identifier();
    const auto& symbolName = symbolPath->path();

    const auto validateArgumentsCount = [&]( const std::string& description,
                                             std::size_t expectedNumberOfArguments ) {
        if( node.arguments()->size() != expectedNumberOfArguments )
        {
            m_log.error(
                { sourceLocation },
                "invalid argument size: " + description + " '" + symbolName + "' expects " +
                    std::to_string( expectedNumberOfArguments ) + " arguments",
                Code::SymbolArgumentSizeMismatch );
        }
    };

    const auto scopeSymbolIt = m_scopeSymbols.find( symbolName );
    if( scopeSymbolIt != m_scopeSymbols.cend() )
    {
        if( symbolName == "this" )
        {
            node.setTargetType( DirectCallExpression::TargetType::THIS );
        }
        else
        {
            node.setTargetType( DirectCallExpression::TargetType::VARIABLE );
        }
        node.setTargetDefinition( scopeSymbolIt->second );
        validateArgumentsCount( "variable", 0 );
        return;
    }

    auto symbol = tryResolveSymbol( *symbolPath );
    if( not symbol )
    {
        const auto& casmSymbolPath =
            IdentifierPath::fromIdentifier( Ast::make< Identifier >( sourceLocation, "CASM" ) );
        for( const auto& symbolPathIdentifier : *symbolPath->identifiers() )
        {
            casmSymbolPath->addIdentifier( symbolPathIdentifier );
        }

        // relax if symbol is a builtin definition inside the CASM namespace
        const auto& symbolResult = m_symboltable.findSymbol( *casmSymbolPath );
        symbol = symbolResult.first;
        if( not symbol or symbol->id() != Node::ID::BUILTIN_DEFINITION )
        {
            m_log.error(
                { sourceLocation },
                "unknown symbol " + node.description() + " '" + symbolPath->path() + "' found",
                Code::SymbolIsUnknown );
            return;
        }
    }

    assert( symbol and " inconsistent state @ SymbolRegistrationPass " );

    symbol = resolveIfAlias( symbol );

    std::size_t expectedNumberOfArguments = 0;

    switch( symbol->id() )
    {
        case Node::ID::FUNCTION_DEFINITION:
        {
            node.setTargetType( DirectCallExpression::TargetType::FUNCTION );
            const auto function = std::static_pointer_cast< FunctionDefinition >( symbol );
            expectedNumberOfArguments = function->argumentTypes()->size();
            break;
        }
        case Node::ID::DERIVED_DEFINITION:
        {
            node.setTargetType( DirectCallExpression::TargetType::DERIVED );
            const auto derived = std::static_pointer_cast< DerivedDefinition >( symbol );
            expectedNumberOfArguments = derived->arguments()->size();
            break;
        }
        case Node::ID::RULE_DEFINITION:
        {
            node.setTargetType( DirectCallExpression::TargetType::RULE );
            const auto rule = std::static_pointer_cast< RuleDefinition >( symbol );
            expectedNumberOfArguments = rule->arguments()->size();
            break;
        }
        case Node::ID::ENUMERATOR_DEFINITION:
        {
            node.setTargetType( DirectCallExpression::TargetType::CONSTANT );
            break;
        }
        case Node::ID::ENUMERATION_DEFINITION:
        {
            node.setTargetType( DirectCallExpression::TargetType::DOMAIN );
            break;
        }
        case Node::ID::DOMAIN_DEFINITION:
        {
            node.setTargetType( DirectCallExpression::TargetType::DOMAIN );
            break;
        }
        case Node::ID::BUILTIN_DEFINITION:
        {
            node.setTargetType( DirectCallExpression::TargetType::BUILTIN );
            const auto& builtinDefinition = symbol->ptr< BuiltinDefinition >();
            expectedNumberOfArguments = builtinDefinition->relationType().argumentTypes()->size();

            symbol = resolveBuiltinCall( node, builtinDefinition );
            if( not symbol )
            {
                return;
            }
            break;
        }
        default:
        {
            m_log.error(
                { symbol->sourceLocation() },
                "cannot reference " + symbol->description() + " '" + symbolName + "'" );
            return;
        }
    }

    node.setTargetDefinition( symbol );
    validateArgumentsCount( symbol->description(), expectedNumberOfArguments );
}

void SymbolResolveVisitor::visit( LiteralCallExpression& node )
{
    RecursiveVisitor::visit( node );
}

void SymbolResolveVisitor::visit( LetExpression& node )
{
    node.variableBindings()->accept( *this );

    pushVariableBindings( node.variableBindings() );
    node.expression()->accept( *this );
    popVariableBindings( node.variableBindings() );
}

void SymbolResolveVisitor::visit( ChooseExpression& node )
{
    node.universe()->accept( *this );

    pushSymbols< VariableDefinition >( node.variables() );
    node.expression()->accept( *this );
    popSymbols< VariableDefinition >( node.variables() );
}

void SymbolResolveVisitor::visit( UniversalQuantifierExpression& node )
{
    node.universe()->accept( *this );

    pushSymbols< VariableDefinition >( node.predicateVariables() );
    node.proposition()->accept( *this );
    popSymbols< VariableDefinition >( node.predicateVariables() );
}

void SymbolResolveVisitor::visit( ExistentialQuantifierExpression& node )
{
    node.universe()->accept( *this );

    pushSymbols< VariableDefinition >( node.predicateVariables() );
    node.proposition()->accept( *this );
    popSymbols< VariableDefinition >( node.predicateVariables() );
}

void SymbolResolveVisitor::visit( LetRule& node )
{
    node.variableBindings()->accept( *this );

    pushVariableBindings( node.variableBindings() );
    node.rule()->accept( *this );
    popVariableBindings( node.variableBindings() );
}

void SymbolResolveVisitor::visit( LocalRule& node )
{
    node.localFunctions()->accept( *this );

    pushSymbols< FunctionDefinition >( node.localFunctions() );
    node.rule()->accept( *this );
    popSymbols< FunctionDefinition >( node.localFunctions() );
}

void SymbolResolveVisitor::visit( ForallRule& node )
{
    node.universe()->accept( *this );

    pushSymbols< VariableDefinition >( node.variables() );
    node.condition()->accept( *this );
    node.rule()->accept( *this );
    popSymbols< VariableDefinition >( node.variables() );
}

void SymbolResolveVisitor::visit( ChooseRule& node )
{
    node.universe()->accept( *this );

    pushSymbols< VariableDefinition >( node.variables() );
    node.rule()->accept( *this );
    popSymbols< VariableDefinition >( node.variables() );
}

void SymbolResolveVisitor::visit( BasicType& node )
{
    RecursiveVisitor::visit( node );

    const auto& domainInstanceTypeName = node.signature();

    const auto scopeSymbolIt = m_scopeSymbols.find( domainInstanceTypeName );
    if( scopeSymbolIt != m_scopeSymbols.cend() )
    {
        const auto& scopeSymbol = scopeSymbolIt->second;
        assert( scopeSymbol->id() == Node::ID::VARIABLE_DEFINITION );
        const auto& variableDefinition = scopeSymbol->ptr< VariableDefinition >();
        node.setTypeDefinition( variableDefinition->objectDefinition() );
        return;
    }

    resolveTypeInstance( node );
}

void SymbolResolveVisitor::visit( TupleType& node )
{
    RecursiveVisitor::visit( node );

    resolveTypeInstance( node );
}

void SymbolResolveVisitor::visit( RecordType& node )
{
    RecursiveVisitor::visit( node );

    resolveTypeInstance( node );
}

void SymbolResolveVisitor::visit( FixedSizedType& node )
{
    RecursiveVisitor::visit( node );

    resolveTypeInstance( node );
}

void SymbolResolveVisitor::visit( RelationType& node )
{
    RecursiveVisitor::visit( node );

    resolveTypeInstance( node );
}

void SymbolResolveVisitor::visit( TemplateType& node )
{
    resolveTypeInstance( node );

    if( not node.typeDefinition() )
    {
        m_log.error(
            { node.sourceLocation() },
            "unknown " + node.description() + " symbol '" + node.signature() + "' found",
            Code::SymbolIsUnknown );
    }
}

void SymbolResolveVisitor::pushSymbol( const Definition::Ptr& symbol )
{
    symbol->accept( *this );

    const auto& name = symbol->identifier()->name();
    static const auto THIS( "this" );
    if( name == THIS )
    {
        if( not m_objectDefinition )
        {
            m_log.error(
                { symbol->sourceLocation() },
                "'this' can only be used inside a behavior and implement definition" );
            return;
        }

        assert( symbol->id() == Node::ID::VARIABLE_DEFINITION );
        const auto& variableDefinition = symbol->ptr< VariableDefinition >();
        variableDefinition->setObjectDefinition( m_objectDefinition );
    }

    const auto result = m_scopeSymbols.emplace( name, symbol );
    if( not result.second )
    {
        m_log.error(
            { symbol->sourceLocation() },
            "redefinition of symbol '" + name + "'",
            Code::SymbolAlreadyDefined );

        const auto& existingSymbol = result.first->second;
        m_log.info(
            { existingSymbol->sourceLocation() }, "previous definition of '" + name + "' is here" );
    }
}

void SymbolResolveVisitor::popSymbol( const Definition::Ptr& symbol )
{
    const auto& name = symbol->identifier()->name();
    m_scopeSymbols.erase( name );
}

void SymbolResolveVisitor::pushVariableBindings( const VariableBindings::Ptr& variableBindings )
{
    for( const auto& variableBinding : *variableBindings )
    {
        pushSymbol( variableBinding->variable() );
    }
}

void SymbolResolveVisitor::popVariableBindings( const VariableBindings::Ptr& variableBindings )
{
    for( const auto& variableBinding : *variableBindings )
    {
        popSymbol( variableBinding->variable() );
    }
}

Definition::Ptr SymbolResolveVisitor::resolveIfAlias( const Definition::Ptr& definition ) const
{
    if( definition->id() != Node::ID::USING_DEFINITION )
    {
        return definition;
    }

    const auto& usingDefinition = static_cast< const UsingDefinition& >( *definition );
    const auto& symbol = tryResolveSymbol( *usingDefinition.aliasType()->signaturePath() );

    if( symbol )
    {
        return resolveIfAlias( symbol );  // resolve again, the symbol may be another alias
    }
    else
    {
        return definition;
    }
}

Definition::Ptr SymbolResolveVisitor::tryResolveSymbol( const IdentifierPath& symbolPath ) const
{
    const auto& symbolName = symbolPath.path();

    const auto scopeSymbolIt = m_scopeSymbols.find( symbolName );
    if( scopeSymbolIt != m_scopeSymbols.cend() )
    {
        return scopeSymbolIt->second;
    }

    const auto& symbolResult = m_symboltable.findSymbol( symbolPath );
    const auto& symbol = symbolResult.first;
    const auto accessible = symbolResult.second;

    if( symbol and not accessible )
    {
        m_log.error(
            { symbolPath.sourceLocation() },
            "'" + symbolName + "' is not accessible",
            Code::SymbolIsInaccessible );
        m_log.warning( { symbol->sourceLocation() }, "'" + symbolName + "' has not been exported" );
    }

    return symbol;
}

Definition::Ptr SymbolResolveVisitor::resolveSymbol( const Definition& node ) const
{
    Namespace* symboltable = &m_symboltable;

    if( m_objectDefinition )
    {
        const auto& domainName = m_objectDefinition->domainType()->signaturePath();
        const auto& domainNamespace = symboltable->findNamespace( *domainName );
        if( not domainNamespace )
        {
            return nullptr;
        }
        assert( domainNamespace and " inconsistent state @ SymbolRegistrationPass " );
        symboltable = domainNamespace.get();
    }

    if( m_behaviorDefinition )
    {
        const auto& behaviorName = m_behaviorDefinition->domainType()->signaturePath();
        const auto& behaviorNamespace = symboltable->findNamespace( *behaviorName );
        if( not behaviorNamespace )
        {
            return nullptr;
        }

        assert( behaviorNamespace and " inconsistent state " );
        symboltable = behaviorNamespace.get();
    }

    const auto& name = node.identifier()->name();
    const auto& symbol = symboltable->findSymbol( name );
    if( not symbol )
    {
        return nullptr;
    }

    return symbol;
}

void SymbolResolveVisitor::resolveBehaviorInstance( Ast::Type& node )
{
    if( node.typeDefinition() )
    {
        return;
    }

    const auto& templateTypeNode = static_cast< const TemplateType& >( node );

    // Domain(Behavior)::Type(Behavior)
    const auto& domainTypeName = node.signature();
    const auto& domainTypePath = node.signaturePath();
    const auto& domainTypeSymbolResult = m_symboltable.findSymbol( *domainTypePath );
    const auto& domainTypeSymbol = domainTypeSymbolResult.first;
    if( domainTypeSymbol )
    {
        assert( domainTypeSymbol->id() == Node::ID::BEHAVIOR_DEFINITION );
        node.setTypeDefinition( domainTypeSymbol->ptr< TypeDefinition >() );
        return;
    }

    // Domain(Behavior)::
    auto domainPath = node.name();
    auto domainNamespace = m_symboltable.findNamespace( *domainPath );
    if( not domainNamespace )
    {
        domainPath = IdentifierPath::fromIdentifier(
            Ast::make< Identifier >( node.sourceLocation(), "CASM" ) );
        for( const auto& domainPathIdentifier : *node.name()->identifiers() )
        {
            domainPath->addIdentifier( domainPathIdentifier );
        }
        domainNamespace = m_symboltable.findNamespace( *domainPath );
        assert( domainNamespace and " inconsistent state @ SymbolRegistrationPass " );
    }

    assert( m_objectDefinition and m_objectDefinition->id() == Node::ID::IMPLEMENT_DEFINITION );
    const auto& implementDefinition = m_objectDefinition->ptr< ImplementDefinition >();

    // Symbol(Behavior)
    const auto& behaviorSymbolResult = m_symboltable.findSymbol( *domainPath );
    const auto& behaviorSymbol = behaviorSymbolResult.first;
    assert( behaviorSymbol and " inconsistent state @ SymbolRegistrationPass " );
    assert( behaviorSymbol->id() == Node::ID::BEHAVIOR_DEFINITION and " inconsistent state " );
    const auto& behaviorDefinition = behaviorSymbol->ptr< BehaviorDefinition >();
    // assert( behaviorDefinition->templateSymbols()->size() > 0 and " inconsistent state " );
    if( behaviorDefinition->templateSymbols()->size() == 0 )
    {
        return;
    }

    if( templateTypeNode.subTypes()->size() != behaviorDefinition->templateSymbols()->size() )
    {
        m_log.error(
            { templateTypeNode.sourceLocation(), behaviorDefinition->sourceLocation() },
            templateTypeNode.description() + " has parameter size " +
                std::to_string( templateTypeNode.subTypes()->size() ) + ", but template " +
                behaviorDefinition->description() + " definition needs parameter size " +
                std::to_string( behaviorDefinition->templateSymbols()->size() ),
            Code::Unspecified );
        // assert( false );
        return;
    }

    const auto& duplicateBehaviorDefinition = behaviorDefinition->duplicate< BehaviorDefinition >();
    duplicateBehaviorDefinition->templateInstances()->clear();

    for( std::size_t position = 0; position < templateTypeNode.subTypes()->size(); position++ )
    {
        const auto& from = ( *behaviorDefinition->templateSymbols() )[ position ];
        const auto& to = ( *templateTypeNode.subTypes() )[ position ];

        // TODO: FIXME: @ppaulweber: check if template parameter variable is concrete type

        const auto& fromBasicType = Ast::make< BasicType >(
            from->sourceLocation(), IdentifierPath::fromIdentifier( from->identifier() ) );

        ReplaceTypeVisitor replaceTypeVisitor( m_log, fromBasicType, to );
        duplicateBehaviorDefinition->accept( replaceTypeVisitor );
    }

    // clear the replaced template symbols
    duplicateBehaviorDefinition->templateSymbols()->clear();

    // Domain::InstanceSymbol + Domain::InstanceType::
    SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, m_symboltable );
    duplicateBehaviorDefinition->accept( symbolRegistrationVisitor );
    duplicateBehaviorDefinition->accept( *this );

    behaviorDefinition->addTemplateInstance( duplicateBehaviorDefinition );

    const auto& duplicateImplementDefinition = Ast::make< ImplementDefinition >(
        implementDefinition->sourceLocation(),
        implementDefinition->implementToken(),
        implementDefinition->templateSymbols(),
        duplicateBehaviorDefinition->domainType(),
        implementDefinition->forToken(),
        implementDefinition->domainType(),
        implementDefinition->assignmentToken(),
        implementDefinition->leftBraceToken(),
        implementDefinition->definitions(),
        implementDefinition->rightBraceToken() );

    duplicateImplementDefinition->accept( symbolRegistrationVisitor );
    duplicateImplementDefinition->accept( *this );

    implementDefinition->addTemplateInstance( duplicateImplementDefinition );
}

void SymbolResolveVisitor::resolveTypeInstance( Ast::Type& node )
{
    if( node.typeDefinition() )
    {
        return;
    }

    const auto& domainInstanceTypeName = node.signature();
    const auto& domainInstanceTypePath = node.signaturePath();
    const auto& domainInstanceTypeSymbolResult =
        m_symboltable.findSymbol( *domainInstanceTypePath );
    const auto& domainInstanceTypeSymbol = domainInstanceTypeSymbolResult.first;

    if( domainInstanceTypeSymbol )
    {
        assert(
            domainInstanceTypeSymbol->id() == Node::ID::DOMAIN_DEFINITION or
            domainInstanceTypeSymbol->id() == Node::ID::ENUMERATION_DEFINITION or
            domainInstanceTypeSymbol->id() == Node::ID::STRUCTURE_DEFINITION or
            domainInstanceTypeSymbol->id() == Node::ID::BEHAVIOR_DEFINITION or
            domainInstanceTypeSymbol->id() == Node::ID::USING_DEFINITION );

        if( domainInstanceTypeSymbol->id() == Node::ID::USING_DEFINITION )
        {
            const auto& usingDomainSymbol = domainInstanceTypeSymbol->ptr< UsingDefinition >();
            usingDomainSymbol->aliasType()->accept( *this );
            node.setTypeDefinition( usingDomainSymbol->aliasType()->typeDefinition() );
            return;
        }

        const auto& typeDefinition = domainInstanceTypeSymbol->ptr< TypeDefinition >();
        node.setTypeDefinition( typeDefinition );
        return;
    }

    const auto& domainName = node.name();
    const auto& domainSymbolResult = m_symboltable.findSymbol( *domainName );
    const auto& domainSymbol = domainSymbolResult.first;
    if( not domainSymbol )
    {
        // unknown symbol found
        return;
    }

    if( domainSymbol->id() == Node::ID::USING_DEFINITION )
    {
        const auto& usingDomainSymbol = domainSymbol->ptr< UsingDefinition >();
        usingDomainSymbol->aliasType()->accept( *this );
        node.setTypeDefinition( usingDomainSymbol->aliasType()->typeDefinition() );
        return;
    }

    assert( domainSymbol and " inconsistent state, checked during symbol registration " );
    const auto& domainDefinition = domainSymbol->ptr< DomainDefinition >();

    u1 isProperty = false;
    if( domainName->path() == "Integer" and node.id() == Node::ID::FIXED_SIZED_TYPE )
    {
        isProperty = true;
    }
    else
    {
        if( not domainDefinition->isTemplate() )
        {
            return;
        }
    }

    ReplaceTypeVisitor replaceTypeVisitor(
        m_log, domainDefinition->domainType(), node.ptr< Ast::Type >() );

    const auto& duplicateDomainDefinition = domainDefinition->duplicate< DomainDefinition >();
    duplicateDomainDefinition->accept( replaceTypeVisitor );
    duplicateDomainDefinition->templateSymbols()->clear();
    node.setTypeDefinition( duplicateDomainDefinition );

    // Domain::InstanceSymbol + Domain::InstanceType::
    SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, m_symboltable );
    duplicateDomainDefinition->accept( symbolRegistrationVisitor );
    duplicateDomainDefinition->accept( *this );

    // add instance domain to template domain
    domainDefinition->addTemplateInstance( duplicateDomainDefinition );

    if( isProperty )
    {
        return;
    }

    // Domain::Type::
    const auto& domainTypeName = domainDefinition->domainType()->signature();
    const auto& domainTypePath = domainDefinition->domainType()->signaturePath();
    const auto& domainTypeNamespace = m_symboltable.findNamespace( *domainTypePath );
    assert( domainTypeNamespace and " inconsistent state @ SymbolRegistrationPass " );

    // Domain::InstanceType::
    const auto& domainInstanceTypeNamespace =
        m_symboltable.findNamespace( *domainInstanceTypePath );
    assert( domainInstanceTypeNamespace and " inconsistent state " );

    for( const auto& inner : domainTypeNamespace->symbols() )
    {
        const auto& innerName = inner.first;
        const auto& innerSymbol = inner.second;
        assert( innerSymbol and " inconsistent state @ domainTypeNamespace " );

        if( innerSymbol->id() != Node::ID::BEHAVIOR_DEFINITION )
        {
            continue;
        }

        const auto& innerNamespace = domainTypeNamespace->findNamespace( innerName );
        assert( innerNamespace and " inconsistent state @ domainTypeNamespace " );

        const auto& behaviorDefinition = innerSymbol->ptr< BehaviorDefinition >();
        const auto& duplicateBehaviorDefinition =
            behaviorDefinition->duplicate< BehaviorDefinition >();
        duplicateBehaviorDefinition->templateInstances()->clear();
        duplicateBehaviorDefinition->accept( replaceTypeVisitor );
        duplicateBehaviorDefinition->templateSymbols()->clear();

        // adding instance to behavior definition
        behaviorDefinition->addTemplateInstance( duplicateBehaviorDefinition );

        const auto& implementNamespace =
            domainTypeNamespace->findNamespace( behaviorDefinition->domainType()->signature() );
        assert( implementNamespace and " inconsistent state @ SymbolRegistrationPass " );

        const auto& implementSymbol =
            implementNamespace->findSymbol( behaviorDefinition->domainType()->signature() );
        assert( implementSymbol and " inconsistent state @ domainTypeNamespace " );
        assert(
            implementSymbol->id() == Node::ID::IMPLEMENT_DEFINITION and " inconsistent state " );

        const auto& implementDefinition = implementSymbol->ptr< ImplementDefinition >();

        const auto& duplicateImplementDefinition = Ast::make< ImplementDefinition >(
            implementDefinition->sourceLocation(),
            implementDefinition->implementToken(),
            std::make_shared< VariableDefinitions >(),
            duplicateBehaviorDefinition->domainType(),
            implementDefinition->forToken(),
            duplicateDomainDefinition->domainType(),
            implementDefinition->assignmentToken(),
            implementDefinition->leftBraceToken(),
            implementDefinition->definitions()->duplicate< Definitions >(),
            implementDefinition->rightBraceToken() );

        duplicateImplementDefinition->accept( replaceTypeVisitor );
        duplicateImplementDefinition->accept( symbolRegistrationVisitor );

        const auto temporaryObjectDefinition = m_objectDefinition;
        const auto temporaryBehaviorDefinition = m_behaviorDefinition;

        m_objectDefinition = duplicateImplementDefinition;
        m_behaviorDefinition = duplicateBehaviorDefinition;

        duplicateImplementDefinition->domainType()->accept( *this );
        duplicateImplementDefinition->behaviorType()->accept( *this );
        duplicateImplementDefinition->definitions()->accept( *this );

        m_objectDefinition = temporaryObjectDefinition;
        m_behaviorDefinition = temporaryBehaviorDefinition;

        // adding instance to implement definition
        implementDefinition->addTemplateInstance( duplicateImplementDefinition );
    }
}

Definition::Ptr SymbolResolveVisitor::resolveBuiltinCall(
    TargetCallExpression& node, const BuiltinDefinition::Ptr& builtinDefinition )
{
    if( builtinDefinition->templateSymbols()->size() > 0 )
    {
        const auto& domainInstanceTypeName = builtinDefinition->relationType().signature();
        const auto& domainInstanceTypePath = builtinDefinition->relationType().signaturePath();
        const auto& domainInstanceTypeSymbolResult =
            m_symboltable.findSymbol( *domainInstanceTypePath );
        const auto& domainInstanceTypeSymbol = domainInstanceTypeSymbolResult.first;
        const auto& duplicateBuiltinDefinition =
            builtinDefinition->duplicate< BuiltinDefinition >();
        duplicateBuiltinDefinition->templateInstances()->clear();

        if( node.templateSymbols()->size() != builtinDefinition->templateSymbols()->size() )
        {
            if( node.templateSymbols()->size() == 0 )
            {
                m_log.error(
                    { node.sourceLocation(),
                      builtinDefinition->templateSymbols()->sourceLocation() },
                    "builtin call is missing 'template< ... >' parameters, because "
                    "template builtin definition needs parameter size of " +
                        std::to_string( builtinDefinition->templateSymbols()->size() ),
                    Code::Unspecified );
            }
            else
            {
                m_log.error(
                    { node.templateSymbols()->sourceLocation(),
                      builtinDefinition->templateSymbols()->sourceLocation() },
                    "template builtin call has parameter size " +
                        std::to_string( node.templateSymbols()->size() ) +
                        ", but template builtin definition needs parameter size " +
                        std::to_string( builtinDefinition->templateSymbols()->size() ),
                    Code::Unspecified );
            }
            return nullptr;
        }

        // Domain::InstanceSymbol + Domain::InstanceType::
        SymbolRegistrationVisitor symbolRegistrationVisitor( m_log, m_symboltable );

        u1 valid = true;
        for( std::size_t position = 0; position < node.templateSymbols()->size(); position++ )
        {
            const auto& from = ( *builtinDefinition->templateSymbols() )[ position ];
            const auto& to = ( *node.templateSymbols() )[ position ];

            if( from->identifier()->name() != to->identifier()->name() )
            {
                m_log.error(
                    { to->identifier()->sourceLocation(), from->identifier()->sourceLocation() },
                    "template parameter variable mismatch at position " +
                        std::to_string( position + 1 ) );
                valid = false;
                continue;
            }

            const auto& fromBasicType = Ast::make< BasicType >(
                from->sourceLocation(), IdentifierPath::fromIdentifier( from->identifier() ) );

            ReplaceTypeVisitor replaceTypeVisitor( m_log, fromBasicType, to->variableType() );
            duplicateBuiltinDefinition->accept( replaceTypeVisitor );
        }

        // clear the replaced template symbols
        duplicateBuiltinDefinition->templateSymbols()->clear();

        if( not valid )
        {
            return nullptr;
        }

        assert( m_objectDefinition and m_objectDefinition->id() == Node::ID::IMPLEMENT_DEFINITION );
        const auto& implementDefinition = m_objectDefinition->ptr< ImplementDefinition >();

        const auto& duplicateBuiltinSymbolPath =
            duplicateBuiltinDefinition->domainType()->signaturePath();
        const auto& duplicateBuiltinSymbolResult =
            m_symboltable.findSymbol( *duplicateBuiltinSymbolPath );
        const auto& duplicateBuiltinSymbol = duplicateBuiltinSymbolResult.first;

        if( not duplicateBuiltinSymbol )
        {
            duplicateBuiltinDefinition->accept( symbolRegistrationVisitor );
        }
        duplicateBuiltinDefinition->accept( *this );

        // symbol resolving of builtin is done during ImplementDefinition symbol resolving
        implementDefinition->addTemplateInstance( duplicateBuiltinDefinition );
        return duplicateBuiltinDefinition->ptr< Definition >();
    }

    return builtinDefinition;
}

//
//
// SymbolResolverPass
//

void SymbolResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< LibraryLoaderPass >();
}

u1 SymbolResolverPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();

    NamespaceResolveVisitor namespaceResolveVisitor( log, *specification->symboltable() );
    specification->definitions()->accept( namespaceResolveVisitor );

    if( log.errors() > 0 )
    {
        log.debug( "symbol table =\n" + specification->symboltable()->dump() );
        log.debug( "found %lu error(s) during namespace resolving", log.errors() );
        return false;
    }

    SymbolResolveVisitor visitor( log, *specification->symboltable() );
    specification->definitions()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "symbol table =\n" + specification->symboltable()->dump() );
        log.debug( "found %lu error(s) during symbol resolving", errors );
        return false;
    }

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
