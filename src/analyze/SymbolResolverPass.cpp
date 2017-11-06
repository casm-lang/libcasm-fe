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

#include "../Logger.h"
#include "../analyze/AttributionPass.h"
#include "../ast/RecursiveVisitor.h"

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
    "resolves AST identifiers of type-, call-, ... nodes", "ast-sym-resolve",
    0 );

class SymbolResolveVisitor final : public RecursiveVisitor
{
  public:
    SymbolResolveVisitor( libcasm_fe::Logger& log, Namespace& symboltable );

    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;

    void visit( ReferenceAtom& node ) override;
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
    void popVariable( const VariableDefinition::Ptr& variable );

    libcasm_fe::Logger& m_log;
    Namespace& m_symboltable;

    std::unordered_map< std::string, VariableDefinition::Ptr > m_variables;
};

SymbolResolveVisitor::SymbolResolveVisitor(
    libcasm_fe::Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
, m_variables()
{
}

void SymbolResolveVisitor::visit( DerivedDefinition& node )
{
    for( const auto& argument : *node.arguments() )
    {
        pushVariable( argument );
    }

    node.expression()->accept( *this );

    const auto end = node.arguments()->rend();
    for( auto it = node.arguments()->rbegin(); it != end; ++it )
    {
        popVariable( *it );
    }
}

void SymbolResolveVisitor::visit( RuleDefinition& node )
{
    for( const auto& argument : *node.arguments() )
    {
        pushVariable( argument );
    }

    node.rule()->accept( *this );

    const auto end = node.arguments()->rend();
    for( auto it = node.arguments()->rbegin(); it != end; ++it )
    {
        popVariable( *it );
    }
}

void SymbolResolveVisitor::visit( ReferenceAtom& node )
{
    RecursiveVisitor::visit( node );

    try
    {
        const auto symbol = m_symboltable.find( *node.identifier() );

        switch( symbol.targetType() )
        {
            case CallExpression::TargetType::FUNCTION:
            {
                node.setReferenceType( ReferenceAtom::ReferenceType::FUNCTION );
                node.setReference( symbol.definition() );
                break;
            }
            case CallExpression::TargetType::DERIVED:
            {
                node.setReferenceType( ReferenceAtom::ReferenceType::DERIVED );
                node.setReference( symbol.definition() );
                break;
            }
            case CallExpression::TargetType::BUILTIN:
            {
                // TODO

                // node.setReferenceType(
                // ReferenceAtom::ReferenceType::BUILTIN
                // );
                // node.setBuiltinId( annotation.id() );
                break;
            }
            case CallExpression::TargetType::RULE:
            {
                node.setReferenceType( ReferenceAtom::ReferenceType::RULE );
                node.setReference( symbol.definition() );
                break;
            }
            default:
            {
                m_log.error( { node.identifier()->sourceLocation() },
                    "cannot reference '" + CallExpression::targetTypeString(
                                               symbol.targetType() )
                        + "'" );
            }
        }
    }
    catch( const std::domain_error& e )
    {
        m_log.error( { node.identifier()->sourceLocation() },
            "'" + node.identifier()->path() + "' has not been defined",
            Code::SymbolIsUnknown );
    }
}

void SymbolResolveVisitor::visit( DirectCallExpression& node )
{
    const auto& path = *node.identifier();

    if( path.type() == IdentifierPath::Type::RELATIVE )
    {
        m_log.debug( "call: symbol '" + path.path() + "' is relative" );

        if( path.identifiers()->size() != 1 )
        {
            m_log.error( { node.sourceLocation() },
                "invalid relative path '" + path.path() + "' found" );
        }
    }
    else
    {
        try
        {
            const auto& symbol = m_symboltable.find( node );

            node.setTargetType( symbol.targetType() );
            node.setTargetDefinition( symbol.definition() );

            if( symbol.targetType() == CallExpression::TargetType::TYPE_DOMAIN
                or symbol.targetType() == CallExpression::TargetType::CONSTANT )
            {
                node.setType( symbol.definition()->type() );
            }
        }
        catch( const std::domain_error& e )
        {
            const auto& name = path.baseName();

            if( libcasm_ir::Builtin::available(
                    name, node.arguments()->size() ) )
            {
                try
                {
                    m_symboltable.registerSymbol(
                        node.ptr< DirectCallExpression >(),
                        CallExpression::TargetType::BUILTIN );
                    node.setTargetType( CallExpression::TargetType::BUILTIN );
                }
                catch( const std::domain_error& e )
                {
                    m_log.error( { node.sourceLocation() }, e.what() );
                }
            }
            else
            {
                const auto it = m_variables.find( name );
                if( it != m_variables.cend() )
                {
                    const auto& variable = it->second;

                    node.setTargetType( CallExpression::TargetType::VARIABLE );
                    node.setTargetDefinition( variable );
                }
                else if( name == "self" )
                {
                    try
                    {
                        const auto& symbol = m_symboltable.find( "Agent" );
                        node.setTargetType( CallExpression::TargetType::SELF );
                        node.setTargetDefinition( symbol.definition() );
                    }
                    catch( const std::domain_error& e )
                    {
                        m_log.error( { node.sourceLocation() },
                            "unable to find 'Agent' symbol" );
                    }
                }
                // single agent execution notation --> agent type domain ==
                // Enumeration!
                else if( name == "$" )
                {
                    assert( node.targetType()
                            == CallExpression::TargetType::CONSTANT );

                    const auto kind
                        = libstdhl::Memory::make< libcasm_ir::Enumeration >(
                            "Agent" );
                    kind->add( "$" );

                    const auto type
                        = libstdhl::Memory::make< libcasm_ir::EnumerationType >(
                            kind );
                    node.setType( type );

                    m_symboltable.registerSymbol( "Agent",
                        node.ptr< DirectCallExpression >(),
                        CallExpression::TargetType::TYPE_DOMAIN );

                    m_symboltable.registerSymbol(
                        node.ptr< DirectCallExpression >(),
                        CallExpression::TargetType::CONSTANT );
                    node.setTargetType( CallExpression::TargetType::CONSTANT );
                }
                else
                {
                    m_log.error( { node.sourceLocation() },
                        "unknown " + node.targetTypeName() + " symbol '"
                            + path.path()
                            + "' found",
                        ( node.targetType()
                            == CallExpression::TargetType::FUNCTION )
                            ? Code::FunctionSymbolIsUnknown
                            : Code::SymbolIsUnknown );
                }
            }
        }

        m_log.debug(
            "call: " + path.path() + "{ " + node.targetTypeName() + " }" );
    }

    RecursiveVisitor::visit( node );
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

    pushVariable( node.variable() );
    node.expression()->accept( *this );
    popVariable( node.variable() );
}

void SymbolResolveVisitor::visit( UniversalQuantifierExpression& node )
{
    node.universe()->accept( *this );

    pushVariable( node.predicateVariable() );
    node.proposition()->accept( *this );
    popVariable( node.predicateVariable() );
}

void SymbolResolveVisitor::visit( ExistentialQuantifierExpression& node )
{
    node.universe()->accept( *this );

    pushVariable( node.predicateVariable() );
    node.proposition()->accept( *this );
    popVariable( node.predicateVariable() );
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

    pushVariable( node.variable() );
    node.condition()->accept( *this );
    node.rule()->accept( *this );
    popVariable( node.variable() );
}

void SymbolResolveVisitor::visit( ChooseRule& node )
{
    node.universe()->accept( *this );

    pushVariable( node.variable() );
    node.rule()->accept( *this );
    popVariable( node.variable() );
}

void SymbolResolveVisitor::pushVariable( const VariableDefinition::Ptr& variable )
{
    const auto& name = variable->identifier()->name();

    const auto result = m_variables.emplace( name, variable );
    if( not result.second )
    {
        m_log.error( { variable->sourceLocation() },
            "redefinition of symbol '" + name + "'",
            Code::SymbolAlreadyDefined );

        const auto& existingVariable = result.first->second;
        m_log.info( { existingVariable->sourceLocation() },
            "previous definition of '" + name + "' is here" );
    }
}

void SymbolResolveVisitor::popVariable( const VariableDefinition::Ptr& variable )
{
    const auto& name = variable->identifier()->name();
    m_variables.erase( name );
}

void SymbolResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< SymbolRegistrationPass >();
}

u1 SymbolResolverPass::run( libpass::PassResult& pr )
{
    libcasm_fe::Logger log( &id, stream() );

    const auto data = pr.result< SymbolRegistrationPass >();
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

    pr.setResult< SymbolResolverPass >( data );

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
