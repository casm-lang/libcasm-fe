//
//  Copyright (C) 2014-2019 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
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

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/SymbolRegistrationPass>
#include <libcasm-fe/import/LibraryLoaderPass>
#include <libcasm-fe/transform/SourceToAstPass>

#include <libcasm-ir/Builtin>

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
            const auto symbolName = std::make_shared< Identifiers >( path.identifiers()->data() );
            symbolName->add( std::make_shared< Identifier >( name ) );
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

    if( useAll and not definition->exported() )
    {
        m_log.debug(
            { node.sourceLocation() }, "omit resolving of not exported symbol '" + pathName + "'" );
        return;
    }

    try
    {
        m_symboltable.registerSymbol( name, definition );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = m_symboltable.findSymbol( name );
        m_log.error( { node.sourceLocation() }, e.what(), Code::IdentifierIsAlreadyUsed );
        m_log.info( { definition->sourceLocation() }, e.what() );
    }

    if( definition->id() == Node::ID::ENUMERATION_DEFINITION )
    {
        const auto enumerationNamespace = m_symboltable.findNamespace( path );
        assert( enumerationNamespace != nullptr );

        try
        {
            m_symboltable.registerNamespace(
                name, enumerationNamespace, Namespace::Visibility::Internal );
        }
        catch( const std::domain_error& e )
        {
            m_log.error( { node.sourceLocation() }, e.what() );
        }
    }
}

//
//
// SymbolResolveVisitor
//

class SymbolResolveVisitor final : public RecursiveVisitor
{
  public:
    SymbolResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

    void visit( InitDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;

    void visit( ReferenceLiteral& node ) override;

    void visit( DirectCallExpression& node ) override;
    void visit( LetExpression& node ) override;
    void visit( ChooseExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( ChooseRule& node ) override;

  private:
    void pushVariable( const VariableDefinition::Ptr& variable );
    void pushVariables( const VariableDefinitions::Ptr& variables );
    void popVariable( const VariableDefinition::Ptr& variable );
    void popVariables( const VariableDefinitions::Ptr& variables );

    void pushVariableBindings( const VariableBindings::Ptr& variableBindings );
    void popVariableBindings( const VariableBindings::Ptr& variableBindings );

    /**
     * If the \a definition is a type alias, it will be resolved and the aliased
     * definition will be returned. Otherwise the given \a definition will be
     * returned.
     */
    Definition::Ptr resolveIfAlias( const Definition::Ptr& definition ) const;

    Definition::Ptr tryResolveSymbol( const IdentifierPath& identifierPath ) const;

  private:
    libcasm_fe::Logger& m_log;
    Namespace& m_symboltable;

    std::unordered_map< std::string, VariableDefinition::Ptr > m_variables;
};

SymbolResolveVisitor::SymbolResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
, m_variables()
{
}

void SymbolResolveVisitor::visit( InitDefinition& node )
{
    RecursiveVisitor::visit( node );
    node.programFunction()->accept( *this );
}

void SymbolResolveVisitor::visit( DerivedDefinition& node )
{
    pushVariables( node.arguments() );
    node.expression()->accept( *this );
    popVariables( node.arguments() );
}

void SymbolResolveVisitor::visit( RuleDefinition& node )
{
    pushVariables( node.arguments() );
    node.rule()->accept( *this );
    popVariables( node.arguments() );
}

void SymbolResolveVisitor::visit( ReferenceLiteral& node )
{
    RecursiveVisitor::visit( node );

    const auto& name = node.identifier()->path();

    if( libcasm_ir::Builtin::available( name ) )
    {
        node.setReferenceType( ReferenceLiteral::ReferenceType::BUILTIN );
        node.setBuiltinId( libcasm_ir::Annotation::find( name ).valueID() );
        return;
    }

    const auto symbol = tryResolveSymbol( *node.identifier() );

    if( not symbol )
    {
        m_log.error(
            { node.identifier()->sourceLocation() },
            "'" + name + "' has not been defined",
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
                { node.identifier()->sourceLocation() },
                "cannot reference '" + symbol->description() + "'" );
        }
    }
}

void SymbolResolveVisitor::visit( DirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    const auto& name = node.identifier()->path();

    const auto validateArgumentsCount = [&]( const std::string& description,
                                             std::size_t expectedNumberOfArguments ) {
        if( node.arguments()->size() != expectedNumberOfArguments )
        {
            m_log.error(
                { node.sourceLocation() },
                "invalid argument size: " + description + " '" + name + "' expects " +
                    std::to_string( expectedNumberOfArguments ) + " arguments",
                Code::SymbolArgumentSizeMismatch );
        }
    };

    const auto variableIt = m_variables.find( name );
    if( variableIt != m_variables.cend() )
    {
        node.setTargetType( DirectCallExpression::TargetType::VARIABLE );
        node.setTargetDefinition( variableIt->second );
        validateArgumentsCount( "variable", 0 );
        return;
    }

    if( libcasm_ir::Builtin::available( name ) )
    {
        const auto& annotation = libcasm_ir::Annotation::find( name );

        node.setTargetType( DirectCallExpression::TargetType::BUILTIN );
        node.setTargetBuiltinId( annotation.valueID() );
        validateArgumentsCount( "builtin", annotation.relations().front().argument.size() );
        return;
    }

    auto symbol = tryResolveSymbol( *node.identifier() );
    if( symbol )
    {
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
                node.setTargetType( DirectCallExpression::TargetType::TYPE_DOMAIN );
                break;
            }
            case Node::ID::USING_DEFINITION:
            {
                // if the using definition points to an IR type then the alias resolving fails,
                // because there is no definition which can be resolved, and we end up here
                node.setTargetType( DirectCallExpression::TargetType::TYPE_DOMAIN );
                break;
            }
            default:
            {
                m_log.error(
                    { node.identifier()->sourceLocation() },
                    "cannot reference '" + symbol->description() + "'" );
                return;
            }
        }

