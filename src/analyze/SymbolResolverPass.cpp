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

#include "SymbolResolverPass.h"

#include "../pass/src/PassRegistry.h"
#include "../pass/src/PassResult.h"
#include "../pass/src/PassUsage.h"

#include "../Logger.h"
#include "../analyze/AttributionPass.h"
#include "../ast/RecursiveVisitor.h"

#include "../casm-ir/src/Builtin.h"

using namespace libcasm_fe;
using namespace Ast;

char SymbolResolverPass::id = 0;

static libpass::PassRegistration< SymbolResolverPass > PASS(
    "ASTSymbolResolverPass",
    "resolves all AST identifiers and creates a symbol table", "ast-symtbl",
    0 );

//
// SymbolTableVisitor
//

class SymbolTableVisitor final : public RecursiveVisitor
{
  public:
    SymbolTableVisitor( Logger& m_log, Namespace& symboltable );

    void visit( FunctionDefinition& node ) override;
    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;
    void visit( EnumerationDefinition& node ) override;

  private:
    Logger& m_log;
    Namespace& m_symboltable;
};

SymbolTableVisitor::SymbolTableVisitor( Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
{
}

void SymbolTableVisitor::visit( FunctionDefinition& node )
{
    try
    {
        m_symboltable.registerSymbol( node.ptr< FunctionDefinition >() );
    }
    catch( const std::domain_error& e )
    {
        const auto& symbol = m_symboltable.find( node );
        const auto& name = node.identifier()->name();

        if( name == "program" )
        {
            m_log.error( { node.sourceLocation(),
                             symbol.definition()->sourceLocation() },
                "init already defined",
                Code::AgentInitRuleMultipleDefinitions );
        }
        else
        {
            m_log.error( { node.sourceLocation(),
                             symbol.definition()->sourceLocation() },
                "function '" + name + "' already defined",
                Code::FunctionDefinitionAlreadyUsed );
        }
    }
    RecursiveVisitor::visit( node );
}

void SymbolTableVisitor::visit( DerivedDefinition& node )
{
    try
    {
        m_symboltable.registerSymbol( node.ptr< DerivedDefinition >() );
    }
    catch( const std::domain_error& e )
    {
        auto symbol = m_symboltable.find( node );

        m_log.error(
            { node.sourceLocation(), symbol.definition()->sourceLocation() },
            e.what(), Code::DerivedDefinitionAlreadyUsed );
    }

    RecursiveVisitor::visit( node );
}

void SymbolTableVisitor::visit( RuleDefinition& node )
{
    try
    {
        m_symboltable.registerSymbol( node.ptr< RuleDefinition >() );
    }
    catch( const std::domain_error& e )
    {
        m_log.error( { node.sourceLocation() }, e.what(),
            Code::RuleDefinitionAlreadyUsed );
    }

    RecursiveVisitor::visit( node );
}

void SymbolTableVisitor::visit( EnumerationDefinition& node )
{
    try
    {
        m_symboltable.registerSymbol( node.ptr< EnumerationDefinition >() );
    }
    catch( const std::domain_error& e )
    {
        m_log.error( { node.sourceLocation() }, e.what() );
    }

    RecursiveVisitor::visit( node );
}

//
// SymbolResolveVisitor
//

class SymbolResolveVisitor final : public RecursiveVisitor
{
  public:
    SymbolResolveVisitor( Logger& log, Namespace& symboltable );

    void visit( DerivedDefinition& node ) override;
    void visit( RuleDefinition& node ) override;

    void visit( DirectCallExpression& node ) override;

    void visit( LetExpression& node ) override;
    void visit( ChooseExpression& node ) override;
    void visit( UniversalQuantifierExpression& node ) override;
    void visit( ExistentialQuantifierExpression& node ) override;

    void visit( UpdateRule& node ) override;
    void visit( LetRule& node ) override;
    void visit( ForallRule& node ) override;
    void visit( ChooseRule& node ) override;

  private:
    void push( VariableDefinition& identifier );
    void pop( VariableDefinition& identifier );

    Logger& m_log;
    Namespace& m_symboltable;

    class Variable
    {
      public:
        Variable( const std::string& name, const std::size_t localIndex,
            const VariableDefinition::Ptr& definition )
        : m_name( name )
        , m_localIndex( localIndex )
        , m_definition( definition )
        {
        }

        std::string name( void ) const
        {
            return m_name;
        }

        std::size_t localIndex( void ) const
        {
            return m_localIndex;
        }

        const VariableDefinition::Ptr& definition( void ) const
        {
            return m_definition;
        }

      private:
        std::string m_name;
        std::size_t m_localIndex;
        const VariableDefinition::Ptr m_definition;
    };

    std::vector< Variable > m_variables;
    std::size_t m_maxNumberOfLocals; /**< Used to calculate the minimum number
                                        of frame slots required for derived
                                        functions and rules during execution */
};

SymbolResolveVisitor::SymbolResolveVisitor(
    Logger& log, Namespace& symboltable )
: m_log( log )
, m_symboltable( symboltable )
, m_maxNumberOfLocals( 0 )
{
}

void SymbolResolveVisitor::visit( DerivedDefinition& node )
{
    m_maxNumberOfLocals = 0;

    for( const auto& argument : *node.arguments() )
    {
        push( *argument );
    }

    node.expression()->accept( *this );

    const auto end = node.arguments()->rend();
    for( auto it = node.arguments()->rbegin(); it != end; ++it )
    {
        pop( **it );
    }

    node.setMaximumNumberOfLocals( m_maxNumberOfLocals );
}

void SymbolResolveVisitor::visit( RuleDefinition& node )
{
    m_maxNumberOfLocals = 0;

    for( const auto& argument : *node.arguments() )
    {
        push( *argument );
    }

    node.rule()->accept( *this );

    const auto end = node.arguments()->rend();
    for( auto it = node.arguments()->rbegin(); it != end; ++it )
    {
        pop( **it );
    }

    node.setMaximumNumberOfLocals( m_maxNumberOfLocals );
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
            auto symbol = m_symboltable.find( node );
            node.setTargetType( symbol.targetType() );

            if( symbol.targetType() == CallExpression::TargetType::TYPE_DOMAIN
                or symbol.targetType() == CallExpression::TargetType::CONSTANT )
            {
                const auto& type = symbol.definition()->type();

                if( not type )
                {
                    if( symbol.definition()->id()
                        == Node::ID::ENUMERATION_DEFINITION )
                    {
                        const auto& definition
                            = std::static_pointer_cast< EnumerationDefinition >(
                                symbol.definition() );

                        const auto& name
                            = ( symbol.targetType()
                                  == CallExpression::TargetType::CONSTANT )
                                  ? path.baseDir()
                                  : path.path();

                        m_log.debug(
                            "creating IR enumeration type '" + name + "'" );

                        auto kind
                            = libstdhl::make< libcasm_ir::Enumeration >( name );

                        for( auto e : *definition->enumerators() )
                        {
                            kind->add( e->name() );
                        }

                        const auto type
                            = libstdhl::make< libcasm_ir::EnumerationType >(
                                kind );

                        definition->setType( type );

                        node.setType( definition->type() );
                    }
                    else
                    {
                        assert( 0 );
                    }
                }
                else
                {
                    node.setType( type );
                }
            }

            node.setTargetDefinition( symbol.definition() );
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
                const auto variable
                    = std::find_if( m_variables.rbegin(), m_variables.rend(),
                        [&]( const Variable& v ) { return v.name() == name; } );

                if( variable != m_variables.rend() )
                {
                    node.setTargetType( CallExpression::TargetType::VARIABLE );
                    node.setTargetDefinition( variable->definition() );
                }
                else if( name == "self" )
                {
                    assert( node.targetType()
                            == CallExpression::TargetType::UNKNOWN );
                    node.setTargetType( CallExpression::TargetType::SELF );
                }
                // single agent execution notation --> agent type domain ==
                // Enumeration!
                else if( name == "$" )
                {
                    assert( node.targetType()
                            == CallExpression::TargetType::CONSTANT );

                    auto kind
                        = libstdhl::make< libcasm_ir::Enumeration >( "Agent" );
                    kind->add( "$" );

                    const auto type
                        = libstdhl::make< libcasm_ir::EnumerationType >( kind );

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
                    auto code = Code::SymbolIsUnknown;
                    if( node.targetType()
                        == CallExpression::TargetType::FUNCTION )
                    {
                        code = Code::FunctionSymbolIsUnknown;
                    }

                    m_log.error( { node.sourceLocation() },
                        "unknown " + node.targetTypeName() + " symbol '"
                            + path.path()
                            + "' found",
                        code );
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

    push( *node.variable() );
    node.expression()->accept( *this );
    pop( *node.variable() );
}

void SymbolResolveVisitor::visit( ChooseExpression& node )
{
    node.universe()->accept( *this );

    push( *node.variable() );
    node.expression()->accept( *this );
    pop( *node.variable() );
}

void SymbolResolveVisitor::visit( UniversalQuantifierExpression& node )
{
    node.universe()->accept( *this );

    push( *node.predicateVariable() );
    node.proposition()->accept( *this );
    pop( *node.predicateVariable() );
}

void SymbolResolveVisitor::visit( ExistentialQuantifierExpression& node )
{
    node.universe()->accept( *this );

    push( *node.predicateVariable() );
    node.proposition()->accept( *this );
    pop( *node.predicateVariable() );
}

void SymbolResolveVisitor::visit( UpdateRule& node )
{
    RecursiveVisitor::visit( node );

    assert( node.function() );
    const auto& function = *node.function();
    const auto& path = *function.identifier();

    if( function.targetType() != CallExpression::TargetType::FUNCTION )
    {
        m_log.error( { function.sourceLocation() },
            "updating " + function.targetTypeName() + " '" + path.path()
                + "' is not allowed, only function symbols are valid",
            Code::UpdateRuleFunctionSymbolIsInvalid );
    }
}

void SymbolResolveVisitor::visit( LetRule& node )
{
    node.expression()->accept( *this );

    push( *node.variable() );
    node.rule()->accept( *this );
    pop( *node.variable() );
}

void SymbolResolveVisitor::visit( ForallRule& node )
{
    node.universe()->accept( *this );

    push( *node.variable() );
    node.rule()->accept( *this );
    pop( *node.variable() );
}

void SymbolResolveVisitor::visit( ChooseRule& node )
{
    node.universe()->accept( *this );

    push( *node.variable() );
    node.rule()->accept( *this );
    pop( *node.variable() );
}

void SymbolResolveVisitor::push( VariableDefinition& node )
{
    const auto& name = node.identifier()->name();

    const auto variable
        = std::find_if( m_variables.rbegin(), m_variables.rend(),
            [&]( const Variable& v ) { return v.name() == name; } );

    if( variable != m_variables.rend() )
    {
        m_log.error( { node.sourceLocation() },
            "redefinition of symbol '" + name + "'",
            Code::SymbolAlreadyDefined );

        m_log.info( { variable->definition()->sourceLocation() },
            "previous definition of '" + name + "' is here" );
    }

    const std::size_t localIndex = m_variables.size(); // used during execution
    m_variables.emplace_back(
        name, localIndex, node.ptr< VariableDefinition >() );

    node.setLocalIndex( localIndex );
    m_maxNumberOfLocals = std::max( m_maxNumberOfLocals, m_variables.size() );
}

void SymbolResolveVisitor::pop( VariableDefinition& node )
{
    assert(
        m_variables.back().definition() == node.ptr< VariableDefinition >() );
    m_variables.pop_back();
}

//
// SymbolResolverPass
//

void SymbolResolverPass::usage( libpass::PassUsage& pu )
{
    pu.require< AttributionPass >();
}

u1 SymbolResolverPass::run( libpass::PassResult& pr )
{
    Logger log( &id, stream() );

    const auto data = pr.result< AttributionPass >();
    const auto specification = data->specification();

    const auto symboltable = std::make_shared< Namespace >();

    SymbolTableVisitor symbolTableGenerator( log, *symboltable );
    specification->accept( symbolTableGenerator );

    const auto symTblErr = log.errors();
    if( symTblErr > 0 )
    {
        log.debug(
            "found %lu error(s) during symbol table creation", symTblErr );
        return false;
    }

    SymbolResolveVisitor symbolResolver( log, *symboltable );
    specification->accept( symbolResolver );

    const auto symResErr = log.errors();
    if( symResErr > 0 )
    {
        log.debug( "found %lu error(s) during symbol resolving", symResErr );
        return false;
    }

#ifndef NDEBUG
    log.debug( "symbol table = \n" + symboltable->dump() );
#endif

    pr.setResult< SymbolResolverPass >(
        libstdhl::make< Data >( specification, symboltable ) );

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
