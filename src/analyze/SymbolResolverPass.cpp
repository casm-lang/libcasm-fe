//
//  Copyright (C) 2014-2018 CASM Organization <https://casm-lang.org>
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                Florian Hahn
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

#include <libcasm-fe/Logger>
#include <libcasm-fe/Namespace>
#include <libcasm-fe/Specification>
#include <libcasm-fe/TypeInfo>
#include <libcasm-fe/ast/RecursiveVisitor>

#include <libcasm-fe/analyze/SymbolRegistrationPass>
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

class SymbolResolveVisitor final : public RecursiveVisitor
{
  public:
    SymbolResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

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

    /**
     * If the \a definition is a type alias, it will be resolved and the aliased
     * definition will be returned. Otherwise the given \a definition will be
     * returned.
     */
    Definition::Ptr resolveIfAlias( const Definition::Ptr& definition ) const;

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

    const auto symbol = m_symboltable.findSymbol( *node.identifier() );
    if( symbol )
    {
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
        return;
    }

    m_log.error(
        { node.identifier()->sourceLocation() },
        "'" + name + "' has not been defined",
        Code::SymbolIsUnknown );
}

void SymbolResolveVisitor::visit( DirectCallExpression& node )
{
    RecursiveVisitor::visit( node );

    assert( node.identifier() );
    const auto& identifier = node.identifier();
    const auto& name = identifier->path();

    if( identifier->type() == IdentifierPath::Type::RELATIVE )
    {
        // only absolute types can be resolved here, relative types will be
        // resolved later in the type inference pass
        return;
    }

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

    auto symbol = m_symboltable.findSymbol( *node.identifier() );
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

    static const auto SELF( "self" );
    static const auto AGENT( "Agent" );
    static const auto SINGLE_AGENT_CONSTANT( "$" );

    if( name == SELF )
    {
        const auto agentSymbol = m_symboltable.findSymbol( AGENT );
        if( not agentSymbol )
        {
            m_log.error( { node.sourceLocation() }, "unable to find 'Agent' symbol" );
            return;
        }

        node.setTargetType( DirectCallExpression::TargetType::SELF );
        node.setTargetDefinition( agentSymbol );
        validateArgumentsCount( "", 0 );
    }
    // single agent execution notation --> agent type domain ==
    // Enumeration!
    else if( name == SINGLE_AGENT_CONSTANT )
    {
        assert( node.targetType() == DirectCallExpression::TargetType::CONSTANT );

        const auto agent = std::make_shared< EnumeratorDefinition >(
            std::make_shared< Identifier >( SINGLE_AGENT_CONSTANT ) );
        const auto agentEnumerators = std::make_shared< Enumerators >();
        agentEnumerators->add( agent );
        const auto agentEnum = std::make_shared< EnumerationDefinition >(
            std::make_shared< Identifier >( AGENT ), agentEnumerators );

        const auto kind = libstdhl::Memory::make< libcasm_ir::Enumeration >( AGENT );
        kind->add( SINGLE_AGENT_CONSTANT );

        const auto type = libstdhl::Memory::make< libcasm_ir::EnumerationType >( kind );
        agent->setType( type );
        agentEnum->setType( type );

        m_symboltable.registerSymbol( AGENT, agentEnum );

        node.setTargetDefinition( agent );
        node.setType( type );
        validateArgumentsCount( agent->description(), 0 );
    }
    else if( TypeInfo::instance().hasType( name ) )
    {
        node.setTargetType( DirectCallExpression::TargetType::TYPE_DOMAIN );
        validateArgumentsCount( "type", 0 );
    }
    else
    {
        m_log.error(
            { node.sourceLocation() },
            "unknown symbol '" + name + "' found",
            Code::SymbolIsUnknown );
    }

    m_log.debug( "call: " + name + "{ " + node.targetTypeName() + " }" );
}

void SymbolResolveVisitor::visit( LetExpression& node )
{
    node.initializer()->accept( *this );

    pushVariable( node.variable() );
    node.expression()->accept( *this );
    popVariable( node.variable() );
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
    node.expression()->accept( *this );

    pushVariable( node.variable() );
    node.rule()->accept( *this );
    popVariable( node.variable() );
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

Definition::Ptr SymbolResolveVisitor::resolveIfAlias( const Definition::Ptr& definition ) const
{
    if( definition->id() != Node::ID::USING_DEFINITION )
    {
        return definition;
    }

    const auto usingDefinition = std::static_pointer_cast< UsingDefinition >( definition );
    const auto symbol = m_symboltable.findSymbol( *usingDefinition->type()->name() );
    if( symbol )
    {
        return resolveIfAlias( symbol );  // resolve again, the symbol may be another alias
    }
    else
    {
        return definition;
    }
}

void SymbolResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< SourceToAstPass >();
    pu.scheduleAfter< SymbolRegistrationPass >();
}

u1 SymbolResolverPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.output< SourceToAstPass >();
    const auto specification = data->specification();

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
