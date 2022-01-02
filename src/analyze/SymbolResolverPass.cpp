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

#include "SymbolResolverPass.h"

#include "../various/GrammarToken.h"

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/analyze/SymbolRegistrationPass>
#include <libcasm-fe/analyze/TemplatingPass>
#include <libcasm-fe/ast/Declaration>
#include <libcasm-fe/ast/Literal>
#include <libcasm-fe/ast/Node>
#include <libcasm-fe/ast/Visitor>
#include <libcasm-fe/import/LibraryLoaderPass>
#include <libcasm-fe/import/SpecificationMergerPass>
#include <libcasm-fe/transform/CstToAstPass>

#include <libcasm-ir/Builtin>
#include <libcasm-ir/Instruction>

#include <libpass/PassRegistry>
#include <libpass/PassResult>
#include <libpass/PassUsage>

#include <libstdhl/String>

#include <unordered_map>

using namespace libcasm_fe;
using namespace AST;

char SymbolResolverPass::id = 0;

static libpass::PassRegistration< SymbolResolverPass > PASS(
    "Symbol Resolver Pass", "resolves AST identifiers of symbols and types", "ast-sym-resolve", 0 );

//
//
// NamespaceResolveVisitor
//

namespace libcasm_fe
{
    namespace AST
    {
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
    }
}

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
                AST::make< Identifiers >( location, path.identifiers()->data() );
            symbolName->add( AST::make< Identifier >( location, name ) );
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
            if( libstdhl::String::startsWith( pathName, "CASM" + Namespace::delimiter() ) )
            {
                if( definition->abstract() and not otherSymbol->abstract() )
                {
                    return;
                }

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
}

namespace libcasm_fe
{
    namespace AST
    {
        class SymbolResolveVisitor final : public RecursiveVisitor
        {
          public:
            SymbolResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

            void visit( Root& node ) override;

            void visit( FunctionDefinition& node ) override;
            void visit( DerivedDefinition& node ) override;
            void visit( RuleDefinition& node ) override;
            void visit( EnumerationDefinition& node ) override;
            void visit( StructureDefinition& node ) override;
            void visit( BehaviorDefinition& node ) override;
            void visit( ImplementDefinition& node ) override;
            void visit( BuiltinDefinition& node ) override;
            void visit( DomainDefinition& node ) override;
            void visit( UsingDefinition& node ) override;
            void visit( Declaration& node ) override;

            void visit( ReferenceLiteral& node ) override;

            void visit( DirectCallExpression& node ) override;
            void visit( LetExpression& node ) override;
            void visit( ChooseExpression& node ) override;
            void visit( UniversalQuantifierExpression& node ) override;
            void visit( ExistentialQuantifierExpression& node ) override;

            void visit( LetRule& node ) override;
            void visit( LocalRule& node ) override;
            void visit( ForallRule& node ) override;
            void visit( ChooseRule& node ) override;

            void visit( BasicType& node ) override;
            void visit( TupleType& node ) override;
            void visit( RecordType& node ) override;
            void visit( FixedSizedType& node ) override;
            void visit( RelationType& node ) override;
            void visit( TemplateType& node ) override;

            const Types::Ptr& templateTypes( void );
            const Definitions::Ptr& templateDefinitions( void );

          private:
            void pushSymbol( const Definition::Ptr& symbol );
            void popSymbol( const Definition::Ptr& symbol );

            template < typename T >
            void pushSymbols( const typename NodeList< T >::Ptr& symbols )
            {
                for( const auto& symbol : *symbols )
                {
                    pushSymbol( symbol );
                }
            }

            template < typename T >
            void popSymbols( const typename NodeList< T >::Ptr& symbols )
            {
                for( const auto& symbol : *symbols )
                {
                    popSymbol( symbol );
                }
            }

            void pushVariableBindings( const VariableBindings::Ptr& variableBindings );
            void popVariableBindings( const VariableBindings::Ptr& variableBindings );