        node.setTargetDefinition( symbol );
        validateArgumentsCount( symbol->description(), expectedNumberOfArguments );
        return;
    }

    static const std::string SELF( "self" );
    static const std::string AGENT( "Agent" );

    if( name == SELF )
    {
        const auto agentSymbol = m_symboltable.findSymbol( AGENT );
        if( not agentSymbol )
        {
            m_log.error( { node.sourceLocation() }, "unable to find '" + AGENT + "' symbol" );
            return;
        }

        node.setTargetType( DirectCallExpression::TargetType::SELF );
        node.setTargetDefinition( agentSymbol );
        validateArgumentsCount( "", 0 );
    }
    else if( TypeInfo::instance().hasType( name ) )
    {
        node.setTargetType( DirectCallExpression::TargetType::TYPE_DOMAIN );
        validateArgumentsCount( "type", 0 );
    }
}

void SymbolResolveVisitor::visit( LetExpression& node )
{
    pushVariableBindings( node.variableBindings() );
    node.expression()->accept( *this );
    popVariableBindings( node.variableBindings() );
}

void SymbolResolveVisitor::visit( ChooseExpression& node )
{
    node.universe()->accept( *this );

    pushVariables( node.variables() );
    node.expression()->accept( *this );
    popVariables( node.variables() );
}

void SymbolResolveVisitor::visit( UniversalQuantifierExpression& node )
{
    node.universe()->accept( *this );

    pushVariables( node.predicateVariables() );
    node.proposition()->accept( *this );
    popVariables( node.predicateVariables() );
}

void SymbolResolveVisitor::visit( ExistentialQuantifierExpression& node )
{
    node.universe()->accept( *this );

    pushVariables( node.predicateVariables() );
    node.proposition()->accept( *this );
    popVariables( node.predicateVariables() );
}

void SymbolResolveVisitor::visit( LetRule& node )
{
    pushVariableBindings( node.variableBindings() );
    node.rule()->accept( *this );
    popVariableBindings( node.variableBindings() );
}