            Definition::Ptr resolveSymbol(
                const IdentifierPath& identifierPath, const u1 silent = false );
            Definition::Ptr resolveAlias( const Definition::Ptr& definition );

            void resolveTypeDefinition( Type& node );

          private:
            libcasm_fe::Logger& m_log;
            Namespace& m_symboltable;
            Types::Ptr m_templateTypes;
            Definitions::Ptr m_templateDefinitions;

            std::unordered_map< std::string, Definition::Ptr > m_scopeSymbols;
            TypeDefinition::Ptr m_objectTypeDefinition;

            DomainDefinition::Ptr m_agentDomainDefinition;
            MappedExpressions::Ptr m_initializers;
        };
    }
}

//
//
// SymbolResolveVisitor
//

SymbolResolveVisitor::SymbolResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
, m_scopeSymbols()
, m_templateTypes( std::make_shared< Types >() )
, m_templateDefinitions( std::make_shared< Definitions >() )
, m_objectTypeDefinition( nullptr )
, m_agentDomainDefinition( nullptr )
, m_initializers( nullptr )
{
}

void SymbolResolveVisitor::visit( Root& node )
{
    RecursiveVisitor::visit( node );

    // determine after the symbol resolving the initialization of the program function
    // if no init definition is present, use an empty set

    const auto& programSymbol = m_symboltable.findSymbol( "program" );
    assert( programSymbol and " inconsistent state in prelude specification " );
    assert( programSymbol->id() == Node::ID::FUNCTION_DEFINITION );
    const auto& programDefinition = programSymbol->ptr< FunctionDefinition >();

    assert( not m_initializers and " inconsistent state " );
    const auto& initSymbol = m_symboltable.findSymbol( "init" );
    if( initSymbol )
    {
        assert( initSymbol->id() == Node::ID::INIT_DEFINITION );
        const auto& initDefinition = initSymbol->ptr< InitDefinition >();
        m_initializers = initDefinition->initializers();
    }
    else
    {
        m_initializers = AST::make< MappedExpressions >( programDefinition->sourceLocation() );
    }

    programDefinition->accept( *this );
    m_initializers = nullptr;
}

void SymbolResolveVisitor::visit( FunctionDefinition& node )
{
    const auto& initially = node.initially();
    const auto& initiallyLocation = initially->sourceLocation();
    const auto& initiallyRules = AST::make< Rules >( initiallyLocation );

    AST::MappedExpressions::Ptr mappedExpressions = initially;
    if( node.program() )
    {
        if( not m_initializers )
        {
            // no not resolve the program function until the initializers are fetched
            // see: SymbolResolveVisitor::visit( Root& node )
            return;
        }

        mappedExpressions = m_initializers;
    }

    for( const auto& mappedExpression : *mappedExpressions )
    {
        const auto& value = mappedExpression->value();
        if( value->id() == Node::ID::ABSTRACT_EXPRESSION )
        {
            continue;
        }

        const auto& location = AST::make< AST::DirectCallExpression >(
            initiallyLocation,
            AST::IdentifierPath::fromIdentifier( node.identifier() ),
            mappedExpression->arguments() );

        const auto& updateRule = make< AST::UpdateRule >( initiallyLocation, location, value );
        initiallyRules->add( updateRule );
    }

    const auto& initiallyRule = AST::make< AST::SequenceRule >( initiallyLocation, initiallyRules );
    node.setInitiallyRule( initiallyRule );

    pushSymbol( node.ptr< Definition >() );
    RecursiveVisitor::visit( node );
    popSymbol( node.ptr< Definition >() );
}

void SymbolResolveVisitor::visit( DerivedDefinition& node )
{
    pushSymbols< VariableDefinition >( node.arguments() );
    RecursiveVisitor::visit( node );
    popSymbols< VariableDefinition >( node.arguments() );
}

void SymbolResolveVisitor::visit( RuleDefinition& node )
{
    pushSymbols< VariableDefinition >( node.arguments() );
    RecursiveVisitor::visit( node );
    popSymbols< VariableDefinition >( node.arguments() );
}

void SymbolResolveVisitor::visit( EnumerationDefinition& node )
{
    const auto& objectSymbol = node.ptr< TypeDefinition >();
    const auto temporaryObjectDefinition = m_objectTypeDefinition;
    m_objectTypeDefinition = objectSymbol;
    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.domainType()->accept( *this );

    popSymbols< VariableDefinition >( node.templateSymbols() );
    m_objectTypeDefinition = temporaryObjectDefinition;

    m_templateDefinitions->add( node.ptr< Definition >() );
}

void SymbolResolveVisitor::visit( StructureDefinition& node )
{
    const auto& objectSymbol = node.ptr< TypeDefinition >();

    const auto temporaryObjectDefinition = m_objectTypeDefinition;
    m_objectTypeDefinition = nullptr;
    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.domainType()->accept( *this );

    popSymbols< VariableDefinition >( node.templateSymbols() );

    m_objectTypeDefinition = objectSymbol;

    node.functions()->accept( *this );

    m_objectTypeDefinition = temporaryObjectDefinition;
}

void SymbolResolveVisitor::visit( BehaviorDefinition& node )
{
    const auto& objectSymbol = node.ptr< TypeDefinition >();

    const auto temporaryObjectDefinition = m_objectTypeDefinition;
    m_objectTypeDefinition = nullptr;
    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.domainType()->accept( *this );

    m_objectTypeDefinition = objectSymbol;

    node.definitions()->accept( *this );

    popSymbols< VariableDefinition >( node.templateSymbols() );
    m_objectTypeDefinition = temporaryObjectDefinition;
}

void SymbolResolveVisitor::visit( ImplementDefinition& node )
{
    const auto& objectSymbol = node.ptr< TypeDefinition >();

    const auto temporaryObjectDefinition = m_objectTypeDefinition;
    m_objectTypeDefinition = nullptr;
    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.domainType()->accept( *this );

    if( node.forBehaviorType() )
    {
        node.behaviorType()->accept( *this );
    }

    const auto& typeDefinition = node.domainType()->typeDefinition();
    if( not typeDefinition )
    {
        m_log.error( { node.domainType()->sourceLocation() }, "unknown symbol detected!" );
        return;
    }

    assert( typeDefinition and " inconsistent state @ SymbolRegistrationPass " );
    m_objectTypeDefinition = typeDefinition;

    const auto& implementDefinition = node.ptr< ImplementDefinition >();
    if( not node.forBehaviorType() )
    {
        // implement <type>
        try
        {
            typeDefinition->setBasicBehavior( implementDefinition );
        }
        catch( const std::domain_error& e )
        {
            const auto& domainTypeName = node.domainType()->signature();
            const auto& symbol =
                typeDefinition->symboltable()->findNamespace( "*" )->findSymbol( domainTypeName );
            assert( symbol and " inconsistent state " );
            if( &node != symbol.get() )
            {
                const auto& domainTypeName = node.domainType()->signature();
                const auto msg = node.description() + " of basic behavior already defined for '" +
                                 domainTypeName + "'";
                m_log.error( { node.sourceLocation() }, msg, Code::IdentifierIsAlreadyUsed );
                m_log.info( { symbol->sourceLocation() }, msg );
            }
        }
    }
    else
    {
        // implement <behavior> for <type>
        try
        {
            typeDefinition->addExtendedBehavior( implementDefinition );
        }
        catch( const std::domain_error& e )
        {
            const auto& behaviorTypeName = node.behaviorType()->signature();
            const auto& domainTypeName = node.domainType()->signature();
            const auto& symbol =
                typeDefinition->symboltable()->findNamespace( "+" )->findSymbol( behaviorTypeName );
            assert( symbol and " inconsistent state " );
            if( &node != symbol.get() )
            {
                const auto msg = node.description() + " of extended behavior '" + behaviorTypeName +
                                 "' already defined for '" + domainTypeName + "'";
                m_log.error( { node.sourceLocation() }, msg, Code::IdentifierIsAlreadyUsed );
                m_log.info( { symbol->sourceLocation() }, msg );
            }
        }

        if( node.behaviorType()->typeDefinition() )
        {
            const auto& behaviorDefinition =
                node.behaviorType()->typeDefinition()->ptr< BehaviorDefinition >();
            for( const auto& definition : *behaviorDefinition->definitions() )
            {
                if( definition->id() == Node::ID::DECLARATION )
                {
                    continue;
                }

                const auto& definitionInstance = TemplatingPass::duplicate(
                    m_log, definition, node.behaviorType(), node.domainType() );

                const auto& definitionName = definition->identifier()->name();
                try
                {
                    node.symboltable()->registerSymbol( definitionName, definitionInstance );
                }
                catch( const std::domain_error& e )
                {
                    continue;
                }

                node.definitions()->add( definitionInstance );
            }
        }
    }

    node.definitions()->accept( *this );

    popSymbols< VariableDefinition >( node.templateSymbols() );
    m_objectTypeDefinition = temporaryObjectDefinition;
}