void SymbolResolveVisitor::visit( ForallRule& node )
{
    node.universe()->accept( *this );

    pushVariables( node.variables() );
    node.condition()->accept( *this );
    node.rule()->accept( *this );
    popVariables( node.variables() );
}

void SymbolResolveVisitor::visit( ChooseRule& node )
{
    node.universe()->accept( *this );

    pushVariables( node.variables() );
    node.rule()->accept( *this );
    popVariables( node.variables() );
}

void SymbolResolveVisitor::pushVariable( const VariableDefinition::Ptr& variable )
{
    const auto& name = variable->identifier()->name();

    const auto result = m_variables.emplace( name, variable );
    if( not result.second )
    {
        m_log.error(
            { variable->sourceLocation() },
            "redefinition of symbol '" + name + "'",
            Code::SymbolAlreadyDefined );

        const auto& existingVariable = result.first->second;
        m_log.info(
            { existingVariable->sourceLocation() },
            "previous definition of '" + name + "' is here" );
    }
}

void SymbolResolveVisitor::pushVariables( const VariableDefinitions::Ptr& variables )
{
    for( const auto& variable : *variables )
    {
        pushVariable( variable );
    }
}

void SymbolResolveVisitor::popVariable( const VariableDefinition::Ptr& variable )
{
    const auto& name = variable->identifier()->name();
    m_variables.erase( name );
}

void SymbolResolveVisitor::popVariables( const VariableDefinitions::Ptr& variables )
{
    for( const auto& variable : *variables )
    {
        popVariable( variable );
    }
}

void SymbolResolveVisitor::pushVariableBindings( const VariableBindings::Ptr& variableBindings )
{
    for( const auto& variableBinding : *variableBindings )
    {
        variableBinding->expression()->accept( *this );
        pushVariable( variableBinding->variable() );
    }
}

void SymbolResolveVisitor::popVariableBindings( const VariableBindings::Ptr& variableBindings )
{
    for( const auto& variableBinding : *variableBindings )
    {
        popVariable( variableBinding->variable() );
    }
}

Definition::Ptr SymbolResolveVisitor::resolveIfAlias( const Definition::Ptr& definition ) const
{
    if( definition->id() != Node::ID::USING_DEFINITION )
    {
        return definition;
    }

    const auto usingDefinition = std::static_pointer_cast< UsingDefinition >( definition );
    const auto symbol = tryResolveSymbol( *usingDefinition->type()->name() );

    if( symbol )
    {
        return resolveIfAlias( symbol );  // resolve again, the symbol may be another alias
    }
    else
    {
        return definition;
    }
}

Definition::Ptr SymbolResolveVisitor::tryResolveSymbol( const IdentifierPath& identifierPath ) const
{
    const auto name = identifierPath.path();
    const auto maybeSymbol = m_symboltable.findSymbol( identifierPath );
    const auto symbol = maybeSymbol.first;
    const auto accessible = maybeSymbol.second;

    if( symbol and not accessible )
    {
        m_log.error(
            { identifierPath.sourceLocation() },
            "'" + name + "' is not accessible",
            Code::SymbolIsInaccessible );
        m_log.warning(
            { symbol->sourceLocation() },
            "'" + symbol->identifier()->name() + "' has not been exported" );
    }

    return symbol;
}

//
//
// SymbolResolverPass
//

void SymbolResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< SymbolRegistrationPass >();
    pu.scheduleAfter< LibraryLoaderPass >();
}

u1 SymbolResolverPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();

    NamespaceResolveVisitor namespaceResolveVisitor( log, *specification->symboltable() );
    specification->definitions()->accept( namespaceResolveVisitor );

#ifndef NDEBUG
    log.debug( "symbol table after namespace resolving\n" + specification->symboltable()->dump() );
#endif

    SymbolResolveVisitor visitor( log, *specification->symboltable() );
    specification->definitions()->accept( visitor );

#ifndef NDEBUG
    log.debug( "symbol table = \n" + specification->symboltable()->dump() );
#endif

    const auto errors = log.errors();
    if( errors > 0 )
    {
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