void SymbolResolveVisitor::visit( DomainDefinition& node )
{
    const auto& objectSymbol = node.ptr< TypeDefinition >();

    const auto temporaryObjectDefinition = m_objectTypeDefinition;
    m_objectTypeDefinition = objectSymbol;
    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.domainType()->accept( *this );

    popSymbols< VariableDefinition >( node.templateSymbols() );
    m_objectTypeDefinition = temporaryObjectDefinition;
}

void SymbolResolveVisitor::visit( UsingDefinition& node )
{
    const auto& symbolName = node.aliasType()->signature();
    const auto& symbolPath = node.aliasType()->name();

    node.aliasType()->accept( *this );

    const auto& symbol = resolveSymbol( *symbolPath );
    if( not symbol )
    {
        return;
    }
}

void SymbolResolveVisitor::visit( BuiltinDefinition& node )
{
    const auto& name = node.identifier()->name();
    const auto& symbol = m_symboltable.findSymbol( name );
    assert( symbol and " inconsistent state, checked during symbol registration " );

    pushSymbols< VariableDefinition >( node.templateSymbols() );

    node.argumentTypes()->accept( *this );
    node.returnType()->accept( *this );

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
    const auto& symbol = resolveSymbol( *symbolPath );
    if( not symbol )
    {
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

    std::size_t expectedNumberOfArguments = 0;
    const auto scopeSymbolIt = m_scopeSymbols.find( symbolName );
    if( scopeSymbolIt != m_scopeSymbols.cend() )
    {
        const auto& scopeSymbol = scopeSymbolIt->second;
        if( scopeSymbol->id() == Node::ID::VARIABLE_DEFINITION )
        {
            node.setTargetType( DirectCallExpression::TargetType::VARIABLE );
        }
        else if( scopeSymbol->id() == Node::ID::FUNCTION_DEFINITION )
        {
            node.setTargetType( DirectCallExpression::TargetType::FUNCTION );
            const auto& function = std::static_pointer_cast< FunctionDefinition >( scopeSymbol );
            expectedNumberOfArguments = function->argumentTypes()->size();
        }
        else
        {
            m_log.error(
                { sourceLocation },
                "invalid scope symbol " + node.description() + " '" + symbolPath->path() +
                    "' found",
                Code::SymbolIsInvalid );
            return;
        }

        node.setTargetDefinition( scopeSymbol );
        validateArgumentsCount( scopeSymbol->description(), expectedNumberOfArguments );
        return;
    }

    auto symbol = resolveSymbol( *symbolPath );
    if( not symbol )
    {
        return;
    }

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
            node.setTargetType( DirectCallExpression::TargetType::DOMAINTYPE );
            break;
        }
        case Node::ID::DOMAIN_DEFINITION:
        {
            node.setTargetType( DirectCallExpression::TargetType::DOMAINTYPE );
            break;
        }
        case Node::ID::BUILTIN_DEFINITION:
        {
            node.setTargetType( DirectCallExpression::TargetType::BUILTIN );
            const auto& builtin = symbol->ptr< BuiltinDefinition >();
            expectedNumberOfArguments = builtin->argumentTypes()->size();
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

    const auto scopeSymbolIt = m_scopeSymbols.find( node.signature() );
    if( scopeSymbolIt != m_scopeSymbols.cend() )
    {
        const auto& scopeSymbol = scopeSymbolIt->second;
        assert( scopeSymbol->id() == Node::ID::VARIABLE_DEFINITION );
        const auto& variableDefinition = scopeSymbol->ptr< VariableDefinition >();
        node.setTypeDefinition( variableDefinition->objectDefinition() );
        return;
    }

    resolveTypeDefinition( node );
}

void SymbolResolveVisitor::visit( TupleType& node )
{
    RecursiveVisitor::visit( node );
    resolveTypeDefinition( node );
}

void SymbolResolveVisitor::visit( RecordType& node )
{
    RecursiveVisitor::visit( node );
    resolveTypeDefinition( node );
}

void SymbolResolveVisitor::visit( FixedSizedType& node )
{
    RecursiveVisitor::visit( node );
    resolveTypeDefinition( node );
}

void SymbolResolveVisitor::visit( RelationType& node )
{
    RecursiveVisitor::visit( node );

    if( node.mapping() )
    {
        return;
    }

    resolveTypeDefinition( node );
}

void SymbolResolveVisitor::visit( TemplateType& node )
{
    if( node.varadic() )
    {
        const auto scopeSymbolIt = m_scopeSymbols.find( node.signature() );
        if( scopeSymbolIt != m_scopeSymbols.cend() )
        {
            const auto& scopeSymbol = scopeSymbolIt->second;
            assert( scopeSymbol->id() == Node::ID::VARIABLE_DEFINITION );
            const auto& variableDefinition = scopeSymbol->ptr< VariableDefinition >();
            node.setTypeDefinition( variableDefinition->objectDefinition() );
            return;
        }
    }

    resolveTypeDefinition( node );

    const auto& typeDefinition = node.typeDefinition();
    const auto templating = typeDefinition and typeDefinition->domainType().get() != &node;
    if( templating )
    {
        pushSymbols< VariableDefinition >( typeDefinition->templateSymbols() );
    }

    RecursiveVisitor::visit( node );

    if( templating )
    {
        popSymbols< VariableDefinition >( typeDefinition->templateSymbols() );
    }
}

const Types::Ptr& SymbolResolveVisitor::templateTypes( void )
{
    return m_templateTypes;
}

const Definitions::Ptr& SymbolResolveVisitor::templateDefinitions( void )
{
    return m_templateDefinitions;
}

void SymbolResolveVisitor::pushSymbol( const Definition::Ptr& symbol )
{
    if( symbol->id() != Node::ID::FUNCTION_DEFINITION )
    {
        symbol->accept( *this );
    }

    const auto& name = symbol->identifier()->name();
    static const auto THIS( "this" );
    if( name == THIS )
    {
        if( not m_objectTypeDefinition )
        {
            m_log.error(
                { symbol->sourceLocation() },
                "'this' can only be used inside a behavior and implement definition" );
            return;
        }

        assert( symbol->id() == Node::ID::VARIABLE_DEFINITION );
        const auto& variableDefinition = symbol->ptr< VariableDefinition >();
        variableDefinition->setObjectDefinition( m_objectTypeDefinition );
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
        variableBinding->expression()->accept( *this );
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

Definition::Ptr SymbolResolveVisitor::resolveSymbol( const IdentifierPath& node, const u1 silent )
{
    const auto& symbolName = node.path();
    const auto scopeSymbolIt = m_scopeSymbols.find( symbolName );
    if( scopeSymbolIt != m_scopeSymbols.cend() )
    {
        return scopeSymbolIt->second;
    }

    auto symbolResult = m_symboltable.findSymbol( node );
    auto symbol = symbolResult.first;
    auto accessible = symbolResult.second;
    if( not symbol )
    {
        const auto& casmPath =
            IdentifierPath::fromIdentifier( std::make_shared< Identifier >( "CASM" ) );
        for( const auto& identifier : *node.identifiers() )
        {
            casmPath->addIdentifier( identifier );
        }

        symbolResult = m_symboltable.findSymbol( *casmPath );
        symbol = symbolResult.first;
        accessible = symbolResult.second;

        if( not symbol )
        {
            if( not silent )
            {
                m_log.error(
                    { node.sourceLocation() },
                    "unknown " + node.description() + " symbol '" + symbolName + "' found",
                    Code::SymbolIsUnknown );

                m_log.info( { node.sourceLocation() }, m_symboltable.dump() );
            }
            return nullptr;
        }
    }

    if( not accessible )
    {
        if( not silent )
        {
            m_log.error(
                { node.sourceLocation() },
                "'" + symbolName + "' is not accessible",
                Code::SymbolIsInaccessible );
            m_log.warning(
                { symbol->sourceLocation() }, "'" + symbolName + "' has not been exported" );
        }
        return nullptr;
    }

    return resolveAlias( symbol );
}

Definition::Ptr SymbolResolveVisitor::resolveAlias( const Definition::Ptr& definition )
{
    if( definition->id() != Node::ID::USING_DEFINITION )
    {
        return definition;
    }

    const auto& usingDefinition = static_cast< const UsingDefinition& >( *definition );
    usingDefinition.aliasType()->accept( *this );
    return resolveAlias( usingDefinition.aliasType()->typeDefinition() );
}

void SymbolResolveVisitor::resolveTypeDefinition( AST::Type& node )
{
    if( node.typeDefinition() )
    {
        return;
    }

    const auto& typeSymbol = resolveSymbol( *node.signaturePath(), true );
    if( typeSymbol )
    {
        assert(
            typeSymbol->id() == Node::ID::DOMAIN_DEFINITION or
            typeSymbol->id() == Node::ID::ENUMERATION_DEFINITION or
            typeSymbol->id() == Node::ID::BEHAVIOR_DEFINITION or
            typeSymbol->id() == Node::ID::IMPLEMENT_DEFINITION or
            typeSymbol->id() == Node::ID::STRUCTURE_DEFINITION );

        const auto& typeDefinition = typeSymbol->ptr< TypeDefinition >();
        node.setTypeDefinition( typeDefinition );
        return;
    }

    const auto& domainSymbol = resolveSymbol( *node.name() );
    if( not domainSymbol )
    {
        return;
    }

    assert(
        domainSymbol->id() == Node::ID::DOMAIN_DEFINITION or
        domainSymbol->id() == Node::ID::ENUMERATION_DEFINITION or
        domainSymbol->id() == Node::ID::BEHAVIOR_DEFINITION or
        domainSymbol->id() == Node::ID::STRUCTURE_DEFINITION );

    const auto& typeDefinition = domainSymbol->ptr< TypeDefinition >();
    node.setTypeDefinition( typeDefinition );
    return;
}

//
//
// SymbolResolverPass
//

void SymbolResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< CstToAstPass >();
    pu.scheduleAfter< LibraryLoaderPass >();
}

u1 SymbolResolverPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< CstToAstPass >();
    const auto specification = data->specification();
    auto& symboltable = *specification->symboltable();

    NamespaceResolveVisitor namespaceResolveVisitor( log, symboltable );
    specification->ast()->accept( namespaceResolveVisitor );

    if( log.errors() > 0 )
    {
        log.debug( "symbol table =\n" + symboltable.dump() );
        log.debug( "found %lu error(s) during namespace resolving", log.errors() );
        return false;
    }

    SymbolResolveVisitor visitor( log, symboltable );
    specification->ast()->accept( visitor );

    const auto errors = log.errors();
    if( errors > 0 )
    {
        log.debug( "symbol table =\n" + symboltable.dump() );
        log.debug( "found %lu error(s) during symbol resolving", errors );
        return false;
    }

    pr.setOutput< SymbolResolverPass >( visitor.templateTypes(), visitor.templateDefinitions() );
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
